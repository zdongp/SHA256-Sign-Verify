/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once
#include "BtParam.h"
#include "BtBC6Adapter.h"
#include <commonFunc.h>


#define PBT_ADAPTER m_pBtHal->m_pBtAdapter

class CBtAdapter;
class CBtApp;
class CBtModule;
class CBtParam;
class CBtHal : public CFlyHal 
{
	SINGLETON_IMPLEMENT(CBtHal)
private:
	CBtHal(void);
public:
	virtual ~CBtHal(void);

public:
	//
	void init(void);
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);
	//
	void analyseHalMessage(halid_t halId, u8 cmd, u8 *p, u8 len);
	void analyseAgentMessage(moduleid_t id, u8 *p, u8 len);
	//1.14 HSP/HFP ÓŠŽð
       void getHfpPowerState(char state);
	void getHfpConnectStatus(E_HFP_CONNECT_STATUS e);
	void getHfpPhoneStatus(E_BT_PHONE_STATUS e);
	void getHfpDiallingFree_SyncCallLogs(E_BT_PHONE_STATUS e);
	void SyncPhoneBookSIM();
	void getHfpDialingTransferPosStatus(E_BT_PHONE_STATUS e);
	void getHfpPhoneNumCallInOrOut(E_BT_PHONE_STATUS e,char *pNo, int len);
	void getPhoneCallinOrCalloutPeopleName(char *pnum);
	void getHfpAudioSource(E_HFP_AUDIO_SOURCE e);
	void getHfpSpkAndMicVolume(int nSpkVolume, int nMicVolume);
	void getHfpMicStatus(bool state);
	//1.22 SDP À¶ÑÀËÑË÷ ÓŠŽð
	void getBtDeviceSearchStatus(E_BT_DEVICE_SEARCH_STATUS e);
	void getBtDeviceHasSearch(char *pAddr, int addrLen, char *pName, int nameLen);
	//1.16 µç»°±Ÿ/Íš»°ŒÇÂŒ ÓŠŽð
	void getPhoneBookSyncStatus(bool b);
	void getPhoneBookOneItem(char *pUserName, int userNameLen, char *pUserNo, int userNoLen);
	//void getHistoryCallOneItem(char *pUserName, int userNameLen, char *pUserNo, int userNoLen);
	void getHistoryCallOneItem(char type,char *pUserName, int userNameLen, char *pUserNo, int userNoLen,char *pUserTime,int userTimeLen);
	void getLoadPhoneBookFinishStatus(void);
	//1.23 ÆäËûÓŠŽð
	//ÀŽµç×Ô¶¯œÓÌý/ Ä£¿éÉÏµç×Ô¶¯ ÖØÁ¬ÉèÖÃ
	void getLocalBtDeviceAutoConnectState(char *p, int len);
	void getLocalBtDeviceVersion(char *p, int len);
	void getLocalBtDeviceName(char *p, int len);
	void getLocalBtDevicePinCode(char *p, int len);
	void getLocalBtDeviceAddr(char *p, int len);
	void getBtDeviceHasPaired(int index, char *pAddr, int addrLen, char *pName, int nameLen);
	void getBtPairStatus(bool b);
	void getLocalBtDeviceInitFinished(void);
	void getMobileSignalAndBattery(char *nSignal,char *nBattery);
	void getCurConnectedBtDeviceName(char *p, int len);
	void getCurConnectedBtDeviceAddr(char *p, int len);
	void BtDeviceNameOfThedeviceconnectedToTheinsidepagesAndtheRealPairIsNotTheSame();
	void getBtDeviceMicGain(char *param);

	//phonebook
	void InitContactsExtendedNameParamValue(void);
	void AnalyzeContactsExtendedName(char *strParam1_In);
	void ToUI_FormalityOfContacts(char *strParam1_out);
	void deleteSpecialCharacters(char *str,char ch);
	
	//³õÊŒ»¯µ×²ãÒÔŒ°·¢ËÍÀ¶ÑÀATÖžÁîÍšµÀ
	void setToHalInit(void);
	void setToHalBtPower(u8 p);
	void setToHalBtMsg(char *p, int len);
	//CBtParam  * getBtParam();
	void clearPhoneNumInput();
	void getPhoneNumCallIn(ST_PHONE_NUM *phoneNum);
	void clearPhoneBookAndHistoryCall();
	void clearAfterHandup();

	void getA2DPInfo(char *singName,int singNameLen,char* author,int authorLen,char* album,int singAlbumLen);
	void getSongTrackInfor(short TotalNumber,short curSongNumber);
	void getSongTotalTime(int p);
	void getSongPlayingTime(long int p);

	void getLocalBtDevice_SearchedDeviceCounts(char *p, int len);
	void getLocalBtDevice_SearchFinish();

	void setToHalMobileStatus( int callStatus );
	void getA2DPStatus(bool b);
	void clearHistoryAfterHFPDisconnect();
	void clearListHistoryCall();
	int SetTimer(int nElaspe_ms, int nMode, int timerId);
	void clearAfterHfpPowerOff();
	void setBC06TestAutoConnect(void);
	void setDefaultParamAfterHfpPowerOff();
	void initParamAfterHfpPowerOn();
	void refreshParamAfterHFPConnected();
	void setParamAfterHFPDisconnect();
	void PhonebookDownloadFinish(void);
	void getA2DPPlayOrStopStatus(char state);
	void GetA2DPPlayOrStopState_switch(char state);
	void FormatBtMacAddress(char *strData,int str_len);
	void ToUIBtDeviceAddr(u8 *p, int len);

	void bohong_test(int nCommand1,int nCommand2,int tag);
	bool bohong_test_HHHHH(int ctrlId,char ctrlType);
	void bohong_test_AVOL_Tx(int cotrl);

	void Message_GetDevice_OK();
	void Message_GetDevice_ERROR();

public://BC8
	void separateCmd_(char *p,int len);
	void IsCanSendRequestCmd(void);
	void Timer_At_CannotReceive(void);
	void ActBuffCommand(void);
	void getPairingModeInfors_Bi_directional(char *cP1,int nP1Len,char *cP2,int nP2Len);
	bool WhetherThereIsCurrentlyDuplicateDeviceSearchList(s8 *cAddr,s32 nAddrLen);	
	void getPhoneCallinOrCalloutPeopleName2(char *pnum);
	void getMultiCallState(E_CUR_MULTI_CALL_STATE em);
	void getCallName(char *input_Num,char *out_Name);
	void getHfpBC8Calling(char *input_Num,int len);
	void getHfpPhoneStatus_Multi_Call(E_BT_PHONE_STATUS e);
	void analyCallData(char *num,int nLen);
	void setSyncCallRecordTimer(void);
	
	void syncInitPhoneBook(void);
	void syncInitPhoneBookAllTime(void);
	void syncInitCallRecord(void);
	void syncInitCallRecordAllTime(void);
	bool searchNameAtPhoneBook(char *input_Num,char *out_Name);
	void getPhoneCallinOrCalloutPeopleName_Temp(char *input_Num);
public:
	void newGetHistoryCallOneItem(char type,char *pUserName, int userNameLen, char *pUserNo, int userNoLen,char *pUserTime,int userTimeLen);
	void getVoiceDialingStatus(u8 p);
	void supportVoiceStatus(u8 p);
	void callRecordDownloadFinish(void);
	bool judgmentPhoneCallCmd(char *p,int len);
	void setFm1388Switch(bool s);
	void getHfpPhoneNumCallTalking(char *pNo, int len);
private:
	//
	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;
	//
	CBtAdapter *m_pBtAdapter; 
	
};

