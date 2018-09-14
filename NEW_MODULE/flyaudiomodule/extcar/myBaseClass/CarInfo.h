#ifndef __CAR_INFO_H__
#define __CAR_INFO_H__

#include "FlyObject.h"
#include "CarInfoDefine.h"

extern "C"
{
	#include "unicodestring.h"
};

class CFlyObject;
class CCarInfo : public CFlyObject
{
public:
	CCarInfo(void);
	virtual ~CCarInfo(void);

	void initCarParam(void);
	void initCarUI(void);
	virtual void initCarInfo(void);
	virtual void AccOffinitCarInfo(void);
	virtual void runCarInfo(void);

	virtual void analyseCarInfo(u8 *p, int len);
	virtual bool pages(u32 id, u8 ms, u8 *p, u8 len);
	
	virtual int updateCarDoor(int nFrom = 0);
	virtual int updateSafeBelt(int nFrom = 0);
	virtual int updateOilRemain(int nFrom = 0);
	virtual void updateOutDoorTemperature(void);
	virtual void updateMileageHaveRun(void);
	virtual void updateMileageCanRun(void);
	virtual void updateAverageOilConsume(void);
	virtual int updateHandLock(int nFrom = 0);
	virtual void updateRainWiper(void);
	virtual void updateEngineDoor(void);
	virtual void updateCarWindow(void);
	virtual void updateFootLock(void);
	virtual void updateCarGear(void);
	virtual void updateCarSpeed(void);
	virtual	void updateAverageOilConsumeHistory(void);
	virtual void updateAverageOilConsumeHistoryPerMinute(void);
	virtual void updateInstantOilConsumeCount(void);
	//ÌøÒ³ÌøÄ£¿é
	void setPage(u16 id);//Ìøµ½Ö¸¶¨Ò³
	void setPrePage(void);//ÌøÇ°Ò»Ò³
	void setNextModule(void);//Ìø×ªµ½ÏÂÒ»Ä£¿é£¨Ñ­»·Ä£¿éÁÐ±íÅäÖÃÎÄ¼þ£©


	virtual void setToHalAudioCtrl(u8 *p, int len);
	virtual void setToHalScreenCoordinates(u8 *p, int nLen);
	virtual void setToHalExitBackcar(u8 param);
public:
	//ï¿½ï¿½
	E_CAR_DOOR m_eCarDoorLF;//ï¿½ï¿½Ç°ï¿½ï¿½
	E_CAR_DOOR m_eCarDoorRF;//
	E_CAR_DOOR m_eCarDoorLR;//ï¿½ï¿½ï¿½ï¿½ï¿?
	E_CAR_DOOR m_eCarDoorRR;//
	E_CAR_DOOR m_eCarDoorEngine;//ï¿½ï¿½ï¿½ï¿½ï¿?
	E_CAR_DOOR m_eCarDoorBack;//ï¿½ï¿½ï¿½ï¿½
	E_CAR_WINDOW m_eCarWindowBack;
	//ï¿½ï¿½
	E_HAND_LOCK m_eHandLock;//ï¿½ï¿½É²
	E_SAFE_BELT m_eSafeBelt;//ï¿½ï¿½È«ï¿½ï¿½
	E_RAIN_WIPER m_eRainWiper;
	E_FOOT_LOCK m_eFootLock;
	//ï¿½ï¿½ï¿½ï¿½
	int m_nCarSpeed;
	//ï¿½ï¿½ï¿?
	int m_nMileageHaveRun;//ï¿½ï¿½ï¿½ï¿½ï¿?
	int m_nMileageCanRun;//Ê£ï¿½ï¿½ï¿½ï¿½ï¿?
	//ï¿½ï¿½
	int m_nAverageOilConsume;//Æ½ï¿½ï¿½ï¿½Íºï¿½
	int m_nOilRemain;
	int m_nOilConsumeUnit;//ï¿½ÍºÄµï¿½Î»
	//ï¿½Â¶ï¿½
	int m_nDegreeOutdoor;//ï¿½ï¿½ï¿½ï¿½ï¿½Â¶ï¿½
	//ï¿½ï¿½Î»
	int m_nCarGear;

	//ï¿½ï¿½ï¿½ï¿½
	bool m_bOilNeedToAlarm;
	bool m_bOilAlarmNeedToSend;
	bool m_bVoiceAlarmEnable;
	bool m_bVoiceAlarmFirstTimeAfterSystemStart;
	
};

#endif

