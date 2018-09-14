#ifndef __APP_RESPONSE_FUNCTION_SYS_H
#define __APP_RESPONSE_FUNCTION_SYS_H

#include "param.h"

//Menu Page
void appToSys_Menu_Function_MouseUp(u32 u32CtrlID);


void appToSys_Menu_SetUp_MouseUp(void);

void appToSys_Menu_Style_MouseUp(void);
//------------------------------------------------------
void appToSys_Menu_DayNight_MouseUp(void);
void appToSys_Menu_NightDay_MouseUp(u8 buf);

void appToSys_Menu_Off_MouseUp(void);
void appToSys_Menu_Dark_MouseUp(void);
void appToSys_Menu_Middle_MouseUp(void);
void appToSys_Menu_Light_MouseUp(void);
void appToSys_Menu_High_Light_MouseUp(void);

//Set Up Jump Page Begin or End
void appToSys_Setup_JumpPage_MouseUp(short PageID); //Jump Page
void appToSys_Setup_Back_MouseUp();

//Setup Next Pre Page
void appToSys_Setup_PrevPage_MouseUp(void);
void appToSys_Setup_NextPage_MouseUp(void);

//Setup System 
void appToSys_Setup_Info_MouseUp(void);
void appToSys_Setup_Screen_MouseUp(void);
void appToSys_Setup_SysReset_MouseUp(void);
void appToSys_Setup_SysUpdate_MouseUp(void);
void appToUiDialogDisplaying_aboutSysUpdate(bool bSign);
void appToSys_Setup_DynamicLogoStyle(int nParam);
void appToSys_Setup_Default_DynamicLogoStyle_Ok(void);


//Setup Steering Wheel
void appToSys_Setup_WheelChoose_Up_MouseUp(void);
void appToSys_Setup_WheelChoose_Down_MouseUp(void);

void appToSys_Setup_WheelLearn_MouseUp(void);
void appToSys_Setup_WheelLearn_ON_MouseUp(void);
void appToSys_Setup_WheelLearn_OFF_MouseUp(void);
void appToSys_Setup_WheelLearn(void);
//---------------------------2012-2-29---------------------------
void appToSys_Setup_WheelLearn_Mode(void);
void appToSys_Setup_WheelLearn_Mute(void);
void appToSys_Setup_WheelLearn_Seek_inc(void);
void appToSys_Setup_WheelLearn_Seek_dec(void);
void appToSys_Setup_WheelLearn_vol_inc(void);
void appToSys_Setup_WheelLearn_vol_dec(void);
void appToSys_Setup_WheelLearn_bt_hand_up(void);
void appToSys_Setup_WheelLearn_bt_call_in(void);
void appToSys_Setup_WheelLearn_Apply(void);
void appToSys_Setup_WheelLearn_Back(void);

void appToSys_Setup_WheelLearn_Delete(void);



void appToSys_handleWheel_CtrlDown(u32 CtrlId);
void appToSys_handleWheel_CtrlUp(u32 ctrlId);

void appToSys_handleUp(u32 ctrlId,u8 u8_MouseStatus,u8 *param,u8 paramLen);
void appToSys_handleTimer(u32 ctrlId,u8 u8_MouseStatus,u8 *param,u8 paramLen);
void appToSys_handleCancel(u32 ctrlId,u8 u8_MouseStatus,u8 *param,u8 paramLen);

//2012 3-7
void apptoSys_hadleDown(u32 ctrlId,u8 u8_MouseStatus,u8 *param,u8 paramLen);

void appTosys_handleResetSystem(u32 ctrlId);
void appTosys_handleSwitchPage(u32 ctrlId);
//Setup Communication

//Setup Function
void appToSys_Setup_BackCarCamaera_ON_MouseUp(void);
void appToSys_Setup_BackCarCamaera_OFF_MouseUp(void);
void appToSys_Setup_LightDetect_ON_MouseUp(void);
void appToSys_Setup_LightDetect_OFF_MouseUp(void);
void appToSys_Setup_BackCarRefLineDisplay_IS_MouseUp();
void appToSys_Setup_BackCarRefLineDisplay_NO_MouseUp();
void appToSys_Setup_BackCarRefLineDisplaySwitch_MouseUp();

void appToSys_Setup_BackCarTraceLineDisplay_IS_MouseUp();
void appToSys_Setup_BackCarTraceLineDisplay_NO_MouseUp();

void appToSys_Setup_BrakeCarDetect_ON_MouseUp(void);
void appToSys_Setup_BrakeCarDetect_OFF_MouseUp(void);
bool IsCanSwitchVideoPage_WhenTheBrakeDownTime(u8 uCmd1,u8 uCmd2);

void appToSys_Setup_Amplifier_ON_MouseUp(void);
void appToSys_Setup_Amplifier_OFF_MouseUp(void);

void appToSys_Setup_PanelLight_Up_MouseUp(void);
void appToSys_Setup_PanelLight_Down_MouseUp(void);

//zhq  DNV
void appToSys_Setup_DNVCamaera_ON_MouseUp(void);
void appToSys_Setup_DNVCamaera_OFF_MouseUp(void);



//Setup Power Vol
void appToSys_Setup_PowerVol_Up_MouseUp(void);
void appToSys_Setup_PowerVol_Down_MouseUp(void);

void appToSys_Setup_Demo(void);

//Setup Multimedia
void appToSys_Setup_IpodSet_ON_MouseUp(void);
void appToSys_Setup_IpodSet_OFF_MouseUp(void);
void appToSys_Setup_TVSet_ON_MouseUp(void);
void appToSys_Setup_TVSet_OFF_MouseUp(void);



void appToSys_Setup_DvdRegionCode_Up_MouseUp(void);
void appToSys_Setup_DvdRegionCode_Down_MouseUp(void);

void appToSys_Setup_MultiRadio_Up_MouseUp(void);
void appToSys_Setup_MultiRadio_Down_MouseUp(void);


//Setup GPSRun
void appToSys_Setup_AutoGPS_ON_MouseUp(void);
void appToSys_Setup_AutoGPS_OFF_MouseUp(void);
void appToSys_Setup_GPSVoicePrompt_ON_MouseUp(void);
void appToSys_Setup_GPSVoicePrompt_OFF_MouseUp(void);


//Setup Time
void appToSys_Setup_TimeSet_MouseUp(void);

void appToSys_Setup_Hour_24_ON_MouseUp(void);
void appToSys_Setup_Hour_24_OFF_MouseUp(void);

void appToSys_Setup_TimeZoneChoose_Up_MouseUp(void);
void appToSys_Setup_TimeZoneChoose_Down_MouseUp(void);

//Setup Style
void appToSys_Setup_SysStyleSet_MouseUp(void);
void appToSys_Setup_LanguageSet_MouseUp(void);

//Copyright
void appToSys_Copyright_MouseUp(void);
void appToSys_Copyright_Back_MouseUp(void);


//Time Set
void appToSys_TimeSet_Year_Prev(void);
void appToSys_TimeSet_Year_Next(void);
void appToSys_TimeSet_Month_Prev(void);
void appToSys_TimeSet_Month_Next(void);
void appToSys_TimeSet_Day_Prev(void);
void appToSys_TimeSet_Day_Next(void);
void appToSys_TimeSet_Hour_Prev(void);
void appToSys_TimeSet_Hour_Next(void);
void appToSys_TimeSet_Minute_Prev(void);
void appToSys_TimeSet_Minute_Next(void);
void appToSys_TimeSet_Second_Prev(void);
void appToSys_TimeSet_Second_Next(void);
void appToSys_TimeSet_Back_MouseUp(void);
void appTosys_Setup_OsdDebugInfo_switch(void);
void appTosys_Setup_ModuleDebugInfo_switch(void);

//add 2013-05-02:
void appToSys_Setup_MouseUp(u32 controlID);
void appToSys_Setup_TvOrDvrSwitchON_MouseUp(void);
void appToSys_Setup_TvOrDvrSwitchOFF_MouseUp(void);
void appToSys_Setup_CarinfoAudioCueON(void);
void appToSys_Setup_CarinfoAudioCueOFF(void);
void appToSys_Setup_CarinfoVoice(u8 state);
void appToSys_Setup_TV_DVR_TPMS_UpOrDownSwitch(int nParam);
void appToSys_Setup_GPS_BOOT_RUN_UpOrDownSwitch(int nParam);
void ToUI_SwitchOne_about_SetupIsRunningNavigationStr(int nParam);
void appToSys_Setup_BootOn_IsAutoPlay(int nParam);
void appToSys_Setup_BootOn_IsAutoPlay_ON_MouseUp();
void appToSys_Setup_BootOn_IsAutoPlay_OFF_MouseUp();



//?�̨�3?��??������??��?����|
void appToSys_Setup_SysResetDialogOKOrCANCEL_MouseUp(u8 state);
//?�̨�3��y??������??��?����|
void appToSys_Setup_SysUpdateDialogOKOrCANCEL_MouseUp(u8 state);
void appToSys_Setup_SysRestoreFactory_MouseUp();
void appToUiDialogDisplaying_aboutRestoreFactory(bool bSign);
void appToSys_Setup_SysRestoreFactoryOKOrCANCEL_MouseUp(u8 state);
void appToUiDialogDisplaying_aboutSysReset(bool bSign);
void appToUiDialogDisplaying_aboutSysUpdate(bool bSign);

void appToSys_Setup_SysCarModulesOKOrCANCEL_MouseUp(u32 controlID);
void DisplayingOrHidingSysCarModules(u8 state);
void appToSys_Setup_CarModelChoose_Up_MouseUp();
void appToSys_Setup_CarModelChoose_Down_MouseUp();
void appToSys_Setup_CarModelChoose_OK_MouseUp();


void appToSys_MatchingModulePageOkOrCancel_MouseUp(u32 ctrlId);


void appToSys_Setup_AUDIO_AUTO_SOUND_ON_MouseUp();
void appToSys_Setup_AUDIO_AUTO_SOUND_OFF_MouseUp();


void appToSys_Setup_Default_NaviGation(int nParam);


void appToSys_Setup_Default_NaviGation_Ok(void );

void appToSys_Setup_Default_Navigation_ShowHide(void);

// setting system
void appToSys_Setup_System_Fan_Up(void);
void appToSys_Setup_System_Fan_Down(void);
void SystemModuleToUI_aboutFanMode(E_FAN_MODE FanMode);

void appToSys_Setup_System_VoltageProtection_Up(void);
void appTSys_Setup_System_VoltageProtection_Down(void);


void appToSys_SetLCD_MouseUp(u32 ctrlId,u8 *param,u8 paramLen);
void appToSys_Set_Brightness_Dim_UpOrDown(u32 ctrlId);
void appToSys_Set_Brightness_Moderate_UpOrDown(u32 ctrlId);
void appToSys_Set_Brightness_Bright_UpOrDown(u32 ctrlId);
void appToSys_set_Brightness_scrolling(u8 *param,u8 paramLen);
void appToUI_Set_Brightness(u8 param,u8 param1);
void appToSys_Set_Brightness_Displaying(u32 CtrlID,u8 param);

//倒车模式
void clickSettingNormalPageBackCarMode(u8 p/*1 u, 0 d*/);
void click_Setup_Backcar_TriggerType_Up(void);
void click_Setup_Backcar_TriggerType_Down(void);

void UiDisplay_System_BackCarVideoSwitch(u8 uParam);
void appToSys_Setup_Backcar_TriggerType_UpOrDownSwitch(int nParam);

void appToSys_Setup_IsAutoMate_ON_MouseUp(void);
void appToSys_Setup_IsAutoMate_OFF_MouseUp(void);
void DisplayAutoMateSwitchButtonUI(bool status);

void appToSys_Setup_BackCar_CVBS_Or_USB_MouseUp(u8 p);
void DisplaySysToUI_aboutBackCarProtocolCVBSorUSB(u8 p);
void appToSys_Setup_BackCar_CVBS_Or_USB_OK_MouseUp();
void appToSys_Setup_SysBACKCAR_SET_CVBS_OR_USB_PROMPT_OKOrCANCEL_MouseUp(u8 p);

void appToSys_Setup_NaviMixLow_ON_MouseUp();
void appToSys_Setup_NaviMixLow_OFF_MouseUp();
void DisplaySysToUI_aboutNaviMixLow(bool b);

void UI_DVR_Protocol_Mode();
void Set_Dvr_ProtocolMode(u8 p);
void appToSys_Setup_Dvr_set_protocol_mode();

void systemToHalAboutAmbientLed_Init(u8 p);
void systemToHalAboutAmbientLed_Switch(u8 p);
void systemToHalAboutAmbientLed_Dimming(u8 p);
void systemToHalAboutAmbientLed_SetRGB(u8 *p,u8 len);
void appToSys_AmbientLed_SetUp_MouseUp(void);
void appToSys_AmbientLed_Back_MouseUp(void);
void appToSys_AmbientLed_Switch_MouseUp(void);
void appToSys_AmbientLed_Commission_MouseUp(u8 p);
void appToSys_AmbientLed_R_MouseUp(u8 p,E_AMBIENT_LED_RGB em);
void appToSys_AmbientLed_G_MouseUp(u8 p,E_AMBIENT_LED_RGB em);
void appToSys_AmbientLed_B_MouseUp(u8 p,E_AMBIENT_LED_RGB em);
void appToSys_AmbientLed_DIMMING_MouseUp(u8 p);
bool GetRGBByLedCommissionMapping(u8 *R,u8 *G,u8 *B,u8 uTPYE);
void DisplayUI_AmbientLed_SwitchButton(u8 p);
void DisplayUI_AmbientLed_CommissionButton(E_AMBIENT_LED_COMMISSION em);
void DisplayUI_AmbientLed_PreviewPaper(u8 p);
void DisplayUI_AmbientLed_R_bar_text(u8 p);
void DisplayUI_AmbientLed_G_bar_text(u8 p);
void DisplayUI_AmbientLed_B_bar_text(u8 p);
void DisplayUI_AmbientLed_Dimming_bar_text(u8 p);

E_AMBIENT_LED_COMMISSION GetTypeByLedCommissionMapping(u8 r,u8 g,u8 b);
void AmbientLed_setCommissionValue(u8 p);

void setRGBValueToUI(u8 pR,u8 pG,u8 pB);
void setR_G_B_BarValue(u8 temp,u8 tag );
void jumpToPageSetRGB();
void setCustomizeColorAndDimming(SAVE_RGB_DIMMING_VALUE t);
SAVE_RGB_DIMMING_VALUE saveCustomizeColorVale(u8 *param,u8 nTem,u8 nDimming);
void initCustomizeColorButen();

void appToSys_Set_Screen_Brightness_value(u8 p);
void ToUI_BackCarVideo_TraceType_System(u8 em);
void DisplayUI_aboutBackCar_Line_Type(u8 p);

void DisplayBackcarReflineSwitch(u8 p);
void DisplayNewBackcarReflineSwitch(u8 p);

void DisplayingOrHidingSysUI_aboutReversingCameraEquipment(u8 state);
void SetDayAndNightMode(u8 buf);
void showDayOrNightModeStatus(u8 buf);
void DisPlayingReverseCameraType(u8 p);
void appToSys_Setup_Reverse_Camera_MouseUp(u8 p);
void appToSys_Setup_Panel_Light_Bar_MouseUp(u8 param);
void appToSys_Setup_Panel_Light_Button_MouseUp();

void showPanelLightValue(u8 param);
void appToSys_Setup_Radio_Area_Selection_MouseUp(u8 param);
void appToSys_Setup_PowerVol_Bar_MouseUp(u8 param);
void appToSys_Setup_PowerVol_Bar_Jump_set(u8 param);

void appToSys_Setup_PowerVol_Bar_Mouse_Time(u8 param);
void appToSys_Setup_PowerVol_Bar_Mouse_Up(u8 param);


void systemToApp_SetPowerVol_BarMaxValue();
void appToSys_Setup_Default_Boot_Animation(u8 param);
void showDefault_Boot_Animation_Button(u8 param);
void setDefault_Boot_Animation_Prop(u8 param);
void getDefault_Boot_Animation_Prop();
void appToSystem_Setup_Boot_Run_Nav_status(u8 param);
void showBoot_Run_Nav_status(u8 param);

void setDefault_Boot_Nav_Baidu();
void setDefault_Boot_Nav_KaiLiDe();
void setDefault_Boot_Nav_GaoDe();
void setDefault_Boot_Nav_TengXun();
void showDefault_Boot_Nav(u8 param);
void showCurTempUnitType(u8 param);
void showCurDistanceUnitType(u8 param);
void showCameraDelaySwitchStatus(u8 param);
void appToSys_Sound_Channel_MouseUp(void);
void appToSys_Sound_Channel_Back(void);
void analyseAppToSystemSoundChannelMessage(u32 ctrlId,u8 param);
void showSoundChannelVolume_Bar( u32 ctrlId,u8 p);
void setSoundChannelVolumeValue(u32 ctrlId,u8 p);

void thirdDailingOption();
void showThirdDailingOption(u8 p);
void saveThirdDailingOption();

void appToSys_Setup_DesktopNavigationMapInformationsSyncSwitch_ON_MouseUp(void);
void appToSys_Setup_DesktopNavigationMapInformationsSyncSwitch_OFF_MouseUp(void);
void DisplayDesktopNavigationMapInformationsSyncSwitchButtonUI(bool b);
void appToSys_Setup_ScreenBrithnessAutoAdjust_Switch_MouseUp(u8 p);
void DisplayScreenBrithnessAutoAdjustSwitchButtonUI(bool b);

void appToSys_Setup_AmbientLedColorSet_MouseUp(u32 ctrlID);
u8 AmbientLed_ID_To_Data(u32 ID);
void DisplayUI_switch_AmbientLedColor_Ford(u8 p);
void DisplayUI_AmbientLedColorTxt_Ford(u8 p);
void DisplayUI_AmbientLedBrightnessValue_Ford(u16 param);
void Step_AmbientLedBrightnessScrollBar_Ford(u32 max);
void DisplayUI_AmbientLedBrightnessScrollBar_Ford(u32 param);
void appToSys_Setup_Ambient_Led_Brightness_Bar_Mouse_Time(u16 p);
void appToSys_Setup_Ambient_Led_Brightness_Bar_Mouse_Up(u16 p);
void DisplayUI_AmbientLedBrightnessEnable_Ford(bool b);

void appToSys_Setup_DistanceUint_Mouse_Up(u8 p);


void appToSys_Setup_MCS_Main_JumpPage_Touch_Screen(u8 s);
void appToSys_Setup_MCS_Adjust_JumpPage_Touch_Screen(u8 s);
void appToSys_Setup_MCS_Adjust_UpperLumbarPre_SCROLL_BAR_Touch_Screen(u8 s);
void appToSys_Setup_MCS_Adjust_UpperLumbarPre_Touch_Screen(u8 p,u8 s);
void appToSys_Setup_MCS_Adjust_MidLumbarPre_SCROLL_BAR_Touch_Screen(u8 s);
void appToSys_Setup_MCS_Adjust_MidLumbarPre_Touch_Screen(u8 p,u8 s);
void appToSys_Setup_MCS_Adjust_LowerLumbarPre_SCROLL_BAR_Touch_Screen(u8 s);
void appToSys_Setup_MCS_Adjust_LowerLumbarPre_Touch_Screen(u8 p,u8 s);
void appToSys_Setup_MCS_Adjust_UpperBolsterPre_SCROLL_BAR_Touch_Screen(u8 s);
void appToSys_Setup_MCS_Adjust_UpperBolsterPre_Touch_Screen(u8 p,u8 s);
void appToSys_Setup_MCS_Adjust_LowerBolsterPre_SCROLL_BAR_Touch_Screen(u8 s);
void appToSys_Setup_MCS_Adjust_LowerBolsterPre_Touch_Screen(u8 p,u8 s);
void appToSys_Setup_MCS_Adjust_DriverSide_Touch_Screen(u8 s);
void appToSys_Setup_MCS_Adjust_PassengerSide_Touch_Screen(u8 s);
void appToSys_Setup_MCS_Passage_JumpPage_Touch_Screen(u8 s);
void appToSys_Setup_MCS_Passage_UpperLumbarSet_Touch_Screen(u8 p,u8 s);
void appToSys_Setup_MCS_Passage_LowerLumbarSet_Touch_Screen(u8 p,u8 s);	
void appToSys_Setup_MCS_Passage_DriverSide_Touch_Screen(u8 s);
void appToSys_Setup_MCS_Passage_PassengerSide_Touch_Screen(u8 s);

void UI_Display_Adjust_UpperLumbarPre(u8 p1,u8 p2);
void UI_Display_Adjust_MidLumbarPre(u8 p1,u8 p2);
void UI_Display_Adjust_LowerLumbarPre(u8 p1,u8 p2);
void UI_Display_Adjust_UpperBolsterPre(u8 p1,u8 p2);
void UI_Display_Adjust_LowerBolsterPre(u8 p1,u8 p2);
void UI_Display_Adjust_DriverSide_State(u8 p);
void UI_Display_Adjust_PassengerSide_State(u8 p);
void UI_Display_Massage_Passage_UpperLumbarSelectedState(u8 p);
void UI_Display_Massage_Passage_UpperLumbarSet(u8 p);
void UI_Display_Massage_Passage_LowerLumbarSelectedState(u8 p);
void UI_Display_Massage_Passage_LowerLumbarSet(u8 p);
void UI_Display_Massage_Passage_DriverSide_State(u8 p);
void UI_Display_Massage_Passage_PassengerSide_State(u8 p);
void UI_Display_Select_Seats_Side(u8 p);
void UI_Display_MCS_MassageFunction_closing_PromptBox(u8 p);

u8 Seats_PercentageToIntegersValue(u8 p);

void showOrHideCarTypeBox(bool param);
void analyseSelectionCarTypeMessage(u8 param);
void confirmSelectionCurCarType();

#endif
