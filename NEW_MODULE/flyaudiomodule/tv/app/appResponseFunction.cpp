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
#include "timer_interface.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"



//控制页的弹起事件
void appToTV_CtrlMenu_MouseUp(u32 nFuncID){

	LOGD("appToTV_CtrlMenu_MouseUp+++++nFuncID: %x", nFuncID);
	
    u8 nKeyCtrlValue = 0x00;
	
    switch(nFuncID){
	    	case CONTROLID_TV_VIDEO_CONTROL_SCAN: //搜索
		     nKeyCtrlValue = Key_AUTO;
		     break;
		case CONTROLID_TV_VIDEO_CONTROL_LEFT: //0x080110 
		     nKeyCtrlValue = Key_VOL_DEC_LEFT;//
		     SetTimer(TIME_5S,0,TV_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
		     break;	      
		case CONTROLID_TV_VIDEO_CONTROL_RIGHT://0x080111
		     nKeyCtrlValue = Key_VOL_INC_RIGHT;
			 SetTimer(TIME_5S,0,TV_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
		     break;
		case CONTROLID_TV_VIDEO_CONTROL_UP://0x080112
		     nKeyCtrlValue = Key_CH_INC_UP;
			 SetTimer(TIME_5S,0,TV_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
		     break;
		case CONTROLID_TV_VIDEO_CONTROL_DOWN://0x080113
             nKeyCtrlValue = Key_CH_DEC_DOWN;
			 SetTimer(TIME_5S,0,TV_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
		     break;
		case CONTROLID_TV_VIDEO_CONTROL_OK://0x080114
             nKeyCtrlValue = Key_OK;
		     break;
		case CONTROLID_TV_VIDEO_CONTROL_MENU://	
		     nKeyCtrlValue = Key_MENU;
		     break;
		case CONTROLID_TV_VIDEO_CONTROL_SHOW://列表
	         nKeyCtrlValue = Key_EPG;
	         break;	     
		case CONTROLID_TV_VIDEO_CONTROL_PREV://	0x080122
		     nKeyCtrlValue = Key_CH_DEC_DOWN;
			 SetTimer(TIME_5S,0,TV_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
		     break;
		case CONTROLID_TV_VIDEO_CONTROL_NEXT://	0x080123 
			 nKeyCtrlValue = Key_CH_INC_UP;
			 SetTimer(TIME_5S,0,TV_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
		     break;
		case CONTROLID_TV_VIDEO_CONTROL_STOP_BACK://
             nKeyCtrlValue = Key_EXIT;
		     break;
    }
    if(0 != nKeyCtrlValue)
    tvToHal_KeyCtrl(nKeyCtrlValue); 
}

//视频设置的弹起事件
void appToTV_VideoSet_MouseUp(u32 nFuncID){
       u32 mapFuncIDAndCmd[][2] = {
	      {CONTROLID_TV_VIDEO_SET_COLOUR_DEC,0x02},//饱和度 0x080200
	      {CONTROLID_TV_VIDEO_SET_COLOUR_INC,0x01},//0x080201
	      {CONTROLID_TV_VIDEO_SET_CHROMINANCE_DEC,0x04},//色调 0x080210
	      {CONTROLID_TV_VIDEO_SET_CHROMINANCE_INC,0x03},//0x080212 
	      {CONTROLID_TV_VIDEO_SET_CONTRAST_DEC,0x06},//对比度 0x080220
	      {CONTROLID_TV_VIDEO_SET_CONTRAST_INC,0x05},//0x080222 
	      {CONTROLID_TV_VIDEO_SET_BRIGHTNESS_DEC,0x08},//高度 0x080230
	      {CONTROLID_TV_VIDEO_SET_BRIGHTNESS_INC,0x07}//0x080232 
      }; 
      int i = 0;
      for(i=0;i<sizeof(mapFuncIDAndCmd)/sizeof(u32)/2;i++)
	      if(nFuncID == mapFuncIDAndCmd[i][0]){		  	
		      //tvToHal_VideoSetting(mapFuncIDAndCmd[i][1]);
			  u8 buf[] = {0x11, 0x00};
			  buf[1] = mapFuncIDAndCmd[i][1];
			  makeAndSendMessageToModule(MODULE_ID_TV,MODULE_ID_AUDIOVIDEO,buf,2);  
	          SetTimer(TIME_5S,0,TV_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
		      break;
	      }
     	        
}

//跳页弹起事件
void appToTV_JumpPage_MouseUp(u32 nFuncID){

	switch(nFuncID){//nFuncID is ctrlId
     	case CONTROLID_TV_NO_VIDEO_BACK://无电视模块 返回
             tvToModule_NotifySystem_JumpPage(PAGE_MENU);
	     break;
		case CONTROLID_MENU_TV:
		{//主页面跳到TV
	 
			LOGD("xxxxxxpLocalParam->nIsBrakeState = %x",pLocalParam->nIsBrakeState);
			LOGD("xxxxxxxpLocalParam->nIsTVModuleExite = %x", pLocalParam->nIsTVModuleExite);
			LOGD("xxxxxxxpLocalParam->nIsTVDriverInit = %x", pLocalParam->nIsTVDriverInit);

			if(0 == pLocalParam->nIsBrakeState) //System传来的状态，不可进入视频	  back car
				 return;
				 
			
            if(0 == pLocalParam->nIsTVModuleExite || 0 ==  pLocalParam->nIsTVDriverInit) 
            {
			    tvToModule_NotifySystem_JumpPage(PAGE_TV_NO_VIDEO);//无电视提示页
				return;
	        }

	
			u8 u_IsDVRstate = 0;
			u8 u_IsDVRstatelen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_IS_DVRORTV, (u8*)&u_IsDVRstate, &u_IsDVRstatelen);
			LOGD("xxxxxx u_IsDVRstate = %x",u_IsDVRstate);
			if(u_IsDVRstate == 1)
				tvToModule_NotifySystem_JumpPage(PAGE_TV_VIDEO);
			else
				tvToModule_NotifySystem_JumpPage(PAGE_TV_NO_VIDEO);
		}
		    break;		
		case CONTROLID_TV_VIDEO_BACKGROUND://视频页背景，要跳到控制页 0x080000
	    	 tvToModule_NotifySystem_JumpPage(PAGE_TV_VIDEO_CONTROL);
			 SetTimer(TIME_5S,0,TV_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
		     break;	
	    case CONTROLID_TV_VIDEO_CONTROL_BACKGROUND://0x080140
			 tvToModule_NotifySystem_JumpPage(PAGE_TV_VIDEO);
			 break;
		case CONTROLID_TV_VIDEO_CONTROL_BACK://返回主菜单
			 DeleteTimer(TV_OSD_TIMER_HIDDEN_DISPLAY);
	         tvToModule_NotifySystem_JumpPage(PAGE_MENU);
	         break;
		case CONTROLID_TV_VIDEO_CONTROL_SET://进入设置页 0x08101
	         tvToModule_NotifySystem_JumpPage(PAGE_TV_VIDEO_SET);
		     break;	 
		case CONTROLID_TV_VIDEO_SET_BACKGROUND://0x080240 
	         tvToModule_NotifySystem_JumpPage(PAGE_TV_VIDEO);
		     break;
	    case CONTROLID_TV_VIDEO_SET_CONTROL_BACKGROUND://0x080241 
	         break;
     }
}

void appToTV_VideoOSD_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType)
{
        u8 swtich_button=0;
        u8 button_status=0xff;
    
        switch(ctrlId){  
            case CONTROLID_TV_VIDEO_CONTROL_SCAN:
            swtich_button=0x01;
            break;
            case CONTROLID_TV_VIDEO_CONTROL_MENU:
            swtich_button=0x02;
            break;
            case CONTROLID_TV_VIDEO_CONTROL_SET:
            swtich_button=0x03;
            break;
            case CONTROLID_TV_VIDEO_CONTROL_BACK:
            swtich_button=0x04;
            break;
    		case CONTROLID_TV_VIDEO_CONTROL_UP:
    		swtich_button=0x05;
    		break;
    		case CONTROLID_TV_VIDEO_CONTROL_LEFT: 
    		swtich_button=0x06;
    		break;
    		case CONTROLID_TV_VIDEO_CONTROL_OK:
    		swtich_button=0x07;
    		break;
    		case CONTROLID_TV_VIDEO_CONTROL_RIGHT:
    		swtich_button=0x08;
    		break;
    		case CONTROLID_TV_VIDEO_CONTROL_DOWN:
    		swtich_button=0x09;
    		break;
    		case CONTROLID_TV_VIDEO_CONTROL_SHOW:
    		swtich_button=0x0A;
    		break;
    		case CONTROLID_TV_VIDEO_CONTROL_PREV:
    		swtich_button=0x0B;
    		break;
    		case CONTROLID_TV_VIDEO_CONTROL_NEXT:
    		swtich_button=0x0C;
    		break;
    		case CONTROLID_TV_VIDEO_CONTROL_STOP_BACK:
    		swtich_button=0x0D;
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

        tvToModule_NotifyOSD_aboutT123_VideoOSD_Button(swtich_button,button_status);
}

void appToTV_VideoOSDColorSet_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType)
{
        u8 swtich_button=0;
        u8 button_status=0xff;
        u8 value=0xff;
        u8 setOptions=0xff;

		switch(ctrlId)
        {
        	case CONTROLID_TV_VIDEO_SET_COLOUR_DEC:
            	swtich_button=0x01;
    			break;
    		case CONTROLID_TV_VIDEO_SET_COLOUR_INC:
    		    swtich_button=0x02;
    			break;
    	    case CONTROLID_TV_VIDEO_SET_BRIGHTNESS_DEC:
    	        swtich_button=0x03;
    			break;
    		case CONTROLID_TV_VIDEO_SET_BRIGHTNESS_INC:
    		    swtich_button=0x04;
    			break;
    		case CONTROLID_TV_VIDEO_SET_CHROMINANCE_DEC:
    		    swtich_button=0x05;
    			break;
    		case CONTROLID_TV_VIDEO_SET_CHROMINANCE_INC:	
    		    swtich_button=0x06;
    			break;	
    		case CONTROLID_TV_VIDEO_SET_CONTRAST_DEC:	
    		    swtich_button=0x07;
    			break;
    		case CONTROLID_TV_VIDEO_SET_CONTRAST_INC:
    		    swtich_button=0x02;
    			break;
			default:
				return;
				break;
        }
			   
		if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
		{
            switch(ctrlId)
            {
            	case CONTROLID_TV_VIDEO_SET_COLOUR_DEC:
                    setOptions=0x42;
        			break;
        		case CONTROLID_TV_VIDEO_SET_COLOUR_INC:
                    setOptions=0x42;
        			break;
        	    case CONTROLID_TV_VIDEO_SET_BRIGHTNESS_DEC:
                    setOptions=0x43;
        			break;
        		case CONTROLID_TV_VIDEO_SET_BRIGHTNESS_INC:
                    setOptions=0x43;
        			break;
        		case CONTROLID_TV_VIDEO_SET_CHROMINANCE_DEC:
                    setOptions=0x44;
        			break;
        		case CONTROLID_TV_VIDEO_SET_CHROMINANCE_INC:
                    setOptions=0x44;
        			break;	
        		case CONTROLID_TV_VIDEO_SET_CONTRAST_DEC:
                    setOptions=0x45;
        			break;
        		case CONTROLID_TV_VIDEO_SET_CONTRAST_INC:
                    setOptions=0x45;
        			break;
    			default:
    				return;
    				break;
            	}
    	
    		   //tvToModule_NotifyOSD_aboutT123_colorSet_Value(setOptions,value);
		}
		
        if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
        {
    	   button_status=0x00;
	    }
	    else
	    {
	       button_status=0x01;
	    }
        
	    tvToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(swtich_button,button_status);
	   
}

