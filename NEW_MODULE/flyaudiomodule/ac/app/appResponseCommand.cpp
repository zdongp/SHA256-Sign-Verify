#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"

#include "appResponseCommand.h"
#include "appResponseFunction.h"

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
	ctrlId += (int)((buffer[6] >> 24) & 0xFF000000);
	ctrlId += (int)((buffer[7] >> 16) & 0xFF0000);
	ctrlId += (int)((buffer[8] >> 8) & 0xFF00);
	
	
	LOGD("AC analyseAppMessage:ctrlId:0x%x.ctrlType:%x",ctrlId,ctrlType);
	switch(ctrlId){
		case CONTROLID_MENU_AIRCONDITION:
			if(ctrlType == UIACTION_MOUSEUP)
				{
					appToaircondition_EnterMainPage_MouseUp();
				}
			break;
		case CONTROLID_AIRCONDITION_BACK:
			if(ctrlType == UIACTION_MOUSEUP){
				//appToaircondition_ReturnMenuPage_MouseUp();
				appToaircondition_BackPage_MouseUp();
			}
			break;
		case CONTROLID_AIRCONDITION_WIND_SPEED_ADD:
			if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
			{
				//setWindSpeedAdd();
				setPublicWindSpeedAddOrDec(0x01);
			}
			break;
		case CONTROLID_AIRCONDITION_WIND_SPEED_LOW:
			if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
			{
				//setWindSpeedLow();
				setPublicWindSpeedAddOrDec(0x02);
			}
			break;
		case CONTROLID_AIRCONDITION_TEMP_L_ADD:
			if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
			{
				//setLeftTemperatureAdd();
				setLeftTemperatureAddOrLow(0x01,0x01);
			}
			break;
		case CONTROLID_AIRCONDITION_TEMP_L_LOW:
			if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
			{
				//setLeftTemperatureLow();
				setLeftTemperatureAddOrLow(0x01,0x02);
			}
			break;
		case CONTROLID_AIRCONDITION_TEMP_R_ADD:
			if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
			{
				//setRightTemperatureAdd();
				setLeftTemperatureAddOrLow(0x02,0x01);
			}
			break;
		case CONTROLID_AIRCONDITION_TEMP_R_LOW:
			if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
			{
				//setRightTemperatureLow();
				setLeftTemperatureAddOrLow(0x02,0x02);
			}
			break;
			
		case CONTROLID_AIRCONDITION_A_C:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setACSwitchOff_ON();
			}
			break;
		case CONTROLID_AIRCONDITION_FOCUS_MAX_A_C:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setMaxACOff_ON();
			}
			break;
		case CONTROLID_AIRCONDITION_AUTO:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setAutoSwitchStatus();
			}
			break;
		case CONTROLID_AIRCONDITION_CAR_REVOLUTION:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setLoopModeStatus();
			}
			break;
		case CONTROLID_AIRCONDITION_DUAL:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setDualStatus();
			}
			break;
		case CONTROLID_AIRCONDITION_OFF:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setAcSwitchStatus();
			}
			break;
		case CONTROLID_AIRCONDITION_WIND_MODE_SELECT:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				//setWindModeStates();
				setPublicWindModeStates();
			}
			break;
		case CONTROLID_AIRCONDITION_SEAT_UP:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setFWindowHeatingStates();
			}
			break;
		case CONTROLID_AIRCONDITION_UP:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setRearWindowHeatingStates();
			}
			break;
		case CONTROLID_AIRMODLE_BLOW_FACE:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setWindModeStatus(0x00);
			}
			break;	
		case CONTROLID_AIRMODLE_BLOW_THE_FEET:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setWindModeStatus(0x01);
			}
			break;	
		case CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setWindModeStatus(0x02);
			}
			break;	
		case CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setWindModeStatus(0x03);
			}
			break;	
		case CONTROLID_AIRMODLE_FRONT_WINDOW:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setWindModeStatus(0x04);
			}
			break;	
		case CONTROLID_AIRCONDITION_LOOP_MODE_OUTER:
		case CONTROLID_AIRCONDITION_LOOP_MODE_INNER:
		case CONTROLID_AIRCONDITION_LOOP_MODE_AUTO:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setLoopModeOfDirect(ctrlId - CONTROLID_AIRCONDITION_LOOP_MODE_OUTER);
			}
			break;
		case CONTROLID_AIRCONDITION_HEAD_BUTTON:
		case CONTROLID_AIRCONDITION_CHEST_BUTTON:
		case CONTROLID_AIRCONDITION_FOOT_BUTTON:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setPublicWindModeStatesForBody(ctrlId - CONTROLID_AIRCONDITION_HEAD_BUTTON);
			}
			break;
		case CONTROLID_AIRCONDITION_HEAT_SEAT_L:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setHeatSeatStatus_L();
			}
			break;
		case CONTROLID_AIRCONDITION_HEAT_SEAT_R:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setHeatSeatStatus_R();
			}
			break;
		case CONTROLID_AIRCONDITION_HEAT_GRADE_SEAT_L:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setAcHeatSeatGrade_L();
			}
			break;
		case CONTROLID_AIRCONDITION_HEAT_GRADE_SEAT_R:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setAcHeatSeatGrade_R();
			}
			break;
		case CONTROLID_AIRCONDITION_FRONT_WINDOW_BLOW_MAX_BUTTON:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setFrontWindowBlowMax();
			}
			break;
		//RearAir
		case CONTROLID_REAR_AIRCONDITION_SWITCH_BUTTON:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setRearAirconditionSwtich();
			}
			break;
		case CONTROLID_REAR_AIRCONDITION_CONTROL_LOCK_BUTTON:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setRearAirconditionControlLock();
			}
			break;
		case CONTROLID_REAR_AIRCONDITION_WIND_SPEED_INC_BUTTON:
		case CONTROLID_REAR_AIRCONDITION_WIND_SPEED_DEC_BUTTON:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setRearAirconditionWindSpeedControl(ctrlId - CONTROLID_REAR_AIRCONDITION_WIND_SPEED_INC_BUTTON);
			}
			break;
		case CONTROLID_REAR_AIRCONDITION_TEMPERATRUE_INC_BUTTON:
		case CONTROLID_REAR_AIRCONDITION_TEMPERATRUE_DEC_BUTTON:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				setRearAirconditionTempeartrueControl(ctrlId - CONTROLID_REAR_AIRCONDITION_TEMPERATRUE_INC_BUTTON);
			}
			break;
		case CONTROLID_AIRCONDITION_SET_BUTTON:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToaircondition_EnterAcSetPage_MouseUp();
			}
			break;
		case CONTROLID_AIRCONDITION_SET_BACK:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToaircondition_Set_Page_Back_MouseUp();
			}
			break;
		case CONTROLID_AIRCONDITION_AUTO_SWITCH_BACK_ROW:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToaircondition_AutoSwitch_BackRow_MouseUp();
			}
			break;
		default:break;
	}
}
