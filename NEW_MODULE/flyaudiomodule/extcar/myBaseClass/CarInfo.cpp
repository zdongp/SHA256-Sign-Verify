#include "CarInfo.h"

#include "stringID.h"
#include "pageID.h"
#include "controlID.h"

#include "flyaudioObject/FlyObject.cpp"
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

extern moduleid_t locale_module_mid(void);

CCarInfo::CCarInfo(void)
{
}

CCarInfo::~CCarInfo(void)
{
}

void CCarInfo::initCarParam(void)
{
	//��
	m_eCarDoorLF = CAR_DOOR_UNKNOW;//��ǰ��
	m_eCarDoorRF = CAR_DOOR_UNKNOW;//
	m_eCarDoorLR = CAR_DOOR_UNKNOW;//�����
	m_eCarDoorRR = CAR_DOOR_UNKNOW;//
	m_eCarDoorEngine = CAR_DOOR_UNKNOW;//�����
	m_eCarDoorBack = CAR_DOOR_UNKNOW;//����
	m_eCarWindowBack = CAR_WINDOW_UNKNOW;
	//��
	m_eHandLock = HAND_LOCK_UNKNOW;//��ɲ
	m_eSafeBelt = SAFE_BELT_UNKNOW;//��ȫ��
	m_eRainWiper = RAIN_WIPER_UNKNOW;
	m_eFootLock = FOOT_LOCK_UNKNOW;
	//����
	int m_nCarSpeed = DEFAULT_NORMAL;
	//���
	m_nMileageHaveRun = DEFAULT_NORMAL;//�����
	m_nMileageCanRun = DEFAULT_NORMAL;//ʣ�����
	//��
	m_nAverageOilConsume = DEFAULT_NORMAL;//ƽ���ͺ�
	m_nOilRemain = DEFAULT_NORMAL;
	m_nOilConsumeUnit = DEFAULT_NORMAL;
	//�¶�
	m_nDegreeOutdoor = DEFAULT_OUTDOOR_DEGREE;//�����¶�
	//��λ
	m_nCarGear = DEFAULT_NORMAL;

	//����
	m_bOilNeedToAlarm = false;
	m_bOilAlarmNeedToSend = true;
	m_bVoiceAlarmEnable = false;
	m_bVoiceAlarmFirstTimeAfterSystemStart = true;
	
}

void CCarInfo::initCarUI(void)
{
	updateCarDoor();
	updateHandLock();
	updateSafeBelt();
	updateRainWiper();
	updateFootLock();
	updateCarSpeed();
	updateMileageHaveRun();
	updateMileageCanRun();
	updateAverageOilConsume();
	updateOilRemain();
	updateOutDoorTemperature();
	updateCarGear();
}

void CCarInfo::runCarInfo(void)
{

}

void CCarInfo::initCarInfo(void)
{
	initCarParam();
	initCarUI();
}

void CCarInfo::AccOffinitCarInfo(void)
{
}

void CCarInfo::analyseCarInfo(u8 *p, int len)
{
	LOGD("[%s] ", __FUNCTION__);
}

bool CCarInfo::pages(u32 id, u8 ms, u8 *p, u8 len)
{
	return false;
}

int CCarInfo::updateCarDoor(int nFrom)
{
	LOGD("[%s] updateCarDoor nFrom = [%d]", "430", nFrom);
	
	int nNeedPlayAudioTimes = 0;	
	int nCarDoorOpenNum = 0;
	int nSide = 0;
	
	if (m_eCarDoorLF == CAR_DOOR_OPEN)
	{
		nSide = 1;
		nCarDoorOpenNum++;
	}
	if (m_eCarDoorLR == CAR_DOOR_OPEN)
	{
		nSide = 2;
		nCarDoorOpenNum++;
	}
	if (m_eCarDoorRF == CAR_DOOR_OPEN)
	{
		nSide = 4;
		nCarDoorOpenNum++;
	}
	if (m_eCarDoorRR == CAR_DOOR_OPEN)
	{
		nSide = 8;
		nCarDoorOpenNum++;
	}

	if (nCarDoorOpenNum > 1)//�������
	{
		nNeedPlayAudioTimes++;
		needToAlarm(CARINFO_ALARM_SOUND_SEVERAL_DOOR_OPEN);
	}
	else if (nCarDoorOpenNum == 1)
	{
		if (m_eCarDoorLF == CAR_DOOR_OPEN)
		{
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_LEFT_FORWARD_DOOR_OPEN);
		}
		else if (m_eCarDoorRF == CAR_DOOR_OPEN)
		{
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_RIGHT_FORWARD_DOOR_OPEN);
		}
		else if (m_eCarDoorLR == CAR_DOOR_OPEN)
		{
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_LEFT_REAR_DOOR_OPEN);
		}
		else if (m_eCarDoorRR == CAR_DOOR_OPEN)
		{
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_RIGHT_REAR_DOOR_OPEN);
		}
	}

	//����
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LEFT_UP, (m_eCarDoorLF == CAR_DOOR_OPEN));
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_RIGHT_UP, (m_eCarDoorRF == CAR_DOOR_OPEN));
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LEFT_DOWN, (m_eCarDoorLR == CAR_DOOR_OPEN));
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_RIGHT_DOWN, (m_eCarDoorRR == CAR_DOOR_OPEN));

	//����
	if (m_eCarDoorBack == CAR_DOOR_OPEN)
	{
		nSide = 32;
		if (1 == nNeedPlayAudioTimes)
		{
			DeleteTimer(EXTCAR_TIMER_ID_PLAY_BACK_DOOR_AUDIO);	
			SetTimer(PLAY_ONE_AUDIO_FILE_NEED_TIME * 1000, 1, EXTCAR_TIMER_ID_PLAY_BACK_DOOR_AUDIO);
			nNeedPlayAudioTimes++;
		}
		else
		{
			needToAlarm(CARINFO_ALARM_SOUND_BACK_DOOR_OPEN);
			nNeedPlayAudioTimes++;
		}

		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_TXT,STRINGID_CAR_INFO_OPEN);
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_IAMGE, 1);

		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK_TXT,STRINGID_CAR_INFO_OPEN);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK, 1);
	}
	else if (m_eCarDoorBack == CAR_DOOR_CLOSE)
	{
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_TXT,STRINGID_CAR_INFO_CLOSE);
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_IAMGE, 0);

		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK_TXT,STRINGID_CAR_INFO_CLOSE);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK, 0);
	}
	else if (m_eCarDoorBack == CAR_DOOR_UNKNOW)
	{
		u8 ansiBuf[10] = {0};
		sprintf((char*)ansiBuf,"%s", "N/A");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_TXT, ansiBuf, strlen((char*)ansiBuf));
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK_TXT, ansiBuf, strlen((char*)ansiBuf));

		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_IAMGE, 0);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK, 0);
	}

	g_clsExtcar.sendToFlyJniSdk_DoorInfo((char)nSide);
	
	return nNeedPlayAudioTimes;
}

int CCarInfo::updateSafeBelt(int nFrom)
{
	LOGD("[%s] updateSafeBelt nFrom = [%d]", "430", nFrom);
	
	int nNeedPlayAudioTimes = 0;

	if (m_eSafeBelt == SAFE_BELT_OPEN)
	{
		nNeedPlayAudioTimes++;
		needToAlarm(CARINFO_ALARM_SOUND_SAFETY_BELT_NOT_LOCK);
	
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SEAT_BELTS_TXT,STRINGID_CAR_INFO_OPEN);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SEAT_BELTS_IAMGE, 1);

		g_clsExtcar.sendToFlyJniSdk_SafetyBelt(1);
	}
	else if (m_eSafeBelt == SAFE_BELT_CLOSE)
	{
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SEAT_BELTS_TXT, STRINGID_CAR_INFO_CLOSE);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SEAT_BELTS_IAMGE, 0);

		g_clsExtcar.sendToFlyJniSdk_SafetyBelt(0);
	}
	else if (m_eSafeBelt == SAFE_BELT_UNKNOW)
	{
		u8 ansiBuf[10] = {0};
	
		sprintf((char*)ansiBuf,"%s", "N/A");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SEAT_BELTS_TXT, ansiBuf, strlen((char*)ansiBuf));

		g_clsExtcar.sendToFlyJniSdk_SafetyBelt(2);
	}

	return nNeedPlayAudioTimes;
}

int CCarInfo::updateOilRemain(int nFrom)
{
	u8 ansiBuf[64] = {0};
	int nNeedPlayAudioTimes = 0;

	if (m_nOilRemain == DEFAULT_NORMAL)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%dL", m_nOilRemain);

	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REMAINING_TXT, ansiBuf, nAnsiBufLen);

	if (m_bOilNeedToAlarm)
	{
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REMAINING_IAMGE, 1);

		double lfCarSpeed = (double)(m_nCarSpeed / 100.0);

		if (m_bVoiceAlarmEnable && m_bOilAlarmNeedToSend && lfCarSpeed >= 2.0)
		{
			m_bOilAlarmNeedToSend = false;
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_OIL_BELOW_SAFETY_LINE);
		}
	}
	else
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REMAINING_IAMGE, 0);

	return nNeedPlayAudioTimes;
}

//void CCarInfo::updateOutDoorTemperature()
//{
//	u8 ansiBuf[64] = {0};
//	double lfDegreeOutDoor = (double)(m_nDegreeOutdoor / 10.0);
//
//	if (m_nDegreeOutdoor == DEFAULT_OUTDOOR_DEGREE)
//		sprintf((char*)ansiBuf,"%s", "N/A");
//	else
//		sprintf((char*)ansiBuf,"%.1lf癈", lfDegreeOutDoor);
//
//	int nAnsiBufLen = strlen((char*)ansiBuf);
//	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_TXT, ansiBuf, nAnsiBufLen);
//
//	if ((lfDegreeOutDoor >= 40.0 || lfDegreeOutDoor <= -10.0) && m_nDegreeOutdoor != DEFAULT_OUTDOOR_DEGREE)
//		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_IAMGE, 1);
//	else
//		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_IAMGE, 0);
//}

void CCarInfo::updateOutDoorTemperature()
{
	double lfDegreeOutDoor = (double)(m_nDegreeOutdoor / 10.0);
	u8 ansiBuf[64] = {0};

	g_clsExtcar.sendToFlyJniSdk_DegreeOfCarGround(m_nDegreeOutdoor);
	
	if (m_nDegreeOutdoor == DEFAULT_OUTDOOR_DEGREE)
	{
	
		sprintf((char*)ansiBuf,"%s", "N/A");
		int nAnsiBufLen = strlen((char*)ansiBuf);
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_TXT, ansiBuf, nAnsiBufLen);
	}
	else
	{
		wchar_t wcharBuf[10] = L"℃";
		u8 unicBuf[32] = {0};

		sprintf((char*)ansiBuf,"%.1lf", lfDegreeOutDoor);
		u32 dwUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicBuf);
		memcpy((char*)unicBuf + dwUnicodeBufLen * 2, (char*)wcharBuf, 2);
		
		//outPutLog(__FUNCTION__, "lfDegreeOutDoor", (u8*)unicBuf, 64);

		setSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_TXT, (u8*)unicBuf, dwUnicodeBufLen * 2 + 2);
	}

	if ((lfDegreeOutDoor >= 40.0 || lfDegreeOutDoor <= -10.0) && m_nDegreeOutdoor != DEFAULT_OUTDOOR_DEGREE)
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_IAMGE, 1);
	else
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_IAMGE, 0);
}

void CCarInfo::updateMileageHaveRun()
{
	u8 ansiBuf[64] = {0};

	if (m_nMileageHaveRun == DEFAULT_NORMAL)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%dkm", m_nMileageHaveRun);

	int nAnsiBufLen = strlen((char*)ansiBuf);

	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_MILEAGE_TXT, ansiBuf, nAnsiBufLen);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_DRIVING_INFO_MILEAGE, ansiBuf, nAnsiBufLen);

	setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_MILEAGE_IAMGE, 0);
}

void CCarInfo::updateMileageCanRun()
{
	u8 ansiBuf[64] = {0};

	if (m_nMileageCanRun == DEFAULT_NORMAL){
		sprintf((char*)ansiBuf,"%s", "N/A");
		g_clsExtcar.sendToFlyJniSdk_MileageCanRun(-1);
	}
	else{
		sprintf((char*)ansiBuf,"%dkm", m_nMileageCanRun);
		g_clsExtcar.sendToFlyJniSdk_MileageCanRun(m_nMileageCanRun);
	}

	int nAnsiBufLen = strlen((char*)ansiBuf);

	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_RUNNING_MILEAGE_TEXT, ansiBuf, nAnsiBufLen);
}

void CCarInfo::updateAverageOilConsume(void)
{
	u8 ansiBuf[64] = {0};

	if (m_nAverageOilConsume == DEFAULT_NORMAL){
		sprintf((char*)ansiBuf,"%s", "N/A");
		g_clsExtcar.sendToFlyJniSdk_AvgOilWearInfo(0,0xFF);
	}
	else
	{
		if (m_nOilConsumeUnit == 1){
			sprintf((char*)ansiBuf,"%.1fL/100km", m_nAverageOilConsume / 10.0);
			g_clsExtcar.sendToFlyJniSdk_AvgOilWearInfo(0,m_nAverageOilConsume*10);
		}
		else if (m_nOilConsumeUnit == 0){
			sprintf((char*)ansiBuf,"%.1fkm/L", m_nAverageOilConsume / 10.0);
			g_clsExtcar.sendToFlyJniSdk_AvgOilWearInfo(1,m_nAverageOilConsume*10);
		}
	}

	int nAnsiBufLen = strlen((char*)ansiBuf);

	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_AVERAGE_FUEL_CONSUMPTION_TEXT, ansiBuf, nAnsiBufLen);
}

int CCarInfo::updateHandLock(int nFrom)
{
	LOGD("[%s] updateHandLock nFrom = [%d]", "430", nFrom);
	
	int nNeedPlayAudioTimes = 0;

	if (m_eHandLock == HAND_LOCK_UP)
	{
		nNeedPlayAudioTimes++;	
		needToAlarm(CARINFO_ALARM_SOUND_HAND_LOCK_LOCK);
		
	    setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_BRAKE_TXT, STRINGID_CAR_INFO_HAND_LOCKER_CLOSE);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_BRAKE_IAMGE, 1);
	}
	else if(m_eHandLock == HAND_LOCK_DOWN)
	{
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_BRAKE_TXT, STRINGID_CAR_INFO_HAND_LOCKER_OPEN);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_BRAKE_IAMGE, 0);
	}
	else if(m_eHandLock == HAND_LOCK_UNKNOW)
	{
		u8 ansiBuf[10] = {0};
		
		sprintf((char*)ansiBuf,"%s", "N/A");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_BRAKE_TXT, ansiBuf, strlen((char*)ansiBuf));
	}

	g_clsExtcar.sendToFlyJniSdk_HandLocker((u8)m_eHandLock);

	return nNeedPlayAudioTimes;
}

void CCarInfo::updateRainWiper(void)
{
	//��� ��
	if (m_eRainWiper == RAIN_WIPER_OPEN)
	{
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_WIPER_TXT,STRINGID_CAR_INFO_OPEN);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_WIPER_IMAGE, 1);
	}
	else if (m_eRainWiper == RAIN_WIPER_CLOSE)
	{
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_WIPER_TXT,STRINGID_CAR_INFO_CLOSE);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_WIPER_IMAGE, 0);
	}
	else if (m_eRainWiper == RAIN_WIPER_UNKNOW)
	{
		u8 ansiBuf[10] = {0};

		sprintf((char*)ansiBuf,"%s", "N/A");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_WIPER_TXT, ansiBuf, strlen((char*)ansiBuf));
	}
}

void CCarInfo::updateEngineDoor(void)
{
	//ǰ����ǿ�
	if (m_eCarDoorEngine == CAR_DOOR_OPEN){
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_PROTEGULUM, 1);
		g_clsExtcar.sendToFlyJniSdk_EngineDoorInfo(1);
	}
	else if (m_eCarDoorEngine == CAR_DOOR_CLOSE){
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_PROTEGULUM, 0);
		g_clsExtcar.sendToFlyJniSdk_EngineDoorInfo(0);
	}
}

void CCarInfo::updateCarWindow()
{
	if (m_eCarWindowBack == CAR_WINDOW_OPEN)
	{
		setVisible(CONTROLIDTRAVEL_CARINFO_DOLD_PRADO_AFTER_CAR_WINDOW, 1);
	}
	else if (m_eCarWindowBack == CAR_WINDOW_CLOSE)
	{
		setVisible(CONTROLIDTRAVEL_CARINFO_DOLD_PRADO_AFTER_CAR_WINDOW, 0);
	}
}

void CCarInfo::updateFootLock(void)
{
	if (m_eFootLock == FOOT_LOCK_OPEN)
	{
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_FOOT_BRAKE, 0);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_FOOT_BRAKE_text, STRINGID_CAR_INFO_FOOT_STEP_OUT);
	}
	else if (m_eFootLock == FOOT_LOCK_CLOSE)
	{
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_FOOT_BRAKE, 1);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_FOOT_BRAKE_text, STRINGID_CAR_INFO_FOOT_STEP_ON);
	}
	else if (m_eFootLock == FOOT_LOCK_UNKNOW)
	{
		u8 ansiBuf[10] = {0};

		sprintf((char*)ansiBuf,"%s", "N/A");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_FOOT_BRAKE_text, ansiBuf, strlen((char*)ansiBuf));
	}

	g_clsExtcar.sendToFlyJniSdk_FootLockState((char)m_eFootLock);
}

void CCarInfo::updateCarGear()
{
	/*setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, strlen(( char*)ansiBuf));
	setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,uGearStage);*/

	switch(m_nCarGear)
	{
	case 0x00://P
		break;
	case 0x01://R
		break;
	case 0x02://N
		break;
	case 0x03://D
		break;
	case 0x04://S1
		break;
	case 0x05://S2
		break;
	case 0x06://S3
		break;
	case 0x07://S4
		break;
	case 0x08://S5
		break;
	}
}

void CCarInfo::updateCarSpeed(void)
 {
	u8 ansiBuf[64] = {0};
	static bool bNeedNotice = false;
	double lfCarSpeed = (double)(m_nCarSpeed / 100.0);

	if (lfCarSpeed <= 2.0)
		bNeedNotice = true;

	if (m_nCarSpeed == DEFAULT_NORMAL)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%.2lfkm/h",  lfCarSpeed);
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_PER_HOUR_TXT, ansiBuf, nAnsiBufLen);

   if (	   (m_bVoiceAlarmEnable && bNeedNotice && (double)(m_nCarSpeed / 100.0) >= 10.0) 
   		|| (m_bVoiceAlarmFirstTimeAfterSystemStart && m_bVoiceAlarmEnable)
   	)
    {
		m_bVoiceAlarmFirstTimeAfterSystemStart = false;
		bNeedNotice = false;
		DeleteTimer(EXTCAR_TIMER_ID_CAR_SPEED_CHECK);
		SetTimer(200, 1, EXTCAR_TIMER_ID_CAR_SPEED_CHECK);
    }
 }

void CCarInfo::updateAverageOilConsumeHistory(void)
{

}

void CCarInfo::updateAverageOilConsumeHistoryPerMinute(void)
{

}

void CCarInfo::updateInstantOilConsumeCount(void)
{

}


//////////////////////////////////////////////////////////////////////////
void CCarInfo::setPage(u16 id)
{
	LOGD("[%s]", __FUNCTION__);
	u8 szMsg[] = {0x82, 0x00, 0x00};
	memcpy(szMsg + 1, &id, 2);
	makeAndSendMessageToModule(locale_module_mid(),  MODULE_ID_SYSTEM,  szMsg, sizeof(szMsg));
}

void CCarInfo::setPrePage(void)
{
	u8 szMsg[] = {0x83, 0x00};
	makeAndSendMessageToModule(locale_module_mid(),  MODULE_ID_SYSTEM,  szMsg, sizeof(szMsg));
}

void CCarInfo::setNextModule(void)
{
	u8 szMsg[] = {0x81, locale_module_mid()};
	makeAndSendMessageToModule(locale_module_mid(),  MODULE_ID_SYSTEM,  szMsg, sizeof(szMsg));
}

void CCarInfo::setToHalAudioCtrl(u8 *p, int len)
{

}
void CCarInfo::setToHalScreenCoordinates(u8 *p, int len)
{

}

void CCarInfo::setToHalExitBackcar(u8 param)
{

}
