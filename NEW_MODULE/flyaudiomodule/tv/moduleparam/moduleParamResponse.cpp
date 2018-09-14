#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleParamResponse.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "param.h"
#include "timer_interface.h"
#include "controlID.h"
#include "pageID.h"
#include "appRequestCommand.h"
#include "otherModuleRequestFunction.h"


void moduleParameterInit(void){
	//参数初始化，应该有另外的接口来初始化才对
	
	LOGD("----------TV--------moduleParameterInit-----------------");
	
}
void setDefaultParam(){
     pLocalParam->nIsBrakeState = 1;//是否有刹车状态 back car
     pLocalParam->nIsTVModuleExite = 0;//是否有电视模块
     pLocalParam->nIsTVDriverInit = 0;//是否初始化完成

}

void initByConfig(){
	
	LOGD("-------TV----initByConfig-------------");
	
	tvToHal_Init();
	
	setAnalogData(CONTROLID_TV_VIDEO_SET_COLOUR_GAUGE, 5);
	setAnalogData(CONTROLID_TV_VIDEO_SET_CHROMINANCE_GAUGE, 5);
	setAnalogData(CONTROLID_TV_VIDEO_SET_CONTRAST_GAUGE, 5);
	setAnalogData(CONTROLID_TV_VIDEO_SET_BRIGHTNESS_GAUGE, 5);
}  
void moduleParameterDeInit(void){
       
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		default:break;
	}
}
void moduleParameterReInit(void)
{
}


int module_extendInterface(char *buffer, int len)
{
	   LOGD("********************TV module_extendInterface:%x,%x",buffer[0],buffer[1]);
	   char extenCmd = buffer[0];
	   char extenParam = buffer[1];
	   switch(extenCmd)
	   	{
		case 0x2C: //ACC Off Or Reset Or Default
			{
				if(extenParam == 0x00) //Acc Off
					{
						TvModule_Process_AccOff();
					}
				else if(extenParam == 0x01)//Reset
					{
						TvModule_Process_Reset();
					}
				else if(extenParam == 0x02)//Reset default
					{
						TvModule_Process_ResetDefault();
					}
			}
			break;
		case 0x2D: //ACC On
			{
				TvMoudule_Process_AccOn();
			}
			break;
		case 0xFD:
			{
				initByConfig();
				//initTimerCenter(&TimerHandlerCenter);
			}
			break;
		default:break;
	   }
	   
	  return 0;
}

void TvModule_Process_AccOff()
{
	LOGD("+++AccOff+++");
	saveParameter();
	setDefaultParam();
}
void TvMoudule_Process_AccOn()
{
	LOGD("+++AccOn+++");
	readParameter();
	saveParameter();
	tvToHal_Init();	
}
void TvModule_Process_Reset()
{
	LOGD("+++Reset(+++");
    saveParameter();
}
void TvModule_Process_ResetDefault()
{
	LOGD("+++ResetDefault+++");
	setDefaultParam();
	saveParameter();
}



