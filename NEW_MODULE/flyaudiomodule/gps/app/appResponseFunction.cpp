#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleRequestCommand.h"

void appToGPS_Parameter(unsigned char *param, unsigned char paramLen){
	switch(param[0]){
		default:
			break;
	}
}

void appToGPS_MenuGPS_MouseUp()
{
	gpsToModule_NotifySystem_jumpPage(PAGE_GPS_PAGE);
}

void appToGPS_Navi_DedicateInformation(u8 *param,u8 paramLen)
{
	for(int i=0;i<paramLen;i++)
	{
		LOGD("(%d)%d",i,param[i]);
	}
	
	switch(param[0])
	{
	    case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x08:
        case 0x09:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x20:
        case 0x88:
        case 0x89:
            gpsToModule_NotifyAuxscreen_NaviInformation(param,paramLen);
        break; 
	    case 0x30:
	        gpsToModule_NotifyBT_aboutPTT(param,paramLen);
	    break;
	    case 0xE0:
		{
		    pLocalParam->m_nLanguageId = (param[1] & 0xFF);
		    LOGD("[%s] language id = [%d]", __FUNCTION__,   pLocalParam->m_nLanguageId);
			
		    gpsToModule_NotifyOSD_aboutSwitchingLanguage(param[0],param[1]);
		    gpsToModule_NotifyBT_aboutSwitchingLanguage(param[0],param[1]);
			gpsToModule_NotifyExtcar_aboutSwitchingLanguage(param[1]);
	    }
	    break;
	    default:break;
	}
}


void appToGPS_Navi_GaodeMap_Information(u8 *param,u8 paramLen)
{
	LOGD("[%s] param[0]=%x",__FUNCTION__,param[0]);
	switch(param[0])
	{
	    case 0x00:
		case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x08:
        case 0x09:
		case 0x0a:
        case 0x0b:
        case 0x0c:
        case 0x0d:
        case 0x0e:
        case 0x0f:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
	case 0x18:
        case 0x19:
	case 0x21:
	case 0x22:
        case 0x88:
        case 0x89:
            gpsToModule_NotifyAuxscreen_GaodeMap_Information(param,paramLen);
        break; 
	    case 0x30:
	        gpsToModule_NotifyBT_aboutPTT(param,paramLen);
	    break;
	    case 0xE0:
		{
		    pLocalParam->m_nLanguageId = (param[1] & 0xFF);
		    LOGD("[%s] language id = [%d]", __FUNCTION__,   pLocalParam->m_nLanguageId);
			
		    gpsToModule_NotifyOSD_aboutSwitchingLanguage(param[0],param[1]);
		    gpsToModule_NotifyBT_aboutSwitchingLanguage(param[0],param[1]);
			gpsToModule_NotifyExtcar_aboutSwitchingLanguage(param[1]);
	    }
	    break;
	    default:break;
	}
}




