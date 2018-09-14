#include <stdio.h>
#include <stdlib.h>
#include <commonFunc.h>


#include "global.h"
#include "param.h"
#include "otherModuleResponseFunction.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"

static bool accstatus = true;

void moduleToExternalCtrl_AnalyseModuleCommand_key(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x00:
			FromKey_GetPanelKey(p[1]);
			break;
		case 0x01:
			if(p[1] == 0x00)
			{
				ExternalctrlModule_IsJumpPrePage();
				externalctrlToModule_NotifySystem_jumpPage(PAGE_SPEECH_APP_MEDIA);
				externalCtrlToSpeechApp_RequestCtrlCmd(0x01);
			}
			else if(p[1] == 0x01)
			{
				externalCtrlToSpeechApp_RequestCtrlCmd(0x00);
			}
			break;
		default:break;
	}
}

void FromKey_GetPanelKey(u8 p)
{
	LOGD("[%s] key:%x",__FUNCTION__,p);
	switch(p)
	{
		case KEY_AV:
			externalctrlToModule_NotifySystem_SwitchModule();
			break;
		case KEY_SEEK_INC:
		case KEY_TUNE_INC:
			externalCtrlToApp_selectedSongs(0x01);
			break;
		case KEY_SEEK_DEC:
		case KEY_TUNE_DEC:
			externalCtrlToApp_selectedSongs(0x00);
			break;
		default:break;
	}
}

void ExternalctrlModule_IsJumpPrePage(void)
{
	short curSound = 0;
	unsigned char soundLen;
	getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&curSound,(u8 *)&soundLen);
	if(curSound != CHANNEL_SPEECH_MEDIA_CTRL)
	{
		pLocalParam->bIsAutoJumpPrePage = true;
	}
}

void moduleToExternalCtrl_AnalyseModuleCommand_Bt(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x00:
			{
				setTagExternalCtrlToApp_CtrlVoiceSwitch(p[1]);
			}
			break;
		default:break;
	}
}

void moduleToExternalCtrl_AnalyseModuleCommand_backcar(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x00:
			{
				setTagExternalCtrlToApp_CtrlVoiceSwitch(p[1]);
			}
			break;
		default:break;
	}
}

void moduleToExternalCtrl_AnalyseModuleCommand_system(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x00:
			{
				externalCtrlToSpeechApp_RequestCtrlCmd(0x00);
			}
			break;
		case 0x01:
			{
				setTagExternalCtrlToApp_CtrlVoiceSwitch(p[1]);
			}
			break;
		default:break;
	}
}

void moduleToExternalCtrl_AnalyseModuleCommand_center(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x00:
		{
			if(p[1] == 0x00)//screen on
			{
				accstatus = true;
				setTagExternalCtrlToApp_CtrlVoiceSwitch(0x01);
			}
			else if(p[1] == 0x01)//screen off
			{
				accstatus = false;
				setTagExternalCtrlToApp_CtrlVoiceSwitch(0x00);
			}
		}
		break;
		default:break;
	}
}

void moduleToExternalCtrl_AnalyseModuleCommand_Audiovideo(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x00:
		{
			externalCtrlToSpeechApp_RequestCtrlCmd(0x00);
		}
		break;
		default:break;
	}

}

void setTagExternalCtrlToApp_CtrlVoiceSwitch(u8 p)
{
    u8 ucLCDBrightNess = 0;
	u8 ucLCDBrightNessLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,LCD_STATE,&ucLCDBrightNess,&ucLCDBrightNessLen);

	u8 backStatus = 0;
	u8 backLen = 0;
	getOtherModuleParam(MODULE_ID_BACK, BACK_CAR_STATE, (u8*)&backStatus, &backLen);
	
	u8 btPhoneStatus = 0;
	u8 btPhoneLen = 0;
	getOtherModuleParam(MODULE_ID_BT, BT_MOBILE_STATUS, (u8*)&btPhoneStatus, &btPhoneLen);

	LOGD("[%s] backStatus:%x btPhoneStatus:%x",__FUNCTION__,backStatus,btPhoneStatus);
	if(p == 0x01){//unembar
		if(!accstatus){
		}
		else if(ucLCDBrightNess == 0){
		}
		else if(backStatus == 0x01){
		}
		else if(btPhoneStatus != 0x00){
		}
		else{
			externalCtrlToApp_CtrlVoiceSwitch(0x01);
		}
	}
	else if(p == 0x00)//embar
	{
		externalCtrlToSpeechApp_RequestCtrlCmd(0x00);
		externalCtrlToApp_CtrlVoiceSwitch(0x00);
	}
}

