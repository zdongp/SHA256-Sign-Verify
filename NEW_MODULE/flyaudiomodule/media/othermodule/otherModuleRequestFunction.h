#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__

void mediaToModule_NotifySystem_jumpPage(u16 pageID);
void mediaToModule_NotifySystem_SwitchModule(void);

void mediaToModule_NotifyAudiovideo_MediaPlayStates(u8 state);

void mediaToModule_NotifyAuxscreen_TotalAndTrack(short title, short track);

void mediaToModule_NotifyAuxscreen_PlayState(char state);
void mediaToModule_NotifyAuxscreen_Time(int time);
void mediaToModule_NotifyAuxscreen_TotalTime(int time);
void mediaToModule_NotifyAuxscreen_SongName(u8 *pBuf, int nLen);
void mediaToModule_NotifyAuxscreen_SongArtist(u8 *pBuf, int nLen);
void mediaToModule_NotifyAuxscreen_SongAlbum(u8 *pBuf, int nLen);
void mediaToModule_NotifyAuxscreen_DeviceName(u8 *pBuf, int nLen);
void mediaToModule_NotifyAuxscreen_ClearMediaInfo();

void mediaToModule_NotifyOsd_DisplayOSDMediaInfo(unsigned char type,u16 title,u16 track);
void mediaToModule_NotifyOsd_t123_DisplayTitle();
void mediaToModule_NotifyOsd_t123_DisplayOSDMediaInfo(u16 Current_Track,u16 Total_Track);




#endif
