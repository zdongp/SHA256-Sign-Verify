#include "FlyJniSdkModuleKey.h"


CFlyJniSdkModuleKey::CFlyJniSdkModuleKey(void)
{

}
CFlyJniSdkModuleKey::~CFlyJniSdkModuleKey(void)
 {

 }

void CFlyJniSdkModuleKey::getAppCtrlMessage(u8 *p, u8 len)
{
	LOGD("[%s] Module_key p[0]:%x", __FUNCTION__,p[0]);
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_KEY,p,2);
}