#ifndef __HAL_RESPONSE_FUNCTION_H__
#define __HAL_RESPONSE_FUNCTION_H__

#include "global.h"
#include "messageQueue.h"

void analyseHalMessage_EXTCAR(u8 resCmd, u8 *param, u8 len);
void analyseHalMessage_CarType_Camry(unsigned char resCmd, unsigned char *param, unsigned char len);
void analyseHalMessage_CarType_Focus(unsigned char *param,unsigned char len);

void analyseHalMessage_fks_CarInfo(unsigned char *p, int len);
void analyseHalMessage_DaZhongCarInfo(unsigned char *p, int len);
void analyseHalMessage_golf_carInfo(unsigned char *p, int len);

void analyseHalMessage_toyota_CarInfor(unsigned char resCmd, unsigned char *param, unsigned char len);
void analyseHalMessage_SiYuCarInfo(u8* param, int len);
void analyseHalMessage_byd_car_info(unsigned char *param, int len);
void analyseHalMessage_mistra_car_info(u8 *param, u32 len);

void process_fks_CarInfo();
void process_DaZhongCarInfo();
void process_toyota_CarInfo();
void process_SiYu_CarInfo();
void process_byd_carInfo();
void process_golf_carInfo();

void process_HondaCRV_carInfo();
void process_DrivingDistanceInfo();
void process_BatteryVoltageInfo();

void process_EngineSpeedInfo();
void process_InstantSpeedInfo();
void process_GearsInfo();
void process_DegreeOfCarGroundInfo();
void process_DegreeOfWaterInfo();
int process_SafetyBeltInfo(int nFrom = 0);
int process_HandLockerInfo(int nFrom = 0);
int process_OilRemindInfo(int nFrom = 0);
void process_avgOilWearInfo();	/*ƽ���ͺ�*/
void process_avgOilWearInfo_kmL();
void process_curOilWearInfo();/*��ǰ�ͺ�*/
int process_CleanWaterStatusInfo(int nFrom = 0);
int process_DoorInfo(int nFrom = 0);//true have play audio, false not

void process_toyota_CarDoorLockState();

void needToAlarm(u8 nAlarmAudioID);
void DoorInfor_New_AlarmVoice(s32 param);
void SafetyBeltInfo_New_AlarmVoice(u8 param);
void HandLockerInfo_New_AlarmVoice(u8 param);

void FocusBackCar_Radar(unsigned char * p, int len);

void halToExtcar_SustainMileage(int Value);
void RunningMileage_Displaying_NewPage(int Value);/*����ʻ���*/
void AverageSpeed_Displaying_NewPage(u16 Value);/*ƽ����*/
void TravelTime_Displaying_NewPage(u8 hour,u8 minute);/*��ʻʱ��*/
void CurOilConsumption_Displaying_NewPage(unsigned char *buf,int len);/*��ǰ�ͺ�*/
void AverageOilConsumption_Displaying_NewPage(unsigned char *buf,int len);/*ƽ���ͺ�*/
void TemperatureOfTheCoolingLiquid_Displaying_NewPage();/*��ȴҺ�¶�*/
void WaterOfTheWaterTank_Displaying_NewPage();/*ˮ��ˮ��*/

void process_GreaStageInfo(void);		
void process_car_stall(void);/*��λ*/
void process_car_locker();/*������*/
void process_car_door_window();
void process_car_dormer();
void process_car_head_light();

/*golf 7*/
//ŒÝÊ»Ô±žšÖúÏµÍ³
void process_driverAssistSystemdDriveMode();
void process_driverAssistSystemLastSelectGap();
void process_driverAssistSystemGap();
//Ç°²¿žšÖúÏµÍ³
void process_preAssistSystemActivation();
void process_preAssistSystemWarning();
void process_preAssistSystemGapWarning();
//Æ£ÀÍŒÝÊ»Ê¶±ðÏµÍ³
void process_fatigueReconizeSystemActivation();
//ESCÏµÍ³
void process_escSystemActivation();
//ÂÖÌ¥
void process_tireType();
void process_carSpeedWarning();
//µÆ¹â
void process_lightSystemConnect();
void process_lightSystemAuto();
void process_lightSystemDirection();
void process_lightSystemDriveRule();
void process_lightSystemGoHome();
void process_lightSystemLeaveHome();
void process_lightSystemMeter();
void process_lightSystemDoor();
void process_lightSystemFeet();
//³µŽ°
void process_windowCtrl();
//³µÃÅËø
void process_unlockDoor();
void process_autoLockDoor();
//ºóÊÓŸµ
void process_backMirror();
//Óê¹Î
void process_autoWiper();
void process_backWiperWhenBackCar();
//×€³µºÍµ÷³µ--µ¹³µÀ×ŽïÏµÍ³
void process_backCarSystemActivation();
void process_backCarSystemPreAudio();
void process_backCarSystemRearAudio();
//¶à¹ŠÄÜÏÔÊŸ
void process_functionDisplay();
void process_cozyEconomyTipDisplay();
//»ÖžŽÊýŸÝ
void process_recoveryDriveDataFromStart();
void process_recoveryDriveDataFromLongTime();
//µ¥Î»ÉèÖÃ
void process_degreeUnit();
void process_volumeUnit();
void process_oilConsumeUnit();
void process_carola_oilConsumeUnit();
void process_tireCompressUnit();
void process_distanceUnit();
void process_speedUnit();
void process_MirrorsInTheFold_HasParking();

//Ê±Œä
void process_systemTime();
void process_systemDate();
void process_SystemDateFormat();
//žŽÎ»³ö³§ÉèÖÃ
void process_recoverySetting();
//ÓïÑÔ
void process_languageSetting();
//À×ŽïÉùÒô¿ª¹Ø
void process_radarAudioDoor();
//vim code
void process_vim();
//³µ¿öŒì²é
void process_carDistanceCheck();
void process_carTimeCheck();
//žü»»»úÓÍ
void process_engineOilDistanceCheck();
void process_engineOilTimeCheck();
//ÐÐ³µÐÅÏ¢
void process_distanceLeaveCanRun();
//žšÖúº¯Êý
void golf_avgOilConsume(int s);
void golf_driveDistance(int s);
void golf_driveTime(int s);
void golf_carSpeed(int s);
//×ÔÆô¶¯Æð
void process_avgOilConsumeFromCarRun();
void process_driveDistanceFromCarRun();
void process_driveTimeFromCarRun();
void process_carSpeedFromCarRun();
//³€Ê±Œä
void process_avgOilConsumeFromLongTimeRun();
void process_driveDistanceFromLongTimeRun();
void process_driveTimeFromLongTimeRun();
void process_carSpeedFromLongTimeRun();
//ŒÓÓÍÆð
void process_avgOilConsumeFromAddOil();
void process_driveDistanceFromAddOil();
void process_driveTimeFromAddOil();
void process_driveSpeedFromAddOil();
//žßµÍÅä
void process_carStyle();

void golf_setScreenTime();
/*golf 7*/
void process_carGolfModeKeyValue();
void process_carRequestOpenMode();
void process_carIsGotoModePage();
void process_carIsOutModePage();
void process_carGolfModeState();
void process_carGolfPersonalizationSet();

void analyseHalMessage_CarType_Nissan(unsigned char *p, int len);
void process_nissan_carInfo(void);

void analyseHalMessage_CarProtocolInfo(u8 *param,u8 len);

void GetBaseCarInfors(u8 *param,u8 len);
void GetACcarInfors(u8 *param,u8 len);
void GetSetCarInfors(u8 *param,u8 len);

void getSeatBelts(u8 *param,u8 len);
void getRemainOil(u8 *param,u8 len);
void getDriveMileage(u8 *param,u8 len);
void getOutSideTemperature(u8 *param, u8 len);
void getHandBrake(u8 *param,u8 len);
void getEngineSpeed(u8 *param,u8 len);
void getInstantSpeed(u8 *param,u8 len);
void getPublicAverageSpeed(u8 *param,u8 len);
void getBatteryVoltage(u8 *param, u8 len);
void getAverageFuelConsumption(u8 *param,u8 len);
void  getDoorStatus(u8 *param,u8 len);
void getTrunkStatus(u8 *param,u8 len);
void getRadarInfo(u8 *param,u8 len);
void getGearsInfo(u8 *param,int len);
void process_BasicCarInfo(u8 param,u8 data);
void new_Process_OilRemindInfo();
void new_Process_DrivingDistanceInfo();
void new_Process_DegreeOfCarGroundInfo();
void new_Process_EngineSpeedInfo();
void new_Process_InstantSpeedInfo();
void new_PublicAverageSpeedInfo();
void new_Process_BatteryVoltageInfo();
void new_Process_BatteryVoltageAnomalyMonitoringInfo();
void new_process_avgOilWearInfo();
int new_Process_DoorInfo(int nFrom);
void showGearsInfoToExtcar();
void analyseGearInfo(u8 param, u8 *buf);

void getPublicElectronicBoosterMode(u8 *param,int len);
void getPublicRemoteControlLocFeedback(u8 *param,int len);
void getPublicShutDownTheUnlock(u8 *param,int len);
void getPublicPositionAfterLocking(u8 *param,int len);

void analysePublicElectronicBoosterMode(u8 param);
void analysePublicShutDownTheUnlock(u8 param);
void analysePublicPublicPositionAfterLocking(u8 param);
void analysegetPublicRemoteControlLocFeedback (u8 param);
void showContinuedDriveMileage();
void getContinuedDriveMileageData(u8 *param,u8 len);

void getPublicPositionSpeedAlarmSwitchAndThreshold(u8 *param,int len);
void getPublicPositionTrunkDegree(u8 *param,int len);
void analysePublicSpeedAlarmSwitch(u8 *p,int len);
void analysePublicSpeedAlarmThreshold(u8 *p,int len);
void analysePublicSpeedAlarmIncAndDec(u8 *p,int len);
void analysePublicTrunkDegreeValue(u8 *p,int len);
void analysePublicTrunkDegreeIncAndDec(u8 *p,int len);
void getPublicWelcomeLamp(u8 *param,int len);
void analysePublicWelcomeLampSwitch(u8 *p,int len);
void analysePublicWelcomeLampTimeValue(u8 *p,int len);
void getPublicCompanyLampHome(u8 *param,int len);
void analysePublicCompanyLampHomeSwtich(u8 *p,int len);
void analysePublicCompanyLampHomeTimeValue(u8 *p,int len);
void getPublicvehicle_mode(u8 *param,int len);
void analysePublicVehicle_mode(u8 *p,int len);
void getPublicDriving_automatic_latch(u8 *param,int len);
void analysePublicDriving_automatic_latch_Switch(u8 *p,int len);
void analysePublicDriving_automatic_latch_SpeedValue(u8 *p,int len);
void analysePublicDriving_automatic_latch_IncAndDec(u8 *p,int len);
void getPublicFlameout_Automatic_Latch(u8 *param,int len);
void analysePublicFlameout_Automatic_Latch(u8 *p,int len);
void getPublicKey_Unlock_Door(u8 *param,int len);
void analysePublicKey_Unlock_Door(u8 *p,int len);
void getPublicKeyLess_Unlock_Door(u8 *param,int len);
void analysePublicKeyLess_Unlock_Door(u8 *p,int len);
void getPublicACSetData(u8 *param,int len);
void analysePublicAC_automatic_mode_flow(u8 *p,int len);
void analysePublicF_B_Defrost_Fog_Linkage_switch(u8 *p,int len);
void getPublicMirrorAutomaticOpenSwitch(u8 *param,int len);
void getPublicSystemLanguageSet(u8 *param, u8 len);
void analysePublicMirrorAutomaticOpenSwitch(u8 *p,int len);


void getRadarDistanceData(u8 *param,int len);
void analyseRadarDistanceData(u8 ForR,u16 p,u8 tag);
void showRadarRearDistanceData(u16 p ,u8 tag);
void analysePublicBackCarViodeMessage(u8 *p,u8 len);
int getMainDriverRightDoorInfo(int num);

void  getDoorLockStatus(u8 *param,u8 len);
void  getFrontCoverStatus(u8 *param,u8 len);
void  getSkyLightStatus(u8 *param,u8 len);
void  getLightStatus(u8 *param,u8 len);
void getHighBeamStatus(u8 param);
void getDippedHeadlightStatus(u8 param);
void getVINCode(u8 *param,u8 len);
void getVINCodeInfo(u8 *param,u8 len);

void getPublicFordTCUMessage(u8 *p,u8 len);

void getPublicFordAmbientLedMessage(u8 *p,u8 len);
void analyseAmbientLedColorValue(u8 param);
void analyseAmbientLedBrightnessValue(u8 *param);
void getRadarData(u8 *p);
void getRadarPOP(u8 p);

void getPublicAuxiliaryParkingSystemMessage(u8 *p,u8 len);
void analyseParkingAssistMode(u8 s);
void analyseParkingAssistModeIsActivety(u8 *param);
void analyseParkingAssistMsg(u8 *param,u8 len);

void getPublicMultiContouredSeatsMessage(u8 *p,u8 len);
void analyseSeatPressurePercentageUpperLumbar(u8 p1,u8 p2);
void analyseSeatPressurePercentageMiddleLumbar(u8 p1,u8 p2);
void analyseSeatPressurePercentageLowerLumbar(u8 p1,u8 p2);
void analyseSeatPressurePercentageUpperBolster(u8 p1,u8 p2);
void analyseSeatPressurePercentageLowerBolster(u8 p1,u8 p2);
void analyseSeatIntensityLumbarMassage(u8 p1,u8 p2);
void analyseSeatIntensityCushionMassage(u8 p1,u8 p2);

#endif
