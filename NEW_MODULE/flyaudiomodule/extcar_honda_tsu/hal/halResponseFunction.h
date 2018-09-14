#ifndef __HAL_RESPONSE_FUNCTION_H__
#define __HAL_RESPONSE_FUNCTION_H__

void analyseHalMessage_EXTCAR_HONDA_TSU(u8 resCmd, u8 *param, u8 len);
void GetGenarlData(u8 *param,u8 len);
void getNoRealTimeDate(u8 *param ,int len);
void getRealTimeDate(u8 *param ,int len);









#endif
