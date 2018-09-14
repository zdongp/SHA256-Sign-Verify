#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "pageID.h"
#include "stringID.h"
#include "controlID.h"

#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "moduleParamResponse.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestFunction.h"

extern "C"
{
	#include "unicodestring.h"
}

void ToPrintMessage(const char* msg, const char* buffer, const int length)
{

		int len = length * 3 + strlen(msg) + 1;
		char *out = (char*)malloc(len);
		if (!out) return ;

		memset(out, 0, sizeof(char) * len);
		snprintf(out, len, "%s:", msg);

		int i, j = strlen(msg);
		for (i = 0; i < length; i++)
			{
				snprintf(out + j, len - j, "%02X ", buffer[i]);
				j += 3;
			}
		LOGI("%s", out);
		free(out);
		
}

void UnicodeTransform(u8 *socParam,u8 *desParam,int nlen){
	for(int i =0;i < nlen - 1;i+=2){
		socParam[i+1] = desParam[i];
		socParam[i] = desParam[i+1];
	}
}

void Get_Sync_Title(u8 *buf,int len){
	if(buf == NULL || len <= 0)
	{
		setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_TITLE_TEXT,(u8*)"",0);
		return;
	}
	
	if(buf[0] == 1)//UNICODE
	{
		int nSendLen = len - 1;
		u8 *pwBuf = (u8 *)malloc(nSendLen+2);
		memset(pwBuf,0,nSendLen+2);
		UnicodeTransform(pwBuf,buf+1,nSendLen);
		setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_TITLE_TEXT,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
	else//ANSI
	{		
		int nSendLen = (len-1) * 2;
		u8 *pwBuf = (u8 *)malloc(nSendLen + 2);
		memset(pwBuf,0,nSendLen);
		ansi_str_to_unicode16(buf+1, (unicode16_t*)pwBuf);
		setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_TITLE_TEXT,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
}

void Get_Sync_String_OneLine(u8 *buf,int len){
	if(buf == NULL || len <= 0){
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_1,(u8*)"",0);
		return;
		}

	if(buf[0] == 1)
	{
		int nSendLen = len - 1;
		u8 *pwBuf = (u8 *)malloc(nSendLen+2);
		memset(pwBuf,0,nSendLen+2);
		UnicodeTransform(pwBuf,buf+1,nSendLen);
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_1,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
	else
	{	
		int nSendLen = (len-1) * 2;
		u8 *pwBuf = (u8 *)malloc(nSendLen + 2);
		memset(pwBuf,0,nSendLen);
		ansi_str_to_unicode16(buf+1, (unicode16_t*)pwBuf);
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_1,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
}

void Get_Sync_String_TwoLine(u8 *buf,int len){
	if(buf == NULL || len <= 0){
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_2,(u8*)"",0);
		return;
		}

	if(buf[0] == 1)
	{
		int nSendLen = len - 1;
		u8 *pwBuf = (u8 *)malloc(nSendLen+2);
		memset(pwBuf,0,nSendLen+2);
		UnicodeTransform(pwBuf,buf+1,nSendLen);
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_2,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
	else
	{
		int nSendLen = (len-1) * 2;
		u8 *pwBuf = (u8 *)malloc(nSendLen + 2);
		memset(pwBuf,0,nSendLen);
		ansi_str_to_unicode16(buf+1, (unicode16_t*)pwBuf);
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_2,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
}

void Get_Sync_String_ThreeLine(u8 *buf,int len){
	if(buf == NULL || len <= 0){
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_3,(u8*)"",0);
		return;
		}


	if(buf[0] == 1)
	{
		int nSendLen = len - 1;
		u8 *pwBuf = (u8 *)malloc(nSendLen+2);
		memset(pwBuf,0,nSendLen+2);
		UnicodeTransform(pwBuf,buf+1,nSendLen);
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_3,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
	else
	{
		int nSendLen = (len-1) * 2;
		u8 *pwBuf = (u8 *)malloc(nSendLen + 2);
		memset(pwBuf,0,nSendLen);
		ansi_str_to_unicode16(buf+1, (unicode16_t*)pwBuf);
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_3,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
}

void Get_Sync_String_FourLine(u8 *buf,int len){
	if(buf == NULL || len <= 0){
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_4,(u8*)"",0);
		return;
		}


	if(buf[0] == 1)
	{
		int nSendLen = len - 1;
		u8 *pwBuf = (u8 *)malloc(nSendLen+2);
		memset(pwBuf,0,nSendLen+2);
		UnicodeTransform(pwBuf,buf+1,nSendLen);
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_4,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;

	}
	else
	{
		int nSendLen = (len-1) * 2;
		u8 *pwBuf = (u8 *)malloc(nSendLen + 2);
		memset(pwBuf,0,nSendLen);
		ansi_str_to_unicode16(buf+1, (unicode16_t*)pwBuf);
		setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_4,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
}

void Get_Sync_Char_Button1(u8 *param,int len){
	if(param == NULL || len <= 0){
		setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_1,(u8*)"",0);
		return;
	}
	
	setDigitalData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_1,param[1]);
	
	if(param[0] == 1){
		if(param[2] == 0xcf){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_1, STRINGID_SYNC_MENU_PAUSE);
		}
		else if(param[2] == 0xD0){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_1, STRINGID_SYNC_MENU_PLAY);
		}
		else if(param[2] == 0x12){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_1, STRINGID_SYNC_MENU_MUTE);
		}
		else{
			int nSendLen = len - 2;
			u8 *pwBuf = (u8 *)malloc(nSendLen+2);
			memset(pwBuf,0,nSendLen+2);
			UnicodeTransform(pwBuf,param+2,nSendLen);
			setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_1,pwBuf,nSendLen);
			free(pwBuf);
			pwBuf = NULL;
		}
	}
	else{
		int nSendLen = (len - 2) * 2;
		u8 *pwBuf = (u8 *)malloc(nSendLen + 2);
		memset(pwBuf,0,nSendLen);
		ansi_str_to_unicode16(param + 2, (unicode16_t*)pwBuf);
		setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_1,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
}

void Get_Sync_Char_Button2(u8 *param,int len){
	if(param == NULL || len <= 0){
		setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_2,(u8*)"",0);
		return;
	}

	setDigitalData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_2,param[1]);
	if(param[0] == 1){
		if(param[2] == 0xcf){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_2, STRINGID_SYNC_MENU_PAUSE);
		}
		else if(param[2] == 0xD0){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_2, STRINGID_SYNC_MENU_PLAY);
		}
		else if(param[2] == 0x12){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_2, STRINGID_SYNC_MENU_MUTE);
		}
		else{
			int nSendLen = len - 2;
			u8 *pwBuf = (u8 *)malloc(nSendLen+2);
			memset(pwBuf,0,nSendLen+2);
			UnicodeTransform(pwBuf,param+2,nSendLen);
			setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_2,pwBuf,nSendLen);
			free(pwBuf);
			pwBuf = NULL;
		}
	}
	else{
		int nSendLen = (len - 2) * 2;
		u8 *pwBuf = (u8 *)malloc(nSendLen + 2);
		memset(pwBuf,0,nSendLen);
		ansi_str_to_unicode16(param + 2, (unicode16_t*)pwBuf);
		setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_2,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
}

void Get_Sync_Char_Button3(u8 *param,int len){
	if(param == NULL || len <= 0){
		setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_3,(u8*)"",0);
		return;
	}
		
	setDigitalData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_3,param[1]);
	if(param[0] == 1){
		if(param[2] == 0xcf){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_3, STRINGID_SYNC_MENU_PAUSE);
		}
		else if(param[2] == 0xD0){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_3, STRINGID_SYNC_MENU_PLAY);
		}
		else if(param[2] == 0x12){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_3, STRINGID_SYNC_MENU_MUTE);
		}
		else{
			int nSendLen = len - 2;
			u8 *pwBuf = (u8 *)malloc(nSendLen+2);
			memset(pwBuf,0,nSendLen+2);
			UnicodeTransform(pwBuf,param+2,nSendLen);
			setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_3,pwBuf,nSendLen);
			free(pwBuf);
			pwBuf = NULL;
		}
	}
	else{
		int nSendLen = (len - 2) * 2;
		u8 *pwBuf = (u8 *)malloc(nSendLen + 2);
		memset(pwBuf,0,nSendLen);
		ansi_str_to_unicode16(param + 2, (unicode16_t*)pwBuf);
		setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_3,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
	
}

void Get_Sync_Char_Button4(u8 *param,int len){
	if(param == NULL || len <= 0)
	{
		setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_4,(u8*)"",0);
		return;
	}

	setDigitalData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_4,param[1]);
	if(param[0] == 1){
		if(param[2] == 0xcf){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_4, STRINGID_SYNC_MENU_PAUSE);
		}
		else if(param[2] == 0xD0){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_4, STRINGID_SYNC_MENU_PLAY);
		}
		else if(param[2] == 0x12){
			setStringText(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_4, STRINGID_SYNC_MENU_MUTE);
		}
		else{
			int nSendLen = len - 2;
			u8 *pwBuf = (u8 *)malloc(nSendLen+2);
			memset(pwBuf,0,nSendLen+2);
			UnicodeTransform(pwBuf,param+2,nSendLen);
			setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_4,pwBuf,nSendLen);
			free(pwBuf);
			pwBuf = NULL;
		}
	}
	else{
		int nSendLen = (len - 2) * 2;
		u8 *pwBuf = (u8 *)malloc(nSendLen + 2);
		memset(pwBuf,0,nSendLen);
		ansi_str_to_unicode16(param + 2, (unicode16_t*)pwBuf);
		setSerialData(CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_4,pwBuf,nSendLen);
		free(pwBuf);
		pwBuf = NULL;
	}
	
}

void LeaveSyncMedia(){
    //if(pLocalParam->c_ByMediaState != 0x00)
    //{
        pLocalParam->c_ByMediaState = 0x00;
    	syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_OUT_SYNCMEDIA);
	//}
	SendSYNCInfoToOSDDebug();
}

void EnterSync(){
	//if(pLocalParam->c_ByMediaState != 0x01)
	//{
	    pLocalParam->c_ByMediaState = 0x01;
		syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_GOIN_SYNCMEDIA);	
	//}
}

void Get_CurSelectLine(u8 line){
	LOGD("Get_CurSelectLine line:%x",line);
	setUpdateUI(0);
	setDigitalData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_1,0);
	setDigitalData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_2,0);
	setDigitalData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_3,0);
	setDigitalData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_4,0);

	switch(line)
	{
		case 1:
			setDigitalData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_1,1);
			break;
		case 2:
			setDigitalData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_2,1);
			break;
		case 3:
			setDigitalData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_3,1);
			break;
		case 4:
			setDigitalData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_4,1);
			break;
	}
	
	setUpdateUI(1);
	
}

bool WhetherThePageCanSwitchChannels(u16 PageID)
{
	switch(PageID)
	{
		case PAGE_GPS_PAGE: 
		case PAGE_THIRD_PAGE:
		case PAGE_COPYRIGHT: 
		case PAGE_EQ: 
		case PAGE_SOUND:
		case PAGE_AUDIO_SET_BOX:
		case PAGE_SYSTEM_STYLE: 
		case PAGE_SYSTEM_WHEEL_LEARNING: 
		case PAGE_TPMS:
		case PAGE_TPMS_EXSET: 
		case PAGE_TPMS_SET: 
		case PAGE_RADIO_NUMBER:
		case PAGE_AIRCONDITION: 
		case PAGE_AUX: 
		case PAGE_BLCD: 
		case PAGE_BLUETOOTH_NO_A2DP:
		case PAGE_DRIVING_RECORD_NO_SIGN:
		case PAGE_TV_NO_VIDEO: 
		case PAGE_TRAVEL_INFORMATION:
		case PAGE_TRAVEL_INFORMATION_HISTORICAL_RECORD: 
		case PAGE_TRAVEL_INFORMATION_CAR_SET1: 
		case PAGE_BLUETOOTH_MAIN: 
		case PAGE_BLUETOOTH_MOBILE_RECORD: 
		case PAGE_BLUETOOTH_RECORD:
		case PAGE_BLUETOOTH_AUDIOVOX_CODE:
        case PAGE_BLUETOOTH_AUDIOVOX_PAIR_FALSE:
        case PAGE_BLUETOOTH_AUDIOVOX_SEARCH:
        case PAGE_BLUETOOTH_AUDIOVOX_CONTACTS:
        case PAGE_BLUETOOTH_AUDIOVOX_BEYBOARD:
        case PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME:
        case PAGE_BLUETOOTH_AUDIOVOX_PAIR_SETTING:
        case PAGE_BLUETOOTH_AUDIOVOX_BTNAME_EDITOR:
        case PAGE_BLUETOOTH_AUDIOVOX_KEYBOARD_HEBREW:
        case PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_EGLISH:
        case PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_ISRAEL:
			return true;
		break;
		default:
		if(PageID >=PAGE_SETUP_BEGIN && PageID <= PAGE_SETUP_END){
			return true;
		}
		else if(PageID >=PAGE_GOLF_DRIVING_DATA && PageID <= PAGE_GOLF_SETUP_FACTORY_SETTINGS_NEXT)
		{
		    return true;
		}
		break;
	}

	
	return false;
}

void Get_Sync_Aux_State(unsigned char State){//获取SYNC media状态
	u16 CurPageID = 0;
	u8	CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
	u16 PrePageID = 0;
	u8	PrePageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,PREV_PAGE,(u8*)&PrePageID,&PrePageIDLen);
	LOGD("Get_Sync_Aux_State State:%x CurPageID:%x  PrePageID:%x",State,CurPageID,PrePageID);
	if(State == 0x01){
		//if(!pLocalParam->b_SyncAble)
		//	return;
		if(CurPageID != PAGE_SYNV_MENU && CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_NOVIDEO &&  
			CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)//倒车的时候不能切页
			syncToModule_NotifySystem_JumpPage(PAGE_SYNV_MENU);
		pLocalParam->c_ByMediaState = State;
		SendSYNCInfoToOSDDebug();
	}
	else if(State == 0x02){
		LeaveSyncMedia();

		if(CurPageID != PAGE_BACK_NOVIDEO && CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)//倒车的时候不能切页
		{
			if(PrePageID == PAGE_BACK_VIDEO)
			{
				PrePageID = PAGE_MENU;
				syncToModule_NotifySystem_JumpPage(PrePageID);
				return;
			}
			else if(PrePageID == PAGE_STANDBY && !pLocalParam->b_BtCallState)
			{
				PrePageID = PAGE_MENU;
				Set_Sound_PreChannel();
				syncToModule_NotifySystem_JumpPage(PrePageID);
				return;
			}

			if(WhetherThePageCanSwitchChannels(PrePageID))/*例如:在DVD,切到导航，然后方控语音，语音播报完返回前一页GPS，继续播放DVD*/
			{
				if(pLocalParam->m_iSoundChannel == 0x05)
					Set_Sound_PreChannel();
			}

			syncToModule_NotifySystem_jumpPrePage();
		}
	}
}

void Get_Sync_State(u8 State){
	LOGD("Get_Sync_State State:%x c_ByMediaState:%x",State,pLocalParam->c_ByMediaState);
	pLocalParam->m_bSpeech_ButtonValue=State;
	switch(State)
	{
	case 0x00:
		if (pLocalParam->c_ByMediaState == 0x01)
		{
			u16 CurPageID = 0;
        	u8	CurPageIDLen = 0;
        	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
        	LOGD("EnterSync CurPageID:%x pLocalParam->c_ByMediaState:%x",CurPageID,pLocalParam->c_ByMediaState);
        	if(CurPageID != PAGE_SYNV_MENU && CurPageID != PAGE_BACK_NOVIDEO && CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)//倒车的时候不能切页
		        syncToModule_NotifySystem_JumpPage(PAGE_SYNV_MENU);
		        
			//EnterSync();
		}
		break;
	case 0x01:
		if (pLocalParam->c_ByMediaState == 0x00)
		{
			//LeaveSyncMedia();
		}
		break;
	case 0x02:
	case 0x03:
	    {
	    	u16 CurPageID = 0;
        	u8	CurPageIDLen = 0;
        	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
        	LOGD("EnterSync CurPageID:%x pLocalParam->c_ByMediaState:%x",CurPageID,pLocalParam->c_ByMediaState);
        	if(CurPageID != PAGE_SYNV_MENU && CurPageID != PAGE_BACK_NOVIDEO && CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)//倒车的时候不能切页
		        syncToModule_NotifySystem_JumpPage(PAGE_SYNV_MENU);
		        
		    //EnterSync();
		}
		break;
		default:break;
	}

}

void Get_Several_Sign_Stat(unsigned short Value){
	//BYTE(1):
	u8 State = 0;
	State = Value & 0x00ff;
	u16 isLightOut = 0;

	/*if(!pLocalParam->b_SyncAble){
		pLocalParam->b_SyncAble = true;
	}*/
	
	isLightOut = (State & 0x01) ? 1 : 0;
	//LOGD("CONTROLIDTRAVEL_SYNV_SYNC_ICO isLightOut:%x",isLightOut);
	setDigitalData(CONTROLIDTRAVEL_SYNV_SYNC_ICO,int(isLightOut));

	isLightOut = (State & 0x02) ? 1 : 0;
	//LOGD("CONTROLIDTRAVEL_SYNV_BLUETOOTH_ICO isLightOut:%x",isLightOut);
	setDigitalData(CONTROLIDTRAVEL_SYNV_BLUETOOTH_ICO,int(isLightOut));
	syncToModule_NotifyCenter_SyncState((u8)isLightOut);
	
	isLightOut = (State & 0x04) ? 1 : 0;
	//LOGD("CONTROLIDTRAVEL_SYNV_NOTE_ICO isLightOut:%x",isLightOut);
	setDigitalData(CONTROLIDTRAVEL_SYNV_NOTE_ICO,int(isLightOut));

	isLightOut = (State & 0x08) ? 1 : 0;
	//LOGD("CONTROLIDTRAVEL_SYNV_MICROPHONE_ICO isLightOut:%x",isLightOut);
	setDigitalData(CONTROLIDTRAVEL_SYNV_MICROPHONE_ICO,int(isLightOut));
	
	isLightOut = (State & 0x10) ? 1 : 0;
	//LOGD("CONTROLIDTRAVEL_SYNV_CALL_ICO isLightOut:%x",isLightOut);
	setDigitalData(CONTROLIDTRAVEL_SYNV_CALL_ICO,int(isLightOut));
	
	isLightOut = (State & 0x20) ? 1 : 0;
	//LOGD("CONTROLIDTRAVEL_SYNV_INFO_ICO isLightOut:%x",isLightOut);
	setDigitalData(CONTROLIDTRAVEL_SYNV_INFO_ICO,int(isLightOut));
	
	//BYTE(2):
	State = (Value & 0xff00)>>8;
	u16 length = 0 ;

	length = State & 0x0f; /*信号图标*/
	//LOGD("CONTROLIDTRAVEL_SYNV_SIGNAL_ICO length:%x",length);
	if(length > 4){/*不显示*/
		setVisible(CONTROLIDTRAVEL_SYNV_SIGNAL_ICO,false);
	}
	else{
		setVisible(CONTROLIDTRAVEL_SYNV_SIGNAL_ICO,true);
		setAnalogData(CONTROLIDTRAVEL_SYNV_SIGNAL_ICO,(int)length);
	}

	length = (State & 0xf0) >> 4;/*电量图标*/
	//LOGD("CONTROLIDTRAVEL_SYNV_BATTERY_ICO length:%x",length);
	if(length > 4){/*不显示*/
		setVisible(CONTROLIDTRAVEL_SYNV_BATTERY_ICO,false);
	}
	else{
		setVisible(CONTROLIDTRAVEL_SYNV_BATTERY_ICO,true);
		setAnalogData(CONTROLIDTRAVEL_SYNV_BATTERY_ICO,(int)length);
	}
	
}

void Get_BtCallState(u8 State){
	pLocalParam->b_BtCallState = State;
	LOGD("Get_BtCallState pLocalParam->b_BtCallState:%x",State);
	syncToModule_NotifyOtherModule_BtCallState(MODULE_ID_KEY,State);

	u16 CurPageID = 0;
	u8	CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
	if(State == 0x01)
	{
		u8 ucBackMode = 0;
		u8 ucBackModeLen = 0;
		getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,&ucBackModeLen);
		LOGD("Get_BtCallState ucBackMode:%d" ,ucBackMode);
		if(ucBackMode == 0x00) //do not back car
		{
    		LOGD("Get_BtCallState CurPageID:%x",CurPageID);
    		if(CurPageID != PAGE_SYNV_MENU && CurPageID != PAGE_BACK_NOVIDEO && CurPageID != PAGE_BACK_VIDEO)
    		{
    			pLocalParam->bAutoJumpPrePage = true;
    		}
		}
		else
		{
			pLocalParam->bAutoJumpPrePage = false;
		}
	}
	else if(State == 0x00)
	{
		if(pLocalParam->bAutoJumpPrePage == true)
		{
			pLocalParam->bAutoJumpPrePage = false;
			LOGD("Get_BtCallState CurPageID:%x",CurPageID);
			if(CurPageID == PAGE_SYNV_MENU)
				syncToModule_NotifySystem_jumpPrePage();
	    }
	}
	
	SendSYNCInfoToOSDDebug();
}

void Get_USB_PlayTime(u8 ucMinute,u8 ucSeconds){
	unsigned char ucHour = ucMinute / 60;
	unsigned char ucMin = ucMinute % 60;
	unsigned char ucSec = ucSeconds % 60;

	u8 buffer[32];
	u8 realBuffer[160];
	int bufferLen;
	u8 *pRealBuf;

	memset(buffer,0x00,32);
	memset(realBuffer,0x00,160);
	sprintf((char *)buffer,"%d:%02d:%02d",ucHour,ucMin,ucSec);
	bufferLen = ansi_str_to_unicode16(buffer,(unicode16_t *) realBuffer);
	setSerialData(CONTROLIDTRAVEL_SYNV_DISPLAY_TEXT_4,realBuffer,bufferLen * 2);
}

void Get_LeaveSyncPage(){
	u16 CurPageID = 0;
	u8	CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
	LOGD("Get_LeaveSyncPage  CurPageID:%x",CurPageID);
	if(CurPageID != PAGE_BACK_NOVIDEO&& CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)
		syncToModule_NotifySystem_JumpPage(PAGE_MENU);
}

void InitConfig_Visible_setup()
{
    setVisible(CONTROLIDTRAVEL_SYNC_SETUP_1,0);
    setVisible(CONTROLIDTRAVEL_SYNC_SETUP_2,0);
    setVisible(CONTROLIDTRAVEL_SYNC_SETUP_3,0);
    setVisible(CONTROLIDTRAVEL_SYNC_SETUP_4,0);
}

void Get_CheckBoxDisplaying(char cmd,u8 param)
{
    /*0x00 无勾选框及圆形选择框
    0x01 有勾选框 没勾选
    0x02 有勾选框 已勾选
    0x03 有圆形选择框 没选中
    0x04 有圆形选择框 已选*/

    switch(cmd)
    {
        case 0x20:// 2 line,setup
            if(param == 1)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_1,2);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_1,1);
            }
            else if(param == 2)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_1,3);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_1,1);
            }
            else if(param == 3)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_1,0);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_1,1);
            }
            else if(param == 4)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_1,1);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_1,1);
            }
            else
            {
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_1,0);
            }
            break;
		case 0x21:// 3 line,setup
    		if(param == 1)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_2,2);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_2,1);
            }
            else if(param == 2)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_2,3);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_2,1);
            }
            else if(param == 3)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_2,0);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_2,1);
            }
            else if(param == 4)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_2,1);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_2,1);
            }
            else
            {
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_2,0);
            }
        break;
		case 0x22:// 4 line,setup
    		if(param == 1)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_3,2);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_3,1);
            }
            else if(param == 2)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_3,3);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_3,1);
            }
            else if(param == 3)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_3,0);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_3,1);
            }
            else if(param == 4)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_3,1);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_3,1);
            }
            else
            {
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_3,0);
            }
        break;
		case 0x23:// 5 line,setup
    		if(param == 1)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_4,2);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_4,1);
            }
            else if(param == 2)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_4,3);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_4,1);
            }
            else if(param == 3)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_4,0);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_4,1);
            }
            else if(param == 4)
            {
                setAnalogData(CONTROLIDTRAVEL_SYNC_SETUP_4,1);
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_4,1);
            }
            else
            {
                setVisible(CONTROLIDTRAVEL_SYNC_SETUP_4,0);
            }
        break;
    }
}


void Get_Ford_Steer_MouseKey(u8 uParam)
{
	/*0x00   OK
		0x01   Up
		0x02   Down
		0x03   left
		0x04   right*/
}

void Get_Ford_NewModels_OriginalCarPanelKeyButtons(u8 uParam1,u8 uParam2)
{
    /*
    BYTE(1) 按键按下时长（1－4）
           1为最短，松开时为0
    BYTE(1)
    0x00  松开（未按按键）
    0x01  CD
    0x02  收音
    0x03  AUX
    0x04  PHONE
    0x05  MENU
    0x06  出碟
    0x07  四个空白键 最左
    0x08  四个空白键 左中
    0x09  四个空白键 右中
    0x0A  四个空白键 最右
    0x0B  上一曲、接电话
    0x0C  下一曲、挂电话
    0x0D  方向键 左
    0x0E  方向键 下
    0x0F  方向键 右
    0x10  方向键 上
    0x11  方向键 OK
    0x12  INFO键
    0x13  TA键
    0x14  音符图标键
    0x15  数字键1
    0x16  数字键2
    0x17  数字键3
    0x18  数字键4
    0x19  数字键5
    0x1A  数字键6
    0x1B  数字键7
    0x1C  数字键8
    0x1D  数字键9
    0x1E  数字键0
    0x1F  数字键*
    0x20  数字键#
    0x21  POWER
    */

    LOGD("steer key uParam1,uParam2:%x %x ",uParam1,uParam2);
    switch(uParam2)
    {
        case 0x00:
        break;
        case 0x01://CD
            syncToModule_NotifySystem_JumpPage(PAGE_DVD_MAIN);
        break;
        case 0x02://RADIO
            syncToModule_NotifySystem_JumpPage(PAGE_RADIO_MAIN);
        break;
        case 0x03://AUX
            syncToModule_NotifySystem_JumpPage(PAGE_AUX);
        break;
        case 0x04://PHONE
        break;
        case 0x05://MENU
        break;
        case 0x06://open disc
        break;
        case 0x07:
        case 0x08:
        case 0x09:
        case 0x0A:
        case 0x0B:
        case 0x0C:
        case 0x0D:
        case 0x0E:
        case 0x0F:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x21:
        break;
    }

}

static int nJoinInputPhNumPage = 0;
void sync_TextFilesAndTextButtonsData(u8 *param,int len)
{
	char cSyncSecondLineText_aboutInputPhNumPage_Unicode[]={0X01,0X01, 0X8F, 0X93, 0X51, 0X65, 0X75, 0X35, 0X8B, 0XDD, 0X53, 0XF7, 0X78, 0X01, 0X00, 0X00};
	if(param[0] == 0x01)
	{
			if(param[1] == 1)
			{
					if(memcmp(cSyncSecondLineText_aboutInputPhNumPage_Unicode,param,16) == 0)
					{
						//LOGD("cSyncSecondLineText_aboutInputPhNumPage_Unicode nJoinInputPhNumPage:%d",nJoinInputPhNumPage);
						++nJoinInputPhNumPage;
					}
					else
					{
						nJoinInputPhNumPage = 0;
					}
				}
			else if(param[1] == 0)
			{
			}
	}
	
	switch(param[0])
	{
		case 0x00:/*文本标题*/
		case 0x01:/*文本第2行*/
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:/*功能文本按钮*/
		case 0x06:
		case 0x07:
		case 0x08:
		case 0x20:// 2 line,setup
		case 0x21:// 3 line,setup
		case 0x22:// 4 line,setup
		case 0x23:// 5 line,setup
			//LOGD("11 nJoinInputPhNumPage:%d",nJoinInputPhNumPage);
			if(nJoinInputPhNumPage > 1)return;
		break;
		default:break;
	}

	switch(param[0])
	{
		case 0x00:/*文本标题*/
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1,&pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1,pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1_len;
			//ToPrintMessage("sync_TextFilesAndTextButtonsData 1pre:",(const char *)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1,(const int)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1_len);
			
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1,param,len);
			pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1_len = len;
			//ToPrintMessage("sync_TextFilesAndTextButtonsData 1cur:",(const char *)pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1,(const int)pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1_len);
		break;
		case 0x01:/*文本第一行*/
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2,&pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2,pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2_len;
			//ToPrintMessage("sync_TextFilesAndTextButtonsData 2pre:",(const char *)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2,(const int)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2_len);

			pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2,param,len);
			//ToPrintMessage("sync_TextFilesAndTextButtonsData 2cur:",(const char *)pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2,(const int)pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2_len);
		break;
		case 0x02:
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3,&pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3,pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3_len;

			pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3,param,len);
		break;
		case 0x03:
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4,&pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4,pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4_len;

			pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4,param,len);
		break;
		case 0x04:
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5,&pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5,pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5_len;

			pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5,param,len);
		break;
		case 0x05:/*功能文本按钮*/
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1,&pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1,pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1_len;

			pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1,param,len);
		break;
		case 0x06:
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2,&pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2,pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2_len;

			pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2,param,len);
		break;
		case 0x07:
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3,&pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3,pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3_len;

			pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3,param,len);
		break;
		case 0x08:
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4,&pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4,pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4_len;

			pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4,param,len);
		break;
		case 0x20:// 2 line,setup
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2,&pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2,pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2_len;

			pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2,param,len);
		break;
		case 0x21:// 3 line,setup
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3,&pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3,pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3_len;

			pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3,param,len);
		break;
		case 0x22:// 4 line,setup
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4,&pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4,pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4_len;

			pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4,param,len);
		break;
		case 0x23:// 5 line,setup
			memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5,&pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5,pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5_len);
			pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5_len;

			pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5,param,len);
		break;
		default:break;
	}
}

void sync_5files_4buttonsinfor_back(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:/*文本标题*/
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1,param,len);
			pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1_len = len;
			ToPrintMessage("sync_5files_4buttonsinfor 1cur:",(const char *)pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1,(const int)pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1_len);

			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1,pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1,pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1_len;
			ToPrintMessage("sync_5files_4buttonsinfor 1pre:",(const char *)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1,(const int)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1_len);
		break;
		case 0x01:/*文本第一行*/
			pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2,param,len);
			ToPrintMessage("sync_5files_4buttonsinfor 2cur:",(const char *)pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2,(const int)pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2_len);
			
			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2,&pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2,pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2_len;
			ToPrintMessage("sync_5files_4buttonsinfor 2pre:",(const char *)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2,(const int)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2_len);
		break;
		case 0x02:
			pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3,param,len);
			
			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3,&pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3,pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3_len;
		break;
		case 0x03:
			pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4,param,len);

			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4,&pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4,pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4_len;
		break;
		case 0x04:
			pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5,param,len);

			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5,&pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5,pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5_len;
		break;
		case 0x05:/*功能文本按钮*/
			pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1,param,len);

			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1,&pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1,pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1_len;
		break;
		case 0x06:
			pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2,param,len);

			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2,&pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2,pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2_len;
		break;
		case 0x07:
			pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3,param,len);

			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3,&pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3,pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3_len;
		break;
		case 0x08:
			pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4,param,len);

			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4,&pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4,pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4_len;
		break;
		case 0x20:// 2 line,setup
			pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2,param,len);

			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2,&pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2,pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2_len;
		break;
		case 0x21:// 3 line,setup
			pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3,param,len);

			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3,&pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3,pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3_len;
		break;
		case 0x22:// 4 line,setup
			pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4,param,len);

			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4,&pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4,pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4_len;
			break;
		case 0x23:// 5 line,setup
			pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5_len = len;
			memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5,0,FILE_SYNC_TEXT_MAX_LEN);
			memcpy(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5,param,len);

			//memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5,0,FILE_SYNC_TEXT_MAX_LEN);
			//memcpy(&pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5,&pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5,pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5_len);
			//pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5_len = pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5_len;
		break;
		default:break;
	}
}

void Get_ShowPreText(u8 State){
	if(State == 1)
	{
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1,pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1_len);
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2,pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2_len );
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3,pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3_len );
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4,pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4_len );
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5,pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5_len );
		
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1,pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1_len);
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2,pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2_len);
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3,pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3_len);
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4,pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4_len);
		
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2,pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2_len);
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3,pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3_len);
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4,pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4_len);
		analyseData_CarType_NEW_FOCUS((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5,pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5_len);

		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1,pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1_len);
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2,pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2_len);
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3,pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3_len);
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4,pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4_len);
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5,pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5_len);
		
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1,pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1_len);
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2,pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2_len);
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3,pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3_len);
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4,pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4_len);
		
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2,pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2_len);
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3,pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3_len);
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4,pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4_len);
		sync_5files_4buttonsinfor_back((u8*)pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5,pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5_len);


	}
}

void analyseData_CarType_NEW_FOCUS(u8 *param, u8 len){
	char resCmd = param[0];
	switch(resCmd)
	{
		case 0x00:/*文本标题*/
			Get_Sync_Title(param + 1,len - 1);
		break;
		case 0x01:/*文本第一行*/
			Get_Sync_String_OneLine(param + 1,len - 1);
		break;
		case 0x02:
			Get_Sync_String_TwoLine(param + 1,len - 1);
		break;
		case 0x03:
			Get_Sync_String_ThreeLine(param + 1,len - 1);
		break;
		case 0x04:
			Get_Sync_String_FourLine(param + 1,len - 1);
		break;
		case 0x05:/*功能文本按钮*/
			Get_Sync_Char_Button1(param + 1,len - 1);
		break;
		case 0x06:
			Get_Sync_Char_Button2(param + 1,len - 1);
		break;
		case 0x07:
			Get_Sync_Char_Button3(param + 1,len - 1);
		break;
		case 0x08:
			Get_Sync_Char_Button4(param + 1,len - 1);
		break;
		case 0x09:/*获取Sync Media状态*/
			Get_Sync_Aux_State(param[1]);
		break;
		case 0x0A:/*获取选中哪一行*/
			Get_CurSelectLine(param[1]);
		break;
		case 0x0B:/*各种指示图标状态*/
		{
			unsigned short Value = param[1]+ (param[2]<<8);
			Get_Several_Sign_Stat(Value);
		}
		break;
		case 0x0c:
			Get_ShowPreText(param[1]);	
		break;
		case 0x0d://获取蓝牙通话状态
			Get_BtCallState(param[1]);
		break;
		case 0x0e:/*获取sync状态*/
			Get_Sync_State(param[1]);
		break;

		case 0x10:
			Get_USB_PlayTime(param[1],param[2]);
		break;
		case 0x11://steer mouse,left key ,jump sync page
			Get_LeaveSyncPage();
		break;

		case 0x20:// 2 line,setup
		case 0x21:// 3 line,setup
		case 0x22:// 4 line,setup
		case 0x23:// 5 line,setup
		    Get_CheckBoxDisplaying(resCmd,param[1]);
		break;
		case 0x24://Battery power symbol
		break;
		case 0x25://Signal strength symbol
		break;
		case 0x26://in Standby,calling status
		break;
		case 0x27://steer mouse key
			Get_Ford_Steer_MouseKey(param[1]);
		break;
		case 0x30://key
		    Get_Ford_NewModels_OriginalCarPanelKeyButtons(param[1],param[2]);/*EcoSport、Fiesta*/
		break;
		default:break;
	}
}

void analyseHalMessage_CarType_NEW_FOCUS(u8 *param, u8 len){
	ToPrintMessage("GetHALSYNC:",(const char *)param,(const int)len);
	//LOGD("Hal To Module SYNC: %02X, %02X len:%d", param[0], param[1],len);
	sync_TextFilesAndTextButtonsData(param,(int)len);
	analyseData_CarType_NEW_FOCUS(param,len);
}



void analyseHalMessage_SYNC(unsigned char resCmd, unsigned char *param, unsigned char len){
	LOGD("HAL MSG(cmd1+cmd2+param):%02X %02X %02X %02X %02X", resCmd, param[0],param[1],param[2],param[3]);
	switch(resCmd){
		default:break;
	}
}






