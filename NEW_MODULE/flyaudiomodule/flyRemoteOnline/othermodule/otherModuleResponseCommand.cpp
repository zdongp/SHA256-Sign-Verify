#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"

#include "otherModuleResponseCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"
#include "appResponseCommand.h"
#include "timer_interface.h"
#include "moduleParamResponse.h"

int nCarInforPushTimes = 0;

void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){
	LOGD("Module_remoteOnline analyseOtherModuleMessage sendModuleId:%x param[0]:%x param[1]:%x",sendModuleId,param[0],param[1]);
	switch(sendModuleId){
		case MODULE_ID_EXTCAR:
			ModuleToRemoteOnline_FromExtcarMessage(param,len);
			break;
		case MODULE_ID_SYSTEM:
			ModuleToRemoteOnline_FromSystemMessage(param,len);
			break;
		case MODULE_ID_CENTER:
			ModuleToRemoteOnline_FromCenterMessage(param,len);
			break;
		default:break;
	}
}

void ModuleToRemoteOnline_FromCenterMessage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x00://0s
		{
			if(p[1] == 1)//screen off
			{
				nCarInforPushTimes = 0;
				pLocalParam->uCurCarNaviDeviceState = 1;
				pLocalParam->emCur_CD_State = Cur_CD_Mode_ScreenOff;
				AccOffMakeToCarMessage();
				ACCoffMobileRequestModule_updataExtcarInfors();
				ACCoffWeChatRequestModule_updataExtcarInfors();
				SetTimer(TIMERS_FLY_REMOTE_ONLINE_ACCOFF_SYNCDATA,0,TIMERID_FLY_REMOTE_ONLINE_ACCOFF_SYNCDATA);
			}
			else if(p[1] == 0)//screen on
			{
				nCarInforPushTimes = 0;
				DeleteTimer(TIMERID_FLY_REMOTE_ONLINE_ACCOFF_SYNCDATA);
				DeleteTimer(TIMERID_FLY_REMOTE_ONLINE_ACCOFF_CONDITION_INFORS_CHANGED);
				RemoteOnlineModule_SetDefaultParam();
				MakeToCarMessage();
				MobileRequestModule_updataExtcarInfors();
				WeChatRequestModule_updataExtcarInfors();
			}
		}
		break;
		case 0x3d://60s
		{
			if(p[1] == 1)
			{
				nCarInforPushTimes = 0;
				DeleteTimer(TIMERID_FLY_REMOTE_ONLINE_ACCOFF_SYNCDATA);
				DeleteTimer(TIMERID_FLY_REMOTE_ONLINE_ACCOFF_CONDITION_INFORS_CHANGED);
			}
		}
		break;
	}
}

void ModuleToRemoteOnline_FromExtcarMessage(u8 *p, u8 len)
{
	if(pLocalParam->sCarModels == 0){
		u8 sCar_Models = 0;
		u8 sCar_Models_Len = 1;
		getOtherModuleParam((u8)MODULE_ID_EXTCAR,(u8)EXTCAR_CAR_MODELS,(u8*)&sCar_Models,(u8*)&sCar_Models_Len);
		pLocalParam->sCarModels = (u16)sCar_Models;
	}

	bool bBatteryVoltage = false,bCarDoor = false,bEngineDoor = false,
		bCarDoorLock = false,bCarDoorWindow = false,bCarDormer = false,
		bCarHeadlight = false,bOilConsumption = false,bTotalMileage = false,
		bHandBrake = false,bResiduaMileage = false,bAverageFuelConsumption = false,
		bFootBrake = false,bWaterTempeature = false,bCleaningLiquid = false,
		bBatteryAnomalyMonitoring = false;
		
	switch(p[0])
	{
		case REMOTEONLINE_INFORS_HAND_BRAKE:
			if(pLocalParam->uCarHandBrake != p[1]){
				pLocalParam->uCarHandBrake = p[1];
				bHandBrake = true;
			}
			break;
		case REMOTEONLINE_INFORS_MAIN_DRIVER_SEAT_BELT:
			if(pLocalParam->uCarMainDriverSeatBelt != p[1]){
				pLocalParam->uCarMainDriverSeatBelt = p[1];
			}
			break;
		case REMOTEONLINE_INFORS_OIL_CONSUMPTION:
			{
				u32 nTem = 0;
				nTem += (int)((p[1] << 24) & 0xFF000000);
				nTem += (int)((p[2] << 16) & 0xFF0000);
				nTem += (int)((p[3] << 8) & 0xFF00);
				nTem += (int)(p[4] & 0xFF);

				if(pLocalParam->nCarOilConsumption != nTem){
					pLocalParam->nCarOilConsumption = nTem;
					bOilConsumption = true;
				}
			}
			break;
		case REMOTEONLINE_INFORS_TOTAL_MILEAGE:
			{
				u32 nTem = 0;
				nTem += (int)((p[1] << 24) & 0xFF000000);
				nTem += (int)((p[2] << 16) & 0xFF0000);
				nTem += (int)((p[3] << 8) & 0xFF00);
				nTem += (int)(p[4] & 0xFF);

				if(pLocalParam->nCarTotalMileage != nTem){
					pLocalParam->nCarTotalMileage = nTem;
					bTotalMileage = true;
				}
			}
			break;
		case REMOTEONLINE_INFORS_ENGINE_SPEED:
			{
				u32 nTem = 0;
				nTem += (int)((p[1] << 24) & 0xFF000000);
				nTem += (int)((p[2] << 16) & 0xFF0000);
				nTem += (int)((p[3] << 8) & 0xFF00);
				nTem += (int)(p[4] & 0xFF);

				if(pLocalParam->nCarEngineSpeed != nTem){
					pLocalParam->nCarEngineSpeed = nTem;
				}
			}
			break;
		case REMOTEONLINE_INFORS_INSTANTANOUS_SPEED:
			{
				u32 nTem = 0;
				nTem += (int)((p[1] << 24) & 0xFF000000);
				nTem += (int)((p[2] << 16) & 0xFF0000);
				nTem += (int)((p[3] << 8) & 0xFF00);
				nTem += (int)(p[4] & 0xFF);

				if(pLocalParam->nCarInstantanousSpeed != nTem){
					pLocalParam->nCarInstantanousSpeed = nTem;
				}
			}
			break;
		case REMOTEONLINE_INFORS_WATER_TEMPEATURE:
			{
				u32 nTem = 0;
				nTem += (int)((p[1] << 24) & 0xFF000000);
				nTem += (int)((p[2] << 16) & 0xFF0000);
				nTem += (int)((p[3] << 8) & 0xFF00);
				nTem += (int)(p[4] & 0xFF);

				if(pLocalParam->nCarWaterTempeature != nTem){
					pLocalParam->nCarWaterTempeature = nTem;
					bWaterTempeature = true;
				}
			}
			break;
		case REMOTEONLINE_INFORS_ACCON_BATTERY:
			{
				u32 nTem = 0;
				nTem += (int)((p[1] << 24) & 0xFF000000);
				nTem += (int)((p[2] << 16) & 0xFF0000);
				nTem += (int)((p[3] << 8) & 0xFF00);
				nTem += (int)(p[4] & 0xFF);

				if(nTem != 0)
					pLocalParam->nCurCarBatteryVoltage = nTem;

			   	LOGD("pLocalParam->nCurCarBatteryVoltage:%d nTem:%d",pLocalParam->nCurCarBatteryVoltage,nTem);
			}
			break;
		case REMOTEONLINE_INFORS_DOORS:
			if(pLocalParam->uCarDoorState != p[1]){
				bCarDoor = true;
				pLocalParam->uCarDoorState = p[1];

				LOGD("bCarDoor:%d",bCarDoor);
			}
			break;
		case REMOTEONLINE_INFORS_ENGINE_DOOR:
 			if(pLocalParam->uCarEngineDoor != p[1]){
				bEngineDoor = true;
				pLocalParam->uCarEngineDoor = p[1];

				LOGD("bEngineDoor:%d",bEngineDoor);
			}
			break;
		case REMOTEONLINE_INFORS_FOOT_BRAKE:
			if(pLocalParam->uCarFootBrake != p[1]){
				pLocalParam->uCarFootBrake = p[1];
				bFootBrake = true;
			}
			break;
		case REMOTEONLINE_INFORS_STALL:
			if(pLocalParam->uCarStall != p[1]){
				pLocalParam->uCarStall = p[1];
			}
			break;
		case REMOTEONLINE_INFORS_CLEANING_LIQUID:
			if(pLocalParam->uCarCleaningLiquid != p[1]){
				pLocalParam->uCarCleaningLiquid = p[1];
				bCleaningLiquid = true;
			}
			break;
		case REMOTEONLINE_INFORS_RESIDUA_MILEAGE:
			{
				u32 nTem = 0;
				nTem += (int)((p[1] << 24) & 0xFF000000);
				nTem += (int)((p[2] << 16) & 0xFF0000);
				nTem += (int)((p[3] << 8) & 0xFF00);
				nTem += (int)(p[4] & 0xFF);

				if(pLocalParam->nCarResiduaMileage != nTem){
					pLocalParam->nCarResiduaMileage = nTem;
					bResiduaMileage = true;
				}
			}
			break;
		case REMOTEONLINE_INFORS_AVERAGE_FUEL_CONSUMPTION:
			{
				u8 unit = p[1];
				pLocalParam->nCarAverageFuelConsumptionUnit = p[1]; 
				
				u32 nTem = 0;
				nTem += (int)((p[2] << 24) & 0xFF000000);
				nTem += (int)((p[3] << 16) & 0xFF0000);
				nTem += (int)((p[4] << 8) & 0xFF00);
				nTem += (int)(p[5] & 0xFF);

				if(pLocalParam->nCarAverageFuelConsumption != nTem){
					pLocalParam->nCarAverageFuelConsumption = nTem;
					bAverageFuelConsumption = true;
				}
			}
			break;
		case REMOTEONLINE_INFORS_TIRE_PRESSURE_UNIT:
			if(pLocalParam->nCarTirePressureUnit != p[1]){
				pLocalParam->nCarTirePressureUnit = p[1];
			}
			break;
		case REMOTEONLINE_INFORS_TIRE_TEMPEARATURE_UNIT:
			if(pLocalParam->nCarTireTempUnit != p[1]){
				pLocalParam->nCarTireTempUnit = p[1];
			}
			break;
		case REMOTEONLINE_INFORS_PRESSURE_TEMPEATATURE_VALUE_FL:
			{
				if(p[1] == 0x00){}
				else if(p[1] == 0x01){}
				else if(p[1] == 0x02){}
				else if(p[1] == 0x03){}
			}
			break;
		case REMOTEONLINE_INFORS_PRESSURE_TEMPEATATURE_VALUE_FR:
			{
				if(p[1] == 0x00){}
				else if(p[1] == 0x01){}
				else if(p[1] == 0x02){}
				else if(p[1] == 0x03){}
			}
			break;
		case REMOTEONLINE_INFORS_PRESSURE_TEMPEATATURE_VALUE_RL:
			{
				if(p[1] == 0x00){}
				else if(p[1] == 0x01){}
				else if(p[1] == 0x02){}
				else if(p[1] == 0x03){}
			}
			break;
		case REMOTEONLINE_INFORS_PRESSURE_TEMPEATATURE_VALUE_RR:
			{
				if(p[1] == 0x00){}
				else if(p[1] == 0x01){}
				else if(p[1] == 0x02){}
				else if(p[1] == 0x03){}
			}
			break;
		case REMOTEONLINE_INFORS_BATTERY_ANOMALY_MONITORING:
			if(pLocalParam->uCarBatteryAnomalyMonitoring != p[1]){
				pLocalParam->uCarBatteryAnomalyMonitoring = p[1];
				bBatteryAnomalyMonitoring = true;
			}
			break;
		case REMOTEONLINE_INFORS_OUTSID_TEMPEATURE:
			{
				u32 nTem = 0;
				nTem += (int)((p[1] << 24) & 0xFF000000);
				nTem += (int)((p[2] << 16) & 0xFF0000);
				nTem += (int)((p[3] << 8) & 0xFF00);
				nTem += (int)(p[4] & 0xFF);

				if(pLocalParam->nCarOutsidTempeature != nTem){
					pLocalParam->nCarOutsidTempeature = nTem;
				}
			}
			break;
		case REMOTEONLINE_INFORS_DOOR_LOCKS:
			if(pLocalParam->uCarDoorLock != p[1]){
				bCarDoorLock = true;
				pLocalParam->uCarDoorLock = p[1];

				LOGD("bCarDoorLock:%d",bCarDoorLock);
			}
			break;
		case REMOTEONLINE_INFORS_COPILOT_DRIVER_SEAT_BELT:
			if(pLocalParam->uCarCopilotDriverSeatBelt != p[1]){
				pLocalParam->uCarCopilotDriverSeatBelt = p[1];
			}
			break;
		case REMOTEONLINE_INFORS_DOOR_WINDOWS:
			if(	pLocalParam->uCarDoorWindow_FL != p[1] ||
				pLocalParam->uCarDoorWindow_FR != p[2] ||
				pLocalParam->uCarDoorWindow_RL != p[3] ||
				pLocalParam->uCarDoorWindow_RR != p[4]){
				bCarDoorWindow = true;
				pLocalParam->uCarDoorWindow_FL = p[1];
				pLocalParam->uCarDoorWindow_FR = p[2];
				pLocalParam->uCarDoorWindow_RL = p[3];
				pLocalParam->uCarDoorWindow_RR = p[4];

				LOGD("bCarDoorWindow:%d",bCarDoorWindow);
			}
			break;
		case REMOTEONLINE_INFORS_CAR_DORMER:
			if(pLocalParam->uCarDormer != p[1]){
				bCarDormer = true;
				pLocalParam->uCarDormer = p[1];
				LOGD("bCarDormer:%d",bCarDormer);
			}
			break;
		case REMOTEONLINE_INFORS_CAR_HEADER_LIGHT:
			if(pLocalParam->uCarHeadlight != p[1]){
				bCarHeadlight = true;
				pLocalParam->uCarHeadlight = p[1];
				LOGD("bCarHeadlight:%d",bCarHeadlight);
			}
			break;
		case REMOTEONLINE_INFORS_ACCOFF_BATTERY://ACC OFF,CarBatteryVoltageValue
			{
				int nTemAccOffBatteryValue = 0;
				nTemAccOffBatteryValue += (int)((p[1] << 24) & 0xFF000000);
		    	nTemAccOffBatteryValue += (int)((p[2] << 16) & 0xFF0000);
		    	nTemAccOffBatteryValue += (int)((p[3] << 8) & 0xFF00);
		   	 	nTemAccOffBatteryValue += (int)(p[4] & 0xFF);
				LOGD("nTemAccOffBatteryValue:%d pLocalParam->nAccOffCurCarBatteryVoltage:%d",nTemAccOffBatteryValue,pLocalParam->nAccOffCurCarBatteryVoltage);
				if(pLocalParam->nAccOffCurCarBatteryVoltage != nTemAccOffBatteryValue && nTemAccOffBatteryValue != 0)
				{
					bBatteryVoltage = true;
					pLocalParam->nAccOffCurCarBatteryVoltage = nTemAccOffBatteryValue;

					LOGD("bBatteryVoltage:%d",bBatteryVoltage);
				}
			}
			break;
		default:
			break;
	}

	switch(p[0])
	{
		case REMOTEONLINE_INFORS_ACCON_BATTERY:
		case REMOTEONLINE_INFORS_DOORS:
		case REMOTEONLINE_INFORS_ENGINE_DOOR:
		case REMOTEONLINE_INFORS_DOOR_LOCKS:
		case REMOTEONLINE_INFORS_DOOR_WINDOWS:
		case REMOTEONLINE_INFORS_CAR_DORMER:
		case REMOTEONLINE_INFORS_CAR_HEADER_LIGHT:
		case REMOTEONLINE_INFORS_ACCOFF_BATTERY:
			
		case REMOTEONLINE_INFORS_OIL_CONSUMPTION:
		case REMOTEONLINE_INFORS_TOTAL_MILEAGE:
		case REMOTEONLINE_INFORS_HAND_BRAKE:
		case REMOTEONLINE_INFORS_RESIDUA_MILEAGE:
		case REMOTEONLINE_INFORS_AVERAGE_FUEL_CONSUMPTION:
		case REMOTEONLINE_INFORS_FOOT_BRAKE:
		case REMOTEONLINE_INFORS_WATER_TEMPEATURE:
		case REMOTEONLINE_INFORS_CLEANING_LIQUID:
		case REMOTEONLINE_INFORS_BATTERY_ANOMALY_MONITORING:
		/*case REMOTEONLINE_INFORS_ENGINE_SPEED:
		case REMOTEONLINE_INFORS_INSTANTANOUS_SPEED:
		case REMOTEONLINE_INFORS_TIRE_PRESSURE_UNIT:
		case REMOTEONLINE_INFORS_TIRE_TEMPEARATURE_UNIT:
		case REMOTEONLINE_INFORS_PRESSURE_TEMPEATATURE_VALUE_FL:
		case REMOTEONLINE_INFORS_PRESSURE_TEMPEATATURE_VALUE_FR:
		case REMOTEONLINE_INFORS_PRESSURE_TEMPEATATURE_VALUE_RL:
		case REMOTEONLINE_INFORS_PRESSURE_TEMPEATATURE_VALUE_RR:
		case REMOTEONLINE_INFORS_MAIN_DRIVER_SEAT_BELT:
		case REMOTEONLINE_INFORS_COPILOT_DRIVER_SEAT_BELT:
		case REMOTEONLINE_INFORS_OUTSID_TEMPEATURE:
		case REMOTEONLINE_INFORS_STALL:*/
			MakeToCarMessage();
			AccOffMakeToCarMessage();
		break;
	}

	if(pLocalParam->emCur_CD_State)
		return;

	LOGD("%d %d %d %d %d %d %d",bBatteryVoltage, bCarDoor, bEngineDoor,bCarDoorLock,bCarDoorWindow,bCarDormer,bCarHeadlight);
	if(bBatteryVoltage || bCarDoor || bEngineDoor || bCarDoorLock || bCarDoorWindow || 
		bCarDormer || bCarHeadlight || bOilConsumption || bTotalMileage || 
		bHandBrake || bResiduaMileage || bAverageFuelConsumption || 
		bFootBrake || bWaterTempeature || bCleaningLiquid || 
		bBatteryAnomalyMonitoring)
	{
		nCarInforPushTimes++;

		LOGD("nCarInforPushTimes:%d",nCarInforPushTimes);
		if(nCarInforPushTimes > 0)
		{
			DeleteTimer(TIMERID_FLY_REMOTE_ONLINE_ACCOFF_CONDITION_INFORS_CHANGED);
			SetTimer(1000,1,TIMERID_FLY_REMOTE_ONLINE_ACCOFF_CONDITION_INFORS_CHANGED);
		}
	}
}

void ModuleToRemoteOnline_FromSystemMessage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x00:
		{
			if(pLocalParam->eLCDState == (E_DEVICE_LCD_STATE)p[1])
				return;
			
			pLocalParam->eLCDState = (E_DEVICE_LCD_STATE)p[1];

			if(pLocalParam->eRequestObject == REQUEST_OBJECT_MOBILE){
				MobileRequestModule_updataLedState();
			}
			else if(pLocalParam->eRequestObject == REQUEST_OBJECT_WECAT){
				WeChatRequestModule_updataLedState();
			}
		}
		break;
		case 0x01:
		{
			if(p[1] == 0x00)//Acc off
			{
				nCarInforPushTimes = 0;
				pLocalParam->emCur_CD_State = Cur_CD_Mode_ScreenOff;
				pLocalParam->uCurCarNaviDeviceState = 1;

				if((pLocalParam->nAccOffCurCarBatteryVoltage == -1 || pLocalParam->nAccOffCurCarBatteryVoltage == 0) && pLocalParam->nCurCarBatteryVoltage != -1 && pLocalParam->nCurCarBatteryVoltage != 0)
				{
					pLocalParam->nAccOffCurCarBatteryVoltage = pLocalParam->nCurCarBatteryVoltage;
				}
				AccOffMakeToCarMessage();
				ACCoffMobileRequestModule_updataExtcarInfors();
				ACCoffWeChatRequestModule_updataExtcarInfors();
				SetTimer(TIMERS_FLY_REMOTE_ONLINE_ACCOFF_SYNCDATA,0,TIMERID_FLY_REMOTE_ONLINE_ACCOFF_SYNCDATA);
			}
			else if(p[1] == 0x01)//Acc on
			{
				nCarInforPushTimes = 0;
				DeleteTimer(TIMERID_FLY_REMOTE_ONLINE_ACCOFF_SYNCDATA);
				DeleteTimer(TIMERID_FLY_REMOTE_ONLINE_ACCOFF_CONDITION_INFORS_CHANGED);
				RemoteOnlineModule_SetDefaultParam();
				MakeToCarMessage();
				MobileRequestModule_updataExtcarInfors();
				WeChatRequestModule_updataExtcarInfors();
			}
		}
		break;
		case 0x02:
		{
			static bool bTemSta = false;
			if(p[1] == 0x00)//standby on
			{
				if(bTemSta)
				{
					bTemSta = false;
					nCarInforPushTimes = 0;
					DeleteTimer(TIMERID_FLY_REMOTE_ONLINE_ACCOFF_SYNCDATA);
					DeleteTimer(TIMERID_FLY_REMOTE_ONLINE_ACCOFF_CONDITION_INFORS_CHANGED);
					RemoteOnlineModule_SetDefaultParam();
					MakeToCarMessage();
					MobileRequestModule_updataExtcarInfors();
					WeChatRequestModule_updataExtcarInfors();
				}
			}
			else if(p[1] == 0x01)//standby off
			{
				bTemSta = true;
			}
		}
		break;
	}
}

void MakeToCarMessage()
{
	u8 szMsg[256] = {0};

	szMsg[0]=(u8)((pLocalParam->sCarModels >> 8) & 0xff);
	szMsg[1]=(u8)(pLocalParam->sCarModels & 0xff);
	szMsg[2]=(u8)((pLocalParam->sCars >> 8) & 0xff);
	szMsg[3]=(u8)(pLocalParam->sCars & 0xff);
	szMsg[4] = pLocalParam->uCarDoorState;
	szMsg[5] = pLocalParam->uCarEngineDoor;
	szMsg[6] = pLocalParam->uCarDoorWindow_FL;
	szMsg[7] = pLocalParam->uCarDoorWindow_FR;
	szMsg[8] = pLocalParam->uCarDoorWindow_RL;
	szMsg[9] = pLocalParam->uCarDoorWindow_RR;
	szMsg[10] = pLocalParam->uCarDormer;
	szMsg[11] = pLocalParam->uCarDoorLock;
	szMsg[12] = pLocalParam->uCarHeadlight;
	szMsg[13] = pLocalParam->uCurCarNaviDeviceState;
	szMsg[14] = (u8)((pLocalParam->nCurCarBatteryVoltage >> 24) & 0xFF);
	szMsg[15] = (u8)((pLocalParam->nCurCarBatteryVoltage >> 16) & 0xFF);
	szMsg[16] = (u8)((pLocalParam->nCurCarBatteryVoltage >> 8) & 0xFF);
	szMsg[17] = (u8)(pLocalParam->nCurCarBatteryVoltage & 0xFF);

	szMsg[18] = (u8)((pLocalParam->nCarOilConsumption >> 24) & 0xFF);
	szMsg[19] = (u8)((pLocalParam->nCarOilConsumption >> 16) & 0xFF);
	szMsg[20] = (u8)((pLocalParam->nCarOilConsumption >> 8) & 0xFF);
	szMsg[21] = (u8)(pLocalParam->nCarOilConsumption & 0xFF);

	szMsg[22] = (u8)((pLocalParam->nCarTotalMileage >> 24) & 0xFF);
	szMsg[23] = (u8)((pLocalParam->nCarTotalMileage >> 16) & 0xFF);
	szMsg[24] = (u8)((pLocalParam->nCarTotalMileage >> 8) & 0xFF);
	szMsg[25] = (u8)(pLocalParam->nCarTotalMileage & 0xFF);

	szMsg[26] = pLocalParam->uCarHandBrake;

	szMsg[27] = (u8)((pLocalParam->nCarResiduaMileage >> 24) & 0xFF);
	szMsg[28] = (u8)((pLocalParam->nCarResiduaMileage >> 16) & 0xFF);
	szMsg[29] = (u8)((pLocalParam->nCarResiduaMileage >> 8) & 0xFF);
	szMsg[30] = (u8)(pLocalParam->nCarResiduaMileage & 0xFF);

	szMsg[31] = pLocalParam->nCarAverageFuelConsumptionUnit; 
	szMsg[32] = (u8)((pLocalParam->nCarAverageFuelConsumption >> 24) & 0xFF);
	szMsg[33] = (u8)((pLocalParam->nCarAverageFuelConsumption >> 16) & 0xFF);
	szMsg[34] = (u8)((pLocalParam->nCarAverageFuelConsumption >> 8) & 0xFF);
	szMsg[35] = (u8)(pLocalParam->nCarAverageFuelConsumption & 0xFF);
	
	szMsg[36] = pLocalParam->uCarFootBrake;
	
	szMsg[37] = (u8)((pLocalParam->nCarWaterTempeature >> 24) & 0xFF);
	szMsg[38] = (u8)((pLocalParam->nCarWaterTempeature >> 16) & 0xFF);
	szMsg[39] = (u8)((pLocalParam->nCarWaterTempeature >> 8) & 0xFF);
	szMsg[40] = (u8)(pLocalParam->nCarWaterTempeature & 0xFF);

	szMsg[41] = pLocalParam->uCarCleaningLiquid;

	szMsg[42] = (u8)((pLocalParam->nCarEngineSpeed >> 24) & 0xFF);
	szMsg[43] = (u8)((pLocalParam->nCarEngineSpeed >> 16) & 0xFF);
	szMsg[44] = (u8)((pLocalParam->nCarEngineSpeed >> 8) & 0xFF);
	szMsg[45] = (u8)(pLocalParam->nCarEngineSpeed & 0xFF);

	szMsg[46] = (u8)((pLocalParam->nCarInstantanousSpeed >> 24) & 0xFF);
	szMsg[47] = (u8)((pLocalParam->nCarInstantanousSpeed >> 16) & 0xFF);
	szMsg[48] = (u8)((pLocalParam->nCarInstantanousSpeed >> 8) & 0xFF);
	szMsg[49] = (u8)(pLocalParam->nCarInstantanousSpeed & 0xFF);

	szMsg[50] = pLocalParam->uCarBatteryAnomalyMonitoring;

	

	pLocalParam->nExtcarInfor_Len = CAR_INFORS_LEN;

	memset(pLocalParam->uExtcarInformation,0,sizeof(pLocalParam->uExtcarInformation));
	memcpy(pLocalParam->uExtcarInformation,szMsg,pLocalParam->nExtcarInfor_Len);

	LOGD("[%s] sCarModels:%x,sCars:%x", __FUNCTION__,pLocalParam->sCarModels,pLocalParam->sCars);
	LOGD("[%s] uCarDoorState:%x uCarEngineDoor:%x", __FUNCTION__,pLocalParam->uCarDoorState,pLocalParam->uCarEngineDoor);
	LOGD("[%s] uCarDoorWindow_FL:%x uCarDoorWindow_FR:%x,uCarDoorWindow_RL:%x pLocalParam->uCarDoorWindow_RR:%x", __FUNCTION__,pLocalParam->uCarDoorWindow_FL,pLocalParam->uCarDoorWindow_FR,pLocalParam->uCarDoorWindow_RL,pLocalParam->uCarDoorWindow_RR);
	LOGD("[%s] uCarDormer:%x uCarDoorLock:%x uCarHeadlight:%x", __FUNCTION__,pLocalParam->uCarDormer,pLocalParam->uCarDoorLock,pLocalParam->uCarHeadlight);
	LOGD("[%s] uCurCarNaviDeviceState:%x nCurCarBatteryVoltage:%d", __FUNCTION__,pLocalParam->uCurCarNaviDeviceState,pLocalParam->nCurCarBatteryVoltage);
}

void AccOffMakeToCarMessage()
{
	u8 szMsg[256] = {0};

	szMsg[0]=(u8)((pLocalParam->sCarModels >> 8) & 0xff);
	szMsg[1]=(u8)(pLocalParam->sCarModels & 0xff);
	szMsg[2]=(u8)((pLocalParam->sCars >> 8) & 0xff);
	szMsg[3]=(u8)(pLocalParam->sCars & 0xff);
	szMsg[4] = pLocalParam->uCarDoorState;
	szMsg[5] = pLocalParam->uCarEngineDoor;
	szMsg[6] = pLocalParam->uCarDoorWindow_FL;
	szMsg[7] = pLocalParam->uCarDoorWindow_FR;
	szMsg[8] = pLocalParam->uCarDoorWindow_RL;
	szMsg[9] = pLocalParam->uCarDoorWindow_RR;
	szMsg[10] = pLocalParam->uCarDormer;
	szMsg[11] = pLocalParam->uCarDoorLock;
	szMsg[12] = pLocalParam->uCarHeadlight;
	szMsg[13] = pLocalParam->uCurCarNaviDeviceState;
	szMsg[14] = (u8)((pLocalParam->nAccOffCurCarBatteryVoltage >> 24) & 0xFF);
	szMsg[15] = (u8)((pLocalParam->nAccOffCurCarBatteryVoltage >> 16) & 0xFF);
	szMsg[16] = (u8)((pLocalParam->nAccOffCurCarBatteryVoltage >> 8) & 0xFF);
	szMsg[17] = (u8)(pLocalParam->nAccOffCurCarBatteryVoltage & 0xFF);
	
	szMsg[18] = (u8)((pLocalParam->nCarOilConsumption >> 24) & 0xFF);
	szMsg[19] = (u8)((pLocalParam->nCarOilConsumption >> 16) & 0xFF);
	szMsg[20] = (u8)((pLocalParam->nCarOilConsumption >> 8) & 0xFF);
	szMsg[21] = (u8)(pLocalParam->nCarOilConsumption & 0xFF);

	szMsg[22] = (u8)((pLocalParam->nCarTotalMileage >> 24) & 0xFF);
	szMsg[23] = (u8)((pLocalParam->nCarTotalMileage >> 16) & 0xFF);
	szMsg[24] = (u8)((pLocalParam->nCarTotalMileage >> 8) & 0xFF);
	szMsg[25] = (u8)(pLocalParam->nCarTotalMileage & 0xFF);

	szMsg[26] = pLocalParam->uCarHandBrake;

	szMsg[27] = (u8)((pLocalParam->nCarResiduaMileage >> 24) & 0xFF);
	szMsg[28] = (u8)((pLocalParam->nCarResiduaMileage >> 16) & 0xFF);
	szMsg[29] = (u8)((pLocalParam->nCarResiduaMileage >> 8) & 0xFF);
	szMsg[30] = (u8)(pLocalParam->nCarResiduaMileage & 0xFF);

	szMsg[31] = pLocalParam->nCarAverageFuelConsumptionUnit; 
	szMsg[32] = (u8)((pLocalParam->nCarAverageFuelConsumption >> 24) & 0xFF);
	szMsg[33] = (u8)((pLocalParam->nCarAverageFuelConsumption >> 16) & 0xFF);
	szMsg[34] = (u8)((pLocalParam->nCarAverageFuelConsumption >> 8) & 0xFF);
	szMsg[35] = (u8)(pLocalParam->nCarAverageFuelConsumption & 0xFF);
	
	szMsg[36] = pLocalParam->uCarFootBrake;
	
	szMsg[37] = (u8)((pLocalParam->nCarWaterTempeature >> 24) & 0xFF);
	szMsg[38] = (u8)((pLocalParam->nCarWaterTempeature >> 16) & 0xFF);
	szMsg[39] = (u8)((pLocalParam->nCarWaterTempeature >> 8) & 0xFF);
	szMsg[40] = (u8)(pLocalParam->nCarWaterTempeature & 0xFF);

	szMsg[41] = pLocalParam->uCarCleaningLiquid;

	szMsg[42] = (u8)((pLocalParam->nCarEngineSpeed >> 24) & 0xFF);
	szMsg[43] = (u8)((pLocalParam->nCarEngineSpeed >> 16) & 0xFF);
	szMsg[44] = (u8)((pLocalParam->nCarEngineSpeed >> 8) & 0xFF);
	szMsg[45] = (u8)(pLocalParam->nCarEngineSpeed & 0xFF);

	szMsg[46] = (u8)((pLocalParam->nCarInstantanousSpeed >> 24) & 0xFF);
	szMsg[47] = (u8)((pLocalParam->nCarInstantanousSpeed >> 16) & 0xFF);
	szMsg[48] = (u8)((pLocalParam->nCarInstantanousSpeed >> 8) & 0xFF);
	szMsg[49] = (u8)(pLocalParam->nCarInstantanousSpeed & 0xFF);

	szMsg[50] = pLocalParam->uCarBatteryAnomalyMonitoring;

	pLocalParam->nAccOffExtcarInfor_Len = CAR_INFORS_LEN;

	memset(pLocalParam->uAccOffExtcarInformation,0,sizeof(pLocalParam->uAccOffExtcarInformation));
	memcpy(pLocalParam->uAccOffExtcarInformation,szMsg,pLocalParam->nAccOffExtcarInfor_Len);

	LOGD("[%s] sCarModels:%x,sCars:%x", __FUNCTION__,pLocalParam->sCarModels,pLocalParam->sCars);
	LOGD("[%s] uCarDoorState:%x uCarEngineDoor:%x", __FUNCTION__,pLocalParam->uCarDoorState,pLocalParam->uCarEngineDoor);
	LOGD("[%s] uCarDoorWindow_FL:%x uCarDoorWindow_FR:%x,uCarDoorWindow_RL:%x pLocalParam->uCarDoorWindow_RR:%x", __FUNCTION__,pLocalParam->uCarDoorWindow_FL,pLocalParam->uCarDoorWindow_FR,pLocalParam->uCarDoorWindow_RL,pLocalParam->uCarDoorWindow_RR);
	LOGD("[%s] uCarDormer:%x uCarDoorLock:%x uCarHeadlight:%x", __FUNCTION__,pLocalParam->uCarDormer,pLocalParam->uCarDoorLock,pLocalParam->uCarHeadlight);
	LOGD("[%s] uCurCarNaviDeviceState:%x nAccOffCurCarBatteryVoltage:%d", __FUNCTION__,pLocalParam->uCurCarNaviDeviceState,pLocalParam->nAccOffCurCarBatteryVoltage);
}



