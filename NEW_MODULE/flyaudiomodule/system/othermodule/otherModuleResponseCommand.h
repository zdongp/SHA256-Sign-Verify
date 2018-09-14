#ifndef __OTHER_MODULE_RESPONSE_COMMAND_H__
#define __OTHER_MODULE_RESPONSE_COMMAND_H__

#include "global.h"
#include "flytypes.h"




void otherModuleInit(void);
void otherModuleDeInit(void);
void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len);

#endif
