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
#include "otherModuleResponseFunction.h"


void setDefaultParam(void){

	pLocalParam->enter = true;
	pLocalParam->playStatus = 0;
	pLocalParam->trackSum=-1;
	pLocalParam->curTrack=-1;
	pLocalParam->rand=0;
	pLocalParam->RPT=0;
	pLocalParam->typeListInfo.iType = 0;
	pLocalParam->typeListInfo.iCurPos = 0;
	pLocalParam->typeListInfo.iSum =0;
	pLocalParam->typeListInfo.iShowPos=0;
	pLocalParam->browseSongPos =0;
	pLocalParam->search = false;
	pLocalParam->initPlayStatus = true;
	//pLocalParam->IPODConnect = true;
	pLocalParam->airMode= false;
	pLocalParam->IPODMode = false;
	pLocalParam->showSubOSD = false;
	pLocalParam->contolPlayStatus = 1;
	pLocalParam->userConnected = true;
	pLocalParam->position=0;
	pLocalParam->cmdlength=0;
	pLocalParam->pingIpodSuccess=0;
	pLocalParam->ipodNextSongTimerING=0;
	//memset(&(pLocalParam->browseHistoryInfo),0,sizeof(pLocalParam->browseHistoryInfo));

	setUpdateUI(false);

	setVisible(CONTROLID_IPOD_MAIN_TITLE_TEXT,false);
	setVisible(CONTROLID_IPOD_MAIN_CURRENT_TITLE_NUM,false);

	setVisible(CONTROLID_IPOD_MAIN_TRACK_TEXT,false);
	//setVisible(CONTROLID_IPOD_MAIN_CURRENT_TRACK_NUM,false);

	setUpdateUI(true);

}


void moduleParameterInit(void){
	LOGD("moduleParameterInit");
}

void moduleParameterDeInit(void){

}

void moduleParameterReInit(void){
	LOGD("&&&&&&&&&&&&&&&&&&&& Ipod moduleParameterReInit");

}

int module_extendInterface(char *buffer, int len){
	LOGD("**********************Ipod module_extendInterface",buffer[0],buffer[1]);
	switch(buffer[0]){
		case 0x2C:
			if(buffer[1] == 0x00)//acc off
			{
				//saveParameter();
				//int bTempTVStatus;
				//bTempTVStatus = pLocalParam->tvStatus;
				//setDefaultParam();
				//pLocalParam->tvStatus = bTempTVStatus;

			}
			if(buffer[1] == 0x01)//restart
			{
				LOGD("************************restart");
				saveParameter();
			}
			if(buffer[1] == 0x02)//default
			{
				LOGD("************************default");
				setDefaultParam();
				saveParameter();
			}
			break;
		case 0x2D://acc on
			if(buffer[1] == 0x00)
			{

				short curSound = 0;
				unsigned char curSoundLen = 2;
				getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8 *)&curSound, (u8 *)&curSoundLen);

				if (curSound != CHANNEL_IPOD_CTRL && curSound != CHANNEL_IPOD_VIDEO)
				{
					ClearIPODMessage();
					return 0;
				}
				//pLocalParam->initPlayStatus = 1;
				GetIPODConnect(1);
				//readParameter();
				//ReInitWhenAccOn();

			}
			break;
		case 0xFD:
			{
				//initTimerCenter(&TimerHandlerCenter);
				ipodToHal_EnterAIRMode();
				usleep(300*1000);
				ipodToHal_QueryIPODType();
			}
			break;
		default:break;
	}

	return 0;
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		default:break;
	}
}


//开始连接IPOD
void StartConnectIpod()
{

	if(!(pLocalParam->IPODMode))//如果不是在IPOD模式
		return;
	//if(!(pLocalParam->IPODConnect))//如果没有连接IPOD
		//return;

	//if(pLocalParam->airMode)//如果在Air模式
       // return;

    LOGD(" StartConnectIpod");
	ipodToHal_EnterAIRMode();
	usleep(300*1000);
	ipodToHal_QueryIPODType();
	//	Message_SetConnectPing();

	//thebug
	//SetTimer(theApp.m_pMainWnd->m_hWnd,500,1000,NULL);
	SetTimer(5000,0,IPOD_CONNECT_TIMER);;

}


//清除IPOD信息，主要是IPOD拔出后 还原IPOD信息
void ClearIPODMessage()
{
	pLocalParam->enter = true;
	pLocalParam->playStatus = 0;
	pLocalParam->trackSum=-1;
	pLocalParam->curTrack=-1;
	pLocalParam->rand=0;
	pLocalParam->RPT=0;
	pLocalParam->typeListInfo.iType = 0;
	pLocalParam->typeListInfo.iCurPos = 0;
	pLocalParam->typeListInfo.iSum =0;
	pLocalParam->typeListInfo.iShowPos=0;
	pLocalParam->browseSongPos =0;
	pLocalParam->initPlayStatus = true;
	pLocalParam->IPODConnect = true;//默认是连接的 是因为在系统启动时 IPOD连接状态不确定 假设连接上去可以加快连接速度
	pLocalParam->airMode= false;
	pLocalParam->pingIpodSuccess=0;
	//memset(&(pLocalParam->browseHistoryInfo),0,sizeof(pLocalParam->browseHistoryInfo));
	setUpdateUI(false);

	setDigitalData(CONTROLID_IPOD_MAIN_CONNECTED,false);

	setSerialData(CONTROLID_IPOD_MAIN_SONG_NAME,(u8*)"",0);
	setSerialData(CONTROLID_IPOD_MAIN_SINGER_NAME,(u8*)"",0);
	setSerialData(CONTROLID_IPOD_MAIN_ABLUM_NAME,(u8*)"",0);

	setVisible(CONTROLID_IPOD_MAIN_SONG_NAME,0);
	setVisible(CONTROLID_IPOD_MAIN_SINGER_NAME,0);
	setVisible(CONTROLID_IPOD_MAIN_ABLUM_NAME,0);

	setVisible(CONTROLID_IPOD_MAIN_TITLE_TEXT,false);
	setVisible(CONTROLID_IPOD_MAIN_CURRENT_TITLE_NUM,false);

	setVisible(CONTROLID_IPOD_MAIN_TRACK_TEXT,false);
	setVisible(CONTROLID_IPOD_MAIN_CURRENT_TRACK_NUM,false);

	setVisible(CONTROLID_IPOD_MAIN_CURRENT_TIME,false);
	setVisible(CONTROLID_IPOD_MAIN_CURRENT_START_TIME,false);
	setVisible(CONTROLID_IPOD_MAIN_CURRENT_SURPLUS_TIME,false);

	setUpdateUI(true);
	//setGroupNumber(CONTROLID_IPOD_MAIN_SHUFFLE,0);
	//setGroupNumber(CONTROLID_IPOD_MAIN_RPT,0);



	//CDrawText *pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_POSITIONTXT);
	//CString str = L"";
	//pText->SetData(str);

    //pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_TRACKTXT);
    //pText->SetVisible(false);

	//pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_TIMETXT);
	//pText->SetData((CString)L"");

	//pText = (CDrawText *)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_SONGTITLE);
	//pText->SetData((CString)L"");

	//pText = (CDrawText *)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_SONGARTIST);
	//pText->SetData((CString)L"");

	//pText = (CDrawText *)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_SONGALBUM);
	//pText->SetData((CString)L"");

	//CDrawImage *pImage = (CDrawImage*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_RPT);
	//pImage->SetData(0);

	//pImage = (CDrawImage*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_RAND);
	//pImage->SetData(0);

	u16 curPage = 0;
	unsigned char curPageLen = 2;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);

	if (curPage == PAGE_IPOD_SEARCH)
		{
			ipodToModule_NotifySystem_jumpPage(PAGE_IPOD);
			pLocalParam->search = false;
		}
	//theApp.RefreshUI();

	LOGD("------------IPOD---------ClearIPODMessage success");
}

void updateTypeListInfo(u8* iSongName){
	memcpy(pLocalParam->curSongName,iSongName,(2*uni16_strlen((unicode16_t *) iSongName))+2);
	//memcpy(&(pLocalParam->browseHistoryInfo),&(pLocalParam->browseInfo),sizeof(pLocalParam->browseInfo));
}

int isCurSong(int index,u8* songName){
	if(pLocalParam->browseInfo.iCurBrowsefolder!=2)
		return false;
	//if(pLocalParam->browseInfo.iCurFilePos != pLocalParam->browseInfo.iCurFileShowPos+index)
		//return false;
	int curSongNameLen = uni16_strlen((u16 *)(pLocalParam->curSongName));
	if(curSongNameLen != uni16_strlen((u16 *)songName))
		return false;
	if(memcmp(pLocalParam->curSongName,songName,2*curSongNameLen)!=0)
		return false;
	//if(memcmp(pLocalParam->curSongName,songName,2*uni16_strlen(pLocalParam->curSongName))!=0)
		//return false;
	//if(memcmp(pLocalParam->curSongName,songName,2*uni16_strlen(songName))!=0)
		//return false;
	return true;
}
