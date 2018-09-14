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
	void clearCallHistoryTypeStatus(void);
	void clickPrePage(E_MOUSE_STATUS e);
	void clickNextPage(E_MOUSE_STATUS e);
	void clickRecordItem(int index, E_MOUSE_STATUS e);
	void control_CallLogs(int param,E_MOUSE_STATUS e);
	void getAndShowCallRecords(EM_SYNC_PHONEBOOK_PATH RecordType);
	void createListHistoryCall(void);
	void annalyListHistoryCall(void);
	void refreshHistoryCall_All(int nFrom);
	void setDataToUI_bt_aboutCallLogName_Displaying(int nPos,char *buff);
	void setDataToUI_bt_aboutCallLogNumber_Displaying(int nPos,char *buff);
	void setDataToUI_bt_aboutCallLogCallTime_Displaying(int nPos,char *buff);
	void setDataToUI_bt_aboutCallLogClassIcon_Displaying(int nPos,int Icon);
	void refreshHistoryCall_Riceived(int nFrom);
	void refreshHistoryCall_Dialed(int nFrom);
	void refreshHistoryCall_Miss(int nFrom);
	void showLoadingCallLogTips(u32 strTips);
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
		int m_nCallLogBrowseFrom ;
public:

	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;



};