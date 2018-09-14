#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestFunction.h"




void appToaircondition_Parameter(unsigned char *param, unsigned char paramLen){
	switch(param[0]){
		default:
			break;			
	}
}

void appToaircondition_EnterMainPage_MouseUp(void){
	//airconditionToModule_NotifySystem_jumpPage(PAGE_MENU);//test
	airconditionToModule_NotifySystem_jumpPage(PAGE_AIRCONDITION);

}

void appToaircondition_BackPage_MouseUp()
{
	airconditionToModule_NotifySystem_JumpPrePage();
}


void appToaircondition_ReturnMenuPage_MouseUp(void){
	//airconditionToModule_NotifyOsd_DisplayOSDACInfor(0x2328,0x2321,0x10,0);//test
	airconditionToModule_NotifySystem_jumpPage(PAGE_MENU);
}

void setWindSpeedAdd()
{
	if(pLocalParam->acWindSpeed  == pLocalParam->acMaxWindSpeed || pLocalParam->acWindSpeed == 0xFF)
		return;
	u8 param = pLocalParam->acWindSpeed + 1;
	setAcwindSpeed(param,pLocalParam->acMinWindSpeed,pLocalParam->acMaxWindSpeed);
}
void setPublicWindSpeedAddOrDec(u8 param)
{
	setpublicAcwindSpeed(param);
}

void setWindSpeedLow()
{
	if(pLocalParam->acWindSpeed  == pLocalParam->acMinWindSpeed || pLocalParam->acWindSpeed == 0xFF)
		return;
	u8 param = pLocalParam->acWindSpeed - 1;
	setAcwindSpeed(param,pLocalParam->acMinWindSpeed,pLocalParam->acMaxWindSpeed);
}

void setLeftTemperatureAdd()
{
	if(pLocalParam->acTempL == pLocalParam->acMaxTemp || pLocalParam->acTempL == 0xFFFF)
		return;
	int param = 0;
	param = pLocalParam->acTempL + 100;
	setAcTemperature(param,pLocalParam->acTempR,pLocalParam->acMinTemp,pLocalParam->acMaxTemp,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
}
void setLeftTemperatureAddOrLow(u8 RorL,u8 param)
{
	setPublicAcTemperature(RorL,param);
}

void setLeftTemperatureLow()
{
	if(pLocalParam->acTempL == pLocalParam->acMinTemp || pLocalParam->acTempL == 0xFFFF)
		return;
	int param = 0;
	param = pLocalParam->acTempL - 100;
	setAcTemperature(param,pLocalParam->acTempR,pLocalParam->acMinTemp,pLocalParam->acMaxTemp,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
}

void setRightTemperatureAdd()
{
	if(pLocalParam->acTempR == pLocalParam->acMaxTemp|| pLocalParam->acTempR == 0xFFFF)
		return;
	int param = 0;
	param = pLocalParam->acTempR + 100;
	setAcTemperature(pLocalParam->acTempL,param,pLocalParam->acMinTemp,pLocalParam->acMaxTemp,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
}

void setRightTemperatureLow()
{
	if(pLocalParam->acTempR == pLocalParam->acMinTemp|| pLocalParam->acTempR == 0xFFFF)
		return;
	int param = 0;
	param = pLocalParam->acTempR - 100;
	setAcTemperature(pLocalParam->acTempL,param,pLocalParam->acMinTemp,pLocalParam->acMaxTemp,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
}

void setACSwitchOff_ON()
{
	if(pLocalParam->AorCSwitchStatus == 0x01)
		setAcAorCSwitch(0x00);
	else 
		setAcAorCSwitch(0x01);
}

void setMaxACOff_ON()
{
	if(pLocalParam->acMaxSwitchStatus == 0x01)
		setAcAorCMaxSwitch(0x00);
	else 
		setAcAorCMaxSwitch(0x01);
}

void setAutoSwitchStatus()
{
	if(pLocalParam->acAUTOSwitchStatus == 0x01)
		setAcAutoSwitch(0x00);
	else
		setAcAutoSwitch(0x01);
}
void setLoopModeStatus()
{
	if(pLocalParam->acLoopMode == 0x01)
		setAcLoopMode(0x00);
	else 
		setAcLoopMode(0x01);
}

void setDualStatus()
{
	if(pLocalParam->acSYNCStatus == 0x01)
		setAcDualSwitch(0x00);
	else 
		setAcDualSwitch(0x01);
}

void setAcSwitchStatus()
{
	LOGD("%s ----- %x",__FUNCTION__,pLocalParam->acSwitchStatus);
	if(pLocalParam->acSwitchStatus == 0x01)
		setAcSwitchToHal(0x00);
	else 
		setAcSwitchToHal(0x01);
}

void setFWindowHeatingStates()
{
	if(pLocalParam->acFMistRemovalStatus  == 0x01)
		setAcFWindowHeating(0x00);
	else
		setAcFWindowHeating(0x01);
}

void setRearWindowHeatingStates()
{
	if(pLocalParam->acRMistRemovalStatus  == 0x01)
		setAcRearWindowHeating(0x00);
	else 
		setAcRearWindowHeating(0x01);
}

void setWindModeStates()
{
	if(pLocalParam->acWindMode  == 0x00)
		setAcwindMode(0x02);
	else if(pLocalParam->acWindMode  == 0x01)
		setAcwindMode(0x04);
	else if(pLocalParam->acWindMode  == 0x02)
		setAcwindMode(0x01);
	else if(pLocalParam->acWindMode  == 0x04)
		setAcwindMode(0x00);
	else 
		setAcwindMode(0x00);
}
void setPublicWindModeStates()
{
	setPublicAcwindMode();
}
void setPublicWindModeStatesForBody(u8 param)
{
	if(param == 0 || param == 1 || param == 2)	
		setPublicAcwindModeForBody(param + 1);
}

void setWindModeStatus(u8 param)
{
	setAcwindMode(param);
}
void setLoopModeOfDirect(u8 param)
{
	setAcLoopMode(param);
}

void setHeatSeatStatus_L()
{
	if(pLocalParam->acHeatSeatStatusL == 0x01)
		setAcHeatSeatSwitch(0x00,0x00);
	else 
		setAcHeatSeatSwitch(0x00,0x01);
}

void setHeatSeatStatus_R()
{
	if(pLocalParam->acHeatSeatStatusR == 0x01)
		setAcHeatSeatSwitch(0x01,0x00);
	else 
		setAcHeatSeatSwitch(0x01,0x01);
}


void setAcHeatSeatGrade_L()
{
	setAcHeatSeatGrade(0x00,0x01);
}

void setAcHeatSeatGrade_R()
{
	setAcHeatSeatGrade(0x01,0x01);
}

void setFrontWindowBlowMax()
{
	if(pLocalParam->acFrontWindowBlowMaxStatus == 0x01)
		setAcFrontWindowBlowMax(0x00);
	else
		setAcFrontWindowBlowMax(0x01);
}

void setRearAirconditionSwtich()
{
	if(pLocalParam->RearAcSwitchStatus == 0x01)
		setRearAcSwitchToHal(0x00);
	else 
		setRearAcSwitchToHal(0x01);
}

void setRearAirconditionControlLock()
{
	if(pLocalParam->RearAcControlLockStatus == 0x01)
		setRearAcControlLockToHal(0x00);
	else 
		setRearAcControlLockToHal(0x01);
}

void setRearAirconditionWindSpeedControl(u8 p)
{
	if(p == 0)
		setRearAcWindSpeed(0x01);
	else if(p == 1)
		setRearAcWindSpeed(0x02);
}

void setRearAirconditionTempeartrueControl(u8 p)
{
	if(p == 0)
		setRearAcTempeartrueControl(0x01);
	else if(p == 1)
		setRearAcTempeartrueControl(0x02);
}

void DisplayRearAcSwitchStatus(u8 s)
{
	setDigitalData(CONTROLID_REAR_AIRCONDITION_SWITCH_BUTTON, s);
}

void DisplayUI_RearAcTempRank(u8 s)
{
	#define AC_SPEED_BUFFER_MAX 16 
	char TempStr[AC_SPEED_BUFFER_MAX];
	unicode16_t uTempStr[AC_SPEED_BUFFER_MAX*2];

	if(s  == 0xFF || s == 0 || s == 0xF9)
	{
		sprintf(TempStr, "%s", " ");
		s = 0;
	}
	else if(s  == 0xF7)
	{ 
		sprintf(TempStr, "%s", "Min");
		s = pLocalParam->RearAcMinTempLevel;
	}
	else if(s  == 0xF8)
	{ 
		sprintf(TempStr, "%s", "Max");
		s = pLocalParam->RearAcMaxTempLevel;
	}
	else if(s == 0xFA)
	{ 
		memcpy(TempStr, "%d", pLocalParam->RearAcTempValue);
		s = pLocalParam->RearAcTempValue;
	}
	else
	{ 
		sprintf(TempStr, "%d", s);
	}

	LOGD("[%s] s:%x",__FUNCTION__,s);
	int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
	if(s == 0xFA)
	{
	}
	else
	{
		setAnalogData(CONTROLID_REAR_AIRCONDITION_TEMPERATRUE_SCROLL_BAR, s);
	}
}

void DisplayRearAcControlLockStatus(u8 s)
{
	setDigitalData(CONTROLID_REAR_AIRCONDITION_CONTROL_LOCK_BUTTON, s);
}

void DisplayRearAcAutoStatus(u8 s)
{
	setDigitalData(CONTROLID_AIRCONDITION_AUTO_SWITCH_BACK_ROW, s);
}

void appToaircondition_EnterAcSetPage_MouseUp(void){
	airconditionToModule_NotifySystem_jumpPage(PAGE_AIRCONDITION_SET);
}

void appToaircondition_Set_Page_Back_MouseUp()
{
	u16 wPageId = 0;
	u8 len = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&wPageId, &len);
	if(PAGE_AIRCONDITION == wPageId)
		return;
	airconditionToModule_NotifySystem_JumpPrePage();
}

void appToaircondition_AutoSwitch_BackRow_MouseUp()
{
	if(pLocalParam->RearAcAutoStatus == 0x01)
		setAcAutoSwitchBackRow(0x00);
	else 
		setAcAutoSwitchBackRow(0x01);
}