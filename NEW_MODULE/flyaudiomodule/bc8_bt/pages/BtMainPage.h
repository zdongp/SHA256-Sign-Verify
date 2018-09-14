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
	//main page
	void clickEntrance(E_MOUSE_STATUS e);
	void clickEntranceBtMainPage(E_MOUSE_STATUS e);
	void clickGoBack(E_MOUSE_STATUS e);
	void clickDeviceMainPageEntrance(E_MOUSE_STATUS e);
	void clickPhoneBookPageEntrance(E_MOUSE_STATUS e);
	void clickCallHistoryPageEntrance(E_MOUSE_STATUS e);
	void clickBtSettingPageEntrance(E_MOUSE_STATUS e);

	void clickDialPanel(u32 id, E_MOUSE_STATUS e);
	void clickBackspace(E_MOUSE_STATUS e);
	void clickAnswer(E_MOUSE_STATUS e);
	void clickHandup(E_MOUSE_STATUS e);
	void clickBtPower(E_MOUSE_STATUS e);
	void clickAudioFromFlyDevice(E_MOUSE_STATUS e);
	void clickAudioFromMobile(E_MOUSE_STATUS e);
	void clickCalling_MicMute(E_MOUSE_STATUS e);
	void clickSwitchCall(E_MOUSE_STATUS e);
	void clickMergeCalls(E_MOUSE_STATUS e);
	void clickAddCalls(E_MOUSE_STATUS e);
  	void DisplayingMuteButtonState();
	
	void refreshPhoneNumInput(char *p, u32 len);
	void refreshPhoneOrCarAnswer(E_HFP_AUDIO_SOURCE e);
	void refreshAnswerHandup(E_BT_PHONE_STATUS e);

	void refreshLocalBtDeviceVersion(char* BtVersion,int len);
	void refreshRemodeBtDeviceName(u8 *param,u32 len);
	void showCallInOrCallOutInfoPanel(bool bShow, ST_PHONE_NUM *pstPhoneNum);
	void DisplayInputDialPhoneTextPrompt(E_BT_PHONE_STATUS nCallState);
	void refreshBTAudioFromFlyDeviceOrFromMobile(E_HFP_AUDIO_SOURCE cFlag);
	void refreshBTManyCallInfo(int cFlag);
	void clickPhonePairing(E_MOUSE_STATUS e);
	void ShowOrHid_PhonePair_PromptBox(int cFlag);

	void clickOpenAllModule_debug(char *param);
	void clickBtAboutDialInFunction_IntermediateProcessing();
	void clickOpenBtMicGainTest(char *param);

public://BC8
	void DisplayInputDialPhoneNumber(s8 *str_number);
	void DisplayInputDialPhoneName(s8 *str_name);
	void ActShowCallingInfor_aboutWhenOnlyOneCall(E_BT_PHONE_STATUS nCallState,bool bShowInputNumbDialog,bool bShowName_Prompt,s8 *strName,s8 *strNumber);
	void AddCallsToUI(bool bState);
	void SwitchCallsToUI(bool bState);
	void SpecialProblems_DuringAcallling_TheSecondPhoneCalling_SuddenlyGetHandleUpInfor();
	void CallingAndWaitingFunction_DisplayingToUI(E_CUR_MULTI_HELD_STATE em);
	void UI_Parrot_ManyPeopleCall_2(u32 strFlag);
	void UI_Parrot_ManyPeopleCall_1(u32 strFlag);
	void AddCallsAndMergeButtonSwitchToUI(bool bItsCtrable);
	void DisplayingMergeButtonToUI(int nAnalog);
	void btVoiceRecgCtl(E_MOUSE_STATUS e);
	void IncomingCallWindowPromt(E_BT_PHONE_STATUS s,bool b,u32 pageID);
	void PopUp_V_Scereen_showDailingInformations(bool v,E_BT_PHONE_STATUS s,ST_PHONE_NUM *pstPhoneNum);
	void showCallInTalkingKeyboardHiddenButton(u8 param);
	void showOrHiddenTalkingPopUp(bool p);
	
	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;

};
