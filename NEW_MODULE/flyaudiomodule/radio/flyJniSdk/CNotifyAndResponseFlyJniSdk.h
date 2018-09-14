#pragma once 

#include "global.h"

#define MESSAGETYPE_STATUS			0x00
#define MESSAGETYPE_CONTROL		0x01


class CNotifyAndResponseFlyJniSdk

{
public:

	CNotifyAndResponseFlyJniSdk(void);

public:

	virtual ~CNotifyAndResponseFlyJniSdk(void);

public:
	void getFlyJniSdkMessage(u8* p, u8 len);

	
	// notify item
	
	void sendToSdkFreNum(u16 freNum); 
	void sendToSdkFreSection(u8 nChannel);
	void sendToSdkRadioPowerStatus(u8 nState);
	void analyseFormSdkMessageRadio(u8 *param, int len);

/*

	//控制项
	void setRadioPowerOn(int p);				//调节收音机开关电源
	void setRadioFrequencySection(int p);		//调节收音机频段
	void setRadioFrequency(int p);				//调节收音机频率
	void setRadioSensitivity(int p);				//调节收音机灵敏度
	void setRadioPreFrequency(int p);			//调节收音机上一频率
	void setRadioNextFrequency(int p);			//调节收音机下一频率
	void setRadioStartScanFrequency(int p);		//收音机开始扫描频段
	void setRadioStopScanFrequency(int p);		//收音机停止扫描频段
	void setRadioPreStation();				//调节收音机上一电台
	void setRadioNextStation();				//调节收音机下一电台
*/

void analyseSdkRequitRadioInfo(u8 param);
void sendToAppRadioSatusInfo(u8 *buf,int len);
void sendToApp_RadioSwitch(u8 param);
void sendToApp_RadioChanelAndFre(u8 param,u16 fre);
void sdkGetCurRadioChanelAndfre();
void analyseSdkRequitSetRadioScan(u8 param);
void sendToApp_RadioScanChanelAndFre(u8 param,u16 fre);
void sendToSdkRadioScanChanelAndfre(u16 param);
void sendToApp_RadioScanStatus(u8 param);

public:
	void sdkToRadioSetChannelAndFre(u8 *param ,int len);
	void analyseSdkToRadioPlayCtrlMessage(u8 *param,int len);






};





























