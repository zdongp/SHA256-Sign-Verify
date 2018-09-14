#pragma once
#include "BtParam.h"
#include "BtAdapter.h"

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
	void separateCmd(u8 rescmd,char *p,int len);//nf
	void separateCmd_Generalcommands(char *p,int len);
	void separateCmd_BluetoothCommands(char *p,int len);
	void separateCmd_BluetoothPairingCommands(char *p,int len);
	void separateCmd_BluetoothConnectionCommands(char *p,int len);
	void separateCmd_BluetoothPhoneCommands(char *p,int len);
	void separateCmd_PlayerManagement(char *p,int len);
	void separateCmd_PhonebookManagementCommands(char *p,int len);
	/***********************************************/
	void setToHalBtPower(u8 p);
	void getHfpPowerState(char state);
	void new_initParamAfterHfpPowerOn();
	void getBtInfoAfterHfpPowerOn();
	void getLocalBtDeviceVersion(char *p, int len);
	void getLocalBtDeviceAddr(char *p, int len);
	void getLocalBtDeviceAddrFormated(char *p, int len);
	void WithoutColonBtMacAddress(char *strData,int str_len);
	void FormatBtMacAddress(char *strData,int str_len);
	void ToUIBtDeviceAddr(u8 *p, int len);
	void getLocalBtDeviceName(char *p, int len);
	void getBtDeviceSearchStatus(E_BT_DEVICE_SEARCH_STATUS e);
	void new_SearchedDeviceCounts(char *p, int len);
	void getBtDeviceHasSearch(char *pAddr, int addrLen, char *pName, int nameLen);
	bool WhetherThereIsCurrentlyDuplicateDeviceSearchList(s8 *cAddr,s32 nAddrLen);
	void new_getBtDeviceHasPaired(int index, char *pAddr, int addrLen, char *pName, int nameLen);
	void getPairingModeInfors_Bi_directional(char *cP1,int nP1Len,char *cP2,int nP2Len);
	void getHfpConnectStatus(E_HFP_CONNECT_STATUS e);
	void getCurConnectedBtDeviceAddr(char *p, int len);
	void new_getCurConnectDeviceName(char *addr);
	void getHfpPhoneStatus(E_BT_PHONE_STATUS e);
	void clearAfterHandup();
	void clearPhoneNumInput();
	void setToHalMobileStatus( int callStatus );
	void getHfpPhoneNumCallInOrOut(E_BT_PHONE_STATUS e,char *pNo, int len);
	void getPhoneCallinOrCalloutPeopleName(char *pnum);
	void getCallName(char *input_Num,char *out_Name);
	bool searchNameAtPhoneBook(char *input_Num,char *out_Name);
	void getHfpDialingTransferPosStatus(E_BT_PHONE_STATUS e);
	void getHfpAudioSource(E_HFP_AUDIO_SOURCE e);
	void getHfpMicStatus(bool state);
	void GetA2DPPlayOrStopState_switch(char state);
	void getA2DPPlayOrStopStatus(char state);
	void getA2DPInfo(char *singName,int singNameLen,char* author,int authorLen,char* album,int singAlbumLen);
	void new_getA2DPStatus(u8 b);
	void new_initParamAfterA2DPConnected();
	void new_getPhoneBookAndRecord(u8 b);
	void PhonebookDownloadFinish(void);
	void getLoadPhoneBookFinishStatus(void);
	void AnalyzeContactsExtendedName(char *strParam1_In);
	void InitContactsExtendedNameParamValue(void);
	void ToUI_FormalityOfContacts(char *strParam1_out);
	void getPhoneBookOneItem(char *pUserName, int userNameLen, char *pUserNo, int userNoLen);
	void clearAfterHfpPowerOff();
	void setDefaultParamAfterHfpPowerOff();
	void initParamAfterHfpPowerOn();
	void refreshParamAfterHFPConnected();
	void clearHistoryAfterHFPDisconnect();
	void setParamAfterHFPDisconnect();
	void getCurConnectedBtDeviceName(char *p, int len);
	void clearPhoneBookAndHistoryCall();
	void setToHalBtMsg(char *p, int len);
	void deleteSpecialCharacters(char *str,char ch);
	void setToHalInit(void);
	void new_initParamAfterHFPConnected();
	void  new_getpairDeviceRecord(u8 *p,int len);
	void new_getPhoneBookLoadState(char p,char tag);
	void new_CreatePhoneBookList(char *p,int len);
	void new_CreateCallRecordList(char *p,int len);
	void new_getLocalBtDevicePinCode(char *p, int len);
	void getBtDeleteStatus(char *p,int len);
	void analyticalSongsDatas(char *p,int len);

	void GetA2dpAudioFucseState(u8 s);

	void GetHistoryCallOneItem(char type,char *pUserName, int userNameLen, char *pUserNo, int userNoLen,char *pUserTime,int userTimeLen);
	void setToHalBtPowerStatus(u8 p);
	void saveCurConnectedBtDeviceAddr(char *p, int len);
	void analyseSongInfo(char *p,int len);

	void getCurPhoneStatusForHal(char *p,int len);
	void delayConnectionDevicePage(void);
private:
	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;
	CBtAdapter *m_pBtAdapter; 
	
};

