#include "global.h"
#include "controlID.h"

#include "CNotifyAndResponseFlyJniSdk.h"
#include "appResponseFunction.h"

CNotifyAndResponseFlyJniSdk:: CNotifyAndResponseFlyJniSdk()
{

}

CNotifyAndResponseFlyJniSdk:: ~CNotifyAndResponseFlyJniSdk()
{

}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_PressureUnit(u8 param)
{
	u8 pMsg[10] = {0};
	pMsg[0] = 0x11;
	pMsg[1] = param;
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,2);
	LOGD("[%s] pMsg[0]=%d pMsg[1]=%d",__FUNCTION__,pMsg[0],pMsg[1]);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_TemperatureUnit(u8 param)
{
	u8 pMsg[10] = {0};
	pMsg[0] = 0x12;
	pMsg[1] = param;
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,2); 
	LOGD("[%s] pMsg[0]=%d pMsg[1]=%d",__FUNCTION__,pMsg[0],pMsg[1]);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_Tpms_FL(u32 Id,int param)
{
	switch(Id)
	{
		case CONTROLID_TPMS_FL_SIGN:
			sendToFlyJniSdk_Sign(0x13,param);
			break;
		case CONTROLID_TPMS_FL_BATTERY:
			sendToFlyJniSdk_Battery(0x13,param);
			break;
		case CONTROLID_TPMS_FL_TIRE_PRESSURE:
			sendToFlyJniSdk_Pressure(0x13,param);
			break;
		case CONTROLID_TPMS_FL_TEMPERATURE:
			sendToFlyJniSdk_Temperature(0x13,param);
			break;
	}
	LOGD("[%s] ",__FUNCTION__);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_Tpms_FR(u32 Id,int param)
{
	switch(Id)
	{
		case CONTROLID_TPMS_FR_SIGN:
			sendToFlyJniSdk_Sign(0x14,param);
			break;
		case CONTROLID_TPMS_FR_BATTERY:
			sendToFlyJniSdk_Battery(0x14,param);
			break;
		case CONTROLID_TPMS_FR_TIRE_PRESSURE:
			sendToFlyJniSdk_Pressure(0x14,param);
			break;
		case CONTROLID_TPMS_FR_TEMPERATURE:
			sendToFlyJniSdk_Temperature(0x14,param);
			break;
	}

}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_Tpms_RL(u32 Id,int param)
{
	switch(Id)
	{		
		case CONTROLID_TPMS_RL_SIGN:
			sendToFlyJniSdk_Sign(0x15,param);
			break;
		case CONTROLID_TPMS_RL_BATTERY:
			sendToFlyJniSdk_Battery(0x15,param);
			break;
		case CONTROLID_TPMS_RL_TIRE_PRESSURE:
			sendToFlyJniSdk_Pressure(0x15,param);
			break;
		case CONTROLID_TPMS_RL_TEMPERATURE:
			sendToFlyJniSdk_Temperature(0x15,param);
			break;
	}

}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_Tpms_RR(u32 Id,int param)
{
	switch(Id)
	{
		case CONTROLID_TPMS_RR_SIGN:
			sendToFlyJniSdk_Sign(0x16,param);
			break;
		case CONTROLID_TPMS_RR_BATTERY:
			sendToFlyJniSdk_Battery(0x16,param);
			break;
		case CONTROLID_TPMS_RR_TIRE_PRESSURE:
			sendToFlyJniSdk_Pressure(0x16,param);
			break;
		case CONTROLID_TPMS_RR_TEMPERATURE:
			sendToFlyJniSdk_Temperature(0x16,param);
			break;
	}

}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_Sign(u8 uCmd,u8 param)
{
	u8 pMsg[10] = {0};
	pMsg[0] = uCmd;
	pMsg[1] = 0x00;
	pMsg[2] = param;
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,3);  
	LOGD("[%s] pMsg[0]=%d pMsg[1]=%d  pMsg[2]=%d",__FUNCTION__,pMsg[0],pMsg[1],pMsg[2]);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_Battery(u8 uCmd,u8 param)
{
	u8 pMsg[10] = {0};
	pMsg[0] = uCmd;
	pMsg[1] = 0x01;
	pMsg[2] = param;
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,3);  
	LOGD("[%s] pMsg[0]=%d pMsg[1]=%d  pMsg[2]=%d",__FUNCTION__,pMsg[0],pMsg[1],pMsg[2]);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_Pressure(u8 uCmd,int param)
{
	u8 pMsg[10] = {0};
	pMsg[0] = uCmd;
	pMsg[1] = 0x02;
	pMsg[2] = (u8)((param >> 24) & 0xFF);
	pMsg[3] = (u8)((param >> 16) & 0xFF);
	pMsg[4] = (u8)((param >> 8) & 0xFF);
	pMsg[5] = (u8)(param & 0xFF);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,6);    
	LOGD("[%s] pMsg[0]=%d pMsg[1]=%d  pMsg[2]=%d",__FUNCTION__,pMsg[0],pMsg[1],pMsg[2]);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_Temperature(u8 uCmd,int param)
{
	u8 pMsg[10] = {0};
	pMsg[0] = uCmd;
	pMsg[1] = 0x03;
	pMsg[2] = (u8)((param >> 24) & 0xFF);
	pMsg[3] = (u8)((param >> 16) & 0xFF);
	pMsg[4] = (u8)((param >> 8) & 0xFF);
	pMsg[5] = (u8)(param & 0xFF);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,6);    
	LOGD("[%s] pMsg[0]=%d pMsg[1]=%d  pMsg[2]=%d",__FUNCTION__,pMsg[0],pMsg[1],pMsg[2]);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_Tpms_Infor(u32 Id,int param)
{
	switch(Id)
	{
		case CONTROLID_TPMS_FL_SIGN:
		case CONTROLID_TPMS_FL_BATTERY:
		case CONTROLID_TPMS_FL_TIRE_PRESSURE:
		case CONTROLID_TPMS_FL_TEMPERATURE:
			sendToFlyJniSdk_Tpms_FL(Id,param);
		break;

		
		case CONTROLID_TPMS_FR_SIGN:
		case CONTROLID_TPMS_FR_BATTERY:
		case CONTROLID_TPMS_FR_TIRE_PRESSURE:
		case CONTROLID_TPMS_FR_TEMPERATURE:
			sendToFlyJniSdk_Tpms_FR(Id,param);
		break;
				
		case CONTROLID_TPMS_RL_SIGN:
		case CONTROLID_TPMS_RL_BATTERY:
		case CONTROLID_TPMS_RL_TIRE_PRESSURE:
		case CONTROLID_TPMS_RL_TEMPERATURE:
			sendToFlyJniSdk_Tpms_RL(Id,param);
		break;
				
		case CONTROLID_TPMS_RR_SIGN:
		case CONTROLID_TPMS_RR_BATTERY:
		case CONTROLID_TPMS_RR_TIRE_PRESSURE:
		case CONTROLID_TPMS_RR_TEMPERATURE:
			sendToFlyJniSdk_Tpms_RR(Id,param);
		break;
	}
}

void CNotifyAndResponseFlyJniSdk::analyseFlyJniSdkMessage(unsigned char *p,int len)
{
  	LOGD("[%s] p[0]:%d",__FUNCTION__,p[0]);
}

