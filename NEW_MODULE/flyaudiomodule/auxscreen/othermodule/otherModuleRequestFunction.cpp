
#include "moduleID.h"
#include "global.h"
#include "param.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"

void auxscreenToModule_NotifyBt_PhoneCtrl(u8 p)
{
     u8 buf[] = {0x00,0x00};
	 buf[1] = p;
     makeAndSendMessageToModule(MODULE_ID_AUXSCREEN,MODULE_ID_BT,buf,sizeof(buf));
}

void auxscreenToModule_NotifyBt_Request_GetCallLogList(u8 p,u8 c)
{
	u8 buf[] = {0x01,0x00,0x00};
	buf[1] = p;
	buf[2] = c;
	makeAndSendMessageToModule(MODULE_ID_AUXSCREEN,MODULE_ID_BT,buf,sizeof(buf));

}

void auxscreenToModule_NotifyBt_ReturnPhoneDialOperating(u8 p,u8 c)
{
	u8 buf[] = {0x02,0x00,0x00};
	buf[1] = p;
	buf[2] = c;
	makeAndSendMessageToModule(MODULE_ID_AUXSCREEN,MODULE_ID_BT,buf,sizeof(buf));

}


void auxscreenToRadioSetStatusMessage(u8 *buf,int len)
{
	makeAndSendMessageToModule(MODULE_ID_AUXSCREEN,MODULE_ID_RADIO,buf,len);
}

void auxscreenToModule_NotifySystem_jumpPage(u16 PageId)
{
     u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&PageId,2);
     makeAndSendMessageToModule(MODULE_ID_AUXSCREEN,MODULE_ID_SYSTEM,buf,3);
}

