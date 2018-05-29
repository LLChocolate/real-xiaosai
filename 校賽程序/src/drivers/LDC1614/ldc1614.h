#ifndef __LDC1614_H__
#define __LDC1614_H__

#include "include.h"
#include "ldc1614iic.h"

#define PORT_LDC1614_PERIPH					SYSCTL_PERIPH_GPIOA
#define PORT_LDC1614_BASE						GPIO_PORTA_BASE
#define CLK_LDC1614						  		GPIO_PIN_6
#define SDA_LDC1614									GPIO_PIN_7

#define LDC1614_HW_IIC_PORT 				SYSCTL_PERIPH_I2C1//硬件iic使用的外设
#define LDC1614_HW_IIC_CLK					GPIO_PA6_I2C1SCL
#define LDC1614_HW_IIC_SDA					GPIO_PA7_I2C1SDA
#define LDC1614_HW_IIC_BASE					I2C1_BASE



#define ADRESS_LDC1614 				0x2A    //LDC1614地址

#define DATA0_MSB							0x00 //Channel 0 Conversion Result and Error Status
#define DATA0_LSB							0x01
#define DATA1_MSB							0x02
#define DATA1_LSB							0x03
#define DATA2_MSB							0x04
#define DATA2_LSB							0x05
#define DATA3_MSB							0x06
#define DATA3_LSB							0x07
#define RCOUNT_CH0						0x08 //Reference Count setting for Channel 0
#define RCOUNT_CH1						0x09
#define RCOUNT_CH2						0x0A
#define RCOUNT_CH3						0x0B
#define OFFSET_CH0						0x0C //Offset value for Channel 0
#define OFFSET_CH1						0x0D
#define OFFSET_CH2						0x0E
#define OFFSET_CH3						0x0F
#define SETTLECOUNT_CH0				0x10 //Channel 0 Settling Reference Count
#define SETTLECOUNT_CH1				0x11
#define SETTLECOUNT_CH2				0x12
#define SETTLECOUNT_CH3				0x13
#define CLOCK_DIVIDERS_CH0		0x14
#define CLOCK_DIVIDERS_CH1		0x15
#define CLOCK_DIVIDERS_CH2		0x16
#define CLOCK_DIVIDERS_CH3		0x17
#define STATUS								0x18 //Device Status Report
#define ERROR_CONFIG					0x19 //Error Reporting Configuration
#define MUX_CONFIG						0x1B //Channel Multiplexing Configuration
#define CONFIG								0x1A //Conversion Configuration
#define RESET_DEV							0x1C //Reset Device
#define DRIVE_CURRENT_CH0			0x1E //Channel 0 sensor current drive configuration
#define DRIVE_CURRENT_CH1			0x1F
#define DRIVE_CURRENT_CH2			0x20
#define DRIVE_CURRENT_CH3			0x21
#define MANUFACTURER_ID			 	0x7E //厂商ID，默认值0x5449
#define DEVICE_ID 						0x7F //设备ID，默认值0x3054


extern u16 ldc1614_readbuf[8];


extern void LDC1614_i2c_INIT(void);
void LDC1614_AUTO_INIT(void);
extern void LDC1614_INIT(u8 i);
extern u8 LDC1614_send_word(u8 reg,u16 data);
extern u16 LDC1614_read_word(u8 reg);
extern uint32_t LDC1614_Result(u8 Channal);


#endif

