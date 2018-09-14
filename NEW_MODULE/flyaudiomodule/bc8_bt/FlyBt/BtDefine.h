/*
	author: YanBin Deng
	  date: 2014/09/01  
*/

#pragma once

//#define MSM_ANDROID_ISR_NEW_FUNCTION
#define MSM_ANDROID_ISR_RECORDS_ALL  45
#define MSM_ANDROID_ISR_RECORDS_RECEIVED  15
#define MSM_ANDROID_ISR_RECORDS_DIALED  15
#define MSM_ANDROID_ISR_RECORDS_MISSED  15

#define MAX_BC8_MIC_VALUE  31

#define BT_DEVICE_PAIR_PAGE_ITEM_NUM_NEW			6
#define SEARCH_LIST_DISPLAY_NUM_NEW					6
#define BT_DEVICE_SEARCHED_PAGE_ITEM_NUM_NEW		7

#define DEF_SET_AUDIO_OPEN_SWITCH "#*#*158359*#*#"
#define DEF_SET_AUDIO_CLOSE_SWITCH "000000"  

//SET
#define FLY_BT_PINCODE_DEFAULT 		"1234"
#define FLY_BT_NAME_DEFAULT 		"DVD"

#define PHONENUM_OR_PHONENAME_MAX_LEN	128
//PAIR RECORDINGS
#define FLY_BT_PAIRING_NAME_MAX_LEN		128
#define FLY_BT_PAIRING_ADDRS_MAX_LEN	128
//CONNECTED INFORS
#define FLY_BT_DEVICE_CONNECTED_ADDRS_MAX_LEN		    256
#define FLY_BT_DEVICE_CONNECTED_NAME_MAX_LEN		    256

//DEVICE INFORS
#define FLY_BT_DEVICE_VERSION_MAX_LEN		64
#define FLY_BT_DEVICE_NAME_MAX_LEN		    64
#define FLY_BT_DEVICE_PINCODE_MAX_LEN		64
#define FLY_BT_DEVICE_ADDRS_MAX_LEN		    64
#define FLY_BT_DEVICE_END_CMD_MAX_LEN		256
#define FLY_BT_DEVICE_TO_HAL_CMD_MAX_LEN	128
//MUSIC
#define FLY_BT_MUSIC_INFOR_MAX_LEN		256
//ERROR CODE
#define ERROR_CALL_BACK_FAILED			0xFF
//电话号码
#define PHONE_NUM_MAX_SIZE				16
#define PHONE_NUM_MIN_SIZE				3
#define PHONE_NUM_NAME_MAX_SIZE			128
#define PHONE_NUm_nNPUT_MAX_SIZE		128
#define PHONE_NUM_ONE_USER_HAVE			5
//->dyb phone search
#define PHONENUM_NAME_MAX_LEN		    128
#define SIZE_PHONE_BOOK_SEARCH_WORD		128
#define SIZE_PHONE_BOOK_USER_NAME		128

#define SEARCH_LIST_DISPLAY_NUM			5
#define SEARCH_RESULT_LIST_DISPLAY_NUM	3
#define ONE_NAME_FOR_MULT_NUM_DISPLAY	5
#define SEARCH_RESULT_RANK_DISPLAY_NUM	5


#define HAN_ZI_MATCH_WEIGHT						6291456			//(1024 * 1024 * 6)
#define FILE_PHONECMD_MAX_LEN 					256
//BC08
#define SEARCH_RANK_RESULT_LIST_DISPLAY_NUM		5

//<-dyb phone search
#define CALL_HISTORY_MAX_NUM				20
#define CALL_HISTORY_NUMBER_MAX_LEN			128
#define CALL_HISTORY_NAME_MAX_LEN			128
#define CALL_HISTORY_TIME_MAX_LEN			256
#define FLY_PHONE_BOOK_TYPE_NUM	        4
//A2DP
#define AUTO_PLAY_A2DP_COUNT_MAX		5
//蓝牙设备//pin code
#define BT_DEVICE_SEARCHED_PAGE_ITEM_NUM	6
#define DEVICE_PIN_CODE_MAX_SIZE			7
#define DOWNLOAD_CALLHISTORY_MAX_COUNT		20
#define DOWN_LOAD_PHONE_BOOK_ITEM_NUM		50
//////////////////////////////////////////////////////////////////////////
#define HALTOKEY_KEYVAL_SLEEP			0x01
#define HALTOKEY_KEYVAL_MENU			0x02
#define HALTOKEY_KEYVAL_AV				0x03
#define HALTOKEY_KEYVAL_BT				0x08
#define HALTOKEY_KEYVAL_CALL_REJECT		0x32
#define HALTOKEY_KEYVAL_SEEK_INC		0x38
#define HALTOKEY_KEYVAL_SEEK_DEC		0x39
#define HALTOKEY_KEYVAL_TUNE_INC		0x3B
#define HALTOKEY_KEYVAL_TUNE_DEC		0x3C
#define HALTOKEY_KEYVAL_kEY_CALLOUT		0x46
#define HALTOKEY_KEYVAL_KEY_CALLINOUT	0x47

#define FLY_MODULE_IS_T123 		"fly.module.is.T123"
#define FLY_BT_LASTDEVICE_ADDR	"persist.bt.deviceAddr"
#define FLY_BT_AUTOCONNECT 		"fly.bt.autoconnect"
#define FLY_BT_LOCAL_PIN		"fly.bt.PIN"
#define FLY_BT_LOGCAT_LEVEL 	"fly.bt.debug"

#define FLY_BT_DEVICEPINCODE_DEFAULT "fly.bt.pincode.default"
#define FLY_BT_DEVICEPINCODE 		 "fly.bt.pin.code"

#define FLY_BT_DEVICENAME_DEFAULT 	"fly.bt.devicename.default"
#define FLY_BT_PARROT_SETBTNAME  	"fly.bt_parrot_setbtname"
#define FLY_BT_DEVICENAME 			"fly.bt.device.name"

#define FLY_BT_DEVICE_AUTOCONNECT 	"fly.bt.device.autoconnect"
#define FLY_BT_GET_COUNTRYNAME      "fly.module.getCountryName" /*“ISRAEL”*/
#define FLY_BT_MIC_GAIN     		"fly.bt.micgain"
#define FLY_BT_MIC_VOLUME_VAL  		"fly.bt.micval"
#define FLY_BT_CONFIG_MIC_VOLUME_VAL "fly.bt.config.micval"

#define FLY_BT_DEVICE_ADDR     		"fly.bt.device.addr"
#define FLY_BT_KEYBOARD_LAUNAGE		"fly.bt.keyboard.launage"

#define TIME_INTERVAL_POWEROFF_STEP_TIP 300
#define TIME_INTERVAL_PB_MSG_DOWNLOAD_TIP 8000
#define TIME_INTERVAL_GET_PB_DATA_LOCAL_TIP 800
#define TIME_INTERVAL_AUTO_CONNECT_TIP 8000
#define TIME_INTERVAL_CLICK_CONNECT_TIP 5000
#define TIME_INTERVAL_GET_A2DP_PLAY_STATUS_TIP	1000
#define TIME_INTERVAL_AUTO_PLAY_A2DP_TIP	1000
#define TIME_INTERVAL_GET_PB_DATA_TIP	800
#define TIME_INTERVAL_JUMPPAGE_TEST_TIP	7000
#define TIME_INTERVAL_POWER_ON_OFF_TIP	5000
#define TIME_INTERVAL_SHOW_CONNECT_NAME_TIP	3000
#define TIME_INTERVAL_TERMINAL_CALL_TIP	8000
#define TIME_INTERVAL_QUERY_PHONE_STATUS_TIP	3000
#define TIME_INTERVAL_AVRCP_ACTION_TIP 200

#define TIME_INTERVAL_PHONECALL_TEST_TIP	15000
#define TIME_INTERVAL_DIAL_TEST_TIP				20000
#define TIME_INTERVAL_QUERY_PHONEBOOK_TIP	  10000
#define TIME_INTERVAL_QUERY_CALLHISTORY_TIP	  5000
#define TIME_INTERVAL_QUERY_SETTIME_TIP	  50000
#define TIME_INTERVAL_HID_PHONEPAIR_TIPBOX     120000

#define TIME_INTERVAL_HID_PHONEPAIRING 1000
#define TIMES_ONE_TOUCH_SPEED_CONNECT_SWITCH 1500
#define TIMER_CALLING_TIMES 1000

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
"fly.debugSet.bc8_bt",
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
"fly.debugSet.NativeServer"
"fly.debugSet.extcar_honda_tsu"};

////////////////////////////////////////////////////
//settime
#define TIMER_BC06_A2DPTIME	  16
#define TIMER_BC06_AUTOCONNECT  19
#define TIMER_BC06_QUERY_PHONEBOOK  20
#define TIMER_BC06_SETTIME_PHONEBOOK     22
#define TIMER_BC06_SET_TRANSFER_DIALING 29
#define TIMER_BC06_SYNC_CALL_LOGS_FREE 30

//BC8
#define TIMER_BC8_NOTRECEIVE 31
#define TIMER_SYNC_CALL_RECORED 32
#define TIMER_SYNC_CALL_RECORED_CLEAR 33
#define TIMER_SYNC_INIT_CALL_RECORED 34
#define TIMER_SYNC_INIT_CALL_RECORED_ALL_TIME 35
#define TIMER_SYNC_INIT_PHONE_BOOK 36
#define TIMER_SYNC_INIT_PHONE_BOOK_ALL_TIME 37

#define TIMES_ONE_TOUCH_SPEED_CONNECT_SWITCH 1500
#define TIME_ID_ONE_TOUCH_SPEED_CONNECT_SWITCH  38

#define TIMER_SET_VOICE_DAILING_STATUS 40
#define TIMER_SET_CALLING_TIMES_1 41
#define TIMER_SET_CALLING_TIMES_2 42


////////////////////////////////////////////////////
enum E_TIP_BOX_NAME{
	TIP_BOX_NAME_DELETE_ALL_DEVICES_HAVE_PAIRED,
	TIP_BOX_NAME_DELETE_ONE_DEVICE_HAS_PAIRED,
	TIP_BOX_NAME_CONNECT_FAIL,
	TIP_BOX_NAME_SEARCH_DEVICES_FAIL,
	TIP_BOX_NAME_SEARCH_PAIRED,
	TIP_BOX_NAME_SPEED_ONE_TOUCH_PAIRED,
	TIP_BOX_NAME_UNKNOW
};

enum E_HFP_AUDIO_SOURCE
{
	HFP_AUDIO_SOURCE_CAR,
	HFP_AUDIO_SOURCE_MOBILE,
	HFP_AUDIO_SOURCE_UNKNOW
};

//PBAP
#define GOLF_CAR_SCREEN_PHONE_BOOK_ITEM_NUM	 16
enum EM_SYNC_PHONEBOOK_PATH{
	BT_PBAP_SYNC_PATH_PHONESELF_PHONEBOOK = 0,
	BT_PBAP_SYNC_PATH_SIM_PHONEBOOK = 1,
	BT_PBAP_SYNC_PATH_ALL_PHONEBOOK = 2,
	BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY = 3,
	BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY = 4,
	BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY = 5,
	BT_PBAP_SYNC_PATH_ALL_CALLHISTORY = 6,
	BT_PBAP_SYNC_PATH_ALL_PHONEBOOK_CALLHISTORY = 7,
	NUM_OF_BT_PBAP_SYNC_PATH = 8
};

//Record
struct ST_PHONE_NUM
{
	char szcPhoneNum[PHONE_NUm_nNPUT_MAX_SIZE];
	u32 dwLen;
	char szcName[PHONE_NUM_NAME_MAX_SIZE];
	u32 dwNameLen;
	char szcTime[PHONE_NUM_NAME_MAX_SIZE];
	u32 dwTimeLen;
};

struct ST_PHONE_NAME
{
	char szcPhoneName[PHONE_NUM_NAME_MAX_SIZE];
	u32 dwLen;
};

struct ST_PHONE_CALLTIME
{
	char szcPBTime[PHONE_NUM_NAME_MAX_SIZE];
	u32 dwLen;
};

struct ST_PB_ITEM
{
	int type;
	ST_PHONE_NAME stPBName;
	ST_PHONE_NUM stPBNum;
	ST_PHONE_CALLTIME stPBCallTime;
/*public:
	bool operator < (const ST_PHONE_NUM &p) const
	{
		return memcmp(stPhoneNum.szcPhoneNum, p.szcPhoneNum, stPhoneNum.dwLen) < 0;
	}
*/
};
//

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


//////////////////////////////////////////////////////////////////////////
struct BluetoothDevice
{
	char index;
	int addrLen;
	u8 deviceAddr[FLY_BT_PAIRING_ADDRS_MAX_LEN];
	int nameLen;
	u8 deviceName[FLY_BT_PAIRING_NAME_MAX_LEN];
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
	long long int nTime;
	 bool operator < (const ST_CALL_RECORD_ONE_USER_INFO &b)const
	{
		return nTime > b.nTime;
	}
};

enum E_BT_DEVICE_SEARCH_STATUS
{
	BT_DEVICE_SEARCH_STATUS_SEARCHING,
	BT_DEVICE_SEARCH_STATUS_SEARCHED_DEVICE_COUNT,
	BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH
};

enum E_HFP_CONNECT_STATUS
{
	HFP_CONNECT_STATUS_DISCONNECT, 
	HFP_CONNECT_STATUS_CONNECTED,
	HFP_CONNECT_STATUS_CONNECTING
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

enum EM_NationalDistinction{
	NATIONAL_UNKNOW,
	NATIONAL_ISRAEL,
	NATIONAL_CHINA,
	NATIONAL_RUSSIA,
	NATIONAL_ARAB
};

enum E_KEY_BOARD_LANGUAGE{
	KEY_BOARD_LANGUAGE_ENGLISH, 
	KEY_BOARD_LANGUAGE_ISRAEL,
	KEY_BOARD_LANGUAGE_ARAB, 
	KEY_BOARD_LANGUAGE_RUSSIA
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

//BC8
#define BT_VERSION_BC08 "[BC08]"
#define FOLDER_FILE_ITEM_COUNT 5
typedef struct {
	int len;
	char cmd[FILE_PHONECMD_MAX_LEN];
}file_phoneCmd_t;

#define FILE_PHONECMD_GROUP_MAX_COUNT 1024

typedef struct
{
	int count;
	file_phoneCmd_t cmdGroup[FILE_PHONECMD_GROUP_MAX_COUNT];
}file_phoneCmdGroup_t;

struct BT_PairingInfors
{
	char szPairingPincode[FLY_BT_PAIRING_NAME_MAX_LEN];
	int nPairingPincodeLen;
	char szPairingName[FLY_BT_PAIRING_NAME_MAX_LEN];
	int nPairingNameLen;
};

//Call
#define CALLING_COUNT_FREE 0
#define CALLING_COUNT_ONLY 1
#define CALLING_COUNT_MUTIL 2

enum E_CUR_MULTI_CALL_STATE{
	MULTI_CALL_STATE_FREE,
	MULTI_CALL_STATE_CALLING_ONLY,
	MULTI_CALL_STATE_CALLING_OR_WAITING,
	MULTI_CALL_STATE_MEETING_TEL
};

enum E_CUR_MULTI_HELD_STATE{
	MULTI_CALL_FREE,
	MULTI_CALL_2_1,
	MULTI_CALL_1_2,
	MULTI_CALL_MEETING_TEL
};

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
