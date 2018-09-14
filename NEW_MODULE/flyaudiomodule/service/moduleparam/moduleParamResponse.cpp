#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <linux/kernel.h>
#include <errno.h>
#include <sys/ioctl.h>

#include "param.h"
#include "global.h"
#include "controlID.h"
#include "moduleParamResponse.h"
#include "pageID.h"
#include "appRequestCommand.h"
#include "halRequestFunction.h"
#include "halResponseFunction.h"

extern "C"{
#include "unicodestring.h"
};

int module_extendInterface(char *buffer, int len)
{
   char extenCmd = buffer[0];
   char extenParam = buffer[1];
   LOGD("*********************service module_extendInterface:%x,%x",extenCmd,extenParam);
   switch(extenCmd)
   	{
		case 0x2C: //ACC Off Or Reset Or Default
		    if(extenParam == 0x02)
		    {
		        ServiceModule_SetDefaultParam();
		    }
			break;
		case 0x2D: //ACC On
			break;
		case 0xFD:
			//setModulesInitCompleted();
			break;
		default:break;
   	}
   	
   return 0;
}

void ServiceModule_SetDefaultParam()
{
	memset(pLocalParam->uc_Barcode,0,INFORS_MAX_LEN);
	memset(pLocalParam->uc_IMEI_Infors,0,INFORS_MAX_LEN);
	memset(pLocalParam->uc_MAC_Infors,0,INFORS_MAX_LEN);
	pLocalParam->uc_WIFI_Status = 0;
	pLocalParam->uc_WIFI_NetworkSignal = 0;
	pLocalParam->uc_4G_NetworkSignal = 0;
	memset(pLocalParam->uc_MemoryUsageSd1_Infors,0,INFORS_MAX_LEN);
	memset(pLocalParam->uc_TotalSizeSd1_Infors,0,INFORS_MAX_LEN);
	memset(pLocalParam->uc_MemoryUsageSd0_Infors,0,INFORS_MAX_LEN);
	memset(pLocalParam->uc_TotalSizeSd0_Infors,0,INFORS_MAX_LEN);
	pLocalParam->uCurSd1Status = 0;
	pLocalParam->uTheNetworkStatus_WiFi = 0;
	pLocalParam->uTheNetworkStatus_4G = 0;
}


void moduleParameterInit(void){
}

void moduleParameterDeInit(void){

}

void moduleParameterReInit(void)
{
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
	    case BARCODE_INFO:
	        memcpy(param,pLocalParam->uc_Barcode,strlen((char*)pLocalParam->uc_Barcode));
	        *paramLen = strlen((char*)pLocalParam->uc_Barcode);
        break;
		 case IMEI_INFO:
		 	 memcpy(param,pLocalParam->uc_IMEI_Infors,strlen((char*)pLocalParam->uc_IMEI_Infors));
	        *paramLen = strlen((char*)pLocalParam->uc_IMEI_Infors);
		 break;
		 case WLAN_MAC_INFO:
		 	 memcpy(param,pLocalParam->uc_MAC_Infors,strlen((char*)pLocalParam->uc_MAC_Infors));
	        *paramLen = strlen((char*)pLocalParam->uc_MAC_Infors);
		 break;
		 case WIFI_CONNECT_STATUS:
			*(u8*)param = pLocalParam->uc_WIFI_Status;
			*paramLen = 1;
		 break;
		 case NETWORK_SIGNAL_WIFI:
		 	*(short*)param = pLocalParam->uc_WIFI_NetworkSignal;
			*paramLen = 2;
		 break;
		 case NETWORK_SIGNAL_4G:
		 	*(short*)param = pLocalParam->uc_4G_NetworkSignal;
			*paramLen = 2;
		 break;
		 case MEMORY_USAGE_SD1:
		 	 memcpy(param,pLocalParam->uc_MemoryUsageSd1_Infors,strlen((char*)pLocalParam->uc_MemoryUsageSd1_Infors));
	        *paramLen = strlen((char*)pLocalParam->uc_MemoryUsageSd1_Infors);
		 break;
		 case SDCARD1_STATUS:
		 	*(u8*)param = pLocalParam->uCurSd1Status;
			*paramLen = 1;
		 break;
		 case TOTAL_SIZE_SD1:
		 	 memcpy(param,pLocalParam->uc_TotalSizeSd1_Infors,strlen((char*)pLocalParam->uc_TotalSizeSd1_Infors));
	        *paramLen = strlen((char*)pLocalParam->uc_TotalSizeSd1_Infors);
		 break;
		 case MEMORY_USAGE_SD0:
		 	 memcpy(param,pLocalParam->uc_MemoryUsageSd0_Infors,strlen((char*)pLocalParam->uc_MemoryUsageSd0_Infors));
	        *paramLen = strlen((char*)pLocalParam->uc_MemoryUsageSd0_Infors);
        break;
		 case TOTAL_SIZE_SD0:
		 	 memcpy(param,pLocalParam->uc_TotalSizeSd0_Infors,strlen((char*)pLocalParam->uc_TotalSizeSd0_Infors));
	        *paramLen = strlen((char*)pLocalParam->uc_TotalSizeSd0_Infors);
		 break;
		 case NETWORK_WIFI_STATUS:
		 	*(u8*)param = pLocalParam->uTheNetworkStatus_WiFi;
			*paramLen = 1;
		 break;
		 case NETWORK_4G_STATUS:
			*(u8*)param = pLocalParam->uTheNetworkStatus_4G;
			*paramLen = 1;
	     break;
		default:break;
	}
}


