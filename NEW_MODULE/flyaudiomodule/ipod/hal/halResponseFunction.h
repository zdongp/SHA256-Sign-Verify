#ifndef __HAL_RESPONSE_FUNCTION_H__
#define __HAL_RESPONSE_FUNCTION_H__

#include "global.h"
#include "messageQueue.h"

void analyseHalMessage_IPOD(unsigned char *param, unsigned char len);
void GetBrowseItemString();
int AnalyseAiRMode();
void analyseHalMessage_IPOD(unsigned char *buf, unsigned char len);
void halToIpod_GetTypeListIndex(int iNumber);


#endif
