
#pragma once
#include "FlyJniSdkParam.h"

class CFlyJniSdkApp;
class CFlyJniSdkModule;
class CFlyJniSdkParam;
class CFlyJniSdkHal : public CFlyHal
{
	SINGLETON_IMPLEMENT(CFlyJniSdkHal)
private:
	CFlyJniSdkHal(void);
public:
	virtual ~CFlyJniSdkHal(void);

public:
	void init(void);
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);

	void analyseHalMessage(halid_t halId, u8 cmd, u8 *p, u8 len);
	void analyseAgentMessage(moduleid_t id, u8 *p, u8 len);
	
private:
	CFlyJniSdkApp *m_pFlyJniSdkApp;
	CFlyJniSdkModule *m_pFlyJniSdkModule;
	CFlyJniSdkHal *m_pFlyJniSdkHal;
	CFlyJniSdkParam *m_pFlyJniSdkParam;
};

