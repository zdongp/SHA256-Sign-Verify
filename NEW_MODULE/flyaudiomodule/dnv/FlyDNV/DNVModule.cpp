/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "DNVModule.h"

//工程根结点指针
CFlyModule *g_pFlyModule = (CFlyModule*)CDNVModule::GetInstance();

CDNVModule::CDNVModule(void)
{
	m_pDNVApp    = CDNVApp::GetInstance();
	m_pDNVModule = this;
	m_pDNVHal    = CDNVHal::GetInstance();
	m_pDNVParam  = CDNVParam::GetInstance();

	m_pFlyApp    = m_pDNVApp;
	m_pFlyModule = m_pDNVModule;
	m_pFlyHal    = m_pDNVHal;
	m_pFlyParam  = m_pDNVParam;

	m_pDNVApp->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);
	m_pDNVHal->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);
	m_pDNVParam->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);
}



CDNVModule::~CDNVModule(void)
{
}

moduleid_t CDNVModule::locale_module_mid(void)
{
	return MODULE_ID_DNV;
}

void CDNVModule::init(void)
{
	// 冷启动起来调用
	LOGD("[%s] [%s]", __FILE__, __FUNCTION__);

	m_pDNVModule->initNativeTimer();


	setTimerSyncTimeToDNV();
	setTimerPingDNV();
	
	
}


void CDNVModule::getAccOn()
{
	LOGD("[%s]", __FUNCTION__);

	m_bSystemStartNeedSyncTimeToDNV = true;
	setTimerSyncTimeToDNV();
	setTimerPingDNV();

	m_pDNVApp->updateSystemFuncStatus();
}

void CDNVModule::getAccOff()
{
	LOGD("[%s]", __FUNCTION__);

	m_bSystemStartNeedSyncTimeToDNV = false;
	killTimerSyncTimeToDNV();
	killTimerPingDNV();
}

void CDNVModule::timerHandleProc(int timerId)
{

}

int CDNVModule::nativeTimerHandlerProcess(timer_t timerId)
{
	switch((s64)timerId)
	{
	case TIMER_ID_SYNC_TIME_TO_DNV:
	{
		static int nCyleSyncCount = 0;
		static int snPreSec = 0; 

		if (m_bSystemStartNeedSyncTimeToDNV)
			nCyleSyncCount++;
		
		time_t now;
		struct tm *timenow;

		time(&now);
		timenow = localtime(&now);

		LOGD("[%s] %s", __FUNCTION__, asctime(timenow));
		
		int y = 0, month = 0, d = 0, h = 0, m = 0, s = 0, as = 0;

		y = timenow->tm_year + 1900;
		month = timenow->tm_mon + 1;
		d = timenow->tm_mday;
		
		h = timenow->tm_hour;
		m = timenow->tm_min;
		s = timenow->tm_sec;

		as = y * 3600 * 8 +  month * 3600 * 4 + d * 3600 * 2 + h * 3600 + m * 60 + s;

		LOGD("[%s] y = %d month = %d d = %d h = %d m = %d s = %d", __FUNCTION__, y & 0xFF, month, d, h, m, s);
		// 1  min or other time sync one time
		if (m_bSystemStartNeedSyncTimeToDNV && (nCyleSyncCount * TIMER_CYCLE_SYNC_TIME_TO_DNV / 1000 >= SYNC_DNV_TIME_CYCLE))
		{
			LOGD("[%s]  1  min or other time sync one time", __FUNCTION__);

			m_bSystemStartNeedSyncTimeToDNV = false;
			
			m_pDNVHal->setToHalYearMonth(y, month);
			m_pDNVHal->setToHalDayHour(d, h);
			m_pDNVHal->setToHalMinSec(m, s);
			m_pDNVHal->setToHalFlyShallowSleep(30);

			nCyleSyncCount = 0;
		}
		//time change too more
		if (abs(as - snPreSec) >= 2 * (TIMER_CYCLE_SYNC_TIME_TO_DNV / 1000))
		{
			LOGD("[%s] sec change more than normal, so sync time to dnv", __FUNCTION__);
			
			m_pDNVHal->setToHalYearMonth(y, month);
			m_pDNVHal->setToHalDayHour(d, h);
			m_pDNVHal->setToHalMinSec(m, s);
		}

		snPreSec = as;
		
	}break;
	case TIMER_ID_HIDE_OSD_MENU:
	{
		LOGD("[%s] TIMER_ID_HIDE_OSD_MENU", __FUNCTION__);

		deleteNativeTimer(TIMER_ID_CLICK_ENABLE);
		
		m_nCurClickBtn = CUR_CLICK_BTN_DEFAULT_VALUE;
		
		u16 pageId = m_pDNVModule->getCurPageId();
		
		if (isDNVOSDMenuPage(pageId))
		{
			m_pDNVModule->setPage(PAGE_DNV_VIEW_BACK_BROUND);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
		}
	}break;
	case TIMER_ID_HIDE_OTHER_DVR_MENU:
	{
		LOGD("[%s] TIMER_ID_HIDE_OTHER_DVR_MENU", __FUNCTION__);
		u16 pageId = m_pDNVModule->getCurPageId();

		if (isOtherDvrOsdMenuPage(pageId))
		{
			m_pDNVModule->setPage(PAGE_OTHER_DVR_BACKGROUND);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
		}
	}break;
	case TIMER_ID_AUDIO_WARNING:
	{
		LOGD("[%s] TIMER_ID_AUDIO_WARNING", __FUNCTION__);		
		m_pDNVHal->m_bDNVAudioWarning = false;
	}break;
	case TIMER_ID_DNV_PING:
	{
		LOGD("[%s] TIMER_ID_DNV_PING", __FUNCTION__);
		if(m_pDNVHal->m_bDNValiveTemp == false)
			m_pDNVHal->m_bDNValive = false;

		m_pDNVHal->m_bDNValiveTemp = false;
	}break;
	case TIMER_ID_HIDE_BLACK_PAGE:
	{
		LOGD("[%s] TIMER_ID_HIDE_BLACK_PAGE", __FUNCTION__);
	
		u16 pageId = m_pDNVModule->getCurPageId();

		if (pageId == PAGE_DNV_EMPTY_BLACK_PAGE)
		{
			m_pDNVModule->setPage(PAGE_DNV_VIEW_BACK_BROUND);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
		}
	}break;
	case TIMER_ID_CLICK_ENABLE:
	{
		LOGD("[%s] TIMER_ID_CLICK_ENABLE", __FUNCTION__);
		m_nCurClickBtn = CUR_CLICK_BTN_DEFAULT_VALUE;
	}break;
	case TIMER_ID_GO_TO_PLAYBACK:
	{
		LOGD("[%s] TIMER_ID_GO_TO_PLAYBACK", __FUNCTION__);
		m_pDNVHal->setToHalPlayBack();
	}break;
	case TIMER_ID_GO_TO_VIEW:
	{
		LOGD("[%s] TIMER_ID_GO_TO_VIEW", __FUNCTION__);		
		m_pDNVHal->setToHalRealTimeWatch();
	}break;
	case TIMER_ID_OPEN_LCD:
	{
		LOGD("[%s] TIMER_ID_OPEN_LCD", __FUNCTION__);
		m_pDNVHal->setToHalSystemLcd(LCD_OPEN, 0);
		LOGD("[%s] LCD ", __FUNCTION__);
	}break;
	case TIMER_ID_OEPN_CAN_SHOW_PLAY_PAUSE:
	{
		LOGD("[%s] TIMER_ID_OEPN_CAN_SHOW_PLAY_PAUSE", __FUNCTION__);
		m_pDNVModule->m_bCanShowPlayPause = true; 
	}break;
	case TIMER_ID_RESET_BUDING_MENU_CLICK:
	{
		LOGD("[%s] TIMER_ID_RESET_BUDING_MENU_CLICK", __FUNCTION__);
		m_pDNVApp->m_bDeleteFileWorking = false;;
		m_pDNVApp->m_bFormatSDcardWorking = false;
		m_pDNVApp->m_bTrafficSelectionWorking = false;
		m_pDNVApp->m_bVersionWroking = false;
	}
	break;
	default:break;

	}


	return 0;
}

void CDNVModule::getMyModuleParam(char id, u8 *p, u8 *pLen)
{
	switch((u8)id)
	{
	//case FLY_DNV_PARAM_SIGNAL:
	//	{
	//		*p = isHaveAvinSignal() ? 1 : 0;
	//		*pLen = 1;

	//		LOGD("[%s] [%s] *p = [%d]", __FUNCTION__, "FLY_DNV_PARAM_SIGNAL", *p);
	//	}
	//	break;
	case FLY_DNV_PARAM_IS_DNV_PAGE:
		{
			*p = isDNVpage(getCurPageId()) ? 1 : 0;
			*pLen = 1;

			LOGD("[%s] [%s] *p = [%d]", __FUNCTION__, "FLY_DNV_PARAM_IS_DNV_PAGE", *p);
		}
		break;
	}
}

void CDNVModule::getSystemMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);

	switch(p[0])
	{
	case 0x00:
		{
			getSystemBackKey();
		}
		break;
	case 0x01:
		{
			m_pDNVApp->enterDNVsystem();

			LOGD("[%s] enterDNVsystem", __FUNCTION__);
		}
		break;
	case 0x02:
		{
			//m_pDNVModule->m_bSurportDNV = (p[1] == 1) ? true : false;

			LOGD("[%s] m_bSurportDNV  = %s", __FUNCTION__, m_pDNVModule->m_bSurportDNV ? "yes" : "no");
		}
		break;
	case 0x03:
		{
			m_pDNVHal->setToHalDayNightMode(p[1]);
		}
		break;
	case 0xE3://page
		{
			u16 fromPageId = 0, toPageId = 0;

			memcpy(&fromPageId, (char*)p + 1, 2);
			memcpy(&toPageId, (char*)p + 3, 2);

			LOGD("[%s] from page id = [0x%x], to page id = [0x%x]", __FUNCTION__, fromPageId, toPageId);
			
			pageChange(fromPageId, toPageId);
		}
		break;
	default:
		break;
	}
}

void CDNVModule::getAudioVideoMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);

	switch(p[0])
	{
	case 0x00:
		if (p[1] == CHANNEL_DNV_CTRL || p[1] == CHANNEL_DNV_VIDEO)
		{
			m_bInDNV = true; 
			m_pDNVHal->setToHalNightSystemOpen();
			
			LOGD("[%s] enter DNV.", __FUNCTION__);
		}
		else
		{
			m_bInDNV = false;
			//m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
			
			LOGD("[%s] leave DNV.", __FUNCTION__);
		}
		break;
	}

}

void CDNVModule::getDvrMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);

	switch(p[0])
	{
	case 0x01:
		//m_pDNVApp->clickMainPageEntrance(MOUSE_STATUS_UP);
		break;
	}
}

void CDNVModule::getKeyMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);

	switch(p[1])
	{
	case 0xE2://enter dnv system 
		{
			LOGD("[%s] E_DNV_SYSTEM_STATUS = [%s]", __FUNCTION__, m_pDNVModule->getSystemStatus(m_pDNVHal->m_eDnvSystemStatus));

			if (m_pDNVHal->m_bDNValive == false)
			{
				u16 pageId = m_pDNVModule->getCurPageId();

				if (pageId == PAGE_DNV_DEVICE_SETTING_TIP)
				{
					m_pDNVModule->setPage(PAGE_MENU);
				}
				else
				{
					m_pDNVModule->setPage(PAGE_DNV_DEVICE_SETTING_TIP);
				}
				
				return;
			}
			
			if (m_pDNVHal->m_eDnvSystemStatus == DNV_SYSTEM_STATUS_STANDBY ||
			    m_pDNVHal->m_eDnvSystemStatus == DNV_SYSTEM_STATUS_LOW_POWER_CONSUME ||
			    m_pDNVHal->m_eDnvSystemStatus == DNV_SYSTEM_STATUS_BACKSTAGE_RECORD ||
			    m_pDNVHal->m_eDnvSystemStatus == DNV_SYSTEM_STATUS_UNKNOW )
				{
				
					if (m_pDNVApp->checkDeviceAndSetting())
						m_pDNVApp->enterDNVsystem();

					LOGD("[%s] enterDNVsystem", __FUNCTION__);
				}
			else
				{
					m_pDNVApp->exitDNVsystem();

					LOGD("[%s] exitDNVsystem", __FUNCTION__);
				}
		}
		break;
	case 0xE3:
		{
			m_pDNVHal->setToHalAvoidGlare();

			LOGD("[%s] setToHalAvoidGlare", __FUNCTION__);
		}
		break;
	}
}

void CDNVModule::getSystemBackKey(void)
{
	LOGD("[%s]", __FUNCTION__);
	
	bool  bBackCar = getBackCarStatus();
	if (bBackCar)
	{
		LOGD("[%s] is backcar", __FUNCTION__);
		return;
	}
	
	u16 pageId = getCurPageId();

	switch(pageId)
	{
	case PAGE_DNV_VIEW_BACK_BROUND:
		{
			m_pDNVApp->exitDNVsystem();
		}
	break;
	case PAGE_DNV_VIEW:
		{
			m_pDNVModule->setPage(PAGE_DNV_VIEW_BACK_BROUND);
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
		}
	break;
	case PAGE_DNV_PLAY:
		{
			m_pDNVHal->setToHalSystemLcd(LCD_CLOSE, TIME_CYCLE_PLAYBACK_TO_VIEW_OPEN_LCD);
			LOGD("[%s] LCD ", __FUNCTION__);
			/*m_pDNVHal->setToHalRealTimeWatch();*/
			m_pDNVModule->m_bCanShowPlayPause = false;
			m_pDNVModule->setTimerOpenCanShowPlayPause();
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
			//m_pDNVModule->setPage(PAGE_DNV_EMPTY_BLACK_PAGE);
			//m_pDNVModule->setTimerHideBlackPage(TIME_CYCLE_PLAYBACK_TO_VIEW);
			m_pDNVModule->setTimerGoToView();
		}
	break;
	case PAGE_DNV_PAUSE:
		{
			m_pDNVHal->setToHalSystemLcd(LCD_CLOSE, TIME_CYCLE_PLAYBACK_TO_VIEW_OPEN_LCD);
			LOGD("[%s] LCD ", __FUNCTION__);
			/*m_pDNVHal->setToHalRealTimeWatch();*/
			m_pDNVModule->m_bCanShowPlayPause = false;
			m_pDNVModule->setTimerOpenCanShowPlayPause();
			m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
			//m_pDNVModule->setPage(PAGE_DNV_EMPTY_BLACK_PAGE);
			//m_pDNVModule->setTimerHideBlackPage(TIME_CYCLE_PLAYBACK_TO_VIEW);
			m_pDNVModule->setTimerGoToView();
		}
	break;
	case PAGE_DNV_MENU:
		{
			m_pDNVHal->setToHalMenuGoBack();
		}
	break;
	case PAGE_DNV_TIP:
	case PAGE_DNV_SOFTWARE_VERSION:
	case PAGE_DNV_EMPTY_BLACK_PAGE:
		break;
	default:
		{
			m_pDNVApp->enterDNVsystem();
		}
		break;
	}
}

void CDNVModule::pageChange(u16 fromPageId, u16 toPageId)
{
	if (m_pDNVHal->m_bOSDMenuHadShow && !isDNVOSDMenuPage(toPageId))
	{
		m_pDNVHal->setToHalGoPage(OSD_T123_PAGE_NONE);
	}

	if (!isDNVpage(toPageId))
	{
		m_pDNVModule->m_bInDNV = false;
		
		if (m_pDNVHal->isDNVFrontWorking())
			m_pDNVHal->setToHalNightSystemClose();
	}
	else
	{
		m_pDNVModule->m_bInDNV = true;
		m_pDNVHal->setToHalNightSystemOpen();
	}
}

bool CDNVModule::isDNVpage(u16 pageId)
{
	bool bRet = false;

	if (pageId == PAGE_DNV_VIEW ||
	    pageId == PAGE_DNV_PLAY ||
	    pageId == PAGE_DNV_PAUSE ||
	    pageId == PAGE_DNV_MENU ||
	    pageId == PAGE_DNV_TIP ||
	    pageId == PAGE_DNV_SOFTWARE_VERSION ||
	    pageId == PAGE_DNV_VIEW_BACK_BROUND ||
	    pageId == PAGE_DNV_EMPTY_BLACK_PAGE)
		bRet = true;
	
	LOGD("[%s] %s", __FUNCTION__, bRet ? "yes" : "no");

	return bRet;
}

bool CDNVModule::isDNVOSDMenuPage(u16 pageId)
{
	bool bRet = false;

	if (pageId == PAGE_DNV_VIEW ||
	    pageId == PAGE_DNV_PLAY ||
	    pageId == PAGE_DNV_PAUSE)
		bRet = true;
	
	LOGD("[%s] %s", __FUNCTION__, bRet ? "yes" : "no");

	return bRet;
}

bool CDNVModule::isOtherDvrOsdMenuPage(u16 pageId)
{
	bool bRet = false;

	if (pageId == PAGE_OTHER_DVR_MAIN ||
		pageId == PAGE_OTHER_DVR_COLOR_SET)
		bRet = true;

	LOGD("[%s] %s", __FUNCTION__, bRet ? "yes" : "no");

	return bRet;
}

void CDNVModule::setTimerSyncTimeToDNV(void)
{
	setNativeTimer(TIMER_CYCLE_SYNC_TIME_TO_DNV, 0, TIMER_ID_SYNC_TIME_TO_DNV);
	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::killTimerSyncTimeToDNV(void)
{
	deleteNativeTimer(TIMER_ID_SYNC_TIME_TO_DNV);
	
	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::setTimerHideOSDmenu(void)
{
	deleteNativeTimer(TIMER_ID_HIDE_OSD_MENU);
	setNativeTimer(TIMER_CYCLE_HIDE_OSD_MENU, 1, TIMER_ID_HIDE_OSD_MENU);

	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::killTimerHideOSDmenu(void)
{
	deleteNativeTimer(TIMER_ID_HIDE_OSD_MENU);
	
	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::setTimerHideOtherDvrOSDmenu(void)
{
	deleteNativeTimer(TIMER_ID_HIDE_OTHER_DVR_MENU);
	setNativeTimer(TIMER_CYCLE_HIDE_OSD_MENU, 1, TIMER_ID_HIDE_OTHER_DVR_MENU);

	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::killTimerHideOtherDvrOSDmenu(void)
{
	deleteNativeTimer(TIMER_ID_HIDE_OTHER_DVR_MENU);

	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::setTimerAudioWarning(int time)
{
	deleteNativeTimer(TIMER_ID_AUDIO_WARNING);
	setNativeTimer(time, 1, TIMER_ID_AUDIO_WARNING);

	LOGD("[%s]", __FUNCTION__);	
}

void CDNVModule::killTimerAudioWarning(void)
{
	deleteNativeTimer(TIMER_ID_AUDIO_WARNING);

	LOGD("[%s]", __FUNCTION__);	
}

void CDNVModule::setTimerPingDNV(void)
{
	setNativeTimer(TIMER_CYCLE_PING_DNV, 0, TIMER_ID_DNV_PING);
	LOGD("[%s]", __FUNCTION__);	
}

void CDNVModule::killTimerPingDNV(void)
{
	deleteNativeTimer(TIMER_ID_DNV_PING);
	
	LOGD("[%s]", __FUNCTION__);	
}

void CDNVModule::setTimerHideBlackPage(int defaultTime)
{
	deleteNativeTimer(TIMER_ID_HIDE_BLACK_PAGE);
	setNativeTimer(defaultTime, 1, TIMER_ID_HIDE_BLACK_PAGE);

	LOGD("[%s] defaultTime = [%d]", __FUNCTION__, defaultTime);	
}

void CDNVModule::killTimerHideBlackPage(void)
{
	deleteNativeTimer(TIMER_ID_HIDE_BLACK_PAGE);
	
	LOGD("[%s]", __FUNCTION__);	
}

void CDNVModule::setTimerEnableClick(int t)
{
	deleteNativeTimer(TIMER_ID_CLICK_ENABLE);
	setNativeTimer(t, 1, TIMER_ID_CLICK_ENABLE);

	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::killTimerEnableClick(void)
{
	deleteNativeTimer(TIMER_ID_CLICK_ENABLE);

	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::setTimerGoToPlayBack(void)
{
	deleteNativeTimer(TIMER_ID_GO_TO_PLAYBACK);
	setNativeTimer(TIMER_CYCLE_GO_TO_PLAYBACK, 1, TIMER_ID_GO_TO_PLAYBACK);

	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::setTimerGoToView(void)
{
	deleteNativeTimer(TIMER_ID_GO_TO_VIEW);
	setNativeTimer(TIMER_CYCLE_GO_TO_VIEW, 1, TIMER_ID_GO_TO_VIEW);

	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::setTimerOpenLcd(int defaultTime)
{
	deleteNativeTimer(TIMER_ID_OPEN_LCD);
	setNativeTimer(defaultTime, 1, TIMER_ID_OPEN_LCD);

	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::setTimerOpenCanShowPlayPause(void)
{
	deleteNativeTimer(TIMER_ID_OEPN_CAN_SHOW_PLAY_PAUSE);
	setNativeTimer(TIME_CYCLE_CAN_SHOW_PLAY_PAUSE, 1, TIMER_ID_OEPN_CAN_SHOW_PLAY_PAUSE);

	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::setTImerResetMenuClickBuDing(void)
{
	deleteNativeTimer(TIMER_ID_RESET_BUDING_MENU_CLICK);
	setNativeTimer(TIME_CYCLE_RESET_BUDING_MENU_CLICK, 1, TIMER_ID_RESET_BUDING_MENU_CLICK);

	LOGD("[%s]", __FUNCTION__);
}

void CDNVModule::syncTimeToDNV(void)
{
	time_t now;
	struct tm *timenow;

	time(&now);
	timenow = localtime(&now);

	LOGD("[%s] %s", __FUNCTION__, asctime(timenow));

	int y = 0, month = 0, d = 0, h = 0, m = 0, s = 0, as = 0;

	y = timenow->tm_year + 1900;
	month = timenow->tm_mon + 1;
	d = timenow->tm_mday;

	h = timenow->tm_hour;
	m = timenow->tm_min;
	s = timenow->tm_sec;

	m_pDNVHal->setToHalYearMonth(y, month);
	m_pDNVHal->setToHalDayHour(d, h);
	m_pDNVHal->setToHalMinSec(m, s);
}

const char* CDNVModule::getSystemStatus(E_DNV_SYSTEM_STATUS e)
{
	const char *pRet = "unknow";

	switch(e)
	{
	case DNV_SYSTEM_STATUS_LOW_POWER_CONSUME:
		pRet = "DNV_SYSTEM_STATUS_LOW_POWER_CONSUME";
		break;
	case DNV_SYSTEM_STATUS_STANDBY: 
		pRet = "DNV_SYSTEM_STATUS_STANDBY";
		break;
	case DNV_SYSTEM_STATUS_BACKSTAGE_RECORD: 
		pRet = "DNV_SYSTEM_STATUS_BACKSTAGE_RECORD";
		break;
	case DNV_SYSTEM_STATUS_VIEW:
		pRet = "DNV_SYSTEM_STATUS_VIEW";
		break;
	case DNV_SYSTEM_STATUS_MENU:
		pRet = "DNV_SYSTEM_STATUS_MENU";
		break;
	case DNV_SYSTEM_STATUS_PLAY:
		pRet = "DNV_SYSTEM_STATUS_PLAY";
		break;
	case DNV_SYSTEM_STATUS_PAUSE:
		pRet = "DNV_SYSTEM_STATUS_PAUSE";
		break;
	case DNV_SYSTEM_STATUS_UNKNOW:
		pRet = "DNV_SYSTEM_STATUS_UNKNOW";
		break;
	default:
		break;
	}

	return pRet;
}

void CDNVModule::updateDNVSupportStatus(void)
{
	
}
////////////////////////////////////////////////////////////
void CDNVModule::setToCenterPlayAudio(u8 id)
{
	u8 szMsg[3] = {0x12, 0x00, 0x00};

	szMsg[1] = id;

	makeAndSendMessageToModule(MODULE_ID_EXTCAR, MODULE_ID_CENTER, szMsg, sizeof(szMsg));
}

