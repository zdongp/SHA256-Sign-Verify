#include "BtConnectionSetPages.h"

CBtConnectionSetPages::CBtConnectionSetPages(void)
{
}

CBtConnectionSetPages::~CBtConnectionSetPages(void)
{
}

void CBtConnectionSetPages::init(void) 
{ 

} 

void CBtConnectionSetPages::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
{ 
    m_pBtApp = (CBtApp *)pFlyApp; 
	
	m_pBtModule  = (CBtModule *)pFlyModule; 
	m_pBtHal	 = (CBtHal *)pFlyHal; 
	m_pBtParam   = (CBtParam *)pFlyParam; 

	m_pFlyApp    = pFlyApp;
	m_pFlyModule = pFlyModule;
	m_pFlyHal    = pFlyHal;
	m_pFlyParam  = pFlyParam;
} 

void CBtConnectionSetPages::initUi(void)
{
}

bool CBtConnectionSetPages::pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = false;

	bRet = btConnectionSetPages(id, e);
	if (bRet)
		return bRet;

	return bRet;
}

bool CBtConnectionSetPages::btConnectionSetPages(u32 id, E_MOUSE_STATUS e)
{
	bool bRet = true;

	switch(id)
	{
		case CONTROLID_BLUETOOTH_AUDIOVOX_CONNECTION_SWITCH_BACK:
			clickBtConnectionsSetPagesGoBack(e);
			break;
		case CONTROLID_BLUETOOTH_AUDIOVOX_CONNECTION_BLUETOOTH_PHONE_SWITCH:
			clickBtConnectionsSetPagesPhoneServer(e);
			break;
		case CONTROLID_BLUETOOTH_AUDIOVOX_CONNECTION_BLUETOOTH_MEDIA_SWITCH:
			clickBtConnectionsSetPagesMediaServer(e);
           break;
		default:
			bRet = false;
			break;
	}

	return bRet;

}

void CBtConnectionSetPages::clickBtConnectionsSetPagesGoBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
			m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME);
			break;
		default:break;
	}
}

void CBtConnectionSetPages::clickBtConnectionsSetPagesPhoneServer(E_MOUSE_STATUS e)
{

}

void CBtConnectionSetPages::clickBtConnectionsSetPagesMediaServer(E_MOUSE_STATUS e)
{

}


void CBtConnectionSetPages::DisplayUI_BtConnectionsHFP_SwitchState(E_HFP_CONNECT_STATUS em)
{
	LOGD("[%s] em:%d",__FUNCTION__,em);
	u8 uTem;
	if(em == HFP_CONNECT_STATUS_DISCONNECT)
		uTem = 0;
	else if(em == HFP_CONNECT_STATUS_CONNECTED)
		uTem = 1;
	
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONNECTION_BLUETOOTH_PHONE_SWITCH,uTem);
}

void CBtConnectionSetPages::DisplayUI_BtConnectionsAV_SwitchState(bool state)
{
	LOGD("[%s] state:%d",__FUNCTION__,state);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONNECTION_BLUETOOTH_MEDIA_SWITCH,state);
}















