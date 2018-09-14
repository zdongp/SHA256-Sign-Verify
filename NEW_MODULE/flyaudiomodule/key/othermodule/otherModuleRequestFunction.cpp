#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "moduleID.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"


void keyToModule_DispatchPanelKey(int nDispatchBySoundMode,unsigned char cToMode,unsigned char cParameter){
	if(nDispatchBySoundMode == true){
        unsigned char cSoundMode = pLocalParam->m_iSoundChannel;

		LOGD("keyToModule_DispatchPanelKey---sound:%x cParameter:%x",cSoundMode,cParameter);

        switch(cSoundMode){
        	case CHANNEL_DVD_CTRL://DVD ctrl
        	case CHANNEL_DVD_VIDEO://DVD video
            	cToMode = MODULE_ID_DVD;
            	break;
        	case CHANNEL_CDC_CTRL: //CDC ctrl
        	case CHANNEL_CDC_VIDEO: //cdc video
           		// cToMode = Module_CDC;
            	break;
        	case CHANNEL_RADIO: //RADIO
            	cToMode = MODULE_ID_RADIO;
            	break;
        	case CHANNEL_AUX_CTRL://AUX ctrl
        	case CHANNEL_AUX_VIDEO://aux video
            	cToMode = MODULE_ID_AUX;
            	break;
        	case CHANNEL_IPOD_CTRL: //IPOD ctrl
        	case CHANNEL_IPOD_VIDEO://ipod video
            	cToMode = MODULE_ID_IPOD;
            	break;
        	case CHANNEL_TV_CTRL://TV ctrl
        	case CHANNEL_TV_VIDEO://tv video
          		cToMode = MODULE_ID_TV;
            	break;
        	case CHANNEL_MP3: //MEDIA
				cToMode = MODULE_ID_MEDIA;
            	break;
			case CHANNEL_BT:
				cToMode = MODULE_ID_BT;
				break;
			case CHANNEL_THREECHANNEL: //����
				{
					if (cParameter == 0x03) //����ͨ����MEDIA����ģ��  
					{
						u16 nCar_Default_channel = 0;
						u8  nCar_Default_channellen = 0;
						getOtherModuleParam(MODULE_ID_AUDIOVIDEO,DEFAULT_CHANNEL,(u8*)&nCar_Default_channel,&nCar_Default_channellen);
						LOGD("nCar_Default_channel:%x",nCar_Default_channel);
						switch(nCar_Default_channel){/*Ĭ���е����������е����Ǹ�ͨ��ȥ*/ 
				        	case 0x00://DVD ctrl
				        	case 0x01://DVD video
				            	cToMode = MODULE_ID_DVD;
				            	break;
				        	case 0x04: //RADIO
				            	cToMode = MODULE_ID_RADIO;
				            	break;
							default:break;
						}
					}
					else{
						return ;
					}
				}
				break;
			case CHANNEL_DVR_CTRL:
			case CHANNEL_DVR_VIDEO:
				cToMode = MODULE_ID_DVR;
				break;
			case CHANNEL_SPEECH_MEDIA_CTRL://WeDrive speech recognition is a non audio channel mode.
				cToMode = MODULE_ID_EXTERNALCTRL;
				break;
        	default:
            	break;
        	}
    }

	LOGD("KeyModule_dispathbysoundMode:%x, ucModuleToSend:0x%x, keyvalue:0x%x", nDispatchBySoundMode, cToMode, cParameter);
    keyToModule_SendPanelKey(cToMode,cParameter);

}

void keyToModule_SendPanelKey(unsigned char cToMode,unsigned char cKeyValue){
    unsigned char pBuf[] = {0x00,cKeyValue};
    makeAndSendMessageToModule(MODULE_ID_KEY,cToMode,pBuf,2);
}

void keyToModule_NotifyBACK_ExitAllScreen(void)
{
	u8 buf[]={0x49,0x00};
	makeAndSendMessageToModule(MODULE_ID_KEY,MODULE_ID_BACK,buf,2);
}

void SendKeyValueToOSDDebug(u8 keyVal)
{
	u8 buf[256]={0};
	buf[0]=0x08;
	char strSound[128]={0};
	
	sprintf(strSound,"KEY_KeyVal:0x%x",keyVal);
	memcpy(&buf[1],strSound,strlen(strSound));
	u8 len=strlen(strSound)+2;

	makeAndSendMessageToModule(MODULE_ID_OSD, MODULE_ID_SYSTEM, buf,len);
}

void keyToSystemModule_About_SmartFan_Telecontrol(u8 param)
{
    unsigned char pBuf[] = {0x00,0x02,param};
    makeAndSendMessageToModule(MODULE_ID_KEY,MODULE_ID_SYSTEM,pBuf,3);
}

void keyToSystemModule_About_LCD_Telecontrol(u8 param)
{
    unsigned char pBuf[] = {0x00,0x04,param};
    makeAndSendMessageToModule(MODULE_ID_KEY,MODULE_ID_SYSTEM,pBuf,3);
}


void keyToSystemModule_About_FanMode_PerformanceSwitch(u8 param)
{
    unsigned char pBuf[] = {0x00,0x05,param};
    makeAndSendMessageToModule(MODULE_ID_KEY,MODULE_ID_SYSTEM,pBuf,3);

}

void keyToSystemModule_About_AntotoItsOpen(u8 param)
{
    unsigned char pBuf[] = {0x00,0x06,param};
    makeAndSendMessageToModule(MODULE_ID_KEY,MODULE_ID_SYSTEM,pBuf,3);
}

void keyToExtcarModule_Notify_Prado_KeyInfo(u8 param)
{
	 unsigned char pBuf[] = {0x84,param};
	 makeAndSendMessageToModule(MODULE_ID_KEY,MODULE_ID_EXTCAR,pBuf,sizeof(pBuf));
}

void keyToExtcarModule_NotifyExternalCtrl_SpeechKeyInfo(u8 p)
{
	 unsigned char pBuf[] = {0x01,p};
	 makeAndSendMessageToModule(MODULE_ID_KEY,MODULE_ID_EXTERNALCTRL,pBuf,sizeof(pBuf));
}



