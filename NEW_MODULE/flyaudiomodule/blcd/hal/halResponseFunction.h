#ifndef __HAL_RESPONSE_COMMAND_H__
#define __HAL_RESPONSE_COMMAND_H__

#include "global.h"
#include "messageQueue.h"


enum emBlcdMode {emBlcdMode_DVD=0x00,emBlcdMode_CDC=0x03,emBlcdMode_Radio=0x02,emBlcdMode_TV=0x01,emBlcdMode_AUX=0x04};

enum emSetBlcdMode	{emSetBlcdMode_DVD=0x00,emSetBlcdMode_CDC_TV=0x01,emSetBlcdMode_Radio=0x02,emSetBlcdMode_AUX=0x04};


////新协议对应的声道
enum emSoundMode{SoundMode_DVD=0x00,VideoMode_DVD =0x01,SoundMode_CDC=0x02,VideoMode_CDC=0x03,SoundMode_RADIO=0x04,SoundMode_AUX=0x05,VideoMode_AUX=0x06,
SoundMode_IPOD=0x07,VideoMode_IPOD=0x08,SoundMode_TV=0x09,VideoMode_TV=0x0A,SoundMode_MEDIA=0x0B,SoundMode_STANDBY=0x80};


void analyseHalMessage_BLCD(char resCmd, unsigned char *param, unsigned char len);

void Get_Mode(u8 param);

void Show_Blcd_Mode();
void halToBLCD_SetMode(u8 param);

void Show_CDC_PlayControl(u8 previousAnolog,u8 playAnolog,u8 stopAnolog,u8 nextAnolog);

#endif
