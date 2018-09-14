#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

void appToExtcar_daZhong_set_iSSendChineseToCarScreen();
////////////////////////////////////////////////////////////////////////// golf
void appToExtcar_golf_set_DriveDataFromSomeTime(u8 p);
//ŒÝÊ»Ô±žšÖúÏµÍ³
void appToExtcar_golf_set_driverAssistSystemdDriveMode(u8 p);
void appToExtcar_golf_set_driverAssistSystemLastSelectGap(u8 p);
void appToExtcar_golf_set_driverAssistSystemGap(u8 p);
//Ç°²¿žšÖúÏµÍ³
void appToExtcar_golf_set_preAssistSystemActivation(u8 p);
void appToExtcar_golf_set_preAssistSystemWarning(u8 p);
void appToExtcar_golf_set_preAssistSystemGapWarning(u8 p);
//Æ£ÀÍŒÝÊ»Ê¶±ðÏµÍ³
void appToExtcar_golf_set_fatigueReconizeSystemActivation(u8 p);
//ESCÏµÍ³
void appToExtcar_golf_set_escSystemActivation(u8 p);
//ÂÖÌ¥
void appToExtcar_golf_set_tireType(u8 p);
void appToExtcar_golf_set_tireTypeYes();
void appToExtcar_golf_set_tireTypeNo();
void appToExtcar_golf_set_carSpeedWarning(u8 p0, u8 p1);
//µÆ¹â
void appToExtcar_golf_set_lightSystemConnect(u8 p);
void appToExtcar_golf_set_lightSystemAuto(u8 p);
void appToExtcar_golf_set_lightSystemDirection(u8 p);
void appToExtcar_golf_set_lightSystemDriveRule(u8 p);
void appToExtcar_golf_set_lightSystemGoHome(u8 p);
void appToExtcar_golf_set_lightSystemLeaveHome(u8 p);
void appToExtcar_golf_set_lightSystemMeter(u8 p);
void appToExtcar_golf_set_lightSystemDoor(u8 p);
void appToExtcar_golf_set_lightSystemFeet(u8 p);
//³µŽ°
void appToExtcar_golf_set_windowCtrl(u8 p);
//³µÃÅËø
void appToExtcar_golf_set_unlockDoor(u8 p);
void appToExtcar_golf_set_autoLockDoor(u8 p);
//ºóÊÓŸµ
void appToExtcar_golf_set_backMirror(u8 p0, u8 p1);
//Óê¹Î
void appToExtcar_golf_set_autoWiper(u8 p);
void appToExtcar_golf_set_backWiperWhenBackCar(u8 p);

//×€³µºÍµ÷³µ--µ¹³µÀ×ŽïÏµÍ³
void appToExtcar_golf_set_backCarSystemActivation(u8 p);
void appToExtcar_golf_set_backCarSystemPreAudio(u8 p0, u8 p1);
void appToExtcar_golf_set_backCarSystemRearAudio(u8 p0, u8 p1);
void appToExtcar_golf_set_radarRingDoor();

//¶à¹ŠÄÜÏÔÊŸ
void appToExtcar_golf_set_functionDisplay(u8 p0, u8 p1);
void appToExtcar_golf_set_cozyEconomyTipDisplay(u8 p0, u8 p1);
//»ÖžŽÊýŸÝ
void appToExtcar_golf_set_recoveryDriveDataFromStart(u8 p);
void appToExtcar_golf_set_recoveryDriveDataFromLongTime(u8 p);
//µ¥Î»ÉèÖÃ
void appToExtcar_golf_set_degreeUnit(u8 p);
void appToExtcar_golf_set_volumeUnit(u8 p);
void appToExtcar_golf_set_oilConsumeUnit(u8 p);
void appToExtcar_golf_set_tireCompressUnit(u8 p);
void appToExtcar_golf_set_distanceUnit(u8 p);
void appToExtcar_golf_set_speedUnit(u8 p);

//Ê±Œä
void appToExtcar_golf_set_systemTime(u8 p0, u8 p1);
void appToExtcar_golf_set_systemDate(u8 p0, u8 p1, u8 p2);
void appToExtcar_golf_set_SystemDateFormat(u8 p);
//žŽÎ»³ö³§ÉèÖÃ
void appToExtcar_golf_set_recoverySetting(u8 p);
void appToExtcar_golf_set_recoverySettingYes();
void appToExtcar_golf_set_recoverySettingNo();
//ÓïÑÔ
void appToExtcar_golf_set_languageSetting(u8 p);
//À×ŽïÉùÒô¿ª¹Ø
void appToExtcar_golf_set_radarAudioDoor(u8 p);
//¿Õµ÷
void appToExtcar_golf_set_airCtrl(u8 p);
//////////////////////////////////////////////////////////////////////////

bool appToExtcar_golf_setDrivingMode_MouseUp(u32 ctrID);
bool appToExtcar_golf_setDrivingMode_MouseDown(u32 ctrID);
bool UI_DrivingModeDisplay(u32 ContrID);
void appToExtcar_golf_set_Personalization(u32 ctrID);
void UI_Car_Golf_PersonalizationModeResetActionBox(bool bShow);

void process_DampingSystemMode();
void process_SteeringWheelMode();
void process_DrivingGearMode();
void process_Dynamic_Headlight_FollowerMode();
void process_AcMode();
void process_InternalEngineSoundsMode();

void appToExtcar_SetDampingSystem(u8 param);
void appToExtcar_SetSteeringWheel(u8 param);
void appToExtcar_SetDrivingGear(u8 param);
void appToExtcar_SetDynamicHeadlight(u8 param);
void appToExtcar_SetAcMod(u8 param);
void appToExtcar_SetEngineSoundsMod(u8 param);
void appToExtcar_SetModeResetAction(u8 param);
void extcarToHal_SetPersonalizationData();

void appToExtcar_carola_set_oilConsumeUnit(u8 p);
bool appToExtcar_blue_skin_tables_MouseUp(u32 ctrID);

void DispalyingUI_speed_limit_alarm_switch(u8 p);
void DispalyingUI_speed_limit_alarm_Value(u32 param);
void DispalyingUI_speed_limit_alarmSet(u8 b);
void appToExtcar_set_speed_limit_alarm_switch();
void appToExtcar_set_alarmSpeedValue(u8 p);//30~240KM/H
void DispalyingUI_trunk_opening_degree_Value(u8 param);
void appToExtcar_set_trunk_opening_degree(u8 p);//40%~100%
void DispalyingUI_welcome_lamp_switch(u8 p);
void DispalyingUI_welcome_lamp_open_time(u16 param);
void DispalyingUI_welcome_lamp_open_Set(u8 b);
void appToExtcar_set_welcome_lamp_switch();
void appToExtcar_set_welcome_lamp_OpenTime(u8 p);
void MakeWelcomeLampOpenTimeData(u16 p);
void DispalyingUI_company_home_lamp_switch(u8 p);
void DispalyingUI_company_home_lamp_open_time(u16 param);
void DispalyingUI_company_home_lamp_Set(u8 b);
void appToExtcar_set_company_home_lamp_switch();
void appToExtcar_set_company_home_lamp_OpenTime(u8 p);
void MakeLampCompanyHomeTimeData(u16 p);
void DispalyingUI_vehicle_mode(u16 param);
void appToExtcar_set_vehicle_mode(u8 p);
void DispalyingUI_driving_automatic_latch_switch(u8 p);
void DispalyingUI_driving_automatic_latch_speed_alarm_Value(u32 param);
void appToExtcar_set_driving_automatic_latch_switch();
void appToExtcar_set_driving_automatic_latch_alarmSpeedValue(u8 p);//30~240KM/H
void DispalyingUI_flameout_automatic_latch_switch(u8 p);
void appToExtcar_set_flameout_automatic_latch_switch();
void DispalyingUI_key_unlock_door(u8 p);
void appToExtcar_set_key_unlock_door(u8 p);
void DispalyingUI_keyLess_unlock_door(u8 p);
void appToExtcar_set_keyLess_unlock_door(u8 p);
void DispalyingUI_AC_automatic_mode_flow(u16 param);
void appToExtcar_set_AC_automatic_mode_flow(u8 p);
void DispalyingUI_F_B_Defrost_Fog_Linkage_switch(u8 p);
void appToExtcar_set_F_B_Defrost_Fog_Linkage_switch();
void DispalyingUI_Mirror_automatic_open_switch(u8 p);
void appToExtcar_set_Mirror_automatic_open_switch();
void DispalyingUI_trunk_opening_degree_Value_Bar(u8 param , u8 p);


void UI_ParkOutAssist(u8 s);
void UI_ParallelPark(u8 s);
void UI_PerpendicularPark(u8 s);
void UI_ActiveParkAssit(u8 s);


#endif
