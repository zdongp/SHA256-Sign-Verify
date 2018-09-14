#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleResponseFunction.h"
#include "appResponseFunction.h"
#include "appRequestFunction.h"
#include "pageID.h"
#include "otherModuleRequestFunction.h"
#include "param.h"


void moduleToTPMS_FromSystem_Message(unsigned char *param, unsigned char len)
{
	//LOGD("------------moduleToTPMS_FromSystem_Message-----------param[0]:%x param[1]:%x", param[0],param[1]);
	switch(param[0])
		{
		case 0x0B://
			{
			u8 battery = param[1];
			Get_Battery(battery);
			break;
			}
		case 0x10://resert
			break;
		case 0x14://huifuchuchang
			break;
		case 0x30: //ACC ON
			break;
		case 0x31: //ACC OFF
			break;
		case 0x0f:
			tpmsToApp_SetTPMSMenuIsEnable(param[1]);
			break;
		default:
			break;
		}
}

void Get_Battery(u8 mbattery){
//	LOGD("tpmstToUI_Infor_scroll:mbattery=%d",mbattery);
	tpmstToUI_Infor_scroll(mbattery);
}

void moduleToTPMS_FromExternalCtrl_Message(unsigned char *param, unsigned char len)
{
	if(param[0] == 0x01)
	{
		if(param[1]==0x01)
		{
			tpmsToModule_NotifySystem_JumpPage(PAGE_TPMS);
		}
		else
		{
			tpmsToModule_NotifySystem_JumpPrePage();
		}
	}
}


void moduleToTpms_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;
    analyseAppMessage(param+1,len-1);   
}

void moduleToTpms_FromExtcar(u8 *param, int len)
{   
    if(param[0] != 0xff)
   	 return;
    analysePublicTpmsHalMessage(param+1,len-1);   
}

void analysePublicTpmsHalMessage(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			getPublicTirePressureInfo(param+1, len -1);
			break;
		case 0x05:
			getPublicTireTemperatureInfo(param+1, len -1);
			break;
		default:
			break;
	}
}
void getPublicTirePressureInfo(u8 *param, u8 len)
	{
		if(len != 9)
			return;
		int nFlTp = 0;
		int nFrTp = 0;
		int nRlTp = 0;
		int nRrTp = 0;
		nFlTp = param[1] + (param[2] << 8);
		nFrTp = param[3] + (param[4] << 8);
		nRlTp = param[5] + (param[6] << 8);
		nRrTp = param[7] + (param[8] << 8);
		getTpmsTirePressureUint( param[0]);
		if(pLocalParam->publicTp_data[0] != nFlTp)
		{
			public_Tpms_TirePressure_Update(CONTROLID_TPMS_FL_TIRE_PRESSURE,nFlTp);
			pLocalParam->publicTp_data[0] = nFlTp;
		}
		if(pLocalParam->publicTp_data[1] != nFrTp)
		{
			public_Tpms_TirePressure_Update(CONTROLID_TPMS_FR_TIRE_PRESSURE,nFrTp);
			pLocalParam->publicTp_data[1] = nFrTp;
		}
		if(pLocalParam->publicTp_data[2] != nRlTp)
		{
			public_Tpms_TirePressure_Update(CONTROLID_TPMS_RL_TIRE_PRESSURE,nRlTp);
			pLocalParam->publicTp_data[2] = nRlTp;
		}
		if(pLocalParam->publicTp_data[3] != nRrTp)
		{
			public_Tpms_TirePressure_Update(CONTROLID_TPMS_RR_TIRE_PRESSURE,nRrTp);
			pLocalParam->publicTp_data[3] = nRrTp;
		}
	}

void getPublicTireTemperatureInfo(u8 *param, u8 len)
{
	if(len < 8)
		return;
	int nFlTt = 0;
	int nFrTt = 0;
	int nRlTt = 0;
	int nRrTt = 0;
	nFlTt = param[0] + (param[1] << 8);
	nFrTt = param[2] + (param[3] << 8);
	nRlTt = param[4] + (param[5] << 8);
	nRrTt = param[6] + (param[7] << 8);
	if(pLocalParam->publicTm_data[0] != nFlTt)
	{
		public_Tpms_Temperature_Update(CONTROLID_TPMS_FL_TEMPERATURE,nFlTt);
		pLocalParam->publicTm_data[0] = nFlTt;
	}
	if(pLocalParam->publicTm_data[1] != nFrTt)
	{
		public_Tpms_Temperature_Update(CONTROLID_TPMS_FR_TEMPERATURE,nFrTt);
		pLocalParam->publicTm_data[1] = nFrTt;
	}
	if(pLocalParam->publicTm_data[2] != nRlTt)
	{
		public_Tpms_Temperature_Update(CONTROLID_TPMS_RL_TEMPERATURE,nRlTt);
		pLocalParam->publicTp_data[2] = nRlTt;
	}
	if(pLocalParam->publicTm_data[3] != nRrTt)
	{
		public_Tpms_Temperature_Update(CONTROLID_TPMS_RR_TEMPERATURE,nRrTt);
		pLocalParam->publicTm_data[3] = nRrTt;
	}
}

void getTpmsTirePressureUint(u8 param)
{
	switch(param)
	{
		case 0x00:
		{
			if(pLocalParam->u8_tpms_tire_pressure_uint == Pressure_PSI)
				return;
			pLocalParam->u8_tpms_tire_pressure_uint = Pressure_PSI;
		}
		break;
		case 0x01:
		{
			if(pLocalParam->u8_tpms_tire_pressure_uint == Pressure_BAR)
				return;
			pLocalParam->u8_tpms_tire_pressure_uint = Pressure_BAR;
		}
		break;
		case 0x02:
		{
			if(pLocalParam->u8_tpms_tire_pressure_uint == Pressure_KPA)
				return;
			pLocalParam->u8_tpms_tire_pressure_uint = Pressure_KPA;
		}
		break;
		default:break;
	}
	tpms_Set_Tire_Pressure_Unit();
}

