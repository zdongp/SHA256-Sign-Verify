#ifndef __HAL_RESPONSE_FUNCTION_H__
#define __HAL_RESPONSE_FUNCTION_H__

void analyseHalMessage_TV(u8 uCmd,u8* param,int len);

#include "global.h"
#include "messageQueue.h"

//     TV 控制                 Key（1）	
#define    Key_POWER                  0x00   //电源
#define    Key_SOURCE                 0x01   
#define    Key_MUTE                   0x02   //静音
#define    Key_TV_RADIOSELECT         0x03
#define    Key_MENU                   0x04   //菜单
#define    Key_CH_INC_UP              0x05   //上一台
//#define    Key_                       0x06
#define    Key_EPG                    0x07
#define    Key_VOL_DEC_LEFT           0x08
#define    Key_OK                     0x09
#define    Key_VOL_INC_RIGHT          0x0A
#define    Key_PREVIEW                0x0B
#define    Key_EXIT                   0x0C
#define    Key_CH_DEC_DOWN            0x0D  //下一台
#define    Key_PLAY_PAUSE             0x0E
#define    Key_AUDIO                  0x0F
#define    Key_1                      0x10
#define    Key_2                      0x11
#define    Key_3                      0x12
#define    Key_INFO                   0x13
#define    Key_4                      0x14
#define    Key_5                      0x15
#define    Key_6                      0x16
#define    Key_AUTO                   0x17  //搜索电台
#define    Key_7                      0x18
#define    Key_8                      0x19
#define    Key_9                      0x1A
#define    Key_MANUAL                 0x1B
#define    Key_RECALL                 0x1C
#define    Key_0                      0x1D
#define    Key_ENTER                  0x1E
#define    Key_TELETEXT               0x1F

#define    Key_REDBUTTON              0x40
#define    Key_GREENBUTTON            0x41
#define    Key_YELLOWBUTTON           0x42
#define    Key_BLUEBUTTON             0x43

#endif
