#pragma once
#include "FlyJniSdkModule.h"

class CFlyJniSdkModule;
class CFlyJniSdkModuleMedia:public CFlyJniSdkModule
{
public:
	 CFlyJniSdkModuleMedia(void);
	virtual ~CFlyJniSdkModuleMedia(void);
	void getMediaMessage(u8 *p, u8 len);
	void analyseMediaAppMessageType(u8 *p, u8 len);
	void analyseMediaReturnStatusMassage(u8 *p, u8 len);
	void analyseControlMediaOperationMassage(u8 *p, u8 len);
	void setToMediaJumpMediaPage(u8 param);
	void setToMediaSpecifyToPlayTheSong(u8 *param,u8 len);
	void sendToAppMediaStatusInfo(u8 *buf,int len);

};