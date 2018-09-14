#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"
#include "appRequestFunction.h"
#include "timer_interface.h"
#include "voiceLogic.h"


void analyseSpeechCtrlCmdToFlyaudio(unsigned char *param, unsigned char paramLen){

    LOGD("param[0]:0x%x--param[1]:0x%x",param[0],param[1]); 
	switch(param[0]){
		case 0x01:
			ExternalCtrlToAudiovideo_SetVol(&param[1],paramLen-1);
			break;
		case 0x02:
			ExternalCtrlToRadio_SetRadio(&param[1],paramLen-1);
			break;
		case 0x03:
			ExternalCtrlToOtherModule_SetPlayState(param[1]);
			break;
		case 0x04:
			break;
		case 0x05:
			ExternalCtrlToKeyModule(&param[1],paramLen-1);
			break;
		case 0x06:
			ExternalCtrl_FlyauidioApp_Management(&param[1],paramLen-1);
			break;
		case 0x07:
			ExternalCtrlToAC_Message(&param[1],paramLen-1);
			break;
		case 0x08:
			ExternalCtrlToBt_Message(&param[1],paramLen-1);
			break;
		case 0x09:
			if(param[1]==0x01)
			ExternalCtrlToSystem_Message(&param[2],paramLen-2);
			break;
		case 0x10:
		    ExternalCtrlToSystem_about_JumpPageMessage(&param[1],paramLen-1);
		    break;
		default:break;
	}
}

void analyseRemoteAppInfors(u8 *param, u8 paramLen)
{
	LOGD("[%s] param[0]=%d,param[1]=%d,param[2]=%d",__FUNCTION__,param[0],param[1],param[2]);
	switch(param[0])
	{
		case 0x01:
			if(param[1] == 0x00)
			{
				ExternalCtrlModuleToApp_aboutMCU();
				ExternalCtrlModuleToApp_aboutBarcode();
				ExternalCtrlModuleToApp_aboutBluetoothVersion();
				ExternalCtrlModuleToApp_aboutMPEG();

				ExternalCtrlModuleToApp_End();
			}
		break;
		case 0x02:
			getVoiceStatus(param+1,paramLen - 1);
		break;
		default:break;
	}
}

void RemoteDureOsVoicePageState(u8 p)
{
	pLocalParam->uCurSpeechState = p;

	u8 ucBackMode = 0;
	int ucBackModeLen = 0;
	getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&ucBackModeLen);
	if(ucBackMode == 0x01)
		return;
			
	switch(p)
	{
		case 0x00://out
		{
			ExternalCtrlToSysModule_MicUsingState(0x00);
			
			unsigned short icurSound = 0;
			u8 icurSoundLen = 0;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&icurSound,&icurSoundLen);
			LOGD("[%s] icurSound = [%x]", __FUNCTION__, icurSound);
			if(icurSound == CHANNEL_SPEECH_MEDIA_CTRL)
			{
				DeleteTimer(TIMERID_FLY_EXTERNALCTRL_END_SPEECH);
				SetTimer(TIMERS_FLY_EXTERNALCTRL_END_SPEECH,1, TIMERID_FLY_EXTERNALCTRL_END_SPEECH);
			}
		}
		break;
		case 0x01:
		{
			unsigned short icurSound = 0;
			u8 icurSoundLen = 0;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&icurSound,&icurSoundLen);
			LOGD("[%s] icurSound = [%x]", __FUNCTION__, icurSound);
			if(icurSound != CHANNEL_SPEECH_MEDIA_CTRL)
			{
				ExternalCtrlToSysModule_MicUsingState(0x01);
				DeleteTimer(TIMERID_FLY_EXTERNALCTRL_END_SPEECH);
				ExternalCtrlToAudiovideo_SetChannel(CHANNEL_SPEECH_MEDIA_CTRL);
			}
		}
		break;
		default:break;
	}
}

void ExternalCtrlModuleToApp_aboutMCU()
{
	u8 szMCU[100];
	memset(szMCU,0,sizeof(szMCU));
	u8 ucParamLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, MCU_INFO, szMCU, &ucParamLen);
	int nInfoLen = strlen((char*)szMCU);
	if(nInfoLen > 1){
		if(szMCU[nInfoLen-1] == 0x0A){
			nInfoLen = nInfoLen -1;
		}
	}
	
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 0x00;
	if(nInfoLen > 0){
		memcpy(pMsg+1, szMCU, nInfoLen);
	}
	externalCtrlToRemoteDiagnosticsApp_SysInfors(pMsg,nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;

}

void ExternalCtrlModuleToApp_aboutBarcode()
{
	u8 szBarCode[100];
	memset(szBarCode,0,sizeof(szBarCode));
	u8 ucParamLen = 0;
	getOtherModuleParam(MODULE_ID_SERVICE, BARCODE_INFO, szBarCode, &ucParamLen);
	int nInfoLen = strlen((char*)szBarCode);
	
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 0x01;
	if(nInfoLen > 0){
		memcpy(pMsg+1, szBarCode, nInfoLen);
	}
	externalCtrlToRemoteDiagnosticsApp_SysInfors(pMsg,nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;

}

void ExternalCtrlModuleToApp_aboutBluetoothVersion()
{
	u8 szBtVersion[100];
	memset(szBtVersion,0,sizeof(szBtVersion));
	u8 ucParamLen = 0;
	getOtherModuleParam(MODULE_ID_BT, BT_VERSION_INFO, szBtVersion, &ucParamLen);
	int nInfoLen = strlen((char*)szBtVersion);
	
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 0x02;
	if(nInfoLen > 0){
		memcpy(pMsg+1, szBtVersion, nInfoLen);
	}
	externalCtrlToRemoteDiagnosticsApp_SysInfors(pMsg,nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;

}

void ExternalCtrlModuleToApp_aboutMPEG()
{
	u8 szMEPG[100];
	memset(szMEPG,0,sizeof(szMEPG));
	u8 ucParamLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, MEPG_INFO, szMEPG, &ucParamLen);
	int nInfoLen = strlen((char*)szMEPG);

	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 0x03;
	if(ucParamLen > 0){
		memcpy(pMsg+1, szMEPG, nInfoLen);
	}
	externalCtrlToRemoteDiagnosticsApp_SysInfors(pMsg,nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;
}

void ExternalCtrlModuleToApp_End()
{
	u8 pMsg[1] = {0xFF};
	externalCtrlToRemoteDiagnosticsApp_SysInfors(pMsg,1);
}

void GetSpeechAppAudioStatusMsg(unsigned char *param, unsigned char paramLen)
{
	switch(param[0])
	{
		case 0x00://speech status
		{
				if(param[1] == 0x00){//speech play
					ExternalCtrlToAudiovideo_aboutSpeechState(0x01);
				}
				else if(param[1] == 0x01){//speech Recognition
					ExternalCtrlToAudiovideo_aboutSpeechState(0x02);
				}
				else if(param[1] == 0x02){//speech end
					ExternalCtrlToAudiovideo_aboutSpeechState(0x00);
				}

				/*
				if(param[1] == 0x02)
				{
					if(pLocalParam->bIsAutoJumpPrePage)
					{
						usleep(200*1000);
						
						u16 wPageId = 0;
						u8 curpagelen = 0;
						getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&wPageId,&curpagelen);
						if(wPageId == PAGE_SPEECH_APP_MEDIA)
						{
							externalctrlToModule_NotifySystem_jumpPrePage();
						}
					}
				}*/
		}
		break;
		case 0x01://speech-app media paly status
		{
			if(param[1] == 0x01)
				pLocalParam->bIsAutoJumpPrePage = false;
			
			ExternalCtrlToAudiovideo_aboutSpeechApp_MediaState(param[1]);
		}
		break;
		case 0x02:
		break;
		case 0x03:
			//RemoteDureOsVoicePageState(param[1]);
		break;
		default:break;
	}
}


