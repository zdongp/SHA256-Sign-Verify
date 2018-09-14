/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once
#include "FatParam.h"

class CFatApp;
class CFatHal;
class CFatParam;
class CFatModule : public CFlyModule
{
	SINGLETON_IMPLEMENT(CFatModule)
private:
	CFatModule(void);
public:
	virtual ~CFatModule(void);

	moduleid_t locale_module_mid(void);
public:
	//��ʼ��
	void init(void);//��ĳ�ʼ��
	//ϵͳ֪ͨ
	void getAccOn(void);//�յ� acc on ��Ϣ
	void getAccOff(void);//�յ� acc off ��Ϣ

	void getMyModuleParam(char id, u8 *p, u8 *pLen);
//System
	void NotifySystemJumpPage(u16 usPageID);
//Key
	void SendKeyValueToOtherModule(u8 ucKeyValue, u8 ucToModule);
//BT
	void NotifyBlueToothIntoAutomateMode_PairingPincodeToDefault();
	void NotifyBlueToothDiscoverable(u8 ucEnable);
	void NotifyBlueToothSendBtPower(u8 p);
	void NotifyBlueToothSendBt_CallingOrHandupr(u8 p);
	void NotifyBlueToothSendBt_AudioTransfer(u8 p);
	void NotifyBlueToothSendBt_CallLogsAllClear(u8 p);
	
	void getDvrMessage(u8 *p, u8 len);
	void getRadioMessage(u8 *p, u8 len);
//MP3
	void NotifyMP3_SelectMusicPlay(u8 data);
	void NotifyMP3_GoToAutoMate();

//DETECION USB
	void NotifyMP3_DetectionUSB();
	void NotifyMP3_UsbStateInit();
	void NotifyBlueToothDiscoverablePairing( u8 p );
	
private:
	CFatApp    *m_pFatApp;
	CFatModule *m_pFatModule;
	CFatHal    *m_pFatHal;
	CFatParam  *m_pFatParam;
};
