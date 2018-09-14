#include <stdio.h>
#include <stdlib.h>
#include <commonFunc.h>
#include <ctype.h>
#include <string.h>
#include "global.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "paramID.h"
#include "moduleID.h"

#include "moduleParamResponse.h"
#include "halRequestFunction.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"
#include "timer_interface.h"


bool bDoSpecial_ChanceSpeechBack = false;

void setSoundChannelToCtrlMode(void){
	LOGD("--setSoundChannelToCtrlMode---");
	videoToHal_SetVideoChannel(0,0);
}

void moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(u8 param){  //0X0D

	if (param == pLocalParam->m_u8ChannelHaveSetToHal)
	{
		LOGD("[%s] m_u8ChannelHaveSetToHal = [0x%x]", __FUNCTION__, pLocalParam->m_u8ChannelHaveSetToHal);
		return;
	}
	else
	{
	    LOGD("[%s] param = [0x%x]", __FUNCTION__, param);
		pLocalParam->m_u8ChannelHaveSetToHal = param;
	}
	
	//if(pLocalParam->uModuleAudio_is_T123 == 1)
	//{
	//	enterOrExitVideoPreProcess(param);
	//}
	
	int newSoundChannel = -1;
	int newVideoChannel = -1;
    findSoundAndVideoChannel(&newSoundChannel,&newVideoChannel,param);

	LOGD("Set SoundChannel:0x%x,VideoChannel:0x%x.\n",newSoundChannel,newVideoChannel);
	if(newVideoChannel != -1){
		if(newVideoChannel)
			SendVideoChannel_enterOrExitVideoPreProcess(param,newSoundChannel,1); //0
		else
			SendVideoChannel_enterOrExitVideoPreProcess(param,newSoundChannel,0);
	}

	if(newSoundChannel != -1)
	{
		audioToHal_SetSoundChannel(newSoundChannel); //9
	}
	
}

void moduleToAudioVideo_FromSystem_EnterOrLeaveSleep(int bEnter)
{
	int cCurChannel = pLocalParam->soundVideoChannel;

    ///////////////////////////////////////////////////////////////////////////////////
    //In the case of reversing stand, reversing the second and subsequent pages will jump twice.(To T123)
	switch(cCurChannel)
	{
		case CHANNEL_DVD_VIDEO:
			cCurChannel = CHANNEL_DVD_CTRL;
			break;
	}
	moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(cCurChannel);
    ///////////////////////////////////////////////////////////////////////////////////	
    
	if (bEnter)
	{
	   audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(cCurChannel,CHANNEL_NOCHANNEL);
	}
	else
	{	
		audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(cCurChannel,cCurChannel);
	}




}


void moduleToAudioVideo_FromSystem_SetVolume(u8 volume){
	pLocalParam->volumeSet = volume;
}


void moduleToAudioVideo_FromSystem_JumpPageWhenAccOn(void){
}


//wen gps sound on or off
void moduleToAudioVideo_FromSystem_GPSSoundOn(u8 OFF){
	if(OFF == 0){
		pLocalParam->gpsSoundOn = 0;//false
		LOGD("gps_sound_off");
	}else{
		pLocalParam->gpsSoundOn = 1;
		LOGD("gps_sound_on");
	}
}

int PageChange_For_CameraOpen(u16 leavePageID, u16 enterPageID){
	int ret = false;

	switch(enterPageID){
		case PAGE_DVD_VIDEO:
			if((leavePageID == PAGE_DVD_VIDEO_CONTROL) || (leavePageID == PAGE_DVD_VIDEO_SET))
				ret = true;
			break;
		case PAGE_AUX_VIDEO:
			if((leavePageID == PAGE_AUX_VIDEO_CONTROL) || (leavePageID == PAGE_AUX_VIDEO_SET))
				ret = true;
			break;
		case PAGE_TV_VIDEO:
			if((leavePageID == PAGE_TV_VIDEO_CONTROL) || (leavePageID == PAGE_TV_VIDEO_SET))
				ret = true;
			break;
		case PAGE_DRIVING_RECORD_VIDEO:
			if((leavePageID == PAGE_DRIVING_RECORD_MENU) || (leavePageID == PAGE_DRIVING_RECORD_PALY) || (leavePageID == PAGE_DRIVING_RECORD_SET) || (leavePageID == PAGE_DRIVING_RECORD_TIME_SET) || (leavePageID == PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD) || (leavePageID == PAGE_DRIVING_CHANGHE_DVR_SET_OSD))
				ret = true;
			break;
		default:
			ret = false;
			break;
	}

	return ret;
}

int getBackCarMode(void)
{
	u8 m = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_PARAM_ID_BACKMODE, (u8*)&m, &len);

	LOGD("[%s] m = [0x%x]", __FUNCTION__, m);

	return m;
}

void moduleToaudiovideo_FromSystem_PageChange(u16 leavePageID,u16 enterPageID,int PageParam){
	LOGD("[%s] LeavePage:0x%x,EnterPage:0x%x \n",__FUNCTION__,leavePageID,enterPageID);

	switch(leavePageID){
		case PAGE_STANDBY:
			moduleToAudioVideo_FromSystem_EnterOrLeaveSleep(0);
			break; 
		default:break;
	}

	switch(enterPageID){	
		case PAGE_STANDBY:
			moduleToAudioVideo_FromSystem_EnterOrLeaveSleep(true);
			break;
		case PAGE_BLUETOOTH_A2DP:
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_BT);
			break;
		case PAGE_RADIO_MAIN:
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_RADIO);
			break;

		case PAGE_DVD_MAIN:
		case PAGE_DVD_FOLDER:
		case PAGE_DVD_TRACKLIST:				//	Track_listҳ??	DVD
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DVD_CTRL);
			break;
		case PAGE_DVD_OPEN:				//	????Ƭҳ??	DVD
			if(pLocalParam->soundVideoChannel == CHANNEL_DVD_VIDEO)
			{
				moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DVD_CTRL);
			}
			break;
		case PAGE_DVD_VIDEO:				//	Osd_dvd_bgҳ??
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DVD_VIDEO);
			break;
		case PAGE_DVD_VIDEO_CONTROL: 			//	Osd_dvd_menuҳ??
		case PAGE_DVD_VIDEO_SET: 			//	Osd_dvd_hideҳ??
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DVD_VIDEO);
			break;
			
		case PAGE_IPOD:
		case PAGE_IPOD_SEARCH:	// PAGE_IPOD_LIST
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_IPOD_CTRL);
			break;

		case PAGE_MEDIA:
		case PAGE_MEDIA_SEARCH:
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_MP3);
			break;

		case PAGE_BACK_NOVIDEO: 				//	BackCarҳ??
		    setToHalBackCarMode(getBackCarMode());
		    moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_BACK_NOVIDEO);
			break;
		case PAGE_BACK_VIDEO:
		case PAGE_BACK_FULL_VIDEO:
		case PAGE_BACK_FULL_VIDEO_CONTROL:
		    setToHalBackCarMode(getBackCarMode());
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_BACK_VIDEO);
			break;

		case PAGE_SYNV_MENU://2013-05-20
		case PAGE_AUX:						//	Auxҳ??
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_AUX_CTRL);
			break;
		case PAGE_AUX_VIDEO:				//	Osd_aux_bgҳ??
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_AUX_VIDEO);
			break;
		case PAGE_TV_VIDEO:				//	Osd_tv_bgҳ??
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_TV_VIDEO);
			break;

		case PAGE_TV_VIDEO_CONTROL:				//	Osd_tv_hideҳ??
		case PAGE_TV_VIDEO_SET:				//	Osd_tv_menuҳ??
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_TV_VIDEO);
			break;


		case PAGE_AUX_VIDEO_CONTROL: 			//	Osd_aux_menuҳ??
		case PAGE_AUX_VIDEO_SET:			//	Osd_aux_colorҳ??
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_AUX_VIDEO);
			break;

		case PAGE_DRIVING_RECORD_MENU:
		case PAGE_DRIVING_RECORD_TIME_SET:
		case PAGE_DRIVING_RECORD_SET:
		case PAGE_DRIVING_RECORD_PALY:
		case PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD:
		case PAGE_DRIVING_CHANGHE_DVR_SET_OSD:
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DVR_VIDEO);
			break;
		case PAGE_DRIVING_RECORD_VIDEO:
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DVR_VIDEO);
			break;
		case PAGE_DNV_VIEW_BACK_BROUND:
		case PAGE_DNV_VIEW:
		case PAGE_DNV_PLAY:
		case PAGE_DNV_PAUSE:
		case PAGE_OTHER_DVR_BACKGROUND:
		case PAGE_OTHER_DVR_MAIN:			
		case PAGE_OTHER_DVR_COLOR_SET:		
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DNV_VIDEO);
			break;
		case PAGE_DNV_MENU:
		case PAGE_DNV_TIP:
		case PAGE_DNV_SOFTWARE_VERSION:
		case PAGE_DNV_DEVICE_SETTING_TIP:
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DNV_CTRL);
			break;
		case PAGE_SPEECH_APP_MEDIA:
			//moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_SPEECH_MEDIA_CTRL);
			break;
		default:
			{
				LOGD("bDoSpecial_ChanceSpeechBack:%d",bDoSpecial_ChanceSpeechBack);
				if(bDoSpecial_ChanceSpeechBack)return;
				
				bDoSpecial_ChanceSpeechBack = false;
				
				moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(pLocalParam->soundVideoChannel);
			}
			break;
	}
}

void moduleToAudioVideo_FromSystem_Message(unsigned char *param, unsigned char len){
	switch(param[0]){
		case 0x10:	// system reset
			if(0 == param[1]){
				saveParameter();
				audioToHal_SetMute(true);
			}
			break;
		case 0x14:	// reset to factory settings
			if(0 == param[1]){
				setDefaultParam();
				saveParameter();
				audioToHal_SetMute(true);
			}
			break;
		case 0x30:	// ACC ON
			readParameter();
			ReInitWhenAccOn();
			break;
		case 0x31:	// ACC OFF
			saveParameter();
			int bTempTVStatus;
			bTempTVStatus = pLocalParam->tvStatus;
			setDefaultParam();
			audioToHal_SetMute(true);
			pLocalParam->tvStatus = bTempTVStatus;
			break;
		case 0x2C:
			break;
		case 0x2D:
			break;
		case 0xE0:	// start volume
			moduleToAudioVideo_FromSystem_SetVolume(param[1]);
			break;
		case 0xE1:	// jumpPageWhenAccOn
			moduleToAudioVideo_FromSystem_JumpPageWhenAccOn();
			break;
		case 0xE2:	// GPS Sound On
			moduleToAudioVideo_FromSystem_GPSSoundOn(param[1]);
			break;
		case 0xE3:{	// Page Change
			u16 leavePageID = param[1] + param[2] * 0x100;
			u16 enterPageID = param[3] + param[4] * 0x100;
			int pageParam = param[5];
			moduleToaudiovideo_FromSystem_PageChange(leavePageID, enterPageID, pageParam);
            if(leavePageID==PAGE_BACK_VIDEO ){
            	audioToHal_EnableMixVoice(1);
            }else if(enterPageID==PAGE_BACK_VIDEO && pageParam){
            	audioToHal_EnableMixVoice(0);
            }
		}
			break;
		case 0x4d:
		{
			if(param[1] == 0)
			{
				u8 ucBackMode = 0;
				int paramLen=0;
				getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&paramLen);
				if(ucBackMode != 0x01)
				{
					if (pLocalParam->soundVideoChannel != CHANNEL_THREECHANNEL)
					{
						LOGD("[%s] 20151228 pLocalParam->soundVideoChannel:%d", __FUNCTION__,pLocalParam->soundVideoChannel);
						moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_THREECHANNEL);
					}
				}
			}
		}
		break;
	}
}



/**************************************************************************************************************/
void moduleToAudioVideo_FromKey_GetKeyVolumeInc()
{
	LOGD("GetKeyVolumeInc:pLocalParam->volume=%d",pLocalParam->volume);
	pLocalParam->volume++;
	if(pLocalParam->volume > pLocalParam->uMaxVol)
		pLocalParam->volume=pLocalParam->uMaxVol;
	audioToHal_SetVolume(pLocalParam->volume);
}

void moduleToAudioVideo_FromKey_GetKeyVolumeDec()
{
	LOGD("GetKeyVolumeInc:pLocalParam->volume=%d",pLocalParam->volume);
	pLocalParam->volume--;
	if(pLocalParam->volume < 0)
		pLocalParam->volume=0;
	audioToHal_SetVolume(pLocalParam->volume);
}

void moduleToAudioVideo_FromKey_GetKeyMute(){
	audioToHal_SetMute(!pLocalParam->mute);
}


void moduleToAudioVideo_FromKey_analyseKeyValue(unsigned char *param, unsigned char len)
{
	if(param[0] == 0x35 || param[0] == 0x36 || param[0] == 0x37)
	{
		pLocalParam->bMuteIsOsd = true;
	}

	switch (param[0])
	  {
		case 0x35:	  //VOL_INC
			moduleToAudioVideo_FromKey_GetKeyVolumeInc();
			break;
		case 0x36:	  //VOL_DEC
			moduleToAudioVideo_FromKey_GetKeyVolumeDec();
			break;
		case 0x37:	  //MUTE
			moduleToAudioVideo_FromKey_GetKeyMute();
			break;
		default:break;
	  }
}

void moduleToAudioVideo_FromKey_Message(unsigned char *param, unsigned char len){

	switch (param[0])
	  {
	  	case 0x00:
	  		moduleToAudioVideo_FromKey_analyseKeyValue(&param[1], len - 1);
	  		break;
		default:break;
	  }
}

/**************************************************************************************************************/
void moduleToAudioVideo_FromAudioVideo_Message(unsigned char *param,unsigned char len){
	switch(param[0]){
		case 0x00:
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(param[1]);
			break;
		default:break;
	}

}
/**************************************************************************************************************/

void moduleToAudiovideo_FromCenter_AnalyseGpsSoundState(unsigned char state){
	pLocalParam->preGpsSoundState = pLocalParam->gpsSoundState;
	pLocalParam->gpsSoundState = state;
	if(!pLocalParam->gpsSoundOn && pLocalParam->gpsSoundState && pLocalParam->soundVideoChannel != CHANNEL_THREECHANNEL && pLocalParam->soundVideoChannel != CHANNEL_MP3){
		audioToHal_SetMixedNaviVoice(0);
	}
	audioVideoToModule_NotifyOSD_SendOsdDebugInfo();


}



void moduleToAudiovideo_FromCenter_AnalyseAppRequestMixedVoice(unsigned char state){
	LOGD("moduleToAudiovideo_FromCenter_AnalyseAppRequestMixedVoice:%x",state);
	pLocalParam->b_mixsound=state;
	if(state)
	{
		if(pLocalParam->mixedNaviVoiceState){
			setMixedExternalAppVoiceState(state);
		}
		else
		{
			audioToHal_SetMixedNaviVoice(1);
		}
	}

	audioVideoToModule_NotifyOSD_SendOsdDebugInfo();
}

void moduleToAudiovideo_FromCenter_AnalyseApp_SimulationOfGPS_Process_RequestMixedVoice(unsigned char state)
{
	LOGD("FromCenter_AnalyseApp_SimulationOfGPS_Process_RequestMixedVoice:%x",state);
	pLocalParam->bTimeKeeperState=state;
	audioVideoToModule_NotifyOSD_SendOsdDebugInfo();
}

u16 getCurPageId(void)
{
	u16 wPageId = 0;
	u8 len = 0;

	getOtherModuleParam(0x02, 0xF0, (u8*)&wPageId, &len);

	LOGD("[%s] id = [0x%x]", __FUNCTION__, wPageId);

	return wPageId;
}

bool isInThePageWithSoundChannel(u16 pageId)
{
	bool bRet = false;

	switch(pageId)
		{
		case PAGE_BLUETOOTH_A2DP:
		case PAGE_RADIO_MAIN:
		case PAGE_DVD_MAIN:
		case PAGE_DVD_FOLDER:
		case PAGE_DVD_TRACKLIST:
		case PAGE_DVD_OPEN:
		case PAGE_DVD_VIDEO:
		case PAGE_DVD_VIDEO_CONTROL:
		case PAGE_DVD_VIDEO_SET:
		case PAGE_IPOD:
		case PAGE_IPOD_SEARCH:
		case PAGE_MEDIA:
		case PAGE_MEDIA_SEARCH:
		case PAGE_SYNV_MENU:
		case PAGE_AUX:
		case PAGE_AUX_VIDEO:
		case PAGE_AUX_VIDEO_CONTROL:
		case PAGE_AUX_VIDEO_SET:
		case PAGE_TV_VIDEO:
		case PAGE_TV_VIDEO_CONTROL:
		case PAGE_TV_VIDEO_SET:
			bRet = true;
			break;
		}

	return bRet;
}

int isInThePageOfDnvOrDvr(u16 pageId)
{
	int nRet = 0;

	switch(pageId)
		{
		case PAGE_DNV_VIEW_BACK_BROUND:
		case PAGE_DNV_VIEW:
		case PAGE_DNV_PLAY:
		case PAGE_DNV_PAUSE:
		case PAGE_OTHER_DVR_BACKGROUND:
		case PAGE_OTHER_DVR_MAIN:			
		case PAGE_OTHER_DVR_COLOR_SET:	
			nRet = 1;
			break;
		case PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD:
		case PAGE_DRIVING_CHANGHE_DVR_SET_OSD:
		case PAGE_DRIVING_RECORD_MENU:
		case PAGE_DRIVING_RECORD_TIME_SET:
		case PAGE_DRIVING_RECORD_SET:
		case PAGE_DRIVING_RECORD_PALY:
		case PAGE_DRIVING_RECORD_VIDEO:
			nRet = 2;
			break;
		default:
		break;
		}

	return nRet;
}

void moduleToAudiovideo_FromCenter_Message(unsigned char *param, unsigned char len){
	LOGD("centerToAudiovideo,param[0]:%x,param[1]:%x",param[0], param[1]);
	setVolumeAmplitude();
	switch(param[0]){
		case 0x01:	// Gps sound status
			moduleToAudiovideo_FromCenter_AnalyseGpsSoundState(param[1]);
			break;
		case 0x70:
			moduleToAudiovideo_FromCenter_AnalyseAppRequestMixedVoice(param[1]);
			break;
		case 0x71:
			moduleToAudiovideo_FromCenter_AnalyseApp_SimulationOfGPS_Process_RequestMixedVoice(param[1]);
			break;
		case 0x80:
		{
			u16 wPageId = 0;
			u8 curpagelen = 0;

			getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&wPageId,&curpagelen);
			if(wPageId==PAGE_BACK_VIDEO)return;
		
			LOGD("[%s] 2015 page id = [%x]", __FUNCTION__, wPageId);

			pLocalParam->uThirdPlayState = param[1];

			if(param[1]==0x01)//play
			{
				if(pLocalParam->soundVideoChannel == CHANNEL_SPEECH_MEDIA_CTRL)
				{
					SetTimer(TIMES_IS_STOP_DUEROS,1,TIMER_ID_STOP_DUEROS);
					return;
				}
				
				if (isInThePageWithSoundChannel(wPageId))
				{
					LOGD("[%s] 20150406 page id = [%x]", __FUNCTION__, wPageId);

					audioVideoToModule_NotifySystem_JumpPage(PAGE_MENU);
				}
					
				u8 ucBackMode = 0;
				int paramLen=0;
				getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&paramLen);
				if(ucBackMode != 0x01)
				{
					if (pLocalParam->soundVideoChannel != CHANNEL_THREECHANNEL)
						moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_THREECHANNEL);
				
					int nRet = isInThePageOfDnvOrDvr(wPageId);
					
					if (nRet == 1)//dnv
					{
						moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DNV_VIDEO);
					}
					else if(nRet == 2)//dvr
					{
						moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DVR_VIDEO);
					}
				}

			}

		}
		break;
		case 0x4d:
		{	
			u16 curPageId = 0;
			u8 curpageLen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curPageId,&curpageLen);
			if (isInThePageWithSoundChannel(curPageId))
			{
				LOGD("[%s] 20150827 page curPageId = [%x]", __FUNCTION__, curPageId);
				audioVideoToModule_NotifySystem_JumpPage(PAGE_MENU);
			}
				
				u8 ucBackMode = 0;
				int paramLen=0;
				getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&paramLen);
				if(ucBackMode != 0x01)
				{
					if (pLocalParam->soundVideoChannel != CHANNEL_THREECHANNEL)
					{
						LOGD("[%s] 20150827 pLocalParam->soundVideoChannel:%d", __FUNCTION__,pLocalParam->soundVideoChannel);
						moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_THREECHANNEL);
					}
				}

		}
		break;

		default:break;
	}
}



void moduleToAudioVideo_FromBlueTooth_Message(unsigned char *param,unsigned char len){

	switch(param[0])
	{
	case 0x00:
		{			
			u8 ucBackMode = 0;
			int paramLen=0;
			getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&paramLen);
			if(ucBackMode != 0x01)
			{
				moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(param[1]);
			}
		}
		break;
	case 0x35:
		LOGD("audioVideo get BT state=%x",param[1]);
		if(param[1]==0)param[1]=1;
		else param[1]=0;
		audioToHal_EnableMixVoice(param[1]);
		break;
	default:
		break;
	}

}

void moduleToAudioVideo_FromTVOrDvd_Message(unsigned char *param, unsigned char len){
	switch(param[0]){
		case 0x11:
       		videoToHal_ColorStepRegulate(param[1]);
			break;
		default:break;
	}
}

void moduleToAudioVideo_FromTmps_Message(unsigned char *param, unsigned char len){
	LOGD("TPMS:%d",pLocalParam->canNotSetMixedNaviVoice);
	switch(param[0]){
		case 0x01:
			break;
		default:break;
	}
}
void moduleToAudioVideo_FromMedia_Message(u8* param,u8 len)
{
	LOGD("moduleToAudioVideo_FromMedia_Message:param[0]=%d",param[0]);
	switch(param[0]){
		case 0x01:
			pLocalParam->b_MediaPlaying = param[1];
			audioVideoToModule_NotifyOSD_SendOsdDebugInfo();
			break;
		default:break;
	}
}


void moduleToAudioVideo_SoundHandle(u8* param,u8 len)
{
	LOGD("moduleToAudioVideo_SoundHandle:param[0]:%d,param[1]:%d",param[0],param[1]);
	switch(param[0])
	{
		case 0x00:
		{
			if(param[1] >= 0 && param[1] <= pLocalParam->uMaxVol)
				audioToHal_SetVolume(param[1]);
		}
		break;
		case 0x02:
		{
			if(param[1] == 0x00)//Inc
			{
				if(pLocalParam->volume <= (pLocalParam->uMaxVol - PROGRESSIVE_VOLUME_LEVEL))
				{
					audioToHal_SetVolume(pLocalParam->volume + PROGRESSIVE_VOLUME_LEVEL);
				}
			}
			else if(param[1] == 0x01)//Dec
			{
				if(pLocalParam->volume >= PROGRESSIVE_VOLUME_LEVEL)
				{
					audioToHal_SetVolume(pLocalParam->volume - PROGRESSIVE_VOLUME_LEVEL);
				}
			}
		}
		break;
		case 0x04:
			audioToHal_SetVolume(pLocalParam->uMaxVol);
		break;
		case 0x05:
			audioToHal_SetVolume(1);
		break;
		case 0x06:
			{
				u8 ucBackMode = 0;
				int paramLen=0;
				getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&paramLen);
				if(ucBackMode != 0x01)
				{
					moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(param[1]);
				}
			}	
		break;
		default:break;
	}
}


void moduleToAudioVideo_FromExternalCtrl_Message(u8* param,u8 len)
{
	LOGD("moduleToAudioVideo_FromExternalCtrl_Message:param[0]=%d",param[0]);
	switch(param[0]){
		case 0x00:
			moduleToAudioVideo_SoundHandle(&param[1],len-1);
			break;
		case 0x01:
			{
				audioToHal_NotifySpeechState(param[1]);
			}
			break;
		case 0x02:
			{
				u16 wPageId = 0;
				u8 curpagelen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&wPageId,&curpagelen);
				if(wPageId == PAGE_BACK_VIDEO)return;
			
				LOGD("[%s] 2016 page id = [%x]", __FUNCTION__, wPageId);
				if (isInThePageWithSoundChannel(wPageId) && pLocalParam->soundVideoChannel != CHANNEL_SPEECH_MEDIA_CTRL)
					return;
				
				if(param[1] == 0x01)//play
				{
					if (pLocalParam->soundVideoChannel != CHANNEL_SPEECH_MEDIA_CTRL)
						moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_SPEECH_MEDIA_CTRL);
				}
			}
			break;
		case 0x03:
			{
				if(param[1] == 0x01)
				{
					PageChange_ToPlayback();
				}
			}
			break;
			case 0x04:
				audioToHal_NotifySpeechState_New(param[1]);
				break;
		default:break;
	}
}

//static int szPradoAudioMapHal2Jni[15] = {};
void updatePradoAudio(void)
{
	setUpdateUI(false);

	setAnalogData(CONTROLID_AUDIO_TREB_GAUGE,(short)pLocalParam->trebPos);
	setAnalogData(CONTROLID_AUDIO_MID_GAUGE,(short)pLocalParam->midPos);
	setAnalogData(CONTROLID_AUDIO_BASS_GAUGE,(short)pLocalParam->bassPos);

	setAnalogData(CONTROLID_AUDIO_ASL, (pLocalParam->m_nPradoAsl == 1) ? 1 : 0);
	setAnalogData(CONTROLID_AUDIO_PARK_SURROUND, (pLocalParam->m_nPradoSurround == 1) ? 1 : 0);

	setExProgressSinglePos(CONTROLID_AUDIO_LISTENPOS, 0x01, pLocalParam->balance);
	setExProgressSinglePos(CONTROLID_AUDIO_LISTENPOS, 0x00, pLocalParam->fader);
	setExProgressSinglePos(CONTROLID_AUDIO_SCROLLBAR_LISTENPOS, 0x01, pLocalParam->balance);
	setExProgressSinglePos(CONTROLID_AUDIO_SCROLLBAR_LISTENPOS, 0x00, pLocalParam->fader);

	setUpdateUI(true);
}

void requestPradoAudio(void)
{
	static u8 szMap[21] = {0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 12, 13, 13, 14, 14}; 
	u8 szMsg[] = {0xB1, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	u8 d = 0;

	d = (pLocalParam->trebPos & 0x7F) | (((pLocalParam->m_nPradoAsl == 1) ? 1 : 0) << 7);
	szMsg[3] = d;
	d =( pLocalParam->midPos & 0x7F) | (((pLocalParam->m_nPradoSurround == 1) ? 1 : 0) << 7);
	szMsg[4] = d;
	d = (pLocalParam->bassPos) & 0x7F;
	szMsg[5] = d;  
	d = szMap[pLocalParam->balance] & 0x7F;
	szMsg[6] = d;
	d = szMap[pLocalParam->fader] & 0x7F;
	szMsg[7] = d;

	LOGD("[%s] 3 = [%d]  4 = [%d] 5 = [%d] 6 = [%d] 7 = [%d]", __FUNCTION__, szMsg[3], szMsg[4], szMsg[5], szMsg[6], szMsg[7]);
	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void moduleToAudioVideo_FromExtcar_Message(u8* p, u8 len)
{
	switch(p[0])
	{
	case 0xB1:
		{
			switch(p[1])
			{
			case 0x04:
				{
					static u8 szMap[15] = {0, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 18, 20};
					int nVolume = 0, nMute = 0, nTreb = 0, nAsl = 0, nMid = 0, nPos = 0, nBass = 0, nBal = 0, nFad = 0;
					
					u8 d0 = p[2], d1 = p[3], d2 = p[4], d3 = p[5], d4 = p[6], d5 = p[7];
			
					nVolume = d0 & 0x7F;
					nMute = d0 >> 7;
					nTreb = d1 & 0x7F;
					nAsl = d1 >> 7;
					nMid = d2 & 0x7F;
					nPos = d2 >> 7;
					nBass = d3 & 0x7F;
					nBal = d4 & 0x7F;
					nFad = d5 & 0x7F;

					LOGD("[%s] prado data ------------------------------------------------------", __FUNCTION__);
					LOGD("[%s] nVolume = [%d]", __FUNCTION__, nVolume);
					LOGD("[%s] nTreb = [%d]", __FUNCTION__, nTreb);
					LOGD("[%s] nAsl = [%d]", __FUNCTION__, nAsl);
					LOGD("[%s] nMid = [%d]", __FUNCTION__, nMid);
					LOGD("[%s] nPos = [%d]", __FUNCTION__, nPos);
					LOGD("[%s] nBass = [%d]", __FUNCTION__, nBass);
					LOGD("[%s] nBal = [%d]", __FUNCTION__, nBal);
					LOGD("[%s] nFad = [%d]", __FUNCTION__, nFad);
					LOGD("[%s] prado data ------------------------------------------------------", __FUNCTION__);

					pLocalParam->trebPos = nTreb;
					pLocalParam->midPos = nMid;
					pLocalParam->bassPos = nBass;

					pLocalParam->m_nPradoAsl = nAsl;
					pLocalParam->m_nPradoSurround = nPos;

					pLocalParam->balance = szMap[nBal];
					pLocalParam->fader = szMap[nFad];

					updatePradoAudio();
				}
				break;
			}
		}
		break;
	default:
		break;
	}
}

void moduleToAudioVideo_FromSync_Message(unsigned char *param,unsigned char len)
{
	switch(param[0]){
		case 0x00:
			{
				bDoSpecial_ChanceSpeechBack = true;
				u8 ucBackMode = 0;
				int paramLen=0;
				getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&paramLen);
				if(ucBackMode != 0x01)
				{
					moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(param[1]);
				}
			}
		break;
		default:break;
	}

}


void moduleToAudioVideo_FromAutomate_Message(unsigned char *param,unsigned char len)
{
    #include "appResponseCommand.h"
    
    if(param[0] == 0xff)
    {
        analyseAppMessage(param+1, len-1);
    }

}

void audioVideoToModule_NotifyOSDModule_AccordingtoChannel(int param)
{
    u8 cmd=0x00;
    switch(param)
    {
    	case 0x01:
    	cmd=0x01;
    	break;
    	case 0x0D:
    	cmd=0x02;
    	break;
    	case 0x04:
    	cmd=0x03;
    	break;
    	case 0x06:
        cmd=0x04;
        break;
    	case 0x11:
    	cmd=0x05;
    	break;
    	default:break;
    }
    audioVideoToModule_NotifyOsdModule_ViewSwitch(cmd);
}


void audioVideoToModule_NotifyOSDModule_PageChange(u32 enterPageID)
{
    LOGD("audiovideo pagechange to osd enterPageID:%x",enterPageID);
    u8 cmd = 0x00;
    switch(enterPageID)
    {
		case PAGE_BACK_VIDEO:
		    cmd=0x20;
		    break;
		case PAGE_BACK_FULL_VIDEO_CONTROL:
		    cmd=0x21;
			break;
		case PAGE_AUX_VIDEO_CONTROL:
			cmd=0x30;
			break;
		case PAGE_AUX_VIDEO_SET:
		   cmd=0x31;
		break;
		case PAGE_TV_VIDEO_CONTROL: 
			cmd=0x40;
			break;
		case PAGE_TV_VIDEO_SET:	
			cmd=0x41;
			break;
		case PAGE_DRIVING_RECORD_MENU:
		    cmd=0x50;
		    break;
		case PAGE_DRIVING_RECORD_PALY:
			cmd=0x51;
		    break;
		case PAGE_DRIVING_RECORD_TIME_SET:
			cmd=0x52;
		    break;
		case PAGE_DRIVING_RECORD_SET:
			cmd=0x53;
		    break;
		case PAGE_DVD_VIDEO_CONTROL: 
			cmd=0x60;
			break;
		case PAGE_DVD_VIDEO_SET:
			cmd=0x61;
			break;
		default:
			cmd=0x00;
			break;
	}

	audioVideoToModule_NotifyOsdModule_OSDPage(cmd);

}

bool isVideoChannel(u8 p)
{
	bool bRet = false;

	if (p == CHANNEL_DVD_VIDEO ||
		p == CHANNEL_DVR_VIDEO ||
		p == CHANNEL_TV_VIDEO  ||
		p == CHANNEL_AUX_VIDEO ||
		p == CHANNEL_BACK_VIDEO ||
		p == CHANNEL_DNV_VIDEO)
	{
		bRet = true;
	}
		
	return bRet;
}

void enterOrExitVideoPreProcess(u8 p)
{
	bool bIsFastBackCar = (getBackCarMode() == 1) ? true : false;

	static u8 sPreChannel = CHANNEL_NOCHANNEL;

	if(sPreChannel != p && isVideoChannel(p) && bIsFastBackCar)
	{
		setToHalSystemLcd(LCD_OPEN, 0);
	}
	else if (sPreChannel != p && isVideoChannel(p) && !bIsFastBackCar) //enter video
	{
		setToHalSystemLcd(LCD_CLOSE, TIME_CYCLE_ENTER_OR_EXIT_VIDEO);
	}
	else if (isVideoChannel(sPreChannel) && sPreChannel != p  && !bIsFastBackCar)
	{
		setToHalSystemLcd(LCD_CLOSE, TIME_CYCLE_ENTER_OR_EXIT_VIDEO);
	}

	sPreChannel = p;
}


void SendVideoChannel_enterOrExitVideoPreProcess(u8 uChannel,u8 p,u8 iVideo)
{
	bool bIsFastBackCar = (getBackCarMode() == 1) ? true : false;

	static u8 sPreChannel = CHANNEL_NOCHANNEL;

	LOGD("[%s] sPreChannel:%d,bIsFastBackCar:%d isVideoChannel(p):%d",__FUNCTION__,sPreChannel,bIsFastBackCar,isVideoChannel(p));
	if(sPreChannel != uChannel && isVideoChannel(uChannel) && bIsFastBackCar)
	{
		SetVideoChannel_videoToHal_enterOrExitVideoPreProcess(p,iVideo,0);
	}
	else if (sPreChannel != uChannel && isVideoChannel(uChannel) && !bIsFastBackCar) //enter video
	{
		#ifdef MTK_3561_64
			if(uChannel == CHANNEL_BACK_VIDEO)
			SetVideoChannel_videoToHal_enterOrExitVideoPreProcess(p,iVideo,TIME_CYCLE_ENTER_OR_EXIT_VIDEO_3561);
			else
			SetVideoChannel_videoToHal_enterOrExitVideoPreProcess(p,iVideo,0);	
		#else
			SetVideoChannel_videoToHal_enterOrExitVideoPreProcess(p,iVideo,TIME_CYCLE_ENTER_OR_EXIT_VIDEO);
		#endif
	}
	else if (isVideoChannel(sPreChannel) && sPreChannel != uChannel  && !bIsFastBackCar)
	{
		#ifdef MTK_3561_64
			SetVideoChannel_videoToHal_enterOrExitVideoPreProcess(p,iVideo,0);	
		#else
			SetVideoChannel_videoToHal_enterOrExitVideoPreProcess(p,iVideo,TIME_CYCLE_ENTER_OR_EXIT_VIDEO);
		#endif
		
	}

	sPreChannel = uChannel;

}

void RequestAudioFocus(u8 p)
{
	if(p == 0x01){
		setRingerCtrl(0xFF);
	}
}

void RequestAudioMuteOrUnMute(u8 p)
{
	audioToHal_NotifySpeechState(p);
}

void PageChange_ToPlayback()
{
	short sT = pLocalParam->oldsoundVideoChannel;
	
	/*
	u16 curPageId = 0;
	u8 curpageLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curPageId,&curpageLen);

	LOGD("[%s] curPageId:0x%x \n",__FUNCTION__,curPageId);
	switch(curPageId){	
		case PAGE_BLUETOOTH_A2DP:
		case PAGE_RADIO_MAIN:
		case PAGE_DVD_MAIN:
		case PAGE_DVD_FOLDER:
		case PAGE_DVD_TRACKLIST:
		case PAGE_DVD_OPEN:
		case PAGE_DVD_VIDEO:
		case PAGE_DVD_VIDEO_CONTROL:
		case PAGE_DVD_VIDEO_SET:
		case PAGE_IPOD:
		case PAGE_IPOD_SEARCH:
		case PAGE_MEDIA:
		case PAGE_MEDIA_SEARCH:
		case PAGE_SYNV_MENU:
		case PAGE_AUX:	
		case PAGE_AUX_VIDEO:
		case PAGE_TV_VIDEO:
		case PAGE_TV_VIDEO_CONTROL:
		case PAGE_TV_VIDEO_SET:
		case PAGE_AUX_VIDEO_CONTROL:
		case PAGE_AUX_VIDEO_SET:
		case PAGE_DRIVING_RECORD_MENU:
		case PAGE_DRIVING_RECORD_TIME_SET:
		case PAGE_DRIVING_RECORD_SET:
		case PAGE_DRIVING_RECORD_PALY:
		case PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD:
		case PAGE_DRIVING_CHANGHE_DVR_SET_OSD:
		case PAGE_DRIVING_RECORD_VIDEO:
		case PAGE_DNV_VIEW_BACK_BROUND:
		case PAGE_DNV_VIEW:
		case PAGE_DNV_PLAY:
		case PAGE_DNV_PAUSE:
		case PAGE_OTHER_DVR_BACKGROUND:
		case PAGE_OTHER_DVR_MAIN:			
		case PAGE_OTHER_DVR_COLOR_SET:
		case PAGE_DNV_MENU:
		case PAGE_DNV_TIP:
		case PAGE_DNV_SOFTWARE_VERSION:
		case PAGE_DNV_DEVICE_SETTING_TIP:
		break;
		default:
		{
			u8 ucBackMode = 0;
			int paramLen=0;
			getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&paramLen);
			if(ucBackMode != 0x01)
			{
				if(sT != CHANNEL_SPEECH_MEDIA_CTRL)
				{
					moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(sT);
				}
			}
		}
		break;
	}*/

	u8 ucBackMode = 0;
	int paramLen=0;
	getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&paramLen);
	if(ucBackMode != 0x01)
	{
		if(sT != CHANNEL_SPEECH_MEDIA_CTRL)
		{
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(sT);
		}
	}
}

