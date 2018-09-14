#ifndef __HAL_RESPONSE_COMMAND_H__
#define __HAL_RESPONSE_COMMAND_H__

#include "global.h"
#include "messageQueue.h"
void halToAuxScreen_InitParam(u8 );//初始化状态
void halToAuxScreen_InitState(u8 );//初始化参数
void halToAuxScreen_IsAuxScreenDeviceExited(u8 );//小屏设备是否存在
void halToAuxScreen_Control(u8 cmd);
void halToAuxScreenSetRadioStatusMessage(u8 param,u8 *buf,int len);
void analyseHalSetGpsStatusMessage(u8 *param,int len);
void analyseHalSetJumpMediaPageMessage(u8 *param,int len);
void halToAuxScreen_Request_GetCallLogList(u8 type,u8 param);
void halToAuxScreen_ReturnPhoneDialOperating(u8 type,u8 param);


#endif
