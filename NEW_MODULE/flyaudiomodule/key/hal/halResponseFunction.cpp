#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "paramID.h"
#include "pageID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestFunction.h"
#include "stringID.h"
#include "controlID.h"
#include "timer_interface.h"
#include "appRequestCommand.h"

extern "C"{
#include "unicodestring.h"
};
void KeyToApp_SendPanelkey(u8 keyval)
{
	LOGD("KeyToApp_SendPanelkey keyval=%d",keyval);
	setPanelKeyToAndroid(keyval);
}

int analyseThreePartyPageKeyValue(u8 keyval){
	u8 keyvalue = 0x00;
	int ret = 0;

	switch(keyval){
		case HALTOKEY_KEYVAL_SEEK_INC:
		case HALTOKEY_KEYVAL_SEEK_INC2:
		case HALTOKEY_KEYVAL_TUNE_INC:
			keyvalue = 0x02;
			ret = 1;
			break;
		case HALTOKEY_KEYVAL_SEEK_DEC:
		case HALTOKEY_KEYVAL_SEEK_DEC2:
		case HALTOKEY_KEYVAL_TUNE_DEC:
			keyvalue = 0x01;
			ret = 1;
			break;

		default:
			break;
	}

	setAndroidSTDKey(keyvalue);

	return ret;
}


void halToKey_KeyValue_Sleep(void){

}

void halToKey_analyseKeyValue(unsigned char keyValue){

	LOGD("[%s] key = [0x%x]", __FUNCTION__, keyValue);

	//////////////////////////////////////////////////////////////////////////
	/*switch(keyValue)
	{
	case HALTOKEY_KEYVAL_SEEK_INC:
		{
			keyValue = HALTOKEY_KEY_DNV_SWITCH_SHORT_PRESS;
		}
		break;
	case HALTOKEY_KEYVAL_SEEK_DEC:
		{
			keyValue = HALTOKEY_KEY_DNV_AVOID_GLARE_LONG_PRESS;
		}
		break;
	}*/
	//////////////////////////////////////////////////////////////////////////

	SendKeyValueToOSDDebug(keyValue);
	 pLocalParam->g_pClsKeyJniSdk->sendToApp_KeyValue(keyValue);
    pLocalParam->bKeyAction_DropDownOSD = true;

	unsigned char ucModuleToSend = 0x00;
    int nDispatchBySoundMode = false;//According to track analyse
    u16 wCurPageID = 0;
	u8 curpageLen = 0;

	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&wCurPageID, &curpageLen);
    if(wCurPageID==PAGE_BACK_VIDEO)
    {
    	bool bExistKey=true;
    	switch(keyValue)
    	{
    	case HALTOKEY_KEYVAL_SEEK_INC:
    	case HALTOKEY_KEYVAL_SEEK_INC2:
    	case HALTOKEY_KEYVAL_TUNE_INC:

    	case HALTOKEY_KEYVAL_SEEK_DEC:
    	case HALTOKEY_KEYVAL_SEEK_DEC2:
    	case HALTOKEY_KEYVAL_TUNE_DEC:
    		bExistKey =false;
    		break;
    	default:
    		break;
    	}
    	if(bExistKey)
    	   keyToExtcarModule_Notify_Prado_KeyInfo(0x01);
    }

	unsigned char cSoundMode = pLocalParam->m_iSoundChannel;
	u8 cMediaState=1;
	u8 cSoundCardState=0;
	getOtherModuleParam(MODULE_ID_AUDIOVIDEO, MEDIA_PLAY_STATE, &cMediaState, &curpageLen);
	getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CARD_STATE, &cSoundCardState, &cSoundCardState);
	
	u8 bIsInBackCar = 0;
	u8 bIsBackCarRadar = 0;
	getOtherModuleParam(MODULE_ID_BACK, BACK_CAR_STATE, &bIsInBackCar, &curpageLen);
	LOGD("\n---halToKey_analyseKeyValue--\n",bIsInBackCar);
	if(bIsInBackCar) return;
	
	getOtherModuleParam(MODULE_ID_BACK, BACK_CAR_RADAR_STATUS, &bIsBackCarRadar, &curpageLen);
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&wCurPageID, &curpageLen);
	LOGD("\n---halToKey_analyseKeyValue--bIsBackCarRadar=%x-----wCurPageID=%x--\n",bIsBackCarRadar,wCurPageID);
	if (bIsBackCarRadar)
	{
		if(wCurPageID == PAGE_BACK_NOVIDEO)
		{	
        	ucModuleToSend = MODULE_ID_SYSTEM;
        	keyToModule_DispatchPanelKey(nDispatchBySoundMode,ucModuleToSend,keyValue);
        	return;
        } 
	}

	if((wCurPageID == PAGE_BACK_FULL_VIDEO) || (wCurPageID == PAGE_BACK_FULL_VIDEO_CONTROL))
	{
		keyToModule_NotifyBACK_ExitAllScreen();
	}

	if(pLocalParam->u_bSync_BTCall)
	{
		if(keyValue == 1)
		return;
	}
	unsigned char ucSleepState = 0;
	unsigned char ucSleepStateLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,SLEEP_STATE,&ucSleepState,&ucSleepStateLen);
	LOGD("ucSleepState:0x%x",ucSleepState);
	if (1 == ucSleepState)//sleep state
	{
		if(keyValue==HALTOKEY_KEYVAL_SLEEP)
		{
			ucModuleToSend = MODULE_ID_SYSTEM;
	       keyToModule_DispatchPanelKey(nDispatchBySoundMode,ucModuleToSend,keyValue);
        }
        
		return;
	}

    unsigned char ucLCDBrightNess = 0;
	unsigned char ucLCDBrightNessLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,LCD_STATE,&ucLCDBrightNess,&ucLCDBrightNessLen);
	LOGD("ucLCDBrightNess:0x%x",ucLCDBrightNess);
	//the screen off state
	if (ucLCDBrightNess == 0)
	{
        ucModuleToSend = MODULE_ID_SYSTEM;
        keyToModule_DispatchPanelKey(nDispatchBySoundMode,ucModuleToSend,keyValue);
        return;
	}

	u16 btPhoneState = 0;
	unsigned char btPhoneStateLen = 1;
	getOtherModuleParam(MODULE_ID_BT, BT_MOBILE_STATUS, (u8 *)&btPhoneState, (u8 *)&btPhoneStateLen);
	
	switch(keyValue)
	{
		case KB_SEEK_INC_CALL_REJECT:
		case KB_SEEK_DEC_CALL:
		{
			if(btPhoneState != 0x00)
			{
				keyToModule_DispatchPanelKey(0x00,MODULE_ID_BT,keyValue);
				return;
			}
			else 
			{
				if(keyValue == KB_SEEK_INC_CALL_REJECT)
					keyValue = HALTOKEY_KEYVAL_SEEK_INC;
				if(keyValue == KB_SEEK_DEC_CALL)
					keyValue = HALTOKEY_KEYVAL_SEEK_DEC;
			}
		}
		break;
			default:break;
	}

	switch(keyValue){
		case HALTOKEY_KEYVAL_NP:
		case HALTOKEY_KEYVAL_SLEEP:
			ucModuleToSend = MODULE_ID_SYSTEM;
			break;
		case HALTOKEY_KEYVAL_MENU:
			nDispatchBySoundMode = true;
			break;
		case HALTOKEY_KEYVAL_AV: 
			if(pLocalParam->n_DispatchBySoundMode == true){
				nDispatchBySoundMode = true;
				pLocalParam->n_DispatchBySoundMode = false;
				DeleteTimer(MEDIA_KEYEVENT);
				SetTimer(500,1,MEDIA_KEYEVENT);
			}
			break;
		case HALTOKEY_KEYVAL_DVD:
			ucModuleToSend = MODULE_ID_DVD;
			break;
		case HALTOKEY_KEYVAL_CDC:
			//ucModuleToSend = Module_CDC;
			break;
		case HALTOKEY_KEYVAL_RADIO:
			ucModuleToSend = MODULE_ID_RADIO;
			break;
		case HALTOKEY_KEYVAL_IPOD:
			ucModuleToSend = MODULE_ID_IPOD;
			break;
		case HALTOKEY_KEYVAL_BT:
			ucModuleToSend = MODULE_ID_BT;
			break;
		case HALTOKEY_KEYVAL_AC:
			ucModuleToSend = MODULE_ID_AC;
			break;
		case HALTOKEY_KEYVAL_TV:
			ucModuleToSend = MODULE_ID_TV;
			break;
		case HALTOKEY_KEYVAL_FM1:
		case HALTOKEY_KEYVAL_FM2:
		case HALTOKEY_KEYVAL_AM:
		case HALTOKEY_KEYVAL_FM:
			ucModuleToSend = MODULE_ID_RADIO;
			break;

		case HALTOKEY_KEYVAL_NAVI:
		case HALTOKEY_KEYVAL_DEST:
		case HALTOKEY_KEYVAL_LOCAL:
			if(pLocalParam->n_DispatchBySoundMode == true){
				ucModuleToSend = MODULE_ID_GPS;
				pLocalParam->n_DispatchBySoundMode = false;
				DeleteTimer(MEDIA_KEYEVENT);
				SetTimer(500,1,MEDIA_KEYEVENT);
			}
			break;	
		//case HALTOKEY_KEYVAL_DEST://������
		//	KeyToApp_SendPanelkey(keyValue);
		//	break;
		case HALTOKEY_KEYVAL_SETUP:
			ucModuleToSend = MODULE_ID_SYSTEM;
			break;
		case HALTOKEY_KEYVAL_INFO:
			ucModuleToSend = MODULE_ID_SYSTEM;
			break;
		case HALTOKEY_KEYVAL_AUX:
			ucModuleToSend = MODULE_ID_AUX;
			break;
        case HALTOKEY_KEYVAL_MEDIA:
            ucModuleToSend = MODULE_ID_MEDIA;
            break;
		case HALTOKEY_KEYVAL_CALL:
		case HALTOKEY_KEYVAL_CALL_REJECT:
			ucModuleToSend = MODULE_ID_BT;
			break;
		case HALTOKEY_KEYVAL_DIMM:
			ucModuleToSend = MODULE_ID_SYSTEM;
			break;
		case HALTOKEY_KEYVAL_OPEN:
			ucModuleToSend = MODULE_ID_DVD;
			break;
		case HALTOKEY_KEYVAL_VOL_INC:
		case HALTOKEY_KEYVAL_VOL_DEC:
		case HALTOKEY_KEYVAL_MUTE:
			ucModuleToSend = MODULE_ID_AUDIOVIDEO;
			break;
		case HALTOKEY_KEYVAL_SEEK_INC:
		case HALTOKEY_KEYVAL_SEEK_DEC:	
		case KEY_RELEASE:
		{
			u8 n_IsAux = 0;
			u8 n_IsAuxLen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_IS_AUX,(u8*)&n_IsAux,&n_IsAuxLen);
			if(n_IsAux == 0)
			{
				if(pLocalParam->m_iSoundChannel == 0x05 || pLocalParam->u_bSync_BTCall){
					ucModuleToSend = MODULE_ID_SYNC;
					keyToModule_DispatchPanelKey(nDispatchBySoundMode,ucModuleToSend,keyValue);
				}

			}
			
			if(pLocalParam->u_bSync_BTCall)
				return;
		
			nDispatchBySoundMode = true;

			
			LOGD(" wCurPageID=%d,cSoundMode=%d,cSoundCardState=%d cMediaState=%d",wCurPageID,cSoundMode,cSoundCardState, cMediaState);
			if((cSoundMode == CHANNEL_THREECHANNEL)
				&&(keyValue == HALTOKEY_KEYVAL_SEEK_INC || keyValue == HALTOKEY_KEYVAL_SEEK_DEC)
				)
			{
				KeyToApp_SendPanelkey(keyValue);
				return ;
			}
		}
		break;
		case HALTOKEY_KEYVAL_TUNE_DOWN:
			if(pLocalParam->n_DispatchBySoundMode == true)
			{
				ucModuleToSend = MODULE_ID_SYSTEM;
				pLocalParam->n_DispatchBySoundMode = false;
				DeleteTimer(MEDIA_KEYEVENT);
				SetTimer(500,1,MEDIA_KEYEVENT);
			}
			break;
		case HALTOKEY_KEYVAL_TUNE_INC:
		case HALTOKEY_KEYVAL_TUNE_DEC:
		{	
			if(PAGE_GPS_PAGE == wCurPageID)
			{
           		ucModuleToSend = MODULE_ID_GPS;
				break;
			}
			else
				nDispatchBySoundMode = true;


			if(cSoundMode == CHANNEL_THREECHANNEL)
			{
				KeyToApp_SendPanelkey(keyValue);
				return ;
			}
			break;
		}
		case HALTOKEY_KEYVAL_SEEK_INC2:
       		ucModuleToSend = MODULE_ID_RADIO;
			break;
		case HALTOKEY_KEYVAL_SEEK_DEC2:
			ucModuleToSend = MODULE_ID_RADIO;
			break;
		case HALTOKEY_KEYVAL_PANEL_ANGLE:
		case HALTOKEY_KEYVAL_PANEL_OPEN:
			ucModuleToSend = MODULE_ID_SYSTEM;
			break;
		case HALTOKEY_KEYVAL_KEY_UP:
		case HALTOKEY_KEYVAL_KEY_DOWN:
		case HALTOKEY_KEYVAL_KEY_LEFT:
		case HALTOKEY_KEYVAL_KEY_RIGHT:
			nDispatchBySoundMode = true;
			break;
		case HALTOKEY_KEYVAL_KEY_ENTER:
			ucModuleToSend = MODULE_ID_SYSTEM;
			break;
		case HALTOKEY_KEYVAL_kEY_CALLOUT:
		case HALTOKEY_KEYVAL_KEY_CALLINOUT:
			{
				ucModuleToSend = MODULE_ID_BT;
				
				u8 n_IsAux = 0;
				u8 n_IsAuxLen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_IS_AUX,(u8*)&n_IsAux,&n_IsAuxLen);
				if(n_IsAux == 0)
				{
					ucModuleToSend = MODULE_ID_SYNC;
				}
			}
			break;
		case HALTOKEY_KEYVAL_KEY_SCAN:
			break;
		case HALTOKEY_KEYVAL_KEY_PAUSE:
			 nDispatchBySoundMode = true;
			 break;
		case HALTOKEY_KEYVAL_KEY_TUNE_DOWN2:
			ucModuleToSend = MODULE_ID_SYSTEM;
			break;

		case HALTOKEY_KEYVAL_KEY_STT:break;

		case HALTOKEY_KEYVAL_KEY_DVD_SEEK_INC:break;
		case HALTOKEY_KEYVAL_KEY_DVD_SEEK_DEC:break;
		case HALTOKEY_KEYVAL_KEY_RADIO_SEEK_INC:break;
		case HALTOKEY_KEYVAL_KEY_RADIO_SEEK_DEC:break;
		case HALTOKEY_KEYVAL_KEY_SRADIO_SEEK_INC:break;
		case HALTOKEY_KEYVAL_KEY_SRADIO_SEEK_DEC:break;

		case HALTOKEY_KEYVAL_KEY_HOME:
		case HALTOKEY_KEYVAL_KEY_MENU:
		case HALTOKEY_KEYVAL_KEY_BACK:
			 //ucModuleToSend = MODULE_ID_SYSTEM;
			break;
		case 0x4b:/*����˹����������*/
		case 0x4c:
			ucModuleToSend = MODULE_ID_SYNC;
			break;
		case HALTOKEY_KEYVAL_ANDROIDSPEECH:
		case HALTOKEY_KEYVAL_KB_FLY_MENU: 
			keyToExtcarModule_NotifyExternalCtrl_SpeechKeyInfo(0x00);
			//KeyToApp_SendPanelkey(keyValue);
			return;
			break;
		case HALTOKEY_KEY_STOP_SPEECH_KEY:
			keyToExtcarModule_NotifyExternalCtrl_SpeechKeyInfo(0x01);
			return;
			break;
		case HALTOKEY_KEYVAL_KEY_KB_SCREEN:
		    ucModuleToSend = MODULE_ID_SYSTEM;
		    break;
		case HALTOKEY_KEY_DNV_SWITCH_SHORT_PRESS:
		case HALTOKEY_KEY_DNV_AVOID_GLARE_LONG_PRESS:
			{
				ucModuleToSend = MODULE_ID_DNV;
				LOGD("[%s] DNV key = [0x%x]", __FUNCTION__, keyValue);
			}
			break;
		case HALTOKEY_KEYVAL_KEY_CUSTOM_APK_1:
		case HALTOKEY_KEYVAL_KEY_CUSTOM_APK_2:
		case HALTOKEY_KEYVAL_KEY_CUSTOM_APK_3:
			ucModuleToSend = MODULE_ID_SYSTEM;
			break;
		default:break;
	}

	LOGD("dispathbysoundMode:%d, ucModuleToSend:%x, keyvalue:%x", nDispatchBySoundMode, ucModuleToSend, keyValue);
	keyToModule_DispatchPanelKey(nDispatchBySoundMode,ucModuleToSend,keyValue);

}


void analyseHalMessage_KEY(char resCmd, unsigned char *param, unsigned char len){
	switch(resCmd){
		case HALTOKEY_GET_KEY:
			halToKey_analyseKeyValue(param[0]);
			break;
		default:break;
	}
}




/*
	for debug
*/
void showDebug(unsigned char type){
	char debugState[5];
	memset(debugState, '*', 5);
	int i;
	for(i = 0;i<5;i++){
		if(i==0){
			sprintf(debugState,"%d", type);
		}else if(i==3){
		debugState[i] = ':';
		}else if(i==4){
		debugState[i] = '\0';
		}
	}
	unicode16_t *numberDislay = (unicode16_t *)malloc(2*5);
	int j;
	for(j=0;j<5; j++){
		numberDislay[j] = '#';
	}
	ansi_str_to_unicode16((u8*)debugState, numberDislay);
	setSerialData(CONTROLID_BLUETOOTH_MAIN_NUMBER_TEXT, (u8*)numberDislay,10);
	free(numberDislay);
	numberDislay = NULL;
}
