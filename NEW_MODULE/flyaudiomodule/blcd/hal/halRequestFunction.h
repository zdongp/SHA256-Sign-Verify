#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__


#define DVDTOHAL_IR_PLAY			0x14
#define DVDTOHAL_IR_PAUSE			0x15
#define DVDTOHAL_IR_STOP			0x17
#define DVDTOHAL_IR_NEXT			0x18
#define DVDTOHAL_IR_PREV			0x19


//void dvdToHal_IR(unsigned char IR_key);
void blcdToHal_Init(char param);
void blcdToHal_SetSoundChannel(unsigned char soundChannel);
void blcdToHal_SetVideoChannel(u8 ch); 

#endif
