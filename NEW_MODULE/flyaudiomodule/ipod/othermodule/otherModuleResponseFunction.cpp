#include <stdio.h>
#include <stdlib.h>
//#include <cutils/properties.h>


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
#include "otherModuleResponseFunction.h"


//void *HalWriteThread(void *arg){
//
//	return NULL;
//}

//void mediaplayer_start(unsigned char ringid);
//void mediaplayer_stop();


//void setRingerCtrl(unsigned char ring){
//	u8 param[] = {0xF1, 0x00};

//	/
//	param[1] = ring;

//	setCommand(0x00000000, param, 2);
//}


void moduleToCenter_FromBT_Message(unsigned char *param, unsigned char len){
	unsigned char cmd = param[0];

	switch(cmd){
		case 0x02:
			//moduleToCenter_StartRing(0x01);
			break;
		case 0x03:
			LOGD("Stop Ring...");
			//moduleToCenter_StopRing();
			break;
		default:
			break;
	}
}

void moduleToIpod_FromSystem_Message(unsigned char *param, unsigned char len){
	unsigned char cmd = param[0];

	switch(cmd){
		case 0x2C:	// acc off
			break;
		case 0x2D:	// acc on
			break;
		case 0x70:
			LOGD("system:ipod:%d",param[1]);
			GetIPODConnect(param[1]);
			break;
	}
}

void moduleToIpod_FromKey_GetPanelKey(unsigned char keyValue){

	switch (keyValue){
		case KEY_MENU:
			ipodToModule_NotifySystem_jumpPage(PAGE_MENU);
			break;
		case KEY_AV:
			otherModuleResponse_ProcessPanelKey_AV();
			break;
		case KEY_IPOD:
		    ipodToModule_NotifySystem_jumpPage(PAGE_IPOD);
			break;
		case KEY_SEEK_INC:
			pLocalParam->showSubOSD = 1;
			ipodToModule_NotifyOsd_DisplayOSDIpodInfo(pLocalParam->curTrack+1,pLocalParam->trackSum);
			ipodToHal_SetSkipNext();

			break;
		case KEY_SEEK_DEC:
			pLocalParam->showSubOSD = 1;
			ipodToModule_NotifyOsd_DisplayOSDIpodInfo(pLocalParam->curTrack+1,pLocalParam->trackSum);
			ipodToHal_SetSkipSuperior();

			break;
		case KEY_TUNE_INC:
			pLocalParam->showSubOSD = 1;
			ipodToModule_NotifyOsd_DisplayOSDIpodInfo(pLocalParam->curTrack+1,pLocalParam->trackSum);
			ipodToHal_SetSkipNext();

			break;
		case KEY_TUNE_DEC:
			pLocalParam->showSubOSD = 1;
			ipodToModule_NotifyOsd_DisplayOSDIpodInfo(pLocalParam->curTrack+1,pLocalParam->trackSum);
			ipodToHal_SetSkipSuperior();

			break;
		default:
			break;
		}

}




void moduleToIpod_FromKey_Message(unsigned char *param, unsigned char len){
	LOGD("moduleToIpod_FromKey_Message:param[0]:%d",param[0]);
	switch(param[0]){
		case 0x00:
			moduleToIpod_FromKey_GetPanelKey(param[1]);
			break;
		case 0x01:
			break;
		default:
			break;
	}

}

void moduleToIpod_FromAudiovideo_Message(unsigned char *param, unsigned char len){
	switch(param[0]){// eg: get the audiovideo mode
		case 0x00:
			if((param[1] == CHANNEL_IPOD_CTRL) || (param[1] == CHANNEL_IPOD_VIDEO)){
				LOGD("moduleToIpod_FromAudiovideo_Message:EnterIPOD");
				EnterIPOD();
			}
			else{
				LOGD("moduleToIpod_FromAudiovideo_Message:LeaveIPOD");
				LeaveIPOD();
			}
			break;
		default:
			break;
	}
}

void moduleToIpod_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;
    analyseAppMessage(param+1,len-1);   
}



void GetIPODConnect(int bConnect)
{
	//if(pLocalParam->airMode == bConnect)
		//return;
	if(pLocalParam->userConnected == false && bConnect == true)//�û�����Ͽ� ������Ͽ�
		return;
    pLocalParam->IPODConnect = bConnect;
	if(bConnect)//����
	{
		LOGD("IPOD Connect");
		EnterIPOD();
		StartConnectIpod();
	}
	else//�Ͽ�
	{
		LOGD("IPOD DisConnect");
 		LeaveIPOD();
		pLocalParam->airMode = false;
		ipodToHal_LeaveAIRMode();
		ClearIPODMessage();
		//CDrawButton *pButton = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_CONNECTED);
        //pButton->SetData((int)0);
		//ClearIPODMessage();

	}
}

//����ipodҳ��
void EnterIPOD()
{
	LOGD("ENTER IPOD");
	pLocalParam->IPODMode = true;
	pLocalParam->enter = true;
	ipodToHal_SetConnectPing();
}

//�뿪ipodҳ��
void LeaveIPOD()
{
	LOGD("LeaveIPOD:pLocalParam->playStatus:%d",pLocalParam->playStatus);
	if(!pLocalParam->IPODMode)
		return;
	pLocalParam->IPODMode = false;
    if(pLocalParam->playStatus == 1)//play
		pLocalParam->initPlayStatus = true;
	else
		pLocalParam->initPlayStatus = false;
	//KillTimer(theApp.GetMainWnd()->m_hWnd,500);
	//DeleteTimer(IPOD_CONNECT_TIMER);
	if(pLocalParam->playStatus == 1)
	{
		pLocalParam->contolPlayStatus = 2;
		ipodToHal_SetPlayPause();
	}
}

void otherModuleResponse_ProcessPanelKey_AV(){
	u16 curPage = 0;
	unsigned char curPageLen = 2;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);

	if (curPage != PAGE_IPOD && curPage != PAGE_IPOD_SEARCH)
		{
			ipodToModule_NotifySystem_jumpPage(PAGE_IPOD);
			return;
		}
	ipodToModule_NotifySystem_SwitchModule();
}
