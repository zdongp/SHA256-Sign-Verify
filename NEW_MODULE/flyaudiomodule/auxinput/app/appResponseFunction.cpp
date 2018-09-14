#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "appResponseCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "timer_interface.h"
#include "otherModuleRequestCommand.h"
#include "moduleParamRequest.h"

void System_notifyApp_DisplayBrakecarPromtBox(u8 u8_Param)
{
	LOGD("[%s] u8_Param:%d",__FUNCTION__,u8_Param);
	u8 buf[] = {0x47, u8_Param};
	setCommand(0x00000000, buf, 2);
}

void appToAux_AuxSet_VideoSwitch_MouseUp()
{
    LOGD("pLocalParam->uAUX_VideoSwitch:%d",pLocalParam->uAUX_VideoSwitch);

    if(pLocalParam->bBrakeState == false) //System传来的状态，不可进入视频 false
    {
        System_notifyApp_DisplayBrakecarPromtBox(1);
		return;
	}
    /*if(pLocalParam->uAUX_VideoSwitch==0)//调试用
    {
        pLocalParam->uAUX_VideoSwitch=1;
        setDigitalData(CONTROLID_AUX_SET_VIDEO_SWITCH, true);
        auxToModule_NotifySystem_jumpPage(PAGE_AUX_VIDEO);
        
    }
    else if(pLocalParam->uAUX_VideoSwitch==1)
    {
        pLocalParam->uAUX_VideoSwitch=0;
        setDigitalData(CONTROLID_AUX_SET_VIDEO_SWITCH, false);
        auxToModule_NotifySystem_jumpPage(PAGE_AUX_VIDEO);
    }*/
    
    auxToModule_NotifySystem_jumpPage(PAGE_AUX_VIDEO);
}

void auxToApp_SetAUXVideo_Checking_Prompt_box(bool state)
{
	LOGD("***********1 %x",state);
	
	setVisible(CONTROLID_AUX_CHECKING_BACKGROUND, state);
	setVisible(CONTROLID_AUX_CHECKING_TEXT1, state);
	setVisible(CONTROLID_AUX_CHECKING_TEXT2, state);
}

void auxToApp_SetAUX_NoSignal_Prompt_box(bool state)
{
	LOGD("***********2 %x",state);
	
	setVisible(CONTROLID_AUX_NO_SIGNAL_BACKGROUND,state);
	setVisible(CONTROLID_AUX_NO_SIGNAL_TEXT1,state);
	setVisible(CONTROLID_AUX_NO_SIGNAL_TEXT2,state);
}

void appToAux_MenuAux_MouseUp(void){
		
	//if(pLocalParam->bBrakeState == false) //System传来的状态，不可进入视频 false
	//{
	//    System_notifyApp_DisplayBrakecarPromtBox(1);
	//	return;
	//}
	
	pLocalParam->bEnterAux = true;
	auxToModule_NotifySystem_jumpPage(PAGE_AUX);
	//auxToHal_QueryVideo();
	
}



void appToAUX_VideoOSD_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType)
{
    u8 swtich_button=0;
     u8 button_status=0xff;
     
      switch(ctrlId){  
          case CONTROLID_AUX_VIDEO_CONTROL_BACK:
          swtich_button=0x02;
          break;         
          case CONTROLID_AUX_VIDEO_CONTROL_SET:
          swtich_button=0x01;
          break;  
          default:
		  	return;
		  	break;
       }
     
        if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
        {
            button_status=0x00;
        }
        else
        {
            button_status=0x01;
        }
       auxToModule_NotifyOSD_aboutT123_VideoOSD_Button(swtich_button,button_status);

}


void appToAUX_VideoOSDColorSet_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType)
{   
        u8 swtich_button=0;
        u8 button_status=0xff;
        u8 value=0xff;
        u8 setOptions=0xff;

		switch(ctrlId)
        {
            case CONTROLID_AUX_VIDEO_SET_COLOUR_DEC:
                swtich_button=0x01;
                break;                             
            case CONTROLID_AUX_VIDEO_SET_COLOUR_INC:
                swtich_button=0x02;
                break; 
            case CONTROLID_AUX_VIDEO_SET_BRIGHTNESS_DEC:
                swtich_button=0x03;
                break;             
            case CONTROLID_AUX_VIDEO_SET_BRIGHTNESS_INC:
                swtich_button=0x04;
                break; 
            case CONTROLID_AUX_VIDEO_SET_CHROMINANCE_DEC:
                swtich_button=0x05;
                break;                         
            case CONTROLID_AUX_VIDEO_SET_CHROMINANCE_INC:
                swtich_button=0x06;
                break;                 
            case CONTROLID_AUX_VIDEO_SET_CONTRAST_DEC:
                swtich_button=0x07;
                break;  
            case CONTROLID_AUX_VIDEO_SET_CONTRAST_INC:
                swtich_button=0x08;
                break;
			default:
				return;
				break;
          }
				
		if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
		{
    		switch(ctrlId)
            {
                case CONTROLID_AUX_VIDEO_SET_COLOUR_DEC:
                    setOptions=0x32;
                    break;                             
                case CONTROLID_AUX_VIDEO_SET_COLOUR_INC:
                    setOptions=0x32;
                    break; 
                case CONTROLID_AUX_VIDEO_SET_BRIGHTNESS_DEC:
                    setOptions=0x33;
                    break;             
                case CONTROLID_AUX_VIDEO_SET_BRIGHTNESS_INC:
                    setOptions=0x33;
                    break; 
                case CONTROLID_AUX_VIDEO_SET_CHROMINANCE_DEC:
                    setOptions=0x34;
                    break;                         
                case CONTROLID_AUX_VIDEO_SET_CHROMINANCE_INC:
                    setOptions=0x34;
                    break;                 
                case CONTROLID_AUX_VIDEO_SET_CONTRAST_DEC:
                    setOptions=0x35;
                    break;  
                case CONTROLID_AUX_VIDEO_SET_CONTRAST_INC:
                    setOptions=0x35;
                    break;
    			default:
    				return;
    				break;
              }
    		
    		  //auxToModule_NotifyOSD_aboutT123_colorSet_Value(setOptions,value);
		}
		
        if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
        {
    	    button_status=0x00;
	    }
	    else
	    {
	        button_status=0x01;
	    }
	    auxToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(swtich_button,button_status);

}

