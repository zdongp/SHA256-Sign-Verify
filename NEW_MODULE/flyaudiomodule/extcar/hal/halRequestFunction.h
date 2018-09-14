#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__

void extcarToHal_Init(char param);

void extcarToHal_SetSpeedLockState(u8 state);

void extcarToHal_SetShiftLockState(u8 state);

void extcarToHal_SetPModeUnlockState(u8 state);

void extcarToHal_SetDPressUnlockState(u8 state);

void extcarToHal_SetFeedbackTone(u8 state);

void extcarToHal_SetLightSensitivity(u8 Value);

void extcarToHal_SetLampAutoOFFTime(u8 state);

void extcarToHal_SetLightRuningState(u8 state);

void extcarToHal_SetCarLockState(u8 state);

void extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(u8 state);/*RAV-4*/

void extcarToHal_Carola_set_oilConsumeUnit(u8 p);

////////////////////////////////////////////////////////////////////////// golf
void extcarToHal_set_initHal();
//ŒÝÊ»Ô±žšÖúÏµÍ³
void extcarToHal_set_driverAssistSystemdDriveMode(u8 p);
void extcarToHal_set_driverAssistSystemLastSelectGap(u8 p);
void extcarToHal_set_driverAssistSystemGap(u8 p);
//Ç°²¿žšÖúÏµÍ³
void extcarToHal_set_preAssistSystemActivation(u8 p);
void extcarToHal_set_preAssistSystemWarning(u8 p);
void extcarToHal_set_preAssistSystemGapWarning(u8 p);
//Æ£ÀÍŒÝÊ»Ê¶±ðÏµÍ³
void extcarToHal_set_fatigueReconizeSystemActivation(u8 p);
//ESCÏµÍ³
void extcarToHal_set_escSystemActivation(u8 p);
//ÂÖÌ¥
void extcarToHal_set_tireType(u8 p);
void extcarToHal_set_carSpeedWarning(u8 p0, u8 p1);
//µÆ¹â
void extcarToHal_set_lightSystemConnect(u8 p);
void extcarToHal_set_lightSystemAuto(u8 p);
void extcarToHal_set_lightSystemDirection(u8 p);
void extcarToHal_set_lightSystemDriveRule(u8 p);
void extcarToHal_set_lightSystemGoHome(u8 p);
void extcarToHal_set_lightSystemLeaveHome(u8 p);
void extcarToHal_set_lightSystemMeter(u8 p);
void extcarToHal_set_lightSystemDoor(u8 p);
void extcarToHal_set_lightSystemFeet(u8 p);
//³µŽ°
void extcarToHal_set_windowCtrl(u8 p);
//³µÃÅËø
void extcarToHal_set_unlockDoor(u8 p);
void extcarToHal_set_autoLockDoor(u8 p);
//ºóÊÓŸµ
void extcarToHal_set_backMirror(u8 p);
//Óê¹Î
void extcarToHal_set_autoWiper(u8 p);
void extcarToHal_set_backWiperWhenBackCar(u8 p);
//×€³µºÍµ÷³µ--µ¹³µÀ×ŽïÏµÍ³
void extcarToHal_set_backCarSystemActivation(u8 p);
void extcarToHal_set_backCarSystemPreAudio(u8 p0, u8 p1);
void extcarToHal_set_backCarSystemRearAudio(u8 p0, u8 p1);
//¶à¹ŠÄÜÏÔÊŸ
void extcarToHal_set_functionDisplay(u8 *p, int nLen);
void extcarToHal_set_cozyEconomyTipDisplay(u8 p);
//»ÖžŽÊýŸÝ
void extcarToHal_set_recoveryDriveDataFromStart(u8 p);
void extcarToHal_set_recoveryDriveDataFromLongTime(u8 p);
//µ¥Î»ÉèÖÃ
void extcarToHal_set_degreeUnit(u8 p);
void extcarToHal_set_volumeUnit(u8 p);
void extcarToHal_set_oilConsumeUnit(u8 p);
void extcarToHal_set_tireCompressUnit(u8 p);
void extcarToHal_set_distanceUnit(u8 p);
void extcarToHal_set_speedUnit(u8 p);
//Ê±Œä
void extcarToHal_set_systemTime(u8 p0, u8 p1);
void extcarToHal_set_systemDate(u8 p0, u8 p1, u8 p2);
void extcarToHal_set_SystemDateFormat(u8 p);
//žŽÎ»³ö³§ÉèÖÃ
void extcarToHal_set_recoverySetting(u8 p);
//ÓïÑÔ
void extcarToHal_set_languageSetting(u8 p);
//À×ŽïÉùÒô¿ª¹Ø
void extcarToHal_set_radarAudioDoor(u8 p);
//¿Õµ÷
void extcarToHal_set_airCtrl(u8 p);
//À¶ÑÀ
void extcarToHal_set_btCtrl(u8 *p, int nLen);
//////////////////////////////////////////////////////////////////////////

////////////////////JNI -¡·LPC Ö±Íš³µ/////////////////////////////////////
void extcarToHal_set_systemPowerMode(u8 *p, int nLen);
///////////////////////////////////////////////////////////////////////////

void extcarToHal_set_DrivingMode(u8 p);
void extcarToHal_set_Personalization(u8 p0,u8 p1,u8 p2,u8 p3,u8 p4,u8 p5,u8 p6);
void extcarToHal_set_ModeOpenOrClose(u8 p);

void extcarToHal_Public_Send_Message(u8 *param, int len);
void ToHal_Public_SetCarsParam(u8 *param, int len);
void setPublicElectronicBoosterMode (u8 param);
void setPublicRemoteControlLocFeedback (u8 param);
void setPublicShutDownTheUnlock (u8 param);
void setPublicPositionAfterLocking (u8 param);

void setPublicPositionSpeedAlarmSwitch(u8 param);
void setPublicPositionSpeedAlarmValue(u8 *param,u32 len);
void setPublicPositionSetSpeedAlarmIncOrDec(u8 param);
void setPublicPositionTrunkOpeningDegree(u8 *param,u32 len);
void setPublicPositionTrunkOpeningDegreeIncAndDec(u8 param);
void setPublicPositionWelcomeLampSwitch(u8 param);
void setPublicPositionWelcomeLampTime(u8 *param,u32 len);//time unit:s Close:0 long_Open:0xFFFA
void setPublicPositionLampCompanyHomeSwitch(u8 param);
void setPublicPositionLampCompanyHomeTime(u8 *param,u32 len);
void setPublicPositionVehicleFindingFeedback(u8 param);//0x01:lightAndWhistles 0x02:Only Whistles
void setPublicPositionDrivingAutomaticLatchSwitchAndDrivingSpeedSwitch(u8 param);
void setPublicPositionDrivingAutomaticLatchSwitchAndDrivingSpeedValue(u8 *param,u32 len);//time unit:s Close:0 long_Open:0xFFFA
void setPublicPositionDrivingAutomaticLatchSwitchAndDrivingSpeedIncAndDec(u8 param);
void setPublicPositionFlameoutAutomaticLatchSwitch(u8 param);
void setPublicPositionKeyUnlockSet(u8 param);
void setPublicPositionKeyLessUnlockSet(u8 param);
void setPublicPositionAcAutomaticFlowSet(u8 param);
void setPublicPosition_F_B_DefrostAndLog_LinkageSwitch(u8 param);
void setPublicPositionExteriorRearviewMirrorAutomaticOpenSwitch(u8 param);
void setPublicAuxscreenLanguage(u8 param);
void setPublicTrunkOpenLevelBar (u8 min,u8 max,u8 step,u8 param);
void setSyncMessageToHal(u8 *p ,int len);
void setPublicFord_TCU_FinalActivateStatus(u8 param);
void setPublicFord_AmbientLedColor_HighModel(u8 param);
void setPublicFord_AmbientLedBrightness_HighModel(u8 *param);
void setPublicFord_DistanceUnit_HighModel(u8 param);

void setPublicFord_Parking_Assist_Mode(u8 param);
void setSkylightControlMessageToHal(u8 param);
void ToHal_Public_SetBasicCarsParam(u8 *param, int len);

#endif
