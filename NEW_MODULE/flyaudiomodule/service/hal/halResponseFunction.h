#ifndef __HAL_RESPONSE_FUNCTION_H__
#define __HAL_RESPONSE_FUNCTION_H__

#include "global.h"
#include "messageQueue.h"



void analyseHalMessage_service(char resCmd, unsigned char *param, unsigned char len);

void service_suspends(char type);

void service_GetBarCode(u8* Barcode, u8 len);














#endif
