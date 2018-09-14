/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once
#include "DNVParam.h"

class CDNVApp;
class CDNVModule;
class CDNVParam;
class CDNVHal : public CFlyHal
{
	SINGLETON_IMPLEMENT(CDNVHal)
private:
	CDNVHal(void);
public:
	virtual ~CDNVHal(void);

public:
	void init(void);
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);

	void analyseHalMessage(halid_t halId, u8 cmd, u8 *p, u8 len);
	void analyseAgentMessage(moduleid_t id, u8 *p, u8 len);
	void comboAndCheckSum(u8 *p, u8 len);
	void processMessage(u8 *p, u8 len);

	void keyResponse(u8 p);
	void menuResponse(E_MENU_OP_STATUS e, u8 pq);
	void dnvSystemStatus(E_DNV_SYSTEM_STATUS e);
	void dnvFuncStatus(u8 s);
	void dnvWarning(u8 p);

	void warningStart(void);
	//assist
	bool isDNVFrontWorking(void);
	//发送到 NV HAL 协议
	void setToHalDirectionUp(u8 p);
	void setToHalDirectionDown(u8 p);
	void setToHalDirectionLeft(u8 p);
	void setToHalDirectionRight(u8 p);
	void setToHalDirectionOk(void);
	void setToHalMenu(void);
	void setToHalRealTimeWatch(void);
	void setToHalPlayBack(void);
	void setToHalRecord(void);
	//void setToHalNightSystem(void);
	void setToHalAvoidGlare(void);
	void setToHalFormatTFcard(void);
	void setToHalDeleteCurMovie(void);
	void setToHalQuerySoftwareVersion(void);
	void setToHalMenuGoBack(void);
	void setToHalTrafficWarning(void);
	void setToHalTrafficWarningOpen(void);
	void setToHalTrafficWarningClose(void);
	void setToHalYearMonth(int year, int month);
	void setToHalDayHour(int day, int hour);
	void setToHalMinSec(int min, int sec);
	void setToHalHeadLight(u8 shortLight, u8 longLight);
	void setToHalFogLight(u8 p);
	void setToHalCarSpeed(short p);
	void setToHalCarWheel(u8 lr, u8 angle);
	void setToHalGear(u8 p);
	void setToHalNightSystemOpen(void);
	void setToHalNightSystemClose(void);
	void setToHalFlyShallowSleep(u8 p);

	void dnvCheckSum(u8 *p, u8 len);
	//发送到 OSD HAL 协议
	void setToHalGoPage(u16 pageId);
	void setToHalViewPageWidgetCtrl(u32 id, u8 status);
	void setToHalPlayPageWidgetCtrl(u32 id, u8 status);
	void setToHalPausePageWidgetCtrl(u32 id, u8 status);
	void setToHalOtherDeviceMainPageWidgetCtrl(u32 id, u8 status);
	void setToHalOtherDeviceColorSettingPageWidgetCtrl(u32 id, u8 status);
	void setToHalDayNightMode(u8 p);
	//发送到 video
	void setToHalVideoSetting(u8 p);
	void setToHalSystemLcd(u8 p, u32 t);
public:
	E_MENU_OP_STATUS m_eMenuOperationStatus;
	E_DNV_SYSTEM_STATUS m_eDnvSystemStatus;

	E_RECORD_STATUS m_eRecordStatus;
	E_DAY_NIGHT_MODE m_eDayNightMode;
	E_FOG_SEE m_eFogSee;
	E_AVOID_GLARE m_eAvoidGlare;
	E_HUMAN_WARNING m_eHumanWarning;
	E_ROAD_WARNING m_eRoadWarning;
	E_TRAFFIC_WARNING m_eTrafficWarning;
	E_TF_CARD m_eTFcard;

	u8 m_szDNVdata[256];
	int m_nMsgLen;
	int m_nPos;

	bool m_bOSDMenuHadShow;
	bool m_bMyRecIsBackMode;
	bool m_bDNVAudioWarning;
	bool m_bDNValive;
	bool m_bDNValiveTemp;
	
	ST_WARN_ITEM m_szstWarnItem[WARN_ITEM_NUM];
private:
	CDNVApp *m_pDNVApp;
	CDNVModule *m_pDNVModule;
	CDNVHal *m_pDNVHal;
	CDNVParam *m_pDNVParam;
};

