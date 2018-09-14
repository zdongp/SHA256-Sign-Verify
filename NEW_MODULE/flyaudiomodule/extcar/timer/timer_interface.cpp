#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <string.h> 
#include <time.h> 

#include "global.h"
#include "appResponseFunction.h"
#include "timer_interface.h"
#include "pageID.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "param.h"
#include "halResponseFunction.h"
#include "moduleParamRequest.h"
#include "halRequestFunction.h"


extern CCarInfoCarSettingToyota gclsCarInforCarSettings;
extern u8 sTrunkInfor;
extern u8 sDoors;
extern u8 sSelfBelts;
extern u8 sHandBreak;

void  select_sleep(int s, int us)
{
	struct timeval timeout;
	timeout.tv_sec = s;
	timeout.tv_usec = us;

	select(0, NULL, NULL, NULL, &timeout);
}

void processCarSpeedCheck(void)
{
	static int nSec = 0;
	static int i = 0;
	static int nProcessTime = 0;
	int nRet = 0;

	LOGD("processCarSpeedCheck nSec = %d", nSec);

	if (NULL == pLocalParam->pszProcessSpeedCheckFun[i])
	{
		nSec = 0, i = 0, nProcessTime = 0;
		DeleteTimer(EXTCAR_TIMER_ID_CAR_SPEED_CHECK);
		return ;
	}
	
	if (nSec == nProcessTime)
	{
		LOGD("[%s] i = [%d]", "exterToCenter_NoticeAlarmTip", i);
		//if((sTrunkInfor == 1) || (sDoors == 1))
		//{
		//	sTrunkInfor = 0xFF;
		//	sDoors = 0xFF;
		//}
		
		nRet = pLocalParam->pszProcessSpeedCheckFun[i++](1);
		nProcessTime += nRet * PLAY_ONE_AUDIO_FILE_NEED_TIME;
		if (nRet == 0)
			nProcessTime += 1;   
	}

	nSec++;
	SetTimer(CAR_SPEED_CHECK_TIME_CUT, 1, EXTCAR_TIMER_ID_CAR_SPEED_CHECK);
	
}

static int mmmm = 0;
int TimerHandlerCenter(timer_t timerId){

	switch((s64)timerId)
	{
	
		case EXTCAR_TIMER_ID_CAR_SPEED_CHECK:
		{
			LOGD("EXTCAR_TIMER_ID_CAR_SPEED_CHECK");
			processCarSpeedCheck();
		}
		break;
		case EXTCAR_TIMER_ID_CAR_SPEED_CHECK_FINISH:
		{
			LOGD("else if (timerId == EXTCAR_TIMER_ID_CAR_SPEED_CHECK_FINISH)");
			pLocalParam->bCarSpeedCheckTimerStart = false;
		}
		break;
		case  EXTCAR_TIMER_ID_TEST:
		{
			static int nSec = 0;
			static int nCarSpeed = 1;
			
			nCarSpeed++;
			nCarSpeed %= 22; 
			
			if(mmmm == 0){
				u8 buf1[] = {0x01,0x40,0x01,21,100};
				u8 buf6[] = {0x03,0,100,10};
				u8 buf7[] = {0x00,0x0c,0x01};
				u8 buf9[] = {0x0f,0x00};
				//analyseHalMessage_EXTCAR(0xB1,buf1,5);
				//analyseHalMessage_EXTCAR(0xB1,buf6,4);
				//analyseHalMessage_EXTCAR(0x81,buf7,3);
				//analyseHalMessage_EXTCAR(0xB0,buf9,2);

				u8 buf10[] = {0x1B,0x01,0x01,0x01,0x01};
				//analyseHalMessage_EXTCAR(0x80,buf10,5);
				//u8 buf11[] = {0x1C,0x01};
				//analyseHalMessage_EXTCAR(0x80,buf11,2);
				u8 buf12[] = {0x1D,0x01};
				//analyseHalMessage_EXTCAR(0x80,buf12,2);
				u8 buf13[] = {0x1E,0x01};
				//analyseHalMessage_EXTCAR(0x80,buf13,2);

				pLocalParam->nOilRemind = 7;
				pLocalParam->nDrivingDistance = 88877;
				pLocalParam->nBatteryVoltage = 2300;
				pLocalParam->nEngineSpeed = 8866;
				pLocalParam->nCarDoorStatus = 1;
				pLocalParam->eSafetyBeltStatus = SATETY_BELT_LOCKED;	// 
				pLocalParam->eHandLockerStatus = HAND_LOCKER_LOCKED;
				pLocalParam->nInstantSpeed = nCarSpeed * 100;
				
				pLocalParam->bOilWarning = 67;
				pLocalParam->nDegreeOfCarGround = 48;
				pLocalParam->nDegreeOfWater = 90;
				pLocalParam->eCleanWaterStatus = CLEAN_WATER_ENOUGH;

				process_DoorInfo(pLocalParam->nCarDoorStatus);
				RunningMileage_Displaying_NewPage(100);
			}
			else if(mmmm == 1){
				u8 buf2[] = {0x01,0x00,0x02,22,200};
				u8 buf6[] = {0x03,0,100,11};
				u8 buf8[] = {0x00,0x0c,0x00};
				u8 buf10[] = {0x0f,0x01};
				//analyseHalMessage_EXTCAR(0xB1,buf2,5);
				//analyseHalMessage_EXTCAR(0xB1,buf6,4);
				//analyseHalMessage_EXTCAR(0x81,buf8,3);
				//analyseHalMessage_EXTCAR(0xB0,buf10,2);

				pLocalParam->nOilRemind = 50;
				pLocalParam->nDrivingDistance = 88888;
				pLocalParam->nBatteryVoltage = 1100;
				pLocalParam->nEngineSpeed = 8877;
				pLocalParam->nCarDoorStatus = 2;
				pLocalParam->eSafetyBeltStatus = SATETY_BELT_UNLOCKED;	// 
				pLocalParam->eHandLockerStatus = HAND_LOCKER_UNLOCKED;
				pLocalParam->nInstantSpeed = nCarSpeed * 100;
				
				pLocalParam->bOilWarning = 30;
				pLocalParam->nDegreeOfCarGround = 1;
				pLocalParam->nDegreeOfWater = 20;
				pLocalParam->eCleanWaterStatus = CLEAN_WATER_ENOUGH;

				process_HandLockerInfo(pLocalParam->eHandLockerStatus);
				RunningMileage_Displaying_NewPage(200);
				
			}
			else if(mmmm == 2){
				//u8 buf3[] = {0x01,0x40,0x10,25,300};
				u8 buf6[] = {0x03,1,100,12};
				u8 buf7[] = {0x00,0x0c,0x01};
				u8 buf9[] = {0x0f,0x00};
				//analyseHalMessage_EXTCAR(0xB1,buf3,5);
				//analyseHalMessage_EXTCAR(0xB1,buf6,4);
				//analyseHalMessage_EXTCAR(0x81,buf7,3);
				//analyseHalMessage_EXTCAR(0xB0,buf9,2);
				u8 buf10[] = {0x1B,0x00,0x00,0x00,0x00};
				//analyseHalMessage_EXTCAR(0x80,buf10,5);
				u8 buf11[] = {0x1C,0x00};
				//analyseHalMessage_EXTCAR(0x80,buf11,2);
				u8 buf12[] = {0x1D,0x00};
				//analyseHalMessage_EXTCAR(0x80,buf12,2);
				u8 buf13[] = {0x1E,0x00};
				//analyseHalMessage_EXTCAR(0x80,buf13,2);

				pLocalParam->nOilRemind = 58;
				pLocalParam->nDrivingDistance = 30000;
				pLocalParam->nBatteryVoltage = 1100;
				pLocalParam->nEngineSpeed = 8877;
				pLocalParam->nCarDoorStatus = 4;
				pLocalParam->eSafetyBeltStatus = SATETY_BELT_LOCKED;	// 
				pLocalParam->eHandLockerStatus = HAND_LOCKER_LOCKED;
				pLocalParam->nInstantSpeed = nCarSpeed * 100;
				
				pLocalParam->bOilWarning = 47;
				pLocalParam->nDegreeOfCarGround = -10;
				pLocalParam->nDegreeOfWater = 69;
				pLocalParam->eCleanWaterStatus = CLEAN_WATER_EMPTY;
			process_HandLockerInfo(pLocalParam->eHandLockerStatus);
			
		
			}
			else if(mmmm == 3){
				//u8 buf4[] = {0x01,0x00,0x09,30,400};
				u8 buf6[] = {0x03,1,100,13};
				u8 buf8[] = {0x00,0x0c,0x00};
				u8 buf10[] = {0x0f,0x01};
				//analyseHalMessage_EXTCAR(0xB1,buf4,5);
				//analyseHalMessage_EXTCAR(0xB1,buf6,4);
				//analyseHalMessage_EXTCAR(0x81,buf8,3);
				//analyseHalMessage_EXTCAR(0xB0,buf10,2);

				pLocalParam->nOilRemind = 20;
				pLocalParam->nDrivingDistance = 88888;
				pLocalParam->nBatteryVoltage = 1100;
				pLocalParam->nEngineSpeed = 8877;
				pLocalParam->nCarDoorStatus = 8;
				pLocalParam->eSafetyBeltStatus = SATETY_BELT_LOCKED;	// 
				pLocalParam->eHandLockerStatus = HAND_LOCKER_LOCKED;
				pLocalParam->nInstantSpeed = nCarSpeed * 100;
				
				pLocalParam->bOilWarning = 27;
				pLocalParam->nDegreeOfCarGround = 125;
				pLocalParam->nDegreeOfWater = 90;
				pLocalParam->eCleanWaterStatus = CLEAN_WATER_ENOUGH;

				
				process_SafetyBeltInfo(pLocalParam->eSafetyBeltStatus);
			}
			else if(mmmm == 4){
				//u8 buf5[] = {0x01,0x40,0x10,33,500};
				u8 buf6[] = {0x03,0,100,14};
				u8 buf7[] = {0x00,0x0c,0x01};
				u8 buf9[] = {0x0f,0x00};
				//analyseHalMessage_EXTCAR(0xB1,buf5,5);
				//analyseHalMessage_EXTCAR(0xB1,buf6,4);
				//analyseHalMessage_EXTCAR(0x81,buf7,3);
				//analyseHalMessage_EXTCAR(0xB0,buf9,2);
				
				pLocalParam->nOilRemind = 19;
				pLocalParam->nDrivingDistance = 4444;
				pLocalParam->nBatteryVoltage = 7000;
				pLocalParam->nEngineSpeed = 8877;
				pLocalParam->nCarDoorStatus = 32;
				pLocalParam->eSafetyBeltStatus = SATETY_BELT_UNLOCKED;	// 
				pLocalParam->eHandLockerStatus = HAND_LOCKER_LOCKED;
				pLocalParam->nInstantSpeed = nCarSpeed * 100;
				
				pLocalParam->bOilWarning = 1;
				pLocalParam->nDegreeOfCarGround = 40;
				pLocalParam->nDegreeOfWater = 80;
				pLocalParam->eCleanWaterStatus = CLEAN_WATER_EMPTY;
		
				process_SafetyBeltInfo(pLocalParam->eSafetyBeltStatus);
			}
			else if(mmmm == 5){
				//u8 buf5[] = {0x01,0x40,0x10,33,500};
				u8 buf6[] = {0x03,0,100,14};
				u8 buf7[] = {0x00,0x0c,0x01};
				u8 buf9[] = {0x0f,0x00};
				//analyseHalMessage_EXTCAR(0xB1,buf5,5);
				//analyseHalMessage_EXTCAR(0xB1,buf6,4);
				//analyseHalMessage_EXTCAR(0x81,buf7,3);
				//analyseHalMessage_EXTCAR(0xB0,buf9,2);
				
				pLocalParam->nOilRemind = 19;
				pLocalParam->nDrivingDistance = 4444;
				pLocalParam->nBatteryVoltage = 7000;
				pLocalParam->nEngineSpeed = 8877;
				pLocalParam->nCarDoorStatus = 2;
				pLocalParam->eSafetyBeltStatus = SATETY_BELT_UNLOCKED;	// 
				pLocalParam->eHandLockerStatus = HAND_LOCKER_LOCKED;
				pLocalParam->nInstantSpeed = nCarSpeed * 100;
				
				pLocalParam->bOilWarning = 1;
				pLocalParam->nDegreeOfCarGround = 40;
				pLocalParam->nDegreeOfWater = 80;
				pLocalParam->eCleanWaterStatus = CLEAN_WATER_EMPTY;

				process_DoorInfo(pLocalParam->nCarDoorStatus);
			}
			else if(mmmm == 6){
				pLocalParam->nCarDoorStatus = 4;
				process_DoorInfo(pLocalParam->nCarDoorStatus);
			}
			else if(mmmm == 7){
				pLocalParam->nCarDoorStatus = 8;
				pLocalParam->avgOilWear = 50;
				process_DoorInfo(pLocalParam->nCarDoorStatus);
			}
			else if(mmmm == 8){
				pLocalParam->nCarDoorStatus = 32;
				pLocalParam->avgOilWear = 60;
				process_DoorInfo(pLocalParam->nCarDoorStatus);
			}
			else if(mmmm == 9){
				pLocalParam->nCarDoorStatus = 0;
				process_DoorInfo(pLocalParam->nCarDoorStatus);
			}

			//process_HandLockerInfo(pLocalParam->eHandLockerStatus);
			//process_SafetyBeltInfo(pLocalParam->eSafetyBeltStatus);
			//process_DoorInfo(pLocalParam->nCarDoorStatus);

			process_OilRemindInfo(pLocalParam->nOilRemind);
			process_DrivingDistanceInfo();
			process_EngineSpeedInfo();
			process_InstantSpeedInfo();
			process_DegreeOfWaterInfo();
			process_BatteryVoltageInfo();
			process_DegreeOfCarGroundInfo();
			new_process_avgOilWearInfo();
			
			if(mmmm == 9){
				mmmm = 0;
			}
			else{
				mmmm++;
			}

			
		}
		break;
		case EXTCAR_TIMER_ID_AUTO_JUMP_TO_EXTCAR_PAGE_PROCESS:
		{
			LOGD("else if (timerId == EXTCAR_TIMER_ID_AUTO_JUMP_TO_EXTCAR_PAGE_PROCESS)");
			u16 nCurPageID = 0;
			u8 nCurPageLen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&nCurPageID, (u8*)&nCurPageLen);
			if (PAGE_TRAVEL_INFORMATION == nCurPageID)
			{
				extcarToModule_NotifySystem_jumpPrePage();
				LOGD("extcarToModule_NotifySystem_jumpPrePage()");
			}
		}
		break;
		case EXTCAR_TIMER_ID_PLAY_BACK_DOOR_AUDIO:
		{
			needToAlarm(CARINFO_ALARM_SOUND_BACK_DOOR_OPEN);
			needToAlarm(CARINFO_ALARM_SOUND_TRUNK_OPEN);
		}
		break;
		case EXTCAR_TIMER_ID_OPEN_VOICE_ALARM:
		{
			pLocalParam->bOpenVoiceLater = true;
			
			if (pLocalParam->m_pCarInfo)
			{
				pLocalParam->m_pCarInfo->m_bVoiceAlarmEnable = true;
				pLocalParam->m_pCarInfo->updateCarSpeed();
			}
			else
			{
				process_InstantSpeedInfo();
				new_Process_InstantSpeedInfo();
			}
		}
		break;
		case EXTCAR_TIMER_ID_TOYOTA_PRADO_AVERAGE_OIL_CONSUME_UPDATE:
		{
			if (pLocalParam->m_pCarInfo)
			{
				pLocalParam->m_pCarInfo->updateAverageOilConsumeHistoryPerMinute();
				SetTimer(EXTCAR_TIMER_TIME_TOYOTA_PRADO_AVERAGE_OIL_CONSUME_UPDATE, 1, EXTCAR_TIMER_ID_TOYOTA_PRADO_AVERAGE_OIL_CONSUME_UPDATE);
			}
		}
		break;
		case EXTCAR_TIMER_ID_TOYOTA_PRADO_INSTANT_OIL_CONSUME_COUNT:
		{
			if (pLocalParam->m_pCarInfo)
			{
				pLocalParam->m_pCarInfo->updateInstantOilConsumeCount();
				SetTimer(EXTCAR_TIMER_TIME_TOYOTA_PRADO_INSTANT_OIL_CONSUME_COUNT, 1, EXTCAR_TIMER_ID_TOYOTA_PRADO_INSTANT_OIL_CONSUME_COUNT);
			}
		}
		break;
		case EXTCAR_TIMER_ID_TOYOTA_CAMRY_SAVECARSETTINGPARAM_SHOWBOMBBOX:
		{
			gclsCarInforCarSettings.saveCarSettings_BombBox(false);
		}
		break;
		case EXTCAR_TIMER_ID_GOLF_MODE_HIDEBOX:
		{
			process_carIsOutModePage();
		}
		break;
		case EXTCAR_TIMER_ID_CORNERING_LAMP_TK:
		{
			gclsCarInforCarSettings.Cornering_Lamp_TK();
		}
		break;
		case EXTCAR_TIMER_ID_DANGER_WARNING_LAMP_TK:
		{
			gclsCarInforCarSettings.DangerWarning_Lamp_TK();
		}
		break;
		default:
		break;

	}
	
	return 0;
}

void  initTimerCenter(timer_handler_function func){
	
	u8 buf[] = {0x10,0x00,0x00,0x00,0x00};
    
    buf[1] = ((u64)func >> 24) & 0xFF;
    buf[2] = ((u64)func >> 16) & 0xFF;
    buf[3] = ((u64)func >> 8) & 0xFF;
    buf[4] = (u64)func & 0xFF;

    
    makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_TIMER,buf,5);
	LOGD("-----------initTimerCenter Success-----------");
	
}

int SetTimer(int nElaspe_ms, int nMode, int timerId){
	u8 buf[10];

	buf[0] = 0x20;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    buf[5] = (nElaspe_ms >> 24) & 0xFF;
    buf[6] = (nElaspe_ms >> 16) & 0xFF;
    buf[7] = (nElaspe_ms >> 8) & 0xFF;
    buf[8] = nElaspe_ms & 0xFF;

	buf[9] = (u8)nMode;
    
    makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_TIMER,buf,10);
	
    return 0;
}

int DeleteTimer(int timerId){
	
	u8 buf[5];
	
	buf[0] = 0x30;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_TIMER,buf,5);
	LOGD("DeleteTimer Success!");
    return 0;
}
