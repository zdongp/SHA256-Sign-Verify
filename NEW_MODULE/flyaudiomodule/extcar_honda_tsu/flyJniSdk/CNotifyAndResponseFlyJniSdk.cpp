#include "CNotifyAndResponseFlyJniSdk.h"
#include "otherModuleResponseFunction.h"
#include "appRequestCommand.h"
#include "appResponseFunction.h"

CNotifyAndResponseFlyJniSdk:: CNotifyAndResponseFlyJniSdk()
{

}

CNotifyAndResponseFlyJniSdk:: ~CNotifyAndResponseFlyJniSdk()
{

}

void CNotifyAndResponseFlyJniSdk::analyseFromFlyJniSdkMessage(unsigned char *p,int len)
{
	switch(p[0])
	{
		case 0xFE:
			analyseFormSdkMessageExtcarHondaTsu(p+1,len - 1);
		break;
		default:break;
	}
}


/************************sendToAppBasicFunction*******************************/
void CNotifyAndResponseFlyJniSdk::sendToAppExtcarHondaTSUData(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = 0x00;
	szMsg[1] = 0x0ff;
	if(len > 256)
		len = 256;
	memcpy(szMsg+2, buf, len);
	sendToExtcarHondaTsuFlyJniSdkService(MODULE_SDK_EXTCAR_HONDA_TSU, szMsg,len+2);
}

void CNotifyAndResponseFlyJniSdk::sendToAppNoRealTimeDate(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = 0x00;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, buf, len);
	sendToExtcarHondaTsuFlyJniSdkService(MODULE_SDK_EXTCAR_HONDA_TSU, szMsg,len+1);
}