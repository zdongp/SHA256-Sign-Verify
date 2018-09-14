/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "DNVHal.h"

CDNVHal::CDNVHal(void)
{
}

CDNVHal::~CDNVHal(void)
{
}

void CDNVHal::init(void)
{
	// 冷启动起来调用
	LOGD("[%s] [%s]", __FILE__ , __FUNCTION__);
	
}

void CDNVHal::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
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

void CDNVHal::analyseHalMessage(halid_t halId, u8 cmd, u8 *p, u8 len)
{
	LOGD("[%s]: cmd = [0x%x]", __FUNCTION__, cmd);
	outPutLog(__FUNCTION__, "p", p, len);

	if (m_pDNVModule->m_bSurportDNV)
	{
		comboAndCheckSum(p, len);
	}
}

void CDNVHal::analyseAgentMessage(moduleid_t id, u8 *p, u8 len)
{
}

void CDNVHal::comboAndCheckSum(u8 *p, u8 len)
{
	int i = 0;
	for (i = 0; i < len; i++)
	{
		m_szDNVdata[m_nPos] = p[i];
		m_nPos++;

		switch(m_nPos)
		{
		case 0x01:
			{
				if (m_szDNVdata[0] != 0xA6)
					m_nPos = 0;
			}
			break;
		default:
			{
				if (m_nPos == 5)
				{
					u8 s = (m_szDNVdata[0] + m_szDNVdata[1] + m_szDNVdata[2] + m_szDNVdata[3]) & 0xFF;

					if (s == m_szDNVdata[4])
					{
						processMessage(m_szDNVdata, 5);
					}
					
					m_nMsgLen = 0;
					m_nPos = 0;
				}
			}
			break;
		}

	}
}

void CDNVHal::processMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);

	switch(p[1])
	{
	case 0x01://按键应答
		keyResponse(p[2]);
		break;
	case 0x11://握手
		{
			u8 t = p[2];
			E_MENU_OP_STATUS m = E_MENU_OP_STATUS(t >> 4);	//m
			E_DNV_SYSTEM_STATUS n = E_DNV_SYSTEM_STATUS(t & 0x0F);	//n
			u8 pq = p[3];

			if (n == DNV_SYSTEM_STATUS_MENU)
				menuResponse(m, pq);
			
			dnvSystemStatus(n);

			if (!(n == DNV_SYSTEM_STATUS_MENU && m == MENU_OP_STATUS_SOFTWARE_VERSION_SHOW))
				dnvFuncStatus(pq);
		}
		break;
	case 0x21://特殊功能
		{
			dnvWarning(p[2]);
		}
		break;
	}//switch(cmd)
}

void CDNVHal::keyResponse(u8 p)
{
	switch(p)
	{
	case 0x01:
		LOGD("[%s] key response ok!", __FUNCTION__);
		break;
	case 0x02:
		LOGD("[%s] key response check sum error!", __FUNCTION__);
		break;
	case 0x04:
		LOGD("[%s] key response unknow error!", __FUNCTION__);
		break;
	default:
		LOGD("[%s] key response other!", __FUNCTION__);
		break;
	}
}

void CDNVHal::menuResponse(E_MENU_OP_STATUS e, u8 pq)
{
	m_pDNVApp->updateMenuTip(e, pq);
}

void CDNVHal::dnvSystemStatus(E_DNV_SYSTEM_STATUS e)
{
	m_pDNVApp->updateSystemStatus(e);
}

void CDNVHal::dnvFuncStatus(u8 s)
{
	static E_DAY_NIGHT_MODE seDayNightMode = DAY_NIGHT_MODE_UNKNOW;
	seDayNightMode = (s & 0x01) ? DAY_NIGHT_MODE_DAY : DAY_NIGHT_MODE_NIGHT;
	if (m_eDayNightMode != seDayNightMode)
	{
		m_eDayNightMode = seDayNightMode;
		m_pDNVApp->updateDayNightMode(m_eDayNightMode);
	}
	
	static E_FOG_SEE seFogSee = FOG_SEE_UNKNOW;
	seFogSee =  (s & 0x02) ? FOG_SEE_OPEN : FOG_SEE_CLOSE;
	if (m_eFogSee != seFogSee)
	{
		m_eFogSee = seFogSee;
		m_pDNVApp->updateFogSee(m_eFogSee);
	}
	
	static E_AVOID_GLARE seAvoidGlare = AVOID_GLARE_UNKNOW;
	seAvoidGlare =  (s & 0x04) ? AVOID_GLARE_OPEN : AVOID_GLARE_CLOSE;
	if (m_eAvoidGlare != seAvoidGlare)
	{
		m_eAvoidGlare = seAvoidGlare;
		m_pDNVApp->updateAvoidGlare(m_eAvoidGlare);
	}

	static E_RECORD_STATUS seRecordStatus = RECORD_STATUS_UNKNOW;
	seRecordStatus =  (s & 0x08) ? RECORD_STATUS_OPEN: RECORD_STATUS_CLOSE;
	if (m_eRecordStatus != seRecordStatus)
	{
		m_eRecordStatus = seRecordStatus;
		m_pDNVApp->updateRecordStatus(m_eRecordStatus);
	}
	
	static E_TF_CARD seTFcard = TF_CARD_UNKNOW;
	seTFcard  =  (s & 0x10) ? TF_CARD_NONE: TF_CARD_EXIST;
	if (m_eTFcard != seTFcard)
	{
		m_eTFcard = seTFcard;
		m_pDNVApp->updateTFcard(m_eTFcard);
	}
	
	static E_TRAFFIC_WARNING seTrafficWarning = TRAFFIC_WARNING_UNKNOW;
	seTrafficWarning  =  (s & 0x80) ? TRAFFIC_WARNING_OPEN: TRAFFIC_WARNING_CLOSE;
	if (m_eTrafficWarning != seTrafficWarning)
	{
		m_eTrafficWarning = seTrafficWarning;
		m_pDNVApp->updateTrafficWarning(m_eTrafficWarning);
	}
	
	
}

void CDNVHal::dnvWarning(u8 p)
{
	u8 r = 0, s = 0, humanCheck = 0, roadCheck = 0, humanWarning  ,roadLeftWarning = 0, roadRightWarning = 0;

	humanCheck = (p >> 4) & 0x01;
	roadCheck = (p >> 5) & 0x01;
	humanWarning = p & 0x01;
	roadLeftWarning = (p >> 1) & 0x01;
	roadRightWarning = (p >> 2) & 0x01;

	LOGD("[%s] human warning %s", __FUNCTION__, (humanWarning == 1) ? "open" : "close");
 	LOGD("[%s] road left warning %s", __FUNCTION__, (roadLeftWarning == 1) ? "open" : "close");
	LOGD("[%s] road right warning %s", __FUNCTION__, (roadRightWarning == 1) ? "open" : "close");
	
	static E_HUMAN_WARNING seHumanWarning = HUMAN_WARNING_UNKNOW;
	seHumanWarning  =  (humanCheck == 1) ? HUMAN_WARNING_OPEN : HUMAN_WARNING_CLOSE;
	if (m_eHumanWarning != seHumanWarning)
	{
		m_eHumanWarning = seHumanWarning;
		m_pDNVApp->updateHumanWarning(m_eHumanWarning);
	}

	static E_ROAD_WARNING seRoadWarning = ROAD_WARNING_UNKNOW;
	seRoadWarning  =  (roadCheck == 1) ? ROAD_WARNING_OPEN : ROAD_WARNING_CLOSE;
	if (m_eRoadWarning != seRoadWarning)
	{
		m_eRoadWarning = seRoadWarning;
		m_pDNVApp->updateRoadWarning(m_eRoadWarning);
	}

	m_szstWarnItem[WARN_SCAN_ID_HUMAN_IN_THE_FRONT].bNeedWarn =  (humanWarning == 1) ? true : false;
	m_szstWarnItem[WARN_SCAN_ID_WHEEL_PASS_ROAD_LINE].bNeedWarn =  (roadLeftWarning == 1) ? true : false;
	m_szstWarnItem[WARN_SCAN_ID_WHEEL_PASS_ROAD_LINE].bNeedWarn =  (roadRightWarning == 1) ? true : false;

	if ((humanWarning == 1 || roadLeftWarning == 1 || roadRightWarning == 1) && !m_bDNVAudioWarning)
		warningStart();
}

void CDNVHal::warningStart(void)
{
	static int j = 0;
	int n = 0;
	j = j % WARN_ITEM_NUM;

	while(!m_szstWarnItem[j].bNeedWarn)
	{
		j++;
		n++;
		
		j = j % WARN_ITEM_NUM;

		if (n >= WARN_ITEM_NUM)
			break;
	}

	if (n < WARN_ITEM_NUM)
	{
		m_bDNVAudioWarning = true;
		m_szstWarnItem[j].bNeedWarn = false;

		m_pDNVModule->setToCenterPlayAudio(m_szstWarnItem[j].warnId);
		m_pDNVModule->setTimerAudioWarning(m_szstWarnItem[j].warnTime);

		LOGD("[%s] warnId = [%d]", __FUNCTION__, m_szstWarnItem[j].warnId);
	}

	j++;
}

//assist
bool CDNVHal::isDNVFrontWorking(void)
{
	bool bRet = false;
	if (m_eDnvSystemStatus == DNV_SYSTEM_STATUS_VIEW ||
	     m_eDnvSystemStatus == DNV_SYSTEM_STATUS_PLAY ||
	     m_eDnvSystemStatus == DNV_SYSTEM_STATUS_PAUSE ||
	     m_eDnvSystemStatus == DNV_SYSTEM_STATUS_MENU)
		{
			bRet = true;
		}

	return bRet;
}
//////////////////////////////////////////////////////////////////////////
void CDNVHal::setToHalDirectionUp(u8 p)
{
	u8 szMsg[4] = {0xA5, 0x01, p, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalDirectionDown(u8 p)
{
	u8 szMsg[4] = {0xA5, 0x02, p, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalDirectionLeft(u8 p)
{
	u8 szMsg[4] = {0xA5, 0x03, p, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalDirectionRight(u8 p)
{
	u8 szMsg[4] = {0xA5, 0x04, p, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalDirectionOk(void)
{
	u8 szMsg[4] = {0xA5, 0x05, 0x04, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalMenu(void)
{
	u8 szMsg[4] = {0xA5, 0x06, 0x04, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalRealTimeWatch(void)
{
	u8 szMsg[4] = {0xA5, 0x07, 0x04, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalPlayBack(void)
{
	u8 szMsg[4] = {0xA5, 0x08, 0x04, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalRecord(void)
{
	u8 szMsg[4] = {0xA5, 0x09, 0x04, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

/*
void CDNVHal::setToHalNightSystem(void)
{
	u8 szMsg[4] = {0xA5, 0x0A, 0x01, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}
*/

void CDNVHal::setToHalAvoidGlare(void)
{
	u8 szMsg[4] = {0xA5, 0x0B, 0x01, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalFormatTFcard(void)
{
	u8 szMsg[4] = {0xA5, 0x0C, 0x01, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalDeleteCurMovie(void)
{
	u8 szMsg[4] = {0xA5, 0x0C, 0x02, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalQuerySoftwareVersion(void)
{
	u8 szMsg[4] = {0xA5, 0x0C, 0x03, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalMenuGoBack(void)
{
	u8 szMsg[4] = {0xA5, 0x0C, 0x05, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalTrafficWarning(void)
{
	u8 szMsg[4] = {0xA5, 0x0C, 0x06, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalTrafficWarningOpen(void)
{
	u8 szMsg[4] = {0xA5, 0x0C, 0x07, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalTrafficWarningClose(void)
{
	u8 szMsg[4] = {0xA5, 0x0C, 0x08, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalFlyShallowSleep(u8 p)
{
	u8 szMsg[4] = {0xA5, 0x0C, 0x09, p};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalYearMonth(int year, int month)
{
	u8 szMsg[4] = {0xA5, 0x33, 0x00, 0x00};

	szMsg[2] = year % 100;
	szMsg[3] = month % 100;

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalDayHour(int day, int hour)
{
	u8 szMsg[4] = {0xA5, 0x34, 0x00, 0x00};

	szMsg[2] = day % 100;
	szMsg[3] = hour % 100;

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalMinSec(int min, int sec)
{
	u8 szMsg[4] = {0xA5, 0x35, 0x00, 0x00};

	szMsg[2] = min % 100;
	szMsg[3] = sec % 100;

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalHeadLight(u8 shortLight, u8 longLight)
{
	u8 szMsg[4] = {0xA5, 0x30, 0x00, 0x00};

	szMsg[2] = shortLight;
	szMsg[3] = longLight;

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalFogLight(u8 p)
{
	u8 szMsg[4] = {0xA5, 0x31, 0x00, 0x00};

	szMsg[2] = p;

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalCarSpeed(short p)
{
	u8 szMsg[4] = {0xA5, 0x32, 0x00, 0x00};

	memcpy(szMsg + 2, &p, 2);

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalCarWheel(u8 lr, u8 angle)
{
	u8 szMsg[4] = {0xA5, 0x36, 0x00, 0x00};

	szMsg[2] = lr;
	szMsg[3] = angle;

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalGear(u8 p)
{
	u8 szMsg[4] = {0xA5, 0x37, 0x00, 0x00};

	szMsg[2] = p;

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalNightSystemOpen(void)
{
	u8 szMsg[4] = {0xA5, 0x11, 0x01, 0x01};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalNightSystemClose(void)
{
	m_bMyRecIsBackMode = true;
	
	u8 szMsg[4] = {0xA5, 0x11, 0x01, 0x00};

	dnvCheckSum(szMsg, sizeof(szMsg));
}

void CDNVHal::dnvCheckSum(u8 *p, u8 len)
{
	u8 szMsg[6] = {0};

	u8 s = (p[0] + p[1] + p[2] + p[3]) & 0xFF;
	szMsg[0] = 0x01;
	memcpy(szMsg + 1, p, len);

	szMsg[5] = s;
	
	if (m_pDNVModule->m_bSurportDNV)
	{
		makeAndSendMessageToHal(HAL_ID_NV, szMsg, sizeof(szMsg));
	}	
}

//发送到 OSD HAL 协议
void CDNVHal::setToHalGoPage(u16 pageId)
{
	if (m_bOSDMenuHadShow == false && OSD_T123_PAGE_NONE == pageId)
		return ;
	
	LOGD("[%s] pageId = [0x%x]", __FUNCTION__, pageId);

	if (pageId != OSD_T123_PAGE_NONE)
		m_bOSDMenuHadShow = true;
	else
		m_bOSDMenuHadShow = false;
	
	u8 szMsg[2] = {0x01, 0x00};

	szMsg[1] = pageId;

	makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalViewPageWidgetCtrl(u32 id, u8 status)
{
	u8 szMsg[3] = {0x58, 0x00, 0x00};

	szMsg[1] = id;
	szMsg[2] = status;

	makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalPlayPageWidgetCtrl(u32 id, u8 status)
{
	u8 szMsg[3] = {0x59, 0x00, 0x00};

	szMsg[1] = id;
	szMsg[2] = status;

	makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalPausePageWidgetCtrl(u32 id, u8 status)
{
	u8 szMsg[3] = {0x5A, 0x00, 0x00};

	szMsg[1] = id;
	szMsg[2] = status;

	makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalOtherDeviceMainPageWidgetCtrl(u32 id, u8 status)
{
	u8 szMsg[3] = {0x5D, 0x00, 0x00};

	szMsg[1] = id;
	szMsg[2] = status;

	makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalOtherDeviceColorSettingPageWidgetCtrl(u32 id, u8 status)
{
	u8 szMsg[3] = {0x5E, 0x00, 0x00};

	szMsg[1] = id;
	szMsg[2] = status;

	makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalDayNightMode(u8 p)
{
	u8 szMsg[2] = {0xE1, 0x00};

	szMsg[1] = p;

	LOGD("[%s] p = [0x%x]", __FUNCTION__, p);
	
	makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, szMsg, sizeof(szMsg));
}

//发送到 video
void CDNVHal::setToHalVideoSetting(u8 p)
{
	u8 szMsg[2] = {0x11, 0x00};

	szMsg[1] = p;

	makeAndSendMessageToHal(HAL_ID_VIDEO, szMsg, sizeof(szMsg));
}

void CDNVHal::setToHalSystemLcd(u8 p, u32 t)
{
	LOGD("[%s] p = [0x%x]", __FUNCTION__, p);

	u8 szMsg[6] = {0};

	szMsg[0] = 0x70;
	szMsg[1] = p;
	
	memcpy(szMsg + 2, &t, sizeof(t));

	makeAndSendMessageToHal(HAL_ID_SYSTEM, szMsg, sizeof(szMsg));
}