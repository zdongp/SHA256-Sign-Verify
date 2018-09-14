/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "BtModule.h"
#include "types_def.h"
#include "commonFunc.h"


//#include <cutils/properties.h>

//���̸����ָ��
CFlyModule *g_pFlyModule = (CFlyModule*)CBtModule::GetInstance();

CBtModule::CBtModule(void)
{
	m_pBtApp    = CBtApp::GetInstance();
	m_pBtModule = this;
	m_pBtHal    = CBtHal::GetInstance();
	m_pBtParam  = CBtParam::GetInstance();

	m_pFlyApp    = m_pBtApp;
	m_pFlyModule = m_pBtModule;
	m_pFlyHal    = m_pBtHal;
	m_pFlyParam  = m_pBtParam;

	m_pBtApp->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);
	m_pBtHal->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);
	m_pBtParam->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);
}

CBtModule::~CBtModule(void)
{
}

moduleid_t CBtModule::locale_module_mid(void)
{
	return MODULE_ID_BT;
}

void CBtModule::init(void)
{
	// ��������������
	LOGD("[%s] [%s]", __FILE__, __FUNCTION__);
	m_pBtModule->initNativeTimer();
}

void CBtModule::getAccOn()
{
	LOGD("[%s]", __FUNCTION__);
	printf("[BT] [ACC ON]\n");
	m_pBtApp->initUi();
	//m_pBtHal->setToHalInit();
	m_pBtModule->btToModule_NotifyAudiovideo_BT_MicSwitch(0x00);
	//getStandByStatus(0,1);
}

void CBtModule::getAccOff()
{
	LOGD("[%s]", __FUNCTION__);
	printf("[BT] [ACC OFF]\n");
	m_pBtParam->saveParameter();
	killAllTimer();
	
	//getStandByStatus(1,1);
}

void CBtModule::getSystemCodeStartInitModule()
{
	LOGD("[%s]", __FUNCTION__);
	init();
	m_pBtApp->initUi();
	m_pBtHal->setToHalInit();
	
	m_pBtApp->setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_UP, (short)0);
	m_pBtApp->setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_DOWN, (short)0);
	m_pBtApp->setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_UP,false);
	m_pBtApp->setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_DOWN,false);
	m_pBtModule->btToModule_NotifyAudiovideo_BT_MicSwitch(0x00);

}

void CBtModule::getReset()
{
	m_pBtParam->saveParameter();
}

void CBtModule::getResetFactorySetting(void)
{
	m_pBtParam->setDefaultParam();
	m_pBtParam->saveParameter();
}

void CBtModule::timerHandleProc(int timerId)
{
}

void CBtModule::killAllTimer()
{

}

////////////////////////////////////////////////////////////////////////////

void CBtModule::getMyModuleParam(char id, u8 *p, u8 *pLen)
{
	switch((u8)id)
	{
	case BT_MOBILE_STATUS:
		{
			*p = m_pBtParam->m_ePhoneStatus ;
			*pLen = 1;
            
			LOGD("[%s] phone status = [%s]", __FUNCTION__,  getBtPhoneStatusString(getBtPhoneStatus()));
		}
		break;
	case BT_A2DP_SUPPORT:
		{
			*p = m_pBtParam->m_bSupport_A2DP;
			*pLen = 1;
		}
		break;
	case BT_HF_CONNECT_STATUS:
		{
			*p = m_pBtParam->m_eHfpConnectStatus ;
			*pLen = 1;

			LOGD("[%s] [%s]", __FUNCTION__,  getBtConnectStatusString(getBtConnectStatus()));
		}
		break;
	case BT_POWER_STATUS:
		{
			*p = m_pBtParam->m_bIsPowerOn;
			*pLen = 1;

			LOGD("[%s] [%s]", __FUNCTION__,  m_pBtParam->m_bIsPowerOn ? "yes" : "no");
		}
		break;
	case BT_VERSION_INFO:
		{
			memcpy(p,m_pBtParam->szLocalBtDeviceVersion,strlen(m_pBtParam->szLocalBtDeviceVersion));
		   *pLen = strlen(m_pBtParam->szLocalBtDeviceVersion);
		}
		break;
	case BT_ADDR:
		{
			memcpy(p,m_pBtParam->szLocalBtDeviceAddr,strlen(m_pBtParam->szLocalBtDeviceAddr));
		   *pLen = strlen(m_pBtParam->szLocalBtDeviceAddr);
		}
		break;
	case BT_NATIONAL_NAME:
		*p = (u8)m_pBtParam->nNationalDistinction;
		*pLen = 1;
		break;
	case BT_IS_PAIR_BOX:
	    *p = (u8)m_pBtParam->bIsPairBox;
		*pLen = 1;
		break;
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////////
bool CBtModule::isPowerOn()
{
	LOGD("[%s] m_bIsPowerOn = [%s]", __FUNCTION__,  m_pBtParam->m_bIsPowerOn ? "yes" : "no");

	return m_pBtParam->m_bIsPowerOn;
}

//bool CBtModule::isWorking()
//{
	//LOGD("[%s] m_bIsWorking = [%s]", __FUNCTION__,  m_pBtParam->m_bIsWorking ? "yes" : "no");

	//return m_pBtParam->m_bIsWorking;

//}

//bool CBtModule::isBtModeInit()
//{
	//LOGD("[%s] m_bIsLocalBtDeviceInitOk = [%s]", __FUNCTION__,  m_pBtParam->m_bIsLocalBtDeviceInitOk ? "yes" : "no");

	//return m_pBtParam->m_bIsLocalBtDeviceInitOk;
//}

E_HFP_CONNECT_STATUS CBtModule::isConnected()
{
	LOGD("[%s] m_eHfpConnectStatus = [%s]", __FUNCTION__,  getBtConnectStatusString(m_pBtParam->m_eHfpConnectStatus));

	return m_pBtParam->m_eHfpConnectStatus;
}

bool CBtModule::isSupportA2DP()
{
	LOGD("[%s] m_bSupport_A2DP = [%s]", __FUNCTION__,  m_pBtParam->m_bSupport_A2DP ? "yes" : "no");

	return m_pBtParam->m_bSupport_A2DP;
}


bool CBtModule::isInBtPage(void)
{
	bool bRet = false;

	u16 pageId = getCurPageId();

	if (pageId == PAGE_BLUETOOTH_MAIN ||
		pageId == PAGE_BLUETOOTH_AUDIOVOX_CODE ||
		pageId == PAGE_BLUETOOTH_AUDIOVOX_PAIR_FALSE ||
		pageId == PAGE_BLUETOOTH_AUDIOVOX_SEARCH ||
		pageId == PAGE_BLUETOOTH_AUDIOVOX_CONTACTS ||
		pageId == PAGE_BLUETOOTH_AUDIOVOX_BEYBOARD ||
		pageId == PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME ||
		pageId == PAGE_BLUETOOTH_AUDIOVOX_PAIR_SETTING ||
		pageId == PAGE_BLUETOOTH_AUDIOVOX_BTNAME_EDITOR
		)
	{
		bRet = true;
	}

	return bRet;
}

bool CBtModule::isBtDeviceSearchFinish(void)
{
	bool bRet = false;

	bRet = ((m_pBtParam->m_eBtDeviceSearchStatus == BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH) ? true : false);
	LOGD("[%s] bRet = [%s]", __FUNCTION__,  bRet ? "yes" : "no");

	return bRet;
}

E_BT_PHONE_STATUS CBtModule::getBtPhoneStatus(void)
{
	LOGD("[%s] m_ePhoneStatus = [%s]", __FUNCTION__,  getBtPhoneStatusString(m_pBtParam->m_ePhoneStatus));

	return m_pBtParam->m_ePhoneStatus;
}

void CBtModule::setPhoneStatus(E_BT_PHONE_STATUS e)
{
	LOGD("[%s] m_ePhoneStatus = [%s]", __FUNCTION__,  getBtPhoneStatusString(e));

	m_pBtParam->m_ePhoneStatus = e; 
}
//
E_HFP_CONNECT_STATUS CBtModule::getBtConnectStatus(void)
{
	LOGD("[%s] m_eHfpConnectStatus = [%s]", __FUNCTION__,  getBtConnectStatusString(m_pBtParam->m_eHfpConnectStatus));
	return  m_pBtParam->m_eHfpConnectStatus;
}

//�߼�������״̬
bool CBtModule::isCanCtrlMainPageFirstLayerWidget()
{
	bool bRet = true;

	switch(getBtPhoneStatus())
	{
	case BT_PHONE_STATUS_FREE:
		bRet = true;
		break;
	case BT_PHONE_STATUS_CALL_IN:
		bRet = false;
		break;
	case BT_PHONE_STATUS_CALL_OUT:
		bRet = false;
		break;
	case BT_PHONE_STATUS_TALKING:
		bRet = true;
		break;
	case PHONE_STATUS_CALL_OUTING:
		bRet = false;
		break;
	case PHONE_STATUS_UNKNOW:
		bRet = true;
		break;
	default:
		break;
	}
	
	LOGD("[%s] bRet = [%s]", __FUNCTION__,  bRet ? "Yes" : "No");

	return bRet;
}

const char* CBtModule::getBtPhoneStatusString(E_BT_PHONE_STATUS e)
{
	const char *pRet = "INIT_VALUE";

	switch(e)
	{
	case BT_PHONE_STATUS_FREE:
		pRet = "BT_PHONE_STATUS_FREE";
		break;
	case BT_PHONE_STATUS_CALL_OUT:
		pRet = "BT_PHONE_STATUS_CALL_OUT";
		break;
	case BT_PHONE_STATUS_CALL_IN:
		pRet = "BT_PHONE_STATUS_CALL_IN";
		break;
	case BT_PHONE_STATUS_TALKING:
		pRet = "BT_PHONE_STATUS_TALKING";
		break;
	case BT_PHONE_STATUS_CALL_IN_FROM_THIRD:
		pRet = "BT_PHONE_STATUS_CALL_IN_FROM_THIRD";
		break;
	case BT_PHONE_STATUS_HAND_UP:
		pRet = "BT_PHONE_STATUS_HAND_UP";
		break;
	case BT_PHONE_STATUS_RECEIVE_BULETOOTH:
		pRet = "BT_PHONE_STATUS_RECEIVE_BULETOOTH";
		break;
	case BT_PHONE_STATUS_RECEIVE_PHONE:
		pRet = "BT_PHONE_STATUS_RECEIVE_PHONE";
		break;
	default:
		pRet = "UNKNOW";
		break;
	}

	return pRet;
}

const char* CBtModule::getBtConnectStatusString(E_HFP_CONNECT_STATUS e)
{
	const char *pRet = "INIT_VALUE";

	switch(e)
	{
	case HFP_CONNECT_STATUS_DISCONNECT:
		pRet = "HFP_CONNECT_STATUS_DISCONNECT";
		break;
	case HFP_CONNECT_STATUS_CONNECTED:
		pRet = "HFP_CONNECT_STATUS_CONNECTED";
		break;
	case HFP_CONNECT_STATUS_CONNECTING:
		pRet = "HFP_CONNECT_STATUS_CONNECTING";
		break;
	}

	return pRet;
}

void CBtModule::btToApp_SendConnectState(unsigned char state)
{
	LOGD("[%s] state:%x",__FUNCTION__,state);
	u8 param[] = {0x3d, 0x01,0x00};
	if(state==0x01)
	{
		param[2]=0x01;
	}
	
	m_pBtApp->makeAndSendMessageToUI(0x00000000, UI_CONTROL_TYPE_PARAMSET, param, 3);

}


int CBtModule::nativeTimerHandlerProcess(timer_t timerId)
{
	long int ID = 0;
	ID = (long int)timerId;
	switch(ID)
	{
		case TIMER_DELAY_CONNECTION_DEVICE_PAGE_TIME:
			{
				if(HFP_CONNECT_STATUS_DISCONNECT == m_pBtModule->getBtConnectStatus())
					g_pClsBtAdapter->btInitiativeConnectDevice(m_pBtParam->selecteDeviceAddr,m_pBtParam->selecteDeviceAddrLen );
			}
			break;
		case TIMER_ACC_ON_BT_INIT:
			g_pClsBtAdapter->btInitCommand();
			break;
		case TIMER_ACC_OFF_BT_OFF:
			StandbyOff_Time();
			break;
			default:break;
	}
	return 0;
}

void CBtModule::getSystemMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__,  "p", p, len); 

	switch(p[0])
	{
	case 0x15:
		{
			getStandByStatus(p[1],0);
		}
	break;
	case 0x2e:
	    SystemDecodingProblemToUiDisplay((char*)&p[1],len-1);
	break;
	case 0xE3:// Page Change
		m_pBtApp->m_pBtDevicePages->getSystemParam_changePage(p+1);
	break;
	default:
		break;
	}
}

void CBtModule::getAudioChannelChange(u8 param)
{
	LOGD("[%s] m_pBtParam->m_eHfpConnectStatus = %d",__FUNCTION__,m_pBtParam->m_eHfpConnectStatus);
	if(param == 0x0D)//A2DP
	{
		 if(m_pBtParam->m_eHfpConnectStatus == HFP_CONNECT_STATUS_CONNECTED)
		 {	 
			 g_pClsBtAdapter->A2dpAudioOutputCtrlSwitch(0x01);
			 m_pBtApp->m_pA2DPpages->setA2DPPlay(); 
		 } 
	}
	else
	{
		 if(m_pBtParam->m_eHfpConnectStatus == HFP_CONNECT_STATUS_CONNECTED)
		 {
		 	g_pClsBtAdapter->A2dpAudioOutputCtrlSwitch(0x00);
			m_pBtApp->m_pA2DPpages->setA2DPPause();
		 }
	}
}

void CBtModule::getAudioMuteState(u8 param)
{
	if(param == 0x00)
	{
		m_pBtParam->muteSwicthState = false;
		m_pBtApp->setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MUTE,0);
		
	}
	else if(param == 0x01)
	{
		m_pBtParam->muteSwicthState = true;
		m_pBtApp->setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MUTE,1);
	}
}


void CBtModule::getAudioVideoMessage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x00://audiochannel
			getAudioChannelChange(p[1]);
		break;
		case 0x01://audiomute
			getAudioMuteState(p[1]);
		break;
		default:
		break;
	}
}

void CBtModule::getKeyMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__,  "p", p, len); 

	if(p[0] != 0)
		return;
	switch(p[1])
	{
	case 0x02: 
		setPage(PAGE_MEDIA);
		break;
	case 0x03://AV
		{
			if(!m_pBtModule->isSupportA2DP())
			{
				setNextModule(); 
				return;
			}
			
			u16 CurPageID = 0;
			u8 CurPageIDLen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen); 
			if(CurPageID != PAGE_BLUETOOTH_A2DP)
			{
				setPage(PAGE_BLUETOOTH_A2DP);
				return;
			}
			setNextModule();  
		}
		break;
	case 0x38: //SEEK+
		{
			m_pBtApp->m_pA2DPpages->setA2DPPageNext();
			LOGD("NEXT SONG");
		}
		break;
	case 0x39: //SEEK-
		{
			m_pBtApp->m_pA2DPpages->setA2DPPagePrev();
			LOGD("PRE SONG");
		}
		break;
	case 0x31: //Call
		m_pBtApp->m_pBtMainPage->clickAnswer(MOUSE_STATUS_UP);
		break;
	case 0x32: //Call Reject
		m_pBtApp->m_pBtMainPage->clickHandup(MOUSE_STATUS_UP);
		break;
	case 0x46://KEY_CALL_OUT
	case 0x47://KEY_CALL_INOUT
	    PanelKey_Switch_CallFunction();
		break;
	case 0x3B:		//TUNE+: 0x3B
		m_pBtApp->m_pA2DPpages->setA2DPPageNext();
		break;
	case 0x3C:		//TUNE-: 0x3C
		m_pBtApp->m_pA2DPpages->setA2DPPagePrev();
		break;
	default:break;
	}
}

void CBtModule::getExternalctrlMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__,  "p", p, len); 
	
	if(p[0] == 0x01)
	{
		if(p[1] == 0x01 && p[2] == 0x00)
		{
			m_pBtParam->bSpecialCaseBackPage = true;
			setPage(PAGE_BLUETOOTH_MAIN); 
		}
		else if(p[1] == 0x01 && p[2] == 0x01)
		{
			if(!m_pBtModule->isSupportA2DP()){
				setPage(PAGE_BLUETOOTH_NO_A2DP);
				return;
			}	
			
			setPage(PAGE_BLUETOOTH_A2DP);
		}
		else
		{
			setPrePage();
		} 
	}
	if(p[0]==0x02)
	{
		switch(p[1])
		{  
		case 0x01:
		    if(m_pBtParam->m_eHfpConnectStatus == HFP_CONNECT_STATUS_CONNECTED)
            {
            		int nLen = len - 2;
            		char cTemP[PHONE_NUm_nNPUT_MAX_SIZE];
					memset(cTemP,0,sizeof(cTemP));

					if(nLen > PHONE_NUm_nNPUT_MAX_SIZE)
						nLen = PHONE_NUm_nNPUT_MAX_SIZE;
					memcpy(cTemP,p+2,nLen);
					
            		memset(m_pBtParam->m_stPhoneNumInput.szcPhoneNum,0,sizeof(m_pBtParam->m_stPhoneNumInput.szcPhoneNum));
					m_pBtParam->m_stPhoneNumInput.dwLen = 0;

					
					m_pBtHal->deleteSpecialCharacters(cTemP,'-');
					memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum,cTemP,strlen(cTemP));
				    m_pBtParam->m_stPhoneNumInput.dwLen = strlen(m_pBtParam->m_stPhoneNumInput.szcPhoneNum);
				    m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);


            		m_pBtApp->m_pBtMainPage->clickAnswer(MOUSE_STATUS_UP);
            }
			break;
		case 0x02:
			//appToBT_GetAllBtPhoneBook();
			break;
		case 0x03:
		    m_pBtApp->m_pBtMainPage->clickBtPower(MOUSE_STATUS_UP);
		    break;
		}

	}
	
}
void CBtModule::getExtcarMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__,  "p", p, len); 

	switch(p[0])
    {
    	case 0x81://golf
    	{
             switch(p[1])
             {
             	case 0x50:
                     golf_dialNum((char*)p + 2, len - 2);
                     break;
              case 0x51:
                     golf_baseCtrl(p + 2, len - 2);
                     break;
               case 0x52:
                     golf_getPhoneBook(p + 2, len - 2);
                     break;
             }
    	}
       break;
	}
}
void CBtModule::getGpsMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__,  "p", p, len); 
	switch(p[0])
    {
        case 0x00:
            if(p[1] == 0x30)
            {
                GPS_aboutCareLand_PTT(&p[2],len-2);
            }
        break;
        case 0x01:
            if(p[1] == 0xE0)
            {
                LOGD("[%s] LanguageToBT:%x ,m_pBtParam->m_nBtLanguageType:%d",__FUNCTION__,p[2],m_pBtParam->m_nBtLanguageType);

                m_pBtParam->m_nBtLanguageType = p[2];

				 
				  switch(m_pBtParam->m_nBtLanguageType)
				  {
				  		case 0x00://CN
				  		case 0x01://EN
							m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ENGLISH;
						break;
						case 0x02://Russian
							m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_RUSSIA;
						break;
						case 0x03://Arabic
							m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ARAB;
						break;
						case 0x04://Hebrew
							m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ISRAEL;
						break;
						default:
							m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ENGLISH;
						break;
					}
					
                
                if((p[2] == 0 && m_pBtParam->m_nBtLanguageType != 0) || (p[2] != 0 && m_pBtParam->m_nBtLanguageType == 0))
                {    
                        if(m_pBtParam->m_eHfpConnectStatus == HFP_CONNECT_STATUS_DISCONNECT)
                            return;
                }
            }
        break;
        default:break;
	}
	
}
void CBtModule::getCenterMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__,  "p", p, len); 
	switch(p[0])
    {
        case 0x00:
        getStandByStatus(p[1],1);
        break;
		 case 0x01:
		 getSimPhoneStatus(p[1]);
		 break;
        default:break;
    }
	
}
void CBtModule::getAutoMateMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__,  "p", p, (u8)len); 
    switch(p[0])
    {
       case 0xff:
			autoMateUIMessage(&p[1], len-1);
       break;
       case 0x00:
        if(p[1] == 0x01)
		 {
			g_pClsBtAdapter->setBtPincode((u8 *)"0000",4);
        }
        break;
		case 0x01:
		{
			
			if(p[1] == 0x01)
			{
				//m_pBtApp->m_pBtDevicePages->clickDevicePairDialogBoxOK();
			}
			else if(p[1] == 0x00)
			{
				//m_pBtApp->m_pBtDevicePages->clickDevicePairDialogBoxChance();
			}
		}
		break;
    }  
	
}

void CBtModule::autoMateUIMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__,  "p", p, (u8)len); 
	u32 id = 0;
	E_MOUSE_STATUS e = MOUSE_STATUS_UNKNOW;
	u8 paramLen = 0;
	u8 *pParam = NULL;
	
	id += (u32)((p[0] << 24) & 0xFF000000);
	id += (u32)((p[1] << 16) & 0xFF0000);
	id += (u32)((p[2] << 8)  & 0xFF00);
	id += (u32)(p[3]		 & 0xFF);
	
	e = (E_MOUSE_STATUS)p[4];
	paramLen = len - 5;
	pParam = p + 5;
	 
	m_pBtApp->processMouseMsg(id, e,pParam, paramLen); 
}

void CBtModule::getSimPhoneStatus(u8 param)
{
	if(param != 0)
	{
		//m_pBtHal->SetToBtModeAboutA2dpMusicSoundExport(1);
	}
	else
	{
		//m_pBtHal->SetToBtModeAboutA2dpMusicSoundExport(0);
	}
}

void CBtModule::getStandByStatus(u8 param,u8 uIsAccOff)
{
	//static bool bStandBYPower = true;
	LOGD("[%s] ",__FUNCTION__);
	printf("[BT] [%s] param:%d\n",__FUNCTION__,param);
	if (param == 0x00)//ACC on
	{
		unsigned char ucSleepState = 0;
		unsigned char ucSleepStateLen = 0;
		getOtherModuleParam(MODULE_ID_SYSTEM,SLEEP_STATE,&ucSleepState,&ucSleepStateLen);
		m_pBtModule->deleteNativeTimer(TIMER_ACC_OFF_BT_OFF);
		
		LOGD("[BT] [%s] ucSleepState:%d\n",__FUNCTION__,ucSleepState);
		if(ucSleepState == 1 )
		{
			return;
		}
		
		if(uIsAccOff == 1)
		{
			if(!m_pBtParam->m_bIsPowerOn)
			{
			   	m_pBtHal->setToHalInit();
			}

			m_pBtParam->bStandBYPower = true;
			return;
		}

		if(m_pBtParam->m_bFirstStart && !m_pBtParam->m_bIsPowerOn)
		{
			m_pBtParam->m_bFirstStart = false;
			return;
		}

		if(!m_pBtParam->bStandBYPower)
		{
			m_pBtHal->setToHalInit();
			m_pBtParam->bStandBYPower = true;
			
		}
		m_pBtParam->m_bFirstStart = false;
	}
	else if(param == 0x01)//ACC off
	{
		printf("[BT] [%s] m_pBtParam->m_bIsPowerOn:%d\n",__FUNCTION__,m_pBtParam->m_bIsPowerOn);
		if(m_pBtParam->m_bIsPowerOn)
		{
			setStandbyOff_Time();
			/*
				printf("[BT] [%s] m_pBtParam->m_eHfpConnectStatus:%d\n",__FUNCTION__,m_pBtParam->m_eHfpConnectStatus);
				if(m_pBtParam->m_eHfpConnectStatus == HFP_CONNECT_STATUS_CONNECTED)
				{
					if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_TALKING){
						if(m_pBtParam->m_eHfpAudioSource == HFP_AUDIO_SOURCE_BT){
							g_pClsBtAdapter->btAnswerformCarOrPhone(0x01);
							usleep(1000*1000);
						}
					}

					if(m_pBtParam->m_bIsA2dpOnPlayState == true){
						m_pBtApp->m_pA2DPpages->setA2DPPause();
						usleep(1000*100);
					}

					g_pClsBtAdapter->btInitiativeDisconnection((u8 *)m_pBtParam->szRemodeBtDeviceHasConnectedAddr,strlen(m_pBtParam->szRemodeBtDeviceHasConnectedAddr));
				}

				usleep(1000*400);
				
				m_pBtHal->setToHalBtPower(0x00);
				bStandBYPower = false;
				m_pBtParam->m_bFirstStart = false;
			*/
		}
		
		LOGD("[%s]m_pBtParam->m_bIsPowerOn=%d",__FUNCTION__,m_pBtParam->m_bIsPowerOn);
	}
}

void CBtModule::PanelKey_Switch_CallFunction()
{	
	LOGD("[%s] m_pBtParam->m_ePhoneStatus:%x",__FUNCTION__,m_pBtParam->m_ePhoneStatus);
	switch(m_pBtParam->m_ePhoneStatus)
	{
    	case BT_PHONE_STATUS_CALL_IN: //����
            m_pBtApp->m_pBtMainPage->clickAnswer(MOUSE_STATUS_UP);
    		break;
    	case BT_PHONE_STATUS_CALL_OUT: //ȥ��
    	case BT_PHONE_STATUS_TALKING: //ͨ����
    		{
				LOGD("[%s] m_pBtParam->nNationalDistinction:%d",__FUNCTION__,m_pBtParam->nNationalDistinction);
				if(m_pBtParam->nNationalDistinction == NATIONAL_ISRAEL)
				{
					u16 CurPageID = 0;
					u8	CurPageIDLen = 0;
					getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
					LOGD("[%s] CurPageID:%d",__FUNCTION__,CurPageID);
					if(CurPageID != PAGE_BLUETOOTH_MAIN && CurPageID != PAGE_BACK_NOVIDEO && CurPageID != PAGE_BACK_VIDEO)
					{
						m_pBtParam->bSpecialCaseBackPage = true;
	    				setPage(PAGE_BLUETOOTH_MAIN);
					}
				}
				else
				{
    				m_pBtApp->m_pBtMainPage->clickHandup(MOUSE_STATUS_UP);
				}
    		}
    		break;
    	default:
		{
			m_pBtParam->bSpecialCaseBackPage = true;
			setPage(PAGE_BLUETOOTH_MAIN);
    	}
    	break;
	}
}

void CBtModule::SystemDecodingProblemToUiDisplay(char *param,u8 len)
{
    u32 ctrlId=0;
    ctrlId += (int)param[0];
	ctrlId += (int)(param[1]*256);
	ctrlId += (int)(param[2]*256*256);
	ctrlId += (int)(param[3]*256*256*256);

	m_pBtApp->setUtf8String(ctrlId, (u8*)&param[4],len - 4);
}
void CBtModule::GPS_aboutCareLand_PTT(u8 *param,int len)
{
	LOGD("[%s] param:%s,len:%d",__FUNCTION__,param,len);
	if(m_pBtParam->m_eHfpConnectStatus == HFP_CONNECT_STATUS_CONNECTED)
	{
	    	btToCareLand_SendConnectState(0x01);
		if(len <= 0)
			return;
		m_pBtHal->deleteSpecialCharacters((char *)param,'-');
       		memset(m_pBtParam->m_stPhoneNumInput.szcPhoneNum,0, m_pBtParam->m_stPhoneNumInput.dwLen);
		m_pBtParam->m_stPhoneNumInput.dwLen = strlen((char *)param);
       		memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum,(char*)param,m_pBtParam->m_stPhoneNumInput.dwLen);
		
		m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
		m_pBtModule->getBtPhoneStatus();
		m_pBtApp->m_pBtMainPage->clickAnswer(MOUSE_STATUS_UP);
	}
	else
	{
		btToCareLand_SendConnectState(0x00);
	}

}
void CBtModule::btToCareLand_SendConnectState(unsigned char state)
{
	LOGD("[%s] connectState state:%x",__FUNCTION__,state);
	u8 param[] = {0x3d, 0x05,0x00};
	if(state==0x01)
	{
		param[2]=0x01;
	}
	m_pBtApp->setCommand(0x00000000,param, 3);
}


void CBtModule::SetAutoConnectDevice()
{
	int j = m_pBtParam->m_listBtDevicesHavePaired.size();
	if(j > 0)
	{
		//setNativeTimer(3500,0,TIMER_BC06_AUTOCONNECT);
		LOGD("[%s] ",__FUNCTION__);
	}
}

//---------------------------------------------------------------------------------------------

//////////////////////////// GOLF ///////////////////////////////////////

void CBtModule::golf_dialNum(char *p, int len)
{
	switch(m_pBtParam->m_ePhoneStatus)
	{
		case BT_PHONE_STATUS_FREE:
			break;
	case BT_PHONE_STATUS_CALL_OUT:
	case BT_PHONE_STATUS_CALL_IN:
	case BT_PHONE_STATUS_TALKING:
		return;
	}

	if (len < (int)sizeof(m_pBtParam->m_stPhoneNumInput.szcPhoneNum))
	{
		m_pBtParam->m_stPhoneNumInput.dwLen = len;
		memset((char*)m_pBtParam->m_stPhoneNumInput.szcPhoneNum, 0, sizeof((char*)m_pBtParam->m_stPhoneNumInput.szcPhoneNum));
		memcpy((char*)m_pBtParam->m_stPhoneNumInput.szcPhoneNum, p, len);
	}
	m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
	m_pBtModule->getBtPhoneStatus();
	if(!m_pBtParam->tempHideBtPage)
		setPage(PAGE_BLUETOOTH_MAIN);

	m_pBtApp->m_pBtMainPage->clickAnswer(MOUSE_STATUS_UP);
}

void CBtModule::golf_baseCtrl(u8 *p, int len)
{
	LOGD("[%s] %x %x",__FUNCTION__,p[0],p[1]);
	printf("[BT] [golf_baseCtrl] %x %x\n",p[0],p[1]);
	if (p[0] == 0x1E && p[1] == 0x00)
	{
		m_pBtApp->m_pBtMainPage->clickAnswer(MOUSE_STATUS_UP);
	}
	else if (p[0] == 0x22 && p[1] == 0x01)
	{
	}
	else if (p[0] == 0x22 && p[1] == 0x00)
	{
	}
	else if (p[0] == 0x21 && p[1] == 0x01)
	{
		//g_pClsBtBC6Adapter->setToBtChipVoiceSwitchToMobilePhone();
	}
	else if (p[0] == 0x21 && p[1] == 0x00)
	{
		//g_pClsBtBC6Adapter->setToBtChipVoiceSwitchToBtChip();
	}
	else if (p[0] == 0x1D && p[1] == 0x00)
	{
		m_pBtApp->m_pBtMainPage->clickHandup(MOUSE_STATUS_UP);
	}
	//else if (p[0] == 0x38 && p[1] == 0x01)
	else if (p[0] == 0x38 && p[1] == 0x00)
	{
		btToModule_NotifyCenter_StopRing();
	}
}

void CBtModule::golf_getPhoneBook_writeOneNum(ST_PHONE_NUM *pPhoneNum, u8 *szAns, int j, int &iAns)
{
	szAns[iAns] = (u8)pPhoneNum->dwLen, iAns += 1;
	memcpy((char*)(szAns + iAns),pPhoneNum->szcPhoneNum, pPhoneNum->dwLen);
	iAns += pPhoneNum->dwLen;

	char cY = 0;
	char cM = 0;
	char cD = 0;

	char cHour = 0;
	char cMin = 0;
	char cSec = 0;

	char cTY[3] = {0};
	char cTM[3] = {0};
	char cTD[3] = {0};
	char cTHour[3] = {0};
	char cTMin[3] = {0};
	char cTSec[3] = {0};

	memcpy(&cTY,pPhoneNum->szcTime + 2,2);
	memcpy(&cTM,pPhoneNum->szcTime + 4,2);
	memcpy(&cTD,pPhoneNum->szcTime + 6,2);
	memcpy(&cTHour,pPhoneNum->szcTime + 9,2);
	memcpy(&cTMin,pPhoneNum->szcTime + 11,2);
	memcpy(&cTSec,pPhoneNum->szcTime + 13,2);

	cY = (char)atoi(cTY);
	cM = (char)atoi(cTM);
	cD = (char)atoi(cTD);

	cHour = (char)atoi(cTHour);
	cMin = (char)atoi(cTMin);
	cSec = (char)atoi(cTSec);
	LOGD("golf_getPhoneBook_writeOneNumDate cY:%02d,cM:%02d,cD:%02d,cHour:%02d,cMin:%02d,cSec:%02d",cY,cM,cD,cHour,cMin,cSec);

	//szAns[iAns] = 6, iAns += 1;
	memcpy((char*)(szAns + iAns), &cD, 1);
	memcpy((char*)(szAns + iAns + 1),&cM, 1);
	memcpy((char*)(szAns + iAns + 2),&cY, 1);
	memcpy((char*)(szAns + iAns + 3),&cHour, 1);
	memcpy((char*)(szAns + iAns + 4),&cMin, 1);
	memcpy((char*)(szAns + iAns + 5),&cSec, 1);

	iAns += 6;

	outPutLog(__FUNCTION__,  "Date szAns:", szAns, iAns);
	
	LOGD(">>>>>>>>>>>>>>>>>");
}

void CBtModule::golf_getPhoneBook_writeOneNumMsg(int nSetTotalCount,u8 *szAns, int j, int nInCount, int nOutCount, int nMissCount,int &iAns)
{
	LOGD("<<<<<<<<<  j = [%d],nSetTotalCount:%d,nInCount = [%d],nOutCount = [%d],nMissCount = [%d],iAns = [%d]",j,nSetTotalCount,nInCount,nOutCount,nMissCount,iAns);
	szAns[iAns] = j, iAns += 1;
	m_pBtParam->cUpdataPhoneBookCountIndex = j;
	
	j -= 1;
	int k = 0;
	if (j >= 0 && nInCount > 0 && (j <= (nInCount - 1)))
	{			
		k = nInCount - 1 - j;
		LOGD("Riceived k:%d j:%d",k,j);

		int x = 0;
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Riceived).begin();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Riceived).end();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
			
		for (it = itFrom; it != itTo; it++)
		{
			if (x == k)
				break;
			x++;
		}
		
		ST_PHONE_NUM phoneNum;
		memset(&phoneNum,0,sizeof(ST_PHONE_NUM));

		memcpy(phoneNum.szcName,it->szUserName, strlen(it->szUserName));
		phoneNum.dwNameLen = strlen(it->szUserName);
		//szAns[iAns] = (u8)phoneNum.dwNameLen;
		LOGD("Riceived phoneNum.szcName,phoneNum.dwNameLen %s %d",phoneNum.szcName,phoneNum.dwNameLen);
		
		memcpy(phoneNum.szcPhoneNum,it->szUserNo, strlen(it->szUserNo));
		phoneNum.dwLen = strlen(it->szUserNo);
		LOGD("Riceived phoneNum.szcPhoneNum,phoneNum.dwLen %s %d",phoneNum.szcPhoneNum,phoneNum.dwLen);
		
		memcpy(phoneNum.szcTime,it->CBTime, strlen(it->CBTime));
		phoneNum.dwTimeLen = strlen(it->CBTime);
		LOGD("Riceived phoneNum.szcTime,phoneNum.dwTimeLen %s %d",phoneNum.szcTime,phoneNum.dwTimeLen);
		
		if(phoneNum.dwNameLen == 0)
		{
			szAns[iAns] = phoneNum.dwLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcPhoneNum, phoneNum.dwLen);
			iAns += phoneNum.dwLen;
		}
		else
		{
			szAns[iAns] = phoneNum.dwNameLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcName, phoneNum.dwNameLen);
			iAns += phoneNum.dwNameLen;
		}


		szAns[iAns] = 3, iAns += 1;
		outPutLog(__FUNCTION__,  "szAns:", szAns, iAns);
		golf_getPhoneBook_writeOneNum(&phoneNum, szAns, j, iAns);
	}
	else if(j >= 0 && nOutCount > 0 && (j <= (nInCount + nOutCount - 1)))
	{
		k = j - nInCount;
		k = nOutCount - 1 - k;
		LOGD("Dialed k:%d j:%d",k,j);

		int x = 0;
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Dialed).begin();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Dialed).end();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
			
		for (it = itFrom; it != itTo; it++)
		{
			if (x == k)
				break;
			x++;
		}
		
		ST_PHONE_NUM phoneNum;
		memset(&phoneNum,0,sizeof(ST_PHONE_NUM));

		memcpy(phoneNum.szcName,it->szUserName, strlen(it->szUserName));
		phoneNum.dwNameLen = strlen(it->szUserName);
		//szAns[iAns] = phoneNum.dwNameLen;
		LOGD("Dialed phoneNum.szcName,phoneNum.dwNameLen %s %d",phoneNum.szcName,phoneNum.dwNameLen);
		
		memcpy(phoneNum.szcPhoneNum,it->szUserNo, strlen(it->szUserNo));
		LOGD("Dialed it->szUserNo,Len %s %d",it->szUserNo,strlen(it->szUserNo));
		phoneNum.dwLen = strlen(it->szUserNo);
		LOGD("Dialed phoneNum.szcPhoneNum,phoneNum.dwLen %s %d",phoneNum.szcPhoneNum,phoneNum.dwLen);
		
		memcpy(phoneNum.szcTime,it->CBTime, strlen(it->CBTime));
		phoneNum.dwTimeLen = strlen(it->CBTime);
		LOGD("Dialed phoneNum.szcTime,phoneNum.dwTimeLen %s %d",phoneNum.szcTime,phoneNum.dwTimeLen);

		if(phoneNum.dwNameLen == 0)
		{
			szAns[iAns] = phoneNum.dwLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcPhoneNum, phoneNum.dwLen);
			iAns += phoneNum.dwLen;
		}
		else
		{
			szAns[iAns] = phoneNum.dwNameLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcName, phoneNum.dwNameLen);
			iAns += phoneNum.dwNameLen;
		}
		
		szAns[iAns] = 2, iAns += 1;
		golf_getPhoneBook_writeOneNum(&phoneNum, szAns, j, iAns);
	}
	else if(j >= 0 && nMissCount > 0 && (j <= (nInCount + nOutCount + nMissCount - 1)))
	{	
		k = j - nInCount - nOutCount;
		k = nMissCount - 1 - k;
		LOGD("Miss k:%d j:%d",k,j);
		
		int x = 0;
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Miss).begin();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Miss).end();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
			
		for (it = itFrom; it != itTo; it++)
		{
			if (x == k)
				break;
			x++;
		}
		
		ST_PHONE_NUM phoneNum;
		memset(&phoneNum,0,sizeof(ST_PHONE_NUM));

		memcpy(phoneNum.szcName,it->szUserName, strlen(it->szUserName));
		phoneNum.dwNameLen = strlen(it->szUserName);
		//szAns[iAns] = phoneNum.dwNameLen;
		LOGD("Miss phoneNum.szcName,phoneNum.dwNameLen %s %d",phoneNum.szcName,phoneNum.dwNameLen);
		
		memcpy(phoneNum.szcPhoneNum,it->szUserNo, strlen(it->szUserNo));
		phoneNum.dwLen = strlen(it->szUserNo);
		LOGD("Miss phoneNum.szcPhoneNum,phoneNum.dwLen %s %d",phoneNum.szcPhoneNum,phoneNum.dwLen);

		memcpy(phoneNum.szcTime,it->CBTime, strlen(it->CBTime));
		phoneNum.dwTimeLen = strlen(it->CBTime);
		LOGD("Miss phoneNum.szcTime,phoneNum.dwTimeLen %s %d",phoneNum.szcTime,phoneNum.dwTimeLen);
		
		if(phoneNum.dwNameLen == 0)
		{
			szAns[iAns] = phoneNum.dwLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcPhoneNum, phoneNum.dwLen);
			iAns += phoneNum.dwLen;
		}
		else
		{
			szAns[iAns] = phoneNum.dwNameLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcName, phoneNum.dwNameLen);
			iAns += phoneNum.dwNameLen;
		}

		szAns[iAns] = 1, iAns += 1;
		golf_getPhoneBook_writeOneNum(&phoneNum, szAns, j, iAns);
	}
}


void CBtModule::golf_getPhoneBook_writeOneNumMsgoo(int nTotalCount,u8 *szAns, int j, int nInCount, int nOutCount, int nMissCount,int &iAns)
{
	LOGD("[%s] j = [%d],nInCount = [%d],nOutCount = [%d],nMissCount = [%d],iAns = [%d]",__FUNCTION__,j,nInCount,nOutCount,nMissCount,iAns);
	szAns[iAns] = j, iAns += 1;
	
	j -= 1;
	int k = 0;
	if (j >= 0 && nInCount > 0 && j < nInCount)
	{			
		k = nInCount - 1 - j;
		LOGD("Riceived k:%d j:%d",k,j);

		int x = 0;
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Riceived).begin();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Riceived).end();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
			
		for (it = itFrom; it != itTo; it++)
		{
			if (x == k)
				break;
			x++;
		}
		
		ST_PHONE_NUM phoneNum;
		memset(&phoneNum,0,sizeof(ST_PHONE_NUM));

		memcpy(phoneNum.szcName,it->szUserName, strlen(it->szUserName));
		phoneNum.dwNameLen = strlen(it->szUserName);
		//szAns[iAns] = (u8)phoneNum.dwNameLen;
		LOGD("Riceived phoneNum.szcName,phoneNum.dwNameLen %s %d",phoneNum.szcName,phoneNum.dwNameLen);
		
		memcpy(phoneNum.szcPhoneNum,it->szUserNo, strlen(it->szUserNo));
		phoneNum.dwLen = strlen(it->szUserNo);
		LOGD("Riceived phoneNum.szcPhoneNum,phoneNum.dwLen %s %d",phoneNum.szcPhoneNum,phoneNum.dwLen);
		
		memcpy(phoneNum.szcTime,it->CBTime, strlen(it->CBTime));
		phoneNum.dwTimeLen = strlen(it->CBTime);
		LOGD("Riceived phoneNum.szcTime,phoneNum.dwTimeLen %s %d",phoneNum.szcTime,phoneNum.dwTimeLen);
		
		if(phoneNum.dwNameLen == 0)
		{
			szAns[iAns] = phoneNum.dwLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcPhoneNum, phoneNum.dwLen);
			iAns += phoneNum.dwLen;
		}
		else
		{
			szAns[iAns] = phoneNum.dwNameLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcName, phoneNum.dwNameLen);
			iAns += phoneNum.dwNameLen;
		}


		szAns[iAns] = 3, iAns += 1;
		outPutLog(__FUNCTION__,  "szAns:", szAns, iAns);
		golf_getPhoneBook_writeOneNum(&phoneNum, szAns, j, iAns);
	}
	else if(j >= 0 && nOutCount > 0 && j < nOutCount)
	{
		//k = j - nInCount;
		//k = nOutCount - 1 - k;
		k = nOutCount - 1 - j;
		LOGD("Dialed k:%d j:%d",k,j);

		int x = 0;
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Dialed).begin();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Dialed).end();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
			
		for (it = itFrom; it != itTo; it++)
		{
			if (x == k)
				break;
			x++;
		}
		
		ST_PHONE_NUM phoneNum;
		memset(&phoneNum,0,sizeof(ST_PHONE_NUM));

		memcpy(phoneNum.szcName,it->szUserName, strlen(it->szUserName));
		phoneNum.dwNameLen = strlen(it->szUserName);
		//szAns[iAns] = phoneNum.dwNameLen;
		LOGD("Dialed phoneNum.szcName,phoneNum.dwNameLen %s %d",phoneNum.szcName,phoneNum.dwNameLen);
		
		memcpy(phoneNum.szcPhoneNum,it->szUserNo, strlen(it->szUserNo));
		LOGD("Dialed it->szUserNo,Len %s %d",it->szUserNo,strlen(it->szUserNo));
		phoneNum.dwLen = strlen(it->szUserNo);
		LOGD("Dialed phoneNum.szcPhoneNum,phoneNum.dwLen %s %d",phoneNum.szcPhoneNum,phoneNum.dwLen);
		
		memcpy(phoneNum.szcTime,it->CBTime, strlen(it->CBTime));
		phoneNum.dwTimeLen = strlen(it->CBTime);
		LOGD("Dialed phoneNum.szcTime,phoneNum.dwTimeLen %s %d",phoneNum.szcTime,phoneNum.dwTimeLen);

		if(phoneNum.dwNameLen == 0)
		{
			szAns[iAns] = phoneNum.dwLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcPhoneNum, phoneNum.dwLen);
			iAns += phoneNum.dwLen;
		}
		else
		{
			szAns[iAns] = phoneNum.dwNameLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcName, phoneNum.dwNameLen);
			iAns += phoneNum.dwNameLen;
		}
		
		szAns[iAns] = 2, iAns += 1;
		golf_getPhoneBook_writeOneNum(&phoneNum, szAns, j, iAns);
	}
	else if(j >= 0 && nMissCount > 0 && j < nMissCount)
	{	
		//k = j - nInCount - nOutCount;
		//k = (nInCount + nOutCount) - 1 - k;
		k = nMissCount - 1 - j;
		LOGD("Miss k:%d j:%d",k,j);
		
		int x = 0;
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Miss).begin();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Miss).end();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
			
		for (it = itFrom; it != itTo; it++)
		{
			if (x == k)
				break;
			x++;
		}
		
		ST_PHONE_NUM phoneNum;
		memset(&phoneNum,0,sizeof(ST_PHONE_NUM));

		memcpy(phoneNum.szcName,it->szUserName, strlen(it->szUserName));
		phoneNum.dwNameLen = strlen(it->szUserName);
		//szAns[iAns] = phoneNum.dwNameLen;
		LOGD("Miss phoneNum.szcName,phoneNum.dwNameLen %s %d",phoneNum.szcName,phoneNum.dwNameLen);
		
		memcpy(phoneNum.szcPhoneNum,it->szUserNo, strlen(it->szUserNo));
		phoneNum.dwLen = strlen(it->szUserNo);
		LOGD("Miss phoneNum.szcPhoneNum,phoneNum.dwLen %s %d",phoneNum.szcPhoneNum,phoneNum.dwLen);

		memcpy(phoneNum.szcTime,it->CBTime, strlen(it->CBTime));
		phoneNum.dwTimeLen = strlen(it->CBTime);
		LOGD("Miss phoneNum.szcTime,phoneNum.dwTimeLen %s %d",phoneNum.szcTime,phoneNum.dwTimeLen);
		
		if(phoneNum.dwNameLen == 0)
		{
			szAns[iAns] = phoneNum.dwLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcPhoneNum, phoneNum.dwLen);
			iAns += phoneNum.dwLen;
		}
		else
		{
			szAns[iAns] = phoneNum.dwNameLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcName, phoneNum.dwNameLen);
			iAns += phoneNum.dwNameLen;
		}

		szAns[iAns] = 1, iAns += 1;
		golf_getPhoneBook_writeOneNum(&phoneNum, szAns, j, iAns);
	}
}

void CBtModule::golf_getPhoneBook(u8 *p, int len)
{
	if (!(p[1] == 0x1A && p[2] == 0x31))
		return;

	int nDataLen = p[0];
	if (nDataLen < 4)
		return;

	int iAns = 0;
	int nInCount = m_pBtParam->m_listHistoryCall_Riceived.size();
	int nOutCount = m_pBtParam->m_listHistoryCall_Dialed.size();
	int nMissCount = m_pBtParam->m_listHistoryCall_Miss.size();
	//int nAllCount = nInCount + nOutCount;
	int nAllCount = nInCount + nOutCount + nMissCount;
	nAllCount = (nAllCount > GOLF_CAR_SCREEN_PHONE_BOOK_ITEM_NUM) ? (GOLF_CAR_SCREEN_PHONE_BOOK_ITEM_NUM) : (nAllCount);
	int nSetAllCount = (nAllCount < p[6]) ? nAllCount : p[6];
	
	u8 szAns[256] = {0};
	szAns[0] = 0x81;
	szAns[1] = 0x00;
	szAns[2] = 0x5A;
	szAns[3] = 0x00;
	szAns[4] = 0x4A;
	szAns[5] = 0x31;
	szAns[6] = p[3];
	szAns[7] = nAllCount;
	szAns[8] = 0x40 + p[4];
	szAns[9] = p[5];
	szAns[10] = nSetAllCount;
	iAns = 11;
	
	int i = p[5];
	int n = p[6];
	int nFrom = 0, nTo = 0;
	if (p[4] == 0x30 || p[4] == 0xB0)
	{
		if (i == 0)
		{
			nFrom = nAllCount;
			nTo = nAllCount - n + 1;
		}
		else
		{
			nFrom = i - 1;
			nTo = i - n;
		}
	}
	else if (p[4] == 0x00 || p[4] == 0x10 || p[4] == 0x90)
	{
		nFrom = i + 1;
		nTo = i + n;
	}
	else if(p[4] == 0x3F)
	{
		szAns[11] = m_pBtParam->cUpdataPhoneBookCountIndex;
		iAns = 12;
	}

	LOGD("++++++++++ nFrom = %d, nTo = %d, p[3] = [%X], p[4] = [%X], p[5] = [%X], p[6] = [%d] nAllCount = [%d]", nFrom, nTo, p[3], p[4], p[5], p[6],nAllCount);

	if (nFrom < 0)
		nFrom = 1;
	if (nFrom > nAllCount )
		nFrom = nAllCount;
	if (nTo < 0)
		nTo = 1;
	if (nTo >= nAllCount )
		nTo = nAllCount;

	if (nAllCount > 0)
	{
		int j = 0;
		if (p[4] == 0x30 || p[4] == 0xB0)
		{
			LOGD("p[4] == 0x30 nFrom,nTo:%d %d",nFrom,nTo);
			for (j = nFrom; j >= nTo; j--)
			{
				golf_getPhoneBook_writeOneNumMsg(nSetAllCount,szAns, j, nInCount, nOutCount, nMissCount, iAns);
			}
		}
		else if (p[4] == 0x00 || p[4] == 0x10 || p[4] == 0x90)
		{
			LOGD("p[4] == 0x00 || p[4] == 0x10    nFrom,nTo:%d %d",nFrom,nTo);
			int y = 0;
			for (j = nFrom; j <= nTo; j++)
			{
				golf_getPhoneBook_writeOneNumMsg(nSetAllCount,szAns, j, nInCount, nOutCount, nMissCount, iAns);
				/*
				if(nInCount > 0 && j <= nInCount){
					y = golf_getPhoneBook_writeRiceived(nTo,u8 *szAns, int j,int nInCount,iAns);
				}

				if(nOutCount > 0 && (nTo - nInCount) > 0){
					y = golf_getPhoneBook_writeDialed(nTo,u8 *szAns, int j, int nOutCount,iAns);
				}

				if(nMissCount > 0 && (nTo - nInCount - nOutCount) > 0){
					y = golf_getPhoneBook_writeMiss(nTo,u8 *szAns, int j,int nMissCount,iAns);
				}*/
			}
		}
	}
	outPutLog(__FUNCTION__,  "szAns:", szAns, iAns);

	szAns[3] = iAns - 6;
	btToModule_golf_phoneNumListOfDialOutAndDialIn(szAns, iAns);

}

int CBtModule::golf_getPhoneBook_writeRiceived(int nTotalCount,u8 *szAns, int j,int nInCount,int &iAns)
{
	LOGD("[%s] j = [%d],nTotalCount = [%d],nInCount = [%d],iAns = [%d]",__FUNCTION__,j,nTotalCount,nInCount,iAns);
	szAns[iAns] = j, iAns += 1;
	
	j -= 1;
	int k = 0;
	if (j >= 0)
	{			
		k = nInCount - 1 - j;
		LOGD("Riceived k:%d j:%d",k,j);

		int x = 0;
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Riceived).begin();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Riceived).end();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
			
		for (it = itFrom; it != itTo; it++)
		{
			if (x == k)
				break;
			x++;
		}
		
		ST_PHONE_NUM phoneNum;
		memset(&phoneNum,0,sizeof(ST_PHONE_NUM));

		memcpy(phoneNum.szcName,it->szUserName, strlen(it->szUserName));
		phoneNum.dwNameLen = strlen(it->szUserName);
		//szAns[iAns] = (u8)phoneNum.dwNameLen;
		LOGD("Riceived phoneNum.szcName,phoneNum.dwNameLen %s %d",phoneNum.szcName,phoneNum.dwNameLen);
		
		memcpy(phoneNum.szcPhoneNum,it->szUserNo, strlen(it->szUserNo));
		phoneNum.dwLen = strlen(it->szUserNo);
		LOGD("Riceived phoneNum.szcPhoneNum,phoneNum.dwLen %s %d",phoneNum.szcPhoneNum,phoneNum.dwLen);
		
		memcpy(phoneNum.szcTime,it->CBTime, strlen(it->CBTime));
		phoneNum.dwTimeLen = strlen(it->CBTime);
		LOGD("Riceived phoneNum.szcTime,phoneNum.dwTimeLen %s %d",phoneNum.szcTime,phoneNum.dwTimeLen);
		
		if(phoneNum.dwNameLen == 0)
		{
			szAns[iAns] = phoneNum.dwLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcPhoneNum, phoneNum.dwLen);
			iAns += phoneNum.dwLen;
		}
		else
		{
			szAns[iAns] = phoneNum.dwNameLen;
			iAns++;
			memcpy((char*)(szAns + iAns),phoneNum.szcName, phoneNum.dwNameLen);
			iAns += phoneNum.dwNameLen;
		}


		szAns[iAns] = 3, iAns += 1;
		outPutLog(__FUNCTION__,  "szAns:", szAns, iAns);
		golf_getPhoneBook_writeOneNum(&phoneNum, szAns, j, iAns);
	}

	return k;

}

int CBtModule::golf_getPhoneBook_writeDialed(int nTotalCount,u8 *szAns, int j, int nOutCount,int &iAns)
{
	LOGD("[%s] j = [%d],nTotalCount = [%d],nOutCount = [%d],iAns = [%d]",__FUNCTION__,j,nTotalCount,nOutCount,iAns);
	szAns[iAns] = j, iAns += 1;
	
	j -= 1;
	int k = 0;
	if(j >= 0)
		{
			//k = j - nInCount;
			//k = nOutCount - 1 - k;
			k = nOutCount - 1 - j;
			LOGD("Dialed k:%d j:%d",k,j);
	
			int x = 0;
			list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Dialed).begin();
			list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Dialed).end();
			list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
				
			for (it = itFrom; it != itTo; it++)
			{
				if (x == k)
					break;
				x++;
			}
			
			ST_PHONE_NUM phoneNum;
			memset(&phoneNum,0,sizeof(ST_PHONE_NUM));
	
			memcpy(phoneNum.szcName,it->szUserName, strlen(it->szUserName));
			phoneNum.dwNameLen = strlen(it->szUserName);
			//szAns[iAns] = phoneNum.dwNameLen;
			LOGD("Dialed phoneNum.szcName,phoneNum.dwNameLen %s %d",phoneNum.szcName,phoneNum.dwNameLen);
			
			memcpy(phoneNum.szcPhoneNum,it->szUserNo, strlen(it->szUserNo));
			LOGD("Dialed it->szUserNo,Len %s %d",it->szUserNo,strlen(it->szUserNo));
			phoneNum.dwLen = strlen(it->szUserNo);
			LOGD("Dialed phoneNum.szcPhoneNum,phoneNum.dwLen %s %d",phoneNum.szcPhoneNum,phoneNum.dwLen);
			
			memcpy(phoneNum.szcTime,it->CBTime, strlen(it->CBTime));
			phoneNum.dwTimeLen = strlen(it->CBTime);
			LOGD("Dialed phoneNum.szcTime,phoneNum.dwTimeLen %s %d",phoneNum.szcTime,phoneNum.dwTimeLen);
	
			if(phoneNum.dwNameLen == 0)
			{
				szAns[iAns] = phoneNum.dwLen;
				iAns++;
				memcpy((char*)(szAns + iAns),phoneNum.szcPhoneNum, phoneNum.dwLen);
				iAns += phoneNum.dwLen;
			}
			else
			{
				szAns[iAns] = phoneNum.dwNameLen;
				iAns++;
				memcpy((char*)(szAns + iAns),phoneNum.szcName, phoneNum.dwNameLen);
				iAns += phoneNum.dwNameLen;
			}
			
			szAns[iAns] = 2, iAns += 1;
			golf_getPhoneBook_writeOneNum(&phoneNum, szAns, j, iAns);
		}
	
		return k;
}

int CBtModule::golf_getPhoneBook_writeMiss(int nTotalCount,u8 *szAns, int j,int nMissCount,int &iAns)
{
	LOGD("[%s] j = [%d],nTotalCount = [%d],nMissCount = [%d],iAns = [%d]",__FUNCTION__,j,nTotalCount,nMissCount,iAns);
	szAns[iAns] = j, iAns += 1;
	
	j -= 1;
	int k = 0;
	if(j >= 0)
	{	
			//k = j - nInCount - nOutCount;
			//k = (nInCount + nOutCount) - 1 - k;
			k = nMissCount - 1 - j;
			LOGD("Miss k:%d j:%d",k,j);
			
			int x = 0;
			list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Miss).begin();
			list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Miss).end();
			list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
				
			for (it = itFrom; it != itTo; it++)
			{
				if (x == k)
					break;
				x++;
			}
			
			ST_PHONE_NUM phoneNum;
			memset(&phoneNum,0,sizeof(ST_PHONE_NUM));
	
			memcpy(phoneNum.szcName,it->szUserName, strlen(it->szUserName));
			phoneNum.dwNameLen = strlen(it->szUserName);
			//szAns[iAns] = phoneNum.dwNameLen;
			LOGD("Miss phoneNum.szcName,phoneNum.dwNameLen %s %d",phoneNum.szcName,phoneNum.dwNameLen);
			
			memcpy(phoneNum.szcPhoneNum,it->szUserNo, strlen(it->szUserNo));
			phoneNum.dwLen = strlen(it->szUserNo);
			LOGD("Miss phoneNum.szcPhoneNum,phoneNum.dwLen %s %d",phoneNum.szcPhoneNum,phoneNum.dwLen);
	
			memcpy(phoneNum.szcTime,it->CBTime, strlen(it->CBTime));
			phoneNum.dwTimeLen = strlen(it->CBTime);
			LOGD("Miss phoneNum.szcTime,phoneNum.dwTimeLen %s %d",phoneNum.szcTime,phoneNum.dwTimeLen);
			
			if(phoneNum.dwNameLen == 0)
			{
				szAns[iAns] = phoneNum.dwLen;
				iAns++;
				memcpy((char*)(szAns + iAns),phoneNum.szcPhoneNum, phoneNum.dwLen);
				iAns += phoneNum.dwLen;
			}
			else
			{
				szAns[iAns] = phoneNum.dwNameLen;
				iAns++;
				memcpy((char*)(szAns + iAns),phoneNum.szcName, phoneNum.dwNameLen);
				iAns += phoneNum.dwNameLen;
			}
	
			szAns[iAns] = 1, iAns += 1;
			golf_getPhoneBook_writeOneNum(&phoneNum, szAns, j, iAns);
	}

	return k;
}

void CBtModule::golf_sendToCarScreen_mobileOperatorName(u8 *p,int len)
{
	//char szName[] = "GOLF 7";
	btToModule_golf_mobileOperatorName(p, len);
}

void CBtModule::golf_sendToCarScreen_signalState(u8 p)
{
	u8 r = 0;
	int s = p;
	u8 szMap[6] = {0x00, 0x14, 0x28, 0x3C, 0x50, 0xFE};
	if (s >=0 && s <= 5)
		r = szMap[s];
	btToModule_golf_signalState(r);
}

void CBtModule::golf_sendToCarScreen_batteryStrength(u8 p)
{
	u8 r = 0;
	int s = p;
	u8 szMap[5] = {0x00, 0x14, 0x28, 0x3C, 0x50};
	if (s >=0 && s <= 4)
		r = szMap[s];
	btToModule_golf_batteryStrength(r);
}

void CBtModule::golf_sendToCarScreen_PhoneConnState(u8 p)
{
	if (p == 0)
	{
		btToModule_golf_blueConnectState(0x00, 0x00);
	}
	else
	{
		btToModule_golf_blueConnectState(0x04, 0x03);
	}
}

void CBtModule::golf_sendToCarScreen_PhoneState(u8 p)
{
	switch(p)
	{
	case 0://no
		btToModule_golf_phoneState(0x00, 0x00);
		break;
	case 1://dia in
		btToModule_golf_phoneState(0x11, 0x01);
		break;
	case 2://dia out
		btToModule_golf_phoneState(0x31, 0x00);
		break;
	case 3://calling
		btToModule_golf_phoneState(0x21, 0x00);
		break;
	}

}

void CBtModule::golf_sendToCarScreen_PhoneNumInTheSpecialState(u8 p, u8 *pNum, int nLen)
{
	if (1 == p || 2 == p || 3 == p)// send to car screen
	{
		if(nLen > PHONENUM_OR_PHONENAME_MAX_LEN - 1)
		{
			u8 buffer[PHONENUM_OR_PHONENAME_MAX_LEN];
			memset((char*)buffer, 0, sizeof(buffer));
			nLen = PHONENUM_OR_PHONENAME_MAX_LEN - 1;
			strncpy((char*)buffer,(char*)pNum,nLen);
			btToModule_golf_phoneNumInTheSpecialState(buffer, nLen, buffer, nLen);
		}
		else
		{
			btToModule_golf_phoneNumInTheSpecialState(pNum, nLen, pNum, nLen);
		}
	}
}


void CBtModule::btToModule_golf_phoneName(u8 *p, int nLen)
{
	int nCopyLen = (nLen > 21) ? 21 : nLen;
	u8 szMsg[64] = {0};
	szMsg[0] = 0x81;
	szMsg[1] = 0x00;
	szMsg[2] = 0x50;
	szMsg[3] = nCopyLen + 1;
	szMsg[4] = 0x3A;
	szMsg[5] = 0x11;
	szMsg[6] = nCopyLen;
	memcpy(szMsg + 7, p, nCopyLen);
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, nCopyLen + 7);
}
void CBtModule::btToModule_golf_mobileOperatorName(u8 *p, int nLen)
{
	int nCopyLen = (nLen > 21) ? 21 : nLen;
	u8 szMsg[64] = {0};
	szMsg[0] = 0x81;
	szMsg[1] = 0x00;
	szMsg[2] = 0x51;
	szMsg[3] = nCopyLen + 4;
	szMsg[4] = 0x3A;
	szMsg[5] = 0x14;
	szMsg[6] = 1;
	szMsg[7] = nCopyLen;
	memcpy(szMsg + 8, p, nCopyLen);
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, nCopyLen + 8 + 2);
}
void CBtModule::btToModule_golf_netInfo(u8 p0, u8 p1)
{
	u8 szMsg[] = {0x81, 0x00, 0x52, 0x3A, 0x12, 0x00, 0x00, 0x00};
	szMsg[5] = p0;
	szMsg[6] = p1;
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, 8);
}
void CBtModule::btToModule_golf_simCardState(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x53, 0x3A, 0x13, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, 6);
}
void CBtModule::btToModule_golf_signalState(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x54, 0x3A, 0x15, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, 6);
}
void CBtModule::btToModule_golf_batteryStrength(u8 p)
{
	u8 szMsg[] = {0x81, 0x00, 0x55, 0x3A, 0x2B, 0x00, 0xFF, 0xFF, 0xFF, 0x00};
	szMsg[5] = p;
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, 10);
}
void CBtModule::btToModule_golf_didntReceivePhoneNum(int n)
{
	u8 szMsg[] = {0x81, 0x00, 0x56, 0x3A, 0x2D, 0x00, 0x00, 0xFF, 0xFF};
	memcpy(szMsg + 5, &n, 2);
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, 9);
}
void CBtModule::btToModule_golf_blueConnectState(u8 p0, u8 p1)
{
	u8 szMsg[] = {0x81, 0x00, 0x57, 0x3A, 0x0E, 0x00, 0x00};
	szMsg[5] = p0;
	szMsg[6] = p1;
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, 7);
}
void CBtModule::btToModule_golf_phoneState(u8 p0, u8 p1)
{
	u8 szMsg[5] = {0x81, 0x00, 0x58, 0x00, 0x00};
	szMsg[3] = p0;
	szMsg[4] = p1;
	LOGD("golf_phoneState len = [%d]", sizeof((char*)szMsg));
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, 5);
}
void CBtModule::btToModule_golf_phoneNumInTheSpecialState(u8 *p0, int nLen0, u8 *p1, int nLen1)
{
	u8 szMsg[256] = {0x00};
	szMsg[0] = 0x81;
	szMsg[1] = 0x00;
	szMsg[2] = 0x59;
	szMsg[3] = 1 + nLen0 + 1 + nLen1 + 19;
	szMsg[4] = 0x4A;
	szMsg[5] = 0x17;
	szMsg[6] = nLen0;
	strcat((char*)(szMsg + 7),(char*)p0);
	szMsg[7 + nLen0] = nLen1;
	strcat((char*)(szMsg + 7 + nLen0 + 1),(char*)p1);
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, 7 + nLen0 + 1 + nLen1 + 19);
}
void CBtModule::btToModule_golf_phoneNumListOfDialOutAndDialIn(u8 *p, int nLen)
{
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, p, nLen);
}

void CBtModule::btToModule_golf_updatePhoneBook()
{
	u8 szMsg[] = {0x81, 0x00, 0x5B, 0x01};
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, 4);
}

void CBtModule::btToModule_golf_deletePhoneBook(u8 pageNum, u8 flag, u8 posFrom)
{
	u8 szMsg[] = {0x81, 0x00, 0x5A, 0x1A, 0x4A, 0x31, pageNum, 0x01, flag + 0x40, posFrom, 0x00, 0x06, 0x31, 0x30, 0x30,
		0x38, 0x36, 0x00, 0x03, 0x06, 0x31, 0x30, 0x30, 0x38, 0x36, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};
	makeAndSendMessageToModule(MODULE_ID_BT, MODULE_ID_EXTCAR, szMsg, 32);
}


//////////////////////////////////////////////////////////////////////////

void CBtModule::ToOSDandAPPaboutConnectState(char cState)
{
	int CurPageID = 0;
	int paramLen=0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,(u8*)&paramLen);
	if(PAGE_BLUETOOTH_MAIN != CurPageID && CurPageID != PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME && CurPageID != PAGE_BLUETOOTH_PHONEPAIR)
	{
		btToModule_NotifyOSD_ShowBTConnectState(cState);
		btToModule_NotifyOSD_ShowTitle();
	}
}

void CBtModule::btToModule_NotifyOSD_ShowTitle()
{
	unsigned char buf[] = {0x01, 0x15};
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_OSD, buf, 2);
}

void CBtModule::btToModule_NotifyOSD_ShowBTConnectState(unsigned char cState)
{
	unsigned char buf[] = {0x15,cState};

	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_OSD, buf, 2);
}

void CBtModule::btToModule_NotifyAUXScreen_BT_PhoneState(unsigned char cState){
	unsigned char buf[] = {0x70, cState};
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_AUXSCREEN, buf, 2);
}

void CBtModule::btToModule_NotifyBackVideo_BT_PhoneState(u8 cState){
	LOGD("btToModule_NotifyBackVideo_BT_PhoneState");
	u8 buf[] = {0x85,cState};
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_BACK, buf,2);
}

void CBtModule::btToModule_NotifySystem_BT_PhoneState(u8 cState)
{
	u8 buf[] = {0x00, cState};
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_SYSTEM, buf, 2);
}

void CBtModule::btToModule_NotifyAudiovideo_BT_PhoneState(u8 cState)
{
	LOGD("btToModule_NotifyAudiovideo_BT_PhoneState");
	u8 buf[] = {0x35,cState};
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_AUDIOVIDEO, buf,2);

}

void CBtModule::btToModule_NotifyBackVideo_BT_CallInfo(u8* pBuf, int nLen){
	int nBufLen = nLen + 1;
	u8 *pBufName = (u8*)malloc(nBufLen);

	if(pBufName == NULL)
		return;

	pBufName[0] = 0x86;
	memcpy(pBufName + 1,pBuf,nLen);
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_BACK,pBufName,nBufLen);
	free(pBufName);
	pBufName = NULL;
}

void CBtModule::btToModule_NotifyCenter_StopRing()
{
	LOGD("--StopRing--");
	unsigned char buff[2] = {0x03,0x00};
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_CENTER,buff,2);
}
void CBtModule::btToModule_NotifyCenter_StartRing(unsigned char ringID)
{
	LOGD("--  StartRing  --");
	unsigned char buff[2] = {0x02,0x00};
	buff[1] = ringID;
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_CENTER,buff,2);
}
/////////////////////////FlyJniSdk////////////////////////////////////////////////////////////
void CBtModule::sendToFlyJniSdkPowerState(char cState)
{
	LOGD("[%s] cState:%d",__FUNCTION__,cState);
    u8 buf[] = {0x00,0x00};
	memcpy(&buf[1],&cState,1);
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_FLYJNISDK,buf,2);       
}

void CBtModule::sendToFlyJniSdkConnectState(char cState)
 {
 	LOGD("[%s] cState:%d",__FUNCTION__,cState);
    u8 buf[] = {0x01,0x00};
	memcpy(&buf[1],&cState,1);
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_FLYJNISDK,buf,2);    
 }

 void CBtModule::sendToFlyJniSdkRemoteDeviceName(char* btName , int len)
 {
 	LOGD("[%s] btName:%s",__FUNCTION__,btName);
    u8 buf[257]={0x00};
	buf[0]=0x02;
	memcpy(&buf[1],btName,strlen(btName));
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_FLYJNISDK,buf,strlen(btName)+1);  
 }

 void CBtModule::sendToFlyJniSdkPhoneStatus(char cState)
 {
 	LOGD("[%s] Status:%d",__FUNCTION__,cState);
	u8 buf[] = {0x03,0x00};
	memcpy(&buf[1],&cState,1);
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_FLYJNISDK,buf,2);   
 }


void CBtModule::sendToFlyJniSdkBtMusicSong( char* song,int len)
{
	//LOGD("[%s] song:%s",__FUNCTION__,song);
	u8 buf[257]={0x00};
	buf[0]=0x07;
	memcpy(&buf[1],song,len);
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_FLYJNISDK,buf,len+1);  
}

void CBtModule::sendToFlyJniSdkBtMusicSonger(char* songer, int len)
{
	//LOGD("[%s] songer:%s",__FUNCTION__,songer);
	u8 buf[257]={0x00};
	buf[0]=0x08;
	memcpy(&buf[1],songer,len);
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_FLYJNISDK,buf,len+1);  
}

void CBtModule::sendToFlyJniSdkBtMusicAlbum(char * album, int len)
{
	LOGD("[%s] album:%s",__FUNCTION__,album);
    u8 buf[257]={0x00};
	buf[0]=0x09;
	memcpy(&buf[1],album,len);
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_FLYJNISDK,buf,len+1);
}

void CBtModule::sendToFlyJNiSdkBtMusicStatus(char cState)
{
	//LOGD("[%s] cState:%d",__FUNCTION__,cState);
    u8 buf[] = {0x0a,0x00};
	buf[1]=cState;
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_FLYJNISDK,buf,2);
}

void CBtModule::sendToFlyJNiSdkBtSupportA2DP(char cState)
{
	 LOGD("[%s] cState:%d",__FUNCTION__,cState);
	 u8 buf[] = {0x0b,0x00};
	 buf[1]=cState;
	 makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_FLYJNISDK,buf,2);
}

void CBtModule::sendToAudiovideoBtA2dpAudioFocuse(char s)
{
	 u8 buf[] = {0x01,0x00};
	 buf[1] = s;
	 makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_AUDIOVIDEO,buf,2);
}

void CBtModule::getFlyJniSdkMessage(u8 *p, u8 len)
{
    outPutLog(__FUNCTION__,  "p", p, len);

	switch(p[0])
	{
		case 0x00:
			m_pBtApp->m_pA2DPpages->setA2DPPlay();
			break;
		case 0x01:
			m_pBtApp->m_pA2DPpages->setA2DPPause();
			break;
		case 0x02:
		 	 m_pBtApp->m_pA2DPpages->setA2DPStop();
			 break;
    		case 0x03:
    			m_pBtApp->m_pA2DPpages->setA2DPPagePrev();
			break;
		case 0x04:
			m_pBtApp->m_pA2DPpages->setA2DPPageNext();
			break;
		case 0x05:							
			GPS_aboutCareLand_PTT(&p[1],len-1);
			break;
		case 0xfe:
			//analysSdkToBtMessage(&p[1], len - 1);
			g_pClsBtJniSdk->getSdkToModuleMessage(&p[1], len - 1);
			break;
		default:
			return;
		break;
	}

 }

 void CBtModule::getStandbyOn()
 {
	 LOGD("[%s]", __FUNCTION__);
	 getStandByStatus(0,0);
 }
 
 void CBtModule::getStandbyOff()
 {
	 LOGD("[%s]", __FUNCTION__);
	 getStandByStatus(1,0);
 }

 void CBtModule::btToModule_NotifyAudiovideo_BT_MicSwitch(u8 cState)
 {
	 u8 buf[2] = {0x41,cState};
	 makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_AUDIOVIDEO, buf,2);
 }

 void CBtModule::btToModule_NotifyExternalctrl_VoiceSwitchCtrl(u8 p){
	 u8 buf[] = {0x00,p};
	 makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_EXTERNALCTRL,buf,2);
 }

 void CBtModule::sendToFlyJNiSdkBtPhoneBook(u8 *date,int len)
 {
	  LOGD("[%s]",__FUNCTION__);
	  makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_FLYJNISDK,date,len);
 }


void CBtModule::analysSdkToBtMessage(u8 *p,u8 len)
{
	switch(p[0])
	{
		  case 0x01:
			  {
				  sendToFlyJniSdkConnectState(m_pBtParam->m_eHfpConnectStatus);
			  }
			  break;
		  case 0x02:
			  {
				  sendToFlyJniSdkPhoneStatus(m_pBtParam->m_ePhoneStatus);
			  }
			  break;
		  case 0x03:
			  {
				//  sendToFlyJniSdkPhoneBookLoadStatus(m_pBtApp->m_pBtPhoneBookPages->m_bIsLoadingPhoneBook);
			  }
			  break;
		  case 0x04:
			  {
				  setPage(PAGE_BLUETOOTH_MAIN);
			  }
			  break;
		case 0x06:
			{
				 GPS_aboutCareLand_PTT(&p[1],len -1);
			}
			break;
		case 0x07:
			{
				if(p[1] == 0x00)
					m_pBtHal->setToHalBtPower(0x00);
				else if(p[1] == 0x01)
					m_pBtHal->setToHalBtPower(0x01);
			}
			break;
		case 0x08:
			{
				if(p[1] == 0x01)
					m_pBtApp->m_pA2DPpages->clickA2dpMainPageEntrance(MOUSE_STATUS_UP);
			}
			break;
		  default:break;
	}
}
  
void CBtModule::sendToFlyJniSdkPhoneBookLoadStatus(u8 cState)
{
	LOGD("[%s] Status:%d",__FUNCTION__,cState);
	u8 buf[2] = {0x10,cState};
	makeAndSendMessageToModule(MODULE_ID_BT,MODULE_ID_FLYJNISDK,buf,2);	
}


void CBtModule::StandbyOff_Time()
{
	printf("[BT] [%s] m_pBtParam->m_eHfpConnectStatus:%d\n",__FUNCTION__,m_pBtParam->m_eHfpConnectStatus);
	if(m_pBtParam->m_eHfpConnectStatus == HFP_CONNECT_STATUS_CONNECTED)
	{
		if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_TALKING){
			if(m_pBtParam->m_eHfpAudioSource == HFP_AUDIO_SOURCE_BT){
				g_pClsBtAdapter->btAnswerformCarOrPhone(0x01);
				usleep(1000*1000);
			}
		}

		if(m_pBtParam->m_bIsA2dpOnPlayState == true){
			m_pBtApp->m_pA2DPpages->setA2DPPause();
			usleep(1000*100);
		}

		g_pClsBtAdapter->btInitiativeDisconnection((u8 *)m_pBtParam->szRemodeBtDeviceHasConnectedAddr,strlen(m_pBtParam->szRemodeBtDeviceHasConnectedAddr));
	}

	usleep(1000*400);
	
	m_pBtHal->setToHalBtPower(0x00);
	m_pBtParam->bStandBYPower = false;
	m_pBtParam->m_bFirstStart = false;
}


void CBtModule::setStandbyOff_Time()
{
	m_pBtModule->deleteNativeTimer(TIMER_ACC_OFF_BT_OFF);
	m_pBtModule->setNativeTimer(4000,1,TIMER_ACC_OFF_BT_OFF);
}