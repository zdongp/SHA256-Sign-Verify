#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleParamResponse.h"
#include "param.h"

void moduleParameterInit(void){

}

void moduleParameterDeInit(void){

}

void moduleParameterReInit(void){
	LOGD("&&&&&&&&&&&&&&&&&&&& center moduleParameterReInit");
}

int module_extendInterface(char *buffer, int len){
	char extenCmd = buffer[0];
	char extenParam = buffer[1];
	LOGD("*******************externalctrl module_extendInterface:%x,%x",extenCmd,extenParam);
	switch(extenCmd)
	{
		case 0x1D:
			{
				if(extenParam == 0x00)//Standby on
				{
					externalctrlModule_SetDefaultParam();
				}
				else if(extenParam == 0x01)//Standby off
				{
				}
			}
			break;
		 case 0x2C: //ACC Off Or Reset Or Default
			 {
				 if(extenParam == 0x00) //Acc Off
				 {		 
				 }
				 else if(extenParam == 0x01) //reset
				 {
				 }
				 else if(extenParam == 0x02)//DF
				 {
				 }
			 }
			 break;
		 case 0x2D: //ACC On
			 {
			 	externalctrlModule_SetDefaultParam();
			 }
			 break;
		 case 0xFD:
			 {
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

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		case SPEECH_STATE:
			 *(u8*)param = (u8)pLocalParam->uCurSpeechState;
			 *paramLen = sizeof(u8);
			break;
		default:break;
	}
}

void externalctrlModule_SetDefaultParam()
{
	pLocalParam->bIsAutoJumpPrePage = false;
	pLocalParam->uCurSpeechState = 0;
}

