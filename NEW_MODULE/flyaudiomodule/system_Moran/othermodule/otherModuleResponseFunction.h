#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

//Key Param Define
#define SYSTEM_KEY_PARAM_SETUP   		 0x13
#define SYSTEM_KEY_PARAM_DIM    		 0x33
#define SYSTEM_KEY_PARAM_TUNEPRESS   	 0x3a
#define SYSTEM_KEY_PARAM_TUNEPRESSLONG   0x4a
//custom apk set
#define SYSTEM_KEY_PARAM_CUSTOM_APK_1		0xD1
#define SYSTEM_KEY_PARAM_CUSTOM_APK_2		0xD2
#define SYSTEM_KEY_PARAM_CUSTOM_APK_3		0xD3

//System Cmd Define
#define SYSTEM_NOTIFY_ACC_ON             0x30
#define SYSTEM_NOTIFY_ACC_OFF            0x31

#define SYS_JUMP_PRE_PAGE 		0xFFFF //Back Pre Page

#define SYS_THIRD_PAGE_BACK 	0xFFFE//Third Page Back
#define SYS_ENTER_HOME_PAGE 	0xFFFD //Enter Home Page
#define SYS_INVALID_PAGE    	0xFFFC //Invalid Page
#define SYS_SET_PRE_PAGE    	0xFFFB
#define SYS_EQ_AUDIO_PRE_PAGE  	0xFFFA //EQ AUDIO PAGE  Back
//2011-03-13
#define SYS_THIRD_PAGE_BACK_NO_HOME_PAGE 0xFFF9 //Enter No Home Page
//2012-04-05
#define SYS_AUX_TEMP_PAGE 0xFFF8
// 2012.05.17
#define SYS_BT_MUSIC_PAGE 0xFFF7
#define SYS_DVD_PAGE   	  0xFFF6
#define SYS_BACK_PAGE     0xFFF5
#define SYS_DVR_PAGE	  0xFFF4
#define SYS_SETUP_PERSONALIZATION_PRE_PAGE 0xFFF3
#define SYS_BT_MAIN_PAGE 0xFFF2
#define SYS_SETUP_COMFORTABLE_CONVERIENT_PRE_PAGE 0xFFF1
#define SYS_EXTCAR_PARKING_ASSIST_PAGE  0xFFF0
#define SYS_EXTCAR_MCS_PAGE  0xFFE0


//Switch Module, Page ,Pre Page
void anyModuleToSysModue_Dispatch_Msg(moduleid_t sendModuleId,char *pBuf, int nLen);
void anyModuleToSysModule_Switch_Module(char cFromModule); //Switch Module
void anyModuleToSysModule_Switch_PrePage(); //Switch Pre Page

u8 SystemModule_InquiryCurModuleID();

void switch_Page(u16 pageId);

void androidKeyMessageDeliverControllor(u16 pageId);

//Key Dispatch Msg
void KeyModuleToSysModule_Dispatch_Msg(char *pBuf, int nLen);
void SystemModule_Process_KeyParam_Setup();
void SystemModule_Process_KeyParam_Dim();
void SystemModule_Process_KeyParam_TunePress();
void SystemModule_Process_KeyParam_TunePressLong();

void SystemModule_Process_KeyParam_AV();
void SystemModule_Process_KeyParam_NIFO();
void SystemModule_FromKeyParam_KEYVAL_SLEEP_NewStandbyMode();
void SystemModule_FromKeyParam_KEYVAL_SLEEP();
void SystemModule_FromKeyParam_SmartFan_Telecontrol(u8 cmd);
void SystemModule_FromKeyParam_LCD_Telecontrol(u8 cmd);
void SystemModule_FromKeyParam_FanMode_PerformanceSwitch(u8 cmd);
void SystemModule_FromKeyParam_AntotoItsOpen(u8 cmd);

void BlueModuleToSysModule_Dispatch_Msg(u8 *pBuf, int nLen);

//BackCar Disatch Msg
void BackCarModuleToSysModule_Dispatch_Msg(char *pBuf, int nLen);

//extcar  Disatch Msg
void ExtcarModuleToSysModule_Dispatch_Msg(u8 *pBuf, int nLen);
void ExternalCtrlModuleToSysModule_Dispatch_Msg(u8 *pBuf, int nLen);

void RadarMsgDispose(u8 *pBuf, int nLen);

//Center Dispatch Msg
void CenterModuleToSysModule_Dispatch_Msg(char *pBuf, int nLen);
void SystemModule_brightLCD(unsigned char buf);
void DisplayAllBarCode();
void SystemModuleToAUX_DisplaySystemTime();

void SendPageTableOSDDebug(void);
void displayPageTable();
void insert_pageToTable(u16 pageId);
void empty_pageToTable();
u16 delete_pageFromTable(void);
u16 getPrePage(void);
u16 getCurPage(void);

bool IsFlyPartyPage(u16 pageId);
u16 process_Back_PrePage_TUGUAN(u16 prePage);
void BaseModuleSwitchPage(char cModule);
void jumpToPage(u16 pageid);

bool Check_SupportA2DP();
char Inquiry_Module(char cmap);
void insert_moduleToTable(char cModule);
void displayTable();
void InitModuleTable();
void GetNextModule(char cModule);
bool Check_WhetherCanJump(u16 u16_NewPageID);

void SystemToSpecificModuleFromAudioVideoChannel(u16 u16_LeavePage,u16 u16_EnterPage);

void RadarInfo(u8 param);

void OsdModuleToSysModule_Dispatch_Msg(u8 *pBuf, int nLen);
void moduleToSystem_FromAutomate(u8 *param, int len);
void moduleToSystem_FromAudiovideo(u8 *param, int len);
void moduleToSystem_FromRemoteOnline(u8 *param, int len);
void moduleToSystem_FromDVR(u8 *param, int len);

bool getCurDeviceTop(int *nTop,char p);
char Inquiry_Device(char cmap);
void insert_deviceToTable(char cDevice);
void DevicedisplayTable();
void InitDeviceTable();
void SwitchDevice(char cDevice);
void SetLastDevice(char cDevice);
void SetNextDevice(char cDevice);
void systemToHal_setExternalDevice(void);

//zhq add  triggertype
char Backcar_Trigger_Type(char cmap);
void Insert_TriggerTypeToTable(char cType);
void TriggerTypedisplayTable();
void InitTriggerTypeTable();
void systemToHal_setTriggerType();
bool getCurTriggerTypeHead(int *nTop,char p);
void SetLastTriggerType(char cType);
void SetNextTriggerType(char cType);

u16 CurBtA2dpIsSupport_CheckBackKeyJumpPage(u16 pageId);
u16 getCurFlyPage();
void SystemModule_TimeFormat(u8 t);
void analyseFormSdkMessage(u8 *param, int len);
void moduleToSystem_FromRadio(u8 *param, int len);
void analysePublicCarInfoToSystemSet(u8 *p,u8 len);

void getAmbientLedColorValue(u8 param);
void getAmbientLedBrightnessValue(u8 *param);
void ImprovingtheRecognitionRateOfMic_aboutFord(u8 p);

void getExtcarPublicMultiContouredSeatsMessage(u8 *p,u8 len);
void SeatPressurePercentageUpperLumbar(u8 p1,u8 p2);
void SeatPressurePercentageMiddleLumbar(u8 p1,u8 p2);
void SeatPressurePercentageLowerLumbar(u8 p1,u8 p2);
void SeatPressurePercentageUpperBolster(u8 p1,u8 p2);
void SeatPressurePercentageLowerBolster(u8 p1,u8 p2);
void SeatIntensityLumbarMassage(u8 p1,u8 p2);
void SeatIntensityCushionMassage(u8 p1,u8 p2);
void SeatSideMassage(u8 p);
void SeatActiveSeatControlSelectMassage(u8 p1,u8 p2);
void SeatMultiCOntouredAvailableMassage(u8 p);

void UI_Display_MassageIntensityLumbarAndCushion(u8 side);
void UI_Display_Select(u8 p1,u8 p2);

#endif
