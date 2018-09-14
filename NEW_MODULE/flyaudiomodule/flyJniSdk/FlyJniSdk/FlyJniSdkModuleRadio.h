#pragma once
#include "FlyJniSdkModule.h"


class CFlyJniSdkModuleRadio : public CFlyJniSdkModule
{
public:
	CFlyJniSdkModuleRadio(void);
	virtual ~CFlyJniSdkModuleRadio(void);

	void getRadioMessage(u8 *p, u8 len);
	void getAppCtrlMessage(u8 *p, u8 len);

	void onRadioPowerStatus(u8 nStatus);				//收音机电源状态监听
	void onRadioFrequencySection(u8 p);			//收音机频段监听
	void onRadioFrequency(u8* p,u8 len);				//收音机当前频率监听
	//控制项
	void setToRadioPowerOn(u8 nStatus);				//调节收音机开关电源
	void setToRadioFrequencyOfChannel(u8 *param);				//调节收音机频率
	void setToRadioSensitivity(int p);				//调节收音机灵敏度
	void setToRadioStartScanFrequency(u8 p);		//收音机开始扫描频段
	void setToRadioStopScanFrequency(int p);		//收音机停止扫描频段
	void setToRadioPreStationScan(u8 nStatus);				//调节收音机上一电台
	void setToRadioNextStationScan(u8 nStatus);				//调节收音机下一电台
	void setToRadioPreFrequency(u8 nStatus);				//调节收音机上一频率
	void setToRadioNextFrequency(u8 nStatus);				//调节收音机下一频率
	void setToRadioChannel(u8 nStatus);	

	void analyseRadioAppMessageType(u8 *p, u8 len);
	void analyseRadioInfoReturnStatusMassage(u8 *buf ,u8 len);
	void analyseControlRadioOperationMassage(u8 *buf ,u8 len);
	void sendToRadioGetRadioInfo(u8 param);
	void sendToRadioSetONorOFF(u8 param);
	void sendToRadioSetFmOrAm(u8 param);
	void sendToRadioSetFmOrAmAndValue(u8 *param,int len);
	void sendToRadioSetRadioScan(u8 param);
;public:
	u8 g_mFreSection;

	
};
