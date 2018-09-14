#include "CarInfoToyotaPrado.h"

#include "stringID.h"
#include "pageID.h"
#include "controlID.h"

#include "param.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseCommand.h"
#include "appResponseFunction.h"
#include "halRequestFunction.h"
#include "halResponseCommand.h"
#include "halResponseFunction.h"
#include "moduleParamRequest.h"
#include "moduleParamResponse.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"
#include "timer_interface.h"
#include <flymoduleApi_internal.h>


CCarInfoToyotaPrado::CCarInfoToyotaPrado(void)
{
}

CCarInfoToyotaPrado::~CCarInfoToyotaPrado(void)
{
}

void CCarInfoToyotaPrado::initCarInfo(void)
{
	initCarParam();
	initCarParamToyotaPrado();
	initCarUI();
	initCarUIToyotaPrado();

	killAverageOilconsumeUpdateTimer();
	killInstantOilconsumeCountTimer();
}

void CCarInfoToyotaPrado::AccOffinitCarInfo(void)
{
	initCarParam();
	initCarParamToyotaPrado();

	killAverageOilconsumeUpdateTimer();
	killInstantOilconsumeCountTimer();
}

void CCarInfoToyotaPrado::runCarInfo(void)
{
	setAverageOilconsumeUpdateTimer();
	setInstantOilconsumeCountTimer();
}

void CCarInfoToyotaPrado::initCarParamToyotaPrado(void)
{
	//�״����
	int m_nRadarAlarmVolume = DEFAULT_NORMAL;
	int m_nRadarAlarmLevel = DEFAULT_NORMAL;
	int m_nFrontSonarFarther = DEFAULT_NORMAL;
	int m_nRearSonarFarther = DEFAULT_NORMAL;
	int m_nRadarSwitch = DEFAULT_NORMAL;

	memset(m_nszAverageOilConsumeHistory, 0, sizeof(m_nszAverageOilConsumeHistory));

	m_nInstantOilConsume = DEFAULT_NORMAL;//ƽ���ͺ�
	m_nOilConsumeUnitHistory = DEFAULT_NORMAL;//�ͺĵ�λ

	m_nInstantOilConsumeCount = 0;
	m_nInstantOilConsumeSum = 0;
}

void CCarInfoToyotaPrado::initCarUIToyotaPrado(void)
{
	updateAverageOilConsumeHistory();
	updateRadarSetting();
}

void CCarInfoToyotaPrado::analyseCarInfo(u8 *p, int len)
{
	switch(p[0])
	{
	case 0x01:
		{
			static int snCarDoorLR = DEFAULT_STATIC_NORMAL;
			static int snCarDoorRR = DEFAULT_STATIC_NORMAL;
			static int snCarDoorRF = DEFAULT_STATIC_NORMAL;
			static int snCarDoorLF = DEFAULT_STATIC_NORMAL;
			static int snCarDoorBack = DEFAULT_STATIC_NORMAL;
			static int snCarDoorEngine = DEFAULT_STATIC_NORMAL;
			static int snHandLock = DEFAULT_STATIC_NORMAL;
			static int snCarWindowBack = DEFAULT_STATIC_NORMAL;
			static int snFootLock = DEFAULT_STATIC_NORMAL;
			static int snSafeBelt = DEFAULT_STATIC_NORMAL;
			static int snCarGear = DEFAULT_STATIC_NORMAL;
			static int snDegreeOutdoor = DEFAULT_STATIC_NORMAL;
			static int snMileageCanRun = DEFAULT_STATIC_NORMAL;
			static int snMileageHaveRun = DEFAULT_STATIC_NORMAL;

			u8 d0 = p[1];
			u8 b0 = d0 & 0x01;
			u8 b1 = d0 & 0x02;
			u8 b2 = d0 & 0x04;
			u8 b3 = d0 & 0x08;

			snCarDoorLR = (b0) ? CAR_DOOR_OPEN : CAR_DOOR_CLOSE;
			snCarDoorRR = (b1) ? CAR_DOOR_OPEN : CAR_DOOR_CLOSE;
			snCarDoorRF = (b2) ? CAR_DOOR_OPEN : CAR_DOOR_CLOSE;
			snCarDoorLF = (b3) ? CAR_DOOR_OPEN : CAR_DOOR_CLOSE;
			snCarDoorBack = (d0 & 0x10) ? CAR_DOOR_OPEN : CAR_DOOR_CLOSE;
			snHandLock = (d0 & 0x20) ? HAND_LOCK_UP : HAND_LOCK_DOWN;
			snCarDoorEngine = (d0 & 0x40) ? CAR_DOOR_OPEN : CAR_DOOR_CLOSE;
			snCarWindowBack = (d0 & 0x80) ? CAR_WINDOW_OPEN : CAR_WINDOW_CLOSE;
			
			u8 d1 = p[2];
			snFootLock = (d1 & 0x01) ? FOOT_LOCK_CLOSE : FOOT_LOCK_OPEN;
			snSafeBelt = (d1 & 0x02) ? SAFE_BELT_OPEN : SAFE_BELT_CLOSE;
			snCarGear = d1 >> 4;

			u8 d2 = p[3];
			snDegreeOutdoor = (char)d2;
			snDegreeOutdoor *= 10;
			
			snMileageCanRun = 0;
			memcpy(&snMileageCanRun, p + 4, 2);
			snMileageHaveRun = 0;
			memcpy(&snMileageHaveRun, p + 6, 3);

			LOGD("[%s]1snCarDoorLF = [%s]", __FUNCTION__, (snCarDoorLF == CAR_DOOR_OPEN) ? "CAR_DOOR_OPEN" : "CAR_DOOR_CLOSE");
			LOGD("[%s] snCarDoorRF = [%s]", __FUNCTION__, (snCarDoorRF == CAR_DOOR_OPEN) ? "CAR_DOOR_OPEN" : "CAR_DOOR_CLOSE");
			LOGD("[%s] snCarDoorLR = [%s]", __FUNCTION__, (snCarDoorLR == CAR_DOOR_OPEN) ? "CAR_DOOR_OPEN" : "CAR_DOOR_CLOSE");
			LOGD("[%s] snCarDoorRR = [%s]", __FUNCTION__, (snCarDoorRR == CAR_DOOR_OPEN) ? "CAR_DOOR_OPEN" : "CAR_DOOR_CLOSE");
			LOGD("[%s] snCarDoorBack = [%s]", __FUNCTION__, (snCarDoorBack == CAR_DOOR_OPEN) ? "CAR_DOOR_OPEN" : "CAR_DOOR_CLOSE");
			LOGD("[%s] snCarDoorEngine = [%s]", __FUNCTION__, (snCarDoorEngine == CAR_DOOR_OPEN) ? "CAR_DOOR_OPEN" : "CAR_DOOR_CLOSE");

			LOGD("[%s] snHandLock = [%s]", __FUNCTION__, (snHandLock == HAND_LOCK_UP) ? "HAND_LOCK_UP" : "HAND_LOCK_DOWN");
			LOGD("[%s] snCarWindowBack = [%s]", __FUNCTION__, (snCarWindowBack == CAR_WINDOW_OPEN) ? "CAR_WINDOW_OPEN" : "CAR_WINDOW_CLOSE");

			LOGD("[%s] snFootLock = [%s]", __FUNCTION__, (snFootLock == FOOT_LOCK_OPEN) ? "FOOT_LOCK_OPEN" : "FOOT_LOCK_CLOSE");
			LOGD("[%s] snSafeBelt = [%s]", __FUNCTION__, (snSafeBelt == SAFE_BELT_OPEN) ? "SAFE_BELT_OPEN" : "SAFE_BELT_CLOSE");

			LOGD("[%s] snCarGear = [%s]", __FUNCTION__, getCarGearString(snCarGear));

			LOGD("[%s] snDegreeOutdoor = [%d]", __FUNCTION__, snDegreeOutdoor);
			LOGD("[%s] snMileageCanRun = [%d]", __FUNCTION__, snMileageCanRun);
			LOGD("[%s] snMileageHaveRun = [%d]", __FUNCTION__, snMileageHaveRun);

			if (snCarDoorLR != (int)m_eCarDoorLR ||
				snCarDoorRR != (int)m_eCarDoorRR ||
				snCarDoorRF != (int)m_eCarDoorRF ||
				snCarDoorLF != (int)m_eCarDoorLF ||
				snCarDoorBack != (int)m_eCarDoorBack)
			{
				m_eCarDoorLR = (E_CAR_DOOR)snCarDoorLR;
				m_eCarDoorRR = (E_CAR_DOOR)snCarDoorRR;
				m_eCarDoorRF = (E_CAR_DOOR)snCarDoorRF;
				m_eCarDoorLF = (E_CAR_DOOR)snCarDoorLF;
				m_eCarDoorBack = (E_CAR_DOOR)snCarDoorBack;
				
				updateCarDoor();
			}
			
			if (snCarDoorEngine != (int)m_eCarDoorEngine)
			{
				m_eCarDoorEngine = (E_CAR_DOOR)snCarDoorEngine;
				
				updateEngineDoor();
			}

			
			if (snHandLock != (int)m_eHandLock)
			{
				m_eHandLock = (E_HAND_LOCK)snHandLock;
				
				updateHandLock();
			}
			
			if (snCarWindowBack != (int)m_eCarWindowBack)
			{
				m_eCarWindowBack = (E_CAR_WINDOW)snCarWindowBack;
				
				updateCarWindow();
			}
			
			if (snFootLock != (int)m_eFootLock)
			{
				m_eFootLock = (E_FOOT_LOCK)snFootLock;
				
				updateFootLock();
			}

			if (snSafeBelt != (int)m_eSafeBelt)
			{
				m_eSafeBelt = (E_SAFE_BELT)snSafeBelt;
				
				updateSafeBelt();
			}
			LOGD("[%s] snGear = [%d], m_nCarGear = [%d]", __FUNCTION__, snCarGear, m_nCarGear);
			
			if (snCarGear != (int)m_nCarGear)
			{
				m_nCarGear = snCarGear;
				
				updateCarGear();
			}
			
			if (snDegreeOutdoor != (int)m_nDegreeOutdoor)
			{
				m_nDegreeOutdoor = snDegreeOutdoor;
				pLocalParam->nDegreeOfCarGround = (s16)snDegreeOutdoor;
				updateOutDoorTemperature();
			}
			
			if (snMileageCanRun != (int)m_nMileageCanRun)
			{
				m_nMileageCanRun = snMileageCanRun;
				pLocalParam->SurplusDistance = snMileageCanRun;
				updateMileageCanRun();
			}
		
			if (snMileageHaveRun != (int)m_nMileageHaveRun)
			{
				m_nMileageHaveRun = snMileageHaveRun;
				pLocalParam->nDrivingDistance = snMileageHaveRun;
				updateMileageHaveRun();
			}
		}
		break;
	/*
	case 0x02:
		{
			LOGD("*******************(%x %x %x %x)",p[1],p[2],p[3],p[4]);
			u8 d0 = p[1];
			m_nRadarAlarmVolume = 0;
			m_nRadarAlarmVolume = d0 & 0x07;

			m_nRadarAlarmLevel = 0;
			m_nRadarAlarmLevel = (d0 >> 3) & 0x03;
			
			m_nFrontSonarFarther = 0;
			m_nFrontSonarFarther = (d0 >> 5) & 0x01;

			m_nRearSonarFarther = 0;
			m_nRearSonarFarther = (d0 >> 6) & 0x01;

			m_nRadarSwitch = (d0 >> 7) & 0x01;

			int nfl = 0, nfm = 0, nfr = 0;
			int nrl = 0, nrm = 0, nrr = 0;
			u8 d1 = p[2], d2 = p[3], d3 = p[4];

			nfr = d1 & 0x0F;
			nfl = (d1 >> 4) & 0x0F;
			nfm = d2 & 0x0F;

			nrr = d3 & 0x0F;
			nrl = (d3 >> 4) & 0x0F;
			nrm = (d2 >> 4) & 0x0F;

			LOGD("[%s] m_nRadarAlarmVolume = [%d]", __FUNCTION__, m_nRadarAlarmVolume);
			LOGD("[%s] m_nRadarAlarmLevel = [%d]", __FUNCTION__, m_nRadarAlarmLevel);
			LOGD("[%s] m_nFrontSonarFarther = [%d]", __FUNCTION__, m_nFrontSonarFarther);
			LOGD("[%s] m_nRearSonarFarther = [%d]", __FUNCTION__, m_nRearSonarFarther);
			LOGD("[%s] m_nRadarSwitch = [%d]", __FUNCTION__, m_nRadarSwitch);

			LOGD("[%s] radar data ------------------------------------------------------", __FUNCTION__);
			LOGD("[%s] front radar l m r [%d] [%d] [%d]", __FUNCTION__, nfl, nfm, nfr);
			LOGD("[%s] rear  radar l m r [%d] [%d] [%d]", __FUNCTION__, nrl, nrm, nrr);
			LOGD("[%s] radar data ------------------------------------------------------", __FUNCTION__);

			updateRadarSetting();
			//////ǰ�״�
			u8 pos = 0;
			u32 d = 0;
			int t = 0;
			t = radar_signal_LPC2JNI(nfl, 4);
			d += t;
			t = radar_signal_LPC2JNI(nfm, 4);
			d += t << 8;
			t = radar_signal_LPC2JNI(nfm, 4);
			d += t << 16;
			t = radar_signal_LPC2JNI(nfr, 4);
			d += t << 24;
			exterToRadar(pos, d);
			////���״�
			pos = 1;
			d = 0;
			t = 0;
			t = radar_signal_LPC2JNI(nrl, 4);
			d += t;
			t = radar_signal_LPC2JNI(nrm, 5);
			d += t << 8;
			t = radar_signal_LPC2JNI(nrm, 5);
			d += t << 16;
			t = radar_signal_LPC2JNI(nrr, 4);
			d += t << 24;
			exterToRadar(pos, d);			
		}
		break;*/
		case 0x02://The USA
		{
			LOGD("*******************(%x %x %x %x)",p[1],p[2],p[3],p[4]);
			u8 d0 = p[1];
			m_nRadarAlarmVolume = 0;
			m_nRadarAlarmVolume = d0 & 0x07;

			m_nRadarAlarmLevel = 0;
			m_nRadarAlarmLevel = (d0 >> 3) & 0x03;
			
			m_nFrontSonarFarther = 0;
			m_nFrontSonarFarther = (d0 >> 5) & 0x01;

			m_nRearSonarFarther = 0;
			m_nRearSonarFarther = (d0 >> 6) & 0x01;

			m_nRadarSwitch = (d0 >> 7) & 0x01;

			int nfl = 0, nfm = 0, nfr = 0;
			int nrl = 0, nrm = 0, nrr = 0;
			u8 d1 = p[2], d2 = p[3], d3 = p[4];

			nfr = d1 & 0x0F;
			nfl = (d1 >> 4) & 0x0F;
			nfm = d2 & 0x0F;

			nrr = d3 & 0x0F;
			nrl = (d3 >> 4) & 0x0F;
			nrm = (d2 >> 4) & 0x0F;

			LOGD("[%s] m_nRadarAlarmVolume = [%d]", __FUNCTION__, m_nRadarAlarmVolume);
			LOGD("[%s] m_nRadarAlarmLevel = [%d]", __FUNCTION__, m_nRadarAlarmLevel);
			LOGD("[%s] m_nFrontSonarFarther = [%d]", __FUNCTION__, m_nFrontSonarFarther);
			LOGD("[%s] m_nRearSonarFarther = [%d]", __FUNCTION__, m_nRearSonarFarther);
			LOGD("[%s] m_nRadarSwitch = [%d]", __FUNCTION__, m_nRadarSwitch);

			LOGD("[%s] radar data ------------------------------------------------------", __FUNCTION__);
			LOGD("[%s] front radar l m r [%d] [%d] [%d]", __FUNCTION__, nfl, nfm, nfr);
			LOGD("[%s] rear  radar l m r [%d] [%d] [%d]", __FUNCTION__, nrl, nrm, nrr);
			LOGD("[%s] radar data ------------------------------------------------------", __FUNCTION__);

			updateRadarSetting();

			exterPradoRadarUISwitchToSystem((u8)m_nRadarSwitch);
			if(m_nRadarSwitch == 0){
				return;
			}
			
			//////ǰ�״�
			u8 pos = 0;
			u32 d = 0;
			int t = 0;
			t = radar_signal_LPC2JNI(nfl, 4);
			d += t;
			t = radar_signal_LPC2JNI(nfm, 4);
			d += t << 8;
			t = radar_signal_LPC2JNI(nfm, 4);
			d += t << 16;
			t = radar_signal_LPC2JNI(nfr, 4);
			d += t << 24;
			//exterToRadar(pos, d);
			////���״�
			pos = 1;
			d = 0;
			t = 0;
			t = radar_signal_LPC2JNI(nrl, 4);
			d += t;
			t = radar_signal_LPC2JNI(nrm, 5);
			d += t << 8;
			t = radar_signal_LPC2JNI(nrm, 5);
			d += t << 16;
			t = radar_signal_LPC2JNI(nrr, 4);
			d += t << 24;
			exterToRadar(pos, d);			
		}
		break;
	case 0x03:
		{
			static int snAverageOilConsume = DEFAULT_STATIC_NORMAL;
			
			u8 d0 = p[1];
			
			if(d0 == 1)//(L/100km)
			{
				pLocalParam->eOilConsumeUnit = OIL_CONSUME_UNIT_L_PER_100_KM;
			}
			else if(d0 == 0)//(km/L)
			{
				pLocalParam->eOilConsumeUnit = OIL_CONSUME_UNIT_KM_PER_L;
			}

			snAverageOilConsume = 0;
			memcpy(&snAverageOilConsume, p + 2, 2);

			LOGD("[%s] m_nOilConsumeUnit = [%s]", __FUNCTION__, getOilConsumeUnitString(m_nOilConsumeUnit));
			LOGD("[%s] snAverageOilConsume = [%d]", __FUNCTION__, snAverageOilConsume);

			if ((snAverageOilConsume != (int)m_nAverageOilConsume) || (m_nOilConsumeUnit != d0))
			{
				m_nOilConsumeUnit = d0;
				m_nAverageOilConsume = snAverageOilConsume;
				pLocalParam->avgOilWear = (float)snAverageOilConsume;
				updateAverageOilConsume();
			}
			
		}
		break;
	case 0x04:
		{
			outPutLog(__FUNCTION__, "extcarToAudioVideo", p, len);

			u8 szMsg[16] = {0};
			szMsg[0] = 0xB1;
			memcpy(szMsg + 1, p, len);
			extcarToAudioVideo(szMsg, len + 1);
		}
		break;
	case 0x05:
		{
			u8 d0 = p[1];
			u8 d1 = p[2];
			m_nInstantOilConsume = (d1 << 8) + d0;
			LOGD("[%s] m_nInstantOilConsume = [%d]", __FUNCTION__, m_nInstantOilConsume);
		}
		break;
	case 0x06:
		{
			pLocalParam->eCarDoorLocker = (p[1] == 0x01) ? CAR_DOOR_LOCKER_UNLOCK : CAR_DOOR_LOCKER_LOCK;
			LOGD("[%s]pLocalParam->nCarDoorLockStates:%x","Prado",pLocalParam->nCarDoorLockStates);
			process_car_locker();
		}
		break;
	case 0x07:
		{
			pLocalParam->eCarDoorWindow_FL = (p[1] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
			pLocalParam->eCarDoorWindow_FR = (p[2] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
			pLocalParam->eCarDoorWindow_RL = (p[3] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
			pLocalParam->eCarDoorWindow_RR = (p[4] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
			LOGD("[%s] CarDoorWindow FL,FR(%x,%x):","Prado",pLocalParam->eCarDoorWindow_FL,pLocalParam->eCarDoorWindow_FR);
			LOGD("[%s] CarDoorWindow RL RR(%x,%x)","Prado",pLocalParam->eCarDoorWindow_RL,pLocalParam->eCarDoorWindow_RR);
			process_car_door_window();
		}
		break;
	case 0x08:
		{
			pLocalParam->eHeadLight = (p[1] == 0x00) ? HEAD_LIGHT_CLOSE: HEAD_LIGHT_OPEN;
			LOGD("[%s] pLocalParam->eHeadLight:%x","Prado",pLocalParam->eHeadLight);
			process_car_head_light();
		}
		break;
	case 0x09:
		{
			pLocalParam->nBatteryVoltage = p[1]*256 + p[2];
			LOGD("[%s] pLocalParam->nBatteryVoltage:%x","Prado",pLocalParam->nBatteryVoltage);
			process_BatteryVoltageInfo();
		}
		break;
	case 0x0A://RadarSwitch_key
		{
			LOGD("[%s] RadarSwitch_key:%x","Prado",p[1]);
			exterPradoRadarKeySwitchToSystem(p[1]);
		}
		break;
	default:
		break;
	}
}


void CCarInfoToyotaPrado::updateCarGear()
{
	u8 *p = (u8*)getCarGearString(m_nCarGear);

	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT, p, strlen(( char*)p));
	
	switch(m_nCarGear)
	{
	case 0x00://P
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE, 0);
		break;
	case 0x01://R
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE, 1);
		break;
	default:
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE, 2);
		break;
	}

	g_clsExtcar.sendToFlyJniSdk_GearState((char)m_nCarGear);
}

void CCarInfoToyotaPrado::updateAverageOilConsumeHistory(void)
{
	setUpdateUI(false);
	int i = 0;
	for (i = 0; i < AVERAGE_OIL_CONSUME_HISTORY_ITEM_NUM; i++)
	{
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_DRIVING_INFO_BAR_CHART_1 + i, int(m_nszAverageOilConsumeHistory[i] / 10.0 + 0.5));
	}
	setUpdateUI(true);
}

void CCarInfoToyotaPrado::updateAverageOilConsumeHistoryPerMinute()
{
	if (m_nInstantOilConsume == DEFAULT_NORMAL)
		return ;

	int i = 0;
	for (i = AVERAGE_OIL_CONSUME_HISTORY_ITEM_NUM - 1; i > 0 ; i--)
	{
		m_nszAverageOilConsumeHistory[i] = m_nszAverageOilConsumeHistory[i - 1];
	}

	int nAverageOilConsumePerMinute = 0;
	nAverageOilConsumePerMinute = int(m_nInstantOilConsumeSum * 1.0 / m_nInstantOilConsumeCount + 0.5); 
	m_nInstantOilConsumeSum = 0;
	m_nInstantOilConsumeCount = 0;
	m_nszAverageOilConsumeHistory[0] = (nAverageOilConsumePerMinute > AVERAGE_OIL_CONSUME_MAX * 10) ? AVERAGE_OIL_CONSUME_MAX * 10 : nAverageOilConsumePerMinute;

	updateAverageOilConsumeHistory();
}

void CCarInfoToyotaPrado::updateInstantOilConsumeCount(void)
{
	if (m_nInstantOilConsume == DEFAULT_NORMAL)
		return ;

	m_nInstantOilConsumeCount++;
	m_nInstantOilConsumeSum += m_nInstantOilConsume;
}

void CCarInfoToyotaPrado::updateRadarSetting(void)
{
	setUpdateUI(false);

	char szMsg[16] = {0};

	//��ʾ����
	if (DEFAULT_NORMAL == m_nRadarSwitch)
	{
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_DISPLAY_SWICH_ON, 0);
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_DISPLAY_WWICH_OFF, 0);
	}
	else
	{
		DisplaySwitchCloseAndOpenButton(m_nRadarSwitch);
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_DISPLAY_SWICH_ON, (m_nRadarSwitch == 1) ? 1 : 0);
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_DISPLAY_WWICH_OFF, (m_nRadarSwitch == 1) ? 0 : 1);
	}
	//ǰ����
	if (DEFAULT_NORMAL == m_nFrontSonarFarther)
	{
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_BEFORE_MORE_RECENT, 0);
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_BEFORE_FURTHER, 0);
	}
	else
	{
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_BEFORE_MORE_RECENT, (m_nFrontSonarFarther == 1) ? 0 : 1);
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_BEFORE_FURTHER, (m_nFrontSonarFarther == 1) ? 1 : 0);
	}
	//������
	if (DEFAULT_NORMAL == m_nRearSonarFarther)
	{
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_AFTER_MORE_RECENT, 0);
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_AFTER_FURTHER, 0);
	}
	else
	{
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_AFTER_MORE_RECENT, (m_nRearSonarFarther == 1) ? 0 : 1);
		setAnalogData(PAGE_SETUP_PARK_ASSIST_SET_AFTER_FURTHER, (m_nRearSonarFarther == 1) ? 1 : 0);
	}
	//��������
	if (m_nRadarAlarmVolume == DEFAULT_NORMAL)
		memcpy(szMsg, "--", strlen("--"));
	else
		sprintf(szMsg, "%d", m_nRadarAlarmVolume);

	setAnsiSerialData(PAGE_SETUP_PARK_ASSIST_SET_ALERT_VOLUME_TEXT, (u8*)szMsg, strlen(szMsg));

	setUpdateUI(true);
}
//page
bool CCarInfoToyotaPrado::pages(u32 id, u8 ms, u8 *p, u8 len)
{
	LOGD("[%s] id = [0x%x]", __FUNCTION__, id);

	E_MOUSE_STATUS e = E_MOUSE_STATUS(ms);

	bool bRet = false;
	bRet = mainPage(id, e, p, len);
	if (bRet)
		return true;

	bRet = false;
	bRet = drivingInfoPage(id, e, p, len);
	if (bRet)
		return true;

	bRet = false;
	bRet = parkCarSettingPage(id, e, p, len);
	if (bRet)
		return true;

	return false;
}

bool CCarInfoToyotaPrado::mainPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	

	bool bRet = true;

	switch(id)
	{
	//��ҳ
	case CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_TRAVEL_INFORMATION: //��ʻ��Ϣ��ť
		clickMainPageDrivingInfoPageEntrance(e);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_PARKING_SET://�������ð�ť
		clickMainPageParkCarSettingPageEntrance(e);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

bool CCarInfoToyotaPrado::drivingInfoPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	//��ҳ
	case CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_DRIVING_INFO_BACK:
		clickDrivingInfoPageGoBack(e);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_DRIVING_INFO_CLEAR_DATA:
		clickDrivingInfoPageErase(e);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

bool CCarInfoToyotaPrado::parkCarSettingPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	//��ҳ
	case PAGE_SETUP_PARK_ASSIST_SET_BACK:
		clickParkCarSettingPageGoBack(e);
		break;
	case PAGE_SETUP_PARK_ASSIST_SET_DISPLAY_SWICH_ON:
		clickParkCarSettingPageDisplaySwitchOpen(e);
		break;
	case PAGE_SETUP_PARK_ASSIST_SET_DISPLAY_WWICH_OFF:
		clickParkCarSettingPageDisplaySwitchClose(e);
		break;
	case PAGE_SETUP_PARK_ASSIST_SET_DISPLAY_SWICH_ON_OFF:
		clickParkCarSettingPageDisplaySwitchCloseAndOpen(e,p[0]);
		break;
	case PAGE_SETUP_PARK_ASSIST_SET_BEFORE_FURTHER:
		clickParkCarSettingPageFrontSonarFar(e);
		break;
	case PAGE_SETUP_PARK_ASSIST_SET_BEFORE_MORE_RECENT:
		clickParkCarSettingPageFrontSonarClose(e);
		break;
	case PAGE_SETUP_PARK_ASSIST_SET_AFTER_FURTHER:
		clickParkCarSettingPageRearSonarFar(e);
		break;
	case PAGE_SETUP_PARK_ASSIST_SET_AFTER_MORE_RECENT:
		clickParkCarSettingPageRearSonarClose(e);
		break;
	case PAGE_SETUP_PARK_ASSIST_SET_ALERT_VOLUME_UP:
		clickParkCarSettingPageAlarmVolumeUp(e);
		break;
	case PAGE_SETUP_PARK_ASSIST_SET_ALERT_VOLUME_DOWN:
		clickParkCarSettingPageAlarmVolumeDown(e);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

//
void CCarInfoToyotaPrado::clickMainPageDrivingInfoPageEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			LOGD("[%s]", __FUNCTION__);
			setPage(TOYOTA_PRADO_DRIVING_INFO_PAGE);
		}
		break;
	default:
		break;
	}
}

void CCarInfoToyotaPrado::clickMainPageParkCarSettingPageEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setPage(TOYOTA_PRADO_PARKING_SETTING_PAGE);
		}
		break;
	default:
		break;
	}
}
//
void CCarInfoToyotaPrado::clickDrivingInfoPageGoBack(E_MOUSE_STATUS e)
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

void CCarInfoToyotaPrado::clickDrivingInfoPageErase(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			memset(m_nszAverageOilConsumeHistory, 0, sizeof(m_nszAverageOilConsumeHistory));

		/*	int i = 0;
			for (i = 0; i < 15; i++)
			{
				m_nszAverageOilConsumeHistory[i] = 25;
			}*/
			updateAverageOilConsumeHistory();
		}
		break;
	default:
		break;
	}
}

void CCarInfoToyotaPrado::clickParkCarSettingPageGoBack(E_MOUSE_STATUS e)
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
//
void CCarInfoToyotaPrado::clickParkCarSettingPageDisplaySwitchOpen(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setToHalDisplaySwitch(1);
		}
		break;
	default:
		break;
	}
}

void CCarInfoToyotaPrado::clickParkCarSettingPageDisplaySwitchClose(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setToHalDisplaySwitch(0);
		}
		break;
	default:
		break;
	}
}

void CCarInfoToyotaPrado::clickParkCarSettingPageDisplaySwitchCloseAndOpen(E_MOUSE_STATUS e,u8 p)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if(p == 0){
				setToHalDisplaySwitch(0);
			}
			else if(p == 1){
				setToHalDisplaySwitch(1);
			}
		}
		break;
	default:
		break;
	}

}

void CCarInfoToyotaPrado::clickParkCarSettingPageFrontSonarClose(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setToHalFrontSonarDistance(0);
		}
		break;
	default:
		break;
	}
}

void CCarInfoToyotaPrado::clickParkCarSettingPageFrontSonarFar(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setToHalFrontSonarDistance(1);
		}
		break;
	default:
		break;
	}
}

void CCarInfoToyotaPrado::clickParkCarSettingPageRearSonarClose(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setToHalRearSonarDistance(0);
		}
		break;
	default:
		break;
	}
}

void CCarInfoToyotaPrado::clickParkCarSettingPageRearSonarFar(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setToHalRearSonarDistance(1);
		}
		break;
	default:
		break;
	}
}

void CCarInfoToyotaPrado::clickParkCarSettingPageAlarmVolumeUp(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if (m_nRadarAlarmVolume == DEFAULT_NORMAL)
				return;

			m_nRadarAlarmVolume += 1;
			m_nRadarAlarmVolume = (m_nRadarAlarmVolume > 5) ? 5 : m_nRadarAlarmVolume;
			
			if (m_nRadarAlarmVolume >= 1 && m_nRadarAlarmVolume <= 5)
				setToHalAlarmVolume(m_nRadarAlarmVolume - 1);
		}
		break;
	default:
		break;
	}
}

void CCarInfoToyotaPrado::clickParkCarSettingPageAlarmVolumeDown(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if (m_nRadarAlarmVolume == DEFAULT_NORMAL)
				return;

			m_nRadarAlarmVolume -= 1;
			m_nRadarAlarmVolume = (m_nRadarAlarmVolume <= 0) ? 1 : m_nRadarAlarmVolume;
			
			if (m_nRadarAlarmVolume >= 1 && m_nRadarAlarmVolume <= 5)
				setToHalAlarmVolume(m_nRadarAlarmVolume - 1);
		}
		break;
	default:
		break;
	}
}
//

const char* CCarInfoToyotaPrado::getCarGearString(int id)
{
	const char *pRet = "N/A";

	const char* szMap[9] = {"P", "R", "N", "D", "S1", "S2", "S3", "S4", "S5"};
	
	if (id >= 0 && id < 9)
	{
		pRet = szMap[id];
	}

	LOGD("[%s] [%s]", __FUNCTION__, pRet);

	return pRet;
}

const char* CCarInfoToyotaPrado::getOilConsumeUnitString(int id)
{
	const char *pRet = "N/A";

	const char* szMap[2] = {"L/100km", "km/L"};

	if (id >= 0 && id < 2)
	{
		pRet = szMap[id];
	}

	LOGD("[%s] [%s]", __FUNCTION__, pRet);

	return pRet;
}
//
void CCarInfoToyotaPrado::setAverageOilconsumeUpdateTimer(void)
{
	DeleteTimer(EXTCAR_TIMER_ID_TOYOTA_PRADO_AVERAGE_OIL_CONSUME_UPDATE);	
	SetTimer(EXTCAR_TIMER_TIME_TOYOTA_PRADO_AVERAGE_OIL_CONSUME_UPDATE, 1, EXTCAR_TIMER_ID_TOYOTA_PRADO_AVERAGE_OIL_CONSUME_UPDATE);
}

void CCarInfoToyotaPrado::killAverageOilconsumeUpdateTimer(void)
{
	DeleteTimer(EXTCAR_TIMER_ID_TOYOTA_PRADO_AVERAGE_OIL_CONSUME_UPDATE);	
}

void CCarInfoToyotaPrado::setInstantOilconsumeCountTimer(void)
{
	DeleteTimer(EXTCAR_TIMER_ID_TOYOTA_PRADO_INSTANT_OIL_CONSUME_COUNT);	
	SetTimer(EXTCAR_TIMER_TIME_TOYOTA_PRADO_INSTANT_OIL_CONSUME_COUNT, 1, EXTCAR_TIMER_ID_TOYOTA_PRADO_INSTANT_OIL_CONSUME_COUNT);
}

void CCarInfoToyotaPrado::killInstantOilconsumeCountTimer(void)
{
	DeleteTimer(EXTCAR_TIMER_ID_TOYOTA_PRADO_INSTANT_OIL_CONSUME_COUNT);	
}

/*
int CCarInfoToyotaPrado::radar_signal_LPC2JNI(int s, int r)
{
	int nRet = 0;
	if (s == 0xFF)
		nRet = 0;
	else
	{
		nRet = s + 1;
		nRet = r - nRet + 1;
	}

	return nRet;
}
*/

int CCarInfoToyotaPrado::radar_signal_LPC2JNI(int s, int r)
{
	int nRet = 0;
	if (s == 0x00)
	{
		nRet = 0;
	}
	else if(s == 0x01)
	{
		nRet = 1;
	}
	else if(s == 0x05)
	{
		nRet = 2;
	}
	else if(s == 0x06)
	{
		nRet = 3;
	}
	else if(s == 0x07)
	{
		nRet = 4;
	}

	return nRet;
}

//
void CCarInfoToyotaPrado::setToHalAlarmVolume(u8 p)
{
	u8 szMsg[3] = {0xB1, 0x80, p};

	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoToyotaPrado::setToHalDisplaySwitch(u8 p)
{
	p = 0x10 | p;

	u8 szMsg[3] = {0xB1, 0x80, p};

	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoToyotaPrado::setToHalFrontSonarDistance(u8 p)
{
	p = 0x20 | p;

	u8 szMsg[3] = {0xB1, 0x80, p};

	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}

void CCarInfoToyotaPrado::setToHalRearSonarDistance(u8 p)
{
	p = 0x40 | p;

	u8 szMsg[3] = {0xB1, 0x80, p};

	makeAndSendMessageToHal(HAL_ID_EXTCAR, szMsg, sizeof(szMsg));
}
//
void CCarInfoToyotaPrado::setToHalAudioCtrl(u8 *p, int len)
{
	p[1] = 0x82;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, p, len);
}

void CCarInfoToyotaPrado::setToHalScreenCoordinates(u8 *p, int nLen)
{
	u8 buf[6] = {0xB1,0x83,0x00,0x00,0x00,0x00};
	buf[2]=p[0];
	buf[3]=p[1];
	buf[4]=p[2];
	buf[5]=p[3];
	makeAndSendMessageToHal(HAL_ID_EXTCAR, buf, sizeof(buf));

	LOGD("extcarToHal,Prado_ScreenCoordinates:x=%d,y=%d",p[0]+p[1]*256,p[2]+p[3]*256);
}

void CCarInfoToyotaPrado::setToHalExitBackcar(u8 param)
{
	u8 buf[3] = {0xB1,0x84,0x00};
	buf[2] = param;
	makeAndSendMessageToHal(HAL_ID_EXTCAR, buf,sizeof(buf));
	LOGD("extcarToHal_Notify_Prado_KeyInfo keyvale=%x",param);
}

void CCarInfoToyotaPrado::DisplaySwitchCloseAndOpenButton(u8 param)
{
	if(param == 1 || param == 0)
		setDigitalData(PAGE_SETUP_PARK_ASSIST_SET_DISPLAY_SWICH_ON_OFF, param);
}

