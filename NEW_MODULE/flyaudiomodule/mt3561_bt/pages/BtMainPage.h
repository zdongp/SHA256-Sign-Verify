#pragma once
#include "BtParam.h"

class CBtApp;
class CBtModule;
class CBtHal;
class CBtParam;

class CBtMainPage :
	public CFlyApp
{
public:
	CBtMainPage(void);
	virtual ~CBtMainPage(void);

public:
	//init
	virtual void init(void);
	virtual void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);
	bool pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	void initUi(void);
	/*******************************Page Function*************************************/
	
	/*******************************Other Function*************************************/
	void refreshLocalBtDeviceVersion(char* BtVersion,int len);
	void refreshRemodeBtDeviceName(u8 *param,u32 len);
	void showCallInOrCallOutInfoPanel(bool bShow, ST_PHONE_NUM *pstPhoneNum);
	void DisplayInputDialPhoneTextPrompt(E_BT_PHONE_STATUS nCallState);
	void refreshPhoneNumInput(char *p, u32 len);
	void DisplayingMuteButtonState();
	void refreshBTAudioFromFlyDeviceOrFromMobile(char cFlag);
	void refreshBTManyCallInfo(int cFlag);
	void refreshAnswerHandup(E_BT_PHONE_STATUS e);
	void AddCallsToUI(bool bState);
	void clickEntrance(E_MOUSE_STATUS e);
	void clickGoBack(E_MOUSE_STATUS e);
	void clickDeviceMainPageEntrance(E_MOUSE_STATUS e);
	void clickCallHistoryPageEntrance(E_MOUSE_STATUS e);
	void clickPhoneBookPageEntrance(E_MOUSE_STATUS e);
	void clickBtSettingPageEntrance(E_MOUSE_STATUS e);
	void clickDialPanel(u32 id, E_MOUSE_STATUS e);
	void clickBackspace(E_MOUSE_STATUS e);
	void clickAnswer(E_MOUSE_STATUS e);
	void ActShowCallingInfor_aboutWhenOnlyOneCall(E_BT_PHONE_STATUS nCallState,bool bShowInputNumbDialog,bool bShowName_Prompt,s8 *strName,s8 *strNumber);
	void DisplayInputDialPhoneName(s8 *str_name);
	void DisplayInputDialPhoneNumber(s8 *str_number);
	void clickHandup(E_MOUSE_STATUS e);
	void clickBtPower(E_MOUSE_STATUS e);
	void clickAudioFromMobile(E_MOUSE_STATUS e);
	void clickAudioFromFlyDevice(E_MOUSE_STATUS e);
	void clickCalling_MicMute(E_MOUSE_STATUS e);
	void clickSwitchCall(E_MOUSE_STATUS e);
	void clickAddCalls(E_MOUSE_STATUS e);
	void clickMergeCalls(E_MOUSE_STATUS e);
	void clickPhonePairing(E_MOUSE_STATUS e);
	void clickUsingWhichDevice(u8 param,E_MOUSE_STATUS e);

public:
	void clickOpenAllModule_debug(char *param);
public:
	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;

};
