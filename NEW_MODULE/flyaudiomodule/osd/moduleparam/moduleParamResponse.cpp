#include <stdio.h>
#include <stdlib.h>
#include <param.h>
#include "global.h"
#include "moduleParamResponse.h"
#include "timer_interface.h"
#include "halRequestFunction.h"


void moduleParameterInit(void){
	//initTimerCenter(&TimerHandlerCenter);
}

void moduleParameterDeInit(void){

}

void OSDModule_SetDefaultParam()
{
	pLocalParam->osddebuginfo_switch = false;

	pLocalParam->uKey_OSDEvent = 0;
	pLocalParam->m_nCurOSDContent=-1;
	pLocalParam->m_haveRadar =0x00;

	pLocalParam->nLanguageType=0;//����
	pLocalParam->bOnSystemPage=false;
	pLocalParam->bBackcarThreeAngle = false;
	pLocalParam->bNoShowACosdState = 0;
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		case OSD_EVENT://Drop OSD display track and DVD track non-corresponding problem
			*param = pLocalParam->uKey_OSDEvent;
			*paramLen = 1;
		break;
		default:break;
	}
}

void moduleParameterReInit(void){
	LOGD("&&&&&&&&&&&&&&&&&&&& osd moduleParameterReInit");
	moduleParameterInit();
}
int module_extendInterface(char *buffer, int len){
	LOGD("***************osd module_extendInterface:%x,%x",buffer[0],buffer[1]);
    char extenCmd = buffer[0];
    char extenParam = buffer[1];
    switch(extenCmd)
    {
         case 0x2C: //ACC Off Or Reset Or Default
             {
                 if(extenParam == 0x00) //Acc Off
                 {       
                     saveParameter();
                 }
                 else if(extenParam == 0x01)
                 {
                     saveParameter();
                 }
                 else if(extenParam == 0x02)
                 {
                    OSDModule_SetDefaultParam();
                    saveParameter();
                 }
             }
             break;
         case 0x2D: //ACC On
             {
                pLocalParam->bDropDownOSD_Switch = true;
                OSDModuleParameterToT123_aboutLanguageType();
             }
             break;
         case 0xFD:
             {
                pLocalParam->bDropDownOSD_Switch = false;
                SetTimer(OSDTIME_DROP_DOWN_SWITCH,1,OSD_TIMER_DROP_DOWN_SWITCH);
                OSDModuleParameterToT123_aboutLanguageType();
             }
             break;
         case 0xFE:
             {
             }
             break;
         default:break;
     }

	return 0;
}

void OSDModuleParameterToT123_aboutLanguageType()
{
    LOGD("OSDModuleParameterToT123_aboutLanguageType pLocalParam->nLanguageType:%D",pLocalParam->nLanguageType);
    u8 buff[]={0xE0,pLocalParam->nLanguageType};
    SetOSDUIValue_OSDToHal(buff,2);
}

