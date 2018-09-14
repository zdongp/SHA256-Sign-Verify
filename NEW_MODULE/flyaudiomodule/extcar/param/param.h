#ifndef __PARAM_H__
#define __PARAM_H__

#include "CarInfo.h"
#include "CarInfoToyotaPrado.h"
#include "CarSettingToyota.h"
#include "CNotifyAndResponseFlyJniSdk.h"

#define TOYOTA "TOYOTA"

#define CAR_TYPE_MAX_LEN		    16
#define SIZE_MAP_ENUM	16

//��ʷ��¼�ṹ��
typedef struct 
{
	float fHistoryCur;	//��ǰ
	float fHistory1;	//�г�1	
	float fHistory2;	//�г�2
	float fHistory3;	//�г�3
	float fHistory4;	//�г�4
	float fHistory5;	//�г�5
}STRUCT_HISTORY;

enum E_CAR_DRIVING_MODE{CAR_DRIVING_MODE_COMFORT = 1,CAR_DRIVING_MODE_STANDARD,CAR_DRIVING_MODE_SPORT,CAR_DRIVING_MODE_LOW_OIL = 5,CAR_DRIVING_MODE_PERSONALIZATION = 7,CAR_DRIVING_MODE_UNKNOW};
enum E_CAR_DAMPING_SYSTEM_MOD{CAR_DAMPING_SYSTEM_COMFORT = 1,CAR_DAMPING_SYSTEM_STANDARD,CAR_DAMPING_SYSTEM_SPORT,CAR_DAMPING_SYSTEM_UNKNOW};
enum E_CAR_STEERING_WHEEL_MOD{CAR_STEERING_WHEEL_MOD_STANDARD = 2,CAR_STEERING_WHEEL_MOD_SPORT = 3,CAR_STEERING_WHEEL_MOD_UNKNOW};
enum E_CAR_DRIVING_GEAR_MOD{CAR_DRIVING_GEAR_MOD_STANDARD = 2,CAR_DRIVING_GEAR_MOD_SPORT = 3,CAR_DRIVING_GEAR_MOD_LOW_OIL = 5,CAR_DRIVING_GEAR_MOD_UNKNOW};
enum E_CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD{CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_STANDARD = 2,CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_SPORT = 3,CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_LOW_OIL = 5,CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD_UNKNOW};
enum E_CAR_AC_MOD{AC_MODE_STANDARD = 2,AC_MODE_LOW_OIL = 5,AC_MODE_UNKNOW};
enum E_CAR_INTERNAL_ENGINE_SOUNDS_MOD{CAR_ENGINE_SOUNDS_MOD_STANDARD = 2,CAR_ENGINE_SOUNDS_MOD_SPORT = 3,CAR_ENGINE_SOUNDS_MOD_LOW_OIL = 5,CAR_ENGINE_SOUNDS_MOD_UNKNOW};
enum E_CAR_MODE_RESET_ACTION{CAR_MODE_RESET_ACTION_NO,CAR_MODE_RESET_ACTION_YES,CAR_MODE_RESET_ACTION_UNKNOW};





enum ENUM_SatetyBeltStatus{SATETY_BELT_LOCKED, SATETY_BELT_UNLOCKED, SATETY_BELT_UNKNOW};
enum ENUM_HandLockerStatus{HAND_LOCKER_LOCKED, HAND_LOCKER_UNLOCKED, HAND_LOCKER_UNKNOW};
enum ENUM_CleanWaterStatus{CLEAN_WATER_ENOUGH, CLEAN_WATER_EMPTY, CLEAN_WATER_UNKNOW};
enum E_CAR_STALL{CAR_STALL_P, CAR_STALL_B, CAR_STALL_N, CAR_STALL_D, CAR_STALL_S, CAR_STALL_S2,CAR_STALL_S1,CAR_STALL_UNKNOW, CAR_STALL_NOT_P};
enum E_CAR_DOOR_LOCKER{CAR_DOOR_LOCKER_LOCK, CAR_DOOR_LOCKER_UNLOCK, CAR_DOOR_LOCKER_UNKNOW};
enum E_DRIVE_MODE{DRIVE_MODE_STANDAR = 1, DRIVE_MODE_SPORT, DRIVE_MODE_ECONOMY, DRIVE_MODE_UNKNOW};
enum E_LAST_SELECT_GAP{LAST_SELECT_GAP_NO, LAST_SELECT_GAP_YES, LAST_SELECT_GAP_UNKNOW};
enum E_GAP{GAP_VERY_SMALL, GAP_SMALL, GAP_MID, GAP_BIG, GAP_VERY_BIG, GAP_UNKNOW};
enum E_PRE_ASSIST_SYSTEM_ACTIVATION{PRE_ASSIST_SYSTEM_ACTIVATION_NO, PRE_ASSIST_SYSTEM_ACTIVATION_YES, PRE_ASSIST_SYSTEM_ACTIVATION_UNKNOW};
enum E_PRE_ASSIST_SYSTEM_WARNING{PRE_ASSIST_SYSTEM_WARNING_NO, PRE_ASSIST_SYSTEM_WARNING_YES, PRE_ASSIST_SYSTEM_WARNING_UNKNOW};
enum E_PRE_ASSIST_SYSTEM_GAP_WARNING{PRE_ASSIST_SYSTEM_GAP_WARNING_NO, PRE_ASSIST_SYSTEM_GAP_WARNING_YES, PRE_ASSIST_SYSTEM_GAP_WARNING_UNKNOW};
enum E_FATIGUE_RECONIZE_SYSTEM_ACTIVATION{FATIGUE_RECONIZE_SYSTEM_ACTIVATION_NO, FATIGUE_RECONIZE_SYSTEM_ACTIVATION_YES = 0x10, FATIGUE_RECONIZE_SYSTEM_ACTIVATION_UNKNOW};
enum E_ESC_SYSTEM_ACTIVATION{ESC_SYSTEM_ACTIVATION_NO = 2, ESC_SYSTEM_ACTIVATION_YES, ESC_SYSTEM_ACTIVATION_UNKNOW};
enum E_TIRE_TYPE{TIRE_TYPE_WINTER, TIRE_TYPE_UNKNOW};
enum E_CAR_SPEED_WARNING{CAR_SPEED_WARNING_NO, CAR_SPEED_WARNING_YES, CAR_SPEED_WARNING_UNKNOW};
enum E_LIGHT_SYSTEM_CONNECT{LIGHT_SYSTEM_CONNECT_AHEAD, LIGHT_SYSTEM_CONNECT_TIMELY, LIGHT_SYSTEM_CONNECT_DELAY, LIGHT_SYSTEM_CONNECT_UNKNOW};
enum E_LIGHT_SYSTEM_AUTO{LIGHT_SYSTEM_AUTO_NO, LIGHT_SYSTEM_AUTO_YES, LIGHT_SYSTEM_AUTO_UNKNOW};
enum E_LIGHT_SYSTEM_DIRECTION{LIGHT_SYSTEM_DIRECTION_NO, LIGHT_SYSTEM_DIRECTION_YES, LIGHT_SYSTEM_DIRECTION_UNKNOW};
enum E_DRIVE_RULE{DRIVE_RULE_RIGHT, DRIVE_RULE_LEFT, DRIVE_RULE_UNKNOW};
enum E_WINDOW_CTRL{WINDOW_CTRL_CLOSE, WINDOW_CTRL_DRIVER_SIDE, WINDOW_CTRL_ALL_OPEN = 0x1F, WINDOW_CTRL_UNKNOW};
enum E_DOOR_CTRL{DOOR_CTRL_SINGLE_UNLOCK, DOOR_CTRL_ONE_SIDE_UNLOCK, DOOR_CTRL_ALL_UNLOCK, DOOR_CTRL_UNKNOW};
enum E_DOOR_AUTO_LOCK{DOOR_AUTO_LOCK_NO, DOOR_AUTO_LOCK_YES = 0x02, DOOR_AUTO_LOCK_UNKNOW};
enum E_BACK_MIRROR_REVERSE_CAR{BACK_MIRROR_REVERSE_CAR_NO, BACK_MIRROR_REVERSE_CAR_YES, BACK_MIRROR_REVERSE_CAR_UNKNOW};
enum E_BACK_MIRROR_SYNC{BACK_MIRROR_SYNC_NO, BACK_MIRROR_SYNC_YES, BACK_MIRROR_SYNC_UNKNOW};
enum E_WIPER_AUTO{WIPER_AUTO_NO, WIPER_AUTO_YES, WIPER_AUTO_UNKNOW};
enum E_BACK_WIN_CLEAN_REVERSE_CAR{BACK_WIN_CLEAN_REVERSE_CAR_NO, BACK_WIN_CLEAN_REVERSE_CAR_YES, BACK_WIN_CLEAN_REVERSE_CAR_UNKNOW};
enum E_REVERSE_CAR_SYSTEM_AUTO_ACTIVATION{REVERSE_CAR_SYSTEM_AUTO_ACTIVATION_NO, REVERSE_CAR_SYSTEM_AUTO_ACTIVATION_YES, REVERSE_CAR_SYSTEM_AUTO_ACTIVATION_UNKNOW};
enum E_OIL_CONSUME_SELECT{OIL_CONSUME_SELECT_NO, OIL_CONSUME_SELECT_YES, OIL_CONSUME_SELECT_UNKNOW};
enum E_OIL_AVG_CONSUME_SELECT{OIL_AVG_CONSUME_SELECT_NO, OIL_AVG_CONSUME_SELECT_YES, OIL_AVG_CONSUME_SELECT_UNKNOW};
enum E_DRIVE_TIME_SELECT{DRIVE_TIME_SELECT_NO, DRIVE_TIME_SELECT_YES, DRIVE_TIME_SELECT_UNKNOW};
enum E_DRIVE_DISTANCE_SELECT{DRIVE_DISTANCE_SELECT_NO, DRIVE_DISTANCE_SELECT_YES, DRIVE_DISTANCE_SELECT_UNKNOW};
enum E_AVG_SPEED_SELECT{AVG_SPEED_SELECT_NO, AVG_SPEED_SELECT_YES, AVG_SPEED_SELECT_UNKNOW};
enum E_DIGIT_SPEED_DISPLAY{DIGIT_SPEED_DISPLAY_NO, DIGIT_SPEED_DISPLAY_YES = 2, DIGIT_SPEED_DISPLAY_UNKNOW};
enum E_CAR_SPEED_WARNING_DISPLAY{CAR_SPEED_WARNING_DISPLAY_NO, CAR_SPEED_WARNING_DISPLAY_YES, CAR_SPEED_WARNING_DISPLAY_UNKNOW};
enum E_COZY_DEVICE_SELECT{COZY_DEVICE_SELECT_NO, COZY_DEVICE_SELECT_YES, COZY_DEVICE_SELECT_UNKNOW};
enum E_ECONOMY_DRIVE_TIP{ECONOMY_DRIVE_TIP_NO, ECONOMY_DRIVE_TIP_YES, ECONOMY_DRIVE_TIP_UNKNOW};
enum E_DEGREE_UNIT{DEGREE_UNIT_C, DEGREE_UNIT_F, DEGREE_UNIT_UNKNOW};
enum E_DISTANCE_UNIT{DISTANCE_UNIT_KM, DISTANCE_UNIT_MI, DISTANCE_UNIT_UNKNOW};
enum E_SPEED_UNIT{SPEED_UNIT_KM_P_H, SPEED_UNIT_M_P_H, SPEED_UNIT_UNKNOW};
enum E_VOLUME_UNIT{VOLUME_UNIT_L, VOLUME_UNIT_GALON_E, VOLUME_UNIT_GALON_A, VOLUME_UNIT_UNKNOW};
enum E_OIL_CONSUME_UNIT{OIL_CONSUME_UNIT_MPG_E, OIL_CONSUME_UNIT_MPG_A, OIL_CONSUME_UNIT_L_PER_100_KM, OIL_CONSUME_UNIT_KM_PER_L, OIL_CONSUME_UNIT_UNKNOW};
enum E_TIE_COMPRESS_UNIT{TIE_COMPRESS_UNIT_BAR, TIE_COMPRESS_UNIT_PSI, TIE_COMPRESS_UNIT_KPA, TIE_COMPRESS_UNIT_UNKNOW};
enum E_RECOVERY_SETTING_TYPE{RECOVERY_SETTING_TYPE_ALL = 1, RECOVERY_SETTING_TYPE_STOP_AND_START_CAR, RECOVERY_SETTING_TYPE_LIGHT,
RECOVERY_SETTING_TYPE_BACK_MIRROR_AND_WIPER,
RECOVERY_SETTING_TYPE_OPEN_AND_CLOSE,
RECOVERY_SETTING_TYPE_MUCH_FUNCTION_DISPLAY,
RECOVERY_SETTING_TYPE_DRIVER_ASSIST_SYSTEM,
RECOVERY_SETTING_DRIVE_DATA_FROM_START,
RECOVERY_SETTING_DRIVE_DATA_FROM_LONG_TIME,
RECOVERY_SETTING_TYPE_UNKNOW};
enum E_RADAR_AUDIO{RADAR_AUDIO_OPEN, RADAR_AUDIO_CLOSE, RADAR_AUDIO_UNKNOW};
enum E_AIR_CONDITION{AIR_CONDITION_CLOSE, AIR_CONDITION_OPEN, AIR_CONDITION_UNKNOW};
//HELP
enum E_SELECT_CTRL{SELECT_CTRL_UP, SELECT_CTRL_DOWN, SELECT_CTRL_UNKNOW};
enum E_AUDIO_TYPE{AUDIO_TYPE_YL, AUDIO_TYPE_YD};
enum E_DRIVE_DATA_TYPE{DRIVE_DATA_TYPE_FROM_START, DRIVE_DATA_TYPE_FROM_LONG_TIME, DRIVE_DATA_TYPE_FROM_ADD_OIL, DRIVE_DATA_TYPE_UNKNOW};
enum E_MOUSE_MSG{MOUSE_MSG_UP, MOUSE_MSG_DOWN, MOUSE_MSG_MOVE};
enum E_CAR_DOOR_WINDOW{CAR_DOOR_WINDOW_CLOSE, CAR_DOOR_WINDOW_OPEN, CAR_DOOR_WINDOW_UNKNOW};
enum E_CAR_DORMER{CAR_DORMER_CLOSE, CAR_DORMER_OPEN, CAR_DORMER_UNKNOW};
enum E_HEAD_LIGHT{HEAD_LIGHT_CLOSE, HEAD_LIGHT_OPEN, HEAD_LIGHT_UNKNOW};
enum E_CAR_MODELS{CAR_MODELS_UNKNOW = 0,CAR_MODELS_DAS_AUTO = 1,CAR_MODELS_CAMRY = 2,CAR_MODELS_FOCUS = 3,CAR_MODELS_HIGHLANDER = 4,CAR_MODELS_BYD = 5,CAR_MODELS_CIVIC = 6,CAR_MODELS_GOLF = 7};

enum E_MIRRORS_IN_THE_FOLD_HAS_PARKING{MIRRORS_IN_THE_FOLD_HAS_PARKING_NO, MIRRORS_IN_THE_FOLD_HAS_PARKING_YES, MIRRORS_IN_THE_FOLD_HAS_PARKING_UNKNOW};

//////////////////////////////       ring index         //////////////////
#define CARINFO_ALARM_SOUND_LEFT_FORWARD_DOOR_OPEN				1
#define CARINFO_ALARM_SOUND_RIGHT_FORWARD_DOOR_OPEN				2
#define CARINFO_ALARM_SOUND_LEFT_REAR_DOOR_OPEN					3
#define CARINFO_ALARM_SOUND_RIGHT_REAR_DOOR_OPEN				4
#define CARINFO_ALARM_SOUND_BACK_DOOR_OPEN						5
#define CARINFO_ALARM_SOUND_SAFETY_BELT_NOT_LOCK				6
#define CARINFO_ALARM_SOUND_HAND_LOCK_LOCK						7
#define CARINFO_ALARM_SOUND_CLEAN_WATER_OVER					8
#define CARINFO_ALARM_SOUND_SEVERAL_DOOR_OPEN					9
#define CARINFO_ALARM_SOUND_OIL_BELOW_SAFETY_LINE				10

//new audio files/en
#define CARINFO_ALARM_SOUND_HAND_BRAKE_0FF		60
#define CARINFO_ALARM_SOUND_HAND_BRAKE_0N		61
#define CARINFO_ALARM_SOUND_SEAT_BELT_0FF		62
#define CARINFO_ALARM_SOUND_SEAT_BELT_0N		63
#define CARINFO_ALARM_SOUND_TRUNK_CLOSED		64
#define CARINFO_ALARM_SOUND_TRUNK_OPEN			65
#define CARINFO_ALARM_SOUND_DOOR_CLOSED			66
#define CARINFO_ALARM_SOUND_DOOR_OPEN			67
//////////////////////////////////////////////////////////////////////////


enum EM_MAIN_DRIVER{MAIN_DRIVER_LEFT = 0, MAIN_DRIVER_RIGHT, MAIN_DRIVER_UNKOWN};

typedef int (*lpProcessFun)(int nFrom);
	


typedef struct {
	EM_MAIN_DRIVER em_MainDriverPos;
	u8 carType[CAR_TYPE_MAX_LEN];//����
	u8 soundChannel;//���
	//WORD m_wCurPage;	//��ǰҳID
	//WORD m_wPrePage;	//��һҳID


	/****************************  ������  ************************************/	

	/*��������(������)*/
	int speedLock;							//���ٸ�Ӧ�����Զ���
	int shiftLock;							//�������������Զ���
	int pModeUnlock;						//P����������
	int dPressUnlock;						//���°�ť���ν���
	int feedbackTone;						//Lock/Unlock feedback -tone
	int lightSensitivity;					//���Ƶ��ڰ�ť������
	int lampAutoOFFTime;					//Headlamps auto �Coff timer
	int isLightRuning;						//Daytime running lights
	
	//̥ѹ
	int rFrontPressure;						//��ǰ��
	int rRearPressure;						//�Һ���
	int lFrontPressure;						//��ǰ��
	int lRearPressure;						//�����
	int isWarn;								//̥ѹ����

	int avgSpeed;							//ƽ����
	int steerTimeH;							//��ʻʱ�䣬ʱ
	int steerTimeM;							//��ʻʱ�䣬��
	float curOilWear;						//��ǰ�ͺ�
	int oilWearCell;						//�ͺĸ���

	int isShowSteerInfo;					//�Ƿ���ʾ�г���Ϣ
	int carLock;							//���ܳ����һ������
	
	STRUCT_HISTORY carHistory;				//��ʷ��¼


	//////////////////////////////////// Da Zhong Car by dyb///////////////////////////////////////////
	s32 nDrivingDistance;
	s16 nBatteryVoltage;
	s16 nEngineSpeed;
	int nCarDoorStatus;
	ENUM_SatetyBeltStatus  eSafetyBeltStatus;
	ENUM_HandLockerStatus eHandLockerStatus;
	s16 nInstantSpeed;
	int nOilRemind;
	s8 bOilWarning;
	s16 nDegreeOfCarGround;
	s16 nDegreeOfWater;
	ENUM_CleanWaterStatus eCleanWaterStatus;
	s8 nKeyValue;
	s8 nCurCmd;
	bool bCarSpeedCheckTimerStart;
	lpProcessFun pszProcessSpeedCheckFun[50];
	bool bOilAlarmNeedToSend;
	bool bHandLockAlarmNeedToSend;
	bool bOpenVoiceLater;
	bool bOpenVoiceAndNeedAlarm;

	u8 AutomaticalAcOrEffectVentilat;
	bool bVoicePrompt;/*������Ϣҳ�汨����������*/
	char c_carName[20];

	int nCarDoorLockStates;/*��������״̬*/
	int nCarWindowStatus;/*��������״̬*/
	int nCarWindowLockStatus;/*������������*/
	u8 uTRCStatus;/*����ǣ��������*/
	u8 uSPORTStatus;/*S�����˶�ģʽ*/
	u8 uCruiseControlStatus;/*Ѳ������*/
	u8 uECOStatus;/*����ģʽ*/
	s16 sTempOfCoolingLiquid;/*��ȴҺ�¶�*/
	int sWaterOfTheWaterTank;/*ˮ��ˮ��*/
	u8 uGearStage;  /*��λ��Ϣ:1 P,2 R,3 N,4 D*/

	//Siyu
	int SurplusDistance;/*ʣ�����*/
	float avgOilWear; /*ƽ���ͺ�*/

	E_CAR_STALL eCarStall;
	E_CAR_DOOR_LOCKER eCarDoorLocker;

	int nCarWiper;/*�����*/
	int nSteeringWheelAngle;/*�����̽Ƕ�*/

	//dyb ŽóÖÚ³µÉèÖÃÏà¹Ø
		int nCanSendChineseToDZCarScreen;	//ÒòÎªÆû³µÐ¡ÆÁÓÐÐ©Ã»×Ö¿â£¬ËùÒÔÒª¿ØÖÆÊÇ·ñ·¢ËÍÖÐÎÄÏÂÈ¥£¬Ä¬Ðí²»·¢ËÍ
		int nGolfRadarRingDoor;

		//dyb
		E_DRIVE_MODE eDriveMode;	////golf///////////////////////////////////////////////////////////////////
		E_LAST_SELECT_GAP eLastSelectGap;
		E_GAP eGap;
		E_PRE_ASSIST_SYSTEM_ACTIVATION ePreAssistSystemActivation;
		E_PRE_ASSIST_SYSTEM_WARNING ePreAssistSystemWarning;
		E_PRE_ASSIST_SYSTEM_GAP_WARNING ePreAssistSystemGapWarning;
		E_FATIGUE_RECONIZE_SYSTEM_ACTIVATION eFatigueReconizeSystemActivation;
		E_ESC_SYSTEM_ACTIVATION eEscSystemActivation;
		E_TIRE_TYPE eTireType;
		E_CAR_SPEED_WARNING eCarSpeedWarning;
		int nCarSpeedWarning;
		E_LIGHT_SYSTEM_CONNECT eLightSystemConnect;
		E_LIGHT_SYSTEM_AUTO eLightSystemAuto;
		E_LIGHT_SYSTEM_DIRECTION eLightSystemDirection;
		E_DRIVE_RULE eDriveRule;
		int nGoHomeModeTime;
		int nLeaveHomeModeTime;
		int nMeterLightBrightness;
		int nDoorLightBrightness;
		int nFeetLightBrightness;
		E_WINDOW_CTRL eWindowCtrl;
		E_DOOR_CTRL eDoorCtrl;
		E_DOOR_AUTO_LOCK eDoorAutoLock;
		E_BACK_MIRROR_REVERSE_CAR eBackMirrorReverseCar;
		E_BACK_MIRROR_SYNC eBackMirrorSync;
		E_WIPER_AUTO eWiperAuto;
		E_BACK_WIN_CLEAN_REVERSE_CAR eBackWinCleanReverseCar;
		E_REVERSE_CAR_SYSTEM_AUTO_ACTIVATION eReverseCarSystemAutoActivation;
		int nCarFrontAudioParam;
		int nCarRearAudioParam;
		E_OIL_CONSUME_SELECT eOilConsumeSelect;
		E_OIL_AVG_CONSUME_SELECT eOilAvgConsumeSelect;
		E_DRIVE_TIME_SELECT eDriveTimeSelect;
		E_DRIVE_DISTANCE_SELECT eDriveDistanceSelect;
		E_AVG_SPEED_SELECT eAvgSpeedSelect;
		E_DIGIT_SPEED_DISPLAY eDigitSpeedDisplay;
		E_CAR_SPEED_WARNING_DISPLAY eCarSpeedWarningDisplay;
		E_COZY_DEVICE_SELECT eCozyDeviceSelect;
		E_ECONOMY_DRIVE_TIP eEconomyDriveTip;
		int nRecoveryDriveDataFromAutoRun;
		int nRecoveryDriveDataFromLongTimeRun;
		E_DEGREE_UNIT eDegreeUnit;
		E_VOLUME_UNIT eVolumeUnit;
		E_OIL_CONSUME_UNIT eOilConsumeUnit;
		E_TIE_COMPRESS_UNIT eTieCompressUnit;
		E_DISTANCE_UNIT eDistanceUnit;
		E_SPEED_UNIT eSpeedUnit;
		int nSystemTimeInfo;
		int nSystemDateInfo;
		int nDateFormat;
		E_RECOVERY_SETTING_TYPE eRecoverySettingType;
		E_RECOVERY_SETTING_TYPE eRecoverySettingTypeSelected;
		int nLanguage;
		E_RADAR_AUDIO eRadarAudio;
		u8 szVim[40];
		int nMaintainDistanceInfo;
		int nMaintainTimeInfo;
		int nMaintainEngineOilDistanceInfo;
		int nMaintainEngineOilTimeInfo;
		int nTheDistanceLeaveCarCanRun;
		int nAvgOilConsumeFromCarRun;
		int nDriveDistanceFromCarRun;
		int nDriveTimeFromCarRun;
		int nCarSpeedFromCarRun;
		int nAvgOilConsumeFromLongTimeRun;
		int nDriveDistanceFromLongTimeRun;
		int nDriveTimeFromLongTimeRun;
		int nCarSpeedFromLongTimeRun;
		int nAvgOilConsumeFromAddOil;
		int nDriveDistanceFromAddOil;
		int nDriveTimeFromAddOil;
		int nDriveSpeedFromAddOil;
		E_AIR_CONDITION eAirCondition;
		int nGolfCarStyle;
		//help
		E_DRIVE_DATA_TYPE eDriveDataType;
		////golf///////////////////////////////////////////////////////////////////

		u32 testCarPage;
		u8  cCarinfoButtonVisible;
		E_MIRRORS_IN_THE_FOLD_HAS_PARKING emMirrorsIntheFoldParkedSelect;
	//////////////////////////////////////////////////////////////////////////////////////

	CCarInfo *m_pCarInfo;
	E_CAR_DOOR_WINDOW eCarDoorWindow_FL;
	E_CAR_DOOR_WINDOW eCarDoorWindow_FR;
	E_CAR_DOOR_WINDOW eCarDoorWindow_RL;
	E_CAR_DOOR_WINDOW eCarDoorWindow_RR;
	E_CAR_DORMER eCarDormer;
	E_HEAD_LIGHT eHeadLight;
	E_CAR_MODELS eCarModels;

	bool bCurMODE_State;
	u8 uModeKeyValue;
	bool bFirstGotoModePage;
	E_CAR_DRIVING_MODE eCar_DrivingMode;
	E_CAR_DAMPING_SYSTEM_MOD eCar_DampingSystemMode;
	E_CAR_STEERING_WHEEL_MOD eCar_SteeringWheelMode;
	E_CAR_DRIVING_GEAR_MOD eCar_DrivingGearMode;
	E_CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD eCar_Dynamic_Headlight_FollowerMode;
	E_CAR_AC_MOD eCar_AcMode;
	E_CAR_INTERNAL_ENGINE_SOUNDS_MOD eCar_InternalEngineSoundsMode;
	E_CAR_MODE_RESET_ACTION eCar_ModeResetAction;

	u8 szDoorStatus[5];

	u8 tagBoosterMode;
	u8 tagLocFeedback;
	u8 tagShutDownUnlock;
	u8 tagPositionAfterLock;
	int publicEngineSpeed;
	int publicDrivingDistance;
	u8 publicDrivingDistanceUint;
	int publicDegreeOfCarGround;
	int CarGroundPosOrNeg;
	int CarGroundDecimalNumber;
	int CarGroundUnit;
	
	int publicnIStantSpeed;
	int publicAverageSpeed;
	u8 nGearsValue;
	int ContinuedDriveMileage;

	u8 uSpeedAlarmSwitch;
	u16 uSpeedAlarmValue;
	u8 uTrunkDegreeValue;
	u8 uTrunkDegreeMax;
	u8 uTrunkDegreeMin;
	u8 uTrunkDegreeStep;
	u8 uWelcomeLampSwitch;
	u16 uWelcomeLampOpenTimeMix;
	u16 uWelcomeLampOpenTimeMax;
	u16 uWelcomeLampOpenTimeStep;
	u16 uWelcomeLampOpenTime;
	u8 uCompanyLampHomeSwitch;
	int uLampCompanyHomeTimeMix;
	int uLampCompanyHomeTimeMax;
	int uLampCompanyHomeTimeStep;
	u16 uCompanyLampHomeTime;
	u8 uVehicle_mode;
	u8 uDrivingAutomaticLatchSwitch;
	u16 uDrivingAutomaticLatchSpeed;
	u8 uFlameoutAutomaticLatchSwitch;
	u8 uKeyLessUnlockDoor;
	u8 uKeyUnlockDoor;
	u8 uAC_automaticModeFlow;
	u8 uFBdeforstFogLinkSwitch;
	u8 uMirrorAutomaticOpenSwitch;
	
	u16 uFrontRadarDistance;
	u16 uRearRadarDistance;
	u8 uBatteryVoltageAnomalyMonitoring;

	u8 szDoorLockStatus[4];
	u8 nFrontCover;
	u8 nSkyLight;
	u8 nHighBeam;
	u8 nDippedHeadlight;
	u8 szVINCode[20];
	
	u8 eCarGears;
	U8 uParkingModeState;

}extcar_local_param_t;

typedef struct{
	
}extcar_global_param_t;


extern extcar_local_param_t *pLocalParam;
extern extcar_global_param_t *pGlobalParam;


extern CCarInfoCarSettingToyota gclsCarInforCarSettings;
extern CNotifyAndResponseFlyJniSdk g_clsExtcar;

void readParameter(void);
void saveParameter(void);



typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;
uni16_size_t uni16_strlen(const unicode16_t *uni16);
unicode16_t ansi_to_unicode16(const unsigned char ansi);
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src);
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);

int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
int enc_get_utf8_size(const unsigned char pInput);

#endif
