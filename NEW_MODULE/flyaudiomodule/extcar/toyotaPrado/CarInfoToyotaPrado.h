#pragma once
#include "CarInfo.h"
#include "toyotaPrado/CarInfoToyotaPradoDefine.h"

class CCarInfoToyotaPrado : public CCarInfo
{
public:
	CCarInfoToyotaPrado(void);
	virtual ~CCarInfoToyotaPrado(void);

public:
	//
	void initCarParamToyotaPrado(void);
	void initCarUIToyotaPrado(void);
	virtual void initCarInfo(void);
	virtual void AccOffinitCarInfo(void);
	virtual void runCarInfo(void);
	//
	virtual void analyseCarInfo(u8 *p, int len);
	virtual void updateCarGear(void);
	virtual	void updateAverageOilConsumeHistory(void);
	virtual void updateAverageOilConsumeHistoryPerMinute(void);
	virtual void updateInstantOilConsumeCount(void);
			void updateRadarSetting(void);
	//page
	virtual bool pages(u32 id, u8 ms, u8 *p, u8 len);
	bool mainPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool drivingInfoPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool parkCarSettingPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	//
	void clickMainPageDrivingInfoPageEntrance(E_MOUSE_STATUS e);
	void clickMainPageParkCarSettingPageEntrance(E_MOUSE_STATUS e);
	//
	void clickDrivingInfoPageGoBack(E_MOUSE_STATUS e);
	void clickDrivingInfoPageErase(E_MOUSE_STATUS e);
	//
	void clickParkCarSettingPageGoBack(E_MOUSE_STATUS e);
	void clickParkCarSettingPageDisplaySwitchOpen(E_MOUSE_STATUS e);
	void clickParkCarSettingPageDisplaySwitchClose(E_MOUSE_STATUS e);
	void clickParkCarSettingPageFrontSonarClose(E_MOUSE_STATUS e);
	void clickParkCarSettingPageDisplaySwitchCloseAndOpen(E_MOUSE_STATUS e,u8 p);
	void clickParkCarSettingPageFrontSonarFar(E_MOUSE_STATUS e);
	void clickParkCarSettingPageRearSonarClose(E_MOUSE_STATUS e);
	void clickParkCarSettingPageRearSonarFar(E_MOUSE_STATUS e);
	void clickParkCarSettingPageAlarmVolumeUp(E_MOUSE_STATUS e);
	void clickParkCarSettingPageAlarmVolumeDown(E_MOUSE_STATUS e);
	//
	const char* getCarGearString(int id);
	const char* getOilConsumeUnitString(int id);
	void setAverageOilconsumeUpdateTimer(void);
	void killAverageOilconsumeUpdateTimer(void);
	void setInstantOilconsumeCountTimer(void);
	void killInstantOilconsumeCountTimer(void);
	int radar_signal_LPC2JNI(int s, int r);
	//
	void setToHalAlarmVolume(u8 p);
	void setToHalDisplaySwitch(u8 p);
	void setToHalFrontSonarDistance(u8 p);
	void setToHalRearSonarDistance(u8 p);
	void setToHalScreenCoordinates(u8 *p, int nLen);
	void setToHalExitBackcar(u8 param);
	void DisplaySwitchCloseAndOpenButton(u8 param);
	//
	virtual void setToHalAudioCtrl(u8 *p, int len);
public:
	//ï¿½×´ï¿½ï¿½ï¿½ï¿½
	int m_nRadarAlarmVolume;
	int m_nRadarAlarmLevel;
	int m_nFrontSonarFarther;
	int m_nRearSonarFarther;
	int m_nRadarSwitch;
	
	int m_nszAverageOilConsumeHistory[AVERAGE_OIL_CONSUME_HISTORY_ITEM_NUM];

	//ÓÍ
	int m_nInstantOilConsume;//Æ½¾ùÓÍºÄ
	int m_nOilConsumeUnitHistory;//ÓÍºÄµ¥Î»
	
	//assist
	int m_nInstantOilConsumeCount;
	int m_nInstantOilConsumeSum; // Ò»·ÖÖÓÖÜÆÚ»ýÀÛ

};
