#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "appRequestFunction.h"
#include "appResponseCommand.h"
#include "halRequestFunction.h"

#include "param.h"
void appInit(void){
	//systemToApp_Init();
}

void appDeInit(void){

}


void analyseAppMessage(unsigned char *buffer, unsigned char len){
	int ctrlId = 0;
	char ctrlType;
	unsigned char paramLen;
	unsigned char *param;
	u8 u8_MouseStatus = 0;

	ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
	ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
	ctrlId += (int)((buffer[2] << 8) & 0xFF00);
	ctrlId += (int)(buffer[3] & 0xFF);


	ctrlType = buffer[4];
	u8_MouseStatus = buffer[5];
	paramLen = len - 5;
	param = &buffer[5];

	LOGD("service analyseAppMessage ctrlId:%x,ctrlType:%x paramLen:%x",ctrlId,ctrlType,paramLen);
	if(ctrlId == CONTROLID_SERVICE_DEDICATE_INFORMATION && ctrlType == 0xFE)
	{
		switch(param[0])
		{
			case 0x01:
			{
				appToService_GeneralKnobPasswd(&param[1],paramLen-1);
			}
			break;
			case 0x02:
			{
				service_GetIMEI(&param[1],paramLen-1);
			}
			break;
			case 0x03:
			{
				service_GetMAC(&param[1],paramLen-1);
			}
			break;
			case 0x04:
			{
				service_GetWifiConnectStatus(&param[1],paramLen-1);
			}
			break;
			case 0x05:
			{
				service_GetWifiNetworkSignalStrength(&param[1],paramLen-1);
			}
			break;
			case 0x06:
			{
				service_Get4GNetworkSignalStrength(&param[1],paramLen-1);
			}
			break;
			case 0x07:
			{
				service_GetSD1_Status(&param[1],paramLen-1);
			}
			break;
			case 0x08:
			{
				service_GetMemoryUsageSd1(&param[1],paramLen-1);
			}
			break;
			case 0x09:
			{
				service_GetTheTotalSizeSd1(&param[1],paramLen-1);
			}
			break;
			case 0x0A:
			{
				service_GetMemoryUsageSd0(&param[1],paramLen-1);
			}
			break;
			case 0x0B:
			{
				service_GetTheTotalSizeSd0(&param[1],paramLen-1);
			}
			break;
			case 0x0C:
			{
				service_GetUsingNetworkStatus_WiFi(&param[1],paramLen-1);
			}
			break;
			case 0x0D:
			{
				service_GetUsingNetworkStatus_4G(&param[1],paramLen-1);
			}
			break;
			default:break;
		}
	}

	switch(ctrlType)
    	{
    	   case UIACTION_MOUSEDOWN:
			    break;
		   case UIACTION_MOUSEUP:
		        break;
			case UIACTION_MOUSETIMER:
				break;
		 defualt:break;
    	}
	
}


void appToService_GeneralKnobPasswd(u8 *buf,u8 len)
{
	for(int i=0;i<len;i++)
	{
		LOGD("buf:%d",buf[i]);
	}
	
	int nTemp = buf[0]*256*256*256+buf[1]*256*256+buf[2]*256+buf[3];
	LOGD("nTemp:%d",nTemp);
	
	u8 buffer[len];
	memset(buffer,0,sizeof(buffer));
	for(int i=len -1;i>=0;i--)
	{
		buffer[i]=nTemp%10;
		nTemp=nTemp/10;
	}

	service_to_hal_SetGeneralKnobPassword(buffer,len);

}


void service_GetIMEI(u8 *buf,u8 len)
{
	memset(pLocalParam->uc_IMEI_Infors,0,INFORS_MAX_LEN);
	memcpy(pLocalParam->uc_IMEI_Infors,buf,len);
	LOGD("[%s] IMEI:%s",__FUNCTION__,pLocalParam->uc_IMEI_Infors);
}

void service_GetMAC(u8 *buf,u8 len)
{
	memset(pLocalParam->uc_MAC_Infors,0,INFORS_MAX_LEN);
	memcpy(&pLocalParam->uc_MAC_Infors,buf,len);
	LOGD("[%s] MAC:%s",__FUNCTION__,pLocalParam->uc_MAC_Infors);
}

void service_GetWifiConnectStatus(u8 *buf,u8 len)
{
	pLocalParam->uc_WIFI_Status = buf[0];
	
	if(buf[0] == 0)
	{
		pLocalParam->uc_WIFI_NetworkSignal = 0;
		pLocalParam->uTheNetworkStatus_WiFi = 0;
	}
	LOGD("[%s] uc_WIFI_Status:%d",__FUNCTION__,pLocalParam->uc_WIFI_Status);
}

void service_GetWifiNetworkSignalStrength(u8 *buf,u8 len)
{
	pLocalParam->uc_WIFI_NetworkSignal = buf[0]*256 + buf[1];
	LOGD("[%s] uc_WIFI_NetworkSignal:%d",__FUNCTION__,pLocalParam->uc_WIFI_NetworkSignal);
}

void service_Get4GNetworkSignalStrength(u8 *buf,u8 len)
{
	pLocalParam->uc_4G_NetworkSignal = buf[1]*256 + buf[2];
	LOGD("[%s] uc_4G_NetworkSignal:%d",__FUNCTION__,pLocalParam->uc_4G_NetworkSignal);
}

void service_GetSD1_Status(u8 *buf,u8 len)
{
	pLocalParam->uCurSd1Status = buf[0]; 
	if(pLocalParam->uCurSd1Status == 0)
	{
		memset(pLocalParam->uc_MemoryUsageSd1_Infors,0,INFORS_MAX_LEN);
		memset(pLocalParam->uc_TotalSizeSd1_Infors,0,INFORS_MAX_LEN);
	}
	LOGD("[%s] SD1 uCurSd1Status:%d",__FUNCTION__,pLocalParam->uCurSd1Status);
}

void service_GetMemoryUsageSd1(u8 *buf,u8 len)
{
	memset(pLocalParam->uc_MemoryUsageSd1_Infors,0,INFORS_MAX_LEN);
	memcpy(pLocalParam->uc_MemoryUsageSd1_Infors,buf,len);
	LOGD("[%s] SD1 uc_MemoryUsageSd1_Infors:%s",__FUNCTION__,pLocalParam->uc_MemoryUsageSd1_Infors);
}

void service_GetTheTotalSizeSd1(u8 *buf,u8 len)
{
	memset(pLocalParam->uc_TotalSizeSd1_Infors,0,INFORS_MAX_LEN);
	memcpy(pLocalParam->uc_TotalSizeSd1_Infors,buf,len);
	LOGD("[%s] SD1 uc_TotalSizeSd1_Infors:%s",__FUNCTION__,pLocalParam->uc_TotalSizeSd1_Infors);
}

void service_GetMemoryUsageSd0(u8 *buf,u8 len)
{
	memset(pLocalParam->uc_MemoryUsageSd0_Infors,0,INFORS_MAX_LEN);
	memcpy(pLocalParam->uc_MemoryUsageSd0_Infors,buf,len);
	LOGD("[%s] SD0 uc_MemoryUsageSd0_Infors:%s",__FUNCTION__,pLocalParam->uc_MemoryUsageSd0_Infors);
}

void service_GetTheTotalSizeSd0(u8 *buf,u8 len)
{
	memset(pLocalParam->uc_TotalSizeSd0_Infors,0,INFORS_MAX_LEN);
	memcpy(pLocalParam->uc_TotalSizeSd0_Infors,buf,len);
	LOGD("[%s] SD0 uc_TotalSizeSd0_Infors:%s",__FUNCTION__,pLocalParam->uc_TotalSizeSd0_Infors);
}

void service_GetUsingNetworkStatus_WiFi(u8 *buf,u8 len)
{
	pLocalParam->uTheNetworkStatus_WiFi = buf[0];
	LOGD("[%s] uTheNetworkStatus_WiFi:%d",__FUNCTION__,pLocalParam->uTheNetworkStatus_WiFi);
}

void service_GetUsingNetworkStatus_4G(u8 *buf,u8 len)
{
	pLocalParam->uTheNetworkStatus_4G = buf[0];
	LOGD("[%s] uTheNetworkStatus_4G:%d",__FUNCTION__,pLocalParam->uTheNetworkStatus_4G);
}


