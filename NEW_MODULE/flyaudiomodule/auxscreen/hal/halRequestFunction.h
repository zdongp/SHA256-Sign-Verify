#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__
#include "global.h"

void auxScreenToHal_Init();//��ʼ��
void auxScreenToHal_EmulateKey(u8 );//ģ�ⰴ��
void auxScreenToHal_PlayingModule(u8 );//���ڲ���ģ��
void auxScreenToHal_PlayingInfo(u8*, int );//������Ϣ
//2012��6��27�� 10:26:37
void auxScreenToHal_PlayVolume(unsigned char );
void auxScreenToHal_TimeInfo(u8*,int);
void auxScreenToHal_GPSInfo(u8 *param,int len);
void auxScreenToHal_GaodeMap_GPSInfo(u8* buf,int len);


#endif
