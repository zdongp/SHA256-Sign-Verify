#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__

#include <flytypes.h>

void backCarToModule_NotifySystem_SwitchModule(void);

void backCarToModule_NotifySystem_JumpPage(u16 nPageId);
void backCarToModule_NotifySystem_JumpPrePage(void);

void backCarToModule_NotifyOSD(u8 m_bBackState);

void backCarToModule_NotifySystem_AlarmBackCar(u8 IsBackCar);
void backCarToModule_NotifySystem_ActualReversingState(u8 p);

void backCarToModule_NotifyBT_HandUp_MouseUp(void);
void backCarToModule_NotifyBT_CallIn_MouseUp(void);

void backCarToModule_NotifySystem_Out_BackCar_RedOsd();
void backCarToModule_NotifyAudioVideo_aboutBackCarVideoSet(u8 param);


void backcarToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(u8 param,u8 status);

void backCarToModule_NotifyOSD_aboutT123_ChangePage_OSDDispalying(u8 u8_Module,u16 u16_LewPage,u16 u16_EnterPage,u8 u8_Param);

void backcarToModule_NotifyOSD_aboutT123_colorSet_Value(u8 param,u8 value);
void backCarToModule_NotifyOSD_aboutT123_BackCarVideoRefLineDisplay(u8 param);
void backCarToModule_NotifyOSD_aboutT123_BackCarWarningsDisplay(u8 State);
void backcarToModule_NotifySystem_VisionAngle(u8 param);
void backcarToModule_NotifyOSD_aboutT123_VideoOSDSetButton(u8 param,u8 status);


void backCarToModule_NotifyExtcar_Prado_ScreenCoordinates(u8* param ,int paramLen);
void backCarToModule_NotifySystem_BackCarVideoLineType(u8 param);

void backCarToModule_NotifyExternalctrl_VoiceSwitchCtrl(u8 p);
void backCarToModule_NotifyExtcar_SetVoiceSize(u8 p);
void setToExtcarSetVoiceSizeMessage(u8 param);



#endif
