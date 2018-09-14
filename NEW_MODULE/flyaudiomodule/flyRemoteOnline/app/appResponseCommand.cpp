#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "appRequestFunction.h"
#include "appResponseCommand.h"
#include "appRequestCommand.h"
#include "halRequestFunction.h"
#include "param.h"
#include "otherModuleRequestFunction.h"

extern int nCarInforPushTimes;

void appInit(void){
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
	paramLen = len - 6;
	param = &buffer[6];

	if(ctrlId == 0x52FFFF && ctrlType == 0xFF)
	{
		if(u8_MouseStatus == 0x52){
			appToRemoteOnline(param,paramLen);
		}
	}
}


void appToRemoteOnline(u8 *p,u8 len)
{
	LOGD("[%s] Module_RemoteOnline p[0]:%x ,p[1]:%x,p[2]:%x,p[3]:%x,p[4]:%x", __FUNCTION__,p[0],p[1],p[2],p[3],p[4],p[5]);
	LOGD("[%s] Module_RemoteOnline p[5]:%x", __FUNCTION__,p[5]);


	pLocalParam->eRequestObject = (E_REMOTE_REQUEST_OBJECT)p[1];
	
	switch(p[2])
	{
		case 0x01://extcar information
		{
			if(p[1] == 0x02)
			{
				if(pLocalParam->emCur_CD_State){
					MobileRequestModule_updataExtcarInfors();
				}
				else{
					nCarInforPushTimes = 0;
					ACCoffMobileRequestModule_updataExtcarInfors();
				}
			}
			else if(p[1] == 0x03)
			{
				if(pLocalParam->emCur_CD_State){
					WeChatRequestModule_updataExtcarInfors();
				}
				else{
					nCarInforPushTimes = 0;
					ACCoffWeChatRequestModule_updataExtcarInfors();
				}
			}
		}
		break;
		case 0x02://control
		{
			switch(p[5])
			{
				case '1'://POWER OFF
				RemoteOnlineCtrl_PowerOff(p[6]);
				break;
				case '2'://LED
				RemoteOnlineCtrl_Led(p[6]);
				break;
				default:break;
			}
		}
		break;
		default:break;
	}

}

void MobileRequestModule_updataExtcarInfors()
{
	u8 buff[500] = {0};
	u32 len = 0;
		
	buff[0] = 0;
	buff[1] = 2;
	buff[2] = 1;
	buff[3] = 0;
	buff[4] = 24;

	len = CAR_INFORS_LEN;
	
	memcpy(&buff[5],pLocalParam->uExtcarInformation,len);
	setToExtcarModule_RemoteOnlineMsg(buff,len + 5);
}

void WeChatRequestModule_updataExtcarInfors()
{
	return;
	
	u8 buff[500] = {0};
	u32 len = 0;
	
	buff[0] = 0;
	buff[1] = 2;
	buff[2] = 1;
	buff[3] = 0;
	buff[4] = 23;
	len = CAR_INFORS_LEN;
	memcpy(&buff[5],pLocalParam->uExtcarInformation,len);
	//setToExtcarModule_RemoteOnlineMsg(buff,len + 5);
}

void ACCoffMobileRequestModule_updataExtcarInfors()////
{
	u8 buff[500] = {0};
	u32 len = 0;
	
	buff[0] = 0;
	buff[1] = 2;
	buff[2] = 1;
	buff[3] = 0;
	buff[4] = 24;

	len = CAR_INFORS_LEN;
	memcpy(&buff[5],pLocalParam->uAccOffExtcarInformation,len);
	buff[CAR_INFORS_LEN + 5] = 0xFF;
	
	setToExtcarModule_RemoteOnlineMsg(buff,len + 6);
}

void ACCoffWeChatRequestModule_updataExtcarInfors()////
{
	u8 buff[500] = {0};
	u32 len = 0;
	
	buff[0] = 0;
	buff[1] = 2;
	buff[2] = 1;
	buff[3] = 0;
	buff[4] = 23;

	len = CAR_INFORS_LEN;
	memcpy(&buff[5],pLocalParam->uAccOffExtcarInformation,len);
	buff[23] = 0xFF;
	
	//setToExtcarModule_RemoteOnlineMsg(buff,len + 6);
}


void MobileRequestModule_updataLedState()
{
	u8 buff[500] = {0};
	buff[0] = 0;
	buff[1] = 2;
	buff[2] = 2;
	buff[3] = 0;
	buff[4] = 24;
	buff[5] = (u8)pLocalParam->eLCDState;
	
	setToExtcarModule_RemoteOnlineMsg(buff,6);
}

void WeChatRequestModule_updataLedState()
{
	u8 buff[500] = {0};
	buff[0] = 0;
	buff[1] = 2;
	buff[2] = 2;
	buff[3] = 0;
	buff[4] = 23;
	buff[5] = (u8)pLocalParam->eLCDState;
	
	//setToExtcarModule_RemoteOnlineMsg(buff,6);

}


void RemoteOnlineCtrl_Led(u8 param)
{
	int nTemState = -1;
	switch(param)
	{
		case '0':
			nTemState = 0;
			break;
		case '1':
			nTemState = 1;
			break;
		case '2':
			nTemState = 2;
			break;
		case '3':
			nTemState = 3;
			break;
		default:
			return;
			break;
	}
	
	RemoteToModule_NotifySystem_ChangeLightness((u8)nTemState);
}

void RemoteOnlineCtrl_PowerOff(u8 param)
{
	switch(param)
	{
		case '1':
			if(pLocalParam->uCurCarNaviDeviceState == 1){
				RemoteToModule_NotifySystem_RemoteOnlineControlPowerOff(0x01);
			}
		break;
		default:
		return;
		break;
	}
}

void setToExtcarModule_RemoteOnlineMsg(u8 *p,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = 0x52;
	
	if(len > 256)
		len = 256;
	
	memcpy(szMsg + 1, p, len);
	LOGD("[%s] %x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x",__FUNCTION__,p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],p[11],p[12],p[13],p[14],p[15],p[16],p[17],p[18],p[19],p[20],p[21],p[22],p[23],p[24],p[25],p[26],p[27]);
	setCommand(0x52FFFF, szMsg, len+1);
}

