#pragma once
#include "FlyObject.h"
#include "BtDefine.h"

class CBtApp;
class CBtHal;
class CBtParam;
class CBtModule;
class CBtJniSdk
{
	SINGLETON_IMPLEMENT(CBtJniSdk)
private:
	CBtJniSdk(void);
public:
	virtual ~CBtJniSdk(void);
public:	//Message sending flag
	bool btSwitchStatusTag = false;
	bool btConnectStatusTag = false;
	bool btPhoneStatusTag = false;
	bool SendBookTag = false;
public: 
	void init(CBtHal *p1,CBtApp *p2,CBtParam *p3,CBtModule *p4);
	void getSdkToModuleMessage(u8 *p,int len);
	void analysSdkToBtStatusMessage(u8 *p,u8 len);
	void analysSdkToBtContrlMessage(u8 *p,u8 len);
	void sendToFlyJniSdkService(u8 moduleId, u8 *p, u8 len);
	void analyseSdkToBtSetSongPlay(u8 param);
	 /***************************************************/
	void sendToAppBtSwitchStatus(u8 p);
	void sendToAppBtConnectStatus(u8 p);
	void sendToAppBtPhoneStatus(u8 p);
	 void sendToAppBtPhoneStatusAndNum(u8 p,char *num,u8 nuLen,char *name ,u8 naLen);
	void sendToAppPhoneBookInfo();
	void sendToAppBtPhoneBook(u8 *date,int len);
	void sendToAppPhoneBookLoadStatus(u8 cState);
	void sendToAppBtSongInfo(char *song,char *auther,char *album,u8 songLen,u8 autherLen,u8 albumLen);
	 void sendToAppConnectBtName(char *name,int len);
	void sendToAppMusicPlayStatus(bool cState);
	void sendToAppReceiveSound(u8 param);
	void sendToAppMicStatus(u8 param);
private:
	CBtHal *m_pBtHal;
	CBtApp *m_pBtApp;
	CBtParam *m_pBtParam;
	CBtModule*m_pBtModule;
};

