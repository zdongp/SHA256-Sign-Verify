#ifndef __PARAM_H__
#define __PARAM_H__

#include <pthread.h>
#include "global.h"
#include "FlyDefine.h"
#include "FlySystemAbout.h"
#include "SteeringWheelStudy.h"

#include "CNotifyAndResponseFlyJniSdk.h"

#define SYS_MAX_PAGE_COUNT	20
#define READ_WRITE_INFO_KEY_LEN 16
#define READ_INFO_KEY  "1234567890000000"

#define READ_UUID_LENGTH    32
#define SIGMYTIMERA 40
#define READ_BARCODE_LENGTH  64


#define AMBIENT_SCREEN_BRIGHTNESS_MAX 100
#define AMBIENT_SCREEN_BRIGHTNESS_MIN 1

#define PANEL_LIGHT_MIN    3

#define RADIO_AREA_NUM 	7
enum emWheelClear{emClear_Mode, emClear_Seek_INC,emClear_Seek_DEC, emClear_Mute, emClear_Vol_INC, emClear_Vol_DEC,emClear_bt_callin,emClear_bt_handup, emClear_NO};
enum E_FAN_MODE
{
	eFanModeShutDown,
	eFanModeShutOpen,
	eFanModeHighPerformance,
	eFanModeFitAuto,
	eFanModeLowPower,
};

enum E_VOLTAGE_PROTECTION
{
	eVoltageProtectionModeHigh,
	eVoltageProtectionModeMid,
	eVoltageProtectionModeLow
};

enum E_BACKCAR_HASREDLINE_STATE
{
	eLineState_NoShow,
	eLineState_IsShow,
	eLineState_Unkown
};

enum E_BACKCAR_MODE
{
	BACKCAR_MODE_NORMAL,
	BACKCAR_MODE_FAST
};
// zhq add for checkmethod
enum E_SETUP_BACKCAR_TRIGGER
{
	eSetupBackcarTriggerAutomatic,
	eSetupBackcarTriggerProtocol,
	eSetupBackcarTriggerLevel,
	eSetupBackcarTriggerUnknow
};

#define AMBIENT_LED_DIMMING_MAX 255
#define AMBIENT_LED_DIMMING_MIN 0

#define AMBIENT_LED_RGB_MAX 255
#define AMBIENT_LED_RGB_MIN 0


enum E_AMBIENT_LED_SWITCH
{
	AMBIENT_LED_ON,
	AMBIENT_LED_OFF
};

enum E_AMBIENT_LED_RGB
{
	AMBIENT_LED_R,
	AMBIENT_LED_G,
	AMBIENT_LED_B
};

enum E_AMBIENT_LED_COMMISSION
{
	LED_COMMISSION_WARM_RED,
	LED_COMMISSION_HAPPY_ORANGE,
	LED_COMMISSION_LIVELY_YELLOW,
	LED_COMMISSION_FRESH_GREEN,
	LED_COMMISSION_WORRY_BLUE,	
	LED_COMMISSION_MYSTERIOUS_PURPLE,
	LED_COMMISSION_ACACIA_RED,
	LED_COMMISSION_ROMANTIC_PINK,
	LED_COMMISSION_FRESH_BLUE,
	LED_COMMISSION_PURE_WHITE,
	LED_COMMISSION_UNKNOWN
};

enum E_EYE_PROTECTION_MODE
{
	PROTICTION_MODE_DAY,
	PROTICTION_MODE_NIGHT,
	PROTICTION_MODE_REVERSING
};

enum E_AMBIENT_LED_CUSTOMIZE
{
	LED_COMMISSION_CUSTOMIZE_1,
	LED_COMMISSION_CUSTOMIZE_2,
	LED_COMMISSION_CUSTOMIZE_3,
	LED_COMMISSION_CUSTOMIZE_UNKNOWN
};

#define EXTERNAL_DEVICE_COUNT 4
//enum E_EXTERNAL_DEVICE
//{
//	EXTERNAL_DEVICE_DVR,
//	EXTERNAL_DEVICE_TV_TPMS,
//	EXTERNAL_DEVICE_DNV,
//	EXTERNAL_DEVICE_UNKNOW
//};

#define FLY_SET_DVD_VERSION         "fly.set.dvd_version"

#define NAVILIST_FILE_PATH "/flysystem/flyconfig/default/modelconfig/NaviPath.xml"
#define NAVILIST_FILE__FLYAPDATA_PATH "/flyapdata/config/NaviPath.xml"
#define NAVICOUNT               10

////////////////NaviPath.xml Attribute////////////////
#define NAMESTR "MapNameStr"
#define NAMEID "Name"
#define PACKNAME "PackName"
#define ClassName "ClassName"
/////////////////////////////////////////////////////

struct Navi
{
	char NaviMark;
	char NaviNameStr[128];
	int NaviNameStrID;
	u8 NaviPackName[128];
	u8 NaviClassName[128];
};

enum E_DVR_PROTOCOL_MODE
{
	e_Is_ProTocol,
	e_No_ProTocol,
	e_Unkown_ProTocol
};


#define LOGOCOUNT 60
#define STYLE_LOGO_LIST_FILE_PATH "/flysystem/flytheme/config/bootanimationConfig.xml"
struct ST_LOGO_STYLE
{
	char cLogoStyleMark;
	char cLogoStylesNameStr[128];
	int cLogoStyleNameStrID;
};

#define SAVE_RGB_NUM 3

struct SAVE_RGB_DIMMING_VALUE
{
	u8 uAmbientLedSaveRValue[2];
	u8 uAmbientLedSaveGValue[2];
	u8 uAmbientLedSaveBValue[2];
	int uShowCurSaveColorValue;
};
enum DAYANDNIGHTMODE
{
	eDayAndNight_Day,
	eDayAndNight_Night,
	eDayAndNight_Auto,
	eDayAndNight_UNKOWN
};
#define RETURN_HOME_PAGE_FILE_PATH "/flysystem/flyconfig/default/modelconfig/returnHomePage.xml"

#define SEAT_COUNT 2
struct SAVE_MCS_ADJUST_MASSAGE_VALUE
{
	u8 uChMk;
	u8 uUL;
	u8 uML;
	u8 uLL;
	u8 uUB;
	u8 uLB;
	u8 uLMI;
	u8 uCMI;
};



typedef struct{
	//Cur Pre Page ID	
	char str_WhichProject[20];
	u8 uModuleSystem_is_T123;
	u8 uBackCarVideoSwitch_Status;
	u8 u8BootOnIsAutoPlay;
	u16 u16_Sys_PrePage; //Pre Page
	//2012-03-10
	u16 u16_Sys_SwitchTempPage; //Temp Page
	//Day Night
	bool b_Sys_LightDetect; //Detect Light Or Not
	bool b_Sys_DayNight;//Day Or Night State
	//Panel Light
	u8 u8_Sys_PanelLight; //Panel Light Status
	u8 u8_Sys_PanelLight_bef;
	//Startup Vol
	u8 u8_Sys_StartupVol;
	u8 u8_Sys_StartupVol_bef;
	u8 cBreakCarEnable;

	//LCD
	u8 u8_Sys_CurLcdLight; //LCD Light
	u8 u8_Sys_PreLcdLight;
	bool bSysStatusBarSet;

	//Standby Status
	u8 u8_Sys_StandbyStatus;
	u8 u8_Sys_StandbyStatus1;
	//FactoryAmplifier State
	bool b_Sys_AmplifierStatus;
	//Brake Car
	bool b_Sys_BrakeCarStatus; //Brake Car Status

	//GPS Run
	bool b_Sys_AutoRunGPS; //Auto Run
	bool b_Sys_GPSVoicePrompt;
	bool b_Sys_Auto_AutoSound;

	
	//zhq	 DNV
	bool m_bSupportDNV;

	
	//Back Car
	bool b_Sys_BackCarDetectEnable;
	bool b_Sys_BackCarStatus;
	bool b_Sys_BackCarVideo;
	u8   m_cRadarData[16];
	u8   m_cRadarDataUI[16];
	u8   m_radarCar;
	//Aux Video Status
	u8 u8_Sys_AuxVideo;

	//SteeringWheel
	bool b_Sys_SpecialSteeringWheel;
	u8 u8_Sys_UserSteeringWheel;
	bool b_Sys_WaitStudy; //Wait Study

	u8 m_cWheelKey[6]; //Wheel Key
	u8 m_cCurClearKey; //\u5f53\u524d\u662f\u4e0d\u662f\u521a\u521a\u6e05\u9664\u5bf9\u5e94\u7684KEY
	enum emWheelClear m_emClearKey;

	//Radio Coountry Code
	u8 u8_Sys_RadioCountryCode;
	//DVD Region Code
	u8 u8_Sys_DVDRegionCode;


	bool b_Sys_Ipod; //Ipod Or Aux
	bool b_Sys_TVOrXM; //TV or XM

	//TV Exist Or Not
	u8 u8_Sys_WhetherTVExist;
	//TPMS Exist Or Not
	u8 u8_Sys_WhetherTPMSExist;

	u8 u8_Sys_AUXVideo; //Whether have AUX Video
	u32 u8_Sys_tempPage;
	//Set Time
	bool b_Sys_HourPerDay_24; //24

	short u16_Sys_PrePageArray[2][2];

	u16 u16_Sys_PageTable[SYS_MAX_PAGE_COUNT];
	int n_Sys_PageTable_Pos;
	int n_Sys_PageTableCount;
	bool b_Sys_ThirdPageMark;
	bool b_Sys_HomePageMark;
	bool b_Sys_ThirdPageBackMark;
	bool b_Sys_GpsPageMark;
	//2011-03-13
	bool b_Sys_ThridPageBackNoHomePageMark;

	char brightness;

    bool b_Timer;

	bool b_Barcode;

	bool f_Visible;
	bool b_Visible;
	bool b_enable_ipol;
	bool b_enable_tv;
    bool b_back;
	int fd;
	char CarName[20];

	int Car_type_version;
	int Default_channel;
	
	int Start_MaxVol;
	int Start_minVol;
	int Start_defaultVol;
    bool b_hal_radar;
    char c_ModuleTable[7];

	bool b_3G_DialIn;
	bool  b_isAUX;/*�Ƿ����AUX*/
	//bool b_SetTimer_AccOn;
	bool b_Gps_Runing;
	bool b_NeedLaunchThirdApp;
	char c_mcu[100];
	
	E_EXTERNAL_DEVICE m_eExternalDevice;

	u8   uDvrTvTpmsVisible;
	u8   cNavigationVisible;
	u8   cSystemUpdateMode;
	bool b_Sys_VoicePrompt;   /*�г���Ϣ������ʾ*/
	u8 blanguage;        
	Navi naviList[NAVICOUNT];
	u8 NaviNub;
	bool DebugSwitch;  /*0ΪHAL��OSD  1ΪModule��OSD*/
	bool osdDebugSwith; /*OSD�ܿ���*/
	
	u8 cChoseeCarMode[128];      /*ѡ��ĳ���*/
	u8 cChoseeCarModeLen;
	u8 cRealCarMode[128];        /*��ʵ����*/
	u8 cRealCarModeLen;
	bool bShowReviseCarModePage;  /*�Ƿ���ʾУ����ҳ*/

	int nSpecificSkin_PrePage;/*����ض�Ƥ������Ҫ������EQҳ��֮��ķ�����ҳ*/
    pthread_mutex_t mutex;
    pthread_mutex_t mutex_notifyPageChange;


	bool bRealCarRecv;
	bool bChooseCarRecv;
	bool initRecv;
	// system setting page
	E_FAN_MODE eCurFanMode;
	E_FAN_MODE ePreFanMode;
	E_VOLTAGE_PROTECTION eVoltageProtectionMode;
	E_SETUP_BACKCAR_TRIGGER eSetupBackcarTriggerType;//zhq add for checkmethod

	u8 cBrightness_Dim;
	u8 cBrightness_Moderate;
	u8 cBrightness_Bright;	
	u8 cBrightness_RangeValue;
	
	u8 cDvdRegion;
	u8 cRadioCountry;
	u8 cCarTypeVisible;
	u8 cCarMatchShow;
	u8 cCarAlarmVisible;
	bool bShowSystemDialog;
	int nNaviCount;
	int nNavigationBootingRunMod;
	E_BACKCAR_HASREDLINE_STATE eBackVideoRefLineIsDisplay;
	E_BACKCAR_HASREDLINE_STATE eBackVideoTraceLineIsDisplay;
	u8 uc_MEPG[100];
	u8 uc_UUID[100];
	u8 ucBattery_Value;

	//class
	CFlySystemAbout m_flySystemAbout;	
	CSteeringWheelStudy m_clsSteeringWheelStudy;

	E_BACKCAR_MODE m_eBackCarMode;

	char uSystemExterDeviceGroup[7];
	char uSystemBackcarTtiggerGroup[5];
	u8 bHomePageOSDCanDrop;
	bool bPrado_RadarSwitchKeyStatus;
	bool bPrado_RadarSwitchUiStatus;

	u8 uStandByStatus;

	int nLogoStyleCount;
	u8 uLogoSetNub;
	ST_LOGO_STYLE st_LogoStyle[LOGOCOUNT];
	bool b_Sys_NaviMixLowSwitch;
	
	u8 uAmbientLedInitState;
	E_AMBIENT_LED_SWITCH emAmbientLedSwitch;
	u8 uAmbientLedDimmValue;
	u8 uAmbientLedRValue[2];
	u8 uAmbientLedGValue[2];
	u8 uAmbientLedBValue[2];
	E_AMBIENT_LED_COMMISSION emAmbientLedCommission;
	
	u8 uBackCarSetCvbsOrUSB;
	u8 uSetCvbsOrUSBTemp;
	u8 uSystemTimeFormat;

	E_DVR_PROTOCOL_MODE eDvrProtocolMode;
	//
	int uShowCurColorValue;
	bool showGRB_Dimming_tag;
	SAVE_RGB_DIMMING_VALUE eSaveRGB_Dimming_value[SAVE_RGB_NUM];
	 E_AMBIENT_LED_CUSTOMIZE eCustomizeRGB;
	 DAYANDNIGHTMODE curDayAndNightMode;
	 int curBackCarLineType;
	 u8 curDailingOption;
	 u8 uCameraDelayTag;
	 u8 uDesktopNivaInforSwitch;

	 int systemSkinType;
	 int pageStrIdList[100];
	 int nPageCount;
	 u8 nScreenSwitchStatus;
	u8 uScreenBrightAutoSwtich;
	u16 fordAlmBrightnessMaxValue;

	SAVE_MCS_ADJUST_MASSAGE_VALUE st_MCS[SEAT_COUNT];
	u8 selectSeatSide;
	u8 uMCS_Available;
	u8 uCurCartype;
	u8 uCurSelectionCarType;
}system_local_param_t;

typedef struct{
	//Cur Pre Page ID
	u16 u16_Sys_PrePage; //Pre Page
	//Day Night
	bool b_Sys_LightDetect; //Detect Light Or Not
	bool b_Sys_DayNight;//Day Or Night State
	//Panel Light
	u8 u8_Sys_PanelLight; //Panel Light Status
	//Startup Vol
	u8 u8_Sys_StartupVol;
    u32 u8_Sys_tempPage;
	//LCD
	u8 u8_Sys_CurLcdLight; //LCD Light
	u8 u8_Sys_PreLcdLight;

	//Standby Status
	u8 u8_Sys_StandbyStatus;
	u8 u8_Sys_StandbyStatus1;
	//FactoryAmplifier State
	bool b_Sys_AmplifierStatus;
	//Brake Car
	bool b_Sys_BrakeCarStatus; //Brake Car Status
	//GPS Run
	bool b_Sys_AutoRunGPS; //Auto Run
	bool b_Sys_GPSVoicePrompt;
	bool b_Sys_Auto_AutoSound;
	
	//Back Car
	bool b_Sys_BackCarDetectEnable;
	bool b_Sys_BackCarStatus;
	bool b_Sys_BackCarVideo;

	//zhq    DNV
	bool m_bSupportDNV;



	//Aux Video Status
	u8 u8_Sys_AuxVideo;

	//SteeringWheel
	bool b_Sys_SpecialSteeringWheel;
	u8 u8_Sys_UserSteeringWheel;
	bool b_Sys_WaitStudy; //Wait Study


	//--------------------2012-2-29-----------------------------------------------------
	u8 m_cWheelKey[6]; //Wheel Key
	u8 m_cCurClearKey; //\u5f53\u524d\u662f\u4e0d\u662f\u521a\u521a\u6e05\u9664\u5bf9\u5e94\u7684KEY
	enum emWheelClear m_emClearKey; //\u6e05\u9664\u76f8\u5e94\u7684\u6309\u952e


	//Radio Coountry Code
	u8 u8_Sys_RadioCountryCode;
	//DVD Region Code
	u8 u8_Sys_DVDRegionCode;


	bool b_Sys_Ipod; //Ipod Or Aux
	bool b_Sys_TVOrXM; //TV or XM

	//TV Exist Or Not//
	u8 u8_Sys_WhetherTVExist;
	//TPMS Exist Or Not
	u8 u8_Sys_WhetherTPMSExist;

	u8 u8_Sys_AUXVideo; //Whether have AUX Video

	//Set Time
	bool b_Sys_HourPerDay_24; //24
	char brightness;

    bool b_Timer;
	bool b_Barcode;
	bool f_Visible;
	bool b_Visible;
	bool b_enable_ipol;
	bool b_enable_tv;
	int fd;
	 bool b_back;
	char CarName[20];
	int Start_MaxVol;
	int Start_minVol;
	int Start_defaultVol;
	bool b_hal_radar;
}system_global_param_t;

extern system_local_param_t localParam;
extern system_global_param_t globalParam;


extern system_local_param_t *pLocalParam;
extern system_global_param_t *pGlobalParam;
//bool DVD_OR_Radio_To_AudioPage=false;
extern CNotifyAndResponseFlyJniSdk g_clsSystem;



void readParameter(void);
void saveParameter(void);
void SystemModule_Timer_WheelData_Clear(void);
void SystemModule_Dispatch_SystemReset(void);
void SystemModule_WheelDataFromRegest(void);
void SystemModule_WheelDataFromRegest_Key(char* buf,u32 ContorlID);

void SystemModule_ReadBarCode();
void Handle_BarCode(void);
//2012-07-24
void SystemModule_ReadUUID();
void SystemModule_ReadMCU();
int bufferToString(char *buffer, int len, char *str);
int stringToBuffer(char *str, char *buffer);
char __intToChar(char value);
char __charToInt(char ch);





typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);

int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
int enc_get_utf8_size(const unsigned char pInput);

void readParam_aboutCvbsOrUsb();
void writeParam_aboutCvbsOrUsb();
void writeParam_aboutCarTypeSelection();

#endif
