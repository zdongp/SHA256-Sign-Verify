/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#ifndef __FLY_PARAM_H__
#define __FLY_PARAM_H__

#include "FlyObject.h"

#include "FlyApp.h"
#include "FlyModule.h"
#include "FlyHal.h"
#include "FlyParam.h"

class CFlyParam : public CFlyObject
{
public:
	CFlyParam(void);
	 ~CFlyParam(void);
public:
	virtual void init(void) = 0;
	virtual void deInit(void);
	virtual void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam) = 0;
	virtual void readParameter(void);
	virtual void saveParameter(void);
	//��Ƶ��ʾ����
	void initFatherParam(void);
	//����
	void readVideoDisplaySettings(void);
	void saveVideoDisplaySettings(void);
	//����
	char __intToChar(int value);
	char __charToInt(u8 c);
	int bufferToString(char *p, int len, char *str);
	int stringToBuffer(char *str, char *p);

	
public:
	//��ʱ��ID
	int  m_nTimerIdGoBackVideoPage;
	//��Ƶ��ʾ����
	int m_nGlobalBrightnessLevel;//��Ļ����
	int m_nGlobalContrastLevel;//�Աȶ�
	int m_nGlobalBackLightLevel;//��������
	int m_nGlobalHueLevel;//ɫ��
	int m_nGlobalSaturationLevel;//���Ͷ�
public:
	//������
	CFlyApp *m_pFlyApp;
	CFlyModule *m_pFlyModule;
	CFlyHal *m_pFlyHal;
	CFlyParam *m_pFlyParam;
};

#endif