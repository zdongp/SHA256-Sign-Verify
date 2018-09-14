#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <string.h>

typedef	unsigned int 	u32;
typedef	unsigned short	u16;
typedef	unsigned char 	u8;

typedef	int 	s32;
typedef	short	s16;
typedef	char	s8;

typedef	 unsigned long 	u64;
typedef	 long 	s64;

//typedef u8		bool;

#define dim(x)	(sizeof(x)/sizeof(x[0]))

#ifndef	false
#define false		0
#endif

#ifndef true
#define	true		1
#endif

/*由于这个宏定义分25和25Q两种情况，MSM_8625代表25Q，否则是25，编译的时候注意下*/
#define MSM_8625 

#define MTK_3561_64

#include "flytypes.h"

#include "moduleID.h"
#include "pageID.h"
#include "controlID.h"
#include "stringID.h"
#include "paramID.h"

#include "debug.h"
#include "hal.h"
#include "boardconfig.h"


//////////////////2011-11-12////////////////////////////
///////////////音视频通道/////////////////////
#define CHANNEL_NOCHANNEL		0xFF//不在任何通道，初始化值，及睡眠时
#define CHANNEL_DVD_CTRL   	0x00// (控制界面)
#define CHANNEL_DVD_VIDEO  	0x01//（视频界面）
#define CHANNEL_CDC_CTRL   	0x02//（控制界面）
#define CHANNEL_CDC_VIDEO  	0x03//（视频界面）
#define CHANNEL_RADIO      	0x04//（控制界面）
#define CHANNEL_AUX_CTRL   	0x05
#define CHANNEL_AUX_VIDEO  	0x06
#define CHANNEL_IPOD_CTRL  	0x07
#define CHANNEL_IPOD_VIDEO 	0x08
#define CHANNEL_TV_CTRL    	0x09
#define CHANNEL_TV_VIDEO   	0x0A
#define CHANNEL_MP3        	0x0B  
#define CHANNEL_SRADIO     	0x0C
#define CHANNEL_BT         	0x0D //蓝牙A2DP的声道

#define CHANNEL_DVR_CTRL    0x11
#define CHANNEL_DVR_VIDEO	0x12
#define CHANNEL_DNV_CTRL	0x13
#define CHANNEL_DNV_VIDEO	0x14
#define CHANNEL_SPEECH_MEDIA_CTRL 0x15

//------------------------------
//Jooph.Lew 2012-01-05
#define CHANNEL_BACK_VIDEO      0x0C
#define CHANNEL_BACK_NOVIDEO    0x1C

#define CHANNEL_THREECHANNEL	0x0E

#define CHANNEL_MAX				0xEE

#define PACKAGE_MESSAGEBUFFER_MAX_LEN	       246


#endif
