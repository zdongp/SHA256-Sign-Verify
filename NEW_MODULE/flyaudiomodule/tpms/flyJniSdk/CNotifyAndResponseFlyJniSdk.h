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

	void sendToFlyJniSdk_PressureUnit(u8 param);
	void sendToFlyJniSdk_TemperatureUnit(u8 param);
	void sendToFlyJniSdk_Sign(u8 uCmd,u8 param);
	void sendToFlyJniSdk_Battery(u8 uCmd,u8 param);
	void sendToFlyJniSdk_Pressure(u8 uCmd,int param);
	void sendToFlyJniSdk_Temperature(u8 uCmd,int param);
	void sendToFlyJniSdk_Tpms_FL(u32 Id,int param);
	void sendToFlyJniSdk_Tpms_FR(u32 Id,int param);
	void sendToFlyJniSdk_Tpms_RL(u32 Id,int param);
	void sendToFlyJniSdk_Tpms_RR(u32 Id,int param);
	void sendToFlyJniSdk_Tpms_Infor(u32 Id,int param);

    void analyseFlyJniSdkMessage(unsigned char *p,int len);
};