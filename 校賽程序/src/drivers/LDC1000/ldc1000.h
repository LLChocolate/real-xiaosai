#ifndef _LDC1000_H_
#define _LDC1000_H_

#include "include.h"
/****************′ú??ò??2??*******************/
#define CS              PTE7_OUT
#define SCLK            PTD14_OUT
#define SI              PTD12_IN // 接LDC的SO
#define SO              PTD13_OUT// 接LDC的SI

extern unsigned int  DataRcv[5] ;  

#define SPI_NOP             0XFF//????á?ó?à′?á×′ì???′??÷

/****************??′??÷μ??·??*******************/
#define LDC1000_CMD_REVID 		0x00
#define LDC1000_CMD_RPMAX 		0x01
#define LDC1000_CMD_RPMIN 		0x02
#define LDC1000_CMD_SENSORFREQ 	0x03
#define LDC1000_CMD_LDCCONFIG 	0x04
#define LDC1000_CMD_CLKCONFIG 	0x05
#define LDC1000_CMD_THRESHILSB 	0x06
#define LDC1000_CMD_THRESHIMSB 	0x07
#define LDC1000_CMD_THRESLOLSB 	0x08
#define LDC1000_CMD_THRESLOMSB 	0x09
#define LDC1000_CMD_INTCONFIG 	0x0A
#define LDC1000_CMD_PWRCONFIG 	0x0B
#define LDC1000_CMD_STATUS	 	0x20
#define LDC1000_CMD_PROXLSB 	0x21
#define LDC1000_CMD_PROXMSB 	0x22
#define LDC1000_CMD_FREQCTRLSB	0x23
#define LDC1000_CMD_FREQCTRMID	0x24
#define LDC1000_CMD_FREQCTRMSB	0x25

// LDC BITMASKS
#define LDC1000_BIT_AMPLITUDE    0x18
#define LDC1000_BIT_RESPTIME     0x07
#define LDC1000_BIT_CLKSEL       0x02
#define LDC1000_BIT_CLKPD        0x01
#define LDC1000_BIT_INTMODE      0x07
#define LDC1000_BIT_PWRMODE      0x01
#define LDC1000_BIT_STATUSOSC    0x80
#define LDC1000_BIT_STATUSDRDYB  0x40
#define LDC1000_BIT_STATUSWAKEUP 0x20
#define LDC1000_BIT_STATUSCOMP   0x10

#define TEST_RPMAX_MAX 	0x13			  /**< maximum calibration value for RPMAX */
#define TEST_RPMAX_MIN 	0x10			  /**< minimum calibration value for RPMAX */
#define TEST_RPMAX_INIT TEST_RPMAX_MIN+1  /**< RPMAX initial value */
#define TEST_RPMIN_MAX 	0x3D   			  /**< maximum calibration value for RPMIN */
#define TEST_RPMIN_MIN 	0x3A    		  /**< minimum calibration value for RPMIN */
#define TEST_RPMIN_INIT TEST_RPMIN_MIN+1  /**< RPMIN initial value */
// Final Test Range
#define TEST_RP_MSB_MAX 0x12	        /**< maximum value for proximity data */
#define TEST_RP_MSB_MIN 0x0A	        /**< minimum value for proximity data */
#define TEST_FC_MAX 0x0D5D		/**< maximum value for frequency counter */
#define TEST_FC_MIN 0x0D39		/**< minimum value for frequency counter */
#define F_ref           8000000


/****************oˉêyéù?÷??*******************/
void LdcInit(void);//spiμ?3?ê??ˉ
void LdcParaInit(void);
void MY_SPI_Init(void);
u8 LdcReadReg(u8 addr);
//void LdcWriteReg(u8 addr, u8 data);
void LdcSetRp(u8 max, u8 min);
void LdcRead(void);
u8 read_data();
void write_reg(u8 data);
#endif //_LDC1000_H_
