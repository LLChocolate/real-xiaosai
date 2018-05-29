#ifndef __LDCIIC_H
#define __LDCIIC_H
//#include "sys.h"
#include "common.h"
#include "gpio.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//MPU6050 IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/17
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 	   		   
#define LDC_SDA_IN()    DDRD14 = 0
#define LDC_SDA_OUT()   DDRD14 = 1


#define LDC_IIC_SCL     PTE7_OUT		//SCL
#define LDC_IIC_SDA     PTD14_OUT		//SDA	 
#define LDC_READ_SDA    PTD14_IN		//??SDA 


//IIC所有操作函数
//void LDC_IIC_Delay(void);				//LDC IIC延时函数
void LDC_IIC_Init(void);                //初始化IIC的IO口				 
void LDC_IIC_Start(void);				//发送IIC开始信号
void LDC_IIC_Stop(void);	  			//发送IIC停止信号
void LDC_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 LDC_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 LDC_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void LDC_IIC_Ack(void);					//IIC发送ACK信号
void LDC_IIC_NAck(void);				//IIC不发送ACK信号

void ILDC_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 LDC_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















