#ifndef ADS131M04_H
#define ADS131M04_H
//ADS131M04.cpp LGPL 
//Adapted for the 8 channel device from https://github.com/icl-rocketry/ADS131M04-Lib (LGPL)


/* Definitions of all the addresses of the registers of the ADS131M04
   Chip. For the content of the registers, please refer to the datasheet:

   https://www.ti.com/lit/gpn/ads131m04

   Written by Imperial College London Rocketry
   Electronics subteam
*/

#include <Arduino.h>
#include <SPI.h>

#define ADS131_ID 0x00
#define ADS131_STATUS 0x01
#define ADS131_MODE 0x02
#define ADS131_CLOCK 0x03
#define ADS131_GAIN1 0x04
#define ADS131_CFG 0x06
#define ADS131_THRSHLD_MSB 0x07
#define ADS131_THRSHLD_LSB 0x08

#define ADS131_CH0_CFG 0x09
#define ADS131_CH0_OCAL_MSB 0x0A
#define ADS131_CH0_OCAL_LSB 0x0B
#define ADS131_CH0_GCAL_MSB 0x0C
#define ADS131_CH0_GCAL_LSB 0x0D
#define ADS131_CH1_CFG 0x0E
#define ADS131_CH1_OCAL_MSB 0x0F
#define ADS131_CH1_OCAL_LSB 0x10
#define ADS131_CH1_GCAL_MSB 0x11
#define ADS131_CH1_GCAL_LSB 0x12
#define ADS131_CH2_CFG 0x13
#define ADS131_CH2_OCAL_MSB 0x14
#define ADS131_CH2_OCAL_LSB 0x15
#define ADS131_CH2_GCAL_MSB 0x16
#define ADS131_CH2_GCAL_LSB 0x17
#define ADS131_CH3_CFG 0x18
#define ADS131_CH3_OCAL_MSB 0x19
#define ADS131_CH3_OCAL_LSB 0x1A
#define ADS131_CH3_GCAL_MSB 0x1B
#define ADS131_CH3_GCAL_LSB 0x1C

#define ADS131_REGMAP_CRC 0x3E
#define ADS131_RESERVED 0x3F


class ADS131M04 {
    public:

    SPIClass * spi = NULL; // SPISettings(spiClk, MSBFIRST, SPI_MODE1)
    int csPIN, DRDY;
    int SpiClk;

    bool firstRead = true;
    int nFrameWords = 10;
    // Dummy word frame to write ADC during ADC data reads
    ADS131M04(int cs, SPIClass* _spi, int8_t _clkoutPin, int clk);
    void init(int clkin = 8192000);
    void readChannels(int8_t * channelArrPtr, int8_t channelArrLen, int32_t * outputArrPtr);
    void readAllChannels(int32_t inputArr[4]);
    int32_t readChannelSingle(int8_t channel);
    bool globalChop(bool enabled, uint8_t log2delay);
    bool writeReg(uint8_t reg, uint16_t data);
    uint16_t readReg(uint8_t reg);
    bool setGain(int gain);
    uint32_t spiTransferWord(uint16_t inputData = 0x0000);
    void spiCommFrame(uint32_t * outPtr, uint16_t command = 0x0000);
    int32_t twoCompDeco(uint32_t data);

};

#endif
