#ifndef __HAL_RESPONSE_COMMAND_H__
#define __HAL_RESPONSE_COMMAND_H__

#include "global.h"

void halInit(void);
void halDeInit(void);
void analyseHalMessage(char halId, char msgResCmd, unsigned char *param, unsigned char len);


#endif