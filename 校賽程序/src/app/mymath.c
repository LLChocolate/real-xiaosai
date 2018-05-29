#include "mymath.h"

int max_s16(int temp[],u16 num)
{
  u16 i;
  int max=-32768;
  for(i=0;i<num;i++)
  {
    if(max<temp[i])
    {
      max=temp[i];
    }
  }
  return max;
}

u8 max_u8(u8 temp[],u16 num)
{
  u16 i;
  u8 max=0;
  for(i=0;i<num;i++)
  {
    if(max<temp[i])
    {
      max=temp[i];
    }
  }
  return max;
}

int min_s16(int temp[],u16 num)
{
  u16 i;
  int min=32767;
  for(i=0;i<num;i++)
  {
    if(min>temp[i])
    {
      min=temp[i];
    }
  }
  return min;
}
u8 min_u8(u8 temp[],u16 num)
{
  u16 i;
  u8 min=0xff;
  for(i=0;i<num;i++)
  {
    if(min>temp[i])
    {
      min=temp[i];
    }
  }
  return min;
}

int power_s16(int buttom,u8 po)
{
  u8 i;
  int result=1;//0´ÎÃİÎª1
  for(i=0;i<po;i++)
  {
    result*=buttom;
  }
  return result;
}

int sum_s16(int input[],u16 num)
{
  u16 i;
  int sum=0;
  for(i=0;i<num;i++)
  {
    sum+=input[i];
  }
  return sum;
}
int sum_u8(u8 input[],u16 num)
{
  u16 i;
  int sum=0;
  for(i=0;i<num;i++)
  {
    sum+=input[i];
  }
  return sum;
}

u16 abs_s16(int i)
{
    if(i>=0)return i;
  else return -i;
}