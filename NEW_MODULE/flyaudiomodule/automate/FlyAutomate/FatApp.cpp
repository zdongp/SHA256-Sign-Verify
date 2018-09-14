/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "FatApp.h" 
#include "FatModule.h"

#include <flytypes.h>
#include <flymoduleApi.h>
#include <allconfig.h>
#include <config.h>
#include <flymoduleApi_internal.h>
#include <flyaudiomodule/debug.h>
extern moduleid_t locale_module_mid(void);

CFatApp::CFatApp() 
{ 
} 
 
CFatApp::~CFatApp() 
{ 
} 
 
void CFatApp::init(void) 
{ 
} 

void CFatApp::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
{ 
	m_pFatApp	 = (CFatApp *)pFlyApp; 
	m_pFatModule = (CFatModule *)pFlyModule; 
	m_pFatHal	 = (CFatHal *)pFlyHal; 
	m_pFatParam  = (CFatParam *)pFlyParam; 

	m_pFlyApp    = pFlyApp;
	m_pFlyModule = pFlyModule;
	m_pFlyHal    = pFlyHal;
	m_pFlyParam  = pFlyParam;
} 

void CFatApp::processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
}

void CFatApp::SendMouseOperateToOtherModule(E_MOUSE_STATUS e, u8 arrivedModuleId, u32 u32_contrID)
{
    FLY_LOG(LOG_LV_DEBUG, "arrivedModuleId = %x u32_contrID:%x ctrlType:%d", arrivedModuleId,u32_contrID,e);
    
    int sendbufLen = 7;
    u8* sendbuf = new u8[sendbufLen];
    sendbuf[0] = 0xff;
    sendbuf[1] = (u8) ((u32_contrID >> 24) & 0xFF);
	sendbuf[2] = (u8) ((u32_contrID >> 16) & 0xFF);
	sendbuf[3] = (u8) ((u32_contrID >> 8) & 0xFF);
	sendbuf[4] = (u8) (u32_contrID & 0xFF);
	sendbuf[5] = (u8)e;
	sendbuf[6] = 0;
	m_pFatModule->makeAndSendMessageToModule(MODULE_ID_AUTOMATE, arrivedModuleId, sendbuf, sendbufLen);
	delete sendbuf;

}

void CFatApp::SendMouseOperateToOtherModule(E_MOUSE_STATUS e, u8 arrivedModuleId, u32 u32_contrID,u8 u8_MouseStatus)
{
    FLY_LOG(LOG_LV_DEBUG, "arrivedModuleId = %x u32_contrID:%x ctrlType:%d", arrivedModuleId,u32_contrID,e);
    
    int sendbufLen = 7;
	u8* sendbuf = new u8[sendbufLen];
	sendbuf[0] = 0xff;
    sendbuf[1] = (u8) ((u32_contrID >> 24) & 0xFF);
	sendbuf[2] = (u8) ((u32_contrID >> 16) & 0xFF);
	sendbuf[3] = (u8) ((u32_contrID >> 8) & 0xFF);
	sendbuf[4] = (u8) (u32_contrID & 0xFF);
	sendbuf[5] = (u8)e;
	sendbuf[6] = u8_MouseStatus;
    m_pFatModule->makeAndSendMessageToModule(MODULE_ID_AUTOMATE, arrivedModuleId, sendbuf, sendbufLen);
    delete sendbuf;

}

void CFatApp::GetIMEI()
{
	u8 szCmd[] = {0x83, 0x00};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::GetCarMAC()
{
	u8 szCmd[] = {0x84, 0x00};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::GetWifiConnectStatus()
{
	u8 szCmd[] = {0x86, 0x03, 0x00};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::GetWifiNetworksignalStrength()
{
	u8 szCmd[] = {0x86, 0x04, 0x00};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::Get4GNetworksignalStrength()
{
	u8 szCmd[] = {0x85, 0x01, 0x00};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::GetSd1Status()
{
	u8 szCmd[] = {0x87, 0x00};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::GetSd1MemoryUsage()
{
	u8 szCmd[] = {0x87, 0x01};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::GetSd1TheTotalSize()
{
	u8 szCmd[] = {0x87, 0x02};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::GetSd0MemoryUsage()
{
	u8 szCmd[] = {0x87, 0x03};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::GetSd0TheTotalSize()
{
	u8 szCmd[] = {0x87, 0x04};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}


void CFatApp::GoBaiduPageWifi(u8 p)
{
	u8 szCmd[] = {0x86, 0x02, 0x00};
	szCmd[2] = p;
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::GoBaiduPage4G(u8 p)
{
	u8 szCmd[] = {0x85, 0x02, 0x00};
	szCmd[2] = p;
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::controlWIFI(u8 p)
{
	u8 szCmd[] = {0x86, 0x00, 0x00};
	szCmd[2] = p;
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::control4G(u8 p)
{
	u8 szCmd[] = {0x85, 0x00, 0x00};
	szCmd[2] = p;
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::ToUIcurIsAutomateMode(u8 p)
{
	u8 szCmd[] = {0x88, 0x00};
	szCmd[1] = p;
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::GetWifiWhetherInternetStatus()
{
	u8 szCmd[] = {0x86, 0x05, 0x01};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatApp::Get4GWhetherInternetStatus()
{
	u8 szCmd[] = {0x85, 0x03, 0x01};
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}


