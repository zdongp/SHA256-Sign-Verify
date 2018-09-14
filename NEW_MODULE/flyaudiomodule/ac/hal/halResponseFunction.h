#ifndef __HAL_RESPONSE_COMMAND_H__
#define __HAL_RESPONSE_COMMAND_H__

#include "global.h"
#include "messageQueue.h"
#include "param.h"

int analyseHalMessage_AIRCONDITION(char msgResCmd, unsigned char *param, unsigned char len);


u8* CalcTemperature(unsigned char *buf);
int CompData(unsigned char *buf);

void halToAIRCondition_RightTemperature(unsigned char *buf);

void halToAIRCondition_LeftTemperature(unsigned char *buf);
void halToAIRCondition_AcMaxState(unsigned char ucAcBuf);
void halToAIRCondition_AcState(unsigned char* ucAcbuf);
void halToAIRCondition_AcAutoState(unsigned char ucAcBuf);
void halToAIRCondition_AcDualState(unsigned char ucAcBuf);
void halToAIRCondition_AcModeUpState(unsigned char ucAcBuf);
void halToAIRCondition_AcModeFrontState(unsigned char ucAcBuf);
void halToAIRCondition_AcModeDownState(unsigned char ucAcBuf);
void halToAIRCondition_Speed(unsigned char *buf);
void halToAIRCondition_AcVaneState(unsigned char ucAcBuf);
void halToAIRCondition_AcModeRearState(unsigned char ucAcBuf);
void IsOffState(int bOffState);
void halToAIRCondition_AcOffState(unsigned char ucAcBuf);
void AcOFFStatusChange(int bOffStatus);

//ADD     :2012-06-22
void halToAC_Speed(char cmd, unsigned char speed);
void TellToOSD();
void fks_TellToOSD();

void toyota_TellToOSD();
void SiYu_TellToOSD();

int byd_ac_degree2osdDegree(int d);
void byd_ac_msg_to_osd(E_AC_COLD_MODE acMode, int leftDegree, int rightDegree, u8 windSpeed, E_AC_AC_MODE acDoor);

int golf_ac_degree2osdDegree(int d);
int golf_ac_degree2osdDegreeByUnit(int d,E_AC_DEGREE_UNIT degreeUnit);
void golf_ac_msg_to_osd(E_AC_COLD_MODE acMode, E_AC_DEGREE_UNIT degreeUnit, int  leftDegree, int rightDegree, u8 windSpeed, E_AC_AC_MODE acDoor);

int crv_ac_degree2osdDegree(int d);
void crv_ac_msg_to_osd(u8 acMode, int  leftDegree, int rightDegree, u8 windSpeed, E_AC_AC_MODE acDoor);

//ADD 2014-07-23
u16 convertTemperatureToT123(u16 tempValue);
u8 convertSpeedTo123(u8 speed);
u16 convertToyotaTemperatureToT123(u16 tempValue);

/********Mistra funtion*********/
void halToAC_Mistra_Speed(u8 speed);
void halToAC_Mistra_RightTemperature(char resCmd, u16 temp_value);
void halToAC_Mistra_LeftTemperature(char resCmd, u16 temp_value);
void mistra_CalculateTemperature(u16 temperature_value, char *temp_str);

void halToAc_AcSeatHeatersRight(unsigned char status);
void halToAc_AcSeatHeatersLeft(unsigned char status);
void halToAc_AcRearStatus(unsigned char status);
void halToAc_AcDualStatus(unsigned char status);
void halToAc_AcAutoStatus(unsigned char status);
void halToAC_RightTemperature(char resCmd, u16 temp_value);
void halToAC_LeftTemperature(char resCmd, u16 temp_value);
void halToAc_AcOFFStatus(unsigned char status);
void mistraToOSD();
u8 MistraConvertSpeedTo123(u8 speed);
u16 MistraConvertTemperatureToT123(u16 tempValue);

void halToAc_PublicAcWindDirection(u8 p);
void halToAc_ACRefrigeration(u8 param);
void halToAc_ACmaxRefrigeration(u8 param);
void halToAc_PublicAcAutoSwitch(u8 p);
void halToAc_RMistRemovalStatus(u8 p);
void halToAc_LoopModeStatus(u8 p);
void halToAc_AcSyncSwitch(u8 param);
void halToAC_Public_Ac_WindSpeed(u8 speed);
void halToAC_Public_Ac_LeftTemperature(int temp_value);
void halToAC_Public_Ac_RightTemperature(int temp_value);
void halToPublic_Ac_Switch_status(u8 param);
void publicAcInfoToOSD(u16 LeftTemp,u16 RightTemp,u8 uSpeed,u8 uACstate);
void halToAc_FMistRemovalStatus(u8 p);
void halToAc_FrontWindowBlowMaxStatus(u8 p);

void TEMP_R(float f,int sf,u8 Tag,u8 unit);
void TEMP_L(float f,int sf,u8 Tag,u8 unit);
void DisplayingUI_WindSpeed(u8 s);
void halToAc_ShowAcWindDirection(u8 param);
void halToAc_ShowAcLoopMode(u8 param);
void halToAc_PublicAcSyncSwitch(u8 param);
void halToAc_PublicAcShowBodyButton(u8 p,u8 param);
void initAcPageAfterAcOff();
void initAcPageAfterAcOn();
void halToAc_PublicAcShowHeatSeatStatus(u8 LorR,u8 param);
void halToAc_PublicAcShowHeatSeatGrade(u8 *buf,u8 len);

void halToPublic_RearAc_Switch_status(u8 param);
void halToAC_Public_RearAc_TempValue(u8 p);
void halToAC_Public_RearAc_WindSpeed(u8 p);
void halToPublic_RearAc_ControlLock_status(u8 p);
void DisplayingUI_RearAcWindSpeed(u8 s);
void halToPublic_RearAc_Auto_status(u8 p);

void halToAC_Public_RearAc_Temperature(int temp_value);
void TEMP_Rear(float f,int sf,u8 Tag,u8 unit);

#endif
