#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleParamResponse.h"
#include "param.h"
#include "halRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "timer_interface.h"

void setDefaultParamters(void){
}

void moduleParameterInit(void){
}

void moduleParameterDeInit(void){

}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		default:break;
	}
}
void moduleParameterReInit(void)
{
	LOGD("&&&&&&&&&&&&&&&&& AC moduleParameterReInit");
}


int module_extendInterface(char *buffer, int len)
{
   char extenCmd = buffer[0];
   char extenParam = buffer[1];
   LOGD("********************AC module_extendInterface:%x %x",extenCmd,extenParam);
   switch(extenCmd)
   	{
	case 0x2C: //ACC Off Or Reset Or Default
		{
			if(extenParam == 0x00) //Acc Off
			{
				AirconditionModule_Process_AccOff();
				publicAcSetDefaultParam();
			}
			else if(extenParam == 0x01)
			{
				AirconditionModule_Process_Reset();
			}
			else if(extenParam == 0x02)
			{
				AirconditionModule_Process_ResetDefault();
			}
		}
		break;
	case 0x2D: //ACC On
		{
			ACModule_SetDefaultParam();
			otherModule_InitACData();
			AirconditionMoudule_Process_AccOn();
		}
		break;
	case 0xFD:
		{
			//initTimerCenter(&TimerHandlerCenter);
			//ACModule_SetDefaultParam();
			//publicAcSetDefaultParam();
			acToHal_Init();
		}
		break;
	default:break;
   	}
   	
   return 0;
}

void  AirconditionModule_Process_AccOff()
{
}
void  AirconditionMoudule_Process_AccOn()
{
	pLocalParam->bACAccOn=true;
}
void  AirconditionModule_Process_Reset()
{
}
void  AirconditionModule_Process_ResetDefault()
{
}

void ACModule_SetDefaultParam()
{
	pLocalParam->bACAccOn=false;

	pLocalParam->ucToyotaSpeed=0xFF;
	pLocalParam->uToyotaAuto_State=0xFF;
	pLocalParam->ucToyotaAOrCState=0xFF;
	pLocalParam->uToyotaAcSwitchPos=0xFF;
	pLocalParam->usToyotaLeftTempValue=0xFF;
	pLocalParam->usToyotaRightTempValue=0xFF;
	pLocalParam->uToyotaRearWindow_heatState=0XFF;
	pLocalParam->usToyotaLeftTempOSD=0xFF;
	pLocalParam->usToyotaRightTempOSD=0xFF;

	
	pLocalParam->fks_uinnerLoopState=0xFF;
	pLocalParam->fks_uMaxUpState=0xFF;
	pLocalParam->fks_uAutoState=0xFF;
	pLocalParam->fks_uAcState=0xFF;
	pLocalParam->fks_uAcSwitch=0xFF;
	pLocalParam->fks_uDown=0xFF;
	pLocalParam->fks_uUp=0xFF;
	pLocalParam->fks_uFront=0xFF;
	pLocalParam->fks_uWindSpeed=0xFF;
	pLocalParam->fks_uMaxAcState=0xFF;
	pLocalParam->fks_fLeftTemperature=0xFF;
	pLocalParam->fks_fRightTemperature=0xFF;

	pLocalParam->SiYu_uWindSpeed = 0xFF;
	pLocalParam->SiYu_uRear = 0xFF;
	pLocalParam->SiYu_uAcSwitch = 0xFF;
	pLocalParam->SiYu_uLoopState = 0xFF ;

	int nInValidValue = 0xFF;
	//BYD
	pLocalParam->e_byd_ac_cold_mode = AC_COLD_MODE_UNKNOW;
	pLocalParam->e_byd_ac_rear_window_heat_mode = AC_REAR_WINDOW_HEAT_MODE_UNKNOW;
	pLocalParam->e_byd_ac_wind_to_window_mode = AC_WIND_TO_WINDOW_MODE_UNKNOW;
	pLocalParam->e_byd_ac_out_recycle_mode = AC_OUT_RECYCLE_MODE_UNKNOW;
	pLocalParam->e_byd_ac_ac_mode = AC_AC_MODE_UNKNOW;
	pLocalParam->e_byd_ac_auto_mode = AC_AUTO_MODE_UNKNOW;
	pLocalParam->e_byd_ac_wind_face = AC_WIND_FACE_UNKNOW;
	pLocalParam->e_byd_ac_ctrl_mode = AC_CTRL_MODE_UNKNOW;


	pLocalParam->u8_byd_wind_level = nInValidValue;
	pLocalParam->u8_byd_degree_left = nInValidValue;
	pLocalParam->u8_byd_degree_right = nInValidValue;
	pLocalParam->s16_byd_degree_out = nInValidValue;
	pLocalParam->bACCanShow = false;
	//GOLF
	pLocalParam->e_golf_ac_cold_mode = AC_COLD_MODE_UNKNOW;
	pLocalParam->e_golf_ac_ac_mode = AC_AC_MODE_UNKNOW;
	pLocalParam->e_golf_ac_auto_mode = AC_AUTO_MODE_UNKNOW;
	pLocalParam->e_golf_ac_ctrl_mode = AC_CTRL_MODE_UNKNOW;
	pLocalParam->e_golf_ac_wind_to_window_mode = AC_WIND_TO_WINDOW_MODE_UNKNOW;
	pLocalParam->e_golf_ac_wind_to_face_mode = AC_WIND_TO_FACE_MODE_UNKNOW;
	pLocalParam->e_golf_ac_wind_to_feet_mode = AC_WIND_TO_FEET_MODE_UNKNOW;
	pLocalParam->e_golf_ac_degree_unit = AC_DEGREE_UNIT_UNKNOW;
	pLocalParam->u8_golf_seat_degree_left = nInValidValue;
	pLocalParam->u8_golf_seat_degree_right = nInValidValue;
	pLocalParam->u8_golf_degree_left = nInValidValue;
	pLocalParam->u8_golf_degree_right = nInValidValue;
	pLocalParam->u8_golf_wind_level = nInValidValue;
	pLocalParam->golf_timer_state= false;

	//CRV

	pLocalParam->e_crv_ac_cold_mode = AC_COLD_MODE_UNKNOW;
	pLocalParam->e_crv_ac_rear_window_heat_mode = AC_REAR_WINDOW_HEAT_MODE_UNKNOW;
	pLocalParam->e_crv_ac_out_recycle_mode = AC_OUT_RECYCLE_MODE_UNKNOW;
	pLocalParam->e_crv_ac_ac_mode= AC_AC_MODE_UNKNOW;
	pLocalParam->e_crv_ac_auto_mode = AC_AUTO_MODE_UNKNOW;
	pLocalParam->e_crv_ac_wind_face = AC_WIND_FACE_UNKNOW;
	pLocalParam->e_crv_ac_ctrl_mode = AC_CTRL_MODE_UNKNOW;
	pLocalParam->u8_crv_wind_level = nInValidValue;
	pLocalParam->u8_crv_degree_left = nInValidValue;
	pLocalParam->u8_crv_degree_right = nInValidValue;
	//////////////////////////////////////////////////////////////////////////////////////////
}
void publicAcSetDefaultParam()
{
	//Public Ac
	pLocalParam->acWindMode = 0xFF;
	pLocalParam->acSwitchStatus = 0xFF;
	pLocalParam->acMaxSwitchStatus = 0xFF;
	pLocalParam->acAUTOSwitchStatus = 0xFF;
	pLocalParam->acRMistRemovalStatus = 0xFF;
	pLocalParam->acFMistRemovalStatus = 0xFF;
	pLocalParam->acFrontWindowBlowMaxStatus = 0xFF;
	pLocalParam->acLoopMode = 0xFF;
	pLocalParam->acSYNCStatus = 0xFF;
	pLocalParam->acWindSpeed = 0xFF;
	pLocalParam->acMaxWindSpeed = 0xFF;
	pLocalParam->acMinWindSpeed = 0xFF;
	pLocalParam->acTempL = 0xFFFF;
	pLocalParam->acTempR = 0xFFFF;
	pLocalParam->acMaxTemp = 0xFFFF;
	pLocalParam->acMinTemp = 0xFFFF;
	pLocalParam->AorCSwitchStatus = 0xFF;
	pLocalParam->acHeatSeatStatusR = 0xFF;
	pLocalParam->acHeatSeatStatusL = 0xFF;
	pLocalParam->acHeatSeatGradeR = 0xFF;
	pLocalParam->acHeatSeatGradeL = 0xFF;
	pLocalParam->acTempDataDigits = 0xFF;
	pLocalParam->acTempDataUnit = 0xFF;

	//RearAc
	pLocalParam->RearAcSwitchStatus = 0xFF;
	pLocalParam->RearAcWindSpeed = 0xFF;

	pLocalParam->RearAcMinTempLevel = 0xFF;
	pLocalParam->RearAcMaxTempLevel = 0xFF;
	pLocalParam->RearAcTempValue = 0xFF;
			
	pLocalParam->RearAcMaxWindSpeed = 0xFF;
	pLocalParam->RearAcMinWindSpeed = 0xFF;
	pLocalParam->RearAcControlLockStatus = 0xFF;
	
	pLocalParam->RearAcAutoStatus = 0xFF;
	pLocalParam->RearAcMinTempV = 0xFFFF;
	pLocalParam->RearAcMaxTempV = 0xFFFF;
	pLocalParam->RearAcTempDataDigits = 0xFF;
	pLocalParam->RearAcTempDataUnit = 0xFF;
	pLocalParam->RearAcTempV = 0xFFFF;
}


