#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "moduleParamResponse.h"
#include "halRequestFunction.h"


void moduleParameterInit(void){
	LOGD("moduleParameterInit");
}

void moduleParameterDeInit(void){

}

void moduleParameterReInit(void){
	moduleParameterInit();
}

int module_extendInterface(char *buffer, int len){
	LOGD("*************************extcar tsu module_extendInterface:%x,%x", buffer[0], buffer[1]);
	switch(buffer[0])
	{
		case 0x2C:
			if(buffer[1] == 0x00)//acc off
			{
				saveParameter();
			}
			if(buffer[1] == 0x01)//restart
			{	
				saveParameter();
			}
			if(buffer[1] == 0x02)//default
			{
				setDefaultParam();
				saveParameter();
			}
			break;
		case 0x2D://acc on
			if(buffer[1] == 0x00)
			{
				initByConfig();
			}
			break;
		case 0xFD:
			{				
				initByConfig();
			}
			break;
		default:break;
	}

	return 0;
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen)
{
	switch(paramId)
	{
	}
}

void setDefaultParam(void)
{
}

void initByConfig(void)
{
	extcarToHal_Init(0x01);
}


