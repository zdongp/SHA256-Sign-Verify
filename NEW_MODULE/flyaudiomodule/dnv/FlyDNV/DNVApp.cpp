/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "DNVApp.h" 

CDNVApp::CDNVApp() 
{ 
} 
 
CDNVApp::~CDNVApp() 
{ 
} 
 
void CDNVApp::init(void) 
{ 
	// 冷启动起来调用
	LOGD("[%s] [%s]",__FILE__ ,__FUNCTION__);

} 

void CDNVApp::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
{ 
	m_pDNVApp	 = (CDNVApp *)pFlyApp; 
	m_pDNVModule = (CDNVModule *)pFlyModule; 
	m_pDNVHal	 = (CDNVHal *)pFlyHal; 
	m_pDNVParam  = (CDNVParam *)pFlyParam; 

	m_pFlyApp    = pFlyApp;
	m_pFlyModule = pFlyModule;
	m_pFlyHal    = pFlyHal;
	m_pFlyParam  = pFlyParam;
} 

void CDNVApp::processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	LOGD("[%s] id12 = [0x%x], mouseStatus = [%s]", __FUNCTION__, id, getMouseMessageType(e));
	outPutLog(__FUNCTION__, "p", p, len);

	bool bCanPass = true;

	bCanPass = isMouseMsgCanPass(id, e);
	LOGD("[%s] bCanPass = [%s]", __FUNCTION__, bCanPass ? "yes" : "no");

	if (!bCanPass)
	{
		return;
	}

	bool bRet = false;

	if (m_pDNVModule->m_bSurportDNV)
	{
		bRet = dnvBackGroundPage(id, e, p, len);
		if (bRet)
			return ;

		bRet = false;
		bRet = dnvMainPage(id, e, p, len);
		if (bRet)
			return ;

		bRet = false;
		bRet = dnvPlayPage(id, e, p, len);
		if (bRet)
			return ;

		bRet = false;
		bRet = dnvPausePage(id, e, p, len);
		if (bRet)
			return ;

		bRet = false;
		bRet = dnvSettingPage(id, e, p, len);
		if (bRet)
			return ;

		bRet = false;
		bRet = dnvVersionPage(id, e, p, len);
		if (bRet)
			return ;
	}
	else
	{
		bRet = false;
		bRet = otherDeviceBackGroundPage(id, e, p, len);
		if (bRet)
			return ;

		bRet = false;
		bRet = otherDeviceMainPage(id, e, p, len);
		if (bRet)
			return ;

		bRet = false;
		bRet = otherDeviceVideoColorSetting(id, e, p, len);
		if (bRet)
			return ;
	}

	bRet = false;
	bRet = dnvTipPage(id, e, p, len);
	if (bRet)
		return ;
}

void CDNVApp::appCmdCtrl(u8 *p, u8 len)
{
	LOGD("[%s]", __FUNCTION__);
}

//////////////////////////////////////////////////////////////////////////
bool CDNVApp::dnvBackGroundPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case CTRL_ID_DNV_BACK_BTN_BACK_GROUND:
		clickBackGoundPageFullBtn(e);
		break;
	default:
		bRet = false;
		break;
	}

	if (bRet)
		m_pDNVModule->setTimerHideOSDmenu();
	
	return bRet;
}
//page
bool CDNVApp::dnvMainPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{  
	bool bRet = true;

	switch(id)
	{
	case CTRL_ID_DNV_VIEW_BTN_ENTRANCE:
		clickMainPageEntrance(e);
		break;
	case CTRL_ID_DNV_VIEW_BTN_HOME:
		clickMainPageHome(e);
		break;
	case CTRL_ID_DNV_VIEW_BTN_UP:
		clickMainPageUp(e);
		break;
	case CTRL_ID_DNV_VIEW_BTN_DOWN:
		clickMainPageDown(e);
		break;
	case CTRL_ID_DNV_VIEW_BTN_LEFT:
		clickMainPageLeft(e);
		break;
	case CTRL_ID_DNV_VIEW_BTN_RIGHT:
		clickMainPageRight(e);
		break;
	case CTRL_ID_DNV_VIEW_BTN_OK:
		clickMainPageOk(e);
		break;
	case CTRL_ID_DNV_VIEW_BTN_PLAYBACK:
		clickMainPagePlayBack(e);
		break;
	case CTRL_ID_DNV_VIEW_BTN_RECORD:
		clickMainPageRecord(e);
		break;
	case CTRL_ID_DNV_VIEW_BTN_BACK_GROUND:
		clickMainPageBackGround(e);
		break;
	default:
		bRet = false;
		break;
	}

	if (bRet)
		m_pDNVModule->setTimerHideOSDmenu();
	
	return bRet;
}

bool CDNVApp::dnvPlayPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case  CTRL_ID_DNV_PLAY_BTN_BACK:  
		clickPlayPageMain(e);
		break;
	case  CTRL_ID_DNV_PLAY_BTN_FB:
		clickPlayPageFB(e);
		break;
	case  CTRL_ID_DNV_PLAY_BTN_PAUSE:
		clickPlayPagePause(e);
		break;
	case  CTRL_ID_DNV_PLAY_BTN_FF:
		clickPlayPageFF(e);
		break;
	case  CTRL_ID_DNV_PLAY_BTN_MENU:
		clickPlayPageSetting(e);
		break;
	case  CTRL_ID_DNV_PLAY_BTN_VIEW:
		clickPlayPageMain(e);
		break;
	case  CTRL_ID_DNV_PLAY_BTN_HOME:
		clickPlayPageHome(e);
		break;
	case CTRL_ID_DNV_PLAY_BTN_BACK_GROUND:
		clickPlayPageBackGround(e);
		break;
	default:
		bRet = false;
		break;
	}

	if (bRet)
		m_pDNVModule->setTimerHideOSDmenu();
	
	return bRet;
}

bool CDNVApp::dnvPausePage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case  CTRL_ID_DNV_PAUSE_BTN_BACK:
		clickPausePageMain(e);
		break;
	case  CTRL_ID_DNV_PAUSE_BTN_PRE_FILE:
		clickPausePagePreMovie(e);
		break;
	case  CTRL_ID_DNV_PAUSE_BTN_PLAY:
		clickPausePagePlay(e);
		break;
	case  CTRL_ID_DNV_PAUSE_BTN_NEXT_FILE:
		clickPausePageNextMovie(e);
		break;
	case  CTRL_ID_DNV_PAUSE_BTN_MENU:
		clickPausePageSetting(e);
		break;
	case  CTRL_ID_DNV_PAUSE_BTN_VIEW:
		clickPausePageMain(e);
		break;
	case  CTRL_ID_DNV_PAUSE_BTN_HOME:
		clickPausePageHome(e);
		break;
	case CTRL_ID_DNV_PAUSE_BTN_BACK_GROUND:
		clickPausePageBackGround(e);
		break;
	default:
		bRet = false;
		break;
	}

	if (bRet)
		m_pDNVModule->setTimerHideOSDmenu();
	
	return bRet;
} 

bool CDNVApp::dnvSettingPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case  CTRL_ID_DNV_MENU_BTN_BACK:
		clickSettingPageGoBack(e);
		break;
	case  CTRL_ID_DNV_MENU_BTN_DELETE_CUR_FILE:
		clickSettingPageDeleteCurMovie(e);
		break;				
	case  CTRL_ID_DNV_MENU_BTN_TF_CARD_FORMAT:
		clickSettingPageFormatTFcard(e);
		break;				
	case CTRL_ID_DNV_MENU_BTN_TRAFFIC_WARNING:
		clickSettingPageTrafficWarning(e);
		break;	
	case CTRL_ID_DNV_MENU_BTN_SOFTWARE_VERSION:
		clickSettingPageDNVVersion(e);
		break;
	case CTRL_ID_DNV_MENU_BOX_BTN_OK:
		clickSettingPageBoxOk(e);
		break;
	case CTRL_ID_DNV_MENU_BOX_BTN_CANCEL:
		clickSettingPageBoxCancle(e);
		break;
	case CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_OPEN:
		clickSettingPageTrafficBoxOpen(e);
		break;
	case CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_CLOSE:
		clickSettingPageTrafficBoxClose(e);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

bool CDNVApp::dnvVersionPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case CTRL_ID_DNV_VERSION_BTN_BACK:
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
	
}

bool CDNVApp::dnvTipPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case CTRL_ID_DNV_TIP_BTN_GO_BACK:
		clickTipPageGoBack(e);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

bool CDNVApp::otherDeviceBackGroundPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case CTRL_ID_OTHER_DVR_BACKGROUND_BACKGROUND:
		clickOtherDeviceBackGroundPageBackGround(e);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}
bool CDNVApp::otherDeviceMainPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case CTRL_ID_DNV_VIEW_BTN_ENTRANCE:
		clickOtherDeviceMainPageEntrance(e);
		break;
	case CTRL_ID_OTHER_DVR_MAIN_BACKGROUND:
		clickOtherDeviceMainPageBackGround(e);
		break;
	case CTRL_ID_OTHER_DVR_MAIN_GO_BACK:
		clickOtherDeviceMainPageGoBack(e);
		break;
	case CTRL_ID_OTHER_DVR_MAIN_SET_COLOR:
		clickOtherDeviceMainPageSetting(e);
		break;
	default:
		bRet = false;
		break;
	}

	if (bRet)
		m_pDNVModule->setTimerHideOtherDvrOSDmenu();

	return bRet;
}

bool CDNVApp::otherDeviceVideoColorSetting(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case CTRL_ID_OTHER_DVR_COLOR_SET_BACKGROUND:
		clickOtherDeviceSetColorPageBackGround(e);
		break;
	case CTRL_ID_OTHER_DVR_COLOR_SET_SATURATION_DOWN:
		clickOtherDeviceSetColorPageSaturationDown(e);
		break;
	case CTRL_ID_OTHER_DVR_COLOR_SET_SATURATION_UP:
		clickOtherDeviceSetColorPageSaturationUp(e);
		break;
	case CTRL_ID_OTHER_DVR_COLOR_SET_BRIGHTNESS_DOWN:
		clickOtherDeviceSetColorPageBrightnessDown(e);
		break;
	case CTRL_ID_OTHER_DVR_COLOR_SET_BRIGHTNESS_UP:
		clickOtherDeviceSetColorPageBrightnessUp(e);
		break;
	case CTRL_ID_OTHER_DVR_COLOR_SET_COLOR_DOWN:
		clickOtherDeviceSetColorPageColorDown(e);
		break;
	case CTRL_ID_OTHER_DVR_COLOR_SET_COLOR_UP:
		clickOtherDeviceSetColorPageColorUp(e);
		break;
	case CTRL_ID_OTHER_DVR_COLOR_SET_CONTRAST_DOWN:
		clickOtherDeviceSetColorPageContrastDown(e);
		break;
	case CTRL_ID_OTHER_DVR_COLOR_SET_CONTRAST_UP:
		clickOtherDeviceSetColorPageContrastUp(e);
		break;
	default:
		bRet = false;
		break;
	}
	
	if (bRet)
		m_pDNVModule->setTimerHideOtherDvrOSDmenu();

	return bRet;
}

//back ground page
void CDNVApp::clickBackGoundPageFullBtn(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			switch(m_pDNVHal->m_eDnvSystemStatus)
			{
			case DNV_SYSTEM_STATUS_VIEW:
				{
					//updateSystemFuncStatus();
					m_pDNVModule->setPage(PAGE_DNV_VIEW);
					m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_VIEW);
				}
				break;
			case DNV_SYSTEM_STATUS_PLAY:
				{
					m_pDNVModule->setPage(PAGE_DNV_PLAY);
					m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_PLAY);
				}
				break;
			case DNV_SYSTEM_STATUS_PAUSE:
				{
					m_pDNVModule->setPage(PAGE_DNV_PAUSE);
					m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_PAUSE);
				}
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}
//main page
void CDNVApp::clickMainPageEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if (checkDeviceAndSetting())
				enterDNVsystem();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickMainPageHome(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_HOME, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_HOME, OSD_T123_BTN_STATUS_UP);
			exitDNVsystem();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickMainPageUp(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_UP, OSD_T123_BTN_STATUS_DOWN);
			m_pDNVHal->setToHalDirectionUp(DIRECTION_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_UP, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalDirectionUp(DIRECTION_STATUS_UP);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickMainPageDown(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_DOWN, OSD_T123_BTN_STATUS_DOWN);
			m_pDNVHal->setToHalDirectionDown(DIRECTION_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_DOWN, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalDirectionDown(DIRECTION_STATUS_UP);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickMainPageLeft(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_LEFT, OSD_T123_BTN_STATUS_DOWN);
			m_pDNVHal->setToHalDirectionLeft(DIRECTION_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_LEFT, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalDirectionLeft(DIRECTION_STATUS_UP);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickMainPageRight(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_RIGHT, OSD_T123_BTN_STATUS_DOWN);
			m_pDNVHal->setToHalDirectionRight(DIRECTION_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_RIGHT, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalDirectionRight(DIRECTION_STATUS_UP);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickMainPageOk(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_OK, OSD_T123_BTN_STATUS_DOWN);

		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_OK, OSD_T123_BTN_STATUS_UP);
			//m_pDNVModule->setPage(PAGE_DNV_EMPTY_BLACK_PAGE);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickMainPagePlayBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_PLAYBACK, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_PLAYBACK, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalSystemLcd(LCD_CLOSE, TIME_CYCLE_VIEW_TO_PLAYBACK_OPEN_LCD);
			LOGD("[%s] LCD ", __FUNCTION__);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
		/*	m_pDNVModule->setPage(PAGE_DNV_EMPTY_BLACK_PAGE);
			m_pDNVModule->setTimerHideBlackPage(TIME_CYCLE_VIEW_TO_PLAYBACK);*/
			//m_pDNVModule->setTimerHideBlackPage(TIME_CYCLE_VIEW_TO_PLAYBACK);
			m_pDNVModule->setTimerGoToPlayBack();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickMainPageRecord(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_RECORD, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_RECORD, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalRecord();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickMainPageBackGround(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pDNVModule->setPage(PAGE_DNV_VIEW_BACK_BROUND);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
		}
		break;
	default:
		break;
	}
}

//play page
void CDNVApp::clickPlayPageHome(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_HOME, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_HOME, OSD_T123_BTN_STATUS_UP);
			exitDNVsystem();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPlayPageSetting(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_MENU, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_MENU, OSD_T123_BTN_STATUS_UP);
			//m_pDNVHal->setToHalSystemLcd(LCD_CLOSE, TIME_CYCLE_PLAYBACK_TO_MENU_OPEN_LCD);
			m_pDNVHal->setToHalMenu();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPlayPageMain(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_VIEW, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVModule->m_bCanShowPlayPause = false;
			m_pDNVModule->setTimerOpenCanShowPlayPause();

			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_VIEW, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalSystemLcd(LCD_CLOSE, TIME_CYCLE_PLAYBACK_TO_VIEW_OPEN_LCD);
			LOGD("[%s] LCD ", __FUNCTION__);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
			/*m_pDNVModule->setPage(PAGE_DNV_EMPTY_BLACK_PAGE);
			m_pDNVModule->setTimerHideBlackPage(TIME_CYCLE_PLAYBACK_TO_VIEW);*/
			m_pDNVModule->setTimerGoToView();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPlayPagePause(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_PAUSE, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_PAUSE, OSD_T123_BTN_STATUS_UP);
			//m_pDNVModule->setPage(PAGE_DNV_EMPTY_BLACK_PAGE);
			m_pDNVModule->setTimerHideBlackPage();
			m_pDNVHal->setToHalDirectionOk();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPlayPageFF(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_FF, OSD_T123_BTN_STATUS_DOWN);
			m_pDNVHal->setToHalDirectionRight(DIRECTION_STATUS_DOWN);
			
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_FF, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalDirectionRight(DIRECTION_STATUS_UP);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPlayPageFB(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_FB, OSD_T123_BTN_STATUS_DOWN);
			m_pDNVHal->setToHalDirectionLeft(DIRECTION_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalPlayPageWidgetCtrl(PLAY_FB, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalDirectionLeft(DIRECTION_STATUS_UP);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPlayPageBackGround(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pDNVModule->setPage(PAGE_DNV_VIEW_BACK_BROUND);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
		}
		break;
	default:
		break;
	}
}

//pause page
void CDNVApp::clickPausePageHome(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_HOME, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_HOME, OSD_T123_BTN_STATUS_UP);
			exitDNVsystem();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPausePageSetting(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_MENU, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_MENU, OSD_T123_BTN_STATUS_UP);
			//m_pDNVHal->setToHalSystemLcd(LCD_CLOSE, TIME_CYCLE_PLAYBACK_TO_MENU_OPEN_LCD);
			m_pDNVHal->setToHalMenu();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPausePageMain(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_VIEW, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVModule->m_bCanShowPlayPause = false;
			m_pDNVModule->setTimerOpenCanShowPlayPause();

			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_VIEW, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalSystemLcd(LCD_CLOSE, TIME_CYCLE_PLAYBACK_TO_VIEW_OPEN_LCD);
			LOGD("[%s] LCD ", __FUNCTION__);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
			//m_pDNVModule->setPage(PAGE_DNV_EMPTY_BLACK_PAGE);
			//m_pDNVModule->setTimerHideBlackPage(TIME_CYCLE_PLAYBACK_TO_VIEW);
			m_pDNVModule->setTimerGoToView();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPausePagePlay(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_PLAY, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_PLAY, OSD_T123_BTN_STATUS_UP);
			//m_pDNVModule->setPage(PAGE_DNV_EMPTY_BLACK_PAGE);
			m_pDNVModule->setTimerHideBlackPage();
			m_pDNVHal->setToHalDirectionOk();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPausePagePreMovie(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_PRE_FILE, OSD_T123_BTN_STATUS_DOWN);
			m_pDNVHal->setToHalDirectionLeft(DIRECTION_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_PRE_FILE, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalDirectionLeft(DIRECTION_STATUS_UP);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPausePageNextMovie(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_NEXT_FILE, OSD_T123_BTN_STATUS_DOWN);
			m_pDNVHal->setToHalDirectionRight(DIRECTION_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalPausePageWidgetCtrl(PAUSE_NEXT_FILE, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalDirectionRight(DIRECTION_STATUS_UP);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickPausePageBackGround(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pDNVModule->setPage(PAGE_DNV_VIEW_BACK_BROUND);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
		}
		break;
	default:
		break;
	}
}

//setting page
void CDNVApp::clickSettingPageGoBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalMenuGoBack();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickSettingPageDeleteCurMovie(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if (isMenuFunWorking())
				return;
			
			m_bDeleteFileWorking = true;
			m_pDNVModule->setTImerResetMenuClickBuDing();
			showCheckBox(SETTING_TYPE_DELETE_CUR_FILE);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickSettingPageFormatTFcard(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if (isMenuFunWorking())
				return;
			
			m_bFormatSDcardWorking = true;
			m_pDNVModule->setTImerResetMenuClickBuDing();
			showCheckBox(SETTING_TYPE_FORMAT_TF_CARD);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickSettingPageTrafficWarning(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if (isMenuFunWorking())
				return;
			
			m_bTrafficSelectionWorking = true;
			m_pDNVModule->setTImerResetMenuClickBuDing();
			m_pDNVHal->setToHalTrafficWarning();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickSettingPageDNVVersion(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if (isMenuFunWorking())
				return;
			
			m_bVersionWroking = true;
			m_pDNVModule->setTImerResetMenuClickBuDing();
			m_pDNVHal->setToHalQuerySoftwareVersion();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickSettingPageBoxOk(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			hideCheckBox();

			switch(m_eSettingType)
			{
			case SETTING_TYPE_DELETE_CUR_FILE:
				m_pDNVHal->setToHalDeleteCurMovie();
				break;
			case SETTING_TYPE_FORMAT_TF_CARD:
				m_pDNVHal->setToHalFormatTFcard();
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickSettingPageBoxCancle(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			hideCheckBox();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickSettingPageTrafficBoxOpen(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			setAnalogData(CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_OPEN, 1);
			setAnalogData(CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_CLOSE,  0);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalTrafficWarningOpen();
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickSettingPageTrafficBoxClose(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			setAnalogData(CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_OPEN, 0);
			setAnalogData(CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_CLOSE,  1);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalTrafficWarningClose();
		}
		break;
	default:
		break;
	}
}
	
//tip page
void CDNVApp::clickTipPageGoBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pDNVModule->setPage(PAGE_MENU);
		}
		break;
	default:
		break;
	}
}

//other back ground page
void CDNVApp::clickOtherDeviceBackGroundPageBackGround(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pDNVModule->setPage(PAGE_OTHER_DVR_MAIN);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_OTHER_MAIN);
		}
		break;
	default:
		break;
	}
}
//other main page
void CDNVApp::clickOtherDeviceMainPageEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if (checkOtherDeviceAndSetting())
				m_pDNVModule->setPage(PAGE_OTHER_DVR_BACKGROUND);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickOtherDeviceMainPageGoBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_MAIN_BACK, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_MAIN_BACK, OSD_T123_BTN_STATUS_UP);

			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
			m_pDNVModule->setPage(PAGE_MENU);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickOtherDeviceMainPageSetting(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_MAIN_SET, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_MAIN_SET, OSD_T123_BTN_STATUS_UP);

			m_pDNVModule->setPage(PAGE_OTHER_DVR_COLOR_SET);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_OTHER_COLOR_SETTING);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickOtherDeviceMainPageBackGround(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
			m_pDNVModule->setPage(PAGE_OTHER_DVR_BACKGROUND);
		}
		break;
	default:
		break;
	}
}

//other color setting page
void CDNVApp::clickOtherDeviceSetColorPageBackGround(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
			m_pDNVModule->setPage(PAGE_OTHER_DVR_BACKGROUND);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickOtherDeviceSetColorPageSaturationDown(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_SATURATION_DOWN, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_SATURATION_DOWN, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalVideoSetting(VIDEO_SET_SATURATION_DOWN);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickOtherDeviceSetColorPageSaturationUp(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_SATURATION_UP, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_SATURATION_UP, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalVideoSetting(VIDEO_SET_SATURATION_UP);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickOtherDeviceSetColorPageBrightnessDown(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_BRIGHTNESS_DOWN, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_BRIGHTNESS_DOWN, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalVideoSetting(VIDEO_SET_BRIGHT_DOWN);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickOtherDeviceSetColorPageBrightnessUp(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_BRIGHTNESS_UP, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_BRIGHTNESS_UP, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalVideoSetting(VIDEO_SET_BRIGHT_UP);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickOtherDeviceSetColorPageColorDown(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_COLOR_DOWN, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_COLOR_DOWN, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalVideoSetting(VIDEO_SET_COLOR_DOWN);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickOtherDeviceSetColorPageColorUp(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_COLOR_UP, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_COLOR_UP, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalVideoSetting(VIDEO_SET_COLOR_UP);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickOtherDeviceSetColorPageContrastDown(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_CONTRAST_DOWN, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_CONTRAST_DOWN, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalVideoSetting(VIDEO_SET_CONTRAST_DOWN);
		}
		break;
	default:
		break;
	}
}

void CDNVApp::clickOtherDeviceSetColorPageContrastUp(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_CONTRAST_UP, OSD_T123_BTN_STATUS_DOWN);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			m_pDNVHal->setToHalOtherDeviceMainPageWidgetCtrl(OTHER_COLOR_SET_CONTRAST_UP, OSD_T123_BTN_STATUS_UP);
			m_pDNVHal->setToHalVideoSetting(VIDEO_SET_CONTRAST_UP);
		}
		break;
	default:
		break;
	}
}
//////////////////////////////////////////////////////////////////////////
//update
void CDNVApp::updateMenuTip(E_MENU_OP_STATUS p, u8 pq)
{
	if (p != m_pDNVHal->m_eMenuOperationStatus)
		{
			m_pDNVHal->m_eMenuOperationStatus = p;
		}
	else
		{
			return ;
		}
	
	const char *pTip = "unknow";
	u16 pageId = m_pDNVModule->getCurPageId();

	switch(p)
	{
	case MENU_OP_STATUS_MAIN_MENU:
		{
			pTip = "enter menu page";
			LOGD("[%s] %s", __FUNCTION__, pTip);

			if (m_bOpenCloseBoxHadShow)
			{
				hideOpenCloseBox();
			}
				
			if (pageId != PAGE_DNV_MENU)
				m_pDNVModule->setPage(PAGE_DNV_MENU);
		}
		break;
	case MENU_OP_STATUS_BEGIN_FORMAT_TF_CARD:
		{
			pTip = "format TF card begin";
			LOGD("[%s] %s", __FUNCTION__, pTip);
			
			setStringById(CTRL_ID_DNV_TIP_TEXT_TIP,  DNV_TIP_BEGIN_FORMAT_TF_CARD);
			//setAnsiSerialData(CTRL_ID_DNV_TIP_TEXT_TIP, (u8*)"format TF card begin", strlen("format TF card begin"));

			if (pageId != PAGE_DNV_TIP)
				m_pDNVModule->setPage(PAGE_DNV_TIP);
		}
		break;
	case MENU_OP_STATUS_FORMAT_TF_CARD_FINISH:
		{
			pTip = "format TF card ok";
			LOGD("[%s] %s", __FUNCTION__, pTip);

			setStringById(CTRL_ID_DNV_TIP_TEXT_TIP,  DNV_TIP_FORMAT_TF_CARD_FINISH);
			//setAnsiSerialData(CTRL_ID_DNV_TIP_TEXT_TIP, (u8*)"format TF card ok", strlen("format TF card ok"));

			if (pageId != PAGE_DNV_TIP)
				m_pDNVModule->setPage(PAGE_DNV_TIP);
		}
		break;
	case MENU_OP_STATUS_FORMAT_TF_CARD_FAIL:
		{
			pTip = "format TF card failed";
			LOGD("[%s] %s", __FUNCTION__, pTip);

			setStringById(CTRL_ID_DNV_TIP_TEXT_TIP,  DNV_TIP_OPERATION_FAIL);
			//setAnsiSerialData(CTRL_ID_DNV_TIP_TEXT_TIP, (u8*)"format TF card failed", strlen("format TF card failed"));

			if (pageId != PAGE_DNV_TIP)
				m_pDNVModule->setPage(PAGE_DNV_TIP);
		}
		break;
	case MENU_OP_STATUS_BEGIN_DELETE_CUR_FILE:
		{
			pTip = "delete current video file begin";
			LOGD("[%s] %s", __FUNCTION__, pTip);

			setStringById(CTRL_ID_DNV_TIP_TEXT_TIP,  DNV_TIP_BEGIN_DELETE_CUR_FILE);
			//setAnsiSerialData(CTRL_ID_DNV_TIP_TEXT_TIP, (u8*)"delete file begin", strlen("delete file begin"));
			
			if (pageId != PAGE_DNV_TIP)
				m_pDNVModule->setPage(PAGE_DNV_TIP);
		}
		break;
	case MENU_OP_STATUS_DELETE_CUR_FILE_FINISH:
		{
			pTip = "delete current video file ok";
			LOGD("[%s] %s", __FUNCTION__, pTip);

			setStringById(CTRL_ID_DNV_TIP_TEXT_TIP,  DNV_TIP_DELETE_CUR_FILE_FINISH);
			//setAnsiSerialData(CTRL_ID_DNV_TIP_TEXT_TIP, (u8*)"delete file ok", strlen("delete file ok"));

			if (pageId != PAGE_DNV_TIP)
				m_pDNVModule->setPage(PAGE_DNV_TIP);
		}
		break;
	case MENU_OP_STATUS_DELETE_CUR_FILE_FAIL:
		{
			pTip = "delete current video file failed";
			LOGD("[%s] %s", __FUNCTION__, pTip);

			setStringById(CTRL_ID_DNV_TIP_TEXT_TIP,  DNV_TIP_OPERATION_FAIL);
			//setAnsiSerialData(CTRL_ID_DNV_TIP_TEXT_TIP, (u8*)"delete file fail", strlen("delete file fail"));

			if (pageId != PAGE_DNV_TIP)
				m_pDNVModule->setPage(PAGE_DNV_TIP);
		}
		break;
	case MENU_OP_STATUS_SOFTWARE_VERSION_SHOW:
		{
			pTip = "enter software version page";
			LOGD("[%s] %s", __FUNCTION__, pTip);

			U8 szVersion[64] = {0};
			int nVersionBig = pq / 100, nVersionSmall = pq % 100;                  
			
			sprintf((char*)szVersion, "Ver%d.%02d", nVersionBig, nVersionSmall);
			setAnsiSerialData(CTRL_ID_DNV_VERSION_TEXT_SOFTWARE_VERSION, szVersion, strlen((char*)szVersion));
			
			if (pageId != PAGE_DNV_SOFTWARE_VERSION)
				m_pDNVModule->setPage(PAGE_DNV_SOFTWARE_VERSION);
		}
		break;
	case MENU_OP_STATUS_TRAFFIC_WARNING_SELECT:
		{
			pTip = "enter road envi check select";
			LOGD("[%s] %s", __FUNCTION__, pTip);

			if (!m_bOpenCloseBoxHadShow)
			{
				showOpenCloseBox();
			}
			
		}
		break;
	default:
		{
			pTip = "other cmd";
			LOGD("[%s] %s", __FUNCTION__, pTip);
		}
		break;
	}

	

}



void CDNVApp::updateSystemStatus(E_DNV_SYSTEM_STATUS e)
{
	m_pDNVHal->m_bDNValive = true;
	m_pDNVHal->m_bDNValiveTemp = true;
	
	LOGD("[%s] E_DNV_SYSTEM_STATUS = [%s]", __FUNCTION__, m_pDNVModule->getSystemStatus(e));

	switch(e)
	{
	case DNV_SYSTEM_STATUS_VIEW:
	case DNV_SYSTEM_STATUS_MENU:
	case DNV_SYSTEM_STATUS_PLAY:
	case DNV_SYSTEM_STATUS_PAUSE:
		{
			if (!m_pDNVModule->m_bInDNV)
			{
				return;
			}
		}
	break;
	default:
		break;
	}

	
	if (m_pDNVHal->m_eDnvSystemStatus == e)
	{
		if (m_bBuDingCanPassEvenModeIsTheSame)
			m_bBuDingCanPassEvenModeIsTheSame = false;
		else
			return ;
	}
	else
	{
		m_pDNVHal->m_eDnvSystemStatus = e;
	}
	
	
	switch(e)
	{
	case DNV_SYSTEM_STATUS_LOW_POWER_CONSUME:
		{
			LOGD("[%s] %s", __FUNCTION__, "DNV_SYSTEM_STATUS_LOW_POWER_CONSUME");
		}
		break;
	case DNV_SYSTEM_STATUS_STANDBY:
		{
			LOGD("[%s] %s", __FUNCTION__, "DNV_SYSTEM_STATUS_STANDBY");
		}
		break;
	case DNV_SYSTEM_STATUS_BACKSTAGE_RECORD:
		{
			LOGD("[%s] %s", __FUNCTION__, "DNV_SYSTEM_STATUS_BACKSTAGE_RECORD");
		}
		break;
	case DNV_SYSTEM_STATUS_VIEW:
		{
			m_pDNVModule->m_bCanShowPlayPause = true;
			
			u16 pageId = m_pDNVModule->getCurPageId();
			
			if (pageId != PAGE_DNV_VIEW_BACK_BROUND)
			{
				LOGD("[%s] LCD DNV_SYSTEM_STATUS_VIEW", __FUNCTION__);

				m_pDNVHal->setToHalSystemLcd(LCD_OPEN, 0);
				
				m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
				m_pDNVModule->setPage(PAGE_DNV_VIEW_BACK_BROUND);
				
				
			/*	m_pDNVModule->setPage(PAGE_DNV_VIEW);
				m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_VIEW);
				m_pDNVApp->updateSystemFuncStatus();
				m_pDNVModule->setTimerHideOSDmenu();*/
			}

			LOGD("[%s] %s", __FUNCTION__, "DNV_SYSTEM_STATUS_VIEW");
		}
		break;
	case DNV_SYSTEM_STATUS_MENU:
		{
			u16 pageId = m_pDNVModule->getCurPageId();
			
			if (pageId != PAGE_DNV_MENU)
			{
				m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
				m_pDNVModule->setPage(PAGE_DNV_MENU);

				//m_pDNVHal->setToHalSystemLcd(LCD_OPEN, 0);
				//m_pDNVModule->m_bCanShowPlayPause = true;
			}

			LOGD("[%s] %s", __FUNCTION__, "DNV_SYSTEM_STATUS_MENU");
		}
		break;
	case DNV_SYSTEM_STATUS_PLAY:
		{
	
			if (!m_pDNVModule->m_bCanShowPlayPause)
				return;

			u16 pageId = m_pDNVModule->getCurPageId();
			
			if (pageId != PAGE_DNV_PLAY)
			{
				m_pDNVHal->setToHalSystemLcd(LCD_OPEN, 0);
				LOGD("[%s] LCD ", __FUNCTION__);
				m_pDNVModule->setPage(PAGE_DNV_PLAY);
				m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_PLAY);

				m_pDNVModule->setTimerHideOSDmenu();
			}
			
			
			LOGD("[%s] %s", __FUNCTION__, "DNV_SYSTEM_STATUS_PLAY");
		}
		break;
	case DNV_SYSTEM_STATUS_PAUSE:
		{
	
			if (!m_pDNVModule->m_bCanShowPlayPause)
				return;

			

			u16 pageId = m_pDNVModule->getCurPageId();
			
			if (pageId != PAGE_DNV_PAUSE)
			{
				m_pDNVHal->setToHalSystemLcd(LCD_OPEN, 0);
				LOGD("[%s] LCD ", __FUNCTION__);
				m_pDNVModule->setPage(PAGE_DNV_PAUSE);
				m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_PAUSE);

				m_pDNVModule->setTimerHideOSDmenu();
			}
			
			
			LOGD("[%s] %s", __FUNCTION__, "DNV_SYSTEM_STATUS_PAUSE");
		}
		break;
	default:
		{
			LOGD("[%s] %s", __FUNCTION__, "UNKNOW");
		}
		break;
	}
}

void CDNVApp::updateRecordStatus(E_RECORD_STATUS e)
{
	m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_RECORD_STATUS, (e == RECORD_STATUS_OPEN) ? OSD_T123_BTN_STATUS_DOWN : OSD_T123_BTN_STATUS_UP);

	LOGD("[%s] %s", __FUNCTION__, (e == RECORD_STATUS_OPEN) ? "RECORD_STATUS_OPEN" : "RECORD_STATUS_CLOSE");
}

void CDNVApp::updateDayNightMode(E_DAY_NIGHT_MODE e)
{
	if (e == DAY_NIGHT_MODE_DAY)
	{
		m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_DAY, OSD_T123_BTN_STATUS_DOWN);
		m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_NIGHT, OSD_T123_BTN_STATUS_UP);

		LOGD("[%s] %s", __FUNCTION__, "DAY_NIGHT_MODE_DAY");
	}
	else if (e == DAY_NIGHT_MODE_NIGHT)
	{
		m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_NIGHT, OSD_T123_BTN_STATUS_DOWN);
		m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_DAY, OSD_T123_BTN_STATUS_UP);

		LOGD("[%s] %s", __FUNCTION__, "DAY_NIGHT_MODE_NIGHT");
	}
	else
	{
		m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_NIGHT, OSD_T123_BTN_STATUS_UP);
		m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_DAY, OSD_T123_BTN_STATUS_UP);

		LOGD("[%s] %s", __FUNCTION__, "UNKNOW");
	}
}

void CDNVApp::updateFogSee(E_FOG_SEE e)
{
	m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_FOG_SEE, (e == FOG_SEE_OPEN) ? OSD_T123_BTN_STATUS_DOWN : OSD_T123_BTN_STATUS_UP);

	LOGD("[%s] %s", __FUNCTION__, (e == FOG_SEE_OPEN) ? "FOG_SEE_OPEN" : "FOG_SEE_CLOSE");
}

void CDNVApp::updateAvoidGlare(E_AVOID_GLARE e)
{
	m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_AVOID_GLARE, (e == AVOID_GLARE_OPEN) ? OSD_T123_BTN_STATUS_DOWN : OSD_T123_BTN_STATUS_UP);
	
	LOGD("[%s] %s", __FUNCTION__, (e == AVOID_GLARE_OPEN) ? "AVOID_GLARE_OPEN" : "AVOID_GLARE_CLOSE");
}

void CDNVApp::updateHumanWarning(E_HUMAN_WARNING e)
{
	m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_HUMAN_WARNING, (e == HUMAN_WARNING_OPEN) ? OSD_T123_BTN_STATUS_DOWN : OSD_T123_BTN_STATUS_UP);

	LOGD("[%s] %s", __FUNCTION__, (e == HUMAN_WARNING_OPEN) ? "HUMAN_WARNING_OPEN" : "HUMAN_WARNING_CLOSE");
}

void CDNVApp::updateRoadWarning(E_ROAD_WARNING e)
{
	m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_ROAD_WARNING, (e == ROAD_WARNING_OPEN) ? OSD_T123_BTN_STATUS_DOWN : OSD_T123_BTN_STATUS_UP);

	LOGD("[%s] %s", __FUNCTION__, (e == ROAD_WARNING_OPEN) ? "ROAD_WARNING_OPEN" : "ROAD_WARNING_CLOSE");
}

void CDNVApp::updateTrafficWarning(E_TRAFFIC_WARNING e)
{
	m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_TRAFFIC_WARNING, (e == TRAFFIC_WARNING_OPEN) ? OSD_T123_BTN_STATUS_DOWN : OSD_T123_BTN_STATUS_UP);

	setAnalogData(CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_OPEN,  (e == TRAFFIC_WARNING_OPEN) ? 1 : 0);
	setAnalogData(CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_CLOSE,  (e == TRAFFIC_WARNING_CLOSE) ? 1 : 0);
	
	LOGD("[%s] %s", __FUNCTION__, (e == TRAFFIC_WARNING_OPEN) ? "TRAFFIC_WARNING_OPEN" : "TRAFFIC_WARNING_CLOSE");
}

void CDNVApp::updateTFcard(E_TF_CARD e)
{
	m_pDNVHal->setToHalViewPageWidgetCtrl(VIEW_TF_CARD, (e == TF_CARD_EXIST) ? OSD_T123_BTN_STATUS_DOWN : OSD_T123_BTN_STATUS_UP);

	if (e == TF_CARD_EXIST)
	{
		m_pDNVModule->syncTimeToDNV();
	}

	LOGD("[%s] %s", __FUNCTION__, (e == TF_CARD_EXIST) ? "TF_CARD_EXIST" : "TF_CARD_NONE");
}

void CDNVApp::updateSystemFuncStatus(void)
{
	updateRecordStatus(m_pDNVHal->m_eRecordStatus);
	updateDayNightMode(m_pDNVHal->m_eDayNightMode);
	updateFogSee(m_pDNVHal->m_eFogSee);
	updateAvoidGlare(m_pDNVHal->m_eAvoidGlare);
	updateTrafficWarning(m_pDNVHal->m_eTrafficWarning);
	updateTFcard(m_pDNVHal->m_eTFcard);
}

void CDNVApp::showCheckBox(E_SETTING_TYPE e)
{
	m_eSettingType = e;

	int szMap[32] = {0};
	szMap[SETTING_TYPE_DELETE_CUR_FILE] = DNV_BOX_CHECK_DELETE_CUR_FILE;
	szMap[SETTING_TYPE_FORMAT_TF_CARD] = DNV_BOX_CHECK_FORMAT_TF_CARD;
	szMap[SETTING_TYPE_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;
	
	bool bVisible = true;
	
	setUpdateUI(false);
	
	setVisible(CTRL_ID_DNV_MENU_BOX, bVisible);
	setVisible(CTRL_ID_DNV_MENU_BOX_BTN_OK, bVisible);
	setVisible(CTRL_ID_DNV_MENU_BOX_BTN_CANCEL, bVisible);
	setVisible(CTRL_ID_DNV_MENU_BOX_TEXT_TIP, bVisible);
	setStringById(CTRL_ID_DNV_MENU_BOX_TEXT_TIP, szMap[e]);

	//if (e == SETTING_TYPE_DELETE_CUR_FILE)
		//setAnsiSerialData(CTRL_ID_DNV_MENU_BOX_TEXT_TIP, (u8*)"delete cur file", strlen("delete cur file"));
	//else 
		//setAnsiSerialData(CTRL_ID_DNV_MENU_BOX_TEXT_TIP, (u8*)"format tf card", strlen("format tf card"));

	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_BACK, WIDGET_CTRL_DISABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_DELETE_CUR_FILE, WIDGET_CTRL_DISABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_TF_CARD_FORMAT, WIDGET_CTRL_DISABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_TRAFFIC_WARNING, WIDGET_CTRL_DISABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_SOFTWARE_VERSION, WIDGET_CTRL_DISABLE);
	
	setUpdateUI(true);
}

void CDNVApp::hideCheckBox()
{
	LOGD("[%s]", __FUNCTION__);

	bool bVisible = false;
	
	setUpdateUI(false);
	setVisible(CTRL_ID_DNV_MENU_BOX, bVisible);
	setVisible(CTRL_ID_DNV_MENU_BOX_BTN_OK, bVisible);
	setVisible(CTRL_ID_DNV_MENU_BOX_BTN_CANCEL, bVisible);
	setVisible(CTRL_ID_DNV_MENU_BOX_TEXT_TIP, bVisible);

	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_BACK, WIDGET_CTRL_ENABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_DELETE_CUR_FILE, WIDGET_CTRL_ENABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_TF_CARD_FORMAT, WIDGET_CTRL_ENABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_TRAFFIC_WARNING, WIDGET_CTRL_ENABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_SOFTWARE_VERSION, WIDGET_CTRL_ENABLE);
	
	setUpdateUI(true);
}

void CDNVApp::showOpenCloseBox(void)
{
	m_bOpenCloseBoxHadShow = true;
	
	bool bVisible = true;
	
	setUpdateUI(false);
	
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX, bVisible);
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX_TEXT_TIP, bVisible);
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_OPEN, bVisible);
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_CLOSE, bVisible);
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX_TEXT_OPEN, bVisible);
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX_TEXT_CLOSE, bVisible);
	
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_BACK, WIDGET_CTRL_DISABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_DELETE_CUR_FILE, WIDGET_CTRL_DISABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_TF_CARD_FORMAT, WIDGET_CTRL_DISABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_TRAFFIC_WARNING, WIDGET_CTRL_DISABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_SOFTWARE_VERSION, WIDGET_CTRL_DISABLE);
	
	setUpdateUI(true);
}

void CDNVApp::hideOpenCloseBox(void)
{
	m_bOpenCloseBoxHadShow = false;
	
	bool bVisible = false;
	
	setUpdateUI(false);
	
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX, bVisible);
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX_TEXT_TIP, bVisible);
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_OPEN, bVisible);
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX_BTN_CLOSE, bVisible);
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX_TEXT_OPEN, bVisible);
	setVisible(CTRL_ID_DNV_MENU_TRAFFIC_BOX_TEXT_CLOSE, bVisible);
	
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_BACK, WIDGET_CTRL_ENABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_DELETE_CUR_FILE, WIDGET_CTRL_ENABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_TF_CARD_FORMAT, WIDGET_CTRL_ENABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_TRAFFIC_WARNING, WIDGET_CTRL_ENABLE);
	setCtrlEnable(CTRL_ID_DNV_MENU_BTN_SOFTWARE_VERSION, WIDGET_CTRL_ENABLE);
	
	setUpdateUI(true);
}

//assist
void CDNVApp::enterDNVsystem(void)
{
	m_pDNVModule->m_bCanShowPlayPause = true;
	m_bBuDingCanPassEvenModeIsTheSame = true;
	m_pDNVModule->m_bInDNV = true; 
	m_pDNVHal->setToHalNightSystemOpen();

	//if (m_pDNVHal->m_eDnvSystemStatus == DNV_SYSTEM_STATUS_UNKNOW)
	//	m_pDNVHal->setToHalRealTimeWatch();

}

void CDNVApp::exitDNVsystem(void)
{
	m_pDNVHal->setToHalSystemLcd(LCD_CLOSE, TIME_CYCLE_VIDEO_TO_HOME);
	LOGD("[%s] LCD ", __FUNCTION__);
	m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
	m_pDNVHal->setToHalNightSystemClose();
	m_pDNVModule->setPage(PAGE_MENU);
}

bool CDNVApp::checkDeviceAndSetting(void)
{
	bool bRet = true;

	u8 s = m_pDNVModule->getCurExternalDeviceId();

	if (s != EXTERNAL_DEVICE_DNV  || m_pDNVHal->m_bDNValive == false)
	{
		m_pDNVModule->setPage(PAGE_DNV_DEVICE_SETTING_TIP);
		bRet = false;
	}
	
	LOGD("[%s] bRet = %s", __FUNCTION__, bRet ? "yes" : "no");

	return bRet;
}

bool CDNVApp::checkOtherDeviceAndSetting(void)
{
	bool bRet = true;

	u8 s = m_pDNVModule->getCurExternalDeviceId();

	if (s != EXTERNAL_DEVICE_DNV)
	{
		m_pDNVModule->setPage(PAGE_DNV_DEVICE_SETTING_TIP);
		bRet = false;
	}
	
	LOGD("[%s] bRet = %s", __FUNCTION__, bRet ? "yes" : "no");

	return bRet;
}

bool CDNVApp::isMouseMsgCanPass(u32 id, E_MOUSE_STATUS e)
{
	if (e == MOUSE_STATUS_DOWN)
		m_pDNVModule->m_mapCtrlIdHaveDown[id] = true;
	
		
	if (m_pDNVModule->m_nCurClickBtn == CUR_CLICK_BTN_DEFAULT_VALUE && MOUSE_STATUS_DOWN == e)
	{
		m_pDNVModule->m_nCurClickBtn = id;

		switch(id)
		{
		case CTRL_ID_DNV_VIEW_BTN_UP:
		case CTRL_ID_DNV_VIEW_BTN_DOWN:
		case CTRL_ID_DNV_VIEW_BTN_LEFT:
		case CTRL_ID_DNV_VIEW_BTN_RIGHT:
		case CTRL_ID_DNV_VIEW_BTN_OK:
			m_pDNVModule->setTimerEnableClick(TIMER_CYCLE_CLICK_ENABLE * 10);
			break;
		default:
			m_pDNVModule->setTimerEnableClick(TIMER_CYCLE_CLICK_ENABLE);
			break;
		}
	}

	if (m_pDNVModule->m_nCurClickBtn != id)
	{
		LOGD("[%s] no. id = [0x%x],  mouseStatus = [%s]", __FUNCTION__, id, getMouseMessageType(e));

		map<int, bool>::iterator it = m_pDNVModule->m_mapCtrlIdHaveDown.find(id);
		bool bRetHave = (it == m_pDNVModule->m_mapCtrlIdHaveDown.end()) ? false : true;
		
		if (!bRetHave && m_pDNVModule->m_nCurClickBtn == CUR_CLICK_BTN_DEFAULT_VALUE && MOUSE_STATUS_UP == e)
			return true;
		else 
		{
			if (m_pDNVModule->m_nCurClickBtn != CUR_CLICK_BTN_DEFAULT_VALUE )
				return false;
		}
	}

	if (m_pDNVModule->m_nCurClickBtn != CUR_CLICK_BTN_DEFAULT_VALUE && MOUSE_STATUS_UP == e)
	{
		m_pDNVModule->killTimerEnableClick();
		m_pDNVModule->m_nCurClickBtn = CUR_CLICK_BTN_DEFAULT_VALUE;
	}

	return true;
}

bool CDNVApp::isMenuFunWorking(void)
{
	bool bRet = false;
	
	if(m_bDeleteFileWorking ||
	m_bFormatSDcardWorking ||
	m_bTrafficSelectionWorking ||
	m_bVersionWroking)
		bRet = true;

	LOGD("[%s] bRet = [%s]", __FUNCTION__, bRet ? "yes" : "no");
	
	return bRet;
}

////////////////////////////////////////////////////////////
