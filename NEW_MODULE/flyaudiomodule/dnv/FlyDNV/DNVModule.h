/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once
#include "DNVParam.h"

class CDNVApp;
class CDNVHal;
class CDNVParam;
class CDNVModule : public CFlyModule
{
	SINGLETON_IMPLEMENT(CDNVModule)
private:
	CDNVModule(void);
public:
	virtual ~CDNVModule(void);

	moduleid_t locale_module_mid(void);
public:
	//初始化
	void init(void);//类的初始化
	//系统通知
	void getAccOn(void);//收到 acc on 消息
	void getAccOff(void);//收到 acc off 消息
	//
	void timerHandleProc(int timerId);
	int nativeTimerHandlerProcess(timer_t timerId);
	void getMyModuleParam(char id, u8 *p, u8 *pLen);
	void getSystemMessage(u8 *p, u8 len);
	void getAudioVideoMessage(u8 *p, u8 len);
	void getDvrMessage(u8 *p, u8 len);
	void getKeyMessage(u8 *p, u8 len);
	//->add your code here////////////////////////////////////////////////////
	//from system
	void getSystemBackKey(void);
	void pageChange(u16 fromPageId, u16 toPageId);
	//from audio video
	//work
	//assist
	bool isDNVpage(u16 pageId);
	bool isDNVOSDMenuPage(u16 pageId);
	bool isOtherDvrOsdMenuPage(u16 pageId);
	void setTimerSyncTimeToDNV(void);
	void killTimerSyncTimeToDNV(void);
	void setTimerHideOSDmenu(void);
	void killTimerHideOSDmenu(void);
	void setTimerHideOtherDvrOSDmenu(void);
	void killTimerHideOtherDvrOSDmenu(void);
	void setTimerAudioWarning(int time);
	void killTimerAudioWarning(void);
	void setTimerPingDNV(void);
	void killTimerPingDNV(void);
	void setTimerHideBlackPage(int defaultTime = TIMER_CYCLE_HIDE_BLACK_PAGE);
	void killTimerHideBlackPage(void);
	void setTimerEnableClick(int t);
	void killTimerEnableClick(void);
	void setTimerGoToPlayBack(void);
	void setTimerGoToView(void);
	void setTimerOpenLcd(int defaultTime = LCD_OPEN_DEFAULT_TIME);
	void setTimerOpenCanShowPlayPause(void);
	void setTImerResetMenuClickBuDing(void);
	void syncTimeToDNV(void);
	const char * getSystemStatus(E_DNV_SYSTEM_STATUS e);
	void updateDNVSupportStatus(void);

	//set to module
	void setToCenterPlayAudio(u8 id);
	//<-add your code here////////////////////////////////////////////////////

public:
	bool m_bSurportDNV;
	bool m_bInDNV;
	bool m_bSystemStartNeedSyncTimeToDNV;
	u32 m_nCurClickBtn;
	map<int, bool> m_mapCtrlIdHaveDown;

	//buding
	bool m_bCanShowPlayPause;
private:
	CDNVApp    *m_pDNVApp;
	CDNVModule *m_pDNVModule;
	CDNVHal    *m_pDNVHal;
	CDNVParam  *m_pDNVParam;
};
