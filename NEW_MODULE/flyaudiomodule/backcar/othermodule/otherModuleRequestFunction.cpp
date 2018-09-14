#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"

void backCarToModule_NotifySystem_SwitchModule(void)
{
	u8 buf[] = {0x81, MODULE_ID_BACK};
    makeAndSendMessageToModule(MODULE_ID_BACK, MODULE_ID_SYSTEM,buf,2);
}

//跳到指定页
void backCarToModule_NotifySystem_JumpPage(u16 nPageId)
{
     u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&nPageId,2);
     makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_SYSTEM,buf,3);
}

//跳到前一页
void backCarToModule_NotifySystem_JumpPrePage(void)
{
     u8 buf[] = {0x83,0x00};
     makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_SYSTEM,buf,2);
}

void backCarToModule_NotifyOSD(u8 m_bBackState)
{
//	u8 buf[] = {0X00,0x01};
//	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_OSD,buf,2);
}

void backCarToModule_NotifySystem_AlarmBackCar(u8 IsBackCar)
{
	 u8 buf[] = {0x00, 0x00};
	 if (IsBackCar)
		 buf[1] = 0x01;
     makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_SYSTEM,buf,2);
}

void backCarToModule_NotifySystem_ActualReversingState(u8 p)
{
	u8 buf[2] = {0x01, 0x00};
	buf[1] = p;
 	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_SYSTEM,buf,2);
}


void backCarToModule_NotifyBT_HandUp_MouseUp(void){
	u8 buf[] = {0x79,0x00};
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_BT,buf,2);
}

void backCarToModule_NotifyBT_CallIn_MouseUp(void){
	u8 buf[] = {0x80,0x00};
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_BT,buf,2);
}

void backCarToModule_NotifySystem_Out_BackCar_RedOsd(){
	u8 buf[] = {0xf8,0x00};
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_SYSTEM,buf,2);
}

void backCarToModule_NotifyAudioVideo_aboutBackCarVideoSet(u8 param){
	unsigned char buf[] = {0x11, param};
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_AUDIOVIDEO,buf,2);
}



void backCarToModule_NotifyExtcar_Prado_ScreenCoordinates(u8* param ,int paramLen)
{
	u8 buf[5] = {0x83,0x00,0x00,0x00,0x00};
	buf[1] = param[0];
	buf[2] = param[1];
	buf[3] = param[2];
	buf[4] = param[3];
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_EXTCAR,buf,sizeof(buf));
}


void backcarToModule_NotifyOSD_aboutT123_VideoOSDSetButton(u8 param,u8 status)
{
	u8 buf[] = {0X20,0x00,0x00};
	buf[1]=param;
	buf[2]=status;
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_OSD,buf,3);
}

void backcarToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(u8 param,u8 status)
{
	u8 buf[] = {0X21,0x00,0x00};

	buf[1]=param;
	buf[2]=status;
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_OSD,buf,3);
}

void backcarToModule_NotifySystem_VisionAngle(u8 param)
{
	u8 buf[2] = {0x60,0x00};
	buf[1] = param;
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_SYSTEM,buf,sizeof(buf));
}

void backCarToModule_NotifyOSD_aboutT123_BackCarWarningsDisplay(u8 State)
{
	u8 buf[] = {0X28,State};
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_OSD,buf,2);
}

void backCarToModule_NotifyOSD_aboutT123_BackCarVideoRefLineDisplay(u8 param)
{
	unsigned char buf[] = {0x2A, param};
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_OSD,buf,2);
}

void backCarToModule_NotifyOSD_aboutT123_ChangePage_OSDDispalying(u8 u8_Module,u16 u16_LewPage,u16 u16_EnterPage,u8 u8_Param)
{
	if(u16_EnterPage == u16_LewPage)
		return;

	unsigned char buf[] = {0xE3,0x00,0x00,0x00,0x00,0x00};
	memcpy(&buf[1],&u16_LewPage,2);
	memcpy(&buf[3],&u16_EnterPage,2);
	buf[5] = u8_Param;
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,u8_Module,buf,6);

}

void backCarToModule_NotifySystem_BackCarVideoLineType(u8 param)
{
	LOGD("BackCarVideoLineType: %x",param);
	unsigned char buf[] = {0x70, param};
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_SYSTEM,buf,2);
}

void backCarToModule_NotifyExternalctrl_VoiceSwitchCtrl(u8 p){
	u8 buf[] = {0x00,p};
	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_EXTERNALCTRL,buf,2);
}

void backCarToModule_NotifyExtcar_SetVoiceSize(u8 p)
{
	u8 buf[] = {0xf0,0x00,0x12,0x05,p};
    	makeAndSendMessageToModule(MODULE_ID_BACK,MODULE_ID_EXTCAR,buf,5);
}
 void setToExtcarSetVoiceSizeMessage(u8 param)
 {
 	switch(param)
 	{
 		case 0x00:
			backCarToModule_NotifyExtcar_SetVoiceSize(0x01);
			break;
		case 0x01:
			backCarToModule_NotifyExtcar_SetVoiceSize(0x00);
			break;
		default:
			LOGD("[%s] param:%x",__FUNCTION__,param);
			break;
 	}
 }