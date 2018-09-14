#include "FlyJniSdkModuleExtcarHondaTsu.h"


CFlyJniSdkModuleExtcarHondaTsu::CFlyJniSdkModuleExtcarHondaTsu(void)
{

}

CFlyJniSdkModuleExtcarHondaTsu::~CFlyJniSdkModuleExtcarHondaTsu(void)
{

}

void CFlyJniSdkModuleExtcarHondaTsu::analyseExtcarHondaTsuAppMessageType(u8 *p, u8 len)
{
	switch(p[0])
	{
		case RESPONE_CHANGE_STATE:
			analyseExtcarHondaTsuMassage(p+1, len - 1);
			break;
		case CONTROL_MESSAGE:
			break;
		default:break;
	}
}

void CFlyJniSdkModuleExtcarHondaTsu::analyseExtcarHondaTsuMassage(u8 *p, u8 len)
{
	sendToextcarHondaTsuData(p,len);
}

void CFlyJniSdkModuleExtcarHondaTsu::sendToextcarHondaTsuData(u8 *param,int len)
{
	u8 buf[256] = {0};
	buf[0] = 0xfe;
	if(len > 256)
		len = 255;
	memcpy(buf+1,param,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_EXTCAR_HONDA_TSU, buf, len + 1);
}

