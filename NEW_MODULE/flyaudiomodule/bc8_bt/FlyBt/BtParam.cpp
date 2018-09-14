/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "BtParam.h"

CBtBC6Adapter *g_pClsBtBC6Adapter = (CBtBC6Adapter*)CBtBC6Adapter::GetInstance();
CBtJniSdk *g_pClsBtJniSdk = (CBtJniSdk*)CBtJniSdk::GetInstance();

CBtParam::CBtParam(void)
{
}

CBtParam::~CBtParam(void)
{
	/*if (!m_listBtDeviceSearched.empty())
		m_listBtDeviceSearched.clear();*/
	
}

void CBtParam::init(void)
{
	/*setDefaultParam();
	m_pBtHal->initDeviceState();
	m_pBtApp->initBtUi();*/
}

void CBtParam::setDefaultParam()
{
	memset(m_pBtParam->m_SendMessagesStr,0,FLY_BT_DEVICE_END_CMD_MAX_LEN);
	m_bIsPowerOn = true;
	m_nBtDevicesHaveSearchedListBrowseFrom = 0;
	m_ePhoneStatus = BT_PHONE_STATUS_FREE;
	memset(szTemBtDevicePinCode,0,sizeof(szTemBtDevicePinCode));
	memset(szLocalBtDevicePinCode_Default, 0, sizeof(szLocalBtDevicePinCode_Default));
	memset(szLocalBtDevice_PinCode, 0, sizeof(szLocalBtDevice_PinCode));
	memset(szTemBtDeviceName,0,sizeof(szTemBtDeviceName));
	memset(szLocalBtDeviceName_Default,0,sizeof(szLocalBtDeviceName_Default));
	memset(szLocalBtDevice_Name,0,sizeof(szLocalBtDevice_Name));

	m_iselectPhoneBook=BT_PBAP_SYNC_PATH_ALL_CALLHISTORY;
	bIsAutoConnect = true;
	m_pBtParam->m_bIsMicOpen = true;
	bHandleStopSearchState = false;
	nNationalDistinction = NATIONAL_UNKNOW;
	memset(cStrBt_GetCountryName,0,sizeof(cStrBt_GetCountryName));

	m_pBtParam->m_bFirstStart = true;

	m_eBtDeviceSearchStatus = BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH;

	m_bAutoJump = false;
	memset(cStrCareLand_PTTNumber,0,sizeof(cStrCareLand_PTTNumber));

	m_bIsLocalBtDeviceInitOk=false;
	bA2DP_To_DevicePageBackButton = false;

	emTempHfpConnectStatus = HFP_CONNECT_STATUS_DISCONNECT;
	emTempHfpTalkingTransferSet = HFP_AUDIO_SOURCE_UNKNOW;
	emTempHfpPhoneStatus = BT_PHONE_STATUS_FREE;
	bAfterDialingSyncCallLogs = false;
	bNoA2dpChannelPlay = false;

	cUpdataPhoneBookCountIndex = 0;
	emPhoneStatusBallon = BT_PHONE_STATUS_FREE;


	//BC8
	m_bCanSendData = true;
	bIsStopPairing = true;
	memset(cSelectDeviceAddr,0,FLY_BT_PAIRING_ADDRS_MAX_LEN);
	bIsSelectPairing = false;
	nCallCount = CALLING_COUNT_FREE;
	bItsAddCalls = false;
	em_MultiCallstate = MULTI_CALL_STATE_FREE;
	memset(m_strTemCallingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
	
	memset(m_strTemInNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_strTemInName,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_strTemOutNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_strTemOutName,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_strTemWaitingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_strTemWaitingName,0,PHONE_NUm_nNPUT_MAX_SIZE);
	
	bSpecialHangUpIsStillOnHold = false;
	bHangUpAutoDailin = false;
	bSpecialCaseBackPage = false;

	
	memset(tempMeetNum1,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(tempMeetNum2,0,PHONE_NUm_nNPUT_MAX_SIZE);

	tempAutoMatetsg = false;
	bIsPairBox = false;
	
	m_bSetBookTimeSign = false;
	m_pBtParam->m_bSetRecordTimeSign = false;

	bIsSpeedConnectState = false;
	
	m_pBtParam->m_bIsA2dpOnPlayState = false;
	m_pBtParam->m_bshowPhonePair_PromptBox = true;
	m_pBtParam->tempHideBtPage = false;
	m_bVioceSupportStatus = 0x00;
	m_bVoiceRecgStatus = 0x00;
	m_bIsCallLogLoadFinish = false;
	FirOrBackTag = false;
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

	property_get(FLY_MODULE_IS_T123,property,"0");
	sscanf(property,"%d",&uModuleBt_is_T123);

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

	u32 nTmic;
	property_get(FLY_BT_CONFIG_MIC_VOLUME_VAL, property, "13");
	sscanf(property,"%d", &nTmic);

	property_get(FLY_BT_MIC_VOLUME_VAL, property, "255");
	sscanf(property,"%d", &m_nMicVolume);
	
	if(m_nMicVolume == 255)
		m_nMicVolume = nTmic;
	

	//property_get(FLY_BT_KEYBOARD_LAUNAGE,property,"0xff");
	//sscanf(property,"%d", &m_ePhoneBookKeyBoardSearchLanguage);
	
}

void CBtParam::saveParameter(void)
{
	LOGD("[%s]", __FUNCTION__);
	
	char property[PROPERTY_VALUE_MAX] = {0};
	
	//saveBtPinCode();
	saveBtName();
	
	sprintf(property, "%hhd",bIsAutoConnect);
	property_set(FLY_BT_DEVICE_AUTOCONNECT, property);

	sprintf(property,"%d", n_MicGain_Volue);
	property_set(FLY_BT_MIC_GAIN,property);
	
	sprintf(property,"%hhd", m_ePhoneBookKeyBoardSearchLanguage);
	property_set(FLY_BT_KEYBOARD_LAUNAGE,property);

	sprintf(property,"%d", m_nMicVolume);
	property_set(FLY_BT_MIC_VOLUME_VAL,property);

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
	LOGD("[%s] [%s]", __FUNCTION__,szLocalBtDevice_Name);
	
	char property[PROPERTY_VALUE_MAX] = {0};

	sprintf(property, "%s",szLocalBtDevice_Name);
	property_set(FLY_BT_DEVICENAME, property);

}








