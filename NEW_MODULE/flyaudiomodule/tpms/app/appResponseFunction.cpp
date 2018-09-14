#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "stringID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"
#include "appResponseFunction.h"
extern "C"{
#include "unicodestring.h"
};
#include "halResponseFunction.h"
#include "timer_interface.h"


void appToTpms_Back_MouseUp(u32 funcID)
{

    switch(funcID)
    {
    case CONTROLID_TPMS_BACK:
		{
		tpmsToModule_NotifySystem_JumpPage(PAGE_MENU);
    	}
		break;
    case CONTROLID_TPMS_SET_BACK:
    case CONTROLID_TPMS_EXSET_BACK:
		tpmsToModule_NotifySystem_JumpPage(PAGE_TPMS);
		break;
    default:
	break;
    }
}


//Menu
void appToTpms_EnterTPMS_MouseUp()
{
	LOGD("[%s]",__FUNCTION__);
   	tpmsToModule_NotifySystem_JumpPage(PAGE_TPMS);
	//tpms_Temperature_Update(CONTROLID_TPMS_FL_TEMPERATURE,50);
	//tpms_TirePressure_Update(CONTROLID_TPMS_FL_TIRE_PRESSURE,100);
	/*int len = 10;
	u8 param0[2] = {0x00,0x00}; 
	u8 param1[2] = {0x01,0x01};
	u8 param2[2] = {0x02,75};
	u8 param3[2] = {0x03,30};
	analyseHalMessage_TPMS(0x20, param0, len);
	analyseHalMessage_TPMS(0x20, param1, len);
	analyseHalMessage_TPMS(0x20, param2, len);
	analyseHalMessage_TPMS(0x20, param3, len);

	u8 param4[2] = {0x00,0x00}; 
	u8 param5[2] = {0x01,0x01};
	u8 param6[2] = {0x02,80};
	u8 param7[2] = {0x03,50};
	analyseHalMessage_TPMS(0x21, param4, len);
	analyseHalMessage_TPMS(0x21, param5, len);
	analyseHalMessage_TPMS(0x21, param6, len);
	analyseHalMessage_TPMS(0x21, param7, len);
	
	
	u8 param8[2] = {0x00,0x00}; 
	u8 param9[2] = {0x01,0x01};
	u8 param10[2] = {0x02,85};
	u8 param11[2] = {0x03,70};
	analyseHalMessage_TPMS(0x22, param8, len);
	analyseHalMessage_TPMS(0x22, param9, len);
	analyseHalMessage_TPMS(0x22, param10, len);
	analyseHalMessage_TPMS(0x22, param11, len);
	

	u8 param12[2] = {0x00,0x00}; 
	u8 param13[2] = {0x01,0x01};
	u8 param14[2] = {0x02,90};
	u8 param15[2] = {0x03,90};
	analyseHalMessage_TPMS(0x23, param12, len);
	analyseHalMessage_TPMS(0x23, param13, len);
	analyseHalMessage_TPMS(0x23, param14, len);
	analyseHalMessage_TPMS(0x23, param15, len);*/

}

void appToTpms_SetUp_MouseUp()
{
    tpmsToModule_NotifySystem_JumpPage(PAGE_TPMS_SET);
	setAnalogData(CONTROLID_TPMS_SET_PREVPAGE,2);
	setControllable(CONTROLID_TPMS_SET_PREVPAGE,0);
}

void appToTpms_NextPage_MouseUp()
{
    tpmsToModule_NotifySystem_JumpPage(PAGE_TPMS_EXSET);
	setAnalogData(CONTROLID_TPMS_EXSET_NEXTPAGE,2);
	setControllable(CONTROLID_TPMS_EXSET_NEXTPAGE,0);
}

void appToTpms_Pair_MouseUp()
{

	LOGD("pLocalParam->u8_tpms_pair:%x", pLocalParam->u8_tpms_pair);
	
	if(pLocalParam->u8_tpms_pair == 0){

		tpmsToHal_PairMode(0x01);//start pair
		pLocalParam->u8_tpms_pair = 1;

	}
	else{
		tpmsToHal_PairMode(0x00);
		pLocalParam->u8_tpms_pair = 0;
	}

}

void appToTpms_MeterDigitalInfo_MouseUp()
{

}

void appToTpms_Copyright_MouseUp()
{
    tpmsToModule_NotifySystem_JumpPage(PAGE_COPYRIGHT);
}

void appToTpms_SetDefaultValue_MouseUp(u32 funcID)
{
    switch(funcID)
    {
    case CONTROLID_TPMS_SET_HIGHEST_TEM_ALARM_DEFAULT:
        {
	    tpms_Set_MaxAlarm_Temperature(TPMS_DEFAULT_MAX_ALARM_TEMPERATURE);
	    pLocalParam->u32_tpms_max_alarm_temperature = TPMS_DEFAULT_MAX_ALARM_TEMPERATURE;
	}
	break;
    case CONTROLID_TPMS_SET_HIGHEST_TIRE_PRESSURE_ALARM_DEFAULT:
        {
		tpms_Set_MaxAlarm_TirePressure(TPMS_DEFAULT_MAX_ALARM_TIRE_PRESSURE);
	    pLocalParam->u32_tpms_max_alarm_tire_pressure = TPMS_DEFAULT_MAX_ALARM_TIRE_PRESSURE;
	}
	break;
    case CONTROLID_TPMS_SET_LOWEST_TIRE_PRESSURE_ALARM_DEFAULT:
        {
	    tpms_Set_MinAlarm_TirePressure(TPMS_DEFAULT_MIN_ALARM_TIRE_PRESSURE);
	    pLocalParam->u32_tpms_min_alarm_tire_pressure = TPMS_DEFAULT_MIN_ALARM_TIRE_PRESSURE;
	}
	break;
    default:break;
    }
}


void appToTpms_RegulateAlarmValue(u32 funcID)
{
   switch(funcID)
   {
    case CONTROLID_TPMS_SET_HIGHEST_TEM_ALARM_UP:
		appToTpms_TopTemperature_Inc_MouseUp();
		break;
    case CONTROLID_TPMS_SET_HIGHEST_TEM_ALARM_DOWN:
		appToTpms_TopTemperature_Dec_MouseUp();
		break;
    case CONTROLID_TPMS_SET_HIGHEST_TIRE_PRESSURE_ALARM_UP:
		appToTpms_TopTirePressure_Inc_MouseUp();
		break;
    case CONTROLID_TPMS_SET_HIGHEST_TIRE_PRESSURE_ALARM_DOWN:
		appToTpms_TopTirePressure_Dec_MouseUp();
		break;
    case CONTROLID_TPMS_SET_LOWEST_TIRE_PRESSURE_ALARM_UP:
		appToTpms_LowTirePressure_Inc_MouseUp();
		break;
    case CONTROLID_TPMS_SET_LOWEST_TIRE_PRESSURE_ALARM_DOWN:
		appToTpms_LowTirePressure_Dec_MouseUp();
		break;
    default:break;
   }
}


void appToTpms_TopTemperature_Inc_MouseUp()
{
   pLocalParam->u32_tpms_max_alarm_temperature++;
   if(pLocalParam->u32_tpms_max_alarm_temperature>TPMS_MAX_TEMPERATURE_TOP)
   {
       pLocalParam->u32_tpms_max_alarm_temperature = TPMS_MAX_TEMPERATURE_TOP;
       return;
   }
   tpms_Set_MaxAlarm_Temperature(pLocalParam->u32_tpms_max_alarm_temperature);
}

void appToTpms_TopTemperature_Dec_MouseUp()
{
   pLocalParam->u32_tpms_max_alarm_temperature--;
   if(pLocalParam->u32_tpms_max_alarm_temperature < TPMS_MAX_TEMPERATURE_LOW)
   {
       pLocalParam->u32_tpms_max_alarm_temperature =TPMS_MAX_TEMPERATURE_LOW;
       return;
   }
   tpms_Set_MaxAlarm_Temperature(pLocalParam->u32_tpms_max_alarm_temperature);
}


void appToTpms_TopTirePressure_Inc_MouseUp()
{
   pLocalParam->u32_tpms_max_alarm_tire_pressure++;
   if(pLocalParam->u32_tpms_max_alarm_tire_pressure>TPMS_MAX_TIRE_PRESSURE_TOP)
   {
       pLocalParam->u32_tpms_max_alarm_tire_pressure = TPMS_MAX_TIRE_PRESSURE_TOP;
       return;
   }
   tpms_Set_MaxAlarm_TirePressure(pLocalParam->u32_tpms_max_alarm_tire_pressure);

}

void appToTpms_TopTirePressure_Dec_MouseUp()
{
   pLocalParam->u32_tpms_max_alarm_tire_pressure--;
   if(pLocalParam->u32_tpms_max_alarm_tire_pressure<TPMS_MAX_TIRE_PRESSURE_LOW)
   {
       pLocalParam->u32_tpms_max_alarm_tire_pressure = TPMS_MAX_TIRE_PRESSURE_LOW;
       return;
   }
   tpms_Set_MaxAlarm_TirePressure(pLocalParam->u32_tpms_max_alarm_tire_pressure);

}

void appToTpms_LowTirePressure_Inc_MouseUp()
{
   pLocalParam->u32_tpms_min_alarm_tire_pressure++;
   if(pLocalParam->u32_tpms_min_alarm_tire_pressure>TPMS_MIN_TIRE_PRESSURE_TOP)
   {
       pLocalParam->u32_tpms_min_alarm_tire_pressure = TPMS_MIN_TIRE_PRESSURE_TOP;
       return;
   }
   tpms_Set_MinAlarm_TirePressure(pLocalParam->u32_tpms_min_alarm_tire_pressure);
}

void appToTpms_LowTirePressure_Dec_MouseUp()
{

   pLocalParam->u32_tpms_min_alarm_tire_pressure--;
   if(pLocalParam->u32_tpms_min_alarm_tire_pressure<TPMS_MIN_TIRE_PRESSURE_LOW)
   {
       pLocalParam->u32_tpms_min_alarm_tire_pressure = TPMS_MIN_TIRE_PRESSURE_LOW;
       return;
   }

   tpms_Set_MinAlarm_TirePressure(pLocalParam->u32_tpms_min_alarm_tire_pressure);

}

void appToTpms_Unit_Temperature_MouseUp(u32 funcID)
{
        pLocalParam->u8_tpms_termerature_uint = !pLocalParam->u8_tpms_termerature_uint ;

		tpms_Set_MaxAlarm_Temperature(pLocalParam->u32_tpms_max_alarm_temperature);
        if(pLocalParam->tpms_data[0].b_update)
	    	tpms_Temperature_Update(CONTROLID_TPMS_FL_TEMPERATURE,local_TPMS_Data[0].u32_temperature);
        if(pLocalParam->tpms_data[1].b_update)
	    	tpms_Temperature_Update(CONTROLID_TPMS_FR_TEMPERATURE,local_TPMS_Data[1].u32_temperature);
        if(pLocalParam->tpms_data[2].b_update)
	    	tpms_Temperature_Update(CONTROLID_TPMS_RL_TEMPERATURE,local_TPMS_Data[2].u32_temperature);
        if(pLocalParam->tpms_data[3].b_update)
	    	tpms_Temperature_Update(CONTROLID_TPMS_RR_TEMPERATURE,local_TPMS_Data[3].u32_temperature);

		tpms_Set_Temperature_Unit();

}

void appToTpms_Unit_TirePressure_MouseUp(u32 funcID)
{

	   pLocalParam->u8_tpms_tire_pressure_uint = !pLocalParam->u8_tpms_tire_pressure_uint;

		tpms_Set_MaxAlarm_TirePressure(pLocalParam->u32_tpms_max_alarm_tire_pressure);
		tpms_Set_MinAlarm_TirePressure(pLocalParam->u32_tpms_min_alarm_tire_pressure);
        if(pLocalParam->tpms_data[0].b_update)
	    	tpms_TirePressure_Update(CONTROLID_TPMS_FL_TIRE_PRESSURE,local_TPMS_Data[0].u32_tire_pressure);
        if(pLocalParam->tpms_data[1].b_update)
	    	tpms_TirePressure_Update(CONTROLID_TPMS_FR_TIRE_PRESSURE,local_TPMS_Data[1].u32_tire_pressure);
        if(pLocalParam->tpms_data[2].b_update)
	    	tpms_TirePressure_Update(CONTROLID_TPMS_RL_TIRE_PRESSURE,local_TPMS_Data[2].u32_tire_pressure);
        if(pLocalParam->tpms_data[3].b_update)
	    	tpms_TirePressure_Update(CONTROLID_TPMS_RR_TIRE_PRESSURE,local_TPMS_Data[3].u32_tire_pressure);


        tpms_Set_Tire_Pressure_Unit();

}


//Setup2--------------------------------------------------
void appToTpms_AlarmType_Up_MouseUp()
{

	LOGD("-----appToTpms_AlarmType_Up_MouseUp------pLocalParam->u8_tpms_alarm_type:%x ----------", pLocalParam->u8_tpms_alarm_type);

	if(Alarm_Voice == pLocalParam->u8_tpms_alarm_type)
	       pLocalParam->u8_tpms_alarm_type = Alarm_Close;
	else
		pLocalParam->u8_tpms_alarm_type += 1;
	tpms_Set_AlarmType();
}
void appToTpms_AlarmType_Down_MouseUp()
{
	if(Alarm_Close == pLocalParam->u8_tpms_alarm_type)
	       pLocalParam->u8_tpms_alarm_type = Alarm_Voice;
	else
		pLocalParam->u8_tpms_alarm_type -= 1;
	tpms_Set_AlarmType();
}

void appToTpms_Clear_MouseUP(u32 funcID)
{
	switch(funcID)
	{
	    case CONTROLID_TPMS_EXSET_CLEAR_FL:
			appToTpms_Clear_FL_MouseUp();
		    break;
        case CONTROLID_TPMS_EXSET_CLEAR_FR:
			appToTpms_Clear_FR_MouseUp();
			break;
        case CONTROLID_TPMS_EXSET_CLEAR_RL:
			appToTpms_Clear_RL_MouseUp();
			break;
	    case CONTROLID_TPMS_EXSET_CLEAR_RR:
			appToTpms_Clear_RR_MouseUp();
			break;
		default:
			break;
	}
}


void appToTpms_Clear_FL_MouseUp()
{
	pLocalParam->u8_tpms_clear_data = emClearData_FL;
	setUpdateUI(false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_BACKGROUND, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_ENSURE, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_CANCEL, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_TEXT, true);
	setUpdateUI(true);
}
void appToTpms_Clear_FR_MouseUp()
{
	pLocalParam->u8_tpms_clear_data = emClearData_FR;
	setUpdateUI(false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_BACKGROUND, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_ENSURE, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_CANCEL, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_TEXT, true);
	setUpdateUI(true);

}
void appToTpms_Clear_RL_MouseUp()
{
	pLocalParam->u8_tpms_clear_data = emClearData_RL;
	setUpdateUI(false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_BACKGROUND, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_ENSURE, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_CANCEL, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_TEXT, true);
	setUpdateUI(true);

}
void appToTpms_Clear_RR_MouseUp()
{
	pLocalParam->u8_tpms_clear_data = emClearData_RR;
	setUpdateUI(false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_BACKGROUND, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_ENSURE, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_CANCEL, true);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_TEXT, true);
	setUpdateUI(true);
}



void appToTpms_PrePage_MouseUp()
{
	tpmsToModule_NotifySystem_JumpPage(PAGE_TPMS_SET);
	setAnalogData(CONTROLID_TPMS_SET_PREVPAGE,2);
	setControllable(CONTROLID_TPMS_SET_PREVPAGE,0);
}

void appToTpms_Clean_OK()
{
	switch(pLocalParam->u8_tpms_clear_data)
	{
	case emClearData_FL:
		Clean_TireData(emTire_FL);
		break;
	case emClearData_FR:
		Clean_TireData(emTire_FR);
		break;
	case emClearData_RL:
		Clean_TireData(emTire_RL);
		break;
	case emClearData_RR:
		Clean_TireData(emTire_RR);
		break;
	default:
		break;
	}
	setUpdateUI(false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_BACKGROUND, false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_ENSURE, false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_CANCEL, false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_TEXT, false);
	setUpdateUI(true);
}
void appToTpms_Clean_Cancel()
{
	setUpdateUI(false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_BACKGROUND, false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_ENSURE, false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_CANCEL, false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_TEXT, false);
	setUpdateUI(true);
}

void Clean_TireData(u8 tireNub)
{

	local_TPMS_Data[tireNub].b_battery_low = false;
	local_TPMS_Data[tireNub].b_update = false;

	setSerialData(CONTROLID_TPMS_FL_SIGN+16*tireNub+2,NULL,0);
	setSerialData(CONTROLID_TPMS_FL_SIGN+16*tireNub+3,NULL,0);

	setVisible(CONTROLID_TPMS_FL_SIGN+16*tireNub+1,local_TPMS_Data[tireNub].b_battery_low);
	setVisible(CONTROLID_TPMS_FL_SIGN+16*tireNub+1,local_TPMS_Data[tireNub].b_update);

}

void tpms_Set_MaxAlarm_Temperature(int nData)
{

    int n_temp = nData;

    if(Temp_Uint_F == pLocalParam->u8_tpms_termerature_uint)
    {
	n_temp = tpms_Temperature_C_To_F((double)nData);
    }

    u8 asciiBuf[16];
    memset(asciiBuf, 0, 4);
    sprintf((char*)asciiBuf,"%d",n_temp);
    int asciiBufLen = strlen((char*)asciiBuf);
    int unicodeBufLen = asciiBufLen*2+2;
    u8 *pUnicodeBuf = (u8 *)malloc(unicodeBufLen);
    memset(pUnicodeBuf, 0, unicodeBufLen);
    int nLen = ansi_str_to_unicode16(asciiBuf, (u16 *)pUnicodeBuf);

    setSerialData(CONTROLID_TPMS_SET_HIGHEST_TEM_ALARM_TEXT, pUnicodeBuf, unicodeBufLen);

    free(pUnicodeBuf);
    pUnicodeBuf = NULL;

}

void tpms_Set_MaxAlarm_TirePressure(int nData)
{

    int n_temp = nData;
    if(Pressure_KPA == pLocalParam->u8_tpms_tire_pressure_uint)
    {
		n_temp = tpms_TirePressure_Psi_To_Kpa(nData);
    }

    u8 asciiBuf[16];
    memset(asciiBuf, 0, 16);
    sprintf((char*)asciiBuf,"%d.%.1d",n_temp/10,n_temp%10);

    int asciiBufLen = strlen((char*)asciiBuf);
    int unicodeBufLen = asciiBufLen*2+2;
    u8 *pUnicodeBuf = (u8 *)malloc(unicodeBufLen);
    memset(pUnicodeBuf, 0, unicodeBufLen);
    int nLen = ansi_str_to_unicode16(asciiBuf, (u16 *)pUnicodeBuf);
    setSerialData(CONTROLID_TPMS_SET_HIGHEST_TIRE_PRESSURE_ALARM_TEXT, pUnicodeBuf, unicodeBufLen);
    free(pUnicodeBuf);
    pUnicodeBuf = NULL;
}

void tpms_Set_MinAlarm_TirePressure(int nData)
{
	LOGD("-----tpms_Set_MinAlarm_TirePressure---nData:%d", nData);

    int n_temp = nData;
    if(Pressure_KPA == pLocalParam->u8_tpms_tire_pressure_uint)
    {
	n_temp = tpms_TirePressure_Psi_To_Kpa(nData);
    }

	LOGD("-----tpms_Set_MinAlarm_TirePressure---n_temp:%d", n_temp);

    u8 asciiBuf[16];
    memset(asciiBuf, 0, 4);
    sprintf((char*)asciiBuf,"%d.%.1d",n_temp/10,n_temp%10);
    int asciiBufLen = strlen((char*)asciiBuf);
    int unicodeBufLen = asciiBufLen*2+2;
    u8 *pUnicodeBuf = (u8 *)malloc(unicodeBufLen);
    memset(pUnicodeBuf, 0, unicodeBufLen);
    int nLen = ansi_str_to_unicode16(asciiBuf, (u16 *)pUnicodeBuf);
    setSerialData(CONTROLID_TPMS_SET_LOWEST_TIRE_PRESSURE_ALARM_TEXT, pUnicodeBuf, unicodeBufLen);
    free(pUnicodeBuf);
    pUnicodeBuf = NULL;

}

int tpms_Temperature_C_To_F(double iC)
{
	LOGD("-----------tpms_Temperature_C_To_F----------------");
	int CF_Data = (int)(iC*9/5+32);
    return CF_Data;
}

int tpms_Temperature_F_To_C(double iF)
{
	//int FC_Data = (int)((iF-32)*5/9);
	int FC_Data = (int)(iF-40);
    return  FC_Data;
}

int tpms_TirePressure_Kpa_To_Psi(int iKpa)
{
    return (int)(iKpa*0.145);
}

int tpms_TirePressure_Psi_To_Kpa(int iPsi)
{
    return (int)(iPsi*100/14.5);
}

void tpms_Set_Temperature_Unit()
{
   int nStrUnitID = 0;
   switch(pLocalParam->u8_tpms_termerature_uint)
   	{
   	case Temp_Uint_C:
        nStrUnitID = STRINGID_TPMS_TEMPERATURE_UNITS_C;
		g_clsTpms.sendToFlyJniSdk_TemperatureUnit(0);
		break;
    case Temp_Uint_F:
		nStrUnitID = STRINGID_TPMS_TEMPERATURE_UNITS_F;
		g_clsTpms.sendToFlyJniSdk_TemperatureUnit(1);
		break;
	default:break;
   	}
   setStringText(CONTROLID_TPMS_SET_TEMPERATURE_UNITS_ICON, nStrUnitID);
   setStringText(CONTROLID_TPMS_FL_TEMPERATURE_UNIT, nStrUnitID);
   setStringText(CONTROLID_TPMS_FR_TEMPERATURE_UNIT, nStrUnitID);
   setStringText(CONTROLID_TPMS_RL_TEMPERATURE_UNIT, nStrUnitID);
   setStringText(CONTROLID_TPMS_RR_TEMPERATURE_UNIT, nStrUnitID);
}

void tpms_Set_Tire_Pressure_Unit()
{
   int nStrUnitID = 0;

   switch(pLocalParam->u8_tpms_tire_pressure_uint)
   	{
   	case Pressure_KPA:
        nStrUnitID = STRINGID_TPMS_PRESSURE_UNITS_KPA;
		g_clsTpms.sendToFlyJniSdk_PressureUnit(1);
		break;
   	case Pressure_PSI:
		nStrUnitID = STRINGID_TPMS_PRESSURE_UNITS_PSI;
		g_clsTpms.sendToFlyJniSdk_PressureUnit(0);
		break;
	case Pressure_BAR:
		nStrUnitID = STRINGID_TPMS_PRESSURE_UNITS_BAR;
	default:break;
   	}
   setStringText(CONTROLID_TPMS_SET_PRESSURE_UNITS_ICON, nStrUnitID);
   setStringText(CONTROLID_TPMS_FL_TIRE_PRESSURE_UNIT, nStrUnitID);
   setStringText(CONTROLID_TPMS_FR_TIRE_PRESSURE_UNIT, nStrUnitID);
   setStringText(CONTROLID_TPMS_RL_TIRE_PRESSURE_UNIT, nStrUnitID);
   setStringText(CONTROLID_TPMS_RR_TIRE_PRESSURE_UNIT, nStrUnitID);
}

void tpms_Set_AlarmType()
{

	int nStrAlarmTypeID = 0;

	switch(pLocalParam->u8_tpms_alarm_type)
	{
	case Alarm_Close:
		nStrAlarmTypeID = STRINGID_TPMS_OFF;
		break;
	case Alarm_Text:
		nStrAlarmTypeID = STRINGID_TPMS_TEXTWARNING;
		break;
	case Alarm_Voice:
		nStrAlarmTypeID = STRINGID_TPMS_RING;
		break;
	default:
		break;
	}

	setStringText(CONTROLID_TPMS_EXSET_TIRE_PRESSURE_ALARM_SET_TEXT,nStrAlarmTypeID);

}
void pushAlarmTextIdToQueue(u32 alarmTextId)
{
	LOGD("pLocalParam->vecAlarmText.size():%d",pLocalParam->vecAlarmText.size());
	int flag=0;
	vector<u32>::iterator it=pLocalParam->vecAlarmText.begin();
	for(it;it != pLocalParam->vecAlarmText.end();it++)
	{
		if(alarmTextId == *it)
		{
			flag=1;
			break;
		}
	}
	if(flag!=1)
	{
		pLocalParam->vecAlarmText.push_back(alarmTextId);
	}
}

void pushAlarmRingIdToQueue(u8 alarmRindId){
	LOGD("pLocalParam->vecAlarmRing.size():%d",pLocalParam->vecAlarmRing.size());
	int flag=0;
	vector<u8>::iterator it=pLocalParam->vecAlarmRing.begin();
	for(it;it != pLocalParam->vecAlarmRing.end();it++)
	{
		if(alarmRindId == *it)
		{
			flag=1;
			break;
		}
	}
	if(flag!=1)
	{
		pLocalParam->vecAlarmRing.push_back(alarmRindId);
	}
}

void popAlarmTextIdToQueue(void)
{
	LOGD("pLocalParam->vecAlarmText.size():%d",pLocalParam->vecAlarmText.size());
	vector<u32>::iterator it=pLocalParam->vecAlarmText.begin();
	if(it != pLocalParam->vecAlarmText.end())
	{
		localParam.curAlarmTextID=*it;
		setVisible(CONTROLID_TPMS_ALARM_TXT,1);
		setStringText(CONTROLID_TPMS_ALARM_TXT,*it);
		pLocalParam->vecAlarmText.erase(it);
		SetTimer(2000, 1, TPMS_TIMER_TEXTALARM);
	}
	else
	{
		LOGD("pLocalParam->qeAlarmText is NULL");
		setSerialData(CONTROLID_TPMS_ALARM_TXT,(u8*)"",0);
		localParam.curAlarmTextID=0;
	}
}

void popAlarmRingIdToQueue(void)
{
	u16 curpage = 0;
	u8 curpagelen = 0;

	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8 *)&curpage,(u8 *)&curpagelen);

	LOGD("pLocalParam->vecAlarmRing.size():%d",pLocalParam->vecAlarmRing.size());
	vector<u8>::iterator it=pLocalParam->vecAlarmRing.begin();
	if(it != pLocalParam->vecAlarmRing.end())
	{

		localParam.curAlarmRingID=*it;
//		setVisible(CONTROLID_TPMS_ALARM_TXT,1);
//		setStringText(CONTROLID_TPMS_ALARM_TXT,*it);
		u8 command= (u8)localParam.curAlarmRingID;
		pLocalParam->vecAlarmRing.erase(it);
		SetTimer(2000, 1, TPMS_TIMER_RINGALARM);
		if(curpage == (u16)PAGE_TPMS)return;
		else{
			tpmsToModule_NotifyOSDT123_ShowTitle();
			Set_TPMS_OSD_Control(command);
		}
	}
	else
	{
		LOGD("pLocalParam->qeAlarmRing is NULL");
		//setSerialData(CONTROLID_TPMS_ALARM_TXT,(u8*)"",0);
		localParam.curAlarmRingID=0;
	}
}

void tpmsToUI_setAlarm_TextShow(u8 command)
{

	u32 alarm_text_obj = 0;

	switch(command){

		case FL_Power_Low:  
			alarm_text_obj = STRINGID_TPMS_MAIN_FL_LOWBATTERY;
			pLocalParam->ucFLAlarmstate = pLocalParam->ucFLAlarmstate | 0x01;
			break;
		case FR_Power_Low:  
			alarm_text_obj = STRINGID_TPMS_MAIN_FR_LOWBATTERY;
			pLocalParam->ucFRAlarmstate = pLocalParam->ucFRAlarmstate | 0x01;
			break;
		case RL_Power_Low:  
			alarm_text_obj = STRINGID_TPMS_MAIN_RL_LOWBATTERY;
			pLocalParam->ucRLAlarmstate = pLocalParam->ucRLAlarmstate | 0x01;
			break;
		case RR_Power_Low:  
			alarm_text_obj = STRINGID_TPMS_MAIN_RR_LOWBATTERY;
			pLocalParam->ucRRAlarmstate = pLocalParam->ucRRAlarmstate | 0x01;
			break;

		case FL_Temperature_High:  
			alarm_text_obj = STRINGID_TPMS_MAIN_FL_TEMPERATURE_ALARM;
			pLocalParam->ucFLAlarmstate = pLocalParam->ucFLAlarmstate | 0x02;
			break;
		case FR_Temperature_High:  
			alarm_text_obj = STRINGID_TPMS_MAIN_FR_TEMPERATURE_ALARM;
			pLocalParam->ucFRAlarmstate = pLocalParam->ucFRAlarmstate | 0x02;
			break;
		case RL_Temperature_High: 
			alarm_text_obj = STRINGID_TPMS_MAIN_RL_TEMPERATURE_ALARM;
			pLocalParam->ucRLAlarmstate = pLocalParam->ucRLAlarmstate | 0x02;
			break;
		case RR_Temperature_High: 
			alarm_text_obj = STRINGID_TPMS_MAIN_RR_TEMPERATURE_ALARM;
			pLocalParam->ucRRAlarmstate = pLocalParam->ucRRAlarmstate | 0x02;
			break;

		case FL_Pressure_High: 
			alarm_text_obj = STRINGID_TPMS_MAIN_FL_TIRE_PRESSURE_HIGHT;
			pLocalParam->ucFLAlarmstate = pLocalParam->ucFLAlarmstate | 0x04;
			break;
		case FR_Pressure_High: 
			alarm_text_obj = STRINGID_TPMS_MAIN_FR_TIRE_PRESSURE_HIGHT;
			pLocalParam->ucFRAlarmstate = pLocalParam->ucFRAlarmstate | 0x04;
			break;
		case RL_Pressure_High: 
			alarm_text_obj = STRINGID_TPMS_MAIN_RL_TIRE_PRESSURE_HIGHT;
			pLocalParam->ucRLAlarmstate = pLocalParam->ucRLAlarmstate | 0x04;
			break;
		case RR_Pressure_High:  
			alarm_text_obj = STRINGID_TPMS_MAIN_RR_TIRE_PRESSURE_HIGHT;
			pLocalParam->ucRRAlarmstate = pLocalParam->ucRRAlarmstate | 0x04;
			break;

		case FL_Pressure_Low:  
			alarm_text_obj = STRINGID_TPMS_MAIN_FL_TIRE_PRESSURE_LOW;
			pLocalParam->ucFLAlarmstate = pLocalParam->ucFLAlarmstate | 0x08;
			break;
		case FR_Pressure_Low:  
			alarm_text_obj = STRINGID_TPMS_MAIN_FR_TIRE_PRESSURE_LOW;
			pLocalParam->ucFRAlarmstate = pLocalParam->ucFRAlarmstate | 0x08;
			break;
		case RL_Pressure_Low:  
			alarm_text_obj = STRINGID_TPMS_MAIN_RL_TIRE_PRESSURE_LOW;
			pLocalParam->ucRLAlarmstate = pLocalParam->ucRLAlarmstate | 0x08;
			break;
		case RR_Pressure_Low: 
			alarm_text_obj = STRINGID_TPMS_MAIN_RR_TIRE_PRESSURE_LOW;
			pLocalParam->ucRRAlarmstate = pLocalParam->ucRRAlarmstate | 0x08;
			break;
		default:
			break;

	}
	LOGD("pLocalParam->ucFLAlarmstate=0x%x",pLocalParam->ucFLAlarmstate);
	LOGD("pLocalParam->ucFRAlarmstate=0x%x",pLocalParam->ucFRAlarmstate);
	LOGD("pLocalParam->ucRLAlarmstate=0x%x",pLocalParam->ucRLAlarmstate);
	LOGD("pLocalParam->ucRRAlarmstate=0x%x",pLocalParam->ucRRAlarmstate);
	if(pLocalParam->curAlarmTextID == 0)
	{
		pLocalParam->curAlarmTextID = alarm_text_obj;
		setVisible(CONTROLID_TPMS_ALARM_TXT,1);
		setStringText(CONTROLID_TPMS_ALARM_TXT,alarm_text_obj);
		DeleteTimer(TPMS_TIMER_TEXTALARM);
		SetTimer(2000, 1, TPMS_TIMER_TEXTALARM);
	}
	else
	{
 		pushAlarmTextIdToQueue(alarm_text_obj);
 	}
	

}

void tpmsToT123_setAlarm(u8 command)
{
	if(pLocalParam->curAlarmRingID == 0)
	{
			pLocalParam->curAlarmRingID = command;
			tpmsToModule_NotifyOSDT123_ShowTitle();
			Set_TPMS_OSD_Control(command);
			DeleteTimer(TPMS_TIMER_RINGALARM);
			SetTimer(2000, 1, TPMS_TIMER_RINGALARM);
	}
	else
	{
	 		pushAlarmRingIdToQueue(command);
	 }
}

void clearAlarmText(u8 command)
{
	u32 clear_alarm_text_ID = 0;

	switch(command){

		case FL_Power_Low:  
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_FL_LOWBATTERY;
			pLocalParam->ucFLAlarmstate = pLocalParam->ucFLAlarmstate & 0x0E;
			break;
		case FR_Power_Low:  
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_FR_LOWBATTERY;
			pLocalParam->ucFRAlarmstate = pLocalParam->ucFRAlarmstate & 0x0E;
			break;
		case RL_Power_Low:  
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_RL_LOWBATTERY;
			pLocalParam->ucRLAlarmstate = pLocalParam->ucRLAlarmstate & 0x0E;
			break;
		case RR_Power_Low:  
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_RR_LOWBATTERY;
			pLocalParam->ucRRAlarmstate = pLocalParam->ucRRAlarmstate & 0x0E;
			break;

		case FL_Temperature_High:  
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_FL_TEMPERATURE_ALARM;
			pLocalParam->ucFLAlarmstate = pLocalParam->ucFLAlarmstate & 0x0D;
			break;
		case FR_Temperature_High:  
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_FR_TEMPERATURE_ALARM;
			pLocalParam->ucFRAlarmstate = pLocalParam->ucFRAlarmstate & 0x0D;
			break;
		case RL_Temperature_High: 
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_RL_TEMPERATURE_ALARM;
			pLocalParam->ucRLAlarmstate = pLocalParam->ucRLAlarmstate & 0x0D;
			break;
		case RR_Temperature_High: 
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_RR_TEMPERATURE_ALARM;
			pLocalParam->ucRRAlarmstate = pLocalParam->ucRRAlarmstate & 0x0D;
			break;

		case FL_Pressure_High: 
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_FL_TIRE_PRESSURE_HIGHT;
			pLocalParam->ucFLAlarmstate = pLocalParam->ucFLAlarmstate & 0x0B;
			break;
		case FR_Pressure_High: 
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_FR_TIRE_PRESSURE_HIGHT;
			pLocalParam->ucFRAlarmstate = pLocalParam->ucFRAlarmstate & 0x0B;
			break;
		case RL_Pressure_High: 
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_RL_TIRE_PRESSURE_HIGHT;
			pLocalParam->ucRLAlarmstate = pLocalParam->ucRLAlarmstate & 0x0B;
			break;
		case RR_Pressure_High:  
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_RR_TIRE_PRESSURE_HIGHT;
			pLocalParam->ucRRAlarmstate = pLocalParam->ucRRAlarmstate & 0x0B;
			break;

		case FL_Pressure_Low:  
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_FL_TIRE_PRESSURE_LOW;
			pLocalParam->ucFLAlarmstate = pLocalParam->ucFLAlarmstate & 0x07;
			break;
		case FR_Pressure_Low:  
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_FR_TIRE_PRESSURE_LOW;
			pLocalParam->ucFRAlarmstate = pLocalParam->ucFRAlarmstate & 0x07;
			break;
		case RL_Pressure_Low:  
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_RL_TIRE_PRESSURE_LOW;
			pLocalParam->ucRLAlarmstate = pLocalParam->ucRLAlarmstate & 0x07;
			break;
		case RR_Pressure_Low: 
			clear_alarm_text_ID = STRINGID_TPMS_MAIN_RR_TIRE_PRESSURE_LOW;
			pLocalParam->ucRRAlarmstate = pLocalParam->ucRRAlarmstate & 0x07;
			break;
		default:
			break;

	}
	u32  set_alarm_text_ID = 0;
	LOGD("pLocalParam->curAlarmTextID=0x%x,clear_alarm_text_ID=0x%x",pLocalParam->curAlarmTextID,clear_alarm_text_ID);
	if(pLocalParam->curAlarmTextID !=0 &&pLocalParam->curAlarmTextID == clear_alarm_text_ID)
	{
		LOGD("pLocalParam->ucFLAlarmstate=0x%x",pLocalParam->ucFLAlarmstate);
		LOGD("pLocalParam->ucFRAlarmstate=0x%x",pLocalParam->ucFRAlarmstate);
		LOGD("pLocalParam->ucRLAlarmstate=0x%x",pLocalParam->ucRLAlarmstate);
		LOGD("pLocalParam->ucRRAlarmstate=0x%x",pLocalParam->ucRRAlarmstate);
		if(pLocalParam->ucFLAlarmstate > 0)
		{
			if((pLocalParam->ucFLAlarmstate & 0x01 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_FL_LOWBATTERY;
			else if((pLocalParam->ucFLAlarmstate & 0x02 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_FL_TEMPERATURE_ALARM;
			else if((pLocalParam->ucFLAlarmstate & 0x04 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_FL_TIRE_PRESSURE_HIGHT;
			else if((pLocalParam->ucFLAlarmstate & 0x08 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_FL_TIRE_PRESSURE_LOW;
				
		}
		else if(pLocalParam->ucFRAlarmstate >0 )
		{
			if((pLocalParam->ucFRAlarmstate & 0x01 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_FR_LOWBATTERY;
			else if((pLocalParam->ucFRAlarmstate & 0x02 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_FR_TEMPERATURE_ALARM;
			else if((pLocalParam->ucFRAlarmstate & 0x04 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_FR_TIRE_PRESSURE_HIGHT;
			else if((pLocalParam->ucFRAlarmstate & 0x08 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_FR_TIRE_PRESSURE_LOW;
				
		}
		else if(pLocalParam->ucRLAlarmstate > 0)
		{
			if((pLocalParam->ucRLAlarmstate & 0x01 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_RL_LOWBATTERY;
			else if((pLocalParam->ucRLAlarmstate & 0x02 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_RL_TEMPERATURE_ALARM;
			else if((pLocalParam->ucRLAlarmstate & 0x04 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_RL_TIRE_PRESSURE_HIGHT;
			else if((pLocalParam->ucRLAlarmstate & 0x08 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_RL_TIRE_PRESSURE_LOW;
				
		}
		else if(pLocalParam->ucRRAlarmstate >0 )
		{
			if((pLocalParam->ucRRAlarmstate & 0x01 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_RR_LOWBATTERY;
			else if((pLocalParam->ucRRAlarmstate & 0x02 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_RR_TEMPERATURE_ALARM;
			else if((pLocalParam->ucRRAlarmstate & 0x04 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_RR_TIRE_PRESSURE_HIGHT;
			else if((pLocalParam->ucRRAlarmstate & 0x08 )>0)
				set_alarm_text_ID = STRINGID_TPMS_MAIN_RR_TIRE_PRESSURE_LOW;
				
		}
		pLocalParam->curAlarmTextID = set_alarm_text_ID;
		if(set_alarm_text_ID == 0)
		{
			setSerialData(CONTROLID_TPMS_ALARM_TXT,(u8*)"",0);
			if(pLocalParam->vecAlarmText.size()!=0)
				pLocalParam->vecAlarmText.clear();
		}
		else
			setStringText(CONTROLID_TPMS_ALARM_TXT,set_alarm_text_ID);
		
	}
}

void tpmsToUI_Load(){

	//LOGD("------------tpmsToUI_Load!-------------");

	tpms_Set_MaxAlarm_Temperature(localParam.u32_tpms_max_alarm_temperature);
	tpms_Set_MaxAlarm_TirePressure(localParam.u32_tpms_max_alarm_tire_pressure);
	tpms_Set_MinAlarm_TirePressure(localParam.u32_tpms_min_alarm_tire_pressure);

	tpms_Set_AlarmType();
	tpms_Set_Temperature_Unit();
	tpms_Set_Tire_Pressure_Unit();

	tpmstToUI_Infor_scroll(120);

	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_BACKGROUND, false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_ENSURE, false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_CANCEL, false);
	setVisible(CONTROLID_TPMS_EXSET_CLEAR_DIALOG_TEXT, false);
	setSerialData(CONTROLID_TPMS_ALARM_TXT,(u8*)"",0);
}

void tpmstToUI_Infor_scroll(u8 data){
	//int tempData = ((data + 5)/10 - 8);
	if(data >= 8){
		int tempData = (data - 8);
		setAnalogData(CONTROLID_TPMS_IMAGE_GAUGE,tempData);
	}
}

void Pair_Mode(bool pair){

	if(pair){

		LOGD("Pair_Mode^^^^^^^^^^^^^^^^^^^pair:0x0%x", pair);

		setDigitalData(CONTROLID_TPMS_PAIR,1);
        //clear tire data 20141015
		 Clean_TireData(emTire_FL);
		 Clean_TireData(emTire_FR);
		 Clean_TireData(emTire_RL);
		 Clean_TireData(emTire_RR);

		setStringText(CONTROLID_TPMS_ALARM_TXT,0);
		setVisible(CONTROLID_TPMS_ALARM_TXT,false);
		setVisible(CONTROLID_TPMS_FL_SIGN,false);
		setVisible(CONTROLID_TPMS_FR_SIGN,false);
		setVisible(CONTROLID_TPMS_RL_SIGN,false);
		setVisible(CONTROLID_TPMS_RR_SIGN,false);

	}else{

		setDigitalData(CONTROLID_TPMS_PAIR,0);

	}

}

void UpdateData(u32 ctrlID,bool bPair){
	if(bPair)
		{
			setVisible(ctrlID,1);
		}
	else
		{
			setVisible(ctrlID,0);
		}
	
	g_clsTpms.sendToFlyJniSdk_Tpms_Infor(ctrlID,bPair);
}

void UpdateBattery(u32 ctrlID,bool bLow){

	if(bLow){

			setVisible(ctrlID,1);

		}else{

			setVisible(ctrlID,0);

		}
		
	g_clsTpms.sendToFlyJniSdk_Tpms_Infor(ctrlID,bLow);
}

void tpms_Temperature_Update(u32 ctrlID,int nData)
{
    int n_temp = nData;

    if(Temp_Uint_F == pLocalParam->u8_tpms_termerature_uint)
    {
    	LOGD("-----------nData:%d-----------%d", nData, (int)((double)nData*9/5+32));
		n_temp = tpms_Temperature_C_To_F(nData);
    }

	LOGD("-----0x03==Conmand_Type-----F----temperature:%d", n_temp);
	
	g_clsTpms.sendToFlyJniSdk_Tpms_Infor(ctrlID,n_temp);
	
	u8 asciiBuf[16];
	memset(asciiBuf, 0, 16);
	sprintf((char*)asciiBuf,"%d",n_temp);

	int asciiBufLen = strlen((char*)asciiBuf);
	int unicodeBufLen = asciiBufLen*2+2;
	u8 *pUnicodeBuf = (u8 *)malloc(unicodeBufLen);
	memset(pUnicodeBuf, 0, unicodeBufLen);
	int nLen = ansi_str_to_unicode16(asciiBuf, (u16 *)pUnicodeBuf);
	setSerialData(ctrlID, pUnicodeBuf, unicodeBufLen);

	free(pUnicodeBuf);
	pUnicodeBuf = NULL;

	LOGD("---------Temperature-------------");
}

void tpms_TirePressure_Update(u32 ctrlID,int nData)
{
      int n_temp = nData;
      if(Pressure_KPA== pLocalParam->u8_tpms_tire_pressure_uint){
		n_temp = tpms_TirePressure_Psi_To_Kpa(nData);
      }

	LOGD("-----0x02==Conmand_Type---nData=%d------pressure:%d",nData ,n_temp);
	g_clsTpms.sendToFlyJniSdk_Tpms_Infor(ctrlID,n_temp);
	
	u8 asciiBuf[16];
	memset(asciiBuf, 0, 16);
	sprintf((char*)asciiBuf,"%d.%.1d",n_temp/10,n_temp%10);

	int asciiBufLen = strlen((char*)asciiBuf);
	int unicodeBufLen = asciiBufLen*2+2;
	u8 *pUnicodeBuf = (u8 *)malloc(unicodeBufLen);
	memset(pUnicodeBuf, 0, unicodeBufLen);
	int nLen = ansi_str_to_unicode16(asciiBuf, (u16 *)pUnicodeBuf);
	setSerialData(ctrlID, pUnicodeBuf, unicodeBufLen);
	free(pUnicodeBuf);
	pUnicodeBuf = NULL;
}

void show_SwapTpmsDlg(bool value)
{
	setUpdateUI(false);
	/*setVisible(CONTROLID_TPMS_DISPLAY_BUTTON_1, !value);
	setVisible(CONTROLID_TPMS_DISPLAY_BUTTON_2, !value);
	setVisible(CONTROLID_TPMS_DISPLAY_BUTTON_3, !value);
	setVisible(CONTROLID_TPMS_DISPLAY_BUTTON_4, !value);*/
	setVisible(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_BACKGROUND, value);
	setVisible(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_TEXT, value);
	setVisible(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_FL, value);
	setVisible(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_FR, value);
	setVisible(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_RL, value);
	setVisible(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_RR, value);
	setVisible(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_ENSURE, value);
	setVisible(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_CANCEL, value);
	setUpdateUI(true);
}
void appToTpms_DisplayButton(u8 index)
{
	localParam.swapbtn = false;
	pLocalParam->curTire = index;
	pLocalParam->swapTire = index;
	show_SwapTpmsDlg(true);
	setDigitalData(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_FL,0);
	setDigitalData(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_FR,0);
	setDigitalData(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_RL,0);
	setDigitalData(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_RR,0);
	setDigitalData(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_FL+index,1);
}

void appToTpms_MainDisplayTpmsBtn_TireSelect(u8 index)
{
	pLocalParam->swapTire = index;
	setDigitalData(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_FL,0);
	setDigitalData(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_FR,0);
	setDigitalData(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_RL,0);
	setDigitalData(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_RR,0);
	setDigitalData(CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_FL+index,1);
}

void appToTpms_MainDisplayTpmsBtn_Ensure(void)
{
	
	show_SwapTpmsDlg(false);
	LOGD("pLocalParam->curTire=%d,pLocalParam->swapTire=%d",pLocalParam->curTire,pLocalParam->swapTire);
	if(pLocalParam->curTire == pLocalParam->swapTire || localParam.curTire==emTire_NONE || localParam.swapTire==emTire_NONE)
	{
		localParam.swapbtn = true;
		return ;
	}
	int tireCur=pLocalParam->curTire;
	int tireSwap=pLocalParam->swapTire;
	u32 temp=pLocalParam->tireSignIDArr[tireCur];
	pLocalParam->tireSignIDArr[tireCur]=pLocalParam->tireSignIDArr[tireSwap];
	pLocalParam->tireSignIDArr[tireSwap]=temp;
	Clean_TireData(pLocalParam->curTire);
	Clean_TireData(pLocalParam->swapTire);
	for(int i=0;i<4;i++)
		LOGD("pLocalParam->tireSignIDArr[%d]=%x",i,pLocalParam->tireSignIDArr[i]);
	localParam.swapbtn = true;
}
void appToTpms_MainDisplayTpmsBtn_Cancel(void)
{
	show_SwapTpmsDlg(false);
	localParam.swapbtn = true;
}

void public_Tpms_TirePressure_Update(u32 ctrlID,int nData)
{
      	float n_temp = nData/100.0;
	g_clsTpms.sendToFlyJniSdk_Tpms_Infor(ctrlID,nData);

	u8 asciiBuf[16];
	memset(asciiBuf, 0, 16);
	sprintf((char*)asciiBuf,"%3.1f",n_temp);

	int asciiBufLen = strlen((char*)asciiBuf);
	int unicodeBufLen = asciiBufLen*2+2;
	u8 *pUnicodeBuf = (u8 *)malloc(unicodeBufLen);
	memset(pUnicodeBuf, 0, unicodeBufLen);
	int nLen = ansi_str_to_unicode16(asciiBuf, (u16 *)pUnicodeBuf);
	setSerialData(ctrlID, pUnicodeBuf, unicodeBufLen);
	free(pUnicodeBuf);
	pUnicodeBuf = NULL;
}

void public_Tpms_Temperature_Update(u32 ctrlID,int nData)
{
    	float n_temp = nData/100.0;
	g_clsTpms.sendToFlyJniSdk_Tpms_Infor(ctrlID,nData);
	
	u8 asciiBuf[16];
	memset(asciiBuf, 0, 16);
	sprintf((char*)asciiBuf,"%3.1f",n_temp);

	int asciiBufLen = strlen((char*)asciiBuf);
	int unicodeBufLen = asciiBufLen*2+2;
	u8 *pUnicodeBuf = (u8 *)malloc(unicodeBufLen);
	memset(pUnicodeBuf, 0, unicodeBufLen);
	int nLen = ansi_str_to_unicode16(asciiBuf, (u16 *)pUnicodeBuf);
	setSerialData(ctrlID, pUnicodeBuf, unicodeBufLen);

	free(pUnicodeBuf);
	pUnicodeBuf = NULL;
}

