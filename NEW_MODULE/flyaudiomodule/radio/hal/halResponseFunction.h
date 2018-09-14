#ifndef __HAL_RESPONSE_COMMAND_RADIO_H__
#define __HAL_RESPONSE_COMMAND_RADIO_H__

#include "global.h"
#include "messageQueue.h"

void analyseHalMessage_RADIO(char _RES, unsigned char *param, unsigned char len);

void halToRadio_InitParam(u8 nParam);//初始化参数
void halToRadio_InitState(u8 nState);//初始化状态
void halToRadio_Frequency(u16 nFrequency);//频点
void halToRadio_ScanCtrlState(u8 nState);//Scan控制状态
void halToRadio_SearchState();//搜索状态
void halToRadio_PowerState(u8 nState);//开关状态
void halToRadio_AFState(u8 nState);//AF状态
void halToRadio_TAState(u8 nState);//TA状态
void halToRadio_FlickerCtrl(u8 nCtrlFlag);//闪烁控制
void halToRadio_FrequencyChannel(u8 cChannel);//频段
void halToRadio_FrequencyName(u8* buf,u32 len);//频道名称
void halToRadio_CurTextInfo(u8* buf,u32 len);//当前文本信息
void halToRadio_CurProgaramType(u8 nType);//当前的节目类型
void halToRadio_AreaChoose(u8* buf, u32 len);//    收音机区域选择
void IsCurFreqInRecord(u16 nChannel, u16 nFrequency);
void halTRadio_Switch_TP(u8 nState);
void halTRadio_Switch_AF(u8 nState);
void halTRadio_Switch_TA(u8 nState);

void RadioToApp_Get_sensitivityState(u8 state);


void halToAutoMate(char resCmd, unsigned char *param, unsigned char len);



#endif
