/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once

#include "FlyApp.h"
#include "FlyModule.h"
#include "FlyHal.h"
#include "FlyParam.h"

#include "BtDefine.h"
#include "BtApp.h"
#include "BtModule.h"
#include "BtHal.h"
#include "BtParam.h"

#include "BtBC6Adapter.h"
#include "PhoneBookPages.h"
#include <commonFunc.h>
#include "BtJniSdk.h"


#define MODULE_SDK_BT 				0x01
extern CBtJniSdk *g_pClsBtJniSdk;
extern CBtBC6Adapter *g_pClsBtBC6Adapter;

static bool BtCallin_SetAudio_TestSwitch = false;
static u32 nTemMicValue = -1;

	
class CBtApp;
class CBtModule;
class CBtHal;
class CBtParam : public CFlyParam
{
	SINGLETON_IMPLEMENT(CBtParam)
private:
	CBtParam(void);
public:
	 ~CBtParam(void);
	//
	void init(void);
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);
	//
	void setDefaultParam();
	//
	void readParameter(void);
	void saveParameter(void);

	void saveBtPinCode(void);
	void saveBtName(void);
public:
	u8 uModuleBt_is_T123;
	
	//normal
	bool m_bIsPowerOn;	//µçÔŽ
	bool m_bIsWorking;	//¿ªÊŒ¹€×÷
	bool m_bIsLocalBtDeviceInitOk;//À¶ÑÀ³õÊŒ»¯Íê³É
	
	E_BT_PHONE_STATUS m_ePhoneStatus;
	E_HFP_CONNECT_STATUS m_eHfpConnectStatus;
	E_HFP_AUDIO_SOURCE m_eHfpAudioSource;
	
	u8 bIsAutoConnect;
	
	int m_nSpkVolume;
	int m_nMicVolume;
	bool m_bIsMicOpen;
	int n_MicGain_Volue;

	char szPhoneNumCallInOrOut[PHONE_NUm_nNPUT_MAX_SIZE];
	ST_PHONE_NUM m_stPhoneNumInput;	//ÊäÈëµÄµç»°ºÅÂë
	ST_PHONE_NUM m_stPhoneNumCallIn; //ŽòœøµÄµç»°ºÅÂë

	//1.22 SDP
	E_BT_DEVICE_SEARCH_STATUS m_eBtDeviceSearchStatus;
	list<BluetoothDevice> m_listBtDevicesHaveSearched;	
	int  m_btDevicesHaveNum;
	int m_nBtDevicesHaveSearchedListBrowseFrom;
	int m_nBtDevicesHavePairedListBrowseFrom;

	//1.16 PhoneBook
	bool m_bRemodeMobilePhoneBookSyncOk;//µç»°±ŸÍ¬²œ×ŽÌ¬
	list<ST_PHONE_BOOK_ONE_USER_INFO> m_listPhoneBook;//µç»°ÌõÄ¿
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall;//ÍšÑ¶ŒÇÂŒÌõÄ¿
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall_Miss;
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall_Dialed;
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall_Riceived;
	list<ST_CALL_RECORD_ONE_USER_INFO> m_tempListHistoryCall;
	bool m_bIsPhoneBookLoadFinish;
	bool m_bIsCallLogLoadFinish;
	EM_SYNC_PHONEBOOK_PATH  m_iselectPhoneBook;
	//1.23 Local Device
	char szLocalBtDeviceVersion[FLY_BT_DEVICE_VERSION_MAX_LEN];//Ä£¿é°æ±ŸºÅ
	char szTemBtDeviceName[FLY_BT_DEVICE_NAME_MAX_LEN];//Ä£¿éÉè±žÃû
	char szLocalBtDeviceName_Default[FLY_BT_DEVICE_NAME_MAX_LEN];//Ä£¿éÉè±žÃû
	char szLocalBtDevice_Name[FLY_BT_DEVICE_NAME_MAX_LEN];
	char szTemBtDevicePinCode[FLY_BT_DEVICE_PINCODE_MAX_LEN];//Ä£¿é PIN Âë
	char szLocalBtDevicePinCode_Default[FLY_BT_DEVICE_PINCODE_MAX_LEN];//Ä£¿é PIN Âë
	char szLocalBtDevice_PinCode[FLY_BT_DEVICE_PINCODE_MAX_LEN];
	char szLocalBtDeviceAddr[FLY_BT_DEVICE_ADDRS_MAX_LEN];//Ä£¿éÉè±žµØÖ·
	
	//Paired and Connected
	list<BluetoothDevice> m_listBtDevicesHavePaired;//ÓëÄ£¿éÅä¶Ô¹ýµÄÀ¶ÑÀÉè±ž
	char szRemodeBtDeviceHasConnectedAddr[FLY_BT_DEVICE_CONNECTED_ADDRS_MAX_LEN];//µ±Ç°ÒÑÁ¬œÓÀ¶ÑÀÉè±žµØÖ·
	char szRemodeBtDeviceHasConnectedName[FLY_BT_DEVICE_CONNECTED_NAME_MAX_LEN];//µ±Ç°ÒÑÁ¬œÓÀ¶ÑÀÉè±žÃû×Ö
	int m_nMobileSignal;//ÊÖ»úÐÅºÅÇ¿¶È/
	int m_nMobileBattery;//µç³ØµçÁ¿
	
	//A2DP & AVRCP
	bool m_bSupport_A2DP;
	char musicName[256];
	char musicAuthor[256];
	char musicAlbum[256];
	short musicTotal;
	short musicCurSong;
	char m_strFirstCallNum[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strSecondCallNum[PHONE_NUm_nNPUT_MAX_SIZE];

	int m_nBtLanguageType;
	EM_NationalDistinction nNationalDistinction;
	char cStrBt_GetCountryName[128];

	char cStrCareLand_PTTNumber[64];
	int m_nBtConnectSign;
	char cStrCallPeopleName[128];

	PhoneBookItem_ExtendedInfo extended_Infor;
	E_KEY_BOARD_LANGUAGE m_ePhoneBookKeyBoardSearchLanguage;
	
	char cUpdataPhoneBookCountIndex;
	E_BT_PHONE_STATUS emPhoneStatusBallon;
	u8 m_bVoiceRecgStatus;
	u8 m_bVioceSupportStatus;

public://BC8
	//Cmd
	bool m_bCanSendData;
	file_phoneCmdGroup_t m_SendMessageBuf;
	char m_SendMessagesStr[FLY_BT_DEVICE_END_CMD_MAX_LEN];

	E_TIP_BOX_NAME m_eTipBoxName;
	BT_PairingInfors str_BtPairing;
	bool bIsStopPairing;

	//other
	bool m_bShowTipsDlg;
	s8 cSelectDeviceAddr[FLY_BT_PAIRING_ADDRS_MAX_LEN];
	bool bIsSelectPairing;
	
	char m_strTemCallingNum[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemInNum[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemInName[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemOutNum[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemOutName[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemWaitingNum[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemWaitingName[PHONE_NUm_nNPUT_MAX_SIZE];

	bool bSpecialHangUpIsStillOnHold;
	bool bSpecialCaseBackPage;

	E_HFP_CONNECT_STATUS emTempHfpConnectStatus;
	E_HFP_AUDIO_SOURCE emTempHfpTalkingTransferSet;
	E_BT_PHONE_STATUS emTempHfpPhoneStatus;
	bool bAfterDialingSyncCallLogs;
	bool bNoA2dpChannelPlay;
	
	//Multi-call
	E_CUR_MULTI_CALL_STATE em_MultiCallstate;
	int nCallCount;
	bool bItsAddCalls;
	BT_Call_Infor str_CallInfor[2];

	char tempMeetNum1[PHONE_NUm_nNPUT_MAX_SIZE];
	char tempMeetNum2[PHONE_NUm_nNPUT_MAX_SIZE];
	//PhoneBook
	list<ST_PHONE_BOOK_ONE_USER_INFO> m_listPhoneBook_BC8;//µç»°ÌõÄ¿
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall_BC8;//ÍšÑ¶ŒÇÂŒÌõÄ¿
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall_Miss_BC8;
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall_Dialed_BC8;
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall_Riceived_BC8;

	list<ST_CALL_RECORD_ONE_USER_INFO> m_listCallLog_All;
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listCallLog_Miss;
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listCallLog_Dialed;
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listCallLog_Riceived;

	bool tempAutoMatetsg;
	bool bIsPairBox;
                                                                                                                               
	bool m_bSetBookTimeSign;
	bool m_bSetRecordTimeSign;

	ST_CALL_RECORD_ONE_USER_INFO st_UserInforsOnetouchDial;
	u8 str_addrSpeedConnect[FLY_BT_PAIRING_ADDRS_MAX_LEN];
	bool bIsSpeedConnectState;

public:
	bool m_bIsA2dpOnPlayState; 
	bool m_bshowPhonePair_PromptBox;
	bool tempHideBtPage;

	int m_nDeleteOneBtDevice;
	u8 uSetConnectbtAddr[FLY_BT_DEVICE_ADDRS_MAX_LEN];

	bool m_bFirstStart;
	bool m_bAutoJump;
	int m_nPhonebookReturnSign;
	bool bA2DP_To_DevicePageBackButton;
	bool FirOrBackTag;
	bool bHangUpAutoDailin;
	bool bHandleStopSearchState;

private:
	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;
};


