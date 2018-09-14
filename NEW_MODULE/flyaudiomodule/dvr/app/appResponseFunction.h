#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

#include "param.h"

void dvrToApp_SetDVRMenuEnable();
void dvrToApp_SetDVRMenuDisable();

void HaveDVREquipment();

//PAGE_DRIVING_RECORD_MENU  	0x4001
void appToDvr_Return_Button_MouseUp();
void appToDvr_Menu_Button_MouseUp();
void appToDvr_DVR_RECORD_VIDEO_Button_MouseUp();
void appToDvr_DVR_RECORD_MUTE_Button_MouseUp();
void appToDvr_DVR_RECORD_TIME_SET_Button_MouseUp();
void appToDvr_DVR_RECORD_SET_Button_MouseUp();
void appToDvr_DVR_RECORD_CODE_Button_MouseUp();
void appToDvr_DVR_RECORD_FOLDER_Button_MouseUp();
void appToDvr_DVR_RECORD_BACKGROUND_Button_MouseUp();


//PAGE_DRIVING_RECORD_TIME_SET  	0x4002
void appToDvr_TIME_SET_UP_Button_MouseUp();
void appToDvr_TIME_SET_DOWN_Button_MouseUp();
void appToDvr_TIME_SET_OK_Button_MouseUp();
void appToDvr_TIME_SET_SET_Button_MouseUp();
void appToDvr_TIME_SET_BACK_Button_MouseUp();

//PAGE_DRIVING_RECORD_SET	0x4003		
void appToDvr_SET_UP_Button_MouseUp();
void appToDvr_SET_DOWN_Button_MouseUp();
void appToDvr_SET_SURE_Button_MouseUp();
void appToDvr_SET_BACK_Button_MouseUp();

void appToDvr_PALY_UP_Button_MouseUp();
void appToDvr_PALY_PLAY_Button_MouseUp();
void appToDvr_PALY_NEXT_Button_MouseUp();
void appToDvr_PALY_CODE_Button_MouseUp();
void appToDvr_PALY_BACK_Button_MouseUp();
void appToDvr_PLAY_BACKGROUND_Button_MouseUp();


void appToDvr_VIDEO_BACKGROUND_Button_MouseUp();
void appToDvr_VIDEO_NoSign_Back_Button_MouseUp();

void appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_menu(int ctrlId,u8 ctrlType);
void appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_videoset(int ctrlId,u8 ctrlType);
void appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_folderplay(int ctrlId,u8 ctrlType);
void appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_timeset(int ctrlId,u8 ctrlType);


void appToDvr_Menu_Button_Camera_MouseUp();
void appToDvr_Menu_Button_Camera_Recording();
void appToDvr_Menu_Button_Camera_Photograph();

void dvrToApp_SetDVR_RecordingDisPlay(u8 status);

void appToDvr_Menu_Button_UsbCamera_YMD(u8 y, u8 month, u8 d);
void appToDvr_Menu_Button_UsbCamera_HMS(u8 h, u8 m, u8 s);

void appToDvr_UsbCameraVersion(u8 uId,u8 *param,u8 len);
void appToDvr_DVR_RECORD_SET_Button_Camera_MouseUp();
void appToDvr_Usb_Camera_Set_Resolution_Button(u8 param);
void appToDvr_Usb_Camera_Set_RecordingTimes_Button(u8 param);
void appToDvr_Usb_Camera_Set_StorageSize_Button(u8 param);
void appToDvr_Usb_Camera_Set_StoragePath_Button(u8 param);

void UI_Usb_Camera_Resolution(E_DVR_USB_CAMERA_RESOLUTION em);
void UI_Usb_Camera_Recording_Times(E_DVR_USB_CAMERA_RECORDING_TIMES em);
void UI_Usb_Camera_Storage_Size(E_DVR_USB_CAMERA_STORAGE_SIZE em);
void UI_Usb_Camera_Storage_Path(E_DVR_USB_CAMERA_STORAGE_PATH em);

void UI_Usb_Camera_ApplyButton_IsControllable(bool bState);
void DisplayUI_Usb_Camera_Storage_Path(u8 *param,int len);
void setAnsiSerialData(u32 id, u8 *p, u32 len);
void appToDvr_Usb_Camera_Setting_Apply();
void UI_Usb_Camera_Show_Setting_Info();

void applyUsbCaremaDataToDevice();
void UsbCameraParamVariable_Temp_To_Real();
void UsbCameraParamVariable_Real_To_Temp();
void UsbCameraParam_StorageFilePath_EM_To_String(E_DVR_USB_CAMERA_STORAGE_PATH em,char *str);
void UsbCameraParam_Resolution_EM_To_String();
void ToHal_DVR_USB_Carema_Resolution(E_DVR_USB_CAMERA_RESOLUTION em);
void ToHal_DVR_USB_Carema_StorageFilePath(E_DVR_USB_CAMERA_STORAGE_PATH em);

E_DVR_USB_CAMERA_STORAGE_PATH UsbCameraParam_StorageFilePath_String_To_EM(char *str);
E_DVR_USB_CAMERA_RESOLUTION UsbCameraParam_Resolution_String_To_EM(u8 *str);


void appToDvd_VideoSet_Color(u8 param);
void appToDvd_VideoSet_Chrominace(u8 param);
void appToDvd_VideoSet_Brightness(u8 param);
void appToDvd_VideoSet_ContrastGauge(u8 param);
bool UsbCamera_SetVideoParam_Level_To_Data(E_DVR_USB_CAMERA_SET_VIDEO_TPYE emType,u8 uInLevel,u8 *uOutTemData);
bool UsbCamera_SetVideoParam_Data_To_Level(E_DVR_USB_CAMERA_SET_VIDEO_TPYE emType,u8 uInData,u8 *uOutLevel);
void DisplayingUI_GetUsbCameraVideoSettingParam(E_DVR_USB_CAMERA_SET_VIDEO_TPYE emType,u8 u8Level);

void appToDvr_Usb_Camera_Set_Switch_one(u8 param);
void UI_Usb_Camera_Mono_Road(E_DVR_USB_CAMERA_WHICH_ROAD em);
void ToHal_DVR_USB_Carema_WhichOne_Road_Recording(E_DVR_USB_CAMERA_WHICH_ROAD em);
void appToDvr_DVR_UsbCamara_FOLDER_Button_MouseUp();

void DisplayingOrHidingFormatPromtDialog(u8 state);
void appToDvr_Usb_Camera_Set_Format();
void appToDvr_Usb_Camera_Set_SureOrChance_Format(u8 p);
void appToDvr_Usb_Camera_Format_PromtDialogs_Hide();
void GetSyncInforsToFormatPromtDialog(u8 state);
void GetAsyncInforsToFormatPromtDialog(u8 state);

void ToHalDvr_EmergencyCollisionSwitch(u8 param);
void ToHalDvr_SetKeepTimesOfEmergencyCollision(u8 param);
void ToUI_KeepTimesOfEmergencyCollision(u8 param);

//ChangHe
void appToDvr_ChangHe_DVR_NO_DATA_VIDEO_OSD_BUTTON_BACKGROUND(void);
void appToDvr_ChangHe_DVR_NO_DATA_VIDEO_OSD_BUTTON_SET(void);
s32 getCurSysSetDvrProtocolModeStatus(void);
void appToDvr_Menu_Button_Camera_changhe_MouseUp();

void ToUI_USB_CaremaRecordingStatePromt(u8 p);
void ToUI_USB_CaremaSdcardStatePromt(u8 p);
void ToUI_USB_CaremaRecordingLockStatePromt(u8 p);
void ToUI_USB_CaremaRecordingLockStateButton(u8 p);
void ToUI_USB_CaremaSensitivityStateButton(u8 p);
void appToDvr_Usb_Camera_Set_Sensitivity(u8 param);
void appToDvr_Usb_Camera_Set_RecordingLock();

#endif
