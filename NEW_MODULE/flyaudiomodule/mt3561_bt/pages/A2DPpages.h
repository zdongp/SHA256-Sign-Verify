#pragma once
#include "BtParam.h"

class CBtApp;
class CBtModule;
class CBtHal;
class CBtParam;


class CA2DPpages :
	public CFlyApp
{
public:
	CA2DPpages(void);
	virtual ~CA2DPpages(void);

public:
	//init
	virtual void init(void);
	virtual void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);

	void initUi(void);
	//
	bool pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	//
	bool btA2dpMainPage(u32 id, E_MOUSE_STATUS e);
	void clearA2DPInfo();
	void displyA2DPInfo();
	void ToUI_aboutSupportMusicBrowsings(bool b);
	void clickA2dpMainPageEntrance(E_MOUSE_STATUS e);
	void clickA2dpMainPageGoBack(E_MOUSE_STATUS e);
	void clickA2dpMainPageDevice(E_MOUSE_STATUS e);
	void clickA2dpMainPagePlay(E_MOUSE_STATUS e);
	void setA2DPPlay();
	void clickA2dpMainPagePause(E_MOUSE_STATUS e);
	void setA2DPPause();
	void clickA2dpMainPageStop(E_MOUSE_STATUS e);
	void setA2DPStop();
	void clickA2dpMainPagePrev(E_MOUSE_STATUS e);
	void clickA2dpMainPageNext(E_MOUSE_STATUS e);
	void setA2DPPagePrev();
	void setA2DPPageNext();
	void clickA2dpMainPageSound(E_MOUSE_STATUS e);
	void clickA2dpMainPageGoMusicBrowsing(E_MOUSE_STATUS e);
CBtApp    *m_pBtApp;
CBtModule *m_pBtModule;
CBtHal    *m_pBtHal;
CBtParam  *m_pBtParam;
};