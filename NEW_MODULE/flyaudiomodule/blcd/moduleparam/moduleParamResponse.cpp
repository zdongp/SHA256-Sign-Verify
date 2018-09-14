#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "moduleParamResponse.h"
#include "otherModuleRequestFunction.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"

void moduleParameterInit(void){
}

void moduleParameterDeInit(void){

}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		default:break;
	}
}

void SetDefaultParam()
{
	pLocalParam->setMode=emSetBlcdMode_DVD;	
	pLocalParam->audioMode=SoundMode_IPOD;
	
}

void initByConfig(void){
	readParameter();
	switch (pLocalParam->setMode)
	{
	case emSetBlcdMode_DVD:
		Set_Mode(emSetBlcdMode_DVD);
		pLocalParam->getMode=emBlcdMode_DVD;
		//m_pCenterModule->Set_Mode(emBlcdMode_DVD);
		break;
	case emSetBlcdMode_CDC_TV:
		Set_Mode(emSetBlcdMode_CDC_TV);
		pLocalParam->getMode=emBlcdMode_CDC;
		//m_pCenterModule->Set_Mode(emBlcdMode_CDC);
		break;
	case emSetBlcdMode_AUX:
		Set_Mode(emSetBlcdMode_AUX);
		pLocalParam->getMode=emBlcdMode_AUX;
		//m_pCenterModule->Set_Mode(emBlcdMode_AUX);
		break;
	case emSetBlcdMode_Radio:
		Set_Mode(emSetBlcdMode_Radio);
		pLocalParam->getMode=emBlcdMode_Radio;
		//m_pCenterModule->Set_Mode(emBlcdMode_Radio);
		break;
	default:
		Set_Mode(emSetBlcdMode_DVD);
		pLocalParam->getMode=emBlcdMode_DVD;
		//m_pCenterModule->Set_Mode(emBlcdMode_DVD);
		break;
	}
	Show_Blcd_Mode();


}


void moduleParameterReInit(void){
	LOGD("&&&&&&&&&&&&&&&&&&&& backcar moduleParameterReInit");
}
int module_extendInterface(char *buffer, int len){
	int extendCmd = buffer[0];
	int extendParam = buffer[1];
	LOGD("**************************BLCD module_extendInterface:%x,%x",extendCmd,extendParam);
	switch(extendCmd)
	{
		case 0x2C:
			if(extendParam == 0x00)//acc off
			{
				LOGD("Module_Blcd ----> Acc Off");
			}
			else if(extendParam == 0x01)// 
			{
				LOGD("Module_Blcd ----> Acc restart");
			}
			else if(extendParam == 0x02)//default
			{
				Set_RestoreToFactoryDefaults();
			}
			break;
		case 0x2D:
			if(extendParam == 0x00) //acc on
			{
				LOGD("Module_Blcd ----> Acc On");
			}
			break;
		case 0xFD:
			{
				blcdToHal_Init(0x01);
				initByConfig();
			}
			break;
		default:break;	
	}	
	
	return 0;
}

