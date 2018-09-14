#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "flytypes.h"
#include "moduleParamRequest.h"

#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"


void otherModuleInit(void){

}

void otherModuleDeInit(void){

}
moduleid_t ModuleIDToChannel(short sChannel)
{
	moduleid_t modeId=0;
	 switch(sChannel){
    	case 0x00://DVD ctrl
    	case 0x01://DVD video
        	modeId = MODULE_ID_DVD;
        	break;
    	case 0x02: //CDC ctrl
    	case 0x03: //cdc video
       		// cToMode = Module_CDC;
        	break;
    	case 0x04: //RADIO
        	modeId = MODULE_ID_RADIO;
        	break;
    	case 0x05://AUX ctrl
    	case 0x06://aux video
        	modeId = MODULE_ID_AUX;
        	break;
    	case 0x07: //IPOD ctrl
    	case 0x08://ipod video
        	modeId = MODULE_ID_IPOD;
        	break;
    	case 0x09://TV ctrl
    	case 0x0A://tv video
      		modeId = MODULE_ID_TV;
        	break;
    	case 0x0B: //MEDIA
			modeId = MODULE_ID_MEDIA;
        	break;
		case 0x0D:
			modeId = MODULE_ID_BT;
			break;
		case 0x0E: //����
			modeId = MODULE_ID_MEDIA;
			break;
		case 0x11:
		case 0x12:
			modeId = MODULE_ID_DVR;
			break;
    	default:
        	break;
        }
	 return modeId;
}

bool AuxscreenModule_AccordingToTheChannelAndGetModuleID(moduleid_t sendModuleId)
{
		short curSound = 0;
		unsigned char curSoundLen = 2;
		getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8 *)&curSound, (u8 *)&curSoundLen);
		moduleid_t curModeId = 0;
		curModeId = ModuleIDToChannel(curSound);
		if(MODULE_ID_DVD == sendModuleId 
			|| MODULE_ID_RADIO == sendModuleId
			|| MODULE_ID_MEDIA == sendModuleId
			|| MODULE_ID_BT == sendModuleId)
		{
			if(curModeId != sendModuleId)
				return true;
		}


		return false;

}

void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){

	LOGD("[%s] sendModuleId:%x param[0]:%x param[1]:%d param[2]:%d",__FUNCTION__,sendModuleId,param[0],param[1],param[2]);

	switch(sendModuleId){
		case MODULE_ID_DVD:
			moduleToAuxScreen_FromDVD_message(param,len);
			break;
		case MODULE_ID_RADIO:
			moduleToAuxScreen_FromRadio_message(param,len);
			break;		
		case MODULE_ID_BT:
			moduleToAuxScreen_FromBT_message(param,len);
			break;
		case MODULE_ID_AUXSCREEN://�ɸ���С����С����Э��
			moduleToAuxScreen_FromAUXscreen_message(param,len);
			break;
		case MODULE_ID_AUDIOVIDEO:
			moduleToAuxScreen_FromAudioVideo_message(param,len);
			break;
		case MODULE_ID_SYSTEM:
			moduleToAuxScreen_FromSystem_Message(param, len);
			break;
		case MODULE_ID_MEDIA:
			moduleToAuxScreen_FromMedia_Message(param, len);
			break;
		case MODULE_ID_GPS:
			moduleToAuxScreen_FromGPS_Message(param, len);
			break;
		case MODULE_ID_EXTCAR:
			moduleToAuxScreen_FromExtcar_Message(param, len);
		    break;
		default:break;
	}
}

void analyseTimerHandleMessage(u8 *p, u8 len)
{
	timer_t tId = (timer_t)0xFFFFFF;
	memcpy(&tId,p+3,sizeof(timer_t));
}

