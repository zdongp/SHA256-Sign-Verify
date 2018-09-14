#ifndef __OTHER_MODULE_RESPONSE_COMMAND_H__
#define __OTHER_MODULE_RESPONSE_COMMAND_H__

#include "global.h"

void otherModuleInit(void);
void otherModuleDeInit(void);
void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len);
moduleid_t ModuleIDToChannel(short sChannel); /*由声道ID获取模块ID*/
bool AuxscreenModule_AccordingToTheChannelAndGetModuleID(moduleid_t sendModuleId);

void analyseTimerHandleMessage(u8 *p, u8 len);

#endif
