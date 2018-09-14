#ifndef __APP_REQUEST_FUNCTION_RADIO_H__
#define __APP_REQUEST_FUNCTION_RADIO_H__
#define RADIO_SET_UP 0
#define RADIO_SET_DOWN 1
void RadioToApp_IsCanVisitRadio(u8 bIsCanVisit);
void RadioToApp_ScanCtrlState(u8 nState);
void RadioToApp_IsRadioPowerOn(u8 nState);
void RadioToApp_FlashState(u8 nState);
void RadioToApp_LightCurChannel(u8 cChannel);
void RadioToApp_ChannelRecord(u8 cChannel);
void RadioToApp_LightCurChannelFreq(u8 cChannel, short curPage);
void RadioToApp_ClearRadioStationNameAndInfo(void);
void RadioToApp_TextInfo(u8 *pBuf, int nLen);
void RadioToApp_RadioStationName(u8 *pBuf, int nLen);
void RadioToApp_CurChannelFreqText(u8 *pBuf, int nLen);
void RadioToApp_CurAndPreChange(u32 dwPreFuncID, u32 dwCurFuncID);

void RadioToApp_SetSerialData_Ansi2Unicode(int controlId, u8 *pBuf, int nLen);
void RadioToApp_SetSerialData_Unicode(int controlId, u8 *pBuf, int nLen);
void RadioToApp_ShowCurArea(u8 areaCode);
void RadioToApp_Switch_TA(u8 nState);
void RadioToApp_Switch_AF(u8 nState);
void RadioToApp_Switch_TP(u8 nState);
void RadioToApp_Set_Switch_AF(u8 nState);
void RadioToApp_Set_Switch_TA(u8 nState);
void RadioToApp_BeginAndEndFreq(u8 cChannel);
void RadioToApp_ShowInputFreq(void);
void RadioToApp_UpdatePageAndRecord(void);
void RadioToApp_UpdatePage(u8 cChannel);
void RadioToApp_DisplayOneRecord(u32 whichOne);
void RadioToApp_NumberPagePointIsEnable(u8 isEnable);
void RadioToApp_SetGuangMaxValue(u8 cChannel);
void RadioToApp_SendRadioScanState(u8 state);/*·¢ËÍËÑÌ¨×´Ì¬¸øUI*/
void RadioToUI_Main_FM_AM_One_button(u8 p);
void RadioToUI_Main_FM_AM_Show_Unit(u8 p);



#endif
