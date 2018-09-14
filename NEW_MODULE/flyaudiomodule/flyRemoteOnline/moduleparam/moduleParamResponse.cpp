#include <stdio.h>
#include <stdlib.h>


#include "global.h"
#include "moduleParamResponse.h"
#include "param.h"
#include "appResponseCommand.h"
#include "otherModuleResponseCommand.h"
#include "timer_interface.h"


extern int nCarInforPushTimes;

int module_extendInterface(char *buffer, int len)
{
   char extenCmd = buffer[0];
   char extenParam = buffer[1];
   LOGD("*********************remoteOnline module_extendInterface:%x,%x",extenCmd,extenParam);
   switch(extenCmd)
   	{
		case 0x2C: //ACC Off Or Reset Or Default
		if(extenParam == 0x00) //Acc Off
		{
			saveParameter();
		}
		else if(extenParam == 0x01)//Reset
		{  
			saveParameter();
		}
		else if(extenParam == 0x02)//Reset default
		{
		}
		break;
		case 0x2D: //ACC On
		{
		}
		break;
		case 0xFD:
		{
			getProperty_acc_status();
			if(pLocalParam->uRealAccStatus == 1){
				getProperty_Cur_carInfors();
				AccOffMakeToCarMessage();
				ACCoffMobileRequestModule_updataExtcarInfors();
				ACCoffWeChatRequestModule_updataExtcarInfors();
				SetTimer(TIMERS_FLY_REMOTE_ONLINE_ACCOFF_SYNCDATA,0,TIMERID_FLY_REMOTE_ONLINE_ACCOFF_SYNCDATA);
			}
			else 
			{
				DeleteTimer(TIMERID_FLY_REMOTE_ONLINE_ACCOFF_SYNCDATA);
				DeleteTimer(TIMERID_FLY_REMOTE_ONLINE_ACCOFF_CONDITION_INFORS_CHANGED);
				nCarInforPushTimes = 0;
				MakeToCarMessage();
				MobileRequestModule_updataExtcarInfors();
				WeChatRequestModule_updataExtcarInfors();
			}
		}
		break;
		default:break;
   	}
   	
   return 0;
}

void moduleParameterInit(void){
}

void moduleParameterDeInit(void){

}

void moduleParameterReInit(void)
{
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		default:break;
	}
}

void initRemoteOnlineParam()
{
	LOGD("[%s]", __FUNCTION__);
	RemoteOnlineModule_SetDefaultParam();
	
	pLocalParam->sCarModels = 0;
	pLocalParam->sCars = 0;
	
	pLocalParam->uCarDoorState = -1;
	pLocalParam->uCarEngineDoor = 2;

	pLocalParam->uCarDoorWindow_FL = 2;
	pLocalParam->uCarDoorWindow_FR = 2;
	pLocalParam->uCarDoorWindow_RL = 2;
	pLocalParam->uCarDoorWindow_RR = 2;

	pLocalParam->uCarDormer = 2;
	pLocalParam->uCarDoorLock = 2;
	pLocalParam->uCarHeadlight = 2;

	pLocalParam->nCurCarBatteryVoltage = -1;
	pLocalParam->nAccOffCurCarBatteryVoltage = -1;

	pLocalParam->uCarHandBrake = 2;
	pLocalParam->uCarMainDriverSeatBelt = 2;
	pLocalParam->nCarOilConsumption = -1;
	pLocalParam->nCarTotalMileage = -1;
	pLocalParam->nCarEngineSpeed = -1;
	pLocalParam->nCarInstantanousSpeed = -1;
	pLocalParam->nCarWaterTempeature = -1;
	pLocalParam->uCarFootBrake = 2;
	pLocalParam->uCarStall = 7;
	pLocalParam->uCarCleaningLiquid = 2;
	pLocalParam->nCarResiduaMileage = -1;
	pLocalParam->nCarAverageFuelConsumptionUnit = 0;
	pLocalParam->nCarAverageFuelConsumption = -1;
	pLocalParam->nCarTirePressureUnit = 0;
	pLocalParam->nCarTireTempUnit = 0;
	pLocalParam->uCarBatteryAnomalyMonitoring = 0;
	pLocalParam->nCarOutsidTempeature = -10000;
	pLocalParam->uCarCopilotDriverSeatBelt = 2;
	
	MakeToCarMessage();
	AccOffMakeToCarMessage();
}

void RemoteOnlineModule_SetDefaultParam()
{
	memset(pLocalParam->uExtcarInformation,0,sizeof(pLocalParam->uExtcarInformation));
	pLocalParam->nExtcarInfor_Len = 0;

	memset(pLocalParam->uAccOffExtcarInformation,0,sizeof(pLocalParam->uAccOffExtcarInformation));
	pLocalParam->nAccOffExtcarInfor_Len = 0;

	pLocalParam->eLCDState = DEVICE_LCDBRIGHTNESS_BLACK;
	pLocalParam->eRequestObject = REQUEST_OBJECT_UNKNOW;
	pLocalParam->uCurCarNaviDeviceState = 0;
	pLocalParam->emCur_CD_State = Cur_CD_Mode_ScreenOn;

	pLocalParam->uRealAccStatus = 0;
}

void Car_AsynchResetSystemOn_a_RegularBasis_Processing(void)
{
	for(int i = 0; i < CAR_INFORS_LEN;i++)
	{
		switch(i)
		{
			case 0:
			{
				u16 nTemV = 0;
				nTemV += (int)((pLocalParam->uAccOffExtcarInformation[0] << 8) & 0xFF00);
				nTemV += (int)(pLocalParam->uAccOffExtcarInformation[1] & 0xFF);
				pLocalParam->sCarModels = nTemV;
			}
			break;
			case 2:
			{
				u16 nTemV = 0;
				nTemV += (int)((pLocalParam->uAccOffExtcarInformation[2] << 8) & 0xFF00);
				nTemV += (int)(pLocalParam->uAccOffExtcarInformation[3] & 0xFF);
				pLocalParam->sCars = nTemV;
			}
			break;
			case 4:
			pLocalParam->uCarDoorState = pLocalParam->uAccOffExtcarInformation[4];
			break;
			case 5:
			pLocalParam->uCarEngineDoor = pLocalParam->uAccOffExtcarInformation[5];
			break;
			case 6:
			pLocalParam->uCarDoorWindow_FL = pLocalParam->uAccOffExtcarInformation[6];
			break;
			case 7:
			pLocalParam->uCarDoorWindow_FR = pLocalParam->uAccOffExtcarInformation[7];
			break;
			case 8:
			pLocalParam->uCarDoorWindow_RL = pLocalParam->uAccOffExtcarInformation[8];
			break;
			case 9:
			pLocalParam->uCarDoorWindow_RR = pLocalParam->uAccOffExtcarInformation[9];
			break;
			case 10:
			pLocalParam->uCarDormer = pLocalParam->uAccOffExtcarInformation[10];
			break;
			case 11:
			pLocalParam->uCarDoorLock = pLocalParam->uAccOffExtcarInformation[11];
			break;
			case 12:
			pLocalParam->uCarHeadlight = pLocalParam->uAccOffExtcarInformation[12];
			break;
			case 13:
			pLocalParam->uCurCarNaviDeviceState = pLocalParam->uAccOffExtcarInformation[13];
			break;
			case 14:
			{
				int nTemVOff = 0;
				nTemVOff += (int)((pLocalParam->uAccOffExtcarInformation[14] << 24) & 0xFF000000);
				nTemVOff += (int)((pLocalParam->uAccOffExtcarInformation[15] << 16) & 0xFF0000);
				nTemVOff += (int)((pLocalParam->uAccOffExtcarInformation[16] << 8) & 0xFF00);
				nTemVOff += (int)(pLocalParam->uAccOffExtcarInformation[17] & 0xFF);

				if(nTemVOff != 0)
					pLocalParam->nAccOffCurCarBatteryVoltage = nTemVOff;

				int nTemVOn = 0;
				nTemVOn += (int)((pLocalParam->uExtcarInformation[14] << 24) & 0xFF000000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[15] << 16) & 0xFF0000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[16] << 8) & 0xFF00);
				nTemVOn += (int)(pLocalParam->uExtcarInformation[17] & 0xFF);

				if(nTemVOn != 0)
					pLocalParam->nCurCarBatteryVoltage = nTemVOn;
			}
			break;
			case 18:
			{
				int nTemVOn = 0;
				nTemVOn += (int)((pLocalParam->uExtcarInformation[18] << 24) & 0xFF000000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[19] << 16) & 0xFF0000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[20] << 8) & 0xFF00);
				nTemVOn += (int)(pLocalParam->uExtcarInformation[21] & 0xFF);

				pLocalParam->nCarOilConsumption = nTemVOn;
			}
			break;
			case 22:
			{
				int nTemVOn = 0;
				nTemVOn += (int)((pLocalParam->uExtcarInformation[22] << 24) & 0xFF000000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[23] << 16) & 0xFF0000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[24] << 8) & 0xFF00);
				nTemVOn += (int)(pLocalParam->uExtcarInformation[25] & 0xFF);
				pLocalParam->nCarTotalMileage = nTemVOn;
			}
			break;
			case 26:
				pLocalParam->uCarHandBrake = pLocalParam->uExtcarInformation[26]; 
			break;
			case 27:
			{
				int nTemVOn = 0;
				nTemVOn += (int)((pLocalParam->uExtcarInformation[27] << 24) & 0xFF000000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[28] << 16) & 0xFF0000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[29] << 8) & 0xFF00);
				nTemVOn += (int)(pLocalParam->uExtcarInformation[30] & 0xFF);
				pLocalParam->nCarResiduaMileage = nTemVOn;
			}
			break;
			case 31:
			{
				pLocalParam->nCarAverageFuelConsumptionUnit = pLocalParam->uExtcarInformation[31];
				int nTemVOn = 0;
				nTemVOn += (int)((pLocalParam->uExtcarInformation[32] << 24) & 0xFF000000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[33] << 16) & 0xFF0000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[34] << 8) & 0xFF00);
				nTemVOn += (int)(pLocalParam->uExtcarInformation[35] & 0xFF);
				pLocalParam->nCarAverageFuelConsumption = nTemVOn;

			}
			break;
			case 36:
				pLocalParam->uCarFootBrake = pLocalParam->uExtcarInformation[36];
			break;
			case 37:
			{
				int nTemVOn = 0;
				nTemVOn += (int)((pLocalParam->uExtcarInformation[37] << 24) & 0xFF000000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[38] << 16) & 0xFF0000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[39] << 8) & 0xFF00);
				nTemVOn += (int)(pLocalParam->uExtcarInformation[40] & 0xFF);
				pLocalParam->nCarWaterTempeature = nTemVOn;
			}
			break;
			case 41:
				pLocalParam->uCarCleaningLiquid = pLocalParam->uExtcarInformation[41];
			break;
			case 42:
			{
				int nTemVOn = 0;
				nTemVOn += (int)((pLocalParam->uExtcarInformation[42] << 24) & 0xFF000000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[43] << 16) & 0xFF0000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[44] << 8) & 0xFF00);
				nTemVOn += (int)(pLocalParam->uExtcarInformation[45] & 0xFF);
				pLocalParam->nCarEngineSpeed = nTemVOn; 
			}
			break;
			case 46:
			{
				int nTemVOn = 0;
				nTemVOn += (int)((pLocalParam->uExtcarInformation[46] << 24) & 0xFF000000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[47] << 16) & 0xFF0000);
				nTemVOn += (int)((pLocalParam->uExtcarInformation[48] << 8) & 0xFF00);
				nTemVOn += (int)(pLocalParam->uExtcarInformation[49] & 0xFF);
				pLocalParam->nCarInstantanousSpeed = nTemVOn; 
			}
			break;
			case 50:
				pLocalParam->uCarBatteryAnomalyMonitoring = pLocalParam->uExtcarInformation[50];
			break;
		}
	}
}



