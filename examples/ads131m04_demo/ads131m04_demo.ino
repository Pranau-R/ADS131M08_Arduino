// Test code for the ADS131M04 library
// Daniele Valentino Bella

#include "ADS131M04.h"
#include <Arduino.h>
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

// SPIClass ADCSPI=SPIClass(VSPI);

ADS131M04 ads = ADS131M04(D5, &gSPI2, D12, 8192000);

void printData() {

  /*int32_t outputArray[4];
  
  int8_t channelArr[4] = {0, 1, 2, 3};

  ads.rawChannels(&channelArr[0], 4, &outputArray[0]);

  for (int8_t i = 0; i<4; i++) {
    Serial.print("CH"); Serial.print(i);
    Serial.print(" : ");
    Serial.print(outputArray[i], HEX);
    Serial.print(" ");

  } */
  
  int8_t channel = 0;
  Serial.print("CH0: ");
  Serial.println(ads.readChannelSingle(channel), HEX);
  // Serial.println(" ");
}

void setup() {
  gCatena.begin();
  
  gSPI2.begin();

  ads.init();
  Serial.println("Initialised! Reading all Registers:");

  // Set chip select pins to high
  pinMode(D5, OUTPUT);
  digitalWrite(D5, HIGH);

  // Try to read every single register
  for (uint8_t i=0x00; i<=0x3F; i++) {
    Serial.print("Result for: 0x");
    Serial.print(i);
    Serial.print(" : 0x");
    Serial.println(ads.readReg(i), HEX);
  }
  Serial.println(" ---------------------------------- ");
}

void loop() {
  /*
  printData();

  delay(100);
*/
//  printData();
  // Try writing the gain; and then reading that register
  printData();
  // printData();
  // printData();
/*
  Serial.print("Writing: ");
  Serial.println(ads.setGain(3,3,3,3));
  */
  Serial.print("Write Success? [1]Yes [0]No :");
  Serial.println(ads.writeReg(0x04,0x6767));
  Serial.print("Reading: 0x00");
  Serial.println(ads.readReg(0x04), HEX);
  Serial.println("#######################");

  delay(1000);

  printData();
  printData();
  printData();

  /* Serial.print("Writing: ");
  Serial.println(ads.setGain());
  */
  /*
  Serial.println(ads.writeReg(0x04,0x0000));
  Serial.print("Reading: ");
  Serial.println(ads.readReg(0x04));
  Serial.println("#######################");
*/
  //delay(1000);
  // Try putting to sleep and waking it up
  /*
  printData();
  printData();
  printData();
  Serial.println("Putting to sleep...");
  ads.sendCommand(0x0022);
  printData();
  printData();
  printData();

  Serial.println("Waking up... ");
  ads.sendCommand(0x0033);
  printData();
  printData();
  printData();
  */
}