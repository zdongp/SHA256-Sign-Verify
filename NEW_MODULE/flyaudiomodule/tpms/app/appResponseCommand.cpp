#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "param.h"

#include "appResponseCommand.h"
#include "appResponseFunction.h"
#include "halResponseFunction.h"
#include "timer_interface.h"



void appInit(void){

}

void appDeInit(void){

}

void analyseAppMessage(unsigned char *buffer, unsigned char len){
	
	int ctrlId = 0;
	char ctrlType;
	unsigned char paramLen;
	unsigned char *param;

	ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
	ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
	ctrlId += (int)((buffer[2] << 8) & 0xFF00);
	ctrlId += (int)(buffer[3] & 0xFF);

	ctrlType = buffer[4];
	paramLen = len - 5;
	param = &buffer[5];

	LOGD("tpms analyseAppMessage---ctrlId:%x ctrlType:%x", ctrlId,ctrlType);
	
	
	switch(ctrlId){
		
        case CONTROLID_MENU_TPMS:
		{
		    appToTpms_EnterTPMS_MouseUp();
			/*<<<<<<<<<------------------[BEN] ADD----------------------*/
		//	SetTimer(TIME_500MS, 1, TPMS_TIMER_SEND_THE_DATA_OF_TMPS);
			/*-------------------------------END------->>>>>>>>>>>>>>>>*/
		}
			break;
			
       	case CONTROLID_TPMS_BACK:
	    case CONTROLID_TPMS_SET_BACK:
	    case CONTROLID_TPMS_EXSET_BACK:
		{
		    appToTpms_Back_MouseUp(ctrlId);
			/*<<<<<<<<<------------------[BEN] ADD----------------------*/
		//	DeleteTimer(TPMS_TIMER_SEND_THE_DATA_OF_TMPS);
			/*-------------------------------END------->>>>>>>>>>>>>>>>*/
		}
			break;
			
        case CONTROLID_TPMS_PAIR:
			if(ctrlType == UIACTION_MOUSEUP){
 		    	appToTpms_Pair_MouseUp();
			}
			break;
			
	    case CONTROLID_TPMS_SET:
		{
		    appToTpms_SetUp_MouseUp();
	    }
			break;
			
        case CONTROLID_TPMS_AUX:
		{
			
		}
			break;
			
		
        case CONTROLID_TPMS_SET_NEXTPAGE:
		{
		    appToTpms_NextPage_MouseUp();
		}
			break;
			
		case CONTROLID_TPMS_SET_PREVPAGE:
			break;

		case CONTROLID_TPMS_SET_HIGHEST_TEM_ALARM_DEFAULT:
	    case CONTROLID_TPMS_SET_HIGHEST_TIRE_PRESSURE_ALARM_DEFAULT:
	    case CONTROLID_TPMS_SET_LOWEST_TIRE_PRESSURE_ALARM_DEFAULT:
			appToTpms_SetDefaultValue_MouseUp(ctrlId);
			break;

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

		case CONTROLID_TPMS_SET_TEMPERATURE_UNITS_UP:
	    case CONTROLID_TPMS_SET_TEMPERATURE_UNITS_DOWN:
		{
	 	    appToTpms_Unit_Temperature_MouseUp(ctrlId);	
		}
			break;

		case CONTROLID_TPMS_SET_PRESSURE_UNITS_UP:
	    case CONTROLID_TPMS_SET_PRESSURE_UNITS_DOWN:
		{
		    appToTpms_Unit_TirePressure_MouseUp(ctrlId);
		}
			break;

	
		case CONTROLID_TPMS_EXSET_PREVPAGE:
		{
		    appToTpms_PrePage_MouseUp();
		}
			break;
			
		case CONTROLID_TPMS_EXSET_NEXTPAGE:
			break;
			
        case CONTROLID_TPMS_EXSET_TIRE_PRESSURE_ALARM_SET_UP:
		{
	 	    appToTpms_AlarmType_Up_MouseUp();	    
		}
			break;
			
	    case CONTROLID_TPMS_EXSET_TIRE_PRESSURE_ALARM_SET_DOWN:
		{
		    appToTpms_AlarmType_Up_MouseUp();
		}
			break;
			
        case CONTROLID_TPMS_EXSET_CLEAR_FL:
        case CONTROLID_TPMS_EXSET_CLEAR_FR:
        case CONTROLID_TPMS_EXSET_CLEAR_RL:
	    case CONTROLID_TPMS_EXSET_CLEAR_RR:
			appToTpms_Clear_MouseUP(ctrlId);
			break;
			
		case CONTROLID_TPMS_EXSET_CLEAR_DIALOG_ENSURE:
			appToTpms_Clean_OK();
			break;
			
		case CONTROLID_TPMS_EXSET_CLEAR_DIALOG_CANCEL:
			appToTpms_Clean_Cancel();
			break;
		case CONTROLID_TPMS_DISPLAY_BUTTON_1:
		case CONTROLID_TPMS_DISPLAY_BUTTON_2:
		case CONTROLID_TPMS_DISPLAY_BUTTON_3:
		case CONTROLID_TPMS_DISPLAY_BUTTON_4:
			LOGD("localParam.swapbtn=%d",localParam.swapbtn);
			if(localParam.swapbtn)
			{
				appToTpms_DisplayButton(ctrlId-CONTROLID_TPMS_DISPLAY_BUTTON_1);
			}
			break;
		case CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_FL:
		case CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_FR:
		case CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_RL:
		case CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_RR:
				appToTpms_MainDisplayTpmsBtn_TireSelect(ctrlId-CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_FL);
				break;
		case CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_ENSURE:
			 appToTpms_MainDisplayTpmsBtn_Ensure();
			break;
		case CONTROLID_TPMS_MAIN_DISPLAY_TPMS_BUTTON_CANCEL:
			appToTpms_MainDisplayTpmsBtn_Cancel();
			break;
	    default:break;
		
	}
	
}
