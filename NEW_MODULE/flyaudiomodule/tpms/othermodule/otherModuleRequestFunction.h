#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__


void tpmsToModule_NotifySystem_JumpPage(u16 u16_PageID);
void tpmsToModule_NotifySystem_JumpPrePage(void);
void tpmsToModule_NotifySystem_SwitchModule(u8 u8_ModuleID);

void StartRing(u8 ringID);
void StopRing();

void Set_OSD_ShowTitle(u8 cType);
void Set_Tpms_Osd_Control(u8 cControl);
void Set_TPMS_OSD_Control(u8 cType);
void tpmsToModule_NotifyOSDT123_ShowTitle();




#endif
