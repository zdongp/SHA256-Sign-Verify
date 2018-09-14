#ifndef __PARAM_H__
#define __PARAM_H__
#include "global.h"
#include "CNotifyAndResponseFlyJniSdk.h"

typedef struct {
 	u8 nCurPlayingModule;
 	bool mediaPlayState;
	int totalTrack;
	int currenTrack;
	u8 curSongName[128];
	u8 curSongArtist[128];
	u8 curSongAlbum[128];
	u8 usbDeviceName[256];

	u8 usb1state;
	bool mediaVoiceState;
}media_local_param_t;

typedef struct{
	
}media_global_param_t;


extern media_local_param_t *pLocalParam;
extern media_global_param_t *pGlobalParam;
extern CNotifyAndResponseFlyJniSdk  g_clsMedia;


void readParameter(void);
void saveParameter(void);




#endif
