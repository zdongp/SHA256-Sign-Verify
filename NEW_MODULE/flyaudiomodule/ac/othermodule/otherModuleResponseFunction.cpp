#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "moduleParamResponse.h"
#include "halRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "halResponseFunction.h"
#include "dazong_acMsgdispose.cpp"
#include "controlID.h"
#include "appRequestCommand.h"
#include <flymoduleApi_internal.h>
#include "moduleParamRequest.h"
#include "pageID.h"

#include "appRequestFunction.h"
#include "timer_interface.h"

void GetParamOfACShow(){
}

void Get_System_AccOn(){
	acToHal_Init();
	GetParamOfACShow();
	pLocalParam->bInitAc = false;
	pLocalParam->nOsdStatusMark = 0;
	pLocalParam->ucSpeed = 0;
	pLocalParam->bSpeedMarkToOSD = false;
}

void Get_System_AccOff(){


}


int moduleToAIRCONDITION_FromSystem_Message(unsigned char *param, unsigned char len){
	switch(param[0])
	{
	case 0x10:
		if(0 == param[1])//ϵͳ��λ
			setDefaultParamters();
		break;
	case 0x14:
		if(0 == param[1])//�ָ���������
			setDefaultParamters();
		break;
	case 0x30://acc oGn
		Get_System_AccOn();
		break;
	case 0x31://acc off
		Get_System_AccOff();
		break;
	case 0x2C:
       halToSystem_Galaxy_AccOn();
    case 0x2D:
       halToSystem_Galaxy_AccOff();
	default:
		break;
	}
	return true;
}

int moduleToAIRCONDITION_FromExtcar_Message(unsigned char *param, unsigned char len)
{
	LOGD("param[0]=0x%x",param[0]);
	switch(param[0])
	{
		case 0x80:
			DealTuguanAcData(param+2);
			break;
		case 0x50:
			analyFocusAcData(param+1, len - 1);
			break;
        	case 0x81:
		{
			switch(param[1])
			{
				case 0x00:
				analyse_golf_ac_data(param + 2, len - 2);
				break;
				case 0x01:
				analyse_golf_ac_ctrl(param[2]);
				break;
				case 0x02:
				//analyse_golf_ac_acState(param[2]);
				break;
			}
        	}
			break;
		case 0x90:
			analyToyotaAcData(param+1, len - 1);
			break;
		case 0xB0:
			analySiYuAcData(param+1, len - 1);
			break;
		case 0xC0:
			analyse_byd_ac_data(param + 1, len - 1);
			break;
		case 0xd0:
			analyse_HondaCRV_ac_data(param + 1, len - 1);
			break;
		case 0xd1:
			analyse_Mistra_ac_data(param + 1, len - 1);
			break;
		case 0xff:
			analyse_Public_ac_date(param + 1, len - 1);
			//setAcInfoToSdk(param + 1, len - 1);
			break;
		default:break;
	}
	
	return true;

}



void analyFocusAcData(u8* param,u8 len)
{
	LOGD("[DYB220]: param:%x  %x  %x  %x  %x  %x  %x  %x",param[0],param[1],param[2],param[3],param[4],param[5],param[6],param[7]);
	u8 uinnerLoopState=param[0]&0x01;  //0x01:0000 0001
	
	u8 uMaxUpState=(param[0]&0x02)>>1;        //0x02:0000 0010
	
	u8 uAutoState=(param[0]&0x04)>>2;       //0x04:0000 0100


	u8 uAcState=((param[1]& 0x40)>>6) ? 0 : 1;       //0x40:0100 0000

	u8 uAcSwitch=(param[1]& 0x80)>>7;        //0x40:0100 0000
	
	u8 uDown=(param[1] & 0x08)>>3;     //0x08 0000 1000
	
	u8 uFront=(param[1] & 0x10)>>4;       //0x10 0001 0000
	
	u8 uUp=(param[1] & 0x20)>>5;         //0x20 0010 0000
	float fLeftTemperature=param[2]/2.0;
	float fRightTemperature=param[3]/2.0;

	u8 uWindSpeed= (param[4]>>4);
	if (uWindSpeed >= 7)
		uWindSpeed = 7;

	u8 uMaxAcState=(param[7]& 0x80)>>7;   //0x80  1000 0000

	
	
	LOGD("[DYB220]: uinnerLoopState = [%d],  uMaxState = [%d],  uAutoState = [%d] ", uinnerLoopState, uMaxUpState, uAutoState);
	LOGD("[DYB220]: uAcState = [%d],  uDown = [%d],  uUp = [%d] ", uAcState, uDown, uUp);
	LOGD("[DYB220]: uFront = [%d],  fLeftTemperature = [%.1f],  fRightTemperature = [%.1f] ", uFront, fLeftTemperature, fRightTemperature);
	LOGD("[DYB220]: uWindSpeed = [%d],  uMaxAcState = [%d] uAcSwitch = [%d]", uWindSpeed, uMaxAcState,uAcSwitch);

	if(pLocalParam->fks_uAcSwitch != uAcSwitch)
	{
		pLocalParam->fks_uAcSwitch=uAcSwitch;
		appRequest_refreshACDoor(pLocalParam->fks_uAcSwitch);
	}

	if(pLocalParam->fks_uAcSwitch == 0x00)
	{
		uAcState = 0x00;
		uWindSpeed = 0x00;
		uMaxAcState=0;
		uFront = 0;
		uUp=0;
		uDown=0;
		uAutoState=0;
		uinnerLoopState =0;
		uMaxUpState =0;
		fRightTemperature=127.5;
		fLeftTemperature=127.5;
	}
	if(pLocalParam->fks_uinnerLoopState != uinnerLoopState)
	{
		pLocalParam->fks_uinnerLoopState = uinnerLoopState;
		appRequest_refreshuinnerLoopStatus(pLocalParam->fks_uinnerLoopState);
	}
	if(pLocalParam->fks_uMaxUpState != uMaxUpState)
	{
		pLocalParam->fks_uMaxUpState = uMaxUpState;
		appRequest_fks_refreshMaxUpStatus(pLocalParam->fks_uMaxUpState);
	}
	if(pLocalParam->fks_uAutoState != uAutoState)
	{
		pLocalParam->fks_uAutoState = uAutoState;
		appRequest_refreshAutoMode(pLocalParam->fks_uAutoState);
	}
	if(pLocalParam->fks_uAcState != uAcState)
	{
		pLocalParam->fks_uAcState = uAcState;
		appRequest_refreshAOrCMode(pLocalParam->fks_uAcState);
		fks_TellToOSD();
	}
	if(pLocalParam->fks_uDown != uDown)
	{
		pLocalParam->fks_uDown = uDown;
		appRequest_fks_refreshDownStatus(pLocalParam->fks_uDown);
	}
	if(pLocalParam->fks_uUp != uUp)
	{
		pLocalParam->fks_uUp = uUp;
		appRequest_refreshWindToWindowMode(pLocalParam->fks_uUp);
	}
	if(pLocalParam->fks_uFront != uFront)
	{
		pLocalParam->fks_uFront = uFront;
		appRequest_fks_refreshFrontStatus(pLocalParam->fks_uFront);
	}
	if(uAutoState != 0x01 && pLocalParam->fks_uWindSpeed != uWindSpeed)
	{
		pLocalParam->fks_uWindSpeed = uWindSpeed;
		appRequest_refreshWindSpeedLevel(pLocalParam->fks_uWindSpeed);
		fks_TellToOSD();
	}
	if(pLocalParam->fks_uMaxAcState != uMaxAcState)
	{
		pLocalParam->fks_uMaxAcState = uMaxAcState;
		appRequest_fks_refreshAcMaxStatus(pLocalParam->fks_uMaxAcState);
	}
	if(pLocalParam->fks_fLeftTemperature != fLeftTemperature )
	{
		pLocalParam->fks_fLeftTemperature = fLeftTemperature;
		appRequest_fks_refreshLeftTemple(pLocalParam->fks_fLeftTemperature);
	}
	if(pLocalParam->fks_fRightTemperature != fRightTemperature)
	{
		pLocalParam->fks_fRightTemperature = fRightTemperature;
		appRequest_fks_refreshRightTemple(pLocalParam->fks_fRightTemperature);
	}
}







/*******************************************************TOYOTA start************************************************************/
void analyToyotaAcData(u8* param,u8 len)
{
	for(int i=0;i<17;i++)
	{
		LOGD("<<<<<<<<[TOYOTA]:param[%x]:%x>>>>>>>>",i,param[i]);
	}

	u8 uCurAuto_State=(param[1]&0xFF)>>7;
	u8 uCurAOrC_State=(param[1]&1);
	u8 uCurAC_WindSpeed=param[2];/*0~7 0ʱ�յ��ر� ����(1~7)*/
	u8 uCurAcSwitchPos=param[3]&0xF0; 
	int fCurLeftTemperature=param[8];
	int fCurRightTemperature=param[9];
	u8 uCurRearWindow_heatState=param[16]>>7;

	LOGD("[TOYOTA] AcOff_State:(%x)",pLocalParam->nToyotaAcOff);
	LOGD("[TOYOTA] Auto:(%x %x)",pLocalParam->uToyotaAuto_State,uCurAuto_State);
	LOGD("[TOYOTA] A/C:(%x %x)",pLocalParam->ucToyotaAOrCState,uCurAOrC_State);
	LOGD("[TOYOTA] WindSpeed:(%x %x)",pLocalParam->ucToyotaSpeed ,uCurAC_WindSpeed);
	LOGD("[TOYOTA] SwitchPos:(%x %x)",pLocalParam->uToyotaAcSwitchPos,uCurAcSwitchPos);
	LOGD("[TOYOTA] Left Temperature:(%x %x)",pLocalParam->usToyotaLeftTempValue,fCurLeftTemperature);
	LOGD("[TOYOTA] Right Temperature:(%x %x)",pLocalParam->usToyotaRightTempValue,fCurRightTemperature);
	LOGD("[TOYOTA] RearWindow_heatState:(%x %x)",pLocalParam->uToyotaRearWindow_heatState,uCurRearWindow_heatState);

	if(uCurAC_WindSpeed == 0)
	{
		pLocalParam->uToyotaAuto_State=0xFF;
		pLocalParam->ucToyotaAOrCState=0xFF;
		pLocalParam->uToyotaAcSwitchPos=0xFF;
		pLocalParam->usToyotaLeftTempValue=0xFF;
		pLocalParam->usToyotaRightTempValue=0xFF;
		pLocalParam->uToyotaRearWindow_heatState=0XFF;

		setDigitalData(CONTROLID_AIRCONDITION_A_C, 0);
		setDigitalData(CONTROLID_AIRCONDITION_AUTO, 0);
		
		setSerialData(CONTROLID_AIRCONDITION_TEMP_L, (u8*)"",0);
		setSerialData(CONTROLID_AIRCONDITION_TEMP_R, (u8*)"",0);
		setSerialData(CONTROLID_AIRCONDITION_GAUGE_TEXT, (u8*)"",0);
		setAnalogData(CONTROLID_AIRCONDITION_FOCUS_PROGRESSBAR, 0);
		setDigitalData(CONTROLID_AIRCONDITION_SEAT_UP, 0);
		setAnalogData(CONTROLID_AIRCONDITION_SEAT_RIGHT_OR_DOWN, 8);
		setDigitalData(CONTROLID_AIRCONDITION_UP, 0);
	}

	if(pLocalParam->ucToyotaSpeed != uCurAC_WindSpeed)
	{
		if(uCurAC_WindSpeed <= 7)
		{
			pLocalParam->ucToyotaSpeed = uCurAC_WindSpeed;
			pLocalParam->nToyotaAcOff = uCurAC_WindSpeed;
		}

		if(uCurAC_WindSpeed == 0)
		{
			appRequest_refreshACDoor(1);
		}
		else
		{
			appRequest_refreshACDoor(0);
		}
		appRequest_toyota_refreshAcSpeed(uCurAC_WindSpeed);
	}
	
	if(pLocalParam->uToyotaAuto_State != uCurAuto_State && pLocalParam->nToyotaAcOff != 0)
	{
		pLocalParam->uToyotaAuto_State = uCurAuto_State;
		appRequest_refreshAutoMode(uCurAuto_State);
		
	}
	if(pLocalParam->ucToyotaAOrCState != uCurAOrC_State && pLocalParam->nToyotaAcOff != 0)
	{
		pLocalParam->ucToyotaAOrCState = uCurAOrC_State;
		appRequest_refreshAOrCMode(uCurAOrC_State);
		toyota_TellToOSD();

	}

	if(pLocalParam->uToyotaAcSwitchPos != uCurAcSwitchPos && pLocalParam->nToyotaAcOff != 0)
	{
		pLocalParam->uToyotaAcSwitchPos = uCurAcSwitchPos;
		if(uCurAcSwitchPos == 0x10 || uCurAcSwitchPos == 0x90)
		{
			appRequest_refreshWindFace(5);
			appRequest_refreshWindToWindowMode(0);
		}
		else if(uCurAcSwitchPos == 0x20 || uCurAcSwitchPos == 0xa0)
		{
			appRequest_refreshWindFace(1);
			appRequest_refreshWindToWindowMode(0);
		}
		else if(uCurAcSwitchPos == 0x30 || uCurAcSwitchPos == 0xb0)
		{
			appRequest_refreshWindFace(3);
			appRequest_refreshWindToWindowMode(0);

		}
		else if(uCurAcSwitchPos== 0x40)
		{
			appRequest_refreshWindFace(7);
			appRequest_refreshWindToWindowMode(0);

		}
		else if(uCurAcSwitchPos == 0x00)
		{
			appRequest_refreshWindFace(8);
			appRequest_refreshWindToWindowMode(1);
		}
	}
	else if(pLocalParam->uToyotaAcSwitchPos != uCurAcSwitchPos && pLocalParam->nToyotaAcOff == 0)
	{
		LOGD("toyota off");
		if(uCurAcSwitchPos == 0x10 || uCurAcSwitchPos == 0x90)
		{
			appRequest_refreshWindFace(4);
		}
		else if(uCurAcSwitchPos == 0x20 || uCurAcSwitchPos == 0xa0)
		{
			appRequest_refreshWindFace(0);
		}
		else if(uCurAcSwitchPos == 0x30 || uCurAcSwitchPos == 0xb0)
		{
			appRequest_refreshWindFace(2);
		}
		else if(uCurAcSwitchPos == 0x40)
		{
			appRequest_refreshWindFace(6);
		}
		else if(uCurAcSwitchPos == 0x00)
		{
			appRequest_refreshWindFace(8);
		}
	}

	if(pLocalParam->usToyotaLeftTempValue != fCurLeftTemperature && pLocalParam->nToyotaAcOff != 0)
	{
		pLocalParam->usToyotaLeftTempValue=fCurLeftTemperature;
		appRequest_toyota_refreshLeftTemple(fCurLeftTemperature);
	}

	if(pLocalParam->usToyotaRightTempValue != fCurRightTemperature && pLocalParam->nToyotaAcOff != 0)
	{
		pLocalParam->usToyotaRightTempValue  = fCurRightTemperature;
		appRequest_toyota_refreshRightTemple(fCurRightTemperature);
	}

	if(pLocalParam->uToyotaRearWindow_heatState != uCurRearWindow_heatState && pLocalParam->nToyotaAcOff != 0)
	{
		pLocalParam->uToyotaRearWindow_heatState = uCurRearWindow_heatState;
		appRequest_refreshRearWindowsHeatMode(uCurRearWindow_heatState);
	}
}



/*SiYu AC*/
void analySiYuAcData(u8* param,u8 len)
{
	LOGD("param[0]:0x%x,param[1]:0x%x,param[2]:0x%x,param[3]:0x%x",param[0],param[1],param[2],param[3]);
	u8 uRear = (param[0]!=0);
	u8 uWindSpeed = (param[1]/0x10)-3;
	u8 uAcSwitch =(param[1]!=0);;
	u8 uLoopState = (param[2]!=0);
	LOGD("(SiYu) bRear=0x%x,uWindSpeed=0x%x,bAcSwitch=0x%x,uLoopState=0x%x",uRear,uWindSpeed,uAcSwitch,uLoopState);

	if(uAcSwitch != pLocalParam->SiYu_uAcSwitch)
	{
		pLocalParam->SiYu_uAcSwitch=uAcSwitch;
		
		if(pLocalParam->SiYu_uAcSwitch == 0)
		{
			appRequest_refreshACDoor(1);
			appRequest_refreshAcOffStatus(0);
		}
		else
		{
			appRequest_refreshACDoor(0);
			appRequest_refreshAcOffStatus(1);
		}
		
	}

	if(uAcSwitch == 0)
	{
		uRear=0;
		uWindSpeed=0;
		uLoopState=0;
	}
	if(uRear != pLocalParam->SiYu_uRear)
	{
		pLocalParam->SiYu_uRear=uRear;
		appRequest_refreshRearWindowsHeatMode(pLocalParam->SiYu_uRear);
	}
	if(uWindSpeed != pLocalParam->SiYu_uWindSpeed)
	{
		pLocalParam->SiYu_uWindSpeed=uWindSpeed;
		appRequest_refreshWindSpeedLevel(pLocalParam->SiYu_uWindSpeed);
	}
	
	if(uLoopState != pLocalParam->SiYu_uLoopState)
	{
		pLocalParam->SiYu_uLoopState=uLoopState;
		appRequest_refreshuinnerLoopStatus(pLocalParam->SiYu_uLoopState);
	}
	
	
	
	
}

// byd
#define BYD_AC_TAG		"byd_ac_tag"

void analyse_byd_ac_data(u8* param, u8 len)
{
	E_AC_COLD_MODE e_byd_ac_cold_mode = (param[0] & 2) ? AC_COLD_MODE_ON : AC_COLD_MODE_OFF;
	E_AC_REAR_WINDOW_HEAT_MODE e_byd_ac_rear_window_heat_mode = (param[0] & 1) ? AC_REAR_WINDOW_HEAT_MODE_ON : AC_REAR_WINDOW_HEAT_MODE_OFF;
	E_AC_WIND_TO_WINDOW_MODE e_byd_ac_wind_to_window_mode = AC_WIND_TO_WINDOW_MODE_UNKNOW;
	if ((param[1] & 0xC0) == 0x40)
		e_byd_ac_wind_to_window_mode = AC_WIND_TO_WINDOW_MODE_OFF;
	if ((param[1] & 0xC0) == 0x80)
		e_byd_ac_wind_to_window_mode = AC_WIND_TO_WINDOW_MODE_ON;
	
	E_AC_OUT_RECYCLE_MODE e_byd_ac_out_recycle_mode = AC_OUT_RECYCLE_MODE_UNKNOW;
	if ((param[1] & 0x30) == 0x10)
		e_byd_ac_out_recycle_mode = AC_OUT_RECYCLE_MODE_OFF;
	if ((param[1] & 0x30) == 0x20)
		e_byd_ac_out_recycle_mode = AC_OUT_RECYCLE_MODE_ON;
	
	E_AC_AC_MODE e_byd_ac_ac_mode = AC_AC_MODE_UNKNOW;
	if ((param[1] & 0x03) == 0x01)
		e_byd_ac_ac_mode = AC_AC_MODE_ON;
	if ((param[1] & 0x03) == 0x02)
		e_byd_ac_ac_mode = AC_AC_MODE_OFF;
	
	E_AC_AUTO_MODE e_byd_ac_auto_mode = AC_AUTO_MODE_UNKNOW;
	if ((param[1] & 0x0C) == 0x04)
		e_byd_ac_auto_mode = AC_AUTO_MODE_OFF;
	if((param[1] & 0x0C) == 0x08)
		e_byd_ac_auto_mode = AC_AUTO_MODE_ON;
	
	E_AC_WIND_FACE e_byd_ac_wind_face = AC_WIND_FACE_UNKNOW;
	if ((param[2] & 0x0F) == 0x01)
		e_byd_ac_wind_face = AC_WIND_FACE_FRONT;
	if ((param[2] & 0x0F) == 0x02)
		e_byd_ac_wind_face = AC_WIND_FACE_FRONT_DOWN;
	if ((param[2] & 0x0F) == 0x03)
		e_byd_ac_wind_face = AC_WIND_FACE_DOWN;
	if ((param[2] & 0x0F) == 0x04)
		e_byd_ac_wind_face = AC_WIND_FACE_DOWN_WINDOW;
	if ((param[2] & 0x0F) == 0x05)
		e_byd_ac_wind_face = AC_WIND_FACE_WINDOW;
	
	
	E_AC_CTRL_MODE e_byd_ac_ctrl_mode = AC_CTRL_MODE_UNKNOW;
	if ((param[3] & 0x30) == 0x10)
		e_byd_ac_ctrl_mode = AC_CTRL_MODE_DOUBLE;
	if ((param[3] & 0x30) == 0x20)
		e_byd_ac_ctrl_mode = AC_CTRL_MODE_SINGLE;
	

	u8 u8_byd_wind_level = (param[2] >> 4) & 0x0F;
	u8 u8_byd_degree_left = param[4];
	u8 u8_byd_degree_right = param[5];
	s16 s16_byd_degree_out = param[6] - 0x80;

	bool bACDoor = false, bleftDegree = false, bRightDegree = false, bWindSpeed = false, bCode = false;	// check if change state
	//log
	LOGD("[%s] e_byd_ac_cold_mode: l = [%d], g = [%d]",  BYD_AC_TAG, e_byd_ac_cold_mode, pLocalParam->e_byd_ac_cold_mode);
	LOGD("[%s] e_byd_ac_rear_window_heat_mode: l = [%d], g = [%d]", BYD_AC_TAG,  e_byd_ac_rear_window_heat_mode, pLocalParam->e_byd_ac_rear_window_heat_mode);
	LOGD("[%s] e_byd_ac_wind_to_window_mode: l = [%d], g = [%d]",  BYD_AC_TAG, e_byd_ac_wind_to_window_mode, pLocalParam->e_byd_ac_wind_to_window_mode);
	LOGD("[%s] e_byd_ac_out_recycle_mode: l = [%d], g = [%d]", BYD_AC_TAG,  e_byd_ac_out_recycle_mode, pLocalParam->e_byd_ac_out_recycle_mode);
	LOGD("[%s] e_byd_ac_ac_mode: l = [%d], g = [%d]",  BYD_AC_TAG, e_byd_ac_ac_mode, pLocalParam->e_byd_ac_ac_mode);
	LOGD("[%s] e_byd_ac_auto_mode: l = [%d], g = [%d]", BYD_AC_TAG,  e_byd_ac_auto_mode, pLocalParam->e_byd_ac_auto_mode);
	LOGD("[%s] e_byd_ac_wind_face: l = [%d], g = [%d]",  BYD_AC_TAG, e_byd_ac_wind_face, pLocalParam->e_byd_ac_wind_face);
	LOGD("[%s] e_byd_ac_ctrl_mode: l = [%d], g = [%d]", BYD_AC_TAG,  e_byd_ac_ctrl_mode, pLocalParam->e_byd_ac_ctrl_mode);
	
	LOGD("[%s] u8_byd_wind_level: l = [%d], g = [%d]",  BYD_AC_TAG, u8_byd_wind_level, pLocalParam->u8_byd_wind_level);
	LOGD("[%s] u8_byd_degree_left: l = [%d], g = [%d]", BYD_AC_TAG,  u8_byd_degree_left, pLocalParam->u8_byd_degree_left);
	LOGD("[%s] u8_byd_degree_right: l = [%d], g = [%d]",  BYD_AC_TAG, u8_byd_degree_right, pLocalParam->u8_byd_degree_right);
	LOGD("[%s] s16_byd_degree_out: l = [%d], g = [%d]", BYD_AC_TAG,  s16_byd_degree_out, pLocalParam->s16_byd_degree_out);


	if (e_byd_ac_ac_mode == AC_AC_MODE_OFF)
	{
		u8 invalidValue = 0xFF;
		u8_byd_degree_left = invalidValue;
		u8_byd_degree_right = invalidValue;
		s16_byd_degree_out = invalidValue;
		
	}
	else if (e_byd_ac_ac_mode == AC_AC_MODE_ON)
	{
		if (e_byd_ac_ac_mode != pLocalParam->e_byd_ac_ac_mode)
		{
			pLocalParam->bACCanShow = true;
			SetTimer(5000, 1, AC_TIMER_ID_BYD_AC_DO_NOT_SHOW);
		}
	}

	if (e_byd_ac_cold_mode != pLocalParam->e_byd_ac_cold_mode)
	{
		bCode = true;
		pLocalParam->e_byd_ac_cold_mode = e_byd_ac_cold_mode;
		 appRequest_refreshColdMode((u8)e_byd_ac_cold_mode);
	}
	if (e_byd_ac_rear_window_heat_mode != pLocalParam->e_byd_ac_rear_window_heat_mode)
	{
		pLocalParam->e_byd_ac_rear_window_heat_mode = e_byd_ac_rear_window_heat_mode;
		 appRequest_refreshRearWindowsHeatMode((u8) e_byd_ac_rear_window_heat_mode);
	}  
	if (e_byd_ac_wind_to_window_mode != pLocalParam->e_byd_ac_wind_to_window_mode)
	{
		pLocalParam->e_byd_ac_wind_to_window_mode = e_byd_ac_wind_to_window_mode;
		 appRequest_refreshWindToWindowMode((u8) e_byd_ac_wind_to_window_mode);
	}
	if (e_byd_ac_out_recycle_mode != pLocalParam->e_byd_ac_out_recycle_mode)
	{
		pLocalParam->e_byd_ac_out_recycle_mode = e_byd_ac_out_recycle_mode;
		 appRequest_refreshOutRecycleMode((u8) e_byd_ac_out_recycle_mode);
	}
	if (e_byd_ac_ac_mode != pLocalParam->e_byd_ac_ac_mode)
	{
		bACDoor = true;
		pLocalParam->e_byd_ac_ac_mode = e_byd_ac_ac_mode;
		 appRequest_refreshACDoor((u8) e_byd_ac_ac_mode);
	}
	if (e_byd_ac_auto_mode != pLocalParam->e_byd_ac_auto_mode)
	{
		pLocalParam->e_byd_ac_auto_mode = e_byd_ac_auto_mode;
		 appRequest_refreshAutoMode((u8) e_byd_ac_auto_mode);
	}

	//if (e_byd_ac_wind_face != pLocalParam->e_byd_ac_wind_face || e_byd_ac_ac_mode == AC_AC_MODE_OFF)
	{
		pLocalParam->e_byd_ac_wind_face = e_byd_ac_wind_face;
	 	u8 mode = (e_byd_ac_ac_mode == AC_AC_MODE_ON) ? ((u8) e_byd_ac_wind_face * 2 + ((AC_WIND_FACE_WINDOW == e_byd_ac_wind_face) ? 0 : 1)) :
	 																										((u8) e_byd_ac_wind_face * 2);																									
		 appRequest_refreshWindFace(mode);
	}
	if (u8_byd_wind_level != pLocalParam->u8_byd_wind_level)
	{
		bWindSpeed = true;
		pLocalParam->u8_byd_wind_level = u8_byd_wind_level;
		 appRequest_refreshWindSpeedLevel((u8) u8_byd_wind_level);
	}
	if (e_byd_ac_ctrl_mode != pLocalParam->e_byd_ac_ctrl_mode)
	{
		pLocalParam->e_byd_ac_ctrl_mode = e_byd_ac_ctrl_mode;
		 appRequest_refreshDegreeCtrlMode((u8) e_byd_ac_ctrl_mode);
	}
	if (u8_byd_degree_left != pLocalParam->u8_byd_degree_left)
	{
		bleftDegree = true;
		pLocalParam->u8_byd_degree_left = u8_byd_degree_left;
		 appRequest_byd_refreshLeftTemprature((int)u8_byd_degree_left);
	}

	if (u8_byd_degree_right != pLocalParam->u8_byd_degree_right)
	{
		bRightDegree = true;
		pLocalParam->u8_byd_degree_right = u8_byd_degree_right;
		 appRequest_byd_refreshRightTemprature((int) u8_byd_degree_right);
	}
	if(s16_byd_degree_out != pLocalParam->s16_byd_degree_out)
	{
		pLocalParam->s16_byd_degree_out = s16_byd_degree_out;
		 appRequest_byd_refreshCarGroundDegree((int)s16_byd_degree_out);
	}

	if (bACDoor||bleftDegree||bRightDegree||bWindSpeed||(pLocalParam->bACCanShow && bCode))
		byd_ac_msg_to_osd(e_byd_ac_cold_mode, u8_byd_degree_left, u8_byd_degree_right, u8_byd_wind_level , e_byd_ac_ac_mode);
	
}

//golf
#define GOLF_AC_TAG		"golf_ac_tag"
void analyse_golf_ac_data(u8 *param, u8 len)
{
//	dyb_log_output("AC ", "analyse_golf_ac_data ", (char*)param, len, printLog, TAG);
	static E_AC_COLD_MODE e_golf_ac_cold_mode = AC_COLD_MODE_UNKNOW;
	static E_AC_AC_MODE e_golf_ac_ac_mode = AC_AC_MODE_UNKNOW;
	static E_AC_AUTO_MODE e_golf_ac_auto_mode = AC_AUTO_MODE_UNKNOW;
	static E_AC_CTRL_MODE e_golf_ac_ctrl_mode = AC_CTRL_MODE_UNKNOW;
	static E_AC_WIND_TO_WINDOW_MODE e_golf_ac_wind_to_window_mode = AC_WIND_TO_WINDOW_MODE_UNKNOW;
	static E_AC_WIND_TO_FACE_MODE e_golf_ac_wind_to_face_mode = AC_WIND_TO_FACE_MODE_UNKNOW;
	static E_AC_WIND_TO_FEET_MODE e_golf_ac_wind_to_feet_mode = AC_WIND_TO_FEET_MODE_UNKNOW;
	static E_AC_DEGREE_UNIT e_golf_ac_degree_unit = AC_DEGREE_UNIT_UNKNOW;
	static u8 u8Invalid = 0xFF;
	static u8 u8_golf_seat_degree_left = u8Invalid;
	static u8 u8_golf_seat_degree_right = u8Invalid;
	static u8 u8_golf_degree_left = u8Invalid;
	static u8 u8_golf_degree_right = u8Invalid;
	static u8 u8_golf_wind_level = u8Invalid;
	static u8 u8_golf_DoorDegreeWind_State = 0;
	static bool ACCState = false;

	static  u8 h = 0x00;
	if(0x41 == param[3])
		h = param[0] | 0x40;

	if (h == param[0])//·ÖÎöÈ«ÊýŸÝÖ¡
	{
		switch(param[0] & 0x0F)
		{
		case 0x01:
			e_golf_ac_ac_mode = (param[7] == 0x10) ? AC_AC_MODE_ON : AC_AC_MODE_OFF;
			break;
		case 0x03:
			e_golf_ac_ctrl_mode = (param[6] == 0x01) ? AC_CTRL_MODE_DOUBLE : AC_CTRL_MODE_SINGLE;
			break;
		case 0x04:
			u8_golf_degree_left = param[4];
			e_golf_ac_degree_unit = (param[5] == 0x00) ? AC_DEGREE_UNIT_C : AC_DEGREE_UNIT_F;
			u8_golf_wind_level = param[6];
			break;
		case 0x05:
			e_golf_ac_wind_to_window_mode = (param[1] == 0x0C) ? AC_WIND_TO_WINDOW_MODE_ON : AC_WIND_TO_WINDOW_MODE_OFF;
			e_golf_ac_wind_to_face_mode =	 (param[2] == 0x0C) ? AC_WIND_TO_FACE_MODE_ON : AC_WIND_TO_FACE_MODE_OFF;
			e_golf_ac_wind_to_feet_mode =	 (param[3] == 0x0C) ? AC_WIND_TO_FEET_MODE_ON : AC_WIND_TO_FEET_MODE_OFF;
			e_golf_ac_auto_mode = (param[4] == 0x03) ? AC_AUTO_MODE_ON : AC_AUTO_MODE_OFF;
			u8_golf_seat_degree_left = param[6];
			u8_golf_degree_right = param[7];
			break;
		case 0x06:
			u8_golf_seat_degree_right = param[2];
			break;
		}
		h++;
	}

	if (param[0] == 0x40 || param[0] == 0x30)
	{
		switch(param[1])
		{
		case 0x4D:
			e_golf_ac_ac_mode = (param[2] == 0x10) ? AC_AC_MODE_ON : AC_AC_MODE_OFF;
			break;
		case 0x52:
			e_golf_ac_cold_mode = (param[2] == 0x01) ? AC_COLD_MODE_ON : AC_COLD_MODE_OFF;
			break;
		case 0x5C://0~7
			u8_golf_wind_level = param[2];
			break;
		case 0x55:
			e_golf_ac_ctrl_mode = (param[2] == 1) ? AC_CTRL_MODE_DOUBLE : AC_CTRL_MODE_SINGLE;
			break;
		case 0x5E:
			e_golf_ac_wind_to_window_mode = (param[2] == 0x0C) ? AC_WIND_TO_WINDOW_MODE_ON : AC_WIND_TO_WINDOW_MODE_OFF;
			e_golf_ac_wind_to_face_mode = (param[3] == 0x0C) ? AC_WIND_TO_FACE_MODE_ON : AC_WIND_TO_FACE_MODE_OFF;
			e_golf_ac_wind_to_feet_mode = (param[4] == 0x0C) ? AC_WIND_TO_FEET_MODE_ON : AC_WIND_TO_FEET_MODE_OFF;
			e_golf_ac_auto_mode = (param[5] == 0x03) ? AC_AUTO_MODE_ON : AC_AUTO_MODE_OFF;
			break;
		case 0x61:
			u8_golf_degree_right = (param[2] == 0xFF) ? 0xFE : param[2];
			e_golf_ac_degree_unit = (param[3] == 0x01) ? AC_DEGREE_UNIT_F : AC_DEGREE_UNIT_C;
			break;
		case 0x5B:
			u8_golf_degree_left = (param[2] == 0xFF) ? 0xFE : param[2];
			e_golf_ac_degree_unit = (param[3] == 0x01) ? AC_DEGREE_UNIT_F : AC_DEGREE_UNIT_C;
			break;
		case 0x65:
			u8_golf_seat_degree_right = param[2];
			break;
		case 0x5F:
			u8_golf_seat_degree_left = param[2];
			break;
		}//switch(param[1])
	}//if (param[0] == 0x40)

	bool bACDoor = false, bleftDegree = false, bRightDegree = false, bWindSpeed = false, bAC_Cold = false;	// check if change state
	LOGD("[%s] e_golf_ac_ac_mode: L = [%d], G = [%d]",  GOLF_AC_TAG, e_golf_ac_ac_mode, pLocalParam->e_golf_ac_ac_mode);
	LOGD("[%s] e_golf_ac_auto_mode: L = [%d], G = [%d]", GOLF_AC_TAG,  e_golf_ac_auto_mode, pLocalParam->e_golf_ac_auto_mode);
	LOGD("[%s] e_golf_ac_ctrl_mode: L = [%d], G = [%d]", GOLF_AC_TAG,  e_golf_ac_ctrl_mode, pLocalParam->e_golf_ac_ctrl_mode);

	LOGD("[%s] e_golf_ac_wind_to_window_mode: L = [%d], G = [%d]",  GOLF_AC_TAG, e_golf_ac_wind_to_window_mode, pLocalParam->e_golf_ac_wind_to_window_mode);
	LOGD("[%s] e_golf_ac_wind_to_face_mode: L = [%d], G = [%d]",  GOLF_AC_TAG, e_golf_ac_wind_to_face_mode, pLocalParam->e_golf_ac_wind_to_face_mode);
	LOGD("[%s] e_golf_ac_wind_to_feet_mode: L = [%d], G = [%d]",  GOLF_AC_TAG, e_golf_ac_wind_to_feet_mode, pLocalParam->e_golf_ac_wind_to_feet_mode);

	LOGD("[%s] u8_golf_wind_level: L = [%d], G = [%d]",  GOLF_AC_TAG, u8_golf_wind_level, pLocalParam->u8_golf_wind_level);
	LOGD("[%s] u8_golf_degree_left: L = [%d], G = [%d]", GOLF_AC_TAG,  u8_golf_degree_left, pLocalParam->u8_golf_degree_left);
	LOGD("[%s] u8_golf_degree_right: L = [%d], G = [%d]",  GOLF_AC_TAG, u8_golf_degree_right, pLocalParam->u8_golf_degree_right);
	LOGD("[%s] u8_golf_seat_degree_left: L = [%d], G = [%d]", GOLF_AC_TAG,  u8_golf_seat_degree_left, pLocalParam->u8_golf_seat_degree_left);
	LOGD("[%s] u8_golf_seat_degree_right: L = [%d], G = [%d]",  GOLF_AC_TAG, u8_golf_seat_degree_right, pLocalParam->u8_golf_seat_degree_right);

	pLocalParam->e_golf_ac_degree_unit = e_golf_ac_degree_unit;

	if (e_golf_ac_ac_mode == AC_AC_MODE_OFF)
	{
		u8 invalidValue = 0xFF;

		e_golf_ac_ac_mode = AC_AC_MODE_OFF;
		e_golf_ac_auto_mode = AC_AUTO_MODE_OFF;
		e_golf_ac_ctrl_mode = AC_CTRL_MODE_SINGLE;
		e_golf_ac_wind_to_window_mode = AC_WIND_TO_WINDOW_MODE_OFF;
		e_golf_ac_wind_to_face_mode = AC_WIND_TO_FACE_MODE_OFF;
		e_golf_ac_wind_to_feet_mode = AC_WIND_TO_FEET_MODE_OFF;
		u8_golf_degree_left = invalidValue;
		u8_golf_degree_right = invalidValue;
		u8_golf_wind_level = 0;

	}

	if (e_golf_ac_cold_mode != pLocalParam->e_golf_ac_cold_mode)
	{
		bAC_Cold = true;
		pLocalParam->e_golf_ac_cold_mode = e_golf_ac_cold_mode;
	}

	if (e_golf_ac_ac_mode != pLocalParam->e_golf_ac_ac_mode)
	{
		bACDoor = true;
		pLocalParam->e_golf_ac_ac_mode = e_golf_ac_ac_mode;
		appRequest_refreshACDoor((u8) e_golf_ac_ac_mode);
		u8_golf_DoorDegreeWind_State |= 0x01;
	}

	if (e_golf_ac_auto_mode != pLocalParam->e_golf_ac_auto_mode)
	{
		pLocalParam->e_golf_ac_auto_mode = e_golf_ac_auto_mode;
		appRequest_refreshAutoMode((u8) e_golf_ac_auto_mode);
	}

	if (e_golf_ac_ctrl_mode != pLocalParam->e_golf_ac_ctrl_mode)
	{
		pLocalParam->e_golf_ac_ctrl_mode = e_golf_ac_ctrl_mode;
		appRequest_refreshDegreeCtrlMode((u8) e_golf_ac_ctrl_mode);
	}

	if (e_golf_ac_wind_to_window_mode != pLocalParam->e_golf_ac_wind_to_window_mode)
	{
		pLocalParam->e_golf_ac_wind_to_window_mode = e_golf_ac_wind_to_window_mode;
		appRequest_refreshWindToWindowMode((u8) e_golf_ac_wind_to_window_mode);
	}

	if (e_golf_ac_wind_to_face_mode != pLocalParam->e_golf_ac_wind_to_face_mode)
	{
		pLocalParam->e_golf_ac_wind_to_face_mode = e_golf_ac_wind_to_face_mode;
		appRequest_refreshWindToFaceMode((u8) e_golf_ac_wind_to_face_mode);
	}

	if (e_golf_ac_wind_to_feet_mode != pLocalParam->e_golf_ac_wind_to_feet_mode)
	{
		pLocalParam->e_golf_ac_wind_to_feet_mode = e_golf_ac_wind_to_feet_mode;
		appRequest_refreshWindToFeetMode((u8) e_golf_ac_wind_to_feet_mode);
	}

	if (u8_golf_wind_level != pLocalParam->u8_golf_wind_level)
	{
		bWindSpeed = true;
		pLocalParam->u8_golf_wind_level = u8_golf_wind_level;
		appRequest_refreshWindSpeedLevel((u8) u8_golf_wind_level);
		u8_golf_DoorDegreeWind_State |= 0x02;
		g_pClsAcJniSdk.analysAcWindSpeedAndSendToApp(0x00,0x07,pLocalParam->u8_golf_wind_level);
	}
	if (u8_golf_degree_left != pLocalParam->u8_golf_degree_left)
	{
		bleftDegree = true;
		pLocalParam->u8_golf_degree_left = u8_golf_degree_left;
		appRequest_golf_refreshLeftTemprature((int)u8_golf_degree_left);
		u8_golf_DoorDegreeWind_State |= 0x04;
		sendToAcTempToSdk_Golf();
	}
	if (u8_golf_degree_right != pLocalParam->u8_golf_degree_right)
	{
		bRightDegree = true;
		pLocalParam->u8_golf_degree_right = u8_golf_degree_right;
		appRequest_golf_refreshRightTemprature((int) u8_golf_degree_right);
		u8_golf_DoorDegreeWind_State |= 0x08;
		sendToAcTempToSdk_Golf();
	}
	if (u8_golf_seat_degree_left != pLocalParam->u8_golf_seat_degree_left)
	{
		pLocalParam->u8_golf_seat_degree_left = u8_golf_seat_degree_left;
		appRequest_refreshLeftSeatHeat((int)u8_golf_seat_degree_left);
	}
	if (u8_golf_seat_degree_right != pLocalParam->u8_golf_seat_degree_right)
	{
		pLocalParam->u8_golf_seat_degree_right = u8_golf_seat_degree_right;
		appRequest_refreshRightSeatHeat((int)u8_golf_seat_degree_right);
	}

	LOGD("[ben%s] bACDoor=%d,bleftDegree=%d,bRightDegree=%d,bWindSpeed=%d,u8_golf_DoorDegreeWind_State=0x%x",
		__FUNCTION__,bACDoor,bleftDegree,bRightDegree,bWindSpeed,u8_golf_DoorDegreeWind_State);
	if (u8_golf_DoorDegreeWind_State == 0x0F && pLocalParam->e_golf_ac_ac_mode != AC_AC_MODE_OFF)
	{
		pLocalParam->golf_timer_state = false;
		u8_golf_DoorDegreeWind_State = 0;

		if(!ACCState){
			ACCState = !ACCState;
		}

		if (ACCState)
		{
			LOGD("GOLF_TIMER START!");
			setTimerAcDataTimeToOSD();
		}
	}
	else if (ACCState)
	{
		u8_golf_DoorDegreeWind_State = 0;
		LOGD("GOLF_TIMER golf_timer_state = %d",pLocalParam->golf_timer_state );
		if (pLocalParam->golf_timer_state )
			{
				LOGD("GOLF_TIMER FINISH AND SHOW THE 2ND+ OSD!");
				if (bACDoor || bleftDegree || bRightDegree || bWindSpeed || bAC_Cold)
				golf_ac_msg_to_osd(pLocalParam->e_golf_ac_cold_mode, e_golf_ac_degree_unit, u8_golf_degree_left, u8_golf_degree_right, u8_golf_wind_level , e_golf_ac_ac_mode);
			}
		
	}
	LOGD("[ben] ACCState = %d",ACCState);
}//void analyse_golf_ac_data(u8 *param, u8 len)

/*
u8 r = 0;
if (param[2] == 0)//low
r = 0;
else if (param[2] == 0xFF)//hi
r = 0xFE;
else

(param[2] - 0x3C) + 160;	//0.1C
pLocalParam->u8_golf_degree_right = r;
*/
void analyse_golf_ac_ctrl(u8 param)
{
	switch(param)
	{
	case 0x01:
		airconditionToModule_NotifySystem_jumpPage(PAGE_AIRCONDITION);
		break;
	}
}

void analyse_golf_ac_acState(u8 p)
{
	bool bCode = false;
	E_AC_COLD_MODE e_golf_ac_cold_mode = (E_AC_COLD_MODE)p;
	LOGD("[%s] e_golf_ac_cold_mode: l = [%d], g = [%d]",  GOLF_AC_TAG, e_golf_ac_cold_mode, pLocalParam->e_golf_ac_cold_mode);
	if (e_golf_ac_cold_mode != pLocalParam->e_golf_ac_cold_mode)
	{
		bCode = true;
		pLocalParam->e_golf_ac_cold_mode = e_golf_ac_cold_mode;
		//appRequest_refreshColdMode((u8)e_golf_ac_cold_mode);
	}
	/*if (bCode)
		golf_ac_msg_to_osd(e_golf_ac_cold_mode, pLocalParam->e_golf_ac_degree_unit, pLocalParam->u8_golf_degree_left,
				pLocalParam->u8_golf_degree_right, pLocalParam->u8_golf_wind_level , pLocalParam->e_golf_ac_ac_mode);*/
}

// CRV
#define CRV_AC_TAG		"crv_ac_tag"
static  E_AC_AC_MODE e_crv_ac_ac_mode = AC_AC_MODE_UNKNOW;
static	E_AC_WIND_FACE e_crv_ac_wind_face = AC_WIND_FACE_UNKNOW;
static	E_AC_AUTO_MODE e_crv_auto_mode = AC_AUTO_MODE_UNKNOW;
static  E_AC_COLD_MODE e_crv_cold_mode = AC_COLD_MODE_UNKNOW;
static  E_AC_OUT_RECYCLE_MODE e_crv_ac_in_recycle_mode = AC_OUT_RECYCLE_MODE_UNKNOW;
static	E_AC_REAR_WINDOW_HEAT_MODE e_crv_ac_rear_window_heat_mode = AC_REAR_WINDOW_HEAT_MODE_UNKNOW;
static  E_AC_CTRL_MODE e_crv_sync_mode = AC_CTRL_MODE_UNKNOW;

void analyse_HondaCRV_ac_data(u8* param, u8 len)
{
	for(int i=0;i<6;i++)
	{
		LOGD("<<<<<<<<[%s]:param[%x]:%x>>>>>>>>",CRV_AC_TAG,i,param[i]);
	}

	if((param[0]&0x0f) == 0x0f)//�յ���
		e_crv_ac_ac_mode = AC_AC_MODE_OFF;
	if((param[0]&0x0f) != 0x0f)
		e_crv_ac_ac_mode = AC_AC_MODE_ON;

	u8 u8_crv_wind_level=0;//����
	if(e_crv_ac_ac_mode==AC_AC_MODE_OFF || e_crv_ac_ac_mode == AC_AC_MODE_UNKNOW)
	u8_crv_wind_level=0;
	else
	u8_crv_wind_level=(param[0]&0x0f);
	
	u8 u8_crv_degree_left = param[1]/4;//����¶�
	u8 u8_crv_degree_right = param[2]/4;//�ұ��¶�

	if((param[3]&0xf0) == 0x50)//����ͷ
		e_crv_ac_wind_face = AC_WIND_FACE_FRONT;
	if((param[3]&0xf0)  == 0x40)//��ͷ�ͽ�
		e_crv_ac_wind_face = AC_WIND_FACE_FRONT_DOWN;
	if((param[3]&0xf0)  == 0x30)//����
		e_crv_ac_wind_face = AC_WIND_FACE_DOWN;
	if((param[3]&0xf0)  == 0x20)//�����ͽ�
		e_crv_ac_wind_face = AC_WIND_FACE_DOWN_WINDOW;
	if((param[3]&0xf0)  == 0xF0)//��ǰ��
		e_crv_ac_wind_face = AC_WIND_FACE_WINDOW;

	if((param[4]&0xf0)==0x80)//�Զ� 
	{
		e_crv_auto_mode = AC_AUTO_MODE_ON;
	}
	else
	{
		e_crv_auto_mode = AC_AUTO_MODE_OFF;
	}
	if((param[4]&0xf0)==0x20)//AC ON
	{
		e_crv_cold_mode = AC_COLD_MODE_ON;
	}
	if((param[4]&0xf0)==0x10)//AC OFF
	{
		e_crv_cold_mode = AC_COLD_MODE_OFF;
	}


	if((param[4]&0x0c)==0x08)//����ѭ��
		e_crv_ac_in_recycle_mode = AC_OUT_RECYCLE_MODE_ON;
	if((param[4]&0x0c)==0x04)
		e_crv_ac_in_recycle_mode = AC_OUT_RECYCLE_MODE_OFF;
		

	if((param[4]&1)==0x01)//����
		e_crv_ac_rear_window_heat_mode = AC_REAR_WINDOW_HEAT_MODE_ON;
	if((param[4]&1)==0x00)
		e_crv_ac_rear_window_heat_mode = AC_REAR_WINDOW_HEAT_MODE_OFF;

	if((param[5]&0xC0) == 0xC0)//SYNC
		e_crv_sync_mode = AC_CTRL_MODE_SINGLE;
	if((param[5]&0xC0) == 0x80)
		e_crv_sync_mode = AC_CTRL_MODE_DOUBLE;
		
	bool bACDoor = false, bleftDegree = false, bRightDegree = false, bWindSpeed = false, bCode = false;	// check if change state
	//log
	LOGD("[%s] ac_off:      [%d],[%d]",  CRV_AC_TAG, e_crv_ac_ac_mode, pLocalParam->e_crv_ac_ac_mode);
	LOGD("[%s] wind_speed: 	[%d],[%d]",  CRV_AC_TAG, u8_crv_wind_level, pLocalParam->u8_crv_wind_level);
	LOGD("[%s] left_temp:	[%d],[%d]",  CRV_AC_TAG,  u8_crv_degree_left, pLocalParam->u8_crv_degree_left);
	LOGD("[%s] right_temp:	[%d],[%d]",  CRV_AC_TAG, u8_crv_degree_right, pLocalParam->u8_crv_degree_right);
	LOGD("[%s] wind_face:   [%d],[%d]",  CRV_AC_TAG, e_crv_ac_wind_face, pLocalParam->e_crv_ac_wind_face);
	LOGD("[%s] auto_mode:   [%d],[%d]",  CRV_AC_TAG,  e_crv_auto_mode, pLocalParam->e_crv_ac_auto_mode);
	LOGD("[%s] a/c_mode:    [%d],[%d]",  CRV_AC_TAG, e_crv_cold_mode, pLocalParam->e_crv_ac_cold_mode);
	LOGD("[%s] in_recycle:  [%d],[%d]", CRV_AC_TAG,  e_crv_ac_in_recycle_mode, pLocalParam->e_crv_ac_out_recycle_mode);
	LOGD("[%s] rear_window_heat:[%d],[%d]", CRV_AC_TAG,  e_crv_ac_rear_window_heat_mode, pLocalParam->e_crv_ac_rear_window_heat_mode);
	LOGD("[%s] sync_mode:   [%d],[%d]", CRV_AC_TAG,  e_crv_sync_mode, pLocalParam->e_crv_ac_ctrl_mode);
	


	if (e_crv_ac_ac_mode == AC_AC_MODE_OFF)
	{
		u8 invalidValue = 0xFF;
		u8_crv_degree_left = invalidValue;
		u8_crv_degree_right = invalidValue;
		e_crv_cold_mode = AC_COLD_MODE_OFF;
		e_crv_auto_mode = AC_AUTO_MODE_OFF;
	}

	//�յ�����ģʽ
	if (e_crv_ac_ac_mode != pLocalParam->e_crv_ac_ac_mode)
	{
		bACDoor = true;
		pLocalParam->e_crv_ac_ac_mode = e_crv_ac_ac_mode;
		appRequest_refreshACDoor_PowerSupply((u8) e_crv_ac_ac_mode);
	}
	//����
	if (u8_crv_wind_level != pLocalParam->u8_crv_wind_level)
	{
		bWindSpeed = true;
		pLocalParam->u8_crv_wind_level = u8_crv_wind_level;
		appRequest_crv_refreshWindSpeedLevel((u8) u8_crv_wind_level);
	}
	//���¶�
	if (u8_crv_degree_left != pLocalParam->u8_crv_degree_left)
	{
		bleftDegree = true;
		pLocalParam->u8_crv_degree_left = u8_crv_degree_left;
		appRequest_crv_refreshLeftTemprature((int)u8_crv_degree_left);
	}
	//���¶�
	if (u8_crv_degree_right != pLocalParam->u8_crv_degree_right)
	{
		bRightDegree = true;
		pLocalParam->u8_crv_degree_right = u8_crv_degree_right;
		appRequest_crv_refreshRightTemprature((int) u8_crv_degree_right);
	}
	//Autoģʽ
	if (e_crv_auto_mode != pLocalParam->e_crv_ac_auto_mode)
	{
		pLocalParam->e_crv_ac_auto_mode = e_crv_auto_mode;
		appRequest_refreshAutoMode((u8) e_crv_auto_mode);
	}
	//A/Cģʽ
	if (e_crv_cold_mode != pLocalParam->e_crv_ac_cold_mode)
	{
		bCode = true;
		pLocalParam->e_crv_ac_cold_mode = e_crv_cold_mode;
		appRequest_refreshAOrCMode((u8)e_crv_cold_mode);
	}
	//��ѭ��
	if (e_crv_ac_in_recycle_mode != pLocalParam->e_crv_ac_out_recycle_mode)
	{
		pLocalParam->e_crv_ac_out_recycle_mode = e_crv_ac_in_recycle_mode;
		appRequest_refreshOutRecycleMode((u8) e_crv_ac_in_recycle_mode);
	}
	//����ģʽ
	if(e_crv_ac_wind_face != AC_WIND_FACE_WINDOW)
	{
		pLocalParam->e_byd_ac_wind_face = e_crv_ac_wind_face;
	 	u8 mode = (e_crv_ac_ac_mode == AC_AC_MODE_ON) ? ((u8) e_crv_ac_wind_face * 2 + ((AC_WIND_FACE_WINDOW == e_crv_ac_wind_face) ? 0 : 1)) :
	 			  ((u8) e_crv_ac_wind_face * 2);																									
		appRequest_refreshWindFace(mode);
		appRequest_refreshWindToWindowMode(0);
		
	}
	else if(e_crv_ac_wind_face == AC_WIND_FACE_WINDOW)
	{
		appRequest_refreshWindFace(8);
		appRequest_refreshWindToWindowMode(1);
	}

	//����
	if (e_crv_ac_rear_window_heat_mode != pLocalParam->e_crv_ac_rear_window_heat_mode)
	{
		pLocalParam->e_crv_ac_rear_window_heat_mode = e_crv_ac_rear_window_heat_mode;
		appRequest_refreshRearWindowsHeatMode((u8) e_crv_ac_rear_window_heat_mode);
	}  
	//SYNC
	if (e_crv_sync_mode != pLocalParam->e_crv_ac_ctrl_mode)
	{
		pLocalParam->e_crv_ac_ctrl_mode = e_crv_sync_mode;
		appRequest_refreshAC_SYNC_Mode((u8) e_crv_sync_mode);
	}

	//����OSD
	if (bACDoor|| bCode|| bleftDegree||bRightDegree||bWindSpeed)
		crv_ac_msg_to_osd(pLocalParam->e_crv_ac_cold_mode, pLocalParam->u8_crv_degree_left, pLocalParam->u8_crv_degree_right, pLocalParam->u8_crv_wind_level , e_crv_ac_ac_mode);

}




void moduleToAIRCONDITION_FromExternalCtrl_Message(unsigned char *param, unsigned char len)
{
	LOGD("moduleToAIRCONDITION_FromExternalCtrl_Message %d %d %d",param[0],param[1],param[2]);
	if(param[0]==0x00)
	{
		switch(param[1])
		{
			case 0x00:
			case 0x01:
			case 0x02:
			case 0x03:
			case 0x04:
			case 0x05:
			case 0x06:
			case 0x07:
			break;
			default:break;
		}
	}
	else if(param[0]==0x01)
	{
		if(param[1]==0x01)
		{
		    airconditionToModule_NotifySystem_jumpPage(PAGE_AIRCONDITION);
		}
		else
		{
		}
	}
}



void moduleToAIRCONDITION_FromAutomate_Message(u8 *param, u8 len)
{
    #include "appResponseCommand.h"
    
    if(param[0] == 0xff)
    {
        analyseAppMessage(param+1, len-1);
    }
}

void halToSystem_Galaxy_AccOn()
{
}
void halToSystem_Galaxy_AccOff()
{
}



void analyse_Mistra_ac_data(u8 *p,u8 len)
{
	u8 recmd;
	u8 *param;
	recmd = p[0];
	param = p+1;
	len = len - 1;
	switch(recmd)
	{
		case 0x00:			//AC On-Off
			halToAc_AcSwitch(param, len);
			break;
		case 0x01:			//AC Temperature
			halToAc_AcTemperature(param, len);
			break;
		case 0x02:			
			halToAc_AcAirSpeed(param, len);
			break;
		case 0x03:			
			halToAc_AcWindDirection(param, len);
			break;
		case 0x04:
			halToAc_AcAirCycle(param, len);
			break;
		case 0x05:			//A/C
			halToAc_AcRefrigeration(param, len);
			break;
		case 0x06:
			halToAc_MaxRefrigeration(param, len);
			break;
		case 0x07:			//Auto On-Off
			halToAc_AcAutoSwitch(param, len);
			break;
		case 0x08:
			halToAc_AcSyncSwitch(param, len);
			break;
		case 0x09:			
			halToAc_AcDemist(param, len);
			break;
		case 0x0A:			
			halToAc_Luch(param, len);
			break;
		case 0x0B:
			halToAc_SeatHeating(param, len);
			break;
		default:break;
	}
}


void halToAc_AcSwitch(u8 *p,u8 len)
{
	if(p[0] == 0x00)
	{
		if(p[1] == 0x00)
			{
				setDigitalData(CONTROLID_AIRCONDITION_OFF, 1);
				setUpdateUI(0x00);
				setSerialData(CONTROLID_AIRCONDITION_TEMP_R,(u8*)"",0);
				setSerialData(CONTROLID_AIRCONDITION_TEMP_L,(u8*)"",0);
				setUpdateUI(0x01);
				pLocalParam->bOff = 1;
				pLocalParam->ucSpeed = 0xFF;
				pLocalParam->rightTempValue = 0xFFFF;
				pLocalParam->leftTempValue = 0xFFFF;

				mistraToOSD();
			}
			else if(p[1] == 0x01)
			{
				setDigitalData(CONTROLID_AIRCONDITION_OFF, 0);
				pLocalParam->bOff = 0;
			}
				
	}
}

void halToAc_AcTemperature(u8 *p, u8 len)
{
	if(pLocalParam->bOff == 1)
		return;
	
	u16 tempL;
	u16 tempR;
	tempL =p[1] + (p[2]<<8);
	tempR =p[3] + (p[4]<<8);
	LOGD("AC TEMPERATURE:%X",tempL);
	LOGD("AC TEMPERATURE:%X",tempR);

	halToAC_Mistra_RightTemperature(p[0],tempR);
	halToAC_Mistra_LeftTemperature(p[0],tempL);
}

void halToAc_AcAirSpeed(u8 *p, u8 len)
{
	if(p[0] != 0x00&&p[0] != 0x01)
		return ;
	halToAC_Mistra_Speed(p[1]);
}

void halToAc_AcWindDirection(u8 *p, u8 len)
{
	if(p[0] == 0x00)
		
	{
		switch(p[1])
		{
			LOGD("WindDirction:  %2X  ",p[1]);
			case 0x00:
				setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 1);
				setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 0);
				break;
			case 0x01:
				setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 0);
				setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 1);
				setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 0);
				break;
			case 0x02:
				setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 0);
				setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 1);
				setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 0);
				break;
	/*
			case 0x03:
				setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 0);
				setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 1);
				break;
	*/
			case 0x04:
				setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 0);
				setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 0);
				setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 1);
				setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 0);
				break;
			case 0x05:
				break;
			default:break;
		}
	}
}

void halToAc_AcAirCycle(u8 *p, u8 len)
{
	//AC page no tag
}

void halToAc_AcRefrigeration(u8 *p, u8 len)
{
	if(p[0] == 0x00)
	{
		if(p[1] == 0x00)
			setDigitalData(CONTROLID_AIRCONDITION_A_C,0);
		else if(p[1] == 0x01)
			setDigitalData(CONTROLID_AIRCONDITION_A_C,1);
	}
	pLocalParam->ucMistraAOrCState = p[1];
	mistraToOSD();
}

void halToAc_MaxRefrigeration(u8 *p, u8 len)
{
}

void halToAc_AcAutoSwitch(u8 *p, u8 len)
{
	if(p[0] == 0x00)
	{
		if(p[1] == 0x00)
			setDigitalData(CONTROLID_AIRCONDITION_AUTO,0);
		else if(p[1] == 0x01)
			setDigitalData(CONTROLID_AIRCONDITION_AUTO,1);
	}
}

void halToAc_AcSyncSwitch(u8 *p, u8 len)
{
	if(p[0] == 0x00 || p[0] == 0x01)
		setDigitalData(CONTROLID_AIRCONDITION_SYNC ,p[0]);
}

void halToAc_AcDemist(u8 *p, u8 len)////
{
	if(p[0] == 0x00)
		setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW,0);
	else 
		if(p[0] == 0x01)
		{
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 1);
		}
}

void halToAc_Luch(u8 *p, u8 len)
{
	if(p[0] == 0x00||p[0] == 0x01)
		halToAc_AcRearStatus(p[0]);
}

void halToAc_SeatHeating(u8 *p, u8 len)
{
	if(p[0] == 0x00)
	{
		if(p[1] == 0x00||p[1] == 0x01)
		{
			halToAc_AcSeatHeatersLeft(p[1]);
		}
		
	}
	else if(p[0] == 0x01)
		{
			if(p[1] == 0x00||p[1] == 0x01)
				halToAc_AcSeatHeatersRight(p[1]);
		}
}


void moduleToAIRCONDITION_FromKey_Message(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			if(param[1] == 0x09)
			{
				u16 curPage = 0;
				unsigned char curPageLen = 2;
				getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);
				if(curPage != PAGE_AIRCONDITION)
				{
					airconditionToModule_NotifySystem_jumpPage(PAGE_AIRCONDITION);
				}
				else if(curPage == PAGE_AIRCONDITION)
				{
					airconditionToModule_NotifySystem_JumpPrePage();
				}
			}
			break;
		default:break;
	}
}

/*******************************************************************************************************/

/*************************PublicAcInfo************************/
void analyse_Public_ac_date(u8 *param, u8 len)
{
	switch(param[0])
	{
		case 0x00:
			getAirConditionSwitchStatus(param+1,len -1);
			break;
		case 0x01:
			getAirConditionTemperatureValue(param+1,len -1);
			break;
		case 0x02:
			getAirConditionWindSpeedValue(param+1,len -1);
			break;
		case 0x03:
			getAirConditionWindMode(param+1,len -1);
			break;
		case 0x04:
			getAirConditionLoopMode(param+1,len -1);
			break;
		case 0x05:
			getAirConditionACSwitchStatus(param+1,len -1);
			break;
		case 0x06:
			getAirConditionAUTOSwitchStatus(param+1,len -1);
			break;
		case 0x07:
			getAirConditionSYNCorDUALSwitchStatus(param+1,len -1);
			break;
		case 0x08:
			getAirConditionFrontGlassMistRemoval(param+1,len -1);
			break;
		case 0x09:
			getAirConditionRearwindowHeatingOrGlassMistRemoval(param+1,len -1);
			break;
		case 0x0A:
			getAirConditionHeatSeat(param+1,len -1);
			break;
		//Rear Aircondition
		case 0x80:
			getRearAirConditionSwitchStatus(param+1,len -1);
			break;
		case 0x81:
			getRearAirConditionTemperatrueData(param+1,len -1);
			break;
		case 0x82:
			getRearAirConditionWindSpeedData(param+1,len -1);
			break;
		case 0x86:
			getRearAirConditionRearAcAutoStatus(param+1,len -1);
			break;
		case 0x8B:
			getRearAirConditionControlLock(param+1,len -1);
			break;
		default:
			break;
	}
}
void getAirConditionSwitchStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToPublic_Ac_Switch_status(param[1]);
			break;
		default:
			break;
	}
}
void getAirConditionTemperatureValue(u8 *param,u8 len)
{
	switch(param[0])
		{
			case 0x00:
				{
					int minTemp = 0;
					minTemp = param[1] + (param[2] << 8);
					pLocalParam->acMinTemp = minTemp;
					int maxTemp = 0;
					maxTemp = param[3] + (param[4] << 8);
					pLocalParam->acMaxTemp = maxTemp;
					
					int nTempL = 0;
					nTempL = param[5] + (param[6] << 8);
					int nTempR = 0;
					nTempR = param[7] + (param[8] << 8);
					pLocalParam->acTempDataDigits = param[9];
					if(param[10] == 0x01 ||param[10] == 0x00)
						pLocalParam->acTempDataUnit = param[10];
					if((nTempL == pLocalParam->acTempL) && (nTempR == pLocalParam->acTempR))
						return;
					halToAC_Public_Ac_LeftTemperature(nTempL);
					halToAC_Public_Ac_RightTemperature(nTempR);

					//analysAcTempAndSendToSdk(pLocalParam->acMinTemp ,pLocalParam->acMaxTemp,pLocalParam->acTempL,pLocalParam->acTempR,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
					g_pClsAcJniSdk.analysAcTempAndSendToApp(pLocalParam->acMinTemp ,pLocalParam->acMaxTemp,pLocalParam->acTempL,pLocalParam->acTempR,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
			}
				break;
			default:
				break;
		}

	
	
	
}
void getAirConditionWindSpeedValue(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			{
				pLocalParam->acMinWindSpeed = param[1];
				pLocalParam->acMaxWindSpeed = param[2];
				 halToAC_Public_Ac_WindSpeed(param[3]);
			}
			break;
		default:
			break;
	}
}
void getAirConditionWindMode(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToAc_PublicAcWindDirection(param[1]);
			break;
		case 0x01:
			break;
		case 0x02:
			halToAc_PublicAcShowBodyButton(param[1],param[2]);
			break;
		default:
			break;
	}
}		
void getAirConditionLoopMode(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToAc_LoopModeStatus(param[1]);
			break;
		default:
			break;
	}
}
void getAirConditionACSwitchStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToAc_ACRefrigeration(param[1]);
			break;
		case 0x05:
			halToAc_ACmaxRefrigeration(param[1]);
			break;
		default:
			break;
	}
}
void getAirConditionAUTOSwitchStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToAc_PublicAcAutoSwitch(param[1]);
			break;
		default:
			break;
	}
}
void getAirConditionSYNCorDUALSwitchStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToAc_PublicAcSyncSwitch(param[1]);
			break;
		default:
			break;
	}
}
void getAirConditionFrontGlassMistRemoval(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToAc_FMistRemovalStatus(param[1]);
			break;
		case 0x05:
			halToAc_FrontWindowBlowMaxStatus(param[1]);
			break;
		default:
			break;
	}
}
void getAirConditionRearwindowHeatingOrGlassMistRemoval(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToAc_RMistRemovalStatus(param[1]);
			break;
		default:
			break;
	}
}
void getAirConditionHeatSeat(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToAc_PublicAcShowHeatSeatStatus(param[1],param[2]);
			break;
		case 0x01:
			halToAc_PublicAcShowHeatSeatGrade(param+1,len -1);
			break;
		default:
			break;
	}
}
void getBackSeatAirConditionLock(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			break;
		default:
			break;
	}
}

void getRearAirConditionSwitchStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToPublic_RearAc_Switch_status(param[1]);
			break;
		default:
			break;
	}
}

void getRearAirConditionTemperatrueData(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x03:
		{
			pLocalParam->RearAcMinTempLevel = param[1];
			pLocalParam->RearAcMaxTempLevel = param[2];
			halToAC_Public_RearAc_TempValue(param[3]);
		}
		break;
		case 0x05:
		{
			int minTemp = 0;
			minTemp = param[1] + (param[2] << 8);
			pLocalParam->RearAcMinTempV = minTemp;
			
			int maxTemp = 0;
			maxTemp = param[3] + (param[4] << 8);
			pLocalParam->RearAcMaxTempV = maxTemp;
			
			int nTempV = 0;
			nTempV = param[5] + (param[6] << 8);
		
			pLocalParam->RearAcTempDataDigits = param[7];
			pLocalParam->RearAcTempDataUnit = param[8];
			
			if(nTempV == pLocalParam->RearAcTempV)
				return;
			
			halToAC_Public_RearAc_Temperature(nTempV);
		}
		break;
		default:
			break;
	}
}

void getRearAirConditionWindSpeedData(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
		{
			pLocalParam->RearAcMinWindSpeed = param[1];
			pLocalParam->RearAcMaxWindSpeed = param[2];
			halToAC_Public_RearAc_WindSpeed(param[3]);
		}
		break;
		default:
			break;
	}
}

void getRearAirConditionControlLock(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToPublic_RearAc_ControlLock_status(param[1]);
			break;
		default:
			break;
	}
}

void getRearAirConditionRearAcAutoStatus(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			halToPublic_RearAc_Auto_status(param[1]);
			break;
		default:
			break;
	}
}

void moduleToAIRCONDITION_FromJniSdk_Message(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x01:
			if(param[1] == 0x01)
				SenfCurAcInfoToSdk();
			break;
		case 0x02:
			if(param[1] == 0x01)
				airconditionToModule_NotifySystem_jumpPage(PAGE_AIRCONDITION);
			break;
		default:break;
	}
}
void SenfCurAcInfoToSdk()
{
	sendToModuleJniSdk_AcSwitch(pLocalParam->acSwitchStatus);
	analysAcTempAndSendToSdk(pLocalParam->acMinTemp ,pLocalParam->acMaxTemp,pLocalParam->acTempL,pLocalParam->acTempR,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
	 analysAcWindSpeedAndSendToSdk(pLocalParam->acMinWindSpeed,pLocalParam->acMaxWindSpeed,pLocalParam->acWindSpeed);
	 sendToModuleJniSdk_AcWindMode(pLocalParam->acWindMode);
	 sendToModuleJniSdk_AcLoopMode(pLocalParam->acLoopMode);
	 sendToModuleJniSdk_AcAorCStatus(pLocalParam->AorCSwitchStatus);
	 sendToModuleJniSdk_AcMaxAorCStatus(pLocalParam->acMaxSwitchStatus);
	 sendToModuleJniSdk_AcAutoSwitch(pLocalParam->acAUTOSwitchStatus);
	 sendToModuleJniSdk_AcDual(pLocalParam->acSYNCStatus);
	 sendToModuleJniSdk_FrontClassMistRemoval(pLocalParam->acFMistRemovalStatus);
	 sendToModuleJniSdk_RearWindowHeat(pLocalParam->acRMistRemovalStatus);
	 sendToModuleJniSdk_HeatSeatStatus(0x00,pLocalParam->acHeatSeatStatusL);
	 sendToModuleJniSdk_HeatSeatStatus(0x01,pLocalParam->acHeatSeatStatusR);
	 //sendToModuleJniSdk_HeatSeatGrade(0x00,pLocalParam->acHeatSeatGradeL);
	 //sendToModuleJniSdk_HeatSeatGrade(0x01,pLocalParam->acHeatSeatGradeR);
}

void sendToModuleJniSdk_AcSwitch(u8 param)
{
	u8 buf[] = {0x00,0x00,param};
	setAcInfoToSdk(buf,3);
}

void sendToModuleJniSdk_AcTemp(int min,int max,int Ltemp,int Rtemp,u8 Decimal,u8 unit)
{
	u8 buf[20] = {0};
	buf[0] = 0x01;
	buf[1] = 0x00;
	memcpy(buf+2,&min,2);
	memcpy(buf+4,&max,2);
	memcpy(buf+6,&Ltemp,2);
	memcpy(buf+8,&Rtemp,2);
	buf[10] = Decimal;
	buf[11] = unit;
	setAcInfoToSdk(buf,12);
}
void sendToModuleJniSdk_AcWindSpeed(u8 min,u8 max,u8 speed)
{
	u8 buf[] = {0x02,0x00,min,max,speed};
	setAcInfoToSdk(buf,5);
}
void sendToModuleJniSdk_AcWindMode(u8 param)
{
	u8 buf[] = {0x03,0x00,param};
	setAcInfoToSdk(buf,3);
}

void sendToModuleJniSdk_AcLoopMode(u8 param)
{
	u8 buf[] = {0x04,0x00,param};
	setAcInfoToSdk(buf,3);
}
void sendToModuleJniSdk_AcAorCStatus(u8 param)
{
	u8 buf[] = {0x05,0x00,param};
	setAcInfoToSdk(buf,3);
}
void sendToModuleJniSdk_AcMaxAorCStatus(u8 param)
{
	u8 buf[] = {0x05,0x05,param};
	setAcInfoToSdk(buf,3);
}
void sendToModuleJniSdk_AcAutoSwitch(u8 param)
{
	u8 buf[] = {0x06,0x00,param};
	setAcInfoToSdk(buf,3);
}
void sendToModuleJniSdk_AcDual(u8 param)
{
	u8 buf[] = {0x07,0x00,param};
	setAcInfoToSdk(buf,3);
}
void sendToModuleJniSdk_FrontClassMistRemoval(u8 param)
{
	u8 buf[] = {0x08,0x00,param};
	setAcInfoToSdk(buf,3);
}
void sendToModuleJniSdk_RearWindowHeat(u8 param)    //Glass mist removal
{
	u8 buf[] = {0x09,0x00,param};
	setAcInfoToSdk(buf,3);
}

void sendToModuleJniSdk_HeatSeatStatus(u8 tag,u8 param) 
{
	u8 buf[] = {0x0A,0x00,tag,param};
	setAcInfoToSdk(buf,4);
}

void sendToModuleJniSdk_HeatSeatGrade(u8 tag,u8 param) 
{
	u8 buf[] = {0x0A,0x01,tag,param};
	setAcInfoToSdk(buf,4);
}

void analysAcTempAndSendToSdk(int min, int max, int tempL, int tempR,u8 Digits,u8 unit)
{
	int nL = tempL;
	int nR =tempR;
	if(nL == 0xFFF7)
		nL = pLocalParam->acMinTemp;
	else if(nL  == 0xFFF8)
		nL  = pLocalParam->acMaxTemp;
	else if(nL  == 0xFFF9)
		nL  = 0xFFFF;
	
	if(nR == 0xFFF7)
		nR = pLocalParam->acMinTemp;
	else if(nR  == 0xFFF8)
		nR  = pLocalParam->acMaxTemp;
	else if(nR  == 0xFFF9)
		nR  = 0xFFFF;

	if(nL  == 0xFFFA ||nR == 0xFFFA)
		return;
	sendToModuleJniSdk_AcTemp(min,max,nL,nR,Digits,unit);

}

void analysAcWindSpeedAndSendToSdk(u8 min, u8 max, u8 curvalue)
{
	u8 value = curvalue;
	if(value == 0xF7)
		value == pLocalParam->acMinWindSpeed;
	else if(value == 0xF8)
		value == pLocalParam->acMaxWindSpeed;
	else if(value == 0xF9)
		value = 0xFF;
	publicAcInfoToOSD( pLocalParam->acTempL, pLocalParam->acTempR,value,pLocalParam->acSwitchStatus);
	sendToModuleJniSdk_AcWindSpeed(pLocalParam->acMinWindSpeed,pLocalParam->acMaxWindSpeed,value);
}

void sendToAcTempToSdk_Golf()
{
	if(pLocalParam->e_golf_ac_degree_unit == 0x00)
	{
		int tempCL = ((pLocalParam->u8_golf_degree_left - 0x3C) + 160)*10;
		int tempCR = ((pLocalParam->u8_golf_degree_right - 0x3C) + 160)*10;
		if(pLocalParam->u8_golf_degree_left == 0xFe)
			tempCL = 3000;
		if(pLocalParam->u8_golf_degree_right == 0xFe)
			tempCR = 3000;
		if(pLocalParam->u8_golf_degree_left == 0x00)
			tempCL = 1550;
		if(pLocalParam->u8_golf_degree_right == 0x00)
			tempCR = 1550;
		
		g_pClsAcJniSdk.analysAcTempAndSendToApp(1550 ,3000,tempCL,tempCR,0x01,pLocalParam->e_golf_ac_degree_unit);
	}
	else if(pLocalParam->e_golf_ac_degree_unit == 0x01)
	{
		int tempFL = (pLocalParam->u8_golf_degree_left - 0x28) / 4 + 60;
		int tempFR = (pLocalParam->u8_golf_degree_right - 0x28) / 4 + 60;
		if(pLocalParam->u8_golf_degree_left == 0xFe)
			tempFL = 8600;
		if(pLocalParam->u8_golf_degree_right == 0xFe)
			tempFR = 8600;
		if(pLocalParam->u8_golf_degree_left == 0x00)
			tempFL = 5900;
		if(pLocalParam->u8_golf_degree_right == 0x00)
			tempFR = 5900;
		g_pClsAcJniSdk.analysAcTempAndSendToApp(5900 ,8600,tempFL,tempFR,0x01,pLocalParam->e_golf_ac_degree_unit);
	}
}
