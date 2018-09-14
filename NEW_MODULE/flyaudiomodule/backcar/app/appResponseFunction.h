#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

#include "param.h"

void appToBackCar_Cordonl_MouseUp(char cIndex);
void appToBackCar_Cordonl_MouseTimer(char cIndex);

void appToBackcar_EnterPanoramicVideo(void);
void appToBackcar_ExitPanoramicVideo(void);
void appToBackcar_SelectVideo(char direction);
void appToBackcar_EnterFullScreen(void);
void appToBackCar_T123VideoSetButton(int ctrlId,u8 ctrlType);
void appToBackCar_Process_Prado_ScreenCoordinate(u8* param,u8 paramLen);

void appToBackcar_T123videoOSD_colorSetButton(int ctrlID,u8 ctrlType);
void appToBackCar_T123VideoSetButton_ColorPage(int ctrlId,u8 ctrlType);

void appToBackcar_T123videoOSD(int ctrlID,u8 ctrlType);

void appToBackCar_Video_TraceType_switch(void);
void ToUI_BackCarVideo_TraceType(Em_Backcar_TraceType em);
void IsDisplaying_WarnintLineText(u8 p);
void showVideoZoomInOrOutStatus(u8 param);



#endif
