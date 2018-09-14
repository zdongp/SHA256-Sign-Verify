#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "stringID.h"
#include "timer_interface.h"


void appToExtcar_daZhong_set_iSSendChineseToCarScreen()
{
	int t = pLocalParam->nCanSendChineseToDZCarScreen;
	(t == 1) ? (t = 0, setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_SMALL_SCREEN, t))
			   :(t = 1, setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_SMALL_SCREEN, t));
	pLocalParam->nCanSendChineseToDZCarScreen = t;
	exterToAuxScreen_aboutMp3NameAndGpsRoadName_IsDisplaying(pLocalParam->nCanSendChineseToDZCarScreen);
}
////////////////////////////////////////////////////////////////////////// golf
//ÐÐÊ»ÊýŸÝ
void appToExtcar_golf_set_DriveDataFromSomeTime(u8 p)
{
	if (pLocalParam->nAvgOilConsumeFromCarRun == -1)
		return;

	u8 s = pLocalParam->eDriveDataType;
	if (p == SELECT_CTRL_UP)
		s = (s + 1) % 3;
	else
		s = (s + 3 - 1) % 3;
	pLocalParam->eDriveDataType = (E_DRIVE_DATA_TYPE)s;
	//Ä£ÄâLPC·¢Ò»Ö¡ÊýŸÝ
	//×ÔÆô¶¯Æð
	process_avgOilConsumeFromCarRun();
	process_driveDistanceFromCarRun();
	process_driveTimeFromCarRun();
	process_carSpeedFromCarRun();
	//³€Ê±Œä
	process_avgOilConsumeFromLongTimeRun();
	process_driveDistanceFromLongTimeRun();
	process_driveTimeFromLongTimeRun();
	process_carSpeedFromLongTimeRun();
	//ŒÓÓÍÆð
	process_avgOilConsumeFromAddOil();
	process_driveDistanceFromAddOil();
	process_driveTimeFromAddOil();
	process_driveSpeedFromAddOil();
}
//ŒÝÊ»Ô±žšÖúÏµÍ³
void appToExtcar_golf_set_driverAssistSystemdDriveMode(u8 p)
{
	int n = 3;
	int t = pLocalParam->eDriveMode - 1;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ( ((t - 1) + n) % n );
	t += 1;
	pLocalParam->eDriveMode = (E_DRIVE_MODE)t;
	LOGD("dyb test drivemode = [%d]", t);
	extcarToHal_set_driverAssistSystemdDriveMode(t);
}
void appToExtcar_golf_set_driverAssistSystemLastSelectGap(u8 p)
{
	extcarToHal_set_driverAssistSystemLastSelectGap(p);
}
void appToExtcar_golf_set_driverAssistSystemGap(u8 p)
{
	int n = 5;
	int t = pLocalParam->eGap;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ( ((t - 1) + n) % n );
	pLocalParam->eGap = (E_GAP)t;
	extcarToHal_set_driverAssistSystemGap(t);
}
//Ç°²¿žšÖúÏµÍ³
void appToExtcar_golf_set_preAssistSystemActivation(u8 p)
{
	extcarToHal_set_preAssistSystemActivation(p);
}
void appToExtcar_golf_set_preAssistSystemWarning(u8 p)
{
	extcarToHal_set_preAssistSystemWarning(p);
}
void appToExtcar_golf_set_preAssistSystemGapWarning(u8 p)
{
	extcarToHal_set_preAssistSystemGapWarning(p);
}
//Æ£ÀÍŒÝÊ»Ê¶±ðÏµÍ³
void appToExtcar_golf_set_fatigueReconizeSystemActivation(u8 p)
{
	extcarToHal_set_fatigueReconizeSystemActivation(p);
}
//ESCÏµÍ³
void appToExtcar_golf_set_escSystemActivation(u8 p)
{
	extcarToHal_set_escSystemActivation(p);
}
//ÂÖÌ¥
void appToExtcar_golf_set_tireType(u8 p)
{
	bool bVisible = true;
	setUpdateUI(false);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP_BOX, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_CANCLE, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_ENTER, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP1, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP2, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP3, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP4, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP5, bVisible);
	setUpdateUI(true);
}

void appToExtcar_golf_set_tireTypeYes()
{
	bool bVisible = false;
	setUpdateUI(false);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP_BOX, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_CANCLE, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_ENTER, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP1, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP2, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP3, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP4, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP5, bVisible);
	setUpdateUI(true);
	extcarToHal_set_tireType(0);
}

void appToExtcar_golf_set_tireTypeNo()
{
	bool bVisible = false;
	setUpdateUI(false);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP_BOX, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_CANCLE, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_ENTER, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP1, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP2, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP3, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP4, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_TIP5, bVisible);
	setUpdateUI(true);
}

void appToExtcar_golf_set_carSpeedWarning(u8 p0, u8 p1)
{
	int r = 220;
	int t = (pLocalParam->nCarSpeedWarning <= 30) ? 0 : (pLocalParam->nCarSpeedWarning - 30);
	if (p1 != SELECT_CTRL_UNKNOW)
		t = (p1 == SELECT_CTRL_UP) ? ((t + 10) % r) : ((t + r - 10) % r);
	t += 30;
	pLocalParam->nCarSpeedWarning = t;
	extcarToHal_set_carSpeedWarning(p0, t);
}
//µÆ¹â
void appToExtcar_golf_set_lightSystemConnect(u8 p)
{
	int n = 3;
	int t = pLocalParam->eLightSystemConnect;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ((t + n - 1) % n);
	pLocalParam->eLightSystemConnect = (E_LIGHT_SYSTEM_CONNECT)t;
	extcarToHal_set_lightSystemConnect(t);
}
void appToExtcar_golf_set_lightSystemAuto(u8 p)
{
	extcarToHal_set_lightSystemAuto(p);
}
void appToExtcar_golf_set_lightSystemDirection(u8 p)
{
	extcarToHal_set_lightSystemDirection(p);
}
void appToExtcar_golf_set_lightSystemDriveRule(u8 p)
{
	int n = 2;
	int t = pLocalParam->eDriveRule;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ( (t + n - 1) % n );
	pLocalParam->eDriveRule = (E_DRIVE_RULE)t;
	extcarToHal_set_lightSystemDriveRule(t);
}
void appToExtcar_golf_set_lightSystemGoHome(u8 p)
{
	LOGD("dyb go home");
	int r = 95;
	int t = pLocalParam->nGoHomeModeTime;
	if (p != SELECT_CTRL_UNKNOW)
		t = (p == SELECT_CTRL_UP) ? ((t + 5) % r) : ((t + r - 5) % r);
	pLocalParam->nGoHomeModeTime = t;
	extcarToHal_set_lightSystemGoHome(t);
}
void appToExtcar_golf_set_lightSystemLeaveHome(u8 p)
{
	LOGD("dyb leave home");
	int r = 95;
	int t = pLocalParam->nLeaveHomeModeTime;
	if (p != SELECT_CTRL_UNKNOW)
		t = (p == SELECT_CTRL_UP) ? ((t + 5) % r) : ((t + r - 5) % r);
	pLocalParam->nLeaveHomeModeTime = t;
	extcarToHal_set_lightSystemLeaveHome(t);
}
void appToExtcar_golf_set_lightSystemMeter(u8 p)
{
	int r = 110;
	int t = pLocalParam->nMeterLightBrightness;
	if (p != SELECT_CTRL_UNKNOW)
		t = (p == SELECT_CTRL_UP) ? ((t + 10) % r) : ((t + r - 10) % r);
	pLocalParam->nMeterLightBrightness = t;
	extcarToHal_set_lightSystemMeter(t);
}
void appToExtcar_golf_set_lightSystemDoor(u8 p)
{
	int r = 110;
	int t = pLocalParam->nDoorLightBrightness;
	if (p != SELECT_CTRL_UNKNOW)
		t = (p == SELECT_CTRL_UP) ? ((t + 10) % r) : ((t + r - 10) % r);
	pLocalParam->nDoorLightBrightness = t;
	extcarToHal_set_lightSystemDoor(t);
}
void appToExtcar_golf_set_lightSystemFeet(u8 p)
{
	int r = 110;
	int t = pLocalParam->nFeetLightBrightness;
	if (p != SELECT_CTRL_UNKNOW)
		t = (p == SELECT_CTRL_UP) ? ((t + 10) % r) : ((t + r - 10) % r);
	pLocalParam->nFeetLightBrightness = t;
	extcarToHal_set_lightSystemFeet(t);
}
//³µŽ°
void appToExtcar_golf_set_windowCtrl(u8 p)
{
	int n = 3;
	int t = (pLocalParam->eWindowCtrl == 0x1F) ? 2 : pLocalParam->eWindowCtrl;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ( (t + n - 1) % n );
	pLocalParam->eWindowCtrl = (E_WINDOW_CTRL)((t == 2) ? 0x1F : t);
	extcarToHal_set_windowCtrl((u8)pLocalParam->eWindowCtrl );
}
//³µÃÅËø
void appToExtcar_golf_set_unlockDoor(u8 p)
{
	int n = 3;
	int t = pLocalParam->eDoorCtrl;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ( (t + n - 1) % n );
	pLocalParam->eDoorCtrl = (E_DOOR_CTRL)t;
	extcarToHal_set_unlockDoor(t);
}
void appToExtcar_golf_set_autoLockDoor(u8 p)
{
	extcarToHal_set_autoLockDoor(p);
}
//ºóÊÓŸµ
void appToExtcar_golf_set_backMirror(u8 p0, u8 p1)
{
	u8 r = 0;
	if (p0 == 0)//µ¹³µµµÊ±œµµÍ
	{
		r |= p1;
		r |= ( (pLocalParam->eBackMirrorSync == BACK_MIRROR_SYNC_YES) ? 1 : 0 ) << 1;
		r |= ( (pLocalParam->emMirrorsIntheFoldParkedSelect == MIRRORS_IN_THE_FOLD_HAS_PARKING_YES) ? 1 : 0) << 2;
	}
	else if(p0 == 1)//Í¬²œµ÷œÚ
	{
		r |= (pLocalParam->eBackMirrorReverseCar == BACK_MIRROR_REVERSE_CAR_YES) ? 1 : 0;
		r |= p1 << 1;
		r |= ( (pLocalParam->emMirrorsIntheFoldParkedSelect == MIRRORS_IN_THE_FOLD_HAS_PARKING_YES) ? 1 : 0) << 2;
	}
	else if(p0 == 2)
	{
		r |= (pLocalParam->eBackMirrorReverseCar == BACK_MIRROR_REVERSE_CAR_YES) ? 1 : 0;
		r |= ( (pLocalParam->eBackMirrorSync == BACK_MIRROR_SYNC_YES) ? 1 : 0 ) << 1;
		r |= p1 << 2;
	}
	
	extcarToHal_set_backMirror(r);
}
//Óê¹Î
void appToExtcar_golf_set_autoWiper(u8 p)
{
	extcarToHal_set_autoWiper(p);
}
void appToExtcar_golf_set_backWiperWhenBackCar(u8 p)
{
	extcarToHal_set_backWiperWhenBackCar(p);
}
//×€³µºÍµ÷³µ--µ¹³µÀ×ŽïÏµÍ³
void appToExtcar_golf_set_backCarSystemActivation(u8 p)
{
	extcarToHal_set_backCarSystemActivation(p);
}
void appToExtcar_golf_set_backCarSystemPreAudio(u8 p0, u8 p1)
{
	int n = 9;
	int yd = pLocalParam->nCarFrontAudioParam & 0xFF;
	int yl = pLocalParam->nCarFrontAudioParam >> 8;
	if (p0 == AUDIO_TYPE_YL)//ÒôÁ¿
	{
		yl -= 1;
		yl = (p1 == SELECT_CTRL_UP) ? ( (yl + 1) % n ) : ( (yl + n - 1) % n );
		yl += 1;
	}
	else//Òôµ÷
	{
		yd -= 1;
		yd = (p1 == SELECT_CTRL_UP) ? ( (yd + 1) % n ) : ( (yd + n - 1) % n );
		yd += 1;
	}
	int m = yd;
	m += yl << 8;
	pLocalParam->nCarFrontAudioParam = m;
	extcarToHal_set_backCarSystemPreAudio(yd, yl);
}
void appToExtcar_golf_set_backCarSystemRearAudio(u8 p0, u8 p1)
{
	int n = 9;
	int yd = pLocalParam->nCarRearAudioParam & 0xFF;
	int yl = pLocalParam->nCarRearAudioParam >> 8;
	if (p0 == AUDIO_TYPE_YL)//ÒôÁ¿
	{
		yl -= 1;
		yl = (p1 == SELECT_CTRL_UP) ? ( (yl + 1) % n ) : ( (yl + n - 1) % n );
		yl += 1;

	}
	else//Òôµ÷
	{
		yd -= 1;
		yd = (p1 == SELECT_CTRL_UP) ? ( (yd + 1) % n ) : ( (yd + n - 1) % n );
		yd += 1;

	}
	int m = yd;
	m += yl << 8;
	pLocalParam->nCarRearAudioParam = m;
	extcarToHal_set_backCarSystemRearAudio(yd, yl);
}

void appToExtcar_golf_set_radarRingDoor()
{
	int t = pLocalParam->nGolfRadarRingDoor;
	(t == 1) ? (t = 0) : (t = 1);
	pLocalParam->nGolfRadarRingDoor = t;
	extcarToHal_set_radarAudioDoor(pLocalParam->nGolfRadarRingDoor);
}

//¶à¹ŠÄÜÏÔÊŸ
void appToExtcar_golf_set_functionDisplay(u8 p0, u8 p1)
{
	static const int nLen = 7;
	u8 szMsg[nLen] = {0};
	szMsg[0] = pLocalParam->eOilConsumeSelect;
	szMsg[1] = pLocalParam->eOilAvgConsumeSelect;
	szMsg[2] = pLocalParam->eDriveTimeSelect;
	szMsg[3] = pLocalParam->eDriveDistanceSelect;
	szMsg[4] = pLocalParam->eAvgSpeedSelect;
	szMsg[5] = pLocalParam->eDigitSpeedDisplay;
	szMsg[6] = pLocalParam->eCarSpeedWarningDisplay;
	szMsg[p0] = p1;
	extcarToHal_set_functionDisplay(szMsg, nLen);
}
void appToExtcar_golf_set_cozyEconomyTipDisplay(u8 p0,u8 p1)
{
	u8 r = 0;
	if (p0 == 1)
	{
		r |=( p1 << 1);
		r |= (pLocalParam->eCozyDeviceSelect << 2);
	}
	else if (p0 == 2)
	{
		r |= (pLocalParam->eEconomyDriveTip << 1);
		r |= (p1 << 2);
	}
	LOGD("dyb r = [%X], coze = [%X], eco = [%X]", r, pLocalParam->eCozyDeviceSelect, pLocalParam->eEconomyDriveTip);
	extcarToHal_set_cozyEconomyTipDisplay(r);
}
//»ÖžŽÊýŸÝ
void appToExtcar_golf_set_recoveryDriveDataFromStart(u8 p)
{
	extcarToHal_set_recoveryDriveDataFromStart(p);
}
void appToExtcar_golf_set_recoveryDriveDataFromLongTime(u8 p)
{
	extcarToHal_set_recoveryDriveDataFromLongTime(p);
}
//µ¥Î»ÉèÖÃ
void appToExtcar_golf_set_degreeUnit(u8 p)
{
	int n = 2;
	int t = pLocalParam->eDegreeUnit;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ( (t + n - 1) % n );
	pLocalParam->eDegreeUnit = (E_DEGREE_UNIT)t;
	extcarToHal_set_degreeUnit(t);
}
void appToExtcar_golf_set_volumeUnit(u8 p)
{
	int n = 3;
	int t = pLocalParam->eVolumeUnit;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ( (t + n - 1) % n );
	pLocalParam->eVolumeUnit = (E_VOLUME_UNIT)t;
	extcarToHal_set_volumeUnit(t);
}
void appToExtcar_golf_set_oilConsumeUnit(u8 p)
{
	int n = 4;
	int t = pLocalParam->eOilConsumeUnit;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ( (t + n - 1) % n );
	pLocalParam->eOilConsumeUnit = (E_OIL_CONSUME_UNIT)t;
	extcarToHal_set_oilConsumeUnit(t);
}
void appToExtcar_golf_set_distanceUnit(u8 p)
{
	int n = 2;
	int t = pLocalParam->eDistanceUnit;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ( (t + n - 1) % n );
	pLocalParam->eDistanceUnit = (E_DISTANCE_UNIT)t;
	extcarToHal_set_distanceUnit(t);
}
void appToExtcar_golf_set_speedUnit(u8 p)
{
	int n = 2;
	int t = pLocalParam->eSpeedUnit;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ( (t + n - 1) % n );
	pLocalParam->eSpeedUnit = (E_SPEED_UNIT)t;
	extcarToHal_set_speedUnit(t);
}

void appToExtcar_golf_set_tireCompressUnit(u8 p){}
//Ê±Œä
void appToExtcar_golf_set_systemTime(u8 p0, u8 p1){}
void appToExtcar_golf_set_systemDate(u8 p0, u8 p1, u8 p2){}
void appToExtcar_golf_set_SystemDateFormat(u8 p){}
//žŽÎ»³ö³§ÉèÖÃ
void appToExtcar_golf_set_recoverySetting(u8 p)
{
	pLocalParam->eRecoverySettingTypeSelected = (E_RECOVERY_SETTING_TYPE)p;
	int szMap[32] = {0};
	szMap[RECOVERY_SETTING_TYPE_ALL] = CARINFO_GOLD_SETUP_RESET_ALL;
	szMap[RECOVERY_SETTING_TYPE_STOP_AND_START_CAR] = CARINFO_GOLD_SETUP_RESET_PARKING_AND_DISPATCH;
	szMap[RECOVERY_SETTING_TYPE_LIGHT] = CARINFO_GOLD_SETUP_RESET_CAR_LIGHT;
	szMap[RECOVERY_SETTING_TYPE_BACK_MIRROR_AND_WIPER] = CARINFO_GOLD_SETUP_RESET_BACK_MIRROR_AND_WINDOWSHIELD_WIPER;
	szMap[RECOVERY_SETTING_TYPE_OPEN_AND_CLOSE] = CARINFO_GOLD_SETUP_RESET_ONOFF;
	szMap[RECOVERY_SETTING_TYPE_MUCH_FUNCTION_DISPLAY] = CARINFO_GOLD_SETUP_RESET_MULTIFUNCTION_DISPLAY;
	szMap[RECOVERY_SETTING_TYPE_DRIVER_ASSIST_SYSTEM] = CARINFO_GOLD_SETUP_RESET_DRIVER_AUXILIARY_SYSTEMS;
	szMap[RECOVERY_SETTING_DRIVE_DATA_FROM_START] = CARINFO_GOLD_SETUP_RESET_DRVING_DATA_FROM_START;
	szMap[RECOVERY_SETTING_DRIVE_DATA_FROM_LONG_TIME] = CARINFO_GOLD_SETUP_RESET_DRVING_DATA_FROM_LONGTIME;
	szMap[RECOVERY_SETTING_TYPE_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;

	bool bVisible = true;
	setUpdateUI(false);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_PROMPT_BOX, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_OK, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_CANCEL, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_TIP_TEXT, bVisible);
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_TIP_TEXT, szMap[p]);//ÐèÒª³Ì×Óºé
	setUpdateUI(true);
}
void appToExtcar_golf_set_recoverySettingYes()
{
	bool bVisible = false;
	setUpdateUI(false);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_PROMPT_BOX, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_OK, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_CANCEL, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_TIP_TEXT, bVisible);
	setUpdateUI(true);
	switch(pLocalParam->eRecoverySettingTypeSelected)
	{
	case RECOVERY_SETTING_DRIVE_DATA_FROM_START:
		extcarToHal_set_recoveryDriveDataFromStart(pLocalParam->eRecoverySettingTypeSelected);
		break;
	case RECOVERY_SETTING_DRIVE_DATA_FROM_LONG_TIME:
		extcarToHal_set_recoveryDriveDataFromLongTime(pLocalParam->eRecoverySettingTypeSelected);
		break;
	default:
		extcarToHal_set_recoverySetting(pLocalParam->eRecoverySettingTypeSelected);
		break;
	}

}
void appToExtcar_golf_set_recoverySettingNo()
{
	bool bVisible = false;
	setUpdateUI(false);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_PROMPT_BOX, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_OK, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_CANCEL, bVisible);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_TIP_TEXT, bVisible);
	setUpdateUI(true);
}
//ÓïÑÔ
void appToExtcar_golf_set_languageSetting(u8 p)
{
	extcarToHal_set_languageSetting(p);
}
//À×ŽïÉùÒô¿ª¹Ø
void appToExtcar_golf_set_radarAudioDoor(u8 p)
{
	extcarToHal_set_radarAudioDoor(p);
}
//¿Õµ÷
void appToExtcar_golf_set_airCtrl(u8 p)
{
	extcarToHal_set_airCtrl(p);
}

bool appToExtcar_golf_setDrivingMode_MouseUp(u32 ctrID)
{
	LOGD("[%s] ctrID:%x",__FUNCTION__,ctrID);
	bool bRet = true;
	switch(ctrID)
	{
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_COMFORT:
		{
			if(pLocalParam->eCar_DrivingMode != CAR_DRIVING_MODE_COMFORT){
				extcarToHal_set_DrivingMode((u8)CAR_DRIVING_MODE_COMFORT);
				SetTimer(TIME_MODE_GOTO_MODE_PAGE,1,EXTCAR_TIMER_ID_GOLF_MODE_HIDEBOX);
				pLocalParam->eCar_DrivingMode = CAR_DRIVING_MODE_COMFORT;
			}
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_STANDARD:
		{
			if(pLocalParam->eCar_DrivingMode != CAR_DRIVING_MODE_STANDARD){
				extcarToHal_set_DrivingMode((u8)CAR_DRIVING_MODE_STANDARD);
				SetTimer(TIME_MODE_GOTO_MODE_PAGE,1,EXTCAR_TIMER_ID_GOLF_MODE_HIDEBOX);
				pLocalParam->eCar_DrivingMode = CAR_DRIVING_MODE_STANDARD;
			}
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_SPORT:
		{
			if(pLocalParam->eCar_DrivingMode != CAR_DRIVING_MODE_SPORT){
				extcarToHal_set_DrivingMode((u8)CAR_DRIVING_MODE_SPORT);
				SetTimer(TIME_MODE_GOTO_MODE_PAGE,1,EXTCAR_TIMER_ID_GOLF_MODE_HIDEBOX);
				pLocalParam->eCar_DrivingMode = CAR_DRIVING_MODE_SPORT;
			}
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_LOW_OIL:
		{
			if(pLocalParam->eCar_DrivingMode != CAR_DRIVING_MODE_LOW_OIL){
				extcarToHal_set_DrivingMode((u8)CAR_DRIVING_MODE_LOW_OIL);
				SetTimer(TIME_MODE_GOTO_MODE_PAGE,1,EXTCAR_TIMER_ID_GOLF_MODE_HIDEBOX);
				pLocalParam->eCar_DrivingMode = CAR_DRIVING_MODE_LOW_OIL;
			}
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_PERSONALIZATION:
		{
			if(pLocalParam->eCar_DrivingMode != CAR_DRIVING_MODE_PERSONALIZATION){
				extcarToHal_set_DrivingMode((u8)CAR_DRIVING_MODE_PERSONALIZATION);
				SetTimer(TIME_MODE_GOTO_MODE_PAGE,1,EXTCAR_TIMER_ID_GOLF_MODE_HIDEBOX);
				pLocalParam->eCar_DrivingMode = CAR_DRIVING_MODE_PERSONALIZATION;
			}
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_ADJUST:
			extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_PERSONALIZATION_1);
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_BACK:
			extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_MENU:
			//extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_DRIVING_MOD);
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_NEXT_BUTTON:
			extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_PERSONALIZATION_2);
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_PREV_BUTTON:
			extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_PERSONALIZATION_1);
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_BACK:
			extcarToModule_NotifySystem_jumpPrePage();
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DAMPING_SYSTEM_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DAMPING_SYSTEM_DOWN:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_STEERING_WHEEL_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_STEERING_WHEEL_DOWN:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DRIVING_GEAR_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DRIVING_GEAR_DOWN:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DYNAMIC_HEADLIGHT_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DYNAMIC_HEADLIGHT_DOWN:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_AC_MOD_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_AC_MOD_DOWN:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_ENGINE_SOUNDS_MOD_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_ENGINE_SOUNDS_MOD_DOWN:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_MODE_RESET_ACTION_BUTTON:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_MODE_RESET_ACTION_SURE:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_MODE_RESET_ACTION_CHANCE:
			appToExtcar_golf_set_Personalization(ctrID);
		break;
		default:
			bRet = false;
			break;
	}

	return bRet;

}

void appToExtcar_golf_set_Personalization(u32 ctrID)
{
	if(pLocalParam->eCar_DrivingMode != CAR_DRIVING_MODE_PERSONALIZATION)
		return;
	
	switch(ctrID)
	{
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DAMPING_SYSTEM_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DAMPING_SYSTEM_DOWN:
		{
			appToExtcar_SetDampingSystem(ctrID - CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DAMPING_SYSTEM_UP);
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_STEERING_WHEEL_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_STEERING_WHEEL_DOWN:
		{
			appToExtcar_SetSteeringWheel(ctrID - CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_STEERING_WHEEL_UP);
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DRIVING_GEAR_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DRIVING_GEAR_DOWN:
		{
			appToExtcar_SetDrivingGear(ctrID - CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DRIVING_GEAR_UP);
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DYNAMIC_HEADLIGHT_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DYNAMIC_HEADLIGHT_DOWN:
		{
			appToExtcar_SetDynamicHeadlight(ctrID - CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DYNAMIC_HEADLIGHT_UP);
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_AC_MOD_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_AC_MOD_DOWN:
		{
			appToExtcar_SetAcMod(ctrID - CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_AC_MOD_UP);
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_ENGINE_SOUNDS_MOD_UP:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_ENGINE_SOUNDS_MOD_DOWN:
		{
			appToExtcar_SetEngineSoundsMod(ctrID - CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_ENGINE_SOUNDS_MOD_UP);
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_MODE_RESET_ACTION_BUTTON:
		{
			UI_Car_Golf_PersonalizationModeResetActionBox(true);
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_MODE_RESET_ACTION_SURE:
		case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_MODE_RESET_ACTION_CHANCE:
		{
			UI_Car_Golf_PersonalizationModeResetActionBox(false);
			appToExtcar_SetModeResetAction(ctrID - CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_MODE_RESET_ACTION_SURE);
		}
		break;
	}
}

void appToExtcar_SetDampingSystem(u8 param)
{
	int eTemp = (int)pLocalParam->eCar_DampingSystemMode;
	
	if((E_SELECT_CTRL)param == SELECT_CTRL_UP)
	{
		if(eTemp == (int)CAR_DAMPING_SYSTEM_SPORT)
			eTemp = (int)CAR_DAMPING_SYSTEM_COMFORT;
		else	
			eTemp++;
	}
	else if((E_SELECT_CTRL)param == (int)SELECT_CTRL_DOWN)
	{
		if(eTemp == (int)CAR_DAMPING_SYSTEM_COMFORT)
			eTemp = (int)CAR_DAMPING_SYSTEM_SPORT;
		else	
			eTemp--;
	}

	LOGD("pLocalParam->eCar_DampingSystemMode:%d",pLocalParam->eCar_DampingSystemMode);
	pLocalParam->eCar_DampingSystemMode = (E_CAR_DAMPING_SYSTEM_MOD)eTemp;

	//process_DampingSystemMode();
	extcarToHal_SetPersonalizationData();
}

void appToExtcar_SetSteeringWheel(u8 param)
{
	if(pLocalParam->eCar_SteeringWheelMode == CAR_STEERING_WHEEL_MOD_SPORT){
		pLocalParam->eCar_SteeringWheelMode = CAR_STEERING_WHEEL_MOD_STANDARD;
	}
	else if(pLocalParam->eCar_SteeringWheelMode == CAR_STEERING_WHEEL_MOD_STANDARD){
		pLocalParam->eCar_SteeringWheelMode = CAR_STEERING_WHEEL_MOD_SPORT;
	}
	//process_SteeringWheelMode();
	LOGD("pLocalParam->eCar_SteeringWheelMode:%d",pLocalParam->eCar_SteeringWheelMode);
	extcarToHal_SetPersonalizationData();
}

void appToExtcar_SetDrivingGear(u8 param)
{
	if((E_SELECT_CTRL)param == SELECT_CTRL_UP)
	{
		if(pLocalParam->eCar_DrivingGearMode == CAR_DRIVING_GEAR_MOD_STANDARD)
		{
			pLocalParam->eCar_DrivingGearMode = CAR_DRIVING_GEAR_MOD_SPORT;
		}
		else if(pLocalParam->eCar_DrivingGearMode == CAR_DRIVING_GEAR_MOD_SPORT)
		{
			pLocalParam->eCar_DrivingGearMode = CAR_DRIVING_GEAR_MOD_LOW_OIL;
		}
		else if(pLocalParam->eCar_DrivingGearMode == CAR_DRIVING_GEAR_MOD_LOW_OIL)
		{
			pLocalParam->eCar_DrivingGearMode = CAR_DRIVING_GEAR_MOD_STANDARD;
		}
	}
	else if((E_SELECT_CTRL)param == SELECT_CTRL_DOWN)
	{
		if(pLocalParam->eCar_DrivingGearMode == CAR_DRIVING_GEAR_MOD_STANDARD)
		{
			pLocalParam->eCar_DrivingGearMode = CAR_DRIVING_GEAR_MOD_LOW_OIL;
		}
		else if(pLocalParam->eCar_DrivingGearMode == CAR_DRIVING_GEAR_MOD_LOW_OIL)
		{
			pLocalParam->eCar_DrivingGearMode = CAR_DRIVING_GEAR_MOD_SPORT;
		}
		else if(pLocalParam->eCar_DrivingGearMode == CAR_DRIVING_GEAR_MOD_SPORT)
		{
			pLocalParam->eCar_DrivingGearMode = CAR_DRIVING_GEAR_MOD_STANDARD;
		}
	}
	//process_DrivingGearMode();
	LOGD("pLocalParam->eCar_DrivingGearMode:%d",pLocalParam->eCar_DrivingGearMode);
	extcarToHal_SetPersonalizationData();
}

void appToExtcar_SetDynamicHeadlight(u8 param)
{
	if((E_SELECT_CTRL)param == SELECT_CTRL_UP)
	{
		if(pLocalParam->eCar_Dynamic_Headlight_FollowerMode == CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_STANDARD)
		{
			pLocalParam->eCar_Dynamic_Headlight_FollowerMode = CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_SPORT;
		}
		else if(pLocalParam->eCar_Dynamic_Headlight_FollowerMode == CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_SPORT)
		{
			pLocalParam->eCar_Dynamic_Headlight_FollowerMode = CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_LOW_OIL;
		}
		else if(pLocalParam->eCar_Dynamic_Headlight_FollowerMode == CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_LOW_OIL)
		{
			pLocalParam->eCar_Dynamic_Headlight_FollowerMode = CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_STANDARD;
		}
	}
	else if((E_SELECT_CTRL)param == SELECT_CTRL_DOWN)
	{
		if(pLocalParam->eCar_Dynamic_Headlight_FollowerMode == CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_STANDARD)
		{
			pLocalParam->eCar_Dynamic_Headlight_FollowerMode = CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_LOW_OIL;
		}
		else if(pLocalParam->eCar_Dynamic_Headlight_FollowerMode == CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_LOW_OIL)
		{
			pLocalParam->eCar_Dynamic_Headlight_FollowerMode = CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_SPORT;
		}
		else if(pLocalParam->eCar_Dynamic_Headlight_FollowerMode == CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_SPORT)
		{
			pLocalParam->eCar_Dynamic_Headlight_FollowerMode = CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_STANDARD;
		}
	}
	LOGD("pLocalParam->eCar_Dynamic_Headlight_FollowerMode:%d",pLocalParam->eCar_Dynamic_Headlight_FollowerMode);

	//process_Dynamic_Headlight_FollowerMode();
	extcarToHal_SetPersonalizationData();
}

void appToExtcar_SetAcMod(u8 param)
{
	if(pLocalParam->eCar_AcMode == AC_MODE_STANDARD){
		pLocalParam->eCar_AcMode = AC_MODE_LOW_OIL;
	}
	else if(pLocalParam->eCar_AcMode == AC_MODE_LOW_OIL){
		pLocalParam->eCar_AcMode = AC_MODE_STANDARD;
	}
	LOGD("pLocalParam->eCar_AcMode:%d",pLocalParam->eCar_AcMode);
	//process_AcMode();
	extcarToHal_SetPersonalizationData();
}

void appToExtcar_SetEngineSoundsMod(u8 param)
{
	if((E_SELECT_CTRL)param == SELECT_CTRL_UP)
	{
		if(pLocalParam->eCar_InternalEngineSoundsMode == CAR_ENGINE_SOUNDS_MOD_STANDARD)
		{
			pLocalParam->eCar_InternalEngineSoundsMode = CAR_ENGINE_SOUNDS_MOD_SPORT;
		}
		else if(pLocalParam->eCar_InternalEngineSoundsMode == CAR_ENGINE_SOUNDS_MOD_SPORT)
		{
			pLocalParam->eCar_InternalEngineSoundsMode = CAR_ENGINE_SOUNDS_MOD_LOW_OIL;
		}
		else if(pLocalParam->eCar_InternalEngineSoundsMode == CAR_ENGINE_SOUNDS_MOD_LOW_OIL)
		{
			pLocalParam->eCar_InternalEngineSoundsMode = CAR_ENGINE_SOUNDS_MOD_STANDARD;
		}
	}
	else if((E_SELECT_CTRL)param == SELECT_CTRL_DOWN)
	{
		if(pLocalParam->eCar_InternalEngineSoundsMode == CAR_ENGINE_SOUNDS_MOD_STANDARD)
		{
			pLocalParam->eCar_InternalEngineSoundsMode = CAR_ENGINE_SOUNDS_MOD_LOW_OIL;
		}
		else if(pLocalParam->eCar_InternalEngineSoundsMode == CAR_ENGINE_SOUNDS_MOD_LOW_OIL)
		{
			pLocalParam->eCar_InternalEngineSoundsMode = CAR_ENGINE_SOUNDS_MOD_SPORT;
		}
		else if(pLocalParam->eCar_InternalEngineSoundsMode == CAR_ENGINE_SOUNDS_MOD_SPORT)
		{
			pLocalParam->eCar_InternalEngineSoundsMode = CAR_ENGINE_SOUNDS_MOD_STANDARD;
		}
	}
	//process_InternalEngineSoundsMode();
	LOGD("pLocalParam->eCar_InternalEngineSoundsMode:%d",pLocalParam->eCar_InternalEngineSoundsMode);

	extcarToHal_SetPersonalizationData();
}

void appToExtcar_SetModeResetAction(u8 param)
{
	if(param == 0)
	{
		pLocalParam->eCar_ModeResetAction = CAR_MODE_RESET_ACTION_YES;
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_DRIVING_MOD);
	}
	else if(param == 1)
	{
		pLocalParam->eCar_ModeResetAction = CAR_MODE_RESET_ACTION_NO;
	}

	LOGD("pLocalParam->eCar_ModeResetAction:%d",pLocalParam->eCar_ModeResetAction);

	extcarToHal_SetPersonalizationData();
}

void extcarToHal_SetPersonalizationData()
{
	LOGD("[%s] ",__FUNCTION__);
	extcarToHal_set_Personalization((u8)pLocalParam->eCar_DampingSystemMode,(u8)pLocalParam->eCar_SteeringWheelMode,(u8)pLocalParam->eCar_DrivingGearMode,(u8)pLocalParam->eCar_Dynamic_Headlight_FollowerMode,(u8)pLocalParam->eCar_AcMode,(u8)pLocalParam->eCar_InternalEngineSoundsMode,(u8)pLocalParam->eCar_ModeResetAction);
	pLocalParam->eCar_ModeResetAction = CAR_MODE_RESET_ACTION_NO;
}

void process_DampingSystemMode()
{
	int nMap[SIZE_MAP_ENUM] = {0};
	nMap[CAR_DRIVING_MODE_COMFORT] = STRING_CAR_DRTVING_MOD_COMFORT;
	nMap[CAR_DRIVING_MODE_STANDARD] = STRING_CAR_DRTVING_MOD_STANDARD;
	nMap[CAR_DRIVING_MODE_SPORT] = STRING_CAR_DRTVING_MOD_SPORT;
	if (pLocalParam->eCar_DampingSystemMode < SIZE_MAP_ENUM)
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DAMPING_SYSTEM_TXT, nMap[pLocalParam->eCar_DampingSystemMode]);
}
	
void process_SteeringWheelMode()
{
	int nMap[SIZE_MAP_ENUM] = {0};
	nMap[CAR_STEERING_WHEEL_MOD_STANDARD] = STRING_CAR_DRTVING_MOD_STANDARD;
	nMap[CAR_STEERING_WHEEL_MOD_SPORT] = STRING_CAR_DRTVING_MOD_SPORT;
	if (pLocalParam->eCar_SteeringWheelMode < SIZE_MAP_ENUM)
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_STEERING_WHEEL_TXT, nMap[pLocalParam->eCar_SteeringWheelMode]);
}
	
void process_DrivingGearMode()
{
	int nMap[SIZE_MAP_ENUM] = {0};
	nMap[CAR_DRIVING_GEAR_MOD_STANDARD] = STRING_CAR_DRTVING_MOD_STANDARD;
	nMap[CAR_DRIVING_GEAR_MOD_SPORT] = STRING_CAR_DRTVING_MOD_SPORT;
	nMap[CAR_DRIVING_GEAR_MOD_LOW_OIL] = STRING_CAR_DRTVING_MOD_LOW_OIL;
	if (pLocalParam->eCar_DrivingGearMode < SIZE_MAP_ENUM)
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DRIVING_GEAR_TXT, nMap[pLocalParam->eCar_DrivingGearMode]);
}
	
void process_Dynamic_Headlight_FollowerMode()
{
	int nMap[SIZE_MAP_ENUM] = {0};
	nMap[CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_STANDARD] = STRING_CAR_DRTVING_MOD_STANDARD;
	nMap[CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_SPORT] = STRING_CAR_DRTVING_MOD_SPORT;
	nMap[CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_LOW_OIL] = STRING_CAR_DRTVING_MOD_LOW_OIL;
	if (pLocalParam->eCar_Dynamic_Headlight_FollowerMode < SIZE_MAP_ENUM)
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_DYNAMIC_HEADLIGHT_TXT, nMap[pLocalParam->eCar_Dynamic_Headlight_FollowerMode]);
}
	
void process_AcMode()
{
	int nMap[SIZE_MAP_ENUM] = {0};
	nMap[AC_MODE_STANDARD] = STRING_CAR_DRTVING_MOD_STANDARD;
	nMap[AC_MODE_LOW_OIL] = STRING_CAR_DRTVING_MOD_LOW_OIL;
	if (pLocalParam->eCar_AcMode < SIZE_MAP_ENUM)
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_AC_MOD_TXT, nMap[pLocalParam->eCar_AcMode]);
}
	
void process_InternalEngineSoundsMode()
{
	int nMap[SIZE_MAP_ENUM] = {0};
	nMap[CAR_ENGINE_SOUNDS_MOD_STANDARD] = STRING_CAR_DRTVING_MOD_STANDARD;
	nMap[CAR_ENGINE_SOUNDS_MOD_SPORT] = STRING_CAR_DRTVING_MOD_SPORT;
	nMap[CAR_ENGINE_SOUNDS_MOD_LOW_OIL] = STRING_CAR_DRTVING_MOD_LOW_OIL;
	if (pLocalParam->eCar_InternalEngineSoundsMode < SIZE_MAP_ENUM)
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_ENGINE_SOUNDS_MOD_TXT, nMap[pLocalParam->eCar_InternalEngineSoundsMode]);
}
	
void UI_Car_Golf_PersonalizationModeResetActionBox(bool bShow)
{
	setUpdateUI(false);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_MODE_RESET_ACTION_BOX, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_MODE_RESET_ACTION_TXT, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_MODE_RESET_ACTION_SURE, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATION_MODE_RESET_ACTION_CHANCE, bShow);
	setUpdateUI(true);
}
	
bool appToExtcar_golf_setDrivingMode_MouseDown(u32 ctrID)
{
	return UI_DrivingModeDisplay(ctrID);
}

bool UI_DrivingModeDisplay(u32 ContrID)
{
	bool bRet = true;
	switch(ContrID)
	{
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_STANDARD:
		{
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_STANDARD,1);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_LOW_OIL,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_SPORT,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_COMFORT,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_PERSONALIZATION,0);

			setControllable(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_ADJUST, false);
			setAnalogData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_ADJUST,2);
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_LOW_OIL:
		{
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_STANDARD,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_LOW_OIL,1);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_SPORT,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_COMFORT,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_PERSONALIZATION,0);

			setControllable(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_ADJUST, false);
			setAnalogData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_ADJUST,2);
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_SPORT:
		{
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_STANDARD,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_LOW_OIL,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_SPORT,1);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_COMFORT,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_PERSONALIZATION,0);

			setControllable(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_ADJUST, false);
			setAnalogData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_ADJUST,2);
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_COMFORT:
		{
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_STANDARD,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_LOW_OIL,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_SPORT,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_COMFORT,1);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_PERSONALIZATION,0);

			setControllable(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_ADJUST, false);
			setAnalogData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_ADJUST,2);
		}
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_PERSONALIZATION:
		{
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_STANDARD,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_LOW_OIL,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_SPORT,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_COMFORT,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_PERSONALIZATION,1);

			setControllable(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_ADJUST, true);
			setAnalogData(CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_ADJUST,0);
		}
		break;
		default:
			bRet = false;
			break;
	}

	return bRet;
}

void appToExtcar_carola_set_oilConsumeUnit(u8 p)
{
	int n = 2;
	int t = pLocalParam->eOilConsumeUnit;
	t = (p == SELECT_CTRL_UP) ? ( (t + 1) % n ) : ( (t + n - 1) % n );
	pLocalParam->eOilConsumeUnit = (E_OIL_CONSUME_UNIT)t;
	extcarToHal_Carola_set_oilConsumeUnit(t);
}


bool appToExtcar_blue_skin_tables_MouseUp(u32 ctrID)
{
	bool bRet = true;
	switch(ctrID)
	{
		case CONTROLID_BLUE_SKIN_CARINFOR_TO_MAIN_PAGE_SETUP_BUTTON:
			extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION);
			break;
		case CONTROLID_BLUE_SKIN_CARINFOR_TO_SETUP_PAGE_SET_BUTTON:
			extcarToModule_NotifySystem_jumpPage(PAGE_BLUE_SKIN_CAR_SETUP);
			break;
		case CONTROLID_BLUE_SKIN_CARINFOR_TO_SETUP_PAGE_SET_BACK_BUTTON:
			extcarToModule_NotifySystem_jumpPage(PAGE_BLUE_SKIN_CAR_SETUP);
			break;
		case CONTROLID_BLUE_SKIN_CARINFOR_TO_DRIKINGDATA_PAGE_SET_BUTTON:
			extcarToModule_NotifySystem_jumpPage(PAGE_BLUE_SKIN_CAR_DRIVING_DATA);
			break;
		case CONTROLID_BLUE_SKIN_CARINFOR_TO_MAINTAIN_PAGE_SET_BUTTON:
			extcarToModule_NotifySystem_jumpPage(PAGE_BLUE_SKIN_CAR_MAINTAIN);
			break;
		case CONTROLID_BLUE_SKIN_CARINFOR_TO_HISTORY_RECORD_PAGE_SET_BUTTON:
			extcarToModule_NotifySystem_jumpPage(PAGE_BLUE_SKIN_CAR_TOYOTA_HISTORY_RECORD);
			break;
		case CONTROLID_BLUE_SKIN_CARINFOR_TO_HIGHLANDER_SETUP_PAGE_BACK_BUTTON:
			extcarToModule_NotifySystem_jumpPage(PAGE_BLUE_SKIN_CAR_HIGHLANDER_SETUP);
			break;
		case CONTROLID_BLUE_SKIN_CARINFOR_TO_HIGHLANDER_SETUP_PAGE_SET_BUTTON:
			extcarToModule_NotifySystem_jumpPage(PAGE_BLUE_SKIN_CAR_HIGHLANDER_SETUP);
			break;
		case CONTROLID_BLUE_SKIN_CARINFOR_TO_PARKINGPAGE_SET_BUTTON:
			extcarToModule_NotifySystem_jumpPage(PAGE_BLUE_SKIN_CAR_HIGHLANDER_PARKING);
			break;
		default:
			bRet = false;
		break;
	}
		
	return bRet;
}

void DispalyingUI_speed_limit_alarm_switch(u8 p)
{
	setDigitalData(CONTROLIDTRAVEL_SET_SPEED_LIMIT_ALARM_SWITCH,p);

	DispalyingUI_speed_limit_alarmSet(p);
}

void DispalyingUI_speed_limit_alarm_Value(u32 param)
{
	u8 ansiBuf[128];
	int nT = param;
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (nT < 0)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%dkm/h", nT);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_TXT, ansiBuf, nAnsiBufLen);
}

void DispalyingUI_speed_limit_alarmSet(u8 b)
{
	if(b == 0x01)
	{
		setControllable(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_TXT, 0x01);
		setAnalogData(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_TXT,1);

		setControllable(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_INC, 0x01);
		setAnalogData(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_INC,0);

		setControllable(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_DEC, 0x01);
		setAnalogData(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_DEC,0);
	}
	else
	{
		setControllable(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_TXT, 0x00);
		setAnalogData(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_TXT,2);

		setControllable(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_INC, 0x00);
		setAnalogData(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_INC,2);

		setControllable(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_DEC, 0x00);
		setAnalogData(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_DEC,2);
	}
}

void appToExtcar_set_speed_limit_alarm_switch()
{
	u8 uT = pLocalParam->uSpeedAlarmSwitch;
	if(uT == 0x00)
		uT = 0x01;
	else
		uT = 0x00;

	setPublicPositionSpeedAlarmSwitch(uT);
}

void appToExtcar_set_alarmSpeedValue(u8 p)
{
	if(pLocalParam->uSpeedAlarmSwitch == 0x01)
	{
		u16 uT = 0xFF;
		if(p == 0)//+
		{
			uT = 0x01;
		}
		else if(p == 1)//-
		{
			uT = 0x02;
		}

		setPublicPositionSetSpeedAlarmIncOrDec(uT);
	}
}

void DispalyingUI_trunk_opening_degree_Value(u8 param)
{
	u8 ansiBuf[128];
	u8 nT = param;
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (nT < 0)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%d%%", nT);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_TRUNK_OPENING_DEGREE_TXT, ansiBuf, nAnsiBufLen);
}

void appToExtcar_set_trunk_opening_degree(u8 p)////40%~100%
{
	u8 uT = 0xFF;
	if(p == 0)//+
	{
		uT = 0x01;
	}
	else if(p == 1)//-
	{
		uT = 0x02;
	}

	setPublicPositionTrunkOpeningDegreeIncAndDec(uT);
}


void DispalyingUI_welcome_lamp_switch(u8 p)
{
	setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_LAMP_SWITCH,p);
	
	DispalyingUI_welcome_lamp_open_Set(p);
}

void DispalyingUI_welcome_lamp_open_time(u16 param)
{
	switch(param)
	{
		case 0x001E:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_30S,1);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_60S,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_90S,0);
		break;
		case 0x003C:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_30S,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_60S,1);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_90S,0);
		break;
		case 0x005A:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_30S,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_60S,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_90S,1);
		break;
		default:
			return;
		break;
	}
}

void DispalyingUI_welcome_lamp_open_Set(u8 b)
{
	if(b == 0x01)
	{
		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_30S, 0x01);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_30S,0);

		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_60S, 0x01);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_60S,0);

		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_90S, 0x01);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_90S,0);
	}
	else
	{
		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_30S, 0x00);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_30S,2);

		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_60S, 0x00);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_60S,2);

		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_90S, 0x00);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_90S,2);
	}
}

void appToExtcar_set_welcome_lamp_switch()
{
	u8 uT = pLocalParam->uWelcomeLampSwitch;
	if(uT == 0x00)
		uT = 0x01;
	else
		uT = 0x00;
	
	setPublicPositionWelcomeLampSwitch(uT);
}

void appToExtcar_set_welcome_lamp_OpenTime(u8 p)
{
	if(pLocalParam->uWelcomeLampSwitch == 0x01)
	{
		u16 nT = 0;
		switch(p)
		{
			case 0x00://30s
				nT = 0x001E;
			break;
			case 0x01://60s
				nT = 0x003C;
			break;
			case 0x02://90s
				nT = 0x005A;
			break;
			default:
				return;
			break;
		}

		MakeWelcomeLampOpenTimeData(nT);
	}
}

void MakeWelcomeLampOpenTimeData(u16 p)
{
	u8 buff[8] = {0x00};
	buff[0] = (pLocalParam->uWelcomeLampOpenTimeMix & 0xFF);
	buff[1] = ((pLocalParam->uWelcomeLampOpenTimeMix >> 8) & 0xFF);

	buff[2] = (pLocalParam->uWelcomeLampOpenTimeMax & 0xFF);
	buff[3] = ((pLocalParam->uWelcomeLampOpenTimeMax >> 8) & 0xFF);

	buff[4] = (pLocalParam->uWelcomeLampOpenTimeStep & 0xFF);
	buff[5] = ((pLocalParam->uWelcomeLampOpenTimeStep >> 8) & 0xFF);
	
	buff[6] = (p & 0xFF);
	buff[7] = ((p >> 8) & 0xFF);

	setPublicPositionWelcomeLampTime(buff,sizeof(buff));
}

void DispalyingUI_company_home_lamp_switch(u8 p)
{
	setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_SWITCH,p);

	DispalyingUI_company_home_lamp_Set(p);
}

void DispalyingUI_company_home_lamp_open_time(u16 param)
{
	switch(param)
	{
		case 0x001E:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_30S,1);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_60S,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_90S,0);
		break;
		case 0x003C:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_30S,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_60S,1);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_90S,0);
		break;
		case 0x005A:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_30S,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_60S,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_90S,1);
		break;
		default:
			return;
		break;
	}
}

void DispalyingUI_company_home_lamp_Set(u8 b)
{
	if(b == 0x01)
	{
		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_30S, 0x01);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_30S,0);

		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_60S, 0x01);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_60S,0);

		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_90S, 0x01);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_90S,0);
	}
	else
	{
		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_30S, 0x00);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_30S,2);

		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_60S, 0x00);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_60S,2);

		setControllable(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_90S, 0x00);
		setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_90S,2);
	}
}

void appToExtcar_set_company_home_lamp_switch()
{
	u8 uT = pLocalParam->uCompanyLampHomeSwitch;
	if(uT == 0x00)
		uT = 0x01;
	else
		uT = 0x00;
	
	setPublicPositionLampCompanyHomeSwitch(uT);
}

void appToExtcar_set_company_home_lamp_OpenTime(u8 p)
{
	if(pLocalParam->uCompanyLampHomeSwitch == 0x01)
	{
		u16 nT = 0;
		switch(p)
		{
			case 0x00://30s
				nT = 0x001E;
			break;
			case 0x01://60s
				nT = 0x003C;
			break;
			case 0x02://90s
				nT = 0x005A;
			break;
			default:
				return;
			break;
		}

		MakeLampCompanyHomeTimeData(nT);
	}
}

void MakeLampCompanyHomeTimeData(u16 p)
{
	u8 buff[8] = {0x00};
	buff[0] = (pLocalParam->uLampCompanyHomeTimeMix & 0xFF);
	buff[1] = ((pLocalParam->uLampCompanyHomeTimeMix >> 8) & 0xFF);

	buff[2] = (pLocalParam->uLampCompanyHomeTimeMax & 0xFF);
	buff[3] = ((pLocalParam->uLampCompanyHomeTimeMax >> 8) & 0xFF);

	buff[4] = (pLocalParam->uLampCompanyHomeTimeStep & 0xFF);
	buff[5] = ((pLocalParam->uLampCompanyHomeTimeStep >> 8) & 0xFF);
	
	buff[6] = (p & 0xFF);
	buff[7] = ((p >> 8) & 0xFF);

	setPublicPositionLampCompanyHomeTime(buff,sizeof(buff));
}

void DispalyingUI_vehicle_mode(u16 param)
{
	switch(param)
	{
		case 0x01:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_VEHICLE_LIGHTS_WHISTLES,1);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_VEHICLE_ONLY_WHISTLES,0);
		break;
		case 0x02:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_VEHICLE_LIGHTS_WHISTLES,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_VEHICLE_ONLY_WHISTLES,1);
		break;
		default:
			return;
		break;
	}
}
void appToExtcar_set_vehicle_mode(u8 p)
{
	u8 uT = 0;

	switch(p)
	{
		case 0x00:
			uT = 0x01;
		break;
		case 0x01:
			uT = 0x02;
		break;
		default:
			return;
		break;
	}
	
	setPublicPositionVehicleFindingFeedback(uT);
}

void DispalyingUI_driving_automatic_latch_switch(u8 p)
{
	setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_DRIVING_AUTOMATIC_LATCH_SWITCH,p);
}

void DispalyingUI_driving_automatic_latch_speed_alarm_Value(u32 param)
{
	u8 ansiBuf[128];
	int nT = param;
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (nT < 0)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%dkm/h", nT);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	//setAnsiSerialData(CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_TXT, ansiBuf, nAnsiBufLen);
}

void appToExtcar_set_driving_automatic_latch_switch()
{	
	u8 uT = pLocalParam->uDrivingAutomaticLatchSwitch;
	if(uT == 0x00)
		uT = 0x01;
	else
		uT = 0x00;

	setPublicPositionDrivingAutomaticLatchSwitchAndDrivingSpeedSwitch(uT);
}

void appToExtcar_set_driving_automatic_latch_alarmSpeedValue(u8 p)//30~240KM/H
{
	if(pLocalParam->uDrivingAutomaticLatchSwitch == 0x01)
	{
		u8 uT = 0xFF;
		if(p == 0)//+
		{
			uT = 0x01;
		}
		else if(p == 1)//-
		{
			uT = 0x02;
		}
		setPublicPositionDrivingAutomaticLatchSwitchAndDrivingSpeedIncAndDec(uT);
	}
}

void DispalyingUI_flameout_automatic_latch_switch(u8 p)
{
	setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_FLAMEOUT_AUTOMATIC_LATCH_SWITCH,p);
}

void appToExtcar_set_flameout_automatic_latch_switch()
{	
	u8 uT = pLocalParam->uFlameoutAutomaticLatchSwitch;
	if(uT == 0x00)
		uT = 0x01;
	else
		uT = 0x00;

	setPublicPositionFlameoutAutomaticLatchSwitch(uT);
}

void DispalyingUI_key_unlock_door(u8 p)
{
	switch(p)
	{
		case 0x01:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEY_UNLOCK_ALL_DOOR,1);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEY_UNLOCK_MAIN_DRIVING,0);
			break;
		case 0x02:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEY_UNLOCK_ALL_DOOR,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEY_UNLOCK_MAIN_DRIVING,1);
			break;
		default:
			break;
	}
}

void appToExtcar_set_key_unlock_door(u8 p)
{	
	u8 uT = pLocalParam->uKeyUnlockDoor;
	if(p == 0)
		uT = 0x01;
	else if(p == 1)
		uT = 0x02;

	setPublicPositionKeyUnlockSet(uT);
}

void DispalyingUI_keyLess_unlock_door(u8 p)
{
	switch(p)
	{
		case 0x01:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEYLESS_UNLOCK_ALL_DOOR,1);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEYLESS_UNLOCK_MAIN_DRIVING,0);
			break;
		case 0x02:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEYLESS_UNLOCK_ALL_DOOR,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEYLESS_UNLOCK_MAIN_DRIVING,1);
			break;
		default:
			break;
	}
}

void appToExtcar_set_keyLess_unlock_door(u8 p)
{	
	u8 uT = pLocalParam->uKeyLessUnlockDoor;
	if(p == 0)
		uT = 0x01;
	else if(p == 1)
		uT = 0x02;

	setPublicPositionKeyLessUnlockSet(uT);
}

void DispalyingUI_AC_automatic_mode_flow(u16 param)
{
	switch(param)
	{
		case 0x01:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_HIGH,1);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_MID,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_LOW,0);
		break;
		case 0x02:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_HIGH,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_MID,1);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_LOW,0);
		break;
		case 0x03:
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_HIGH,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_MID,0);
			setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_LOW,1);
		break;
		default:
		break;
	}
}

void appToExtcar_set_AC_automatic_mode_flow(u8 p)
{
	u16 nT = 0;
	switch(p)
	{
		case 0x00://high
			nT = 0x01;
		break;
		case 0x01://midd
			nT = 0x02;
		break;
		case 0x02://low
			nT = 0x03;
		break;
		default:
			return;
		break;
	}

	setPublicPositionAcAutomaticFlowSet(nT);
}

void DispalyingUI_F_B_Defrost_Fog_Linkage_switch(u8 p)
{
	setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_F_B_DEFROST_FOG_LINKAGE_SWITCH,p);
}

void appToExtcar_set_F_B_Defrost_Fog_Linkage_switch()
{	
	u8 uT = pLocalParam->uFBdeforstFogLinkSwitch;
	if(uT == 0x00)
		uT = 0x01;
	else
		uT = 0x00;

	setPublicPosition_F_B_DefrostAndLog_LinkageSwitch(uT);
}

void DispalyingUI_Mirror_automatic_open_switch(u8 p)
{
	setDigitalData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_MIRROR_AUTOMATIC_OPEN_SWITHCH,p);
}

void appToExtcar_set_Mirror_automatic_open_switch()
{	
	u8 uT = pLocalParam->uMirrorAutomaticOpenSwitch;
	if(uT == 0x00)
		uT = 0x01;
	else
		uT = 0x00;

	setPublicPositionExteriorRearviewMirrorAutomaticOpenSwitch(uT);
}
void DispalyingUI_trunk_opening_degree_Value_Bar(u8 param , u8 p)
{
	LOGD("[%s]--- param:%x      p:%x",__FUNCTION__,param,p);
	u8 nT = param -p ;
	if(nT < 0)
		return;
	setAnalogData(CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_TRUNK_OPEN_LEVEL,nT);
}

void UI_ParkOutAssist(u8 s)
{
	setUpdateUI(0);
	switch(s)
	{
		case 0x0C:
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,4);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_OUT_ASSIST_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REMOVE_PLEASE_CONTROL_THE_STEERING_WHEEL);
	    }
		break;
	    case 0x17://Stop shift to forword
	    {
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_OUT_ASSIST_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE_SHIFT_TO_DRIVE_FORWORD);
	    }
		break;
		case 0x18://Pull forward slowly Be prepared to stop
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_OUT_ASSIST_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REMOVE_DRIVING_FORWORD_READY_STOP_VEHICLE);
		}
		break;
		case 0x19://Stop shift to reverse
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_OUT_ASSIST_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE_SHIFT_TO_REVERSE);
		}
		break;
		case 0x1A://Stop Back up slowly Be prepared to stop
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,2);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_OUT_ASSIST_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REVERSING_READY_STOP_VEHICLE);
		}
		break;
		case 0x1B:
		{
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,0);
			
			setAnalogData(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,0);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,STRINGID_PARK_SELECT_SIDE_PARKING_SPOT);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,0);
		}
		break;
		case 0x1C://
		{
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,2);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,STRINGID_PARK_REMOVE_HANDS);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,STRINGID_PARK_SHIFT_TO_REVERSE);
		}
		break;
		case 0x1D://
		{
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,1);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,STRINGID_PARK_REMOVE_HANDS);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,STRINGID_PARK_SHIFT_TO_REVERSE);
		}
		break;
		case 0x1E://right
		{
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,2);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,STRINGID_PARK_REMOVE_HANDS);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,STRINGID_PARK_SHIFT_TO_DRIVE_FORWORD);
		}
		break;
		case 0x1F://left
		{
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,1);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,STRINGID_PARK_REMOVE_HANDS);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,STRINGID_PARK_SHIFT_TO_DRIVE_FORWORD);
		}
		break;
		case 0xF0://right
		{
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,0);
			
			setAnalogData(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,2);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,STRINGID_PARK_RIGHT_SIDE);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,0);
		}
		break;
		case 0xF1://left
		{
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,0);
			
			setAnalogData(CONTROLID_PARK_OUT_ASSIST_PARK_CAR_BODY_ICON,1);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_FIRST,STRINGID_PARK_LEFT_SIDE);
			setStringText(CONTROLID_PARK_OUT_ASSIST_PARK_TXT_LINE_SECOND,0);
		}
		break;
	}
	setUpdateUI(1);
}

void UI_ParallelPark(u8 s)
{
	setUpdateUI(0);
	switch(s)
	{
		case 0x01://parking close
			break;
		case 0x0A:
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,4);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PARALLEL_PARK);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_FINISHED);


			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,0);//????
			//setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,5);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,0);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_FINISHED);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
	    }
		break;
		case 0x0F://Stop Shift to forword
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PARALLEL_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE_SHIFT_TO_DRIVE_FORWORD);

			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,0);//???
			//setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,5);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,0);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,1);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_STOP_VEHICLE);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,STRINGID_PARK_DRIVE_FORWORD);
		}
		break;
		case 0x10://Pull forward slowly Be prepared to stop
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);	
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PARALLEL_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REMOVE_DRIVING_FORWORD_READY_STOP_VEHICLE);

			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,0);//????
			//setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,5);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,0);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_REMOVE_DRIVING_FORWORD_READY_STOP_VEHICLE);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0x11://Stop Shift to reverse
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);	
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PARALLEL_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE_SHIFT_TO_REVERSE);


			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,0);//????
			//setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,5);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,0);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_STOP_VEHICLE_SHIFT_TO_REVERSE);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0x12://Back up slowly Be prepared to stop
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,2);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PARALLEL_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REVERSING_READY_STOP_VEHICLE);

			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,0);//????
			//setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,5);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,0);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_REVERSING_READY_STOP_VEHICLE);
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0x20://
		case 0x22://
		case 0x24://
		case 0x26://
		case 0x28://
		case 0x2A://
		case 0x2C://
		case 0x2E://
		{
			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,0);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,1);
			
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_RIGHT_SIDE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,STRINGID_PARK_SELECT_LEFT_SIDE_SCANING);
		}
		break;
		case 0x21:
		case 0x23://
		case 0x25://
		case 0x27://
		case 0x29://
		case 0x2B://
		case 0x2D://
		case 0x2F://
		{
			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,3);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,1);
	
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_LEFT_SIDE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,STRINGID_PARK_SELECT_RIGHT_SIDE_SCANING);
		}
		break;
		case 0x32://
		case 0x34://
		case 0x36://
		case 0x38://
		case 0x3A://
		case 0x3C://
		case 0x3E://
		{
			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,0);
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,1);
			setAnalogData(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,1);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,1);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0x33://
		case 0x35://
		case 0x37://
		case 0x39://
		case 0x3B://
		case 0x3D://
		case 0x3F://
		{
			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,3);	

			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,1);
			
			setAnalogData(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,1);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,1);

			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0x42://
		case 0x44://
		case 0x46://
		case 0x48://
		case 0x4A://
		case 0x4C://
		case 0x4E://
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PARALLEL_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE_REMOVE_HANDS);

			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,1);
			setAnalogData(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,1);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,1);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0x43://
		case 0x45://
		case 0x47://
		case 0x49://
		case 0x4B://
		case 0x4D://
		case 0x4F://
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PARALLEL_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE_REMOVE_HANDS);

			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,1);	
			
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,4);	
			setAnalogData(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,1);

			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);

		}
		break;
		case 0x52://
		case 0x54://
		case 0x56://
		case 0x58://
		case 0x5A://
		case 0x5C://
		case 0x5E://
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PARALLEL_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE_REMOVE_HANDS);

			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,1);
			setAnalogData(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,1);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_REMOVE_HANDS_SHIFT_TO_REVERSE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break; 
		case 0x53:// 
		case 0x55:// 
		case 0x57:// 
		case 0x59:// 
		case 0x5B:// 
		case 0x5D:// 
		case 0x5F://
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PARALLEL_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE_REMOVE_HANDS);

			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,1);	
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,1); 
			
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,4);	
			setAnalogData(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_REMOVE_HANDS_SHIFT_TO_REVERSE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);

		}
		break;
		case 0xE0:
		case 0xE1:
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,2);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PARALLEL_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REVERSING_READY_STOP_VEHICLE);
		}
		break;
		case 0xE4:
		{
			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);	
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,0);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_RIGHT_SIDE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0xE5:
		{
			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);		 
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,3);	

			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_LEFT_SIDE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0xE6:
		case 0xE8:
		{
			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);	
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,2);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,1);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0xE7:
		case 0xE9:
		{
			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);	
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,4);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,1);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0xF2:
		{
			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);	
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,0);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,1);

			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_RIGHT_SIDE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		case 0xF3:
		{
			setVisible(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,1);	
			setAnalogData(CONTROLID_PARALLEL_PARK_CAR_BODY_ICON,3);	
			
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_OBSTACLE_ICON,1);
			setVisible(CONTROLID_PARALLEL_PARK_LEFT_SIDE_ASSIT_ICON,0);
			
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PARALLEL_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_RIGHT_SIDE);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PARALLEL_PARK_TXT_LINE_THIRD,0);
		}
		break;
	}
	setUpdateUI(1);
}

void UI_PerpendicularPark(u8 s)
{
	setUpdateUI(0);
	switch(s)
	{
		case 0x0B:
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,4);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PERPENDICULAR_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_FINISHED);
		}
		break;
		case 0x13://Stop Shift to forword
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PERPENDICULAR_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE_SHIFT_TO_DRIVE_FORWORD);

	 		setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,5);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);

			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);

			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,1);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_STOP_VEHICLE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,0);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,STRINGID_PARK_DRIVE_FORWORD);
		}
		break;
		case 0x14://Pull forward slowly Be prepared to stop
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PERPENDICULAR_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REMOVE_DRIVING_FORWORD_READY_STOP_VEHICLE);
		}
		break;
		case 0x15://Stop Shift to reverse
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PERPENDICULAR_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE_SHIFT_TO_REVERSE);
		}
		break;
		case 0x16://Back up slowly Be prepared to stop
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,2);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PERPENDICULAR_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REVERSING_READY_STOP_VEHICLE);
		}
		break;
		case 0x60:////// 
		case 0x62:////// 
		case 0x64:////// 
		case 0x66:////// 
		case 0x68:////// 
		case 0x6A:////// 
		case 0x6C:////// 
		case 0x6E:////// 
		case 0x70:////// 
		case 0x72:///// 
		case 0x74:///// 
		case 0x76:///// 
		case 0x78:///// 
		case 0x7A:///// 
		case 0x7C: 
		case 0x7E: 
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,0);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,1);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_RIGHT_SIDE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,STRINGID_PARK_SELECT_LEFT_SIDE_SCANING);
		}
		break; 
		case 0x61: 
		case 0x63: 
		case 0x65: 
		case 0x67: 
		case 0x69: 
		case 0x6B: 
		case 0x6D: 
		case 0x6F: 
		case 0x71: 
		case 0x73: 
		case 0x75: 
		case 0x77: 
		case 0x79: 
		case 0x7B: 
		case 0x7D: 
		case 0x7F:
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,3);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,1);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_LEFT_SIDE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,STRINGID_PARK_SELECT_RIGHT_SIDE_SCANING);
		}
		break;
		case 0x82: 
		case 0x86: 
		case 0x88: 
		case 0x8A: 
		case 0x8C: 
		case 0x8E:
		case 0x92: 
		case 0x94: 
		case 0x96: 
		case 0x9A: 
		case 0x9C: 
		case 0x9E: 
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,0);	
			
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,1);

			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
		}
		break; 
		case 0x83: 
		case 0x87: 
		case 0x89: 
		case 0x8B: 
		case 0x8D: 
		case 0x8F:  
		case 0x93: 
		case 0x95:
		case 0x97:  
		case 0x9B: 
		case 0x9D: 
		case 0x9F: 
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);
			
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,3);	

			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,1);

			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0xA2: 
		case 0xA4: 
		case 0xA6: 
		case 0xA8: 
		case 0xAA: 
		case 0xAC: 
		case 0xB0:   
		case 0xB2: 
		case 0xB4: 
		case 0xB6: 
		case 0xB8: 
		case 0xBA: 
		case 0xBC: 
		case 0xBE: 
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,1);			

			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);

			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PERPENDICULAR_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REMOVE_HANDS_SHIFT_TO_REVERSE);
		
		}
		break; 
		case 0xA3: 
		case 0xA5: 
		case 0xA7: 
		case 0xA9: 
		case 0xAB: 
		case 0xAD: 
		case 0xB1:  
		case 0xB3: 
		case 0xB5: 
		case 0xB7: 
		case 0xB9: 
		case 0xBB: 
		case 0xBD:  
		case 0xBF:
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,4);
			
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,1);

			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);  
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);

			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PERPENDICULAR_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REMOVE_HANDS_SHIFT_TO_REVERSE);
		

		}
		break;
		case 0xC2:
		case 0xC4:
		case 0xC6:
		case 0xC8:
		case 0xCA:
		case 0xCC:
	   	case 0xD0: 
		case 0xD2: 
		case 0xD4:
		case 0xD6:
		case 0xD8:
		case 0xDA:
		case 0xDC: 
		case 0xDE:
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,1);

			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,1);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,STRINGID_PARK_REMOVE_HANDS_SHIFT_TO_REVERSE);


			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PERPENDICULAR_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REMOVE_HANDS_SHIFT_TO_REVERSE);

		}
		break;
		case 0xC3: 
		case 0xC5: 
		case 0xC7: 
		case 0xC9: 
		case 0xCB: 
		case 0xCD:
		case 0xD1: 
		case 0xD3: 
		case 0xD5: 
		case 0xD7: 
		case 0xD9: 
		case 0xDB: 
		case 0xDD:  
		case 0xDF: 
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,1);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,3);	
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,1);

			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,1);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,STRINGID_PARK_REMOVE_HANDS_SHIFT_TO_REVERSE);


			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,3);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PERPENDICULAR_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REMOVE_HANDS_SHIFT_TO_REVERSE);
		}
		break; 
		case 0xE2:
		case 0xE3:
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,2);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_PERPENDICULAR_PARK);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REVERSING_READY_STOP_VEHICLE);
		}
		break;
		case 0xEA:
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);	
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,0);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_RIGHT_SIDE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0xEB:
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);		 
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,3);	

			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);


			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_LEFT_SIDE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0xEC:
		case 0xEE:
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);	
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);
			
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);

			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0xED:
		case 0xEF:
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);	
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,4); 
			
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);
		
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SPOT_FOUND);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_STOP_VEHICLE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
		}
		break;
		case 0xF4:
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);	
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,0);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);
			
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,1);

			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_RIGHT_SIDE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
		}
		case 0xF5:
		{
			setVisible(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,1);	
			setAnalogData(CONTROLID_PERPENDICULAR_PARK_CAR_BODY_ICON,3); 
			
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_OBSTACLE_ICON,1);
			setVisible(CONTROLID_PERPENDICULAR_PARK_LEFT_SIDE_ASSIT_ICON,0);
			
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_ASSIT_ICON,0);
			setVisible(CONTROLID_PERPENDICULAR_PARK_RIGHT_SIDE_OBSTACLE_ICON,0);
		
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,1);	
			setVisible(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_FIRST,STRINGID_PARK_SCANING_PARKING_SPOT_RIGHT_SIDE);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_SECOND,STRINGID_PARK_DRIVE_FORWORD);
			setStringText(CONTROLID_PERPENDICULAR_PARK_TXT_LINE_THIRD,0);
		}
		break;
	}
	setUpdateUI(1);
}

void UI_ActiveParkAssit(u8 s)
{
	setUpdateUI(0);
	switch(s)//Active Park assist
	{
		case 0x01://please check surroundings for safety
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,0);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,0);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,0);
		}
		break;
		case 0x05://Cancelled by driver(Finish_Chime)
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,4);

			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,0);

			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_FINISHED);
		}
		break;
		case 0x06://Fault refer to owner guide(Warning_Chime)
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,0);

			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_ACTIVE_PARK_VIDEO);

			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_REMOVE_PLEASE_GET_OUT_OF_THR_REVERSE_GEAR);
		}
		break;
		case 0x07://Cancelled by driver(Finish_Chime)
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,4);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,0);
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,1);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,STRINGID_PARK_FINISHED);
		}
		break;
		case 0x08://Press Button Remove hands to resume parking
		break;
		case 0x09://Not available refer to owner guide(Warning_Chime)
		break;
		case 0x0e://(Warning_Chime)
		{
			setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,1);
			setAnalogData(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,0);

			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,1);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,STRINGID_PARK_ACTIVE_PARK_VIDEO);

			setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,0);
			setStringText(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,0);
		
		}
		break;
	}
	setUpdateUI(1);
}
