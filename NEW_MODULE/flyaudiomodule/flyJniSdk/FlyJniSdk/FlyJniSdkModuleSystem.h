#pragma once
#include "FlyJniSdkModule.h"

class CFlyJniSdkModule;
class CFlyJniSdkModuleSystem:public CFlyJniSdkModule
{
public:
	 CFlyJniSdkModuleSystem(void);
	virtual ~CFlyJniSdkModuleSystem(void);
	void FlyJniSdkToModule_NotifySystem_JumpPage(unsigned char* pageID);
	void getAppCtrlMessage(u8 *p, u8 len);
	void FlyJniSdkToModule_NotifySystem_ResetFactorySeting(unsigned char param);
	void  FlyJniSdkToModule_NotifySystem_ChangeLightness(unsigned char lightness);
	void getSystemMessage(u8 *p, u8 len);
	void onSystemBrightness(unsigned char brightness );
	void onSystemToFrontCameraApp(u8 p);
	void FlyJniSdkToModule_NotifySystem_CloseOrTurnOnBrightness(unsigned char param);
	void FlyJniSdkToModule_NotifySystem_OtaUpdata(unsigned char param);
	void analyseSystemAppMessageType(u8 *p, u8 len);
	void analyseSystemControlSystemOperationMassage(u8 *buf ,u8 len);
	void sendToSystemSetOffScreen(u8 param);
	void sendToSystemSetScreenBrightness (u8 param);
	void analyseReturnStatusMassage(u8 *buf ,u8 len);
	void sendToSystemJumpToSetPage (u8 param);
	void sendToSystemGetCurLightness(u8 param);
	void sendToSystemGetRadarDate(u8 param);
	void sendToSystemJumpPage(u8 *Buff,u8 len);
	void sendToSystemSetDayOrNightMode(u8 param);
	void sendToSystemSetScreenBrightnessValue(u8 param);
	void sendToSystemGetDayAndNightStatus(u8 param);
	void sendToSystemGetAutoLightStatus(u8 param);
	void sendToSystemSetAutoLightStatus(u8 param);
	void sendToSystemSetLightAddOrRed(u8 *buf,int len);
	void sendToSystemGetCurPageID(u8 param);
	void sendToSystemGetBackCarStatus(u8 param);
	void sendToSystemSetSystemReset();
	/***************************send to app function****************************************/
	void sendToAppSystemLightnessValue(u8 param ,u8 value);
	void sendToAppSystemRadarDate(u8 *param ,u8 len);
	void sendToAppSystemGetCurStatusFinish();
};
