/************************2017-11-17**************************************/
#include "acJniSdk.h"
#include "param.h"
#include <stdio.h>
#include <stdlib.h>
#include <flyutils/debug.h>
#include <cstring>

#include "appRequestCommand.h"
#include "appResponseFunction.h"
#include "otherModuleResponseFunction.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"

//
#define MESSAGETYPE_STATUS			0x00
#define MESSAGETYPE_CONTROL		0x01
//
#define AC_SWITCH						0x00
#define AC_TEMP						0x01
#define AC_WIND_SPEED				0x02
#define AC_WIND_MODE				0x03
#define AC_LOOP_MODE				0x04
#define AC_AorC_STATUS				0x05
#define AC_AUTO_SWITCH				0x06
#define AC_SYNC_SWITCH				0x07
#define AC_FRONT_REMOVAL			0x08
#define AC_REAR_REMOVAL				0x09
#define AC_HEAT_SEAT					0x0A
#define AC_BACK_SEAT_LOCK			0x0B


CAcJniSdk:: CAcJniSdk()
{

}

CAcJniSdk:: ~CAcJniSdk()
{

}
void CAcJniSdk::getSdkToModuleAcMessage(u8 *p,int len)
{
	LOGD("[%s] MessageType:%x ---p[1]:%x",__FUNCTION__,p[0],p[1]);
	switch(p[0])
	{
		case MESSAGETYPE_STATUS:
			analysSdkToAcStatusMessage(p+1,len -1);
		break;
		case MESSAGETYPE_CONTROL:
			analysSdkToAcContrlMessage(p+1,len -1);
		break;
		default:break;
	}
}
void CAcJniSdk::analysSdkToAcStatusMessage(u8 *buf,u8 len)
{
	switch(buf[0])
	{
		case 0x00:
		{
			 acSwitchSendTag = true;
			sendToApp_AcSwitch(pLocalParam->acSwitchStatus);
		}
		break;
		case 0x01:
		{
			acTempSendTag = true;
			if(pLocalParam->u8_golf_degree_left!=0xFF && pLocalParam->u8_golf_degree_right !=0xFF)
			{
				sendToAcTempToSdk_Golf();
			}
			else
				analysAcTempAndSendToApp(pLocalParam->acMinTemp ,pLocalParam->acMaxTemp,pLocalParam->acTempL,pLocalParam->acTempR,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
		}
		break;
		case 0x02:
		{
			acSeedSendTag = true;
			if(pLocalParam->u8_golf_wind_level != 0xFF)
				analysAcWindSpeedAndSendToApp(0x00,0x07,pLocalParam->u8_golf_wind_level);
			else
				analysAcWindSpeedAndSendToApp(pLocalParam->acMinWindSpeed,pLocalParam->acMaxWindSpeed,pLocalParam->acWindSpeed);
		}
		break;
		case 0x03:
		{
			acWModeSendTag = true;
			sendToApp_AcWindMode(pLocalParam->acWindMode);
		}
		break;
		case 0x04:
		{
			acLModeSendTag = true;
			sendToApp_AcLoopMode(pLocalParam->acLoopMode);
		}
		break;
		case 0x05:
		{
			acACSatusSendTag = true;
			sendToApp_AcAorCStatus(pLocalParam->AorCSwitchStatus);
		}
		break;
		case 0x06:
		{
			acACMaxSendTag = true;
			sendToApp_AcMaxAorCStatus(pLocalParam->acMaxSwitchStatus);
		}
		break;
		case 0x07:
		{
			acAutoSendTag = true;
			sendToApp_AcAutoSwitch(pLocalParam->acAUTOSwitchStatus);
		}
		break;
		case 0x08:
		{
			acSyncSendTag =true;
			sendToApp_AcDual(pLocalParam->acSYNCStatus);
		}
		break;
		case 0x09:
		{
			acFrontSendTag = true;
			sendToApp_FrontClassMistRemoval(pLocalParam->acFMistRemovalStatus);
		}
		break;
		case 0x0A:
		{
			acRearSendTag = true;
			sendToApp_RearWindowHeat(pLocalParam->acRMistRemovalStatus);
		}
		break;
		case 0x0B:
		{
			acHeatSeatSendTag = true;
			sendToApp_HeatSeatStatus(0x00,pLocalParam->acHeatSeatStatusL);
	 		sendToApp_HeatSeatStatus(0x01,pLocalParam->acHeatSeatStatusR);
		}
		break;
		case 0x0C:
		{
			acHeatGradeSendTag = true;
			sendToApp_HeatSeatGrade(0x00,pLocalParam->acHeatSeatGradeL);
			sendToApp_HeatSeatGrade(0x01,pLocalParam->acHeatSeatGradeR);
		}
		break;
		default:break;
	}
}
  
void CAcJniSdk::analysSdkToAcContrlMessage(u8 *buf,u8 len)
{
	switch(buf[0])
		{
			case 0x00:
			{
				if(buf[1] == 0x01)
					airconditionToModule_NotifySystem_jumpPage(PAGE_AIRCONDITION);
			}
			break;
			case 0x02:
			{
				if(buf[1] == 0x00 ||buf[1] == 0x01)
					setAcSwitchToHal(buf[1]);
			}
			break;
			case 0x03:
				sdkToAcSetWindSpeed(buf+1,len-1);
			break;
			case 0x04:
			{
				if(buf[1] == 0x00 ||buf[1] == 0x01)
					setAcDualSwitch(buf[1]);
			}
			break;
			case 0x05:
			{
				if(buf[1] == 0x00 ||buf[1] == 0x01)
					setAcLoopMode(buf[1]);
			}
			break;
			case 0x06:
				sdkToAcSetTempValue(buf+1,len-1);
			break;
			case 0x07:
				sdkToAcSetMistRemoval(buf+1,len-1);
			break;
			case 0x08:
			{
				if(buf[1] == 0x00 && buf[2] == 0x01)
					setPublicAcwindMode();
				else if(buf[1] == 0x01)
					setAcwindMode(buf[2]);
			}
			break;
			case 0x09:
			{
				if(buf[1] == 0x00 || buf[1] == 0x01)
					setAcAorCSwitch(buf[1]);
			}
			break;
			case 0x0a:
				setAcHeatSeatSwitch(buf[1],buf[2]);
				break;
			case 0x0b:
				if(buf[1] == 0x00 || buf[1] == 0x01)
					setAcAutoSwitch(buf[1]);
				break;
			case 0x0c:
				if(buf[1] == 0x00 || buf[1] == 0x01)
					setAcAorCMaxSwitch(buf[1]);
				break;
			case 0x0d:
				sdkToAcSetMaxMistRemoval(buf+1,len-1);
				break;
			case 0x0e:
				analyseSdkSetTempAddOrRed(buf+1,len-1);
				break;
			case 0x0f:
				analyseSdkSetWindSpeedAddOrRed(buf+1,len-1);
				break;
			default:break;
		}

}

/************************sendToAppBasicFunction*******************************/
void CAcJniSdk::sendToFlyJniSdkService(u8 moduleId, u8 *p, int len)
{
	static u8 szMsg[256] = {0};
	szMsg[0] = moduleId;

	if(len > 256)
		len = 256;
	memcpy(szMsg + 1, p, len);
	setCommand(0x51FFFE, szMsg, len + 1);
}

void CAcJniSdk::sendToAppAcStatusInfo(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = MESSAGETYPE_STATUS;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, buf, len);
	sendToFlyJniSdkService(MODULE_SDK_AC, szMsg,len+1);
}
/*****************************sendToAppFunction*****************************/
void CAcJniSdk::sendToApp_AcSwitch(u8 param)
{
	if(!acSwitchSendTag)
		return;
	u8 buf[] = {AC_SWITCH,0x00,param};
	sendToAppAcStatusInfo(buf,3);
}

void CAcJniSdk::sendToApp_AcTemp(int min,int max,int Ltemp,int Rtemp,u8 Decimal,u8 unit)
{
	if(!acTempSendTag)
		return;
	u8 buf[20] = {0};
	buf[0] = AC_TEMP;
	buf[1] = 0x00;
	memcpy(buf+2,&min,2);
	memcpy(buf+4,&max,2);
	memcpy(buf+6,&Ltemp,2);
	memcpy(buf+8,&Rtemp,2);
	buf[10] = Decimal;
	buf[11] = unit;
	sendToAppAcStatusInfo(buf,12);
}
void CAcJniSdk::sendToApp_AcWindSpeed(u8 min,u8 max,u8 speed)
{
	if(!acSeedSendTag)
		return;
	u8 buf[] = {AC_WIND_SPEED,0x00,min,max,speed};
	sendToAppAcStatusInfo(buf,5);
}
void CAcJniSdk::sendToApp_AcWindMode(u8 param)
{
	if(!acWModeSendTag)
		return;
	u8 buf[] = {AC_WIND_MODE,0x00,param};
	sendToAppAcStatusInfo(buf,3);
}

void CAcJniSdk::sendToApp_AcLoopMode(u8 param)
{
	if(!acLModeSendTag)
		return;
	u8 buf[] = {AC_LOOP_MODE,0x00,param};
	sendToAppAcStatusInfo(buf,3);
}
void CAcJniSdk::sendToApp_AcAorCStatus(u8 param)
{
	if(!acACSatusSendTag)
		return;
	u8 buf[] = {0x05,0x00,param};
	sendToAppAcStatusInfo(buf,3);
}
void CAcJniSdk::sendToApp_AcMaxAorCStatus(u8 param)
{
	if(!acACMaxSendTag)
		return;
	u8 buf[] = {AC_AorC_STATUS,0x05,param};
	sendToAppAcStatusInfo(buf,3);
}
void CAcJniSdk::sendToApp_AcAutoSwitch(u8 param)
{
	if(!acAutoSendTag)
		return;
	u8 buf[] = {AC_AUTO_SWITCH,0x00,param};
	sendToAppAcStatusInfo(buf,3);
}
void CAcJniSdk::sendToApp_AcDual(u8 param)
{
	if(!acSyncSendTag)
		return;
	u8 buf[] = {AC_SYNC_SWITCH,0x00,param};
	sendToAppAcStatusInfo(buf,3);
}
void CAcJniSdk::sendToApp_FrontClassMistRemoval(u8 param)
{
	if(!acFrontSendTag)
		return;
	u8 buf[] = {AC_FRONT_REMOVAL,0x00,param};
	sendToAppAcStatusInfo(buf,3);
}
void CAcJniSdk::sendToApp_RearWindowHeat(u8 param)    //Glass mist removal
{
	if(!acRearSendTag)
		return;
	u8 buf[] = {AC_REAR_REMOVAL,0x00,param};
	sendToAppAcStatusInfo(buf,3);
}

void CAcJniSdk::sendToApp_HeatSeatStatus(u8 tag,u8 param) 
{
	if(!acHeatSeatSendTag)
		return;
	u8 buf[] = {AC_HEAT_SEAT,0x00,tag,param};
	sendToAppAcStatusInfo(buf,4);
}

void CAcJniSdk::sendToApp_HeatSeatGrade(u8 tag,u8 param) 
{
	if(!acHeatGradeSendTag)
		return;
	u8 buf[] = {AC_HEAT_SEAT,0x01,tag,param};
	sendToAppAcStatusInfo(buf,4);
}

void CAcJniSdk::analysAcTempAndSendToApp(int min, int max, int tempL, int tempR,u8 Digits,u8 unit)
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
	sendToApp_AcTemp(min,max,nL,nR,Digits,unit);

}

void CAcJniSdk::analysAcWindSpeedAndSendToApp(u8 min, u8 max, u8 curvalue)
{
	u8 value = curvalue;
	if(value == 0xF7)
		value == pLocalParam->acMinWindSpeed;
	else if(value == 0xF8)
		value == pLocalParam->acMaxWindSpeed;
	else if(value == 0xF9)
		value = 0xFF;
	sendToApp_AcWindSpeed(pLocalParam->acMinWindSpeed,pLocalParam->acMaxWindSpeed,value);
}

void CAcJniSdk::sdkToAcSetWindSpeed(u8 *buf,u8 len)
{
	switch(buf[0])
	{
		case 0x00:
		{
			setAcwindSpeed(buf[1],pLocalParam->acMinWindSpeed,pLocalParam->acMaxWindSpeed);
		}
		break;
		case 0x01:
		{
			if(buf[1] == 0x00)
				setPublicWindSpeedAddOrDec(0x02);
			else if(buf[1] == 0x01)
				setPublicWindSpeedAddOrDec(0x01);
		}
		break;
		default:
			LOGD("[%s] buf[0]:%x",__FUNCTION__,buf[0]);
		break;
	}
}

void CAcJniSdk::sdkToAcSetTempValue(u8 *buf,u8 len)
{
	switch(buf[0])
	{
		case 0x00:
		{
			if(buf[1] == 0x00)
			{
				int paramL = buf[2] + (buf[3] << 8);
				int paramR = buf[4] + (buf[5] << 8);
				setAcTemperature(paramL,paramR,pLocalParam->acMinTemp,pLocalParam->acMaxTemp,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
			}
		}
		break;
		case 0x01:		//Left
		{
			if(buf[1] == 0x00)
			{
				int param = buf[2] + (buf[3] << 8);
				setAcTemperature(param,pLocalParam->acTempR,pLocalParam->acMinTemp,pLocalParam->acMaxTemp,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
			}
			else if(buf[1] == 0x01)
			{
				setLeftTemperatureAddOrLow(0x01,buf[2]);
			}
		}
		break;
		case 0x02:		//right
		{
			if(buf[1] == 0x00)
			{
				int param1 = buf[2] + (buf[3] << 8);
				setAcTemperature(pLocalParam->acTempL,param1,pLocalParam->acMinTemp,pLocalParam->acMaxTemp,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
			}
			else if(buf[1] == 0x01)
			{
				setLeftTemperatureAddOrLow(0x02,buf[2]);
			}
		}
		break;
		default:
			LOGD("[%s] buf[0]:%x",__FUNCTION__,buf[0]);
		break;
	}
}


void CAcJniSdk::sdkToAcSetMistRemoval(u8 *buf,u8 len)
{
	switch(buf[0])
	{
		case 0x00:
		{
			if(buf[1] == 0x00 ||buf[1] == 0x01)
				setAcFWindowHeating(buf[1]);
		}
		break;
		case 0x01:
		{
			if(buf[1] == 0x00 ||buf[1] == 0x01)
				setAcRearWindowHeating(buf[1]);
		}
		break;
		default:
			LOGD("[%s] buf[0]:%x",__FUNCTION__,buf[0]);
		break;
	}
}

void CAcJniSdk::sdkToAcSetMaxMistRemoval(u8 *buf,u8 len)
{
	switch(buf[0])
	{
		case 0x00:
		{
			if(buf[1] == 0x00 ||buf[1] == 0x01)
				setAcFrontWindowBlowMax(buf[1]);
		}
		break;
		case 0x01:
		break;
		default:
			LOGD("[%s] buf[0]:%x",__FUNCTION__,buf[0]);
		break;
	}
}

void CAcJniSdk::analyseSdkSetTempAddOrRed(u8 *buf,int len)
{
	if(buf[0] == 0x00)	//All
		analyseSdkSetTempAddOrRed_All(buf+1,len -1);
	else if(buf[0] == 0x01)   //left
		analyseSdkSetTempAddOrRed_Left(buf+1,len -1);
	else if(buf[0] == 0x02) //right
		analyseSdkSetTempAddOrRed_Right(buf+1,len -1);
}

void CAcJniSdk::analyseSdkSetTempAddOrRed_All(u8 *buf,int len)
{
	int tempL = 0;
	int tempR = 0;
	int tempStep = 0;
	switch(buf[0])
	{
		case 0x00:
		{
			tempStep = buf[2] + (buf[3] << 8);
			if(buf[1] == 0x00)
			{
				tempL = pLocalParam->acTempL - tempStep;
				tempR = pLocalParam->acTempR - tempStep;
			}
			else if(buf[1] == 0x01)
			{
				tempL = pLocalParam->acTempL + tempStep;
				tempR = pLocalParam->acTempR + tempStep;
			}
		}
		break;
		case 0x01:
		{
			int tempStep1 = (pLocalParam->acMaxTemp -pLocalParam->acMinTemp)/500;
			tempStep = tempStep1 *100;
			if(buf[1] == 0x00)
			{
				tempL = pLocalParam->acTempL - tempStep;
				tempR = pLocalParam->acTempR - tempStep;
			}
			else if(buf[1] == 0x01)
			{
				tempL = pLocalParam->acTempL + tempStep;
				tempR = pLocalParam->acTempR + tempStep;
			}
		}
		break;
		case 0x02:
		{
			if(buf[1] == 0x00)
			{
				tempL = pLocalParam->acMinTemp;
				tempR = pLocalParam->acMinTemp;
			}
			else if(buf[1] == 0x01)
			{
				tempL = pLocalParam->acMaxTemp;
				tempR = pLocalParam->acMaxTemp;
			}
		}
		break;
		default:break;
	}
	if(tempL != 0x00 && tempR != 0x00)
	{
		if(tempL > pLocalParam->acMaxTemp)
			tempL = pLocalParam->acMaxTemp;
		if(tempL < pLocalParam->acMinTemp)
			tempL = pLocalParam->acMinTemp;
		if(tempR > pLocalParam->acMaxTemp)
			tempR = pLocalParam->acMaxTemp;
		if(tempR < pLocalParam->acMinTemp)
			tempR = pLocalParam->acMinTemp;
		setAcTemperature(tempL,tempR,pLocalParam->acMinTemp,pLocalParam->acMaxTemp,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
	}
}

void CAcJniSdk::analyseSdkSetTempAddOrRed_Left(u8 *buf,int len)
{
	int tempL = pLocalParam->acTempL;
	int tempStep = 0;
	switch(buf[0])
	{
		case 0x00:
		{
			tempStep = buf[2] + (buf[3] << 8);
			if(buf[1] == 0x00)
			{
				tempL = tempL - tempStep;
			}
			else if(buf[1] == 0x01)
			{
				tempL = tempL + tempStep;
			}
		}
		break;
		case 0x01:
		{
			int tempStep1 = (pLocalParam->acMaxTemp -pLocalParam->acMinTemp)/500;
			tempStep = tempStep1 *100;
			if(buf[1] == 0x00)
			{
				tempL = tempL - tempStep;
			}
			else if(buf[1] == 0x01)
			{
				tempL = tempL + tempStep;
			}
		}
		break;
		case 0x02:
		{
			if(buf[1] == 0x00)
			{
				tempL = pLocalParam->acMinTemp;
			}
			else if(buf[1] == 0x01)
			{
				tempL = pLocalParam->acMaxTemp;
			}
		}
		break;
		default:break;
	}
	if(tempL != pLocalParam->acTempL)
	{
		if(tempL > pLocalParam->acMaxTemp)
			tempL = pLocalParam->acMaxTemp;
		if(tempL < pLocalParam->acMinTemp)
			tempL = pLocalParam->acMinTemp;
		setAcTemperature(tempL,pLocalParam->acTempR,pLocalParam->acMinTemp,pLocalParam->acMaxTemp,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
	}
}
void CAcJniSdk::analyseSdkSetTempAddOrRed_Right(u8 *buf,int len)
{
	int tempR = pLocalParam->acTempR;
	int tempStep = 0;
	switch(buf[0])
	{
		case 0x00:
		{
			tempStep = buf[2] + (buf[3] << 8);
			if(buf[1] == 0x00)
			{
				tempR = tempR - tempStep;
			}
			else if(buf[1] == 0x01)
			{
				tempR = tempR + tempStep;
			}
		}
		break;
		case 0x01:
		{
			int tempStep1 = (pLocalParam->acMaxTemp -pLocalParam->acMinTemp)/500;
			tempStep = tempStep1 *100;
			if(buf[1] == 0x00)
			{
				tempR = tempR - tempStep;
			}
			else if(buf[1] == 0x01)
			{
				tempR = tempR + tempStep;
			}
		}
		break;
		case 0x02:
		{
			if(buf[1] == 0x00)
			{
				tempR = pLocalParam->acMinTemp;
			}
			else if(buf[1] == 0x01)
			{
				tempR = pLocalParam->acMaxTemp;
			}
		}
		break;
		default:break;
	}
	if(tempR != pLocalParam->acTempR)
	{
		if(tempR > pLocalParam->acMaxTemp)
			tempR = pLocalParam->acMaxTemp;
		if(tempR < pLocalParam->acMinTemp)
			tempR = pLocalParam->acMinTemp;
		setAcTemperature(pLocalParam->acTempL,tempR,pLocalParam->acMinTemp,pLocalParam->acMaxTemp,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
	}
}

void CAcJniSdk::analyseSdkSetWindSpeedAddOrRed(u8 *buf,int len)
{
	int tempWind = 0xFF;
	int step = 0;
	switch(buf[0])
	{
		case 0x00:
		{
			step = buf[2];
			if(buf[1] == 0x00)
				tempWind =  pLocalParam->acWindSpeed - step;
			else if(buf[1] == 0x01)
				tempWind =  pLocalParam->acWindSpeed + step;
		}
		break;
		case 0x01:
		{
			step = 1;
			if(buf[1] == 0x00)
				tempWind = pLocalParam->acWindSpeed - step;
			else if(buf[1] == 0x01)
				tempWind = pLocalParam->acWindSpeed + step;
		}
		break;
		case 0x02:
		{
			if(buf[1] == 0x00)
				tempWind = pLocalParam->acMinWindSpeed;
			else if(buf[1] == 0x01)
				tempWind = pLocalParam->acMaxWindSpeed;
		}
		break;
		default:break;
	}
	if(tempWind !=0xFF)
	{
		if(tempWind > pLocalParam->acMaxWindSpeed)
			tempWind = pLocalParam->acMaxWindSpeed;
		if(tempWind < pLocalParam->acMinWindSpeed )
			tempWind = pLocalParam->acMinWindSpeed;
		setAcwindSpeed(tempWind,pLocalParam->acMinWindSpeed,pLocalParam->acMaxWindSpeed);
	}
}