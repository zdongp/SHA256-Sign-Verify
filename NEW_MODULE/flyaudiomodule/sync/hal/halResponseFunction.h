#ifndef __HAL_RESPONSE_FUNCTION_H__
#define __HAL_RESPONSE_FUNCTION_H__

#include "global.h"
#include "messageQueue.h"


void analyseHalMessage_SYNC(unsigned char resCmd, unsigned char *param, unsigned char len);

void analyseHalMessage_CarType_NEW_FOCUS(u8 *param, u8 len);
void analyseData_CarType_NEW_FOCUS(u8 *param, u8 len);

void Get_Sync_Title(u8 *buf,int len);
void Get_Sync_String_OneLine(u8 *buf,int len);
void Get_Sync_String_TwoLine(u8 *buf,int len);
void Get_Sync_String_ThreeLine(u8 *buf,int len);
void Get_Sync_String_FourLine(u8 *buf,int len);

void Get_Sync_Char_Button1(u8 *param,int len);
void Get_Sync_Char_Button2(u8 *param,int len);
void Get_Sync_Char_Button3(u8 *param,int len);
void Get_Sync_Char_Button4(u8 *param,int len);

void Get_Several_Sign_Stat(unsigned short Value);
void Get_Sync_Aux_State(unsigned char State);
void Get_Sync_State(u8 State);
void Get_BtCallState(u8 State);
void Get_ShowPreText(u8 State);
void Get_USB_PlayTime(u8 ucMinute,u8 ucSeconds);
void Get_LeaveSyncPage();


void EnterSync();
void LeaveSyncMedia();

void Get_CurSelectLine(u8 line);
bool WhetherThePageCanSwitchChannels(u16 PageID);

void ToPrintMessage(const char* msg, const char* buffer, const int length);

void InitConfig_Visible_setup();
void Get_CheckBoxDisplaying(char cmd,u8 param);
void Get_Ford_Steer_MouseKey(u8 uParam);
void Get_Ford_NewModels_OriginalCarPanelKeyButtons(u8 uParam1,u8 uParam2);
void sync_TextFilesAndTextButtonsData(u8 *param,int len);
void sync_5files_4buttonsinfor_back(u8 *param,int len);




#endif
