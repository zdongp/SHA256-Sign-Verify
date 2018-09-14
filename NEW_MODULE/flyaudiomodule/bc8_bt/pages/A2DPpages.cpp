#include "A2DPpages.h"

CA2DPpages::CA2DPpages(void)
{
}

CA2DPpages::~CA2DPpages(void)
{
}

void CA2DPpages::init(void) 
{ 

} 

void CA2DPpages::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
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

void CA2DPpages::initUi(void)
{
	refreshID3();
	ToUI_aboutSupportMusicBrowsings(false);
}

bool CA2DPpages::pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = false;

	bRet = btA2dpMainPage(id, e);
	if (bRet)
		return bRet;

	return bRet;
}

bool CA2DPpages::btA2dpMainPage(u32 id, E_MOUSE_STATUS e)
{
	bool bRet = true;

	switch(id)
	{
	case CONTROLID_BLUETOOTH_A2DP_MENU:
	case CONTROLID_BLUETOOTH_JUMP_TO_A2DP_PAGE:
		clickA2dpMainPageEntrance(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_BACK:
	case CONTROLID_BLUETOOTH_A2DP_NOSIGN_BACK:
		clickA2dpMainPageGoBack(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_DEVICE:
		clickA2dpMainPageDevice(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_PLAY:
		clickA2dpMainPagePlay(e);	
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_PAUSE:
		clickA2dpMainPagePause(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_STOP:
		clickA2dpMainPageStop(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_PREV:
		clickA2dpMainPagePrev(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_NEXT:
		clickA2dpMainPageNext(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_AUDIO:
		clickA2dpMainPageSound(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING:
		clickA2dpMainPageGoMusicBrowsing(e);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

void CA2DPpages::clickA2dpMainPageEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if (HFP_CONNECT_STATUS_CONNECTED != m_pBtModule->getBtConnectStatus())
			{   LOGD("To PAGE_BLUETOOTH_NO_A2DP");
				m_pBtModule->setPage(PAGE_BLUETOOTH_NO_A2DP);
				break;
			}

			g_pClsBtBC6Adapter->setToBtChipQueryA2dpInfo();
			m_pBtModule->setPage(PAGE_BLUETOOTH_A2DP);
		}
		break;
	default:
		break;
	}
}

void CA2DPpages::clickA2dpMainPageGoBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		m_pBtModule->setPage(PAGE_MENU);
		break;
	default:
		break;
	}
}

void CA2DPpages::clickA2dpMainPageDevice(E_MOUSE_STATUS e)
{
    switch(e)
	{
		case MOUSE_STATUS_UP:
			m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME);
			m_pBtParam->bA2DP_To_DevicePageBackButton = true;
			break;
		default:
			break;
	}
}
void CA2DPpages::clickA2dpMainPageSound(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		m_pBtModule->setPage(PAGE_SOUND);
		break;
	default:
		break;
	}
}

void CA2DPpages::clickA2dpMainPagePlay(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		setA2DPPlay();
		break;
	default:
		break;
	}
}

void CA2DPpages::clickA2dpMainPagePause(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		setA2DPPause();
		break;
	default:
		break;
	}
}

void CA2DPpages::clickA2dpMainPageStop(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
		setA2DPStop();
		}
		break;
	default:
		break;
	}
}

void CA2DPpages::clickA2dpMainPageNext(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setA2DPPageNext();
		}
		break;
	default:
		break;
	}
}

void CA2DPpages::clickA2dpMainPagePrev(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setA2DPPagePrev();
		}
		break;
	default:
		break;
	}
}

void CA2DPpages::setA2DPPlay()
{
	if(m_pBtParam->m_bIsA2dpOnPlayState == true)
		return;
	g_pClsBtBC6Adapter->setToBtChipMusicPlay();
	g_pClsBtBC6Adapter->setToBtChipQueryA2dpInfo();
}

void CA2DPpages::setA2DPPause()
{
	g_pClsBtBC6Adapter->setToBtChipMusicPause();
}

void CA2DPpages::setA2DPStop()
{
	clearA2DPInfo();
	g_pClsBtBC6Adapter->setToBtChipMusicStop();
}

void CA2DPpages::setA2DPPagePrev()
{
	g_pClsBtBC6Adapter->setToBtChipPreSong();
	g_pClsBtBC6Adapter->setToBtChipQueryA2dpInfo();
}

void CA2DPpages::setA2DPPageNext()
{
	g_pClsBtBC6Adapter->setToBtChipNextSong();
	g_pClsBtBC6Adapter->setToBtChipQueryA2dpInfo();
}

void CA2DPpages::refreshID3()
{

}

void CA2DPpages::displyA2DPInfo()
{
	//LOGD("[%s] musicName:%s,musicAuthor:%s",__FUNCTION__,m_pBtParam->musicName,m_pBtParam->musicAuthor);
	setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_TRANK,(u8*)m_pBtParam->musicName,strlen(m_pBtParam->musicName));
	setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_ARTIST,(u8*)m_pBtParam->musicAuthor,strlen(m_pBtParam->musicAuthor));
	setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_ALBUM,(u8*)m_pBtParam->musicAlbum,strlen(m_pBtParam->musicAlbum));
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_TRANK,true);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_ARTIST,true);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_ALBUM,true);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_BACKGROUND_IMAGE,true);
}

void CA2DPpages::clearA2DPInfo()
{
	memset(m_pBtParam->musicName,0,sizeof(m_pBtParam->musicName));
	memset(m_pBtParam->musicAuthor,0,sizeof(m_pBtParam->musicAuthor));
	memset(m_pBtParam->musicAlbum,0,sizeof(m_pBtParam->musicAlbum));
	m_pBtParam->musicTotal = 0;
	m_pBtParam->musicCurSong = 0;
	setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_TRANK,(u8*)"",0);
	setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_ARTIST,(u8*)"",0);
	setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_ALBUM,(u8*)"",0);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_TRANK,false);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_ARTIST,false);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_ALBUM,false);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_BACKGROUND_IMAGE,false);
	m_pBtModule->btClearAuxscreenA2DPInfors();
}

void CA2DPpages::clickA2dpMainPageGoMusicBrowsing(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		m_pBtModule->setPage(PAGE_BLUETOOTH_A2DP_MUSIC_BROWSING);
		break;
	default:
		break;
	}
}

void CA2DPpages::ToUI_aboutSupportMusicBrowsings(bool b)
{
	if(b)
	{	
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING,0);
		setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING,true);
	}
	else
	{
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING,2);
		setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_A2DP_MUSIC_BROWSING,false);
	}
}


