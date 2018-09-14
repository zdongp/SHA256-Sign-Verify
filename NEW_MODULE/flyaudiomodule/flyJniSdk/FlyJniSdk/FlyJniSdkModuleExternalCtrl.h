#pragma once
#include "FlyJniSdkModule.h"
class CFlyJniSdkModule;
class CFlyJniSdkModuleExternalCtrl:public CFlyJniSdkModule
{
public:
	CFlyJniSdkModuleExternalCtrl(void);
	virtual ~CFlyJniSdkModuleExternalCtrl(void);

	void analyseExternalCtrlAppMessageType(u8 *p, u8 len);
	void analyseExternalCtrlReturnStatusMassage(u8 *p, u8 len);
	void analyseControlExternalCtrlOperationMassage(u8 *p, u8 len);
	void sendToExternalCtrlSpeechStatus(u8 param);
};

