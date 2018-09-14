#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "appResponseCommand.h"
#include "appResponseFunction.h"
#include "halRequestFunction.h"
#include "otherModuleRequestFunction.h"
#include "timer_interface.h"

void appInit(void){

}

void appDeInit(void){

}

void analyseAppMessage(unsigned char *buffer, unsigned char len){
	int ctrlId = 0;
	char ctrlType;
	unsigned char paramLen;
	unsigned char *param;

	ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
	ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
	ctrlId += (int)((buffer[2] << 8) & 0xFF00);
	ctrlId += (int)(buffer[3] & 0xFF);
  
	ctrlType = buffer[4];
	paramLen = len - 5;
	param = &buffer[5];
	LOGD("<<<<<++++ aux analyseAppMessage++++>>>>>ctrlId:%x ctrlType:%x",ctrlId,ctrlType);
	
	appToAUX_VideoOSDColorSet_ButtonMessageToT123ChipLocation(ctrlId,ctrlType);
	appToAUX_VideoOSD_ButtonMessageToT123ChipLocation(ctrlId,ctrlType);
	switch(ctrlId){
	    case CONTROLID_AUX_SET_VIDEO_SWITCH:
	        if(ctrlType == UIACTION_MOUSEUP)
	        {
	           appToAux_AuxSet_VideoSwitch_MouseUp();
	        }
       	    break;
		case CONTROLID_AUX_BACK:
		    if(ctrlType == UIACTION_MOUSEUP){
				DeleteTimer(AUX_OSD_TIMER_HIDDEN_DISPLAY);
				auxToModule_NotifySystem_jumpPage(PAGE_MENU);
		    }
			break;
		case CONTROLID_MENU_AUX:
			if(ctrlType == UIACTION_MOUSEUP){	
				appToAux_MenuAux_MouseUp();
			}
			break;
 		case CONTROLID_AUX_VIDEO_BACKGROUND:
			if(ctrlType == UIACTION_MOUSEUP){
				auxToModule_NotifySystem_jumpPage(PAGE_AUX_VIDEO_CONTROL);
				SetTimer(TIME_5S,1,AUX_OSD_TIMER_HIDDEN_DISPLAY);
			}
			break; 					
 		case CONTROLID_AUX_VIDEO_CONTROL_BACK:
		    if(ctrlType == UIACTION_MOUSEUP){
				pLocalParam->bEnterAux = false;
				auxToHal_MenuControl(0x80);
				DeleteTimer(AUX_OSD_TIMER_HIDDEN_DISPLAY);
				auxToModule_NotifySystem_jumpPage(PAGE_MENU);
		    }
			break;		   
 		case CONTROLID_AUX_VIDEO_CONTROL_SET:
		    if(ctrlType == UIACTION_MOUSEUP){
				auxToHal_MenuControl(0x81);
				auxToModule_NotifySystem_jumpPage(PAGE_AUX_VIDEO_SET);
				SetTimer(TIME_5S,1,AUX_OSD_TIMER_HIDDEN_DISPLAY);
		    }
			else if(ctrlType == UIACTION_MOUSEDOWN){
				auxToHal_MenuControl(0x01);
			}
			break;		   

		//--------------osd start----------------------
 		case CONTROLID_AUX_VIDEO_SET_COLOUR_DEC:
		    if(ctrlType == UIACTION_MOUSEUP){
				appToAux_VideoSet_ColorDec_MouseUp();
		    }else if(ctrlType == UIACTION_MOUSETIMER){
		    	appToAux_VideoSet_ColorDec_MouseUp();
		    }
			break;					   		   
 		case CONTROLID_AUX_VIDEO_SET_COLOUR_INC:
		    if(ctrlType == UIACTION_MOUSEUP){
				appToAux_VideoSet_ColorInc_MouseUp();
		    }else if(ctrlType == UIACTION_MOUSETIMER){
		    	appToAux_VideoSet_ColorInc_MouseUp();
		    }
			break;					   
 		case CONTROLID_AUX_VIDEO_SET_CHROMINANCE_DEC:
		    if(ctrlType == UIACTION_MOUSEUP){
				appToAux_VideoSet_ChrominanceDec_MouseUp();
		    }else if(ctrlType == UIACTION_MOUSETIMER){
		    	appToAux_VideoSet_ChrominanceDec_MouseUp();
		    }
			break;				   		   
 		case CONTROLID_AUX_VIDEO_SET_CHROMINANCE_INC:
		    if(ctrlType == UIACTION_MOUSEUP){
				appToAux_VideoSet_ChrominanceInc_MouseUp();
		    }else if(ctrlType == UIACTION_MOUSETIMER){
		    	appToAux_VideoSet_ChrominanceInc_MouseUp();
		    }
			break;				   
 		case CONTROLID_AUX_VIDEO_SET_CONTRAST_DEC:
		    if(ctrlType == UIACTION_MOUSEUP){
				appToAux_VideoSet_ContrastDec_MouseUp();
		    }else if(ctrlType == UIACTION_MOUSETIMER){
		    	appToAux_VideoSet_ContrastDec_MouseUp();
		    }
			break;				   
			   
 		case CONTROLID_AUX_VIDEO_SET_CONTRAST_INC:
		    if(ctrlType == UIACTION_MOUSEUP){
				appToAux_VideoSet_ContrastInc_MouseUp();
		    }else if(ctrlType == UIACTION_MOUSETIMER){
		    	appToAux_VideoSet_ContrastInc_MouseUp();
		    }
			break;				   
			
 		case CONTROLID_AUX_VIDEO_SET_BRIGHTNESS_DEC:
		    if(ctrlType == UIACTION_MOUSEUP){
				appToAux_VideoSet_BrightnessDec_MouseUp();
		    }else if(ctrlType == UIACTION_MOUSETIMER){
		    	appToAux_VideoSet_BrightnessDec_MouseUp();
		    }
			break;			   
 		case CONTROLID_AUX_VIDEO_SET_BRIGHTNESS_INC:
		    if(ctrlType == UIACTION_MOUSEUP){
				appToAux_VideoSet_BrightnessInc_MouseUp();
		    }else if(ctrlType == UIACTION_MOUSETIMER){
		    	appToAux_VideoSet_BrightnessInc_MouseUp();
		    }
			break;			   
		//--------------osd end----------------------	
		
 		case CONTROLID_AUX_VIDEO_SET_BACKGROUND:
		    if(ctrlType == UIACTION_MOUSEUP){
				auxToModule_NotifySystem_jumpPage(PAGE_AUX_VIDEO);	
		    }
			break;	
		case CONTROLID_AUX_VIDEO_CONTROL_BACKGROUND:
		    if(ctrlType == UIACTION_MOUSEUP){
				auxToModule_NotifySystem_jumpPage(PAGE_AUX_VIDEO);	
		    }
			break;
 		case CONTROLID_AUX_VIDEO_SET_CONTROL_BACKGROUND:
       		    if(ctrlType == UIACTION_MOUSEUP){
       				SetTimer(TIME_5S,1,AUX_OSD_TIMER_HIDDEN_DISPLAY);
       		    }
       			break;
       	default:break;
       	}
 }
