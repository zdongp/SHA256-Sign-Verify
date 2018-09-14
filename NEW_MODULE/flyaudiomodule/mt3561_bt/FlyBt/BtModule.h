/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once
#include "BtParam.h"

class CBtApp;
class CBtHal;
class CBtParam;
class CBtModule : public CFlyModule
{
	SINGLETON_IMPLEMENT(CBtModule)
private:
	CBtModule(void);
public:
	virtual ~CBtModule(void);

	moduleid_t locale_module_mid(void);
public:
	//初始化
	void init(void);//类的初始化
	//系统通知
	void getAccOn(void);//收到 acc on 消息
	void getAccOff(void);//收到 acc off 消息
	void getSystemCodeStartInitModule(void);
	void getReset(void);//
	void getResetFactorySetting(void);

	void timerHandleProc(int timerId);
    void getMyModuleParam(char id, u8 *p, u8 *pLen);
//	
//	void getPageNoA2dpMsgFromAudioVideo();//
//
	void killAllTimer();


	void UpdateA2dpPlayStatus(A2DP_MUSIC_STATE musicState);

//	bool checkIfAbnormal();
	bool isPowerOn(void);
	bool isWorking(void);
	E_HFP_CONNECT_STATUS isConnected(void);
	bool isInBtPage(void);
	bool isBtDeviceSearchFinish(void);
	bool isBtModeInit();
	bool isSupportA2DP();

	E_BT_PHONE_STATUS getBtPhoneStatus(void);
	E_HFP_CONNECT_STATUS getBtConnectStatus(void);


	void setPhoneStatus(E_BT_PHONE_STATUS e);
	//辅助
	const char* getBtPhoneStatusString(E_BT_PHONE_STATUS e);
	const char* getBtConnectStatusString(E_HFP_CONNECT_STATUS e);
	
//	//逻辑处理类状态
	bool isCanCtrlMainPageFirstLayerWidget(void);
    void btToApp_SendConnectState(unsigned char state);

	int nativeTimerHandlerProcess(timer_t timerId);
	void getSystemMessage(u8 *p, u8 len);
	void getAudioVideoMessage(u8 *p, u8 len);
	void getKeyMessage(u8 *p, u8 len);
	void getCenterMessage(u8 *p, u8 len);
	void getAutoMateMessage(u8 *p, u8 len);
	void getGpsMessage(u8 *p, u8 len);
	void getExternalctrlMessage(u8 *p, u8 len);
	void getExtcarMessage(u8 *p, u8 len);

	void autoMateUIMessage(u8 *p, u8 len);
	void getSimPhoneStatus(u8 param);
	void getStandByStatus(u8 param,u8 uIsAccOff);
	void PanelKey_Switch_CallFunction();
	void SystemDecodingProblemToUiDisplay(char *param,u8 len);
	void GPS_aboutCareLand_PTT(u8 *param,int len);
	void btToCareLand_SendConnectState(unsigned char state);
	void SetAutoConnectDevice();
	void golf_dialNum(char *p, int len);
	void golf_baseCtrl(u8 *p, int len);
	void golf_getPhoneBook(u8 *p, int len);
	void ToOSDandAPPaboutConnectState(char cState);
	void btToModule_NotifyOSD_ShowTitle();
	void btToModule_NotifyOSD_ShowBTConnectState(unsigned char cState);

	void btToModule_NotifyAUXScreen_BT_PhoneState(unsigned char cState); //AUXScreen BT Phone State
	void btToModule_NotifyBackVideo_BT_PhoneState(u8 cState);
	void btToModule_NotifyAudiovideo_BT_PhoneState(u8 cState);
	void btToModule_NotifySystem_BT_PhoneState(u8 cState);
	void btToModule_NotifyBackVideo_BT_CallInfo(u8* pBuf, s32 nLen);
	void btToModule_NotifyCenter_StopRing();
	void btToModule_NotifyCenter_StartRing(unsigned char ringID);

	////////////////////////FlyJniSdk//////////////////////////////////////////
	void sendToFlyJniSdkPowerState(char cState);
	void sendToFlyJniSdkConnectState(char cState);
	void sendToFlyJniSdkRemoteDeviceName(char* btName , int len);
	void sendToFlyJniSdkPhoneStatus(char cState);
	void sendToFlyJniSdkBtMusicSong( char* song,int len);
	void sendToFlyJniSdkBtMusicSonger(char* songer, int len);
	void sendToFlyJniSdkBtMusicAlbum(char * album, int len);
	void sendToFlyJNiSdkBtMusicStatus(char cState);
	void sendToFlyJNiSdkBtSupportA2DP(char cState);
	void getFlyJniSdkMessage(u8 *p, u8 len);

	void getStandbyOn();
	void getStandbyOff();


	void golf_sendToCarScreen_mobileOperatorName(u8 *p, int nLen);
	void golf_sendToCarScreen_signalState(u8 p);
	void golf_sendToCarScreen_batteryStrength(u8 p);
	void golf_sendToCarScreen_PhoneConnState(u8 p);
	void golf_sendToCarScreen_PhoneState(u8 p);
	void golf_sendToCarScreen_PhoneNumInTheSpecialState(u8 p, u8 *pNum, int nLen);
	void golf_getPhoneBook_writeOneNum(ST_PHONE_NUM *pPhoneNum, u8 *szAns, int j, int &iAns);
	void golf_getPhoneBook_writeOneNumMsg(int nSetTotalCount,u8 *szAns, int j, int nInCount, int nOutCount, int nMissCount,int &iAns);
	
	void golf_getPhoneBook_writeOneNumMsgoo(int nTotalCount,u8 *szAns, int j, int nInCount, int nOutCount, int nMissCount ,int &iAns);
	int golf_getPhoneBook_writeRiceived(int nTotalCount,u8 *szAns, int j,int nInCount,int &iAns);
	int golf_getPhoneBook_writeDialed(int nTotalCount,u8 *szAns, int j, int nOutCount,int &iAns);
	int golf_getPhoneBook_writeMiss(int nTotalCount,u8 *szAns, int j,int nMissCount,int &iAns);

	void btToModule_golf_phoneName(u8 *p, int nLen);
	void btToModule_golf_mobileOperatorName(u8 *p, int nLen);
	void btToModule_golf_netInfo(u8 p0, u8 p1);
	void btToModule_golf_simCardState(u8 p);
	void btToModule_golf_signalState(u8 p);
	void btToModule_golf_batteryStrength(u8 p);
	void btToModule_golf_didntReceivePhoneNum(int n);
	void btToModule_golf_blueConnectState(u8 p0, u8 p1);
	void btToModule_golf_phoneState(u8 p0, u8 p1);
	void btToModule_golf_phoneNumInTheSpecialState(u8 *p0, int nLen0, u8 *p1, int nLen1);
	void btToModule_golf_phoneNumListOfDialOutAndDialIn(u8 *p, int nLen);
	void btToModule_golf_updatePhoneBook();
	void btToModule_golf_deletePhoneBook(u8 pageNum, u8 flag, u8 posFrom);
	void btToModule_NotifyAudiovideo_BT_MicSwitch(u8 cState);

	void getAudioChannelChange(u8 param);
	void getAudioMuteState(u8 param);

	void sendToAudiovideoBtA2dpAudioFocuse(char s);
	void btToModule_NotifyExternalctrl_VoiceSwitchCtrl(u8 p);
	void sendToFlyJNiSdkBtPhoneBook(u8 *date,int len);
	void analysSdkToBtMessage(u8 *p,u8 len);
	void sendToFlyJniSdkPhoneBookLoadStatus(u8 cState);
	void StandbyOff_Time();
	void setStandbyOff_Time();
	private:
		CBtApp    *m_pBtApp;
		CBtModule *m_pBtModule;
		CBtHal    *m_pBtHal;
		CBtParam  *m_pBtParam;

};
