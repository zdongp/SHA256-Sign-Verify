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
void appToService_GeneralKnobPasswd(u8 *buf,u8 len);

void service_GetIMEI(u8 *buf,u8 len);
void service_GetMAC(u8 *buf,u8 len);
void service_GetWifiConnectStatus(u8 *buf,u8 len);
void service_GetWifiNetworkSignalStrength(u8 *buf,u8 len);
void service_Get4GNetworkSignalStrength(u8 *buf,u8 len);
void service_GetSD1_Status(u8 *buf,u8 len);
void service_GetMemoryUsageSd1(u8 *buf,u8 len);
void service_GetTheTotalSizeSd1(u8 *buf,u8 len);
void service_GetMemoryUsageSd0(u8 *buf,u8 len);
void service_GetTheTotalSizeSd0(u8 *buf,u8 len);
void service_GetUsingNetworkStatus_WiFi(u8 *buf,u8 len);
void service_GetUsingNetworkStatus_4G(u8 *buf,u8 len);

#endif
