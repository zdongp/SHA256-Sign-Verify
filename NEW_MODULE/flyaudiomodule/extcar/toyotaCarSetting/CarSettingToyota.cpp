
#include "CarSettingToyota.h"

#include "stringID.h"
#include "pageID.h"
#include "controlID.h"
#include "param.h"

#include <flymoduleApi_internal.h>
#include "timer_interface.h"
#include "appRequestCommand.h"

#include "otherModuleRequestCommand.h"
extern moduleid_t locale_module_mid(void);

static E_CAR_CORNERING_LAMP_STATE s = CORNERING_LAMP_UNKNOW;
static E_CAR_DANGER_WARNING_LAMP_STATE d = DANGER_WARNING_LAMP_UNKNOW;

CCarInfoCarSettingToyota::CCarInfoCarSettingToyota(void)
{
}

CCarInfoCarSettingToyota::~CCarInfoCarSettingToyota(void)
{
}

void CCarInfoCarSettingToyota::initCarSettings_SetDefaultParam(void)
{
	m_enCarSet_SpeedAutoLockState = SPEED_UNKNOW;
	m_enCarSet_HeadLightSentivity = SENTIVITY_UNKNOW;
	m_enCarSet_IntertiorLightTimer = TIME_UNKNOW;
	m_enCarSet_SwitchDoorUnlockSwitch = DOOR_UNLOCK_UNKNOW;
	m_enCarSet_ElectronicToSysKeyState = ELECTRONICTOSYSKEY_UNKNOW;
	m_enCarSet_PilotlampState = PILOTLAMP_UNKNOW;
	m_enCarSet_OutPAutoLockState = OUT_P_UNKNOW;
	m_enCarSet_InPAutoLockState = IN_P_UNKNOW;
	m_enCarSet_DriverDoorAutoUnlockState = DRIVERDOOR_AUTOUNLOCK_UNKNOW;
	m_enCarSet_BackCarGuideLineSet = GUIDELINESET_UNKNOW;
	m_enCarSet_Telecontrol2StepState = TELECONTROL_2SEP_UNKNOW;
	m_enCarSet_AutoAcModeState = ACMODE_UNKNOW;
	m_enCarSet_VentilatModeState = VENTILATMODE_UNKNOW;
	m_enCarDangerWarningLampState = DANGER_WARNING_LAMP_UNKNOW;
	m_enCarDrivingRemoteDippedLampState = DRIVING_REMOTE_DIPPED_LAMP_UNKNOW;
	m_enCarBrakeTailLampState = BRAKE_TAIL_LAMP_UNKNOW;
	m_enCarCorneringLampState = CORNERING_LAMP_UNKNOW;
	m_enCarGearsState = GEARS_UNKNOW;
	m_enCar_EngineState = ENGINE_UNKNOW;
	m_enCar_OilConsumptionAlarmState = OIL_STATE_UNKNOW;
}

void CCarInfoCarSettingToyota::initCarInfo_CarSettingsByConfig(void)
{	
	LOGD("[%s] m_enCarSet_SpeedAutoLockState:%x",CAMRY,m_enCarSet_SpeedAutoLockState);
	LOGD("[%s] m_enCarSet_HeadLightSentivity:%x",CAMRY,m_enCarSet_HeadLightSentivity);
	LOGD("[%s] m_enCarSet_IntertiorLightTimer:%x",CAMRY,m_enCarSet_IntertiorLightTimer);
	LOGD("[%s] m_enCarSet_SwitchDoorUnlockSwitch:%x",CAMRY,m_enCarSet_SwitchDoorUnlockSwitch);
	LOGD("[%s] m_enCarSet_ElectronicToSysKeyState:%x",CAMRY,m_enCarSet_ElectronicToSysKeyState);
	LOGD("[%s] m_enCarSet_PilotlampState:%x",CAMRY,m_enCarSet_PilotlampState);
	LOGD("[%s] m_enCarSet_OutPAutoLockState:%x",CAMRY,m_enCarSet_OutPAutoLockState);
	LOGD("[%s] m_enCarSet_InPAutoLockState:%x",CAMRY,m_enCarSet_InPAutoLockState);
	LOGD("[%s] m_enCarSet_DriverDoorAutoUnlockState:%x",CAMRY,m_enCarSet_DriverDoorAutoUnlockState);
	LOGD("[%s] m_enCarSet_BackCarGuideLineSet:%x",CAMRY,m_enCarSet_BackCarGuideLineSet);
	LOGD("[%s] m_enCarSet_Telecontrol2StepState:%x",CAMRY,m_enCarSet_Telecontrol2StepState);
	LOGD("[%s] m_enCarSet_AutoAcModeState:%x",CAMRY,m_enCarSet_AutoAcModeState);
	LOGD("[%s] m_enCarSet_VentilatModeState:%x",CAMRY,m_enCarSet_VentilatModeState);

	if(m_enCarSet_SpeedAutoLockState == SPEED_UNKNOW){
		m_enCarSet_SpeedAutoLockState = SPEED_OFF;
	}
	setToHalSpeedAutoLock((u8)m_enCarSet_SpeedAutoLockState);

	if(m_enCarSet_HeadLightSentivity == SENTIVITY_UNKNOW){
		m_enCarSet_HeadLightSentivity = SENTIVITY_MODERATE;
	}
	setToHalHeadLight_OpenSensitivity((u8)m_enCarSet_HeadLightSentivity);

	if(m_enCarSet_IntertiorLightTimer == TIME_UNKNOW){
		m_enCarSet_IntertiorLightTimer = TIME_7_5;
	}
	setToHalInteriorLightsTimer((u8)m_enCarSet_IntertiorLightTimer);

	if(m_enCarSet_SwitchDoorUnlockSwitch == DOOR_UNLOCK_UNKNOW){
		m_enCarSet_SwitchDoorUnlockSwitch = DOOR_UNLOCK_ALL;
		}
	setToHalSwitchOneDoorUnLock((u8)m_enCarSet_SwitchDoorUnlockSwitch);

	if(m_enCarSet_ElectronicToSysKeyState == ELECTRONICTOSYSKEY_UNKNOW){
		m_enCarSet_ElectronicToSysKeyState = ELECTRONICTOSYSKEY_ON;
		}
	setToHalElectronicGoToSystemKey((u8)m_enCarSet_ElectronicToSysKeyState);

	if(m_enCarSet_PilotlampState == PILOTLAMP_UNKNOW){
		m_enCarSet_PilotlampState = PILOTLAMP_ON;
		}
	setToHalLockStatePilotlamp((u8)m_enCarSet_PilotlampState);

	if(m_enCarSet_OutPAutoLockState == OUT_P_UNKNOW){
		m_enCarSet_OutPAutoLockState = OUT_P_OFF;
		}
	setToHalOutPblockAutoLock((u8)m_enCarSet_OutPAutoLockState);

	if(m_enCarSet_InPAutoLockState == IN_P_UNKNOW){
		m_enCarSet_InPAutoLockState = IN_P_OFF;
		}
	setToHalInPblockAutoLock((u8)m_enCarSet_InPAutoLockState);

	if(m_enCarSet_DriverDoorAutoUnlockState == DRIVERDOOR_AUTOUNLOCK_UNKNOW){
		m_enCarSet_DriverDoorAutoUnlockState = DRIVERDOOR_AUTOUNLOCK_OFF;
		}
	setToHalDriverDoorAutoUnLock((u8)m_enCarSet_DriverDoorAutoUnlockState);

	if(m_enCarSet_BackCarGuideLineSet == GUIDELINESET_UNKNOW){
		m_enCarSet_BackCarGuideLineSet = GUIDELINESET_1;
	}
	setToHalAfterSettingtheCameraGuideLine((u8)m_enCarSet_BackCarGuideLineSet);

	if(m_enCarSet_Telecontrol2StepState == TELECONTROL_2SEP_UNKNOW){
		m_enCarSet_Telecontrol2StepState = TELECONTROL_2SEP_OFF;
	}
	setToHalclickTelecontrolButton2StepsAutoUnLock((u8)m_enCarSet_Telecontrol2StepState);

	if(m_enCarSet_AutoAcModeState == ACMODE_UNKNOW){
		m_enCarSet_AutoAcModeState = ACMODE_ON;
	}
	setToHalAutoAcMode((u8)m_enCarSet_AutoAcModeState);

	if(m_enCarSet_VentilatModeState == VENTILATMODE_UNKNOW){
		m_enCarSet_VentilatModeState = VENTILATMODE_ON;
	}
	setToHalEffectiveVentilatMode((u8)m_enCarSet_VentilatModeState);
}

void CCarInfoCarSettingToyota::analyseCarInfo_CarSettings(u8 *p, int len)
{
	if(p[0] == 0x60 || p[0] == 0x65 || p[0] == 0xb1  || p[0] == 0xb2 || 
		p[0] == 0xb3 || p[0] == 0xb4 || p[0] == 0xb5 || p[0] == 0xb6 || 
		p[0] == 0xb7 || p[0] == 0xb8 || p[0] == 0xb9 || p[0] == 0xba || p[0] == 0xbb ||
		p[0] == 0xc0 || p[0] == 0xc1 || p[0] == 0xc2 || p[0] == 0xc3 || p[0] == 0xc4 ||
		p[0] == 0xc5 || p[0] == 0xc6 || p[0] == 0xc7)
	{
		LOGD("[%s] p[0]:%x,p[1]:%x",CAMRY,p[0],p[1]);
	}
	
	switch(p[0])
	{
		case 0x60://车速自动锁止
				m_enCarSet_SpeedAutoLockState = (E_CARSET_SPEED_AUTOLOCK_STATE)p[1];
				setDigitalSpeedAutoLock();
			break;
		case 0x65://车灯调节灵敏度
				m_enCarSet_HeadLightSentivity = (E_CARSET_HEADLIGHT_SENTIVITY)p[1];
				setDigitalHeadLightOpenSentivityStringID();
			break;

		case 0xb1://车内照明灯熄灭定时器
				m_enCarSet_IntertiorLightTimer = (E_CARSET_INTERTIORLIGHT_TIMER)p[1];
				setDigitalInteriorLightTimerStringID();
			break;
		case 0xb2://选择车门进行解锁
				m_enCarSet_SwitchDoorUnlockSwitch = (E_CARSET_DOOR_UNLOCK_SWITCH)p[1];
				setDigitalDoorUnlockStringID();
			break;
		case 0xb3://带电子钥匙的进入系统钥匙
				m_enCarSet_ElectronicToSysKeyState = (E_CARSET_ELECTRONICTOSYSKEY_STATE)p[1];
				setDigitalElectronicToSystemKey();
			break;
		case 0xb4://锁止/解锁反馈指示灯
				m_enCarSet_PilotlampState = (E_CARSET_LOCKSTATE_PILOTLAMP_STATE)p[1];
				setDigitalLockStatePilotlamp();
			break;
		case 0xb5://换出P挡自动锁止
				m_enCarSet_OutPAutoLockState = (E_CARSET_OUT_P_AUTOLOCK_STATE)p[1];
				setDigitalOut_P_blockAutoLock();
			break;
		case 0xb6://换入P挡自动锁止
				m_enCarSet_InPAutoLockState = (E_CARSET_IN_P_AUTOLOCK_STATE)p[1];
				setDigitalIn_P_blockAutoLock();
			break;
		case 0xb7://通过驾驶员车门自动解锁
				m_enCarSet_DriverDoorAutoUnlockState = (E_CARSET_DRIVERDOOR_AUTOUNLOCK_STATE)p[1];
				setDigitalDriverDoorAutoUnLock();
			break;
		case 0xb8://倒车引导线设置(三种模式)
				m_enCarSet_BackCarGuideLineSet = (E_CARSET_BACKCAR_GUIDELINESET)p[1];
				setDigitalAfterSetTheCameraGuideLine();
			break;
		case 0xb9://遥控按钮两步解锁
				m_enCarSet_Telecontrol2StepState = (E_CARSET_TELECONTROL_2SEP_AUTOUNLOCK_STATE)p[1];
				setDigitalTelecontrolButton2StepsAutoUnLock();
			break;
		case 0xba://自动A/C模式
				m_enCarSet_AutoAcModeState = (E_CARSET_AUTO_ACMODE_STATE)p[1];
				setDigitalAutoAcMode();
			break;
		case 0xbb://有效通风模式
				m_enCarSet_VentilatModeState = (E_CARSET_EFFECTIVE_VENTILATMODE_STATE)p[1];
				setDigitalEffectiveventilatMode();
			break;
		case 0xc0:
				m_enCarDangerWarningLampState = (E_CAR_DANGER_WARNING_LAMP_STATE)p[1];
				setDigitalDangerWarningLampState();
			break;
		case 0xc1:
				m_enCarDrivingRemoteDippedLampState = (E_CAR_DRIVING_REMOTE_DIPPED_LAMP_STATE)p[1];
				setDigitalDrivingRemoteDippedLampState(p[2]);
			break;
		case 0xc2:
				m_enCarBrakeTailLampState = (E_CAR_BRAKE_TAIL_LAMP_STATE)p[1];
				setDigitalBrakeTailLampState();
			break;
		case 0xc3:
				m_enCarCorneringLampState = (E_CAR_CORNERING_LAMP_STATE)p[1];
				setDigitalCorneringLampState();
			break;
		case 0xc4:
				m_enCarGearsState = (E_CAR_GEARS_STATE)p[1];
				setDigitalGearsState();
			break;
		case 0xc5://HL_BrakeState//analyseHalMessage_toyota_CarInfor()
			break;
		case 0xc6:
				m_enCar_EngineState = (E_CAR_ENGINE_STATE)p[1];
				setDigitalEngineState();
			break;
		case 0xc7:
				m_enCar_OilConsumptionAlarmState = (E_CAR_OIL_CONSUMPTION_ALARM_STATE)p[1];
				setDigitalOilConsumptionAlarmState();
				noticAppBombOilConsumptionAlarm();
			break;
		default:
			break;
	}
}

bool CCarInfoCarSettingToyota::pages(u32 id, u8 ms, u8 *p, u8 len)
{
	LOGD("[%s] %s id = [0x%x]", CAMRY,__FUNCTION__, id);

	E_MOUSE_STATUS e = (E_MOUSE_STATUS)(ms);

	bool bRet = false;
	bRet = carInforMainPage(id, e, p, len);
	if (bRet)
		return true;

	bRet = false;
	bRet = carPersonalization_Page(id, e, p, len);
	if (bRet)
		return true;

	bRet = false;
	bRet = carAfterSettingtheCameraGuideLine_Page(id, e, p, len);
	if (bRet)
		return true;

	bRet = false;
	bRet = carPersonalization_DoorLockSettings_Page(id, e, p, len);
	if (bRet)
		return true;
	
	bRet = false;
	bRet = carPersonalization_ClimateSettings_Page(id, e, p, len);
	if (bRet)
		return true;
	
	bRet = false;
	bRet = carPersonalization_LightsSettings_Page(id, e, p, len);
	if (bRet)
		return true;

	return false;

}

bool CCarInfoCarSettingToyota::carInforMainPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;
	switch(id)
	{
	case CONTROLID_CARINFOR_CARSETTINGS_PERSONALIZATIONG:// 0x20013f //(new)      车辆设置  (车辆信息主页)   
		clickButtonCarSettings_Personalization(e);
		break;
	case CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE:// 0x200140// (new)     倒车设置  (车辆信息主页)  
		clickButtonCarSettings_AfterSettingTheCameraGuideLine(e);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;

}

bool CCarInfoCarSettingToyota::carPersonalization_Page(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	//#define PAGE_CAMRY_CARSET_PERSONALIZATION 0x2030		// 长和凯美瑞车辆信息车辆设置页 
	bool bRet = true;
	switch(id)
	{
		case CONTROLID_CARINFOR_CARSETTINGS_DOORLOCKSETTINGS:// 0x203000 //(new)  门锁设置 
			clickButtonCarPersonalization_DoorLockSettings(e);
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_CLIMATESETTINGS:// 0x203001 //(new)   气候设置
			clickButtonCarPersonalization_ClimateSettings(e);
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_LIGHTSSETTINGS:// 0x203002 //(new)  车灯设置
			clickButtonCarPersonalization_LightsSettings(e);
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_MAIN_BACK:// 0x2030f0 //(new)   返回键 
			clickButtonJumpToCarInformationgMainPage_Back(e);
			break;
		default:
			bRet = false;
		break;
	}

	return bRet;

}

bool CCarInfoCarSettingToyota::carPersonalization_DoorLockSettings_Page(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	//#define PAGE_CAMRY_CARSET_PERSONALIZATION_DOORLOCK  0x2031 // 长和凯美瑞车辆信息门锁设置页
	bool bRet = true;
	switch(id)
	{
		case CONTROLID_CARINFOR_CARSETTINGS_SPEED_AUTOLOCKSWITCH:// 0x203100 //(new)   通过车速自动锁止开关 
			clickButtonSpeedAutoLockSwitch(p[0]);
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_OUT_P_BLOCK_AUTOLOCKSWITCH:// 0x203101 //(new)   通过换出P档自动锁止开关
			clickButtonOut_P_blockAutoLockSwitch(p[0]);
			break;       
		case CONTROLID_CARINFOR_CARSETTINGS_IN_P_BLOCK_AUTOUNLOCKSWITCH:// 0x203102 //(new)   通过换入P档自动解锁开关  
			clickButtonIn_P_blockAutoLockSwitch(p[0]);
			break; 
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVERDOOR_AUTOUNLOCKSWITCH:// 0x203103 //(new)   通过驾驶员车门自动解锁开关  
			clickButtonDriverDoorAutoUnLockSwitch(p[0]);
			break; 
		case CONTROLID_CARINFOR_CARSETTINGS_Button2Steps_AUTOUNLOCKSWITCH:// 0x203104 //(new)   遥控按钮两步解锁开关  
			clickButtonTelecontrol2StepsAutoUnLockSwitch(p[0]);
			break; 
		case CONTROLID_CARINFOR_CARSETTINGS_LOCKSTATE_PILOTLAMPSWITCH:// 0x203105 //(new)   锁止/解锁反馈指示灯开关 
			clickButtonLockStatePilotlampSwitch(p[0]);
			break; 
		case CONTROLID_CARINFOR_CARSETTINGS_DOORUNLOCK_TEXT:// 0x203106 //  选择车门进行解锁显示文本(独有的控件ID)    
		case CONTROLID_CARINFOR_CARSETTINGS_DOORUNLOCK_UP:// 0x203107 //  选择车门进行解锁UP按钮               
		case CONTROLID_CARINFOR_CARSETTINGS_DOORUNLOCK_DOWN:// 0x203108 //  选择车门进行解锁DOWN按钮   
			clickButtonDoorUnlockUpOrDown(id-CONTROLID_CARINFOR_CARSETTINGS_DOORUNLOCK_UP,e);
			break; 
		case CONTROLID_CARINFOR_CARSETTINGS_ELECTRONICKEYTOSYSKEY_SWITCH:// 0x203109 // 通带电子钥匙的进入系统钥匙开关 
			clickButtonElectronicToSystemKeySwitch(p[0]);
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_OK_BOMBBOX:// 0x203119 //  智能钥匙功能已禁用弹框 确定按钮  
		case CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_CHANCE_BOMBBOX:// 0x20311a //  智能钥匙功能已禁用弹框 取消按钮
			clickButtonDisabingSmartKeyOkOrChance(id-CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_OK_BOMBBOX,e);
			break; 
		case CONTROLID_CARINFOR_CARSETTINGS_DOORLOCKSETTINGSPAGE_BACK:// 0X2031f0 //(new)   返回键 
			clickButtonJumpToPersonalizationPage_Back(e);
			break; 
		default:
			bRet = false;
		break;
	}

	switch(id)
	{
		case CONTROLID_CARINFOR_CARSETTINGS_SPEED_AUTOLOCKSWITCH:// 0x203100 //(new)   通过车速自动锁止开关 
		case CONTROLID_CARINFOR_CARSETTINGS_OUT_P_BLOCK_AUTOLOCKSWITCH:// 0x203101 //(new)   通过换出P档自动锁止开关
		case CONTROLID_CARINFOR_CARSETTINGS_IN_P_BLOCK_AUTOUNLOCKSWITCH:// 0x203102 //(new)   通过换入P档自动解锁开关  
		case CONTROLID_CARINFOR_CARSETTINGS_DRIVERDOOR_AUTOUNLOCKSWITCH:// 0x203103 //(new)   通过驾驶员车门自动解锁开关  
		case CONTROLID_CARINFOR_CARSETTINGS_Button2Steps_AUTOUNLOCKSWITCH:// 0x203104 //(new)   遥控按钮两步解锁开关  
		case CONTROLID_CARINFOR_CARSETTINGS_LOCKSTATE_PILOTLAMPSWITCH:// 0x203105 //(new)   锁止/解锁反馈指示灯开关 
		case CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_OK_BOMBBOX:// 0x203119 //  智能钥匙功能已禁用弹框 确定按钮  
			if(e == MOUSE_STATUS_UP){
				saveCarSettings_BombBox(true);
				SetsaveCarSetInforsParamTimer();
			}
			break;

	}



	return bRet;

}

void CCarInfoCarSettingToyota::setDigitalSpeedAutoLock(void)
{
	LOGD("[%s] %s m_enCarSet_SpeedAutoLockState:%x",CAMRY,__FUNCTION__,m_enCarSet_SpeedAutoLockState);
	if(m_enCarSet_SpeedAutoLockState == SPEED_ON)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_SPEED_AUTOLOCKSWITCH,1);
	}
	else if(m_enCarSet_SpeedAutoLockState == SPEED_OFF)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_SPEED_AUTOLOCKSWITCH,0);
	}
}

void CCarInfoCarSettingToyota::setDigitalOut_P_blockAutoLock(void)
{
	LOGD("[%s] %s m_enCarSet_OutPAutoLockState:%x",CAMRY,__FUNCTION__,m_enCarSet_OutPAutoLockState);
	if(m_enCarSet_OutPAutoLockState == OUT_P_ON)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_OUT_P_BLOCK_AUTOLOCKSWITCH,1);
	}
	else if(m_enCarSet_OutPAutoLockState == OUT_P_OFF)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_OUT_P_BLOCK_AUTOLOCKSWITCH,0);
	}
}

void CCarInfoCarSettingToyota::setDigitalIn_P_blockAutoLock(void)
{
	LOGD("[%s] %s m_enCarSet_InPAutoLockState:%x",CAMRY,__FUNCTION__,m_enCarSet_InPAutoLockState);
	if(m_enCarSet_InPAutoLockState == IN_P_ON)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_IN_P_BLOCK_AUTOUNLOCKSWITCH,1);
	}
	else if(m_enCarSet_InPAutoLockState == IN_P_OFF)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_IN_P_BLOCK_AUTOUNLOCKSWITCH,0);
	}
}

void CCarInfoCarSettingToyota::setDigitalDriverDoorAutoUnLock(void)
{
	LOGD("[%s] %s m_enCarSet_DriverDoorAutoUnlockState:%x",CAMRY,__FUNCTION__,m_enCarSet_DriverDoorAutoUnlockState);
	if(m_enCarSet_DriverDoorAutoUnlockState == DRIVERDOOR_AUTOUNLOCK_ON)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVERDOOR_AUTOUNLOCKSWITCH,1);
	}
	else if(m_enCarSet_DriverDoorAutoUnlockState == DRIVERDOOR_AUTOUNLOCK_OFF)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_DRIVERDOOR_AUTOUNLOCKSWITCH,0);
	}
}

void CCarInfoCarSettingToyota::setDigitalTelecontrolButton2StepsAutoUnLock(void)
{
	LOGD("[%s] %s m_enCarSet_Telecontrol2StepState:%x",CAMRY,__FUNCTION__,m_enCarSet_Telecontrol2StepState);
	if(m_enCarSet_Telecontrol2StepState == TELECONTROL_2SEP_ON)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_Button2Steps_AUTOUNLOCKSWITCH,1);
	}
	else if(m_enCarSet_Telecontrol2StepState == TELECONTROL_2SEP_OFF)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_Button2Steps_AUTOUNLOCKSWITCH,0);
	}
}

void CCarInfoCarSettingToyota::setDigitalLockStatePilotlamp(void)
{
	LOGD("[%s] %s m_enCarSet_PilotlampState:%x",CAMRY,__FUNCTION__,m_enCarSet_PilotlampState);
	if(m_enCarSet_PilotlampState == PILOTLAMP_ON)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_LOCKSTATE_PILOTLAMPSWITCH,1);
	}
	else if(m_enCarSet_PilotlampState == PILOTLAMP_OFF)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_LOCKSTATE_PILOTLAMPSWITCH,0);
	}
}

void CCarInfoCarSettingToyota::setDigitalDoorUnlockStringID(void)
{
	LOGD("[%s] %s m_enCarSet_SwitchDoorUnlockSwitch:%x",CAMRY,__FUNCTION__,m_enCarSet_SwitchDoorUnlockSwitch);
	switch(m_enCarSet_SwitchDoorUnlockSwitch)
	{
		case DOOR_UNLOCK_ALL:
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_DOORUNLOCK_TEXT,STRING_CARINFO_DOORUNLOCK_ALL);
		break;
		case DOOR_UNLOCK_DRITVER:
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_DOORUNLOCK_TEXT,STRING_CARINFO_DOORUNLOCK_DRIVER);
		break;
		default:
		break;
	}
}

void CCarInfoCarSettingToyota::setDigitalElectronicToSystemKey(void)
{
	LOGD("[%s] %s m_enCarSet_ElectronicToSysKeyState:%x",CAMRY,__FUNCTION__,m_enCarSet_ElectronicToSysKeyState);
	if(m_enCarSet_ElectronicToSysKeyState == ELECTRONICTOSYSKEY_ON)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_ELECTRONICKEYTOSYSKEY_SWITCH,1);
	}
	else if(m_enCarSet_ElectronicToSysKeyState == ELECTRONICTOSYSKEY_OFF)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_ELECTRONICKEYTOSYSKEY_SWITCH,0);
	}
}

void CCarInfoCarSettingToyota::setDigitalAutoAcMode(void)
{
	LOGD("[%s] %s m_enCarSet_AutoAcModeState:%x",CAMRY,__FUNCTION__,m_enCarSet_AutoAcModeState);
	if(m_enCarSet_AutoAcModeState == ACMODE_ON)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_AUTOACMODE_SWITCH,1);
	}
	else if(m_enCarSet_AutoAcModeState == ACMODE_OFF)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_AUTOACMODE_SWITCH,0);
	}
}

void CCarInfoCarSettingToyota::setDigitalEffectiveventilatMode(void)
{
	LOGD("[%s] %s m_enCarSet_VentilatModeState:%x",CAMRY,__FUNCTION__,m_enCarSet_VentilatModeState);
	if(m_enCarSet_VentilatModeState == VENTILATMODE_ON)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_EFFECTIVEVENTILATMODE_SWITCH,1);
	}
	else if(m_enCarSet_VentilatModeState == VENTILATMODE_OFF)
	{
		setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_EFFECTIVEVENTILATMODE_SWITCH,0);
	}
}

void CCarInfoCarSettingToyota::disabingSmartKey_BombBox(bool bShow)
{
	setUpdateUI(0x00);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_ICON_BOMBBOX, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_TEXT1_BOMBBOX, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_TEXT2_BOMBBOX, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_TEXT3_BOMBBOX, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_TEXT4_BOMBBOX, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_OK_BOMBBOX, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_CHANCE_BOMBBOX, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_DISABINGSMARTKEY_BACKGROUND_BOMBBOX, bShow);
	setUpdateUI(0x01);
}

void CCarInfoCarSettingToyota::SetsaveCarSetInforsParamTimer()
{
	DeletesaveCarSetInforsParamTimer();
	SetTimer(TIME_3S_,1,EXTCAR_TIMER_ID_TOYOTA_CAMRY_SAVECARSETTINGPARAM_SHOWBOMBBOX);
}

void CCarInfoCarSettingToyota::DeletesaveCarSetInforsParamTimer()
{
	DeleteTimer(EXTCAR_TIMER_ID_TOYOTA_CAMRY_SAVECARSETTINGPARAM_SHOWBOMBBOX);
}

void CCarInfoCarSettingToyota::saveCarSettings_BombBox(bool bShow)
{
	setUpdateUI(0x00);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_SAVECARSETINFOR_ICON_BOMBBOX, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_SAVECARSETINFOR_TEXT_BOMBBOX, bShow);
	setVisible(CONTROLID_CARINFOR_CARSETTINGS_SAVECARSETINFOR_BACKGROUND_BOMBBOX, bShow);
	setUpdateUI(0x01);
}

void CCarInfoCarSettingToyota::setDigitalHeadLightOpenSentivityStringID(void)
{
	LOGD("[%s] %s m_enCarSet_HeadLightSentivity:%x",CAMRY,__FUNCTION__,m_enCarSet_HeadLightSentivity);
	switch(m_enCarSet_HeadLightSentivity)
	{
		case SENTIVITY_WEAKEST:
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_HEADLIGHT_OPENSENSITIVITY_TEXT,STRING_CARINFO_HEADLIGHT_OPENSENSITIVITY_WEAKEST);
		break;
		case SENTIVITY_WEAK:
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_HEADLIGHT_OPENSENSITIVITY_TEXT,STRING_CARINFO_HEADLIGHT_OPENSENSITIVITY_WEAK);
		break;
		case SENTIVITY_MODERATE:
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_HEADLIGHT_OPENSENSITIVITY_TEXT,STRING_CARINFO_HEADLIGHT_OPENSENSITIVITY_MODERATE);
		break;
		case SENTIVITY_STRONG:
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_HEADLIGHT_OPENSENSITIVITY_TEXT,STRING_CARINFO_HEADLIGHT_OPENSENSITIVITY_STRONG);
		break;
		case SENTIVITY_MOST:
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_HEADLIGHT_OPENSENSITIVITY_TEXT,STRING_CARINFO_HEADLIGHT_OPENSENSITIVITY_MOST);
		break;
		default:
		break;
	}
}

void CCarInfoCarSettingToyota::setDigitalInteriorLightTimerStringID(void)
{
	LOGD("[%s] m_enCarSet_IntertiorLightTimer:%x",__FUNCTION__,m_enCarSet_IntertiorLightTimer);
	switch(m_enCarSet_IntertiorLightTimer)
	{
		case TIME_7_5:
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_INTERIORLIGHTS_TIMER_TEXT,STRING_CARINFO_INTERIORLIGHTS_TIMER_7_5);
		break;
		case TIME_15:
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_INTERIORLIGHTS_TIMER_TEXT,STRING_CARINFO_INTERIORLIGHTS_TIMER_15);
		break;
		case TIME_30:
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_INTERIORLIGHTS_TIMER_TEXT,STRING_CARINFO_INTERIORLIGHTS_TIMER_30);
		break;
		case TIME_CLOSE:
		setStringText(CONTROLID_CARINFOR_CARSETTINGS_INTERIORLIGHTS_TIMER_TEXT,STRING_CARINFO_INTERIORLIGHTS_TIMER_CLOSE);
		break;
		default:
		break;
	}
}

void CCarInfoCarSettingToyota::setDigitalAfterSetTheCameraGuideLine(void)
{
	LOGD("[%s] m_enCarSet_BackCarGuideLineSet:%x",__FUNCTION__,m_enCarSet_BackCarGuideLineSet);
	switch(m_enCarSet_BackCarGuideLineSet)
	{
		case GUIDELINESET_1:
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_1,1);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_2,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_3,0);
		break;
		case GUIDELINESET_2:
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_1,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_2,1);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_3,0);
		break;
		case GUIDELINESET_3:
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_1,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_2,0);
			setDigitalData(CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_3,1);
		break;
		default:
		break;
	}
}

void CCarInfoCarSettingToyota::setDigitalDangerWarningLampState()
{
	d = m_enCarDangerWarningLampState;
	DisplayingUI_DangerWarningLampState(m_enCarDangerWarningLampState);

	switch(m_enCarDangerWarningLampState)
	{
		case DANGER_WARNING_LAMP_OFF:
		case DANGER_WARNING_LAMP_UNKNOW:
		{
			DeleteTimer(EXTCAR_TIMER_ID_DANGER_WARNING_LAMP_TK);
			setDigitalCorneringLampState();
		}
		break;
		case DANGER_WARNING_LAMP_ON:
		{
			DeleteTimer(EXTCAR_TIMER_ID_CORNERING_LAMP_TK);
			
			DeleteTimer(EXTCAR_TIMER_ID_DANGER_WARNING_LAMP_TK);
			SetTimer(TIME_EXTCAR_DANGER_WARNING_LAMP_TK,0,EXTCAR_TIMER_ID_DANGER_WARNING_LAMP_TK);
		}
		break;
	}
}

void CCarInfoCarSettingToyota::DangerWarning_Lamp_TK()
{
	if(d == DANGER_WARNING_LAMP_ON)
	{
		d = DANGER_WARNING_LAMP_OFF;
	}
	else
	{
		d = m_enCarDangerWarningLampState;
	}

	DisplayingUI_DangerWarningLampState(d);

}

void CCarInfoCarSettingToyota::DisplayingUI_DangerWarningLampState(E_CAR_DANGER_WARNING_LAMP_STATE em)
{
	setUpdateUI(0);
	switch(em)
	{
		case DANGER_WARNING_LAMP_OFF:
		case DANGER_WARNING_LAMP_UNKNOW:
		{
			setVisible(CONTROLID_CARINFOR_DANGER_WARNING_LAMP_LEFT_F,0);
			setVisible(CONTROLID_CARINFOR_DANGER_WARNING_LAMP_LEFT_R,0);
			setVisible(CONTROLID_CARINFOR_DANGER_WARNING_LAMP_RIGHT_F,0);
			setVisible(CONTROLID_CARINFOR_DANGER_WARNING_LAMP_RIGHT_R,0);
		}
		break;
		case DANGER_WARNING_LAMP_ON:
		{
			setVisible(CONTROLID_CARINFOR_DANGER_WARNING_LAMP_LEFT_F,1);
			setVisible(CONTROLID_CARINFOR_DANGER_WARNING_LAMP_LEFT_R,1);
			setVisible(CONTROLID_CARINFOR_DANGER_WARNING_LAMP_RIGHT_F,1);
			setVisible(CONTROLID_CARINFOR_DANGER_WARNING_LAMP_RIGHT_R,1);
		}
		break;
	}
	setUpdateUI(1);
}

void CCarInfoCarSettingToyota::setDigitalDrivingRemoteDippedLampState(u8 s)
{
	setUpdateUI(0);
	switch(m_enCarDrivingRemoteDippedLampState)
	{
		case DRIVING_REMOTE_DIPPED_LAMP_UNKNOW:
			{
				setVisible(CONTROLID_CARINFOR_DIPPED_LAMP,0);
				setVisible(CONTROLID_CARINFOR_REMOTE_LAMP,0);
				setVisible(CONTROLID_CARINFOR_DRIVING_LAMP_F,0);
				setVisible(CONTROLID_CARINFOR_DRIVING_LAMP_R,0);
			}
			break;
		case DRIVING_LAMP:
			if(s == 1)
			{
				setVisible(CONTROLID_CARINFOR_DRIVING_LAMP_F,1);
				setVisible(CONTROLID_CARINFOR_DRIVING_LAMP_R,1);
			}
			else
			{
				setVisible(CONTROLID_CARINFOR_DRIVING_LAMP_F,0);
				setVisible(CONTROLID_CARINFOR_DRIVING_LAMP_R,0);
			}
			break;
		case DIPPED_LAMP:
			if(s == 1)
			{
				setVisible(CONTROLID_CARINFOR_DIPPED_LAMP,1);
			}
			else
			{
				setVisible(CONTROLID_CARINFOR_DIPPED_LAMP,0);
			}
			break;
		case REMOTE_LAMP:
			if(s == 1)
			{
				setVisible(CONTROLID_CARINFOR_REMOTE_LAMP,1);
			}
			else
			{
				setVisible(CONTROLID_CARINFOR_REMOTE_LAMP,0);
			}
			break;
	}
	setUpdateUI(1);
}

void CCarInfoCarSettingToyota::setDigitalBrakeTailLampState()
{
	switch(m_enCarBrakeTailLampState)
	{
		case BRAKE_TAIL_LAMP_OFF:
		case BRAKE_TAIL_LAMP_UNKNOW:
		{
			setVisible(CONTROLID_CARINFOR_BRAKE_TAIL_LAMP,0);
		}
		break;
		case BRAKE_TAIL_LAMP_ON:
		{
			setVisible(CONTROLID_CARINFOR_BRAKE_TAIL_LAMP,1);
		}
		break;
	}
}

void CCarInfoCarSettingToyota::setDigitalCorneringLampState()
{
	if(m_enCarDangerWarningLampState == DANGER_WARNING_LAMP_ON)
		return;
	
	s = m_enCarCorneringLampState;
	DisplayingUI_Cornering_LampState(m_enCarCorneringLampState);
	
	switch(m_enCarCorneringLampState)
	{
		case CORNERING_LAMP_OFF:
		case CORNERING_LAMP_UNKNOW:
		{
			DeleteTimer(EXTCAR_TIMER_ID_CORNERING_LAMP_TK);
		}
		break;
		case CORNERING_LAMP_LEFT:
		case CORNERING_LAMP_RIGHT:
		{
			DeleteTimer(EXTCAR_TIMER_ID_CORNERING_LAMP_TK);
			SetTimer(TIME_EXTCAR_CORNERING_LAMP_TK,0,EXTCAR_TIMER_ID_CORNERING_LAMP_TK);
		}
		break;
	}
}

void CCarInfoCarSettingToyota::Cornering_Lamp_TK()
{
	if(s == CORNERING_LAMP_LEFT || s == CORNERING_LAMP_RIGHT)
	{
		s = CORNERING_LAMP_OFF;
	}
	else
	{
		s = m_enCarCorneringLampState;
	}

	DisplayingUI_Cornering_LampState(s);
}

void CCarInfoCarSettingToyota::DisplayingUI_Cornering_LampState(E_CAR_CORNERING_LAMP_STATE em)
{
	setUpdateUI(0);
	switch(em)
	{
		case CORNERING_LAMP_OFF:
		case CORNERING_LAMP_UNKNOW:
		{
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_LEFT_F,0);
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_LEFT_R,0);
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_RIGHT_F,0);
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_RIGHT_R,0);
		}
		break;
		case CORNERING_LAMP_LEFT:
		{
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_LEFT_F,1);
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_LEFT_R,1);
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_RIGHT_F,0);
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_RIGHT_R,0);
		}
		break;
		case CORNERING_LAMP_RIGHT:
		{
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_LEFT_F,0);
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_LEFT_R,0);
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_RIGHT_F,1);
			setVisible(CONTROLID_CARINFOR_CORNERING_LAMP_RIGHT_R,1);
		}
		break;
	}
	setUpdateUI(1);
}

void CCarInfoCarSettingToyota::setDigitalGearsState()
{
	switch(m_enCarGearsState)
	{
		case GEARS_N:
		break;
		case GEARS_P:
		break;
		case GEARS_R:
		break;
		case GEARS_D:
		break;
		case GEARS_M:
		break;
		case GEARS_UNKNOW:
		break;
	}
}

void CCarInfoCarSettingToyota::setDigitalEngineState()
{
}

void CCarInfoCarSettingToyota::setDigitalOilConsumptionAlarmState()
{
	switch(m_enCar_OilConsumptionAlarmState)
	{
		case OIL_STATE_NORMAL:
		{
			setAnalogData(CONTROLID_CARINFOR_OIL_CONSUMPTION_ALARM_ICON,0);
			setStringText(CONTROLID_CARINFOR_OIL_CONSUMPTION_ALARM_TXT,STRING_CARINFOR_OIL_CONSUMPTION_ALARM_NORMAR);
		}
		break;
		case OIL_STATE_WARNING:
		{
			setAnalogData(CONTROLID_CARINFOR_OIL_CONSUMPTION_ALARM_ICON,1);
			setStringText(CONTROLID_CARINFOR_OIL_CONSUMPTION_ALARM_TXT,STRING_CARINFOR_OIL_CONSUMPTION_ALARM_WARNING);
		}
		break;
		case OIL_STATE_UNKNOW:
		{
			setAnalogData(CONTROLID_CARINFOR_OIL_CONSUMPTION_ALARM_ICON,0);
		}
		break;
		default:
		break;
	}
}

void CCarInfoCarSettingToyota::noticAppBombOilConsumptionAlarm()
{
	switch(m_enCar_OilConsumptionAlarmState)
	{
		case OIL_STATE_NORMAL:
			extcarToApp_OpenBombBox_OilConsumptionAlarm(0x00);
		break;
		case OIL_STATE_WARNING:
			extcarToApp_OpenBombBox_OilConsumptionAlarm(0x01);
		break;
		default:
		break;
	}

}

void CCarInfoCarSettingToyota::clickButtonSpeedAutoLockSwitch(u8 p)
{
	LOGD("[%s] %s p:%x",CAMRY,__FUNCTION__,p);
	setToHalSpeedAutoLock(p);
}

void CCarInfoCarSettingToyota::clickButtonOut_P_blockAutoLockSwitch(u8 p)
{
	LOGD("[%s] %s p:%x",CAMRY,__FUNCTION__,p);
	setToHalOutPblockAutoLock(p);
} 

void CCarInfoCarSettingToyota::clickButtonIn_P_blockAutoLockSwitch(u8 p)
{
	LOGD("[%s] %s p:%x",CAMRY,__FUNCTION__,p);
	setToHalInPblockAutoLock(p);
} 

void CCarInfoCarSettingToyota::clickButtonDriverDoorAutoUnLockSwitch(u8 p)
{
	LOGD("[%s] %s p:%x",CAMRY,__FUNCTION__,p);
	setToHalDriverDoorAutoUnLock(p);
}

void CCarInfoCarSettingToyota::clickButtonTelecontrol2StepsAutoUnLockSwitch(u8 p)
{
	LOGD("[%s] %s p:%x",CAMRY,__FUNCTION__,p);
	setToHalclickTelecontrolButton2StepsAutoUnLock(p);
}

void CCarInfoCarSettingToyota::clickButtonLockStatePilotlampSwitch(u8 p)
{
	LOGD("[%s] %s p:%x",CAMRY,__FUNCTION__,p);
	setToHalLockStatePilotlamp(p);
}

void CCarInfoCarSettingToyota::clickButtonDoorUnlockUpOrDown(u8 param,E_MOUSE_STATUS e)
{
	switch(e)
	{
	 	case MOUSE_STATUS_UP:
		{
			static u8 uTemp = 0;
			if(param == 0)
			{
				if(uTemp == 1)
					uTemp = 0;
				else if(uTemp == 0)
					uTemp = 1;
			}
			else if(param == 1)
			{
				if(uTemp == 1)
					uTemp = 0;
				else if(uTemp == 0)
					uTemp = 1;
			}

			LOGD("[%s] %s param:%x uTemp:%x",CAMRY,__FUNCTION__,param,uTemp);
			setToHalSwitchOneDoorUnLock(uTemp);
	 	}
		break;
		default:
		break;
	}
}

void CCarInfoCarSettingToyota::clickButtonElectronicToSystemKeySwitch(u8 p)
{
	if(p == 0)//OFF
	{
		disabingSmartKey_BombBox(true);
	}
	else if(p == 1)//ON
	{
		LOGD("[%s] %s :1 ",CAMRY,__FUNCTION__);
		setToHalElectronicGoToSystemKey(1);
		
		saveCarSettings_BombBox(true);
		SetsaveCarSetInforsParamTimer();
	}
}
void CCarInfoCarSettingToyota::clickButtonDisabingSmartKeyOkOrChance(u8 param,E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
			if(param == 0)//OK
			{
				LOGD("[%s] %s :0",CAMRY,__FUNCTION__);
				setToHalElectronicGoToSystemKey(0);
				disabingSmartKey_BombBox(false);
			}
			else if(param == 1)//chance
			{ 
				disabingSmartKey_BombBox(false);
				setDigitalElectronicToSystemKey();
			}
		}
		break;
		default:
		break;
	}
		
}

void CCarInfoCarSettingToyota::clickButtonAutoAcModeSwitch(u8 p)
{
	LOGD("[%s] %s p:%x",CAMRY,__FUNCTION__,p);
	setToHalAutoAcMode(p);
}

void CCarInfoCarSettingToyota::clickButtonEffectiveventilatModeSwitch(u8 p)
{
	LOGD("[%s] %s p:%x",CAMRY,__FUNCTION__,p);
	setToHalEffectiveVentilatMode(p);
}

void CCarInfoCarSettingToyota::clickButtonHeadLightOpenSentivityUpOrDown(u8 param,E_MOUSE_STATUS e)
{
	static u8 nTempParam = (u8)m_enCarSet_HeadLightSentivity;

	if(nTempParam >= 1 && nTempParam <= 5)
	{
		if(param == 0)
		{
			if(nTempParam == 1){
				nTempParam = 5;
			}
			else{
				nTempParam--;
			}
			
		}
		else if(param == 1)
		{
			if(nTempParam == 5){
				nTempParam = 1;
			}
			else{
				nTempParam++;
			}
		}

		LOGD("[%s] %s param:%x nTempParam:%x",CAMRY,__FUNCTION__,param,nTempParam);
		setToHalHeadLight_OpenSensitivity(nTempParam);
	}
}

void CCarInfoCarSettingToyota::clickButtonInteriorLightTimerUpOrDown(u8 param,E_MOUSE_STATUS e)
{
	static u8 nTempParam = (u8)m_enCarSet_IntertiorLightTimer;
	if(nTempParam >= 1 && nTempParam <= 4)
	{
		if(param == 0)
		{
			if(nTempParam == 1){
				nTempParam = 4;
			}
			else{
				nTempParam--;
			}
			
		}
		else if(param == 1)
		{
			if(nTempParam == 4){
				nTempParam = 1;
			}
			else{
				nTempParam++;
			}
		}
		LOGD("[%s] %s param:%x nTempParam:%x",CAMRY,__FUNCTION__,param,nTempParam);
		setToHalInteriorLightsTimer(nTempParam);
	}

}

void CCarInfoCarSettingToyota::clickButtonAfterSetTheCameraGuideLine(u8 param,E_MOUSE_STATUS e)
{
	switch(param)
	{
		case 0:
			setToHalAfterSettingtheCameraGuideLine(2);
		break;
		case 1:
			setToHalAfterSettingtheCameraGuideLine(4);
		break;
		case 2:
			setToHalAfterSettingtheCameraGuideLine(6);
		break;
		default:
		break;
	}
}

bool CCarInfoCarSettingToyota::carPersonalization_ClimateSettings_Page(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	//#define PAGE_CAMRY_CARSET_PERSONALIZATION_CLIMATE 0x2032   气候设置页
	bool bRet = true;
	switch(id)
	{
		case CONTROLID_CARINFOR_CARSETTINGS_AUTOACMODE_SWITCH:// 0x203200 //(new)    自动A/C模式开关 
			clickButtonAutoAcModeSwitch(p[0]);
			break; 
		case CONTROLID_CARINFOR_CARSETTINGS_EFFECTIVEVENTILATMODE_SWITCH:// 0x203201 //(new)    有效通风模式开关   
			clickButtonEffectiveventilatModeSwitch(p[0]);
			break; 
		case CONTROLID_CARINFOR_CARSETTINGS_CLIMATESETTINGSPAGE_BACK:// 0x2032f0 //(new)    返回键 
			clickButtonJumpToPersonalizationPage_Back(e);
			break; 
		default:
			bRet = false;
		break;
	}

	switch(id)
	{
		case CONTROLID_CARINFOR_CARSETTINGS_AUTOACMODE_SWITCH:
		case CONTROLID_CARINFOR_CARSETTINGS_EFFECTIVEVENTILATMODE_SWITCH:  
			if(e == MOUSE_STATUS_UP){
			saveCarSettings_BombBox(true);
			SetsaveCarSetInforsParamTimer();
			}
		break;
	}


	return bRet;

}

bool CCarInfoCarSettingToyota::carPersonalization_LightsSettings_Page(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	//#define PAGE_CAMRY_CARSET_PERSONALIZATION_LIGHTS 0x2033   车灯设置页
	bool bRet = true;
	switch(id)
	{    
		case CONTROLID_CARINFOR_CARSETTINGS_HEADLIGHT_OPENSENSITIVITY_TEXT:// 0x203300 //(new)   大灯打开灵敏度 高             
		case CONTROLID_CARINFOR_CARSETTINGS_HEADLIGHT_OPENSENSITIVITY_UP:// 0x203301 //(new)   大灯打开灵敏度 中             
		case CONTROLID_CARINFOR_CARSETTINGS_HEADLIGHT_OPENSENSITIVITY_DOWN:// 0x203302 //(new)   大灯打开灵敏度 低  
			clickButtonHeadLightOpenSentivityUpOrDown(id-CONTROLID_CARINFOR_CARSETTINGS_HEADLIGHT_OPENSENSITIVITY_UP,e);
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_INTERIORLIGHTS_TIMER_TEXT:// 0x203303 //(new)   车内照明灯熄灭定时时间              
		case CONTROLID_CARINFOR_CARSETTINGS_INTERIORLIGHTS_TIMER_UP:// 0x203304 //(new)   车内照明灯熄灭定时时间 UP按钮            
		case CONTROLID_CARINFOR_CARSETTINGS_INTERIORLIGHTS_TIMER_DOWN:// 0x203305 //(new)   车内照明灯熄灭定时时间 DOWN按钮  
			clickButtonInteriorLightTimerUpOrDown(id-CONTROLID_CARINFOR_CARSETTINGS_INTERIORLIGHTS_TIMER_UP,e);
			break;
		case CONTROLID_CARINFOR_CARSETTINGS_LIGHTSSETTINGSPAGE_BACK:// 0x2033f0 //(new)   返回键
			clickButtonJumpToPersonalizationPage_Back(e);
			break;
		default:
			bRet = false;
		break;
	}

	return bRet;

}

bool CCarInfoCarSettingToyota::carAfterSettingtheCameraGuideLine_Page(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	//#define PAGE_CAMRY_AFTERSETTEHCAMERAGUIDELINE 0x2034  倒车设置页				 
	bool bRet = true;
	switch(id)
	{

		case CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_1:// 0x203400 //(new)  倒车引导线01 （左图）            
		case CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_2:// 0x203401 //(new)  倒车引导线02 （中图）            
		case CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_3:// 0x203402 //(new)  倒车引导线03 （右图） 
			clickButtonAfterSetTheCameraGuideLine(id-CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_1,e);
		break;
		case CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_BACK:// 0x2034f0 //(new)  返回键  
			clickButtonJumpToCarInformationgMainPage_Back(e);
			break;

		default:
			bRet = false;
		break;
	}

	switch(id)
	{
				
		case CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_1:// 0x203400 //(new)  倒车引导线01 （左图） 		   
		case CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_2:// 0x203401 //(new)  倒车引导线02 （中图） 		   
		case CONTROLID_CARINFOR_CARSETTINGS_ARTERSETTINGTHECAMERAGUIDELINE_3:// 0x203402 //(new)  倒车引导线03 （右图） 		
		if(e == MOUSE_STATUS_UP){
			saveCarSettings_BombBox(true);
			SetsaveCarSetInforsParamTimer();
		}
		break;	
	}

	return bRet;

}

void CCarInfoCarSettingToyota::clickButtonCarSettings_Personalization(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setPage(PAGE_CAMRY_CARSET_PERSONALIZATION);
		}
		break;
	default:
		break;
	}

}

void CCarInfoCarSettingToyota::clickButtonCarSettings_AfterSettingTheCameraGuideLine(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setPage(PAGE_CAMRY_AFTERSETTEHCAMERAGUIDELINE);
		}
		break;
	default:
		break;
	}

}

void CCarInfoCarSettingToyota::clickButtonCarPersonalization_DoorLockSettings(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setPage(PAGE_CAMRY_CARSET_PERSONALIZATION_DOORLOCK);
		}
		break;
	default:
		break;
	}
}

void CCarInfoCarSettingToyota::clickButtonCarPersonalization_ClimateSettings(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setPage(PAGE_CAMRY_CARSET_PERSONALIZATION_CLIMATE);
		}
		break;
	default:
		break;
	}
}

void CCarInfoCarSettingToyota::clickButtonCarPersonalization_LightsSettings(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setPage(PAGE_CAMRY_CARSET_PERSONALIZATION_LIGHTS);
		}
		break;
	default:
		break;
	}
}


void CCarInfoCarSettingToyota::clickButtonJumpToPersonalizationPage_Back(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setPage(PAGE_CAMRY_CARSET_PERSONALIZATION);
		}
		break;
	default:
		break;
	}
}

void CCarInfoCarSettingToyota::clickButtonJumpToCarInformationgMainPage_Back(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setPage(PAGE_TRAVEL_INFORMATION);
		}
		break;
	default:
		break;
	}
}


void CCarInfoCarSettingToyota::setToHalSpeedAutoLock(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0x60,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setToHalHeadLight_OpenSensitivity(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0x65,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setToHalInteriorLightsTimer(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0xb1,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setToHalSwitchOneDoorUnLock(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0xb2,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
void CCarInfoCarSettingToyota::setToHalElectronicGoToSystemKey(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0xb3,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setToHalLockStatePilotlamp(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0xb4,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setToHalOutPblockAutoLock(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0xb5,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setToHalInPblockAutoLock(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0xb6,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setToHalDriverDoorAutoUnLock(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0xb7,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setToHalAfterSettingtheCameraGuideLine(u8 param)
{
	LOGD("[%s] %s param:%x ",CAMRY,__FUNCTION__,param);
	u8 szMsg[4] = {0x90,0x00,0xb8,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setToHalclickTelecontrolButton2StepsAutoUnLock(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0xb9,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setToHalAutoAcMode(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0xba,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setToHalEffectiveVentilatMode(u8 param)
{
	u8 szMsg[4] = {0x90,0x00,0xbb,param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoCarSettingToyota::setPage(u16 id)
{
	LOGD("[%s]", __FUNCTION__);
	u8 szMsg[] = {0x82, 0x00, 0x00};
	memcpy(szMsg + 1, &id, 2);
	makeAndSendMessageToModule(locale_module_mid(),  MODULE_ID_SYSTEM,  szMsg, sizeof(szMsg));
}


