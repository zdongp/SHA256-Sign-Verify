
#include <stdio.h>
#include <stdlib.h>

#include "global.h"

#include "param.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "moduleParamResponse.h"
#include "moduleID.h"
#include "halResponseFunction.h"

//跳到指定页
void blcdToModule_NotifySystem_JumpPage(u16 nPageId){
     u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&nPageId,2);
     makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_SYSTEM,buf,3);
}
//跳到前一页
void blcdToModule_NotifySystem_JumpPrePage(void){
     u8 buf[] = {0x83,0x00};
     makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_SYSTEM,buf,3);
}

void Set_DVD_PlayControl(char command)	
{

	unsigned char buff[]={0x10,0x00};  //
	buff[1] = command;
	makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_DVD,buff,2);
}

void Set_CDC_PlayControl(char command)	
{
	unsigned char buff[]={0x03,0x00};
	buff[1] = command;
	makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_DVD,buff,2);
}

void Set_TV_PlayControl(char command){
	//unsigned char buff[]={0x03,0x00};
	//buff[1] = command;
	//makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_DVD,buff,2);
}
void Set_AUX_PlayControl(char command){
	//unsigned char buff[]={0x03,0x00};
	//buff[1] = command;
	//makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_DVD,buff,2);

}

//给模块发送设置的BLCD模式
void Set_Mode(unsigned char mode)
{
	unsigned char buff[]={0x01,0x00};
	buff[1]=mode;
	
	//edit by lijiewen 2012.8.20
	switch (mode)
	{
	case emSetBlcdMode_DVD:
		makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_DVD,buff,2);
		moduleToBlcd_FromBlcd_SetSoundVideoChannel(CHANNEL_DVD_CTRL);
		break;
	case emSetBlcdMode_CDC_TV:
		makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_TV,buff,2);
		moduleToBlcd_FromBlcd_SetSoundVideoChannel(CHANNEL_TV_CTRL);
		break;
	case emSetBlcdMode_AUX:
		makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_AUX,buff,2);
		moduleToBlcd_FromBlcd_SetSoundVideoChannel(CHANNEL_AUX_CTRL);
		break;
	case emSetBlcdMode_Radio:
		makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_RADIO,buff,2);
		moduleToBlcd_FromBlcd_SetSoundVideoChannel(CHANNEL_RADIO);
		break;
	case emBlcdMode_CDC:
		//makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_TV,buff,2);
		moduleToBlcd_FromBlcd_SetSoundVideoChannel(CHANNEL_CDC_CTRL);
		break;
	default:
		makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_DVD,buff,2);
		moduleToBlcd_FromBlcd_SetSoundVideoChannel(CHANNEL_DVD_CTRL);
		break;
	}

			
		
	//buff[0] = Module_CDC;
	//MakeAndSendToModule(buff,3);
	//buff[0] = Module_TV;
	//MakeAndSendToModule(buff,3);
	//buff[0] = Module_RADIO;
	//MakeAndSendToModule(buff,3);
	//buff[0] = Module_AUX;
	//MakeAndSendToModule(buff,3);
}

void Set_SaveDataToRestart()
{
    saveParameter();
}

void Set_RestoreToFactoryDefaults()
{
	SetDefaultParam();
	saveParameter();
}


/*
void SetDefaultParam(){
	pLocalParam->setMode=emSetBlcdMode_DVD;	
	pLocalParam->audioMode=SoundMode_IPOD;

}
*/

