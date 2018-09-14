#ifndef __HAL_RESPONSE_COMMAND_RADIO_H__
#define __HAL_RESPONSE_COMMAND_RADIO_H__

#include "global.h"
#include "messageQueue.h"

void analyseHalMessage_RADIO(char _RES, unsigned char *param, unsigned char len);

void halToRadio_InitParam(u8 nParam);//��ʼ������
void halToRadio_InitState(u8 nState);//��ʼ��״̬
void halToRadio_Frequency(u16 nFrequency);//Ƶ��
void halToRadio_ScanCtrlState(u8 nState);//Scan����״̬
void halToRadio_SearchState();//����״̬
void halToRadio_PowerState(u8 nState);//����״̬
void halToRadio_AFState(u8 nState);//AF״̬
void halToRadio_TAState(u8 nState);//TA״̬
void halToRadio_FlickerCtrl(u8 nCtrlFlag);//��˸����
void halToRadio_FrequencyChannel(u8 cChannel);//Ƶ��
void halToRadio_FrequencyName(u8* buf,u32 len);//Ƶ������
void halToRadio_CurTextInfo(u8* buf,u32 len);//��ǰ�ı���Ϣ
void halToRadio_CurProgaramType(u8 nType);//��ǰ�Ľ�Ŀ����
void halToRadio_AreaChoose(u8* buf, u32 len);//    ����������ѡ��
void IsCurFreqInRecord(u16 nChannel, u16 nFrequency);
void halTRadio_Switch_TP(u8 nState);
void halTRadio_Switch_AF(u8 nState);
void halTRadio_Switch_TA(u8 nState);

void RadioToApp_Get_sensitivityState(u8 state);


void halToAutoMate(char resCmd, unsigned char *param, unsigned char len);



#endif
