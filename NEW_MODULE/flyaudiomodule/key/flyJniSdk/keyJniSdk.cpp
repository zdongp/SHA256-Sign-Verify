/************************2017-11-17**************************************/
#include "keyJniSdk.h"
#include "param.h"
#include <stdio.h>
#include <stdlib.h>
#include <flyutils/debug.h>
#include <cstring>

#include "appRequestCommand.h"
#include "appResponseFunction.h"
#include "otherModuleResponseFunction.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"

//
#define MESSAGETYPE_STATUS			0x00
#define MESSAGETYPE_CONTROL		0x01
//

CKeyJniSdk::CKeyJniSdk()
{
	return;
}

CKeyJniSdk::~CKeyJniSdk()
{
	return;
}
void CKeyJniSdk::getSdkToModuleKeyMessage(u8 *p,int len)
{
	LOGD("[%s] MessageType:%x ---p[1]:%x",__FUNCTION__,p[0],p[1]);
	switch(p[0])
	{
		case MESSAGETYPE_STATUS:
			analysSdkToKeyStatusMessage(p+1,len -1);
		break;
		case MESSAGETYPE_CONTROL:
			analysSdkToKeyContrlMessage(p+1,len -1);
		break;
		default:break;
	}
}
void CKeyJniSdk::analysSdkToKeyStatusMessage(u8 *buf,u8 len)
{
}
  
void CKeyJniSdk::analysSdkToKeyContrlMessage(u8 *buf,u8 len)
{
}


void CKeyJniSdk::sendToFlyJniSdkService(u8 moduleId, u8 *p, u8 len)
{
	static u8 szMsg[256] = {0};
	szMsg[0] = moduleId;

	if(len > 256)
		len = 256;
	memcpy(szMsg + 1, p, len);
	setCommand(0x51FFFE, szMsg, len + 1);
}

void CKeyJniSdk::sendToAppKeyStatusInfo(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = MESSAGETYPE_STATUS;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, buf, len);
	sendToFlyJniSdkService(MODULE_SDK_KEY, szMsg,len+1);
}

void CKeyJniSdk::sendToAppKeyCtrlInfo(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = MESSAGETYPE_CONTROL;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, buf, len);
	sendToFlyJniSdkService(MODULE_SDK_KEY, szMsg,len+1);
}


void CKeyJniSdk::sendToApp_KeyValue(u8 param)
{
	u8 buf[] = {0x01,param};
	sendToAppKeyCtrlInfo(buf,2);
}

