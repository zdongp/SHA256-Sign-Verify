#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__


//cmd:0x00
#define IR_SYNV_SPEECH 		0x01
#define IR_SYNV_MENU_BTN  	0x02
#define IR_SYNV_PHONE_BTN 	0x03
#define IR_SYNV_END_BTN  	0x04
#define IR_SYNV_SEND_BTN 	0x05
#define IR_SYNV_INFO_BTN 	0x06
#define IR_SYNV_SHUFF_BTN 	0x07
#define IR_SYNV_PREV_BTN 	0x08
#define IR_SYNV_NEXT_BTN 	0x09
#define IR_SYNV_UP_BTN 	 	0x0a
#define IR_SYNV_DOWN_BTN 	0x0b
#define IR_SYNV_OK_BTN   	0x0c
#define IR_SYNV_SYNV_0 		0x0d
#define IR_SYNV_SYNV_1 		0x0e
#define IR_SYNV_SYNV_2 		0x0f
#define IR_SYNV_SYNV_3 		0x10
#define IR_SYNV_SYNV_4 		0x11
#define IR_SYNV_SYNV_5 		0x12
#define IR_SYNV_SYNV_6 		0x13
#define IR_SYNV_SYNV_7 		0x14
#define IR_SYNV_SYNV_8 		0x15
#define IR_SYNV_SYNV_9 		0x16
#define IR_SYNV_SYNV_MULTIPLY 		0x17
#define IR_SYNV_SYNV_WELL     		0x18
#define IR_SYNV_BTN_1  				0x19
#define IR_SYNV_BTN_2  				0x1a
#define IR_SYNV_BTN_3  				0x1b
#define IR_SYNV_BTN_4  				0x1c
#define IR_SYNV_SYNV_QUITSPEECH 	0x1d
#define IR_SYNV_SYNV_CALLIN_LASTONE 0x1e
#define IR_SYNV_SYNV_HANGUP_NEXTONE 0x1f
#define IR_SYNV_FAST_FORWARD   		0x20
#define IR_SYNV_FAST_REWIND    		0x21

#define IR_SYNV_RELEASE_FINGER		0xFF

#define IR_SYNV_AUX_BTN 			0x81
#define IR_SYNV_GOIN_SYNCMEDIA 		0x82
#define IR_SYNV_OUT_SYNCMEDIA 		0x83

#define IR_SYNV_APPLICATION   		0x22
#define IR_SYNV_NOTSYNCPAGE   		0xA0
#define IR_SYNV_ISSYNCPAGE   		0xA1
#define IR_SYNV_STANDBY_TRIGGER_SPEECH  0x50

//cmd:0x01
//cmd:0x02

//cmd:0xFF
#define IR_SYNV_FLYSYSTEM_OPERATNORMAL 0x00


////////////////////////////////////////////////////////////////////////
#define SYNC_MODE       0xA0
#define SYNC_CMD_0X00   0x00
#define SYNC_CMD_0X01   0x01
#define SYNC_CMD_0X02   0x02
#define SYNC_CMD_0XFF   0xFF

void syncToHal_Command(u8 uMode,u8 uCmd,u8 u8Param);
/////////////////////////////////////////////////////////////////////////

#endif
