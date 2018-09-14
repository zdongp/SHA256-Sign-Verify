#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "param.h"
#include "moduleParamResponse.h"
#include <flymoduleApi_internal.h>


void radioTohal_InitCmd(u8 nState)
{
	LOGD("notify  hal init");
    u8 buf[] = {0x01,nState};
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 2);
}//初始化命令

void radioTohal_InitParamCmd(u8 *param,int len)
{
	LOGD("notify  hal Paraminit");
	u8 buf[64];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x02;
	memcpy(buf+1,param,len);
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, len+1);
}//初始化命令

void radioTohal_ImitateKey(u8 nState)
{
	if(nState == 0x02)
		nState = 0x01;
	u8 buf[] = {0x03, nState};
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 2);
}//模拟按键


void radioTohal_Frequency2(u16 nFrequency)
{
	LOGD("radioTohal_Frequency2   Frequency = %d", nFrequency);
	unsigned char buf[3];
	buf[0] = 0x10;
	buf[1] = (unsigned char)( (nFrequency & 0xFF00) >> 8);
	buf[2] = (unsigned char)(nFrequency & 0x00FF);
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 3);
}

void radioTohal_Frequency(u16 nFrequency)
{
	LOGD("radioTohal_Frequency = %d", nFrequency);
	u8 buf[3];
	buf[0] = 0x10;
	memcpy(&buf[1], &nFrequency, 2);
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 3);
}//设置收音机频率
	
void radioTohal_Frequency_Inc(u8 nState)
{
	u8 buf[] = {0x11, nState};
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 2);
}//频率增加
	
void radioTohal_Frequency_Dec(u8 nState)
{
	u8 buf[] = {0x12, nState};
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 2);
}//频率减少

void radioTohal_ScanCtrl(u8 nState)
{
	u8 buf[] = {0x13, nState};
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 2);
}//扫描控制
	

void rdaioToHal_Scan(int cmd)
{
	//ModuleParamResponse_WriteData();
	if(Ctrl_STOP != pLocalParam->eScanState)
	{
		radioTohal_ScanCtrl(Ctrl_STOP);
	}
	else
	{
		radioTohal_ScanCtrl(cmd);
	}
}


void radioTohal_RadioSwitch_Power(u8 nState)
{
	u8 buf[] = {0x15, nState};
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 2);
}//收音机开关

void radioTohal_RadioSwitch_AF(u8 nState)
{
	u8 buf[] = {0x41, nState};
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 2);
}//AF 开关

	

void radioTohal_RadioSwitch_TA(u8 nState)
{
	u8 buf[] = {0x42, nState};
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 2);
}//TA 开关
	

// add and modify  yangzhong 2012-12-29 10:45:38
void radioTohal_RadioContinuousBeginAndEndNode(u16 beginNode, u16 endNode)
{
	u8 buf[5];
	//buf[0] = 0x30;
	//memcpy(&buf[1], &beginNode, 2);
	//memcpy(&buf[3], &endNode, 2);
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 5);
}//连续搜索的起始频点和结束频点


void radioTohal_RadioDebugText(u8 nState)
{
	u8 buf[] = {0xFF, nState};
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 2);
}//Debug 通道

void radioTohal_SetSensitivity(u8 state)
{
	LOGD("radioTohal_SetSensitivity:state=%d",state);
	u8 buf[2] ={0x43,state};
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 2);
}

void radioTohal_SetChannelAndFre(u8 nChannel,u16 nFrequency)
{
       LOGD("[%s]  channel = %x , Frequency = %d", __FUNCTION__,nChannel,nFrequency);
       unsigned char buf[4];
       buf[0] = 0x09;
       buf[1] = nChannel;
       buf[2] = (unsigned char)( (nFrequency & 0xFF00) >> 8);
       buf[3] = (unsigned char)(nFrequency & 0x00FF);
       makeAndSendMessageToHal(HAL_ID_RADIO, buf, 4);
}