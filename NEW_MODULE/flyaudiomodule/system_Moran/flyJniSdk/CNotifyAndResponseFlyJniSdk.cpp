#include "CNotifyAndResponseFlyJniSdk.h"
#include "appResponseFunction.h"
#include "halRequestFunction.h"
#include "param.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"


#include "otherModuleResponseFunction.h"
CNotifyAndResponseFlyJniSdk:: CNotifyAndResponseFlyJniSdk()
{

}

CNotifyAndResponseFlyJniSdk:: ~CNotifyAndResponseFlyJniSdk()
{

}


void CNotifyAndResponseFlyJniSdk::moduleToSystem_FromFlyJniSdk(u8 *param, int len)
{
	LOGD("[%s] param[0]:%x,param[1]:%x",__FUNCTION__,param[0],param[1]);
	switch(param[0])
	{
		case 0x0A:
			if (param[1] == 1)
			{
				systemToHal_SetSystemUpdate();
			}
			else
			{
				appToUiDialogDisplaying_aboutSysUpdate(true);
			}
		break;
		case 0xF2:
			systemToHal_SetLCDBrightness(param[1]);
			break;
		case 0xF3:
			setToHalCloseOrTurnOnLightness(param[1]);
			break;
		case 0xF4:
			if(param[1] == 0)
			{
				systemToHal_SimulateKey(0x0c);
			}
			break;
		case 0xFE:
			analyseFormSdkMessage(param+1,len - 1);
			break;
		default:
			break;
	}
}

void CNotifyAndResponseFlyJniSdk::analyseSdkSetLightAddOrRedValue(u8 *param,int len)
{
	int temp = 0;
	int step = (AMBIENT_SCREEN_BRIGHTNESS_MAX -AMBIENT_SCREEN_BRIGHTNESS_MIN)/5;
	switch(param[0])
	{
		case 0x00:
		{
			if(param[1] == 0x00)
			{
				temp = pLocalParam->cBrightness_RangeValue - param[2];
				if(temp < AMBIENT_SCREEN_BRIGHTNESS_MIN)
				temp = AMBIENT_SCREEN_BRIGHTNESS_MIN;
			}
			else if(param[1] == 0x01)
			{
				temp = pLocalParam->cBrightness_RangeValue + param[2];
				if(temp > AMBIENT_SCREEN_BRIGHTNESS_MAX)
					temp = AMBIENT_SCREEN_BRIGHTNESS_MAX;
			}
		}
		break;
		case 0x01:
		{
			if(param[1] == 0x00)
			{
				temp = pLocalParam->cBrightness_RangeValue - step;
				if(temp < AMBIENT_SCREEN_BRIGHTNESS_MIN)
				temp = AMBIENT_SCREEN_BRIGHTNESS_MIN;
			}
			else if(param[1] == 0x01)
			{
				temp = pLocalParam->cBrightness_RangeValue + step;
				if(temp > AMBIENT_SCREEN_BRIGHTNESS_MAX)
					temp = AMBIENT_SCREEN_BRIGHTNESS_MAX;
			}
		}
		break;
		case 0x02:
			if(param[1] == 0x00)
			{
				temp = AMBIENT_SCREEN_BRIGHTNESS_MIN;
			}
			else if(param[1] == 0x01)
			{
				temp = AMBIENT_SCREEN_BRIGHTNESS_MAX;
			}
			break;
		default:break;
	}
	if(temp != 0)
		systemToHal_SetScreenBrightnessSpecificValue((u8)temp);
}
void CNotifyAndResponseFlyJniSdk::setToHalCloseOrTurnOnLightness(u8 param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	switch(param)
	{
		case 0x00:
			systemToHal_SetLCDBrightness(SYSTEMTOHAL_LCDBRIGHTNESS_BLACK);
			break;
		case 0x01:
			systemToHal_SetLCDBrightness( pLocalParam->u8_Sys_PreLcdLight );
			break;
		default:
			break;

	}
}
void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkSystemBrightnessMessage(u8 brightness)
{
	LOGD("[%s] brightness:%d",__FUNCTION__,brightness);
	unsigned char buf[] = {0x00,0x00};
	buf[1]=brightness;
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_FLYJNISDK,buf,2);
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkSystemFrontCameraApp(u8 p)
{
	u8 buf[] = {0x02,0x00};
	buf[1] = p;
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_FLYJNISDK,buf,sizeof(buf));
}


void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkRadarDate(u8 ForR,u8 *p,u8 len)
{
	if(len < 4)
	{
		LOGD("Radar Date error!!");
		return;
	}	
	unsigned char buf[10] = {0};
	buf[0] = 0x01;
	buf[1] = ForR;
	if(len > 4);
		len = 4;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_FLYJNISDK,buf,len +2);
}

void CNotifyAndResponseFlyJniSdk::sdkToSystemJumpPage(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x01:
			analyseSdkJumpPage_Bt(p[1]);
			break;
		case 0x05:
			analyseSdkJumpPage_Radio(p[1]);
			break;
		default:break;
	}
}

void CNotifyAndResponseFlyJniSdk::analyseSdkJumpPage_Bt(u8 param)
{
	switch(param)
	{
		case 0x01:
			break;
		default:break;
	}
}
void CNotifyAndResponseFlyJniSdk::analyseSdkJumpPage_Radio(u8 param)
{
	LOGD("[%s] param:%x",__FUNCTION__,param);
	switch(param)
	{
		case 0x01:
			switch_Page(PAGE_RADIO_MAIN);
			break;
		default:break;
	}
}
void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkBackCarStatus(u8 backcar)
{
	u8 buf[] = {0x03,backcar};
	sendToAppSystemStatusInfo(buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkSystemDayOrNightStatus(u8 nDayOrNight)
{
	LOGD("[%s] nDayOrNight:%x",__FUNCTION__,nDayOrNight);
	unsigned char buf[] = {0x04,nDayOrNight};
	sendToAppSystemStatusInfo(buf,2);
}
void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkDefualtNaviChange()
{
	u8 buf[] = {0x06,0x01};
	sendToAppSystemStatusInfo(buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkCurPageID()
{
	u16 curPageId = getCurPage();
	u8 buf[10] = {0x00};
	buf[0] = 0x07;
	memcpy(buf+1,&curPageId,2);
	sendToAppSystemStatusInfo(buf,3);
}
void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkSystemAutoLightStatus(u8 uSwitch)
{
	LOGD("[%s] Auto Light Switch:%x",__FUNCTION__,uSwitch);
	unsigned char buf[] = {0x08,uSwitch};
	sendToAppSystemStatusInfo(buf,2);
}
void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkSystemBrightnessValueMessage(u8 brightness)
{
	LOGD("[%s] brightness:%d",__FUNCTION__,brightness);
	unsigned char buf[] = {0x01,0x01,AMBIENT_SCREEN_BRIGHTNESS_MIN,AMBIENT_SCREEN_BRIGHTNESS_MAX,brightness};
	sendToAppSystemStatusInfo(buf,5);
}
/************************sendToAppBasicFunction*******************************/
void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkService(u8 moduleId, u8 *p, int len)
{
	static u8 szMsg[256] = {0};
	szMsg[0] = moduleId;

	if(len > 256)
		len = 256;
	memcpy(szMsg + 1, p, len);
	setCommand(0x51FFFE, szMsg, len + 1);
}

void CNotifyAndResponseFlyJniSdk::sendToAppSystemStatusInfo(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = 0x00;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, buf, len);
	sendToFlyJniSdkService(MODULE_SDK_SYSTEM, szMsg,len+1);
}
