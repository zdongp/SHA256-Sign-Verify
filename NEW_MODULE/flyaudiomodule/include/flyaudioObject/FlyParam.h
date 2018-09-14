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
	//视频显示设置
	void initFatherParam(void);
	//保存
	void readVideoDisplaySettings(void);
	void saveVideoDisplaySettings(void);
	//辅助
	char __intToChar(int value);
	char __charToInt(u8 c);
	int bufferToString(char *p, int len, char *str);
	int stringToBuffer(char *str, char *p);

	
public:
	//定时器ID
	int  m_nTimerIdGoBackVideoPage;
	//视频显示参数
	int m_nGlobalBrightnessLevel;//屏幕亮度
	int m_nGlobalContrastLevel;//对比度
	int m_nGlobalBackLightLevel;//背光亮度
	int m_nGlobalHueLevel;//色彩
	int m_nGlobalSaturationLevel;//饱和度
public:
	//类桥梁
	CFlyApp *m_pFlyApp;
	CFlyModule *m_pFlyModule;
	CFlyHal *m_pFlyHal;
	CFlyParam *m_pFlyParam;
};

#endif