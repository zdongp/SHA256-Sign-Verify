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
	//��ҳ��ģ��
	void setPage(u16 id);//����ָ��ҳ
	void setPrePage(void);//��ǰһҳ
	void setNextModule(void);//��ת����һģ�飨ѭ��ģ���б������ļ���


	virtual void setToHalAudioCtrl(u8 *p, int len);
	virtual void setToHalScreenCoordinates(u8 *p, int nLen);
	virtual void setToHalExitBackcar(u8 param);
public:
	//��
	E_CAR_DOOR m_eCarDoorLF;//��ǰ��
	E_CAR_DOOR m_eCarDoorRF;//
	E_CAR_DOOR m_eCarDoorLR;//�����?
	E_CAR_DOOR m_eCarDoorRR;//
	E_CAR_DOOR m_eCarDoorEngine;//�����?
	E_CAR_DOOR m_eCarDoorBack;//����
	E_CAR_WINDOW m_eCarWindowBack;
	//��
	E_HAND_LOCK m_eHandLock;//��ɲ
	E_SAFE_BELT m_eSafeBelt;//��ȫ��
	E_RAIN_WIPER m_eRainWiper;
	E_FOOT_LOCK m_eFootLock;
	//����
	int m_nCarSpeed;
	//���?
	int m_nMileageHaveRun;//�����?
	int m_nMileageCanRun;//ʣ�����?
	//��
	int m_nAverageOilConsume;//ƽ���ͺ�
	int m_nOilRemain;
	int m_nOilConsumeUnit;//�ͺĵ�λ
	//�¶�
	int m_nDegreeOutdoor;//�����¶�
	//��λ
	int m_nCarGear;

	//����
	bool m_bOilNeedToAlarm;
	bool m_bOilAlarmNeedToSend;
	bool m_bVoiceAlarmEnable;
	bool m_bVoiceAlarmFirstTimeAfterSystemStart;
	
};

#endif

