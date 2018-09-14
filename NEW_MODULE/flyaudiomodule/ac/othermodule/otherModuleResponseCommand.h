#ifndef __OTHER_MODULE_RESPONSE_COMMAND_H__
#define __OTHER_MODULE_RESPONSE_COMMAND_H__

#include "global.h"
#include "flytypes.h"
void otherModuleInit(void);
void otherModuleDeInit(void);
void analyseOtherModuleMessage(moduleid_t , u8 *, u8 );

#endif
