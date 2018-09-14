#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"

#include <flymoduleApi_internal.h>

void dvdToHal_Init(unsigned char param){
	unsigned char buf[] = {0x01, 0x01};
	makeAndSendMessageToHal(HAL_ID_DVD,buf, 2);
}

void dvdToHal_SimulateKey(unsigned char key){
	unsigned char buf[] = { 0x03, key};
	makeAndSendMessageToHal(HAL_ID_DVD,buf, 2);
}

void dvdToHal_IR(unsigned char IR_key){

	unsigned char buf[] = {0x10, IR_key};
	makeAndSendMessageToHal(HAL_ID_DVD,buf, 2);
}

void dvdToHal_PlayMode(unsigned char playMode){
	unsigned char buf[] = {0x11, playMode};

	makeAndSendMessageToHal(HAL_ID_DVD,buf,2);
}

void dvdToHal_PlayByIndex(unsigned short index){
	unsigned char buf[] = { 0x12, 0x00, 0x00};
	buf[1] = (unsigned char)((index & 0xFF00) >> 8);
	buf[2] = (unsigned char)(index & 0x00FF);

	makeAndSendMessageToHal(HAL_ID_DVD,buf, 3);
}

void dvdToHal_RequestFileDirName(unsigned char browseSize, unsigned short startPos){
	unsigned char buf[] = { 0x13, browseSize, 0x00, 0x00};
	buf[2] = (unsigned char)( (startPos & 0xFF00) >> 8);
	buf[3] = (unsigned char)(startPos & 0x00FF);

	makeAndSendMessageToHal(HAL_ID_DVD,buf, 4);
}

void dvdToHal_SetVideoMode(unsigned char mode){
	unsigned char buf[] = { 0x15, mode};

	makeAndSendMessageToHal(HAL_ID_DVD,buf, 2);
}
