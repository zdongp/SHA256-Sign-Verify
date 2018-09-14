#ifndef __APP_RESPONSE_COMMAND_H__
#define __APP_RESPONSE_COMMAND_H__

#include "global.h"
#include "messageQueue.h"

void appInit(void);
void appDeInit(void);
void analyseAppMessage(unsigned char *buffer, unsigned char len);
void analyseAppToKeyDedicate_information(u8 *param,int len);



#endif
