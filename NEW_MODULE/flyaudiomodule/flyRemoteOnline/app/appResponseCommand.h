#ifndef __APP_RESPONSE_COMMAND_H__
#define __APP_RESPONSE_COMMAND_H__

#include "global.h"
#include "messageQueue.h"

#define UIACTION_MOUSEDOWN		0x00
#define UIACTION_MOUSEUP		0x10
#define UIACTION_MOUSETIMER		0x20

#define SYS_SETUP_ON 1
#define SYS_SETUP_OFF 0
void appInit(void);
void appDeInit(void);
void analyseAppMessage(unsigned char *buffer, unsigned char len);
void appToRemoteOnline(u8 *p,u8 len);
void setToExtcarModule_RemoteOnlineMsg(u8 *p,int len);
void MobileRequestModule_updataExtcarInfors();
void WeChatRequestModule_updataExtcarInfors();

void ACCoffMobileRequestModule_updataExtcarInfors();////
void ACCoffWeChatRequestModule_updataExtcarInfors();////

void RemoteOnlineCtrl_Led(u8 param);
void RemoteOnlineCtrl_PowerOff(u8 param);

void MobileRequestModule_updataLedState();
void WeChatRequestModule_updataLedState();



#endif
