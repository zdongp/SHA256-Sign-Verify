/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once
#include "BtParam.h"
#include "BtMainPage.h"
#include "BtDevicePages.h"
#include "PhoneBookPages.h"
#include "A2DPpages.h"
#include "CallRecordPages.h"

class CBtMainPage;
class CBtDevicePages;
class CPhoneBookPages;
class CCallRecordPages;
class CA2DPpages;
class CBtModule;
class CBtHal;
class CBtParam;
class CBtApp : public CFlyApp
{
	SINGLETON_IMPLEMENT(CBtApp)
private:
	CBtApp(void);
public:
	virtual ~CBtApp(void);

public:
	//init
	virtual void init(void);
	virtual void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);
//	//ui click event
	
	void processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);

	void initUi();

	void btToApp_SendConnectState(unsigned char state);
	void btToApp_SendPairState(unsigned char state);
	void btToApp_SendBtPhoneState(unsigned char state);
	void btToApp_SendBtPowerState(unsigned char state);
	void btToApp_SendBtMac(u8 *param,int len);
	void btToApp_CallingInfors(u8 *buf,u32 len);
	void btToApp_CallingWindowPrompt(u8 p);

	bool DontDisplayWindowPromptAboutT123Video();
	void MakeCallingInforsToUI(E_BT_PHONE_STATUS e,ST_PHONE_NUM *pst);
	void SwitchToSetData(u32 id, u8 *p, u32 len);
	
	void SendPhoneNumToAppEndTag(void);
	void SendPhoneNumToApp(char *tempInof,int len);
	void SendBtMacToSdk(u8 *param,u32 len);
	void SendBtNameToSdk(u8 *param,u32 len);
	void SendConnectedBtMacToSdk(u8 *param,u32 len);
	void SendConnectedBtNameToSdk(u8 *param,u32 len);

private:
	//info head node
	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;
public:
	CBtMainPage *m_pBtMainPage;
	CBtDevicePages *m_pBtDevicePages;
	CPhoneBookPages *m_pBtPhoneBookPages;
	CCallRecordPages* m_pCallRecordPages;
	CA2DPpages *m_pA2DPpages;
};


