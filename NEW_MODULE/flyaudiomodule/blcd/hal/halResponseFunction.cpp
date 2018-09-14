#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestCommand.h"

void analyseHalMessage_BLCD(char resCmd, unsigned char *param, unsigned char len){
	switch(resCmd){
		case 0x01:
			//halToBlcd_InitParam(param[0]);
			break;
		case 0x02:
		   // halToBlcd_InitState(param[0]);
			break;
		case 0x10:{
				//unsigned short curFreq = 0;
				//curFreq = (unsigned short)(((param[1] << 8) & 0xFF00) + (param[0] & 0xFF));
				//halToRadio_Frequency(curFreq);
			}
			break;
		case 0x11:
			//halToRadio_ScanCtrlState(param[0]);
			break;
		default:
			break;
	}
}


void Show_CDC_PlayControl(u8 previousAnolog,u8 playAnolog,u8 stopAnolog,u8 nextAnolog){

	setAnalogData(CONTROLID_BLCD_MAIN_PLAYPAUSE,previousAnolog);
	setAnalogData(CONTROLID_BLCD_MAIN_STOP,playAnolog);
	setAnalogData(CONTROLID_BLCD_MAIN_PREV,stopAnolog);
	setAnalogData(CONTROLID_BLCD_MAIN_NEXT,nextAnolog);
	if(previousAnolog == 2 && playAnolog == 2 && stopAnolog == 2 && nextAnolog == 2){
		setControllable(CONTROLID_BLCD_MAIN_PLAYPAUSE,0);
		setControllable(CONTROLID_BLCD_MAIN_STOP,0);
		setControllable(CONTROLID_BLCD_MAIN_PREV,0);
		setControllable(CONTROLID_BLCD_MAIN_NEXT,0);
	}
	else
		{
		setControllable(CONTROLID_BLCD_MAIN_PLAYPAUSE,1);
		setControllable(CONTROLID_BLCD_MAIN_STOP,1);
		setControllable(CONTROLID_BLCD_MAIN_PREV,1);
		setControllable(CONTROLID_BLCD_MAIN_NEXT,1);
	}

}

void Show_Blcd_Mode(){
	LOGD("Show_Blcd_Mode pLocalParam->getMode:%x pLocalParam->audioMode:%x",pLocalParam->getMode,pLocalParam->audioMode);
	if(pLocalParam->getMode == emBlcdMode_DVD){
		setDigitalData(CONTROLID_BLCD_MAIN_DVD,2);
		//setDigitalData(CONTROLID_BLCD_MAIN_CDC_TV,0);
		if(SoundMode_DVD != pLocalParam->audioMode && VideoMode_DVD != pLocalParam->audioMode)
		{
			Show_CDC_PlayControl(0,0,0,0);
		}
		else{
			Show_CDC_PlayControl(2,2,2,2);
		}
	}
	else{
		setAnalogData(CONTROLID_BLCD_MAIN_DVD,0);
		//setAnalogData(CONTROLID_BLCD_MAIN_CDC_TV,3);
		Show_CDC_PlayControl(2,2,2,2);
	}
}
void halToBLCD_SetMode(u8 param){
	unsigned char buff[2]={0x01,param};
	makeAndSendMessageToModule(MODULE_ID_BLCD,MODULE_ID_DVD,buff,2);
}

void Get_Mode(u8 param){
	pLocalParam->getMode = param;
	Show_Blcd_Mode();
	halToBLCD_SetMode(param);
}

