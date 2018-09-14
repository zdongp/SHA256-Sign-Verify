#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__

void AboutNewLogic_HideOrDisplayingOSD(u8 param);
void SoundValue_OSDToHal(u8 param);
void ACMessage_OSDToHal(short nLeftTemp,short nRightTemp,u8 nUnit,u8 nSpeed,u8 nACState);

void DVDplay_titleAndTrack_OSDToHal(u8 *param,int len);
void CDC_TitleTrackTimesValue_OSDToHal(u8 title,u16 track);
void MediaPlay_TrackValue_OSDToHal(u8 *param);
void BTcontectStatus_OSDToHal(u8 *param);
void TPMS_TempsAndStatus_OSDToHal(u8 tire,u8 status);

void Radio_Channel_Value_OSDToHal(u8 type,u16 value,u8 unit);

void BackcarVideoSetButton_OSDToHal(u8 param1,u8 param2);
void BackcarVideoLCDColorSet_OSDToHal(u8 param1,u8 param2);
void BackcarVideoColorValue_OSDToHal(u8 param1,u8 param2);
void BackcarVideoRaderDisplaying_OSDToHal(u8 param1,u8 param2);
void BackcarVideoCarDisplayingStatus_OSDToHal(u8 param);
void BackcarVideoWarningsDisplayingStatus_OSDToHal(u8 param);

void AuxVideoSetButton_OSDToHal(u8 param1,u8 param2);
void AuxVideoLCDColorSet_OSDToHal(u8 param1,u8 param2);
void AuxVideoColorValue_OSDToHal(u8 param1,u8 param2);

void TVVideoSetButton_OSDToHal(u8 param1,u8 param2);
void TVVideoLCDColorSet_OSDToHal(u8 param1,u8 param2);
void TVVideoColorValue_OSDToHal(u8 param1,u8 param2);

void dvrVideoSetButton_OSDToHal(u8 param1,u8 param2);
void dvrVideoPlaySet_OSDToHal(u8 param1,u8 param2);
void dvrVideoYMDSet_OSDToHal(u8 param1,u8 param2);
void dvrVideoSet_OSDToHal(u8 param1,u8 param2);

void dvdVideoSetButton_OSDToHal(u8 param1,u8 param2);
void dvdVideoPlayTimes_OSDToHal(u8 *param);
void dvdVideoLCDColorSet_OSDToHal(u8 param1,u8 param2);
void dvdVideoColorValue_OSDToHal(u8 param1,u8 param2);

void ViewChannelSwitchOSDToHal(u8 param);

//byte GetShowOSDWagFlag(int nOSDContent,bool bShowFlag);//Ҫ�����л�OSD�ķ�ʽ
void ShowHideOSD(int nOSDContent,bool bShowFlag);//��ʾ ���� ĳosd
void Set_DisplayOSDPage(unsigned char cPageFlag);//������ʾ�������osdҳ


void SetOSDUIValue_OSDToHal(u8* param,int len);

void OsdMsgTheAdapterEntrance(moduleid_t halId,u8* param,int len);
void makeAndSendMessageToUI(u8* param,int len);

//Define Current Module Function ID:
enum OSDPAGE{
OSD_NoDisplay,
OSD_Sound_SubTitle,
OSD_AC_SubTitle,
OSD_DVD_SubTitle,
OSD_CDC_SubTitle,
OSD_Media_SubTitle,
OSD_BT_SubTitle,
OSD_TPMS_SubTitle,
OSD_Radio_SubTitle,
OSD_BACK,
OSD_BACK_Color,
OSD_AUX_Menu,
OSD_AUX_Color,
OSD_TV_Menu,
OSD_TV_Color,
OSD_DVR_Menu,
OSD_DVR_Play,
OSD_DVR_TimeSet,
OSD_DVR_VideoSet,
OSD_DVD_Menu,
OSD_DVD_Color,
OSD_System_SubTitle,
OSD_CDC_Menu,
OSD_CDC_Color,
OSD_TV_Number,
};

//OSD PAGE FLAG
#define OSDPAGE_HIDEOSD            0x00
#define OSDPAGE_SOUND_TITLE        0x10
#define OSDPAGE_AC_TITLE           0x11
#define OSDPAGE_DVD_TITLE          0x12
#define OSDPAGE_CDC_TITLE          0x13
#define OSDPAGE_MEDIA_TITLE        0x14
#define OSDPAGE_BT_TITLE           0x15
#define OSDPAGE_TPMS_TITLE         0x16
#define OSDPAGE_RADIO_TITLE        0x17

#define OSDPAGE_BACK               0x20
//#define OSDPAGE_BACK_COLOR       0x21
#define OSDPAGE_BACK_RADAR_CAR     0x22

#define OSDPAGE_BACK_COLOR         0x80

#define OSDPAGE_BACK_GUANGJIAO     0x23


#define OSDPAGE_AUX_MENU           0x30
#define OSDPAGE_AUX_COLOR          0x31

#define OSDPAGE_TV_MENU            0x40
#define OSDPAGE_TV_COLOR           0x41

#define OSDPAGE_DVR_MENU           0x50
#define OSDPAGE_DVR_PLAY           0x51
#define OSDPAGE_DVR_TIMESET       0x52
#define OSDPAGE_DVR_VIDEOSET      0x53

#define OSDPAGE_DVD_MENU           0x60
#define OSDPAGE_DVD_COLOR          0x61

//#define  TIMEOUT_HIDE_SUBTITLE     3000//
//#define  TIMEOUT_HIDE_OSDPAGE      5000//

#endif
