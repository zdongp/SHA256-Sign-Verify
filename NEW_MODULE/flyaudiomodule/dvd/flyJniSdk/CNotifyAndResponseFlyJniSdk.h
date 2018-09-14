#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <flyutils/debug.h>
#include <cstring>
#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "controlID.h"

class  CNotifyAndResponseFlyJniSdk
{
public:
    CNotifyAndResponseFlyJniSdk();
     ~CNotifyAndResponseFlyJniSdk();
    void  sendToFlyJniSdkPlayState(char cState);
    void   sendToFlyJniSdkTitleAndTrack(unsigned short title,unsigned short track);
    void sendToFlyJniSdkCurrentTime(unsigned char hour,unsigned char minute,unsigned char second);
    void  sendToFlyJniSdkDvdDiscAndFileType(unsigned char discType,unsigned char fileType);
    void  sendToFlyJniSdkDevState(unsigned char devState);

   void  analyseFlyJniSdkMessage(unsigned char *p,int len);
};