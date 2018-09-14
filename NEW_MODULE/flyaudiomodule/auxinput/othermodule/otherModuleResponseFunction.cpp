#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "moduleParamRequest.h"
#include "moduleParamResponse.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "appRequestCommand.h"
#include "timer_interface.h"
#include "appResponseFunction.h"


void moduleToAUX_FromAudiovideo_GetOsdVideoSetting(unsigned char type, unsigned char value){
	switch(type){
		case 0x00:
			setAnalogData(CONTROLID_AUX_VIDEO_SET_COLOUR_GAUGE, value);
			break;
		case 0x01:
			setAnalogData(CONTROLID_AUX_VIDEO_SET_CHROMINANCE_GAUGE, value);
			break;
		case 0x02:
			setAnalogData(CONTROLID_AUX_VIDEO_SET_CONTRAST_GAUGE, value);
			break;
		case 0x03:
			setAnalogData(CONTROLID_AUX_VIDEO_SET_BRIGHTNESS_GAUGE, value);
			break;
		default:
			break;
	}
}


void moduleToAux_FromKey_AnalyseMsg(unsigned char* buf,int len){
	switch(buf[0]){
		case 0x00:
			moduleToAux_FromKey_DispatchProcessKeyCmd(buf[1]);
			break;
		default:
			break;
	}
}

void moduleToAux_FromExternalCtrl_AnalyseMsg(unsigned char* buf,int len)
{
	if(buf[0]==0x01)
	{
		if(buf[1]==0x01)
		{
			if(pLocalParam->bBrakeState == false && pLocalParam->bInSleep) //System´«À´µÄ×´Ì¬£¬²»¿É½øÈëÊÓÆµ false
				return;

			u16 CurPageID = 0;
			u8	CurPageIDLen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen); 
			LOGD("moduleToAux_FromKey_ProcessPanelKey_AV   ++++CUR_PAGE:%x", CurPageID);
			if(CurPageID!=PAGE_AUX && CurPageID!=PAGE_AUX_VIDEO && CurPageID != PAGE_AUX_VIDEO_CONTROL && CurPageID != PAGE_AUX_VIDEO_SET)
			{
				pLocalParam->bEnterAux = true;
				auxToModule_NotifySystem_jumpPage(PAGE_AUX);
				auxToApp_SetAUX_NoSignal_Prompt_box(false);
				auxToApp_SetAUXVideo_Checking_Prompt_box(true);
				auxToHal_QueryVideo();
			}
		}
		else
		{
		}
	}
}

void moduleToAux_FromAutomate_AnalyseMsg(unsigned char* buf,int len)
{
    #include "appResponseCommand.h"
    
    if(buf[0] != 0xff)
    return;
    analyseAppMessage(buf+1,len-1);   
}

void moduleToAux_FromSystem_AnalyseMsg(unsigned char* buf,int len){
	unsigned char ucSystemCmd = buf[0];
	
	switch(ucSystemCmd)
	{
	case 0x09: //É²³µ×´Ì¬
		{
			unsigned char ucState = buf[1];
			moduleToAux_FromSystem_BrakeState((char)ucState);
		}
		break;
	case 0x10:
		moduleToAux_FromSystem_SaveDataToRestart();
		break;
	case 0x14: //Í¨Öª¸÷Ä£¿é»Ö¸´³ö³§ÉèÖÃ
		moduleToAux_FromSystem_RestoreToFactoryDefaults();
		break;
	case 0x28://ÓÉSystem×ª·¢À´×ÔDriverµÄÏûÏ¢
		halToAux_QueryVideo(buf[1]);
		break;
	case 0x38:
		LOGI("+++++++AUX_OSD BACK,buf[1]:%x",buf[1]);
		if(buf[1] == 0x00){
			DeleteTimer(AUX_OSD_TIMER_HIDDEN_DISPLAY);
			}
		break;
	case 0x0E:
		if(buf[1] == 0x01){
			pLocalParam->bInSleep = true;
			pLocalParam->uSleepOnDealLogic=0;
		}
		else if(buf[1 == 0x00]){
			pLocalParam->bInSleep = false;
			pLocalParam->uSleepOnDealLogic=1;
		}
		break;
	case 0x39:
		{
			u16 CurPageID = 0;
			u8	CurPageIDLen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
			LOGD("------------------> %x", CurPageID);
			if(CurPageID == PAGE_AUX)
			{
				auxToApp_SetAUX_NoSignal_Prompt_box(false);
				auxToApp_SetAUXVideo_Checking_Prompt_box(true);
			}
			else
			{
				auxToModule_NotifySystem_jumpPage(PAGE_AUX);
				auxToApp_SetAUX_NoSignal_Prompt_box(false);
				auxToApp_SetAUXVideo_Checking_Prompt_box(true);
			}
		}
		break;
	default:break;
	}
}

void moduleToAux_FromAudio_AnalyseMsg(unsigned char* buf,int len){
	u8 cmd = buf[0];
	u8 param = buf[1];
	switch(cmd)
	{
	case 0x00://µÃµ½ÉùµÀÇÐ»»
		{
			if(param == 0x05 || param == 0x06)
			{
				LOGD("pLocalParam->bInAuxChannel:%d",pLocalParam->bInAuxChannel);
				if(pLocalParam->bInAuxChannel == true)
					return;//±¾ÉíÒÑÔÚauxÍ¨µÀ£¬²»ÓÃÖØ¸´´¦Àí

				pLocalParam->bInAuxChannel = true;
				
				u16 CurPageID = 0;
				u8  CurPageIDLen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
				LOGD("moduleToAux_FromAudio_AnalyseMsg----->pLocalParam->bInSleep:%d %x", pLocalParam->bInSleep,CurPageID);
				if((!(CurPageID == PAGE_AUX_VIDEO || CurPageID == PAGE_AUX_VIDEO_CONTROL || CurPageID == PAGE_AUX_VIDEO_SET)) && pLocalParam->bInSleep){
					pLocalParam->bInSleep = false;
					return;
				}

				u8 is_canJumpAUX=1;
				u8 is_canJumpAUX_Len=1;
				getOtherModuleParam(MODULE_ID_AUDIOVIDEO, IS_CANJUMPAUX, &is_canJumpAUX, &is_canJumpAUX_Len);
				LOGD("aux otherModule is_canJumpAUX:%x",is_canJumpAUX);
				if(is_canJumpAUX == 0)
				{
					return;
				}

				LOGD("CurPageID:%x pLocalParam->uSleepOnDealLogic:%x",CurPageID,pLocalParam->uSleepOnDealLogic);
				if(CurPageID != PAGE_AUX && CurPageID != PAGE_AUX_VIDEO && pLocalParam->uSleepOnDealLogic==1)
				{
					pLocalParam->bEnterAux = false;
					pLocalParam->uSleepOnDealLogic=0;
				}
				else
				{
					pLocalParam->bEnterAux = true;
				}
				
			}
			else
			{
				pLocalParam->bInAuxChannel = false;
				pLocalParam->bEnterAux = false;

				auxToApp_SetAUXVideo_Checking_Prompt_box(false);
				auxToApp_SetAUX_NoSignal_Prompt_box(true);
			}
		}
		break;
	case 0x11:
		moduleToAUX_FromAudiovideo_GetOsdVideoSetting(buf[1], buf[2]);
		break;
	}
}

void moduleToAux_FromKey_DispatchProcessKeyCmd(unsigned char ucCmd){
	switch(ucCmd)
	{
	case 0x01://Ãæ°å°´¼üNAVI
		moduleToAux_FromKey_ProcessPanelKey_NAVI();
		break;
	case 0x02://Ãæ°å°´¼üMENU
		moduleToAux_FromKey_ProcessPanelKey_MENU();
		break;
	case 0x03:  //Ãæ°å°´¼üAV
		moduleToAux_FromKey_ProcessPanelKey_AV();
		break;
	case 0x15://Ãæ°åAUX
		moduleToAux_FromKey_ProcessPanelKey_AUX();
		break;
	default:
		break;
	}
}

void moduleToAux_FromKey_ProcessPanelKey_NAVI(){//-----------2012--6-07-chenbohong----------

	u16 CurPageID = 0;
	u8  CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen);
	if(CurPageID==PAGE_AUX || CurPageID==PAGE_AUX_VIDEO || CurPageID==PAGE_AUX_VIDEO_CONTROL || CurPageID == PAGE_AUX_VIDEO_SET){
		//Èç¹ûÔÚauxÒ³ÃæÀï£¬ÇÐµ½ÆäËûÄ£¿
		pLocalParam->bEnterAux = false;
		unsigned char buf[] = {0x81,MODULE_ID_AUX};
		makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_SYSTEM,buf,2);
	}
	else{
		//Èç¹û²»ÔÚaux,ÔòÏÈÇÐµ½aux
		pLocalParam->bEnterAux = true;
		auxToModule_NotifySystem_jumpPage(PAGE_AUX);
		auxToApp_SetAUX_NoSignal_Prompt_box(false);
		auxToApp_SetAUXVideo_Checking_Prompt_box(true);
	}
}

void moduleToAux_FromSystem_SaveDataToRestart(){
	saveParameter();
}

void moduleToAux_FromSystem_RestoreToFactoryDefaults(){
	SetDefaultParam();
	saveParameter();
}

void moduleToAux_FromSystem_EnterVideo(){
	
	u16 CurPageID = 0;
	u8 CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen);
	LOGD("moduleToAux_FromSystem_EnterVideo---->CUR_PAGE:%x", CurPageID);

	if (PAGE_AUX_VIDEO == CurPageID || PAGE_AUX_VIDEO_CONTROL == CurPageID || PAGE_AUX_VIDEO_SET == CurPageID)//AuxÒ³Ãæ
		return;
	auxToModule_NotifySystem_jumpPage(PAGE_AUX_VIDEO);
}

void moduleToAux_FromSystem_EnterCtrlFace(){
	u16 CurPageID = 0;
	u8 CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen); 
	LOGD("moduleToAux_FromSystem_EnterCtrlFace---->CUR_PAGE:%x", CurPageID);
	
	auxToApp_SetAUXVideo_Checking_Prompt_box(false);
	auxToApp_SetAUX_NoSignal_Prompt_box(true);
	
	if (PAGE_AUX == CurPageID)//AuxÒ³Ãæ
		return;	
	auxToModule_NotifySystem_jumpPage(PAGE_AUX);//jump page to no video
}

void moduleToAux_FromKey_ProcessPanelKey_MENU(){
	pLocalParam->bEnterAux = false;
	auxToModule_NotifySystem_jumpPage(PAGE_MENU);
}

void moduleToAux_FromKey_ProcessPanelKey_AV(){
	
	u16 CurPageID = 0;
	u8  CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen); 
	LOGD("moduleToAux_FromKey_ProcessPanelKey_AV   ++++CUR_PAGE:%x", CurPageID);
	if(CurPageID==PAGE_AUX || CurPageID==PAGE_AUX_VIDEO || CurPageID==PAGE_AUX_VIDEO_CONTROL || CurPageID == PAGE_AUX_VIDEO_SET)
	{
		//ÈçÔÚauxÒ³ÃæÀï£¬ÇÐµ½ÆäËûÄ£¿é
		pLocalParam->bEnterAux = false;
		unsigned char buf[] = {0x81,MODULE_ID_AUX};
		makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_SYSTEM,buf,2);
	}else
	{
		LOGD(" ++++pLocalParam->bBrakeState:%x", pLocalParam->bBrakeState);
		if(pLocalParam->bBrakeState)
		{
			//Èç²»ÔÚaux,ÔòÏÈÇÐµ½aux
	       	pLocalParam->bEnterAux = true;
			auxToModule_NotifySystem_jumpPage(PAGE_AUX);
		}
		else
		{
			pLocalParam->bEnterAux = false;
			unsigned char buf[] = {0x81,MODULE_ID_AUX};
			makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_SYSTEM,buf,2);
		}
		
	}
}

void moduleToAux_FromKey_ProcessPanelKey_AUX()
{
	if(pLocalParam->bBrakeState == false) //System´«À´µÄ×´Ì¬£¬²»¿É½øÈëÊÓÆµ false
		return;
	pLocalParam->bEnterAux = true;
	
	u16 CurPageID = 0;
	u8  CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen); 
	LOGD("moduleToAux_FromKey_ProcessPanelKey_AV   ++++CUR_PAGE:%x", CurPageID);
	if(CurPageID!=PAGE_AUX && CurPageID!=PAGE_AUX_VIDEO && CurPageID!=PAGE_AUX_VIDEO_CONTROL && CurPageID != PAGE_AUX_VIDEO_SET)
	{
		auxToModule_NotifySystem_jumpPage(PAGE_AUX);
		auxToApp_SetAUX_NoSignal_Prompt_box(false);
		auxToApp_SetAUXVideo_Checking_Prompt_box(true);
	}
}

void moduleToAux_FromSystem_BrakeState(char cBrake){
	LOGD("moduleToAux_FromSystem_BrakeState++++cBrake:%x", cBrake);
	if(cBrake == 0x01)//¿ÉÒÔ½øÈëÊÓÆµ
	{        
		pLocalParam->bBrakeState = true;
	}
	else //²»¿É½øÈëÊÓÆµ£¬ÔÚÊÓÆµÀï¾ÍÒªÍË³öÊÓÆµ
	{
		pLocalParam->bBrakeState = false;
		u16 CurPageID = 0;
		u8 CurPageIDLen = 0;
		getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen); 
		if (CurPageID == PAGE_AUX_VIDEO||CurPageID == PAGE_AUX_VIDEO_CONTROL ||CurPageID == PAGE_AUX_VIDEO_SET)
		{
			pLocalParam->bEnterAux = false;
			auxToModule_NotifySystem_jumpPage(PAGE_MENU);
		}
	}
}

