#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "halRequestFunction.h"
#include "otherModuleRequestFunction.h"
#include "stringID.h"

extern "C"{
#include "unicodestring.h"
};

void extcarToApp_SetUp_HistoryUpdate()
{
	pLocalParam->carHistory.fHistory5 = pLocalParam->carHistory.fHistory4;
	pLocalParam->carHistory.fHistory4 = pLocalParam->carHistory.fHistory3;
	pLocalParam->carHistory.fHistory3 = pLocalParam->carHistory.fHistory2;
	pLocalParam->carHistory.fHistory2 = pLocalParam->carHistory.fHistory1;
	pLocalParam->carHistory.fHistory1 = pLocalParam->carHistory.fHistoryCur;
	setUpdateUI(false);
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP1,(int)(pLocalParam->carHistory.fHistory1));
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP2,(int)(pLocalParam->carHistory.fHistory2));
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP3,(int)(pLocalParam->carHistory.fHistory3));
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP4,(int)(pLocalParam->carHistory.fHistory4));
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP5,(int)(pLocalParam->carHistory.fHistory5));
	setUpdateUI(true);
}

void extcarToApp_SetUp_HistoryClear()
{

	pLocalParam->carHistory.fHistory5 = 0;
	pLocalParam->carHistory.fHistory4 = 0;
	pLocalParam->carHistory.fHistory3 = 0;
	pLocalParam->carHistory.fHistory2 = 0;
	pLocalParam->carHistory.fHistory1 = 0;
	setUpdateUI(false);
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_HISTORICAL_RECORD,(int)(pLocalParam->carHistory.fHistoryCur));
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP1,(int)(pLocalParam->carHistory.fHistory1));
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP2,(int)(pLocalParam->carHistory.fHistory2));
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP3,(int)(pLocalParam->carHistory.fHistory3));
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP4,(int)(pLocalParam->carHistory.fHistory4));
	setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP5,(int)(pLocalParam->carHistory.fHistory5));
	setUpdateUI(true);
}

void extcarToApp_SetExtcarMenuEnable()
{
	setAnalogData(CONTROLID_MENU_DRIVING_INFORMATION,0);
	setControllable(CONTROLID_MENU_DRIVING_INFORMATION,true);
}

void extcarToApp_SetExtcarMenuDisable()
{
	setAnalogData(CONTROLID_MENU_DRIVING_INFORMATION,2);
	setControllable(CONTROLID_MENU_DRIVING_INFORMATION,false);
	
}

void extcarToApp_SetSerialData_Ansi2Unicode(int controlId, u8 *pBuf, int nLen)
{
	int nSendLen = nLen * 2;
	u8 *pwBuf = (u8*)malloc(nSendLen + 2);
	memset(pwBuf, 0, nSendLen + 2);
	ansi_str_to_unicode16(pBuf, (unsigned short *)pwBuf);
	setSerialData(controlId, pwBuf, nSendLen);
	free(pwBuf);
}

void extcarToApp_SetUp_LightSensitivity_INC()
{
	int LightSensitivity=pLocalParam->lightSensitivity;
	if (LightSensitivity == 1)
	{
		LightSensitivity=32;
		pLocalParam->lightSensitivity = 2;
	}
	else if (LightSensitivity == 2)
	{
		LightSensitivity=0;
		pLocalParam->lightSensitivity = 3;
	}
	else if (LightSensitivity == 3)
	{
		LightSensitivity=48;
		pLocalParam->lightSensitivity = 4;
	}
	else if (LightSensitivity == 4)
	{
		LightSensitivity=64;
		pLocalParam->lightSensitivity = 5;
	}
	else if (LightSensitivity == 5)
	{
		LightSensitivity=16;
		pLocalParam->lightSensitivity = 1;
	}
	else
	{
		LightSensitivity=0;
		pLocalParam->lightSensitivity = 3;
	}

	u8 *pwBuf = (u8*)malloc(STRING_BUF_MAX_LEN);
	memset(pwBuf, 0, STRING_BUF_MAX_LEN);
	sprintf((char*)pwBuf, "%d",pLocalParam->lightSensitivity);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_INFORMATION_CAR_SET_LIGHT_SENSITIVITY_TEXT,pwBuf,(int)strlen((char *)pwBuf));
	free(pwBuf);

	extcarToHal_SetLightSensitivity(LightSensitivity);
}

void extcarToApp_SetUp_LightSensitivity_DEC()
{
	int LightSensitivity=pLocalParam->lightSensitivity;
	if (LightSensitivity == 1)
	{
		LightSensitivity=64;
		pLocalParam->lightSensitivity = 5;
	}
	else if (LightSensitivity == 2)
	{
		LightSensitivity=16;
		pLocalParam->lightSensitivity = 1;
	}
	else if (LightSensitivity == 3)
	{
		LightSensitivity=32;
		pLocalParam->lightSensitivity = 2;
	}
	else if (LightSensitivity == 4)
	{
		LightSensitivity=0;
		pLocalParam->lightSensitivity = 3;
	}
	else if (LightSensitivity == 5)
	{
		LightSensitivity=48;
		pLocalParam->lightSensitivity = 4;
	}
	else
	{
		LightSensitivity=0;
		pLocalParam->lightSensitivity = 3;
	}

	u8 *pwBuf = (u8*)malloc(STRING_BUF_MAX_LEN);
	memset(pwBuf, 0, STRING_BUF_MAX_LEN);
	sprintf((char*)pwBuf, "%d",pLocalParam->lightSensitivity);
	extcarToApp_SetSerialData_Ansi2Unicode(CONTROLIDTRAVEL_INFORMATION_CAR_SET_LIGHT_SENSITIVITY_TEXT,pwBuf,(int)strlen((char *)pwBuf));
	free(pwBuf);

	extcarToHal_SetLightSensitivity(LightSensitivity);
}


void extarToApp_CarInfoInitUI(void)
{
	LOGD("extarToApp_DaZhongCarInitUI");
	u8 ansiBuf[10];
	memset(ansiBuf, 0, sizeof(ansiBuf));
	sprintf((char*)ansiBuf,"%s", "N/A");
	int len = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SEAT_BELTS_TXT, ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_REMAINING_TXT, ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TEMPERATURE_TXT, ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_VOLTAGE_TXT, ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_BRAKE_TXT, ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_SPEED_TXT, ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_PER_HOUR_TXT, ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_MILEAGE_TXT, ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_RUNNING_MILEAGE_TEXT, ansiBuf, len);/* ����ʹ����ı�*/
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_COOLANT_TEMPERATURE_TEXT, ansiBuf, len);/* ��ȴҺ�ı�*/       
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_AVERAGE_FUEL_CONSUMPTION_TEXT, ansiBuf, len);/* ƽ���ͺ��ı�*/
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRVEL_TIME_TEXT, ansiBuf, len);/*��ʻʱ�� �ı�*/
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_FUEL_CONSUMPTION_TEXT, ansiBuf, len);/* ��ǰ�ͺ��ı�*/
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATER_TEXT, ansiBuf, len);/*   ˮ��ˮ���ı� */ 
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_AVERAGE_SPEED_TEXT, ansiBuf, len);/*  ƽ���ٶ��ı� */
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE_TEXT,ansiBuf, len);  /*��λ��Ϣ�ı�*/
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK_TXT,ansiBuf, len); /*�����ı�*/
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_WATRE_TXT,ansiBuf, len);
	setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_GEARSTAGE,0);
	setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_TRUNK,0);
	setAnalogData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LOCKER_IMAG,1);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_LOCKER_TXT,ansiBuf, len);
	LOGD("[DYB %s] nCanSendChineseToDZCarScreen = [%d]",__FUNCTION__,pLocalParam->nCanSendChineseToDZCarScreen);
	setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_SMALL_SCREEN, pLocalParam->nCanSendChineseToDZCarScreen);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_FOOT_BRAKE_text, ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_DRIVING_INFO_MILEAGE,  ansiBuf, len);
	setAnsiSerialData(PAGE_SETUP_PARK_ASSIST_SET_ALERT_VOLUME_TEXT,  ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_PUBLIC_INSTANT_SPEED_TEXT, ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_PUBLIC_AVERAGE_SPEED_TEXT, ansiBuf, len);
	setAnsiSerialData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_MILEAGE_NEW_TXT, ansiBuf, len);
	setAnsiSerialData(CONTROLID_CARINFOR_OIL_CONSUMPTION_ALARM_TXT, ansiBuf, len);
	extcarToApp_golfInitUI();
}

void extcarToApp_InitData()
{
	g_clsExtcar.sendToFlyJniSdk_SafetyBelt(2);
	g_clsExtcar.sendToFlyJniSdk_OilRemind(-1);
	g_clsExtcar.sendToFlyJniSdk_DegreeOfCarGround(DEFAULT_OUTDOOR_DEGREE);
	g_clsExtcar.sendToFlyJniSdk_BatteryVoltageInfo(-1);
	g_clsExtcar.sendToFlyJniSdk_HandLocker(2);
	g_clsExtcar.sendToFlyJniSdk_EngineSpeed(-1);
	g_clsExtcar.sendToFlyJniSdk_InstantSpeed(-1);
	g_clsExtcar.sendToFlyJniSdk_DrivingDistance(-1);
	g_clsExtcar.sendToFlyJniSdk_MileageCanRun(-1);
	g_clsExtcar.sendToFlyJniSdk_DegreeOfWater(-1);
	g_clsExtcar.sendToFlyJniSdk_AvgOilWearInfo(0,0xFF);
	g_clsExtcar.sendToFlyJniSdk_GearState(7);
	g_clsExtcar.sendToFlyJniSdk_CleanWaterStatus(2);
	g_clsExtcar.sendToFlyJniSdk_CarLocker(CAR_DOOR_LOCKER_UNKNOW);
	g_clsExtcar.sendToFlyJniSdk_FootLockState(2);
}

void extcarToApp_golfInitUI()
{
       /*golf 7*/
       //<BC><DD>ʻԱ<B8><A8><D6><FA>ϵ<U+0373>^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TRAVEL_PROGRAM_TXT, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_DISTANCE_TXT, STRING_CARINFO_DATA_UNKNOW);
       //ǰ<B2><BF><B8><A8><D6><FA>ϵ<U+0373>^M
       //ƣ<C0>ͼ<DD>ʻʶ<B1><F0>ϵ<U+0373>^M
       //ESCϵ<U+0373>^M
       //<C2><D6>̥^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_UNITS_TXT, STRING_CARINFO_DATA_UNKNOW);
       //<B5>ƹ<E2>^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TURN_ON_TIME_TXT, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TRAVEL_MODE_TXT, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_RETURN_HOME_MODE_TXT, STRING_CARINFO_DATA_UNKNOW);
      setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_HOME_MODE_TXT, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_METER_TXT, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_CAR_ENVIRONMENT_TXT, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_FOOT_SPACE_TXT, STRING_CARINFO_DATA_UNKNOW);
       //<B3><B5><B4><B0>^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_OPEN_WINDOW_CONVENIENT_TXT, STRING_CARINFO_DATA_UNKNOW);
       //<B3><B5><C3><C5><CB><F8>^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_CENTRAL_TXT, STRING_CARINFO_DATA_UNKNOW);
       //<BA><F3><CA>Ӿ<B5>^M
       //<D3><EA><B9><CE>^M
       //פ<B3><B5><BA>͵<F7><B3><B5>--<B5><B9><B3><B5><C0>״<EF>ϵ<U+0373>^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_FRONT_VOLUME_TXT, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_FRONT_PITCH_TXT, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_REAR_VOLUME_TXT, STRING_CARINFO_DATA_UNKNOW);
      setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_REAR_PITCH_TXT, STRING_CARINFO_DATA_UNKNOW);
       //<B6><U+0E66><C4><DC><CF><D4>ʾ^M
       //<BB>ָ<B4><CA><FD><BE><DD>^M
       //<B5><A5>λ<C9><E8><D6><C3>^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_TEMPERATURE_TXT, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_VOLUME_TXT, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_FUEL_CONSUM_PTION_TXT, STRING_CARINFO_DATA_UNKNOW);
       //ʱ<BC><E4>^M
       //<B8><B4>λ<B3><F6><B3><A7><C9><E8><D6><C3>^M
       //<D3><EF><D1><D4>^M
       //<C0>״<EF><C9><F9><D2><U+13FAB9><D8>^M
       //vim code^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CAR_NUMBER, STRING_CARINFO_DATA_UNKNOW);
       //<B3><B5><BF><F6><BC><EC><B2><E9>^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CHECK_NUMBER_DAYS, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_CHECK_MILEAGE, STRING_CARINFO_DATA_UNKNOW);
       //<B8><FC><BB><BB><BB><FA><D3><CD>^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_BACK_REPLACE_SERVICE, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_BACK_REPLACE_MILEAGE, STRING_CARINFO_DATA_UNKNOW);
       //<D0>г<B5><D0><C5>Ϣ^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_CONTINUED_MILEAGE, STRING_CARINFO_DATA_UNKNOW);
       //<B8><A8><D6><FA><BA><AF><CA><FD>^M
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_SWITCHING, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_FUEL_CONSUMPTION, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_MILEAGE, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_TRAVEL_TIME, STRING_CARINFO_DATA_UNKNOW);
       setStringText(CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_AVERAGE_SPEED, STRING_CARINFO_DATA_UNKNOW);
       /*golf 7*/
}

void extcarToApp_golfCarStyleSetting(u8 p)
{
	return ;
	if (p == 0)//0->žßÅä
	{
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_SETUP, !p);
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_DRIVING_DATA, !p);
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLF_MAINTAIN, !p);
	}
	else if (p == 1)
	{
		if(pLocalParam->cCarinfoButtonVisible==0){
			setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_CARINFORVOICEPRT, 0x00);
			setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_SMALL_SCREEN, 0x00);
			return;
		}
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_CARINFORVOICEPRT, p);
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_SMALL_SCREEN, p);
	}
}


void extcarToApp_about_CarInforVoicePrompt()
{
	LOGD("pLocalParam->bVoicePrompt:%d",pLocalParam->bVoicePrompt);

	if (pLocalParam->bVoicePrompt)
	{
		pLocalParam->bVoicePrompt = false;
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_CARINFORVOICEPRT,0);
	}
	else
	{
		pLocalParam->bVoicePrompt = true;
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_CARINFORVOICEPRT,1);
	}
	extcarToSystem_about_CarInforVoicePrompt(!pLocalParam->bVoicePrompt);
}

void setCarinfoButtonVisible(void)
{
	if(pLocalParam->cCarinfoButtonVisible==0)
	{
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_CARINFORVOICEPRT, 0x00);
		setVisible(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_SMALL_SCREEN, 0x00);

	}
}

void ExtcarToAPP_TCU_ActiveRequest(u8 p)
{
	extcarToApp_OpenBombBox_TCU(p);
}



