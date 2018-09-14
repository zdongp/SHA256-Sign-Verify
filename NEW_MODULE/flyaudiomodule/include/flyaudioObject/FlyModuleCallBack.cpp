/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "FlyModuleCallBack.h"

extern CFlyModule *g_pFlyModule;

void moduleParameterInit(void)
{
	g_pFlyModule->outCallBack_moduleParameterInit();
}

void moduleParameterReInit(void)
{
	g_pFlyModule->outCallBack_moduleParameterReInit();
}

 void readParameter(void)
{
	g_pFlyModule->outCallBack_readParameter();
}

void saveParameter(void)
{
	g_pFlyModule->outCallBack_saveParameter();
}

moduleid_t locale_module_mid(void)
{
	return g_pFlyModule->locale_module_mid();
}

void analyseHalMessage(halid_t hid, u8 cmd, u8 *p, u8 len)
{
	g_pFlyModule->outCallBack_analyseHalMessage(hid, cmd, p, len);
}

void analyseAppMessage(u8 *p, u8 len)
{
	g_pFlyModule->outCallBack_analyseAppMessage(p, len);
}

void analyseOtherModuleMessage(moduleid_t id, u8 *p, u8 len)
{
	g_pFlyModule->outCallBack_analyseOtherModuleMessage(id, p, len);
}

void analyseTimerHandleMessage(u8 *p, u8 len)
{
	g_pFlyModule->outCallBack_analyseTimerHandleMessage(p,len);
}

void getMyModuleParam(char id, u8 *p, u8 *pLen)
{
	g_pFlyModule->outCallBack_getMyModuleParam(id, p, pLen);
}

 int module_extendInterface(char *p, int len)
{
	return g_pFlyModule->outCallBack_analyseFlyNativeServerMessage(p, len);
}

void analyseAgentMessage(moduleid_t id,u8 *p, u8 len)
{
	g_pFlyModule->outCallBack_analyseAgentMessage(id, p, len);
}

void timerHandleProc(int timerId)
{
	g_pFlyModule->outCallBack_timerHandleProc(timerId);
}

void pageIdUiHaveGone(int pageId)
{
	g_pFlyModule->pageIdUiHaveGone(pageId);
}