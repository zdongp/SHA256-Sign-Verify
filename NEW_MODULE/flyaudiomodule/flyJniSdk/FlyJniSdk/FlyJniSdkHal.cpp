
#include "FlyJniSdkHal.h"


CFlyJniSdkHal::CFlyJniSdkHal(void)
{
}

CFlyJniSdkHal::~CFlyJniSdkHal(void)
{
}

void CFlyJniSdkHal::init(void)
{
	// 冷启动起来调用
	LOGD("[%s] [%s]", __FILE__ , __FUNCTION__);
	
}

void CFlyJniSdkHal::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
{
	m_pFlyJniSdkApp	 = (CFlyJniSdkApp *)pFlyApp; 
	m_pFlyJniSdkModule = (CFlyJniSdkModule *)pFlyModule; 
	m_pFlyJniSdkHal	 = (CFlyJniSdkHal *)pFlyHal; 
	m_pFlyJniSdkParam  = (CFlyJniSdkParam *)pFlyParam; 

	m_pFlyApp    = pFlyApp;
	m_pFlyModule = pFlyModule;
	m_pFlyHal    = pFlyHal;
	m_pFlyParam  = pFlyParam;
}

void CFlyJniSdkHal::analyseHalMessage(halid_t halId, u8 cmd, u8 *p, u8 len)
{
	LOGD("[%s]: cmd = [0x%x]", __FUNCTION__, cmd);
	outPutLog(__FUNCTION__, "p", p, len);

}

void CFlyJniSdkHal::analyseAgentMessage(moduleid_t id, u8 *p, u8 len)
{
}
