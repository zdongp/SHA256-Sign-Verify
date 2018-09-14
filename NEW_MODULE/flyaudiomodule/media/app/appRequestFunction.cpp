#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"

void mediaToApp_playNext()//������һ��
{
	u8 param[2] = {0x60, 0x01};
	sendCommandToApp(param,2);
}
void mediaToApp_palyPrev()//������һ��
{
	u8 param[2] = {0x60, 0x02};
	sendCommandToApp(param,2);	
}

void mediaToApp_stop(void)//ֹͣ����
{
	u8 param[2] = {0x61, 0x00};
	sendCommandToApp(param,2);	
}

void mediaToApp_play(void)//����
{
	u8 param[2] = {0x61, 0x01};
	sendCommandToApp(param,2);	

}

void mediaToApp_pause(void)
{
	u8 param[2] = {0x61, 0x02};
	sendCommandToApp(param,2);	

}

void mediaToApp_SendMediaChannelState(u8 bMediaChannel)
{
	u8 param[2] = {0x62, bMediaChannel};
	sendCommandToApp(param,2);
}

void Automate_GoToAutoMate(u8 b)
{
	u8 param[2] = {0x63, b};
	sendCommandToApp(param,2);
}

void Automate_selectMusic(u8 b)
{
	u8 param[2] = {0x64, b};
	sendCommandToApp(param,2);
}

void Automate_getUSBState(u8 b)
{
	u8 param[2] = {0x65, b};
	sendCommandToApp(param,2);
}

void mediaToApp_SetplayMod(u8 b)
{
	u8 param[2] = {0x66, b};
	sendCommandToApp(param,2);	
}

void mediaToApp_finishPlay(void)
{
	u8 param[2] = {0x67, 0x01};
	sendCommandToApp(param,2);	
}

void mediaToApp_SpecifyToPlayTheSongOrNo(u8 *param,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = 0x68;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, param, len);
	sendCommandToApp(szMsg,len+1);	
}

void mediaToApp_enterMediaChannel_IsNormal(u8 p)
{
	u8 param[2] = {0x69, 0x00};
	param[1] = p;
	sendCommandToApp(param,2);	
}

