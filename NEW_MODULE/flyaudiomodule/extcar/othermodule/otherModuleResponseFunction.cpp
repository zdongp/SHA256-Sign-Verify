#include <stdio.h>
#include <stdlib.h>
#include <commonFunc.h>


#include "global.h"
#include "otherModuleResponseFunction.h"
#include "appRequestCommand.h"
#include "halRequestFunction.h"
#include "pageID.h"
#include "param.h"
#include "controlID.h"
#include "otherModuleRequestFunction.h"
#include "timer_interface.h"
#include "halResponseFunction.h"



void SystemModuleToExtcar_about_carinforvoice(u8 state)
{
	if(state)
	{
		pLocalParam->bVoicePrompt = false;
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_CARINFORVOICEPRT,0);
	}
	else
	{
		pLocalParam->bVoicePrompt = true;
		setDigitalData(CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_CARINFORVOICEPRT,1);
	}

}

void moduleToExtcar_FromSystem_Message(unsigned char *param, unsigned char len){
	LOGD("moduleToExtcar_FromSystem_Message  param[0]:%x,param[1]:%x",param[0],param[1]);
	unsigned char cmd = param[0];
	switch(cmd){
		case 0x00:
			SystemModuleToExtcar_about_carinforvoice(param[1]);
			break;
		case 0x04:
			setPublicFord_AmbientLedColor_HighModel(param[1]);
			break;
		case 0x05:
			setPublicFord_AmbientLedBrightness_HighModel(&param[1]);
			break;
		case 0x06:
			setPublicFord_DistanceUnit_HighModel(param[1]);
			break;
		case 0x2C:	// acc off
			break;
		case 0x2D:	// acc on
			break;
		case 0xEE:
			extcarToHal_set_systemPowerMode(param, len);
			break;
		case 0xE3:{	// Page Change
			u16 leavePageID = param[1] + param[2] * 0x100;
			u16 enterPageID = param[3] + param[4] * 0x100;
			int pageParam = param[5];
			LOGD("moduleToSYNC_FromSystem_Message enterPageID:%x,leavePageID:%x",enterPageID,leavePageID);

			if((enterPageID == PAGE_BACK_VIDEO || enterPageID == PAGE_BACK_RADAR || enterPageID == PAGE_BACK_NOVIDEO) && leavePageID == PAGE_GOLF_SETUP_DRIVING_MOD)
			{
				pLocalParam->bFirstGotoModePage = false;
			}
			else if(enterPageID == PAGE_BLUETOOTH_MAIN && leavePageID == PAGE_GOLF_SETUP_DRIVING_MOD)
			{
				pLocalParam->bFirstGotoModePage = false;
			}
			else if(enterPageID == PAGE_GOLF_SETUP_PERSONALIZATION_1 || enterPageID == PAGE_GOLF_SETUP_PERSONALIZATION_2)
			{
				pLocalParam->bFirstGotoModePage = false;
			}
			else if(enterPageID == PAGE_GOLF_SETUP_DRIVING_MOD)
			{
				//if(pLocalParam->bFirstGotoModePage == false){
					SetTimer(TIME_MODE_GOTO_MODE_PAGE,1,EXTCAR_TIMER_ID_GOLF_MODE_HIDEBOX);
				//}
			}
			else
			{
				if(pLocalParam->bCurMODE_State == true)
				{
					extcarToHal_set_ModeOpenOrClose(0x00);
					pLocalParam->bCurMODE_State = false;
					pLocalParam->bFirstGotoModePage = false;
				}
			}
		}
		break;
		case 0x59:
			g_clsExtcar.sendToFlyJniSdk_BatteryAnomalyMonitoring(param[1]);
		break;
		case 0x60:
		{
			int nTemBatteryValue = 0;
			memcpy(&nTemBatteryValue, param + 1, 2);
			LOGD("GetSystem ACC OFF nTemBatteryValue [%d]",nTemBatteryValue);
			g_clsExtcar.sendToFlyJniSdk_AccOffBatteryVoltageInfo(nTemBatteryValue);
		}
		break;
		case 0xf0:
			ToHal_Public_SetCarsParam(param + 1, len -1);
			break;
		default:break;

	}
}

void moduleToExtcar_FromExternalCtrl_Message(unsigned char *param, unsigned char len)
{
    if(param[0] == 0x00)
    {
    }
	else if(param[0] == 0x01)
	{
		if(param[1] == 0x01)
		{
			extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION);
		}
		else
		{
		}
	}
}

void moduleToExtcar_FromAudioVideo(unsigned char *p, int len)
{
	switch(p[0])
	{
	case 0xB1://prado
		{
			switch(p[1])
			{
			case 0x81:
				if (pLocalParam->m_pCarInfo)
				{
					pLocalParam->m_pCarInfo->setToHalAudioCtrl(p, len);
				}
				break;
			}
		}
		break;
	}
}

void moduleToExtcar_FromBackCar_Message(unsigned char *param, unsigned char len)
{
	switch(param[0])
	{
	 case 0x83://prado need coordinates
		 {
		    if(pLocalParam->m_pCarInfo)
		    {
		    	pLocalParam->m_pCarInfo->setToHalScreenCoordinates(&param[1],len-1);
		    }
		 }
		break;
	case 0xf0:
		ToHal_Public_SetCarsParam(param + 1, len -1);
	 default:
		 break;
	}
}

void moduleToExtcar_FromKey_Message(unsigned char *param, unsigned char len)
{
	switch(param[0])
		{
		 case 0x84://prado exit backcar
		 {
			   if(pLocalParam->m_pCarInfo )
			   {
			      pLocalParam->m_pCarInfo->setToHalExitBackcar(param[1]);
			   }
		 }
			 break;
		 default:
			 break;
		}
}

void moduleToExtcar_FromBT_Message(unsigned char *p, int nLen)
{
	switch(p[0])
	{
	case 0x81://golf
		extcarToHal_set_btCtrl(p, nLen);
		break;
	}
}

void moduleToExtcar_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;
    analyseAppMessage(param+1,len-1);   
}

void moduleToExtcar_FromGPS(u8 *param, int len)
{
	switch(param[0])
	{
		case 0x00:
			setPublicAuxscreenLanguage(param[1]);
		break;
		default:break;
	}
}

void moduleToExtcar_From_Public_AC_Message(u8 *p, int nLen)
{
	switch(p[0])
	{
		case 0xf0:
			extcarToHal_Public_Send_Message(p + 1, nLen -1);
		break;
		default:break;
	}
}

void moduleToExtcar_From_Public_SYNC_Message(u8 *p, int nLen)
{
	switch(p[0])
	{
		case 0xa0:
			setSyncMessageToHal(p+1 ,nLen -1);
		break;
		default:break;
	}
}

void moduleToExtcar_From_Public_Center_Message(u8 *p, int nLen)
{
	switch(p[0])
	{
		case 0x00:
			setPublicFord_TCU_FinalActivateStatus(p[1]);
		break;
		default:break;
	}
}
