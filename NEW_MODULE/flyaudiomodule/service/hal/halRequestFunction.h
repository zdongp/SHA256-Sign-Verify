#ifndef __HAL_REQUEST_COMMAND_SYSTEM_H__
#define __HAL_REQUEST_COMMAND_SYSTEM_H__


void service_to_hal_for_suspends(u8 mode);

void service_to_hal_TheNewStructure(u8 param);
void service_to_hal_ACCOff_30s_TheNewStructure(u8 param);
void service_to_hal_FastToSwitchMachine_60s_TheNewStructure(u8 param);
void service_to_hal_SetGeneralKnobPassword(u8 *param,u8 len);
void service_to_hal_15Days_reset(u8* param);

#endif
