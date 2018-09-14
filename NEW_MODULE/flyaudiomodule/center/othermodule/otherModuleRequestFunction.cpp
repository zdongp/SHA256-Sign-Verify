#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"


void centerToModule_NotifySystem_jumpPage(u16 pageId){
	u8 buf[] = {0x82, 0x00, 0x00};

	memcpy(&buf[1], &pageId, 2);

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 3);
}

void centerToModule_NotifySystem_jumpPrePage(void){
	u8 buf[] = {0x83, 0x00};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_Hardware_JumpPrePage(void){
	u8 buf[] = {0x84, 0x00};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_EnterThreePartyApp(void){
	u8 buf[] = {0x85, 0x00};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_EnterHomePage(void){
	u8 buf[] = {0x86, 0x00};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_EnterGpsPage(void){
	u8 buf[] =  {0x87, 0x00};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_EnterNonHomePage(void){
	u8 buf[] = {0x88, 0x00};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_ReturnToPage(unsigned char *pageid,int len){
	u8 buf[len+1];
	buf[0] = 0x89;
	memcpy(&buf[1], pageid, len);
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, len+1);
}
void centerToModule_NotifySystem_DisplayBarCode()
{
   u8 buf[]={0x90,0x00};
   makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf,2);
}

void centerToModule_NotifySystem_DebugPanelType(unsigned char panelType){
	u8 buf[] = {0xF0, panelType};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_Brightness(unsigned char brightness){
	u8 buf[] = {0xF2, brightness};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);

}

void centerToModule_NotifySystem_ScreenOff_Brightness(unsigned char brightness)
{
	u8 buf[] = {0xF3, brightness};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);

}

void centerToModule_NotifyBT_SIMPhoneStatus(char status)
{
	u8 buf[] = { 0x01, status};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_BT, buf, 2);
}

void centerToModule_NotifySystem_SIMPhoneStatus(char status)
{
	u8 buf[] = { 0x38, status};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_BrightnessBlackPageClick(void){
	u8 buf[] = {0x00, 0x01};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}


void centerToModule_NotifyOSD_SetOSDHidden(void){
	u8 buf[] = {0x0F, 0x00};
	//u8 buf[] = {0x01, 0x00};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_OSD, buf, 2);
}

void centerToModule_NotifyAudiovideo_GpsSoundState(unsigned char state){
	u8 buf[] = {0x01, state};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_AUDIOVIDEO, buf, 2);
}

void centerToModule_NotifyAudiovideo_AppRequestMixedVoice(unsigned char mixed)
{
	u8 buf[] = {0x70, mixed};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_AUDIOVIDEO, buf, 2);
}

void centerToModule_NotifyAudiovideo_SimulationOfGPS_Process_RequestMixedVoice(unsigned char mixed)
{
	u8 buf[] = {0x71, mixed};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_AUDIOVIDEO, buf, 2);

}



//2012-07-16
void centerToModule_NotifyBackEnterAllscreen(void)
{
    u8 buf[] = {0x91, 0x00};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_BACK, buf, 2);
}
void centerToModule_NotifyBackExitAllscreen(void)
{
  u8 buf[] = {0x92, 0x00};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_BACK, buf, 2);
}
void centerToModule_NotifyBackEnterFrontscreen(void)
{
    u8 buf[] = {0x93, 0x00};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_BACK, buf, 2);
}
void centerToModule_NotifyBackEnterBehindscreen(void)
{
    u8 buf[] = {0x94, 0x00};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_BACK, buf, 2);
}
void centerToModule_NotifyBackEnterRigthscreen(void)
{
    u8 buf[] = {0x95, 0x00};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_BACK, buf, 2);
}
void centerToModule_NotifyBackEnterLeftscreen(void)
{
    u8 buf[] = {0x96, 0x00};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_BACK, buf, 2);
}
void centerToModule_NotifyBackOnlyEnterscreen(void)
{
    u8 buf[] = {0x97, 0x00};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_BACK, buf, 2);
}
void centerToModule_NotifyBackExitscreenPage(void)
{
    u8 buf[] = {0x98, 0x00};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_BACK, buf, 2);
}




void centerToModule_NotifyAudiovideo_AndroidIntentAction_MediaPlay_States(u8 state)
{
	u8 buf[] = {0x80, state};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_AUDIOVIDEO, buf, 2);
}

void centerToModule_NotifyOtherModule_FromAndroid_Power_OnOrOff_0s(u8 state)
{
	u8 ModuleBuf[] = {MODULE_ID_DVD,MODULE_ID_BT,MODULE_ID_SERVICE,MODULE_ID_SYNC,MODULE_ID_DVR,MODULE_ID_RADIO,MODULE_ID_EXTERNALCTRL};
	u32 i = 0;
	for(i=0;i < (u32)dim(ModuleBuf);i++)
	{
       u8 buf[2] = {0x00, state};
		makeAndSendMessageToModule(MODULE_ID_CENTER,ModuleBuf[i],buf,2);
	}
}



void centerToModule_NotifyService_FromAndroid_Acc_OnOrOff_30s(u8 state)
{
	u8 buf[] = {0x3c, state};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SERVICE, buf, 2);
}

void centerToModule_NotifyService_FromAndroid_FastToSwitichMachine_60s(u8 state)
{
	u8 buf[] = {0x3d, state};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SERVICE, buf, 2);
}

void centerToModule_NotifyFlyRemoteOnline_FromAndroid_FastToSwitichMachine_60s(u8 state)
{
	u8 buf[] = {0x3d, state};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_REMOTEONLINE, buf, 2);
}

void centerToModule_NotifyService_FromAndroid_PingLoop(u8 state)
{
	u8 buf[] = {0x02, state};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifyService_FromAndroid_15DaysReset(u8 *param,int len)
{
	u8 buf[] = {0x00,0x000,0x00,0x00,0x00};
    buf[0] = (u8)0xe0;
	buf[1] = param[0];
	buf[2] = param[1];
	buf[3] = param[2];
	buf[4] = param[3];
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SERVICE, buf, 5);
	LOGD("centerToModule_NotifyService_FromAndroid_15DaysReset");
}

void centerToModule_NotifyAudiovideo_SetThirdChannel(){
	u8 buf[] = {0x4d, 0x00};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_AUDIOVIDEO, buf, 2);
}

void centerToModule_NotifySystem_SysTimeFormat(u8 p)
{
	u8 buf[] = {0x03, p};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifyExtcar_FordTCU_Request(u8 p)
{
	u8 buf[] = {0x00, p};
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_EXTCAR, buf, 2);
}