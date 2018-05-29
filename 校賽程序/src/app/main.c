#include "include.h"
#include "stdlib.h"
//u8 B_f=0;

Motor_Status Motor1;//电机状态结构体
Motor_Status Motor2;//电机状态结构体
int Speed_L_50ms=0;
int Speed_R_50ms=0;
u32 Duty_Motor1;//电机占空比
u32 Duty_Motor2;//电机占空比
PID_Struct Motor1_PID;//pid结构体
PID_Struct Motor2_PID;//pid结构体
PID_Struct Diff_PID;//差速PID
PID_Struct Diff_Straight;//直线PID
float Speed_goal1=10;//电机转速目标值
float Speed_goal2=10;//电机转速目标值
u16 Diff_goal=0;
int Diff_error=0;
u16 Master_Speed=4;
u16 Differ_Speed=2;
u16 ADC_Value;//ADC值
u16 Speed_stand;
int Weight_mean=0;
uint16_t ldc1614_init0,ldc1614_init1,
         ldc1614_init2,ldc1614_init3;
int ldc_temp=0;
//***************************定时器标志位*************************
u8 button_timeout=255;//按键时间标志
long int Time_1ms=0;//时间轴
//****************************************************************
u8 Road_Status_Flag=0;
u8 Switch_Status;//拨码状态
u8 Key_status;//按键状态
u8 LCD_DISPLAY_FLAG=1;
u8 Motor_enable_Flag=1;
u8 Slow_Flag=0;
u8 Reduct_Flag=0;
u8 Blue_Start_Flag=1;//蓝牙开启
u8 Key_Start_Flag=0;
u8 Left_Turn=0;
u8 Right_Turn=0;
u8 Go_straight=0;
u8 Init_Speed_flag=1;
//***********************调试用临时全局变量**************************
float stand_p;
float stand_d;
int P_TEMP1=550;//201//550
int I_TEMP1=70;//70
int D_TEMP1=0;
int P_TEMP2=550;//90
int I_TEMP2=70;
int D_TEMP2=0;
signed int Speed_goal1_TEMP=40;//电机转速目标值
signed int Speed_goal2_TEMP=40;//电机转速目标值
u8 Image_Flag=0;
u8 LED_timeout=50;
u8 Dir_temp=1;
  u16 hang=0;
  int DIFF_UP=110;
  int DIFF_DOWN=-110;
long int  temp_cnt=0;
u8 DIFF_PID_CHANGE_FLAG=0;
u16 temp_CNT_WATCH=0;
u8 Speed_max_to_min_diff;
u8 Acc_Limit=40;
float Acc_K=1;
uint16_t ldc1614_readbuf[8];
uint16_t ldc1614_result[4];
uint16_t result_temp[32];
//******************************************************************
void main()
{


  //u8 Str_temp[40];//
  u8 Key;
  u16 i=0,j;

  System_Init();
  Brush_Color=Black;
  Motor1_PID.P=P_TEMP1;
  Motor1_PID.I=I_TEMP1;
  Motor1_PID.D=D_TEMP1;
  Motor2_PID.P=P_TEMP2;
  Motor2_PID.I=I_TEMP2;
  Motor2_PID.D=D_TEMP2;
  Motor1_PID.target=Speed_goal1;
  Motor2_PID.target=Speed_goal2;
  Duty_Motor1=32767;
  Duty_Motor2=32767;

  
  
//  while(1)
//  {
//    MOTOR1_DIR=1;
//    FTM_PWM_Duty(MOTOR_1,Duty_Motor1);
//    MOTOR2_DIR=1;
//    FTM_PWM_Duty(MOTOR_2,Duty_Motor2);
//  }

  
//for(i=0;i<32;i++)
//{
//  delayms(500);
//  LDC1614_INIT(0);
//  delayms(500);
//  result_temp[i]=LDC1614_Result(0);
//}
while(1)
{
  Motor1_PID.P=P_TEMP1;
  Motor1_PID.I=I_TEMP1;
  Motor1_PID.D=D_TEMP1;
  Motor2_PID.P=P_TEMP2;
  Motor2_PID.I=I_TEMP2;
  Motor2_PID.D=D_TEMP2;
  
//    if(Init_Speed_flag==1)
//  {
//     MOTOR1_DIR=0; 
//     FTM_PWM_Duty(MOTOR_1,8000);
//     MOTOR2_DIR=0;
//     FTM_PWM_Duty(MOTOR_2,8000);
//  }

//摄像头采集一次
//图像处理  
//    if(Image_Flag==1)
//    {
//      Image_Flag=0;
////      StoreDate();//转存数据
//      ov7725_get_img();//转存结束后立刻允许接收场中断
//      if(LCD_DISPLAY_FLAG==1)  
//      Send_Image_to_LCD(Image_fire);
//      image_process();
//      if(LCD_DISPLAY_FLAG==1)
//      {
//        LCD_Draw_Line(100,Three_lie_end[0],100,160);  
//        LCD_Draw_Line(160,Three_lie_end[1],160,160);  
//        LCD_Draw_Line(220,Three_lie_end[2],220,160);  
////        LCD_Draw_Line(101,0,101,240);  
////        LCD_Draw_Line(81,0,81,240);  
////        LCD_Draw_Line(37,0,37,240);  
////        LCD_Draw_Line(0,73,319,73);  
////        LCD_Draw_Line(0,90,319,90);  
////        LCD_Draw_Line(0,140,319,140);
//        LCD_Draw_Line(0,105,319,105);
//        LCD_Draw_Line(0,100,319,100);
//        
//      }
//      temp_cnt++;
//    }
  
  
/*
    if(LCD_DISPLAY_FLAG==1)
    {
      LCD_Put_Int(210,10,"",Diff_PID.result,Red,White);
      LCD_Put_Int(240,10,"",Weight_mean,Red,White);
      LCD_Put_Int(180,10,"",Black_Lock,Red,White);
      LCD_DrawPoint(160-90,Start_Point);
//      LCD_DrawPoint(160-60 ,Start_Point);
//      LCD_DrawPoint(160+60 ,Start_Point);
      LCD_DrawPoint(160+90,Start_Point);
      LCD_DrawPoint(160-65,Start_Point-20);
      LCD_DrawPoint(160+65,Start_Point-20);

      LCD_DrawPoint(160-40,Start_Point-40);
      LCD_DrawPoint(160+40,Start_Point-40);
//      LCD_DrawPoint(160-120,Start_Point);
    }
*/    
    
    
    
//  Speed_goal1=Speed_goal2=Speed_stand;
  
//调试用？
/*
Motor1_PID.target=Speed_goal1;//+1;
Motor2_PID.target=Speed_goal2;
*/
  
 
//  SCISend_to_PIDDebug(UART5);
  //SCI_Send_Datas(UART5);
//  hang++;
  if(Motor_enable_Flag==0)
  {
    Speed_goal1=0;
    Speed_goal2=0;
    
    if(Motor1.Speed<1&&Motor2.Speed<1)
    {
      disable_irq(68); 
      MOTOR1_DIR=0;
      FTM_PWM_Duty(MOTOR_1,0);
      MOTOR2_DIR=0;
      FTM_PWM_Duty(MOTOR_2,0);
    }
  }
  if(Blue_Start_Flag==0)
  {
      MOTOR1_DIR=0;
      FTM_PWM_Duty(MOTOR_1,0);
      MOTOR2_DIR=0;
      FTM_PWM_Duty(MOTOR_2,0);
  }
  
  /*
  if(hang>ALL_LINE)//图像扫描太多次，退出程序
  {
    hang=1;
    centre[0]=centre[ALL_LINE-1];
//    break;
  }
  */
  
}
BEEP_Open_once();
while(1);
}