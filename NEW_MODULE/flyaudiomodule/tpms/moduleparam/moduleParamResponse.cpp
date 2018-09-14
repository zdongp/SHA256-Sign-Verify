#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleParamResponse.h"
#include "param.h"
#include "halRequestFunction.h"
#include "timer_interface.h"
#include "appResponseFunction.h"
#include "controlID.h"

void moduleParameterInit(void){

	LOGD("---------------Tpms--------moduleParameterInit---------");
	
	
}


void moduleParameterDeInit(void){
	saveParameter();
}
void TpmsModule_SetDefaultParam()
{

	LOGD("--------Tpms--------SetDefaultParam-----------------");
    localParam.u32_tpms_max_alarm_temperature = TPMS_DEFAULT_MAX_ALARM_TEMPERATURE;
    localParam.u32_tpms_max_alarm_tire_pressure  = TPMS_DEFAULT_MAX_ALARM_TIRE_PRESSURE;
    localParam.u32_tpms_min_alarm_tire_pressure = TPMS_DEFAULT_MIN_ALARM_TIRE_PRESSURE;
    localParam.u8_tpms_termerature_uint = Temp_Uint_C;
    localParam.u8_tpms_tire_pressure_uint = Pressure_PSI; 
    memset(localParam.tpms_data, 0, sizeof(TPMS_Data)*4);
    localParam.u8_tpms_alarm_type = Alarm_Close;
    localParam.u8_tpms_clear_data = emClearData_NO; 

	localParam.u8_tpms_bInitState = false;
	pLocalParam->u8_tpms_pair = 0;    
	localParam.u8_CurAlarmValue = 0;
	localParam.bCanRing = true;
	
	Clean_TireData(emTire_FL);
 	Clean_TireData(emTire_FR);
	Clean_TireData(emTire_RL);
 	Clean_TireData(emTire_RR);
	
	localParam.curTire=emTire_NONE;
	localParam.swapTire=emTire_NONE;
	
	localParam.tireSignIDArr[0]=CONTROLID_TPMS_FL_SIGN;
	localParam.tireSignIDArr[1]=CONTROLID_TPMS_FR_SIGN;
	localParam.tireSignIDArr[2]=CONTROLID_TPMS_RL_SIGN;
	localParam.tireSignIDArr[3]=CONTROLID_TPMS_RR_SIGN;
	
	localParam.swapbtn = true;
	localParam.ucFLAlarmstate = 0; 
	localParam.ucFRAlarmstate = 0;
	localParam.ucRLAlarmstate = 0;
	localParam.ucRRAlarmstate = 0;

	localParam.curAlarmTextID = 0;
	localParam.vecAlarmText.clear();

	localParam.curAlarmRingID = 0;
	localParam.vecAlarmRing.clear();

	localParam.ucTpmsPairStatus=0;
	LOGD("----------TpmsModule_SetDefaultParam------pLocalParam->u8_tpms_pair:%x", pLocalParam->u8_tpms_pair);
	pLocalParam->publicTp_data[0] = 0xFFFF;
	pLocalParam->publicTp_data[1] = 0xFFFF;
	pLocalParam->publicTp_data[2] = 0xFFFF;
	pLocalParam->publicTp_data[3] = 0xFFFF;
	
	pLocalParam->publicTm_data[0] = 0xFFFF;
	pLocalParam->publicTm_data[1] = 0xFFFF;
	pLocalParam->publicTm_data[2] = 0xFFFF;
	pLocalParam->publicTm_data[3] = 0xFFFF;
}

void TpmsModule_InitByConfig()
{

	LOGD("-----Tpms-------InitByConfig----------------");
	
	TpmsModule_SetDefaultParam();
    readParameter();
    tpmsToUI_Load();
    tpmsToHal_Init(0x01);
	
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
	    case PAIR_STATUS:
	        *param = localParam.ucTpmsPairStatus;
	        *paramLen = 1;
	    break;
		default:break;
	}
}

void moduleParameterReInit(void){
	 LOGD("&&&&&&&&&&&&&&&&&&&& tpms moduleParameterReInit");
}
int module_extendInterface(char *buffer, int len){
	LOGD("*****************tpms module_extendInterface:%x,%x",buffer[0],buffer[1]);
	u8 ucSystemCmd = buffer[0];
	u8 ucSystemParam = buffer[1];
	switch(ucSystemCmd){
		case 0x2c:
			if(0x00 == ucSystemParam)      //ACC off
				{
					Get_Acc_off();
				}
			else if(0x01 == ucSystemParam) //Restart
				{
					Set_SaveDataToRestart();
				}
			else if(0x02 == ucSystemParam) //FactoryDefaults
				{
					Set_RestoreToFactoryDefaults();
				}
			break;
		case 0x2d:
			if(0x00 == ucSystemParam)     //ACC ON
				Get_Acc_on();
			break;
		case 0xFD:
			{
				TpmsModule_InitByConfig();
				//initTimerCenter(&TimerHandlerCenter);
			}
			break;
		default:break;
	}
	
	return 0;
}

void Set_SaveDataToRestart(){
	saveParameter();
}

void Set_RestoreToFactoryDefaults(){
	TpmsModule_SetDefaultParam();
	saveParameter();
}

void Get_Acc_off(){
	saveParameter();
}

void Get_Acc_on(){
	
	TpmsModule_SetDefaultParam();
	readParameter();
	TpmsModule_InitByConfig();
	
}



