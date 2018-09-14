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

	//������
	void setRadioPowerOn(int p);				//�������������ص�Դ
	void setRadioFrequencySection(int p);		//����������Ƶ��
	void setRadioFrequency(int p);				//����������Ƶ��
	void setRadioSensitivity(int p);				//����������������
	void setRadioPreFrequency(int p);			//������������һƵ��
	void setRadioNextFrequency(int p);			//������������һƵ��
	void setRadioStartScanFrequency(int p);		//��������ʼɨ��Ƶ��
	void setRadioStopScanFrequency(int p);		//������ֹͣɨ��Ƶ��
	void setRadioPreStation();				//������������һ��̨
	void setRadioNextStation();				//������������һ��̨
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





























