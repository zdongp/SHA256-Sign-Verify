#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

void appToAux_AuxSet_VideoSwitch_MouseUp();

void appToAux_MenuAux_MouseUp(void);


void auxToApp_SetAUXVideo_Checking_Prompt_box(bool state);
void auxToApp_SetAUX_NoSignal_Prompt_box(bool state);

void appToAUX_VideoOSDColorSet_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType);
void appToAUX_VideoOSD_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType);

void System_notifyApp_DisplayBrakecarPromtBox(u8 u8_Param);

#endif
