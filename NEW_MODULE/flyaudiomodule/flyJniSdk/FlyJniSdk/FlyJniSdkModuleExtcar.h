#pragma once
#include "FlyJniSdkModule.h"

class CFlyJniSdkModule;
class CFlyJniSdkModuleExtcar:public CFlyJniSdkModule
{
public:
	 CFlyJniSdkModuleExtcar(void);
	virtual ~CFlyJniSdkModuleExtcar(void);

	void getExtcarMessage(u8 *p, u8 len);

	bool AnalyzeCarMessage(u8 *p, u8 len);
	void MakeCarMessage();
	void initCarInforParam();
	/***************************************/
	void analyseExtcarAppMessageType(u8 *p, u8 len);
	void analyseExtcarReturnStatusMassage(u8 *p, u8 len);
	void analyseControlExtcarOperationMassage(u8 *p, u8 len);
	/***********************************/
	void setToExtcarGetCurExtcarInfo();
	void setToExtcarGetSeatBeltsStatus(u8 param);
	void setToExtcarGetRemainOil(u8 param);
	void setToExtcarGetDriveMileage(u8 param);
	void setToExtcarGetOutSideTemperature(u8 param);
	void setToExtcarGetHandBrakeStatus(u8 param);
	void setToExtcarGetEngineSpeed(u8 param);
	void setToExtcarGetAverageSpeed(u8 param);
	void setToExtcarGetInstantSpeed(u8 param);
	void setToExtcarGetBatteryVoltage(u8 param);
	void setToExtcarGetContinuedDriveMileage(u8 param);
	void setToExtcarGetAverageFuelConsumption(u8 param);
	void setToExtcarGetDoorStatus(u8 param);
	void setToExtcarGetDoorLockStatus(u8 param);
	void setToExtcarGetTrunkStatus(u8 param);
	void setToExtcarGetFrontCoverStatus(u8 param);
	void setToExtcarGetSkyLightStatus(u8 param);
	void setToExtcarGetLightStatus(u8 param);
	void setToExtcarGetVINCode(u8 param);
	void setToExtcarGetGearsInfo(u8 param);
public:
	u16 sCarModels;
	u16 sCars;
	
	u8 uCarDoorState;
	u8 uCarEngineDoor;

	u8 uCarDoorWindow_FL;
	u8 uCarDoorWindow_FR;
	u8 uCarDoorWindow_RL;
	u8 uCarDoorWindow_RR;

	u8 uCarDormer;
	u8 uCarDoorLock;
	u8 uCarHeadlight;
	
};

