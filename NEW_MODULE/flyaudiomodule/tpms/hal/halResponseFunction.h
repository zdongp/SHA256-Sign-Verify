#ifndef __HAL_RESPONSE_COMMAND_H__
#define __HAL_RESPONSE_COMMAND_H__
#endif

#include "global.h"
#include "messageQueue.h"



//Define
#define HALTOTPMS_INIT_CMD  0x01
#define HALTOTPMS_INIT_STATUS  0x02
#define HALTOTPMS_WHETHER_EXIST  0x03
#define HALTOTPMS_PAIR_MODE      0x10
#define HALTOTPMS_FL_UPDATA 0X20 
#define HALTOTPMS_FR_UPDATA 0X21 
#define HALTOTPMS_RL_UPDATA 0X22 
#define HALTOTPMS_RR_UPDATA 0X23 

//Function
void analyseHalMessage_TPMS(char resCmd, unsigned char *param, unsigned char len); 
void halToTPMS_TireSwapDispose(char resCmd, unsigned char *param, unsigned char len);

void halToTPMS_InitParam(u8 u8_Param);
void halToTPMS_InitStatus(u8 u8_Param);

void halToTPMS_WhetherExist(u8 u8_Param);
void halToTPMS_PairMode(u8 u8_Param);
void halToTPMS_UpdataTrieInfo(u8 *pBuf, u8 len , u8 TireNub);


int  halToTPMS_PresureData(u8 getData);
int  halToTPMS_TemperatureData(u8 getData);

void Alarm(u8 command);




