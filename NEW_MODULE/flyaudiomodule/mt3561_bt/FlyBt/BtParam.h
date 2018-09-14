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
#include "PhoneBookPages.h"
//#include <cutils/properties.h>

#include "flyprop.h"
#include "BtAdapter.h"
#include "BtJniSdk.h"


extern CBtAdapter *g_pClsBtAdapter;
extern CBtJniSdk *g_pClsBtJniSdk;


extern int property_get(const char* property, char* value, const char* defaultValue);
extern int property_set(const char* property, const char* value);


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
	void saveLastConnectBtAddr(void);

public:
	bool m_bIsPowerOn;
	E_HFP_CONNECT_STATUS m_eHfpConnectStatus;
	/**********************************************************************/
	char szLocalBtDeviceAddr[FLY_BT_DEVICE_ADDRS_MAX_LEN];//模块设备地址
	
	/********************** 蓝牙搜索 应答**********************/
	E_BT_DEVICE_SEARCH_STATUS m_eBtDeviceSearchStatus;
	list<BluetoothDevice> m_listBtDevicesHaveSearched;	
	int  m_btDevicesHaveNum;
	bool bHandleStopSearchState;
	int m_nBtDevicesHavePairedListBrowseFrom;
	/**********************Paired and Connected**********************/
	list<BluetoothDevice> m_listBtDevicesHavePaired;
	BT_PairingInfors str_BtPairing;
	E_HFP_CONNECT_STATUS emTempHfpConnectStatus;
	char szRemodeBtDeviceHasConnectedAddr[FLY_BT_DEVICE_CONNECTED_ADDRS_MAX_LEN];//当前已连接蓝牙设备地址
	char szRemodeBtDeviceHasConnectedName[FLY_BT_DEVICE_CONNECTED_NAME_MAX_LEN];//当前已连接蓝牙设备名字

	int nPairRecordTotal;
	/************************device*********************************/
	int m_nMobileSignal;//手机信号强度/
	int m_nMobileBattery;//电池电量
	/*********************************************************/
	bool tempAutoMatetsg;
	bool bIsPairBox;
	bool m_bAutoJump;
	bool bSpecialCaseBackPage;
	/*************************call************************************/
	E_BT_PHONE_STATUS m_ePhoneStatus;
	E_HFP_TALKING_TRANSFER_SET emTempHfpTalkingTransferSet;
	E_BT_PHONE_STATUS emTempHfpPhoneStatus;
	ST_PHONE_NUM m_stPhoneNumInput;
	ST_PHONE_NUM m_stPhoneNumCallIn;
	E_BT_PHONE_STATUS emPhoneStatusBallon;
	char szPhoneNumCallInOrOut[PHONE_NUm_nNPUT_MAX_SIZE];
	bool bItsAddCalls;
	char m_strTemInNum[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemInName[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemOutNum[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemOutName[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemWaitingNum[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemWaitingName[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strTemCallingNum[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strFirstCallNum[PHONE_NUm_nNPUT_MAX_SIZE];
	char m_strSecondCallNum[PHONE_NUm_nNPUT_MAX_SIZE];
	bool m_bRemodeMobilePhoneBookSyncOk;//电话本同步状态
	list<ST_PHONE_BOOK_ONE_USER_INFO> m_listPhoneBook;//电话条目
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall;//通讯记录条目
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall_Miss;
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall_Dialed;
	list<ST_CALL_RECORD_ONE_USER_INFO> m_listHistoryCall_Riceived;
	list<ST_CALL_RECORD_ONE_USER_INFO> m_tempListHistoryCall;
	bool m_bIsPhoneBookLoadFinish;//电话本下载结束
	EM_SYNC_PHONEBOOK_PATH  m_iselectPhoneBook;
	EM_SelectedPhoneBookType m_emSelectedPhone;
	EM_NationalDistinction nNationalDistinction;
	PhoneBookItem_ExtendedInfo extended_Infor;
	//A2DP & AVRCP
	char musicName[256];
	char musicAuthor[256];
	char musicAlbum[256];
	char cStrCallPeopleName[128];
	bool m_bIsA2dpOnPlayState; 
	bool bNoA2dpChannelPlay;
	bool m_bSupport_A2DP;
	bool bA2DP_To_DevicePageBackButton;
	u8 curIsFolder;
	list<st_theBrows_Folders_Info> m_TheFolderlistSongBrowsing;
	list<Songs_TheSong_ExtendedInfo> m_theSongs;
//devise page 
	bool m_bShowTipsDlg;
	E_TIP_BOX_NAME m_eTipBoxName;
	int m_nDeleteOneBtDevice;
	int  m_nClickHasPairedDeviceIndex;
	char szTemBtDevicePinCode[FLY_BT_DEVICE_PINCODE_MAX_LEN];//模块 PIN 码
	char szLocalBtDevicePinCode_Default[FLY_BT_DEVICE_PINCODE_MAX_LEN];//模块 PIN 码
	char szLocalBtDevice_Name[FLY_BT_DEVICE_NAME_MAX_LEN];
	char szTemBtDeviceName[FLY_BT_DEVICE_NAME_MAX_LEN];//模块设备名
	char szLocalBtDeviceVersion[FLY_BT_DEVICE_VERSION_MAX_LEN];//模块版本号
	char szLocalBtDevice_PinCode[FLY_BT_DEVICE_PINCODE_MAX_LEN];
	int m_nBtDevicesHaveSearchedListBrowseFrom;
	u8 bIsAutoConnect;
	int n_MicGain_Volue;
	E_KEY_BOARD_LANGUAGE m_ePhoneBookKeyBoardSearchLanguage;
	bool bPairingStatus;
	//BTmainpage
	BT_Call_Infor str_CallInfor[2];
	int m_nBtLanguageType;
	char cUpdataPhoneBookCountIndex;
	bool m_bFirstStart;
	E_HFP_AUDIO_SOURCE m_eHfpAudioSource;
	u8 * btAddr1;
   	int btAddrLen1;
	bool bIsStopPairing;
	char cStrBt_GetCountryName[128];
	char szLocalBtDeviceName_Default[FLY_BT_DEVICE_NAME_MAX_LEN];//模块设备名
	char szRemodeBtDeviceLastConnectedAddr[FLY_BT_DEVICE_CONNECTED_ADDRS_MAX_LEN];//当前已连接蓝牙设备地址

	bool muteSwicthState;
	bool FirOrBackTag;
	bool bInitState;
	u8 selecteDeviceAddr[FLY_BT_PAIRING_ADDRS_MAX_LEN];
	int selecteDeviceAddrLen;
	bool tempHideBtPage;
	bool bStandBYPower = true;
private:
	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;
};


