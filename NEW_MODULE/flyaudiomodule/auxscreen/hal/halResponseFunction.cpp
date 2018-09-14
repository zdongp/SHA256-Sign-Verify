#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
//初始化状态
void halToAuxScreen_InitParam(u8 nState){
 
}

//初始化参数
void halToAuxScreen_InitState(u8 nState){
}


//小屏设备是否存在
void halToAuxScreen_IsAuxScreenDeviceExited(u8 nExited){
	pLocalParam->nIsAuxscreenExited = nExited;
	//if(pLocalParam->nIsAuxscreenExited)
		//auxScreenToHal_PlayingModule(pLocalParam->nCurPlayingModule);
}

void halToAuxScreen_Control(u8 cmd)
{
	switch(cmd)
	{
		case 0x00://end calling
		case 0x01://answer
		case 0x02://hang
		case 0x03://Transfer phone
		case 0x04://Transfer car
		case 0x05://Mic Mute
		case 0x06://Mic UnMute
			auxscreenToModule_NotifyBt_PhoneCtrl(cmd);
		break;
	}
}

void halToAuxScreen_Request_GetCallLogList(u8 type,u8 param)
{
	switch(type)
	{
		case 0x01://ALL logs
		case 0x02://Received
		case 0x03://Dialed
		case 0x04://missed
		case 0x05://other list
			auxscreenToModule_NotifyBt_Request_GetCallLogList(type,param);
		break;
	}
}

void halToAuxScreen_ReturnPhoneDialOperating(u8 type,u8 param)
{
	switch(type)
	{
		case 0x01://ALL logs
		case 0x02://Received
		case 0x03://Dialed
		case 0x04://missed
		case 0x05://other list
			auxscreenToModule_NotifyBt_ReturnPhoneDialOperating(type,param);
		break;
	}
}


void halToAuxScreenSetRadioStatusMessage(u8 param,u8 *buf,int len)
{
	u8 buff[255] = {0};
	buff[0] = param;
	memcpy(buff+1,buf,len);
	auxscreenToRadioSetStatusMessage(buff,len+1);
}
void analyseHalSetGpsStatusMessage(u8 *param,int len)
{
	switch(param[0])
       {
               case 0xF0:
                       sendToApp_EndNavigationMessage(param[1]);
                       break;
               default:break;
       }
}

void analyseHalSetJumpMediaPageMessage(u8 *param,int len)
{
	switch(param[0])
       {
               case 0x02:
			   	auxscreenToModule_NotifySystem_jumpPage(PAGE_RADIO_MAIN);
                       break;
		case 0x06:
				auxscreenToModule_NotifySystem_jumpPage(PAGE_MEDIA);
			break;
		case 0x08:
				auxscreenToModule_NotifySystem_jumpPage(PAGE_BLUETOOTH_A2DP);
			break;
               default:break;
       }
}


