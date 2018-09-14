/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "DNVParam.h"

extern CFlyModule *g_pFlyModule;

CDNVParam::CDNVParam(void)
{
}

CDNVParam::~CDNVParam(void)
{
}

void CDNVParam::init(void)
{
	//初始化参数(init param), 冷启动初始化 module 的 第一轮消息
	LOGD("[%s] [%s]", __FILE__ , __FUNCTION__);

	//HAL
	m_pDNVHal->m_eMenuOperationStatus = MENU_OP_STATUS_UNKNOW;
	m_pDNVHal->m_eDnvSystemStatus = DNV_SYSTEM_STATUS_UNKNOW;
	m_pDNVHal->m_eRecordStatus = RECORD_STATUS_UNKNOW;
	m_pDNVHal->m_eDayNightMode = DAY_NIGHT_MODE_UNKNOW;
	m_pDNVHal->m_eFogSee = FOG_SEE_UNKNOW;
	m_pDNVHal->m_eAvoidGlare = AVOID_GLARE_UNKNOW;
	m_pDNVHal->m_eHumanWarning = HUMAN_WARNING_UNKNOW;
	m_pDNVHal->m_eRoadWarning = ROAD_WARNING_UNKNOW;
	m_pDNVHal->m_eTrafficWarning = TRAFFIC_WARNING_UNKNOW;
	m_pDNVHal->m_eTFcard = TF_CARD_UNKNOW;

	memset((char*)m_pDNVHal->m_szDNVdata, 0, sizeof(m_pDNVHal->m_szDNVdata));
	m_pDNVHal->m_nMsgLen = 0;
	m_pDNVHal->m_nPos = 0;

	m_pDNVHal->m_bOSDMenuHadShow = false;

	ST_WARN_ITEM stWarnItem;
	stWarnItem.warnId = WARNING_AUDIO_FILE_ID_HUMAN_IN_THE_FRONT;
	stWarnItem.warnTime = 3000;
	stWarnItem.bNeedWarn = false;
	m_pDNVHal->m_szstWarnItem[WARN_SCAN_ID_HUMAN_IN_THE_FRONT] = stWarnItem;

	stWarnItem.warnId = WARNING_AUDIO_FILE_ID_WHEEL_PASS_ROAD_LINE;
	stWarnItem.warnTime = 3000;
	stWarnItem.bNeedWarn = false;
	m_pDNVHal->m_szstWarnItem[WARN_SCAN_ID_WHEEL_PASS_ROAD_LINE] = stWarnItem;

	m_pDNVHal->m_bMyRecIsBackMode = true;
	m_pDNVHal->m_bDNVAudioWarning = false;
	m_pDNVHal->m_bDNValive = false;
	m_pDNVHal->m_bDNValiveTemp = false;
	//MODULE
	m_pDNVModule->m_bSystemStartNeedSyncTimeToDNV = true;
	m_pDNVModule->m_bInDNV = false;
	m_pDNVModule->m_bSurportDNV = true;
	m_pDNVModule->m_nCurClickBtn = CUR_CLICK_BTN_DEFAULT_VALUE;

	map<int, bool>::iterator itFrom = m_pDNVModule->m_mapCtrlIdHaveDown.begin();
	map<int, bool>::iterator itTo = m_pDNVModule->m_mapCtrlIdHaveDown.end();
	m_pDNVModule->m_mapCtrlIdHaveDown.erase(itFrom, itTo);	//浣跨敤鍓嶆竻绌?	//APP
	m_pDNVApp->m_bOpenCloseBoxHadShow = false;
	m_pDNVApp->m_bBuDingCanPassEvenModeIsTheSame = false;
	
	m_pDNVApp->m_bDeleteFileWorking = false;;
	m_pDNVApp->m_bFormatSDcardWorking = false;
	m_pDNVApp->m_bTrafficSelectionWorking = false;
	m_pDNVApp->m_bVersionWroking = false;

	m_pDNVModule->m_bCanShowPlayPause = true;
}

void CDNVParam::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
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

void CDNVParam::readParameter(void)
{
	LOGD("[%s]", __FUNCTION__);

	
}

void CDNVParam::saveParameter(void)
{
	LOGD("[%s]", __FUNCTION__);

	
}

uni16_size_t CDNVParam::uni16_strlen(const unicode16_t *uni16)
{
	return 0;
}
unicode16_t CDNVParam::ansi_to_unicode16(const unsigned char ansi)
{
	return 0;
}
uni16_size_t CDNVParam::ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16)
{
	int nSrcLen = strlen((char*)ansi);
	int nUni16Len = nSrcLen*2+2;
	int nRetLen = utf8_2_ucs2(ansi, nSrcLen, (u8*)uni16, nUni16Len);
	
	return (nRetLen/2);
}
unicode16_t * CDNVParam::uni16_strcpy(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
unicode16_t * CDNVParam::uni16_strcat(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
uni16_size_t CDNVParam::utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16)
{
	return 0;
}



