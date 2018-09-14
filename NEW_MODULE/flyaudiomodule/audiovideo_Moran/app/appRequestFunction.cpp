#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"

void AudioVideoToApp_SetCameraIsReady(void){
	LOGW("bIsVideoOpen:%d, bIsRetrySendCameraReady:%d",pLocalParam->bIsVideoOpen,pLocalParam->bIsRetrySendCameraReady);
	if(pLocalParam->bIsVideoOpen){
		setCamaraReadyForOpen(true);
		pLocalParam->bIsRetrySendCameraReady = false;
	}
	else{
		setCamaraReadyForOpen(false);
		pLocalParam->bIsRetrySendCameraReady = true;
	}
}


void appToAudiovideo_DisplayMenuTitle(int nSoundvideoChannel){

	switch(nSoundvideoChannel)
	{
		case CHANNEL_NOCHANNEL://  0xFF//不在任何通道，初始化值，及睡眠时 CHANNEL_DVD_CTRL
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVD_CTRL,true);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_IPOD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_CDC_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_TV_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_RADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_SRADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_MP3,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_AUX_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVR_CTRL,false);
			break;
		case CHANNEL_DVD_CTRL://   0x00// (控制界面)
		case CHANNEL_DVD_VIDEO://  0x01//（视频界面）
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVD_CTRL,true);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_IPOD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_CDC_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_TV_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_RADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_SRADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_MP3,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_AUX_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVR_CTRL,false);
			break;
		case CHANNEL_CDC_CTRL://   0x02//（控制界面）
		case CHANNEL_CDC_VIDEO://  0x03//（视频界面）
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_IPOD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_CDC_CTRL,true);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_TV_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_AUX_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_RADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_SRADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_MP3,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVR_CTRL,false);
			break;
		case CHANNEL_RADIO://	   0x04//（控制界面）
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_IPOD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_CDC_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_TV_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_AUX_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_RADIO,true);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_SRADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_MP3,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVR_CTRL,false);
			break;
		case CHANNEL_AUX_CTRL://   0x05
		case CHANNEL_AUX_VIDEO://  0x06
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_IPOD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_CDC_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_TV_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_AUX_CTRL,true);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_RADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_SRADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_MP3,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVR_CTRL,false);
			break;
		case CHANNEL_IPOD_CTRL://  0x07
		case CHANNEL_IPOD_VIDEO:// 0x08
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_IPOD_CTRL,true);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_CDC_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_TV_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_AUX_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_RADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_SRADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_MP3,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVR_CTRL,false);
			break;
		//case CHANNEL_TV_CTRL://	 0x09
		case CHANNEL_TV_VIDEO://   0x0A
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_IPOD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_CDC_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_TV_CTRL,true);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_AUX_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_RADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_SRADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_MP3,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVR_CTRL,false);
			break;
		case CHANNEL_MP3:// 	   0x0B  
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_IPOD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_CDC_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_TV_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_AUX_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_RADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_SRADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_MP3,true);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVR_CTRL,false);
			break;
		case CHANNEL_SRADIO://	   0x0C
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_IPOD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_CDC_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_TV_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_AUX_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_RADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_SRADIO,true);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_MP3,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVR_CTRL,false);
			break;
		case CHANNEL_DVR_CTRL:
		case CHANNEL_DVR_VIDEO:
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_IPOD_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_CDC_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_TV_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_AUX_CTRL,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_RADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_SRADIO,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_MP3,false);
			appToAudiovideo_DisplayTitleInfo(CHANNEL_DVR_CTRL,true);
			break;
		default:break;
	}
}

void appToAudiovideo_DisplayTitleInfo(int iChannel,int iVisible){

	setUpdateUI(false);
	switch(iChannel)
	{
	case CHANNEL_DVD_CTRL:
	case CHANNEL_DVD_VIDEO:
		//setVisible(FUNCID_DVD_IMG_MENU_TITLE,iVisile);
		//setVisible(FUNCID_DVD_BTN_MENU_TYPE,iVisile);
		setVisible(CONTROLID_DVD_MAIN_TITLE_TEXT, iVisible);//setVisible(FUNCID_DVD_BTN_MENU_TITLE_TXT,iVisile);
		setVisible(CONTROLID_DVD_MAIN_TRACK_TEXT, iVisible);//setVisible(FUNCID_DVD_BTN_MENU_TRACK_TXT,iVisile);
		setVisible(CONTROLID_DVD_MAIN_CURRENT_TIME, iVisible);//setVisible(FUNCID_DVD_BTN_MENU_TIME,iVisile);
		setVisible(CONTROLID_DVD_MAIN_CURRENT_TITLE_NUM, iVisible);//setVisible(FUNCID_DVD_BTN_MENU_TITLE,iVisile);
		setVisible(CONTROLID_DVD_MAIN_CURRENT_TRACK_NUM, iVisible);//setVisible(FUNCID_DVD_BTN_MENU_TRACK,iVisile);
		//setVisible(FUNCID_DVD_BTN_MENU_STATE,iVisile);
		break;
	case CHANNEL_RADIO:
		//setVisible(FUNCID_RADIO_BTN_MENU_TITLE,iVisile);
		//setVisible(FUNCID_RADIO_BTN_MENU_DISPLAY,iVisile);
		//setVisible(FUNCID_RADIO_BTN_MENU_CHANNELS_INFO,iVisile);
		break;
	case CHANNEL_MP3:
		//setVisible(FUNCID_MP3_REF_IMG_TITLE,iVisile);
		//setVisible(FUNCID_MP3_REF_TEXT_TRACKVALUE,iVisile);
		//setVisible(FUNCID_MP3_REF_TEXT_TRACK,iVisile);
		//setVisible(FUNCID_MP3_REF_TEXT_STREAMTIME,iVisile);
		//setVisible(FUNCID_MP3_REF_TEXT_TYPE,iVisile);
		break;
	case CHANNEL_IPOD_VIDEO:
	case CHANNEL_IPOD_CTRL:
		//setVisible(FUNCID_IPOD_BTN_MENU_TITLE,iVisile);
		//setVisible(FUNCID_IPOD_BTN_MENU_TRACK_TXT,iVisile);
		//setVisible(FUNCID_IPOD_BTN_MENU_TRACK,iVisile);
		//setVisible(FUNCID_IPOD_BTN_MENU_time,iVisile);
		break;
	case CHANNEL_SRADIO:
		break;
	case CHANNEL_TV_CTRL:
	case CHANNEL_TV_VIDEO:
		//setVisible(FUNCID_TV_PICTURE_TITLE,iVisile);
		break;
	case CHANNEL_AUX_CTRL:
	case CHANNEL_AUX_VIDEO:
		//setVisible(FUNCID_AUX_REF_IMG_TITLE,iVisile);
		break;
	}
	setUpdateUI(true);
}


void appToAudiovideo_Display_SubOnOFF(){
	if(pLocalParam->subState)
	{
		//Set_Data(FUNCID_AUDIO_BTN_SUB_OFF, false);
		//Set_Data(FUNCID_AUDIO_BTN_SUB_ON, true);
	}
	else
	{
		//Set_Data(FUNCID_AUDIO_BTN_SUB_ON, false);
		//Set_Data(FUNCID_AUDIO_BTN_SUB_OFF, true);
	}
}

void appToAudiovideo_Display_SubFilter(u8 cValue){
	u8 cOldFilterValue = pLocalParam->subFilter;
	u8 cNewFilterValue = cValue;
	//Set_Data(FUNCID_AUDIO_BTN_SUB_FILTER_80+cOldFilterValue, false);
	//Set_Data(FUNCID_AUDIO_BTN_SUB_FILTER_80+cNewFilterValue, true);
	pLocalParam->subFilter = cNewFilterValue;
}

void appToAudio_Display_ScrollSubLevel(){
	u8 cLevelValue = pLocalParam->subLevel;
	//Set_Data(FUNCID_AUDIO_SCROLL_SUB_LEVEL, (short)cLevelValue);
}


// audioToApp_xxx();
