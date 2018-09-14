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
    void btToApp_SendConnectState(u8 state);

	int nativeTimerHandlerProcess(timer_t timerId);
	void getSystemMessage(u8 *p, u8 len);
	void getAudioVideoMessage(u8 *p, u8 len);
	void getKeyMessage(u8 *p, u8 len);
	void getCenterMessage(u8 *p, u8 len);
	void getAutoMateMessage(u8 *p, u8 len);
	void getGpsMessage(u8 *p, u8 len);
	void getExternalctrlMessage(u8 *p, u8 len);
	void getExtcarMessage(u8 *p, u8 len);
	void getAuxScreenMessage(u8 *p, u8 len);
	void getFlyJniSdkMessage(u8 *p, u8 len);
	
	void autoMateUIMessage(u8 *p, u8 len);
	void getSimPhoneStatus(u8 param);
	void getStandByStatus(u8 param,u8 uIsAccOff);
	void PanelKey_Switch_CallFunction();
	void SystemDecodingProblemToUiDisplay(char *param,u8 len);
	void GPS_aboutCareLand_PTT(u8 *param,int len);
	void btToCareLand_SendConnectState(u8 state);
	void SetAutoConnectDevice();
	void golf_dialNum(char *p, int len);
	void golf_baseCtrl(u8 *p, int len);
	void golf_getPhoneBook(u8 *p, int len);
	void ToOSDandAPPaboutConnectState(char cState);
	void btToModule_NotifyOSD_ShowTitle();
	void btToModule_NotifyOSD_ShowBTConnectState(u8 cState);
	void btToModule_NotifyAUXScreen_BT_PhoneState(u8 cState); //AUXScreen BT Phone State
	void btToModule_NotifyBackVideo_BT_PhoneState(u8 cState);
	void btToModule_NotifyAudiovideo_BT_PhoneState(u8 cState);
	void btToModule_NotifySystem_BT_PhoneState(u8 cState);
	void btToModule_NotifyBackVideo_BT_CallInfo(u8* pBuf, s32 nLen);
	void btToModule_NotifyCenter_StopRing();
	void btToModule_NotifyCenter_StartRing(u8 ringID);

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
	void sendToFlyJNiSdkBtPhoneBook(u8 *date,int len);

	void sendToFlyJNiSdkBtMac(u8 *p,u32 len);
	void sendToFlyJNiSdkBtName(u8 *p,u32 len);
	void sendToFlyJNiSdkConnectedBtMac(u8 *p,u32 len);
	void sendToFlyJNiSdkConnectedBtName(u8 *p,u32 len);
	
	void getStandbyOn();
	void getStandbyOff();

	void getStandByStatusFromLpcSpeedMsg(u8 p);
	void btToModule_NotifyExternalctrl_VoiceSwitchCtrl(u8 p);
	void HoldingTimes_1(u8 s);
	void HoldingTimes_2(u8 s);
	void PhoneControl(u8 p);
	void RequestSyncCallLogs(u8 type,u8 param);
	void RequestOperatingDialing(u8 type,u8 param);
	void CallLog_All(int nCount);
	void CallLog_Riceived(int nCount);
	void CallLog_Dialed(int nCount);
	void CallLog_Miss(int nCount);
	void SyncCallLogData(u8 unit,u8 Totalcount,u8 index,u8 callType,u8 phoneType,u8 *str,u8 strLen);
	void CallLog_All_Dialing(u8 index);
	void CallLog_Riceived_Dialing(u8 index);
	void CallLog_Dialed_Dialing(u8 index);
	void CallLog_Miss_Dialing(u8 index);

public:
	//********************** To Auxscreen**********************//
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

	void btToOtherModule_Auxscreen_Phone_Number(u8 *p, int nLen);
	void btToOtherModule_Auxscreen_Phone_Name(u8 *p, int nLen);
	void btToOtherModule_Auxscreen_Phone_status(u8 cState);
	void btToOtherModule_Auxscreen_Phone_Time(u16 p);
	void btToOtherModule_Auxscreen_CallLogList(u8 *p, int nLen);
	void btToOtherModule_Auxscreen_A2DP_Infors(u8 *p, int nLen);
	void btToOtherModule_Auxscreen_A2DP_Cur_TrackAndTotalTrack(u8 *p, int nLen);
	void btToOtherModule_Auxscreen_A2DP_Cur_TrackPlayTime(u8 *p, int nLen);
	void btToOtherModule_Auxscreen_A2DP_Cur_PlayStatus(u8 p);
	void btToOtherModule_Auxscreen_A2DP_Cur_TrackPlayTotalTime(u8 *p, int nLen);
	void btToOtherModule_Auxscreen_A2DP_Cur_TrackPlayTitle(u8 *p, int nLen);
	void btToOtherModule_Auxscreen_A2DP_Cur_TrackPlayArtist(u8 *p, int nLen);
	void btToOtherModule_Auxscreen_A2DP_Cur_TrackPlayAlbum(u8 *p, int nLen);
	void btToOtherModule_Auxscreen_A2DP_Cur_TrackFolderName(u8 *p, int nLen);
	void btToOtherModule_Auxscreen_A2DP_Cur_Connect_Bt_Name(u8 *p, int nLen);
	void btClearAuxscreenA2DPInfors();
	void btToAuxscreenAccOnSyncA2DPInfo();
	//*********************************************************//

private:
		CBtApp    *m_pBtApp;
		CBtModule *m_pBtModule;
		CBtHal    *m_pBtHal;
		CBtParam  *m_pBtParam;

};
