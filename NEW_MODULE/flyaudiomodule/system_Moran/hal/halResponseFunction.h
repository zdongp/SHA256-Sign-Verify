#ifndef __HAL_RESPONSE_FUNCTION_H__
#define __HAL_RESPONSE_FUNCTION_H__

#include "global.h"
#include "messageQueue.h"


enum emSoundMode{SoundMode_NOCHANNEL=0xff,SoundMode_DVD=0x00,VideoMode_DVD =0x01,SoundMode_CDC=0x02,VideoMode_CDC=0x03,SoundMode_RADIO=0x04,SoundMode_AUX=0x05,VideoMode_AUX=0x06,
                 SoundMode_IPOD=0x07,VideoMode_IPOD=0x08,SoundMode_TV=0x09,VideoMode_TV=0x0A,SoundMode_MEDIA=0x0B,SoundMode_SRADIO=0x0C, SoundMode_STANDBY=0x80,SoundMode_BT=0x0d};


enum emRadioCountryCode{emCode_CHINA = 0x00,emCode_USA = 0x01,emCode_SAMER_1 = 0x02,emCode_SAMER_2 = 0x03,emCode_KOREA = 0x04,emCode_THAILAND = 0x05,emCode_RUSSIA = 0x06};





#define HALTOSYSTEM_INIT_CMD					0x01
#define HALTOSYSTEM_INIT_STATE					0x02
#define HALTOSYSTEM_BACKCAR_DETECT				0x10
#define HALTOSYSTEM_LIGHT_DETECT				0x11
#define HALTOSYSTEM_DAY_NIGHT					0x12
#define HALTOSYSTEM_EXT_AMPLIFIER				0x13
#define HALTOSYSTEM_LCD_BRIGHTNESS				0x14
#define HALTOSYSTEM_KEY_LEDBRIGHTNESS			0x15
#define HALTOSYSTEM_SPECIFIC_FUNC_STEEL_SWITCH	0x16
#define HALTOSYSTEM_RADIO_REGION				0x17
#define HALTOSYSTEM_DEMO_MODE					0x19
#define HALTOSYSTEM_CUSTOM_STEELPANELDATA		0x1A
#define HALTOSYSTEM_STEELPANEL_LEARN_STATE		0x1B
#define HALTOSYSTEM_DVD_REGION_CODE			0x1E
#define HALTOSYSTEM_FAN_CTRL				0x1F
#define HALTOSYSTEM_CPU_PERFORMANCE			0x50

#define HALTOSYSTEM_BRAKE_STATE				0x20
#define HALTOSYSTEM_BACKCAR_STATE				0x21
#define HALTOSYSTEM_ACC_VOLTAGE				0x22
#define HALTOSYSTEM_CUR_STEELPANEL_NAME		0x24
#define ALTOSYSTEM_TV_MODULE_EXIST	        0x25
#define ALTOSYSTEM_TPMS_MODULE_EXIST	        0x26

#define HALTOSYSTEM_3G_MODULE_EXIST			0x27
#define HALTOSYSTEM_AUX_VIDEO_SIGINAL			0x28
#define HALTOSYSTEM_EXIT_IPOL                0x29
#define HALTOSYSTEM_BATTERY_STATE			 0x30

#define HALTOSYSTEM_ACC_OFF					0x31
#define HALTOSYSTEM_STANDBY_MODE				0x32
#define HALTOSYSTEM_MCU_VERSION				0x33
#define HALTOSYSTEM_DVD_VERSION				0x34
#define HALTOSYSTEM_BT_VERSION				0x35
#define HALTOSYSTEM_KEY_15S_GPS             0x2e
#define HALTOSYSTEM_RADAR_CAR_FRONT         0x41
#define HALTOSYSTEM_RADAR_CAR_BEHIND        0x42
#define HALTOSYSTEM_RADAR_CAR_INFO          0x43

#define HALTOSYSTEM_TIME_INFO               0x37
#define HALTOSYSTEM_AUTO_ADJUST_SWITCH      0x39

#define HALTOSYSTEM_AUXTIME_INFO            0xA0
#define HALTOSYSTEM_RETURN_IPOL_TV_TPMS     0x2D
#define HALTOSYSTEM_RETURN_DVR_TV_TPMS      0x2F

#define HALTOSYSTEM_RETURN_CHOOSE_CARNAME   0x44

#define HALTOSYSTEM_RETURN_TRIGGER_TYPE     0xA4

void analyseHalMessage_SYSTEM(char resCmd, unsigned char *param, unsigned char len);


void halToSystem_InitCmd(u8 u8_Param); //Init Cmd
void halToSystem_InitStatus(u8 u8_Param); //Init Status
void halToSystem_BackCarDetectEnable(u8 u8_Param); //Back Car Detect enable
void halToSystem_LightDetectEnable(u8 u8_Param); //Light Detect Enable
void halToSystem_DayOrNight(u8 u8_Param); //Day Or Night Mode
void halToSystem_ExternalAmplifier(u8 u8_Param);
void halToSystem_LCDBrightness(u8 *Param);
void halToSystem_LEDBrightness(u8 u8_Param);
void halToSystem_SpecialSteeringWheel(u8 u8_Param);
void halToSystem_RadioConturyCode(u8 u8_Param);
void halToSystem_DemoMode(u8 u8_Param);
void halToSystem_ApplyUserDefinedWheelData(u8 u8_Param);
void halToSystem_WheelStudyStatus(u8 u8_Param);
void halToSystem_DVDRegionCode(u8 u8_Param);
void halToSystem_BrakeCarStatus(u8 u8_Param);
void halToSystem_BackCarStatus(u8 u8_Status, u8 u8_Video);
void halToSystem_FanCtrlMode(u8 u8_Param);
void System_BrakeCarDetect_IsCanSeeVideo();
void halToSystem_aboutAmbientLedMsg(u8 *p,u8 len);

//------------------2012-2-29(WheelStudy)---------------------------------------
void SystemTohal_CancelWheelStudy ();
void SystemTohal_StudyWheelData(u8 ckey);
void SystemTohal_ClearWheelData(u8 cKey);
void SystemTohal_SaveRegistry(void);

void halToSystem_MagnitudeOfVoltage(u8 u8_Param);
void halToSystem_CurWheelName(u8 *pBuf, u8 u8_len);
void halToSystem_WhetherTVExist(u8 u8_Param);
void halToSystem_WhetherTpmsExist(u8 u8_Param);
void halToSystem_Whether3GPhoneExist(u8 u8_Param);

void halToSystem_AuxVideo(u8 u8_Param);

void halToSystem_StandbyStatus(u8 u8_Param1,u8 u8_Param2);
void halToSystem_ACC_Status(u8 p);
void GetToSystem_StandbyStatus_New(u8 p);

void halToSystem_MCU_Version(u8 *pBuf, u8 len);

void halToSystem_DVD_Version(u8 *pBuf, u8 len);
void halToSystem_BT_Version(u8 *pBuf, u8 len);



void halToSystem_Debug_Info(u8 *pBuf, u8 len);
void halToSystem_Key_Gps(u8 *pBuf,u8 len);
//void halToSystem_Radar_Info(u8* pBuf,u8 len);
void halToSystem_Radar_Info_F(u8* pBuf); 
void halToSystem_Radar_Info_FF(u8* pBuf); 

void halToSystem_Radar_Info_B(u8* pBuf); 
void halToSystem_Radar_Info_BB(u8* pBuf); 

void systemGetRadarDataDeal(u8* pBuf);

void halToSystem_Radar_Info(u8* Buf,u8 resCmd);
void halToSystem_Radar_Info_Car(u8* pBuf,u8 resCmd); 
/*******************************************************************************************/
void halToSystem_battery_state(u8 u8_Param);


void analyseHalMessage_Global(char resCmd, unsigned char *param, unsigned char len);
void halToSystem_Return_Dvr_Tv_Tpms(u8 u8_Param);


void halToSystem_Return_choose_CarName(u8 *param,u8 len);
void halToSystem_RealCarMode(u8 *pBuf,u8 len);
void halToSystem_VIMCode(u8 *pBuf,u8 len);
void halToSystem_WakeUpInfo(u8 state);

void halToSystem_Global_Circle_Ping(u8 state);

//zhq add triggertype
void SetTriggerTypeStringText(int n);
void halToSystem_ReturnTriggerMessage(u8 *Param);
void HalToSystem_TransparentChannel_Message(u8 *u8_Param);


void halToSystem_BatteryVolt_NewPassageway_aboutOnlinePrompt(u8 *param,int len);


void halToSystem_Return_Setchoose_CarName(u8 *param,u8 len);
void halToSystem_SetRealCarMode(u8 *pBuf,u8 len);


void Radar_Visible(bool b);

void halToSystem_NaviMixLowSwitch_Status(u8 p);

//AmbientLed2017017
void Get_AmbientLed_InitState(u8 param);
void Get_AmbientLed_SwitchState(u8 param);
void Get_AmbientLed_Dimming_Value(u8 param);
void Get_AmbientLed_RGB_Value(u8 *param,u8 uLen);

void halToSystem_Screen_Brightness(u8 u8_Param);
void HalToSystem_ShowDayOrNightMode_Message(u8 Param);
void halToSystem_BatteryVolt_AnomalyMonitoring(u8 p);

void HalToSystem_AutoAdjustmentSwitchOfScreenBrightnessStatus(u8 p);

void halToSystem_Radar_Info_L(u8* pBuf);
void halToSystem_Radar_Info_LL(u8* pBuf);
void halToSystem_Radar_Info_R(u8* pBuf);
void halToSystem_Radar_Info_RR(u8* pBuf);
void halToSystem_BarCode(u8 *pBuf,u8 len);
void halToSystem_LCDBrightness_Value(u8 Param);
void halToSystem_LCDBrightness_OnOrOff(u8 param);

#endif
