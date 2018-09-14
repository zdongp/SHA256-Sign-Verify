#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "stringID.h"
#include "pageID.h"
#include "controlID.h"
#include "stringID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "moduleParamResponse.h"
#include "otherModuleRequestFunction.h"
#include "timer_interface.h"
#include "moduleParamRequest.h"

extern CCarInfoCarSettingToyota gclsCarInforCarSettings;
extern u8 sTrunkInfor;
extern u8 sDoors;
extern u8 sSelfBelts;
extern u8 sHandBreak;

void halToExtcar_SpeedLockState(u8 state){
	pLocalParam->speedLock = state;
	if (state)
	{
		setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_SPEED_SENSOR_ON, true);
	}
	else
	{
		setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_SPEED_SENSOR_ON, false);
	}
}

void halToExtcar_ShiftLockState(u8 state){
	pLocalParam->shiftLock = state;
	if (state)
	{
		setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_SHIFT_LINKAGE_ON, true);
	}
	else
	{
		setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_SHIFT_LINKAGE_ON, false);
	}
}

void halToExtcar_PModeUnlockState(u8 state){
	pLocalParam->pModeUnlock= state;
	if (state)
	{
		setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_P_GEAR_LINKAGE_ON, true);
	}
	else
	{
		setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_P_GEAR_LINKAGE_ON, false);
	}
}

void halToExtcar_DPressUnlockState(u8 state){
	pLocalParam->dPressUnlock= state;
	if (state)
	{
		setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_TOW_UNLOCKED_ON, true);
	}
	else
	{
		setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_TOW_UNLOCKED_ON, false);
	}
}

void halToExtcar_FeedbackTone(u8 Value){
	pLocalParam->feedbackTone = Value;
}

void halToExtcar_LightSensitivity(u8 Value){

	if (Value == 16)
	{
		pLocalParam->lightSensitivity = 1;
	}
	if (Value == 32)
	{
		pLocalParam->lightSensitivity = 2;
	}
	if (Value == 0)
	{
		pLocalParam->lightSensitivity = 3;
	}
	if (Value == 48)
	{
		pLocalParam->lightSensitivity = 4;
	}
	if (Value == 64)
	{
		pLocalParam->lightSensitivity = 5;
	}

	u8 *pwBuf = (u8*)malloc(STRING_BUF_MAX_LEN);
	memset(pwBuf, 0, STRING_BUF_MAX_LEN);
	sprintf((char*)pwBuf, "%d",pLocalParam->lightSensitivity);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_INFORMATION_CAR_SET_LIGHT_SENSITIVITY_TEXT,pwBuf,strlen((char *)pwBuf));
	free(pwBuf);

}

void halToExtcar_LampAutoOFFTime(u8 Value){
	pLocalParam->lampAutoOFFTime = Value;
}

void halToExtcar_LightRuningState(u8 Value){
	pLocalParam->isLightRuning = Value;
}

void halToExtcar_WheelPressure(unsigned char *buf,int len){
	pLocalParam->isWarn = buf[2];

	pLocalParam->rFrontPressure = buf[3];
	pLocalParam->rRearPressure = buf[4];
	pLocalParam->lFrontPressure = buf[5];
	pLocalParam->lRearPressure = buf[6];
}

void halToExtcar_AverageSpeed(u16 Value){
	pLocalParam->avgSpeed = Value;
	u8 *pwBuf = (u8*)malloc(STRING_BUF_MAX_LEN);
	memset(pwBuf, 0, STRING_BUF_MAX_LEN);
	sprintf((char*)pwBuf, "%d km/h",  Value);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_INFORMATION_AVERAGE_SPEED,pwBuf,strlen((char *)pwBuf));
	free(pwBuf);
}

void halToExtcar_SteerTime(u8 hour,u8 minute){
	pLocalParam->steerTimeH = hour;
	pLocalParam->steerTimeM= minute;
	u8 *pwBuf = (u8*)malloc(STRING_BUF_MAX_LEN);
	memset(pwBuf, 0, STRING_BUF_MAX_LEN);
	sprintf((char*)pwBuf, "%02d:%02d",hour,minute);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_INFORMATION_TRAVEL_TIME,pwBuf,strlen((char *)pwBuf));
	free(pwBuf);
}

void halToExtcar_SustainMileage(int Value){
	u8 ansiBuf[128];
	int nDrivingDistance = Value;
	memset(ansiBuf, 0, sizeof(ansiBuf));
	if (nDrivingDistance < 0)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%d km", nDrivingDistance);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);

	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_INFORMATION_MILEAGE,ansiBuf,nAnsiBufLen);
}

void halToExtcar_CurOilWear(unsigned char *buf,int len){

	LOGD("kmr oil buf[0] = %02X, buf[1] = %02X, buf[2] = %02X ", buf[0], buf[1], buf[2]);
	if(buf==NULL || len <=0)
		return;

	float Value = 0;
	float Front = buf[0];
	float Rear = buf[1] ;

	if (Rear/10 < 1)
	{
		Value = Front + Rear/10;
	}
	else if (Rear/100 < 1)
	{
		Value = Front + Rear/100;
	}
	else if (Rear/1000 < 1)
	{
		Value = Front + Rear/1000;
	}

	pLocalParam->curOilWear = Value;

	int t = buf[2];
	if (t >= 0 && t <= 30)
	{
		pLocalParam->oilWearCell = buf[2];//������
		setAnalogData(CONTROLIDTRAVEL_INFORMATION_CURRENT_GAUGE,(int)(buf[2]));
	}


	u8 *pwBuf = (u8*)malloc(STRING_BUF_MAX_LEN);
	memset(pwBuf, 0, STRING_BUF_MAX_LEN);
	sprintf((char*)pwBuf, "%3.1f L/100km",Value);
	LOGD("The oil is %s ", pwBuf);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_INFORMATION_OIL_CONSUMPTION,pwBuf,strlen((char *)pwBuf));
	free(pwBuf);

}

void halToExtcar_History(unsigned char *buf,int len){
	if(buf==NULL || len <=0)
		return;

	float Value = 0;
	float Front = buf[0];
	float Rear = buf[1] ;

	if (Rear/10 < 1)
	{
		Value = Front + Rear/10;
	}
	else if (Rear/100 < 1)
	{
		Value = Front + Rear/100;
	}
	else if (Rear/1000 < 1)
	{
		Value = Front + Rear/1000;
	}

	//m_pTheApp->m_pCenterParam->m_CarHistory.fHistory5 = m_pTheApp->m_pCenterParam->m_CarHistory.fHistory4;
	//m_pTheApp->m_pCenterParam->m_CarHistory.fHistory4 = m_pTheApp->m_pCenterParam->m_CarHistory.fHistory3;
	//m_pTheApp->m_pCenterParam->m_CarHistory.fHistory3 = m_pTheApp->m_pCenterParam->m_CarHistory.fHistory2;
	//m_pTheApp->m_pCenterParam->m_CarHistory.fHistory2 = m_pTheApp->m_pCenterParam->m_CarHistory.fHistory1;
	//m_pTheApp->m_pCenterParam->m_CarHistory.fHistory1 = m_pTheApp->m_pCenterParam->m_CarHistory.fHistoryCur;
	pLocalParam->carHistory.fHistoryCur=Value;
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_HISTORICAL_RECORD,(int)(Value));
}

void halToExtcar_IsShowSteerInfo(u8 state){
	pLocalParam->isShowSteerInfo = state;

	LOGD("[dyb] halToExtcar_IsShowSteerInfo: state = %d", state);
	
	if (state)
	{
		extcarToApp_SetExtcarMenuEnable();
		recoverLastSet();
	}
	else
	{
		extcarToApp_SetExtcarMenuDisable();
	}
}

void halToExtcar_CarLockState(u8 state){
	pLocalParam->carLock = state;
	if (state)
	{
		setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET2_KEY_START_ON, true);
	}
	else
	{
		setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET2_KEY_START_ON, false);
	}
}


void halToExtcar_AutomaticallyAcOrEffectiveVentilationModel(u8 state)
{
	switch(state)
	{
		case 0xC0:
		{
			setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_ZIDON, 1);
			setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_YOUXIAO, 1);
		}
		break;
		case 0x80:
		{
			setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_ZIDON, 1);
			setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_YOUXIAO, 0);
		}
		break;
		case 0x40:
		{
			setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_ZIDON, 0);
			setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_YOUXIAO, 1);

		}
		break;
		default:
		{
			setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_ZIDON, 0);
			setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_YOUXIAO, 0);
		}
		break;
	}

}


/************************************************************************/
/*								������									*/
/************************************************************************/


void analyseHalMessage_CarType_Camry(unsigned char resCmd, unsigned char *param, unsigned char len){
	switch(resCmd){
		case 0x60:										//���ٸ�Ӧ�����Զ���
		{
			halToExtcar_SpeedLockState(param[0]);
		}
		break;

		case 0x61:										//�������������Զ���
		{
			halToExtcar_ShiftLockState(param[0]);
		}
		break;

		case 0x62:										//P����������
		{
			halToExtcar_PModeUnlockState(param[0]);
		}
		break;

		case 0x63:										//���°�ť���ν���
		{
			halToExtcar_DPressUnlockState(param[0]);
		}
		break;

		case 0x64:										//Lock/Unlock feedback -tone
		{
			halToExtcar_FeedbackTone(param[0]);
		}
		break;

		case 0x65:										//���Ƶ��ڰ�ť������
		{
			halToExtcar_LightSensitivity(param[0]);
		}
		break;

		case 0x66:										//Headlamps auto �Coff timer
		{
			halToExtcar_LampAutoOFFTime(param[0]);
		}
		break;

		case 0x67:										//Daytime running lights
		{
			halToExtcar_LightRuningState(param[0]);
		}
		break;

		case 0x68:										//��ȡ̥ѹ
		{
			halToExtcar_WheelPressure(param,8);
		}

		break;
		case 0x69:										//ƽ����
		{
			u16 Value=param[0]+ (param[1]<<8);
			halToExtcar_AverageSpeed(Value);
			AverageSpeed_Displaying_NewPage(Value);
		}
		break;
		case 0x6a:										//��ʻʱ��
		{
			halToExtcar_SteerTime(param[0],param[1]);
			TravelTime_Displaying_NewPage(param[0],param[1]);
		}
		break;

		case 0x6b:										//��������ʻ�����
		{
			u16 Value=param[0]+ (param[1]<<8);
			pLocalParam->SurplusDistance = (int)Value;
			halToExtcar_SustainMileage(Value);
			RunningMileage_Displaying_NewPage(Value);
		}
		break;

		case 0x6c:										//��ȡ�ͺĺ��ͺĸ���
		{
			LOGD("[%s] THE OIL 6C COMING",TOYOTA);
			halToExtcar_CurOilWear(param,3);
			CurOilConsumption_Displaying_NewPage(param,3);
		}
		break;

		case 0x6d:										//��ȡ��ʷ��¼
		{
			halToExtcar_History(param,2);
			AverageOilConsumption_Displaying_NewPage(param,2);
		}
		break;

		case 0x6e:										//�Ƿ���ʾ�г���Ϣ
		{
			
			halToExtcar_IsShowSteerInfo(param[0]);
		}
		break;

		case 0x6f:
		{
			halToExtcar_CarLockState(param[0]);				//���ܳ����һ������
		}
		break;
		//Q�汾
		case 0x70:
		case 0x71:
		case 0x72:
		case 0xc4://Gears
		case 0xc5://HL_voltage_BrakeState
		case 0x73:
		case 0x74:
		case 0x75:
		case 0x76:
		case 0x77:
		case 0x78:
		case 0x79:
		case 0x7a:
		case 0x7b:
		case 0x7c:
		case 0x7d:
		case 0x7e:
		case 0x83:
		case 0x84:
		case 0x85:
		case 0x86:
		case 0x87:
			analyseHalMessage_toyota_CarInfor(resCmd,param,len);
		break;
		default:break;
	}
}


/************************************************************************/
/*								����˹								*/
/************************************************************************/
void analyseHalMessage_CarType_Focus(unsigned char *param,unsigned char len)
{
	switch(param[0])
	{
		case 0x00:/*�ı�����*/
		case 0x01:/*�ı���һ��*/
		case 0x02:
		case 0x03:
		case 0x04:/*�����ı���ť*/
		case 0x05:
		case 0x06:
		case 0x07:
		case 0x08:/*����ָʾͼ��״̬*/
		case 0x09:/*��ȡSync Media״̬*/
		case 0x10:
		case 0x11:
		case 0x0a:/*��ȡѡ����һ��*/
		case 0x0b:
		case 0x0c:
		case 0x0d://��ȡ����ͨ��״̬
		case 0x0e:/*��ȡsync״̬*/
		case 0x20:// 2 line,setup
		case 0x21:// 3 line,setup
		case 0x22:// 4 line,setup
		case 0x23:// 5 line,setup
		case 0x24://Battery power symbol
		case 0x25://Signal strength symbol
		case 0x26://in Standby,calling status
		case 0x27://steer mouse key
		case 0x30://key
			exterToFOCUS_sync_FromHal(param,len);
		break;
		case 0x42:
		case 0x43:
			FocusBackCar_Radar(param,len);
		break;
		case 0x50:
			exterToAC_fks(param + 1, len - 1);
		break;
		case 0x51:
		case 0x52:
		case 0x53:
		case 0x54:
		case 0x55:
		case 0x56:
		case 0x57:
		case 0x58:
		case 0x59:
		case 0x5a:
			analyseHalMessage_fks_CarInfo(param,len);
		break;
		default:break;
	}
}

void FocusBackCar_Radar(unsigned char * p, int len)
{
	pLocalParam->nCurCmd = p[0];
	switch(p[0])
	{
		case 0x42:
		{
			u8 pos = p[1];
			u32 distance = 0;
			memcpy(&distance, p + 2, 4);
			LOGD("*********focus(backcar radar 0x42) %d %d", pos, distance);
			exterToRadar(pos, distance);
			break;
		}
		case 0x43:
		{
			LOGD("*********focus(backcar radar 0x43) %x ", p[1]);
			exterToRadar(p[1]);
			break;
		}
		default:break;
	}
}


#define SPEED_LIMIT_ALARM		2.0

void process_DrivingDistanceInfo()
{
	u8 ansiBuf[128];
	int nDrivingDistance = pLocalParam->nDrivingDistance;
	memset(ansiBuf, 0, sizeof(ansiBuf));
	if (nDrivingDistance < 0)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%dkm", nDrivingDistance);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);

	LOGD("process_DrivingDistanceInfo %s \n", ansiBuf);
	
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_MILEAGE_TXT, ansiBuf, nAnsiBufLen);
	setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_MILEAGE_IAMGE, 0);

	g_clsExtcar.sendToFlyJniSdk_DrivingDistance(nDrivingDistance);
}

void process_BatteryVoltageInfo()
{
	u8 ansiBuf[128];
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (pLocalParam->nBatteryVoltage < 0)
	{
		sprintf((char*)ansiBuf,"%s", "N/A");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_VOLTAGE_TXT, ansiBuf, strlen((char*)ansiBuf));
		g_clsExtcar.sendToFlyJniSdk_BatteryVoltageInfo(pLocalParam->nBatteryVoltage);
		return ;
	}
	
	double lfBatteryVoltage = (double)(pLocalParam->nBatteryVoltage / 100.0);
	sprintf((char*)ansiBuf,"%.2lfV", lfBatteryVoltage);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_VOLTAGE_TXT, ansiBuf, nAnsiBufLen);
	if (lfBatteryVoltage < 10.0)
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_VOLTAGE_IAMGE, 1);
	else
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_VOLTAGE_IAMGE, 0);

	g_clsExtcar.sendToFlyJniSdk_BatteryVoltageInfo(pLocalParam->nBatteryVoltage);
	exterToSystem_aboutBatteryVoltageInfo(pLocalParam->nBatteryVoltage);
	
}

void process_EngineSpeedInfo()
{
	u8 ansiBuf[128];
	int nEngineSpeed = pLocalParam->nEngineSpeed;
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (nEngineSpeed < 0)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%drpm", nEngineSpeed);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SPEED_TXT, ansiBuf, nAnsiBufLen);
	setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SPEED_IAMGE, 0);

	g_clsExtcar.sendToFlyJniSdk_EngineSpeed(nEngineSpeed);
}

void DoorInfor_New_AlarmVoice(s32 param)
{
	int nNeedPlayAudioTimes = 0;

	u8 nSideDoor = param & 0x0F;  //1111
	if(sDoors != nSideDoor)
	{
		sDoors = nSideDoor;
		static u8 uTemDoor = 0xff;
		//LOGD("DOOR:%c,%c,%c,%c",(nSideDoor & 1),((nSideDoor & 2) >> 1),((nSideDoor & 4) >> 2),((nSideDoor & 8) >> 3));
		if (!(1 == nSideDoor || 2 == nSideDoor || 4 == nSideDoor || 8 == nSideDoor || 0 == nSideDoor))
		{
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_DOOR_OPEN);
		}
		else if(((nSideDoor & 1) == 0) && (((nSideDoor & 2) >> 1) == 0) && (((nSideDoor & 4) >> 2) == 0) && (((nSideDoor & 8) >> 3) == 0))
		{
			if(nSideDoor != uTemDoor){
				needToAlarm(CARINFO_ALARM_SOUND_DOOR_CLOSED);
			}
		}
		else
		{
			if (((nSideDoor & 1) == 1) || (((nSideDoor & 2) >> 1) == 1) || (((nSideDoor & 4) >> 2) == 1) || (((nSideDoor & 8) >> 3) == 1))
			{
				nNeedPlayAudioTimes++;
				needToAlarm(CARINFO_ALARM_SOUND_DOOR_OPEN);
			}
		}
		uTemDoor = nSideDoor;
	}
	
	u8 uTemTrunk = (param & 32) >> 5;
	//LOGD("TRUNK:%c",uTemTrunk);
	if(uTemTrunk != sTrunkInfor)
	{
		sTrunkInfor = uTemTrunk;
		
		if (uTemTrunk == 1)
		{
			if (1 == nNeedPlayAudioTimes)
			{
				nNeedPlayAudioTimes++;
			}
			else
			{
				nNeedPlayAudioTimes++;
				needToAlarm(CARINFO_ALARM_SOUND_TRUNK_OPEN);
			}
		}
		else if(uTemTrunk == 0)
		{
			needToAlarm(CARINFO_ALARM_SOUND_TRUNK_CLOSED);
		}
	}
}

int process_DoorInfo(int nFrom)
{

	if (pLocalParam->m_pCarInfo)
	{
		return pLocalParam->m_pCarInfo->updateCarDoor(nFrom);
	}

	int nNeedPlayAudioTimes = 0;

	u8 ansiBuf[128];
	int t = pLocalParam->nCarDoorStatus;
	if (t < 0)
		return 0;
	else
		LOGD("The t ==================%0X ======", t);

	DoorInfor_New_AlarmVoice(t);

	int nSideDoor = t & 15;  //1111
	double lfInstantSpeed = (double)(pLocalParam->nInstantSpeed / 100.0);

	if(pLocalParam->em_MainDriverPos == MAIN_DRIVER_RIGHT)
	{
		//if(nSideDoor == 1)
			//nSideDoor = 2;
		//else if(nSideDoor == 2)
			//nSideDoor = 1;
		nSideDoor = getMainDriverRightDoorInfo(nSideDoor);
	}
	
	g_clsExtcar.sendToFlyJniSdk_DoorInfo((char)nSideDoor);
	
	//if (lfInstantSpeed > SPEED_LIMIT_ALARM)
	//{
		if (!(1 == nSideDoor || 2 == nSideDoor || 4 == nSideDoor || 8 == nSideDoor || 0 == nSideDoor))//����Ŵ�, ������������
		{
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_SEVERAL_DOOR_OPEN);
		}
		else
		{
			if (nSideDoor & 1)
			{
				nNeedPlayAudioTimes++;
				needToAlarm(CARINFO_ALARM_SOUND_LEFT_FORWARD_DOOR_OPEN);
			}
			if (nSideDoor & 2)
			{
				nNeedPlayAudioTimes++;
				needToAlarm(CARINFO_ALARM_SOUND_RIGHT_FORWARD_DOOR_OPEN);
			}
			if (nSideDoor & 4)
			{
				nNeedPlayAudioTimes++;
				needToAlarm(CARINFO_ALARM_SOUND_LEFT_REAR_DOOR_OPEN);
			}
			if (nSideDoor & 8)
			{
				nNeedPlayAudioTimes++;
				needToAlarm(CARINFO_ALARM_SOUND_RIGHT_REAR_DOOR_OPEN);
			}
		}
	//}
	
	// car door
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LEFT_UP, nSideDoor & 1);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_RIGHT_UP, nSideDoor & 2);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LEFT_DOWN, nSideDoor & 4);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_RIGHT_DOWN, nSideDoor & 8);

	//////////////////////////////////////////////////////////////////////////
	g_clsExtcar.sendToFlyJniSdk_DoorInfo((char)t);
	memset(ansiBuf, 0, sizeof(ansiBuf));
	if (t & 32)//����
	{
		if (1 == nNeedPlayAudioTimes)//up play, so need to settimer and play
		{
			DeleteTimer(EXTCAR_TIMER_ID_PLAY_BACK_DOOR_AUDIO);	
			SetTimer(PLAY_ONE_AUDIO_FILE_NEED_TIME * 1000, 1, EXTCAR_TIMER_ID_PLAY_BACK_DOOR_AUDIO);
			nNeedPlayAudioTimes++;
		}
		else
		{
			//if (lfInstantSpeed > SPEED_LIMIT_ALARM)
			//{
				needToAlarm(CARINFO_ALARM_SOUND_BACK_DOOR_OPEN);
				nNeedPlayAudioTimes++;
			//}
		}
		
		//u8 ansiBufA[4] = {0x00, 0x5f, 0x00, 0x00};
		//setSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_TXT, ansiBufA, 4);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_TXT,STRINGID_CAR_INFO_OPEN);
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_IAMGE, 1);

		//setSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK_TXT, ansiBufA, 4);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK_TXT,STRINGID_CAR_INFO_OPEN);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK, 1);
		
	}
	else
	{
		//u8 ansiBufB[4] = {0x73, 0x51, 0x00, 0x00};
		//setSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_TXT, ansiBufB, 4);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_TXT,STRINGID_CAR_INFO_CLOSE);
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_IAMGE, 0);

		//setSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK_TXT, ansiBufB, 4);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK_TXT,STRINGID_CAR_INFO_CLOSE);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK, 0);
	}
	//////////////////////////////////////////////////////////////////////////

	return nNeedPlayAudioTimes;
}


int process_SafetyBeltInfo(int nFrom)
{

	if (pLocalParam->m_pCarInfo)
	{
		return pLocalParam->m_pCarInfo->updateSafeBelt(nFrom);
	}

	int nNeedPlayAudioTimes = 0;
	double lfInstantSpeed = (double)(pLocalParam->nInstantSpeed / 100.0);

	SafetyBeltInfo_New_AlarmVoice((u8)pLocalParam->eSafetyBeltStatus);
	
	if (pLocalParam->eSafetyBeltStatus == SATETY_BELT_UNLOCKED)
	{
		//if (lfInstantSpeed > SPEED_LIMIT_ALARM)
	//	{
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_SAFETY_BELT_NOT_LOCK);
		//}
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SEAT_BELTS_TXT,STRINGID_CAR_INFO_OPEN);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SEAT_BELTS_IAMGE, 1);
	}
	else if (pLocalParam->eSafetyBeltStatus == SATETY_BELT_LOCKED)
	{
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SEAT_BELTS_TXT, STRINGID_CAR_INFO_CLOSE);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SEAT_BELTS_IAMGE, 0);
	}
	else if (pLocalParam->eSafetyBeltStatus == SATETY_BELT_UNKNOW)
	{
		u8 ansiBuf[10];
		memset(ansiBuf, 0, sizeof(ansiBuf));
		sprintf((char*)ansiBuf,"%s", "N/A");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SEAT_BELTS_TXT, ansiBuf, strlen((char*)ansiBuf));
	}

	g_clsExtcar.sendToFlyJniSdk_SafetyBelt((u8)pLocalParam->eSafetyBeltStatus);
	g_clsExtcar.extcarSendSeatBeltsStatusToSdk(pLocalParam->eSafetyBeltStatus);

	return nNeedPlayAudioTimes;
}

void SafetyBeltInfo_New_AlarmVoice(u8 param)
{
	static u8 uTemSafe = SATETY_BELT_UNKNOW;
	if (param == SATETY_BELT_UNLOCKED)
	{
		needToAlarm(CARINFO_ALARM_SOUND_SEAT_BELT_0FF);
	}
	else if (param == SATETY_BELT_LOCKED)
	{	
		if(param != uTemSafe){
			needToAlarm(CARINFO_ALARM_SOUND_SEAT_BELT_0N);
		}
	}
	else if (param == SATETY_BELT_UNKNOW)
	{
	}
	uTemSafe = param;
}

void HandLockerInfo_New_AlarmVoice(u8 param)
{
	static u8 uTemHandLock = HAND_LOCKER_UNKNOW;
	if (param == HAND_LOCKER_LOCKED)
	{
		needToAlarm(CARINFO_ALARM_SOUND_HAND_BRAKE_0N);
	}
	else if(param == HAND_LOCKER_UNLOCKED)
	{
		if(param != uTemHandLock){
			needToAlarm(CARINFO_ALARM_SOUND_HAND_BRAKE_0FF);
		}
	}
	else if(param == HAND_LOCKER_UNKNOW)
	{
	}
	
	uTemHandLock = param;
}

int process_HandLockerInfo(int nFrom)
{

	if (pLocalParam->m_pCarInfo)
		{
			return pLocalParam->m_pCarInfo->updateHandLock(nFrom);
		}
	
	int nNeedPlayAudioTimes = 0;
	double lfInstantSpeed = (double)(pLocalParam->nInstantSpeed / 100.0);

	HandLockerInfo_New_AlarmVoice((u8)pLocalParam->eHandLockerStatus);

	if (pLocalParam->eHandLockerStatus == HAND_LOCKER_LOCKED /*&& lfInstantSpeed >= SPEED_LIMIT_ALARM*/)
	{
/*
		if (false == pLocalParam->bHandLockAlarmNeedToSend)
		{
			pLocalParam->bHandLockAlarmNeedToSend = true;
		}
		else
		*/
		
			nNeedPlayAudioTimes++;	
			needToAlarm(CARINFO_ALARM_SOUND_HAND_LOCK_LOCK);
		
		
	    setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_BRAKE_TXT, STRINGID_CAR_INFO_HAND_LOCKER_CLOSE);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_BRAKE_IAMGE, 1);
	}
	else if(pLocalParam->eHandLockerStatus == HAND_LOCKER_UNLOCKED)
	{
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_BRAKE_TXT, STRINGID_CAR_INFO_HAND_LOCKER_OPEN);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_BRAKE_IAMGE, 0);
	}
	else if(pLocalParam->eHandLockerStatus == HAND_LOCKER_UNKNOW)
	{
		u8 ansiBuf[10];
		memset(ansiBuf, 0, sizeof(ansiBuf));
		sprintf((char*)ansiBuf,"%s", "N/A");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_BRAKE_TXT, ansiBuf, strlen((char*)ansiBuf));
	}

	g_clsExtcar.extcarSendHandBrakeStatusToSdk(pLocalParam->eHandLockerStatus);
	g_clsExtcar.sendToFlyJniSdk_HandLocker((u8)pLocalParam->eHandLockerStatus);

	return nNeedPlayAudioTimes;
}

void process_GearsInfo()
{
	u8 temT = pLocalParam->eCarGears;
	switch(temT)
	{
		case 0x00://N
		break;
		case 0x01://P
		break;
		case 0x02://R
		break;
		case 0x03://D
		break;
		case 0x04://M
		break;
		case 0xFF://UnKnow
		break;
	}
}

void process_InstantSpeedInfo()
{
	static bool bNeedNotice = false;
	u8 ansiBuf[128];

	double lfInstantSpeed = (double)(pLocalParam->nInstantSpeed / 100.0);

	if (lfInstantSpeed <= 2.0)
		bNeedNotice = true;


	memset(ansiBuf, 0, sizeof(ansiBuf));
	if (pLocalParam->nInstantSpeed < 0)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%.2lfkm/h",  lfInstantSpeed);
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_PER_HOUR_TXT, ansiBuf, nAnsiBufLen);

	g_clsExtcar.sendToFlyJniSdk_InstantSpeed(pLocalParam->nInstantSpeed);
	g_clsExtcar.extcarSendInstantSpeedToSdk(pLocalParam->nInstantSpeed);

	LOGD("(((((((((( bNeedNotice = %d, lfINstantSpeed is %.2lf", (int)bNeedNotice,  lfInstantSpeed);
    if((pLocalParam->bOpenVoiceLater && bNeedNotice && (double)(pLocalParam->nInstantSpeed / 100.0) >= 10.0) ||
   	(pLocalParam->bOpenVoiceAndNeedAlarm && pLocalParam->bOpenVoiceLater))//check hand locked
    {
		LOGD("EXTCAR -> 20############$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
		pLocalParam->bOpenVoiceAndNeedAlarm = false;
		bNeedNotice = false;
		DeleteTimer(EXTCAR_TIMER_ID_CAR_SPEED_CHECK);
		SetTimer(200, 1, EXTCAR_TIMER_ID_CAR_SPEED_CHECK);
	}
	//////////////////////////////////////////////////////////////////////////


}
int process_OilRemindInfo(int nFrom)
{
	u8 ansiBuf[128];
	int nNeedPlayAudioTimes = 0;
	int nOilRemind = pLocalParam->nOilRemind;
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (nOilRemind < 0)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%dL", nOilRemind);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REMAINING_TXT, ansiBuf, nAnsiBufLen);

	 if (pLocalParam->bOilWarning)
 	{
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REMAINING_IAMGE, 1);

		LOGI("process_OilRemindInfo : pLocalParam->bOilAlarmNeedToSend = %d, nFrom = %d",  pLocalParam->bOilAlarmNeedToSend, nFrom);

		double lfInstantSpeed = (double)(pLocalParam->nInstantSpeed / 100.0);
		if (pLocalParam->bOpenVoiceLater && pLocalParam->bOilAlarmNeedToSend && lfInstantSpeed >= 2.0)
		{
			pLocalParam->bOilAlarmNeedToSend = false;
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_OIL_BELOW_SAFETY_LINE);
		}
 	}
	else
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REMAINING_IAMGE, 0);

	g_clsExtcar.sendToFlyJniSdk_OilRemind(nOilRemind);
	g_clsExtcar.extcarSendRemainOilToSdk(nOilRemind);
	return nNeedPlayAudioTimes;
	
}
void process_avgOilWearInfo()
{
	u8 strAvgOilWear[30]={0};
	float avgOilWear=pLocalParam->avgOilWear/10.0;
	if (pLocalParam->avgOilWear == 0x07 || pLocalParam->avgOilWear == 0xFF || pLocalParam->avgOilWear == -1000){
		sprintf((char*)strAvgOilWear, "N/A");
		g_clsExtcar.sendToFlyJniSdk_AvgOilWearInfo(0,0xFF);
	}
	else{
		sprintf((char*)strAvgOilWear, "%.1fL/100km",avgOilWear);
		g_clsExtcar.sendToFlyJniSdk_AvgOilWearInfo(0,pLocalParam->avgOilWear*10);
	}
	LOGD("strAvgOilWear: %s ", strAvgOilWear);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_AVERAGE_FUEL_CONSUMPTION_TEXT,strAvgOilWear,strlen((char *)strAvgOilWear));
}

void process_avgOilWearInfo_kmL()
{
	u8 strAvgOilWear[30]={0};
	float avgOilWear=pLocalParam->avgOilWear/10.0;
	if (pLocalParam->avgOilWear == 0x07 || pLocalParam->avgOilWear == 0xFF || pLocalParam->avgOilWear == -1000){
		sprintf((char*)strAvgOilWear, "N/A");
		g_clsExtcar.sendToFlyJniSdk_AvgOilWearInfo(0,0xFF);
	}
	else{
		sprintf((char*)strAvgOilWear, "%.1fkm/L",avgOilWear);
		g_clsExtcar.sendToFlyJniSdk_AvgOilWearInfo(0,pLocalParam->avgOilWear*10);
	}
	LOGD("strAvgOilWear: %s ", strAvgOilWear);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_AVERAGE_FUEL_CONSUMPTION_TEXT,strAvgOilWear,strlen((char *)strAvgOilWear));
}

void process_curOilWearInfo()
{
	u8 strCurOilWear[30]={0};
	sprintf((char*)strCurOilWear, "%dL/100km",(int)pLocalParam->curOilWear);
	LOGD("[dyb] strCurOilWear: %s ", strCurOilWear);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_FUEL_CONSUMPTION_TEXT, strCurOilWear,strlen((char *)strCurOilWear));
}
/*
void process_DegreeOfCarGroundInfo()
{
	u8 ansiBuf[128];
	double lfDegreeOfCarGround = (double)(pLocalParam->nDegreeOfCarGround / 10.0);
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (pLocalParam->nDegreeOfCarGround == -10000)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%.1lf\B0C", lfDegreeOfCarGround);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_TXT, ansiBuf, nAnsiBufLen);
	if (lfDegreeOfCarGround >= 40.0)
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_IAMGE, 1);
	else
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_IAMGE, 0);
}
*/


void process_DegreeOfCarGroundInfo()
{
	u8 ansiBuf[64];
	double lfDegreeOfCarGround = (double)(pLocalParam->nDegreeOfCarGround / 10.0);
	memset(ansiBuf, 0, sizeof(ansiBuf));

	g_clsExtcar.sendToFlyJniSdk_DegreeOfCarGround(pLocalParam->nDegreeOfCarGround);
	
	if (pLocalParam->nDegreeOfCarGround == -10000)
	{
		sprintf((char*)ansiBuf,"%s", "N/A");
		int nAnsiBufLen = strlen((char*)ansiBuf);
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_TXT, ansiBuf, nAnsiBufLen);
	}
	else
	{
		wchar_t wcharBuf[10] = L"℃";
		u8 unicBuf[32] = {0};

		sprintf((char*)ansiBuf,"%.1lf", lfDegreeOfCarGround);
		u32 dwUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicBuf);
		memcpy((char*)unicBuf + dwUnicodeBufLen * 2, (char*)wcharBuf, 2);
		setSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_TXT, (u8*)unicBuf, dwUnicodeBufLen * 2 + 2);
	}
	
	if (lfDegreeOfCarGround >= 40.0)
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_IAMGE, 1);
	else
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_IAMGE, 0);
}


void process_toyota_CarDoorLockState()
{
	if(pLocalParam->nCarDoorLockStates == 0x1f)
	{
	}
	else if(pLocalParam->nCarDoorLockStates == 0x1e)
	{
	}
	else if(pLocalParam->nCarDoorLockStates == 0x00)
	{
	}
	else if(pLocalParam->nCarDoorLockStates == 0x10)
	{
	}
	else if(pLocalParam->nCarDoorLockStates == 0x08)
	{
	}
	else if(pLocalParam->nCarDoorLockStates == 0x06)
	{
	}

	pLocalParam->eCarDoorLocker = (pLocalParam->nCarDoorLockStates == 0x00) ? CAR_DOOR_LOCKER_LOCK : CAR_DOOR_LOCKER_UNLOCK;
	process_car_locker();
}

void process_DegreeOfWaterInfo()
{
	
	u8 ansiBuf[128];
	int nDegreeOfWater = pLocalParam->nDegreeOfWater;
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (nDegreeOfWater < 0)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%d\B0C", nDegreeOfWater);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_COOLANT_TEMPERATURE_TEXT, ansiBuf, nAnsiBufLen);
	
	if (nDegreeOfWater >= 95.0)
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_COOLANT_TEMPERATURE, 1);
	else
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_COOLANT_TEMPERATURE, 0);

	g_clsExtcar.sendToFlyJniSdk_DegreeOfWater(nDegreeOfWater);

}

int process_CleanWaterStatusInfo(int nFrom)
{
	int nNeedPlayAudioTimes = 0;

	g_clsExtcar.sendToFlyJniSdk_CleanWaterStatus((char)pLocalParam->eCleanWaterStatus);
	
	if (CLEAN_WATER_EMPTY == pLocalParam->eCleanWaterStatus)
	{
		nNeedPlayAudioTimes++;
		needToAlarm(CARINFO_ALARM_SOUND_CLEAN_WATER_OVER);
		//u8 ansiBufA[] = {0x28, 0x75, 0x8c, 0x5b, 0x00, 0x00};
		//setSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATRE_TXT, ansiBufA, 6);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATRE_TXT,STRINGID_CAR_INFO_CLEAN_WATER_NON);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATRE_IAMGE, 1);
	}
	else if (CLEAN_WATER_ENOUGH == pLocalParam->eCleanWaterStatus)
	{
		//u8 ansiBufB[] = {0x63, 0x6b, 0x38, 0x5e, 0x00, 0x00};
		//setSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATRE_TXT, ansiBufB, 6);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATRE_TXT,STRINGID_CAR_INFO_CLEAN_WATER_NORMAL);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATRE_IAMGE, 0);
	}
	else if (CLEAN_WATER_UNKNOW == pLocalParam->eCleanWaterStatus)
	{
		u8 ansiBuf[10];
		memset(ansiBuf, 0, sizeof(ansiBuf));
		sprintf((char*)ansiBuf,"%s", "N/A");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATRE_TXT, ansiBuf, strlen((char*)ansiBuf));
	}

	return nNeedPlayAudioTimes;
	
}
void process_GreaStageInfo(void)
{
	u8 uGearStage=pLocalParam->uGearStage;
	u8 ansiBuf[20]={0};
	switch(uGearStage)
	{
	case 0x00:
		sprintf((char*)ansiBuf,"%s", "P");
		break;
	case 0x01:
		sprintf((char*)ansiBuf,"%s", "R");
		break;
	case 0x02:
		sprintf((char*)ansiBuf,"%s", "N");
		break;
	case 0x03:
		sprintf((char*)ansiBuf,"%s", "D");
		break;
	default:
		break;
	}

	g_clsExtcar.sendToFlyJniSdk_GearState((char)uGearStage);
	
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, strlen(( char*)ansiBuf));
	setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,uGearStage);
}

void process_car_stall(void)
{
	u8 ansiBuf[20]={0};
	if (pLocalParam->eCarStall == CAR_STALL_P)
	{
		sprintf((char*)ansiBuf,"%s", "P");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, strlen(( char*)ansiBuf));
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,1);
	}
	else if (pLocalParam->eCarStall == CAR_STALL_B)
	{
		sprintf((char*)ansiBuf,"%s", "R");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, strlen(( char*)ansiBuf));
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,1);
	}
	else if (pLocalParam->eCarStall == CAR_STALL_N)
	{
		sprintf((char*)ansiBuf,"%s", "N");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, strlen(( char*)ansiBuf));
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,1);
	}
	else if (pLocalParam->eCarStall == CAR_STALL_D)
	{
		sprintf((char*)ansiBuf,"%s", "D");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, strlen(( char*)ansiBuf));
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,1);
	}
	else if (pLocalParam->eCarStall == CAR_STALL_S)
	{
		sprintf((char*)ansiBuf,"%s", "S");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, strlen(( char*)ansiBuf));
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,1);
	}
	else if (pLocalParam->eCarStall == CAR_STALL_S2)
	{
		sprintf((char*)ansiBuf,"%s", "2");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, strlen(( char*)ansiBuf));
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,1);
	}
	else if (pLocalParam->eCarStall == CAR_STALL_S1)
	{
		sprintf((char*)ansiBuf,"%s", "1");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, strlen(( char*)ansiBuf));
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,1);
	}
	else if (pLocalParam->eCarStall == CAR_STALL_NOT_P)
	{
		sprintf((char*)ansiBuf,"%s", "O");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, strlen(( char*)ansiBuf));
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,0);
	}
	else if (pLocalParam->eCarStall == CAR_STALL_UNKNOW)
	{
		sprintf((char*)ansiBuf,"%s", "N/A");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, strlen(( char*)ansiBuf));
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,0);
	}

	g_clsExtcar.sendToFlyJniSdk_GearState(pLocalParam->eCarStall);
	
}

void process_car_locker()
{
	if (pLocalParam->eCarDoorLocker == CAR_DOOR_LOCKER_LOCK)
	{
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LOCKER_TXT, STRINGID_CAR_INFO_CLOSE);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LOCKER_IMAG,1);
	}
	else if (pLocalParam->eCarDoorLocker == CAR_DOOR_LOCKER_UNLOCK)
	{
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LOCKER_TXT, STRINGID_CAR_INFO_OPEN);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LOCKER_IMAG,0);
	}
	else
	{
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LOCKER_IMAG,1);
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LOCKER_TXT,(u8*)("N/A"), sizeof("N/A"));
	}

	g_clsExtcar.sendToFlyJniSdk_CarLocker((char)pLocalParam->eCarDoorLocker);
}

void process_car_door_window()
{
	u8 uBuff[4] = {0};
	uBuff[0] = (u8)pLocalParam->eCarDoorWindow_FL;
	uBuff[1] = (u8)pLocalParam->eCarDoorWindow_FR;
	uBuff[2] = (u8)pLocalParam->eCarDoorWindow_RL;
	uBuff[3] = (u8)pLocalParam->eCarDoorWindow_RR;
	
	g_clsExtcar.sendToFlyJniSdk_CarDoorWindow(uBuff,4);
}

void process_car_dormer()
{
	g_clsExtcar.sendToFlyJniSdk_CarDormer((char)pLocalParam->eCarDormer);
}

void process_car_head_light()
{
	g_clsExtcar.sendToFlyJniSdk_CarHeadlight((char)pLocalParam->eHeadLight);
}

void process_DaZhongCarInfo()
{
	switch(pLocalParam->nCurCmd)
	{
	case 0x01:
		break;
	case 0x10:
		process_DrivingDistanceInfo();
		break;
	case 0x11:
		process_BatteryVoltageInfo();
		break;
	case 0x12:
		process_EngineSpeedInfo();
		break;
	case 0x13:// car door
		process_DoorInfo();
		break;
	case 0x14:// safety belt
		process_SafetyBeltInfo();
		break;
	case 0x15:// hand stop
		process_HandLockerInfo(1);
		break;
	case 0x16:
		process_InstantSpeedInfo();
		break;
	case 0x17:
		process_OilRemindInfo();
		break;
	case 0x18:
		process_DegreeOfCarGroundInfo();
		break;
	case 0x19:
		//process_DegreeOfWaterInfo();
		break;
	case 0x1A:
		//process_CleanWaterStatusInfo();
		break;
	case 0x1B:
		process_car_door_window();
		break;
	case 0x1C:
		process_car_dormer();
		break;
	case 0x1D:
		process_car_locker();
		break;
	case 0x1E:
		process_car_head_light();
		break;
	}
}
void process_fks_CarInfo()

{
	switch(pLocalParam->nCurCmd)
	{
	case 0x51:
		process_DrivingDistanceInfo();
		break;
	
	case 0x52:// car door
		process_DoorInfo();
		break;
		
	case 0x53:// hand stop
		process_HandLockerInfo(1);
		break;
		
	case 0x54:// safety belt
		process_SafetyBeltInfo();
		break;
		
	case 0x55:
		process_DegreeOfCarGroundInfo();
		break;
		
	case 0x56:
		process_EngineSpeedInfo();
		break;
		
	case 0x57:
		process_BatteryVoltageInfo();
		break;
	
	case 0x59:
		process_InstantSpeedInfo();
		break;
	case 0x5A:
		process_GreaStageInfo();
	case 0x58:
		//process_OilRemindInfo();
		break;
	}
}

void process_toyota_CarInfo()
{
	switch(pLocalParam->nCurCmd)
	{
		case 0x70:
			halToExtcar_AutomaticallyAcOrEffectiveVentilationModel(pLocalParam->AutomaticalAcOrEffectVentilat);
		break;
		case 0x71:
			process_SafetyBeltInfo();
		break;
		case 0x72:
		case 0xc5://HL_voltage_BrakeState
			process_HandLockerInfo(1);
		break;
		case 0x73:
			process_EngineSpeedInfo();
		break;
		case 0x74:
			process_DoorInfo();
		break;
		case 0x75:
			process_DrivingDistanceInfo();
		break;
		case 0x76:
			process_InstantSpeedInfo();
		break;
		case 0xc4://Gears
			process_GearsInfo();
		break;
		case 0x77:
			process_DegreeOfCarGroundInfo();
		break;
		case 0x78:
		break;
		case 0x79:
			process_toyota_CarDoorLockState();
		break;
		case 0x7a:
		break;
		case 0x7b:
		break;
		case 0x7c:
		break;
		case 0x7d:
		break;
		case 0x7e:
			process_BatteryVoltageInfo();
		break;
		case 0x83:
			process_carola_oilConsumeUnit();
		break;
		case 0x84:
			process_car_dormer();
		break;
		case 0x85:
			process_car_head_light();
		break;
		case 0x86:
			process_car_door_window();
		break;
		case 0x87:
			process_car_locker();
		break;
		default:break;
	}
}

void process_SiYu_CarInfo()
{
	switch(pLocalParam->nCurCmd)
	{
		case 0x00:/*˼��AC*/
			break;
		case 0x01: /*���ֵ*/
			process_DrivingDistanceInfo();
			break;
		case 0x02: /*������Ϣ*/
			process_DoorInfo();
			break;
		case 0x03: /*��ɲ*/
			process_HandLockerInfo(1);
			break;
		case 0x04: /*��ȫ��*/
			process_SafetyBeltInfo();
			break;
		case 0x05: /*�ⲿ�¶�*/
			process_DegreeOfCarGroundInfo();
			break;
		case 0x06: /*����ת��*/
			process_EngineSpeedInfo();
			break;
		case 0x07:/*��ص�ѹ*/
			process_BatteryVoltageInfo();
			break;
		case 0x09:/*˲ʱ�ٶ�*/
			process_InstantSpeedInfo();
			break;
		case 0x0A:/*ʣ�����*/
			RunningMileage_Displaying_NewPage(pLocalParam->SurplusDistance);
			break;
		case 0x0B:/*ƽ���ͺ�*/
			process_avgOilWearInfo();
			break;
		case 0x0C:/*��ǰ�ͺ�*/
			process_curOilWearInfo();
			break;
		case 0x0D:/*CRV AC*/
			break;
		case 0x0E:/*��λ*/
			process_car_stall();
			break;
		case 0x0F:/*������*/
			process_car_locker();
			break;
		default:break;
	}
}

void process_byd_carInfo()
{
	switch(pLocalParam->nCurCmd)
	{
		case 0x00:
			process_DegreeOfCarGroundInfo();
		break;
		case 0x12:
			process_EngineSpeedInfo();
			break;
		case 0x13:// car door
			process_DoorInfo();
			break;
		case 0x14:// safety belt
			process_SafetyBeltInfo();
			break;
		case 0x15:// hand stop
			process_HandLockerInfo(1);
			break;
		case 0x16:
			process_curOilWearInfo();
			break;
		case 0x17:
			process_car_stall();
			break;
		case 0x18:
			process_car_locker();
			break;	
		default:break;
	}
}

void RunningMileage_Displaying_NewPage(int Value)/*����ʻ���*/
{
	u8 ansiBuf[128];
	int nDrivingDistance = Value;
	memset(ansiBuf, 0, sizeof(ansiBuf));
	if (nDrivingDistance < 0)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%d km", nDrivingDistance);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);

	LOGD("ansiBuf %s \n", ansiBuf);
	
	g_clsExtcar.sendToFlyJniSdk_MileageCanRun(Value);
	
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_RUNNING_MILEAGE_TEXT,ansiBuf,nAnsiBufLen);
}

void AverageSpeed_Displaying_NewPage(u16 Value)/*ƽ����*/
{
	u8 pwBuf[30];
	memset(pwBuf, 0, sizeof(pwBuf));

	sprintf((char*)pwBuf, "%d km/h",  Value);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_AVERAGE_SPEED_TEXT,pwBuf,strlen((char *)pwBuf));

}

void TravelTime_Displaying_NewPage(u8 hour,u8 minute)/*��ʻʱ��*/
{
	u8 pwBuf[30];
	memset(pwBuf, 0, sizeof(pwBuf));

	sprintf((char*)pwBuf, "%02d:%02d",hour,minute);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRVEL_TIME_TEXT,pwBuf,strlen((char *)pwBuf));

}

void CurOilConsumption_Displaying_NewPage(unsigned char *buf,int len)/*��ǰ�ͺ�*/
{
	LOGD("CurOilConsumption_Displaying_NewPage buf[0] = %02X, buf[1] = %02X, buf[2] = %02X ", buf[0], buf[1], buf[2]);
	if(buf==NULL || len <=0)
		return;

	float Value = 0;
	float Front = buf[0];
	float Rear = buf[1] ;

	if (Rear/10 < 1)
	{
		Value = Front + Rear/10;
	}
	else if (Rear/100 < 1)
	{
		Value = Front + Rear/100;
	}
	else if (Rear/1000 < 1)
	{
		Value = Front + Rear/1000;
	}

	u8 pwBuf[30];
	memset(pwBuf, 0, sizeof(pwBuf));

	sprintf((char*)pwBuf, "%3.1f L/100km",Value);
	LOGD("ddddd %s ", pwBuf);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_FUEL_CONSUMPTION_TEXT,pwBuf,strlen((char *)pwBuf));

}

void AverageOilConsumption_Displaying_NewPage(unsigned char *buf,int len)/*ƽ���ͺ�*/
{
	LOGD("AverageOilConsumption_Displaying_NewPage buf[0] = %02X, buf[1] = %02X ", buf[0], buf[1]);
	if(buf==NULL || len <=0)
		return;

	float Value = 0;
	float Front = buf[0];
	float Rear = buf[1] ;

	if (Rear/10 < 1)
	{
		Value = Front + Rear/10;
	}
	else if (Rear/100 < 1)
	{
		Value = Front + Rear/100;
	}
	else if (Rear/1000 < 1)
	{
		Value = Front + Rear/1000;
	}

	u8 pwBuf[30];
	memset(pwBuf, 0, sizeof(pwBuf));

	sprintf((char*)pwBuf, "%3.1f L/100km",Value);
	LOGD("ddddd %s ", pwBuf);
	
	g_clsExtcar.sendToFlyJniSdk_AvgOilWearInfo(0,(int)Value*10);
	
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_AVERAGE_FUEL_CONSUMPTION_TEXT,pwBuf,strlen((char *)pwBuf));

}

void TemperatureOfTheCoolingLiquid_Displaying_NewPage()/*��ȴҺ�¶�*/
{
	u8 ansiBuf[128];
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (pLocalParam->sTempOfCoolingLiquid == -1000)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%d�C", pLocalParam->sTempOfCoolingLiquid);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_COOLANT_TEMPERATURE_TEXT, ansiBuf, nAnsiBufLen);

	if (pLocalParam->sTempOfCoolingLiquid >= 40)
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_COOLANT_TEMPERATURE, 1);
	else
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_COOLANT_TEMPERATURE, 0);


}

void WaterOfTheWaterTank_Displaying_NewPage()/*ˮ��ˮ��*/
{
	u8 ansiBuf[128];
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (pLocalParam->sWaterOfTheWaterTank == -1)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%d L", pLocalParam->sWaterOfTheWaterTank);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATER_TEXT, ansiBuf, nAnsiBufLen);
	if (pLocalParam->sWaterOfTheWaterTank >= 40)
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATER, 1);
	else
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATER, 0);
}


//case CARINFO_ALARM_SOUND_LEFT_FORWARD_DOOR_OPEN:
//case CARINFO_ALARM_SOUND_RIGHT_FORWARD_DOOR_OPEN:
//case CARINFO_ALARM_SOUND_LEFT_REAR_DOOR_OPEN:
//case CARINFO_ALARM_SOUND_RIGHT_REAR_DOOR_OPEN:
//case CARINFO_ALARM_SOUND_BACK_DOOR_OPEN:
//case CARINFO_ALARM_SOUND_SAFETY_BELT_NOT_LOCK:
//case CARINFO_ALARM_SOUND_HAND_LOCK_LOCK:
//case CARINFO_ALARM_SOUND_SEVERAL_DOOR_OPEN:
void needToAlarm(u8 nAlarmAudioID)
{
	u8 bIsneedToAlarm = 0;
	u8 nLen = 1;
	getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_SET_OPTION_EXTCAR_VOICE_PROMPT_STATUS, (u8*)&bIsneedToAlarm, (u8*)&nLen);

	LOGI("needToAlarm: bIsneedToAlarm = %d, nAlarmAudioID = %d \n", bIsneedToAlarm, nAlarmAudioID);
	//exterToCenter_NoticeAlarmTip(nAlarmAudioID);
	if (0 != bIsneedToAlarm)
	{
		if (pLocalParam->bOpenVoiceLater)
			exterToCenter_NoticeAlarmTip(nAlarmAudioID);
	}
}

	/*
	LOGD("[analyseHalMessage_DaZhongCarInfo]->AirCondition len:%d\n",len -1);

	//////////////////////////////////////
	u8 msg[600] = {0};
	len = len - 1;
	int a = len * 3;
	int i, j = 0;
	for (i = 1; i <= len; i++)
		{
			snprintf((char*)(msg + j) , a - j, "%02X ", p[i]);
			j += 3;
		}
	LOGI("%s", msg);
	
	LOGD("p :%x",p[1]);
	//////////////////////////////////////
	*/

#define TAG_GOLF_CAR	"golf_carInfo"
#define TAG_GOLF_AC		"golf_ac"
#define TAG_GOLF_BLUETOOTH	"golf_blueTooth"
#define TAG_GOLF_GPS		"golf_gps"

int radar_signal_LPC2JNI(int s, int r)
{
	int nRet = 0;
		 if (s >= 0 && s <= 0x0F)
		nRet = 1;
	else if (s >= 0x10 && s <= 0x1E)
		nRet = 2;
	else if (s >= 0x1F && s <= 0x2A)
		nRet = 3;
	else if (s >= 0x2B && s <= 0x3A)
		nRet = 4;
	else if (s >= 0x3B && s <= 0x4A)
		nRet = 5;
	else if (s >= 0x4B && s <= 0x5A)
		nRet = 6;
	else if (s >= 0x5B && s <= 0x6A)
		nRet = 7;
	else if (s >= 0x6B && s <= 0x7A)
		nRet = 8;
	else if (s >= 0x7B && s <= 0x8A)
		nRet = 9;
	else if (s >= 0x8B && s <= 0x9A)
		nRet = 10;
	else if (s >= 0x9B && s <= 0xB0)
		nRet = 11;
	else if (s == 0xFF)
		nRet = 0;

	if (nRet != 0)
		nRet = r - nRet + 1;

	return nRet;
}

void analyseHalMessage_golf_carInfo(unsigned char *p, int len)
{
	if(pLocalParam->eCarModels != CAR_MODELS_DAS_AUTO){
		pLocalParam->eCarModels = CAR_MODELS_DAS_AUTO;
	}

	pLocalParam->nCurCmd = p[0];
	switch(p[0])
	{
	case 0x01:
		{
			pLocalParam->eSafetyBeltStatus =   ( ((p[1] & (1<<3)) && (0 == (p[2] & 1)))  ||  ((p[1] & (1<<2)) && (0 == (p[2] & (1<<2)))) ) ?  SATETY_BELT_UNLOCKED : SATETY_BELT_LOCKED;
			LOGD("[%s] pLocalParam->eSafetyBeltStatus = [0x%X], p[1] = [0x%02X]", TAG_GOLF_CAR, pLocalParam->eSafetyBeltStatus, p[1]);
		}
		break;
	case 0x02:
		{
			pLocalParam->eHandLockerStatus = (0x01 == p[1]) ? HAND_LOCKER_LOCKED : HAND_LOCKER_UNLOCKED;
			LOGD("[%s] pLocalParam->eHandLockerStatus [0x%X]", TAG_GOLF_CAR, pLocalParam->eHandLockerStatus);
		}
		break;
	case 0x03:
		{
			pLocalParam->nEngineSpeed = (p[1] * 256 + p[2]) / 4;
			LOGD("[%s] pLocalParam->nEngineSpeed [%d]", TAG_GOLF_CAR, pLocalParam->nEngineSpeed);
		}
		break;
	case 0x04:
		{
			pLocalParam->nInstantSpeed = p[1] * 100;
			LOGD("[%s] pLocalParam->nInstantSpeed [%d]", TAG_GOLF_CAR, pLocalParam->nInstantSpeed);
		}
		break;
	case 0x05:
		{
			pLocalParam->nDegreeOfCarGround = (p[1] - 0x64) * 10 / 2;
			LOGD("[%s] pLocalParam->nDegreeOfCarGround [%d]", TAG_GOLF_CAR, pLocalParam->nDegreeOfCarGround);
		}
		break;
	case 0x06:// code water
		{
			pLocalParam->sTempOfCoolingLiquid = p[1] - 0x5E;
			pLocalParam->nDegreeOfWater = p[1] - 0x5E;
			LOGD("[%s] code water pLocalParam->sTempOfCoolingLiquid [%d]", TAG_GOLF_CAR, pLocalParam->sTempOfCoolingLiquid);
		}
		break;
	case 0x07:// radar page open or not
		{
			exterToRadar(p[1]);
			LOGD("[%s] radar page open [%d]", TAG_GOLF_CAR, p[1]);
		}
		break;
	case 0x08:// radar
		{
			u8 pos = p[1] - 1;
			u32 d = 0;
			int t = 0;
			t = radar_signal_LPC2JNI(p[2], 4);
			d += t;
			t = radar_signal_LPC2JNI(p[3], (0 == pos) ? 8 : 11);
			d += t << 8;
			t = radar_signal_LPC2JNI(p[4], (0 == pos) ? 8 : 11);
			d += t << 16;
			t = radar_signal_LPC2JNI(p[5], 4);
			d += t << 24;
			exterToRadar(pos, d);
			LOGD("[%s] radar data 0~4 [0X%0X] [0X%0X] [0X%0X] [0X%0X] [0X%0X]", TAG_GOLF_CAR, p[1], p[2], p[3], p[4], p[5]);
		}
		break;
	case 0x09:
		{
			char m = p[1];
			char t = p[2];
			char r = 0;
			r |= (t & (1<<2)) >> 2;// l f door
			r |= (t & 1) << 1;// r f door
			r |= (m & (1<<4)) >> 2;// l r door
			r |= (m & (1<<5)) >> 2;// r r door
			r |= (t & (1<<5)) >> 1;// front door
			r |= (t & (1<<6)) >> 1;// back door
			r |= (t & (1<<3)) << 3;// rain fan

			pLocalParam->nCarDoorStatus = r;
			LOGD("[%s] pLocalParam->nCarDoorStatus [0x%X]", TAG_GOLF_CAR, pLocalParam->nCarDoorStatus);
		}
		break;
	case 0x0A:
		{
			pLocalParam->nBatteryVoltage = 0;
			memcpy(&pLocalParam->nBatteryVoltage, p + 1, 2);
			LOGD("[%s] pLocalParam->nBatteryVoltage [%d]", TAG_GOLF_CAR, pLocalParam->nBatteryVoltage);
		}
		break;
	case 0x0B:
		{
			pLocalParam->nOilRemind = p[1];
			LOGD("[%s] pLocalParam->nOilRemind [%d]", TAG_GOLF_CAR, pLocalParam->nOilRemind);
		}
		break;
	case 0x0C://clean water
		{
			pLocalParam->eCleanWaterStatus = (0x01 == p[1]) ? CLEAN_WATER_EMPTY : CLEAN_WATER_ENOUGH;
			LOGD("[%s] pLocalParam->eCleanWaterStatus [0x%X]", TAG_GOLF_CAR, pLocalParam->eCleanWaterStatus);
		}
		break;
	case 0x10://
		{
			pLocalParam->eDriveMode =(E_DRIVE_MODE) p[1];
			LOGD("[%s] driver assist system driver assist system pLocalParam->eDriveMode [%d]", TAG_GOLF_CAR, pLocalParam->eDriveMode);
		}
		break;
	case 0x11:// last select car distance
		{
			pLocalParam->eLastSelectGap = (E_LAST_SELECT_GAP)p[1];
			LOGD("[%s] driver assist system last select car distance pLocalParam->eLastSelectGap [%d]", TAG_GOLF_CAR, pLocalParam->eLastSelectGap);
		}
		break;
	case 0x12:// car distance
		{
			pLocalParam->eGap = (E_GAP)p[1];
			LOGD("[%s] driver assist system car distance pLocalParam->eGap [%d]", TAG_GOLF_CAR, pLocalParam->eGap);
		}
		break;
	///////////////////////////// front assist system //////////////////////////////////////
	case 0x13:// active
		{
			pLocalParam->ePreAssistSystemActivation = (E_PRE_ASSIST_SYSTEM_ACTIVATION)p[1];
			LOGD("[%s] front assist system active pLocalParam->ePreAssistSystemActivation [%d]", TAG_GOLF_CAR, pLocalParam->ePreAssistSystemActivation);
		}
		break;
	case 0x14:// pre warning
		{
			pLocalParam->ePreAssistSystemWarning = (E_PRE_ASSIST_SYSTEM_WARNING)p[1];
			LOGD("[%s] front assist system pre warning pLocalParam->ePreAssistSystemWarning [%d]", TAG_GOLF_CAR, pLocalParam->ePreAssistSystemWarning);
		}
		break;
	case 0x15:// distance warning
		{
			pLocalParam->ePreAssistSystemGapWarning = (E_PRE_ASSIST_SYSTEM_GAP_WARNING)p[1];
			LOGD("[%s] front assist system distance warning pLocalParam->ePreAssistSystemGapWarning [%d]", TAG_GOLF_CAR, pLocalParam->ePreAssistSystemGapWarning);
		}
		break;
	///////////////////////////////// fatigue recognize system /////////////////////////////////////
	case 0x16:
		{
			pLocalParam->eFatigueReconizeSystemActivation = (E_FATIGUE_RECONIZE_SYSTEM_ACTIVATION)p[1];
			LOGD("[%s] fatigue recognize system active pLocalParam->eFatigueReconizeSystemActivation [%d]", TAG_GOLF_CAR, pLocalParam->eFatigueReconizeSystemActivation);
		}
		break;
	////////////////////////////////// esc system ////////////////////////////////
	case 0x17:
		{
			pLocalParam->eEscSystemActivation = (E_ESC_SYSTEM_ACTIVATION)p[1];
			LOGD("[%s] esc system active pLocalParam->eEscSystemActivation [%d]", TAG_GOLF_CAR, pLocalParam->eEscSystemActivation);
		}
		break;
	case 0x18:
		{
			pLocalParam->eTireType = (E_TIRE_TYPE)p[1];
			LOGD("[%s] winter tie pLocalParam->eTireType [%d]", TAG_GOLF_CAR, pLocalParam->eTireType);
		}
		break;
	case 0x19:
		{
			pLocalParam->eCarSpeedWarning = (E_CAR_SPEED_WARNING)p[1];
			pLocalParam->nCarSpeedWarning = p[2];
			LOGD("[%s] pLocalParam->eCarSpeedWarning [%d], pLocalParam->nCarSpeedWarning [%d]", TAG_GOLF_CAR, pLocalParam->eCarSpeedWarning, pLocalParam->nCarSpeedWarning);
		}
		break;
	case 0x1A:
		{
			pLocalParam->eLightSystemConnect = (E_LIGHT_SYSTEM_CONNECT)p[1];
			LOGD("[%s] pLocalParam->eLightSystemConnect [%d]", TAG_GOLF_CAR, pLocalParam->eLightSystemConnect);
		}
		break;
	case 0x1B:
		{
			pLocalParam->eLightSystemAuto = (E_LIGHT_SYSTEM_AUTO)p[1];
			LOGD("[%s] pLocalParam->eLightSystemAuto [%d]", TAG_GOLF_CAR, pLocalParam->eLightSystemAuto);
		}
		break;
	case 0x1C:
		{
			pLocalParam->eLightSystemDirection = (E_LIGHT_SYSTEM_DIRECTION)p[1];
			LOGD("[%s] pLocalParam->eLightSystemDirection [%d]", TAG_GOLF_CAR, pLocalParam->eLightSystemDirection);
		}
		break;
	case 0x1D:
		{
			pLocalParam->eDriveRule = (E_DRIVE_RULE)p[1];
			LOGD("[%s] pLocalParam->eDriveRule [%d]", TAG_GOLF_CAR, pLocalParam->eDriveRule);
		}
		break;
	case 0x1E:
		{
			pLocalParam->nGoHomeModeTime = p[1];
			LOGD("[%s] pLocalParam->nGoHomeModeTime [%d]", TAG_GOLF_CAR, pLocalParam->nGoHomeModeTime);
		}
		break;
	case 0x1F:
		{
			pLocalParam->nLeaveHomeModeTime = p[1];
			LOGD("[%s] pLocalParam->nLeaveHomeModeTime [%d]", TAG_GOLF_CAR, pLocalParam->nLeaveHomeModeTime);
		}
		break;
	case 0x20:
		{
			pLocalParam->nMeterLightBrightness = p[1];
			LOGD("[%s] pLocalParam->nMeterLightBrightness [%d]", TAG_GOLF_CAR, pLocalParam->nMeterLightBrightness);
		}
		break;
	case 0x21:
		{
			pLocalParam->nDoorLightBrightness = p[1];
			LOGD("[%s] pLocalParam->nDoorLightBrightness [%d]", TAG_GOLF_CAR, pLocalParam->nDoorLightBrightness);
		}
		break;
	case 0x22:
		{
			pLocalParam->nFeetLightBrightness = p[1];
			LOGD("[%s] pLocalParam->nFeetLightBrightness [%d]", TAG_GOLF_CAR, pLocalParam->nFeetLightBrightness);
		}
		break;
	case 0x23:
		{
			pLocalParam->eWindowCtrl = (E_WINDOW_CTRL)p[1];
			LOGD("[%s] pLocalParam->eWindowCtrl [%d]", TAG_GOLF_CAR, pLocalParam->eWindowCtrl);
		}
		break;
	case 0x24:
		{
			pLocalParam->eDoorCtrl = (E_DOOR_CTRL)p[1];
			LOGD("[%s] pLocalParam->eDoorCtrl [%d]", TAG_GOLF_CAR, pLocalParam->eDoorCtrl);
		}
		break;
	case 0x25:
		{
			pLocalParam->eDoorAutoLock = (E_DOOR_AUTO_LOCK)p[1];
			LOGD("[%s] pLocalParam->eDoorAutoLock [%d]",TAG_GOLF_CAR,  pLocalParam->eDoorAutoLock);
		}
		break;
	case 0x26:
		{
			pLocalParam->eBackMirrorReverseCar =(E_BACK_MIRROR_REVERSE_CAR) (p[1] & 1);
			pLocalParam->eBackMirrorSync = (E_BACK_MIRROR_SYNC)((p[1] & 0x02) >> 1);
			pLocalParam->emMirrorsIntheFoldParkedSelect = (E_MIRRORS_IN_THE_FOLD_HAS_PARKING)((p[1] & 0x04) >> 2);
			LOGD("[%s] pLocalParam->eBackMirrorReverseCar [%d]", TAG_GOLF_CAR, pLocalParam->eBackMirrorReverseCar);
			LOGD("[%s] pLocalParam->eBackMirrorSync [%d]", TAG_GOLF_CAR,pLocalParam->eBackMirrorSync);
			LOGD("[%s] pLocalParam->emMirrorsIntheFoldParkedSelect [%d]", TAG_GOLF_CAR,pLocalParam->emMirrorsIntheFoldParkedSelect);
		}
		break;
	case 0x27:
		{
			pLocalParam->eWiperAuto = (E_WIPER_AUTO)p[1];
			LOGD("[%s] pLocalParam->eWiperAuto [%d]",TAG_GOLF_CAR,  pLocalParam->eWiperAuto);
		}
		break;
	case 0x28:
		{
			pLocalParam->eBackWinCleanReverseCar = (E_BACK_WIN_CLEAN_REVERSE_CAR)p[1];
			LOGD("[%s] pLocalParam->eBackWinCleanReverseCar [%d]",TAG_GOLF_CAR,  pLocalParam->eBackWinCleanReverseCar);
		}
		break;
	case 0x29://back radar
		{
			pLocalParam->eReverseCarSystemAutoActivation = (E_REVERSE_CAR_SYSTEM_AUTO_ACTIVATION)p[1];
			LOGD("[%s] pLocalParam->eReverseCarSystemAutoActivation [%d]",TAG_GOLF_CAR,  pLocalParam->eReverseCarSystemAutoActivation);
		}
		break;
	case 0x2A:
		{
			pLocalParam->nCarFrontAudioParam = 0;
			memcpy(&(pLocalParam->nCarFrontAudioParam), p + 1, 2);
			LOGD("[%s] pLocalParam->nCarFrontAudioParam [%d]",TAG_GOLF_CAR,  pLocalParam->nCarFrontAudioParam);
		}
		break;
	case 0x2B:
		{
			pLocalParam->nCarRearAudioParam = 0;
			memcpy(&(pLocalParam->nCarRearAudioParam), p + 1, 2);
			LOGD("[%s] pLocalParam->nCarRearAudioParam [%d]",TAG_GOLF_CAR,  pLocalParam->nCarRearAudioParam);
		}
		break;
	case 0x2C:
		{
			pLocalParam->eOilConsumeSelect = (E_OIL_CONSUME_SELECT)p[1];
			pLocalParam->eOilAvgConsumeSelect = (E_OIL_AVG_CONSUME_SELECT)p[2];
			pLocalParam->eDriveTimeSelect = (E_DRIVE_TIME_SELECT)p[3];
			pLocalParam->eDriveDistanceSelect = (E_DRIVE_DISTANCE_SELECT)p[4];
			pLocalParam->eAvgSpeedSelect = (E_AVG_SPEED_SELECT)p[5];
			pLocalParam->eDigitSpeedDisplay = (E_DIGIT_SPEED_DISPLAY)p[6];
			pLocalParam->eCarSpeedWarningDisplay = (E_CAR_SPEED_WARNING_DISPLAY)p[7];
			LOGD("[%s] pLocalParam->eOilConsumeSelect [%d] [%d] [%d] [%d] [%d] [%d] [%d]",TAG_GOLF_CAR,  p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
		}
		break;
	case 0x2D:
		{
			pLocalParam->eCozyDeviceSelect = (E_COZY_DEVICE_SELECT)((p[1] & (1<<2)) >> 2);
			pLocalParam->eEconomyDriveTip = (E_ECONOMY_DRIVE_TIP)((p[1] & (1<<1)) >> 1);
			LOGD("[%s] eCozyDeviceSelect [%d], eEconomyDriveTip [%d]",TAG_GOLF_CAR,  pLocalParam->eCozyDeviceSelect, pLocalParam->eEconomyDriveTip);
		}
		break;
	case 0x2E:
		{
			pLocalParam->nRecoveryDriveDataFromAutoRun = p[1];
			LOGD("[%s] pLocalParam->nRecoveryDriveDataFromAutoRun [%d]",TAG_GOLF_CAR,  pLocalParam->nRecoveryDriveDataFromAutoRun);
		}
		break;
	case 0x2F:
		{
			pLocalParam->nRecoveryDriveDataFromLongTimeRun = p[1];
			LOGD("[%s] pLocalParam->nRecoveryDriveDataFromLongTimeRun [%d]",TAG_GOLF_CAR,  pLocalParam->nRecoveryDriveDataFromLongTimeRun);
		}
		break;
	//	unit setting
	case 0x30:
		{
			pLocalParam->eDegreeUnit = (E_DEGREE_UNIT)p[1];
			LOGD("[%s] pLocalParam->eDegreeUnit [%d]",TAG_GOLF_CAR,  pLocalParam->eDegreeUnit);
		}
		break;
	case 0x31:
		{
			pLocalParam->eVolumeUnit = (E_VOLUME_UNIT)p[1];
			LOGD("[%s] pLocalParam->eVolumeUnit [%d]",TAG_GOLF_CAR,  pLocalParam->eVolumeUnit);
		}
		break;
	case 0x32:
		{
			pLocalParam->eOilConsumeUnit = (E_OIL_CONSUME_UNIT)p[1];
			LOGD("[%s] pLocalParam->eOilConsumeUnit [%d]",TAG_GOLF_CAR,  pLocalParam->eOilConsumeUnit);
		}
		break;
	case 0x33:
		{
			pLocalParam->eTieCompressUnit = (E_TIE_COMPRESS_UNIT)p[1];
			LOGD("[%s] pLocalParam->eTieCompressUnit [%d]",TAG_GOLF_CAR,  pLocalParam->eTieCompressUnit);
		}
		break;
		// time and date
	case 0x34:
		{
			pLocalParam->nSystemTimeInfo = 0;
			memcpy(&(pLocalParam->nSystemTimeInfo), p + 1, 2);
			LOGD("[%s] pLocalParam->nSystemTimeInfo [%d]",TAG_GOLF_CAR,  pLocalParam->nSystemTimeInfo);
		}
		break;
	case 0x35:
		{
			pLocalParam->nSystemDateInfo = 0;
			memcpy(&(pLocalParam->nSystemDateInfo), p + 1, 3);
			LOGD("[%s] pLocalParam->nSystemDateInfo [%d]",TAG_GOLF_CAR,  pLocalParam->nSystemDateInfo);
		}
		break;
	case 0x36:
		{
			pLocalParam->nDateFormat = p[1];
			LOGD("[%s] pLocalParam->nDateFormat [%d]",TAG_GOLF_CAR,  pLocalParam->nDateFormat);
		}
		break;
		// recovery factory setting
	case 0x37:
		{
			pLocalParam->eRecoverySettingType = (E_RECOVERY_SETTING_TYPE)p[1];
			LOGD("[%s] pLocalParam->eRecoverySettingType [%d]",TAG_GOLF_CAR,  pLocalParam->eRecoverySettingType);
		}
		break;
		// language setting
	case 0x38:
		{
			pLocalParam->nLanguage = p[1];
			LOGD("[%s] pLocalParam->nLanguage [%d]",TAG_GOLF_CAR,  pLocalParam->nLanguage);
		}
		break;
		// radar volume
	case 0x39:
		{
			pLocalParam->nGolfRadarRingDoor = p[1];
			LOGD("[%s] pLocalParam->nGolfRadarRingDoor [%d]",TAG_GOLF_CAR,  pLocalParam->nGolfRadarRingDoor);
		}
		break;
		// maintenance car
	case 0x3A:
		{
			memset(pLocalParam->szVim, 0, sizeof(pLocalParam->szVim));
			memcpy(pLocalParam->szVim, p + 1, len - 1);
			LOGD("[%s] pLocalParam->szVim [%s]",TAG_GOLF_CAR,  pLocalParam->szVim);
		}
		break;
		// car base info
	case 0x3B:
		{
			pLocalParam->nMaintainDistanceInfo = 0;
			memcpy(&pLocalParam->nMaintainDistanceInfo, p + 1, 3);
			LOGD("[%s] pLocalParam->nMaintainDistanceInfo [%d]",TAG_GOLF_CAR,  pLocalParam->nMaintainDistanceInfo);
		}
		break;
	case 0x3C:
		{
			pLocalParam->nMaintainTimeInfo = 0;
			memcpy(&pLocalParam->nMaintainTimeInfo, p + 1, 3);
			LOGD("[%s] pLocalParam->nMaintainTimeInfo [%d]",TAG_GOLF_CAR,  pLocalParam->nMaintainTimeInfo);
		}
		break;
		// car engine oil
	case 0x3D:
		{
			pLocalParam->nMaintainEngineOilDistanceInfo = 0;
			memcpy(&pLocalParam->nMaintainEngineOilDistanceInfo, p + 1, 3);
			LOGD("[%s] pLocalParam->nMaintainEngineOilDistanceInfo [%d]",TAG_GOLF_CAR,  pLocalParam->nMaintainEngineOilDistanceInfo);
		}
		break;
	case 0x3E:
		{
			pLocalParam->nMaintainEngineOilTimeInfo = 0;
			memcpy(&pLocalParam->nMaintainEngineOilTimeInfo, p + 1, 3);
			LOGD("[%s] pLocalParam->nMaintainEngineOilTimeInfo [%d]",TAG_GOLF_CAR,  pLocalParam->nMaintainEngineOilTimeInfo);
		}
		break;
		// car normal info
	case 0x3F:
		{
			pLocalParam->nTheDistanceLeaveCarCanRun = 0;
			memcpy(&pLocalParam->nTheDistanceLeaveCarCanRun, p + 1, 2);
			LOGD("[%s] pLocalParam->nTheDistanceLeaveCarCanRun [%d]",TAG_GOLF_CAR,  pLocalParam->nTheDistanceLeaveCarCanRun);
		}
		break;
	case 0x40:
		{
			pLocalParam->nAvgOilConsumeFromCarRun = 0;
			memcpy(&pLocalParam->nAvgOilConsumeFromCarRun, p + 1, 3);
			LOGD("[%s] pLocalParam->nAvgOilConsumeFromCarRun [%d]",TAG_GOLF_CAR,  pLocalParam->nAvgOilConsumeFromCarRun);
		}
		break;
	case 0x41:
		{
			pLocalParam->nDriveDistanceFromCarRun = 0;
			memcpy(&pLocalParam->nDriveDistanceFromCarRun, p + 1, 4);
			LOGD("[%s] pLocalParam->nDriveDistanceFromCarRun [%d]",TAG_GOLF_CAR,  pLocalParam->nDriveDistanceFromCarRun);
		}
		break;
	case 0x42:
		{
			pLocalParam->nDriveTimeFromCarRun = 0;
			memcpy(&pLocalParam->nDriveTimeFromCarRun, p + 1, 3);
			LOGD("[%s] pLocalParam->nDriveTimeFromCarRun [%d]",TAG_GOLF_CAR,  pLocalParam->nDriveTimeFromCarRun);
		}
		break;
	case 0x43:
		{
			pLocalParam->nCarSpeedFromCarRun = 0;
			memcpy(&pLocalParam->nCarSpeedFromCarRun, p + 1, 3);
			LOGD("[%s] pLocalParam->nCarSpeedFromCarRun [%d]",TAG_GOLF_CAR,  pLocalParam->nCarSpeedFromCarRun);
		}
		break;
	case 0x44:
		{
			pLocalParam->nAvgOilConsumeFromLongTimeRun = 0;
			memcpy(&pLocalParam->nAvgOilConsumeFromLongTimeRun, p + 1, 3);
			LOGD("[%s] pLocalParam->nAvgOilConsumeFromLongTimeRun [%d]",TAG_GOLF_CAR,  pLocalParam->nAvgOilConsumeFromLongTimeRun);
		}
		break;
	case 0x45:
		{
			pLocalParam->nDriveDistanceFromLongTimeRun = 0;
			memcpy(&pLocalParam->nDriveDistanceFromLongTimeRun, p + 1, 4);
			LOGD("[%s] pLocalParam->nDriveDistanceFromLongTimeRun [%d]",TAG_GOLF_CAR,  pLocalParam->nDriveDistanceFromLongTimeRun);
		}
		break;
	case 0x46:
		{
			pLocalParam->nDriveTimeFromLongTimeRun = 0;
			memcpy(&pLocalParam->nDriveTimeFromLongTimeRun, p + 1, 3);
			LOGD("[%s] pLocalParam->nDriveTimeFromLongTimeRun [%d]",TAG_GOLF_CAR,  pLocalParam->nDriveTimeFromLongTimeRun);
		}
		break;
	case 0x47:
		{
			pLocalParam->nCarSpeedFromLongTimeRun = 0;
			memcpy(&pLocalParam->nCarSpeedFromLongTimeRun, p + 1, 3);
			LOGD("[%s] pLocalParam->nCarSpeedFromLongTimeRun [%d]",TAG_GOLF_CAR,  pLocalParam->nCarSpeedFromLongTimeRun);
		}
		break;
	case 0x48:
		{
			pLocalParam->nAvgOilConsumeFromAddOil = 0;
			memcpy(&pLocalParam->nAvgOilConsumeFromAddOil, p + 1, 3);
			LOGD("[%s] pLocalParam->nAvgOilConsumeFromAddOil [%d]",TAG_GOLF_CAR,  pLocalParam->nAvgOilConsumeFromAddOil);
		}
		break;
	case 0x49:
		{
			pLocalParam->nDriveDistanceFromAddOil = 0;
			memcpy(&pLocalParam->nDriveDistanceFromAddOil, p + 1, 4);
			LOGD("[%s] pLocalParam->nDriveDistanceFromAddOil [%d]",TAG_GOLF_CAR,  pLocalParam->nDriveDistanceFromAddOil);
		}
		break;
	case 0x4A:
		{
			pLocalParam->nDriveTimeFromAddOil = 0;
			memcpy(&pLocalParam->nDriveTimeFromAddOil, p + 1, 3);
			LOGD("[%s] pLocalParam->nDriveTimeFromAddOil [%d]",TAG_GOLF_CAR,  pLocalParam->nDriveTimeFromAddOil);
		}
		break;
	case 0x4B:
		{
			pLocalParam->nDriveSpeedFromAddOil = 0;
			memcpy(&pLocalParam->nDriveSpeedFromAddOil, p + 1, 3);
			LOGD("[%s] pLocalParam->nDriveSpeedFromAddOil [%d]",TAG_GOLF_CAR,  pLocalParam->nDriveSpeedFromAddOil);
		}
		break;
	// ¿Õµ÷
	case 0x4C:
		{
			exterToAC_golf(p + 1, len - 1);
			LOGD("[%s] MSG",TAG_GOLF_AC);
		}
		break;
	case 0x4D://ÇÐ¿Õµ÷Ò³
		{
			exterToAC_golf_ctrl(p[1]);
			LOGD("[%s] MSG",TAG_GOLF_AC);
		}
		break;
	case 0x4E://AC 1->open, 0->close
		exterToAC_golf_acState(p[1]);
		break;
	// À¶ÑÀ
	case 0x50:
	case 0x51:
	case 0x52:
		{
			exterToBT_golf(p, len);
			LOGD("[%s] phone list request",TAG_GOLF_BLUETOOTH);
		}
		break;
	// GPS
	case 0x60:
		{
			exterToGPS_golf(p, len);
			LOGD("[%s] request playSound",TAG_GOLF_GPS);
		}
		break;
	case 0x7B:
			{
				pLocalParam->eCarDoorWindow_FL = (p[1] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				pLocalParam->eCarDoorWindow_FR = (p[2] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				pLocalParam->eCarDoorWindow_RL = (p[3] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				pLocalParam->eCarDoorWindow_RR = (p[4] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				LOGD("[%s] [%s] CarDoorWindow FL,FR(%x,%x):",TAG_GOLF_CAR,__FUNCTION__,pLocalParam->eCarDoorWindow_FL,pLocalParam->eCarDoorWindow_FR);
				LOGD("[%s] [%s] CarDoorWindow RL RR(%x,%x)",TAG_GOLF_CAR,__FUNCTION__,pLocalParam->eCarDoorWindow_RL,pLocalParam->eCarDoorWindow_RR);
			}
			break;
	case 0x7C:
				{
					pLocalParam->eCarDormer = (p[1] == 0x00) ? CAR_DORMER_CLOSE  : CAR_DORMER_OPEN;
					LOGD("[%s] [%s] pLocalParam->eCarDormer:%x",TAG_GOLF_CAR,__FUNCTION__,pLocalParam->eCarDormer);
				}
			break;
	case 0x7D:
				{
					pLocalParam->eCarDoorLocker = (p[1] == 0x00) ? CAR_DOOR_LOCKER_UNLOCK : CAR_DOOR_LOCKER_LOCK;
					LOGD("[%s] [%s] pLocalParam->eCarDoorLocker:%x",TAG_GOLF_CAR,__FUNCTION__,pLocalParam->eCarDoorLocker);
				}
			break;
	case 0x7E:
				{
					pLocalParam->eHeadLight = (p[1] == 0x00) ? HEAD_LIGHT_CLOSE: HEAD_LIGHT_OPEN;
					LOGD("[%s] [%s] pLocalParam->eHeadLight:%x",TAG_GOLF_CAR,__FUNCTION__,pLocalParam->eHeadLight);
				}
			break;
	case 0xF0://žßµÍÅä 0->žßÅä, 1->µÍÅä
		{
			pLocalParam->nGolfCarStyle = p[1];
			LOGD("[%s] car type is [%d]",TAG_GOLF_CAR, p[1]);
		}
		break;
	case 0xF1:
		{
			pLocalParam->nCanSendChineseToDZCarScreen = p[1];
			LOGD("[%s] nCanSendChineseToDZCarScreen is [%d]",TAG_GOLF_CAR, p[1]);
		}
		break;
	case 0x64:
		{
			pLocalParam->bCurMODE_State = p[1];
			LOGD("[%s] MODE OSD PAGE is [%d]",TAG_GOLF_CAR, p[1]);
		}
		break;
	case 0x65:
		{
			if(pLocalParam->eCar_DrivingMode == (E_CAR_DRIVING_MODE)p[1])
				return;
			SetTimer(TIME_MODE_GOTO_MODE_PAGE,1,EXTCAR_TIMER_ID_GOLF_MODE_HIDEBOX);
			pLocalParam->eCar_DrivingMode = (E_CAR_DRIVING_MODE)p[1];
			LOGD("[%s] Driving Mode is [%d]",TAG_GOLF_CAR, p[1]);
		}
		break;
	case 0x66:
		{
			if((E_CAR_DAMPING_SYSTEM_MOD)p[1] == CAR_DAMPING_SYSTEM_COMFORT || (E_CAR_DAMPING_SYSTEM_MOD)p[1] == CAR_DAMPING_SYSTEM_STANDARD || (E_CAR_DAMPING_SYSTEM_MOD)p[1] == CAR_DAMPING_SYSTEM_SPORT)
			{
				pLocalParam->eCar_DampingSystemMode = (E_CAR_DAMPING_SYSTEM_MOD)p[1];
			}
			if((E_CAR_STEERING_WHEEL_MOD)p[2] == CAR_STEERING_WHEEL_MOD_STANDARD || (E_CAR_STEERING_WHEEL_MOD)p[2] == CAR_STEERING_WHEEL_MOD_SPORT )
			{
				pLocalParam->eCar_SteeringWheelMode = (E_CAR_STEERING_WHEEL_MOD)p[2];
			}
			if((E_CAR_DRIVING_GEAR_MOD)p[3] == CAR_DRIVING_GEAR_MOD_STANDARD || (E_CAR_DRIVING_GEAR_MOD)p[3] == CAR_DRIVING_GEAR_MOD_SPORT || (E_CAR_DRIVING_GEAR_MOD)p[3] == CAR_DRIVING_GEAR_MOD_LOW_OIL)
			{
				pLocalParam->eCar_DrivingGearMode = (E_CAR_DRIVING_GEAR_MOD)p[3];
			}
			if((E_CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD)p[4] == CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_STANDARD || (E_CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD)p[4] == CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_SPORT || (E_CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD)p[4] == CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_LOW_OIL)
			{
				pLocalParam->eCar_Dynamic_Headlight_FollowerMode = (E_CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD)p[4];
			}	
			if((E_CAR_AC_MOD)p[5] == AC_MODE_STANDARD || (E_CAR_AC_MOD)p[5] == AC_MODE_LOW_OIL )
			{
				pLocalParam->eCar_AcMode = (E_CAR_AC_MOD)p[5];
			}
			if((E_CAR_INTERNAL_ENGINE_SOUNDS_MOD)p[6] == CAR_ENGINE_SOUNDS_MOD_STANDARD || (E_CAR_INTERNAL_ENGINE_SOUNDS_MOD)p[6] == CAR_ENGINE_SOUNDS_MOD_SPORT || (E_CAR_INTERNAL_ENGINE_SOUNDS_MOD)p[6] == CAR_ENGINE_SOUNDS_MOD_LOW_OIL)
			{
				pLocalParam->eCar_InternalEngineSoundsMode = (E_CAR_INTERNAL_ENGINE_SOUNDS_MOD)p[6];
			}
			LOGD("[%s]  process_carGolfPersonalizationSet [%d] [%d] [%d] [%d] [%d] [%d]",TAG_GOLF_CAR, p[1],p[2],p[3],p[4],p[5],p[6]);
		}
		break;
	case 0x67:
		{
			pLocalParam->uModeKeyValue = p[1];
			LOGD("[%s] MODE OSD PAGE key value [%d]",TAG_GOLF_CAR, p[1]);
		}
		break;
	case 0x68:
		{
			process_carRequestOpenMode();
		}
		break;
	case 0x80://distance Unit
			pLocalParam->eDistanceUnit = (E_DISTANCE_UNIT)p[1];
			LOGD("[%s] pLocalParam->eDistanceUnit [%d]",TAG_GOLF_CAR, p[1]);
		break;
	case 0x81://speed Unit
			pLocalParam->eSpeedUnit = (E_SPEED_UNIT)p[1];
			LOGD("[%s] pLocalParam->eSpeedUnit [%d]",TAG_GOLF_CAR, p[1]);
		break;
	}
	process_golf_carInfo();
}

void process_golf_carInfo()
{
	switch(pLocalParam->nCurCmd)
	{
	case 0x01:
		process_SafetyBeltInfo();
		break;
	case 0x02:
		process_HandLockerInfo();
		break;
	case 0x03:
		process_EngineSpeedInfo();
		break;
	case 0x04:
		process_InstantSpeedInfo();
		break;
	case 0x05:
		process_DegreeOfCarGroundInfo();
		break;
	case 0x06:
		process_DegreeOfWaterInfo();
		break;
	case 0x09:
		process_DoorInfo();
		break;
	case 0x0A:
		process_BatteryVoltageInfo();
		break;
	case 0x0B:
		process_OilRemindInfo();
		break;
	case 0x0C:
		process_CleanWaterStatusInfo();
		break;
	case 0x10:
		process_driverAssistSystemdDriveMode();
		break;
	case 0x11:
		process_driverAssistSystemLastSelectGap();
		break;
	case 0x12:
		process_driverAssistSystemGap();
		break;
	case 0x13:
		process_preAssistSystemActivation();
		break;
	case 0x14:
		process_preAssistSystemWarning();
		break;
	case 0x15:
		process_preAssistSystemGapWarning();
		break;
	case 0x16:
		process_fatigueReconizeSystemActivation();
		break;
	case 0x17:
		process_escSystemActivation();
		break;
	case 0x18:
		process_tireType();
		break;
	case 0x19:
		process_carSpeedWarning();
		break;
	case 0x1A:
		process_lightSystemConnect();
		break;
	case 0x1B:
		process_lightSystemAuto();
		break;
	case 0x1C:
		process_lightSystemDirection();
		break;
	case 0x1D:
		process_lightSystemDriveRule();
		break;
	case 0x1E:
		process_lightSystemGoHome();
		break;
	case 0x1F:
		process_lightSystemLeaveHome();
		break;
	case 0x20:
		process_lightSystemMeter();
		break;
	case 0x21:
		process_lightSystemDoor();
		break;
	case 0x22:
		process_lightSystemFeet();
		break;
	case 0x23:
		process_windowCtrl();
		break;
	case 0x24:
		process_unlockDoor();
		break;
	case 0x25:
		process_autoLockDoor();
		break;
	case 0x26:
		process_backMirror();
		process_MirrorsInTheFold_HasParking();
		break;
	case 0x27:
		process_autoWiper();
		break;
	case 0x28:
		process_backWiperWhenBackCar();
		break;
	case 0x29:
		process_backCarSystemActivation();
		break;
	case 0x2A:
		process_backCarSystemPreAudio();
		break;
	case 0x2B:
		process_backCarSystemRearAudio();
		break;
	case 0x2C:
		process_functionDisplay();
		break;
	case 0x2D:
		process_cozyEconomyTipDisplay();
		break;
	case 0x2E:
		process_recoveryDriveDataFromStart();
		break;
	case 0x2F:
		process_recoveryDriveDataFromLongTime();
		break;
	case 0x30:
		process_degreeUnit();
		break;
	case 0x31:
		process_volumeUnit();
		break;
	case 0x32:
		process_oilConsumeUnit();
		break;
	case 0x33:
		process_tireCompressUnit();
		break;
	case 0x34:
		process_systemTime();
		break;
	case 0x35:
		process_systemDate();
		break;
	case 0x36:
		process_SystemDateFormat();
		break;
	case 0x37:
		process_recoverySetting();
		break;
	case 0x38:
		process_languageSetting();
		break;
	case 0x39:
		process_radarAudioDoor();
		break;
	case 0x3A:
		process_vim();
		break;
	case 0x3B:
		process_carDistanceCheck();
		break;
	case 0x3C:
		process_carTimeCheck();
		break;
	case 0x3D:
		process_engineOilDistanceCheck();
		break;
	case 0x3E:
		process_engineOilTimeCheck();
		break;
	case 0x3F:
		process_distanceLeaveCanRun();
		break;
	case 0x40:
		process_avgOilConsumeFromCarRun();
		break;
	case 0x41:
		process_driveDistanceFromCarRun();
		break;
	case 0x42:
		process_driveTimeFromCarRun();
		break;
	case 0x43:
		process_carSpeedFromCarRun();
		break;
	case 0x44:
		process_avgOilConsumeFromLongTimeRun();
		break;
	case 0x45:
		process_driveDistanceFromLongTimeRun();
		break;
	case 0x46:
		process_driveTimeFromLongTimeRun();
		break;
	case 0x47:
		process_carSpeedFromLongTimeRun();
		break;
	case 0x48:
		process_avgOilConsumeFromAddOil();
		break;
	case 0x49:
		process_driveDistanceFromAddOil();
		break;
	case 0x4A:
		process_driveTimeFromAddOil();
		break;
	case 0x4B:
		process_driveSpeedFromAddOil();
		break;
	case 0x7B:
		process_car_door_window();
		break;
	case 0x7C:
		process_car_dormer();
		break;
	case 0x7D:
		process_car_locker();
		break;
	case 0x7E:
		process_car_head_light();
		break;
	case 0xF0:
		process_carStyle();
		break;
	case 0x64:
		process_carIsGotoModePage();
		break;
	case 0x65:
		process_carGolfModeState();
		break;
	case 0x66:
		process_carGolfPersonalizationSet();
		break;

	case 0x67:
		process_carGolfModeKeyValue();
		break;
	case 0x80:
		process_distanceUnit();
		break;
	case 0x81:
		process_speedUnit();
		break;
	}
}

/*golf 7*/
//ŒÝÊ»Ô±žšÖúÏµÍ³
void process_driverAssistSystemdDriveMode()
{
	int nMap[SIZE_MAP_ENUM] = {0};
	nMap[DRIVE_MODE_STANDAR] = STRING_CARINFO_GOLD_SETUP_DRVING_PROGRAM_2;
	nMap[DRIVE_MODE_SPORT] = STRING_CARINFO_GOLD_SETUP_DRVING_PROGRAM_3;
	nMap[DRIVE_MODE_ECONOMY] = STRING_CARINFO_GOLD_SETUP_DRVING_PROGRAM_1;
	nMap[DRIVE_MODE_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;
	if (pLocalParam->eDriveMode < SIZE_MAP_ENUM)
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TRAVEL_PROGRAM_TXT, nMap[pLocalParam->eDriveMode]);
}
void process_driverAssistSystemLastSelectGap()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT3_ON, pLocalParam->eLastSelectGap);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT3_OFF, !pLocalParam->eLastSelectGap);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_CHECKBOX_4, pLocalParam->eLastSelectGap);

	setControllable(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_DISTANCE_UP, !pLocalParam->eLastSelectGap);
	setControllable(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_DISTANCE_DOWN, !pLocalParam->eLastSelectGap);
}
void process_driverAssistSystemGap()
{
	int nMap[SIZE_MAP_ENUM] = {0};
	nMap[GAP_VERY_SMALL] = STRING_CARINFO_GOLD_SETUP_CAR_DISTANT_1;
	nMap[GAP_SMALL] = STRING_CARINFO_GOLD_SETUP_CAR_DISTANT_2;
	nMap[GAP_MID] = STRING_CARINFO_GOLD_SETUP_CAR_DISTANT_3;
	nMap[GAP_BIG] = STRING_CARINFO_GOLD_SETUP_CAR_DISTANT_4;
	nMap[GAP_VERY_BIG] = STRING_CARINFO_GOLD_SETUP_CAR_DISTANT_5;
	nMap[GAP_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;
	if (pLocalParam->eGap < SIZE_MAP_ENUM)
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_DISTANCE_TXT, nMap[pLocalParam->eGap]);
}
//Ç°²¿žšÖúÏµÍ³
void process_preAssistSystemActivation()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT1_ON, pLocalParam->ePreAssistSystemActivation);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT1_OFF, !pLocalParam->ePreAssistSystemActivation);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_CHECKBOX_1, pLocalParam->ePreAssistSystemActivation);
}
void process_preAssistSystemWarning()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_THE_FRONT_ON, pLocalParam->ePreAssistSystemWarning);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_THE_FRONT_OFF, !pLocalParam->ePreAssistSystemWarning);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_CHECKBOX_2, pLocalParam->ePreAssistSystemWarning);

}
void process_preAssistSystemGapWarning()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_SHOW_ON, pLocalParam->ePreAssistSystemGapWarning);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_SHOW_OFF, !pLocalParam->ePreAssistSystemGapWarning);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_CHECKBOX_3, pLocalParam->ePreAssistSystemGapWarning);
}
//Æ£ÀÍŒÝÊ»Ê¶±ðÏµÍ³
void process_fatigueReconizeSystemActivation()
{
	if (pLocalParam->eFatigueReconizeSystemActivation == FATIGUE_RECONIZE_SYSTEM_ACTIVATION_YES)
	{
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT2_ON, 1);
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT2_OFF, 0);
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_CHECKBOX_5, 1);

	}
	else
	{
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT2_ON, 0);
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT2_OFF, 1);
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_CHECKBOX_5, 0);
	}
}
//ESCÏµÍ³
void process_escSystemActivation()
{
	if (pLocalParam->eEscSystemActivation == ESC_SYSTEM_ACTIVATION_YES)
		{
			setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SYSTEM_ON, 1);
			setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SYSTEM_OFF, 0);

			setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SYSTEM_CHECKBOX, 1);
		}
	else if (pLocalParam->eEscSystemActivation == ESC_SYSTEM_ACTIVATION_NO)
		{
			setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SYSTEM_ON, 0);
			setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SYSTEM_OFF, 1);

			setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SYSTEM_CHECKBOX, 0);
		}

}
//ÂÖÌ¥
void process_tireType(){}
void process_carSpeedWarning()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_ON, pLocalParam->eCarSpeedWarning);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_OFF, !pLocalParam->eCarSpeedWarning);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_ALARM_CHECKBOX, pLocalParam->eCarSpeedWarning);


	setControllable(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_UNITS_ON, pLocalParam->eCarSpeedWarning);
	setControllable(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_UNITS_OFF, pLocalParam->eCarSpeedWarning);

	u8 ansiBuf[20] = {0};
	sprintf((char*)ansiBuf, "%dkm/h", pLocalParam->nCarSpeedWarning);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_UNITS_TXT, ansiBuf, strlen((char*)ansiBuf));
}
//µÆ¹â
void process_lightSystemConnect()
{
	int nMap[SIZE_MAP_ENUM] = {0};
	nMap[LIGHT_SYSTEM_CONNECT_AHEAD] = STRING_CARINFO_GOLD_SETUP_CONNEC_TIME_1;
	nMap[LIGHT_SYSTEM_CONNECT_TIMELY] = STRING_CARINFO_GOLD_SETUP_CONNEC_TIME_2;
	nMap[LIGHT_SYSTEM_CONNECT_DELAY] = STRING_CARINFO_GOLD_SETUP_CONNEC_TIME_3;
	nMap[LIGHT_SYSTEM_CONNECT_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;
	if (pLocalParam->eLightSystemConnect < SIZE_MAP_ENUM)
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TURN_ON_TIME_TXT, nMap[pLocalParam->eLightSystemConnect]);
}
void process_lightSystemAuto()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_LIGHTS_ON, pLocalParam->eLightSystemAuto);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_LIGHTS_OFF, !pLocalParam->eLightSystemAuto);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_CHECKBOX_1, pLocalParam->eLightSystemAuto);
}
void process_lightSystemDirection()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TURN_LIGHTS_ON, pLocalParam->eLightSystemDirection);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TURN_LIGHTS_OFF, !pLocalParam->eLightSystemDirection);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_CHECKBOX_2, pLocalParam->eLightSystemDirection);
}
void process_lightSystemDriveRule()
{
	int nMap[SIZE_MAP_ENUM] = {0};
	nMap[DRIVE_RULE_RIGHT] = STRING_CARINFO_GOLD_SETUP_DRVING_SIDE_1;
	nMap[DRIVE_RULE_LEFT] = STRING_CARINFO_GOLD_SETUP_DRVING_SIDE_2;
	nMap[DRIVE_RULE_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;
	if (pLocalParam->eDriveRule < SIZE_MAP_ENUM)
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TRAVEL_MODE_TXT, nMap[pLocalParam->eDriveRule]);
}
void process_lightSystemGoHome()
{
	u8 ansiBuf[20] = {0};
	sprintf((char*)ansiBuf, "%dS", pLocalParam->nGoHomeModeTime);
	if (pLocalParam->nGoHomeModeTime > 0)
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_RETURN_HOME_MODE_TXT, ansiBuf, strlen((char*)ansiBuf));
	else
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_RETURN_HOME_MODE_TXT, STRINGID_CAR_INFO_CLOSE);
}
void process_lightSystemLeaveHome()
{
	u8 ansiBuf[20] = {0};
	sprintf((char*)ansiBuf, "%dS", pLocalParam->nLeaveHomeModeTime);
	if (pLocalParam->nLeaveHomeModeTime > 0)
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_HOME_MODE_TXT, ansiBuf, strlen((char*)ansiBuf));
	else
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_HOME_MODE_TXT, STRINGID_CAR_INFO_CLOSE);
}
void process_lightSystemMeter()
{
	u8 ansiBuf[20] = {0};
	sprintf((char*)ansiBuf, "%d%%", pLocalParam->nMeterLightBrightness);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_METER_TXT, ansiBuf, strlen((char*)ansiBuf));
}
void process_lightSystemDoor()
{
	u8 ansiBuf[20] = {0};
	sprintf((char*)ansiBuf, "%d%%", pLocalParam->nDoorLightBrightness);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_CAR_ENVIRONMENT_TXT, ansiBuf, strlen((char*)ansiBuf));
}
void process_lightSystemFeet()
{
	u8 ansiBuf[20] = {0};
	sprintf((char*)ansiBuf, "%d%%", pLocalParam->nFeetLightBrightness);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_FOOT_SPACE_TXT, ansiBuf, strlen((char*)ansiBuf));
}
//³µŽ°
void process_windowCtrl()
{
	int nMap[SIZE_MAP_ENUM * 3] = {0};
	nMap[WINDOW_CTRL_CLOSE] = STRING_CARINFO_GOLD_SETUP_CARWINDOW_OPEN_3;
	nMap[WINDOW_CTRL_DRIVER_SIDE] = STRING_CARINFO_GOLD_SETUP_CARWINDOW_OPEN_1;
	nMap[WINDOW_CTRL_ALL_OPEN] = STRING_CARINFO_GOLD_SETUP_CARWINDOW_OPEN_2;
	nMap[WINDOW_CTRL_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;
	if (pLocalParam->eWindowCtrl < SIZE_MAP_ENUM * 3)
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_OPEN_WINDOW_CONVENIENT_TXT, nMap[pLocalParam->eWindowCtrl]);
}
//³µÃÅËø
void process_unlockDoor()
{
	int nMap[SIZE_MAP_ENUM] = {0};
	nMap[DOOR_CTRL_SINGLE_UNLOCK] = STRING_CARINFO_GOLD_SETUP_DOOR_LOCK_1;
	nMap[DOOR_CTRL_ONE_SIDE_UNLOCK] = STRING_CARINFO_GOLD_SETUP_DOOR_LOCK_3;
	nMap[DOOR_CTRL_ALL_UNLOCK] = STRING_CARINFO_GOLD_SETUP_DOOR_LOCK_2;
	nMap[DOOR_CTRL_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;
	if (pLocalParam->eDoorCtrl < SIZE_MAP_ENUM)
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_CENTRAL_TXT, nMap[pLocalParam->eDoorCtrl]);
}

void process_autoLockDoor()
{
	if (DOOR_AUTO_LOCK_YES == pLocalParam->eDoorAutoLock)
	{
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_AUTOMATIC_LOCKING_ON, 1);
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_AUTOMATIC_LOCKING_OFF, 0);
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_ON_OFF_CHECKBOX, 1);
	}
	else
	{
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_AUTOMATIC_LOCKING_ON, 0);
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_AUTOMATIC_LOCKING_OFF, 1);
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_ON_OFF_CHECKBOX, 0);
	}
}
//ºóÊÓŸµ
void process_backMirror()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REARVIEW_MIRROR_ON, pLocalParam->eBackMirrorSync);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REARVIEW_MIRROR_OFF, !pLocalParam->eBackMirrorSync);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_CHECKBOX_1, pLocalParam->eBackMirrorSync);

	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REVERSE_GEAR_ON, pLocalParam->eBackMirrorReverseCar);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REVERSE_GEAR_OFF, !pLocalParam->eBackMirrorReverseCar);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_CHECKBOX_2, pLocalParam->eBackMirrorReverseCar);

}
//Óê¹Î
void process_autoWiper()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_RAIN_ON, pLocalParam->eWiperAuto);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_RAIN_OFF, !pLocalParam->eWiperAuto);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_CHECKBOX_3, pLocalParam->eWiperAuto);
}
void process_backWiperWhenBackCar()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REAR_WINDOW_ON, pLocalParam->eBackWinCleanReverseCar);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REAR_WINDOW_OFF, !pLocalParam->eBackWinCleanReverseCar);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_CHECKBOX_4, pLocalParam->eBackWinCleanReverseCar);
}
//×€³µºÍµ÷³µ--µ¹³µÀ×ŽïÏµÍ³
void process_backCarSystemActivation()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_AUTOMATIC_ACTIVATION_ON, pLocalParam->eReverseCarSystemAutoActivation);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_AUTOMATIC_ACTIVATION_OFF, !pLocalParam->eReverseCarSystemAutoActivation);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_AUTOMATIC_CHECKBOX, pLocalParam->eReverseCarSystemAutoActivation);
}
void process_backCarSystemPreAudio()
{
	int s = pLocalParam->nCarFrontAudioParam;
	int yl = s >> 8;
	int yd = s & 0x00FF;
	u8 ansiBuf[20] = {0};
	sprintf((char*)ansiBuf, "%d", yl);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_FRONT_VOLUME_TXT, ansiBuf, strlen((char*)ansiBuf));
	memset(ansiBuf, 0, sizeof(ansiBuf));
	sprintf((char*)ansiBuf, "%d", yd);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_FRONT_PITCH_TXT, ansiBuf, strlen((char*)ansiBuf));
}
void process_backCarSystemRearAudio()
{
	int s = pLocalParam->nCarRearAudioParam;
	int yl = s >> 8;
	int yd = s & 0x00FF;
	u8 ansiBuf[20] = {0};
	sprintf((char*)ansiBuf, "%d", yl);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_REAR_VOLUME_TXT, ansiBuf, strlen((char*)ansiBuf));
	memset(ansiBuf, 0, sizeof(ansiBuf));
	sprintf((char*)ansiBuf, "%d", yd);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_REAR_PITCH_TXT, ansiBuf, strlen((char*)ansiBuf));
}
//¶à¹ŠÄÜÏÔÊŸ
void process_functionDisplay()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CURRENT_FUEL_ON, pLocalParam->eOilConsumeSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CURRENT_FUEL_OFF, !pLocalParam->eOilConsumeSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_AVERAGE_FUEL_ON, pLocalParam->eOilAvgConsumeSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_AVERAGE_FUEL_OFF, !pLocalParam->eOilAvgConsumeSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_TRAVEL_TIME_ON, pLocalParam->eDriveTimeSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_TRAVEL_TIME_OFF, !pLocalParam->eDriveTimeSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_MILEAGE_ON, pLocalParam->eDriveDistanceSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_MILEAGE_OFF, !pLocalParam->eDriveDistanceSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_AVERAGE_SPEED_ON, pLocalParam->eAvgSpeedSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_AVERAGE_SPEED_OFF, !pLocalParam->eAvgSpeedSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_DIGTAL_ON, pLocalParam->eDigitSpeedDisplay);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_DIGTAL_OFF, !pLocalParam->eDigitSpeedDisplay);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_SPEED_ALARM_ON, pLocalParam->eCarSpeedWarningDisplay);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_SPEED_ALARM_OFF, !pLocalParam->eCarSpeedWarningDisplay);
	//4s ui
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_1, pLocalParam->eOilConsumeSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_2, pLocalParam->eOilAvgConsumeSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_5, pLocalParam->eDriveTimeSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_6, pLocalParam->eDriveDistanceSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_7, pLocalParam->eAvgSpeedSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_8, pLocalParam->eDigitSpeedDisplay);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_9, pLocalParam->eCarSpeedWarningDisplay);
}

void process_cozyEconomyTipDisplay()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_COZY_ON, pLocalParam->eCozyDeviceSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_COZY_OFF, !pLocalParam->eCozyDeviceSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_ECONOMY_ON, pLocalParam->eEconomyDriveTip);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_ECONOMY_OFF, !pLocalParam->eEconomyDriveTip);

	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_3, pLocalParam->eCozyDeviceSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_4, pLocalParam->eEconomyDriveTip);
}
//»ÖžŽÊýŸÝ
void process_recoveryDriveDataFromStart()
{

}
void process_recoveryDriveDataFromLongTime()
{

}
//µ¥Î»ÉèÖÃ
void process_degreeUnit()
{
	int szMap[SIZE_MAP_ENUM] = {0};
	szMap[DISTANCE_UNIT_KM] = STRINGID_TPMS_TEMPERATURE_UNITS_C;
	szMap[DISTANCE_UNIT_MI] = STRINGID_TPMS_TEMPERATURE_UNITS_F;
	szMap[DISTANCE_UNIT_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;

	if (pLocalParam->eDegreeUnit < SIZE_MAP_ENUM)
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_TEMPERATURE_TXT, szMap[pLocalParam->eDegreeUnit]);
}
void process_distanceUnit()
{
	int szMap[SIZE_MAP_ENUM] = {0};
	szMap[DISTANCE_UNIT_KM] = STRING_CARINFO_GOLD_SETUP_DISTANCE_KM;
	szMap[DISTANCE_UNIT_MI] = STRING_CARINFO_GOLD_SETUP_DISTANCE_MI;
	szMap[DISTANCE_UNIT_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;

	if (pLocalParam->eDistanceUnit < SIZE_MAP_ENUM)
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_DISTANCE_TXT, szMap[pLocalParam->eDistanceUnit]);
}
void process_speedUnit()
{
	int szMap[SIZE_MAP_ENUM] = {0};
	szMap[SPEED_UNIT_KM_P_H] = STRING_CARINFO_GOLD_SETUP_SPEED_KM_H;
	szMap[SPEED_UNIT_M_P_H] = STRING_CARINFO_GOLD_SETUP_SPEED_MP_H;
	szMap[SPEED_UNIT_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;

	if (pLocalParam->eSpeedUnit < SIZE_MAP_ENUM)
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_SPEED_TXT, szMap[pLocalParam->eSpeedUnit]);
}
void process_volumeUnit()
{
	char szMap[SIZE_MAP_ENUM][20] = {{0}};
	memcpy(szMap[VOLUME_UNIT_L],  "L", strlen("L"));
	memcpy(szMap[VOLUME_UNIT_GALON_E], "GAL-E", strlen("GAL-E"));
	memcpy(szMap[VOLUME_UNIT_GALON_A], "GAL-A", strlen("GAL-A"));
	memcpy(szMap[VOLUME_UNIT_UNKNOW], "N/A", strlen("N/A"));
	if (pLocalParam->eVolumeUnit < SIZE_MAP_ENUM)
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_VOLUME_TXT, (u8*)szMap[pLocalParam->eVolumeUnit], strlen(szMap[pLocalParam->eVolumeUnit]));
}
void process_oilConsumeUnit()
{
	char szMap[SIZE_MAP_ENUM][20] = {{0}};
	memcpy(szMap[OIL_CONSUME_UNIT_MPG_E], "MPG-E", strlen("MPG-E"));
	memcpy(szMap[OIL_CONSUME_UNIT_MPG_A], "MPG-A", strlen("MPG-A"));
	memcpy(szMap[OIL_CONSUME_UNIT_L_PER_100_KM], "L/100km", strlen("L/100km"));
	memcpy(szMap[OIL_CONSUME_UNIT_KM_PER_L], "km/L", strlen("km/L"));
	memcpy(szMap[OIL_CONSUME_UNIT_UNKNOW], "N/A", strlen("N/A"));
	if (pLocalParam->eOilConsumeUnit < SIZE_MAP_ENUM)
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_FUEL_CONSUM_PTION_TXT, (u8*)szMap[pLocalParam->eOilConsumeUnit], strlen(szMap[pLocalParam->eOilConsumeUnit]));
}

void process_carola_oilConsumeUnit()
{
	char szMap[SIZE_MAP_ENUM][20] = {{0}};
	memcpy(szMap[OIL_CONSUME_UNIT_MPG_E], "MPG-E", strlen("MPG-E"));
	memcpy(szMap[OIL_CONSUME_UNIT_MPG_A], "MPG-A", strlen("MPG-A"));
	memcpy(szMap[OIL_CONSUME_UNIT_L_PER_100_KM], "L/100km", strlen("L/100km"));
	memcpy(szMap[OIL_CONSUME_UNIT_KM_PER_L], "km/L", strlen("km/L"));
	memcpy(szMap[OIL_CONSUME_UNIT_UNKNOW], "N/A", strlen("N/A"));
	if (pLocalParam->eOilConsumeUnit < SIZE_MAP_ENUM)
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_CAROLA_SET_OILPOINT_TEXT, (u8*)szMap[pLocalParam->eOilConsumeUnit], strlen(szMap[pLocalParam->eOilConsumeUnit]));
}

void process_MirrorsInTheFold_HasParking()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_IN_THE_FOLD_HAS_PARKING_ON, pLocalParam->emMirrorsIntheFoldParkedSelect);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_IN_THE_FOLD_HAS_PARKING_OFF, !pLocalParam->emMirrorsIntheFoldParkedSelect);
}

void process_tireCompressUnit(){}
//Ê±Œä
void process_systemTime(){}
void process_systemDate(){}
void process_SystemDateFormat(){}
//žŽÎ»³ö³§ÉèÖÃ
void process_recoverySetting()
{

}
//ÓïÑÔ
void process_languageSetting(){}
//À×ŽïÉùÒô¿ª¹Ø
void process_radarAudioDoor()
{
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_RADAR_RING_DOOR, !pLocalParam->nGolfRadarRingDoor);
}
//vim code
void process_vim()
{
	char szMsg[128] = {0};
	sprintf(szMsg, "%s", (char*)pLocalParam->szVim);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CAR_NUMBER, (u8*)szMsg, strlen(szMsg));
}
//³µ¿öŒì²é
void process_carDistanceCheck()
{
	char szMsg[32] = {0};
	int s = pLocalParam->nMaintainDistanceInfo;
	u8 f = s & 0xFF;
	u8 fh = f >> 4;
	u8 fl = f & 0x0F;
	int dis = (s >> 8) * 100;
	if (fh == 0 || fh == 1)
	{
		sprintf(szMsg, " -- %s", (0 == fl) ? "km" : "mi");
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CHECK_MILEAGE, CARINFO_GOLD_MAINTAIN_REMAIN_MILEAGE);
	}
	else if(fh == 2)
	{
		sprintf(szMsg, " %d %s", dis, (0 == fl) ? "km" : "mi");
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CHECK_MILEAGE, CARINFO_GOLD_MAINTAIN_REMAIN_MILEAGE);
	}
	else if (fh == 3)
	{
		sprintf(szMsg, " %d %s", dis, (0 == fl) ? "km" : "mi");
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CHECK_MILEAGE, CARINFO_GOLD_MAINTAIN_EXCEED_MILEAGE);

		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CHECK_NUMBER_DAYS, CARINFO_GOLD_MAINTAIN_REMAIN_DAYS);
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_CAR_CHECK_DAYS, (u8*)" -- ", strlen(" -- "));
	}
	else
	{
		return;
	}
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_CAR_CHECK_MILEAGES, (u8*)szMsg, strlen(szMsg));
}

void process_carTimeCheck()
{
	char szMsg[32] = {0};
	int s = pLocalParam->nMaintainTimeInfo;
	u8 f = s & 0xFF;
	int time = s >> 8;
	if (f == 0 || f == 1)
	{
		sprintf(szMsg, " -- ");
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CHECK_NUMBER_DAYS, CARINFO_GOLD_MAINTAIN_REMAIN_DAYS);
	}
	else if(f == 2)
	{
		sprintf(szMsg, "%d", time);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CHECK_NUMBER_DAYS, CARINFO_GOLD_MAINTAIN_REMAIN_DAYS);
	}
	else if (f == 3)
	{
		sprintf(szMsg, "%d", time);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CHECK_NUMBER_DAYS, CARINFO_GOLD_MAINTAIN_EXCEED_DAYS);

		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_CAR_CHECK_MILEAGES, (u8*)" -- ", strlen(" -- "));
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CHECK_MILEAGE, CARINFO_GOLD_MAINTAIN_REMAIN_MILEAGE);
	}
	else
	{
		return;
	}
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_CAR_CHECK_DAYS, (u8*)szMsg, strlen(szMsg));
}
//žü»»»úÓÍ
void process_engineOilDistanceCheck()
{
	char szMsg[32] = {0};
	int s = pLocalParam->nMaintainEngineOilDistanceInfo;
	u8 f = s & 0xFF;
	u8 fh = f >> 4;
	u8 fl = f & 0x0F;
	int dis = (s >> 8) * 100;
	if (fh == 0 || fh == 1)
	{
		sprintf(szMsg, " -- %s", (0 == fl) ? "km" : "mi");
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_BACK_REPLACE_MILEAGE, CARINFO_GOLD_MAINTAIN_REMAIN_MAINTENANCE_MILEAGE);
	}
	else if(fh == 2)
	{
		sprintf(szMsg, " %d %s", dis, (0 == fl) ? "km" : "mi");
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_BACK_REPLACE_MILEAGE, CARINFO_GOLD_MAINTAIN_REMAIN_MAINTENANCE_MILEAGE);
	}
	else if (fh == 3)
	{
		sprintf(szMsg, " %d %s", dis, (0 == fl) ? "km" : "mi");
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_BACK_REPLACE_MILEAGE, CARINFO_GOLD_MAINTAIN_EXCEED_MAINTENANCE_MILEAGE);

		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_BACK_REPLACE_SERVICE, CARINFO_GOLD_MAINTAIN_REMAIN_MAINTENANCE_DYAS);
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_OIL_CHECK_DAYS, (u8*)"--", strlen("--"));
	}
	else
	{
		return;
	}
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_OIL_CHECK_MILEAGES, (u8*)szMsg, strlen(szMsg));
}


void process_engineOilTimeCheck()
{
	char szMsg[32] = {0};
	int s = pLocalParam->nMaintainEngineOilTimeInfo;
	u8 f = s & 0xFF;
	int time = s >> 8;
	if (f == 0 || f == 1)
	{
		sprintf(szMsg, "--");
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_BACK_REPLACE_SERVICE, CARINFO_GOLD_MAINTAIN_REMAIN_MAINTENANCE_DYAS);
	}
	else if(f == 2)
	{
		sprintf(szMsg, " %d ", time);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_BACK_REPLACE_SERVICE, CARINFO_GOLD_MAINTAIN_REMAIN_MAINTENANCE_DYAS);
	}
	else if (f == 3)
	{
		sprintf(szMsg, " %d ", time);
		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_BACK_REPLACE_SERVICE, CARINFO_GOLD_MAINTAIN_EXCEED_MAINTENANCE_DYAS);

		setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_BACK_REPLACE_MILEAGE, CARINFO_GOLD_MAINTAIN_REMAIN_MAINTENANCE_MILEAGE);
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_OIL_CHECK_MILEAGES, (u8*)"--", strlen("--"));
	}
	else
	{
		return;
	}
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_OIL_CHECK_DAYS, (u8*)szMsg, strlen(szMsg));
}
//ÐÐ³µÐÅÏ¢
void process_distanceLeaveCanRun()
{
	int data = pLocalParam->nTheDistanceLeaveCarCanRun;
	char szMsg[20] = {0};
	sprintf(szMsg, "%dkm", data);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_CONTINUED_MILEAGE, (u8*)szMsg, strlen(szMsg));
}

void golf_avgOilConsume(int s)
{
	int data = s & 0xFFFF;
	int dw = ((s >> 16) & 0xFF);
	char szMap[4][10] = {"L/100km", "km/l", "MPG-E", "MPG-A"};
	if (dw >=0 && dw <4)
	{
		char szMsg[20] = {0};
		if (data == 0xFFFF)
			sprintf(szMsg, "%s%s", "--", szMap[dw]);
		else
			sprintf(szMsg, "%.1lf%s", data * 0.1, szMap[dw]);
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_FUEL_CONSUMPTION, (u8*)szMsg, strlen(szMsg));
	}
}
void golf_driveDistance(int s)
{
	int data = s & 0xFFFFFF;
	char szMsg[20] = {0};
	sprintf(szMsg, "%.1lfkm", data * 0.1);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_MILEAGE, (u8*)szMsg, strlen(szMsg));
}
void golf_driveTime(int s)
{
	int data = s & 0xFFFFFF;
	char szMsg[20] = {0};
	sprintf(szMsg, "%.1lfh", data / 60.0);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_TRAVEL_TIME, (u8*)szMsg, strlen(szMsg));
}
void golf_carSpeed(int s)
{
	int data = s & 0xFFFF;
	char szMsg[20] = {0};
	sprintf(szMsg, "%.1lfkm/h", data * 0.1);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_AVERAGE_SPEED, (u8*)szMsg, strlen(szMsg));
}
//×ÔÆô¶¯Æð
void process_avgOilConsumeFromCarRun()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_START)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_START);
	golf_avgOilConsume(pLocalParam->nAvgOilConsumeFromCarRun);
}
void process_driveDistanceFromCarRun()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_START)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_START);
	golf_driveDistance(pLocalParam->nDriveDistanceFromCarRun);
}
void process_driveTimeFromCarRun()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_START)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_START);
	golf_driveTime(pLocalParam->nDriveTimeFromCarRun);
}
void process_carSpeedFromCarRun()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_START)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_START);
	golf_carSpeed(pLocalParam->nCarSpeedFromCarRun);
}
//³€Ê±Œä
void process_avgOilConsumeFromLongTimeRun()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_LONG_TIME)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_LONG);
	golf_avgOilConsume(pLocalParam->nAvgOilConsumeFromLongTimeRun);
}
void process_driveDistanceFromLongTimeRun()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_LONG_TIME)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_LONG);
	golf_driveDistance(pLocalParam->nDriveDistanceFromLongTimeRun);
}
void process_driveTimeFromLongTimeRun()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_LONG_TIME)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_LONG);
	golf_driveTime(pLocalParam->nDriveTimeFromLongTimeRun);
}
void process_carSpeedFromLongTimeRun()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_LONG_TIME)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_LONG);
	golf_carSpeed(pLocalParam->nCarSpeedFromLongTimeRun);
}


//ŒÓÓÍÆð
void process_avgOilConsumeFromAddOil()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_ADD_OIL)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_REFUELING);
	golf_avgOilConsume(pLocalParam->nAvgOilConsumeFromAddOil);
}
void process_driveDistanceFromAddOil()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_ADD_OIL)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_REFUELING);
	golf_driveDistance(pLocalParam->nDriveDistanceFromAddOil);
}
void process_driveTimeFromAddOil()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_ADD_OIL)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_REFUELING);
	golf_driveTime(pLocalParam->nDriveTimeFromAddOil);
}
void process_driveSpeedFromAddOil()
{
	if (pLocalParam->eDriveDataType != DRIVE_DATA_TYPE_FROM_ADD_OIL)
		return;
	setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_GOLD_REFUELING);
	golf_carSpeed(pLocalParam->nDriveSpeedFromAddOil);
}

void process_carStyle()
{
	extcarToApp_golfCarStyleSetting(pLocalParam->nGolfCarStyle);
}

void golf_setScreenTime()
{
	time_t now;
	struct tm *timenow;
	time(&now);
	timenow = localtime(&now);
	extcarToHal_set_systemTime(timenow->tm_hour, timenow->tm_min);
	extcarToHal_set_systemDate(timenow->tm_year, timenow->tm_mon, timenow->tm_mday);
	LOGD("[DYB] golf_setScreenTime: y = [%d], m = [%d], d = [%d], h = [%d], m = [%d]",
		timenow->tm_year, timenow->tm_mon, timenow->tm_mday, timenow->tm_hour, timenow->tm_min);
}
/*golf 7*/


void analyseHalMessage_DaZhongCarInfo (unsigned char * p, int len)
{
	if(pLocalParam->eCarModels != CAR_MODELS_DAS_AUTO){
		pLocalParam->eCarModels = CAR_MODELS_DAS_AUTO;
	}

	pLocalParam->nCurCmd = p[0];
	switch(p[0])
	{
		case 0x00:
			{
				/*
				u8 msg[600] = {0};
				int lent = len - 1;
				int a = lent * 3;
				int i, j = 0;
				for (i = 1; i <= lent; i++)
					{
						snprintf((char*)(msg + j) , a - j, "%02X ", p[i]);
						j += 3;
					}
				LOGI("---------------------------------------------->%s", msg);
				*/
				exterToAirCondition(p + 1, len - 1);
			}
			break;
		case 0x01:
			{ 
				pLocalParam->nKeyValue = p[1];
				LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->nKeyValue 0x%02X",pLocalParam->nKeyValue);
				//exterToKey_Da_Zhong_Steer_Key(p[1]);
			}
			break;
		case 0x03:
			{
				u8 pos = p[1];
				u32 distance = 0;
				memcpy(&distance, p + 2, 4);
				LOGD("[analyseHalMessage_DaZhongCarInfo]->Radar: pos is %d, distance is %d \n", pos, distance);
				exterToRadar(pos, distance);
			}
			break;
		case 0x04:
			{
				LOGD("[analyseHalMessage_DaZhongCarInfo]->Radar: strong go to info page param = 0x%02X ", p[1]);
				exterToRadar(p[1]);
			}
			break;
		case 0x10:
			{
				pLocalParam->nDrivingDistance = 0;
				memcpy(&pLocalParam->nDrivingDistance, p + 1, 3);
				LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->nDrivingDistance %d", pLocalParam->nDrivingDistance);
			}
			break;
		case 0x11:
			{
				memcpy(&pLocalParam->nBatteryVoltage, p + 1, 2);
				LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->nBatteryVoltage %d", pLocalParam->nBatteryVoltage);
			}
			break;
		case 0x12:
			{
				memcpy(&pLocalParam->nEngineSpeed, p + 1, 2);
				//LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->nEngineSpeed %d", pLocalParam->nEngineSpeed);
			}
			break;
		case 0x13:// car door
			{
				pLocalParam->nCarDoorStatus = p[1];
				LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->nCarDoorStatus 0x%X", pLocalParam->nCarDoorStatus);
			}
			break;
		case 0x14:// safety belt
			{
				pLocalParam->eSafetyBeltStatus =   ( ((p[1] & 32) && (0 == (p[1] & 16)))  ||  ((p[1] & 128) && (0 == (p[1] & 64))) ) ?  SATETY_BELT_UNLOCKED : SATETY_BELT_LOCKED;
				LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->eSafetyBeltStatus = 0x%X, p[1] = 0x%02X ", pLocalParam->eSafetyBeltStatus, p[1]);
			}
			break;
		case 0x15:// hand stop
			{
				pLocalParam->eHandLockerStatus = (0x01 == p[1]) ? HAND_LOCKER_LOCKED : HAND_LOCKER_UNLOCKED;
				LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->eHandLockerStatus 0x%X", pLocalParam->eHandLockerStatus);
			}
			break;
		case 0x16:
			{
				memcpy(&pLocalParam->nInstantSpeed, p + 1, 2);
				LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->nInstantSpeed %d", pLocalParam->nInstantSpeed);
			}
			break;
		case 0x17:
			{
				pLocalParam->nOilRemind = p[1] & 0x7F;
				pLocalParam->bOilWarning = p[1] & 0x80;
				LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->nOilRemind %d, bOilWarning %d ]", pLocalParam->nOilRemind,  pLocalParam->bOilWarning);
			}
			break;
		case 0x18:
			{
				memcpy(&pLocalParam->nDegreeOfCarGround, p + 1, 2);
				LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->nDegreeOfCarGround %d", pLocalParam->nDegreeOfCarGround);
			}
			break;
		case 0x19:
			{
				pLocalParam->nDegreeOfWater = p[1];
				LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->nDegreeOfWater %d", pLocalParam->nDegreeOfWater);
			}
			break;
		case 0x1A:
			{
				pLocalParam->eCleanWaterStatus = (0x01 == p[1]) ? CLEAN_WATER_EMPTY : CLEAN_WATER_ENOUGH;
				LOGD("[analyseHalMessage_DaZhongCarInfo]->pLocalParam->eCleanWaterStatus 0x%X", pLocalParam->eCleanWaterStatus);
			}
			break;
		case 0x1B:
			{
				pLocalParam->eCarDoorWindow_FL = (p[1] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				pLocalParam->eCarDoorWindow_FR = (p[2] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				pLocalParam->eCarDoorWindow_RL = (p[3] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				pLocalParam->eCarDoorWindow_RR = (p[4] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				LOGD("[%s] CarDoorWindow FL,FR(%x,%x):",__FUNCTION__,pLocalParam->eCarDoorWindow_FL,pLocalParam->eCarDoorWindow_FR);
				LOGD("[%s] CarDoorWindow RL RR(%x,%x)",__FUNCTION__,pLocalParam->eCarDoorWindow_RL,pLocalParam->eCarDoorWindow_RR);
			}
			break;
		case 0x1C:
				{
					pLocalParam->eCarDormer = (p[1] == 0x00) ? CAR_DORMER_CLOSE  : CAR_DORMER_OPEN;
					LOGD("[%s] pLocalParam->eCarDormer:%x",__FUNCTION__,pLocalParam->eCarDormer);
				}
			break;
		case 0x1D:
				{
					pLocalParam->eCarDoorLocker = (p[1] == 0x00) ? CAR_DOOR_LOCKER_UNLOCK : CAR_DOOR_LOCKER_LOCK;
					LOGD("[%s] pLocalParam->eCarDoorLocker:%x",__FUNCTION__,pLocalParam->eCarDoorLocker);
				}
			break;
		case 0x1E:
				{
					pLocalParam->eHeadLight = (p[1] == 0x00) ? HEAD_LIGHT_CLOSE: HEAD_LIGHT_OPEN;
					LOGD("[%s] pLocalParam->eHeadLight:%x",__FUNCTION__,pLocalParam->eHeadLight);
				}
			break;
	}
	process_DaZhongCarInfo();
}

#define FKS_LOG_TAG		"FOCUS"

void analyseHalMessage_fks_CarInfo(unsigned char *p, int len)
{
	pLocalParam->nCurCmd = p[0];
	LOGD( "p[0]:0x%x", p[0]);
	switch(p[0])
	{
		case 0x51:/*��ʻ���*/
			{
				pLocalParam->nDrivingDistance = 0;
				u8 DrivingDistance[4]={p[3],p[2],p[1]};
				memcpy(&pLocalParam->nDrivingDistance, DrivingDistance, 4);
				LOGD("[%s] foucs]pLocalParam->nDrivingDistance %d", FKS_LOG_TAG, pLocalParam->nDrivingDistance);
			}
			break;
		
		case 0x52:/*������Ϣ*/
			{
			
				int s = 0, d = 0;
				s = p[1];
				d |= (s & 0x80) ? 0x01 : 0;
				d |= (s & 0x40) ? 0x02 : 0;
				d |= (s & 0x20) ? 0x04 : 0;
				d |= (s & 0x10) ? 0x08 : 0;
				d |= (s & 0x08) ? 0x20 : 0;
				pLocalParam->nCarDoorStatus = d;
				LOGD("[%s], pLocalParam->nCarDoorStatus = [0x%X], p[1] = [0x%X]", FKS_LOG_TAG, pLocalParam->nCarDoorStatus, p[1]);
				
				
			}
			break;
		case 0x53:/*��ɲ*/
			{
				pLocalParam->eHandLockerStatus = (0x80 == p[1]) ? HAND_LOCKER_LOCKED : HAND_LOCKER_UNLOCKED;
				LOGD("[%s] foucs]pLocalParam->eHandLockerStatus 0x%x", FKS_LOG_TAG, pLocalParam->eHandLockerStatus);
			}
			break;
		case 0x54:/*��ȫ����Ϣ*/
			{
				u8 left=p[1]>>1;
				u8 right=p[1]>>4;
				pLocalParam->eSafetyBeltStatus =   (!left||!right) ?  SATETY_BELT_UNLOCKED : SATETY_BELT_LOCKED;
				LOGD("[%s]pLocalParam->eSafetyBeltStatus = 0x%X, p[1] = 0x%02X ", FKS_LOG_TAG, pLocalParam->eSafetyBeltStatus, p[1]);
			}
			break;
		case 0x55:/*�����¶�*/
			{
				pLocalParam->nDegreeOfCarGround=p[1]*10.0;
				LOGD("[%s]pLocalParam->nDegreeOfCarGround: 0x%x", FKS_LOG_TAG, pLocalParam->nDegreeOfCarGround);
			}
			break;
		case 0x56:/*����ת��*/
			{
				u8 EngineSpeed[2]={p[2],p[1]};
				memcpy(&pLocalParam->nEngineSpeed, EngineSpeed, 2);
				LOGD("[%s]pLocalParam->nEngineSpeed %d", FKS_LOG_TAG, pLocalParam->nEngineSpeed);
			}
			break;
		case 0x57:/*��ص�ѹ*/
			{
				pLocalParam->nBatteryVoltage=p[1]*10;
				LOGD("[%s]pLocalParam->nBatteryVoltage %d", FKS_LOG_TAG, pLocalParam->nBatteryVoltage);
			}
			break;
		case 0x59:/*˲ʱ����*/
			{
				pLocalParam->nInstantSpeed = 0;
				pLocalParam->nInstantSpeed += p[2];
				pLocalParam->nInstantSpeed += (p[1] << 8);

				LOGD("[%s]pLocalParam->nInstantSpeed %d", FKS_LOG_TAG, pLocalParam->nInstantSpeed);

			}
			break;
			/*
		case 0x58:
			{
				pLocalParam->nOilRemind = p[1] & 0x7F;
				pLocalParam->bOilWarning = p[1] & 0x80;
				LOGD("[%s]->pLocalParam->nOilRemind %d, bOilWarning %d ]", FKS_LOG_TAG, pLocalParam->nOilRemind,  pLocalParam->bOilWarning);
			}
			break;*/
		
		case 0x5A:/* ��λ��Ϣ*/
			{
				pLocalParam->uGearStage=p[1]>>4;
				LOGD("[%s]pLocalParam->uGearStage 0x%x", FKS_LOG_TAG, pLocalParam->uGearStage);
			}
			break;
			default:break;
	}
	process_fks_CarInfo();
}

/***************************************************************************************************************/
/*								             TOYOTA															   */
/***************************************************************************************************************/
void analyseHalMessage_toyota_CarInfor(unsigned char resCmd, unsigned char *param, unsigned char len)
{
	pLocalParam->nCurCmd = resCmd;
	switch(resCmd)
	{
		case 0x70:/*ͨ�����*/
			pLocalParam->AutomaticalAcOrEffectVentilat = param[0];
			LOGD("[%s]pLocalParam->AutomaticalAcOrEffectVentilat:%x",TOYOTA,pLocalParam->AutomaticalAcOrEffectVentilat);
		break;
		case 0x71:/*��ȫ��*/
			if(param[0] == 0)
			{
				pLocalParam->eSafetyBeltStatus = SATETY_BELT_LOCKED;
			}
			else if(param[0] == 1)
			{
				pLocalParam->eSafetyBeltStatus = SATETY_BELT_UNLOCKED;
			}
			else
			{
				pLocalParam->eSafetyBeltStatus = SATETY_BELT_UNKNOW;
			}
			LOGD("[%s]pLocalParam->eSafetyBeltStatus:%x",TOYOTA,pLocalParam->eSafetyBeltStatus);
		break;
		case 0x72:/*��ɲ*/
		case 0xc5://HL_voltage_BrakeState
			pLocalParam->eHandLockerStatus = (0x01 == param[0]) ? HAND_LOCKER_LOCKED : HAND_LOCKER_UNLOCKED;
			LOGD("[%s]pLocalParam->eHandLockerStatus:%x",TOYOTA,pLocalParam->eHandLockerStatus);
		break;
		case 0x73:/*ת��*/
			pLocalParam->nEngineSpeed = (param[0]*256 + param[1])*4/5;
			LOGD("[%s]pLocalParam->nEngineSpeed:%x",TOYOTA,pLocalParam->nEngineSpeed);
		break;
		case 0x74:/*���Źر�״̬*/
			{
			int s = 0, d = 0;
			s = param[0];
			d |= (s & 0x20) ? 0x01 : 0;
			d |= (s & 0x10) ? 0x02 : 0;
			d |= (s & 0x04) ? 0x04 : 0;
			d |= (s & 0x08) ? 0x08 : 0;
			d |= (s & 0x02) ? 0x20 : 0;
			pLocalParam->nCarDoorStatus = d;
			LOGD("[%s]pLocalParam->nCarDoorStatus:0x%x,param[0]=0x%x",TOYOTA,pLocalParam->nCarDoorStatus,param[0]);
			}
			break;
		case 0x75:/*���*/
			pLocalParam->nDrivingDistance = 0;
			pLocalParam->nDrivingDistance = param[0]*256*256 + param[1]*256+param[2];
			LOGD("[%s]pLocalParam->nDrivingDistance:%x",TOYOTA,pLocalParam->nDrivingDistance);
		break;
		case 0x76:/*����*/
			pLocalParam->nInstantSpeed = param[0]*256 + param[1];
			LOGD("[%s]pLocalParam->nInstantSpeed:%x",TOYOTA,pLocalParam->nInstantSpeed);
		break;
		case 0xc4:
			pLocalParam->eCarGears = param[0];
			break;
		case 0x77:/*�����¶�*/
			pLocalParam->nDegreeOfCarGround = (param[0]-0x30)*10.0;
			LOGD("[%s]pLocalParam->nDegreeOfCarGround:%x param[0]:%x",TOYOTA,pLocalParam->nDegreeOfCarGround,param[0]);
		break;
		case 0x78:/*�յ�*/
			exterToAirData_aboutToyotaCamry(param, len);
		break;
		case 0x79:/*��������*/
			pLocalParam->nCarDoorLockStates = param[0];
			LOGD("[%s]pLocalParam->nCarDoorLockStates:%x",TOYOTA,pLocalParam->nCarDoorLockStates);
		break;
		case 0x7a:/*����ǣ��������*/
			pLocalParam->uTRCStatus = (param[0] & 0x20) ? 0x00 : 0x01;
			LOGD("[%s]pLocalParam->uTRCStatus:%x",TOYOTA,pLocalParam->uTRCStatus);
		break;
		case 0x7b:/*S�����˶�ģʽ*/
			pLocalParam->uSPORTStatus = (param[0] & 0x20) ? 0x01 : 0x00;
			LOGD("[%s]pLocalParam->uSPORTStatus:%x",TOYOTA,pLocalParam->uSPORTStatus);
		break;
		case 0x7c:/*Ѳ������*/
			pLocalParam->uCruiseControlStatus = param[0];
			LOGD("[%s]pLocalParam->uCruiseControlStatus:%x",TOYOTA,pLocalParam->uCruiseControlStatus);
		break;
		case 0x7d:/*����ģʽ*/
			pLocalParam->uECOStatus = param[0];
			LOGD("[%s]pLocalParam->uECOStatus:%x",TOYOTA,pLocalParam->uECOStatus);
		break;
		case 0x7e:/*��ص�ѹ*/
			pLocalParam->nBatteryVoltage = param[0]*256 + param[1];
			LOGD("[%s]pLocalParam->nBatteryVoltage:%x",TOYOTA,pLocalParam->nBatteryVoltage);
		break;
		case 0x83:
		{
			if(param[0] == 0){
				pLocalParam->eOilConsumeUnit = OIL_CONSUME_UNIT_L_PER_100_KM;
			}
			else if(param[0] == 1){
				pLocalParam->eOilConsumeUnit = OIL_CONSUME_UNIT_KM_PER_L;
			}
			LOGD("[%s] pLocalParam->eOilConsumeUnit [%d]",TOYOTA, pLocalParam->eOilConsumeUnit);
		}
	   	break;
		case 0x84:
				{
					pLocalParam->eCarDormer = (param[0] == 0x00) ? CAR_DORMER_CLOSE  : CAR_DORMER_OPEN;
					LOGD("[%s] pLocalParam->eCarDormer:%x",TOYOTA,pLocalParam->eCarDormer);
				}
			break;
		case 0x85:
				{
					pLocalParam->eHeadLight = (param[0] == 0x00) ? HEAD_LIGHT_CLOSE: HEAD_LIGHT_OPEN;
					LOGD("[%s] pLocalParam->eHeadLight:%x",TOYOTA,pLocalParam->eHeadLight);
				}
			break;
		case 0x86:
			{
				if(param[0] == 0xff)
				{
					pLocalParam->eCarDoorWindow_FL = CAR_DOOR_WINDOW_UNKNOW;
				}
				else
				{
					pLocalParam->eCarDoorWindow_FL = (param[0] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				}

				if(param[1] == 0xff)
				{
					pLocalParam->eCarDoorWindow_FR = CAR_DOOR_WINDOW_UNKNOW;
				}
				else
				{
					pLocalParam->eCarDoorWindow_FR = (param[1] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				}

				if(param[2] == 0xff)
				{
					pLocalParam->eCarDoorWindow_RL = CAR_DOOR_WINDOW_UNKNOW;
				}
				else
				{
					pLocalParam->eCarDoorWindow_RL = (param[2] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				}

				if(param[3] == 0xff)
				{
					pLocalParam->eCarDoorWindow_RR = CAR_DOOR_WINDOW_UNKNOW;
				}
				else
				{
					pLocalParam->eCarDoorWindow_RR = (param[3] == 0x00) ? CAR_DOOR_WINDOW_CLOSE  : CAR_DOOR_WINDOW_OPEN;
				}
				
				LOGD("[%s] CarDoorWindow FL,FR(%x,%x):",TOYOTA,pLocalParam->eCarDoorWindow_FL,pLocalParam->eCarDoorWindow_FR);
				LOGD("[%s] CarDoorWindow RL RR(%x,%x)",TOYOTA,pLocalParam->eCarDoorWindow_RL,pLocalParam->eCarDoorWindow_RR);
			}
			break;
			case 0x87:
				pLocalParam->eCarDoorLocker = (param[0] == 0x00) ? CAR_DOOR_LOCKER_UNLOCK : CAR_DOOR_LOCKER_LOCK;
				LOGD("[%s]pLocalParam->nCarDoorLockStates:%x",TOYOTA,pLocalParam->nCarDoorLockStates);
			break;
		default:break;
	}
	process_toyota_CarInfo();
}

void analyseHalMessage_SiYuCarInfo(u8* param, int len)
{
	u8 cmd =param[0];
	pLocalParam->nCurCmd=cmd;
	switch(cmd)
	{
		case 0x00:
			LOGD("(SiYu)exterToAC_SiYu");
			exterToAC_SiYu(param + 1, len - 1);
			break;
		case 0x01: /*���ֵ*/
			{
			pLocalParam->nDrivingDistance = 0;
			u8 DrivingDistance[4]={param[3],param[2],param[1],0};
			memcpy(&pLocalParam->nDrivingDistance, DrivingDistance, 4);
			LOGD("(SiYu)pLocalParam->nDrivingDistance:0x%x",pLocalParam->nDrivingDistance);
			}
		break;
		case 0x02: /*������Ϣ*/
			{
			int s = 0, d = 0;
			s = param[1];
			d |= (s & 0x10) ? 0x01 : 0; 
			d |= (s & 0x08) ? 0x02 : 0;
			d |= (s & 0x04) ? 0x04 : 0;
			d |= (s & 0x02) ? 0x08 : 0;
			d |= (s & 0x01) ? 0x20 : 0;
			pLocalParam->nCarDoorStatus = d;
			LOGD("(SiYu)pLocalParam->nCarDoorStatus:0x%x,p[1]=0x%x",pLocalParam->nCarDoorStatus,param[1]);
			}
		break;
		case 0x03: /*��ɲ*/
			pLocalParam->eHandLockerStatus = (0x00 != param[1]) ? HAND_LOCKER_LOCKED : HAND_LOCKER_UNLOCKED;
			LOGD("(SiYu)pLocalParam->eHandLockerStatus:0x%x,param[1]:0x%x",pLocalParam->eHandLockerStatus,param[1]);
			break;
		case 0x04: /*��ȫ��*/
			{
			u8 left=param[1]>>1;
			u8 right=param[1]>>4;
			pLocalParam->eSafetyBeltStatus =   (!left||!right) ?  SATETY_BELT_UNLOCKED : SATETY_BELT_LOCKED;
			LOGD("(SiYu)pLocalParam->eSafetyBeltStatus:0x%x", pLocalParam->eSafetyBeltStatus);
			}
			break;
		case 0x05: /*�ⲿ�¶�*/
			pLocalParam->nDegreeOfCarGround=param[1];
			LOGD("(SiYu)pLocalParam->nDegreeOfCarGround:0x%x",pLocalParam->nDegreeOfCarGround);
			break;
		case 0x06: /*����ת��*/
			{
			u8 EngineSpeed[2]={param[2],param[1]};
			memcpy(&pLocalParam->nEngineSpeed, EngineSpeed, 2);
			LOGD("(SiYu)pLocalParam->nEngineSpeed:0x%x",pLocalParam->nEngineSpeed);
			}
			break;
		case 0x07:/*��ص�ѹ*/
			pLocalParam->nBatteryVoltage=param[1]*10;
			LOGD("(SiYu)pLocalParam->nBatteryVoltage:0x%x",pLocalParam->nBatteryVoltage);
			break;
		case 0x09:/*˲ʱ�ٶ�*/
			pLocalParam->nInstantSpeed=param[1]*100;
			LOGD("(SiYu)pLocalParam->nInstantSpeed:0x%x",pLocalParam->nInstantSpeed);
			break;
		case 0x0A:/*ʣ�����*/
			{
			//u8 SurplusDistance[2]={param[2],param[1]};
			LOGD("[SiYu] p H = [%x], L = [%X]", param[1], param[2]);
			//memcpy(&pLocalParam->SurplusDistance,SurplusDistance,2);
			u16 Value=param[1]+ (param[2]<<8);
			pLocalParam->SurplusDistance = (int)Value;
			LOGD("(SiYu)pLocalParam->SurplusDistance:0x%x",pLocalParam->SurplusDistance);
			}
			break;
		case 0x0B:/*ƽ���ͺ�*/
			LOGD("[SiYu] avg oil use = H [0x%X], L [0x%X]", param[1], param[2]);
			pLocalParam->avgOilWear=param[1]*256 + param[2];
			LOGD("(SiYu)pLocalParam->avgOilWear:0f%f",pLocalParam->avgOilWear);
			break;
		case 0x0C:/*��ǰ�ͺ�*/
			LOGD("[SiYu] oil use = [%d]", param[1]);
			pLocalParam->curOilWear=param[1] * 1.0;
			LOGD("(SiYu)pLocalParam->curOilWear: [%f]",pLocalParam->curOilWear);
			break;
		case 0x0D:
			LOGD("AC_Data of HondaCRV");
			exterToAC_HondaCRV(param+1, len-1);
			break;
		case 0x0E:/*CRV��λ*/
			{
				LOGD("[SiYu] eCarStall param[1] 0x%X", param[1]);
				if(param[1] == 0x40)
				pLocalParam->eCarStall = CAR_STALL_P;
				else if(param[1] == 0x10)
				pLocalParam->eCarStall = CAR_STALL_B;
				else if(param[1] == 0x04)
				pLocalParam->eCarStall = CAR_STALL_N;
				else if(param[1] == 0x01)
				pLocalParam->eCarStall = CAR_STALL_D;
				else if(param[1] == 0x00)
				pLocalParam->eCarStall = CAR_STALL_S;
				else if(param[1] == 0x08)
				pLocalParam->eCarStall = CAR_STALL_S2;
				else if(param[1] == 0x02)
				pLocalParam->eCarStall = CAR_STALL_S1;
				else
				pLocalParam->eCarStall = CAR_STALL_NOT_P;
				LOGD("[SiYu]->pLocalParam->eCarStall 0x%X", pLocalParam->eCarStall);
			}
			break;
		case 0x0F:/*CRV������*/
			LOGD("[SiYu] param[1] carlock 0x%X",param[1]);
			pLocalParam->eCarDoorLocker = (param[1] == 0x00) ? CAR_DOOR_LOCKER_LOCK : CAR_DOOR_LOCKER_UNLOCK;
			LOGD("[SiYu]pLocalParam->eCarDoorLocker 0x%X, param[1] = [%X]", pLocalParam->eCarDoorLocker);
			break;
		default:break;
	}
	
	process_SiYu_CarInfo();
}

void analyseHalMessage_EXTCAR(u8 resCmd, u8 *param, u8 len)
	{
	LOGD("resCmd:0x%x param[0]:%d",resCmd,param[0]);
	switch(resCmd){
		case 0x01:
		case 0x02:
			break;
		case 0x90://TOYOTA
			if(param[0] == 0X00)
			{
				analyseHalMessage_CarType_Camry(param[1],param+2,len-2);
				gclsCarInforCarSettings.analyseCarInfo_CarSettings(param+1,len-1);
			}
			break;
		case 0xa0:
			analyseHalMessage_CarType_Focus(param,len);
			break;
		case 0x80:
			analyseHalMessage_DaZhongCarInfo(param,  len);
			break;
		case 0x81:
			analyseHalMessage_golf_carInfo(param + 1, len);
			break;
		case 0xB0:
			analyseHalMessage_SiYuCarInfo(param,  len);
			break;
		case 0xB1:
			{
				if (pLocalParam->m_pCarInfo == NULL)
					{
						pLocalParam->m_pCarInfo = new CCarInfoToyotaPrado();
						pLocalParam->m_pCarInfo->initCarInfo();
						pLocalParam->m_pCarInfo->runCarInfo();
					}
				pLocalParam->m_pCarInfo->analyseCarInfo(param, len);
			}
			break;
		case 0xB2://Nissan
			if(param[0] == 0X00)
			{
				analyseHalMessage_CarType_Nissan(param+1,len-1);
			}
			break;
		case 0xc0:		
			analyseHalMessage_byd_car_info(param,len);
			break;
		case 0xD1:
			analyseHalMessage_mistra_car_info(param,len);
			break;
		case 0xF0://public
			analyseHalMessage_CarProtocolInfo(param,  len);
			break;
		default:break;
	}
}


#define BYD_CAR_INFO_TAG		"byd_car_info_tag"

void analyseHalMessage_byd_car_info(unsigned char *param, int len)
{
	pLocalParam->nCurCmd = param[0];
	switch(param[0])
	{
		case 0x00:
			{
				exterToAC_byd(param + 1, len - 1);
				pLocalParam->nDegreeOfCarGround = (param[7] - 0x80) * 10;
				LOGD("[%s]->pLocalParam->nDegreeOfCarGround [%d]", BYD_CAR_INFO_TAG,  pLocalParam->nDegreeOfCarGround);
			}
			break;
		case 0x12:
			{
				memcpy(&pLocalParam->nEngineSpeed, param + 1, 2);
				pLocalParam->nEngineSpeed /= 4;
			}
			break;
		case 0x13:
			{
				pLocalParam->nCarDoorStatus = param[1];
				LOGD("[%s]->pLocalParam->nCarDoorStatus 0x%X", BYD_CAR_INFO_TAG,  pLocalParam->nCarDoorStatus);
			}
			break;
		case 0x14:
			{
				pLocalParam->eSafetyBeltStatus =   ((param[1] & 0x10) == 0 || (param[1] & 0x40) == 0) ?  SATETY_BELT_UNLOCKED : SATETY_BELT_LOCKED;
				//pLocalParam->eSafetyBeltStatus =   (param[1] & 0x40) ?  SATETY_BELT_LOCKED : SATETY_BELT_UNLOCKED;
				LOGD("[%s]->pLocalParam->eSafetyBeltStatus = 0x%X, p[1] = 0x%02X ", BYD_CAR_INFO_TAG,  pLocalParam->eSafetyBeltStatus, param[1]);
			}
			break;
		case 0x15:
			{
				pLocalParam->eHandLockerStatus = (0x01 == param[1]) ? HAND_LOCKER_LOCKED : HAND_LOCKER_UNLOCKED;
				LOGD("[%s]->pLocalParam->eHandLockerStatus 0x%X", BYD_CAR_INFO_TAG, pLocalParam->eHandLockerStatus);
			}
		break;
		case 0x16:
			{	
				s16 oilUse = 0;
				memcpy(&oilUse, param + 1, 2);
				pLocalParam->curOilWear = oilUse;
				LOGD("[%s]->pLocalParam->curOilWear [%.1lf]", BYD_CAR_INFO_TAG, pLocalParam->curOilWear);
			}
			break;
		case 0x17:
				pLocalParam->eCarStall = (0x00 == param[1]) ? CAR_STALL_P: CAR_STALL_NOT_P;
				LOGD("[%s]->pLocalParam->eCarStall 0x%X", BYD_CAR_INFO_TAG, pLocalParam->eCarStall);
			break;
		case 0x18:
				pLocalParam->eCarDoorLocker = (param[1] & 0x08) ? CAR_DOOR_LOCKER_UNLOCK : CAR_DOOR_LOCKER_LOCK;
				LOGD("[%s]->pLocalParam->eCarDoorLocker 0x%X, param[1] = [%X]", BYD_CAR_INFO_TAG, pLocalParam->eCarDoorLocker);
			
				LOGD("[%s]->Press car lock 0x%X", BYD_CAR_INFO_TAG, param[1] & 0x01);
				
				LOGD("[%s]->Press car unlock 0x%X", BYD_CAR_INFO_TAG, param[1] & 0x02);
			break;
	}
	process_byd_carInfo();
}

void process_carRequestOpenMode()
{
	extcarToHal_set_ModeOpenOrClose(0x01);
}

void process_carGolfModeKeyValue()
{
	if(pLocalParam->uModeKeyValue == 0x02)
	{
		int CurPageID = 0;
		int paramLen=0;
		getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,(u8*)&paramLen);
		LOGD("[%s] pageID:%x",__FUNCTION__,CurPageID);
		switch(CurPageID)
		{
			case PAGE_BLACK:
			case PAGE_STANDBY:
			case PAGE_BACK_VIDEO:
			case PAGE_BACK_NOVIDEO:
			case PAGE_GOLF_SETUP_DRIVING_MOD:
				return;
			break;
		}

		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_DRIVING_MOD);
	}
}

void process_carIsGotoModePage()
{
	if(pLocalParam->bCurMODE_State == true)
	{
		u8 ucBackMode = 0;
		int paramLen=0;
		getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&paramLen);
		LOGD("[%s] ucBackMode=0x%x",__FUNCTION__,ucBackMode);
		if(ucBackMode == 0x00)
		{
			pLocalParam->bFirstGotoModePage = true;
			SetTimer(TIME_MODE_FIRST_GOTO_MODE_PAGE,1,EXTCAR_TIMER_ID_GOLF_MODE_HIDEBOX);
			extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_DRIVING_MOD);
		}
	}

}

void process_carIsOutModePage()
{
	int CurPageID = 0;
	int paramLen=0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,(u8*)&paramLen);
	LOGD("[%s] pageID:%x",__FUNCTION__,CurPageID);
	if(CurPageID == PAGE_GOLF_SETUP_DRIVING_MOD)
	{
		extcarToHal_set_ModeOpenOrClose(0x00);
		pLocalParam->bCurMODE_State = false;
		pLocalParam->bFirstGotoModePage = false;
		extcarToModule_NotifySystem_jumpPrePage();
	}
}

void process_carGolfModeState()
{
	u32 nMap[SIZE_MAP_ENUM] = {0};
	nMap[CAR_DRIVING_MODE_COMFORT] = CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_COMFORT ;
	nMap[CAR_DRIVING_MODE_STANDARD] = CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_STANDARD;
	nMap[CAR_DRIVING_MODE_SPORT] = CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_SPORT;
	nMap[CAR_DRIVING_MODE_LOW_OIL] =  CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_LOW_OIL;
	nMap[CAR_DRIVING_MODE_PERSONALIZATION] = CONTROLID_CARINFOR_CARSETTINGS_DRIVINGMOD_PERSONALIZATION;
	
	if ((u8)pLocalParam->eCar_DrivingMode < SIZE_MAP_ENUM){
		UI_DrivingModeDisplay(nMap[pLocalParam->eCar_DrivingMode]);
	}
}

void process_carGolfPersonalizationSet()
{
	process_DampingSystemMode();
	process_SteeringWheelMode();
	process_DrivingGearMode();
	process_Dynamic_Headlight_FollowerMode();
	process_AcMode();
	process_InternalEngineSoundsMode();
}


#define NISSAN_CAR_INFO_TAG		"nissan_car_info_tag"
void analyseHalMessage_CarType_Nissan(unsigned char *p, int len)
{
	pLocalParam->nCurCmd = p[0];
	switch(p[0])
	{
		case 0x01:
		{
			s16 nTemBatteryVoltage = 0;
			memcpy(&nTemBatteryVoltage, p + 1, 2);
			pLocalParam->nBatteryVoltage = nTemBatteryVoltage*10;
			
			LOGD("[%s] pLocalParam->nBatteryVoltage %d",NISSAN_CAR_INFO_TAG, pLocalParam->nBatteryVoltage);
		}
		break;
	}

	process_nissan_carInfo();
}


void process_nissan_carInfo(void)
{
	switch(pLocalParam->nCurCmd)
	{
		case 0x01:
			process_BatteryVoltageInfo();
			break;
	}
}


#define MISTRA_CAR_INFO_TAG		"mistra_car_info_tag"

void analyseHalMessage_mistra_car_info(u8 *param, u32 len)
{
	switch(param[0])
	{
		case 0x00://AC DATA
			mistraCarToAirCondition(param + 1, len - 1);
		break;
		default:break;
	}
}


void analyseHalMessage_CarProtocolInfo(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x01://base carInfors
			GetBaseCarInfors(param + 1, len - 1);
			break;
		case 0x02://acInfors
			GetACcarInfors(param + 1, len - 1);
			break;
		case 0x03://set carInfors 
			GetSetCarInfors(param + 1, len - 1);
			break;
		default:
			break;
	}
}

void GetBaseCarInfors(u8 *param,u8 len)
{
	LOGD("%s %x  %x  %x",__FUNCTION__,param[0],param[1],param[2]);
	switch(param[0])
	{
		case 0x00://SeatBelts
			getSeatBelts(param + 1, len - 1);
			break;
		case 0x01://Remain Oil
			getRemainOil(param + 1, len - 1);
			break;
		case 0x02://drive mileage
			getDriveMileage(param + 1, len - 1);
			break;
		case 0x03:
			getOutSideTemperature(param + 1, len - 1);
			break;
		case 0x04:
			getHandBrake(param + 1, len - 1);
			break;
		case 0x05:
			getEngineSpeed(param+1,len -1);
			break;
		case 0x06:
			getPublicAverageSpeed(param+1,len -1);
			break;
		case 0x07:
			getInstantSpeed(param+1,len -1);
			break;
		case 0x08:
			getBatteryVoltage(param + 1, len - 1);
			break;
		case 0x0B:
			getContinuedDriveMileageData(param + 1,len -1);
			break;
		case 0x0D:
			getAverageFuelConsumption(param + 1, len - 1);
			break;
		case 0x0E:
			getDoorStatus(param + 1, len - 1);
			break;
		case 0x10:
			getDoorLockStatus(param + 1, len - 1);
			break;
		case 0x11:
			getTrunkStatus(param + 1, len - 1);
			break;
		case 0x12:
			getFrontCoverStatus(param + 1, len - 1);
			break;
		case 0x13:
			getSkyLightStatus(param + 1, len - 1);
			break;
		case 0x14:
			getRadarInfo(param + 1, len - 1);
			break;
		case 0x16:
			getLightStatus(param + 1, len - 1);
			break;
		case 0x1B:
			getVINCode(param + 1, len - 1);
			break;
		case 0x1C:
			ExtcarToModule_Tpms_PublicTpmsInfo(param+1,len -1);
			break;
		case 0x18:
			getGearsInfo(param + 1, len - 1);
			break;
		default:
			break;
	}
	process_BasicCarInfo(param[0],param[1]);
}

void GetACcarInfors(u8 *param,u8 len)
{
	ExtcarToModule_Ac_PublicAcInfo(param,len);
}

void GetSetCarInfors(u8 *param,u8 len)
{
	if(param[0] == 0x00)
	{
		switch(param[1])
		{
			case 0x00:
				getPublicElectronicBoosterMode(param+2,len - 2);
				break;
			case 0x01:
				getPublicRemoteControlLocFeedback(param+2,len - 2);
				break;
			case 0x02:
				getPublicShutDownTheUnlock(param+2,len - 2);
				break;
			case 0x03:
				getPublicPositionAfterLocking(param+2,len - 2);
				break;
			case 0x04:
				getPublicPositionSpeedAlarmSwitchAndThreshold(param+2,len - 2);
				break;
			case 0x05:
				getPublicPositionTrunkDegree(param+2,len - 2);
				break;
			case 0x06:
				getPublicWelcomeLamp(param+2,len - 2);
				break;
			case 0x07:
				getPublicCompanyLampHome(param+2,len - 2);
				break;
			case 0x08:
				getPublicvehicle_mode(param+2,len - 2);
				break;
			case 0x09:
				getPublicDriving_automatic_latch(param+2,len - 2);
				break;
			case 0x0A:
				getPublicFlameout_Automatic_Latch(param+2,len - 2);
				break;
			case 0x0B:
				getPublicKey_Unlock_Door(param+2,len - 2);
				break;
			case 0x0C:
				getPublicKeyLess_Unlock_Door(param+2,len - 2);
				break;
			case 0x0D:
				getPublicACSetData(param+2,len - 2);
				break;
			case 0x0E:
				getPublicMirrorAutomaticOpenSwitch(param+2,len - 2);
				break;
			case 0x0F:
				exterToFOCUS_sync_FromHal(param+2,len-2);
				break;
			case 0x10:
				getPublicSystemLanguageSet(param+2,len - 2);
				break;
			case 0x11:
				ExtcarToModule_system_PublicVehicleSettings(param+1,len-1);
				break;
			case 0x12:
				analysePublicBackCarViodeMessage(param+1,len-1);
				break;
			case 0x13:
				getPublicFordTCUMessage(param+2,len-2);
				break;
			case 0x14:
				getPublicFordAmbientLedMessage(param+2,len-2);
				break;
			case 0x15:
				//getPublicAuxiliaryParkingSystemMessage(param+2,len-2);
				break;
			case 0x16:
				ExtcarToModule_system_PublicVehicleSettings(param+1,len-1);//getPublicMultiContouredSeatsMessage
				break;
			default:
				break;
		}
	}
}

/*******************************************/
void getSeatBelts(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			{
				if(param[1] == 0xFF)
					pLocalParam->eSafetyBeltStatus = SATETY_BELT_UNKNOW;
				else
					pLocalParam->eSafetyBeltStatus =  param[1] ?  SATETY_BELT_LOCKED : SATETY_BELT_UNLOCKED;
			}
			break;
		case 0x01:
			break;
		case 0x02:
			break;
		default:
			break;
	}
}

void getRemainOil(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			{
				pLocalParam->nOilRemind = 0;
				memcpy(&pLocalParam->nOilRemind, param + 1, 2);
			}
			break;
		default:
			break;
	}
}

void getDriveMileage(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			{
				int nDistance1 = param[1]+(param[2] << 8);
				int nDistance2 = param[3]+(param[4] << 8);
				if(nDistance1 == 0xFFFF && nDistance2 == 0xFFFF)
					pLocalParam->publicDrivingDistance = -1;
				else
					pLocalParam->publicDrivingDistance = param[1]+(param[2] << 8) +(param[3] << 16)+(param[4] << 24);
				if(len > 5)
					pLocalParam->publicDrivingDistanceUint = param[5];
			}
			break;
		case 0x05:
			break;
		case 0x0A:
			break;
		case 0x10:
			break;
		case 0x15:
			break;
		case 0x1A:
			break;
		default:
			break;
	}
}

void getOutSideTemperature(u8 *param, u8 len)
{
	switch(param[0])
	{
		case 0x00:
			pLocalParam->publicDegreeOfCarGround =  param[1]+(param[2] << 8);
			pLocalParam->CarGroundDecimalNumber = param[3];
			pLocalParam->CarGroundUnit = param[4];
			pLocalParam->CarGroundPosOrNeg = param[5];
			break;
		default:
			break;
	}
}

void getHandBrake(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			if(param[1] == 0xFF)
				pLocalParam->eHandLockerStatus = HAND_LOCKER_UNKNOW;
			else
				pLocalParam->eHandLockerStatus = (0x01 == param[1]) ? HAND_LOCKER_LOCKED : HAND_LOCKER_UNLOCKED;
		}
		break;
		default:
		break;
	}
}

void getEngineSpeed(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			pLocalParam->publicEngineSpeed = param[1] + (param[2] << 8);
		}
		break;
		default:
		break;
	}
}

void getInstantSpeed(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			pLocalParam->publicnIStantSpeed =  param[1] + (param[2] << 8);
		}
		break;
		default:
		break;
	}
}

void getPublicAverageSpeed(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			pLocalParam->publicAverageSpeed =  param[1] + (param[2] << 8);
		}
		break;
		default:
		break;
	}
}

void getBatteryVoltage(u8 *param, u8 len)
{
	switch(param[0])
	{
		case 0x00:
			pLocalParam->nBatteryVoltage = param[1]+(param[2] << 8);
			break;
		case 0x01:
			pLocalParam->uBatteryVoltageAnomalyMonitoring = param[1];
			break;
		default:
			break;
	}
}

void getAverageFuelConsumption(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00://base
			{
				pLocalParam->avgOilWear= param[1] + (param[2] << 8);
			}
			break;
		case 0x01://startup
			break;
		case 0x0A:
			break;
		case 0x10:
			break;
		case 0x15:
			break;
		case 0x1A:
			break;
		default:
			break;
	}

}

void  getDoorStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			memcpy(pLocalParam->szDoorStatus, param + 1, 4);
			g_clsExtcar.extcarSendDoorStatusToSdk(param + 1,4);
		}
		break;
		default:
		break;
	}
}

void getTrunkStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			pLocalParam->szDoorStatus[4] = param[1];
			g_clsExtcar.extcarSendTrunkStatusToSdk( param[1]);
		}
		break;
		default:
		break;
	}
}

void getRadarInfo(u8 *param,u8 len)
{
	//outPutLogg(__FUNCTION__,"param",param,len);
	LOGD("getRadarInfo");
	int i ;
	for (i = 0;i<len;i++)
		LOGD("param[%d] :%x",i,param[i]);
	switch(param[0])
	{
		case 0x00://F
		case 0x05://B
		case 0x0A://L
		case 0x10://R
			getRadarData(param);
		break;
		case 0x15://Radar PAGE
		break;
		case 0x16://Radar POP
			//getRadarPOP(param[1]);
		break;
		case 0x20:	
		case 0x25:
			getRadarDistanceData(param,len);
		break;
		default:
		break;
	}
}

void getGearsInfo(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			{
				if(pLocalParam->nGearsValue != param[1])
					pLocalParam->nGearsValue = param[1];
			}
			break;
		default:
			break;
	}
}
/****************/
void process_BasicCarInfo(u8 param,u8 data)
{
	printf("\n [%s]:%d, %d",__FUNCTION__,param,data);
	LOGD("\n [%s]:%d, %d",__FUNCTION__,param,data);
	switch(param)
	{
		case 0x00:
			process_SafetyBeltInfo();
			break;
		case 0x01:
			new_Process_OilRemindInfo();
			break;
		case 0x02:
			new_Process_DrivingDistanceInfo();
			break;
		case 0x03:
			new_Process_DegreeOfCarGroundInfo();
			break;
		case 0x04:
			process_HandLockerInfo(1);
			break;
		case 0x05:
			new_Process_EngineSpeedInfo();
			break;
		case 0x06:
			new_PublicAverageSpeedInfo();
			break;
		case 0x07:
			new_Process_InstantSpeedInfo();
			break;
		case 0x08:
			{
				if(data == 0x00){
					new_Process_BatteryVoltageInfo();
				}
			}
			break;
		case 0x0B:
			showContinuedDriveMileage();
			break;
		case 0x0D:
			new_process_avgOilWearInfo();
			break;
		case 0x0E:
		case 0x11:
			new_Process_DoorInfo(0);
			break;
		case 0x14:
			break;
		case 0x18:
			showGearsInfoToExtcar();
			break;
		default:
			break;
	}
}

void new_Process_OilRemindInfo()
{
	u8 ansiBuf[128];
	int nNeedPlayAudioTimes = 0;
	int nOilRemind = pLocalParam->nOilRemind;
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (nOilRemind == 0xFFFF)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%dL", nOilRemind);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REMAINING_TXT, ansiBuf, nAnsiBufLen);
	g_clsExtcar.sendToFlyJniSdk_OilRemind(nOilRemind);
	g_clsExtcar.extcarSendRemainOilToSdk(nOilRemind);
}

void new_Process_DrivingDistanceInfo()
{
	u8 ansiBuf[128];
	int temp =  pLocalParam->publicDrivingDistance;
	int nDrivingDistance = temp/100;
	memset(ansiBuf, 0, sizeof(ansiBuf));
	if (pLocalParam->publicDrivingDistance == -1)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else if(pLocalParam->publicDrivingDistanceUint == 0x01)
		sprintf((char*)ansiBuf,"%dMile", nDrivingDistance);
	else 
		sprintf((char*)ansiBuf,"%dKm", nDrivingDistance);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_MILEAGE_NEW_TXT, ansiBuf, nAnsiBufLen);
	setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_MILEAGE_NEW_IAMGE, 0);
	if(temp == -1)
		temp = 0xFFFFFFFF;
	g_clsExtcar.extcarSendDriveMileageToSdk(temp);
	g_clsExtcar.sendToFlyJniSdk_DrivingDistance(nDrivingDistance);
}

void new_Process_DegreeOfCarGroundInfo()
{
	u8 ansiBuf[64];
	float lfDegreeOfCarGround = (float)(pLocalParam->publicDegreeOfCarGround / 100.0);
	memset(ansiBuf, 0, sizeof(ansiBuf));

	g_clsExtcar.sendToFlyJniSdk_DegreeOfCarGround(pLocalParam->publicDegreeOfCarGround);
	g_clsExtcar.extcarSendOutSideTemperatureToSdk(pLocalParam->publicDegreeOfCarGround,
					pLocalParam->CarGroundDecimalNumber,pLocalParam->CarGroundUnit ,pLocalParam->CarGroundPosOrNeg);
	if (pLocalParam->publicDegreeOfCarGround == 0xFFFF)
	{
		sprintf((char*)ansiBuf,"%s", "N/A");
		int nAnsiBufLen = strlen((char*)ansiBuf);
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_OUTSIDE_TEMPERATURE_TXT, ansiBuf, nAnsiBufLen);
	}
	else
	{
		u8 unicBuf[32] = {0};
		u8 unicBuf1[64] = {0};
		if(pLocalParam->CarGroundDecimalNumber == 0)
			sprintf((char*)ansiBuf,"%.0f", lfDegreeOfCarGround);
		else if(pLocalParam->CarGroundDecimalNumber == 1)
			sprintf((char*)ansiBuf,"%.1f", lfDegreeOfCarGround);
		else  if(pLocalParam->CarGroundDecimalNumber == 2)
			sprintf((char*)ansiBuf,"%.2f", lfDegreeOfCarGround);

		wchar_t wcharBuf_C[10] = L"℃";
		wchar_t wcharBuf_F[10] = L"℉";
		u32 dwUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicBuf);
		if(pLocalParam->CarGroundUnit == 0x00)
			memcpy((char*)unicBuf + dwUnicodeBufLen * 2, (char*)wcharBuf_C, 2);
		else if(pLocalParam->CarGroundUnit == 0x01)
			memcpy((char*)unicBuf + dwUnicodeBufLen * 2, (char*)wcharBuf_F, 2);

		int uLen = 0;
		if(pLocalParam->CarGroundPosOrNeg == 0x01)
		{
			u32 len1 = ansi_str_to_unicode16((u8 *)"-" , (unicode16_t*)unicBuf1 );
			memcpy((char*)unicBuf1 + (len1*2), unicBuf,dwUnicodeBufLen * 2 + 2);
			uLen = len1*2 + dwUnicodeBufLen * 2 + 2;
		}
		else if(pLocalParam->CarGroundPosOrNeg == 0x00)
		{
			memcpy((char*)unicBuf1, unicBuf,dwUnicodeBufLen * 2 + 2);
			uLen =  dwUnicodeBufLen * 2 +2;
		}
		
		setSerialData(CONTROLIDTRAVEL_CARINFO_OUTSIDE_TEMPERATURE_TXT, (u8*)unicBuf1, uLen);
		if(pLocalParam->CarGroundUnit == 0x01)
		{
			if (lfDegreeOfCarGround >= 104)
				setAnalogData(CONTROLIDTRAVEL_CARINFO_OUTSIDE_TEMPERATURE_IAMGE, 1);
			else
				setAnalogData(CONTROLIDTRAVEL_CARINFO_OUTSIDE_TEMPERATURE_IAMGE, 0);
		}
		else 
		{
			if (lfDegreeOfCarGround >= 40.0)
				setAnalogData(CONTROLIDTRAVEL_CARINFO_OUTSIDE_TEMPERATURE_IAMGE, 1);
			else
				setAnalogData(CONTROLIDTRAVEL_CARINFO_OUTSIDE_TEMPERATURE_IAMGE, 0);
		}
	}
}

void new_Process_EngineSpeedInfo()
{
	u8 ansiBuf[128];
	int nEngineSpeed = pLocalParam->publicEngineSpeed;
	memset(ansiBuf, 0, sizeof(ansiBuf));

	if (nEngineSpeed== 0xFFFF)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%drpm", nEngineSpeed);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SPEED_TXT, ansiBuf, nAnsiBufLen);
	setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SPEED_IAMGE, 0);

	g_clsExtcar.sendToFlyJniSdk_EngineSpeed(nEngineSpeed);
	g_clsExtcar.extcarSendEngineSpeedToSdk(pLocalParam->publicEngineSpeed);
}

void new_Process_InstantSpeedInfo()
{
	static bool bNeedNotice = false;
	u8 ansiBuf[128];
	double lfInstantSpeed = (double)(pLocalParam->publicnIStantSpeed / 100.0);
	if (lfInstantSpeed <= 2.0)
		bNeedNotice = true;
	memset(ansiBuf, 0, sizeof(ansiBuf));
	if (pLocalParam->publicnIStantSpeed == 0xFFFF)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%.2lfkm/h",  lfInstantSpeed);
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_PUBLIC_INSTANT_SPEED_TEXT, ansiBuf, nAnsiBufLen);
	g_clsExtcar.sendToFlyJniSdk_InstantSpeed(pLocalParam->publicnIStantSpeed);
	g_clsExtcar.extcarSendInstantSpeedToSdk(pLocalParam->publicnIStantSpeed);
	   if ((pLocalParam->bOpenVoiceLater && bNeedNotice && (double)(pLocalParam->publicnIStantSpeed / 100.0) >= 10.0) ||
	   	(pLocalParam->bOpenVoiceAndNeedAlarm && pLocalParam->bOpenVoiceLater)
	   	)
	    {
			pLocalParam->bOpenVoiceAndNeedAlarm = false;
			bNeedNotice = false;
			DeleteTimer(EXTCAR_TIMER_ID_CAR_SPEED_CHECK);
			SetTimer(200, 1, EXTCAR_TIMER_ID_CAR_SPEED_CHECK);
	    }
}

void new_PublicAverageSpeedInfo()
{
	static bool bNeedNotice = false;
	u8 ansiBuf[128];
	double lfAverageSpeed = (double)(pLocalParam->publicAverageSpeed / 100.0);
	if (lfAverageSpeed <= 2.0)
		bNeedNotice = true;
	memset(ansiBuf, 0, sizeof(ansiBuf));
	if (pLocalParam->publicAverageSpeed == 0xFFFF)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%.2lfkm/h",  lfAverageSpeed);
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_PUBLIC_AVERAGE_SPEED_TEXT, ansiBuf, nAnsiBufLen);
	g_clsExtcar.extcarSendPublicAverageSpeedToSdk(pLocalParam->publicAverageSpeed);
/*
	g_clsExtcar.sendToFlyJniSdk_InstantSpeed(pLocalParam->publicAverageSpeed);
	   if ((pLocalParam->bOpenVoiceLater && bNeedNotice && (double)(pLocalParam->publicAverageSpeed / 100.0) >= 10.0) ||
	   	(pLocalParam->bOpenVoiceAndNeedAlarm && pLocalParam->bOpenVoiceLater)
	   	)
	    {
			pLocalParam->bOpenVoiceAndNeedAlarm = false;
			bNeedNotice = false;
			DeleteTimer(EXTCAR_TIMER_ID_CAR_SPEED_CHECK);
			SetTimer(200, 1, EXTCAR_TIMER_ID_CAR_SPEED_CHECK);
	    }
*/
}

void new_Process_BatteryVoltageInfo()
{
	u8 ansiBuf[128];
	memset(ansiBuf, 0, sizeof(ansiBuf));
	printf("process_BatteryVoltageInfo:%d",pLocalParam->nBatteryVoltage);
	if (pLocalParam->nBatteryVoltage == 0xFFFF)
	{
		sprintf((char*)ansiBuf,"%s", "N/A");
		setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_VOLTAGE_TXT, ansiBuf, strlen((char*)ansiBuf));
		g_clsExtcar.sendToFlyJniSdk_BatteryVoltageInfo(pLocalParam->nBatteryVoltage);
		return ;
	}
	
	double lfBatteryVoltage = (double)(pLocalParam->nBatteryVoltage / 100.0);
	sprintf((char*)ansiBuf,"%.2lfV", lfBatteryVoltage);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_VOLTAGE_TXT, ansiBuf, nAnsiBufLen);
	if (lfBatteryVoltage < 10.0)
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_VOLTAGE_IAMGE, 1);
	else
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_VOLTAGE_IAMGE, 0);

	g_clsExtcar.sendToFlyJniSdk_BatteryVoltageInfo(pLocalParam->nBatteryVoltage);
	g_clsExtcar.extcarSendBatteryVoltageToSdk(pLocalParam->nBatteryVoltage);
	exterToSystem_aboutBatteryVoltageInfo(pLocalParam->nBatteryVoltage);
	
}

void new_Process_BatteryVoltageAnomalyMonitoringInfo()
{
	
}

void new_process_avgOilWearInfo()
{
	u8 strAvgOilWear[30]={0};
	if (pLocalParam->avgOilWear == 0xFFFF){
		sprintf((char*)strAvgOilWear, "N/A");
		g_clsExtcar.sendToFlyJniSdk_AvgOilWearInfo(0,0xFF);
	}
	else{
		float avgOilWear = pLocalParam->avgOilWear/100.0;
		sprintf((char*)strAvgOilWear, "%.1fL/100km",avgOilWear);
		g_clsExtcar.sendToFlyJniSdk_AvgOilWearInfo(0,pLocalParam->avgOilWear);
	}
	g_clsExtcar.extcarSendAverageFuelConsumptionToSdk(pLocalParam->avgOilWear);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_AVERAGE_FUEL_CONSUMPTION_TEXT,strAvgOilWear,strlen((char *)strAvgOilWear));

}

int new_Process_DoorInfo(int nFrom)
{
	if(pLocalParam->szDoorStatus[0] == 0xFF || pLocalParam->szDoorStatus[1] == 0xFF || pLocalParam->szDoorStatus[2] == 0xFF || pLocalParam->szDoorStatus[3] == 0xFF || pLocalParam->szDoorStatus[4] == 0xFF)
		return 0;
	
	int nNeedPlayAudioTimes = 0;
	u8 nStatus = pLocalParam->szDoorStatus[0] + pLocalParam->szDoorStatus[1] + pLocalParam->szDoorStatus[2] + pLocalParam->szDoorStatus[3] + pLocalParam->szDoorStatus[4];
	if (nStatus != 0 && nStatus != 1)//����Ŵ�, ������������
	{
		nNeedPlayAudioTimes++;
		needToAlarm(CARINFO_ALARM_SOUND_SEVERAL_DOOR_OPEN);
	}
	else
	{
		if (pLocalParam->szDoorStatus[0] == 1)
		{
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_LEFT_FORWARD_DOOR_OPEN);
		}
		if (pLocalParam->szDoorStatus[1] == 1)
		{
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_RIGHT_FORWARD_DOOR_OPEN);
		}
		if (pLocalParam->szDoorStatus[2] == 1)
		{
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_LEFT_REAR_DOOR_OPEN);
		}
		if (pLocalParam->szDoorStatus[3] == 1)
		{
			nNeedPlayAudioTimes++;
			needToAlarm(CARINFO_ALARM_SOUND_RIGHT_REAR_DOOR_OPEN);
		}
	}

	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LEFT_UP, pLocalParam->szDoorStatus[0]);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_RIGHT_UP, pLocalParam->szDoorStatus[1]);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LEFT_DOWN, pLocalParam->szDoorStatus[2]);
	setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_RIGHT_DOWN, pLocalParam->szDoorStatus[3]);

	//////////////////////////////////////////////////////////////////////////
	if (pLocalParam->szDoorStatus[4])
	{
		if (1 == nNeedPlayAudioTimes)//up play, so need to settimer and play
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
	else
	{

		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_TXT,STRINGID_CAR_INFO_CLOSE);
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REAR_BOX_IAMGE, 0);

		setStringText(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK_TXT,STRINGID_CAR_INFO_CLOSE);
		setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK, 0);
		DeleteTimer(EXTCAR_TIMER_ID_PLAY_BACK_DOOR_AUDIO);	
	}
	//////////////////////////////////////////////////////////////////////////
	int t = 0;
	if(pLocalParam->szDoorStatus[0] != 0xFF && pLocalParam->szDoorStatus[4] != 0xFF)
	{
		t = (pLocalParam->szDoorStatus[0] + (pLocalParam->szDoorStatus[1]*2) + (pLocalParam->szDoorStatus[2]*4) + (pLocalParam->szDoorStatus[3]*8) + (pLocalParam->szDoorStatus[4]*32));
		g_clsExtcar.sendToFlyJniSdk_DoorInfo((char)t);
	}
	return nNeedPlayAudioTimes;
}
void showGearsInfoToExtcar()
{
	u8 ansiBuf[128];
	memset(ansiBuf, 0, sizeof(ansiBuf));
	analyseGearInfo(pLocalParam->nGearsValue, ansiBuf);
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT, ansiBuf, nAnsiBufLen);
	g_clsExtcar.extcarSendGearsInfoToSdk(pLocalParam->nGearsValue);
}

void analyseGearInfo(u8 param, u8 *buf)
{
	switch(param)
	{
		case 0x00:
			sprintf((char*)buf,"%s",  "P");
			break;
		case 0x01:
			sprintf((char*)buf,"%s",  "R");
			break;
		case 0x02:
			sprintf((char*)buf,"%s",  "N");
			break;
		case 0x10:
			sprintf((char*)buf,"%s",  "D");
			break;
		case 0x11:
			sprintf((char*)buf,"%s+", "D");
			break;
		case 0x12:
			sprintf((char*)buf,"%s-",  "D");
			break;
		case 0x20:
			sprintf((char*)buf,"%s",  "S");
			break;
		case 0x21:
			sprintf((char*)buf,"%s+",  "S");
			break;
		case 0x22:
			sprintf((char*)buf,"%s-",  "S");
			break;
		case 0x30:
			sprintf((char*)buf,"%s",  "L");
			break;
		case 0xFF:
			sprintf((char*)buf,"%s", "N/A");
			break;
			default:break;
	}
}

void getPublicElectronicBoosterMode(u8 *param,int len)
{
		analysePublicElectronicBoosterMode(param[0]);
}
void getPublicRemoteControlLocFeedback (u8 *param,int len)
{
	analysegetPublicRemoteControlLocFeedback(param[0]);
}
void getPublicShutDownTheUnlock (u8 *param,int len)
{
	analysePublicShutDownTheUnlock(param[0]);
}
void getPublicPositionAfterLocking(u8 *param,int len)
{
	analysePublicPublicPositionAfterLocking(param[0]);
}
void getPublicPositionSpeedAlarmSwitchAndThreshold(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			analysePublicSpeedAlarmSwitch(param+1,len -1);
		break;
		case 0x01:
			analysePublicSpeedAlarmThreshold(param+1,len -1);
		break;
		case 0x02:
			analysePublicSpeedAlarmIncAndDec(param+1,len -1);
		break;
	}
}

void analysePublicSpeedAlarmSwitch(u8 *p,int len)
{
	pLocalParam->uSpeedAlarmSwitch = p[0];
	DispalyingUI_speed_limit_alarm_switch(p[0]);
}

void analysePublicSpeedAlarmThreshold(u8 *p,int len)//
{
	u16 sMin = 0xFF;
	memcpy(&sMin,&p[0],2);
	
	u16 sMax = 0xFF;
	memcpy(&sMax,&p[2],2);
	
	u16 sStep = 0xFF;
	memcpy(&sStep,&p[4],2);
	
	u16 sV = 0xFF;
	memcpy(&sV,&p[6],2);
	sV = (sV/100);
	pLocalParam->uSpeedAlarmValue = sV;
	DispalyingUI_speed_limit_alarm_Value(sV);
}

void analysePublicSpeedAlarmIncAndDec(u8 *p,int len)
{
}

void getPublicPositionTrunkDegree(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			analysePublicTrunkDegreeValue(param+1,len -1);
		break;
		case 0x01:
			analysePublicTrunkDegreeIncAndDec(param+1,len -1);
		break;
	}
}

void analysePublicTrunkDegreeValue(u8 *p,int len)
{
	u8 uMix = p[0];
	u8 uMax = p[1];
	u8 uStep = p[2];
	pLocalParam->uTrunkDegreeMin = p[0];
	pLocalParam->uTrunkDegreeMax = p[1];
	pLocalParam->uTrunkDegreeStep = p[2];
	pLocalParam->uTrunkDegreeValue = p[3];
	DispalyingUI_trunk_opening_degree_Value(p[3]);
	DispalyingUI_trunk_opening_degree_Value_Bar(p[3],p[0]);
}

void analysePublicTrunkDegreeIncAndDec(u8 *p,int len)
{
}

void getPublicWelcomeLamp(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			analysePublicWelcomeLampSwitch(param+1,len -1);
		break;
		case 0x01:
			analysePublicWelcomeLampTimeValue(param+1,len -1);
		break;
	}
}

void analysePublicWelcomeLampSwitch(u8 *p,int len)
{
	pLocalParam->uWelcomeLampSwitch = p[0];
	DispalyingUI_welcome_lamp_switch(p[0]);
}

void analysePublicWelcomeLampTimeValue(u8 *p,int len)
{
	memcpy(&pLocalParam->uWelcomeLampOpenTimeMix,&p[0],2);
	memcpy(&pLocalParam->uWelcomeLampOpenTimeMax,&p[2],2);
	memcpy(&pLocalParam->uWelcomeLampOpenTimeStep,&p[4],2);

	u16 sT = 0xFFF;
	memcpy(&sT,&p[6],2);
	pLocalParam->uWelcomeLampOpenTime = sT;
	DispalyingUI_welcome_lamp_open_time(sT);
}

void getPublicCompanyLampHome(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			analysePublicCompanyLampHomeSwtich(param+1,len -1);
		break;
		case 0x01:
			analysePublicCompanyLampHomeTimeValue(param+1,len -1);
		break;
	}
}

void analysePublicCompanyLampHomeSwtich(u8 *p,int len)
{
	pLocalParam->uCompanyLampHomeSwitch = p[0];
	DispalyingUI_company_home_lamp_switch(p[0]);
}

void analysePublicCompanyLampHomeTimeValue(u8 *p,int len)
{
	memcpy(&pLocalParam->uLampCompanyHomeTimeMix,&p[0],2);
	memcpy(&pLocalParam->uLampCompanyHomeTimeMax,&p[2],2);
	memcpy(&pLocalParam->uLampCompanyHomeTimeStep,&p[4],2);

	u16 sT = 0;
	memcpy(&sT,&p[6],2);
	pLocalParam->uCompanyLampHomeTime = sT;
	DispalyingUI_company_home_lamp_open_time(sT);
}


void getPublicvehicle_mode(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			analysePublicVehicle_mode(param+1,len -1);
		break;
	}
}

void analysePublicVehicle_mode(u8 *p,int len)
{
	pLocalParam->uVehicle_mode = p[0];
	DispalyingUI_vehicle_mode(p[0]);
}


void getPublicDriving_automatic_latch(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			analysePublicDriving_automatic_latch_Switch(param+1,len -1);
		break;
		case 0x01:
			analysePublicDriving_automatic_latch_SpeedValue(param+1,len -1);
		break;
		case 0x02:
			analysePublicDriving_automatic_latch_IncAndDec(param+1,len -1);
		break;
	}
}

void analysePublicDriving_automatic_latch_Switch(u8 *p,int len)
{
	pLocalParam->uDrivingAutomaticLatchSwitch = p[0];
	DispalyingUI_driving_automatic_latch_switch(p[0]);
}

void analysePublicDriving_automatic_latch_SpeedValue(u8 *p,int len)
{
	u16 sT = 0;
	memcpy(&sT,&p[4],2);
	pLocalParam->uDrivingAutomaticLatchSpeed = sT;
}

void analysePublicDriving_automatic_latch_IncAndDec(u8 *p,int len)
{
}



void getPublicFlameout_Automatic_Latch(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			analysePublicFlameout_Automatic_Latch(param+1,len -1);
		break;
	}
}

void analysePublicFlameout_Automatic_Latch(u8 *p,int len)
{
	pLocalParam->uFlameoutAutomaticLatchSwitch = p[0];
	DispalyingUI_flameout_automatic_latch_switch(p[0]);
}


void getPublicKey_Unlock_Door(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			analysePublicKey_Unlock_Door(param+1,len -1);
		break;
	}
}

void analysePublicKey_Unlock_Door(u8 *p,int len)
{
	pLocalParam->uKeyUnlockDoor = p[0];
	DispalyingUI_key_unlock_door(p[0]);
}

void getPublicKeyLess_Unlock_Door(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			analysePublicKeyLess_Unlock_Door(param+1,len -1);
		break;
	}
}

void analysePublicKeyLess_Unlock_Door(u8 *p,int len)
{
	pLocalParam->uKeyLessUnlockDoor = p[0];
	DispalyingUI_keyLess_unlock_door(p[0]);
}

void getPublicACSetData(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			analysePublicAC_automatic_mode_flow(param+1,len -1);
		break;
		case 0x01:
			analysePublicF_B_Defrost_Fog_Linkage_switch(param+1,len -1);
		break;
	}
}

void analysePublicAC_automatic_mode_flow(u8 *p,int len)
{
	pLocalParam->uAC_automaticModeFlow = p[0];
	DispalyingUI_AC_automatic_mode_flow(p[0]);
}

void analysePublicF_B_Defrost_Fog_Linkage_switch(u8 *p,int len)
{
	pLocalParam->uFBdeforstFogLinkSwitch = p[0];
	DispalyingUI_F_B_Defrost_Fog_Linkage_switch(p[0]);
}


void getPublicMirrorAutomaticOpenSwitch(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
			analysePublicMirrorAutomaticOpenSwitch(param+1,len -1);
		break;
	}
}

void getPublicSystemLanguageSet(u8 *param, u8 len)
{
	switch(param[0])
	{
		case 0x00:
			extcarToApp_SetSystemLanguage(param[1]);
		break;
	}
}

void analysePublicMirrorAutomaticOpenSwitch(u8 *p,int len)
{
	pLocalParam->uMirrorAutomaticOpenSwitch = p[0];
	DispalyingUI_Mirror_automatic_open_switch(p[0]);
}


void analysePublicElectronicBoosterMode (u8 param)
{
	if(param == 0x00)
	    	setStringText(CONTROLIDTRAVEL_CARINFO_PUBLIC_ELECTRONUC_BOOSTER_TXT, STRINGID_CAR_INFO_ELECTRONIC_BOOSTER_COMFORTABLE_MODE);
	else if(param == 0x01)
		setStringText(CONTROLIDTRAVEL_CARINFO_PUBLIC_ELECTRONUC_BOOSTER_TXT, STRINGID_CAR_INFO_ELECTRONIC_BOOSTER_MOVE_MODE);
	else if(param == 0xFF)
		setStringText(CONTROLIDTRAVEL_CARINFO_PUBLIC_ELECTRONUC_BOOSTER_TXT, STRINGID_CAR_INFO_ELECTRONIC_BOOSTER_COMFORTABLE_MODE);
	pLocalParam->tagBoosterMode = param;
}

void analysegetPublicRemoteControlLocFeedback (u8 param)
{
	if(param == 0x00)
		setStringText(CONTROLIDTRAVEL_CARINFO_PUBLIC_REMOTE_PADLOCK_TXT, STRINGID_CAR_INFO_REMOTE_CONTROL_LOCK_RING);
	else if(param == 0x01)
		setStringText(CONTROLIDTRAVEL_CARINFO_PUBLIC_REMOTE_PADLOCK_TXT, STRINGID_CAR_INFO_REMOTE_CONTROL_LOCK_NO_RING);
	else if(param == 0xFF)
		setStringText(CONTROLIDTRAVEL_CARINFO_PUBLIC_REMOTE_PADLOCK_TXT, STRINGID_CAR_INFO_REMOTE_CONTROL_LOCK_RING);
	pLocalParam->tagLocFeedback = param;
}

void analysePublicShutDownTheUnlock (u8 param)
{
	if(param == 0x00)
		setDigitalData(CONTROLIDTRAVEL_CARINFO_PUBLIC_SET_SHUT_DOWN_UNLOCK,0);
	else if(param == 0x01)
		setDigitalData(CONTROLIDTRAVEL_CARINFO_PUBLIC_SET_SHUT_DOWN_UNLOCK,1);
	else if(param == 0xFF)
		setDigitalData(CONTROLIDTRAVEL_CARINFO_PUBLIC_SET_SHUT_DOWN_UNLOCK,0);
	pLocalParam->tagShutDownUnlock = param;
}

void analysePublicPublicPositionAfterLocking (u8 param)
{
	if(param == 0x00)
		setDigitalData(CONTROLIDTRAVEL_CARINFO_PUBLIC_SET_REMOVE_HEAT_POSITION,0);
	else if(param == 0x01)
		setDigitalData(CONTROLIDTRAVEL_CARINFO_PUBLIC_SET_REMOVE_HEAT_POSITION,1);
	else if(param == 0xFF)
		setDigitalData(CONTROLIDTRAVEL_CARINFO_PUBLIC_SET_REMOVE_HEAT_POSITION,0);
	pLocalParam->tagPositionAfterLock = param;
}

void getContinuedDriveMileageData(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			pLocalParam->ContinuedDriveMileage =  param[1] + (param[2] << 8);
		}
		break;
		default:
		break;
	}
}

void showContinuedDriveMileage()
{
	u8 ansiBuf[128];
	int nDrivingDistance = pLocalParam->ContinuedDriveMileage/100;
	memset(ansiBuf, 0, sizeof(ansiBuf));
	if (pLocalParam->ContinuedDriveMileage == 0xFFFF ||pLocalParam->ContinuedDriveMileage < 0)
		sprintf((char*)ansiBuf,"%s", "N/A");
	else
		sprintf((char*)ansiBuf,"%dkm", nDrivingDistance);
	
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_RUNNING_MILEAGE_TEXT, ansiBuf, nAnsiBufLen);
	g_clsExtcar.sendToFlyJniSdk_MileageCanRun(nDrivingDistance);
	g_clsExtcar.extcarSendContinuedDriveMileageToSdk(pLocalParam->ContinuedDriveMileage);

}

void getRadarDistanceData(u8 *param,int len)
{
	u8 uUnit = param[1];
	u16 minDistance = param[2] + (param[3] << 8);
	u16 maxDistance = param[4] + (param[5] << 8);
	u16 uT = param[6] + (param[7] << 8);
	
	if(param[0] == 0x20)
	{
		pLocalParam->uFrontRadarDistance = uT;
		if((uT >= minDistance && uT <=maxDistance) ||
			uT == 0xFFF9 || uT == 0xFFFA||
			uT == 0xFFFE || uT == 0xFFFF ){
			analyseRadarDistanceData(0x00,uT,uUnit);
		}
	}
	else if(param[0] == 0x25)
	{
		pLocalParam->uRearRadarDistance = uT;
		LOGD("Cur:%d      M:%d --- I:%d",uT,maxDistance,minDistance);
		if((uT >= minDistance && uT <=maxDistance) ||
			uT == 0xFFF9 || uT == 0xFFFA||
			uT == 0xFFFE || uT == 0xFFFF ){
			analyseRadarDistanceData(0x01,uT,uUnit);
		}
	}
}

void analyseRadarDistanceData(u8 ForR,u16 p,u8 tag)
{
	if(ForR == 0x00)
	{
		if(p == 0xFFF9)
		{
			
		}
		else if(p == 0xFFFA)
		{
		
		}
		else if(p == 0xFFFE || p == 0xFFFF)
		{
		
		}
		else
		{
			
		}
	}
	else if(ForR == 0x01)
	{
		LOGD("uRearRadarDistance:%x",p);
		if(p == 0xFFF9)
		{
			setVisible(CONTROLID_BACK_VIDEO_RADAR_TOO_CLOSE_IAMGE,false);
			setVisible(CONTROLID_BACK_VIDEO_RADAR_DISTANCE_TXT,false);
			setVisible(CONTROLID_BACK_VIDEO_RADAR_DISTANCE_UNIT,false);
		}
		else if(p == 0xFFFA)
		{
			setVisible(CONTROLID_BACK_VIDEO_RADAR_TOO_CLOSE_IAMGE,true);
			setVisible(CONTROLID_BACK_VIDEO_RADAR_DISTANCE_TXT,false);
			setVisible(CONTROLID_BACK_VIDEO_RADAR_DISTANCE_UNIT,false);
		}
		else if(p == 0xFFFE || p == 0xFFFF)
		{
			setVisible(CONTROLID_BACK_VIDEO_RADAR_TOO_CLOSE_IAMGE,false);
			setVisible(CONTROLID_BACK_VIDEO_RADAR_DISTANCE_TXT,false);
			setVisible(CONTROLID_BACK_VIDEO_RADAR_DISTANCE_UNIT,false);
		}
		else
		{
			setVisible(CONTROLID_BACK_VIDEO_RADAR_DISTANCE_TXT,true);
			setVisible(CONTROLID_BACK_VIDEO_RADAR_TOO_CLOSE_IAMGE,false);	
			setVisible(CONTROLID_BACK_VIDEO_RADAR_DISTANCE_UNIT,true);
		}
		
		showRadarRearDistanceData(p,tag);
	}
}
void showRadarRearDistanceData(u16 p ,u8 tag)
{
	u8 ansiBuf[128];
	u16 nRadarDistance = p;
	float nRadarDistanceM = p/100.0;
	memset(ansiBuf, 0, sizeof(ansiBuf));
	if(p != 0xFFF9 && p!=0xFFFA && p!=0xFFFE&& p!=0xFFFF)
	{
		if(tag == 0x00)
			sprintf((char*)ansiBuf,"%d", nRadarDistance);
		else if(tag == 0x01)
			sprintf((char*)ansiBuf,"%.2f", nRadarDistanceM);
	}
	else
		sprintf((char*)ansiBuf," ");
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLID_BACK_VIDEO_RADAR_DISTANCE_TXT, ansiBuf, nAnsiBufLen);
}

void analysePublicBackCarViodeMessage(u8 *p,u8 len)
{
	if(p[0] != 0x12)
		return;
	switch(p[1])
	{
		case 0x00:
				ExtcarToModule_system_PublicVehicleSettings(p,len);
			break;
		case 0x05:
				ExtcarToModule_BackCar_VideoSet(p,len);
			break;
		default:break;
	}
}

int getMainDriverRightDoorInfo(int num)
{
       int a,b,c,d,e;
       a = 0;b = 0;c = 0;d= 0;e =0;
       a = (num&1)&15;
       b = (num&2)>>1&15;
       c = (num&4)>>2&15;
       d = (num&8)>>3&15;
       e = b + a*2+ d*8+c*4;
       return e;
}

void  getDoorLockStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			if(param[1] == 0x00)
			{
				memset(pLocalParam->szDoorLockStatus, 0x01, sizeof(pLocalParam->szDoorLockStatus));
			}
			else if(param[1] == 0x01)
			{
				memset(pLocalParam->szDoorLockStatus, 0x00, sizeof(pLocalParam->szDoorLockStatus));
			}
			else if(param[1] == 0xFF)
				memset(pLocalParam->szDoorLockStatus, 0xFF, sizeof(pLocalParam->szDoorLockStatus));
			g_clsExtcar.extcarSendDoorLockStatusToSdk(pLocalParam->szDoorLockStatus,4);
			LOGD("[%s] :%x  %x  %x  %x",__FUNCTION__,pLocalParam->szDoorLockStatus[0],pLocalParam->szDoorLockStatus[1],pLocalParam->szDoorLockStatus[2],pLocalParam->szDoorLockStatus[3]);
		}
		break;
		case 0x01:
		{
			if(len < 5)
				return;
			memset(pLocalParam->szDoorLockStatus, 0, sizeof(pLocalParam->szDoorLockStatus));
			memcpy(pLocalParam->szDoorLockStatus, param + 1, 4);
			g_clsExtcar.extcarSendDoorLockStatusToSdk(param + 1,4);
			LOGD("[%s] :%x  %x  %x  %x",__FUNCTION__,pLocalParam->szDoorLockStatus[0],pLocalParam->szDoorLockStatus[1],pLocalParam->szDoorLockStatus[2],pLocalParam->szDoorLockStatus[3]);
		}
		break;
		default:
		break;
	}
}

void  getFrontCoverStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			pLocalParam->nFrontCover = param[1];
			g_clsExtcar.extcarSendFrontCoverStatusToSdk(param[1]);
			LOGD("[%s] :%x ",__FUNCTION__,pLocalParam->nFrontCover);
		}
		break;
		default:
		break;
	}
}

void  getSkyLightStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			pLocalParam->nSkyLight = param[1];
			g_clsExtcar.extcarSendSkyLightStatusToSdk(param[1]);
			LOGD("[%s] :%x ",__FUNCTION__,pLocalParam->nSkyLight);
		}
		break;
		default:
		break;
	}
}

void  getLightStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
		}
		break;
		case 0x05:
		{
			getDippedHeadlightStatus(param[1]);
		}
		break;
		case 0x0A:
		{
			getHighBeamStatus(param[1]);
		}
		break;
		default:
		break;
	}
}

void getHighBeamStatus(u8 param)
{
	pLocalParam->nHighBeam = param;
	g_clsExtcar.extcarSendLightStatusToSdk(0x0A,param);
	LOGD("[%s] :%x ",__FUNCTION__,pLocalParam->nHighBeam);
}
void getDippedHeadlightStatus(u8 param)
{
	pLocalParam->nDippedHeadlight = param;
	g_clsExtcar.extcarSendLightStatusToSdk(0x05,param);
	LOGD("[%s] :%x ",__FUNCTION__,pLocalParam->nDippedHeadlight);
}

void getVINCode(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			getVINCodeInfo(param + 1,len - 1);
		}
		break;
		default:
		break;
	}
}

void getVINCodeInfo(u8 *param,u8 len)
{
	if(len > 17)
		len =17;
	memset(pLocalParam->szVINCode,0,sizeof(pLocalParam->szVINCode));
	memcpy(pLocalParam->szVINCode,param,len);
	g_clsExtcar.extcarSendVINCodeToSdk(param,len)	;
	LOGD("VINcode %x %x %x %x",param[0],param[1],param[2],param[3]);
}

void getPublicFordTCUMessage(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x00://FinalActiveRequest
				ExtcarToAPP_TCU_ActiveRequest(p[1]);
			break;
		case 0x05://FinalActiveStatus
			break;
		default:break;
	}
}

void getPublicFordAmbientLedMessage(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x00:
			break;
		case 0x05://color set
			analyseAmbientLedColorValue(p[1]);
			break;
		case 0x0A://brightness set
			analyseAmbientLedBrightnessValue(&p[1]);
			break;
		default:break;
	}
}

void getPublicAuxiliaryParkingSystemMessage(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x00://Parking Mode
			analyseParkingAssistMode(p[1]);
			break;
		case 0x01:
			analyseParkingAssistModeIsActivety(&p[1]);
			break;
		case 0x05://Parking Assist Status
			analyseParkingAssistMsg(&p[1],len - 1);
			break;
			break;
		default:break;
	}
}

void analyseAmbientLedColorValue(u8 param)
{
	u8 uMsg[] = {0x00,0xFF};
	uMsg[1] = param;
	ExtcarToModule_system_PublicVehicleSettings(uMsg,sizeof(uMsg));
}

void analyseAmbientLedBrightnessValue(u8 *param)
{
	u8 uMsg[] = {0x01,0xFF,0xFF,0xFF,0xFF};
	memcpy(&uMsg[1],param,4);
	ExtcarToModule_system_PublicVehicleSettings(uMsg,sizeof(uMsg));
}

void getRadarData(u8 *p)
{
	LOGD("%s :(%x,%x,%x,%x,%x,%x,%x,%x,%x)",__FUNCTION__,p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8]);
	if(p[5] == 0xFF || p[6] == 0xFF || p[7] == 0xFF || p[8] == 0xFF)
		return;
	
	if((p[5] > p[1]) || (p[6] > p[2]) || (p[7] > p[3]) || (p[8] > p[4]))
		return;

	u8 pos = 0xFF;
	switch(p[0])
	{
		case 0x00://F
		pos = 0x00;
		break;
		case 0x05://B
		pos = 0x01;
		break;
		case 0x0A://L
		pos = 0x02;
		break;
		case 0x10://R
		pos = 0x03;
		break;
	}

	u8 uMax_Level_1 = p[1];
	u8 uMax_Level_2 = p[2];
	u8 uMax_Level_3 = p[3];
	u8 uMax_Level_4 = p[4];

	u32 data = 0;
	memcpy(&data, p + 5, 4);
	
	exterToRadar(pos, data);
	extcarToApp_OpenBombBox_RadarData(pos,p + 5);
}

void getRadarPOP(u8 p)
{
	extcarToApp_OpenBombBox_Radar(p);
}

void analyseParkingAssistMode(u8 s)
{
	LOGD("[%s]%x","PARKING analyseParkingAssistMode",s);
	pLocalParam->uParkingModeState = s;
	switch(s)
	{
		case 0x00://close park
			{
				u8 ucBackMode = 0;
				u8 ucBackModeLen = 0;
				getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,&ucBackModeLen);
				if(ucBackMode != 1)
				{
					extcarToModule_NotifySystem_jumpPrePage();
				}
			}
			break;
		case 0x01://parallel park
			extcarToModule_NotifySystem_jumpPage(PAGE_PARALLEL_PARK_PAGE);
			break;
		case 0x02://perpendicular park
			extcarToModule_NotifySystem_jumpPage(PAGE_PERPENDICULAR_PARK_PAGE);
			break;
		case 0x03://park out assist
			extcarToModule_NotifySystem_jumpPage(PAGE_PARK_OUT_ASSIST_PAGE);
			break;
		case 0xFF:
			break;
	}
}

void analyseParkingAssistModeIsActivety(u8 *param)
{
	LOGD("[%s]%x %x %x","PARKING analyseParkingAssistModeIsActivety",param[0],param[1],param[2]);
	if(param[0] == 1)//Parallel Park
	{
	}
	else
	{
	}

	if(param[1] == 1)//Perpendicular Park
	{
	}
	else
	{
	}

	if(param[2] == 1)//Park Out Assist
	{
		setAnalogData(CONTROLID_PARK_OUT_ASSIST_PARK_SWITCH_BUTTON, 0);
		setControllable(CONTROLID_PARK_OUT_ASSIST_PARK_SWITCH_BUTTON, 1);
	}
	else
	{
		setAnalogData(CONTROLID_PARK_OUT_ASSIST_PARK_SWITCH_BUTTON, 2);
		setControllable(CONTROLID_PARK_OUT_ASSIST_PARK_SWITCH_BUTTON, 0);
	}
}

void analyseParkingAssistMsg(u8 *param,u8 len)
{
	LOGD("[%s] %x","PARKING analyseParkingAssistMsg",param[0]);
	switch(param[0])//Active Park assist
	{
		case 0x01://please check surroundings for safety
		case 0x05://Cancelled by driver(Finish_Chime)
		case 0x06://Fault refer to owner guide(Warning_Chime)
		case 0x07://Cancelled by driver(Finish_Chime)
		case 0x08://Press Button Remove hands to resume parking
		case 0x09://Not available refer to owner guide(Warning_Chime)
		case 0x0D://Deactivated(Warning_Chime)
		case 0x0E://Driver forward to scan for parking spot(Warning_Chime)
		UI_ActiveParkAssit(param[0]);
		break;
	}
	
	switch(param[0])//Parallel Park
	{
		case 0x01://parking close
		case 0x0A://Finish_Chime
		case 0x0F://Stop Shift to forword
		case 0x10://Pull forward slowly Be prepared to stop
		case 0x11://Stop Shift to reverse
		case 0x12://Back up slowly Be prepared to stop
		case 0x20://///////
		case 0x21://
		case 0x22://///////
		case 0x23://
		case 0x24://///////
		case 0x25://
		case 0x26://///////
		case 0x27://
		case 0x28://///////
		case 0x29://
		case 0x2A://///////
		case 0x2B://
		case 0x2C://///////
		case 0x2D://
		case 0x2E://///////
		case 0x2F://
		
		case 0x32://
		case 0x33://
		case 0x34://
		case 0x35://
		case 0x36://
		case 0x37://
		case 0x38://
		case 0x39://
		case 0x3A://
		case 0x3B://
		case 0x3C://
		case 0x3D://
		case 0x3E://
		case 0x3F://
		
		case 0x42://
		case 0x43://
		case 0x44://
		case 0x45://
		case 0x46://
		case 0x47://
		case 0x48://
		case 0x49://
		case 0x4A://
		case 0x4B://
		case 0x4C://
		case 0x4D://
		case 0x4E://
		case 0x4F://
		
		case 0x52://
		case 0x53://
		case 0x54://
		case 0x55://
		case 0x56://
		case 0x57://
		case 0x58://
		case 0x59://
		case 0x5A://
		case 0x5B://
		case 0x5C://
		case 0x5D://
		case 0x5E://
		case 0x5F://

		case 0xE0:
		case 0xE1:
			
		case 0xE4:
		case 0xE5:
		case 0xE6:
		case 0xE7:
		case 0xE8:
		case 0xE9:
		case 0xF2:
		case 0xF3:
		UI_ParallelPark(param[0]);
		break;
	}
	
	switch(param[0])//Perpendicular Park
	{
		case 0x0B://Finish_Chime
		case 0x13://Stop Shift to forword
		case 0x14://Pull forward slowly Be prepared to stop
		case 0x15://Stop Shift to reverse
		case 0x16://Back up slowly Be prepared to stop
		
		case 0x60://////
		case 0x61:
		case 0x62://////
		case 0x63:
		case 0x64://////
		case 0x65:
		case 0x66://////
		case 0x67:
		case 0x68://////
		case 0x69:
		case 0x6A://////
		case 0x6B:
		case 0x6C://////
		case 0x6D:
		case 0x6E://////
		case 0x6F:
		case 0x70://////
		case 0x71:
		case 0x72://///
		case 0x73:
		case 0x74://///
		case 0x75:
		case 0x76://///
		case 0x77:
		case 0x78://///
		case 0x79:
		case 0x7A://///
		case 0x7B:
		case 0x7C:
		case 0x7D://///
		case 0x7E:
		case 0x7F:

		case 0x82:
		case 0x83:
		case 0x86:
		case 0x87:
		case 0x88:
		case 0x89:
		case 0x8A:
		case 0x8B:
		case 0x8C:
		case 0x8D:
		case 0x8E:
		case 0x8F: 
		case 0x92:
		case 0x93:
		case 0x94:
		case 0x95:
		case 0x96:
		case 0x97: 
		case 0x9A:
		case 0x9B:
		case 0x9C:
		case 0x9D:
		case 0x9E:
		case 0x9F: 

		case 0xA2:
		case 0xA3:
		case 0xA4:
		case 0xA5:
		case 0xA6:
		case 0xA7:
		case 0xA8:
		case 0xA9:
		case 0xAA:
		case 0xAB:
		case 0xAC:
		case 0xAD: 

		case 0xB0: 
		case 0xB1: 
		case 0xB2:
		case 0xB3:
		case 0xB4:
		case 0xB5:
		case 0xB6:
		case 0xB7:
		case 0xB8:
		case 0xB9:
		case 0xBA:
		case 0xBB:
		case 0xBC:
		case 0xBD: 
		case 0xBE:
		case 0xBF:

		case 0xC2:
		case 0xC3: 
		case 0xC4:
		case 0xC5: 
		case 0xC6:
		case 0xC7: 
		case 0xC8:
		case 0xC9: 
		case 0xCA:
		case 0xCB: 
		case 0xCC:
		case 0xCD:

	   	case 0xD0: 
		case 0xD1: 
		case 0xD2:
		case 0xD3: 
		case 0xD4:
		case 0xD5: 
		case 0xD6:
		case 0xD7: 
		case 0xD8:
		case 0xD9: 
		case 0xDA:
		case 0xDB: 
		case 0xDC:
		case 0xDD:  
		case 0xDE:
		case 0xDF: 
			
		case 0xE2:
		case 0xE3:
		case 0xEA:
		case 0xEB:
		case 0xEC:
		case 0xED:
		case 0xEE:
		case 0xEF:
		case 0xF4:
		case 0xF5:
		UI_PerpendicularPark(param[0]);
		break;
	}
	
	switch(param[0])//Park Out Assist
	{
		case 0x0C://Finish_Chime
	    case 0x17://Stop shift to forword
		case 0x18://Pull forward slowly Be prepared to stop
		case 0x19://Stop shift to reverse
		case 0x1A://Stop Back up slowly Be prepared to stop
		case 0x1B://
		case 0x1C://
		case 0x1D://
		case 0x1E://
		case 0x1F://
		case 0xF0://
		case 0xF1://
		UI_ParkOutAssist(param[0]);
		break;
	}
}

void getPublicMultiContouredSeatsMessage(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x00://Upper Lumbar Pressure Percentage
			analyseSeatPressurePercentageUpperLumbar(p[1],p[2]);
			break;
		case 0x05://Middle Lumbar Pressure Percentage
			analyseSeatPressurePercentageMiddleLumbar(p[1],p[2]);
			break;
		case 0x0A://Lower Lumbar Pressure Percentage
			analyseSeatPressurePercentageLowerLumbar(p[1],p[2]);
			break;
		case 0x10://Upper Bolster Pressure Percentage
			analyseSeatPressurePercentageUpperBolster(p[1],p[2]);
			break;
		case 0x15://Lower Bolster Pressure Percentage
			analyseSeatPressurePercentageLowerBolster(p[1],p[2]);
			break;
		case 0x1A://Lumbar Massage Intensity
			analyseSeatIntensityLumbarMassage(p[1],p[2]);
			break;
		case 0x20://Cushion Massage Intensity
			analyseSeatIntensityCushionMassage(p[1],p[2]);
			break;
		default:break;
	}
}

void analyseSeatPressurePercentageUpperLumbar(u8 p1,u8 p2)
{
}

void analyseSeatPressurePercentageMiddleLumbar(u8 p1,u8 p2)
{
}

void analyseSeatPressurePercentageLowerLumbar(u8 p1,u8 p2)
{
}

void analyseSeatPressurePercentageUpperBolster(u8 p1,u8 p2)
{
}

void analyseSeatPressurePercentageLowerBolster(u8 p1,u8 p2)
{
}

void analyseSeatIntensityLumbarMassage(u8 p1,u8 p2)
{
}

void analyseSeatIntensityCushionMassage(u8 p1,u8 p2)
{
}
