#include <stdio.h>
#include <stdlib.h>
#include <commonFunc.h>
#include "global.h"
#include "param.h"
#include "paramID.h"
#include "pageID.h"

#include "controlID.h"
#include "moduleParamResponse.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "timer_interface.h"
#include <pthread.h>


bool bAccOnOrInit_State = false;

void moduleParameterInit(void){

}

void moduleParameterDeInit(void){

}

void moduleParameterReInit(void){
	LOGD("&&&&&&&&&&&&&&&&& audiovideo moduleParameterReInit");
}
int module_extendInterface(char *buffer, int len){
	LOGD("******************audiovideo module_extendInterface %x,%x",buffer[0],buffer[1]);
	switch(buffer[0]){
		case 0x2C:
			{
				if(buffer[1] == 0x00)//acc off
				{
					LOGD("************************audiovideo ACC OFF");
					DeleteTimer(TIMER_ID_IS_SUPPORT_USB_CAMERA);
					DeleteTimer(TIMER_ID_IS_SUPPORT_USB_CAMERA_TIMEOUT);
					DeleteTimer(TIMER_ID_IS_SET_LOGO_DISAPPEARS);
					saveParameter();
				}
				if(buffer[1] == 0x01)//restart
				{
					LOGD("************************audiovideo restart");
					saveParameter();
				}
				if(buffer[1] == 0x02)//default
				{
					LOGD("************************audiovideo default");
					setDefaultParam();
					bAccOnOrInit_State=true;
					LOGD("bAccOnOrInit_State11111:%d",bAccOnOrInit_State);
					saveParameter();
					audioToHal_SetMute(true);
				}

				char property[PROPERTY_VALUE_MAX];
				property_set(LIDBG_HOLD_HOOTANIM,"true");
			}
			break;
		case 0x2D://acc on
			if(buffer[1] == 0x00)
			{
				LOGD("************************audiovideo ACC ON");
				readParameter();
				
				if(pLocalParam->soundVideoChannel == 0x05 || pLocalParam->soundVideoChannel == 0x06){
					pLocalParam->b_autoJumpAux = false;/*��������������AUXҳ��*/
				}
				bAccOnOrInit_State=true;
				LOGD("555bAccOnOrInit_State:%x",bAccOnOrInit_State);
				pLocalParam->getVolumeTimes = 0;
				sendStartVolToHalWhenAccOn();
				audioToHal_SetStartVolume(pLocalParam->volume);

				audioToHal_EnableMixVoice(1);
				audioVideoToModule_NotifyOSD_SendOsdDebugInfo();
				DeleteTimer(TIMER_ID_ENABLE_MIXVOICE);
		    	SetTimer(TIMES_ENABLE_MIXVOICE,1,TIMER_ID_ENABLE_MIXVOICE);

				//audiovideoModule_ACCON();
				audiovideoModule_ACCON_JumpPage();
		
				pLocalParam->bMuteIsOsd = true;
			}
			break;
		case 0xFD:
			{
				LOGD("************************audiovideo Init");

				char property[PROPERTY_VALUE_MAX];
				property_set(LIDBG_HOLD_HOOTANIM,"true");
				
				if(pLocalParam->soundVideoChannel == 0x05 || pLocalParam->soundVideoChannel == 0x06){
					pLocalParam->b_autoJumpAux = false;/*��������������AUXҳ��*/
				}

				bAccOnOrInit_State=true;

				audioToHal_Init(0x01);		//��ʼ������
			    videoToHal_Init(0x01);
				//initTimerCenter(&TimerHandlerCenter);
				initByConfig();
				readHalProperty_aboutMaxVolumeVal();

				//Wait until the jump page action is completed.
				usleep(5000*1000);
				setModulesInitCompleted();
			}
			break;
		default:break;
	}

	return 0;
}

void initSoundVideoChannelWhenPowerOn(){

    char property[PROPERTY_VALUE_MAX];
    
    u8 uTempAutoPlayStatu=1;
	property_get("fly.booton.isautopaly",property,"1");
	sscanf(property,"%d",&uTempAutoPlayStatu);
	
    LOGD("uTempAutoPlayStatu:%d",uTempAutoPlayStatu);
	if(uTempAutoPlayStatu == 0)
	{
	    pLocalParam->savemode = CHANNEL_THREECHANNEL;
	}
	else
	{
	    LOGD("[%s] pLocalParam->savemode:%x pLocalParam->Default_channel:%d ", __FUNCTION__,pLocalParam->savemode,pLocalParam->Default_channel);
    	if(pLocalParam->savemode < 0 || pLocalParam->savemode > CHANNEL_MAX)
    	{
    		pLocalParam->savemode = CHANNEL_DVD_CTRL;
    	}

    	if(pLocalParam->Default_channel < 0 || pLocalParam->Default_channel > CHANNEL_MAX ){
    		pLocalParam->Default_channel = CHANNEL_DVD_CTRL;
    	}
    		
    	if(pLocalParam->savemode == 0x00){
    		pLocalParam->savemode = pLocalParam->Default_channel;		
    	}
	}

	switch(pLocalParam->savemode){

		case CHANNEL_DVD_VIDEO:
		//case CHANNEL_BT:
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(pLocalParam->Default_channel);
			break;
		default:
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(pLocalParam->savemode);
			break;
	}
}

void InitAudioParamMakeAndSendMessageToHal()
{
	u8 buff[63];
	memset(buff,0,sizeof(buff));
	
	buff[0] = pLocalParam->volume;
	buff[1] = pLocalParam->balance;
	buff[2] = pLocalParam->fader;
	buff[3] = pLocalParam->bass;
	buff[4] = pLocalParam->treb;
	buff[5] = pLocalParam->loudness;
	buff[6] = pLocalParam->mid;
	memcpy(&buff[7],pLocalParam->EQValue,10);
	buff[17] = pLocalParam->trebPos;
	buff[18] = pLocalParam->bassPos;
	buff[19] = pLocalParam->loudnessPos;
	buff[20] = pLocalParam->midPos;
	buff[21] = pLocalParam->soundPos;
	buff[22] = pLocalParam->bIsLoudnessOn;
	buff[23] = 0x00;
	buff[24] = 0x00;
	buff[25] = 0x05;
	buff[26] = pLocalParam->readPowerOnEQTemp;

	audioTohal_InitParamCmd(buff,27);
}

void initByConfig(void){

	//��ʼ��
	//���ÿ�������/
   // sendStartVolToHalWhenAccOn();
	sendStartVolToHalWhenInit();

	if(pLocalParam->bIsMixingSwitch)
	{
		setDigitalData(CONTROLID_AUDIO_MEDIA_MIX_ON_OFF, 1);
	}
	else
	{
		setDigitalData(CONTROLID_AUDIO_MEDIA_MIX_ON_OFF, 0);
	}

	LOGD("*******pLocalParam->bIsMixingSwitch:%x********",pLocalParam->bIsMixingSwitch);

	////audioToHal_Balance(pLocalParam->balance);
	////audioToHal_Fader(pLocalParam->fader);
	////audioToHal_SetBassFreq(pLocalParam->bass);
	////audioToHal_SetTrebFreq(pLocalParam->treb);
	////audioToHal_SetLoudnessFreq(pLocalParam->loudness);
	////audioToHal_SetMidFreq(pLocalParam->mid);

	////audioToHal_SetEQAll(pLocalParam->EQValue,10);		// xu xiu gai

	////audioToHal_SetTredLevel(pLocalParam->trebPos);
	////audioToHal_SetBassLevel(pLocalParam->bassPos);
	////audioToHal_SetLoudnessLevel(pLocalParam->loudnessPos);
	////audioToHal_SetMidLevel(pLocalParam->midPos);
	////audioToHal_SetPOSValue(pLocalParam->soundPos);

	requestPradoAudio();//Teo

	//audiovideoModule_ACCON_Init();
	audiovideoModule_Init_JumpPage();

	////audioToHal_SetLoudnessSwitch(pLocalParam->bIsLoudnessOn);
	////audioToHal_SetSubSwitch(0x00);
	////audioToHal_SetSubFilter(0x00);
	////audioToHal_SetSubLevel(0x05);

	pLocalParam->firstDisplayEQFlag = 1;
   ////audioToHal_SetInnerEQSetting(pLocalParam->readPowerOnEQTemp);

	InitAudioParamMakeAndSendMessageToHal();
}

void audiovideoModule_ACCON_Init(void){
		initSoundVideoChannelWhenPowerOn();

		if(strncmp(pLocalParam->str_WhichProject,"G8II-KOREA",10) == NULL)
		{
			audioVideoToModule_NotifySystem_FirstEnterSoundMode();//����������һ��ҳȥ
			usleep(2500*1000);
			audioVideoToModule_NotifySystem_StartGPS();
		}
		else
		{
			audioVideoToModule_NotifySystem_StartGPS();
			#ifdef MTK_3561_64
			usleep(4000*1000);
			#endif
			usleep(4000*1000);
			audioVideoToModule_NotifySystem_FirstEnterSoundMode();//����������һ��ҳȥ
		}
}

void audiovideoModule_Init_JumpPage(void){
		initSoundVideoChannelWhenPowerOn();

		if(strncmp(pLocalParam->str_WhichProject,"G8II-KOREA",10) == NULL)
		{
			audioVideoToModule_NotifySystem_FirstEnterSoundMode();//����������һ��ҳȥ
			usleep(2500*1000);
			audioVideoToModule_NotifySystem_StartGPS();
		}
		else
		{
			//audioVideoToModule_NotifySystem_StartGPS();
			NotifySystem_StartGPS(0x01);
			audioVideoToModule_NotifySystem_FirstEnterSoundMode();
		}
}


void audiovideoModule_ACCON(void){
		initSoundVideoChannelWhenPowerOn();

		if(strncmp(pLocalParam->str_WhichProject,"G8II-KOREA",10) == NULL)
		{
			audioVideoToModule_NotifySystem_FirstEnterSoundMode();//����������һ��ҳȥ
			//audioVideoToModule_NotifySystem_StartGPS();

			SetTimer(TIMES_IS_SUPPORT_USB_CAMERA,0, TIMER_ID_IS_SUPPORT_USB_CAMERA);
			SetTimer(TIMES_IS_SUPPORT_USB_CAMERA_TIMEOUT,0, TIMER_ID_IS_SUPPORT_USB_CAMERA_TIMEOUT);
		}
		else
		{
			audioVideoToModule_NotifySystem_StartGPS();
			#ifdef MTK_3561_64
			usleep(1500*1000);
			#endif
			usleep(1500*1000);
			audioVideoToModule_NotifySystem_FirstEnterSoundMode();//����������һ��ҳȥ

			if(pLocalParam->savemode == CHANNEL_MP3){
				usleep(1500*1000);
			}
			
			#ifdef MTK_3561_64
			usleep(2000*1000);
			#endif
			usleep(2000*1000);
			char property[PROPERTY_VALUE_MAX];
			property_set(LIDBG_HOLD_HOOTANIM,"false");

		}

}

void audiovideoModule_ACCON_JumpPage(void){
		initSoundVideoChannelWhenPowerOn();
		
		if(strncmp(pLocalParam->str_WhichProject,"G8II-KOREA",10) == NULL)
		{
			audioVideoToModule_NotifySystem_FirstEnterSoundMode();//����������һ��ҳȥ
			//audioVideoToModule_NotifySystem_StartGPS();

			SetTimer(TIMES_IS_SUPPORT_USB_CAMERA,0, TIMER_ID_IS_SUPPORT_USB_CAMERA);
			SetTimer(TIMES_IS_SUPPORT_USB_CAMERA_TIMEOUT,0, TIMER_ID_IS_SUPPORT_USB_CAMERA_TIMEOUT);
		}
		else
		{
			//audioVideoToModule_NotifySystem_StartGPS();
			NotifySystem_StartGPS(0x00);
			audioVideoToModule_NotifySystem_FirstEnterSoundMode();

			if(pLocalParam->savemode == CHANNEL_MP3){
				//usleep(1500*1000);
			}
			SetTimer(TIMER_ID_IS_SET_LOGO_DISAPPEARS_TIME,1, TIMER_ID_IS_SET_LOGO_DISAPPEARS);
		}


}

void ReInitWhenAccOn(void)
{
	//audioToHal_Init(0x01);		//��ʼ������
    //videoToHal_Init(0x01);

	audioToHal_Balance(pLocalParam->balance);
	audioToHal_Fader(pLocalParam->fader);
	audioToHal_SetBassFreq(pLocalParam->bass);
	audioToHal_SetTrebFreq(pLocalParam->treb);
	audioToHal_SetLoudnessFreq(pLocalParam->loudness);
	audioToHal_SetMidFreq(pLocalParam->mid);

	audioToHal_SetEQAll(pLocalParam->EQValue,10);		// xu xiu gai

	audioToHal_SetTredLevel(pLocalParam->trebPos);
	audioToHal_SetBassLevel(pLocalParam->bassPos);
	audioToHal_SetLoudnessLevel(pLocalParam->loudnessPos);
	audioToHal_SetMidLevel(pLocalParam->midPos);
	audioToHal_SetPOSValue(pLocalParam->soundPos);

	audioToHal_SetLoudnessSwitch(pLocalParam->bIsLoudnessOn);
	audioToHal_SetSubSwitch(0x00);
	audioToHal_SetSubFilter(0x00);
	audioToHal_SetSubLevel(0x05);

	initSoundVideoChannelWhenPowerOn();
	audioVideoToModule_NotifySystem_FirstEnterSoundMode();

    audioToHal_SetInnerEQSetting(pLocalParam->settingIndex);

	audioVideoToModule_NotifyOSD_SendOsdDebugInfo();
}

void setDefaultParam(void){
	memset(pLocalParam->str_WhichProject,0,sizeof(pLocalParam->str_WhichProject));
	pLocalParam->settingIndex = EQ_DEFAULT;
	pLocalParam->readPowerOnEQTemp = EQ_DEFAULT;
	
	pLocalParam->oldsoundVideoChannel = CHANNEL_NOCHANNEL;
	pLocalParam->soundVideoChannel = CHANNEL_NOCHANNEL;
	pLocalParam->soundChannel = CHANNEL_NOCHANNEL;
	pLocalParam->videoChannel = CHANNEL_NOCHANNEL;
	pLocalParam->m_u8ChannelHaveSetToHal = CHANNEL_NOCHANNEL;
	pLocalParam->lastMediaChannel = CHANNEL_RADIO;

	pLocalParam->soundcardSoundState = false;

	pLocalParam->sleepMode = false;

	pLocalParam->volume = 15;	// ����
	pLocalParam->mute = false;	// ����

	pLocalParam->balance = 10;	// ����ƽ��
	pLocalParam->fader = 10;	// ǰ��ƽ��
	pLocalParam->soundPos = 0;	// ����λ��

	pLocalParam->m_nPradoAsl = 0;
	pLocalParam->m_nPradoSurround = 0;

	pLocalParam->bass = 0;
	pLocalParam->treb = 0;
	pLocalParam->loudness = 0;
	pLocalParam->mid = 0;

	pLocalParam->bassPos = 5;
	pLocalParam->trebPos = 5;
	pLocalParam->loudnessPos = 0;
	pLocalParam->midPos = 5;		// ����Ƶ��

	pLocalParam->EQCount = 10;
	pLocalParam->EQ = EQ_DEFAULT;	//EQ ģʽ�洢

	int i=0;
	for(; i < 10; i++){
		pLocalParam->EQValue[i] = 12;
		pLocalParam->EQUser1[i] = 12;
		pLocalParam->EQUser2[i] = 12;
		pLocalParam->EQUser3[i] = 12;
		pLocalParam->fineTurningValue[i] = 20;
	}

	if(pLocalParam->EQCount == 9){
		unsigned char tmpClass[10] 	 = {10,  5, 6, 6, 7,  6,  8, 10,  9, 0};
		unsigned char tmpPop[10] 	 = { 8,  4, 7, 5, 7,  5,  7,  9,  8, 0};
		unsigned char tmpJazz[10] 	 = { 8, 10, 6, 6, 8, 10, 10,  8,  9, 0};
		unsigned char tmpRock[10] 	 = {10, 11, 9, 6, 7,  7,  9, 10, 11, 0};
		unsigned char tmpDefault[10] = { 6,  6, 6, 6, 6,  6,  6,  6,  6, 6};
		memcpy(pLocalParam->EQClassic, tmpClass,10);
		memcpy(pLocalParam->EQPopular, tmpPop,10);
		memcpy(pLocalParam->EQJazz, tmpJazz,10);
		memcpy(pLocalParam->EQRock, tmpRock,10);
		memcpy(pLocalParam->EQDefault, tmpDefault,10);
	}
	else if(pLocalParam->EQCount == 10){
		unsigned char tmpClass[10]	 = { 6, 10,  5, 6, 6,  7,  6, 8,  10,  9};
		unsigned char tmpPop[10]	 = { 6,  8,  4, 7, 5,  7,  5,  7,  9,  8};
		unsigned char tmpJazz[10]	 = { 6,  8, 10, 6, 6,  8, 10, 10,  8,  9};
		unsigned char tmpRock[10]	 = { 6, 10, 11, 9, 6,  7,  7,  9, 10, 11};
		unsigned char tmpDefault[10] = { 6,  6,  6, 6, 6,  6,  6,  6,  6,  6};
		memcpy(pLocalParam->EQClassic, tmpClass,10);
		memcpy(pLocalParam->EQPopular, tmpPop,10);
		memcpy(pLocalParam->EQJazz, tmpJazz,10);
		memcpy(pLocalParam->EQRock, tmpRock,10);
		memcpy(pLocalParam->EQDefault, tmpDefault,10);
	}

	//pLocalParam->bIsLoudnessOn = false;
	pLocalParam->bIsLoudnessOn = true;
	pLocalParam->subState = false;
	pLocalParam->subFilter = 0;
	pLocalParam->subLevel = 0;

	pLocalParam->tvStatus = false;
	pLocalParam->getVolumeTimes = 0;

	pLocalParam->preSettingIndexControl = CONTROLID_EQ_TURNOFF;

	pLocalParam->firstDisplayEQFlag = 1;

	pLocalParam->gpsSoundTimerING = 0;
	pLocalParam->gpsSoundState = 0;
	pLocalParam->preGpsSoundState = 0;

	pLocalParam->bIsRetrySendCameraReady  = 0;
	pLocalParam->bIsVideoOpen = 0;
	pLocalParam->bIsSameVideoForCamera = 0;

	pLocalParam->soundcardStateChangeING = 0;

	pLocalParam->mixedNaviVoiceState = 0;
	pLocalParam->canNotSetMixedNaviVoice = 0;
	pLocalParam->notifyAppForMixedNaviVoice = 0;

	pLocalParam->b_IsRequestvoice_state = false;
	pLocalParam->b_MediaPlaying = false;
	pLocalParam->b_mixsound=false;
	pLocalParam->bIsMixingSwitch = true;

	pLocalParam->b_autoJumpAux = true;
	pLocalParam->uThirdPlayState = 0;
	pLocalParam->volumeSet= 0xFF;
	pLocalParam->bTimeKeeperState=false;
	pLocalParam->uEnableMixVoiceState = 1;
	
	pLocalParam->bMuteIsOsd = true;
	pLocalParam->bIsSupportUsbCamera = false;
	pLocalParam->sdkMediaVolume = 0xff;
	pLocalParam->sdkCallingVolume = 0xff;

}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		case SOUND_CHANNEL:
			 *(short*)param = (short)pLocalParam->soundVideoChannel;
			 *paramLen = sizeof(short);
			break;
		case OLD_SOUND_CHANNEL:
			 *(short*)param = (short)pLocalParam->oldsoundVideoChannel;
			 *paramLen = sizeof(short);
			break;
		case DEFAULT_CHANNEL:
			 *(short*)param = (short)pLocalParam->Default_channel;
			 *paramLen = sizeof(short);
			break;
		case MEDIA_PLAY_STATE:
		{
			if(pLocalParam->b_MediaPlaying)
					*param = 1;
				else
					*param = 0;
			 *paramLen = sizeof(u8);
			 
			break;
		}
		case SOUND_CARD_STATE:
			*(u8*)param = (u8)pLocalParam->soundcardSoundState;
			 *paramLen = sizeof(u8);
			break;
		case IS_CANJUMPAUX:
		{
			if(pLocalParam->b_autoJumpAux)
				*param = 1;
			else
				*param = 0;
			*paramLen = sizeof(u8);
		}
		break;
		case CUR_VOLUME:
		{
		     *(u8*)param = (u8)pLocalParam->volume;
			 *paramLen = sizeof(u8);
		}
		break;
		case CUR_EQUALIZER:
		{
			 *(u8*)param = (u8)pLocalParam->settingIndex;
			 *paramLen = sizeof(u8);
		}
		break;
		case CUR_LEFT_RIGHT_BALANCE:
        {
            *(u8*)param = (u8)pLocalParam->balance;
			*paramLen = sizeof(u8);
        }
        break;
		case CUR_FRONT_REAR_BALANCE:
		{
		    *(u8*)param = (u8)pLocalParam->fader;
			*paramLen = sizeof(u8);
		}
		break;
		case MAX_VOLUME:
			*(u8*)param = pLocalParam->uMaxVol;
			*paramLen = sizeof(u8);
		break;
		case LAST_MEDIA_CHANNEL:
			*(short*)param = (short)pLocalParam->lastMediaChannel;
			*paramLen = sizeof(short);
			break;
		default:break;
	}
}

static 	int ChannelToPageMapping[][2] = {
		{CHANNEL_DVD_CTRL,PAGE_DVD_MAIN},
		{CHANNEL_RADIO,PAGE_RADIO_MAIN},
		{CHANNEL_AUX_CTRL,PAGE_AUX},	
		{CHANNEL_IPOD_CTRL,PAGE_IPOD},	
		{CHANNEL_TV_CTRL,PAGE_IPOD},	
		{CHANNEL_MP3,PAGE_MEDIA},
		{CHANNEL_BT,PAGE_BLUETOOTH_MAIN}
};

int GetPageByChannel(u16 *pageID,int channel_param)
{
	int i=0;
	int nCount = 0;
	nCount = (sizeof(ChannelToPageMapping)/sizeof(ChannelToPageMapping[0]));
	for(i=0;i<nCount;i++)
	{
		if (ChannelToPageMapping[i][0] == channel_param)
		{
			*pageID = ChannelToPageMapping[i][1];
			return true;
		}
	}

	return false;
}


static 	int arrayMapping[][3] = {
		{1,0,CHANNEL_DVD_CTRL},
		{1,1,CHANNEL_DVD_VIDEO},
		{2,0,CHANNEL_CDC_CTRL},
		{2,2,CHANNEL_CDC_VIDEO},
		{3,0,CHANNEL_RADIO},
		{4,0,CHANNEL_AUX_CTRL},
		{4,4,CHANNEL_AUX_VIDEO},
		{5,0,CHANNEL_IPOD_CTRL},
		{5,5,CHANNEL_IPOD_VIDEO},
		{6,0,CHANNEL_TV_CTRL},
		{6,6,CHANNEL_TV_VIDEO},
		{7,0,CHANNEL_MP3},
		//{8,0,CHANNEL_SRADIO},
		{9,0,CHANNEL_BT},
		//{0x0C,0x0C,CHANNEL_BACK_VIDEO}
		{0x11,0,CHANNEL_DVR_CTRL},
		{0x11,0x11,CHANNEL_DVR_VIDEO},
		{0x0C,0,CHANNEL_THREECHANNEL},
		{0x0D,0,CHANNEL_BACK_NOVIDEO},
		{0x0D,0x0D,CHANNEL_BACK_VIDEO},
		{0x0E,0, CHANNEL_DNV_CTRL},
		{0x0E,0x0E, CHANNEL_DNV_VIDEO},
		{0x16,0, CHANNEL_SPEECH_MEDIA_CTRL}
};


int findSoundAndVideoChannel(int *newSoundChannel,int *newVideoChannel,int oldSoundVideoChannel)
{
	int i=0;
	int nCount = 0;
	nCount = (sizeof(arrayMapping)/sizeof(arrayMapping[0]));
	for(i=0;i<nCount;i++)
	{
		if (arrayMapping[i][2] == oldSoundVideoChannel)
		{
			*newSoundChannel = arrayMapping[i][0];  //9
			*newVideoChannel = arrayMapping[i][1];	//0
			return true;
		}
	}

	return false;
}

int findCombineSoundVideoChannel(int soundChannel,int videoChannel,int *newSoundVideoChannel)
{
	int arrayMapping[][3] = {
			{1,0,CHANNEL_DVD_CTRL},
			{1,1,CHANNEL_DVD_VIDEO},
			{2,0,CHANNEL_CDC_CTRL},
			{2,2,CHANNEL_CDC_VIDEO},
			{3,0,CHANNEL_RADIO},
			{4,0,CHANNEL_AUX_CTRL},
			{4,4,CHANNEL_AUX_VIDEO},
			{5,0,CHANNEL_IPOD_CTRL},
			{5,5,CHANNEL_IPOD_VIDEO},
			{6,0,CHANNEL_TV_CTRL},
			{6,6,CHANNEL_TV_VIDEO},
			{7,0,CHANNEL_MP3},
			//{8,0,CHANNEL_SRADIO},
			{9,0,CHANNEL_BT},
			//{0x11,0,CHANNEL_DVR_CTRL},
			//{0x11,0x11,CHANNEL_DVR_VIDEO},
			//{0x0C,0x0C,CHANNEL_BACK_VIDEO},
			//{0x0D,0x0D,CHANNEL_BACK_VIDEO},//2013-3-22
			{0x0C,0,CHANNEL_THREECHANNEL},
			{0x16,0,CHANNEL_SPEECH_MEDIA_CTRL}

			//{0x0E,0, CHANNEL_DNV_CTRL},
			//{0x0E,0x0E, CHANNEL_DNV_VIDEO}
	};

	int i=0;
	int nCount = 0;
	nCount = (sizeof(arrayMapping)/sizeof(arrayMapping[0]));
	for(i=0;i<nCount/*(int)sizeof(arrayMapping)/(sizeof(int)*3)*/;i++)
	{
		if (arrayMapping[i][0]==soundChannel && ( (arrayMapping[i][1]&&videoChannel) || (!arrayMapping[i][1]&&!videoChannel) ) )
		{ 
			*newSoundVideoChannel = arrayMapping[i][2];
			return true;
		}

	}
	LOGD("[%s]  fail!!!!!!!!! (soundChannel:%x videoChannel:%x)",__FUNCTION__, soundChannel, videoChannel);
	return false;
}

int findCombineIsAndroidAudioChannel(int soundChannel,int videoChannel)
{
	int arrayMapping[][3] = {
			{7,0,CHANNEL_MP3},
			{0x0C,0,CHANNEL_THREECHANNEL},
			{0x16,0,CHANNEL_SPEECH_MEDIA_CTRL}
	};

	int i=0;
	int nCount = 0;
	nCount = (sizeof(arrayMapping)/sizeof(arrayMapping[0]));
	for(i=0;i < nCount;i++)
	{
		if (arrayMapping[i][0]==soundChannel && ( (arrayMapping[i][1]&&videoChannel) || (!arrayMapping[i][1]&&!videoChannel) ) )
		{ 
			return 1;
		}

	}
	
	LOGD("[%s]  CD Channel !!!!!!!!! (soundChannel:%x videoChannel:%x)",__FUNCTION__, soundChannel, videoChannel);
	return 0;
}

void sendStartVolToHalWhenAccOn(void){
	u8 startVol=0;
	u8 startVolLen=0;

	getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_SET_STARTUPVOL, &startVol, &startVolLen);
	if(0xff==startVol)
	{
		if(pLocalParam->readVolTemp==256)
		    pLocalParam->volume=15;
		else
			 pLocalParam->volume=pLocalParam->readVolTemp;
		return;	//Call the process of acc off,start up a great voice.
	}
	else
	{
		pLocalParam->volume = startVol;
	}

	LOGD("****sendStartVolToHalWhenAccOn** pLocalParam->readVolTemp %d*******pLocalParam->volume %d*****",pLocalParam->readVolTemp,pLocalParam->volume);
	//audioToHal_SetVolume(pLocalParam->volume);
	
	////audioToHal_SetStartVolume(pLocalParam->volume);

}

void sendStartVolToHalWhenInit(void){
	u8 startVol=0;
	u8 startVolLen=0;

	getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_SET_STARTUPVOL, &startVol, &startVolLen);
	if(0xff==startVol)
	{
		if(pLocalParam->readVolTemp==256)
		    pLocalParam->volume=15;
		else
			 pLocalParam->volume=pLocalParam->readVolTemp;
	}
	else
	{
		pLocalParam->volume = startVol;
	}

	LOGD("****sendStartVolToHalWhenAccOn** pLocalParam->readVolTemp %d*******pLocalParam->volume %d*****",pLocalParam->readVolTemp,pLocalParam->volume);
	//audioToHal_SetVolume(pLocalParam->volume);

}

void setVolumeAmplitude(void)
{
	LOGD("setVolumeAmplitue -11--pLocalParam->AvAmplitude =%d",pLocalParam->AvAmplitude);
	if(pLocalParam->AvAmplitude>=10 ||pLocalParam->AvAmplitude<0)return;
	audioToHal_NotifyAmplitude(pLocalParam->AvAmplitude);
}



