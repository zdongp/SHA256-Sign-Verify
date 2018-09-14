#ifndef __APP_REQUEST_FUNCTION_BACK_H__
#define __APP_REQUEST_FUNCTION_BACK_H__

void BackcarToApp_Displaying_VideoColorSet(u8 state);

void BackcarToApp_Displaying_WarnintLineText(bool state);
void BackcarToApp_Inside_ActShowAnswerBox(int isShow);
void BackcarVideo_BackGroundColor_Set(bool state);
void BackcarVideo_IsShowVideoColorButton(bool state);
void BackcarToApp_Displaying_RedWarningLine(bool state);
void BackcarToApp_Displaying_TraceLine_SetButton(bool state);
void setToUI_BackCarLine_Type(int em);
#endif
