#include <stdio.h>
#include <stdlib.h>
//#include <cutils/properties.h>
#include "types_def.h"
#include "commonFunc.h"
#include "global.h"
#include "pageID.h"
#include "otherModuleResponseFunction.h"
#include "param.h"
#include "appRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"

/*#include "timer_interface.h"*/

void moduleToGps_FromKey_Message(unsigned char *param, unsigned char len){
	if(param[0] != 0x00)
		return;

	u16 curpage = 0;
	u8 pagelen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curpage, &pagelen);

	if(curpage == PAGE_BACK_NOVIDEO || curpage == PAGE_BACK_VIDEO){
		return;
	}  
    
    
	short curSound = 0;
	unsigned char curSoundLen = 2;
	getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8 *)&curSound, (u8 *)&curSoundLen);
	LOGD("curSound:0x%x",curSound);
	switch(curSound)
		{
		  case CHANNEL_DVD_CTRL:
		  case CHANNEL_DVD_VIDEO:	
		  	   gpsToModule_NotifyDVDModule_jumpPage();
		  	   break;
	      case CHANNEL_AUX_VIDEO:
		  case CHANNEL_AUX_CTRL:
		  	   gpsToModule_NotifyAuxModule_jumpPage();
		  	   break;
		  case CHANNEL_TV_CTRL:
		  case CHANNEL_TV_VIDEO:
		  	   gpsToModule_NotifyTVModule_jumpPage();
		  	   break;
		  default:
		  	break;
		}
		
	u8 keyvalue = param[1];
	LOGD("keyvalue:0x%x",keyvalue);
	LOGD("curpage %x",curpage);
		
	switch(keyvalue){
		case 0x10:		// NAVI KEY
			if(curpage==PAGE_GPS_PAGE){
				gpsToModule_NotifySystem_jumpPrePage();
			}
			else {
				//setPanelKeyToAndroid(0x00);
				gpsToModule_NotifySystem_jumpPage(PAGE_GPS_PAGE);
			}
			break;	
		case 0x11:		// DEST KEY
			if(curpage != PAGE_GPS_PAGE){
				//setPanelKeyToAndroid(0x00);
				gpsToModule_NotifySystem_jumpPage(PAGE_GPS_PAGE);
			}
			setPanelKeyToAndroid(0x01);
			break;
		case 0x12:		// LOCAL KEY
			if(curpage != PAGE_GPS_PAGE){
				//setPanelKeyToAndroid(0x00);
				gpsToModule_NotifySystem_jumpPage(PAGE_GPS_PAGE);
			}
			setPanelKeyToAndroid(0x02);
			break;
		case 0x3B:		// TUNE_INC
			if(curpage == PAGE_GPS_PAGE){
				setPanelKeyToAndroid(0x03);
			}
			break;
		case 0x3C:		// TUNE_DEC
			if(curpage == PAGE_GPS_PAGE){
				setPanelKeyToAndroid(0x04);
			}
			break;
		case 0x38:		// SEEK_INC
			break;
		case 0x39:		// SEEK_DEC
			break;
		default:
			break;
	}
}


void moduleToGps_FromSystem_Message(unsigned char *param, unsigned char len){
	unsigned char cmd = param[0];
	
	switch(cmd){
		case 0x2C:	// acc off
			break;
		case 0x2D:	// acc on
			break;
		case 0x40:
			pLocalParam->auto_gps_voice_enable = param[1];
			break;
		case 0x41:
			if(pLocalParam->auto_gps_voice_enable){
				u16 curpage = 0, curpagelen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curpage, (u8 *)&curpagelen);
				if(curpage != PAGE_GPS_PAGE){
					//setPanelKeyToAndroid(0x00);
					gpsToModule_NotifySystem_jumpPage(PAGE_GPS_PAGE);
				}
			}
			break;
		case 0x56:
			if(0x00 == param[1]){
				property_set("fly.android.navi.daynightmode","day"); 
				setPanelKeyToAndroid(0xF0);
			}
			else if(0x01 == param[1]){
				property_set("fly.android.navi.daynightmode","night"); 
				setPanelKeyToAndroid(0xF1);
			}
			break;
		default:
			break;
	}
}

void moduleToGps_FromExternalCtrl_Message(unsigned char *param, unsigned char len)
{
	if(param[0] == 0x01)
	{
		if(param[0x01])
		{
			gpsToModule_NotifySystem_jumpPage(PAGE_GPS_PAGE);
		}
		else
		{
		}
	}
}

void moduleToGps_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;
    analyseAppMessage(param+1,len-1);   
}


