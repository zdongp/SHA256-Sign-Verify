#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <flyutils/debug.h>
#include <cstring>
#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "controlID.h"

class  CNotifyAndResponseFlyJniSdk
{
public:
    CNotifyAndResponseFlyJniSdk();
     ~CNotifyAndResponseFlyJniSdk();

	 void moduleToSystem_FromFlyJniSdk(u8 *param, int len);
	 void analyseSdkSetLightAddOrRedValue(u8 *param,int len);
	 void sendToFlyJniSdkSystemBrightnessMessage(u8 brightness);
	 void sendToFlyJniSdkSystemFrontCameraApp(u8 p);
	 void setToHalCloseOrTurnOnLightness(u8 param);
	 void sendToFlyJniSdkRadarDate(u8 ForR,u8 *p,u8 len);

	 void sdkToSystemJumpPage(u8 *p,u8 len);
	void analyseSdkJumpPage_Bt(u8 param);
	void analyseSdkJumpPage_Radio(u8 param);
	void sendToFlyJniSdkBackCarStatus(u8 backcar);	
	void sendToFlyJniSdkSystemDayOrNightStatus(u8 nDayOrNight);
	void sendToFlyJniSdkDefualtNaviChange();
	void sendToFlyJniSdkCurPageID();
	void sendToFlyJniSdkSystemBrightnessValueMessage(u8 brightness);
	void sendToFlyJniSdkSystemAutoLightStatus(u8 uSwitch);
	/************************sendToAppBasicFunction************************/
	void sendToFlyJniSdkService(u8 moduleId, u8 *p, int len);
	void sendToAppSystemStatusInfo(u8 *buf,int len);
};