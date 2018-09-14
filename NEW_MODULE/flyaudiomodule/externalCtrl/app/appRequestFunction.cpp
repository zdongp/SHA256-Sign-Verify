#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"

void externalCtrlToSpeechApp_StartSpeechRecognitionActivity()
{
	u8 param[2] = {0xa0,0x01};
	setCommand(0x00000000, param, 2);
}

void externalCtrlToSpeechApp_RequestCtrlCmd(u8 p)
{
	u8 param[3] = {0xa0,0x02,p};
	setCommand(0x00000000, param, 3);
}

void externalCtrlToApp_selectedSongs(u8 p)
{
	u8 param[3] = {0xa0,0x03,p};
	setCommand(0x00000000, param, 3);
}

void externalCtrlToRemoteDiagnosticsApp_SysInfors(u8 *p,int len)
{
	u8 param[256];
	memset(param,0,sizeof(param));
	
	param[0] = 0xa1;

	if(len > (256-1))
		len = 255;
	
	memcpy(&param[1],p,len);
	
	setCommand(0x00000000, param,len+1);
}

void externalCtrlToApp_CtrlVoiceSwitch(u8 p)
{
	LOGD("[%s] p:%d",__FUNCTION__,p);
	u8 param[3] = {0xa0,0x04,p};
	setCommand(0x00000000, param, 3);
}


