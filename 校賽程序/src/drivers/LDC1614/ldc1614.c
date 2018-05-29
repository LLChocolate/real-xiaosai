#include "LDC1614.h"

//H =12.59uH
//H = 27.305uH
//H = 35.18uH
u16 I_drive_temp=30;
void LDC1614_i2c_INIT(void)
{
    // 使能LDC1614使用的io外设端口
    delayms(1);
    // 使能I2C1外设
    LDC_IIC_Init();
//    exti_init(PORTD,12,falling_up);
    delayms(1);
    // 配置LDC1614使用的io外设端口为上拉开漏端口
    //GPIOPadConfigSet(PORT_PT2314, CLK_PT2314|SDA_PT2314 , GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);
//    ROM_GPIOPinTypeI2C(PORT_LDC1614_BASE, SDA_LDC1614);
//    ROM_GPIOPinTypeI2CSCL(PORT_LDC1614_BASE, CLK_LDC1614);
    // 配置I2C协议时钟信号、数据信号
//    ROM_GPIOPinConfigure(LDC1614_HW_IIC_CLK);
//    ROM_GPIOPinConfigure(LDC1614_HW_IIC_SDA);

    // 初始化I2C主机模块。设置总线速度和使能主机模块
//    I2CMasterInitExpClk(LDC1614_HW_IIC_BASE, 80000000, false); //低速100k
    //I2CMasterInitExpClk(ADS1115_HW_IIC_BASE, SysCtlClockGet(), true);//高速400k

////启用如下代码则切换至3.4M传输速度
//        ui32TPR = ((80000000 + (2 * 3 * 3400000) - 1) /
//                   (2 * 3 * 3400000)) - 1;
//        HWREG(ADS1115_HW_IIC_BASE + 0x00C) = I2C_MTPR_HS | ui32TPR;
////启用上面代码则切换至3.4M传输速度


// 使能I2C主机模块
//    I2CMasterEnable(LDC1614_HW_IIC_BASE);	
}

//i2c向LDC1614发送一个16位的字

u8 LDC1614_send_u8(u8 reg,u8 data)
{
    LDC_IIC_Start(); 
    LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|0);//发送器件地址+写命令	
    if(LDC_IIC_Wait_Ack())	//等待应答
    {
      LDC_IIC_Stop();		 
      return 1;		
    }
    LDC_IIC_Send_Byte(reg);	//写寄存器地址
    LDC_IIC_Wait_Ack();		//等待应答 
    LDC_IIC_Send_Byte(data);//发送数据
    if(LDC_IIC_Wait_Ack())	//等待ACK
    {
            LDC_IIC_Stop();	 
            return 1;		 
    }		 
    LDC_IIC_Stop();	 
    return 0;
}


u8 LDC1614_send_word(uint8_t reg,uint16_t data)
{
    LDC_IIC_Start(); 
    LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|0);//发送器件地址+写命令	
    if(LDC_IIC_Wait_Ack())	//等待应答
    {
      LDC_IIC_Stop();		 
      return 1;		
    }
    LDC_IIC_Send_Byte(reg);	//写寄存器地址
    LDC_IIC_Wait_Ack();		//等待应答 
    LDC_IIC_Send_Byte((u8)(data>>8));//发送高八位
    if(LDC_IIC_Wait_Ack())	//等待ACK
    {
      LDC_IIC_Stop();	 
      return 1;		 
    }
    LDC_IIC_Send_Byte((u8)(data));//发送低八位
    if(LDC_IIC_Wait_Ack())	//等待ACK
    {
      LDC_IIC_Stop();	 
      return 1;		 
    }		 
    LDC_IIC_Stop();	 
    return 0;
}


//i2c读取LDC1614的一个寄存器
u8 LDC1614_read_u8(u8 reg)
{
    u8 res;
    LDC_IIC_Start(); 
    LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|0);//发送器件地址+写命令	
    LDC_IIC_Wait_Ack();		//等待应答 
    LDC_IIC_Send_Byte(reg);	//写寄存器地址
    LDC_IIC_Wait_Ack();		//等待应答
    LDC_IIC_Start();
    LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|1);//发送器件地址+读命令	
    LDC_IIC_Wait_Ack();		//等待应答 
    res=LDC_IIC_Read_Byte(0);//读取数据,发送nACK 
    LDC_IIC_Stop();			//产生一个停止条件 
    return res;		
}


uint16_t LDC1614_read_word(uint8_t reg)
{
  uint8_t data_H=0,data_L=0;
  LDC_IIC_Start(); 
  LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|0);//发送器件地址+写命令	
  LDC_IIC_Wait_Ack();		//等待应答 
  LDC_IIC_Send_Byte(reg);	//写寄存器地址
  LDC_IIC_Wait_Ack();		//等待应答
  LDC_IIC_Start();
  LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|1);//发送器件地址+读命令	
  LDC_IIC_Wait_Ack();		//等待应答 
  data_H = LDC_IIC_Read_Byte(1);//读取数据,发送nACK 
  data_L = LDC_IIC_Read_Byte(0);//读取数据,发送nACK 
  LDC_IIC_Stop();			//产生一个停止条件 	
  return ( (data_H<<8) | (data_L) );
}


void LDC1614_AUTO_INIT(void)
{
	LDC1614_i2c_INIT();
	LDC1614_send_word(RESET_DEV,0x8800);
	delayms(100);
	while(ldc1614_readbuf[0]!=0x3055)
		ldc1614_readbuf[0]=LDC1614_read_word(DEVICE_ID);//等待，I2C正常
//WordWrite1614（RESET_DEV，0x8800）;
/*重启LDC1614*/
//	LDC1614_send_word(MUX_CONFIG,0x8209);//2451开启ch3
/*默认值，睡眠模式开，方便配置*/
	LDC1614_send_word(CLOCK_DIVIDERS_CH0,0X1005);//fSENSOR 1分频，fCLK 1分频
	LDC1614_send_word(CLOCK_DIVIDERS_CH1,0X1005);//fSENSOR 1分频，fCLK 1分频
	LDC1614_send_word(CLOCK_DIVIDERS_CH2,0X1005);//fSENSOR 1分频，fCLK 1分频
	LDC1614_send_word(CLOCK_DIVIDERS_CH3,0X1005);//fSENSOR 1分频，fCLK 1分频
/* 时钟源分频选择，分频系数1，
　　Using L and C， 得fSENSOR = 1/2π*sqrt（L*C）
　　注意fSENSOR须小于8.75 MHz，fSENSOR分频系数才能置1
　　注意fREF0须至少大于 4 × fSENSOR，以决定fREF0分频系数
　　fin0 = fSENSOR0/CH0_FIN_DIVIDER
　　fREF0 = fCLK / CH0_FREF_DIVIDER
*/
	LDC1614_send_word(SETTLECOUNT_CH0,0xf060);//0x0A60
	LDC1614_send_word(SETTLECOUNT_CH1,0xf060);
	LDC1614_send_word(SETTLECOUNT_CH2,0xf060);
	LDC1614_send_word(SETTLECOUNT_CH3,0xf060);
/* 建立（Settling）时间设置
　　计算得Q=Rp*sqrt（C/L）
　　寄存器值小于10取10，大于10取其值，且应满足以下条件：
　　CHx_SETTLECOUNT ≥ QSENSORx × fREFx / （16 × fSENSORx） （10进制）
　　（1）fSENSORx:x通道传感器频率
　　（2）fREFx:x通道参考频率
　　（3）QSENSORx：品质因数，Q=Rp ×sqrt（C/L）
　　注意，不等式右边算出有小数则向上取整
　　建立时间tSx = （CH0_SETTLECOUNT*16） / fREF0
　　通道切换时间tCsd = Channel Switch Delay = 692 ns + 5 / fref （us）
*/
	LDC1614_send_word(RCOUNT_CH0,0xffFF);//ffff
	LDC1614_send_word(RCOUNT_CH1,0xffFF);
	LDC1614_send_word(RCOUNT_CH2,0xffFF);
	LDC1614_send_word(RCOUNT_CH3,0xffFF);
/*转换时间设置
　　得转换时间tCx = TSAMPLE（采样时间） – tSx – tCsd （us）
　　由下式算出寄存器的值（有小数则向下取整（舍去））：
　　转换时间tCx = （CHx_RCOUNT × 16） / fREFx （10进制）
　　注意寄存器的值化为16进制
*/
/*使用ERROR_CONFIG默认值，错误中断关闭*/
//	LDC1614_send_word(DRIVE_CURRENT_CH0,i_temp<<11);//0x9800
//	LDC1614_send_word(DRIVE_CURRENT_CH1,0xffc0);
//	LDC1614_send_word(DRIVE_CURRENT_CH2,0xffc0);
//	LDC1614_send_word(DRIVE_CURRENT_CH3,i_temp<<11);
/*传感器驱动电流设置，使用请同时注意CONFIG寄存器相关配置
　　查数据手册的Figure 15，得IDRIVE值（10进制），INIT_DRIVE值不使用，保持默认
　　使用CH0_IDRIVE［15:11］时，Rp Override须打开
　　使用CH0_INIT_IDRIVE［10:6］时，保证AUTO_AMP_DIS位不置位
*/
LDC1614_send_word(MUX_CONFIG,0xC20D);//801
/* 多通道转换选择，输入尖峰脉冲滤波器带宽选择，使用请同时注意CONFIG寄存器相关配置！
　　（a）置AUTOSCAN_EN位为b1使能连续模式（sequential mode）
　　（b）置RR_SEQUENCE位为b00使能两个通道的数据转换（channel 0，channel 1）
　　（c）置DEGLITCH位为b100设定输入尖峰脉冲滤波器带宽，此值必须高于谐振频率fTank！
*/
//LDC1614_send_word(OFFSET_CH0,0x00);
/*频率偏移（补偿）设置
　　可以设置从每个数据值中减去偏移值，以补偿频率偏移或最大化动态范围的样本数据
　　fOFFSET0 = CH0_OFFSET * （fREF0/2^16）
　　且偏移值应小于 fSENSORx_MIN / fREFx
*/
//	LDC1614_send_word(RESET_DEV,2<<9);
/*输出增益设置，［10:9］，对所有通道有效
　　对于传感器信号变化量小于满量程25％的系统，设置输出增益可以提供更高的分辨率（精度）
*/
/*
状态寄存器：STATUS，ERROR_CONFIG
*/
	LDC1614_send_word(CONFIG,0xD481&(~(1<<12))&(~(1<<10)));//1501
	delayms(1);
	LDC1614_send_word(CONFIG,0xD481&(~(1<<12))&(~(1<<10)));//1501
/*默认连续转换（单）通道0，睡眠模式关，Rp Override开
低功耗模式关，传感器自动幅度校正（AUTO_AMP）关，Ref时钟源选外部时钟源
INTB中断开，高电流驱动关*/
}

void LDC1614_INIT(u8 i_temp)
{
	LDC1614_i2c_INIT();
	LDC1614_send_word(RESET_DEV,0x8800);
	delayms(100);
	while(ldc1614_readbuf[0]!=0x3055)
		ldc1614_readbuf[0]=LDC1614_read_word(DEVICE_ID);//等待，I2C正常
//WordWrite1614（RESET_DEV，0x8800）;
/*重启LDC1614*/
//	LDC1614_send_word(MUX_CONFIG,0x8209);//2451开启ch3
/*默认值，睡眠模式开，方便配置*/
	LDC1614_send_word(CLOCK_DIVIDERS_CH0,0X2009);//fSENSOR 1分频，fCLK 1分频
	LDC1614_send_word(CLOCK_DIVIDERS_CH1,0X1014);//fSENSOR 1分频，fCLK 1分频
	LDC1614_send_word(CLOCK_DIVIDERS_CH2,0X1014);//fSENSOR 1分频，fCLK 1分频
	LDC1614_send_word(CLOCK_DIVIDERS_CH3,0X2009);//fSENSOR 1分频，fCLK 1分频
/* 时钟源分频选择，分频系数1，1
　　Using L and C， 得fSENSOR = 1/2π*sqrt（L*C）
　　注意fSENSOR须小于8.75 MHz，fSENSOR分频系数才能置1
　　注意fREF0须至少大于 4 × fSENSOR，以决定fREF0分频系数
　　fin0 = fSENSOR0/CH0_FIN_DIVIDER
　　fREF0 = fCLK / CH0_FREF_DIVIDER
*/
	LDC1614_send_word(SETTLECOUNT_CH0,0xf060);//0x0A60
	LDC1614_send_word(SETTLECOUNT_CH1,0xf060);
	LDC1614_send_word(SETTLECOUNT_CH2,0xf060);
	LDC1614_send_word(SETTLECOUNT_CH3,0xf060);
/* 建立（Settling）时间设置
　　计算得Q=Rp*sqrt（C/L）
　　寄存器值小于10取10，大于10取其值，且应满足以下条件：
　　CHx_SETTLECOUNT ≥ QSENSORx × fREFx / （16 × fSENSORx） （10进制）
　　（1）fSENSORx:x通道传感器频率
　　（2）fREFx:x通道参考频率
　　（3）QSENSORx：品质因数，Q=Rp ×sqrt（C/L）
　　注意，不等式右边算出有小数则向上取整
　　建立时间tSx = （CH0_SETTLECOUNT*16） / fREF0
　　通道切换时间tCsd = Channel Switch Delay = 692 ns + 5 / fref （us）
*/
	LDC1614_send_word(RCOUNT_CH0,0xffFF);//ffff
	LDC1614_send_word(RCOUNT_CH1,0xffFF);
	LDC1614_send_word(RCOUNT_CH2,0xffFF);
	LDC1614_send_word(RCOUNT_CH3,0xffFF);
/*转换时间设置
　　得转换时间tCx = TSAMPLE（采样时间） – tSx – tCsd （us）
　　由下式算出寄存器的值（有小数则向下取整（舍去））：
　　转换时间tCx = （CHx_RCOUNT × 16） / fREFx （10进制）
　　注意寄存器的值化为16进制
*/
/*使用ERROR_CONFIG默认值，错误中断关闭*/
	LDC1614_send_word(DRIVE_CURRENT_CH0,i_temp<<11);//0x9800
	LDC1614_send_word(DRIVE_CURRENT_CH1,0xffc0);
	LDC1614_send_word(DRIVE_CURRENT_CH2,0xffc0);
	LDC1614_send_word(DRIVE_CURRENT_CH3,i_temp<<11);
/*传感器驱动电流设置，使用请同时注意CONFIG寄存器相关配置
　　查数据手册的Figure 15，得IDRIVE值（10进制），INIT_DRIVE值不使用，保持默认
　　使用CH0_IDRIVE［15:11］时，Rp Override须打开
　　使用CH0_INIT_IDRIVE［10:6］时，保证AUTO_AMP_DIS位不置位
*/
LDC1614_send_word(MUX_CONFIG,0xC20D);//801
/* 多通道转换选择，输入尖峰脉冲滤波器带宽选择，使用请同时注意CONFIG寄存器相关配置！
　　（a）置AUTOSCAN_EN位为b1使能连续模式（sequential mode）
　　（b）置RR_SEQUENCE位为b00使能两个通道的数据转换（channel 0，channel 1）
　　（c）置DEGLITCH位为b100设定输入尖峰脉冲滤波器带宽，此值必须高于谐振频率fTank！
*/
//LDC1614_send_word(OFFSET_CH0,0x00);
/*频率偏移（补偿）设置
　　可以设置从每个数据值中减去偏移值，以补偿频率偏移或最大化动态范围的样本数据
　　fOFFSET0 = CH0_OFFSET * （fREF0/2^16）
　　且偏移值应小于 fSENSORx_MIN / fREFx
*/
//	LDC1614_send_word(RESET_DEV,0x00);
/*输出增益设置，［10:9］，对所有通道有效
　　对于传感器信号变化量小于满量程25％的系统，设置输出增益可以提供更高的分辨率（精度）
*/
/*
状态寄存器：STATUS，ERROR_CONFIG
*/
	LDC1614_send_word(CONFIG,0xD481);//1501
	delayms(1);
	LDC1614_send_word(CONFIG,0xD481);//1501
/*默认连续转换（单）通道0，睡眠模式关，Rp Override开
低功耗模式关，传感器自动幅度校正（AUTO_AMP）关，Ref时钟源选外部时钟源
INTB中断开，高电流驱动关*/
}

/*读取LDC1614转换结果，输入参数为选择通道数*/
uint32_t LDC1614_Result(uint8_t Channal)
{
  uint32_t result = 0;
  uint16_t msb = 0;
  uint16_t lsb = 0;
  switch(Channal)
  {
    case 0x00:
            msb=LDC1614_read_word(DATA0_MSB); //通道0
            lsb=LDC1614_read_word(DATA0_LSB);
            break;
    case 0x01:
            msb=LDC1614_read_word(DATA1_MSB); //通道1
            lsb=LDC1614_read_word(DATA1_LSB);
            break;
    case 0x02:
            msb=LDC1614_read_word(DATA2_MSB); //通道2
            lsb=LDC1614_read_word(DATA2_LSB);
            break;
    case 0x03:
            msb=LDC1614_read_word(DATA3_MSB); //通道3
            lsb=LDC1614_read_word(DATA3_LSB);
            break;
    default:
            break;
  }
//	while((temp&0xF000)!=0);

/*有错误Flag！，有输出增益时注意此句，可能出错！
　　0x000 = under range，0xfff = over range
　　*/
//	return (temp&0x0fff);//忽略错误标志
  result = (msb<<16) | lsb;
        return (result);
}















