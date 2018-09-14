#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"

#include <flymoduleApi_internal.h>

void extcarToHal_Init(char param){
	unsigned char buf[2] = { 0x01, 0x00};

	if(param){
		buf[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_EXTCAR, buf, 2);
}

void extcarToHal_SetSpeedLockState(u8 state){
	unsigned char buf[] = { 0x90, 0x00, 0x60,state};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, buf, 4);
}

void extcarToHal_SetShiftLockState(u8 state){
	unsigned char buf[] = { 0x90, 0x00,  0x61,state};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, buf, 4);
}

void extcarToHal_SetPModeUnlockState(u8 state){
	unsigned char buf[] = { 0x90, 0x00,  0x62,state};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, buf, 4);
}

void extcarToHal_SetDPressUnlockState(u8 state){
	unsigned char buf[] = { 0x90, 0x00,  0x63,state};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, buf, 4);
}

void extcarToHal_SetFeedbackTone(u8 state){

}

void extcarToHal_SetLightSensitivity(u8 state){
	unsigned char buf[] = { 0x90, 0x00,  0x65,state};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, buf, 4);
}

void extcarToHal_SetLampAutoOFFTime(u8 state){

}

void extcarToHal_SetLightRuningState(u8 state){

}

void extcarToHal_SetCarLockState(u8 state){
	unsigned char buf[] = { 0x90, 0x00,  0x6f,state};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, buf, 4);
}

void extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(u8 state)
{
	unsigned char buf[] = { 0x90, 0x00,  0x70,state};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, buf, 4);
}

void extcarToHal_Carola_set_oilConsumeUnit(u8 p)
{
	u8 szMsg[] = {0x90, 0x00,  0x83, 0x00};
	szMsg[3] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

////////////////////////////////////////////////////////////////////////// golf
void extcarToHal_set_initHal()
{
	u8 szMsg[] = {0x81, 0x00, 0x00, 0x00};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, 4);
}
//ŒÝÊ»Ô±žšÖúÏµÍ³
void extcarToHal_set_driverAssistSystemdDriveMode(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x10, 0x21, 0x54, 0x01, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_driverAssistSystemLastSelectGap(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x11, 0x21, 0x52, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_driverAssistSystemGap(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x12, 0x21, 0x53, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//Ç°²¿žšÖúÏµÍ³
void extcarToHal_set_preAssistSystemActivation(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x13, 0x26, 0xCD, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_preAssistSystemWarning(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x14, 0x26, 0xD2, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_preAssistSystemGapWarning(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x15, 0x26, 0xD5, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//Æ£ÀÍŒÝÊ»Ê¶±ðÏµÍ³
void extcarToHal_set_fatigueReconizeSystemActivation(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x16, 0x28, 0x8D, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//ESCÏµÍ³
void extcarToHal_set_escSystemActivation(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x17, 0x29, 0x92, 0x02, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//ÂÖÌ¥
void extcarToHal_set_tireType(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x18, 0x21, 0xD7, 0x00, 0x00};
	//szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_carSpeedWarning(u8 p0, u8 p1)
{
	u8 szMsg[] = {0x81, 0x00, 0x19, 0x23, 0xD2, 0x00, 0x00, 0x00};
	szMsg[5] = p0;
	szMsg[6] = p1;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//µÆ¹â
void extcarToHal_set_lightSystemConnect(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x1A, 0x22, 0x54, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_lightSystemAuto(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x1B, 0x22, 0x5D, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_lightSystemDirection(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x1C, 0x22, 0x56, 0x00, 0x03, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_lightSystemDriveRule(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x1D, 0x22, 0x51, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_lightSystemGoHome(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x1E, 0x22, 0x52, 0x00, 0x01};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_lightSystemLeaveHome(u8 p)
{
	LOGD("dyb test leave home");
	u8 szMsg[] = {0x81, 0x00, 0x1F, 0x22, 0x53, 0x00, 0x01};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_lightSystemMeter(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x20, 0x22, 0x15, 0x01, 0x00, 0x00};
	szMsg[6] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_lightSystemDoor(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x21, 0x22, 0x18, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_lightSystemFeet(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x22, 0x22, 0x17, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

//³µŽ°
void extcarToHal_set_windowCtrl(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x23, 0x23, 0x50, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//³µÃÅËø
void extcarToHal_set_unlockDoor(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x24, 0x23, 0x51, 0x00, 0x00};
	szMsg[6] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_autoLockDoor(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x25, 0x23, 0x57, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//ºóÊÓŸµ
void extcarToHal_set_backMirror(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x26, 0x23, 0x90, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

//Óê¹Î
void extcarToHal_set_autoWiper(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x27, 0x23, 0x14, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_backWiperWhenBackCar(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x28, 0x23, 0x12, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//×€³µºÍµ÷³µ--µ¹³µÀ×ŽïÏµÍ³
void extcarToHal_set_backCarSystemActivation(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x29, 0x22, 0x98, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_backCarSystemPreAudio(u8 p0, u8 p1)
{
	u8 szMsg[] = {0x81, 0x00, 0x2A, 0x22, 0x90, 0x00, 0x00};
	szMsg[5] = p0;
	szMsg[6] = p1;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_backCarSystemRearAudio(u8 p0, u8 p1)
{
	u8 szMsg[] = {0x81, 0x00, 0x2B, 0x22, 0x91, 0x00, 0x00};
	szMsg[5] = p0;
	szMsg[6] = p1;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//¶à¹ŠÄÜÏÔÊŸ
void extcarToHal_set_functionDisplay(u8 *p, int nLen)
{
	u8 szMsg[10] = {0};
	szMsg[0] = 0x81;
	szMsg[1] = 0x00;
	szMsg[2] = 0x2C;
	szMsg[3] = *(p + 0);
	szMsg[4] = *(p + 1);
	szMsg[5] = *(p + 2);
	szMsg[6] = *(p + 3);
	szMsg[7] = *(p + 4);
	szMsg[8] = *(p + 5);
	szMsg[9] = *(p + 6);
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_cozyEconomyTipDisplay(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x2D, 0x23, 0xDB, 0x00, 0x00, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//»ÖžŽÊýŸÝ
void extcarToHal_set_recoveryDriveDataFromStart(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x2E, 0x23, 0xD1, 0x02};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_recoveryDriveDataFromLongTime(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x2F, 0x23, 0xD1, 0x04};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//µ¥Î»ÉèÖÃ
void extcarToHal_set_degreeUnit(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x30, 0x24, 0xD1, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_volumeUnit(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x31, 0x24, 0xD4, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_oilConsumeUnit(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x32, 0x24, 0xD6, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_distanceUnit(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x80,0x00};
	szMsg[3] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_speedUnit(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x81,0x00};
	szMsg[3] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_tireCompressUnit(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x33, 0x24, 0xD3, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//Ê±Œä
void extcarToHal_set_systemTime(u8 p0, u8 p1)
{
	u8 szMsg[] = {0x81, 0x00, 0x34, 0x24, 0x51, 0x00, 0x00, 0x00};
	szMsg[5] = p0;
	szMsg[6] = p1;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_systemDate(u8 p0, u8 p1, u8 p2)
{
	u8 szMsg[] = {0x81, 0x00, 0x35, 0x24, 0x50, 0x00, 0x00, 0x00};
	szMsg[5] = p0;
	szMsg[6] = p1;
	szMsg[7] = p2;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void extcarToHal_set_SystemDateFormat(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x36, 0x24, 0xD5, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//žŽÎ»³ö³§ÉèÖÃ
void extcarToHal_set_recoverySetting(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x37, 0x00};
	szMsg[3] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//ÓïÑÔ
void extcarToHal_set_languageSetting(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x38, 0x24, 0xD0, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//À×ŽïÉùÒô¿ª¹Ø
void extcarToHal_set_radarAudioDoor(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x39, 0x22, 0x94, 0x00, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
	//LOGD("extcarToHal_set_radarAudioDoor, SIZEOF SZMSG = [%d]", sizeof((char*)szMsg));
}
//¿Õµ÷
void extcarToHal_set_airCtrl(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x3A, 0x20, 0x4D, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//À¶ÑÀ
void extcarToHal_set_btCtrl(u8 *p, int nLen)
{
	//dyb_log_output("extcar ", "writebtdatatocarscreen", (char*)p, nLen, printLog, TAG);
	LOGD("writebtdatatocarscreen, nLen = [%d],", nLen);

	makeAndSendMessageToHal(HAL_ID_EXTCAR, p, nLen);
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void extcarToHal_set_systemPowerMode(u8 *p, int nLen)//¿ª¹Ø»úÄ£Êœ£¬0-¡·Ô­ÐÝÃßÄ£Êœ£¬1-¡·LPCÀ­žŽÎ»¶Ïµç
{
	makeAndSendMessageToHal(HAL_ID_EXTCAR, p, nLen);
}



void extcarToHal_set_DrivingMode(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x70,0x00};
	szMsg[3] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_Personalization(u8 p0,u8 p1,u8 p2,u8 p3,u8 p4,u8 p5,u8 p6)
{
	LOGD("[%s] p0:%d,p1:%d,p2:%d,p3:%d,p4:%d,p5:%d,p6:%d",__FUNCTION__,p0,p1,p2,p3,p4,p5,p6);
	u8 szMsg[10] = {0x81, 0x00, 0x71,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	szMsg[3] = p0;
	szMsg[4] = p1;
	szMsg[5] = p2;
	szMsg[6] = p3;
	szMsg[7] = p4;
	szMsg[8] = p5;
	szMsg[9] = p6;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void extcarToHal_set_ModeOpenOrClose(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x72,0x00};
	szMsg[3] = p;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

/**********************NEW STRUCT***********************************/
void extcarToHal_Public_Send_Message(u8 *param, int len)
{
	u8 szMsg[256];
	memset(szMsg,0,sizeof(szMsg));
	szMsg[0] = 0xf0;

	if(len > 255)
		len = 255;
	
	memcpy(szMsg+1,param,len);
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, len+1);
}

void ToHal_Public_SetCarsParam(u8 *param, int len)
{
	u8 szMsg[256];
	memset(szMsg,0,sizeof(szMsg));
	szMsg[0] = 0x03;

	if(len > 255)
		len = 255;
	
	memcpy(szMsg+1,param,len);
	extcarToHal_Public_Send_Message(szMsg,len + 1);
}


void setPublicElectronicBoosterMode (u8 param)
{
	u8 szMsg[] = {0x00, 0x00,0x00};
	szMsg[2] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicRemoteControlLocFeedback (u8 param)
{
	u8 szMsg[] = {0x00, 0x01,0x00};
	szMsg[2] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicShutDownTheUnlock (u8 param)
{
	u8 szMsg[] = {0x00, 0x02,0x00};
	szMsg[2] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionAfterLocking (u8 param)
{
	u8 szMsg[] = {0x00, 0x03,0x00};
	szMsg[2] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionSpeedAlarmSwitch(u8 param)
{
	u8 szMsg[] = {0x00, 0x04, 0x00, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionSpeedAlarmValue(u8 *param,u32 len)
{
	u8 szMsg[11] = {0x00};
	szMsg[0] = 0x00;
	szMsg[1] = 0x04;
	szMsg[2] = 0x01;

	if(len > 8)
		len = 8;
	memcpy(&szMsg[3],param,len);
	
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionSetSpeedAlarmIncOrDec(u8 param)
{
	u8 szMsg[] = {0x00, 0x04, 0x02, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionTrunkOpeningDegree(u8 *param,u32 len)
{
	u8 szMsg[7] = {0x00};
	szMsg[0] = 0x00;
	szMsg[1] = 0x05;
	szMsg[2] = 0x00;

	if(len > 4)
		len = 4;
	memcpy(&szMsg[3],param,len);
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionTrunkOpeningDegreeIncAndDec(u8 param)
{
	u8 szMsg[] = {0x00, 0x05, 0x01, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}


void setPublicPositionWelcomeLampSwitch(u8 param)
{
	u8 szMsg[] = {0x00, 0x06, 0x00, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionWelcomeLampTime(u8 *param,u32 len)//time unit:s Close:0 long_Open:0xFFFA
{
	u8 szMsg[11] = {0x00};
	szMsg[0] = 0x00;
	szMsg[1] = 0x06;
	szMsg[2] = 0x01;

	if(len > 8)
		len = 8;
	memcpy(&szMsg[3],param,len);
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}


void setPublicPositionLampCompanyHomeSwitch(u8 param)
{
	u8 szMsg[] = {0x00, 0x07, 0x00, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionLampCompanyHomeTime(u8 *param,u32 len)//time unit:s Close:0 long_Open:0xFFFA
{
	u8 szMsg[11] = {0x00};
	szMsg[0] = 0x00;
	szMsg[1] = 0x07;
	szMsg[2] = 0x01;

	if(len > 8)
		len = 8;
	memcpy(&szMsg[3],param,len);
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}


void setPublicPositionVehicleFindingFeedback(u8 param)//0x01:lightAndWhistles 0x02:Only Whistles
{
	u8 szMsg[] = {0x00, 0x08, 0x00, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionDrivingAutomaticLatchSwitchAndDrivingSpeedSwitch(u8 param)
{
	u8 szMsg[] = {0x00, 0x09, 0x00, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionDrivingAutomaticLatchSwitchAndDrivingSpeedValue(u8 *param,u32 len)//time unit:s Close:0 long_Open:0xFFFA
{
	u8 szMsg[9] = {0x00};
	szMsg[0] = 0x00;
	szMsg[1] = 0x09;
	szMsg[2] = 0x01;

	if(len > 6)
		len = 6;
	memcpy(&szMsg[3],param,len);
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionDrivingAutomaticLatchSwitchAndDrivingSpeedIncAndDec(u8 param)
{
	u8 szMsg[] = {0x00, 0x09, 0x02, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}


void setPublicPositionFlameoutAutomaticLatchSwitch(u8 param)
{
	u8 szMsg[] = {0x00, 0x0A, 0x00, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionKeyUnlockSet(u8 param)
{
	u8 szMsg[] = {0x00, 0x0B, 0x00, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionKeyLessUnlockSet(u8 param)
{
	u8 szMsg[] = {0x00, 0x0C, 0x00, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionAcAutomaticFlowSet(u8 param)
{
	u8 szMsg[] = {0x00, 0x0D, 0x00, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPosition_F_B_DefrostAndLog_LinkageSwitch(u8 param)
{
	u8 szMsg[] = {0x00, 0x0D, 0x01, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicPositionExteriorRearviewMirrorAutomaticOpenSwitch(u8 param)
{
	u8 szMsg[] = {0x00, 0x0E, 0x00, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicAuxscreenLanguage(u8 param)
{
	u8 szMsg[] = {0x00, 0x10, 0x00, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}


void setPublicTrunkOpenLevelBar (u8 min,u8 max,u8 step,u8 param)
{
	u8 szMsg[7] = {0};
	szMsg[0] = 0x00;
	szMsg[1] = 0x05;
	szMsg[2] = 0x00;
	szMsg[3] = min;
	szMsg[4] = max;
	szMsg[5] = step;
	szMsg[6] = (param + min);
	ToHal_Public_SetCarsParam(szMsg,0x07);
}

void setPublicFord_DistanceUnit_HighModel(u8 param)
{
	u8 szMsg[] = {0x00, 0x11, 0x05, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicFord_TCU_FinalActivateStatus(u8 param)
{
	u8 szMsg[] = {0x00, 0x13, 0x05, 0x00};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicFord_AmbientLedColor_HighModel(u8 param)
{
	u8 szMsg[] = {0x00, 0x14, 0x05, 0xFF};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setPublicFord_AmbientLedBrightness_HighModel(u8 *param)
{
	u8 szMsg[] = {0x00, 0x14, 0x0A, 0xFF,0xFF, 0xFF,0xFF};
	memcpy(&szMsg[3],param,4);
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}


void setSyncMessageToHal(u8 *p ,int len)
{
	u8 buf[10] = {0};
	buf[0] = 0x03;
	buf[1] = 0x00;
	buf[2] = 0x0F;
	if(len > 7)
		len = 7;
	memcpy(buf+3,p,len);
	extcarToHal_Public_Send_Message(buf,len +3);
}

void setPublicFord_Parking_Assist_Mode(u8 param)
{
	u8 szMsg[] = {0x00, 0x15, 0x00, 0xFF};
	szMsg[3] = param;
	ToHal_Public_SetCarsParam(szMsg,sizeof(szMsg));
}

void setSkylightControlMessageToHal(u8 param)
{
	u8 szMsg[] = {0x13, 0x00, 0x00};
	szMsg[2] = param;
	ToHal_Public_SetBasicCarsParam(szMsg,sizeof(szMsg));
}
void ToHal_Public_SetBasicCarsParam(u8 *param, int len)
{
	u8 szMsg[256];
	memset(szMsg,0,sizeof(szMsg));
	szMsg[0] = 0x01;

	if(len > 255)
		len = 255;
	
	memcpy(szMsg+1,param,len);
	extcarToHal_Public_Send_Message(szMsg,len + 1);
}

