#ifndef __APP_REQUEST_FUNCTION_H__
#define __APP_REQUEST_FUNCTION_H__

////////////////1111
void dvdToApp_identifyTrackListOrFolder(void);
void dvdToApp_refreshTrackList(void);
void dvdToApp_refreshBrowseList(int i);
void dvdToApp_clearAllStateWhenOpenDVD(void);

void dvdToApp_enableTrackListAndFolder(int enableTracklist,int enableFolder);
void dvdToApp_displayVideoModeOrAudioMode(int audio);

void dvdToApp_displayDeviceStateOrTraceInfo(int displayTraceInfo);
void dvdToApp_UIDefaultDisplayConfig(void);

void dvdToApp_DisplayPlayCDIndex(int Index);
void dvdToApp_SetStateWhenReady(void);
void dvdToApp_SetUIVideoMode(int modeFlag);





#endif
