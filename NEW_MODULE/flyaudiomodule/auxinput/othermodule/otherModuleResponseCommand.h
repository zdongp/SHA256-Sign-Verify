#ifndef __OTHER_MODULE_RESPONSE_COMMAND_H__
#define __OTHER_MODULE_RESPONSE_COMMAND_H__

#include "global.h"

void otherModuleInit(void);
void otherModuleDeInit(void);
void analyseOtherModuleMessage(unsigned char sendModuleId, unsigned char *param, unsigned char len);

#endif
