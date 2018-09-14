/************************2017-11-17**************************************/
#include "externalJniSdk.h"
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
#include "voiceLogic.h"
//
#define MESSAGETYPE_STATUS			0x00
#define MESSAGETYPE_CONTROL		0x01
//


CExternalJniSdk:: CExternalJniSdk()
{

}

CExternalJniSdk:: ~CExternalJniSdk()
{

}
void CExternalJniSdk::getSdkToModuleExternalMessage(u8 *p,int len)
{
	LOGD("[%s] MessageType:%x ---p[1]:%x",__FUNCTION__,p[0],p[1]);
	switch(p[0])
	{
		case MESSAGETYPE_STATUS:
			analysSdkToExternalStatusMessage(p+1,len -1);
		break;
		case MESSAGETYPE_CONTROL:
			analysSdkToExternalContrlMessage(p+1,len -1);
		break;
		default:break;
	}
}
void CExternalJniSdk::analysSdkToExternalStatusMessage(u8 *buf,u8 len)
{
}
  
void CExternalJniSdk::analysSdkToExternalContrlMessage(u8 *buf,u8 len)
{
	switch(buf[0])
	{
		case 0x01:
		{
			analyseVoiceStatus(buf+1,len - 1);
		}
		break;
		default:break;
	}

}

