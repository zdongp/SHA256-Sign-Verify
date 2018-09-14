#ifndef __APP_RESPONSE_COMMAND_H__
#define __APP_RESPONSE_COMMAND_H__

#include "global.h"
#include "messageQueue.h"

#define UIACTION_MOUSEDOWN		0x00
#define UIACTION_MOUSEUP		0x10
#define UIACTION_MOUSETIMER		0x20
#define UIACTION_MOUSECANCEL 	0X30

#define SYS_SETUP_ON 1
#define SYS_SETUP_OFF 0
void appInit(void);
void appDeInit(void);
void analyseAppMessage(unsigned char *buffer, unsigned char len);




#endif
