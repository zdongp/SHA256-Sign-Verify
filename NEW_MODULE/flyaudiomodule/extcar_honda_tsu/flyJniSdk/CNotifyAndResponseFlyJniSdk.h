#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <flyutils/debug.h>
#include <cstring>
#include "global.h"

class  CNotifyAndResponseFlyJniSdk
{
public:
    CNotifyAndResponseFlyJniSdk();
     ~CNotifyAndResponseFlyJniSdk();
public:
	void sendToAppExtcarHondaTSUData(u8 *buf,int len);
	void sendToAppNoRealTimeDate(u8 *buf,int len);
	void analyseFromFlyJniSdkMessage(unsigned char *p,int len);
};