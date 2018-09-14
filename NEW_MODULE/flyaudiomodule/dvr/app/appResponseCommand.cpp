#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "controlID.h"
#include "appResponseFunction.h"
#include "appResponseCommand.h"
#include "otherModuleRequestFunction.h"

#include "halRequestFunction.h"

void appInit(void){
}

void appDeInit(void){
}

void analyseAppMessage(unsigned char *buffer, unsigned char len){
	int ctrlId = 0;
	char ctrlType;
	unsigned char paramLen;
	unsigned char *param;

	ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
	ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
	ctrlId += (int)((buffer[2] << 8) & 0xFF00);
	ctrlId += (int)(buffer[3] & 0xFF);

	ctrlType = buffer[4];
	paramLen = len - 5;
	param = &buffer[5];
	
	LOGD("Module_dvr analyseAppMessage ctrlType:%x ctrlId:%x",ctrlType,ctrlId);

	appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_menu(ctrlId,ctrlType);
	appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_videoset(ctrlId,ctrlType);
	appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_folderplay(ctrlId,ctrlType);
	appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_timeset(ctrlId,ctrlType);
	
	switch(ctrlId){
		//PAGE_DRIVING_RECORD_MENU  	0x4001
		case CONTROLIDTRAVEL_DRIVING_RECORD_VIDEO:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_DVR_RECORD_VIDEO_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_MUTE:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_DVR_RECORD_MUTE_Button_MouseUp();
			}
			break;     	 	           		 
		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_DVR_RECORD_TIME_SET_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_SET:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				if(pLocalParam->uDvrModule_is_T123 == 1)
				{
					appToDvr_DVR_RECORD_SET_Button_MouseUp();
				}
				else
				{
					UsbCameraParamVariable_Real_To_Temp();
					UI_Usb_Camera_Show_Setting_Info();
					appToDvr_DVR_RECORD_SET_Button_Camera_MouseUp();
				}
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_FOLDER:
			if(ctrlType == UIACTION_MOUSEUP){
				if(pLocalParam->uDvrModule_is_T123 == 1){
					appToDvr_DVR_RECORD_FOLDER_Button_MouseUp();
				}
				else{
					//appToDvr_DVR_UsbCamara_FOLDER_Button_MouseUp();
				}
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_CODE:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_DVR_RECORD_CODE_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_BACKGROUND:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_DVR_RECORD_BACKGROUND_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_MENU_BACK:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_Return_Button_MouseUp();
			}
			break;
		case CONTROLID_MENU_DRIVING_RECORD:
			if(ctrlType == UIACTION_MOUSEUP){
				if(pLocalParam->uDvrModule_is_T123 == 1)
				{
					appToDvr_Menu_Button_MouseUp();
				}
				else
				{
					appToDvr_Menu_Button_Camera_MouseUp();
				}
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_RECORDING://0x400701
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_Menu_Button_Camera_Recording();
			}
			break;
			
		//PAGE_DRIVING_RECORD_TIME_SET  	0x4002
		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET_UP:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_TIME_SET_UP_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET_DOWN:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_TIME_SET_DOWN_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET_OK: 
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_TIME_SET_OK_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET_SET:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_TIME_SET_SET_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET_BACK:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_TIME_SET_BACK_Button_MouseUp();
			}
			break;
			
		//PAGE_DRIVING_RECORD_SET  	0x4003		
		case CONTROLIDTRAVEL_DRIVING_RECORD_SET_UP:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_SET_UP_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_SET_DOWN:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_SET_DOWN_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_SET_SURE:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_SET_SURE_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_SET_BACK: 
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_SET_BACK_Button_MouseUp();
			}
			break;
		//PAGE_DRIVING_RECORD_PALY  	0x4004
		case CONTROLIDTRAVEL_DRIVING_RECORD_PLAY_UP: 
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_PALY_UP_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_PLAY_PLAY:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_PALY_PLAY_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_PLAY_NEXT: 
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_PALY_NEXT_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_PLAY_CODE:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_PALY_CODE_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_PLAY_BACK:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_PALY_BACK_Button_MouseUp();
			}
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_PLAY_BACKGROUND:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_PLAY_BACKGROUND_Button_MouseUp();
			}
			break;
			
		case CONTROLID_DRIVING_RECORD_VIDEO_BACKGROUND:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_VIDEO_BACKGROUND_Button_MouseUp();
			}
			break;
		case CONTROLID_DRIVING_RECORD_NO_SIGN_BACK:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_VIDEO_NoSign_Back_Button_MouseUp();
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_SET_BACK:
			if(ctrlType == UIACTION_MOUSEUP){
				dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_SET_RESOLUTION_UP:
		case CONTROLID_DRIVING_USB_CAREMA_SET_RESOLUTION_DOWN:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_Usb_Camera_Set_Resolution_Button(ctrlId - CONTROLID_DRIVING_USB_CAREMA_SET_RESOLUTION_UP);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_UP:
		case CONTROLID_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_DOWN:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_Usb_Camera_Set_RecordingTimes_Button(ctrlId - CONTROLID_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_UP);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_UP:
		case CONTROLID_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_DOWN:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_Usb_Camera_Set_StorageSize_Button(ctrlId - CONTROLID_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_UP);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_SET_STORAGE_PATH_TOUR:
			if(ctrlType == UIACTION_MOUSEUP){
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_SET_STORAGE_PATH_UP:
		case CONTROLID_DRIVING_USB_CAREMA_SET_STORAGE_PATH_DOWN:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_Usb_Camera_Set_StoragePath_Button(ctrlId - CONTROLID_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_UP);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_SETTING_APPLY:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_Usb_Camera_Setting_Apply();
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_VIDEO_SETTING:
			if(ctrlType == UIACTION_MOUSEUP){
				dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_SET);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_VIDEO_COLOR_INC:
		case CONTROLID_DRIVING_USB_CAREMA_VIDEO_COLOR_DEC:
			if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER){
				appToDvd_VideoSet_Color(ctrlId - CONTROLID_DRIVING_USB_CAREMA_VIDEO_COLOR_INC);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_VIDEO_CHROMINANCE_INC:
		case CONTROLID_DRIVING_USB_CAREMA_VIDEO_CHROMINANCE_DEC:
			if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER){
				appToDvd_VideoSet_Chrominace(ctrlId - CONTROLID_DRIVING_USB_CAREMA_VIDEO_CHROMINANCE_INC);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_VIDEO_BRIGHTNESS_INC:
		case CONTROLID_DRIVING_USB_CAREMA_VIDEO_BRIGHTNESS_DEC:
			if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER){
				appToDvd_VideoSet_Brightness(ctrlId - CONTROLID_DRIVING_USB_CAREMA_VIDEO_BRIGHTNESS_INC);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_VIDEO_CONTRAST_GAUGE_INC:
		case CONTROLID_DRIVING_USB_CAREMA_VIDEO_CONTRAST_GAUGE_DEC:
			if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER){
				appToDvd_VideoSet_ContrastGauge(ctrlId - CONTROLID_DRIVING_USB_CAREMA_VIDEO_CONTRAST_GAUGE_INC);
			}
			break;
			
		case CONTROLID_DRIVING_USB_CAREMA_SET_SWITCH_ONE_RECOIDING_UP:
		case CONTROLID_DRIVING_USB_CAREMA_SET_SWITCH_ONE_RECOIDING_DOWN:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_Usb_Camera_Set_Switch_one(ctrlId - CONTROLID_DRIVING_USB_CAREMA_SET_SWITCH_ONE_RECOIDING_UP);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_FOLDER_BACK_BUTTON:
			if(ctrlType == UIACTION_MOUSEUP){
				dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_BUTTON:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_Usb_Camera_Set_Format();
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_SURE:
		case CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_CHANCE:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_Usb_Camera_Set_SureOrChance_Format(ctrlId - CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_SURE);
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_PROMT_SURE:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvr_Usb_Camera_Format_PromtDialogs_Hide();
			}
			break;
		case CONTROLID_DRIVING_USB_CAREMA_SETTING_EMERGENCY_COLLISION_SWITCH:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				  if(pLocalParam->uCurEmergencyCollisionSwitchStatus == 0)
	            {
	                ToHalDvr_EmergencyCollisionSwitch(1);
	            }
	            else if(pLocalParam->uCurEmergencyCollisionSwitchStatus == 1)
	            {
	                ToHalDvr_EmergencyCollisionSwitch(0);
	            }
			}
			break;
			case CONTROLID_DRIVING_USB_CAREMA_SETTING_NEXT_PAGE:
			if(ctrlType == UIACTION_MOUSEUP){
				dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_USB_CAMERA_EMERGENCY_COLLISION);
			}
			break;
			case CONTROLID_DRIVING_USB_CAREMA_SETTING_PRE_PAGE:
			case CONTROLID_DRIVING_USB_CAREMA_SETTING_EMERGENCY_COLLISION_PAGE_BACK:
			if(ctrlType == UIACTION_MOUSEUP){
				dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_USB_CAMERA_SET);
			}
			break;
			case CONTROLID_DRIVING_USB_CAREMA_SETTING_EC_KEEP_TIMES_UP:
			case CONTROLID_DRIVING_USB_CAREMA_SETTING_EC_KEEP_TIMES_DOWN:
			if(ctrlType == UIACTION_MOUSEUP){
				ToHalDvr_SetKeepTimesOfEmergencyCollision(ctrlId - CONTROLID_DRIVING_USB_CAREMA_SETTING_EC_KEEP_TIMES_UP);
			}	
			break;
			case CONTROLID_DRIVING_CHANGHE_DVR_VIDEO_OSD_BUTTON_BACKGROUND:
			case CONTROLID_DRIVING_CHANGHE_DVR_VIDEO_OSD_BUTTON_SET_BACKGROUND	:
				if(ctrlType == UIACTION_MOUSEUP){
					appToDvr_ChangHe_DVR_NO_DATA_VIDEO_OSD_BUTTON_BACKGROUND();
				}
				break;
			case CONTROLID_DRIVING_CHANGHE_DVR_VIDEO_OSD_BUTTON_SET :
				if(ctrlType == UIACTION_MOUSEUP){
					appToDvr_ChangHe_DVR_NO_DATA_VIDEO_OSD_BUTTON_SET();
				}
				break;
			case CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_LOW:
			case CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_MID:
			case CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_HIGH:
				if(ctrlType == UIACTION_MOUSEUP){
					appToDvr_Usb_Camera_Set_Sensitivity(ctrlId - CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_LOW);
				}
				break;
			case CONTROLID_DRIVING_USB_CAREMA_RECORDING_LOCK_STATE_BUTTON:
				if(ctrlType == UIACTION_MOUSEUP){
					appToDvr_Usb_Camera_Set_RecordingLock();
				}
				break;
			default:break;
	}
}
