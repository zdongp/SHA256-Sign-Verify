#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

#define UIACTION_MOUSEDOWN  	0X00

#define UIACTION_MOUSEUP  		0X10

#define UIACTION_MOUSETIMER  	0X20



int isEnable(int ctrlId);

int MouseUp_Dvd_Ctrl(int dwFunID);

void MouseMove_GaugeBrowse(u8 param);


void appToDvd_MainEQ_MouseUp(void);

void appToDvd_MainAudio_MouseUp(void);

void appToDvd_MainMute_MouseUp(void);

void appToDvd_MainTrackList_MouseUp(void);



void appToDvd_MainFolderButton_MouseUp(void);

void appToDvd_MainPlayPause_MouseUp(void);

void appToDvd_MainStop_MouseUp(void);

void appToDvd_MainPrev_MouseUp(void);

void appToDvd_MainNext_MouseUp(void);

void appToDvd_MainFF_MouseUp(void);

void appToDvd_MainFB_MouseUp(void);

void appToDvd_MainDisplayMode_MouseUp(char type);

void appToDvd_MainDisplayMode_MouseDown(char type);


void appToDvd_MainVideo_MouseUp(void);

void appToDvd_MainPlayBackMode_MouseUp(char type);

void appToDvd_MainBack_MouseUp(void);

void appToDvd_MenuDvd_MouseUp(void);

void appToDvd_TrackListIndex_MouseUp(int index);
void appToDvd_TrackListIndex_MouseDown(int index);

void appToDvd_TrackList_Back_MouseUp(void);

void appToDvd_FolderPrevPage_MouseUp(void);
void appToDvd_FolderNextPage_MouseUp(void);
void appToDvd_FolderCurPage_MouseUp(void);
void appToDvd_FolderGauge_MouseUp(u8 *buffer,u8 len);

void appToDvd_FolderItem_MouseUp(int index);
void appToDvd_FolderItem_MouseDown(int index);

void appToDvd_FolderBack_MouseUp(void);

void appToDvd_VideoBackground_MouseUp(void);

void appToDvd_VideoCtrl_PlayPause_MouseUp(void);
void appToDvd_VideoCtrl_Stop_MouseUp(void);
void appToDvd_VideoCtrl_Prev_MouseUp(void);
void appToDvd_VideoCtrl_Next_MouseUp(void);
void appToDvd_VideoCtrl_FastForward_MouseUp(void);
void appToDvd_VideoCtrl_FastBackward_MouseUp(void);

void appToDvd_VideoCtrl_MainMenu_MouseUp(void);
void appToDvd_VideoCtrl_Menu_MouseUp(void);
void appToDvd_VideoCtrl_Audio_MouseUp(void);

void appToDvd_VideoCtrl_SubTitle_MouseUp(void);
void appToDvd_VideoCtrl_Set_MouseUp(void);
void appToDvd_VideoCtrl_Back_MouseUp(void);

void appToDvd_VideoCtrl_Left_MouseUp(void);
void appToDvd_VideoCtrl_Right_MouseUp(void);
void appToDvd_VideoCtrl_Up_MouseUp(void);
void appToDvd_VideoCtrl_Down_MouseUp(void);
void appToDvd_VideoCtrl_Ok_MouseUp(void);

void appToDvd_VideoCtrl_Background_MouseUp(void);


void appToDvd_VideoSet_ColorDec_MouseUp(void);
void appToDvd_VideoSet_ColorInc_MouseUp(void);

void appToDvd_VideoSet_ChrominanceDec_MouseUp(void);
void appToDvd_VideoSet_ChrominanceInc_MouseUp(void);

void appToDvd_VideoSet_ContrastDec_MouseUp(void);
void appToDvd_VideoSet_ContrastInc_MouseUp(void);

void appToDvd_VideoSet_BrightnessDec_MouseUp(void);
void appToDvd_VideoSet_BrightnessInc_MouseUp(void);

void appToDvd_VideoSet_Background_MouseUp(void);
void appToDvd_VideoSet_CtrlBackground_MouseUp(void);

void appToDvd_DVDOpenBackground_MouseUp(void);

void appToDVD_VideoOSD_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType);
void appToDVD_VideoOSDColorSet_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType);

#endif
