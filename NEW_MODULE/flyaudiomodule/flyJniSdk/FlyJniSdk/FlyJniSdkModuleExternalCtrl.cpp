#include "FlyJniSdkModuleExternalCtrl.h"

CFlyJniSdkModuleExternalCtrl::CFlyJniSdkModuleExternalCtrl(void)
{
}

CFlyJniSdkModuleExternalCtrl::~CFlyJniSdkModuleExternalCtrl(void)
{
	return;
}

void CFlyJniSdkModuleExternalCtrl::analyseExternalCtrlAppMessageType(u8 *p, u8 len)
{
	//outPutLog(__FUNCTION__,"p",p,(int)len);
	switch(p[0])
	{
		case RESPONE_CHANGE_STATE:
			analyseExternalCtrlReturnStatusMassage(p+1, len - 1);
			break;
		case CONTROL_MESSAGE:
			analyseControlExternalCtrlOperationMassage(p+1, len - 1);
			break;
		default:break;
	}

}
void CFlyJniSdkModuleExternalCtrl::analyseExternalCtrlReturnStatusMassage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:
		default:break;
	}
}

void CFlyJniSdkModuleExternalCtrl::analyseControlExternalCtrlOperationMassage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:
			{
				if(p[1] == 0x00 ||p[1] == 0x01)
					sendToExternalCtrlSpeechStatus(p[1]);
			}
			break;
		default:break;
	}
}

/***************************setToAcControl************************************************/
void CFlyJniSdkModuleExternalCtrl::sendToExternalCtrlSpeechStatus(u8 param)
{
	u8 buf[3] = {CONTROL_MESSAGE,0x01,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTERNALCTRL,buf,3);
}

