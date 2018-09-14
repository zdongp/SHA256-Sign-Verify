#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"

#include <flymoduleApi_internal.h>

void tpmsToHal_Init(u8 u8_Param)
{
    unsigned char cmdParam[2] = {0x01, u8_Param};

   if(u8_Param){
   	cmdParam[1] = 0x01;
   	}

    makeAndSendMessageToHal(HAL_ID_TPMS, cmdParam, 2);
}

void tpmsToHal_SoftwareImitateKey(u8 u8_Param)
{
     unsigned char keyParam[2] = {0x03, u8_Param};
     makeAndSendMessageToHal(HAL_ID_TPMS, keyParam, 2);
}

void tpmsToHal_PairMode(u8 u8_Param)
{
    unsigned char pairMode[2] = {0x10, u8_Param};
    makeAndSendMessageToHal(HAL_ID_TPMS, pairMode, 2);

}



