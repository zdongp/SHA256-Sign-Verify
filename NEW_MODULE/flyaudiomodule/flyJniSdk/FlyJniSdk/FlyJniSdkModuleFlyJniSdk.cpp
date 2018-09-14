#include "FlyJniSdkModuleFlyJniSdk.h"


CFlyJniSdkModuleFlyJniSdk::CFlyJniSdkModuleFlyJniSdk(void)
{

}
CFlyJniSdkModuleFlyJniSdk::~CFlyJniSdkModuleFlyJniSdk(void)
{

}

void CFlyJniSdkModuleFlyJniSdk::getAppCtrlMessage(u8 *p, u8 len)
{
	LOGD("[%s] Module_flyJniSdk p[0]:%x", __FUNCTION__,p[0]);
	switch(p[0])
	{
		case 0x01:
			break;
		default:break;
	}
}


