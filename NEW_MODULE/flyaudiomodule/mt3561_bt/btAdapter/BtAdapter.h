#pragma once
#include "FlyObject.h"
#include "BtDefine.h"

class CBtApp;
class CBtHal;
class CBtParam;
class CBtModule;
class CBtAdapter
{
	SINGLETON_IMPLEMENT(CBtAdapter)
private:
	CBtAdapter(void);
public:
	virtual ~CBtAdapter(void);

public: 
	void init(CBtHal *p1,CBtApp *p2,CBtParam *p3,CBtModule *p4);
	//0x01
	void btInitCommand();
	void requestBtversion();
	void requestBtTurnONorOFF(u8 p);

	//0x02
	void requestBtCanbeDetected();
	void requestBtAddr();
	void requestBtName();
	void setBtAutomateConnect(u8 p);
	void requestBtSearchDevice(u8 p);
	void requestBtAutoConnectStatus();
	void setBtCanbeDetected(u8 p);
	void setDeviceBtName(u8 *buf,u8 len);
	void setBtPincode(u8 *p,int len);

	//0x03
	void requestBtPairRecord();
	void requestBtPairDevice(u8 *p,int len);
	void setBtPairConfirm(u8 p);
	void setBtPairMode(u8 p);
	void deleteAllPairRecord();
	void deleteAPairRecord(u8 *p,int len);
	void setBtCancelPair(u8 *p,int len);
	
	//0x04
	void btInitiativeConnectDevice(u8 *p,int len);
	void btInitiativeDisconnection(u8 *p,int len);

	//0x05
	void btCallOperation_HandUp(void);
	void btCallOperation_Answer(void);
	void btCallOperation_CallOut(u8 *p,int len);
	void btCallOperation_Save(void);
	void btCallOperation_Redial(void);
	void btHfpCmdSendDtmf(u8 p);
	void btAnswerformCarOrPhone(u8 p);
	void setBtMicMute(u8 p);
	void setBtVolume(u8 p);
	void setBtMicVolume(u8 p);
	//0x06
	void btAvrcpControl(u8 p);
	void btCyclePlayControl(u8 p);
	void btRandomPlay(u8 p);
	void requestBtMusicInfo();
	void requestBtPlayStatus();
	void requestBtPlayModeStatus();
	void A2dpAudioOutputCtrlSwitch(u8 p);

	//0x07
	void requestBtPhoneBook(u8 p);
	void debugPrintf(u8 *buf,int len);
	int findCharIndex(unsigned char *p, int len, unsigned char d);
	int Inside_FindIndexFromStr(const u8 *pSrc, int nSrcLen, u8 cLetter, int nStart);

private:
	CBtHal *m_pBtHal;
	CBtApp *m_pBtApp;
	CBtParam *m_pBtParam;
	CBtModule*m_pBtModule;
};

