#pragma once
#include "BtParam.h"

class CBtApp;
class CBtModule;
class CBtHal;
class CBtParam;


class CMusicBrowsingPage :
	public CFlyApp
{
public:
	CMusicBrowsingPage(void);
	virtual ~CMusicBrowsingPage(void);

public:
	//init
	virtual void init(void);
	virtual void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);
	void initUi(void);
public:	
	bool pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool btMusicBrowsingPage(u32 id, E_MOUSE_STATUS e);
	void clickMusicBrowsingGoBack(E_MOUSE_STATUS e);
	void clickMusicBrowsingSwitchLevel(u8 p,E_MOUSE_STATUS e);
	void clickMusicBrowsingSetTheSong(u8 p,E_MOUSE_STATUS e);
	void clickMusicBrowsingMenu(u32 uId,E_MOUSE_STATUS e);
	void clickMusicBrowsingRefresh(E_MOUSE_STATUS e);
	void ClearPlaylistsText(void);
	void createListPlayLists(void);
	void ToUI_DisplayPlaylists(u8 *param,int len);

	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;
};

