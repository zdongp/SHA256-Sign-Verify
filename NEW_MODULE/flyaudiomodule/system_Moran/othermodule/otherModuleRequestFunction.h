#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__

#define SYSTEM_NOTIFY_REBOOT               0x10
#define SYSTEM_NOTIFY_RESTOREDEFAULTS      0x14

#define SYSTEM_NOTIFY_GALAXY_ACCON		0x2C
#define SYSTEM_NOTIFY_GALAXY_ACCOFF		0x2D

#define SYSTEM_NOTIFY_ACCON        0x30
#define SYSTEM_NOTIFY_ACCOFF       0x31

#define SYSTEM_NOTIFY_CHANGEPAGE   0xE3



//Notify System Module
//Jump Specify Page
void systemToModule_NotifySystem_JumpPage(short nPageID);
//Jump Pre Page
void systemToModule_NotifySystem_JumpPrePage(void);
void systemToModule_NotifySystem_SwithModule(u8 moduleId);

void systemToModule_NotifyRadio();
//Notify All Module
//Restore Defaults
void systemToModule_NotifyAllModule_RestoreDefaults();
//Reboot
void systemToModule_NotifyAllModule_Reboot();
//ACC ON 
void systemToModule_NotifyAllModule_AccOn();
//ACC OFF
void systemToModule_NotifyAllModule_AccOff();

//ACC ON 
void systemToModule_NotifyAllModule_Galaxy_AccOn();
//ACC OFF
void systemToModule_NotifyAllModule_Galaxy_AccOff();
//Notify Sound Module
void systemToModule_NotifySoundModule_SysInitStatus(u8 u8_status);
void systemToModule_NotifySoundModule_StartupVol(u8 u8_status);
void systemToModule_NotifySoundModule_GPSVoicePrompt(u8 u8_status);


//Notify Some Module
void systemToModule_NotifySomeModule_ChangePage(u8 u8_Module,u16 u16_LewPage,u16 u16_EnterPage,u8 u8_Param);
void systemToModule_NotifySomeModule_BrakeCarStatus(u8 u8Status);
void systemToModule_NotifySomeModule_StandbyStatus(u8 u8Status);
void systemToModule_NotifySomeModule_GPSAutoRunStatus(u8 u8Status);
void systemCallParrotBT_aboutSerialDataUIFunction(u32 u32_ctrID,u8* param,int len);


//Notify Radio Module
void systemToModule_NotifyRadioModule_PressKey_AV();

//Notify Key Module
//Notify Key Whether Lcd Close Or Not
void systemToModule_NotifyKeyModule_WhetherLcdClose(bool bStatus); 


//Notify BackCar Module
void systemToModule_NotifyBackModule_BackCarStatus(u8 bStatus, u8 bVideo); 
void systemToModule_NotifyBackModule_BackCarVideoRefLineDisplaySet(u8 bStatus);
void systemToModule_NotifyBackModule_BackCarRadarStatus(unsigned char status);
void systemToModule_NotifyBackModule_BackCarVideoTraceLineDisplaySet(u8 bStatus);

//Notify TPMS Module
void systemToModule_NotifyTPMSModule_MagnitudeOfVoltage(u8 u8_Param);
void systemToModule_NotifyTPMSModule_WhetherTPMSExist(u8 u8_Param);

//Notify TV Module
void systemToModule_NotifyTVModule_WhetherTVExist(u8 u8_Param);

//Notify AUX Module
void systemToModule_NotifyAUXModule_AUXVideo(u8 u8_Param);

// Notify Ipod Module
void systemToModule_NotifyIpod_ExitIpol(u8 u8_Param);

//Notify GPS
void systemToGPSRun_NotifyGPSRun_AutoRunMsg(bool bStatus); //Send Msg To GPSRun.exe
void systemToGPSRun_NotifyGPS_15sJumpPage();

// Notify OSD Module
void systemToModule_NotifyOSD_Low_Bettery(u8 u8_Parm);  //  jing  2013-8-12 low bettery osd
void systemToModule_NotifyOSD_IsHaveRadarData(u8 HaveRadarData);

/*****************************************************************************************/
void systemToModule_NotifyOSD_OSDDebug_Info(u8 *buffer, u8 len);
void systemToModule_NotifyOSD_OSDDebugInfo_Switch(void);
void systemToModule_NotifyOSD_OSD_barcode();
void systemToModule_NotifyOSD_backcar_RadarDirectAndLevel(u8 u8_Parm1,u8 u8_Parm2);
void systemToModule_NotifyOSD_backcar_carRadar_DisplayingAndHander(u8 u8_Parm);
void systemToModule_NotifyOSD_backcar_carRadar_SwitchRadarcarPage(u8 u8_Parm);
void systemToModule_NotifyGps_DayOrNight(u8 u8_Param);
void systemToModule_NotifyDNV_DayOrNight(u8 p);

void systemToModule_NotifyDVRModule_DVRVideo(u8 u8_param);

void systemToModule_NotifyDVRModule_LewOrEnterDVR();

void systemToModule_NotifyServiceModule_ChangeCarMode(u8 u8_Param);
void systemToModule_NotifyServiceModule_StandbyState(u8 u8_Param);



//�����豸����״̬��OSD��ʾ
void SendDeviceStateToOSDDebug(void);
void SendBackcarInfoAndDiaInStateToOSDDebug(void);


void systemToModule_NotifyExtcarModule_CarInforVoiceStatus(bool state);


//����AUX��Ƶ�����ʾ����
void systemToModule_NotifyAUXModule_AUXChecking();

void systemToModule_NotifyBtModule_aboutStandby(u8 uState);



void systemToModule_NotifySyncModule_aboutFlySystem_OperatingNormal(u8 uParam);
void systemToModule_NotifySyncModule_aboutFastStandy_SyncMediaPlay(u8 uParam);


void setToDNVbackKey(void);
void setToDNVGoInto(void);
void setToDNVSupport(u8 p);



void systemToModule_NotifyAudiovideo_SetThirdChannel();

void systemToModule_NotifyExtcarModule_CarBatteryVolt(u8 *param);

void systemToModule_NotifyRemoteOnline_AccStatus(u8 p);
void systemToModule_NotifyRemoteOnline_StandbyStatus(u8 p);

void systemToModule_NotifyDVR_setBackCarProtocol_CVBS_or_USB(u8 p);

void systemToModule_NotifyBackModule_BackCarVideoTraceLine_Type_Set(u8 bStatus);

void systemToModule_NotifyExternalctrl_SpeechEnable(u8 p);
void systemToModule_NotifyExtcar_SetCameraDelay(u8 p);
void systemToModule_NotifyExtcar_SetTempUnit(u8 p);


void systemToModule_NotifyExtcarModule_CarBatteryVoltAnomalyMonitoring(u8 param);
void systemToModule_NotifyService_BarcodeInfors(u8 *p,u32 len);

void systemToModule_NotifyExtcarModule_AmbientLedColor_HighModelFord(u8 param);
void systemToModule_NotifyExtcarModule_AmbientLedBrightness_HighModelFord(u8 *param);
void systemToModule_NotifyExtcarModule_DistanceUnit_HighModelFord(u8 param);


void setPublicFord_MultiContouredSeats(u8 *param,int len);
void setMultiContouredSeats_PressurePercentage_UpperLumbar(u8 p1,u8 p2);
void setMultiContouredSeats_PressurePercentage_MiddleLumbar(u8 p1,u8 p2);
void setMultiContouredSeats_PressurePercentage_LowerLumbar(u8 p1,u8 p2);
void setMultiContouredSeats_PressurePercentage_UpperBolster(u8 p1,u8 p2);
void setMultiContouredSeats_PressurePercentage_LowerBolster(u8 p1,u8 p2);
void setMultiContouredSeats_MassageIntensity_Lumbar(u8 p1,u8 p2);
void setMultiContouredSeats_MassageIntensity_Cushion(u8 p1,u8 p2);
void setMultiContouredSeats_Control(u8 side,u8 select,u8 cmd,u8 state);
void setMultiContouredSeats_Mode(u8 p);














#endif
