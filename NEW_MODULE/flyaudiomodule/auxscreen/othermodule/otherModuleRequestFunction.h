#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__

void auxscreenToModule_NotifyBt_PhoneCtrl(u8 p);
void auxscreenToRadioSetStatusMessage(u8 *buf,int len);
void auxscreenToModule_NotifySystem_jumpPage(u16 PageId);
void auxscreenToModule_NotifyBt_Request_GetCallLogList(u8 p,u8 c);
void auxscreenToModule_NotifyBt_ReturnPhoneDialOperating(u8 p,u8 c);


#endif
