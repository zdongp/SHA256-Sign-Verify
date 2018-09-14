#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleParamResponse.h"
#include "controlID.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"
#include "param.h"
#include "timer_interface.h"
#include "halResponseFunction.h"
#include "pageID.h"
#include "appResponseFunction.h"

extern CCarInfoCarSettingToyota gclsCarInforCarSettings;
extern u8 sTrunkInfor;
extern u8 sDoors;
extern u8 sSelfBelts;
extern u8 sHandBreak;

void moduleParameterInit(void){
	LOGD("moduleParameterInit");
//	setDefaultParam();
	
}

void moduleParameterDeInit(void){

}

void moduleParameterReInit(void){
	LOGD("&&&&&&&&&&&&&&&&&&&& Extcar moduleParameterReInit");
	moduleParameterInit();

}

int module_extendInterface(char *buffer, int len){
	LOGD("*************************extcar module_extendInterface:%x,%x", buffer[0], buffer[1]);
	switch(buffer[0]){
		case 0x2C:
			if(buffer[1] == 0x00)//acc off
			{
				if (pLocalParam->m_pCarInfo)
				{
					pLocalParam->bOpenVoiceLater = false;

					sTrunkInfor = 0xFF;
					sDoors = 0xFF;
					sSelfBelts = 0xFF;
					sHandBreak = 0xFF; 

					//pLocalParam->m_pCarInfo->initCarInfo();
					pLocalParam->m_pCarInfo->AccOffinitCarInfo();
				}
				else
				{
					//initCarInfoData();
					AccOffCarInfoData();
					extarToApp_CarInfoInitUI();
				}
			
				saveParameter();
			}
			if(buffer[1] == 0x01)//restart
			{
				LOGD("************************extcar restart");
				if (!pLocalParam->m_pCarInfo)
					extarToApp_CarInfoInitUI();
								
				saveParameter();
			}
			if(buffer[1] == 0x02)//default
			{
				LOGD("************************extcar default");
				if (!pLocalParam->m_pCarInfo)
					extarToApp_CarInfoInitUI();
								
				setDefaultParam();
				saveParameter();
			}
			break;
		case 0x2D://acc on
			if(buffer[1] == 0x00)
			{
				LOGD("***********extcar ACC ON");
				
				process_DegreeOfCarGroundInfo();
				process_InstantSpeedInfo();
				process_OilRemindInfo(pLocalParam->nOilRemind);
				process_DegreeOfWaterInfo();
				process_CleanWaterStatusInfo(pLocalParam->eCleanWaterStatus);
				process_DrivingDistanceInfo();
				process_BatteryVoltageInfo();
				process_EngineSpeedInfo();
				halToExtcar_SustainMileage(pLocalParam->SurplusDistance);
				RunningMileage_Displaying_NewPage(pLocalParam->SurplusDistance);

				process_driverAssistSystemdDriveMode();
				process_driverAssistSystemLastSelectGap();
				process_driverAssistSystemGap();
				process_preAssistSystemActivation();
				process_preAssistSystemWarning();
				process_preAssistSystemGapWarning();
				process_fatigueReconizeSystemActivation();
				process_escSystemActivation();
				process_tireType();
				process_carSpeedWarning();
				process_lightSystemConnect();
				process_lightSystemAuto();
				process_lightSystemDirection();
				process_lightSystemDriveRule();
				process_lightSystemGoHome();
				process_lightSystemLeaveHome();
				process_lightSystemMeter();
				process_lightSystemDoor();
				process_lightSystemFeet();
				process_windowCtrl();
				process_unlockDoor();
				process_autoLockDoor();
				process_backMirror();
				process_autoWiper();
				process_backWiperWhenBackCar();
				process_backCarSystemActivation();
				process_backCarSystemPreAudio();
				process_backCarSystemRearAudio();
				process_functionDisplay();
				process_cozyEconomyTipDisplay();
				process_degreeUnit();
				process_volumeUnit();
				process_oilConsumeUnit();
				process_carola_oilConsumeUnit();
				process_radarAudioDoor();
				process_vim();
				process_carDistanceCheck();
				process_carTimeCheck();
				process_engineOilDistanceCheck();
				process_engineOilTimeCheck();
				process_distanceLeaveCanRun();
				process_avgOilConsumeFromCarRun();
				process_driveDistanceFromCarRun();
				process_driveTimeFromCarRun();
				process_carSpeedFromCarRun();
				process_avgOilConsumeFromLongTimeRun();
				process_driveDistanceFromLongTimeRun();
				process_driveTimeFromLongTimeRun();
				process_carSpeedFromLongTimeRun();
				process_avgOilConsumeFromAddOil();
				process_driveDistanceFromAddOil();
				process_driveTimeFromAddOil();
				process_driveSpeedFromAddOil();
				process_carStyle();
				process_distanceUnit();
				process_speedUnit();
				process_MirrorsInTheFold_HasParking();
				process_car_locker();
				
				//showContinuedDriveMileage();
				//new_Process_DegreeOfCarGroundInfo();

				if(pLocalParam->eOilConsumeUnit == OIL_CONSUME_UNIT_KM_PER_L){
					process_avgOilWearInfo_kmL();
				}
				else{
					process_avgOilWearInfo();
				}
				
				if (pLocalParam->m_pCarInfo)
				{
					pLocalParam->m_pCarInfo->runCarInfo();
				}
				
				initByConfig();
				
				SetTimer(OPEN_VOICE_ALARM_TIME_CUT, 1, EXTCAR_TIMER_ID_OPEN_VOICE_ALARM);
			}
			break;
		case 0xFD:
			{				
				//initTimerCenter(&TimerHandlerCenter);
				//if (!pLocalParam->m_pCarInfo)
				//	extarToApp_CarInfoInitUI();
				exterPradoRadarKeySwitchToSystem(0xff);
				exterPradoRadarUISwitchToSystem(0xff);
				
				initByConfig();

				SetTimer(OPEN_VOICE_ALARM_TIME_CUT, 1, EXTCAR_TIMER_ID_OPEN_VOICE_ALARM);
			}
			break;
		default:break;
	}

		return 0;
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
	case EXTCAR_PARAM_DZ_SCREEN_RECEIVE_CHINESE:
		if(param != NULL){
			*param = pLocalParam->nCanSendChineseToDZCarScreen;
			*paramLen = 4;
		}
		break;
	case EXTCAR_CAR_MODELS:
		*param = (u8)pLocalParam->eCarModels;
		*paramLen = 1;
		break;
	case EXTCAR_CAR_GEARS:
		*param = pLocalParam->eCarGears;
		*paramLen = 1;
		break;
	case EXTCAR_CAR_PARKING_ACTIVETY_STATE:
		*param = (u8)pLocalParam->uParkingModeState;
		*paramLen = 1;
	default:break;
	}
}

void setDefaultParam(void){
	pLocalParam->soundChannel = -1;//���

	/****************************  ������  ************************************/
	/*��������(������)*/
	pLocalParam->speedLock=false;						//���ٸ�Ӧ�����Զ���
	pLocalParam->shiftLock=false;						//�������������Զ���
	pLocalParam->pModeUnlock=false;						//P����������
	pLocalParam->dPressUnlock=false;					//���°�ť���ν���
	pLocalParam->feedbackTone=0;						//Lock/Unlock feedback -tone
	pLocalParam->lightSensitivity=0;					//���Ƶ��ڰ�ť������
	pLocalParam->lampAutoOFFTime=0;						//Headlamps auto �Coff timer
	pLocalParam->isLightRuning=false;					//Daytime running lights

	//̥ѹ
	pLocalParam->rFrontPressure=0;						//��ǰ��
	pLocalParam->rRearPressure=0;						//�Һ���
	pLocalParam->lFrontPressure=0;						//��ǰ��
	pLocalParam->lRearPressure=0;						//�����
	pLocalParam->isWarn=false;							//̥ѹ����

	pLocalParam->avgSpeed=0;							//ƽ����
	pLocalParam->steerTimeH=0;							//��ʻʱ�䣬ʱ
	pLocalParam->steerTimeM=0;							//��ʻʱ�䣬��
	pLocalParam->curOilWear=0;							//��ǰ�ͺ�
	pLocalParam->oilWearCell=0;							//�ͺĸ���

	//��ʷ��¼
	pLocalParam->carHistory.fHistoryCur=0;
	pLocalParam->carHistory.fHistory1=0;
	pLocalParam->carHistory.fHistory2=0;
	pLocalParam->carHistory.fHistory3=0;
	pLocalParam->carHistory.fHistory4=0;
	pLocalParam->carHistory.fHistory5=0;


	pLocalParam->isShowSteerInfo=false;					//�Ƿ���ʾ�г���Ϣ
	pLocalParam->carLock=true;							//���ܳ����һ������

	pLocalParam->AutomaticalAcOrEffectVentilat = 0xC0;
	pLocalParam->bVoicePrompt=true;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	initCarInfoData();
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	pLocalParam->uGearStage=0;

	gclsCarInforCarSettings.initCarSettings_SetDefaultParam();

	pLocalParam->bCurMODE_State = false;
	pLocalParam->uModeKeyValue = 0xFF;
	pLocalParam->bFirstGotoModePage = false;
	pLocalParam->eCar_DrivingMode = CAR_DRIVING_MODE_STANDARD;
	pLocalParam->eCar_DampingSystemMode = CAR_DAMPING_SYSTEM_STANDARD;
	pLocalParam->eCar_SteeringWheelMode = CAR_STEERING_WHEEL_MOD_STANDARD;
	pLocalParam->eCar_DrivingGearMode = CAR_DRIVING_GEAR_MOD_STANDARD;
	pLocalParam->eCar_Dynamic_Headlight_FollowerMode = CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_STANDARD;
	pLocalParam->eCar_AcMode = AC_MODE_STANDARD;
	pLocalParam->eCar_InternalEngineSoundsMode = CAR_ENGINE_SOUNDS_MOD_STANDARD;
	pLocalParam->eCar_ModeResetAction = CAR_MODE_RESET_ACTION_NO;

	pLocalParam->tagBoosterMode = 0xFF;
	pLocalParam->tagLocFeedback = 0xFF;
	pLocalParam->publicEngineSpeed = 0xFFFF;
	pLocalParam->publicDrivingDistance = -1;
	pLocalParam->publicDrivingDistanceUint = 0xFF;
	pLocalParam->publicDegreeOfCarGround = 0xFFFF;
	pLocalParam->CarGroundDecimalNumber = 0xFF;
	pLocalParam->CarGroundUnit = 0xFF;
	pLocalParam->CarGroundPosOrNeg = 0xFF;
	
	pLocalParam->publicnIStantSpeed = 0xFFFF;
	pLocalParam->publicAverageSpeed = 0xFFFF;
	pLocalParam->nGearsValue = 0xFF;
	pLocalParam->ContinuedDriveMileage = 0xFFFF;

	pLocalParam->uSpeedAlarmSwitch = 0xFF;
	pLocalParam->uSpeedAlarmValue = 0xFFFF;
	pLocalParam->uTrunkDegreeValue = 0xFF;
	pLocalParam->uTrunkDegreeMin = 0xFF;
	pLocalParam->uTrunkDegreeMax = 0xFF;
	pLocalParam->uTrunkDegreeStep = 0xFF;
	pLocalParam->uWelcomeLampSwitch = 0xFF;
	pLocalParam->uWelcomeLampOpenTimeMix = 0xFFFF;
	pLocalParam->uWelcomeLampOpenTimeMax = 0xFFFF;
	pLocalParam->uWelcomeLampOpenTimeStep = 0xFFFF;
	pLocalParam->uWelcomeLampOpenTime = 0xFFFF;
	pLocalParam->uCompanyLampHomeSwitch = 0xFF;
	pLocalParam->uLampCompanyHomeTimeMix = 0xFFFF;
	pLocalParam->uLampCompanyHomeTimeMax = 0xFFFF;
	pLocalParam->uLampCompanyHomeTimeStep = 0xFFFF;
	pLocalParam->uCompanyLampHomeTime = 0xFFFF;
	pLocalParam->uVehicle_mode = 0xFF;
	pLocalParam->uDrivingAutomaticLatchSwitch = 0xFF;
	pLocalParam->uDrivingAutomaticLatchSpeed = 0xFFFF;
	pLocalParam->uFlameoutAutomaticLatchSwitch = 0xFF;
	pLocalParam->uKeyLessUnlockDoor = 0xFF; 
	pLocalParam->uKeyUnlockDoor = 0xFF;
	pLocalParam->uAC_automaticModeFlow = 0xFF;
	pLocalParam->uFBdeforstFogLinkSwitch = 0xFF;
	pLocalParam->uMirrorAutomaticOpenSwitch = 0xFF;
	pLocalParam->uBatteryVoltageAnomalyMonitoring = 0xFF;
	pLocalParam->eCarGears = 0xFF;
	pLocalParam->uParkingModeState = 0Xff;
}

void initCarInfoData()
{
	if (pLocalParam->m_pCarInfo != NULL)
	{
		delete pLocalParam->m_pCarInfo;
		pLocalParam->m_pCarInfo = NULL;
	}

	pLocalParam->nDegreeOfCarGround = -10000;
	pLocalParam->nInstantSpeed = -1;
	pLocalParam->nOilRemind = -1;
	pLocalParam->bOilWarning = false;
	pLocalParam->nDegreeOfWater = -1; 
	pLocalParam->eCleanWaterStatus = CLEAN_WATER_UNKNOW;
	pLocalParam->nDrivingDistance = -1;
	pLocalParam->nBatteryVoltage = -1;
	pLocalParam->nEngineSpeed = -1;
	
	pLocalParam->nCarDoorStatus = -1;
	pLocalParam->eSafetyBeltStatus = SATETY_BELT_UNKNOW;
	pLocalParam->eHandLockerStatus = HAND_LOCKER_UNKNOW;
	pLocalParam->nKeyValue = 0x00;
	pLocalParam->nCurCmd = 0x00;
	pLocalParam->bCarSpeedCheckTimerStart = false;
	memset(pLocalParam->pszProcessSpeedCheckFun, 0, sizeof(pLocalParam->pszProcessSpeedCheckFun));
	pLocalParam->pszProcessSpeedCheckFun[0] = process_DoorInfo;
	pLocalParam->pszProcessSpeedCheckFun[1] = process_SafetyBeltInfo;
	pLocalParam->pszProcessSpeedCheckFun[2] = process_HandLockerInfo;
	//pLocalParam->pszProcessSpeedCheckFun[3] = process_OilRemindInfo;
	pLocalParam->pszProcessSpeedCheckFun[3] = new_Process_DoorInfo;

	pLocalParam->bOilAlarmNeedToSend = true;
	pLocalParam->bHandLockAlarmNeedToSend = false;
	pLocalParam->bOpenVoiceLater = false;
	pLocalParam->bOpenVoiceAndNeedAlarm = true;

	pLocalParam->nCarDoorLockStates = -1;
	pLocalParam->uTRCStatus = 0xFF;
	pLocalParam->uSPORTStatus = 0xFF;
	pLocalParam->uCruiseControlStatus = 0;
	pLocalParam->uECOStatus = 0;
	pLocalParam->sTempOfCoolingLiquid=-1000;
	pLocalParam->sWaterOfTheWaterTank=-1;

	
	pLocalParam->SurplusDistance=-1;
	pLocalParam->avgOilWear = -1000;
	pLocalParam->curOilWear=0.0;
	pLocalParam->testCarPage=PAGE_TEST_CARPAGE1;

	pLocalParam->eCarStall = CAR_STALL_UNKNOW;
	pLocalParam->eCarDoorLocker = CAR_DOOR_LOCKER_UNKNOW;
	pLocalParam->nCarWiper= -1;
	pLocalParam->nSteeringWheelAngle = -1000;

	//-->ŽóÖÚ³µÉèÖÃÏà¹Ø
	//pLocalParam->nCanSendChineseToDZCarScreen = 0;//0 ²»·¢ËÍ£¬ 1 ·¢ËÍ
	//<--ŽóÖÚ³µÉèÖÃÏà¹Ø

	//golf add
		pLocalParam->eDriveMode = DRIVE_MODE_UNKNOW;
		pLocalParam->eLastSelectGap = LAST_SELECT_GAP_UNKNOW;
		pLocalParam->eGap = GAP_UNKNOW;
		pLocalParam->ePreAssistSystemActivation = PRE_ASSIST_SYSTEM_ACTIVATION_UNKNOW;
		pLocalParam->ePreAssistSystemWarning = PRE_ASSIST_SYSTEM_WARNING_UNKNOW;
		pLocalParam->ePreAssistSystemGapWarning = PRE_ASSIST_SYSTEM_GAP_WARNING_UNKNOW;
		pLocalParam->eFatigueReconizeSystemActivation = FATIGUE_RECONIZE_SYSTEM_ACTIVATION_UNKNOW;
		pLocalParam->eEscSystemActivation = ESC_SYSTEM_ACTIVATION_UNKNOW;
		pLocalParam->eTireType = TIRE_TYPE_UNKNOW;
		pLocalParam->eCarSpeedWarning = CAR_SPEED_WARNING_UNKNOW;
		pLocalParam->nCarSpeedWarning = -1;
		pLocalParam->eLightSystemConnect = LIGHT_SYSTEM_CONNECT_UNKNOW;
		pLocalParam->eLightSystemAuto = LIGHT_SYSTEM_AUTO_UNKNOW;
		pLocalParam->eLightSystemDirection = LIGHT_SYSTEM_DIRECTION_UNKNOW;
		pLocalParam->eDriveRule = DRIVE_RULE_UNKNOW;
		pLocalParam->nGoHomeModeTime = -1;
		pLocalParam->nLeaveHomeModeTime = -1;
		pLocalParam->nMeterLightBrightness = -1;
		pLocalParam->nDoorLightBrightness = -1;
		pLocalParam->nFeetLightBrightness = -1;
		pLocalParam->eWindowCtrl = WINDOW_CTRL_UNKNOW;
		pLocalParam->eDoorCtrl = DOOR_CTRL_UNKNOW;
		pLocalParam->eDoorAutoLock = DOOR_AUTO_LOCK_UNKNOW;
		pLocalParam->eBackMirrorReverseCar = BACK_MIRROR_REVERSE_CAR_UNKNOW;
		pLocalParam->eBackMirrorSync = BACK_MIRROR_SYNC_UNKNOW;
		pLocalParam->eWiperAuto = WIPER_AUTO_UNKNOW;
		pLocalParam->eBackWinCleanReverseCar = BACK_WIN_CLEAN_REVERSE_CAR_UNKNOW;
		pLocalParam->eReverseCarSystemAutoActivation = REVERSE_CAR_SYSTEM_AUTO_ACTIVATION_UNKNOW;
		pLocalParam->nCarFrontAudioParam = -1;
		pLocalParam->nCarRearAudioParam = -1;
		pLocalParam->eOilConsumeSelect = OIL_CONSUME_SELECT_UNKNOW;
		pLocalParam->eOilAvgConsumeSelect = OIL_AVG_CONSUME_SELECT_UNKNOW;
		pLocalParam->eDriveTimeSelect = DRIVE_TIME_SELECT_UNKNOW;
		pLocalParam->eDriveDistanceSelect = DRIVE_DISTANCE_SELECT_UNKNOW;
		pLocalParam->eAvgSpeedSelect = AVG_SPEED_SELECT_UNKNOW;
		pLocalParam->eDigitSpeedDisplay = DIGIT_SPEED_DISPLAY_UNKNOW;
		pLocalParam->eCarSpeedWarningDisplay = CAR_SPEED_WARNING_DISPLAY_UNKNOW;
		pLocalParam->eCozyDeviceSelect = COZY_DEVICE_SELECT_UNKNOW;
		pLocalParam->eEconomyDriveTip = ECONOMY_DRIVE_TIP_UNKNOW;
		pLocalParam->nRecoveryDriveDataFromAutoRun = -1;
		pLocalParam->nRecoveryDriveDataFromLongTimeRun = -1;
		pLocalParam->eDegreeUnit = DEGREE_UNIT_UNKNOW;
		pLocalParam->eVolumeUnit = VOLUME_UNIT_UNKNOW;
		pLocalParam->eOilConsumeUnit = OIL_CONSUME_UNIT_UNKNOW;
		pLocalParam->eDistanceUnit = DISTANCE_UNIT_UNKNOW;
		pLocalParam->eSpeedUnit = SPEED_UNIT_UNKNOW;
		pLocalParam->eTieCompressUnit = TIE_COMPRESS_UNIT_UNKNOW;
		pLocalParam->nSystemTimeInfo = -1;
		pLocalParam->nSystemDateInfo = -1;
		pLocalParam->nDateFormat = -1;
		pLocalParam->eRecoverySettingType = RECOVERY_SETTING_TYPE_UNKNOW;
		pLocalParam->eRecoverySettingTypeSelected = RECOVERY_SETTING_TYPE_UNKNOW;
		pLocalParam->nLanguage = -1;
		pLocalParam->eRadarAudio = RADAR_AUDIO_UNKNOW;
		memset(pLocalParam->szVim, 0, sizeof(pLocalParam->szVim));
		pLocalParam->nMaintainDistanceInfo = -1;
		pLocalParam->nMaintainTimeInfo = -1;
		pLocalParam->nMaintainEngineOilDistanceInfo = -1;
		pLocalParam->nMaintainEngineOilTimeInfo = -1;
		pLocalParam->nTheDistanceLeaveCarCanRun = -1;
		pLocalParam->nAvgOilConsumeFromCarRun = -1;
		pLocalParam->nDriveDistanceFromCarRun = -1;
		pLocalParam->nDriveTimeFromCarRun = -1;
		pLocalParam->nCarSpeedFromCarRun = -1;
		pLocalParam->nAvgOilConsumeFromLongTimeRun = -1;
		pLocalParam->nDriveDistanceFromLongTimeRun = -1;
		pLocalParam->nDriveTimeFromLongTimeRun = -1;
		pLocalParam->nCarSpeedFromLongTimeRun = -1;
		pLocalParam->nAvgOilConsumeFromAddOil = -1;
		pLocalParam->nDriveDistanceFromAddOil = -1;
		pLocalParam->nDriveTimeFromAddOil = -1;
		pLocalParam->nDriveSpeedFromAddOil = -1;
		pLocalParam->eAirCondition = AIR_CONDITION_UNKNOW;
		pLocalParam->nGolfCarStyle = -1;
		pLocalParam->emMirrorsIntheFoldParkedSelect = MIRRORS_IN_THE_FOLD_HAS_PARKING_UNKNOW;

		pLocalParam->cCarinfoButtonVisible=1;
		//pLocalParam->eDriveDataType = DRIVE_DATA_TYPE_FROM_START; //±»±£Žæ£¬²»ÐèÒª³õÊŒ»¯
		//golf
		pLocalParam->eCarDoorWindow_FL = CAR_DOOR_WINDOW_UNKNOW;
		pLocalParam->eCarDoorWindow_FR = CAR_DOOR_WINDOW_UNKNOW;
		pLocalParam->eCarDoorWindow_RL = CAR_DOOR_WINDOW_UNKNOW;
		pLocalParam->eCarDoorWindow_RR = CAR_DOOR_WINDOW_UNKNOW;
		pLocalParam->eCarDormer = CAR_DORMER_UNKNOW;
		pLocalParam->eHeadLight = HEAD_LIGHT_UNKNOW;
		pLocalParam->eCarModels = CAR_MODELS_UNKNOW;

		process_carGolfModeState();
		UI_Car_Golf_PersonalizationModeResetActionBox(false);
		
		memset(pLocalParam->szDoorStatus, 0xFF, sizeof(pLocalParam->szDoorStatus));
		memset(pLocalParam->szDoorLockStatus,0xFF,sizeof(pLocalParam->szDoorLockStatus));
		pLocalParam->nFrontCover = 0xFF;
		pLocalParam->nSkyLight  = 0xFF;
		pLocalParam->nHighBeam = 0xFF;
		pLocalParam->nDippedHeadlight = 0xFF;
		memset(pLocalParam->szVINCode, 0x00, sizeof(pLocalParam->szVINCode));
		memset(pLocalParam->szVINCode, 0xFF, 17);

}

void AccOffCarInfoData()
{
	if (pLocalParam->m_pCarInfo != NULL)
	{
		delete pLocalParam->m_pCarInfo;
		pLocalParam->m_pCarInfo = NULL;
	}

	sTrunkInfor = 0xFF;
	sDoors = 0xFF;
	sSelfBelts = 0xFF;
	sHandBreak = 0xFF; 

	pLocalParam->bCarSpeedCheckTimerStart = false;
	memset(pLocalParam->pszProcessSpeedCheckFun, 0, sizeof(pLocalParam->pszProcessSpeedCheckFun));
	pLocalParam->pszProcessSpeedCheckFun[0] = process_DoorInfo;
	pLocalParam->pszProcessSpeedCheckFun[1] = process_SafetyBeltInfo;
	pLocalParam->pszProcessSpeedCheckFun[2] = process_HandLockerInfo;
	pLocalParam->pszProcessSpeedCheckFun[3] = new_Process_DoorInfo;

	pLocalParam->bOilAlarmNeedToSend = true;
	pLocalParam->bHandLockAlarmNeedToSend = false;
	pLocalParam->bOpenVoiceLater = false;
	pLocalParam->bOpenVoiceAndNeedAlarm = true;

	pLocalParam->testCarPage=PAGE_TEST_CARPAGE1;

	process_carGolfModeState();
	UI_Car_Golf_PersonalizationModeResetActionBox(false);

}

void initByConfig(void){
	//����˹ INFOͼ������
	//setVisible(FUNCID_SYNC_IMG_INFO,false);
	LOGD("initByConfig pLocalParam->c_carName:%s pLocalParam->AutomaticalAcOrEffectVentilat:%x",pLocalParam->c_carName,pLocalParam->AutomaticalAcOrEffectVentilat);
	if(strcmp(pLocalParam->c_carName,"RAV-4") == 0){

		extcarToApp_SetExtcarMenuEnable();
		extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(pLocalParam->AutomaticalAcOrEffectVentilat);
	}
	else if(strcmp(pLocalParam->c_carName,"CAROLA") == 0)
	{
		extcarToApp_SetExtcarMenuDisable();
		extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(pLocalParam->AutomaticalAcOrEffectVentilat);
		extcarToHal_Init(0x01);
	}
	else
	{
		//�г���Ϣ����ť(��ʼ��Ϊ��)
		extcarToApp_SetExtcarMenuDisable();
		extcarToHal_Init(0x01);
	}
	setCarinfoButtonVisible();
	//������
	//getOtherModuleParam(MODULE_ID_SYSTEM,CARTYPRE_INFO,&m_pTheApp->m_pCenterParam->m_strCarType,NULL);
	//RETAILMSG(true,(TEXT("\r\n\n\n (CJY):ExtCardModule CarType : %s\n"),m_pTheApp->m_pCenterParam->m_strCarType));
	//m_pTheApp->m_pCenterDriver->Set_FoxButtonCommand(0x83);

	gclsCarInforCarSettings.initCarInfo_CarSettingsByConfig();

	//extcarToHal_set_DrivingMode((u8)pLocalParam->eCar_DrivingMode);

	process_DampingSystemMode();
	process_SteeringWheelMode();
	process_DrivingGearMode();
	process_Dynamic_Headlight_FollowerMode();
	process_AcMode();
	process_InternalEngineSoundsMode();

	extcarToHal_set_ModeOpenOrClose(0x00);
	pLocalParam->bCurMODE_State = false;
	pLocalParam->bFirstGotoModePage = false;
	process_carGolfModeState();
	UI_Car_Golf_PersonalizationModeResetActionBox(false);
	initPublicExtcarSetPage(pLocalParam->tagLocFeedback,pLocalParam->tagShutDownUnlock,pLocalParam->tagPositionAfterLock);
}

void recoverLastSet()//�ָ����һ������
{

	/*RAV-4�Զ�ACģʽ����Чͨ��ģʽ*/
	LOGD("recoverLastSet pLocalParam->c_carName:%s",pLocalParam->c_carName);
	if(strcmp(pLocalParam->c_carName,"RAV-4") == 0){
	}
	else
	{
	
		LOGD("%d,%d,%d,%d,%d,%d,%f,%f"
			,pLocalParam->speedLock
			,pLocalParam->shiftLock
			,pLocalParam->pModeUnlock
			,pLocalParam->dPressUnlock
			,pLocalParam->lightSensitivity
			,pLocalParam->carLock
			,pLocalParam->carHistory.fHistoryCur
			,pLocalParam->carHistory.fHistory1);

		//���ٸ�Ӧ�����Զ���
		extcarToHal_SetSpeedLockState(pLocalParam->speedLock);

		//�������������Զ���
		extcarToHal_SetShiftLockState(pLocalParam->shiftLock);

		//P����������
		extcarToHal_SetPModeUnlockState(pLocalParam->pModeUnlock);

		//���°�ť���ν���
		extcarToHal_SetDPressUnlockState(pLocalParam->dPressUnlock);

		//�����Զ�ͷ��������
		extcarToHal_SetLightSensitivity(pLocalParam->lightSensitivity);

		//���ܳ����һ������
		extcarToHal_SetCarLockState(pLocalParam->carLock);

		//��ʷ��¼����ͼ
		setUpdateUI(false);
		setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP1,(int)(pLocalParam->carHistory.fHistory1));
		setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP2,(int)(pLocalParam->carHistory.fHistory2));
		setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP3,(int)(pLocalParam->carHistory.fHistory3));
		setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP4,(int)(pLocalParam->carHistory.fHistory4));
		setAnalogData(CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_TRIP5,(int)(pLocalParam->carHistory.fHistory5));
		setUpdateUI(true);
	}
	
}

void initPublicExtcarSetPage(u8 param1,u8 param2,u8 param3)
{
	setPublicRemoteControlLocFeedback (param1);
	setPublicShutDownTheUnlock (param3);
	setPublicPositionAfterLocking (param3);
}

