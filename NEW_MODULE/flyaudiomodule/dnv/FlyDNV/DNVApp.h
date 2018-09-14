/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once
#include "DNVParam.h"

class CDNVModule;
class CDNVHal;
class CDNVParam;
class CDNVApp : public CFlyApp
{
	SINGLETON_IMPLEMENT(CDNVApp)
private:
	CDNVApp(void);
public:
	virtual ~CDNVApp(void);

public:
	//init
	void init(void);
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);
	//ui click event
	void processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);

	void appCmdCtrl(u8 *p, u8 len);

	//page
	bool dnvBackGroundPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool dnvMainPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool dnvPlayPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool dnvPausePage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool dnvSettingPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool dnvVersionPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool dnvTipPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);

	bool otherDeviceBackGroundPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool otherDeviceMainPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool otherDeviceVideoColorSetting(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	//back ground page
	void clickBackGoundPageFullBtn(E_MOUSE_STATUS e);
	//main page
	void clickMainPageEntrance(E_MOUSE_STATUS e);
	void clickMainPageHome(E_MOUSE_STATUS e);
	void clickMainPageUp(E_MOUSE_STATUS e);
	void clickMainPageDown(E_MOUSE_STATUS e);
	void clickMainPageLeft(E_MOUSE_STATUS e);
	void clickMainPageRight(E_MOUSE_STATUS e);
	void clickMainPageOk(E_MOUSE_STATUS e);
	void clickMainPagePlayBack(E_MOUSE_STATUS e);
	void clickMainPageRecord(E_MOUSE_STATUS e);
	void clickMainPageBackGround(E_MOUSE_STATUS e);
	//play page
	void clickPlayPageHome(E_MOUSE_STATUS e);
	void clickPlayPageSetting(E_MOUSE_STATUS e);
	void clickPlayPageMain(E_MOUSE_STATUS e);
	void clickPlayPagePause(E_MOUSE_STATUS e);
	void clickPlayPageFF(E_MOUSE_STATUS e);
	void clickPlayPageFB(E_MOUSE_STATUS e);
	void clickPlayPageBackGround(E_MOUSE_STATUS e);
	//pause page
	void clickPausePageHome(E_MOUSE_STATUS e);
	void clickPausePageSetting(E_MOUSE_STATUS e);
	void clickPausePageMain(E_MOUSE_STATUS e);
	void clickPausePagePlay(E_MOUSE_STATUS e);
	void clickPausePagePreMovie(E_MOUSE_STATUS e);
	void clickPausePageNextMovie(E_MOUSE_STATUS e);
	void clickPausePageBackGround(E_MOUSE_STATUS e);
	//setting page
	void clickSettingPageGoBack(E_MOUSE_STATUS e);
	void clickSettingPageDeleteCurMovie(E_MOUSE_STATUS e);
	void clickSettingPageFormatTFcard(E_MOUSE_STATUS e);
	void clickSettingPageTrafficWarning(E_MOUSE_STATUS e);
	void clickSettingPageDNVVersion(E_MOUSE_STATUS e);
	void clickSettingPageBoxOk(E_MOUSE_STATUS e);
	void clickSettingPageBoxCancle(E_MOUSE_STATUS e);
	void clickSettingPageTrafficBoxOpen(E_MOUSE_STATUS e);
	void clickSettingPageTrafficBoxClose(E_MOUSE_STATUS e);
	//tip page
	void clickTipPageGoBack(E_MOUSE_STATUS e);
	//other back ground page
	void clickOtherDeviceBackGroundPageBackGround(E_MOUSE_STATUS e);
	//other main page
	void clickOtherDeviceMainPageEntrance(E_MOUSE_STATUS e);
	void clickOtherDeviceMainPageGoBack(E_MOUSE_STATUS e);
	void clickOtherDeviceMainPageSetting(E_MOUSE_STATUS e);
	void clickOtherDeviceMainPageBackGround(E_MOUSE_STATUS e);
	//other color setting page
	void clickOtherDeviceSetColorPageBackGround(E_MOUSE_STATUS e);
	void clickOtherDeviceSetColorPageSaturationDown(E_MOUSE_STATUS e);
	void clickOtherDeviceSetColorPageSaturationUp(E_MOUSE_STATUS e);
	void clickOtherDeviceSetColorPageBrightnessDown(E_MOUSE_STATUS e);
	void clickOtherDeviceSetColorPageBrightnessUp(E_MOUSE_STATUS e);
	void clickOtherDeviceSetColorPageColorDown(E_MOUSE_STATUS e);
	void clickOtherDeviceSetColorPageColorUp(E_MOUSE_STATUS e);
	void clickOtherDeviceSetColorPageContrastDown(E_MOUSE_STATUS e);
	void clickOtherDeviceSetColorPageContrastUp(E_MOUSE_STATUS e);
	//update
	void updateMenuTip(E_MENU_OP_STATUS p,  u8 pq);
	void updateSystemStatus(E_DNV_SYSTEM_STATUS e);
	void updateRecordStatus(E_RECORD_STATUS e);
	void updateDayNightMode(E_DAY_NIGHT_MODE e);
	void updateFogSee(E_FOG_SEE e);
	void updateAvoidGlare(E_AVOID_GLARE e);
	void updateHumanWarning(E_HUMAN_WARNING e);
	void updateRoadWarning(E_ROAD_WARNING e);
	void updateTrafficWarning(E_TRAFFIC_WARNING e);
	void updateTFcard(E_TF_CARD e);
	void updateSystemFuncStatus(void);
	
	void showCheckBox(E_SETTING_TYPE e);
	void hideCheckBox();
	void showOpenCloseBox(void);
	void hideOpenCloseBox(void);

	//assist
	void enterDNVsystem(void);
	void exitDNVsystem(void);
	bool checkDeviceAndSetting(void);
	bool checkOtherDeviceAndSetting(void);
	bool isMouseMsgCanPass(u32 id, E_MOUSE_STATUS e);
	bool isMenuFunWorking(void);
public:
	E_SETTING_TYPE m_eSettingType;
	bool m_bOpenCloseBoxHadShow;

	bool m_bBuDingCanPassEvenModeIsTheSame;

	bool m_bDeleteFileWorking;
	bool m_bFormatSDcardWorking;
	bool m_bTrafficSelectionWorking;
	bool m_bVersionWroking;
	
private:
	//info head node
	CDNVApp *m_pDNVApp;
	CDNVModule *m_pDNVModule;
	CDNVHal *m_pDNVHal;
	CDNVParam *m_pDNVParam;
};

