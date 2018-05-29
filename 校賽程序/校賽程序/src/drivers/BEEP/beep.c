#include "beep.h"


void myBEEP_Init(void)
{
  gpio_init(PORTD,6,GPO,LOW);
  BEEP_Open_once();
} 

void BEEP_Open_once(void)
{
  BEEP=1;
  delayms(10);
  BEEP=0;
} 
