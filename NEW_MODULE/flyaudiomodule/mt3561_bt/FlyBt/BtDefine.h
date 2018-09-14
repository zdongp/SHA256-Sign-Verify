#pragma once

#define KEYWORD_MODE_OPEN_LOGCAT "#*#*15935788*#*#"
#define KEYWORD_MODE_CLOSE_LOGCAT "#*#*00000000*#*#"
#define DBG_ALL_MODULE_COUNT 31
const char* const g_dbgAllModuleProperty[DBG_ALL_MODULE_COUNT] ={
"fly.debugSet.ac",
"fly.debugSet.audiovideo",
"fly.debugSet.auxinput",
"fly.debugSet.auxscreen",
"fly.debugSet.backcar",
"fly.debugSet.blcd",
"fly.debugSet.bt",
"fly.debugSet.center",
"fly.debugSet.dvr",
"fly.debugSet.dnv",
"fly.debugSet.flyJniSdk",
"fly.debugSet.dvd",
"fly.debugSet.extcar",
"fly.debugSet.gps",
"fly.debugSet.ipod",
"fly.debugSet.key",
"fly.debugSet.media",
"fly.debugSet.osd",
"fly.debugSet.radio",
"fly.debugSet.service",
"fly.debugSet.system",
"fly.debugSet.timer",
"fly.debugSet.tpms",
"fly.debugSet.tv",
"fly.debugSet.sync",
"fly.debugSet.externalCtrl",
"fly.debugSet.automate",
"fly.debugSet.flyRemoteOnline",
"fly.debugSet.NativeServer",
"fly.debugSet.mt3561_bt"
"fly.debugSet.extcar_honda_tsu"};


#define FLY_BT_PINCODE_DEFAULT "1234"
#define FLY_BT_NAME_DEFAULT "DVD"

#define FLY_BT_LASTDEVICE_ADDR		"persist.bt.deviceAddr"
#define FLY_BT_AUTOCONNECT "fly.bt.autoconnect"
#define FLY_BT_LOCAL_PIN		"fly.bt.PIN"
#define FLY_BT_LOGCAT_LEVEL "fly.bt.debug"
#define FLY_BT_DEVICEPINCODE_DEFAULT "fly.bt.pincode.default"
//#define FLY_BT_DEVICEPINCODE_DEFAULT "persist.bt.pincode.default"
#define FLY_BT_DEVICEPINCODE "fly.bt.pin.code"
#define FLY_BT_DEVICENAME_DEFAULT "fly.bt.devicename.default"
//#define FLY_BT_DEVICENAME_DEFAULT "persist.bt.devicename.default"
#define FLY_BT_PARROT_SETBTNAME  "fly.bt_parrot_setbtname"
#define FLY_BT_DEVICENAME "fly.bt.device.name"
#define FLY_BT_DEVICE_AUTOCONNECT "fly.bt.device.autoconnect"
#define FLY_BT_GET_COUNTRYNAME          "fly.module.getCountryName" /*¡°ISRAEL¡±*/
#define FLY_BT_MIC_GAIN     "fly.bt.micgain"
#define FLY_BT_DEVICE_ADDR     "fly.bt.device.addr"
#define FLY_BT_KEYBOARD_LAUNAGE			"fly.bt.keyboard.launage"
#define BTTAG	"FlyBluetooth"
#define FLY_BT_LAST_CONNECT_DEVICE_ADDR "fly.bt.last.connect.device.addr"


#define FLY_BT_DEVICE_END_CMD_MAX_LEN	256
#define FLY_BT_DEVICE_ADDRS_MAX_LEN		64
/*******************device******************************/

#define BT_DEVICE_PAIR_PAGE_ITEM_NUM_NEW			6
#define SEARCH_LIST_DISPLAY_NUM_NEW					6
#define BT_DEVICE_SEARCHED_PAGE_ITEM_NUM_NEW		7

#define BT_DEVICE_PAIR_PAGE_ITEM_NUM			5
#define SEARCH_LIST_DISPLAY_NUM					5
#define BT_DEVICE_SEARCHED_PAGE_ITEM_NUM	5


/******PAIR RECORDINGS****/
#define FLY_BT_PAIRING_NAME_MAX_LEN			128
#define FLY_BT_PAIRING_ADDRS_MAX_LEN			128

/******CONNECTED INFORS****/
#define FLY_BT_DEVICE_CONNECTED_ADDRS_MAX_LEN		    256
#define FLY_BT_DEVICE_CONNECTED_NAME_MAX_LEN		    256

#define PHONE_NUM_MIN_SIZE				3
#define PHONE_NUm_nNPUT_MAX_SIZE		128

#define CALL_HISTORY_NAME_MAX_LEN			128
#define CALL_HISTORY_NUMBER_MAX_LEN			128
#define CALL_HISTORY_TIME_MAX_LEN				256
#define PHONE_NUM_NAME_MAX_SIZE				128
#define FLY_BT_MUSIC_INFOR_MAX_LEN			256
#define PHONE_NUM_MAX_SIZE						16
#define PHONE_NUM_ONE_USER_HAVE				5
#define SIZE_PHONE_BOOK_SEARCH_WORD			128
#define SEARCH_RESULT_LIST_DISPLAY_NUM		3
#define PHONENUM_OR_PHONENAME_MAX_LEN	128
#define FLY_BT_DEVICE_PINCODE_MAX_LEN		64
#define FLY_BT_DEVICE_VERSION_MAX_LEN		    64
#define FLY_BT_DEVICE_NAME_MAX_LEN		    64
#define SEARCH_RANK_RESULT_LIST_DISPLAY_NUM			5
#define GOLF_CAR_SCREEN_PHONE_BOOK_ITEM_NUM	 16
#define FILE_PHONECMD_MAX_LEN 					256
#define HAN_ZI_MATCH_WEIGHT						6291456

#define TIMER_DELAY_CONNECTION_DEVICE_PAGE_TIME		39

#define TIMER_ACC_ON_BT_INIT		50

#define TIMER_ACC_OFF_BT_OFF		51



enum E_BT_DEVICE_SEARCH_STATUS
{
	BT_DEVICE_SEARCH_STATUS_SEARCHING,
	BT_DEVICE_SEARCH_STATUS_SEARCHED_DEVICE_COUNT,
	BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH

};

struct BluetoothDevice
{
	char index;
	int addrLen;
	u8 deviceAddr[FLY_BT_PAIRING_ADDRS_MAX_LEN];
	int nameLen;
	u8 deviceName[FLY_BT_PAIRING_NAME_MAX_LEN];
	bool curConnectDevice;
	bool operator < (const BluetoothDevice &b)const
	{
		return curConnectDevice <b.curConnectDevice;
	}
};

enum E_HFP_CONNECT_STATUS
{
	HFP_CONNECT_STATUS_DISCONNECT, 
	HFP_CONNECT_STATUS_CONNECTED,
	HFP_CONNECT_STATUS_CONNECTING
};

struct BT_PairingInfors
{
	char szPairingPincode[FLY_BT_PAIRING_NAME_MAX_LEN];
	int nPairingPincodeLen;
	char szPairingName[FLY_BT_PAIRING_NAME_MAX_LEN];
	int nPairingNameLen;
};

enum E_BT_PHONE_STATUS
{
	BT_PHONE_STATUS_FREE,
	BT_PHONE_STATUS_CALL_IN,
	BT_PHONE_STATUS_CALL_OUT,
	BT_PHONE_STATUS_TALKING,
	BT_PHONE_STATUS_CALL_IN_FROM_THIRD,
	BT_PHONE_STATUS_HAND_UP,
	BT_PHONE_STATUS_RECEIVE_BULETOOTH,
	BT_PHONE_STATUS_RECEIVE_PHONE,
	BT_PHONE_STATUS_CALL_MEETING
};

enum E_HFP_TALKING_TRANSFER_SET
{
	HFP_SET_CAR_SIDE, 
	HFP_SET_MOBILE_SIDE,
	HFP_SET_UNKNOWN_SIDE,
};

struct ST_PHONE_NUM
{
	char szcPhoneNum[PHONE_NUm_nNPUT_MAX_SIZE];
	u32 dwLen;
	char szcName[PHONE_NUM_NAME_MAX_SIZE];
	u32 dwNameLen;
	char szcTime[PHONE_NUM_NAME_MAX_SIZE];
	u32 dwTimeLen;
};

struct ST_PHONE_BOOK_ONE_USER_INFO
{	
	char szUserName[CALL_HISTORY_NAME_MAX_LEN];//utf8
	char szUserNo[CALL_HISTORY_NUMBER_MAX_LEN];//ansi
};

struct ST_CALL_RECORD_ONE_USER_INFO
{
	char CBType;
   	char szUserName[CALL_HISTORY_NAME_MAX_LEN];
	char szUserNo[CALL_HISTORY_NUMBER_MAX_LEN];
	char CBTime[CALL_HISTORY_TIME_MAX_LEN];
	char CBDate[CALL_HISTORY_TIME_MAX_LEN];
};

enum EM_SYNC_PHONEBOOK_PATH
{
	BT_PBAP_SYNC_PATH_PHONESELF_PHONEBOOK = 0,
	BT_PBAP_SYNC_PATH_SIM_PHONEBOOK = 1,
	BT_PBAP_SYNC_PATH_ALL_PHONEBOOK = 2,
	BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY = 3,
	BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY = 4,
	BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY = 5,
	BT_PBAP_SYNC_PATH_ALL_CALLHISTORY = 6,
	BT_PBAP_SYNC_PATH_ALL_PHONEBOOK_CALLHISTORY = 7,
	NUM_OF_BT_PBAP_SYNC_PATH = 8,
};

enum EM_SelectedPhoneBookType{PHONEBOOK_DIALED,PHONEBOOK_RECV,PHONEBOOK_MISSED,PHONEBOOK_ALL=4};
enum EM_CALL_HISTORY_TYPE
{
	TYPE_CALL_NONE = 0,
	TYPE_CALL_RECIVED = 1,
	TYPE_CALL_DIALED = 2,
	TYPE_CALL_MISSED = 3
};

enum EM_NationalDistinction{
	NATIONAL_UNKNOW,
	NATIONAL_ISRAEL,
	NATIONAL_CHINA,
	NATIONAL_RUSSIA,
	NATIONAL_ARAB
};

enum E_HFP_AUDIO_SOURCE
{
	HFP_AUDIO_SOURCE_BT,
	HFP_AUDIO_SOURCE_MOBILE,
	HFP_AUDIO_SOURCE_UNKNOW
};

typedef struct{
	char cTheFolderType;
	
	char cTheFolderSongMsb[CALL_HISTORY_NUMBER_MAX_LEN];
	int  nTheFolderSongMsb_Len;
	
	char cTheFolderSongLsb[CALL_HISTORY_NUMBER_MAX_LEN];
	int  nTheFolderSongLsb_Len;
	
	char cTheFolderSongDisplay[CALL_HISTORY_NUMBER_MAX_LEN];
	int  nTheFolderSongDisplay_Len;

}st_theBrows_Folders_Info;

struct Songs_TheSong_ExtendedInfo
{
	char cSongMsb[CALL_HISTORY_NUMBER_MAX_LEN];
	int  nSongMsb_Len;
	
	char cSongLsb[CALL_HISTORY_NUMBER_MAX_LEN];
	int  nSongLsb_Len;
	
	char cSongDisplay[CALL_HISTORY_NUMBER_MAX_LEN];
	int  nSongDisplay_Len;

};

struct ST_PhoneNumInfo
{
	char szPhoneNumUtf8[PHONE_NUM_MAX_SIZE * 4];//utf8
};

struct ST_PhoneBookUserInfo
{
	char szUserNameUtf8[PHONE_NUM_NAME_MAX_SIZE];
	char szUserNameUnicode[PHONE_NUM_NAME_MAX_SIZE];
	int nUserNameMatchWeight;
	int nPhoneNumInfoCount;
	ST_PhoneNumInfo szstPhoneNumInfo[PHONE_NUM_ONE_USER_HAVE];
	
	 bool operator < (const ST_PhoneBookUserInfo &b)const
	{
		return nUserNameMatchWeight < b.nUserNameMatchWeight;
	}
};

struct ST_PhoneBookRankUserInfo
{
	char szUserNameUtf8[PHONE_NUM_NAME_MAX_SIZE];
	char szUserNameUnicode[PHONE_NUM_NAME_MAX_SIZE];
	int key;
	int nPhoneNumInfoCount;
	ST_PhoneNumInfo szstPhoneNumInfo[PHONE_NUM_ONE_USER_HAVE];
	
	 bool operator < (const ST_PhoneBookRankUserInfo &b)const
	{
		return key < b.key;
	}
};

struct PhoneBookItem_ExtendedInfo
{
	char PBName_Prefix[PHONENUM_OR_PHONENAME_MAX_LEN];
	int  PBName_Prefix_Len;
	
	char PBName_First[PHONENUM_OR_PHONENAME_MAX_LEN];
	int  PBName_First_Len;
	
	char PBName_Mid[PHONENUM_OR_PHONENAME_MAX_LEN];
	int  PBName_Mid_Len;
	
	char PBName_Last[PHONENUM_OR_PHONENAME_MAX_LEN];
	int  PBName_Last_Len;
	
	char PBName_Suffix[PHONENUM_OR_PHONENAME_MAX_LEN];
	int  PBName_Suffix_Len;

	int  PBName_CompleteTotal_Len;
	
};

enum E_TIP_BOX_NAME{
TIP_BOX_NAME_DELETE_ALL_DEVICES_HAVE_PAIRED,
TIP_BOX_NAME_DELETE_ONE_DEVICE_HAS_PAIRED,
TIP_BOX_NAME_CONNECT_FAIL,
TIP_BOX_NAME_SEARCH_DEVICES_FAIL,
TIP_BOX_NAME_SEARCH_PAIRED,
TIP_BOX_NAME_UNKNOW
};

enum E_KEY_BOARD_LANGUAGE{KEY_BOARD_LANGUAGE_ENGLISH, KEY_BOARD_LANGUAGE_ISRAEL,KEY_BOARD_LANGUAGE_ARAB, KEY_BOARD_LANGUAGE_RUSSIA};

enum E_CUR_CALL_STATE{
	ACTIVE_CALL,
	HELD_CALL,
	DIALING_IN_PROGRESS_OUTING_CALL,
	RINGING_IN_PROGRESS_OUTING_CALL,
	INCOMING_CALL,
	WAITING_CALL,
	CALL_RELEASED
};

struct BT_Call_Infor
{
	bool m_bIsMicOpenState;
	E_CUR_CALL_STATE nCaller_State;
	char cCaller_name[PHONENUM_OR_PHONENAME_MAX_LEN];
	int nCaller_nameLen;
	char cCaller_numb[PHONENUM_OR_PHONENAME_MAX_LEN];
	int nCaller_numbLen;
};

struct Bt_Book_Accurate_Search
{
	char szUserNameUtf8[PHONE_NUM_NAME_MAX_SIZE];
	ST_PhoneNumInfo szstPhoneNumInfo[PHONE_NUM_ONE_USER_HAVE];
	PhoneBookItem_ExtendedInfo stDetailedInfo;
	int nPhoneNumInfoCount;
};

enum A2DP_MUSIC_STATE
{
	A2DP_MUSIC_STOPPED = 0,
	A2DP_MUSIC_PLAYING = 1,
	A2DP_MUSIC_PAUSED = 2,
};
