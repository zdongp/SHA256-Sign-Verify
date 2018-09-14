#include "FlyJniSdkModuleMedia.h"
bool MediaInfoSendTag = false;

CFlyJniSdkModuleMedia::CFlyJniSdkModuleMedia(void)
{
}

CFlyJniSdkModuleMedia::~CFlyJniSdkModuleMedia(void)
{
}
void CFlyJniSdkModuleMedia::getMediaMessage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:
			if(MediaInfoSendTag)
				sendToAppMediaStatusInfo(p+1, len-1);
		break;
		default:break;
	}
}

void CFlyJniSdkModuleMedia::analyseMediaAppMessageType(u8 *p, u8 len)
{
	switch(p[0])
	{
		case RESPONE_CHANGE_STATE:
			analyseMediaReturnStatusMassage(p+1, len - 1);
			break;
		case CONTROL_MESSAGE:
			analyseControlMediaOperationMassage(p+1, len - 1);
			break;
		default:break;
	}

}
void CFlyJniSdkModuleMedia::analyseMediaReturnStatusMassage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:
			if(p[1] == 0x01)
			{
				//MediaInfoSendTag = true;
				//setToAcGetCurAcInfo();
			}
			break;
		default:break;
	}
}

void CFlyJniSdkModuleMedia::analyseControlMediaOperationMassage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:
			if(p[1] == 0x01||p[1] == 0x00)
			{
				setToMediaJumpMediaPage(p[1]);
			}
			break;
		case 0x02:
			if(p[1] == 0x01)
				setToMediaSpecifyToPlayTheSong(&p[1],len - 1);
			break;
		default:break;
	}
}

/********************send To Media****************************/
void CFlyJniSdkModuleMedia::setToMediaJumpMediaPage(u8 param)
{
	u8 buf[2] = {0x01,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_MEDIA,buf,2);
}

void CFlyJniSdkModuleMedia::setToMediaSpecifyToPlayTheSong(u8 *param,u8 len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = 0x02;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, param, len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_MEDIA,szMsg,len+1);
}

/********************send To App****************************/
void CFlyJniSdkModuleMedia::sendToAppMediaStatusInfo(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = 0x00;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, buf, len);
	sendToFlyJniSdkService(MODULE_SDK_MEDIA, szMsg, strlen((char *)szMsg));
}
