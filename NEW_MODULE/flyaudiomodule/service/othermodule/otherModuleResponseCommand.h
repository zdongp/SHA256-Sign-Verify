#ifndef __OTHER_MODULE_RESPONSE_COMMAND_H__
#define __OTHER_MODULE_RESPONSE_COMMAND_H__

#include "global.h"
#include "flytypes.h"


void otherModuleInit(void);
void otherModuleDeInit(void);
void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len);

void OtherModuleToService_AnalyseCenter(u8 *param);
void OtherModuleToService_AnalyseSystem(u8 *param,u8 uLen);
void OtherModuleToService_analyseBT(u8 *p);

void analyseTimerHandleMessage(u8 *p, u8 len);

#endif
