#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"

#include "appResponseCommand.h"
#include "appResponseFunction.h"

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

	int bRet = 0;
	bRet = isEnable(ctrlId);
	if(!bRet)
		return;
	LOGD("Module_dvd App ctrlId:0x%x ctrlType:0x%x", ctrlId,ctrlType);

	appToDVD_VideoOSD_ButtonMessageToT123ChipLocation(ctrlId,ctrlType);
	appToDVD_VideoOSDColorSet_ButtonMessageToT123ChipLocation(ctrlId,ctrlType);
	
	switch(ctrlId){
		case CONTROLID_DVD_MAIN_EQ: // 0x050000
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainEQ_MouseUp();
			}
			break;

		case CONTROLID_DVD_MAIN_AUDIO: // 0x050001
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainAudio_MouseUp();
			}
			break;
			
		//case CONTROLID_DVD_MAIN_MUTE:	// 0x050002
		//	if(ctrlType == UIACTION_MOUSEUP){
		//		appToDvd_MainMute_MouseUp();
		//	}
		//	break;
			
		case CONTROLID_DVD_MAIN_FOLDER_NAME:	// 0x050010
		case CONTROLID_DVD_MAIN_FILE_NAME:		// 0x050011
			break;
			
		case CONTROLID_DVD_MAIN_TRACKLIST: // 0x050012
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainTrackList_MouseUp();
			}
			break;
			
		case CONTROLID_DVD_MAIN_FOLDER_BUTTON: // 0x050013
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainFolderButton_MouseUp();
			}
			break;
			
		case CONTROLID_DVD_MAIN_PLAYPAUSE: // 0x050020
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainPlayPause_MouseUp();
			}
			break;
			
		case CONTROLID_DVD_MAIN_STOP:	// 0x050021
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainStop_MouseUp();
			}
			break;
			
		case CONTROLID_DVD_MAIN_PREV:	// 0x050022
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainPrev_MouseUp();
			}
			break;
			
		case CONTROLID_DVD_MAIN_NEXT:	// 0x050023
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainNext_MouseUp();
			}
			break;
			
		case CONTROLID_DVD_MAIN_FF: 	// 0x050024
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainFF_MouseUp();
			}
			break;
			
		case CONTROLID_DVD_MAIN_FB: 	// 0x050025
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainFB_MouseUp();
			}
			break;
		case CONTROLID_DVD_MAIN_4_3:
		case CONTROLID_DVD_MAIN_16_9:
		case CONTROLID_DVD_MAIN_FULL: 
			if(ctrlType == UIACTION_MOUSEUP){
				char type = 0x00;
				if(ctrlId == CONTROLID_DVD_MAIN_4_3){
					type = 0x01;
				}
				else if(ctrlId == CONTROLID_DVD_MAIN_16_9){
					type = 0x02;
				}
				else if(ctrlId == CONTROLID_DVD_MAIN_FULL){
					type = 0x03;
				}
				appToDvd_MainDisplayMode_MouseUp(type);
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				char type = 0x00;
				if(ctrlId == CONTROLID_DVD_MAIN_4_3){
					type = 0x01;
				}
				else if(ctrlId == CONTROLID_DVD_MAIN_16_9){
					type = 0x02;
				}
				else if(ctrlId == CONTROLID_DVD_MAIN_FULL){
					type = 0x03;
				}
				appToDvd_MainDisplayMode_MouseDown(type);
			}
			break;
			
		case CONTROLID_DVD_MAIN_VIDEO:	// 0x050033
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainVideo_MouseUp();
			}
			break;		
		
		case CONTROLID_DVD_MAIN_VIDEO_4_3_ICON:
		case CONTROLID_DVD_MAIN_VIDEO_16_9_ICON:
		case CONTROLID_DVD_MAIN_VIDEO_FULL_ICON:
			break;

		case CONTROLID_DVD_MAIN_RPT:
		case CONTROLID_DVD_MAIN_SHUFFLE:
		case CONTROLID_DVD_MAIN_SCAN:
			if(ctrlType == UIACTION_MOUSEUP){
				char type = 0;
				if(ctrlId == CONTROLID_DVD_MAIN_RPT){
					type = 0x01;
				}
				else if(ctrlId == CONTROLID_DVD_MAIN_SHUFFLE){
					type = 0x02;
				}
				else if(ctrlId == CONTROLID_DVD_MAIN_SCAN){
					type = 0x03;
				}
				appToDvd_MainPlayBackMode_MouseUp(type);
			}
			break;

		case CONTROLID_DVD_MAIN_CD_RPT_ICON:
		case CONTROLID_DVD_MAIN_CD_SHUFFLE_ICON:
			break;

		case CONTROLID_DVD_MAIN_NO_DISC:
		case CONTROLID_DVD_MAIN_TITLE_TEXT:
		case CONTROLID_DVD_MAIN_CURRENT_TITLE_NUM:
		case CONTROLID_DVD_MAIN_TRACK_TEXT:
		case CONTROLID_DVD_MAIN_CURRENT_TRACK_NUM:
		case CONTROLID_DVD_MAIN_CURRENT_TIME:
			break;

		case CONTROLID_DVD_MAIN_BACK: 
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MainBack_MouseUp();
			}
			break;

		case CONTROLID_MENU_DVD:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_MenuDvd_MouseUp();
			}
			break;
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x00:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x01:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x02:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x03:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x04:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x05:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x06:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x07:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x08:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x09:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x0A:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x0B:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x0C:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x0D:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x0E:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x0F:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x10:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x11:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x12:
		case CONTROLID_DVD_TRACKLIST_BEGIN+0x13: 
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_TrackListIndex_MouseUp(ctrlId-CONTROLID_DVD_TRACKLIST_BEGIN);
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToDvd_TrackListIndex_MouseDown(ctrlId-CONTROLID_DVD_TRACKLIST_BEGIN);
			}
			break;
		case CONTROLID_DVD_TRACKLIST_BACK:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_TrackList_Back_MouseUp();
			}
			break;

		case CONTROLID_DVD_FOLDER_PREVPAGE: 	// 0x050310
				if(ctrlType == UIACTION_MOUSEUP){
					appToDvd_FolderPrevPage_MouseUp();
				}
			break;
			
		case CONTROLID_DVD_FOLDER_NEXTPAGE: // 0x050311
			if(ctrlType == UIACTION_MOUSEUP){
				
				appToDvd_FolderNextPage_MouseUp();
			}
			break;
			
		case CONTROLID_DVD_FOLDER_CURPAGE:	// 0x050312
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_FolderCurPage_MouseUp();
			}
			break;
			
		case CONTROLID_DVD_FOLDER_GAUGE:	// 0x050313
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_FolderGauge_MouseUp(param,len);
			}
			break;
		case CONTROLID_DVD_FOLDER_ITEM_BEGIN + 0x00:
		case CONTROLID_DVD_FOLDER_ITEM_BEGIN + 0x01:
		case CONTROLID_DVD_FOLDER_ITEM_BEGIN + 0x02:
		case CONTROLID_DVD_FOLDER_ITEM_BEGIN + 0x03:
		case CONTROLID_DVD_FOLDER_ITEM_BEGIN + 0x04:	// 0x050320
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_FolderItem_MouseUp(ctrlId-CONTROLID_DVD_FOLDER_ITEM_BEGIN);
			}
			else{
				appToDvd_FolderItem_MouseDown(ctrlId-CONTROLID_DVD_FOLDER_ITEM_BEGIN);
			}
			break;
		
		case CONTROLID_DVD_FOLDER_BACK:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_FolderBack_MouseUp();
			}
			break;



		////////////////////////////////OSD//////////////////////////////////////////////////////
		case CONTROLID_DVD_VIDEO_BACKGROUND:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoBackground_MouseUp();
			}
			break;

		case CONTROLID_DVD_VIDEO_CONTROL_PLAYPAUSE:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_PlayPause_MouseUp();
			}
			break;

		case CONTROLID_DVD_VIDEO_CONTROL_STOP:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Stop_MouseUp();
			}
			break;

		case CONTROLID_DVD_VIDEO_CONTROL_PREV:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Prev_MouseUp();
			}
			break;

		case CONTROLID_DVD_VIDEO_CONTROL_NEXT:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Next_MouseUp();
			}
			break;

		case CONTROLID_DVD_VIDEO_CONTROL_FF://FAST FORWARD
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_FastForward_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_FB: //FAST BACKWARD
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_FastBackward_MouseUp();
			}
			break;

		//case CONTROLID_DVD_VIDEO_CONTROL_CURTIME:
		//	break;

		case CONTROLID_DVD_VIDEO_CONTROL_MAINMENU:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_MainMenu_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_MENU:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Menu_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_AUDIO:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Audio_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_SUBTITLE:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_SubTitle_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_SET:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Set_MouseUp();
			}
			
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_BACK: 
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Back_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_LEFT:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Left_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_RIGHT:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Right_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_UP:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Up_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_DOWN:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Down_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_OK: 
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Ok_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_CONTROL_BACKGROUND:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoCtrl_Background_MouseUp();
			}
			break;

		case CONTROLID_DVD_VIDEO_SET_COLOUR_DEC:   //色彩减
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoSet_ColorDec_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToDvd_VideoSet_ColorDec_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_SET_COLOUR_GAUGE:
			break;
		case CONTROLID_DVD_VIDEO_SET_COLOUR_INC:  //色彩加
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoSet_ColorInc_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToDvd_VideoSet_ColorInc_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_SET_CHROMINANCE_DEC: 	//色调减
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoSet_ChrominanceDec_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToDvd_VideoSet_ChrominanceDec_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_SET_CHROMINANCE_GAUGE:
			break;
		case CONTROLID_DVD_VIDEO_SET_CHROMINANCE_INC:  //色调加
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoSet_ChrominanceInc_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToDvd_VideoSet_ChrominanceInc_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_SET_CONTRAST_DEC: 		//对比度减
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoSet_ContrastDec_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToDvd_VideoSet_ContrastDec_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_SET_CONTRAST_GAUGE:
			break;
		case CONTROLID_DVD_VIDEO_SET_CONTRAST_INC:  //对比度加
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoSet_ContrastInc_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToDvd_VideoSet_ContrastInc_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_SET_BRIGHTNESS_DEC: 	//亮度 减
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoSet_BrightnessDec_MouseUp();
			}else if(ctrlType == UIACTION_MOUSETIMER)
			{
				appToDvd_VideoSet_BrightnessDec_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_SET_BRIGHTNESS_GAUGE:
			break;
		case CONTROLID_DVD_VIDEO_SET_BRIGHTNESS_INC: 	// 亮度加
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoSet_BrightnessInc_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToDvd_VideoSet_BrightnessInc_MouseUp();
			}
			break;
		
		case CONTROLID_DVD_VIDEO_SET_BACKGROUND:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoSet_Background_MouseUp();
			}
			break;
		case CONTROLID_DVD_VIDEO_SET_CONTROL_BACKGROUND:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_VideoSet_CtrlBackground_MouseUp();
			}
			break;
		case CONTROLID_DVD_OPEN_BACKGROUND:
			if(ctrlType == UIACTION_MOUSEUP){
				appToDvd_DVDOpenBackground_MouseUp();
			}
			break;

			
		default:
			return;
			break;
	}
	
}
	

