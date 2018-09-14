#ifndef __APP_REQUEST_FUNCTION_DVD_H__
#define __APP_REQUEST_FUNCTION_DVD_H__

#define STRING_BUF_MAX_LEN 30

void extcarToApp_SetUp_HistoryUpdate(void);
void extcarToApp_SetUp_HistoryClear(void);
void extcarToApp_SetExtcarMenuEnable(void);
void extcarToApp_SetExtcarMenuDisable(void);
void extcarToApp_SetSerialData_Ansi2Unicode(int controlId, u8 *pBuf, int nLen);
void extcarToApp_SetUp_LightSensitivity_INC(void);
void extcarToApp_SetUp_LightSensitivity_DEC(void);

void extarToApp_CarInfoInitUI(void);
void extcarToApp_golfInitUI(void);
void extcarToApp_golfCarStyleSetting(u8 p);

void extcarToApp_about_CarInforVoicePrompt();
void setCarinfoButtonVisible(void);
void extcarToApp_InitData();
void ExtcarToAPP_TCU_ActiveRequest(u8 p);

#endif
