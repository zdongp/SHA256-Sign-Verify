
#include "FlyJniSdkApp.h" 
#include "FlyJniSdkModuleBt.h"
#include "FlyJniSdkModuleRadio.h"
#include "FlyJniSdkModuleAudioVideo.h"
#include "FlyJniSdkModuleDvd.h"
#include "FlyJniSdkModuleSystem.h"
#include "FlyJniSdkModuleKey.h"
#include "FlyJniSdkModuleFlyJniSdk.h"
#include "FlyJniSdkModuleAc.h"
#include "FlyJniSdkModuleMedia.h"
#include "FlyJniSdkModuleAudioCtrl.h"
#include "FlyJniSdkModuleExtcar.h"
#include "FlyJniSdkModuleExtcarHondaTsu.h"
#include "FlyJniSdkModuleExternalCtrl.h"


CFlyJniSdkApp::CFlyJniSdkApp() 
{ 
} 
 
CFlyJniSdkApp::~CFlyJniSdkApp() 
{ 
} 
 
void CFlyJniSdkApp::init(void) 
{ 
	// 冷启动起来调用
	LOGD("[%s] [%s]",__FILE__ ,__FUNCTION__);

} 

void CFlyJniSdkApp::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
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

void CFlyJniSdkApp::processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	LOGD("[%s] id = [0x%x], mouseStatus = [%x]", __FUNCTION__, id, getMouseMessageType(e));
	outPutLog(__FUNCTION__, "p:", p, len);

	if (e == 0xFF && id == 0x51FFFF)
	{
		appCmdCtrl(p, len);
	}
	else if(e == 0xFF && id == 0x51FFFE)
	{
		analyseAppSdkMessage(p,len);
	}
}

void CFlyJniSdkApp::appCmdCtrl(u8 *p, u8 len)
{
	LOGD("[%s] ModuleId:%x", __FUNCTION__,p[0]);

	switch(p[0])
	{
		case MODULE_ID_BT:
			m_pFlyJniSdkParam->m_pFlyJniSdkModuleBt->getAppCtrlMessage(p + 1 , len - 1);
		break;
		case MODULE_ID_RADIO:
			m_pFlyJniSdkParam->m_pFlyJniModuleRadio->getAppCtrlMessage(p + 1 , len - 1);
		break;
		case MODULE_ID_KEY:
			m_pFlyJniSdkParam->m_pFlyJniModuleKey->getAppCtrlMessage(p + 1 , len - 1);
		break;
		case MODULE_ID_SYSTEM:
	        m_pFlyJniSdkParam->m_pFlyJniModuleSystem->getAppCtrlMessage(p + 1, len - 1);
		break;
		case MODULE_ID_DVD:
	        m_pFlyJniSdkParam->m_pFlyJniModuleDvd->getAppCtrlMessage(p + 1,len - 1);
		break;
		case MODULE_ID_AUDIOVIDEO:
			m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->getAppCtrlMessage(p + 1,len - 1);
		break;
		case MODULE_ID_FLYJNISDK:
			m_pFlyJniSdkParam->m_pFlyJniModuleFlyJniSdk->getAppCtrlMessage(p + 1,len - 1);
		break;
	}
}



void CFlyJniSdkApp::analyseAppSdkMessage(u8 *p, u8 len)
{
	//
	if(RequestAudioFocus_FlyUI(p,len))
		return;
		
	switch(p[0])
	{
		case MODULE_SDK_BT:
			m_pFlyJniSdkParam->m_pFlyJniSdkModuleBt->analyseAppMessageType(p + 1 , len - 1);
		break;
		case MODULE_SDK_AC:
			m_pFlyJniSdkParam->m_pFlyJniSdkModuleAc->analyseAcAppMessageType(p + 1 , len - 1);
			break;
		case MODULE_SDK_SYSTEM:
			m_pFlyJniSdkParam->m_pFlyJniModuleSystem->analyseSystemAppMessageType(p + 1 , len - 1);
		break;
		case MODULE_SDK_AUDIOVIDEO:
			m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->analyseAudioVideoAppMessageType(p + 1,len - 1);
			break;
		case MODULE_SDK_RADIO:
			m_pFlyJniSdkParam->m_pFlyJniModuleRadio->analyseRadioAppMessageType(p + 1,len - 1);
			break;
		case MODULE_SDK_MEDIA:
			m_pFlyJniSdkParam->m_pFlyJniSdkModuleMedia->analyseMediaAppMessageType(p + 1,len - 1);
			break;
		case MODULE_SDK_AUDIOCTRL:
			m_pFlyJniSdkParam->m_pFlyJniSdkModuleAudioCtrl->analyseAudioCtrlAppMessageType(p + 1,len - 1);
			break;
		case MODULE_SDK_EXTCAR:
			m_pFlyJniSdkParam->m_pFlyJniModuleExtcar->analyseExtcarAppMessageType(p + 1,len - 1);
			break;
		case MODULE_SDK_EXTCAR_HONDA_TSU:
			m_pFlyJniSdkParam->m_pFlyJniSdkModuleExtcarHondaTsu->analyseExtcarHondaTsuAppMessageType(p + 1,len - 1);
			break;
		case MODULE_SDK_EXTERNALCTRL:
			m_pFlyJniSdkParam->m_pFlyJnisdkModuleExternalCtrl->analyseExternalCtrlAppMessageType(p + 1,len - 1);
			break;
		default:break;
	}
}


//eg:Open other audio applications by voice operation and the voice release focus is restored to the last media application.
//Preemption audio focus.
bool CFlyJniSdkApp::RequestAudioFocus_FlyUI(u8 *p,int len)
{
	bool bEnble = false;
	m_pFlyJniSdkModule->deleteNativeTimer(JNISDK_TIMER_ID_RADIO_JUMP_PAGE);
	m_pFlyJniSdkModule->deleteNativeTimer(JNISDK_TIMER_ID_A2DP_JUMP_PAGE);
	m_pFlyJniSdkModule->deleteNativeTimer(JNISDK_TIMER_ID_MIDEA_JUMP_PAGE);
			
	switch(p[0])
	{
		case MODULE_SDK_RADIO:
		{
			if(p[1] == CONTROL_MESSAGE)
			{
				if(p[2] == 0x01 && (p[3] == 0x00||p[3] == 0x01||p[3] == 0x02))
				{
					LOGD("[%s]",__FUNCTION__);
					bEnble = true;
					
					if(p[3] != 0x00)
						m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->sendToAudioRequestFocus(0x01);
					m_pFlyJniSdkParam->m_pFlyJniModuleRadio->sendToRadioSetONorOFF(p[3]);
				}
			}
		}
		break;
		case MODULE_SDK_BT:
		{
			if(p[1] == CONTROL_MESSAGE)
			{
				if(p[2] == 0x04 && p[3] == 0x01)
				{
					LOGD("[%s]",__FUNCTION__);
					bEnble = true;
					//m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->sendToAudioRequestMuteOrUnMute(0x01);
					m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->sendToAudioRequestFocus(0x01);
					//m_pFlyJniSdkModule->setNativeTimer(TIMERS_ID_A2DP_JUMP_PAGE, 1, JNISDK_TIMER_ID_A2DP_JUMP_PAGE);
					m_pFlyJniSdkParam->m_pFlyJniSdkModuleBt->setToBtSetBtJumpToBtMusicPage(0x01);
				}
			}
		}
		break;
		case MODULE_SDK_MEDIA:
		{
			if(p[1] == CONTROL_MESSAGE)
			{
				if(p[2] == 0x01 && p[3] == 0x01)
				{
					LOGD("[%s]",__FUNCTION__);
					bEnble = true;
					//m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->sendToAudioRequestMuteOrUnMute(0x01);
					//m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->sendToAudioRequestFocus(0x01);
					//m_pFlyJniSdkModule->setNativeTimer(TIMERS_ID_MIDEA_JUMP_PAGE, 1, JNISDK_TIMER_ID_MIDEA_JUMP_PAGE);
					m_pFlyJniSdkParam->m_pFlyJniSdkModuleMedia->setToMediaJumpMediaPage(0x01);
				}
			}
		}
		break;
		case MODULE_SDK_SYSTEM:
			if(p[1] == CONTROL_MESSAGE && p[2] == 0x00)
			{
				u16 tempPage = 0;
				memcpy(&tempPage,p+3,2);
				if(tempPage == 0x0105)
					m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->sendToAudioRequestFocus(0x01);
			}
			break;
		default:break;
	}

	return bEnble;
}

