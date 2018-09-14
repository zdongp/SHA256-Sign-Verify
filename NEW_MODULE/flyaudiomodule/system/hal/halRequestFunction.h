#ifndef __HAL_REQUEST_COMMAND_SYSTEM_H__
#define __HAL_REQUEST_COMMAND_SYSTEM_H__

#include "param.h"

#define SYSTEMTOHAL_SIMKEY_STEELWHEEL_INC			0x00
#define SYSTEMTOHAL_SIMKEY_STEELWHEEL_DEC			0x01
#define SYSTEMTOHAL_SIMKEY_RADIOCOUNTRY_INC			0x02
#define SYSTEMTOHAL_SIMKEY_RADIOCOUNTRY_DEC			0x03
#define SYSTEMTOHAL_SIMKEY_RESET					0x04
#define SYSTEMTOHAL_SIMKEY_DEBUG					0x05
#define SYSTEMTOHAL_SIMKEY_DVDREGION_INC			0x06
#define SYSTEMTOHAL_SIMKEY_DVDREGION_DEC			0x07

#define SYSTEMTOHAL_CARMODEL_INC					0x09
#define SYSTEMTOHAL_CARMODEL_DEC					0x0a
#define SYSTEMTOHAL_CARMODEL_OK						0x0b


#define SYSTEMTOHAL_BACKCARDETECT_DISABLE			0x00
#define SYSTEMTOHAL_BACKCARDETECT_ENABLE			0x01



#define SYSTEMTOHAL_LIGHTDETECT_DISABLE			0x00
#define SYSTEMTOHAL_LIGHTDETECT_ENABLE			0x01

#define SYSTEMTOHAL_DAYNIGHT_DAY			0x00
#define SYSTEMTOHAL_DAYNIGHT_NIGHT			0x01

#define SYSTEMTOHAL_EXTAMPLIFIER_NONE		0x00
#define SYSTEMTOHAL_EXTAMPLIFIER_EXT		0x01

#define SYSTEMTOHAL_LCDBRIGHTNESS_BLACK		0x00
#define SYSTEMTOHAL_LCDBRIGHTNESS_LOW		0x01
#define SYSTEMTOHAL_LCDBRIGHTNESS_MIDDLE	0x02
#define SYSTEMTOHAL_LCDBRIGHTNESS_HIGH		0x03
#define SYSTEMTOHAL_LCDBRIGHTNESS_HIGH_HIGH	0x04

#define SYSTEMTOHAL_STEELSPECIFICFUNC_OFF		0x00
#define SYSTEMTOHAL_STEELSPECIFICFUNC_ON		0x01

#define SYSTEMTOHAL_RADIOREGION_ID_CHINA		0x00
#define SYSTEMTOHAL_RADIOREGION_ID_USA			0x01
#define SYSTEMTOHAL_RADIOREGION_ID_SAMER1		0x02
#define SYSTEMTOHAL_RADIOREGION_ID_SAMER2		0x03
#define SYSTEMTOHAL_RADIOREGION_ID_KOREA		0x04
#define SYSTEMTOHAL_RADIOREGION_ID_THAILAND		0x05

#define SYSTEMTOHAL_CUSTOMSTEELPANEL_OFF		0x00
#define SYSTEMTOHAL_CUSTOMSTEELPANEL_ON			0x01

#define SYSTEMTOHAL_LEARNSTEELPANEL_MODE		0x00
#define SYSTEMTOHAL_LEARNSTEELPANEL_SEEK_INC	0x01
#define SYSTEMTOHAL_LEARNSTEELPANEL_SEEK_DEC	0x02
#define SYSTEMTOHAL_LEARNSTEELPANEL_MUTE		0x03
#define SYSTEMTOHAL_LEARNSTEELPANEL_VOL_INC		0x04
#define SYSTEMTOHAL_LEARNSTEELPANEL_VOL_DEC		0x05

#define SYSTEMTOHAL_CLEARSTEELPANEL_MODE		0x00
#define SYSTEMTOHAL_CLEARSTEELPANEL_SEEK_INC	0x01
#define SYSTEMTOHAL_CLEARSTEELPANEL_SEEK_DEC	0x02
#define SYSTEMTOHAL_CLEARSTEELPANEL_MUTE		0x03
#define SYSTEMTOHAL_CLEARSTEELPANEL_VOL_INC		0x04
#define SYSTEMTOHAL_CLEARSTEELPANEL_VOL_DEC		0x05

#define SYSTEMTOHAL_ACCOFF_MSG_RECEIVE			0x00
#define SYSTEMTOHAL_ACCOFF_MSG_FINISHED			0x01



void systemToHal_Init(char param);
void systemToHal_SimulateKey(unsigned char key);
void systemToHal_BackCarDetected(char enable);
//ZHQ
//void systemToHal_DNVDetected(char enable);

void systemToHal_LightDetected(char enable);
void systemToHal_DayOrNight(char night);
void systemToHal_SetExternalAmplifier(char exist);
void systemToHal_SetLCDBrightness(unsigned char level);
void systemToHal_KeyLedBrightness(unsigned char brightness);
void systemToHal_Set_LCDBrightness_Rank(unsigned char level);

void systemToHal_WheelPanelSpecificFuncSwitch(char onOff);
void systemToHal_SetRadioRegion(unsigned char regionId);
void systemToHal_FactorySetting(void);
void systemToHal_EnterDemoMode(char mode);
void systemToHal_SetUserWheelPanelData(char onOff);
void systemToHal_LearnWheelPanelData(unsigned char key);
void systemToHal_CancalWheelPanelLearn(void);
void systemToHal_ClearWheelPanelData(unsigned char key);
void systemToHal_SetDVDRegionCode(unsigned char region);
void systemToHal_CheckAuxVideo(void);
void systemToHal_ReceivedACCOnMsg(void);
void systemToHal_DealACCOffMsg(char finished);
void systemToHal_SetAndroidKeyMessageDeliver(int enable);
void systemToHal_SetDebugKeyPanelType(unsigned char panelType);
void systemToHal_ClearWheelPanelData(unsigned char key);

void systemToHal_SetTVOrIpol(u8 cKey);
void systemToHal_NotifySIMPhoneStatus(char status);

/*******************************************************************************/
void systemToHal_Global_Init(char param);
void systemToHal_StandyState(u8 Param1,u8 Param2);
void systemToHal_SetDVROrTV(u8 cKey);

void systemToHal_Notify_PingLoop_NewStructure(u8 param);
void systemToHal_SetCarMode(u8* carMode,u8 len);

void systemToHal_SetFanMode(char param);
void systemToHal_SetCPU_PerformanceMode(u8 cmd);


void systemToHal_SetVoltageProtection(E_VOLTAGE_PROTECTION e);
void systemToHal_SetDenoiseMode(u8 cmd);
void systemToHal_BackcarVisionAngle(u8 param);

void setToHalBackCarMode(u8 p);
void systemToHal_SetSystemUpdate(void);

void systemToHal_SetBackcarTriggerType(E_SETUP_BACKCAR_TRIGGER e);//zhq add triggertype
void systemToHal_Notify_RemoteOnline_VoltageProtection(u8 param);
void systemToHal_InquireCurBrakeStatue(void);

void systemToHal_SetNaviMixLow(u8 p);
void systemToHal_AboutAmbientLedMsg(u8 *p,u8 nLen);
void systemToHal_SetScreenBrightnessValue(u8  buf);
void setSystemToHal_DayOrNight(u8 night);
void systemToRadioHal_SetRadioArea(u8 param);
void systemToHal_AutoAdjustmentSwitchOfScreenBrightness(u8 param);
void systemToHal_NotifyMicUsingState(u8 p);
void systemToHal_SetScreenBrightnessSpecificValue(u8 p);
void systemToHal_SetScreenOnOrOff(u8 p);
void systemToHal_SetSelectionCarTypeOption(u8 param);

#endif
