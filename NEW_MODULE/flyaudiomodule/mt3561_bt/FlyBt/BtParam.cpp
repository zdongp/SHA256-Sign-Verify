/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "BtParam.h"
#include "types_def.h"
#include "commonFunc.h"

CBtAdapter *g_pClsBtAdapter = (CBtAdapter*)CBtAdapter::GetInstance();
CBtJniSdk *g_pClsBtJniSdk = (CBtJniSdk*)CBtJniSdk::GetInstance();

CBtParam::CBtParam(void)
{
}

CBtParam::~CBtParam(void)
{
	
}

void CBtParam::init(void)
{

}

void CBtParam::setDefaultParam()
{ 
	m_bIsPowerOn = false;
	m_nBtDevicesHaveSearchedListBrowseFrom = 0;
	m_ePhoneStatus = BT_PHONE_STATUS_FREE;
	memset(szTemBtDevicePinCode,0,sizeof(szTemBtDevicePinCode));
	memset(szLocalBtDevicePinCode_Default, 0, sizeof(szLocalBtDevicePinCode_Default));
	memset(szLocalBtDevice_PinCode, 0, sizeof(szLocalBtDevice_PinCode));
	memset(szTemBtDeviceName,0,sizeof(szTemBtDeviceName)); 
	memset(szLocalBtDevice_Name,0,sizeof(szLocalBtDevice_Name));
	m_iselectPhoneBook=BT_PBAP_SYNC_PATH_ALL_CALLHISTORY;
	m_pBtParam->m_emSelectedPhone=PHONEBOOK_ALL;
	bIsAutoConnect = true; 
	m_pBtParam->muteSwicthState=false;
	bHandleStopSearchState = true;
	nNationalDistinction = NATIONAL_UNKNOW;
	m_pBtParam->m_bFirstStart = true;

	m_eBtDeviceSearchStatus = BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH;

	m_bAutoJump = false;  
	bA2DP_To_DevicePageBackButton = false;

	emTempHfpConnectStatus = HFP_CONNECT_STATUS_DISCONNECT;
	emTempHfpTalkingTransferSet = HFP_SET_UNKNOWN_SIDE;
	emTempHfpPhoneStatus = BT_PHONE_STATUS_FREE; 
	bNoA2dpChannelPlay = false;

	cUpdataPhoneBookCountIndex = 0;
	emPhoneStatusBallon = BT_PHONE_STATUS_FREE; 
	m_pBtParam->m_TheFolderlistSongBrowsing.clear();
	m_pBtParam->m_theSongs.clear();
	curIsFolder = 0;
	bIsStopPairing = true;  
	bItsAddCalls = false; 
	memset(m_strTemCallingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
	
	memset(m_strTemInNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_strTemInName,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_strTemOutNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_strTemOutName,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_strTemWaitingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_strTemWaitingName,0,PHONE_NUm_nNPUT_MAX_SIZE); 
	bSpecialCaseBackPage = false; 
	tempAutoMatetsg = false;
	bIsPairBox = false; 
	m_pBtParam->m_bIsA2dpOnPlayState = false; 
	nPairRecordTotal = 0;

	muteSwicthState = false;
	memset(szRemodeBtDeviceHasConnectedAddr, 0, sizeof(szRemodeBtDeviceHasConnectedAddr));
	memset(cStrBt_GetCountryName,0,sizeof(cStrBt_GetCountryName));
	memset(szLocalBtDeviceName_Default,0,sizeof(szLocalBtDeviceName_Default));
	FirOrBackTag = false;

	bInitState = false;
	bPairingStatus = false;
	memset(m_pBtParam->szRemodeBtDeviceLastConnectedAddr, 0, sizeof(m_pBtParam->szRemodeBtDeviceLastConnectedAddr));
	m_bSupport_A2DP = false;	
	memset(selecteDeviceAddr,0,FLY_BT_PAIRING_ADDRS_MAX_LEN);
	selecteDeviceAddrLen = 0;
	m_pBtParam->tempHideBtPage = false;
}

void CBtParam::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
{
	m_pBtApp	 = (CBtApp *)pFlyApp; 
	m_pBtModule  = (CBtModule *)pFlyModule; 
	m_pBtHal	 = (CBtHal *)pFlyHal; 
	m_pBtParam   = (CBtParam *)pFlyParam; 

	m_pFlyApp    = pFlyApp;
	m_pFlyModule = pFlyModule;
	m_pFlyHal    = pFlyHal;
	m_pFlyParam  = pFlyParam;
}

void CBtParam::readParameter(void)
{
	LOGD("[%s]", __FUNCTION__);
	
	setDefaultParam();
	
	char property[PROPERTY_VALUE_MAX] = {0};

	property_get(FLY_BT_DEVICEPINCODE_DEFAULT,property,FLY_BT_PINCODE_DEFAULT);
	strcpy(szLocalBtDevicePinCode_Default,property);
	int nLenDefaultPinCode = strlen(szLocalBtDevicePinCode_Default);
	LOGD("[%s] szLocalBtDevicePinCode_Default:%s (%d)",__FUNCTION__,szLocalBtDevicePinCode_Default,nLenDefaultPinCode);

	property_get(FLY_BT_DEVICEPINCODE,property,NULL);
	strcpy(szLocalBtDevice_PinCode,property);
	LOGD("[%s] szLocalBtDevice_PinCode:%s",__FUNCTION__,szLocalBtDevice_PinCode);
	if(strlen(szLocalBtDevice_PinCode) == NULL)
	{
		if(nLenDefaultPinCode > 4){
			memcpy(szLocalBtDevice_PinCode,szLocalBtDevicePinCode_Default,4);
		}
		else
		{
			memcpy(szLocalBtDevice_PinCode,szLocalBtDevicePinCode_Default,nLenDefaultPinCode);
		}
	}
	LOGD("[%s] szLocalBtDevice_PinCode:%s",__FUNCTION__,szLocalBtDevice_PinCode);
	printf("[BT] [read param] PinCode:%s\n",szLocalBtDevice_PinCode);

	property_get(FLY_BT_PARROT_SETBTNAME,property,FLY_BT_NAME_DEFAULT);
	strcpy(szLocalBtDeviceName_Default, property);
	int nLenDefaultName = strlen(szLocalBtDeviceName_Default);
	LOGD("[%s] szLocalBtDeviceName_Default:%s (%d)",__FUNCTION__,szLocalBtDeviceName_Default,nLenDefaultName);

	property_get(FLY_BT_DEVICENAME,property,NULL);
	strcpy(szLocalBtDevice_Name, property);
	LOGD("[%s] szLocalBtDevice_Name:%s",__FUNCTION__,szLocalBtDevice_Name);
	if(strlen(szLocalBtDevice_Name) == NULL)
	{
		strcpy(szLocalBtDevice_Name,szLocalBtDeviceName_Default);
	}
	LOGD("[%s] szLocalBtDevice_Name:%s",__FUNCTION__,szLocalBtDevice_Name);
	printf("[BT] [read param] BtName:%s\n",szLocalBtDevice_Name);
	
	property_get(FLY_BT_DEVICE_AUTOCONNECT,property,"1");
	sscanf(property,"%d",&bIsAutoConnect);

	property_get(FLY_BT_GET_COUNTRYNAME,property,NULL);
	sscanf(property,"%s", &cStrBt_GetCountryName);
	LOGD("pLocalParam->cStrBt_GetCountryName:%s",cStrBt_GetCountryName);
	if(strcmp(cStrBt_GetCountryName,"ISRAEL") == 0)
	{
	   nNationalDistinction = NATIONAL_ISRAEL;
	}
	else if(strcmp(cStrBt_GetCountryName,"CHINA") == 0)
	{
	    nNationalDistinction = NATIONAL_CHINA;
	}
	else if(strcmp(cStrBt_GetCountryName,"RUSSIA") == 0)
	{
	    nNationalDistinction = NATIONAL_RUSSIA;
	}
	/*<<<<<<<<<<<<<-----------[BEN] ADD--------------------*/
	else if(strcmp(cStrBt_GetCountryName,"ARAB") == 0)
	{
	    nNationalDistinction = NATIONAL_ARAB;
	}
	/*----------------------------END----------->>>>>>>>>>>*/
	LOGD("pLocalParam->nNationalDistinction:%d",nNationalDistinction);

	property_get(FLY_BT_MIC_GAIN, property, "23");
	sscanf(property,"%d", &n_MicGain_Volue);

	//property_get(FLY_BT_KEYBOARD_LAUNAGE,property,"0xff");
	//sscanf(property,"%d", &m_ePhoneBookKeyBoardSearchLanguage);
	
	property_get(FLY_BT_LAST_CONNECT_DEVICE_ADDR,property,NULL);
	strcpy(szRemodeBtDeviceLastConnectedAddr, property);
	
}

void CBtParam::saveParameter(void)
{
	LOGD("[%s]", __FUNCTION__);
	
	char property[PROPERTY_VALUE_MAX] = {0};
	saveBtPinCode();
	saveBtName();
	sprintf(property, "%d",bIsAutoConnect);
	property_set(FLY_BT_DEVICE_AUTOCONNECT, property);

	sprintf(property,"%d", n_MicGain_Volue);
	property_set(FLY_BT_MIC_GAIN,property);
	
	sprintf(property,"%d", m_ePhoneBookKeyBoardSearchLanguage);
	property_set(FLY_BT_KEYBOARD_LAUNAGE,property);
}

void CBtParam::saveBtPinCode(void)
{
	LOGD("[%s]", __FUNCTION__);
	
	char property[PROPERTY_VALUE_MAX] = {0};
	sprintf(property, "%s",szLocalBtDevice_PinCode);
	property_set(FLY_BT_DEVICEPINCODE, property);
}

void CBtParam::saveBtName(void)
{
	LOGD("[%s]", __FUNCTION__);
	
	char property[PROPERTY_VALUE_MAX] = {0};
	sprintf(property, "%s",szLocalBtDevice_Name);
	property_set(FLY_BT_DEVICENAME, property);
}

void CBtParam::saveLastConnectBtAddr(void)
{
	LOGD("[%s]", __FUNCTION__);
	char property[PROPERTY_VALUE_MAX] = {0};
	sprintf(property, "%s",szRemodeBtDeviceLastConnectedAddr);
	property_set(FLY_BT_LAST_CONNECT_DEVICE_ADDR, property);
}







