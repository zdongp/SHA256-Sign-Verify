#include <stdio.h>
#include <stdlib.h>


#include "global.h"
#include "hal.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "timer_interface.h"
#include "moduleParamRequest.h"
#include "moduleParamResponse.h"

#include <flymoduleApi_internal.h>

unsigned char checkSum(unsigned char *buf, int len)
{
	int i = 0;
	unsigned char checksum = 0;

	for( ; i <= len; i++)
		checksum += buf[i];

	checksum = 0x100 - (checksum & 0xFF);

	return (unsigned char)checksum;
}

void makeAndSendIpodMessageToHal(char cmd, halid_t halId, u8 *buf, int len)
{
	int sendLen = len+5;
	u8 *messagebuf = (u8*)malloc(sendLen);
	if(!messagebuf) return ;

	memset(messagebuf, 0, sendLen);
	messagebuf[0] = (unsigned char)cmd;
	messagebuf[1] = 0xFF;
	messagebuf[2] = 0x55;
	messagebuf[3] = (unsigned char)len;
	memcpy(&messagebuf[4], buf, len);
	messagebuf[sendLen -1] = checkSum(&messagebuf[3], len);

	makeAndSendMessageToHal(halId, messagebuf, sendLen);
	if(messagebuf)
	{
		free(messagebuf);
		messagebuf = 0;
	}
}

void ipodToHal_SetConnectPing(){
	pLocalParam->pingIpodSuccess = 0;
	unsigned char buf[] = { 0x04,0x00,0x02};//,0xf7};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 3);
}

void ipodToHal_QueryIPODType(){

	unsigned char buf[] = { 0x04,0x00,0x12};//,0xe7};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 3);
}

void ipodToHal_QueryIPODName(){
	unsigned char buf[] = { 0x04,0x00,0x14};//,0xe5};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 3);
}

void ipodToHal_EnterAIRMode(){
	unsigned char buf[] = { 0x00,0x01,0x04};//,0xf8};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 3);
}


void ipodToHal_LeaveAIRMode(){
	unsigned char buf[] = { 0x00,0x01,0x00};//,0xfc};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 3);
}

void ipodToHal_SetMusicControl(){
	unsigned char buf[] = { 0x04,0x00,0x16};//,0xe3};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 3);

	usleep(50*1000);
}

void ipodToHal_SetTypeMode(int iType,unsigned int iItem){
	unsigned char buff[] = { 0x04,0x00,0x17,0x00,0x00,0x00,0x00,0x00};

	buff[3] =(unsigned char)iType;
	buff[4] =(unsigned char)(iItem>>24);
    buff[5] =(unsigned char)((iItem&0x00FF0000)>>16);
	buff[6] =(unsigned char)((iItem&0x0000FF00)>>8);
	buff[7]=(unsigned char)(iItem&0x000000FF);
	//buff[8]=(unsigned char)(0x100-((buff[2]+buff[3]+buff[4]+buff[5]+buff[6]+buff[7]+buff[8]+buff[9]+buff[10])&0xFF));

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buff, 8);
}

void ipodToHal_QueryTypeSum(int iType){
	unsigned char buff[]= {0x04, 0x00, 0x18,0x00};
	buff[3] =(unsigned char)iType;
	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buff, 4);
}

void ipodToHal_QueryTypeItemString(int iType,unsigned int iStartnum,unsigned int iNum){
	unsigned char buff[]= {0x04,0x00,0x1a, 0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00};
	buff[3] =(unsigned char)iType;
	buff[4] =(unsigned char)(iStartnum>>24);
    buff[5] =(unsigned char)((iStartnum&0x00FF0000)>>16);
	buff[6] =(unsigned char)((iStartnum&0x0000FF00)>>8);
	buff[7]=(unsigned char)(iStartnum&0x000000FF);
	buff[8] =(unsigned char)(iNum>>24);
    buff[9] =(unsigned char)((iNum&0x00FF0000)>>16);
	buff[10] =(unsigned char)((iNum&0x0000FF00)>>8);
	buff[11]=(unsigned char)(iNum&0x000000FF);
	//buff[15]=(unsigned char)(0x100-((buff[2]+buff[3]+buff[4]+buff[5]+buff[6]+buff[7]+buff[8]+buff[9]+buff[10]+buff[11]+buff[12]+buff[13]+buff[14])&0xFF));

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buff, 12);
}

void ipodToHal_SetTimeState(){
	unsigned char buf[] = { 0x04, 0x00, 0x1c};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 3);
}

void ipodToHal_QueryTypeListIndex(){
	unsigned char buf[] = { 0x04, 0x00, 0x1E};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 3);
}

void ipodToHal_QueryCurrentPositionMusicName(unsigned int iNumber){
	unsigned char buff[]= {0x04,0x00,0x20, 0x00,0x00,0x00,0x00};
	buff[3] =(unsigned char)(iNumber>>24);
    buff[4] =(unsigned char)((iNumber&0x00FF0000)>>16);
	buff[5] =(unsigned char)((iNumber&0x0000FF00)>>8);
	buff[6]=(unsigned char)(iNumber&0x000000FF);
	//buff[7] =(unsigned char)(0x100-((buff[2]+buff[3]+buff[4]+buff[5]+buff[6]+buff[7]+buff[8]+buff[9])&0xFF));

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buff, 7);
}

void ipodToHal_QueryCurrentPositionArtist(unsigned int iNumber){
	unsigned char buf[]= {0x04,0x00,0x22, 0x00,0x00,0x00,0x00};
	buf[3] =(unsigned char)(iNumber>>24);
    buf[4] =(unsigned char)((iNumber&0x00FF0000)>>16);
	buf[5] =(unsigned char)((iNumber&0x0000FF00)>>8);
	buf[6]=(unsigned char)(iNumber&0x000000FF);
	//buff[10] =(unsigned char)(0x100-((buff[2]+buff[3]+buff[4]+buff[5]+buff[6]+buff[7]+buff[8]+buff[9])&0xFF));

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 7);
}

void ipodToHal_QueryCurrentPositionAlbum(unsigned int iNumber){
	unsigned char buf[] = { 0x04,0x00,0x24, 0x00,0x00,0x00,0x00};
	buf[3] =(unsigned char)(iNumber>>24);
    buf[4] =(unsigned char)((iNumber&0x00FF0000)>>16);
	buf[5] =(unsigned char)((iNumber&0x0000FF00)>>8);
	buf[6]=(unsigned char)(iNumber&0x000000FF);
	//buff[10] =(unsigned char)(0x100-((buff[2]+buff[3]+buff[4]+buff[5]+buff[6]+buff[7]+buff[8]+buff[9])&0xFF));

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 7);
}

void ipodToHal_SetStartReturnTime(){
	unsigned char buf[] = { 0x04, 0x00, 0x26, 0x01};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 4);
}

void ipodToHal_SetStopReturnTime(){
	unsigned char buf[] = { 0x04, 0x00, 0x26, 0x00};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 4);
}


void ipodToHal_SetFirstItemPlay(){
	unsigned char buf[] = { 0x04, 0x00, 0x28, 0xff, 0xff, 0xff, 0xff};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 7);
}

void ipodToHal_SetPlayListPlay(unsigned int iNumber){
	unsigned char buf[] = { 0x04,0x00,0x28, 0x00,0x00,0x00,0x00};
	buf[3] =(unsigned char)(iNumber>>24);
    buf[4] =(unsigned char)((iNumber&0x00FF0000)>>16);
	buf[5] =(unsigned char)((iNumber&0x0000FF00)>>8);
	buf[6]=(unsigned char)(iNumber&0x000000FF);
	//buff[10] =(unsigned char)(0x100-((buff[2]+buff[3]+buff[4]+buff[5]+buff[6]+buff[7]+buff[8]+buff[9])&0xFF));

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 7);
}

void ipodToHal_SetPlayPause(){
	unsigned char buf[] = { 0x04, 0x00, 0x29, 0x01};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 4);

	ipodToHal_SetTimeState();
}

void ipodToHal_SetStop(){
	unsigned char buf[] = { 0x04, 0x00, 0x29, 0x02};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 4);

	ipodToHal_SetTimeState();
}

void ipodToHal_SetSkipSuperior(){
	unsigned char buf[] = { 0x04, 0x00, 0x29, 0x04};
	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 4);

	SetTimer(1000,1,IPOD_PREVNEXTSONG_TIMER);

	if(pLocalParam->curTrack>0)
		halToIpod_GetTypeListIndex(pLocalParam->curTrack-1);
	else
		halToIpod_GetTypeListIndex(pLocalParam->trackSum-1);

}

void ipodToHal_SetSkipNext(){
	unsigned char buf[] = { 0x04 ,0x00 ,0x29 ,0x03};
	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 4);

	SetTimer(1000,1,IPOD_PREVNEXTSONG_TIMER);

	if(pLocalParam->curTrack<pLocalParam->trackSum-1)
		halToIpod_GetTypeListIndex(pLocalParam->curTrack+1);
	else
		halToIpod_GetTypeListIndex(0);
}

void ipodToHal_SetFFwd(){
	unsigned char buf[] = { 0x04, 0x00 ,0x29, 0x05};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 4);
}

void ipodToHal_SetFRwd(){
	unsigned char buf[] = { 0x04 ,0x00, 0x29, 0x06};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 4);
}

void ipodToHal_SetStopFFRW(){
	unsigned char buf[] = { 0x04, 0x00, 0x29, 0x07};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 4);
}

void ipodToHal_QueryShuffleMode(){
	unsigned char buf[] = { 0x04, 0x00, 0x2c};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 3);
}

void ipodToHal_SetShuffleMode(int iShuffleMode){
	unsigned char buf[] = { 0x04, 0x00, 0x2e ,0x00};
	buf[3] =(unsigned char)iShuffleMode;
   // buff[7] =(unsigned char)(0x100-((buff[2]+buff[3]+buff[4]+buff[5]+buff[6])&0xFF));

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 4);
}

void ipodToHal_QueryRepeatMode(){
	unsigned char buf[] = { 0x04, 0x00, 0x2f};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 3);
}

void ipodToHal_SetRepeatMode(int iRepeatMode){
	unsigned char buf[] = { 0x04, 0x00, 0x31 ,0x00};
	buf[3] =(unsigned char)iRepeatMode;
    //buff[4] =(unsigned char)(0x100-((buff[2]+buff[3]+buff[4]+buff[5]+buff[6])&0xFF));

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 4);
}

void ipodToHal_QueryCurPlayListSongSum(){
	unsigned char buf[] = { 0x04, 0x00 ,0x35};

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 3);
}

void ipodToHal_SetCurrentPositionPlay(unsigned int iNumber){
	unsigned char buf[] = { 0x04,0x00,0x37, 0x00,0x00,0x00,0x00};
	buf[3] =(unsigned char)(iNumber>>24);
    buf[4] =(unsigned char)((iNumber&0x00FF0000)>>16);
	buf[5] =(unsigned char)((iNumber&0x0000FF00)>>8);
	buf[6]=(unsigned char)(iNumber&0x000000FF);
	//buff[10] =(unsigned char)(0x100-((buff[2]+buff[3]+buff[4]+buff[5]+buff[6]+buff[7]+buff[8]+buff[9])&0xFF));

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf,7);
}

void ipodToHal_SetBrowseItem(int iType,unsigned int item){
	unsigned char buf[] = { 0x04,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0xFF};
	buf[3] =(unsigned char)iType;
	buf[4] =(unsigned char)(item>>24);
    buf[5] =(unsigned char)((item&0x00FF0000)>>16);
	buf[6] =(unsigned char)((item&0x0000FF00)>>8);
	buf[7]=(unsigned char)(item&0x000000FF);
	//buff[12]=(unsigned char)(0x100-((buff[2]+buff[3]+buff[4]+buff[5]+buff[6]+buff[7]+buff[8]+buff[9]+buff[10]+buff[11])&0xFF));

	makeAndSendIpodMessageToHal(0x09,HAL_ID_IPOD, buf, 9);
}
