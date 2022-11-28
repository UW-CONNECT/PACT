/*
 * ax5043.c
 *
 *  Created on: 2022
 *      Author: Yoganand
 */

#include "ax5043.h"
#include <msp430.h>
#include <stdint.h>
#include <ax5043_reg_values.h>

#define DUMMY   0x00

#define AX_FIFO_TXDATA_UNENC    (1 << 5) /* Bypass framing and encoder */
#define AX_FIFO_TXDATA_RAW      (1 << 4) /* Bypass framing */
#define AX_FIFO_TXDATA_NOCRC    (1 << 3) /* Don't generate CRC */
#define AX_FIFO_TXDATA_RESIDUE  (1 << 2) /* Residue mode on last byte */
#define AX_FIFO_TXDATA_PKTEND   (1 << 1) /* END flag */
#define AX_FIFO_TXDATA_PKTSTART (1 << 0) /* START flag */

#define AX_FIFO_CHUNK_TXCTRL        0x3C /* Transmit Control (Antenna, Power Amp) */
#define AX_FIFO_CHUNK_REPEATDATA    0x62 /* Repeat Data */
#define AX_FIFO_CHUNK_TXPWR         0xFD /* Transmit Power */


#define SLAVE_CS_OUT    P2OUT
#define SLAVE_CS_DIR    P2DIR
#define SLAVE_CS_PIN    BIT4

SPI_Mode MasterMode = IDLE_MODE;
#define MAX_BUFFER_SIZE     2

uint16_t TransmitRegAddr = 0;

uint8_t ReceiveBuffer[1] = {0};
uint8_t RXByteCtr = 0;
uint8_t ReceiveIndex = 0;
uint16_t TransmitBuffer[MAX_BUFFER_SIZE] = {0};
uint16_t TransmitBuffer1[5] = {0};
uint8_t TXByteCtr = 0;
uint8_t TransmitIndex = 0;

uint8_t Addr[1] ={0};

uint16_t Reg3 = 0;
uint8_t Reg4[1] = {0};
uint16_t Reg1 = 0;
uint16_t Reg2 = 0;

// This function is populated with output from RadioLab config.c file
// Update accordingly for customizations.
/*
int ax5043_init()
{
    ax5043_radio_setup_tx();

    SPI_Master_WriteReg(AX5043_PLLLOOP, 0x09, 2);
    SPI_Master_WriteReg(AX5043_PLLCPI, 0x08, 2);

    SPI_Master_WriteReg(AX5043_PWRMODE, AX5043_PWRSTATE_XTAL_ON, 2);
    SPI_Master_WriteReg(AX5043_MODULATION, 0x08, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV2, 0x00, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV1, 0x00, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV0, 0x00, 2);

    ax5043_wait_for_xtal();

    uint32_t f = 0x1a7f9801;
    SPI_Master_WriteReg(AX5043_FREQA0, f, 2);
    SPI_Master_WriteReg(AX5043_FREQA1, f >> 8, 2);
    SPI_Master_WriteReg(AX5043_FREQA2, f >> 16, 2);
    SPI_Master_WriteReg(AX5043_FREQA3, f >> 24, 2);


    SPI_Master_WriteReg(AX5043_IRQMASK1, 0x10, 2);

    SPI_Master_WriteReg(AX5043_PLLRANGINGA, 0x08, 2);

    for (;;) {
           SPI_Master_ReadReg(AX5043_IRQREQUEST1, 2);
           if (ReceiveBuffer[0] & 0x10)
                break;
     }

    SPI_Master_ReadReg(AX5043_PLLRANGINGA, 2);

    if( (ReceiveBuffer[0] & 0x20) ) // ranging error, power down AX5043
     {
        SPI_Master_WriteReg(AX5043_PWRMODE, AX_PWRMODE_STANDBY, 2);
        return 1;
     }

    return 0;
}

*/
void ax5043_radio_setup_tx() {

    // TX: fcarrier=868.000MHz dev=  1.600kHz br=  4.800kBit/s pwr= 15.0dBm
    // RX: fcarrier=868.000MHz bw=  7.200kHz br=  4.800kBit/s

    // 1.2kbps; dev:5k

    SPI_Master_WriteReg(AX5043_MODULATION     ,                                         0x08, 2);
    SPI_Master_WriteReg(AX5043_ENCODING       ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FRAMING        ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCSYSCLK  ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCDCLK    ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCDATA    ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCANTSEL  ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCPWRAMP  ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_WAKEUPXOEARLY  ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_IFFREQ1        ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_IFFREQ0        ,                                         0x33, 2);
    SPI_Master_WriteReg(AX5043_DECIMATION     ,                                         0x0D, 2);
    SPI_Master_WriteReg(AX5043_RXDATARATE2    ,                                         0x02, 2);
    SPI_Master_WriteReg(AX5043_RXDATARATE1    ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_RXDATARATE0    ,                                         0xD2, 2);
    SPI_Master_WriteReg(AX5043_MAXDROFFSET2   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MAXDROFFSET1   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MAXDROFFSET0   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MAXRFOFFSET2   ,                                         0x80, 2);
    SPI_Master_WriteReg(AX5043_MAXRFOFFSET1   ,                                         0x15, 2);
    SPI_Master_WriteReg(AX5043_MAXRFOFFSET0   ,                                         0xB5, 2);
    SPI_Master_WriteReg(AX5043_FSKDMAX1       ,                                         0x0C, 2);
    SPI_Master_WriteReg(AX5043_FSKDMAX0       ,                                         0xC0, 2);
    SPI_Master_WriteReg(AX5043_FSKDMIN1       ,                                         0xF3, 2);
    SPI_Master_WriteReg(AX5043_FSKDMIN0       ,                                         0x40, 2);
    SPI_Master_WriteReg(AX5043_AMPLFILTER     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_RXPARAMSETS    ,                                         0xF4, 2);
    SPI_Master_WriteReg(AX5043_AGCGAIN0       ,                                         0xE8, 2);
    SPI_Master_WriteReg(AX5043_AGCTARGET0     ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_TIMEGAIN0      ,                                         0x8C, 2);
    SPI_Master_WriteReg(AX5043_DRGAIN0        ,                                         0x86, 2);
    SPI_Master_WriteReg(AX5043_PHASEGAIN0     ,                                         0xC3, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINA0,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINB0,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINC0,                                         0x0A, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAIND0,                                         0x0A, 2);
    SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN0 ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV10      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV00      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSRES0     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCGAIN1       ,                                         0xE8, 2);
    SPI_Master_WriteReg(AX5043_AGCTARGET1     ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_AGCAHYST1      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCMINMAX1     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TIMEGAIN1      ,                                         0x8A, 2);
    SPI_Master_WriteReg(AX5043_DRGAIN1        ,                                         0x85, 2);
    SPI_Master_WriteReg(AX5043_PHASEGAIN1     ,                                         0xC3, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINA1,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINB1,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINC1,                                         0x0A, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAIND1,                                         0x0A, 2);
    SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN1 ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV11      ,                                         0x02, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV01      ,                                         0xEB, 2);
    SPI_Master_WriteReg(AX5043_FOURFSK1       ,                                         0x16, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSRES1     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCGAIN3       ,                                         0xFF, 2);
    SPI_Master_WriteReg(AX5043_AGCTARGET3     ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_AGCAHYST3      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCMINMAX3     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TIMEGAIN3      ,                                         0x89, 2);
    SPI_Master_WriteReg(AX5043_DRGAIN3        ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_PHASEGAIN3     ,                                         0xC3, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINA3,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINB3,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINC3,                                         0x0D, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAIND3,                                         0x0D, 2);
    SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN3 ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV13      ,                                         0x02, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV03      ,                                         0xEB, 2);
    SPI_Master_WriteReg(AX5043_FOURFSK3       ,                                         0x16, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSRES3     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MODCFGF        ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV2        ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV1        ,                                         0x14, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV0        ,                                         0x7B, 2);
    SPI_Master_WriteReg(AX5043_MODCFGA        ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_TXRATE2        ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TXRATE1        ,                                         0x04, 2);
    SPI_Master_WriteReg(AX5043_TXRATE0        ,                                         0xEA, 2);
    SPI_Master_WriteReg(AX5043_TXPWRCOEFFB1   ,                                         0x02, 2);
    SPI_Master_WriteReg(AX5043_TXPWRCOEFFB0   ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_PLLVCOI        ,                                         0x97, 2);
    SPI_Master_WriteReg(AX5043_PLLRNGCLK      ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_BBTUNE         ,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSCAP      ,                                         0x77, 2);
    SPI_Master_WriteReg(AX5043_PKTADDRCFG     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_PKTLENCFG      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_PKTLENOFFSET   ,                                         0x09, 2);
    SPI_Master_WriteReg(AX5043_PKTMAXLEN      ,                                         0xC8, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT3     ,                                         0xAA, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT2     ,                                         0xCC, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT1     ,                                         0xAA, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT0     ,                                         0xCC, 2);
    SPI_Master_WriteReg(AX5043_MATCH0LEN      ,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_MATCH0MAX      ,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_MATCH1PAT1     ,                                         0x55, 2);
    SPI_Master_WriteReg(AX5043_MATCH1PAT0     ,                                         0x55, 2);
    SPI_Master_WriteReg(AX5043_MATCH1LEN      ,                                         0x0A, 2);
    SPI_Master_WriteReg(AX5043_MATCH1MAX      ,                                         0x0A, 2);
    SPI_Master_WriteReg(AX5043_TMGTXBOOST     ,                                         0x32, 2);
    SPI_Master_WriteReg(AX5043_TMGTXSETTLE    ,                                         0x14, 2);
    SPI_Master_WriteReg(AX5043_TMGRXBOOST     ,                                         0x32, 2);
    SPI_Master_WriteReg(AX5043_TMGRXSETTLE    ,                                         0x14, 2);
    SPI_Master_WriteReg(AX5043_TMGRXOFFSACQ   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TMGRXCOARSEAGC ,                                         0x73, 2);
    SPI_Master_WriteReg(AX5043_TMGRXRSSI      ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_TMGRXPREAMBLE2 ,                                         0x35, 2);
    SPI_Master_WriteReg(AX5043_RSSIABSTHR     ,                                         0xE3, 2);
    SPI_Master_WriteReg(AX5043_BGNDRSSITHR    ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_PKTCHUNKSIZE   ,                                         0x0D, 2);
    SPI_Master_WriteReg(AX5043_PKTACCEPTFLAGS ,                                         0x20, 2);
    SPI_Master_WriteReg(AX5043_DACVALUE1      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_DACVALUE0      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_DACCONFIG      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_REF            ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_XTALOSC        ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_XTALAMPL       ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_0xF1C          ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_0xF21          ,                                         0x68, 2);
    SPI_Master_WriteReg(AX5043_0xF22          ,                                         0xFF, 2);
    SPI_Master_WriteReg(AX5043_0xF23          ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_0xF26          ,                                         0x98, 2);
    SPI_Master_WriteReg(AX5043_0xF34          ,                                         0x08, 2);
    SPI_Master_WriteReg(AX5043_0xF35          ,                                         0x10, 2);
    SPI_Master_WriteReg(AX5043_0xF44          ,                                         0x25, 2);


    // 4.8 kbps, dev- 10KHz

    /*SPI_Master_WriteReg(AX5043_MODULATION     ,                                         0x08, 2);
    SPI_Master_WriteReg(AX5043_ENCODING       ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FRAMING        ,                                         0x26, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCSYSCLK  ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCDCLK    ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCDATA    ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCANTSEL  ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCPWRAMP  ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_WAKEUPXOEARLY  ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_IFFREQ1        ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_IFFREQ0        ,                                         0x66, 2);
    SPI_Master_WriteReg(AX5043_DECIMATION     ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_RXDATARATE2    ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_RXDATARATE1    ,                                         0x15, 2);
    SPI_Master_WriteReg(AX5043_RXDATARATE0    ,                                         0xC7, 2);
    SPI_Master_WriteReg(AX5043_MAXDROFFSET2   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MAXDROFFSET1   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MAXDROFFSET0   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MAXRFOFFSET2   ,                                         0x80, 2);
    SPI_Master_WriteReg(AX5043_MAXRFOFFSET1   ,                                         0x15, 2);
    SPI_Master_WriteReg(AX5043_MAXRFOFFSET0   ,                                         0xB5, 2);
    SPI_Master_WriteReg(AX5043_FSKDMAX1       ,                                         0x05, 2);
    SPI_Master_WriteReg(AX5043_FSKDMAX0       ,                                         0xE0, 2);
    SPI_Master_WriteReg(AX5043_FSKDMIN1       ,                                         0xFA, 2);
    SPI_Master_WriteReg(AX5043_FSKDMIN0       ,                                         0x20, 2);
    SPI_Master_WriteReg(AX5043_AMPLFILTER     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_RXPARAMSETS    ,                                         0xF4, 2);
    SPI_Master_WriteReg(AX5043_AGCGAIN0       ,                                         0xC6, 2);
    SPI_Master_WriteReg(AX5043_AGCTARGET0     ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_TIMEGAIN0      ,                                         0x8B, 2);
    SPI_Master_WriteReg(AX5043_DRGAIN0        ,                                         0x85, 2);
    SPI_Master_WriteReg(AX5043_PHASEGAIN0     ,                                         0xC3, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINA0,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINB0,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINC0,                                         0x08, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAIND0,                                         0x08, 2);
    SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN0 ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV10      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV00      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSRES0     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCGAIN1       ,                                         0xC6, 2);
    SPI_Master_WriteReg(AX5043_AGCTARGET1     ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_AGCAHYST1      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCMINMAX1     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TIMEGAIN1      ,                                         0x89, 2);
    SPI_Master_WriteReg(AX5043_DRGAIN1        ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_PHASEGAIN1     ,                                         0xC3, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINA1,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINB1,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINC1,                                         0x08, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAIND1,                                         0x08, 2);
    SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN1 ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV11      ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV01      ,                                         0x75, 2);
    SPI_Master_WriteReg(AX5043_FOURFSK1       ,                                         0x16, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSRES1     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCGAIN3       ,                                         0xFF, 2);
    SPI_Master_WriteReg(AX5043_AGCTARGET3     ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_AGCAHYST3      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCMINMAX3     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TIMEGAIN3      ,                                         0x88, 2);
    SPI_Master_WriteReg(AX5043_DRGAIN3        ,                                         0x83, 2);
    SPI_Master_WriteReg(AX5043_PHASEGAIN3     ,                                         0xC3, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINA3,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINB3,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINC3,                                         0x0C, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAIND3,                                         0x0C, 2);
    SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN3 ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV13      ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV03      ,                                         0x75, 2);
    SPI_Master_WriteReg(AX5043_FOURFSK3       ,                                         0x16, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSRES3     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MODCFGF        ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV2        ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV1        ,                                         0x28, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV0        ,                                         0xF6, 2);
    SPI_Master_WriteReg(AX5043_MODCFGA        ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_TXRATE2        ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TXRATE1        ,                                         0x13, 2);
    SPI_Master_WriteReg(AX5043_TXRATE0        ,                                         0xA9, 2);
    SPI_Master_WriteReg(AX5043_TXPWRCOEFFB1   ,                                         0x02, 2);
    SPI_Master_WriteReg(AX5043_TXPWRCOEFFB0   ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_PLLVCOI        ,                                         0x97, 2);
    SPI_Master_WriteReg(AX5043_PLLRNGCLK      ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_BBTUNE         ,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSCAP      ,                                         0x77, 2);
    SPI_Master_WriteReg(AX5043_PKTADDRCFG     ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PKTLENCFG      ,                                         0x80, 2);
    SPI_Master_WriteReg(AX5043_PKTLENOFFSET   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_PKTMAXLEN      ,                                         0xC8, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT3     ,                                         0xAA, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT2     ,                                         0xCC, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT1     ,                                         0xAA, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT0     ,                                         0xCC, 2);
    SPI_Master_WriteReg(AX5043_MATCH0LEN      ,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_MATCH0MAX      ,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_MATCH1PAT1     ,                                         0x55, 2);
    SPI_Master_WriteReg(AX5043_MATCH1PAT0     ,                                         0x55, 2);
    SPI_Master_WriteReg(AX5043_MATCH1LEN      ,                                         0x8A, 2);
    SPI_Master_WriteReg(AX5043_MATCH1MAX      ,                                         0x0A, 2);
    SPI_Master_WriteReg(AX5043_TMGTXBOOST     ,                                         0x32, 2);
    SPI_Master_WriteReg(AX5043_TMGTXSETTLE    ,                                         0x14, 2);
    SPI_Master_WriteReg(AX5043_TMGRXBOOST     ,                                         0x32, 2);
    SPI_Master_WriteReg(AX5043_TMGRXSETTLE    ,                                         0x14, 2);
    SPI_Master_WriteReg(AX5043_TMGRXOFFSACQ   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TMGRXCOARSEAGC ,                                         0x73, 2);
    SPI_Master_WriteReg(AX5043_TMGRXRSSI      ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_TMGRXPREAMBLE2 ,                                         0x35, 2);
    SPI_Master_WriteReg(AX5043_RSSIABSTHR     ,                                         0xE6, 2);
    SPI_Master_WriteReg(AX5043_BGNDRSSITHR    ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_PKTCHUNKSIZE   ,                                         0x0D, 2);
    SPI_Master_WriteReg(AX5043_PKTACCEPTFLAGS ,                                         0x20, 2);
    SPI_Master_WriteReg(AX5043_DACVALUE1      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_DACVALUE0      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_DACCONFIG      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_REF            ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_XTALOSC        ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_XTALAMPL       ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_0xF1C          ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_0xF21          ,                                         0x68, 2);
    SPI_Master_WriteReg(AX5043_0xF22          ,                                         0xFF, 2);
    SPI_Master_WriteReg(AX5043_0xF23          ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_0xF26          ,                                         0x98, 2);
    SPI_Master_WriteReg(AX5043_0xF34          ,                                         0x08, 2);
    SPI_Master_WriteReg(AX5043_0xF35          ,                                         0x10, 2);
    SPI_Master_WriteReg(AX5043_0xF44          ,                                         0x25, 2);*/

    //10kbps; dev-10KHz

    /*SPI_Master_WriteReg(AX5043_MODULATION     ,                                         0x08, 2);
    SPI_Master_WriteReg(AX5043_ENCODING       ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FRAMING        ,                                         0x26, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCSYSCLK  ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCDCLK    ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCDATA    ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCANTSEL  ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PINFUNCPWRAMP  ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_WAKEUPXOEARLY  ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_IFFREQ1        ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_IFFREQ0        ,                                         0x66, 2);
    SPI_Master_WriteReg(AX5043_DECIMATION     ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_RXDATARATE2    ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_RXDATARATE1    ,                                         0x85, 2);
    SPI_Master_WriteReg(AX5043_RXDATARATE0    ,                                         0x55, 2);
    SPI_Master_WriteReg(AX5043_MAXDROFFSET2   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MAXDROFFSET1   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MAXDROFFSET0   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MAXRFOFFSET2   ,                                         0x80, 2);
    SPI_Master_WriteReg(AX5043_MAXRFOFFSET1   ,                                         0x15, 2);
    SPI_Master_WriteReg(AX5043_MAXRFOFFSET0   ,                                         0xB5, 2);
    SPI_Master_WriteReg(AX5043_FSKDMAX1       ,                                         0x02, 2);
    SPI_Master_WriteReg(AX5043_FSKDMAX0       ,                                         0x4C, 2);
    SPI_Master_WriteReg(AX5043_FSKDMIN1       ,                                         0xFD, 2);
    SPI_Master_WriteReg(AX5043_FSKDMIN0       ,                                         0xB4, 2);
    SPI_Master_WriteReg(AX5043_AMPLFILTER     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_RXPARAMSETS    ,                                         0xF4, 2);
    SPI_Master_WriteReg(AX5043_AGCGAIN0       ,                                         0xB4, 2);
    SPI_Master_WriteReg(AX5043_AGCTARGET0     ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_TIMEGAIN0      ,                                         0x8A, 2);
    SPI_Master_WriteReg(AX5043_DRGAIN0        ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_PHASEGAIN0     ,                                         0xC3, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINA0,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINB0,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINC0,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAIND0,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN0 ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV10      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV00      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSRES0     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCGAIN1       ,                                         0xB4, 2);
    SPI_Master_WriteReg(AX5043_AGCTARGET1     ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_AGCAHYST1      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCMINMAX1     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TIMEGAIN1      ,                                         0x88, 2);
    SPI_Master_WriteReg(AX5043_DRGAIN1        ,                                         0x83, 2);
    SPI_Master_WriteReg(AX5043_PHASEGAIN1     ,                                         0xC3, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINA1,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINB1,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINC1,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAIND1,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN1 ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV11      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV01      ,                                         0xB3, 2);
    SPI_Master_WriteReg(AX5043_FOURFSK1       ,                                         0x16, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSRES1     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCGAIN3       ,                                         0xFF, 2);
    SPI_Master_WriteReg(AX5043_AGCTARGET3     ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_AGCAHYST3      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_AGCMINMAX3     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TIMEGAIN3      ,                                         0x87, 2);
    SPI_Master_WriteReg(AX5043_DRGAIN3        ,                                         0x82, 2);
    SPI_Master_WriteReg(AX5043_PHASEGAIN3     ,                                         0xC3, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINA3,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINB3,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAINC3,                                         0x0B, 2);
    SPI_Master_WriteReg(AX5043_FREQUENCYGAIND3,                                         0x0B, 2);
    SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN3 ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV13      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FREQDEV03      ,                                         0xB3, 2);
    SPI_Master_WriteReg(AX5043_FOURFSK3       ,                                         0x16, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSRES3     ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_MODCFGF        ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV2        ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV1        ,                                         0x28, 2);
    SPI_Master_WriteReg(AX5043_FSKDEV0        ,                                         0xF6, 2);
    SPI_Master_WriteReg(AX5043_MODCFGA        ,                                         0x06, 2);
    SPI_Master_WriteReg(AX5043_TXRATE2        ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TXRATE1        ,                                         0x28, 2);
    SPI_Master_WriteReg(AX5043_TXRATE0        ,                                         0xF6, 2);
    SPI_Master_WriteReg(AX5043_TXPWRCOEFFB1   ,                                         0x02, 2);
    SPI_Master_WriteReg(AX5043_TXPWRCOEFFB0   ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_PLLVCOI        ,                                         0x97, 2);
    SPI_Master_WriteReg(AX5043_PLLRNGCLK      ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_BBTUNE         ,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_BBOFFSCAP      ,                                         0x77, 2);
    SPI_Master_WriteReg(AX5043_PKTADDRCFG     ,                                         0x01, 2);
    SPI_Master_WriteReg(AX5043_PKTLENCFG      ,                                         0x80, 2);
    SPI_Master_WriteReg(AX5043_PKTLENOFFSET   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_PKTMAXLEN      ,                                         0xC8, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT3     ,                                         0xAA, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT2     ,                                         0xCC, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT1     ,                                         0xAA, 2);
    SPI_Master_WriteReg(AX5043_MATCH0PAT0     ,                                         0xCC, 2);
    SPI_Master_WriteReg(AX5043_MATCH0LEN      ,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_MATCH0MAX      ,                                         0x1F, 2);
    SPI_Master_WriteReg(AX5043_MATCH1PAT1     ,                                         0x55, 2);
    SPI_Master_WriteReg(AX5043_MATCH1PAT0     ,                                         0x55, 2);
    SPI_Master_WriteReg(AX5043_MATCH1LEN      ,                                         0x8A, 2);
    SPI_Master_WriteReg(AX5043_MATCH1MAX      ,                                         0x0A, 2);
    SPI_Master_WriteReg(AX5043_TMGTXBOOST     ,                                         0x32, 2);
    SPI_Master_WriteReg(AX5043_TMGTXSETTLE    ,                                         0x14, 2);
    SPI_Master_WriteReg(AX5043_TMGRXBOOST     ,                                         0x32, 2);
    SPI_Master_WriteReg(AX5043_TMGRXSETTLE    ,                                         0x14, 2);
    SPI_Master_WriteReg(AX5043_TMGRXOFFSACQ   ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_TMGRXCOARSEAGC ,                                         0x73, 2);
    SPI_Master_WriteReg(AX5043_TMGRXRSSI      ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_TMGRXPREAMBLE2 ,                                         0x35, 2);
    SPI_Master_WriteReg(AX5043_RSSIABSTHR     ,                                         0xE6, 2);
    SPI_Master_WriteReg(AX5043_BGNDRSSITHR    ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_PKTCHUNKSIZE   ,                                         0x0D, 2);
    SPI_Master_WriteReg(AX5043_PKTACCEPTFLAGS ,                                         0x20, 2);
    SPI_Master_WriteReg(AX5043_DACVALUE1      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_DACVALUE0      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_DACCONFIG      ,                                         0x00, 2);
    SPI_Master_WriteReg(AX5043_REF            ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_XTALOSC        ,                                         0x03, 2);
    SPI_Master_WriteReg(AX5043_XTALAMPL       ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_0xF1C          ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_0xF21          ,                                         0x68, 2);
    SPI_Master_WriteReg(AX5043_0xF22          ,                                         0xFF, 2);
    SPI_Master_WriteReg(AX5043_0xF23          ,                                         0x84, 2);
    SPI_Master_WriteReg(AX5043_0xF26          ,                                         0x98, 2);
    SPI_Master_WriteReg(AX5043_0xF34          ,                                         0x08, 2);
    SPI_Master_WriteReg(AX5043_0xF35          ,                                         0x10, 2);
    SPI_Master_WriteReg(AX5043_0xF44          ,                                         0x25, 2); */

    // 12kbps; dev: 10KHz

        /*SPI_Master_WriteReg(AX5043_MODULATION     ,                                         0x08, 2);
        SPI_Master_WriteReg(AX5043_ENCODING       ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_FRAMING        ,                                         0x26, 2);
        SPI_Master_WriteReg(AX5043_PINFUNCSYSCLK  ,                                         0x01, 2);
        SPI_Master_WriteReg(AX5043_PINFUNCDCLK    ,                                         0x01, 2);
        SPI_Master_WriteReg(AX5043_PINFUNCDATA    ,                                         0x01, 2);
        SPI_Master_WriteReg(AX5043_PINFUNCANTSEL  ,                                         0x01, 2);
        SPI_Master_WriteReg(AX5043_PINFUNCPWRAMP  ,                                         0x07, 2);
        SPI_Master_WriteReg(AX5043_WAKEUPXOEARLY  ,                                         0x01, 2);
        SPI_Master_WriteReg(AX5043_IFFREQ1        ,                                         0x06, 2);
        SPI_Master_WriteReg(AX5043_IFFREQ0        ,                                         0x66, 2);
        SPI_Master_WriteReg(AX5043_DECIMATION     ,                                         0x06, 2);
        SPI_Master_WriteReg(AX5043_RXDATARATE2    ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_RXDATARATE1    ,                                         0x6F, 2);
        SPI_Master_WriteReg(AX5043_RXDATARATE0    ,                                         0x1C, 2);
        SPI_Master_WriteReg(AX5043_MAXDROFFSET2   ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_MAXDROFFSET1   ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_MAXDROFFSET0   ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_MAXRFOFFSET2   ,                                         0x80, 2);
        SPI_Master_WriteReg(AX5043_MAXRFOFFSET1   ,                                         0x15, 2);
        SPI_Master_WriteReg(AX5043_MAXRFOFFSET0   ,                                         0xB5, 2);
        SPI_Master_WriteReg(AX5043_FSKDMAX1       ,                                         0x01, 2);
        SPI_Master_WriteReg(AX5043_FSKDMAX0       ,                                         0xC0, 2);
        SPI_Master_WriteReg(AX5043_FSKDMIN1       ,                                         0xFE, 2);
        SPI_Master_WriteReg(AX5043_FSKDMIN0       ,                                         0x40, 2);
        SPI_Master_WriteReg(AX5043_AMPLFILTER     ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_RXPARAMSETS    ,                                         0xF4, 2);
        SPI_Master_WriteReg(AX5043_AGCGAIN0       ,                                         0xB4, 2);
        SPI_Master_WriteReg(AX5043_AGCTARGET0     ,                                         0x84, 2);
        SPI_Master_WriteReg(AX5043_TIMEGAIN0      ,                                         0xD9, 2);
        SPI_Master_WriteReg(AX5043_DRGAIN0        ,                                         0xD3, 2);
        SPI_Master_WriteReg(AX5043_PHASEGAIN0     ,                                         0xC3, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAINA0,                                         0x0F, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAINB0,                                         0x1F, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAINC0,                                         0x06, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAIND0,                                         0x06, 2);
        SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN0 ,                                         0x06, 2);
        SPI_Master_WriteReg(AX5043_FREQDEV10      ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_FREQDEV00      ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_BBOFFSRES0     ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_AGCGAIN1       ,                                         0xB4, 2);
        SPI_Master_WriteReg(AX5043_AGCTARGET1     ,                                         0x84, 2);
        SPI_Master_WriteReg(AX5043_AGCAHYST1      ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_AGCMINMAX1     ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_TIMEGAIN1      ,                                         0xD7, 2);
        SPI_Master_WriteReg(AX5043_DRGAIN1        ,                                         0xD2, 2);
        SPI_Master_WriteReg(AX5043_PHASEGAIN1     ,                                         0xC3, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAINA1,                                         0x0F, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAINB1,                                         0x1F, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAINC1,                                         0x06, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAIND1,                                         0x06, 2);
        SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN1 ,                                         0x06, 2);
        SPI_Master_WriteReg(AX5043_FREQDEV11      ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_FREQDEV01      ,                                         0x95, 2);
        SPI_Master_WriteReg(AX5043_FOURFSK1       ,                                         0x16, 2);
        SPI_Master_WriteReg(AX5043_BBOFFSRES1     ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_AGCGAIN3       ,                                         0xFF, 2);
        SPI_Master_WriteReg(AX5043_AGCTARGET3     ,                                         0x84, 2);
        SPI_Master_WriteReg(AX5043_AGCAHYST3      ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_AGCMINMAX3     ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_TIMEGAIN3      ,                                         0xD6, 2);
        SPI_Master_WriteReg(AX5043_DRGAIN3        ,                                         0xD1, 2);
        SPI_Master_WriteReg(AX5043_PHASEGAIN3     ,                                         0xC3, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAINA3,                                         0x0F, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAINB3,                                         0x1F, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAINC3,                                         0x0A, 2);
        SPI_Master_WriteReg(AX5043_FREQUENCYGAIND3,                                         0x0A, 2);
        SPI_Master_WriteReg(AX5043_AMPLITUDEGAIN3 ,                                         0x06, 2);
        SPI_Master_WriteReg(AX5043_FREQDEV13      ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_FREQDEV03      ,                                         0x95, 2);
        SPI_Master_WriteReg(AX5043_FOURFSK3       ,                                         0x16, 2);
        SPI_Master_WriteReg(AX5043_BBOFFSRES3     ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_MODCFGF        ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_FSKDEV2        ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_FSKDEV1        ,                                         0x28, 2);
        SPI_Master_WriteReg(AX5043_FSKDEV0        ,                                         0xF6, 2);
        SPI_Master_WriteReg(AX5043_MODCFGA        ,                                         0x06, 2);
        SPI_Master_WriteReg(AX5043_TXRATE2        ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_TXRATE1        ,                                         0x31, 2);
        SPI_Master_WriteReg(AX5043_TXRATE0        ,                                         0x27, 2);
        SPI_Master_WriteReg(AX5043_TXPWRCOEFFB1   ,                                         0x02, 2);
        SPI_Master_WriteReg(AX5043_TXPWRCOEFFB0   ,                                         0x07, 2);
        SPI_Master_WriteReg(AX5043_PLLVCOI        ,                                         0x97, 2);
        SPI_Master_WriteReg(AX5043_PLLRNGCLK      ,                                         0x03, 2);
        SPI_Master_WriteReg(AX5043_BBTUNE         ,                                         0x0F, 2);
        SPI_Master_WriteReg(AX5043_BBOFFSCAP      ,                                         0x77, 2);
        SPI_Master_WriteReg(AX5043_PKTADDRCFG     ,                                         0x01, 2);
        SPI_Master_WriteReg(AX5043_PKTLENCFG      ,                                         0x80, 2);
        SPI_Master_WriteReg(AX5043_PKTLENOFFSET   ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_PKTMAXLEN      ,                                         0xC8, 2);
        SPI_Master_WriteReg(AX5043_MATCH0PAT3     ,                                         0xAA, 2);
        SPI_Master_WriteReg(AX5043_MATCH0PAT2     ,                                         0xCC, 2);
        SPI_Master_WriteReg(AX5043_MATCH0PAT1     ,                                         0xAA, 2);
        SPI_Master_WriteReg(AX5043_MATCH0PAT0     ,                                         0xCC, 2);
        SPI_Master_WriteReg(AX5043_MATCH0LEN      ,                                         0x1F, 2);
        SPI_Master_WriteReg(AX5043_MATCH0MAX      ,                                         0x1F, 2);
        SPI_Master_WriteReg(AX5043_MATCH1PAT1     ,                                         0x55, 2);
        SPI_Master_WriteReg(AX5043_MATCH1PAT0     ,                                         0x55, 2);
        SPI_Master_WriteReg(AX5043_MATCH1LEN      ,                                         0x8A, 2);
        SPI_Master_WriteReg(AX5043_MATCH1MAX      ,                                         0x0A, 2);
        SPI_Master_WriteReg(AX5043_TMGTXBOOST     ,                                         0x32, 2);
        SPI_Master_WriteReg(AX5043_TMGTXSETTLE    ,                                         0x14, 2);
        SPI_Master_WriteReg(AX5043_TMGRXBOOST     ,                                         0x32, 2);
        SPI_Master_WriteReg(AX5043_TMGRXSETTLE    ,                                         0x14, 2);
        SPI_Master_WriteReg(AX5043_TMGRXOFFSACQ   ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_TMGRXCOARSEAGC ,                                         0x73, 2);
        SPI_Master_WriteReg(AX5043_TMGRXRSSI      ,                                         0x03, 2);
        SPI_Master_WriteReg(AX5043_TMGRXPREAMBLE2 ,                                         0x35, 2);
        SPI_Master_WriteReg(AX5043_RSSIABSTHR     ,                                         0xE6, 2);
        SPI_Master_WriteReg(AX5043_BGNDRSSITHR    ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_PKTCHUNKSIZE   ,                                         0x0D, 2);
        SPI_Master_WriteReg(AX5043_PKTACCEPTFLAGS ,                                         0x20, 2);
        SPI_Master_WriteReg(AX5043_DACVALUE1      ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_DACVALUE0      ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_DACCONFIG      ,                                         0x00, 2);
        SPI_Master_WriteReg(AX5043_REF            ,                                         0x03, 2);
        SPI_Master_WriteReg(AX5043_XTALOSC        ,                                         0x03, 2);
        SPI_Master_WriteReg(AX5043_XTALAMPL       ,                                         0x07, 2);
        SPI_Master_WriteReg(AX5043_0xF1C          ,                                         0x07, 2);
        SPI_Master_WriteReg(AX5043_0xF21          ,                                         0x68, 2);
        SPI_Master_WriteReg(AX5043_0xF22          ,                                         0xFF, 2);
        SPI_Master_WriteReg(AX5043_0xF23          ,                                         0x84, 2);
        SPI_Master_WriteReg(AX5043_0xF26          ,                                         0x98, 2);
        SPI_Master_WriteReg(AX5043_0xF34          ,                                         0x08, 2);
        SPI_Master_WriteReg(AX5043_0xF35          ,                                         0x10, 2);
        SPI_Master_WriteReg(AX5043_0xF44          ,                                         0x25, 2);*/



    // tx related

    SPI_Master_WriteReg(AX5043_PLLLOOP        ,                                         0x09, 2);
    SPI_Master_WriteReg(AX5043_PLLCPI         ,                                         0x02, 2);
    SPI_Master_WriteReg(AX5043_PLLVCODIV      ,                                         0x20, 2);
    SPI_Master_WriteReg(AX5043_XTALCAP        ,                                         0x07, 2);
    SPI_Master_WriteReg(AX5043_0xF00          ,                                         0x0F, 2);
    SPI_Master_WriteReg(AX5043_0xF18          ,                                         0x06, 2);


    // Frequency related
    uint32_t f = 0x38ac0001;                                     //For 906.75 - 0x38ac0001; For 906.92 - 0x38aeb853; For 907.22 - 0x38b3851f; For 907.07 - 0x38b11eb9; 906.4 - 0x38a66667
    SPI_Master_WriteReg(AX5043_FREQA0, f,2);
    SPI_Master_WriteReg(AX5043_FREQA1, (f >> 8),2);
    SPI_Master_WriteReg(AX5043_FREQA2, (f >> 16),2);
    SPI_Master_WriteReg(AX5043_FREQA3, (f >> 24),2);

}

void ax5043_reset() {
    // AX5043 requires the programmer to set and then clear the reset bit to do a reset
    // Set reset bit, and enable crystal ocsillator,
    // enable reference, and don't care for wake from deep sleep (used a 0)
    // Set power mode to 0111 which is FIFO enabled with xtal
    SPI_Master_WriteReg(AX5043_PWRMODE, 0xE7, 2);

    // Clear reset bit with same settings as above
    SPI_Master_WriteReg(AX5043_PWRMODE, 0x67, 2);
}

uint8_t ax5043_pll_ranging() {

    uint8_t pllloop_save[1], pllcpi_save[1],pllrng[1],pllock[1];

    // Save current loop filter bandwidth and charge pump current settings
    SPI_Master_ReadReg(AX5043_PLLLOOP, 2);
    CopyArray1(ReceiveBuffer, pllloop_save, 1);


    SPI_Master_ReadReg(AX5043_PLLCPI, 2);
    CopyArray1(ReceiveBuffer, pllcpi_save, 1);


    // Default to 100kHz loop filter bandwidth and default starting point for charge pump current
    SPI_Master_WriteReg(AX5043_PLLLOOP, 0x09, 2);
    SPI_Master_WriteReg(AX5043_PLLCPI, 0x08, 2);


    // Turn on XTAL and wait for it to be stablilized
    SPI_Master_WriteReg(AX5043_PWRMODE, 0x65, 2);
    ax5043_wait_for_xtal();

    // Enable PLL auto ranging interrupt and do the ranging starting at range 8

    SPI_Master_WriteReg(AX5043_IRQMASK1, 0x10, 2);
    SPI_Master_WriteReg(AX5043_PLLRANGINGA, 0x18, 2);

    do {
        SPI_Master_ReadReg(AX5043_PLLRANGINGA,2);
      } while (ReceiveBuffer[0] & AX_PLLRANGING_RNG_START);

    // Done, clear interrupt
    SPI_Master_ReadReg(AX5043_PLLRANGINGA,2);
    CopyArray1(ReceiveBuffer, pllock, 1);

    SPI_Master_WriteReg(AX5043_IRQMASK1, 0x00, 2);

    SPI_Master_ReadReg(AX5043_PLLRANGINGA, 2);
    CopyArray1(ReceiveBuffer, pllrng, 1);

    // Ranging error, power down AX5043
    if( (pllrng[0] & AX_PLLRANGING_RNGERR) ) // ranging error, power down AX5043
    {
        SPI_Master_WriteReg(AX5043_PWRMODE, AX5043_PWRSTATE_POWERDOWN, 2);
        return 1;
    }

    // Restore settings
    SPI_Master_WriteReg(AX5043_PLLLOOP, pllloop_save[0], 2);
    SPI_Master_WriteReg(AX5043_PLLCPI, pllcpi_save[0], 2);

    return 0;
}

void ax5043_wait_for_xtal() {
    // Enable XTAL interrupt
    int i = 0;

    SPI_Master_ReadReg(AX_REG_XTALSTATUS,2);

    while (!ReceiveBuffer[0] & 1) {
       SPI_Master_ReadReg(AX_REG_XTALSTATUS,2);
       i++;
     }
}

void ax5043_transmit(uint8_t *pkt, uint16_t pktlen) {
    uint8_t preamble[5] , data[5];

    uint8_t ax_syncword[4] = {(SYNCWORD)>>0 & 0xFF, (SYNCWORD)>>8 & 0xFF, (SYNCWORD)>>16 & 0xFF, (SYNCWORD)>>24 & 0xFF};
    // Clear the FIFO and set power mode to FULL_TX

    SPI_Master_WriteReg(AX5043_FIFOSTAT, 0x03,2); // clear FIFO
    SPI_Master_WriteReg(AX5043_PWRMODE, 0x0D,2);

    // Loop until the VDD for the modem is stable before writing to FIFO
    SPI_Master_ReadReg(AX5043_POWSTAT,2);
    while (!(ReceiveBuffer[0]) & AX_POWSTAT_SVMODEM);

    // Write preamble to the FIFO using a REPEATDATA chunk

    SPI_Master_WriteReg(AX5043_FIFODATA, 0x62,2);
    SPI_Master_WriteReg(AX5043_FIFODATA, 0x28,2);
    SPI_Master_WriteReg(AX5043_FIFODATA, 1,2);
    SPI_Master_WriteReg(AX5043_FIFODATA, 0xFF,2);

   /* // Write SYNC WORD to FIFO
    SPI_Master_ReadReg(AX5043_FRAMING,2);
    if ((ReceiveBuffer[0] & 0x0E) == 0x06) {
        // Write SYNC word if framing mode is raw_patternmatch
        uint8_t i;
        SPI_Master_WriteReg(AX5043_FIFODATA, (AX5043_FIFOCMD_DATA | ((sizeof(ax_syncword) + 1) << 5)),2);
        SPI_Master_WriteReg(AX5043_FIFODATA, SYNCWORD_FLAGS,2);
        for (i = 0; i < sizeof(ax_syncword); ++i) {
            SPI_Master_WriteReg(AX5043_FIFODATA, ax_syncword[i],2);
        }
    }
*/

   // SPI_Master_WriteReg(AX5043_RADIOEVENTMASK0, 0x01,2); // TX done flag
   // SPI_Master_WriteReg(AX5043_IRQMASK0, 0x40,2);         // Radio controller irq

    // Write packet to FIFO using a DATA chunk

      SPI_Master_WriteReg(AX5043_FIFODATA, 0xE1,2);
      SPI_Master_WriteReg(AX5043_FIFODATA, pktlen+1,2);   // Write FIFO chunk length byte (length includes the flag byte, thus the +1)
      SPI_Master_WriteReg(AX5043_FIFODATA, 0x03,2);         // pkt_start | pkt_end
      SPI_Master_WriteReg(AX5043_FIFODATA, 0x00,2);

    //SPI_Master_ReadReg(AX5043_RADIOEVENTREQ0,2);     // Clear flag

    ax5043_wait_for_xtal();                     // Wait until cystal oscillator ready

    SPI_Master_WriteReg(AX5043_FIFOSTAT, 0x04,2);            // Commit the FIFO --> TX starts

    // Wait until TX is finished
    {

        for(;;)
        {
            SPI_Master_ReadReg(AX5043_RADIOSTATE,2);
            if(ReceiveBuffer[0] == 0x06 || ReceiveBuffer == 0x07)
                continue;
            else
                break;
        }
    }

    // Transmit is done, go back to sleep
    //SPI_Master_WriteReg(AX5043_PWRMODE, AX_PWRMODE_POWERDOWN,2);
}


void ax5043_writefifo(const uint8_t *ptr, uint8_t len) {
    if (!len)
        return;
    do {
        SPI_Master_WriteReg(AX5043_FIFODATA, *ptr++, 2);
        //*(uint8_t *)(AX8052_RADIOBASE | FDATA) = *ptr++;
    } while (--len);
}



void SendUCB0Data(uint16_t val)
{
    while (!(UCB0IFG & UCTXIFG));              // USCI_B0 TX buffer ready?
    UCB0TXBUF = val;
}

void CopyArray(uint16_t source, uint16_t *dest, uint8_t count)
{
    if (count == 2)
    {
        dest[1]=source;
    }
}

void CopyArray1(uint8_t *source, uint8_t *dest, uint8_t count)
{
    if (count == 1)
    {
        dest[0]=source[0];
    }
}

void CopyArray2(uint16_t *source, uint16_t *dest, uint8_t count)
{

    if (count > 2)
    {
        int i;
        for (i=0;i<count;i++)
        {
        dest[i+1]=source[i];
        }
    }
}



SPI_Mode SPI_Master_WriteReg(uint16_t reg_addr, uint8_t reg_data, uint8_t count)
{
    Reg1 = ((reg_addr >> 8) | 0xF0);
    Reg2 = (reg_addr & 0xFF);

    MasterMode = TX_REG_ADDRESS_MODE;
    TransmitRegAddr = Reg1;

    TransmitBuffer[0] = Reg2;
    //Copy register data to TransmitBuffer
    CopyArray(reg_data, TransmitBuffer, count);

    TXByteCtr = count;
    RXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;

    SLAVE_CS_OUT &= ~(SLAVE_CS_PIN);

    SendUCB0Data(TransmitRegAddr);

    __bis_SR_register(CPUOFF + GIE);              // Enter LPM0 w/ interrupts

    SLAVE_CS_OUT |= SLAVE_CS_PIN;
    return MasterMode;
}

SPI_Mode SPI_Master_WriteArray(uint16_t reg_addr, uint8_t *reg_array, uint8_t count)
{
    Reg1 = ((reg_addr >> 8) | 0xF0);
    Reg2 = (reg_addr & 0xFF);

    MasterMode = TX_REG_ADDRESS_MODE;
    TransmitRegAddr = Reg1;

    TransmitBuffer1[0] = Reg2;
    //Copy register data to TransmitBuffer
    CopyArray2(reg_array, TransmitBuffer1, count);

    TXByteCtr = count;
    RXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;

    SLAVE_CS_OUT &= ~(SLAVE_CS_PIN);

    SendUCB0Data(TransmitRegAddr);

    __bis_SR_register(CPUOFF + GIE);              // Enter LPM0 w/ interrupts

    SLAVE_CS_OUT |= SLAVE_CS_PIN;
    return MasterMode;
}

SPI_Mode SPI_Master_ReadReg(uint16_t reg_addr, uint8_t count)
{



    Reg3 = ((reg_addr >> 8) | 0x70);
    Reg4[0] = (reg_addr & 0xFF);

    CopyArray1(Reg4, Addr, 1);

    MasterMode = TX_REG_ADDRESS_MODE;
    TransmitRegAddr = Reg3;
    RXByteCtr = count;
    TXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;


    SLAVE_CS_OUT &= ~(SLAVE_CS_PIN);

    SendUCB0Data(TransmitRegAddr);

    __bis_SR_register(CPUOFF + GIE);              // Enter LPM0 w/ interrupts

    SLAVE_CS_OUT |= SLAVE_CS_PIN;
    return MasterMode;
}

//******************************************************************************
// SPI Interrupt ***************************************************************
//******************************************************************************

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_B0_VECTOR))) USCI_B0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    uint8_t ucb0_rx_val = 0;
    switch(__even_in_range(UCB0IV, USCI_SPI_UCTXIFG))
    {
        case USCI_NONE: break;
        case USCI_SPI_UCRXIFG:
            ucb0_rx_val = UCB0RXBUF;
            UCB0IFG &= ~UCRXIFG;
            switch (MasterMode)
            {
                case TX_REG_ADDRESS_MODE:
                    if (RXByteCtr)
                    {
                        MasterMode = RX_DATA_MODE;   // Need to start receiving now
                        //Send Dummy To Start
                        __delay_cycles(2000000);
                        SendUCB0Data(Addr[0]);
                    }
                    else
                    {
                        MasterMode = TX_DATA_MODE;        // Continue to transmision with the data in Transmit Buffer
                        //Send First
                        SendUCB0Data(TransmitBuffer[TransmitIndex++]);
                        TXByteCtr--;
                    }
                    break;

                case TX_DATA_MODE:
                    if (TXByteCtr)
                    {
                      SendUCB0Data(TransmitBuffer[TransmitIndex++]);
                      TXByteCtr--;
                    }
                    else
                    {
                      //Done with transmission
                      MasterMode = IDLE_MODE;
                      __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
                    }
                    break;

                case RX_DATA_MODE:
                    if (RXByteCtr==1)
                    {
                        ReceiveBuffer[ReceiveIndex++] = ucb0_rx_val;
                        //Transmit a dummy
                        RXByteCtr--;
                    }
                    if (RXByteCtr == 0)
                    {
                        MasterMode = IDLE_MODE;
                        __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
                    }
                    else
                    {
                        SendUCB0Data(DUMMY);
                        RXByteCtr--;
                    }
                    break;

                default:
                    __no_operation();
                    break;
            }
            __delay_cycles(1000);
            break;
        case USCI_SPI_UCTXIFG:
            break;
        default: break;
    }
}
