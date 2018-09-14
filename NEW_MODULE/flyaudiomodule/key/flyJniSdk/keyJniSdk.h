#pragma once
#include "global.h"

class  CKeyJniSdk
{
	public:
		CKeyJniSdk();
		~CKeyJniSdk();
public:		//analyse Function
	void getSdkToModuleKeyMessage(u8 *p,int len);
	void analysSdkToKeyStatusMessage(u8 *buf,u8 len);
	void analysSdkToKeyContrlMessage(u8 *buf,u8 len);
public: 		
	void sendToFlyJniSdkService(u8 moduleId, u8 *p, u8 len);
	void sendToAppKeyStatusInfo(u8 *buf,int len);
	void sendToAppKeyCtrlInfo(u8 *buf,int len);
public: //Function
	void sendToApp_KeyValue(u8 param);
};

