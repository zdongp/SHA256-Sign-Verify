#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

void appToMedia_MenuMedia_MouseUp();
void appToMedia_MainBack_MouseUp(void);
void appToMedia_GetMediaPlayState(u8 state );

void appToMedia_GetMediaPlayAndTotalTime(u8* param,int len );

void appToMedia_GetMediaPlaySongName(u8 *param,int len);
void appToMedia_GetMediaPlaySongArtist(u8 *param,int len);
void appToMedia_GetMediaPlaySongAlbum(u8 *param,int len);

void appToMedia_GetMediaPlaySongtrack(u8 *param,int len);

void appToMedia_GetMediaUsbState(u8 *p,int len);
void appToMedia_GetUSBDeviceName(u8 *p,int len);


#endif
