#pragma once
#include "FlyJniSdkModule.h"
class CFlyJniSdkModule;
class CFlyJniSdkModuleAc:public CFlyJniSdkModule
{
public:
	CFlyJniSdkModuleAc(void);
	virtual ~CFlyJniSdkModuleAc(void);

	void getAcMessage(u8 *p, u8 len);
	void analyseAcAppMessageType(u8 *p, u8 len);
	void analyseAcReturnStatusMassage(u8 *p, u8 len);
	void setToAcGetCurAcInfo();
	void sendToAppAcStatusInfo(u8 *buf,int len);
	void analyseControlACOperationMassage(u8 *p, u8 len);
	//

/********************send To Ac get Status****************************/
void setToAcGetCurAcSwitch();
void setToAcGetCurTemp();
void setToAcGetCurWSpeed(); //W:wind
void setToAcGetCurWMode();//W:wind
void setToAcGetCurLoopMode();
void setToAcGetCurAorCSwitch();
void setToAcGetCurMaxAorCSwitch();
void setToAcGetCurAutoSwitch();
void setToAcGetCurSYNCSwitch();
void setToAcGetCurFGlassMistRemoval();
void setToAcGetCurRGlassMistRemoval();
void setToAcGetCurHeatSeatStatus();
void setToAcGetCurHeatSeatGrade();

/********************send To Ac Control****************************/
void sendToAcJumpAcPage(u8 param);
void sendToAcSetAcSwitch(u8 param);
void sendToAcSetAcWindSpeed(u8 *p,u8 len);
void sendToAcSetAcSyncSwitch(u8 param);
void sendToAcSetAcCycleModel(u8 param);
void sendToAcSetAcTemp(u8 *p,u8 len);
void sendToAcSetAcWindowHeat(u8 *p,u8 len);
void sendToAcSetAcWindModel(u8 *p,u8 len);
void sendToAcSetAcAorCModel(u8 *p,u8 len);
void sendToAcSetAcSeatHeatSwitch(u8 *p,u8 len);
void sendToAcSetAcAUTOSwitch(u8 *p,u8 len);
void sendToAcSetAcMaxAorCModel(u8 *p,u8 len);
void sendToAcSetAcMaxWindowHeat(u8 *p,u8 len);
void sendToAcSetAcSetAcTempAddOrRed(u8 *p,u8 len);
void sendToAcSetAcSetAcWindSpeedAddOrRed(u8 *p,u8 len);

};

