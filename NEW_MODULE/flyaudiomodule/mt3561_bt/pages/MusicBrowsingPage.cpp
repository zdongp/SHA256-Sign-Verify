#include "MusicBrowsingPage.h"

CMusicBrowsingPage::CMusicBrowsingPage(void)
{
}

CMusicBrowsingPage::~CMusicBrowsingPage(void)
{
}

void CMusicBrowsingPage::init(void) 
{ 

} 

void CMusicBrowsingPage::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
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

void CMusicBrowsingPage::initUi(void)
{
}

bool CMusicBrowsingPage::pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = false;

	bRet = btMusicBrowsingPage(id, e);
	if (bRet)
		return bRet;

	return bRet;
}

bool CMusicBrowsingPage::btMusicBrowsingPage(u32 id, E_MOUSE_STATUS e)
{
	bool bRet = true;

	switch(id)
	{
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_REFRESH:
			clickMusicBrowsingRefresh(e);
			break;
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_PAGE_BACK:
			clickMusicBrowsingGoBack(e);
			break;
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_TEXT_1: 
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_TEXT_2: 
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_TEXT_3:
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_TEXT_4: 
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_TEXT_5:
			clickMusicBrowsingSetTheSong(id - CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_TEXT_1 ,e);
			break;
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_UP: 
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_DOWN:
			clickMusicBrowsingSwitchLevel(id - CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_UP ,e);
			break;
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_SCROLL_BAR:
			break;
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_FOLDER:
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_ARTISTS:
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_ALBUMS:
		case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_SONGS:
			clickMusicBrowsingMenu(id ,e);
			break;
		default:
			bRet = false;
			break;
	}

	return bRet;

}

void CMusicBrowsingPage::clickMusicBrowsingRefresh(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
			m_pBtParam->m_TheFolderlistSongBrowsing.clear();
			m_pBtParam->m_theSongs.clear();
			ClearPlaylistsText();
		}
		break;
		default:break;
	}
}

void CMusicBrowsingPage::clickMusicBrowsingGoBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
			if(HFP_CONNECT_STATUS_CONNECTED == m_pBtModule->getBtConnectStatus())
			{
				m_pBtModule->setPage(PAGE_BLUETOOTH_A2DP);
			}
			else
			{
				m_pBtModule->setPage(PAGE_BLUETOOTH_NO_A2DP);
			} 
			break;
		default:
			break;
	}
}

void CMusicBrowsingPage::clickMusicBrowsingSwitchLevel(u8 p,E_MOUSE_STATUS e)
{
	u8 t = p;
	switch(e)
	{
		case MOUSE_STATUS_UP:
			if(HFP_CONNECT_STATUS_CONNECTED == m_pBtModule->getBtConnectStatus())
			{
			}
			break;
		default:break;
	}
}

void CMusicBrowsingPage::clickMusicBrowsingSetTheSong(u8 p,E_MOUSE_STATUS e)
{
	
}

void CMusicBrowsingPage::clickMusicBrowsingMenu(u32 uId,E_MOUSE_STATUS e)
{
}

void CMusicBrowsingPage::ClearPlaylistsText(void)
{
}

void CMusicBrowsingPage::ToUI_DisplayPlaylists(u8 *param,int len)
{
	int nCount = 0;
	if(m_pBtParam->curIsFolder == 1)
	{
	 	nCount = m_pBtParam->m_TheFolderlistSongBrowsing.size();
		if(nCount > 0)
		{
			int i = nCount - 1;
			setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_TEXT_1 + i,2);
			setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_TEXT_1 + i,param,len);
		}
	}
	else if(m_pBtParam->curIsFolder == 2)
	{
		nCount = m_pBtParam->m_theSongs.size();
		if(nCount > 0)
		{
			int i = nCount - 1;
			setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_TEXT_1 + i,3);
			setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING_TEXT_1 + i,param,len);
		}
	}


}


void CMusicBrowsingPage::createListPlayLists(void)
{

}



