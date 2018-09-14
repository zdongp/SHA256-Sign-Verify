#ifndef __APP_RESPONSE_COMMAND_H__
#define __APP_RESPONSE_COMMAND_H__

#include "global.h"
#include "messageQueue.h"



#define UIACTION_MOUSEDOWN  	0X00

#define UIACTION_MOUSEUP  		0X10

#define UIACTION_MOUSETIMER  	0X20

#define UIACTION_PARAMETER		0xFF

#define SETUP_ON 1
#define SETUP_OFF 0

void appInit(void);
void appDeInit(void);
void analyseAppMessage(unsigned char *buffer, unsigned char len);
void appToExtcar_MouseUp(u32 ctrlId,u8 u8_MouseStatus,u8 *param);
void appToExtcar_MouseDown(u32 ctrlId,u8 u8_MouseStatus);

//golf
bool golf_driveDataPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_maintenanceInfoPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_settingMainPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_escSystemSettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_driveAssistSystemASettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_driveAssistSystemBSettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_parkingSystemSettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_lightSystemASettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_lightSystemBSettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_unitSettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_backMirrorAndWiperSettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_doorSettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_multipleFuncDisplayASettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_multipleFuncDisplayBSettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_recoveryFactoryASettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool golf_recoveryFactoryBSettingPage(u32 objID, E_MOUSE_MSG e = MOUSE_MSG_UP);
bool daZhong_normalSettingPage(u32 objID, E_MOUSE_MSG e);

bool rx5_normalSettingPage(u32 objID, E_MOUSE_MSG e,u8 *param);
bool appToExtcar_Parking_Assist_Page(u32 objID, E_MOUSE_MSG e);

#endif
