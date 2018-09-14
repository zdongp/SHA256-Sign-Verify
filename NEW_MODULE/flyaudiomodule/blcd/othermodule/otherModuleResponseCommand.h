#ifndef __OTHER_MODULE_RESPONSE_COMMAND_H__
#define __OTHER_MODULE_RESPONSE_COMMAND_H__

#include "global.h"

void otherModuleInit(void);
void otherModuleDeInit(void);
//void analyseOtherModuleMessage(char sendModuleId, unsigned char *param, unsigned char len);
void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len);

void analyseTimerHandleMessage(u8 *p, u8 len);

#endif
