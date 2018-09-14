#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__



void ipodToModule_NotifySystem_jumpPage(u16 pageId);
void ipodToModule_NotifySystem_jumpPrePage(void);
void ipodToModule_NotifySystem_SwitchModule();
void ipodToModule_NotifyOsd_DisplayOSDIpodInfo(u16 track,u16 trackSum);

/*
void centerToModule_NotifySystem_Hardware_JumpPrePage(void);
void centerToModule_NotifySystem_EnterThreePartyApp(void);
void centerToModule_NotifySystem_EnterHomePage(void);
void centerToModule_NotifySystem_EnterNonHomePage(void);


void centerToModule_NotifySystem_DebugPanelType(unsigned char panelType);

void centerToModule_NotifyOSD_SetOSDHidden(void);

void centerToModule_NotifyAudiovideo_GpsSoundState(unsigned char state);

void centerToModule_NotifySystem_ReturnToPage(unsigned char *pageid, int len);
*/
#endif
