#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__


void syncToModule_NotifySystem_JumpPage(u16 pageId);	
void syncToModule_NotifySystem_jumpPrePage(void);
void syncToModule_NotifyOtherModule_BtCallState(unsigned char toModule, int state);
void Set_Sound_PreChannel();
void SendSYNCInfoToOSDDebug(void);
void syncToModule_NotifyCenter_SyncState(u8 state);


#endif
