#include "CallRecordPages.h"

CCallRecordPages::CCallRecordPages(void)
{
}

CCallRecordPages::~CCallRecordPages(void)
{

}

void CCallRecordPages::initUi(void)
{
}

 void CCallRecordPages::init(void)
 {

 }

 void CCallRecordPages::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
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

bool CCallRecordPages::pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_BACK:
		clickGoBack(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_PREV:
		clickPrePage(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_NEXT:
		clickNextPage(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_MOBILE_RECORD_PREV:
		clickPrePage_New(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_MOBILE_RECORD_NEXT:
		clickNextPage_New(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_DISPLAY_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_DISPLAY_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_DISPLAY_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_DISPLAY_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_DISPLAY_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_DISPLAY_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_DISPLAY_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_DISPLAY_8:
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1:       
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_2:     
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_3:       
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_4:      
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_5:
		clickRecordItem(id-CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1, e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_1:       
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_2:     
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_3:       
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_4:      
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_6:
		{
			clickRecordItem(id-CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_1, e);
		}
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_RICEIVED:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_DIALED:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_MISS:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_ALL:
		{	
			if(HFP_CONNECT_STATUS_CONNECTED != m_pBtParam->m_eHfpConnectStatus)
				break;
			control_CallLogs(id - CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_RICEIVED,e);
		}
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

void CCallRecordPages::clickGoBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
					
		}
		break;
	default:
		break;
	}
}

void CCallRecordPages::clickPrePage(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			LOGD("[%s] m_nCallLogBrowseFrom:%d",__FUNCTION__,m_nCallLogBrowseFrom);
			
			static int nPreStartBrowse = -1;
			nPreStartBrowse = m_nCallLogBrowseFrom;
			m_nCallLogBrowseFrom = max(0, m_nCallLogBrowseFrom - SEARCH_LIST_DISPLAY_NUM);

			if (nPreStartBrowse == m_nCallLogBrowseFrom)
				return;
			EM_SYNC_PHONEBOOK_PATH em = m_pBtParam->m_iselectPhoneBook;
            if(em == BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY)
				refreshHistoryCall_Riceived(m_nCallLogBrowseFrom);
			else if(em == BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY)
				refreshHistoryCall_Dialed(m_nCallLogBrowseFrom);
			else if(em == BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY)
				refreshHistoryCall_Miss(m_nCallLogBrowseFrom);
			else if(em == BT_PBAP_SYNC_PATH_ALL_CALLHISTORY)
				refreshHistoryCall_All(m_nCallLogBrowseFrom);
		}
		break;
	default:
		break;
	}
}

void CCallRecordPages::clickNextPage(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		case MOUSE_STATUS_TIMER:
		{
			LOGD("[%s] m_nCallLogBrowseFrom:%d",__FUNCTION__,m_nCallLogBrowseFrom);
			EM_SYNC_PHONEBOOK_PATH em = m_pBtParam->m_iselectPhoneBook;
			if(em == BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY)
			{
				if(m_nCallLogBrowseFrom > (MSM_ANDROID_ISR_RECORDS_RECEIVED - 10))
					return;
			}
			else if(em == BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY)
			{
				if(m_nCallLogBrowseFrom > (MSM_ANDROID_ISR_RECORDS_DIALED - 10))
					return;
			}
			else if(em == BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY)
			{
				if(m_nCallLogBrowseFrom > (MSM_ANDROID_ISR_RECORDS_MISSED - 10))
					return;
			}
			else if(em == BT_PBAP_SYNC_PATH_ALL_CALLHISTORY)
			{
				if(m_nCallLogBrowseFrom > (MSM_ANDROID_ISR_RECORDS_ALL - 10))
					return;
			}
			
			static int nNextStartBrowse = -1;
			nNextStartBrowse = m_nCallLogBrowseFrom;

			m_nCallLogBrowseFrom += SEARCH_LIST_DISPLAY_NUM;
			if(em == BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY)
			{
			    if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall_Riceived.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;
				refreshHistoryCall_Riceived(m_nCallLogBrowseFrom);

			}
			else if(em == BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY)
			{
			 	if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall_Dialed.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;
				
				refreshHistoryCall_Dialed(m_nCallLogBrowseFrom);
			}
			else if(em == BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY)
			{
				if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall_Miss.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;

				refreshHistoryCall_Miss(m_nCallLogBrowseFrom);
			}
			else if(em == BT_PBAP_SYNC_PATH_ALL_CALLHISTORY)
			{
				if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;

				refreshHistoryCall_All(m_nCallLogBrowseFrom);
			}
		}
		break;
		default:
		break;
	}
}

void CCallRecordPages::callLogs_Type(int index)
{
		int j=0;

		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Dialed).begin();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Dialed).end();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;

		LOGD("[%s] index=%d m_pBtParam->m_listHistoryCall_Dialed.size()=%d ",__FUNCTION__,index,m_pBtParam->m_listHistoryCall_Dialed.size());
		
		if(index > m_pBtParam->m_listHistoryCall_Dialed.size())
			return;
		
		if(m_pBtParam->m_listHistoryCall_Dialed.size() == 0)
			return;
			
		for (it = itFrom; it != itTo; it++)
		{
			if (j== index)
				break;
			j++;
		}

		LOGD("[%s] j=%d ",__FUNCTION__,j);
		if(j < index)
			return;
			
		memset(&(m_pBtParam->m_stPhoneNumInput),0,sizeof(m_pBtParam->m_stPhoneNumInput));
		m_pBtParam->m_stPhoneNumInput.dwLen=strlen(it->szUserNo);
		memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, it->szUserNo, strlen(it->szUserNo));
					
		m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(it->szUserName), strlen(it->szUserName));
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);  
		memcpy(m_pBtParam->m_stPhoneNumInput.szcName, it->szUserName, strlen(it->szUserName));
			
		m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
		m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
		m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);

}

void CCallRecordPages::clickRecordItem(int index, E_MOUSE_STATUS e)
{
	if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_CALL_IN || m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_CALL_OUT)
		return;
	if(m_pBtParam->nCallCount == CALLING_COUNT_MUTIL)
		return;
	
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			LOGD("[%s] m_nCallLogBrowseFrom=%d index=%d",__FUNCTION__,m_nCallLogBrowseFrom,index);
			index = index + m_nCallLogBrowseFrom;

			memset(&(m_pBtParam->m_stPhoneNumInput), 0, sizeof(ST_PHONE_NUM));	

			int j=0;
			EM_SYNC_PHONEBOOK_PATH em = m_pBtParam->m_iselectPhoneBook;
			if(em == BT_PBAP_SYNC_PATH_ALL_CALLHISTORY)
			{
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall).begin();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall).end();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;

				LOGD("[%s] index:%d m_pBtParam->m_listHistoryCall.size:%d",__FUNCTION__,index,m_pBtParam->m_listHistoryCall.size());
				if((index + 1) > m_pBtParam->m_listHistoryCall.size())
						return;
				
				if(m_pBtParam->m_listHistoryCall.size() == 0)
						return;
				
				for (it = itFrom; it != itTo; it++)
				{
					if (j== index)
						break;
					j++;
				}
				
				if(j<index)
					return;
				memset(&(m_pBtParam->m_stPhoneNumInput),0,sizeof(m_pBtParam->m_stPhoneNumInput));
				m_pBtParam->m_stPhoneNumInput.dwLen=strlen(it->szUserNo);
				memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, it->szUserNo, strlen(it->szUserNo));

				m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(it->szUserName), strlen(it->szUserName));
				setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);  
				memcpy(m_pBtParam->m_stPhoneNumInput.szcName, it->szUserName, strlen(it->szUserName));

				m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
				m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
				m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
			}
			else if(em == BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY)
			{
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Riceived).begin();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Riceived).end();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;

				LOGD("[%s] index:%d m_pBtParam->m_listHistoryCall_Riceived.size():%d",__FUNCTION__,index,m_pBtParam->m_listHistoryCall_Riceived.size());
				if((index + 1) > m_pBtParam->m_listHistoryCall_Riceived.size())
					return;
				
				if(m_pBtParam->m_listHistoryCall_Riceived.size() == 0)
					return;
				for (it = itFrom; it != itTo; it++)
				{
					if(it==itTo)
					 {
						LOGD("[%s] invilid iterator",__FUNCTION__);
						return ;
					 }
					
					if (j== index)
						break;
					j++;
				}
				LOGD("[%s] index=%d,j=%d",__FUNCTION__,index,j);
				
				
				
				if(j<index)
					return;

				LOGD("Will To send Number");
				memset(&(m_pBtParam->m_stPhoneNumInput),0,sizeof(m_pBtParam->m_stPhoneNumInput));
				m_pBtParam->m_stPhoneNumInput.dwLen=strlen(it->szUserNo);
				memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, it->szUserNo, strlen(it->szUserNo));

				m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(it->szUserName), strlen(it->szUserName));
				setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);  
					memcpy(m_pBtParam->m_stPhoneNumInput.szcName, it->szUserName, strlen(it->szUserName));
					
				
				
				m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
				m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
				m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
				
			}
			else if(em == BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY)
			{
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Dialed).begin();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Dialed).end();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;

				LOGD("[%s] index:%d m_pBtParam->m_listHistoryCall_Dialed.size():%d",__FUNCTION__,index,m_pBtParam->m_listHistoryCall_Dialed.size());
				if((index + 1) > m_pBtParam->m_listHistoryCall_Dialed.size())
					return;
				if(m_pBtParam->m_listHistoryCall_Dialed.size() == 0)
					return;
				
				for (it = itFrom; it != itTo; it++)
				{
					if (j== index)
						break;
					j++;
				}
				
				if(j<index)
					return;

				memset(&(m_pBtParam->m_stPhoneNumInput),0,sizeof(m_pBtParam->m_stPhoneNumInput));
				m_pBtParam->m_stPhoneNumInput.dwLen=strlen(it->szUserNo);
				memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, it->szUserNo, strlen(it->szUserNo));
				
				m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(it->szUserName), strlen(it->szUserName));
				setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);  
				memcpy(m_pBtParam->m_stPhoneNumInput.szcName, it->szUserName, strlen(it->szUserName));

				m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
				m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
				m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
				
			}
			else if(em == BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY)
			{
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Miss).begin();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Miss).end();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;

				LOGD("[%s] index:%d m_pBtParam->m_listHistoryCall_Miss.size():%d",__FUNCTION__,index,m_pBtParam->m_listHistoryCall_Miss.size());
				if((index + 1) > m_pBtParam->m_listHistoryCall_Miss.size())
						return;
				
				if(m_pBtParam->m_listHistoryCall_Miss.size() == 0)
						return;

				for (it = itFrom; it != itTo; it++)
				{
					if (j== index)
						break;
					j++;
				}
				
				if(j<index)
					return;
				memset(&(m_pBtParam->m_stPhoneNumInput),0,sizeof(m_pBtParam->m_stPhoneNumInput));
				m_pBtParam->m_stPhoneNumInput.dwLen=strlen(it->szUserNo);
				memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, it->szUserNo, strlen(it->szUserNo));
				memcpy(m_pBtParam->m_stPhoneNumInput.szcName, it->szUserName, strlen(it->szUserName));

				m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_FREE,true,true,m_pBtParam->m_stPhoneNumInput.szcName,m_pBtParam->m_stPhoneNumInput.szcPhoneNum);
				if(m_pBtParam->nCallCount != 0)
				{
			    	m_pBtParam->bItsAddCalls = true;
			    	m_pBtApp->m_pBtMainPage->AddCallsToUI(m_pBtParam->bItsAddCalls);
				}

				m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
				m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
			}

		}
		break;
		default:
		break;
	}

	if(m_pBtParam->nCallCount != CALLING_COUNT_FREE)
	{
    	m_pBtParam->bItsAddCalls = true;
    	m_pBtApp->m_pBtMainPage->AddCallsToUI(m_pBtParam->bItsAddCalls);
	}
	
	setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DEFAULT);
	setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_ENABLE);
}

void CCallRecordPages::clickRecordType(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{

		}
		break;
	default:
		break;
	}
}

void CCallRecordPages::control_CallLogs(int param,E_MOUSE_STATUS e)
{
    LOGD("[%s] param:(%d)",__FUNCTION__,param);
	EM_SYNC_PHONEBOOK_PATH em = BT_PBAP_SYNC_PATH_ALL_CALLHISTORY;
	switch(param)
	{
		case 0:
			em = BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY;
		break;
		case 1:
			em = BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY;
		break;
		case 2:
			em = BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY;
		break;
		case 3:
			em = BT_PBAP_SYNC_PATH_ALL_CALLHISTORY;
		break;
		default:break;
	}
	
	m_pBtParam->m_iselectPhoneBook = em;
	SwitchSelectRecordType(em);
	getAndShowCallRecords(em);
	getAndShowCallRecords_New(em);
}

void CCallRecordPages::SwitchSelectRecordType(EM_SYNC_PHONEBOOK_PATH RecordType)
{
	switch(RecordType)
	{
		case BT_PBAP_SYNC_PATH_ALL_CALLHISTORY:
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_ALL,true);
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_MISS,false);
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_DIALED,false);
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_RICEIVED,false);
			break;
		case BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY:
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_RICEIVED,true);
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_MISS,false);
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_DIALED,false);
      		setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_ALL,false);
			break;
		case BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY:
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_DIALED,true);
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_MISS,false);
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_RICEIVED,false);
       		setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_ALL,false);
			break;
		case BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY:
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_MISS,true);
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_DIALED,false);
			setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_RICEIVED,false);
       		setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_ALL,false);
			break;
		default:break;
	}
}

void CCallRecordPages::getAndShowCallRecords(EM_SYNC_PHONEBOOK_PATH RecordType)
{
	switch(RecordType)
	{
		case BT_PBAP_SYNC_PATH_ALL_CALLHISTORY:
			refreshHistoryCall_All(0);
			break;
		case BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY:
			refreshHistoryCall_Riceived(0);
			break;
		case BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY:
			refreshHistoryCall_Dialed(0);
			break;
		case BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY:
			refreshHistoryCall_Miss(0);
			break;
		default:break;
	}
}

void CCallRecordPages::setDataToUI_bt_aboutCallLogName_Displaying(int nPos,char *buff)
{
    setUtf8String((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_DISPLAY_NAME_1+nPos, (u8*)buff,strlen(buff));
}

void CCallRecordPages::setDataToUI_bt_aboutCallLogNumber_Displaying(int nPos,char *buff)
{
    setUtf8String((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1+nPos, (u8*)buff,strlen(buff));
}

void CCallRecordPages::setDataToUI_bt_aboutCallLogCallTime_Displaying(int nPos,char *buff)
{
    int nLen = strlen(buff);
	if (nLen == 0)
	{
		setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_DISPLAY_TIME_1+nPos, (u8*)buff, nLen);
		return;
	}
	
    char temp[256]={0};
    memset(temp,0,sizeof(temp));

    char cHour[10]={0};
    memset(cHour,0,2);
    
    char cMin[10]={0};
    memset(cMin,0,2);
    
    memcpy(&cHour,buff+9,2);
    memcpy(&cMin,buff+11,2);

    strcpy(temp,cHour);
    strcat(temp,":");
    strcat(temp,cMin);

    setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_DISPLAY_TIME_1+nPos, (u8*)temp,strlen(temp));
}


void CCallRecordPages::setDataToUI_bt_aboutCallLogClassIcon_Displaying(int nPos,int Icon)
{
     u8 uSwitchIcon = 0;
     uSwitchIcon=Icon;
     setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1+nPos,uSwitchIcon);
    
} 


void CCallRecordPages::refreshHistoryCall_All(int nFrom)
{
	LOGD("[%s] nFrom:%d",__FUNCTION__,nFrom);

	setUpdateUI(false);
	
	int nBrowseFileNum =m_pBtParam->m_listHistoryCall.size();
	LOGD("[%s] nBrowseFileNum=%d",__FUNCTION__,nBrowseFileNum);

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM;

	if (nFrom < 0)
		nFrom = 0;
	
    m_nCallLogBrowseFrom = nFrom;
	   
	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
		       
			setDataToUI_bt_aboutCallLogName_Displaying(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,it->CBTime);
			switch(it->CBType)
			{
			case '4':
				setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,1);
				break;
			case '5':
				setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,3);
				break;
			case '6':
				setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,2);
				break;
			}
			
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1+k,true);
			//LOGD("[%s] szUserName:%s , szUserNo:%s , CBTime:%s",__FUNCTION__,it->szUserName,it->szUserNo,it->CBTime);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,0);
		}
		
		k++;
	}

	setUpdateUI(true);
	
}
		
void CCallRecordPages::refreshHistoryCall_Dialed(int nFrom)
{
	LOGD("[%s] nFrom:%d",__FUNCTION__,nFrom);
	
	setUpdateUI(false);
	
	int nBrowseFileNum =m_pBtParam->m_listHistoryCall_Dialed.size();
	LOGD("[%s] nBrowseFileNum=%d",__FUNCTION__,nBrowseFileNum);

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM;

	if (nFrom < 0)
		nFrom = 0;
	
       m_nCallLogBrowseFrom = nFrom;
	   
	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Dialed).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Dialed).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
			setDataToUI_bt_aboutCallLogName_Displaying(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,it->CBTime);
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,1);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1+k,true);
			//LOGD("[%s] szUserName:%s , szUserNo:%s , CBTime:%s",__FUNCTION__,it->szUserName,it->szUserNo,it->CBTime);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,0);
		}
		
		k++;
	}

	setUpdateUI(true);
}


void CCallRecordPages::refreshHistoryCall_Riceived(int nFrom)
{
	LOGD("[%s] nFrom:%d",__FUNCTION__,nFrom);

	setUpdateUI(false);
	
	int nBrowseFileNum =m_pBtParam->m_listHistoryCall_Riceived.size();
	LOGD("[%s] nBrowseFileNum=%d",__FUNCTION__,nBrowseFileNum);

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM;

	if (nFrom < 0)
		nFrom = 0;

	m_nCallLogBrowseFrom = nFrom;

	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Riceived).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Riceived).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
			setDataToUI_bt_aboutCallLogName_Displaying(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,it->CBTime);
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,3);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1+k,true);
			//LOGD("[%s] szUserName:%s , szUserNo:%s , CBTime:%s",__FUNCTION__,it->szUserName,it->szUserNo,it->CBTime);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,0);
		}
		
		k++;
	}

	setUpdateUI(true);


}




void CCallRecordPages::refreshHistoryCall_Miss(int nFrom)
{
	LOGD("[%s] nFrom:%d",__FUNCTION__,nFrom);

	setUpdateUI(false);

	int nBrowseFileNum =m_pBtParam->m_listHistoryCall_Miss.size();
	LOGD("[%s] nBrowseFileNum=%d",__FUNCTION__,nBrowseFileNum);

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM;

	if (nFrom < 0)
		nFrom = 0;

	m_nCallLogBrowseFrom = nFrom;

	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Miss).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Miss).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
			setDataToUI_bt_aboutCallLogName_Displaying(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,it->CBTime);
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,2);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1+k,true);
			//LOGD("[%s] szUserName:%s , szUserNo:%s , CBTime:%s",__FUNCTION__,it->szUserName,it->szUserNo,it->CBTime);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,0);
		}
		
		k++;
	}

	setUpdateUI(true);
}




void CCallRecordPages::createListHistoryCall(void)
{
	if (NULL == m_pBtParam)
	{
		LOGD("[%s] list come in",__FUNCTION__);
		return;
	}

	annalyListHistoryCall();


	EM_SYNC_PHONEBOOK_PATH em = m_pBtParam->m_iselectPhoneBook;
	SwitchSelectRecordType(em);
	getAndShowCallRecords(em);
	getAndShowCallRecords_New(em);
}

void CCallRecordPages::annalyListHistoryCall(void)
{
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itVecFrom = m_pBtParam->m_listHistoryCall.begin();

	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itVecTo = m_pBtParam->m_listHistoryCall.end();

	int i = 1;
	LOGD("[%s] m_listHistoryCall.size:%d",__FUNCTION__,(m_pBtParam->m_listHistoryCall).size());

	m_pBtParam->m_listHistoryCall_Dialed.clear();
	m_pBtParam->m_listHistoryCall_Riceived.clear();
	m_pBtParam->m_listHistoryCall_Miss.clear();

	for (list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itVec = itVecFrom; itVec != itVecTo; itVec++)
	{	  
		ST_CALL_RECORD_ONE_USER_INFO t;
		
		memset(&t, 0, sizeof(ST_CALL_RECORD_ONE_USER_INFO));
		memcpy(t.szUserName, itVec->szUserName, strlen(itVec->szUserName));
		memcpy(t.szUserNo, itVec->szUserNo, strlen(itVec->szUserNo));
		memcpy(t.CBTime, itVec->CBTime, strlen(itVec->CBTime));
		t.CBType=itVec->CBType;  
		
		if('4'==(itVec->CBType))
		{
			m_pBtParam->m_listHistoryCall_Dialed.push_back(t);
		   //LOGD("[%s]  itVec->CBType:%c",__FUNCTION__, itVec->CBType);
			//LOGD("[%s] m_listHistoryCall_Dialed.size:%d",__FUNCTION__,(m_pBtParam->m_listHistoryCall_Dialed).size());

		   if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_FREE)
		   {
			   if(m_pBtParam->m_listHistoryCall_Dialed.size() == 1)
			   {
				   memset(&m_pBtParam->st_UserInforsOnetouchDial,0,sizeof(ST_CALL_RECORD_ONE_USER_INFO));
				   m_pBtParam->st_UserInforsOnetouchDial.CBType=itVec->CBType;
				   memcpy(m_pBtParam->st_UserInforsOnetouchDial.szUserName, itVec->szUserName, strlen(itVec->szUserName));
				   memcpy(m_pBtParam->st_UserInforsOnetouchDial.szUserNo, itVec->szUserNo, strlen(itVec->szUserNo));
				   memcpy(m_pBtParam->st_UserInforsOnetouchDial.CBTime, itVec->CBTime, strlen(itVec->CBTime));
			   }
		   }//if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_FREE)

		}
		
		else if('5'==(itVec->CBType))
		{
			m_pBtParam->m_listHistoryCall_Riceived.push_back(t);
			//LOGD("[%s]  itVec->CBType:%c",__FUNCTION__, itVec->CBType);
			//LOGD("[%s] m_listHistoryCall_Riceived.size:%d",__FUNCTION__,(m_pBtParam->m_listHistoryCall_Riceived).size());
		}
		
		else if('6'==(itVec->CBType))
		{
			m_pBtParam->m_listHistoryCall_Miss.push_back(t);
			//LOGD("[%s]  itVec->CBType:%c",__FUNCTION__, itVec->CBType);
			//LOGD("[%s] m_listHistoryCall_Miss.size:%d",__FUNCTION__,(m_pBtParam->m_listHistoryCall_Miss).size());

			if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_FREE)
			{
				if((m_pBtParam->m_listHistoryCall_Dialed.size() == 0) && (m_pBtParam->m_listHistoryCall_Riceived.size() == 0))
				{
					if(m_pBtParam->m_listHistoryCall_Miss.size() == 1)
					{
						memset(&m_pBtParam->st_UserInforsOnetouchDial,0,sizeof(ST_CALL_RECORD_ONE_USER_INFO));
						m_pBtParam->st_UserInforsOnetouchDial.CBType=itVec->CBType;
						memcpy(m_pBtParam->st_UserInforsOnetouchDial.szUserName, itVec->szUserName, strlen(itVec->szUserName));
						memcpy(m_pBtParam->st_UserInforsOnetouchDial.szUserNo, itVec->szUserNo, strlen(itVec->szUserNo));
						memcpy(m_pBtParam->st_UserInforsOnetouchDial.CBTime, itVec->CBTime, strlen(itVec->CBTime));
					}
				}
				else if((m_pBtParam->m_listHistoryCall_Dialed.size() == 0) && (m_pBtParam->m_listHistoryCall_Riceived.size() != 0))
				{
					list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Riceived).begin();

					memset(&m_pBtParam->st_UserInforsOnetouchDial,0,sizeof(ST_CALL_RECORD_ONE_USER_INFO));
					m_pBtParam->st_UserInforsOnetouchDial.CBType=itFrom->CBType;
					memcpy(m_pBtParam->st_UserInforsOnetouchDial.szUserName, itFrom->szUserName, strlen(itFrom->szUserName));
					memcpy(m_pBtParam->st_UserInforsOnetouchDial.szUserNo, itFrom->szUserNo, strlen(itFrom->szUserNo));
					memcpy(m_pBtParam->st_UserInforsOnetouchDial.CBTime, itFrom->CBTime, strlen(itFrom->CBTime));
				}
			}//if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_FREE)
		}
	}
}

void CCallRecordPages::clearCallHistoryTypeStatus(void)
{
	m_pBtApp->setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_ALL,false);
	m_pBtApp->setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_MISS,false);
	m_pBtApp->setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_DIALED,false);
	m_pBtApp->setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_CALL_RICEIVED,false);
}

void CCallRecordPages::showLoadingCallLogTips(u32 strTips)
{
    if(strTips != 0)
    {
        setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_LOADING, STRINGID_BT__DEVICE_CALL_LOG_LOADING);
		LOGD("[%s]    SHOW",__FUNCTION__);
	}
	else
	{
	    setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_LOADING, (u8*)"", 0);
		LOGD("[%s]    HID",__FUNCTION__);
	}
}


//BC8
void CCallRecordPages::annalyListHistoryCall2(void)
{
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itVecFrom = m_pBtParam->m_listHistoryCall_BC8.begin();

	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itVecTo = m_pBtParam->m_listHistoryCall_BC8.end();

	int i = 1;
	LOGD("[%s] m_listHistoryCall_BC8.size:%d",__FUNCTION__,(m_pBtParam->m_listHistoryCall_BC8).size());

	m_pBtParam->m_listHistoryCall_Dialed_BC8.clear();
	m_pBtParam->m_listHistoryCall_Riceived_BC8.clear();
	m_pBtParam->m_listHistoryCall_Miss_BC8.clear();

	for (list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itVec = itVecFrom; itVec != itVecTo; itVec++)
	{	  
		ST_CALL_RECORD_ONE_USER_INFO t;
		
		memset(&t, 0, sizeof(ST_CALL_RECORD_ONE_USER_INFO));
		memcpy(t.szUserName, itVec->szUserName, strlen(itVec->szUserName));
		memcpy(t.szUserNo, itVec->szUserNo, strlen(itVec->szUserNo));
		memcpy(t.CBTime, itVec->CBTime, strlen(itVec->CBTime));
		t.CBType=itVec->CBType;  
		
		if('4'==(itVec->CBType))
		{
			m_pBtParam->m_listHistoryCall_Dialed_BC8.push_back(t);
		   //LOGD("[%s]  itVec->CBType:%c",__FUNCTION__, itVec->CBType);
			//LOGD("[%s] m_listHistoryCall_Dialed_BC8.size:%d",__FUNCTION__,(m_pBtParam->m_listHistoryCall_Dialed_BC8).size());
		}
		
		else if('5'==(itVec->CBType))
		{
			m_pBtParam->m_listHistoryCall_Riceived_BC8.push_back(t);
			//LOGD("[%s]  itVec->CBType:%c",__FUNCTION__, itVec->CBType);
			//LOGD("[%s] m_listHistoryCall_Riceived_BC8.size:%d",__FUNCTION__,(m_pBtParam->m_listHistoryCall_Riceived_BC8).size());
		}
		
		else if('6'==(itVec->CBType))
		{
			m_pBtParam->m_listHistoryCall_Miss_BC8.push_back(t);
			//LOGD("[%s]  itVec->CBType:%c",__FUNCTION__, itVec->CBType);
			//LOGD("[%s] m_listHistoryCall_Miss_BC8.size:%d",__FUNCTION__,(m_pBtParam->m_listHistoryCall_Miss_BC8).size());
		}
	}

}

void CCallRecordPages::clickPrePage2(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nPreStartBrowse = -1;
			nPreStartBrowse = m_nCallLogBrowseFrom;
			m_nCallLogBrowseFrom = max(0, m_nCallLogBrowseFrom - SEARCH_LIST_DISPLAY_NUM);

			if (nPreStartBrowse == m_nCallLogBrowseFrom)
				return;

			EM_SYNC_PHONEBOOK_PATH em = m_pBtParam->m_iselectPhoneBook;
        	if(em == BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY)
				refreshHistoryCall_Riceived_BC8(m_nCallLogBrowseFrom);
			else if(em == BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY)
				refreshHistoryCall_Dialed_BC8(m_nCallLogBrowseFrom);
			else if(em == BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY)
				refreshHistoryCall_Miss_BC8(m_nCallLogBrowseFrom);
			else if(em == BT_PBAP_SYNC_PATH_ALL_CALLHISTORY)
				refreshHistoryCall_All_BC8(m_nCallLogBrowseFrom);
		}
		break;
	default:
		break;
	}
}

void CCallRecordPages::clickNextPage2(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nNextStartBrowse = -1;
			nNextStartBrowse = m_nCallLogBrowseFrom;

			m_nCallLogBrowseFrom += SEARCH_LIST_DISPLAY_NUM;

			EM_SYNC_PHONEBOOK_PATH em = m_pBtParam->m_iselectPhoneBook;
			if(em == BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY)
			{
			    if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall_Riceived_BC8.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;
				refreshHistoryCall_Riceived_BC8(m_nCallLogBrowseFrom);
			}
			else if(em == BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY)
			{
			 	if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall_Dialed_BC8.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;
				
				refreshHistoryCall_Dialed_BC8(m_nCallLogBrowseFrom);
			}
			else if(em == BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY)
			{
				if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall_Miss_BC8.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;

				refreshHistoryCall_Miss_BC8(m_nCallLogBrowseFrom);
			}
			else if(em == BT_PBAP_SYNC_PATH_ALL_CALLHISTORY)
			{
				if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall_BC8.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;

				refreshHistoryCall_All_BC8(m_nCallLogBrowseFrom);
			}
		}
		break;
	default:
		break;
	}

}

void CCallRecordPages::clickRecordItem2(int index, E_MOUSE_STATUS e)
{
	if(m_pBtParam->m_ePhoneStatus != BT_PHONE_STATUS_FREE)
		return;
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			LOGD("[%s] m_nCallLogBrowseFrom=%d index=%d",__FUNCTION__,m_nCallLogBrowseFrom,index);
			index = index + m_nCallLogBrowseFrom;

			memset(&(m_pBtParam->m_stPhoneNumInput), 0, sizeof(ST_PHONE_NUM));	

			int j=0;

			EM_SYNC_PHONEBOOK_PATH em = m_pBtParam->m_iselectPhoneBook;
			if(em == BT_PBAP_SYNC_PATH_ALL_CALLHISTORY)
			{
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_BC8).begin();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_BC8).end();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;

				LOGD("[%s] index:%d m_pBtParam->m_listHistoryCall_BC8.size:%d",__FUNCTION__,index,m_pBtParam->m_listHistoryCall_BC8.size());
				if((index + 1) > m_pBtParam->m_listHistoryCall_BC8.size())
						return;
				
				if(m_pBtParam->m_listHistoryCall_BC8.size() == 0)
						return;
				
				for (it = itFrom; it != itTo; it++)
				{
					if (j== index)
						break;
					j++;
				}
				
				if(j<index)
					return;
				memset(&(m_pBtParam->m_stPhoneNumInput),0,sizeof(m_pBtParam->m_stPhoneNumInput));
				m_pBtParam->m_stPhoneNumInput.dwLen=strlen(it->szUserNo);
				memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, it->szUserNo, strlen(it->szUserNo));

				m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(it->szUserName), strlen(it->szUserName));
				setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);  
				memcpy(m_pBtParam->m_stPhoneNumInput.szcName, it->szUserName, strlen(it->szUserName));

				m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
				m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
				m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
			}
			else if(em == BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY)
			{
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Riceived_BC8).begin();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Riceived_BC8).end();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;

				LOGD("[%s] index:%d m_pBtParam->m_listHistoryCall_Riceived_BC8.size():%d",__FUNCTION__,index,m_pBtParam->m_listHistoryCall_Riceived_BC8.size());
				if((index + 1) > m_pBtParam->m_listHistoryCall_Riceived_BC8.size())
					return;
				
				if(m_pBtParam->m_listHistoryCall_Riceived_BC8.size() == 0)
					return;
				for (it = itFrom; it != itTo; it++)
				{
					if(it==itTo)
					 {
						LOGD("[%s] invilid iterator",__FUNCTION__);
						return ;
					 }
					
					if (j== index)
						break;
					j++;
				}
				LOGD("[%s] index=%d,j=%d",__FUNCTION__,index,j);
				
				
				
				if(j<index)
					return;

				LOGD("Will To send Number");
				memset(&(m_pBtParam->m_stPhoneNumInput),0,sizeof(m_pBtParam->m_stPhoneNumInput));
				m_pBtParam->m_stPhoneNumInput.dwLen=strlen(it->szUserNo);
				memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, it->szUserNo, strlen(it->szUserNo));

				m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(it->szUserName), strlen(it->szUserName));
				setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);  
					memcpy(m_pBtParam->m_stPhoneNumInput.szcName, it->szUserName, strlen(it->szUserName));
					
				
				
				m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
				m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
				m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
				
			}
			else if(em == BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY)
			{
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Dialed_BC8).begin();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Dialed_BC8).end();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;

				LOGD("[%s] index:%d m_pBtParam->m_listHistoryCall_Dialed_BC8.size():%d",__FUNCTION__,index,m_pBtParam->m_listHistoryCall_Dialed_BC8.size());
				if((index + 1) > m_pBtParam->m_listHistoryCall_Dialed_BC8.size())
					return;
				if(m_pBtParam->m_listHistoryCall_Dialed_BC8.size() == 0)
					return;
				
				for (it = itFrom; it != itTo; it++)
				{
					if (j== index)
						break;
					j++;
				}
				
				if(j<index)
					return;

				memset(&(m_pBtParam->m_stPhoneNumInput),0,sizeof(m_pBtParam->m_stPhoneNumInput));
				m_pBtParam->m_stPhoneNumInput.dwLen=strlen(it->szUserNo);
				memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, it->szUserNo, strlen(it->szUserNo));
				
				   m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(it->szUserName), strlen(it->szUserName));
				setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);  
					memcpy(m_pBtParam->m_stPhoneNumInput.szcName, it->szUserName, strlen(it->szUserName));

				m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
				m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
				m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
				
			}
			else if(em == BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY)
			{
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Miss_BC8).begin();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Miss_BC8).end();
				list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;

				LOGD("[%s] index:%d m_pBtParam->m_listHistoryCall_Miss_BC8.size():%d",__FUNCTION__,index,m_pBtParam->m_listHistoryCall_Miss_BC8.size());
				if((index + 1) > m_pBtParam->m_listHistoryCall_Miss_BC8.size())
						return;
				
				if(m_pBtParam->m_listHistoryCall_Miss_BC8.size() == 0)
						return;

				for (it = itFrom; it != itTo; it++)
				{
					if (j== index)
						break;
					j++;
				}
				
				if(j<index)
					return;
				memset(&(m_pBtParam->m_stPhoneNumInput),0,sizeof(m_pBtParam->m_stPhoneNumInput));
				m_pBtParam->m_stPhoneNumInput.dwLen=strlen(it->szUserNo);
				memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, it->szUserNo, strlen(it->szUserNo));

				m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(it->szUserName), strlen(it->szUserName));
				setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);  
				memcpy(m_pBtParam->m_stPhoneNumInput.szcName, it->szUserName, strlen(it->szUserName));

				m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
				m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
				m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
			}
		}
		break;
		default:
		break;
	}
	
	setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DEFAULT);
	setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_ENABLE);

}

void CCallRecordPages::refreshHistoryCall_All_BC8(int nFrom)
{
	//LOGD("[%s] nFrom:%d",__FUNCTION__,nFrom);
	
	setUpdateUI(false);
	
	int nBrowseFileNum =m_pBtParam->m_listHistoryCall_BC8.size();
	//LOGD("[%s] nBrowseFileNum=%d",__FUNCTION__,nBrowseFileNum);

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM;

	if (nFrom < 0)
		nFrom = 0;
	
    m_nCallLogBrowseFrom = nFrom;
	   
	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_BC8).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_BC8).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
		       
			setDataToUI_bt_aboutCallLogName_Displaying(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,it->CBTime);
			switch(it->CBType)
			{
			case '4':
				setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,1);
				break;
			case '5':
				setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,3);
				break;
			case '6':
				setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,2);
				break;
			}
			
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1+k,true);
			//LOGD("[%s] szUserName:%s , szUserNo:%s , CBTime:%s",__FUNCTION__,it->szUserName,it->szUserNo,it->CBTime);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,0);
		}
		
		k++;
	}

	setUpdateUI(true);
	
}
		
void CCallRecordPages::refreshHistoryCall_Dialed_BC8(int nFrom)
{
    //LOGD("[%s] nFrom:%d",__FUNCTION__,nFrom);
	
	setUpdateUI(false);
	
	int nBrowseFileNum =m_pBtParam->m_listHistoryCall_Dialed_BC8.size();
	//LOGD("[%s] nBrowseFileNum=%d",__FUNCTION__,nBrowseFileNum);

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM;

	if (nFrom < 0)
		nFrom = 0;
	
       m_nCallLogBrowseFrom = nFrom;
	   
	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Dialed_BC8).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Dialed_BC8).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
			setDataToUI_bt_aboutCallLogName_Displaying(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,it->CBTime);
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,1);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1+k,true);
			//LOGD("[%s] szUserName:%s , szUserNo:%s , CBTime:%s",__FUNCTION__,it->szUserName,it->szUserNo,it->CBTime);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,0);
		}
		
		k++;
	}

	setUpdateUI(true);
}


void CCallRecordPages::refreshHistoryCall_Riceived_BC8(int nFrom)
{
 	//LOGD("[%s] nFrom:%d",__FUNCTION__,nFrom);
	   
	setUpdateUI(false);
	
	int nBrowseFileNum =m_pBtParam->m_listHistoryCall_Riceived_BC8.size();
	//LOGD("[%s] nBrowseFileNum=%d",__FUNCTION__,nBrowseFileNum);

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM;

	if (nFrom < 0)
		nFrom = 0;

	m_nCallLogBrowseFrom = nFrom;

	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Riceived_BC8).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Riceived_BC8).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
			setDataToUI_bt_aboutCallLogName_Displaying(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,it->CBTime);
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,3);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1+k,true);
			//LOGD("[%s] szUserName:%s , szUserNo:%s , CBTime:%s",__FUNCTION__,it->szUserName,it->szUserNo,it->CBTime);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,0);
		}
		
		k++;
	}

	setUpdateUI(true);


}




void CCallRecordPages::refreshHistoryCall_Miss_BC8(int nFrom)
{
	//LOGD("[%s] nFrom:%d",__FUNCTION__,nFrom);
	setUpdateUI(false);

	int nBrowseFileNum =m_pBtParam->m_listHistoryCall_Miss_BC8.size();
	//LOGD("[%s] nBrowseFileNum=%d",__FUNCTION__,nBrowseFileNum);

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM;

	if (nFrom < 0)
		nFrom = 0;

	m_nCallLogBrowseFrom = nFrom;

	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Miss_BC8).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Miss_BC8).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
			setDataToUI_bt_aboutCallLogName_Displaying(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,it->CBTime);
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,2);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_RECORD_MULTIBUTTON_1+k,true);
			//LOGD("[%s] szUserName:%s , szUserNo:%s , CBTime:%s",__FUNCTION__,it->szUserName,it->szUserNo,it->CBTime);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying(k,0);
		}
		
		k++;
	}

	setUpdateUI(true);
}


void CCallRecordPages::showListHistoryCall(void)
{
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	it = m_pBtParam->m_listHistoryCall.begin();
 
	ST_CALL_RECORD_ONE_USER_INFO t;
	memset(&t, 0, sizeof(ST_CALL_RECORD_ONE_USER_INFO));
	memcpy(t.szUserName, it->szUserName, strlen(it->szUserName));
	memcpy(t.szUserNo, it->szUserNo, strlen(it->szUserNo));
	memcpy(t.CBTime, it->CBTime, strlen(it->CBTime));
	t.CBType=it->CBType;  
	t.nTime=it->nTime;  
	if('4'==(it->CBType))
	{
		m_pBtParam->m_listHistoryCall_Dialed.push_front(t);
	}
	else if('5'==(it->CBType))
	{
		m_pBtParam->m_listHistoryCall_Riceived.push_front(t);
	}
	else if('6'==(it->CBType))
	{
		m_pBtParam->m_listHistoryCall_Miss.push_front(t);
	}
	
	m_pBtParam->m_listHistoryCall.sort();
	m_pBtParam->m_listHistoryCall_Dialed.sort();
	m_pBtParam->m_listHistoryCall_Riceived.sort();
	m_pBtParam->m_listHistoryCall_Miss.sort();
	
	SwitchSelectRecordType(m_pBtParam->m_iselectPhoneBook);
	switch(m_pBtParam->m_iselectPhoneBook)
	{
		case BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY:
		{
			if(m_pBtParam->m_listHistoryCall_Riceived.size() < SEARCH_LIST_DISPLAY_NUM)
				getAndShowCallRecords(BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY);
			if(m_pBtParam->m_listHistoryCall_Riceived.size() < SEARCH_LIST_DISPLAY_NUM_NEW)
				getAndShowCallRecords_New(BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY);
		}	
		break;
		case BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY:
		{
			if(m_pBtParam->m_listHistoryCall_Dialed.size() < SEARCH_LIST_DISPLAY_NUM)
				getAndShowCallRecords(BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY);
			if(m_pBtParam->m_listHistoryCall_Dialed.size() < SEARCH_LIST_DISPLAY_NUM_NEW)
				getAndShowCallRecords_New(BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY);
		}	
		break;
		case BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY:
		{
			if(m_pBtParam->m_listHistoryCall_Miss.size() < SEARCH_LIST_DISPLAY_NUM)
				getAndShowCallRecords(BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY);
			if(m_pBtParam->m_listHistoryCall_Miss.size() < SEARCH_LIST_DISPLAY_NUM_NEW)
				getAndShowCallRecords_New(BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY);
		}
		break;
		case BT_PBAP_SYNC_PATH_ALL_CALLHISTORY:
		{
			if(m_pBtParam->m_listHistoryCall.size() < SEARCH_LIST_DISPLAY_NUM)
				getAndShowCallRecords(BT_PBAP_SYNC_PATH_ALL_CALLHISTORY);
			if(m_pBtParam->m_listHistoryCall.size() < SEARCH_LIST_DISPLAY_NUM_NEW)
				getAndShowCallRecords_New(BT_PBAP_SYNC_PATH_ALL_CALLHISTORY);
		}
		break;
		default:break;
	}
}


void CCallRecordPages::setDataToUI_bt_aboutCallLogName_Displaying_New(int nPos,char *buff)
{
    setUtf8String((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_DISPLAY_NAME_1+nPos, (u8*)buff,strlen(buff));
}

void CCallRecordPages::setDataToUI_bt_aboutCallLogCallTime_Displaying_New(int nPos,char *buff)
{
    int nLen = strlen(buff);
	if (nLen == 0)
	{
		setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_DISPLAY_TIME_1+nPos, (u8*)buff, nLen);
		return;
	}
	
    char temp[256]={0};
    memset(temp,0,sizeof(temp));

    char cHour[10]={0};
    memset(cHour,0,2);
    
    char cMin[10]={0};
    memset(cMin,0,2);
    
    memcpy(&cHour,buff+9,2);
    memcpy(&cMin,buff+11,2);

    strcpy(temp,cHour);
    strcat(temp,":");
    strcat(temp,cMin);

    setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_DISPLAY_TIME_1+nPos, (u8*)temp,strlen(temp));
}

void CCallRecordPages::setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(int nPos,int Icon)
{
     u8 uSwitchIcon = 0;
     uSwitchIcon=Icon;
     setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_1+nPos,uSwitchIcon);
    
} 

void CCallRecordPages::setDataToUI_bt_aboutCallLogNumber_Displaying_New(int nPos,char *buff)
{
    setUtf8String((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_1+nPos, (u8*)buff,strlen(buff));
}

void CCallRecordPages::refreshHistoryCall_All_New(int nFrom)
{
	setUpdateUI(false);
	int nBrowseFileNum =m_pBtParam->m_listHistoryCall.size();

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM_NEW;

	if (nFrom < 0)
		nFrom = 0;
	
   	m_nCallLogBrowseFrom = nFrom;
	   
	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM_NEW; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
		       
			setDataToUI_bt_aboutCallLogName_Displaying_New(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying_New(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying_New(k,it->CBTime);
			switch(it->CBType)
			{
			case '4':
				setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(k,1);
				break;
			case '5':
				setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(k,3);
				break;
			case '6':
				setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(k,2);
				break;
			}
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_1+k,true);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying_New( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying_New(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying_New(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(k,0);
		}
		
		k++;
	}

	setUpdateUI(true);
	
}


void CCallRecordPages::refreshHistoryCall_Riceived_New(int nFrom)
{  
	setUpdateUI(false);
	int nBrowseFileNum =m_pBtParam->m_listHistoryCall_Riceived.size();
	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM_NEW;

	if (nFrom < 0)
		nFrom = 0;

	m_nCallLogBrowseFrom = nFrom;

	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Riceived).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Riceived).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM_NEW; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
			setDataToUI_bt_aboutCallLogName_Displaying_New(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying_New(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying_New(k,it->CBTime);
			setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(k,3);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_1+k,true);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying_New( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying_New(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying_New(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(k,0);
		}
		
		k++;
	}
	setUpdateUI(true);
}

void CCallRecordPages::refreshHistoryCall_Dialed_New(int nFrom)
{
	setUpdateUI(false);
	int nBrowseFileNum =m_pBtParam->m_listHistoryCall_Dialed.size();
	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM_NEW;
	if (nFrom < 0)
		nFrom = 0;
       m_nCallLogBrowseFrom = nFrom;
	   
	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Dialed).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Dialed).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM_NEW; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
			setDataToUI_bt_aboutCallLogName_Displaying_New(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying_New(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying_New(k,it->CBTime);
			setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(k,1);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_1+k,true);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying_New( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying_New(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying_New(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(k,0);
		}
		
		k++;
	}
	setUpdateUI(true);
}

void CCallRecordPages::refreshHistoryCall_Miss_New(int nFrom)
{
	setUpdateUI(false);
	int nBrowseFileNum =m_pBtParam->m_listHistoryCall_Miss.size();
	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_LIST_DISPLAY_NUM_NEW;

	if (nFrom < 0)
		nFrom = 0;

	m_nCallLogBrowseFrom = nFrom;

	int i = 0, j = 0, k = 0;
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall_Miss).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall_Miss).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
	
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_LIST_DISPLAY_NUM_NEW; i++)
	{     
		if (j >= nFrom && it != itTo)
		{
			setDataToUI_bt_aboutCallLogName_Displaying_New(k,it->szUserName);
			setDataToUI_bt_aboutCallLogNumber_Displaying_New(k,it->szUserNo);
			setDataToUI_bt_aboutCallLogCallTime_Displaying_New(k,it->CBTime);
			setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(k,2);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MOBILE_NEW_RECORD_MULTIBUTTON_1+k,true);
			it++, j++;
		}
		else
		{
			setDataToUI_bt_aboutCallLogName_Displaying_New( k, (char *)"");
			setDataToUI_bt_aboutCallLogNumber_Displaying_New(k,(char *)"");
			setDataToUI_bt_aboutCallLogCallTime_Displaying_New(k,(char *)"");
			setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(k,0);
		}
		k++;
	}
	setUpdateUI(true);
}


void CCallRecordPages::clickPrePage_New(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nPreStartBrowse = -1;
			nPreStartBrowse = m_nCallLogBrowseFrom;
			m_nCallLogBrowseFrom = max(0, m_nCallLogBrowseFrom - SEARCH_LIST_DISPLAY_NUM_NEW);

			if (nPreStartBrowse == m_nCallLogBrowseFrom)
				return;

			EM_SYNC_PHONEBOOK_PATH em = m_pBtParam->m_iselectPhoneBook;
            if(em == BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY){
				refreshHistoryCall_Riceived_New(m_nCallLogBrowseFrom);
            }
			else if(em == BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY){
				refreshHistoryCall_Dialed_New(m_nCallLogBrowseFrom);
			}
			else if(em == BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY){
				refreshHistoryCall_Miss_New(m_nCallLogBrowseFrom);
			}
			else if(em == BT_PBAP_SYNC_PATH_ALL_CALLHISTORY){
				refreshHistoryCall_All_New(m_nCallLogBrowseFrom);
			}
		}
		break;
	default:
		break;
	}
}

void CCallRecordPages::clickNextPage_New(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nNextStartBrowse = -1;
			nNextStartBrowse = m_nCallLogBrowseFrom;

			m_nCallLogBrowseFrom += SEARCH_LIST_DISPLAY_NUM_NEW;

			EM_SYNC_PHONEBOOK_PATH em = m_pBtParam->m_iselectPhoneBook;
			if(em == BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY)
			{
			    if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall_Riceived.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM_NEW;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;
				refreshHistoryCall_Riceived_New(m_nCallLogBrowseFrom);

			}
			else if(em == BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY)
			{
			 	if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall_Dialed.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM_NEW;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;
				
				refreshHistoryCall_Dialed_New(m_nCallLogBrowseFrom);
			}
			else if(em == BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY)
			{
				if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall_Miss.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM_NEW;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;

				refreshHistoryCall_Miss_New(m_nCallLogBrowseFrom);
			}
			else if(em == BT_PBAP_SYNC_PATH_ALL_CALLHISTORY)
			{
				if (m_nCallLogBrowseFrom >= (int)m_pBtParam->m_listHistoryCall.size())
					m_nCallLogBrowseFrom -= SEARCH_LIST_DISPLAY_NUM_NEW;
				   
				if(nNextStartBrowse == m_nCallLogBrowseFrom)
					return;

				refreshHistoryCall_All_New(m_nCallLogBrowseFrom);
			}
		}
		break;
	default:
		break;
	}
}

void CCallRecordPages::getAndShowCallRecords_New(EM_SYNC_PHONEBOOK_PATH RecordType)
{
	switch(RecordType)
	{
		case BT_PBAP_SYNC_PATH_ALL_CALLHISTORY:
			refreshHistoryCall_All_New(0);
			break;
		case BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY:
			refreshHistoryCall_Riceived_New(0);
			break;
		case BT_PBAP_SYNC_PATH_DIALED_CALLHISTORY:
			refreshHistoryCall_Dialed_New(0);
			break;
		case BT_PBAP_SYNC_PATH_MISSED_CALLHISTORY:
			refreshHistoryCall_Miss_New(0);
			break;
		default:break;
	}
}


