#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__
#include "global.h"

void auxScreenToHal_Init();//初始化
void auxScreenToHal_EmulateKey(u8 );//模拟按键
void auxScreenToHal_PlayingModule(u8 );//正在播放模块
void auxScreenToHal_PlayingInfo(u8*, int );//播放信息
//2012年6月27日 10:26:37
void auxScreenToHal_PlayVolume(unsigned char );
void auxScreenToHal_TimeInfo(u8*,int);
void auxScreenToHal_GPSInfo(u8 *param,int len);
void auxScreenToHal_GaodeMap_GPSInfo(u8* buf,int len);


#endif
