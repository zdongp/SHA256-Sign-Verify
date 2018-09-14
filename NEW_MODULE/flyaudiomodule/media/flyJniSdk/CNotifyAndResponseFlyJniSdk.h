/* fengxingxing   2015/7/29   */


#pragma once 

#include "global.h"


class CNotifyAndResponseFlyJniSdk

{
public:
	CNotifyAndResponseFlyJniSdk(void);
	virtual ~CNotifyAndResponseFlyJniSdk(void);

public:
	void sendToFlyJniSdkMusicSongName(unsigned char* songName,int len);
       


};

