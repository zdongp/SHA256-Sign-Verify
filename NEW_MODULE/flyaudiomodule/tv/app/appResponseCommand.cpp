#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"

#include "appResponseCommand.h"
#include "appResponseFunction.h"
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
	
	LOGD("<<<<<<<<<<<TV analyseAppMessage>>>>>>>>++++ctrlId:0X%x ctrlType:%x",ctrlId,ctrlType);

	appToTV_VideoOSD_ButtonMessageToT123ChipLocation(ctrlId,ctrlType);
	appToTV_VideoOSDColorSet_ButtonMessageToT123ChipLocation(ctrlId,ctrlType);
	
	switch(ctrlId){
		//case CONTROLID_TV_NO_SIGN://\u65e0\u7535\u89c6\u6807\u5fd7\uff0c\u4e0d\u7528\u5904\u7406
		case CONTROLID_TV_NO_VIDEO_BACK://\u65e0\u7535\u89c6\u6a21\u5757 \u8fd4\u56de
		case CONTROLID_MENU_TV://\u4e3b\u9875\u9762\u8df3\u5230TV	
		case CONTROLID_TV_VIDEO_BACKGROUND://\u89c6\u9891\u9875\u80cc\u666f\uff0c\u8981\u8df3\u51fa\u63a7\u5236\u9875	
		case CONTROLID_TV_VIDEO_CONTROL_BACK://\u8fd4\u56de\u4e3b\u83dc\u5355
		case CONTROLID_TV_VIDEO_CONTROL_SET://\u8fdb\u5165\u8bbe\u7f6e\u9875
		case CONTROLID_TV_VIDEO_CONTROL_BACKGROUND:
        	if(ctrlType == UIACTION_MOUSEUP){
				appToTV_JumpPage_MouseUp(ctrlId);
			}
		       break;	
			   
		case CONTROLID_TV_VIDEO_CONTROL_SCAN:// 
		
		case CONTROLID_TV_VIDEO_CONTROL_LEFT://		  0x080110 
		case CONTROLID_TV_VIDEO_CONTROL_RIGHT://	  0x080111 
		case CONTROLID_TV_VIDEO_CONTROL_UP://		  0x080112 
		case CONTROLID_TV_VIDEO_CONTROL_DOWN://		  0x080113 
		case CONTROLID_TV_VIDEO_CONTROL_OK://		  0x080114 
              
		case CONTROLID_TV_VIDEO_CONTROL_MENU://		  0x080120 
		case CONTROLID_TV_VIDEO_CONTROL_SHOW://		  0x080121 
		case CONTROLID_TV_VIDEO_CONTROL_PREV://		  0x080122 
		case CONTROLID_TV_VIDEO_CONTROL_NEXT://		  0x080123 
		case CONTROLID_TV_VIDEO_CONTROL_STOP_BACK://	  0x080124 
             if(ctrlType == UIACTION_MOUSEUP){
				appToTV_CtrlMenu_MouseUp(ctrlId);
			}			 
		       break;
	//------------------------------------OSD start-----------------------
		case CONTROLID_TV_VIDEO_SET_COLOUR_DEC://	  0x080200 
			if(ctrlType == UIACTION_MOUSEUP){
				appToTV_VideoSet_MouseUp(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToTV_VideoSet_MouseUp(ctrlId);	
			}	
			break;
		case CONTROLID_TV_VIDEO_SET_COLOUR_GAUGE://	  0x080201 
			break;
		case CONTROLID_TV_VIDEO_SET_COLOUR_INC://	  0x080202 
			if(ctrlType == UIACTION_MOUSEUP){
				appToTV_VideoSet_MouseUp(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToTV_VideoSet_MouseUp(ctrlId);	
			}	
			break;
			
		case CONTROLID_TV_VIDEO_SET_CHROMINANCE_DEC://    0x080210 
			if(ctrlType == UIACTION_MOUSEUP){
				appToTV_VideoSet_MouseUp(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToTV_VideoSet_MouseUp(ctrlId);	
			}	
			break;
		case CONTROLID_TV_VIDEO_SET_CHROMINANCE_GAUGE://  0x080211 
			break;
		case CONTROLID_TV_VIDEO_SET_CHROMINANCE_INC://	  0x080212 
			if(ctrlType == UIACTION_MOUSEUP){
				appToTV_VideoSet_MouseUp(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToTV_VideoSet_MouseUp(ctrlId);	
			}	
			break;
			
		case CONTROLID_TV_VIDEO_SET_CONTRAST_DEC://       0x080220 
			if(ctrlType == UIACTION_MOUSEUP){
				appToTV_VideoSet_MouseUp(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToTV_VideoSet_MouseUp(ctrlId);	
			}	
			break;
		case CONTROLID_TV_VIDEO_SET_CONTRAST_GAUGE://     0x080221 
		    break;
		case CONTROLID_TV_VIDEO_SET_CONTRAST_INC://       0x080222 
			if(ctrlType == UIACTION_MOUSEUP){
				appToTV_VideoSet_MouseUp(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToTV_VideoSet_MouseUp(ctrlId);	
			}	
			break;
			
		case CONTROLID_TV_VIDEO_SET_BRIGHTNESS_DEC://     0x080230 
			if(ctrlType == UIACTION_MOUSEUP){
				appToTV_VideoSet_MouseUp(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToTV_VideoSet_MouseUp(ctrlId);	
			}	
			break;
		case CONTROLID_TV_VIDEO_SET_BRIGHTNESS_GAUGE://	  0x080231 
		    break;
		case CONTROLID_TV_VIDEO_SET_BRIGHTNESS_INC://	  0x080232 
			if(ctrlType == UIACTION_MOUSEUP){
				appToTV_VideoSet_MouseUp(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToTV_VideoSet_MouseUp(ctrlId);	
			}
			break;
	//-----------------------OSD end---------------------
		case CONTROLID_TV_VIDEO_SET_BACKGROUND://0x080200 
	        case CONTROLID_TV_VIDEO_SET_CONTROL_BACKGROUND://0x080201 
                	if(ctrlType == UIACTION_MOUSEUP){
				appToTV_JumpPage_MouseUp(ctrlId);
			}
			break;
		default:break;
	}
}

