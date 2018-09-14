#ifndef __APP_REQUEST_FUNCTION_H__
#define __APP_REQUEST_FUNCTION_H__



//App Init
void systemToApp_Init();
void SystemToApp_DisplayRadioCountry(void);
void SysteToApp_DisplayDVDRegionCode();
void systemToApp_SendVIMCode(u8 *pbuf,u8 len);
void systemToApp_WakeUpInfo(u8 status);
void systemToApp_BackVideo_CarRadarIsDisplay(u8 status);
void systemToApp_FanMode(u8 status);
void systemToApp_AllowReadParam(u8 status);
void systemToApp_HidePull_DownBar(void);
void systemToApp_getTimeFormat(void);
void SystemToApp_ShowRadioCountry( u8 param);
void systemToApp_Sound_Channel_Volume_Adjust(u8 nChannel,u8 nValue);
void systemToApp_Open_Custom_Apk(u8 nValue);


#endif
