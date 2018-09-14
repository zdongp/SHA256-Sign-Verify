#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "moduleParamResponse.h"
#include "timer_interface.h"
#include "pageID.h"
#include "otherModuleRequestFunction.h"
#include "halRequestFunction.h"
#include "moduleParamRequest.h"
#include "appResponseFunction.h"


void moduleParameterInit(void){
	pLocalParam->bInAuxChannel = 0; 
	pLocalParam->bInSleep = false;
	pLocalParam->uSleepOnDealLogic = 0;

}

void moduleParameterDeInit(void){

}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		default:break;
	}
}

void InitByConfig(void){
	SetDefaultParam();/*不跳进AUX页面*/
}

void SetDefaultParam(){
	pLocalParam->bEnterAux = false;
	auxToApp_SetAUXVideo_Checking_Prompt_box(false);
	auxToApp_SetAUX_NoSignal_Prompt_box(false);
    pLocalParam->uAUX_VideoSwitch=0;
}


void moduleParameterReInit(){
	LOGD("&&&&&&&&&&&&&&&&& aux moduleParameterReInit");
	moduleParameterInit();
}

void AuxModule_Process_AccOff(){
	SetDefaultParam();/*不跳进AUX页面*/
	
	u16 CurPageID = 0;
	u8  CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
	if(CurPageID == PAGE_AUX_VIDEO || CurPageID == PAGE_AUX_VIDEO_CONTROL || CurPageID == PAGE_AUX_VIDEO_SET){
		auxToModule_NotifySystem_jumpPage(PAGE_AUX);//jump page to no video
	}
}

void AuxModule_Process_Reset(){
	SetDefaultParam();/*不跳进AUX页面*/
}

void AuxModule_Process_ResetDefault(){
	SetDefaultParam();
}

void AuxMoudule_Process_AccOn(){
}

int module_extendInterface(char *buffer, int len){
   char extenCmd = buffer[0];
   char extenParam = buffer[1];
   LOGD("************************aux module_extendInterface %x,%x",extenCmd,extenParam);
   switch(extenCmd){
   		case 0x2C: //ACC Off Or Reset Or Default
		{
			if(extenParam == 0x00) //Acc Off
			{
				AuxModule_Process_AccOff();
			}
			else if(extenParam == 0x01)//Reset
			{
				AuxModule_Process_Reset();
			}
			else if(extenParam == 0x02)//Reset default
			{
				AuxModule_Process_ResetDefault();
			}
		}
		break;
	case 0x2D: //ACC On
		{
			AuxMoudule_Process_AccOn();
		}
		break;
	case 0xFD:
		{
			InitByConfig();
			//initTimerCenter(&TimerHandlerCenter);
		}
		break;
	default:break;
   	}  
   return 0;
}





