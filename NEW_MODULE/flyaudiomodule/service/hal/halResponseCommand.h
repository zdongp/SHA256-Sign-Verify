#ifndef __HAL_RESPONSE_COMMAND_H__
#define __HAL_RESPONSE_COMMAND_H__

#include "global.h"
#include "flytypes.h"


void analyseHalMessage(moduleid_t halId, u8 msgResCmd, u8 *param, u8 len);


#endif
