#pragma once
#include "FlyJniSdkModule.h"

class CFlyJniSdkModule;
class CFlyJniSdkModuleKey:public CFlyJniSdkModule
{
public:
	 CFlyJniSdkModuleKey(void);
	virtual ~CFlyJniSdkModuleKey(void);
	void getAppCtrlMessage(u8 *p, u8 len);
};