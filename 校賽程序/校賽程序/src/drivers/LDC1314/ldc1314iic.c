#include "ldc1314iic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板V3
//LDC6050 IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/17
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
  //LDC IIC 延时函数
void LDC_IIC_Delay(void)
{
  delayus(2);
}

//初始化IIC
void LDC_IIC_Init(void)
{		
  gpio_init(PORTD,14,GPO,1);                  //SCL
  gpio_init(PORTE,7,GPO,1);                  //SDA
}
//产生IIC起始信号
void LDC_IIC_Start(void)
{
	LDC_SDA_OUT();     //sda线输出
	LDC_IIC_SDA=1;	  	  
	LDC_IIC_SCL=1;
	LDC_IIC_Delay();
 	LDC_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	LDC_IIC_Delay();
	LDC_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void LDC_IIC_Stop(void)
{
	LDC_SDA_OUT();//sda线输出
	LDC_IIC_SCL=0;
	LDC_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	LDC_IIC_Delay();
	LDC_IIC_SCL=1; 
	LDC_IIC_SDA=1;//发送I2C总线结束信号
	LDC_IIC_Delay();							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 LDC_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	LDC_SDA_IN();      //SDA设置为输入  
	LDC_IIC_SDA=1;//LDC_IIC_Delay();	   
	LDC_IIC_SCL=1;//LDC_IIC_Delay();	 
	while(LDC_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			LDC_IIC_Stop();
			return 1;
		}
	}
	LDC_IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void LDC_IIC_Ack(void)
{
	LDC_IIC_SCL=0;
	LDC_SDA_OUT();
	LDC_IIC_SDA=0;
	LDC_IIC_Delay();
	LDC_IIC_SCL=1;
	LDC_IIC_Delay();
	LDC_IIC_SCL=0;
}
//不产生ACK应答		    
void LDC_IIC_NAck(void)
{
	LDC_IIC_SCL=0;
	LDC_SDA_OUT();
	LDC_IIC_SDA=1;
	LDC_IIC_Delay();
	LDC_IIC_SCL=1;
	LDC_IIC_Delay();
	LDC_IIC_SCL=0;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void LDC_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	LDC_SDA_OUT(); 	    
    LDC_IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        LDC_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		    LDC_IIC_SCL=1;
		    LDC_IIC_Delay(); 
		    LDC_IIC_SCL=0;	
		    LDC_IIC_Delay();
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 LDC_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	LDC_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        LDC_IIC_SCL=0; 
        LDC_IIC_Delay();
		LDC_IIC_SCL=1;
        receive<<=1;
        if(LDC_READ_SDA)receive++;   
		LDC_IIC_Delay(); 
    }					 
    if (!ack)
        LDC_IIC_NAck();//发送nACK
    else
        LDC_IIC_Ack(); //发送ACK   
    return receive;
}

