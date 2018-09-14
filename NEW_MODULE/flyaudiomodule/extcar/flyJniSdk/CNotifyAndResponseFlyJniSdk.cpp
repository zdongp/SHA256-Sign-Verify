#include "CNotifyAndResponseFlyJniSdk.h"
#include "appResponseFunction.h"
#include "param.h"
#include "appRequestCommand.h"
#include "halRequestFunction.h"





CNotifyAndResponseFlyJniSdk:: CNotifyAndResponseFlyJniSdk()
{

}

CNotifyAndResponseFlyJniSdk:: ~CNotifyAndResponseFlyJniSdk()
{

}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_HandLocker(u8 state)
{
	LOGD("[%s] state:%d",__FUNCTION__,state);
    u8 buf[] = {0x01,0x00};
	buf[1] = state;
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,2);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_SafetyBelt(u8 state)
{
	LOGD("[%s] state:%d",__FUNCTION__,state);
    u8 buf[] = {0x02,0x00};
	buf[1] = state;
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,2);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_OilRemind(int param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 pMsg[10] = {0};
	pMsg[0] = 0x03;
	pMsg[1] = (u8)((param >> 24) & 0xFF);
	pMsg[2] = (u8)((param >> 16) & 0xFF);
	pMsg[3] = (u8)((param >> 8) & 0xFF);
	pMsg[4] = (u8)(param & 0xFF);
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,5); 
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,pMsg,5);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_DrivingDistance(int param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 pMsg[10] = {0};
	pMsg[0] = 0x04;
	pMsg[1] = (u8)((param >> 24) & 0xFF);
	pMsg[2] = (u8)((param >> 16) & 0xFF);
	pMsg[3] = (u8)((param >> 8) & 0xFF);
	pMsg[4] = (u8)(param & 0xFF);
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,5);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,pMsg,5);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_EngineSpeed(int param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 pMsg[10] = {0};
	pMsg[0] = 0x05;
	pMsg[1] = (u8)((param >> 24) & 0xFF);
	pMsg[2] = (u8)((param >> 16) & 0xFF);
	pMsg[3] = (u8)((param >> 8) & 0xFF);
	pMsg[4] = (u8)(param & 0xFF);
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,5);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,pMsg,5);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_InstantSpeed(int param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 pMsg[10] = {0};
	pMsg[0] = 0x06;
	pMsg[1] = (u8)((param >> 24) & 0xFF);
	pMsg[2] = (u8)((param >> 16) & 0xFF);
	pMsg[3] = (u8)((param >> 8) & 0xFF);
	pMsg[4] = (u8)(param & 0xFF);
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,5);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,pMsg,5);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_DegreeOfWater(int param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 pMsg[10] = {0};
	pMsg[0] = 0x07;
	pMsg[1] = (u8)((param >> 24) & 0xFF);
	pMsg[2] = (u8)((param >> 16) & 0xFF);
	pMsg[3] = (u8)((param >> 8) & 0xFF);
	pMsg[4] = (u8)(param & 0xFF);
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,5);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,pMsg,5);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_BatteryVoltageInfo(int param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 pMsg[10] = {0};
	pMsg[0] = 0x08;
	pMsg[1] = (u8)((param >> 24) & 0xFF);
	pMsg[2] = (u8)((param >> 16) & 0xFF);
	pMsg[3] = (u8)((param >> 8) & 0xFF);
	pMsg[4] = (u8)(param & 0xFF);
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,5);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,pMsg,5);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_DoorInfo(char param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
    u8 buf[] = {0x09,0x00};
	buf[1] = param;
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,2);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_EngineDoorInfo(char param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
    u8 buf[] = {0x0a,0x00};
	buf[1] = param;
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,2); 
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_FootLockState(char param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
    u8 buf[] = {0x0b,0x00};
	buf[1] = param;
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,2);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_GearState(char param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
    u8 buf[] = {0x0c,0x00};
	buf[1] = param;
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,2); 
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_CleanWaterStatus(char param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 buf[] = {0x0d,0x00};
	buf[1] = param;
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,2); 
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_MileageCanRun(int param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 pMsg[10] = {0};
	pMsg[0] = 0x0e;
	pMsg[1] = (u8)((param >> 24) & 0xFF);
	pMsg[2] = (u8)((param >> 16) & 0xFF);
	pMsg[3] = (u8)((param >> 8) & 0xFF);
	pMsg[4] = (u8)(param & 0xFF);
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,5);  
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,pMsg,5);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_AvgOilWearInfo(char cUnit,int param)
{
	LOGD("[%s] cUnit:%d param:%d",__FUNCTION__,cUnit,param);
	u8 pMsg[10] = {0};
	pMsg[0] = 0x0f;
	pMsg[1] = cUnit;
	pMsg[2] = (u8)((param >> 24) & 0xFF);
	pMsg[3] = (u8)((param >> 16) & 0xFF);
	pMsg[4] = (u8)((param >> 8) & 0xFF);
	pMsg[5] = (u8)(param & 0xFF);
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,6); 
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,pMsg,6);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_BatteryAnomalyMonitoring(u8 param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 buf[] = {0x17,0x00};
	buf[1] = param;
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_DegreeOfCarGround(int param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 pMsg[10] = {0};
	pMsg[0] = 0x40;
	pMsg[1] = (char)((param >> 24) & 0xFF);
	pMsg[2] = (char)((param >> 16) & 0xFF);
	pMsg[3] = (char)((param >> 8) & 0xFF);
	pMsg[4] = (char)(param & 0xFF);
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,pMsg,5);  
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,pMsg,5);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_CarLocker(char param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 buf[] = {0x41,0x00};
	buf[1] = param;
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,2); 
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_TheCopilot_SafetyBelt(char state)
{
	LOGD("[%s] param:%d",__FUNCTION__,state);
	u8 buf[] = {0x42,0x00};
	buf[1] = state;
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,2);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_CarDoorWindow(u8 * param,int len)
{
	u8 buf[] = {0x43,0x00,0x00,0x00,0x00};
	memcpy(&buf[1],param,len);
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,5); 
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,5);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_CarDormer(char param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
    u8 buf[] = {0x44,0x00};
	buf[1] = param;
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,2);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_CarHeadlight(char param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
    u8 buf[] = {0x45,0x00};
	buf[1] = param;
	//makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_FLYJNISDK,buf,2);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdk_AccOffBatteryVoltageInfo(int param)
{
	LOGD("[%s] param:%d",__FUNCTION__,param);
	u8 pMsg[10] = {0};
	pMsg[0] = 0x46;
	pMsg[1] = (u8)((param >> 24) & 0xFF);
	pMsg[2] = (u8)((param >> 16) & 0xFF);
	pMsg[3] = (u8)((param >> 8) & 0xFF);
	pMsg[4] = (u8)(param & 0xFF);
	makeAndSendMessageToModule(MODULE_ID_EXTCAR,MODULE_ID_REMOTEONLINE,pMsg,5);
}

/*****************************AnalyseFunction*****************************/
void CNotifyAndResponseFlyJniSdk::analyseFlyJniSdkMessage(unsigned char *p,int len)
{
  	LOGD("[%s] p[0]:%d",__FUNCTION__,p[0]);
	switch(p[0])
	{
		case 0x00:
			analyseFlyJniSdkStatusMessage(p + 1,len -1);
		break;
		case 0x01:
			analyseFlyJniSdkCtrlMessage(p + 1,len -1);
		break;
		default:break;
	}
}

void CNotifyAndResponseFlyJniSdk::analyseFlyJniSdkStatusMessage(unsigned char *p,int len)
{
  	LOGD("[%s] p[0]:%d",__FUNCTION__,p[0]);
	switch(p[0])
	{
		case 0x00:
		{
			if(p[1] == 0x00)
			{
				extcarSendSeatBeltsStatusToSdk(pLocalParam->eSafetyBeltStatus);
			}
		}
			break;
		case 0x01:
		{
			if(p[1] == 0x00)
				extcarSendRemainOilToSdk(pLocalParam->nOilRemind);
		}
			break;
		case 0x02:
		{
			if(p[1] == 0x00)
			{
				int temp = pLocalParam->publicDrivingDistance;
				if(temp == -1)
					temp = 0xFFFFFFFF;
				extcarSendDriveMileageToSdk(temp);
			}
		}
		break;
		case 0x03:
		{
			if(p[1] == 0x00)
			{
				extcarSendOutSideTemperatureToSdk(pLocalParam->publicDegreeOfCarGround,
					pLocalParam->CarGroundDecimalNumber,pLocalParam->CarGroundUnit ,pLocalParam->CarGroundPosOrNeg);
			}
		}
		break;
		case 0x04:
		{
			if(p[1] == 0x00)
				extcarSendHandBrakeStatusToSdk(pLocalParam->eHandLockerStatus);
		}
		break;
		case 0x05:
		{
			if(p[1] == 0x00)
				extcarSendEngineSpeedToSdk(pLocalParam->publicEngineSpeed);
		}
		break;
		case 0x06:
		{
			if(p[1] == 0x00)
				extcarSendPublicAverageSpeedToSdk(pLocalParam->publicAverageSpeed);
		}
		break;
		case 0x07:
		{
			if(p[1] == 0x00)
			{
				if(pLocalParam->nInstantSpeed > 0 )
					extcarSendInstantSpeedToSdk(pLocalParam->nInstantSpeed);
				else
					extcarSendInstantSpeedToSdk(pLocalParam->publicnIStantSpeed);
			}
		}
		break;
		case 0x08:
		{
			if(p[1] == 0x00)
				extcarSendBatteryVoltageToSdk(pLocalParam->nBatteryVoltage);
		}
		break;
		case 0x0B:
		{
			if(p[1] == 0x00)
				extcarSendContinuedDriveMileageToSdk(pLocalParam->ContinuedDriveMileage);
		}
		break;
		case 0x0D:
		{
			if(p[1] == 0x00)
				extcarSendAverageFuelConsumptionToSdk(pLocalParam->avgOilWear);
		}
		break;
		case 0x0E:
		{
			if(p[1] == 0x00)
				extcarSendDoorStatusToSdk(pLocalParam->szDoorStatus,4);
		}
		break;
		case 0x10:
		{
			if(p[1] == 0x00)
				extcarSendDoorLockStatusToSdk(pLocalParam->szDoorLockStatus,4);
		}
		break;
		case 0x11:
		{
			if(p[1] == 0x00)
				extcarSendTrunkStatusToSdk(pLocalParam->szDoorStatus[4]);
		}
		break;
		case 0x12:
		{
			if(p[1] == 0x00)
				extcarSendFrontCoverStatusToSdk(pLocalParam->nFrontCover);
		}
		break;
		case 0x13:
		{
			if(p[1] == 0x00)
				extcarSendSkyLightStatusToSdk(pLocalParam->nSkyLight);
		}
		break;
		case 0x16:
		{
			if(p[1] == 0x05)
				extcarSendLightStatusToSdk(p[1],pLocalParam->nHighBeam);
			else if(p[1] == 0x0A)
				extcarSendLightStatusToSdk(p[1],pLocalParam->nDippedHeadlight);
		}
		break;
		case 0x18:
		{
			if(p[1] == 0x00)
				extcarSendGearsInfoToSdk(pLocalParam->nGearsValue);
		}
		break;
		case 0x1B:
		{
			if(p[1] == 0x00)
				extcarSendVINCodeToSdk(pLocalParam->szVINCode,strlen((char *)pLocalParam->szVINCode));
		}
		break;
		default:break;
	}
}

void CNotifyAndResponseFlyJniSdk::analyseFlyJniSdkCtrlMessage(unsigned char *p,int len)
{
  	LOGD("[%s] p[0]:%d",__FUNCTION__,p[0]);
	switch(p[0])
	{
		case 0x01:
		{
			analyseFindCarFeedBackInfo(p+1,len -1);
		}
		break;
		case 0x02:
		{
			analyseDrivingAutoLockInfo(p+1,len -1);
		}
		break;
		case 0x03:
		{
			analyseFollowMeHomeInfo(p+1,len -1);
		}
		break;
		case 0x04:
			analyseSdkToModuleSkylightControl(p+1,len -1);
		break;
		default:break;
	}
}

void CNotifyAndResponseFlyJniSdk::analyseFindCarFeedBackInfo(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
		{
			if(param[1] == 0x01||param[1] == 0x02||param[1] == 0xFF)
				setPublicPositionVehicleFindingFeedback(param[1]);
		}
		break;
		default:break;
	}
}
void CNotifyAndResponseFlyJniSdk::analyseDrivingAutoLockInfo(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00:
		{
			if(param[1] == 0x01||param[1] == 0x00||param[1] == 0xFF)
				setPublicPositionDrivingAutomaticLatchSwitchAndDrivingSpeedSwitch(param[1]);
		}
		break;
		case 0x01:
		{
		}
		break;
		default:break;
	}
}
void CNotifyAndResponseFlyJniSdk::analyseFollowMeHomeInfo(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x01:
		{
			u16 nTime = 0;
			memcpy(&nTime,param,2);
			LOGD("%s : %d",__FUNCTION__,nTime);
			MakeLampCompanyHomeTimeData(nTime);
		}
		break;
		default:break;
	}
}
void CNotifyAndResponseFlyJniSdk::analyseSdkToModuleSkylightControl(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x01:
		{
			if(param[1] == 0x00 || param[1] == 0x01)
			setSkylightControlMessageToHal(param[1]);
		}
		break;
		default:break;
	}
}

/************************sendToAppBasicFunction*******************************/
void CNotifyAndResponseFlyJniSdk::sendToAppExtcarStatusInfo(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = MESSAGETYPE_STATUS;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, buf, len);
	sendExtcarToFlyJniSdkService(MODULE_SDK_EXTCAR, szMsg,len+1);
}

/*****************************sendToAppFunction*****************************/
void	 CNotifyAndResponseFlyJniSdk::extcarSendSeatBeltsStatusToSdk(u8 param)
{
	if(param == SATETY_BELT_UNKNOW)
		param = 0xFF;
	else if(param == SATETY_BELT_UNLOCKED)
		param = 0x00;
	else if(param == SATETY_BELT_LOCKED)
		param  = 0x01;
	u8 buf[] = {0x00,0x00,param};
	sendToAppExtcarStatusInfo(buf,3);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendRemainOilToSdk(int param)
{
	u8 pMsg[4] = {0};
	pMsg[0] = 0x01;
	pMsg[1] = 0x00;
	memcpy(pMsg+2,&param,2);
	sendToAppExtcarStatusInfo(pMsg,4);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendDriveMileageToSdk(int param)
{
	u8 pMsg[6] = {0};
	pMsg[0] = 0x02;
	pMsg[1] = 0x00;
	memcpy(pMsg+2,&param,4);
	sendToAppExtcarStatusInfo(pMsg,6);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendOutSideTemperatureToSdk(int nTemp,u8 nDecimal,u8 nUnit ,u8 PosOrNeg)
{
	u8 pMsg[7] = {0};
	pMsg[0] = 0x03;
	pMsg[1] = 0x00;
	memcpy(pMsg+2,&nTemp,2);
	pMsg[4] = nDecimal;
	pMsg[5] = nUnit;
	pMsg[6] = PosOrNeg;
	sendToAppExtcarStatusInfo(pMsg,7);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendHandBrakeStatusToSdk(u8 param)
{
	if(param == HAND_LOCKER_UNKNOW)
		param = 0xFF;
	else if(param == HAND_LOCKER_UNLOCKED)
		param = 0x00;
	else if(param == HAND_LOCKER_LOCKED)
		param  = 0x01;
	u8 buf[] = {0x04,0x00,param};
	sendToAppExtcarStatusInfo(buf,3);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendEngineSpeedToSdk(int param)
{
	u8 pMsg[4] = {0};
	pMsg[0] = 0x05;
	pMsg[1] = 0x00;
	memcpy(pMsg+2,&param,2);
	sendToAppExtcarStatusInfo(pMsg,4);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendPublicAverageSpeedToSdk(int param)
{
	u8 pMsg[4] = {0};
	pMsg[0] = 0x06;
	pMsg[1] = 0x00;
	memcpy(pMsg+2,&param,2);
	sendToAppExtcarStatusInfo(pMsg,4);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendInstantSpeedToSdk(int param)
{
	u8 pMsg[4] = {0};
	pMsg[0] = 0x07;
	pMsg[1] = 0x00;
	memcpy(pMsg+2,&param,2);
	sendToAppExtcarStatusInfo(pMsg,4);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendBatteryVoltageToSdk(int param)
{
	u8 pMsg[4] = {0};
	pMsg[0] = 0x08;
	pMsg[1] = 0x00;
	memcpy(pMsg+2,&param,2);
	sendToAppExtcarStatusInfo(pMsg,4);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendContinuedDriveMileageToSdk(int param)
{
	u8 pMsg[4] = {0};
	pMsg[0] = 0x0B;
	pMsg[1] = 0x00;
	memcpy(pMsg+2,&param,2);
	sendToAppExtcarStatusInfo(pMsg,4);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendAverageFuelConsumptionToSdk(int param)
{
	u8 pMsg[4] = {0};
	pMsg[0] = 0x0D;
	pMsg[1] = 0x00;
	memcpy(pMsg+2,&param,2);
	sendToAppExtcarStatusInfo(pMsg,4);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendDoorStatusToSdk(u8 *param,int len)
{
	u8 pMsg[6] = {0};
	pMsg[0] = 0x0E;
	pMsg[1] = 0x00;
	if(len > 4)
		len = 4;
	memcpy(pMsg+2,param,len);
	sendToAppExtcarStatusInfo(pMsg,len + 2);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendDoorLockStatusToSdk(u8 *param,int len)
{
	u8 pMsg[6] = {0};
	pMsg[0] = 0x10;
	pMsg[1] = 0x00;
	if(len > 4)
		len = 4;
	memcpy(pMsg+2,param,len);
	sendToAppExtcarStatusInfo(pMsg,len + 2);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendTrunkStatusToSdk(u8 param)
{
	u8 buf[] = {0x11,0x00,param};
	sendToAppExtcarStatusInfo(buf,3);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendFrontCoverStatusToSdk(u8 param)
{
	u8 buf[] = {0x12,0x00,param};
	sendToAppExtcarStatusInfo(buf,3);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendSkyLightStatusToSdk(u8 param)
{
	u8 buf[] = {0x13,0x00,param};
	sendToAppExtcarStatusInfo(buf,3);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendLightStatusToSdk(u8 LightType,u8 param)
{
	u8 buf[] = {0x16,LightType,param};
	sendToAppExtcarStatusInfo(buf,3);
}
void	 CNotifyAndResponseFlyJniSdk::extcarSendGearsInfoToSdk(u8 param)
{ 
	u8 buf[] = {0x18,0x00,param};
	sendToAppExtcarStatusInfo(buf,3);
}

void	 CNotifyAndResponseFlyJniSdk::extcarSendVINCodeToSdk(u8 *param,int len)
{
	u8 pMsg[19] = {0}; 
	pMsg[0] = 0x1B;
	pMsg[1] = 0x00;
	if(len > 17)
		len = 17;
	memcpy(pMsg+2,param,len);
	sendToAppExtcarStatusInfo(pMsg,len + 2);
}

