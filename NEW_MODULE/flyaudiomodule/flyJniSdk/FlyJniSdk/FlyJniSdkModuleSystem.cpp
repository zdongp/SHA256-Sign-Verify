#include "FlyJniSdkModuleSystem.h"
bool RadarMessageSwitch = false;

CFlyJniSdkModuleSystem::CFlyJniSdkModuleSystem(void)
{

}
CFlyJniSdkModuleSystem::~CFlyJniSdkModuleSystem(void)
 {

 }

void CFlyJniSdkModuleSystem::FlyJniSdkToModule_NotifySystem_JumpPage(unsigned char* pageID)
{
		unsigned short temPage = 0;
	    u8 buf[] = {0x82,0x00,0x00};
		temPage += (unsigned short )((pageID[0] << 8) & 0xFF00);
		temPage += (unsigned short )(pageID[1] & 0xFF);
		LOGD("[%s] temPage:%x",__FUNCTION__,temPage);
		memcpy(&buf[1],&temPage,2);
		makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_SYSTEM,buf,3);
}

void CFlyJniSdkModuleSystem::FlyJniSdkToModule_NotifySystem_ResetFactorySeting(unsigned char param)
{
	    u8 buf[] = {0x0A,0x00};
		buf[1] = param;
		makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_SYSTEM,buf,2);
}

void  CFlyJniSdkModuleSystem::FlyJniSdkToModule_NotifySystem_ChangeLightness(unsigned char lightness)
{

	LOGD("[%s] brightness:%d",__FUNCTION__,lightness);
	u8 buf[] = {0xF2, lightness};
	if(lightness >=4)
		return;

	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 2);

}

void CFlyJniSdkModuleSystem::FlyJniSdkToModule_NotifySystem_CloseOrTurnOnBrightness(unsigned char param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 buf[] = {0xF3, param};

	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 2);
}

void CFlyJniSdkModuleSystem::FlyJniSdkToModule_NotifySystem_OtaUpdata(unsigned char param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 buf[] = {0xF4, param};

	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 2);
}

void CFlyJniSdkModuleSystem::getSystemMessage(u8 *p, u8 len)
{
    LOGD("[%s] p[0]:%x",__FUNCTION__,p[0]);
	switch(p[0])
	{
        case 0x00:
			onSystemBrightness(p[1]);
			if(p[1] == 0x01 ||p[1] == 0x02 ||p[1] == 0x03)
			{
				u8 param = p[1] - 0x01;
				sendToAppSystemLightnessValue(0x00,param);
			}
			else if(p[1] == 0x00)
			{
				sendToAppSystemLightnessValue(0x00,0x03);
			}
		break;
		case 0x01:
			{
				if(RadarMessageSwitch)
					sendToAppSystemRadarDate(p+1,len -1);
			}
			break;
		case 0x02:
			onSystemToFrontCameraApp(p[1]);
			break;
		default:
			break;
	}	   
}
void CFlyJniSdkModuleSystem::onSystemBrightness(unsigned char brightness )
{
	LOGD("[%s] AudioVideo:%x",__FUNCTION__,brightness);
	u8 szMsg[2] = {0x04, brightness};
	setToFlyJniSdkService(MODULE_ID_SYSTEM, szMsg, sizeof(szMsg));

}

void CFlyJniSdkModuleSystem::onSystemToFrontCameraApp(u8 p)
{
	u8 szMsg[] = {0x10, p};
	setToFlyJniSdkService(MODULE_ID_SYSTEM, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModuleSystem::getAppCtrlMessage(u8 *p, u8 len)
{
	LOGD("[%s] Module_system p[0]:%x",__FUNCTION__,p[0]);
	switch(p[0])
	{
		case 0x06:
			FlyJniSdkToModule_NotifySystem_JumpPage(p+1);
			break;
		case 0x0A:
			FlyJniSdkToModule_NotifySystem_ResetFactorySeting(p[1]);
			break;
		case 0x04:
			FlyJniSdkToModule_NotifySystem_ChangeLightness(p[1]);
			break;
		case  0x0B:
			FlyJniSdkToModule_NotifySystem_CloseOrTurnOnBrightness(p[1]);
			break;
		case 0x0C:
			FlyJniSdkToModule_NotifySystem_OtaUpdata(p[1]);
			break;
		default:
			break;
	}
}
/******************new pro*********************/
void CFlyJniSdkModuleSystem::analyseSystemAppMessageType(u8 *p, u8 len)
{
	LOGD("[%s]	p[0]:%x --p[1]:%x len:%x",__FUNCTION__,p[0],p[1],len);
	switch(p[0])
	{
		case RESPONE_CHANGE_STATE:
			analyseReturnStatusMassage(p+1, len - 1);
			break;
		case CONTROL_MESSAGE:
			analyseSystemControlSystemOperationMassage(p+1, len - 1);
			break;
		default:break;
	}
}
void CFlyJniSdkModuleSystem::analyseSystemControlSystemOperationMassage(u8 *buf ,u8 len)
{
	switch(buf[0])
	{
		case 0x00:
			{
				sendToSystemJumpPage(buf+1,len -1);
			}
		break;
		case 0x01:
			if(buf[1] == 0x01 || buf[1] == 0x00)
			{
				sendToSystemSetOffScreen(buf[1]);
			}
		break;
		case 0x02:
			{
				if(buf[1] == 0x00 ||buf[1] == 0x01 ||buf[1] == 0x02)
				{
					u8 p = buf[1] + 0x01;
					sendToSystemSetScreenBrightness(p);
				}
			}
		break;
		case 0x03:
			{
				if(buf[1] == 0x01||buf[1] == 0x00)
					sendToSystemJumpToSetPage(buf[1]);
			}
		break;
		case 0x05:
			{
				if(buf[1] == 0x00||buf[1] == 0x01||buf[1] == 0x02)
				{
					sendToSystemSetDayOrNightMode(buf[1]);
				}
			}
			break;
		case 0x06:
			{
				sendToSystemSetScreenBrightnessValue(buf[1]);
			}
			break;
		case 0x07:
			{
				sendToSystemSetAutoLightStatus(buf[1]);
			}
			break;
		case 0x08:
			{
				sendToSystemSetLightAddOrRed(buf + 1,len - 1);
			}
			break;
		case 0xfe:
			{
				if(buf[1] == 0xfe)
					sendToSystemSetSystemReset();
			}
		break;
		default:break;
	}
}
void CFlyJniSdkModuleSystem::analyseReturnStatusMassage(u8 *buf ,u8 len)
{
	switch(buf[0])
	{
		case 0x01:
			{
				if(buf[1] == 0x00||buf[1] == 0x01)
					sendToSystemGetCurLightness(buf[1]);
			}
		break;
		case 0x04:
			{
				if(buf[1] == 0x01)
					sendToSystemGetDayAndNightStatus(buf[1]);
			}
			break;
		case 0x05:
			if(buf[1] == 0x01)
			{
				sendToSystemGetRadarDate(0x01);
				RadarMessageSwitch = true;
			}
			break;
		case 0x06:
			{
				if(buf[1] == 0x01)
					sendToSystemGetCurPageID(buf[1]);
			}
			break;
		case 0x07:
			{
				if(buf[1] == 0x01)
					sendToSystemGetAutoLightStatus(buf[1]);
			}
			break;
		case 0xff:
			if(buf[1] == 0xff)
				sendToAppSystemGetCurStatusFinish();
		default:break;
	}
}
void CFlyJniSdkModuleSystem::sendToSystemSetOffScreen(u8 param)
{
	u8 buf[] = {0xfe,0x01, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}
void CFlyJniSdkModuleSystem::sendToSystemSetScreenBrightness (u8 param)
{
	u8 buf[] = {0xfe,0x02, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}
void CFlyJniSdkModuleSystem::sendToSystemJumpToSetPage (u8 param)
{
	u8 buf[] = {0xfe,0x03, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}

void CFlyJniSdkModuleSystem::sendToSystemGetCurLightness(u8 param)
{
	u8 buf[] = {0xfe,0x04, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}

void CFlyJniSdkModuleSystem::sendToSystemGetRadarDate(u8 param)
{
	u8 buf[] = {0xfe,0x05, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}

void CFlyJniSdkModuleSystem::sendToSystemJumpPage(u8 *Buff,u8 len)
{
	u8 buf[4] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x06;
	memcpy(buf+2,Buff,2);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 4);
}
void CFlyJniSdkModuleSystem::sendToSystemSetDayOrNightMode(u8 param)
{
	u8 buf[] = {0xfe,0x07, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}
void CFlyJniSdkModuleSystem::sendToSystemSetScreenBrightnessValue(u8 param)
{
	u8 buf[] = {0xfe,0x08, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}
void CFlyJniSdkModuleSystem::sendToSystemGetBackCarStatus(u8 param)
{
	u8 buf[] = {0xfe,0x09, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}

void CFlyJniSdkModuleSystem::sendToSystemGetCurPageID(u8 param)
{
	u8 buf[] = {0xfe,0x0a, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}

void CFlyJniSdkModuleSystem::sendToSystemGetDayAndNightStatus(u8 param)
{
	u8 buf[] = {0xfe,0x0b, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}

void CFlyJniSdkModuleSystem::sendToSystemGetAutoLightStatus(u8 param)
{
	u8 buf[] = {0xfe,0x0c, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}
void CFlyJniSdkModuleSystem::sendToSystemSetAutoLightStatus(u8 param)
{
	u8 buf[] = {0xfe,0x0d, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 3);
}

void CFlyJniSdkModuleSystem::sendToSystemSetLightAddOrRed(u8 *buf,int len)
{
	if(len > 8)
		len =8;
	u8 buff[10] = {0};
	buff[0] = 0xfe;
	buff[1] = 0x0e;
	memcpy(buff+2,buf,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buff, len+2);
}
void CFlyJniSdkModuleSystem::sendToSystemSetSystemReset()
{
	u8 buf[] = {0xfe,0xfe};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 2);
}
/****************send To App*****************/
void CFlyJniSdkModuleSystem::sendToAppSystemLightnessValue(u8 param ,u8 value)
{
	LOGD("[%s] value:%x", __FUNCTION__,value);
	u8 szMsg[4] = {0x00, 0x01,param,value};
	sendToFlyJniSdkService(MODULE_SDK_SYSTEM, szMsg, 4);
}
void CFlyJniSdkModuleSystem::sendToAppSystemRadarDate(u8 *param ,u8 len)
{
	LOGD("[%s] ForR:%x", __FUNCTION__,param[0]);
	u8 szMsg[7] = {0};
	szMsg[0] = 0x00;
	szMsg[1] = 0x05;
	if(len > 5)
		len = 5;
	memcpy(szMsg+2,param,len);
	sendToFlyJniSdkService(MODULE_SDK_SYSTEM, szMsg, len+2);
}

void CFlyJniSdkModuleSystem::sendToAppSystemGetCurStatusFinish()
{
	u8 szMsg[3] = {0x00, 0xff,0xff};
	sendToFlyJniSdkService(MODULE_SDK_SYSTEM, szMsg, 3);
}