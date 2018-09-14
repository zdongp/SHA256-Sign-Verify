#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "param.h"
#include "pageID.h"
#include "appResponseCommand.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"


void appInit(void){

}

void appDeInit(void){

}

void appToIpod_MouseUp(u32 ctrlId,u8 u8_MouseStatus,u8 *param,u8 len)
{
	switch(ctrlId){
		/* ÌøÒ³°´Å¥ */
		case CONTROLID_MENU_IPOD:
		case CONTROLID_IPOD_SEARCH_BACK:
			//SetTimer(1000,0,THEBUG_TIMER);
			pLocalParam->search = false;
			ipodToModule_NotifySystem_jumpPage(PAGE_IPOD);
			break;
		case CONTROLID_IPOD_MAIN_BACK:
			ipodToModule_NotifySystem_jumpPage(PAGE_MENU);
			break;
		case CONTROLID_IPOD_MAIN_SEARCH:
			appToIpod_EnterSearchPage();
			
			break;
		case CONTROLID_IPOD_MAIN_AUDIO:
			ipodToModule_NotifySystem_jumpPage(PAGE_SOUND);		
			break;
		////////////////////////////////
		case CONTROLID_IPOD_MAIN_NEXT:
			appToIpod_MainNext_MouseUp();
			break;
		case CONTROLID_IPOD_MAIN_PREV:
			appToIpod_MainPrev_MouseUp();
			break;
		case CONTROLID_IPOD_MAIN_PLAYPAUSE:
			appToIpod_MainPlayPause_MouseUp();
			break;
		
		case CONTROLID_IPOD_MAIN_SHUFFLE:
			appToIpod_MainShuffle_MouseUp();
			break;
		case CONTROLID_IPOD_SEARCH_CURPAGE:
			appToIpod_BrowseReturn();
			break;
		case CONTROLID_IPOD_MAIN_RPT:
			appToIpod_MainRPT_MouseUp();
			break;
		case CONTROLID_IPOD_SEARCH_PREVPAGE:
			appToIpod_SearchPrevPage_MouseUp();
			break;
		case CONTROLID_IPOD_SEARCH_NEXTPAGE:
			appToIpod_SearchNextPage_MouseUp();
			break;
		case CONTROLID_IPOD_SEARCH_GAUGE:	
			appToIpod_SearchGauge_MouseUp(param,len);
			break;
		case CONTROLID_IPOD_MAIN_CONNECTED:
			appToIpod_MainConnected_MouseUp();
			break;

		case CONTROLID_IPOD_SEARCH_ITEM_BEGIN + 0x00:
		case CONTROLID_IPOD_SEARCH_ITEM_BEGIN + 0x01:
		case CONTROLID_IPOD_SEARCH_ITEM_BEGIN + 0x02:
		case CONTROLID_IPOD_SEARCH_ITEM_BEGIN + 0x03:
		case CONTROLID_IPOD_SEARCH_ITEM_BEGIN + 0x04:	
			{
				appToIpod_SearchItem_MouseUp(ctrlId-CONTROLID_IPOD_SEARCH_ITEM_BEGIN);
			}
			break;
		default:break;
	}
}

void analyseAppMessage(unsigned char *buffer, unsigned char len){
	int ctrlId = 0;
	char ctrlType;
	unsigned char paramLen;
	unsigned char *param;
	u8 u8_MouseStatus = 0;

	ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
	ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
	ctrlId += (int)((buffer[2] << 8) & 0xFF00);
	ctrlId += (int)(buffer[3] & 0xFF);

	ctrlType = buffer[4];
	u8_MouseStatus = buffer[5];
	paramLen = len - 5;
	param = &buffer[5];

	LOGD("AppToIpod_ctrlType:0x%x. %x %x+++++++++\n",ctrlId,ctrlType,u8_MouseStatus);
	switch(ctrlType)
    {
		 case UIACTION_MOUSEUP:
		   	    appToIpod_MouseUp(ctrlId,u8_MouseStatus,param,len);
		        break;
		 defualt:break;
    }
}






