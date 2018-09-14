#ifndef __HAL_RESPONSE_COMMAND_H__
#define __HAL_RESPONSE_COMMAND_H__

#include "global.h"
#include "messageQueue.h"

//hal msg  come form system module
void halToAux_QueryVideo(unsigned char cFlag); //返回是否有视频 cFlag 0 表示没 ，1 表示有

#endif
