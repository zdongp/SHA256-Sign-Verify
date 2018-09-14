#pragma once

#include "CarInfo.h"
#include "CarSettingToyotaDefine.h"

class CCarInfoCarSettingToyota
{
public:
	CCarInfoCarSettingToyota(void);
    ~CCarInfoCarSettingToyota(void);

public:
	void initCarSettings_SetDefaultParam(void);
	void initCarInfo_CarSettingsByConfig(void);
	void analyseCarInfo_CarSettings(u8 *p, int len);
	bool pages(u32 id, u8 ms, u8 *p, u8 len);
	void setPage(u16 id);
public:
	bool carInforMainPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool carPersonalization_Page(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool carAfterSettingtheCameraGuideLine_Page(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);

	bool carPersonalization_DoorLockSettings_Page(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool carPersonalization_ClimateSettings_Page(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool carPersonalization_LightsSettings_Page(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
public:
	void clickButtonCarSettings_Personalization(E_MOUSE_STATUS e);
	void clickButtonCarSettings_AfterSettingTheCameraGuideLine(E_MOUSE_STATUS e);
	void clickButtonCarPersonalization_DoorLockSettings(E_MOUSE_STATUS e);
	void clickButtonCarPersonalization_ClimateSettings(E_MOUSE_STATUS e);
	void clickButtonCarPersonalization_LightsSettings(E_MOUSE_STATUS e);

	void clickButtonJumpToPersonalizationPage_Back(E_MOUSE_STATUS e);
	void clickButtonJumpToCarInformationgMainPage_Back(E_MOUSE_STATUS e);
public:
	void clickButtonSpeedAutoLockSwitch(u8 p);
	void clickButtonOut_P_blockAutoLockSwitch(u8 p); 
	void clickButtonIn_P_blockAutoLockSwitch(u8 p); 
	void clickButtonDriverDoorAutoUnLockSwitch(u8 p);
	void clickButtonTelecontrol2StepsAutoUnLockSwitch(u8 p);
	void clickButtonLockStatePilotlampSwitch(u8 p);
	void clickButtonDoorUnlockUpOrDown(u8 param,E_MOUSE_STATUS e);
	void clickButtonElectronicToSystemKeySwitch(u8 p);
	void clickButtonDisabingSmartKeyOkOrChance(u8 param,E_MOUSE_STATUS e);

	void clickButtonAutoAcModeSwitch(u8 p);
	void clickButtonEffectiveventilatModeSwitch(u8 p);


	void clickButtonHeadLightOpenSentivityUpOrDown(u8 param,E_MOUSE_STATUS e);
	void clickButtonInteriorLightTimerUpOrDown(u8 param,E_MOUSE_STATUS e);

	void clickButtonAfterSetTheCameraGuideLine(u8 param,E_MOUSE_STATUS e);
	

public:
	void saveCarSettings_BombBox(bool bShow);
	void disabingSmartKey_BombBox(bool bShow);
	void SetsaveCarSetInforsParamTimer();
	void DeletesaveCarSetInforsParamTimer();
	void setDigitalSpeedAutoLock(void);
	void setDigitalOut_P_blockAutoLock(void);
	void setDigitalIn_P_blockAutoLock(void);
	void setDigitalDriverDoorAutoUnLock(void);
	void setDigitalTelecontrolButton2StepsAutoUnLock(void);
	void setDigitalLockStatePilotlamp(void);
	void setDigitalDoorUnlockStringID(void);
	void setDigitalElectronicToSystemKey(void);
	void setDigitalAutoAcMode(void);
	void setDigitalEffectiveventilatMode(void);
	void setDigitalHeadLightOpenSentivityStringID(void);
	void setDigitalInteriorLightTimerStringID(void);
	void setDigitalAfterSetTheCameraGuideLine(void);
	void setDigitalDangerWarningLampState();
	void setDigitalDrivingRemoteDippedLampState(u8 s);
	void setDigitalBrakeTailLampState();
	void setDigitalCorneringLampState();
	void setDigitalGearsState();
	void setDigitalEngineState();
	void setDigitalOilConsumptionAlarmState();
	
	void DisplayingUI_Cornering_LampState(E_CAR_CORNERING_LAMP_STATE em);
	void Cornering_Lamp_TK();
	void DisplayingUI_DangerWarningLampState(E_CAR_DANGER_WARNING_LAMP_STATE em);
	void DangerWarning_Lamp_TK();
	void noticAppBombOilConsumptionAlarm();

public:
	void setToHalSpeedAutoLock(u8 param);
	void setToHalOutPblockAutoLock(u8 param);
	void setToHalInPblockAutoLock(u8 param);
	void setToHalDriverDoorAutoUnLock(u8 param);
	void setToHalclickTelecontrolButton2StepsAutoUnLock(u8 param);
	void setToHalLockStatePilotlamp(u8 param);
	void setToHalSwitchOneDoorUnLock(u8 param);
	void setToHalElectronicGoToSystemKey(u8 param);

	void setToHalAutoAcMode(u8 param);
	void setToHalEffectiveVentilatMode(u8 param);

	void setToHalHeadLight_OpenSensitivity(u8 param);
	void setToHalInteriorLightsTimer(u8 param);

	void setToHalAfterSettingtheCameraGuideLine(u8 param);
public:
		E_CARSET_SPEED_AUTOLOCK_STATE m_enCarSet_SpeedAutoLockState;
		E_CARSET_HEADLIGHT_SENTIVITY m_enCarSet_HeadLightSentivity;
		E_CARSET_INTERTIORLIGHT_TIMER m_enCarSet_IntertiorLightTimer;
		E_CARSET_DOOR_UNLOCK_SWITCH m_enCarSet_SwitchDoorUnlockSwitch;
		E_CARSET_ELECTRONICTOSYSKEY_STATE m_enCarSet_ElectronicToSysKeyState;
		E_CARSET_LOCKSTATE_PILOTLAMP_STATE m_enCarSet_PilotlampState;
		E_CARSET_OUT_P_AUTOLOCK_STATE m_enCarSet_OutPAutoLockState;
		E_CARSET_IN_P_AUTOLOCK_STATE m_enCarSet_InPAutoLockState;
		E_CARSET_DRIVERDOOR_AUTOUNLOCK_STATE m_enCarSet_DriverDoorAutoUnlockState;
		E_CARSET_BACKCAR_GUIDELINESET m_enCarSet_BackCarGuideLineSet;
		E_CARSET_TELECONTROL_2SEP_AUTOUNLOCK_STATE m_enCarSet_Telecontrol2StepState;
		E_CARSET_AUTO_ACMODE_STATE m_enCarSet_AutoAcModeState;
		E_CARSET_EFFECTIVE_VENTILATMODE_STATE m_enCarSet_VentilatModeState;
		E_CAR_DANGER_WARNING_LAMP_STATE m_enCarDangerWarningLampState;
		E_CAR_DRIVING_REMOTE_DIPPED_LAMP_STATE m_enCarDrivingRemoteDippedLampState;
		E_CAR_BRAKE_TAIL_LAMP_STATE m_enCarBrakeTailLampState;
		E_CAR_CORNERING_LAMP_STATE m_enCarCorneringLampState;
		E_CAR_GEARS_STATE m_enCarGearsState;
		E_CAR_ENGINE_STATE m_enCar_EngineState;
		E_CAR_OIL_CONSUMPTION_ALARM_STATE m_enCar_OilConsumptionAlarmState;

};

