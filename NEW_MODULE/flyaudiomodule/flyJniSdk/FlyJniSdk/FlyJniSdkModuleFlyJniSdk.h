#pragma once
#include "FlyJniSdkModule.h"

class CFlyJniSdkModule;
class CFlyJniSdkModuleFlyJniSdk:public CFlyJniSdkModule
{
public:
	 CFlyJniSdkModuleFlyJniSdk(void);
	virtual ~CFlyJniSdkModuleFlyJniSdk(void);

	void getAppCtrlMessage(u8 *p, u8 len);
};

