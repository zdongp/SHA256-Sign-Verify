#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__

void dvdToModule_NotifySystem_jumpPage(u16 pageID);
void dvdToModule_NotifySystem_JumpPrePage(void);
void dvdToModule_NotifySystem_SwitchModule(void);//����AV KEY


void dvdToModule_NotifyAuxscreen_TitleTrack(short title, short track);
void dvdToModule_NotifyAuxscreen_TotalTime(int time);//add 2012-07-11 09:31:56
void dvdToModule_NotifyAuxscreen_Time(int time);
void dvdToModule_NotifyAuxscreen_DiscInfo(char discType, char fileType);
void dvdToModule_NotifyAuxscreen_PlayState(char state);
void dvdToModule_NotifyAuxscreen_DeviceState(char state);


void audioVideoToModule_NotifyOsd_ShowDVDTitle();
void audioVideoToModule_NotifyOsd_DVDTitleValue(u8 type,u16 title,u16 track);
void dvdToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(u8 swtich_button,u8 button_status);
void dvdToModule_NotifyOSD_aboutT123_colorSet_Value(u8 setOptions,u8 value);
void dvdToModule_NotifyOSD_aboutT123_VideoOSD_Button(u8 swtich_button,u8 button_status);
void dvdToModule_NotifyOSD_aboutT123_playtimes_Value(int timeValue);



#endif
