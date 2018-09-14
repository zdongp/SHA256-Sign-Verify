#include "FlyJniSdkModuleExtcar.h"


CFlyJniSdkModuleExtcar::CFlyJniSdkModuleExtcar(void)
{

}
CFlyJniSdkModuleExtcar::~CFlyJniSdkModuleExtcar(void)
{

}

void CFlyJniSdkModuleExtcar::getExtcarMessage(u8 *p, u8 len)
{
	setToFlyJniSdkService(MODULE_ID_EXTCAR, p, len);
	
	if(AnalyzeCarMessage(p,len))
	{
		MakeCarMessage();
	}
}
	
bool CFlyJniSdkModuleExtcar::AnalyzeCarMessage(u8 *p, u8 len)
{
	bool bRet = false;

	if(sCarModels == 0){
		u8 sCar_Models = 0;
		u8 sCar_Models_Len = 1;
		m_pFlyModule->getOtherModuleParam((u8)MODULE_ID_EXTCAR,(u8)EXTCAR_CAR_MODELS,(u8*)&sCar_Models,(u8*)&sCar_Models_Len);
		sCarModels = (u16)sCar_Models;
	}
	
	switch(p[0])
	{
		case 0x09:
			bRet = true;
			uCarDoorState = p[1];
			break;
		case 0x0a:
			bRet = true;
			uCarEngineDoor = p[1];
			break;
		case 0x41:
			bRet = true;
			uCarDoorLock = p[1];
			break;
		case 0x43:
			bRet = true;
			uCarDoorWindow_FL = p[1];
			uCarDoorWindow_FR = p[2];
			uCarDoorWindow_RL = p[3];
			uCarDoorWindow_RR = p[4];
			break;
		case 0x44:
			bRet = true;
			uCarDormer = p[1];
			break;
		case 0x45:
			bRet = true;
			uCarHeadlight = p[1];
			break;
		default:
			break;
	}
	
	return bRet;
}

void CFlyJniSdkModuleExtcar::MakeCarMessage()
{
	u8 szMsg[256] = {0};

	szMsg[0] = 0xFF;
	szMsg[1]=(u8)((sCarModels >> 8) & 0xff);
	szMsg[2]=(u8)(sCarModels & 0xff);
	szMsg[3]=(u8)((sCars >> 8) & 0xff);
	szMsg[4]=(u8)(sCars & 0xff);
	szMsg[5] = uCarDoorState;
	szMsg[6] = uCarEngineDoor;
	szMsg[7] = uCarDoorWindow_FL;
	szMsg[8] = uCarDoorWindow_FR;
	szMsg[9] = uCarDoorWindow_RL;
	szMsg[10] = uCarDoorWindow_RR;
	szMsg[11] = uCarDormer;
	szMsg[12] = uCarDoorLock;
	szMsg[13] = uCarHeadlight;

	LOGD("[%s] sCarModels:%x,sCars:%x", __FUNCTION__,sCarModels,sCars);
	LOGD("[%s] uCarDoorState:%x uCarEngineDoor:%x", __FUNCTION__,uCarDoorState,uCarEngineDoor);
	LOGD("[%s] uCarDoorWindow_FL:%x uCarDoorWindow_FR:%xs,uCarDoorWindow_RL:%x uCarDoorWindow_RR:%x", __FUNCTION__,uCarDoorWindow_FL,uCarDoorWindow_FR,uCarDoorWindow_RL,uCarDoorWindow_RR);
	LOGD("[%s] uCarDormer:%x uCarDoorLock:%x uCarHeadlight:%x", __FUNCTION__,uCarDormer,uCarDoorLock,uCarHeadlight);

	setToFlyJniSdkService(MODULE_ID_EXTCAR, szMsg, 14);
}

void CFlyJniSdkModuleExtcar::initCarInforParam()
{
	LOGD("[%s]", __FUNCTION__);
	sCarModels = 0;
	sCars = 0;
	uCarDoorState = 0;
	uCarEngineDoor = 0;

	uCarDoorWindow_FL = 0;
	uCarDoorWindow_FR = 0;
	uCarDoorWindow_RL = 0;
	uCarDoorWindow_RR = 0;

	uCarDormer = 0;
	uCarDoorLock = 0;
	uCarHeadlight = 0;
}
/******************NEW    SDK********************/
void CFlyJniSdkModuleExtcar::analyseExtcarAppMessageType(u8 *p, u8 len)
{
	switch(p[0])
	{
		case RESPONE_CHANGE_STATE:
			analyseExtcarReturnStatusMassage(p+1,len - 1);
			break;
		case CONTROL_MESSAGE:
			analyseControlExtcarOperationMassage(p,len);
			break;
		default:break;
	}

}

void CFlyJniSdkModuleExtcar::analyseExtcarReturnStatusMassage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x00:
			if(p[1] == 0x00)
			{
				setToExtcarGetCurExtcarInfo();
			}
			break;
		default:break;
	}
}

void CFlyJniSdkModuleExtcar::analyseControlExtcarOperationMassage(u8 *p, u8 len)
{
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,p,len);
}

/************Function****************/
void CFlyJniSdkModuleExtcar::setToExtcarGetCurExtcarInfo()
{
	 setToExtcarGetSeatBeltsStatus(0x00);
	 setToExtcarGetRemainOil(0x00);
	 setToExtcarGetDriveMileage(0x00);
	 setToExtcarGetOutSideTemperature(0x00);
	 setToExtcarGetHandBrakeStatus(0x00);
	 setToExtcarGetEngineSpeed(0x00);
	 setToExtcarGetAverageSpeed(0x00);
	 setToExtcarGetInstantSpeed(0x00);
	 setToExtcarGetBatteryVoltage(0x00);
	 setToExtcarGetContinuedDriveMileage(0x00);
	 setToExtcarGetAverageFuelConsumption(0x00);
	 setToExtcarGetDoorStatus(0x00);
	 setToExtcarGetDoorLockStatus(0x00);
	 setToExtcarGetTrunkStatus(0x00);
	 setToExtcarGetFrontCoverStatus(0x00);
	 setToExtcarGetSkyLightStatus(0x00);
	 setToExtcarGetLightStatus(0x05);
	 setToExtcarGetLightStatus(0x0A);
	 setToExtcarGetGearsInfo(0x00);
	 setToExtcarGetVINCode(0x00);

}
void CFlyJniSdkModuleExtcar::setToExtcarGetSeatBeltsStatus(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x00,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetRemainOil(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x01,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetDriveMileage(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x02,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetOutSideTemperature(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x03,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetHandBrakeStatus(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x04,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetEngineSpeed(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x05,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetAverageSpeed(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x06,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}

void CFlyJniSdkModuleExtcar::setToExtcarGetInstantSpeed(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x07,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetBatteryVoltage(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x08,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}

void CFlyJniSdkModuleExtcar::setToExtcarGetContinuedDriveMileage(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x0B,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetAverageFuelConsumption(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x0D,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetDoorStatus(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x0E,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetDoorLockStatus(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x10,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetTrunkStatus(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x11,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetFrontCoverStatus(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x12,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}

void CFlyJniSdkModuleExtcar::setToExtcarGetSkyLightStatus(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x13,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetLightStatus(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x16,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetGearsInfo(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x18,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}
void CFlyJniSdkModuleExtcar::setToExtcarGetVINCode(u8 param)
{
	u8 buf[3] = {RESPONE_CHANGE_STATE,0x1B,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_EXTCAR,buf,3);
}

