#ifndef __HAL_RESPONSE_COMMAND_H__
#define __HAL_RESPONSE_COMMAND_H__

#include "global.h"
#include "messageQueue.h"



void halInit_ResponseDVD(void);
void analyseHalMessage_DVD(char msgResCmd, unsigned char *param, unsigned char len);

#endif
