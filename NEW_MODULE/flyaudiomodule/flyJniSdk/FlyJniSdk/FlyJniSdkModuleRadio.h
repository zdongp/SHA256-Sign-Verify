#pragma once
#include "FlyJniSdkModule.h"


class CFlyJniSdkModuleRadio : public CFlyJniSdkModule
{
public:
	CFlyJniSdkModuleRadio(void);
	virtual ~CFlyJniSdkModuleRadio(void);

	void getRadioMessage(u8 *p, u8 len);
	void getAppCtrlMessage(u8 *p, u8 len);

	void onRadioPowerStatus(u8 nStatus);				//��������Դ״̬����
	void onRadioFrequencySection(u8 p);			//������Ƶ�μ���
	void onRadioFrequency(u8* p,u8 len);				//��������ǰƵ�ʼ���
	//������
	void setToRadioPowerOn(u8 nStatus);				//�������������ص�Դ
	void setToRadioFrequencyOfChannel(u8 *param);				//����������Ƶ��
	void setToRadioSensitivity(int p);				//����������������
	void setToRadioStartScanFrequency(u8 p);		//��������ʼɨ��Ƶ��
	void setToRadioStopScanFrequency(int p);		//������ֹͣɨ��Ƶ��
	void setToRadioPreStationScan(u8 nStatus);				//������������һ��̨
	void setToRadioNextStationScan(u8 nStatus);				//������������һ��̨
	void setToRadioPreFrequency(u8 nStatus);				//������������һƵ��
	void setToRadioNextFrequency(u8 nStatus);				//������������һƵ��
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
