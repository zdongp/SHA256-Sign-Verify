
#pragma once
#include "FlyJniSdkParam.h"


class CFlyJniSdkModule;
class CFlyJniSdkHal;
class CFlyJniSdkParam;
class CFlyJniSdkApp : public CFlyApp
{
	SINGLETON_IMPLEMENT(CFlyJniSdkApp)
private:
	CFlyJniSdkApp(void);
public:
	virtual ~CFlyJniSdkApp(void);

public:
	//init
	void init(void);
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);
	//ui click event
	void processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);

	void appCmdCtrl(u8 *p, u8 len);
	void analyseAppSdkMessage(u8 *p, u8 len);

public:
	bool RequestAudioFocus_FlyUI(u8 *p,int len);
private:
	//info head node
	CFlyJniSdkApp *m_pFlyJniSdkApp;
	CFlyJniSdkModule *m_pFlyJniSdkModule;
	CFlyJniSdkHal *m_pFlyJniSdkHal;
	CFlyJniSdkParam *m_pFlyJniSdkParam;
};

