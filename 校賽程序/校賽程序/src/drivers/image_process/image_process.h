#ifndef __IMAGE_PROCESS_H__
#define __IMAGE_PROCESS_H__

#include "common.h"
//寻找黑线并寻找中心值
#define CENTER_             160
#define HALF_WIDTH          126
#define HALF_NEAR           170
#define Far_Point           72            //1m处
#define Start_Point         105         //45cm处
#define Near_Point          150            //近处
#define ALL_LINE            240
#define Image_Point(x,y)    Image_fire[x][y/8]>>(7-(y%8))&1
void image_process(void);
void get_black_line(unsigned char *ImageData_in,int hang,int half_width);//捕捉黑线 
void CenterlineToDiff(int center);
void get_three_lie(void);
void StoreDate(void);
u8 Cross_Test(void);

#endif