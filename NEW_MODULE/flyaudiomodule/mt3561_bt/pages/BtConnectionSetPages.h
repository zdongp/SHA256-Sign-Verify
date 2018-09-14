#pragma once
#include "BtParam.h"

class CBtApp;
class CBtModule;
class CBtHal;
class CBtParam;


class CBtConnectionSetPages :
	public CFlyApp
{
public:
	CBtConnectionSetPages(void);
	virtual ~CBtConnectionSetPages(void);

public:
	//init
	virtual void init(void);
	virtual void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);
	void initUi(void);
public:	
	bool pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool btConnectionSetPages(u32 id, E_MOUSE_STATUS e);

	void clickBtConnectionsSetPagesGoBack(E_MOUSE_STATUS e);
	void clickBtConnectionsSetPagesPhoneServer(E_MOUSE_STATUS e);
	void clickBtConnectionsSetPagesMediaServer(E_MOUSE_STATUS e);
	void DisplayUI_BtConnectionsHFP_SwitchState(E_HFP_CONNECT_STATUS em);
	void DisplayUI_BtConnectionsAV_SwitchState(bool state);

	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;
};

