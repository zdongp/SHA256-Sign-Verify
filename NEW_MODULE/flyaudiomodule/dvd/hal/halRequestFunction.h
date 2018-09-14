#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__

#define DVDTOHAL_IR_NUM0			0x00
#define DVDTOHAL_IR_NUM1			0x01
#define DVDTOHAL_IR_NUM2			0x02
#define DVDTOHAL_IR_NUM3			0x03
#define DVDTOHAL_IR_NUM4			0x04
#define DVDTOHAL_IR_NUM5			0x05
#define DVDTOHAL_IR_NUM6			0x06
#define DVDTOHAL_IR_NUM7			0x07
#define DVDTOHAL_IR_NUM8			0x08
#define DVDTOHAL_IR_NUM9			0x09

#define DVDTOHAL_IR_UP			0x0D
#define DVDTOHAL_IR_LEFT			0x0E
#define DVDTOHAL_IR_RIGHT			0x0F
#define DVDTOHAL_IR_DOWN			0x10
#define DVDTOHAL_IR_ENTER			0x11

#define DVDTOHAL_IR_PLAY			0x14
#define DVDTOHAL_IR_PAUSE			0x15
#define DVDTOHAL_IR_STOP			0x17
#define DVDTOHAL_IR_NEXT			0x18
#define DVDTOHAL_IR_PREV			0x19
#define DVDTOHAL_IR_REPEAT		0x1A

/* FF:Fast Forward; FR:Fast Backward; SF:Slow Forward; SR:Slow Backward */
#define DVDTOHAL_IR_FF			0x21
#define DVDTOHAL_IR_FR			0x27
#define DVDTOHAL_IR_SF			0x2D
#define DVDTOHAL_IR_SR			0x33
#define DVDTOHAL_IR_STEPF			0x39

/* IR_SET_A:AB Repeat; IR_ROOT_MENU: return/exit dvd menu */
#define DVDTOHAL_IR_SET_A			0x3C
#define DVDTOHAL_IR_TITLE_MENU	0x3E
#define DVDTOHAL_IR_ROOT_MENU		0x3F

/* AUDIO: audio switch; SUB_TITLE:title switch; ANGLE:angle switch; DISPLAY:show play info */
#define DVDTOHAL_IR_AUDIO			0x44
#define DVDTOHAL_IR_SUB_TITLE		0x45
#define DVDTOHAL_IR_ANGLE			0x47
#define DVDTOHAL_IR_DISPLAY		0x48

/* search button */
#define DVDTOHAL_IR_GOTO			0x4A

/* VCD PBC On/Off */
#define DVDTOHAL_IR_PBC			0x4D

/* program button */
#define DVDTOHAL_IR_PROGRAM		0x4F

/* MEMORY:memory or remembrance; PLAY_MODE:play mode switch; PAL_NTSC:N/P switch */
#define DVDTOHAL_IR_MEMORY		0x52
#define DVDTOHAL_IR_PLAY_MODE		0x53
#define DVDTOHAL_IR_PAL_NTSC		0x54

/* to Enlarge */
#define DVDTOHAL_IR_ZOOM_OUT		0x5A

#define DVDTOHAL_IR_SETUP			0x60

#define DVDTOHAL_IR_UART_PM_NORMAL		0x62
#define DVDTOHAL_IR_UART_PM_SHUFFLE		0x63
#define DVDTOHAL_IR_UART_PM_RANDOM		0x64
#define DVDTOHAL_IR_UART_PM_INTRO			0x65

#define DVDTOHAL_IR_REPEAT_OFF		0x67
#define DVDTOHAL_IR_REPEAT_SINGLE		0x68
#define DVDTOHAL_IR_REPEAT_FOLDER		0x69
#define DVDTOHAL_IR_REPEAT_ALL		0x6A

#define DVDTOHAL_IR_MUTE				0x6B
#define DVDTOHAL_IR_VOLUME_UP			0x6C
#define DVDTOHAL_IR_VOLUME_DOWN		0x6D

/* Out of DVD DISC */
#define DVDTOHAL_IR_EJECT				0x7C

#define DVDTOHAL_IR_DISC				0x95
#define DVDTOHAL_IR_USB				0x96
#define DVDTOHAL_IR_SD				0x97





void dvdToHal_Init(unsigned char param);
void dvdToHal_SimulateKey(unsigned char key);
void dvdToHal_IR(unsigned char IR_key);
void dvdToHal_PlayMode(unsigned char playMode);
void dvdToHal_PlayByIndex(unsigned short index);
void dvdToHal_RequestFileDirName(unsigned char browseSize, unsigned short startPos);
void dvdToHal_SetVideoMode(unsigned char mode);

#endif
