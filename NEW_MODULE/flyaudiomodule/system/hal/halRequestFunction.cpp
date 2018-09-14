#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"
#include "pageID.h"

#include "appResponseFunction.h"
#include "param.h"

#include <flymoduleApi_internal.h>

void systemToHal_Init(char param){
	unsigned char cmdParam[2] = {0x01, 0x00};
	if(param){
		cmdParam[1] = 0x01;
	}
	makeAndSendMessageToHal(HAL_ID_SYSTEM, cmdParam, 2);
}

void systemToHal_SimulateKey(unsigned char key){
	unsigned char keyParam[2] = {0x03,key};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, keyParam, 2);
}

void systemToHal_SetSystemUpdate(void)
{	
	LOGD("systemToHal_SystemUpdate");
	unsigned char cmdParam[2] = {0x03, 0x08};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, cmdParam, 2);
}


void systemToHal_BackCarDetected(char enable){
	//unsigned char param[2] = {0x10, 0x00};

	//if(enable){
	//	param[1] = 0x01;
	//}

	//makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

//zhq 
/*void systemToHal_DNVDetected(char enable){
	unsigned char param[2] = {0xF2, 0x00};

	if(enable){
		param[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}*/


void systemToHal_LightDetected(char enable){
	unsigned char param[2] = {0x11, 0x00};

	if(enable){
		param[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_DayOrNight(char night){
	unsigned char param[2] = {0x12, 0x00};

	if(night){
		param[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_SetExternalAmplifier(char exist){
	unsigned char param[2] = {0x13, 0x00};

	if(exist){
		param[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_SetLCDBrightness(unsigned char level){
	LOGD("systemToHal_SetLCDBrightness %d",level);
	unsigned char param[2] = {0x14, level};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_Set_LCDBrightness_Rank(unsigned char level)
{
	LOGD("systemToHal_Set_LCDBrightness_Rank %d",level);
	unsigned char param[3] = {0x14,0x04, level};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 3);
}
void systemToHal_KeyLedBrightness(unsigned char brightness){
	unsigned char param[2] = {0x15, brightness};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_WheelPanelSpecificFuncSwitch(char onOff){
	unsigned char param[2] = {0x16, 0x00};

	if(onOff){
		param[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_SetRadioRegion(unsigned char regionId){
	unsigned char param[2] = {0x17, regionId};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_FactorySetting(void){
	unsigned char param[2] = {0x18, 0x00};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_EnterDemoMode(char mode){
	unsigned char param[2] = {0x19, 0x00};

	if(mode){
		param[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_SetUserWheelPanelData(char onOff){
	unsigned char param[2] = {0x1A, 0x00};

	if(onOff){
		param[1] = 0x01;
		}
	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_LearnWheelPanelData(unsigned char key){
	unsigned char param[2] = {0x1B, key};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_CancalWheelPanelLearn(void){
	unsigned char param[2] = {0x1C, 0x00};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_ClearWheelPanelData(unsigned char key){
	unsigned char param[2] = {0x1D, key};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_SetDVDRegionCode(unsigned char region){
	unsigned char param[2] = {0x1E, region};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}
void systemToHal_CheckAuxVideo(void){
	unsigned char param[2] = {0x28, 0x00};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_ReceivedACCOnMsg(void){
	unsigned char param[2] = {0x30, 0x00};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_DealACCOffMsg(char finished){
	unsigned char param[2] = {0x31, 0x00};

	if(finished){
		param[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_NotifySIMPhoneStatus(char status)
{
	unsigned char param[2] = { 0x38, status};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_SetAndroidKeyMessageDeliver(int enable){
	unsigned char param[2] = {0x40, 0x00};

	if(enable){
		param[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void systemToHal_SetDebugKeyPanelType(unsigned char panelType){
	unsigned char param[2] = {0xF0, panelType};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}
void SystemModule_brightLCD(unsigned char buf)
{
	 switch(buf)
	 {
		case 0x00:
			appToSys_Menu_Off_MouseUp();
		break;
		case 0x01:
			appToSys_Menu_Dark_MouseUp();
		break;
		case 0x02:
			appToSys_Menu_Middle_MouseUp();
		break;
		case 0x03:
			appToSys_Menu_Light_MouseUp();
		break;
		case 0x04:
			appToSys_Menu_High_Light_MouseUp();
		break;
		default:break;
	 }
}

void systemToHal_AccOffDealFinished(unsigned char type){
	unsigned char param[2] = {0x2C, 0x00};

	param[1] = type;

	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}

void SystemTohal_CancelWheelStudy (){
	unsigned char buf[]={0x1c,0x00};
	makeAndSendMessageToHal(HAL_ID_SYSTEM,buf,2);
}

void SystemTohal_StudyWheelData(u8 ckey){
	unsigned char buf[]={0x1b,ckey};
	makeAndSendMessageToHal(HAL_ID_SYSTEM,buf,2);
}

void SystemTohal_ClearWheelData(u8 cKey)
{
    u8 buf[]={0x1d,cKey};
	makeAndSendMessageToHal(HAL_ID_SYSTEM,buf,2);
}

void systemToHal_SetTVOrIpol(u8 cKey)
{
    u8 buf[]={0x2D,cKey};
	LOGD("systemToHal_SetTVOrIpol--cKey:0x%x",cKey);
	makeAndSendMessageToHal(HAL_ID_SYSTEM,buf,2);
}

/*************************************************************************************/
void systemToHal_Global_Init(char param){
	unsigned char cmdParam[2] = {0x01, 0x00};

	if(param){
		cmdParam[1] = 0x01;
	}
	makeAndSendMessageToHal(HAL_ID_GLOBAL, cmdParam, 2);
}
void systemToHal_StandyState(u8 Param1,u8 Param2)
{
   unsigned char cmdParam[3] = {0x32, 0x00,0x00};
	cmdParam[1]=Param1;
	cmdParam[2]=Param2;
	LOGD(" SLEEP Param1:%d",Param1);
	makeAndSendMessageToHal(HAL_ID_SYSTEM, cmdParam, 2);
}

void systemToHal_SetDVROrTV(u8 cKey)
{
	//cKey = 0x02;

	u8 buf[]={0x2F,cKey};

	LOGD("systemToHal_SetTVOrDVR--cKey:0x%x",cKey);
	makeAndSendMessageToHal(HAL_ID_SYSTEM,buf,2);
}

void systemToHal_Notify_PingLoop_NewStructure(u8 param)
{
	u8 buf[]={0xF0,param};
	LOGD("systemToHal_Notify_PingLoop_NewStructure--param:0x%x",param);
	makeAndSendMessageToHal(HAL_ID_SYSTEM,buf,2);
}

void systemToHal_Notify_RemoteOnline_VoltageProtection(u8 param)
{
	u8 buf[]={0xF1,param};
	makeAndSendMessageToHal(HAL_ID_SYSTEM,buf,2);
}

void systemToHal_SetCarMode(u8* carMode,u8 len)
{
	u8 buf[256]={0x04,0x00};
	LOGD("systemToHal_SetCarMode:%s",carMode);
	memcpy(&buf[1],carMode,len);
	makeAndSendMessageToHal(HAL_ID_SYSTEM,buf,len+1);
}

void systemToHal_SetFanMode(char param)
{
	u8 szCmd[2] = {0x1F, 0x00};
	szCmd[1] = param;
	makeAndSendMessageToHal(HAL_ID_SYSTEM, szCmd, 2);
}

void systemToHal_InquireCurBrakeStatue(void)
{
	u8 szCmd[2] = {0x21, 0x00};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, szCmd, 2);
}

void systemToHal_SetVoltageProtection(E_VOLTAGE_PROTECTION e)
{
	u8 szCmd[2] = {0x22, 0x00};
	
	switch(e)
	{
	case eVoltageProtectionModeHigh:
		szCmd[1] = 108;
		break;
	case eVoltageProtectionModeMid:
		szCmd[1] = 90;
		break;
	case eVoltageProtectionModeLow:
		szCmd[1] = 80;
		break;
	}

	makeAndSendMessageToHal(HAL_ID_SYSTEM, szCmd, 2);
}

void systemToHal_SetDenoiseMode(u8 cmd)
{
	u8 szCmd[2] = {0x31, 0x00};
	szCmd[1] = cmd;
	makeAndSendMessageToHal(HAL_ID_SYSTEM, szCmd, 2);
}

void systemToHal_SetCPU_PerformanceMode(u8 cmd)
{
	u8 szCmd[2] = {0x50, 0x00};
	szCmd[1] = cmd;
	makeAndSendMessageToHal(HAL_ID_SYSTEM, szCmd, 2);
}

void systemToHal_BackcarVisionAngle(u8 param)
{
	u8 szCmd[2] = {0x60, 0x00};
	szCmd[1] = param;
	makeAndSendMessageToHal(HAL_ID_SYSTEM, szCmd, 2);
	LOGD("systemToHal_BackcarVisionAngle = %d",param);
}

//·¢ËÍµ½ video
void setToHalBackCarMode(u8 p)
{
	LOGD("[%s] p = [0x%x]", __FUNCTION__, p);

	u8 szMsg[2] = {0x2B, 0x00};

	szMsg[1] = p;

	makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN , szMsg, sizeof(szMsg));
}

//zhq add
void systemToHal_SetBackcarTriggerType(E_SETUP_BACKCAR_TRIGGER e)
{
	u8 szCmd[4] = {0xFE,0xA4, 0x01, 0x01};
	
	switch(e)
	{
	case eSetupBackcarTriggerLevel:
		szCmd[2] = 0x00;
		break;
	case eSetupBackcarTriggerProtocol:
		szCmd[3] = 0x00;
		break;
	case eSetupBackcarTriggerAutomatic:
		
		break;
	}
	LOGD("zhq send[%s] szCmd[0]=%x  szCmd[1]=%x  szCmd[2]=%d  szCmd[3]=%d",__FUNCTION__,szCmd[0],szCmd[1],szCmd[2],szCmd[3]);
	makeAndSendMessageToHal(HAL_ID_SYSTEM, szCmd, 4);
}

void systemToHal_NotifyMicUsingState(u8 p)
{
	u8 szMsg[2] = {0x51, 0x00};
	szMsg[1] = p;
	makeAndSendMessageToHal(HAL_ID_SYSTEM , szMsg, 2);
}


void systemToHal_SetNaviMixLow(u8 p)
{
	u8 szMsg[2] = {0x61, 0x00};
	szMsg[1] = p;
	makeAndSendMessageToHal(HAL_ID_SYSTEM , szMsg, 2);
}


//AMBIENT_LED20170117
void systemToHal_AboutAmbientLedMsg(u8 *p,u8 nLen)
{
	int pBufLen = nLen + 1;
	u8* pBuf = (u8*)malloc(pBufLen);
	if(pBuf == NULL)
		return;

	pBuf[0] = 0xFC;
	memcpy(pBuf + 1, p, nLen);

	makeAndSendMessageToHal(HAL_ID_SYSTEM, pBuf, pBufLen);
	free(pBuf);
	pBuf = NULL;
}

void systemToHal_SetScreenBrightnessValue(u8  buf){
	u8 param[3] = {0x14,0xFF, buf};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 3);
}

void setSystemToHal_DayOrNight(u8 night)
{
	unsigned char param[2] = {0x12, night};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, param, 2);
}
void systemToRadioHal_SetRadioArea(u8 param)
{
	u8 buf[2] = {0x40, param};
	makeAndSendMessageToHal(HAL_ID_RADIO, buf, 2);
}
void systemToHal_AutoAdjustmentSwitchOfScreenBrightness(u8 param)
{
	u8 buf[2] = {0x39, param};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, buf, 2);
}

void systemToHal_SetScreenBrightnessSpecificValue(u8 p)
{
	if(p < AMBIENT_SCREEN_BRIGHTNESS_MIN ||p> AMBIENT_SCREEN_BRIGHTNESS_MAX)
		return;
	u8 szMsg[2] = {0x62, 0x00};
	szMsg[1] = p;
	makeAndSendMessageToHal(HAL_ID_SYSTEM , szMsg, 2);
}
void systemToHal_SetScreenOnOrOff(u8 p)
{
       LOGD("[%s] --%x",__FUNCTION__,p);
       u8 szMsg[2] = {0x23, 0x00};
       szMsg[1] = p;
       makeAndSendMessageToHal(HAL_ID_SYSTEM , szMsg, 2);
}

void systemToHal_SetSelectionCarTypeOption(u8 param)
{
	param = param;
	u8 buf[3] = {0x03, 0x0D,param};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, buf, 3);
}