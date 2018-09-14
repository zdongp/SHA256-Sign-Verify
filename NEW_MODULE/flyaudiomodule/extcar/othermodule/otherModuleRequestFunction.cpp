#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"


void extcarToModule_NotifySystem_jumpPage(u16 pageId){
	u8 buf[] = {0x82, 0x00, 0x00};
	
	memcpy(&buf[1], &pageId, 2);
	
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_SYSTEM, buf, 3);
}

void extcarToModule_NotifySystem_jumpPrePage(void){
	u8 buf[] = {0x83, 0x00};
	
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_SYSTEM, buf, 2);
}

void exterToFOCUS_sync_FromHal(u8 *param, u8 len){
	u8 buf[300];
	memset(buf,0x00,300);
	buf[0] = 0x01;
	if(len <= 300)
	{
	    memcpy(&buf[1],param,len);
	}
	else
	{
	    memcpy(&buf[1],param,300);
	}
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_SYNC, buf, len + 1);
}

void exterToCenter_NoticeAlarmTip(u8 param)
{
	LOGD("[%s] p = [%d]", "430", param);
	
	u8 cmd[2] = {0x12, 0x00};
	cmd[1] = param;
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_CENTER, cmd, 2);
}

////////////////////////////////////////DA ZHONG//////////////////////////////////////
void exterToAirCondition(u8 *param, u8 len)
{
	u8 pMsg[256] = {0};
	pMsg[0] = 0x80;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AC, pMsg, len+1);
}

void exterToAirData_aboutToyotaCamry(u8 *param, u8 len)
{
	u8 pMsg[256] = {0};
	pMsg[0] = 0x90;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AC, pMsg, len+1);

}

void exterToKey_Da_Zhong_Steer_Key(u8 key)
{
	u8 cmd[2] = {0x80, 0x00};
	cmd[1] = key;
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_KEY, cmd, 2);
}

void exterToRadar(u8 pos, u32 distance)
{
	u8 cmd[7] = {0x00};
	cmd[0] = 0x80;
	cmd[1] = 0x00;
	cmd[2] = pos;
	memcpy(cmd + 3, &distance, 4);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_SYSTEM, cmd, 7);
}

void exterToRadar(u8 param)
{
	u8 cmd[3] = {0x00};
	cmd[0] = 0x80;
	cmd[1] = 0x01;
	cmd[2] = param;
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_SYSTEM, cmd, 3);
	//makeAndSendMessageToModule(unsigned char sendModuleId, unsigned char arrivedModuleId, unsigned char * buffer, int len)
}
//////////////////////////////////////DA ZHONG ////////////////////////////////////////

void exterPradoRadarKeySwitchToSystem(u8 param)
{
	u8 buf[] = {0xb1,0x00,0x00};
	buf[2] = param;
    makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_SYSTEM,buf,3);
}

void exterPradoRadarUISwitchToSystem(u8 param)
{
	u8 buf[] = {0xb1,0x01,0x00};
	buf[2] = param;
    makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_SYSTEM,buf,3);
}

void exterToAC_fks(u8 *param, int len)
{
	u8 pMsg[256] = {0};
	pMsg[0] = 0x50;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AC, pMsg, len+1);
	
}

void exterToAC_SiYu(u8 *param, int len)
{
	u8 pMsg[256] = {0};
	pMsg[0] = 0xB0;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AC, pMsg, len+1);
}



void exterToAC_byd(u8 *param, int len)
{
	u8 pMsg[256] = {0};
	pMsg[0] = 0xC0;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AC, pMsg, len+1);
	
}

void exterToAC_golf(u8 *param, int len)
{
	u8 pMsg[128] = {0};
	pMsg[0] = 0x81;
	pMsg[1] = 0x00;
	memcpy(pMsg + 2, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AC, pMsg, len + 2);
}

void exterToAC_golf_ctrl(u8 param)
{
	u8 pMsg[3] = {0};
	pMsg[0] = 0x81;
	pMsg[1] = 0x01;
	pMsg[2] = param;
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AC, pMsg, 3);
}

void exterToAC_golf_acState(u8 param)
{
	u8 pMsg[3] = {0};
	pMsg[0] = 0x81;
	pMsg[1] = 0x02;
	pMsg[2] = param;
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AC, pMsg, 3);
}


void exterToAC_HondaCRV(u8 *param, int len)
{
	u8 pMsg[256] = {0};
	pMsg[0] = 0xd0;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AC, pMsg, len+1);
}

void extcarToSystem_about_CarInforVoicePrompt(bool state)
{
	u8 buf[] = {0x00, state};
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_SYSTEM, buf, 2);
}


void exterToBT_golf(u8 *param, int len)
{
	u8 pMsg[64]= {0};
	pMsg[0] = 0x81;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_BT, pMsg, len + 1);

}

void exterToGPS_golf(u8 *param, int len)
{
	u8 pMsg[4] = {0};
	pMsg[0] = 0x81;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_GPS, pMsg, len + 1);
}


void exterToAuxScreen_aboutMp3NameAndGpsRoadName_IsDisplaying(u8 state)
{
    LOGD("state:%d",state);
	u8 buf[] = {0x00, state};
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AUXSCREEN, buf, 2);
}
 
void extcarToAudioVideo(u8 *p, int len)
{
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AUDIOVIDEO, p, len);
}

void exterToSystem_aboutBatteryVoltageInfo(int nParam)
{
	u8 uTempBattery_Value = (u8)(nParam/100);
	LOGD("++++++uTempBattery_Value:%d",uTempBattery_Value);
	
	u8 buf[] = {0x60, uTempBattery_Value};
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_SYSTEM, buf, 2);
}

void mistraCarToAirCondition(u8 *param, u8 len)
{
	u8 pMsg[256] = {0};
	pMsg[0] = 0xD1;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AC, pMsg, len+1);
}
void ExtcarToModule_Ac_PublicAcInfo(u8 *param,u8 len)
{
	u8 pMsg[128] = {0};
	pMsg[0] = 0xff;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_AC, pMsg, len + 1);
}
void ExtcarToModule_Tpms_PublicTpmsInfo(u8 *param,u8 len)
{
	u8 pMsg[128] = {0};
	pMsg[0] = 0xff;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_TPMS, pMsg, len + 1);
}

void ExtcarToModule_system_PublicVehicleSettings(u8 *param,u8 len)
{
	u8 pMsg[128] = {0};
	pMsg[0] = 0xf0;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_SYSTEM, pMsg, len + 1);
}

void ExtcarToModule_BackCar_VideoSet(u8 *param,u8 len)
{
	u8 pMsg[128] = {0};
	pMsg[0] = 0xf0;
	memcpy(pMsg + 1, param, len);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_BACK, pMsg, len + 1);
}

void extcarToOtherModule_System_FrontCameraApp(u8 p)
{
	u8 szMsg[] = {0x02, 0x00};
	szMsg[1] = p;
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,  MODULE_ID_SYSTEM,  szMsg, sizeof(szMsg));
}