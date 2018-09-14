#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleParamResponse.h"
#include "param.h"
#include "paramID.h"

void moduleParameterInit(void){
    pLocalParam->uIsAgreePageHide = 0;
}

void moduleParameterDeInit(void){

}

void moduleParameterReInit(void){
	LOGD("&&&&&&&&&&&&&&&&&&&& center moduleParameterReInit");
}

int module_extendInterface(char *buffer, int len){
	LOGD("*****************Center module_extendInterface");
	char extenCmd = buffer[0];
    char extenParam = buffer[1];
    switch(extenCmd)
    {
         case 0x2C: //ACC Off Or Reset Or Default
             {
                 if(extenParam == 0x00) //Acc Off
                 {       
                 }
                 else if(extenParam == 0x01)
                 {
                 }
                 else if(extenParam == 0x02)
                 {
                 }
             }
             break;
         case 0x2D: //ACC On
             {
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
	    case CENTER_AGREEPAGE_ISHIDE:
	        *param = pLocalParam->uIsAgreePageHide;
	        *paramLen = 1;
	    break;
		default:break;
	}
}

