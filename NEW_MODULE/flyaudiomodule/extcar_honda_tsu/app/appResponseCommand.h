#ifndef __APP_RESPONSE_COMMAND_H__
#define __APP_RESPONSE_COMMAND_H__

#include "global.h"
#include "messageQueue.h"



#define UIACTION_MOUSEDOWN  	0X00
#define UIACTION_MOUSEUP  		0X10
#define UIACTION_MOUSETIMER  	0X20
#define UIACTION_PARAMETER		0xFF



void appInit(void);
void appDeInit(void);
void analyseAppMessage(unsigned char *buffer, unsigned char len);






#endif
