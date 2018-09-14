#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__



void extcarToModule_NotifySystem_jumpPage(u16 pageId);
void extcarToModule_NotifySystem_jumpPrePage(void);

void exterToFOCUS_sync_FromHal(u8 *param, u8 len);
void exterToCenter_NoticeAlarmTip(u8 param);

///////////////////////////////// DA ZHONG //////////////////////////////////////////////
void exterToAirCondition(u8 *param, u8 len);
void exterToAirData_aboutToyotaCamry(u8 *param, u8 len);

void exterToKey_Da_Zhong_Steer_Key(u8 key);
void exterToRadar(u8 pos, u32 distance);
void exterToRadar(u8 param);
///////////////////////////////// DA ZHONG //////////////////////////////////////////////

void exterToAC_fks(u8 *param, int len);
void exterToAC_SiYu(u8 *param, int len);

void exterToAC_byd(u8 *param, int len);
void exterToAC_golf(u8 *param, int len);
void exterToAC_golf_ctrl(u8 param);
void exterToAC_golf_acState(u8 param);
void exterToBT_golf(u8 *param, int len);
void exterToGPS_golf(u8 *param, int len);
void exterToUI_golf_car_style(u8 p);//žßµÍÅä

void exterToAC_HondaCRV(u8 *param, int len);
void extcarToSystem_about_CarInforVoicePrompt(bool state);
void exterToAuxScreen_aboutMp3NameAndGpsRoadName_IsDisplaying(u8 state);

void exterToSystem_aboutBatteryVoltageInfo(int nParam);

/*
void centerToModule_NotifySystem_Hardware_JumpPrePage(void);
void centerToModule_NotifySystem_EnterThreePartyApp(void);
void centerToModule_NotifySystem_EnterHomePage(void);
void centerToModule_NotifySystem_EnterNonHomePage(void);


void centerToModule_NotifySystem_DebugPanelType(unsigned char panelType);

void centerToModule_NotifyOSD_SetOSDHidden(void);

void centerToModule_NotifyAudiovideo_GpsSoundState(unsigned char state);

void centerToModule_NotifySystem_ReturnToPage(unsigned char *pageid, int len);
*/


void extcarToAudioVideo(u8 *p, int len);
void exterPradoRadarKeySwitchToSystem(u8 param);
void exterPradoRadarUISwitchToSystem(u8 param);

void mistraCarToAirCondition(u8 *param, u8 len);
void ExtcarToModule_Ac_PublicAcInfo(u8 *param,u8 len);
void ExtcarToModule_Tpms_PublicTpmsInfo(u8 *param,u8 len);
void ExtcarToModule_system_PublicVehicleSettings(u8 *param,u8 len);
void ExtcarToModule_BackCar_VideoSet(u8 *param,u8 len);
void extcarToOtherModule_System_FrontCameraApp(u8 p);



#endif
