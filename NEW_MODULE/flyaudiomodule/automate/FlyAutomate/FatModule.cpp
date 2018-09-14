/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "FatModule.h"
moduleid_t CFatModule::locale_module_mid(void)
{
	return MODULE_ID_AUTOMATE;
}

//工程根结点指针
CFlyModule *g_pFlyModule = (CFlyModule*)CFatModule::GetInstance();

CFatModule::CFatModule(void)
{
	m_pFatApp    = CFatApp::GetInstance();
	m_pFatModule = this;
	m_pFatHal    = CFatHal::GetInstance();
	m_pFatParam  = CFatParam::GetInstance();

	m_pFlyApp    = m_pFatApp;
	m_pFlyModule = m_pFatModule;
	m_pFlyHal    = m_pFatHal;
	m_pFlyParam  = m_pFatParam;

	m_pFatApp->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);
	m_pFatHal->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);
	m_pFatParam->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);
}

CFatModule::~CFatModule(void)
{
}

void CFatModule::init(void)
{
}

void CFatModule::getAccOn()
{
	LOGD("[%s]", __FUNCTION__);
}

void CFatModule::getAccOff()
{
	LOGD("[%s]", __FUNCTION__);
}

void CFatModule::getMyModuleParam(char id, u8 *p, u8 *pLen)
{
	switch(id){
		default:break;
	}

}

void CFatModule::NotifySystemJumpPage( u16 usPageID )
{
	u16 usCurPage = m_pFatModule->getCurPageId();
	if (usCurPage == usPageID)
		return;

	u8 szMsg[] = {0x82, 0x00, 0x00};
	memcpy(&szMsg[1], &usPageID, 2);
	makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_SYSTEM, szMsg, 3);
}

void CFatModule::SendKeyValueToOtherModule( u8 ucKeyValue, u8 ucToModule )
{
	u8 szMsg[] = {0x00, ucKeyValue};
	makeAndSendMessageToModule(MODULE_ID_KEY, ucToModule, szMsg, sizeof(szMsg));
}

void CFatModule::NotifyBlueToothIntoAutomateMode_PairingPincodeToDefault()
{
	u8 sendbuf[] = {0x00,0x01};
	m_pFatModule->makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_BT, sendbuf, 2);//Into the automated test mode, BT the pairing password should be changed to 0000
}

void CFatModule::NotifyBlueToothDiscoverable( u8 ucEnable )
{
	FLY_LOG(LOG_LV_DEBUG, "ucEnable = %d", ucEnable);
	u8 szMsg[] = {0xFA, 0x01, ucEnable};
	makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_BT, szMsg, sizeof(szMsg));
}

void CFatModule::NotifyBlueToothSendBtPower(u8 p)
{
	u8 szMsg[3] = {0xFA,0x02,p};
	makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_BT, szMsg, sizeof(szMsg));
}

void CFatModule::NotifyBlueToothSendBt_CallingOrHandupr(u8 p)
{
	u8 szMsg[3] = {0xFA,0x03,p};
	makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_BT, szMsg, sizeof(szMsg));
}

void CFatModule::NotifyBlueToothSendBt_AudioTransfer(u8 p)
{
	u8 szMsg[3] = {0xFA,0x04,p};
	makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_BT, szMsg, sizeof(szMsg));
}

void CFatModule::NotifyBlueToothSendBt_CallLogsAllClear(u8 p)
{
	u8 szMsg[3] = {0xFA,0x05,p};
	makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_BT, szMsg, sizeof(szMsg));
}


void CFatModule::NotifyMP3_SelectMusicPlay(u8 data )
{
	FLY_LOG(LOG_LV_DEBUG, "data = %d", data);
	u8 szMsg[] = {0x01,data};
	makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_MEDIA, szMsg, sizeof(szMsg));
}

void CFatModule::NotifyMP3_GoToAutoMate()
{
	FLY_LOG(LOG_LV_DEBUG, "NotifyMP3_GoToAutoMate",0);
	u8 szMsg[] = {0x02,0x01};
	makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_MEDIA, szMsg, sizeof(szMsg));
}


void CFatModule::getDvrMessage(u8 *p, u8 len)
{
    FLY_LOG(LOG_LV_DEBUG, " p:%s", p);
    if(p[0] != 0)return;
    m_pFatHal->analyseHalMessage(HAL_ID_DVR,p[1],&p[2],len-2);
}

void CFatModule::getRadioMessage(u8 *p, u8 len)
{
    FLY_LOG(LOG_LV_DEBUG, " p= %s", p);
    if(p[0] != 0)return;
    m_pFatHal->analyseHalMessage(HAL_ID_RADIO,p[1],&p[2],len-2);
}

void CFatModule::NotifyMP3_DetectionUSB()
{
	u8 szMsg[] = {0x04,0x01};
	makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_MEDIA, szMsg, sizeof(szMsg));
}

void CFatModule::NotifyMP3_UsbStateInit()
{
	u8 szMsg[] = {0x05,0x01};
	makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_MEDIA, szMsg, sizeof(szMsg));
}

void CFatModule::NotifyBlueToothDiscoverablePairing( u8 p )
{
	FLY_LOG(LOG_LV_DEBUG, "p = %d", p);
	u8 szMsg[] = {0x01, p};
	makeAndSendMessageToModule(MODULE_ID_AUTOMATE, MODULE_ID_BT, szMsg, sizeof(szMsg));
}