#include "ADS131M08.h"
#include <Catena.h>
#include <SPI.h>

using namespace McciCatena;

// the primary object
Catena gCatena;

SPIClass gSPI2(
    Catena::PIN_SPI2_MOSI,
    Catena::PIN_SPI2_MISO,
    Catena::PIN_SPI2_SCK
    );

#define CS_PIN                5
#define DRDY_PIN              12

int CLKOUT  =                 8192000; //XTAL speed (50% duty cycle PWM)

ADS131M08 adc(CS_PIN, DRDY_PIN, 8192000);

unsigned long long sampleNum = 0;
char outputarr[128];

void setup() {
  // put your setup code here, to run once:
  gCatena.begin();
  
  gSPI2.begin();

  Serial.begin(1000000);
  adc.init(CLKOUT);

  delay(100);


  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);

  adc.writeReg(ADS131_CLOCK,0b1111111100011010); //Clock register (page 55 in datasheet)
  /*CLOCK REG SETTINGS
   * Bytes 15-8: ADC Channel enable/disable
   * Byte 7: Crystal disable 
   * Byte 6: External Reference Enable
   * Byte 5: Reserved
   * Bytes 4-2: Modulator Oversampling 000 = 128 OSR (32ksps), 111 = 16256 OSR (250sps)
   * Bytes 1-0: Power mode selections 11 or 10 = high resolution, 01 = low power, 00 = very low power
   */

  //adc.writeReg(ADS131_CFG,0b0000000000000000);

  //DC Block Filter settings:
  //adc.writeReg(ADS131_THRSHLD_LSB,0b0000000000001010);

  //Channel settings
  //adc.writeReg(ADS131_CH0_CFG,0b0000000000000000);

  //Gain settings, 1-128 (increasing by factor of 2)
  adc.setGain(32);

   
  uint16_t clkreg = adc.readReg(ADS131_CLOCK);
  Serial.print("CLOCK: ");
  Serial.println(clkreg,BIN);
  

  
  uint16_t gainreg = adc.readReg(ADS131_GAIN1);
  Serial.print("GAIN1: ");
  Serial.println(gainreg, BIN);
  
  //adc.globalChop(true,2);
  
  uint16_t id = adc.readReg(ADS131_ID);
  Serial.print("ID: ");
  Serial.println(id, BIN);
  
  uint16_t stat = adc.readReg(ADS131_STATUS);
  Serial.print("Status: ");
  Serial.println(stat, BIN);

  uint16_t Mode = adc.readReg(ADS131_MODE);
  Serial.print("Mode: ");
  Serial.println(Mode, BIN);

  Serial.println("Starting in 3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...");
  delay(1000);

}


void loop() {
 if(digitalRead(DRDY_PIN)) {

    //Serial.println(adc.readChannelSingle(0)); //Just read the first one
    int32_t channelArr[4];
    adc.readAllChannels(channelArr);
    sprintf(outputarr, "%d|%d|%d|%d|%d|%d|%d|%d|%lu\r\n", 
              channelArr[0], 
              channelArr[1], 
              channelArr[2],
              channelArr[3],
              );
              
    Serial.print(outputarr);
//    Serial.print(channelArr[0]);
//    Serial.print("|");
//    Serial.print("\r\n");
    sampleNum++;
  }
  else {
  }
}
