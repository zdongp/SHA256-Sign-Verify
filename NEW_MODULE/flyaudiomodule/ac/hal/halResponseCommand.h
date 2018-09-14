#ifndef __HAL_RESPONSE_COMMAND_H__
#define __HAL_RESPONSE_COMMAND_H__

#include "global.h"

void halInit(void);
void halDeInit(void);
void analyseHalMessage(halid_t hid, u8 cmd, u8 *param, u8 len);


#endif
