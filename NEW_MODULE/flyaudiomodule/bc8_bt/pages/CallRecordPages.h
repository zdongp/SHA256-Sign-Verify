#pragma once
#include "BtParam.h"


class CBtApp;
class CBtModule;
class CBtHal;
class CBtParam;

class CCallRecordPages :	public CFlyApp
{
public:
	CCallRecordPages(void);
	virtual ~CCallRecordPages(void);

public:
	//init
	 void init(void);
	 void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);

	void initUi(void);

	bool pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);

	void clickGoBack(E_MOUSE_STATUS e);
	void clickPrePage(E_MOUSE_STATUS e);
	void clickNextPage(E_MOUSE_STATUS e);
	void clickRecordItem(int index, E_MOUSE_STATUS e);
	void clickRecordType(E_MOUSE_STATUS e);

	void SwitchSelectRecordType(EM_SYNC_PHONEBOOK_PATH RecordType);
	void getAndShowCallRecords(EM_SYNC_PHONEBOOK_PATH RecordType);
	void control_CallLogs(int param,E_MOUSE_STATUS e);
	void setDataToUI_bt_aboutCallLogName_Displaying(int nPos,char *buff);
	void setDataToUI_bt_aboutCallLogNumber_Displaying(int nPos,char *buff);
	void setDataToUI_bt_aboutCallLogCallTime_Displaying(int nPos,char *buff);
	void setDataToUI_bt_aboutCallLogClassIcon_Displaying(int nPos,int Icon);
	//void setDataToUI_bt_aboutCallLogClassIcon_Displaying(int nPos,u8 uPBType,bool bItsShow);
	//void DisplayCallLog( int Pos );
	void refreshHistoryCall_All(int nFrom);
	void refreshHistoryCall_Dialed(int nFrom);
	void refreshHistoryCall_Riceived(int nFrom);
	void refreshHistoryCall_Miss(int nFrom);
	void createListHistoryCall(void);
	void clearCallHistoryTypeStatus(void);
	void callLogs_Type(int index);
	void showLoadingCallLogTips(u32 strTips);
	int m_nCallLogBrowseFrom ;
	void annalyListHistoryCall(void);

//BC8
public:
	void annalyListHistoryCall2(void);
	void clickPrePage2(E_MOUSE_STATUS e);
	void clickNextPage2(E_MOUSE_STATUS e);
	void clickRecordItem2(int index, E_MOUSE_STATUS e);
	void refreshHistoryCall_All_BC8(int nFrom);
	void refreshHistoryCall_Dialed_BC8(int nFrom);
	void refreshHistoryCall_Riceived_BC8(int nFrom);
	void refreshHistoryCall_Miss_BC8(int nFrom);
	void showListHistoryCall(void);
	
	void setDataToUI_bt_aboutCallLogName_Displaying_New(int nPos,char *buff);
	void setDataToUI_bt_aboutCallLogCallTime_Displaying_New(int nPos,char *buff);
	void setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(int nPos,int Icon);
	void setDataToUI_bt_aboutCallLogNumber_Displaying_New(int nPos,char *buff);
	void refreshHistoryCall_All_New(int nFrom);
	void refreshHistoryCall_Riceived_New(int nFrom);
	void refreshHistoryCall_Dialed_New(int nFrom);
	void refreshHistoryCall_Miss_New(int nFrom);
	void clickPrePage_New(E_MOUSE_STATUS e);
	void clickNextPage_New(E_MOUSE_STATUS e);
	void getAndShowCallRecords_New(EM_SYNC_PHONEBOOK_PATH RecordType);
public:

	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;



};