#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include "types_def.h"
#include "commonFunc.h"
//#include <cutils/properties.h>
#include <ctype.h>
#include <android/log.h>

#include "param.h"
#include "controlID.h"
#include "pageID.h"
#include "appRequestCommand.h"
#include "halRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "moduleParamResponse.h"


extern "C"{
#include "unicodestring.h"
};

#define FLY_EXTCAR_INFORS_ACCOFF  "fly.online.infors.accoff"
#define FLY_EXTCAR_INFORS_ACCON  "fly.online.infors.accon"


local_param_t localParam;
local_param_t *pLocalParam = (local_param_t*)&localParam;

global_param_t globalParam;
global_param_t *pGlobalParam = (global_param_t*)&globalParam;

char __intToChar(char value){
	if(value >= 0 && value <= 9){
		return (value+0x30);
	}
	else if(value >= 10 && value <=15){
		return (value + 0x37);
	}
	else{
		return '\0';
	}
}

char __charToInt(char ch){
	if(ch >= '0' && ch <= '9'){
		return (ch-0x30);
	}
	else if(ch >= 'A' && ch <= 'F'){
		return (ch-0x37);
	}
	else{
		return 0;
	}
}

int bufferToString(char *buffer, int len, char *str)
	{
		int n;
		int i , j;
		if(len <= 0 || len >= (PROPERTY_VALUE_MAX/2)){
			return -1;
		}

		for(i = 0, j=0; i < len; i++,j+=2){
			str[j] = __intToChar((buffer[i]&0xF0)>>4);
			str[j+1] = __intToChar((buffer[i]&0x0F));
		}
		str[2*len] = '\0';

		return (2*len+1);
	}

int stringToBuffer(char *str, char *buffer)
{
	int str_len = strlen(str);
	if(str_len <= 0)
		return 0;
	int i , j;
	for(i = 0, j=0; j < str_len; i++, j+=2){
		buffer[i] = __charToInt(str[j])<<4;
		buffer[i] += __charToInt(str[j+1]);
	}

	return (str_len/2);
}

void readParameter(void)
{
	LOGD("******[%s]******flyRemoteOnline",__FUNCTION__);

	char property[PROPERTY_VALUE_MAX];
	getProperty_acc_status();

	if(pLocalParam->uRealAccStatus == 0){
		initRemoteOnlineParam();
	}
}


void saveParameter(void)
{
	LOGD("******[%s]******flyRemoteOnline",__FUNCTION__);
	char property[PROPERTY_VALUE_MAX];
	bufferToString((char *)pLocalParam->uAccOffExtcarInformation, CAR_INFORS_LEN, property);
	property_set(FLY_EXTCAR_INFORS_ACCOFF,property);

	bufferToString((char *)pLocalParam->uExtcarInformation, CAR_INFORS_LEN, property);
	property_set(FLY_EXTCAR_INFORS_ACCON,property);

}

void getProperty_acc_status(void)
{
	char property[PROPERTY_VALUE_MAX];
	property_get("persist.lidbg.acc.status", property, "0");
   	sscanf(property,"%d", &pLocalParam->uRealAccStatus);
	LOGD("******[%s]******pLocalParam->uRealAccStatus:%d",__FUNCTION__,pLocalParam->uRealAccStatus);
}

void getProperty_Cur_carInfors(void)
{
	char property[PROPERTY_VALUE_MAX];
	int value = 0;
	char buffer[CAR_INFORS_LEN]={0};
	if(pLocalParam->uRealAccStatus == 1)
	{
		 property_get(FLY_EXTCAR_INFORS_ACCOFF, property, "0");
		 value = stringToBuffer(property, buffer);
		 if(value > 0){
		   	memcpy(pLocalParam->uAccOffExtcarInformation, buffer, CAR_INFORS_LEN);
		 }


		 value = 0;
		 buffer[CAR_INFORS_LEN]=0;
		 property_get(FLY_EXTCAR_INFORS_ACCON, property, "0");
		 value = stringToBuffer(property, buffer);
		 if(value > 0){
		   	memcpy(pLocalParam->uExtcarInformation, buffer, CAR_INFORS_LEN);
		 }
		 
	    Car_AsynchResetSystemOn_a_RegularBasis_Processing();
	}
}




