#include "include.h"
#include "ldc1000.h"

#define SPI_RWBIT 		0x80
unsigned long ProximityData;
float Y_ProximityData;
unsigned long FrequencyData;  
unsigned long Fre_sensor;
//float Fre_sensor;
unsigned long Rp_MaxData;
unsigned long Rp_MinData;
unsigned long Rp_RealData;
const int Response_time = 6144;
unsigned int  DataRcv[5] ;  
u8 Status;
Filter_1st_Str  Rp_1st={0.8,{0,0},{0,0}};
Filter_1st_Str  Fre_1st={0.8,{0,0},{0,0}};

void LdcInit(void)
{
  gpio_init(PORTD,14,GPO,LOW);
  gpio_init(PORTE,7,GPO,LOW);
  gpio_init(PORTD,12,GPI,LOW);
  gpio_init(PORTD,13,GPO,LOW);
  exti_init(PORTD,11,rising_up);
  
  gpio_init(PORTC,3,GPO,LOW);
  SIM_SCGC5 |= (SIM_SCGC5_PORTC_MASK);
  PORT_PCR_REG(PORTX[PORTC],3) = PORT_PCR_MUX(5);//设置PA6为输出总线频率模式；
  LdcParaInit();
}

u16 LdcWriteRead(u16 data)
{
  u16 rdata;
  u8 ret;
  u8 i;
  CS=0;
  
  for(i=0;i<16;i++)
  {
    if(data&0X8000)
       SO = 1;
    else
       SO = 0;
    data <<= 1;
    rdata <<= 1;
    if(SI)
        rdata |= 1;
    else
        rdata &= ~1;
    
    SCLK = 1;
    delayus(4);
    SCLK = 0;
    delayus(4);
  }
  
  ret = rdata&0XFF;
  CS=1;
  return ret;
}
void LdcWriteReg(u8 addr, u8 data)
{
  u16 wAddr = addr;
  wAddr <<= 8;
  wAddr |= data;
  LdcWriteRead(wAddr);
}

u8 LdcReadReg(u8 addr)
{
  u16 wAddr = (addr | SPI_RWBIT);
  wAddr <<= 8;
  return LdcWriteRead(wAddr);
}
/**************************
*oˉêy1|?ü￡oldc1000 3?ê??ˉ
*°?±?D??￠￡o2016.7.19 by Jiaqing
***************************/
void LdcParaInit(void)
{
  u8 LDC_ID = 0;
  while(LDC_ID!=0x80)
    LDC_ID = LdcReadReg(LDC1000_CMD_REVID);
  
  LdcWriteReg(LDC1000_CMD_PWRCONFIG,   0x00);
//  LdcWriteReg(LDC1000_CMD_RPMAX,0x0C);
  LdcWriteReg(LDC1000_CMD_RPMAX,0x0);
  Rp_MaxData = 21.547e3;
//  LdcWriteReg(LDC1000_CMD_RPMIN,0x33);					//????Rp_MIN(0x02)??′??÷
  LdcWriteReg(LDC1000_CMD_RPMIN,0x30);
  Rp_MinData = 3.078e3;
  LdcWriteReg(LDC1000_CMD_SENSORFREQ,0xd8);						//????Sensor Frequency(0x03)??′??÷
  LdcWriteReg(LDC1000_CMD_LDCCONFIG,0x17);							//????LDC Configuration(0x04)??′??÷
  LdcWriteReg(LDC1000_CMD_CLKCONFIG,0x02);							//????Clock Configuration(0x05)??′??÷,
//  LdcWriteReg(LDC1000_CMD_INTCONFIG,0x02);
//  LdcWriteReg(LDC1000_CMD_THRESHILSB,0x50);						//????Comparator Threshold High(0x06)??′??÷μí8??
//  LdcWriteReg(LDC1000_CMD_THRESHIMSB,0x14);						//????Comparator Threshold High(0x07)??′??÷??8??
//  LdcWriteReg(LDC1000_CMD_THRESLOLSB,0xC0);						//????Comparator Threshold Low(0x08)??′??÷μí8??
//  LdcWriteReg(LDC1000_CMD_THRESLOMSB,0x12);							//????INTB Pin Configuration(0x0A),	
  LdcWriteReg(LDC1000_CMD_PWRCONFIG,0x01);							//????Power Configuration(0x0B)??′??÷￡?	//?aActive Mode,ê1?ü×a?ˉ
  delayms(1);
  LdcWriteReg(LDC1000_CMD_PWRCONFIG,0x01);
}
/**************************
*oˉêy1|?ü￡oldc?áè? RP oí Frequency
*°?±?D??￠￡o2016.7.19 by Jiaqing
***************************/
void LdcRead(void)
{
  
  ProximityData = 0;
  FrequencyData = 0;
  Status = LdcReadReg(LDC1000_CMD_STATUS);
  DataRcv[0] = LdcReadReg(LDC1000_CMD_PROXLSB);          			//D′è???òa?áè?μ?Proximity Data LSB??′??÷μ??·(0x21)
  ProximityData|= DataRcv[0] ;
  DataRcv[1] = LdcReadReg(LDC1000_CMD_PROXMSB);					//D′è???òa?áè?μ?Proximity Data MSB??′??÷μ??·(0x22)
  ProximityData|= (DataRcv[1]<<8) ;									//×éo?3éProximityData
//  ProximityData = filter_1st(ProximityData,&Rp_1st);
  
  Y_ProximityData = ProximityData*1.0/power_s16(2,15);
  
  DataRcv[2] = LdcReadReg(LDC1000_CMD_FREQCTRLSB);					//D′è???òa?áè?μ?Frequency Counter Data LSB??′??÷μ??·(0x23)
  FrequencyData|= DataRcv[2] ;
  DataRcv[3] = LdcReadReg(LDC1000_CMD_FREQCTRMID);					//D′è???òa?áè?μ?Frequency Counter Data Mid-Byte??′??÷μ??·(0x24)
  FrequencyData|= (DataRcv[3]<<8) ;
  
  DataRcv[4] = LdcReadReg(LDC1000_CMD_FREQCTRMSB);					//D′è???òa?áè?μ?Frequency Counter Data MSB??′??÷μ??·(0x25)
  FrequencyData|= (DataRcv[4]<<16) ;	 //×éo?3éFrequencyData

  Rp_RealData = (Rp_MaxData*Rp_MinData)/(Rp_MinData*(1-Y_ProximityData)+Rp_MaxData*(Y_ProximityData));
  Fre_sensor=F_ref*1.0*Response_time/(3*(FrequencyData+1));
//  Fre_sensor = filter_1st(Fre_sensor,&Fre_1st);
  
  
}
/**************************
*oˉêy1|?ü￡oμ÷?úRp_MINoíRp_MAXμ?oˉêy
*2?êy?μ?÷￡omax - 0X00-0X1F   min - 0X20-0X3F
*°?±?D??￠￡o2016.7.19 by Jiaqing
***************************/
void LdcSetRp(u8 max, u8 min)
{
  /*
  if(max>0X1F)
  return;
  if((min<0X20) || (min>0X3F))
  return;
  */	
  LdcWriteReg(LDC1000_CMD_PWRCONFIG,0x00);
  LdcWriteReg(LDC1000_CMD_RPMAX, max);					//????Rp_MAX(0x01)??′??÷
  LdcWriteReg(LDC1000_CMD_RPMIN, min);					//????Rp_MIN(0x02)??′??÷
  LdcWriteReg(LDC1000_CMD_PWRCONFIG,0x01);
}