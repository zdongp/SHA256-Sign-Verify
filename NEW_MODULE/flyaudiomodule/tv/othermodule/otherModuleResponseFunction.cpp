#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "otherModuleResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "param.h"
#include "pageID.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "moduleParamRequest.h"
#include "moduleParamResponse.h"
#include "appRequestCommand.h"
#include "moduleParamStruct.h"
#include "appResponseFunction.h"

 
 //来自systemmodule的消息
 void moduleToTV_FromSystem_Message(u8* param,int len){
 
 	u8 uCmd = param[0];//命令
 	
 	LOGD("moduleToTV_FromSystem_Message++++++uCmd:%x", param[0]);
	
 	switch(uCmd){
 		case 0x09://刹车状态
                  moduleToTV_FromSystem_BrakeState(param[1]);
 		 break;
 		case 0x0E://是否有电视盒
                  moduleToTV_FromSystem_TVModuleExited(param[1]);
 		 break;
 		case 0x10://复位
                  moduleToTV_FromSystem_PrepareToShupDown();
 		 break;
        case 0x14://恢复出厂设置
                 moduleToTV_FromSystem_ResetToDefaultSetting();
		 break;
		case 0x30://ACC OFF
                 moduleToTV_FromSystem_ACCOn();
		 break;
		case 0x31://ACC On
                 moduleToTV_FromSystem_ACCOff();
        break;
        case 0x2C:
        		halToSystem_Galaxy_AccOn();
		break;
        case 0x2D:
        		halToSystem_Galaxy_AccOff();
		break;
		case 0x79:
				moduleToTV_FromSystem_Navil();
		 break;
	}
}

void moduleToTV_FromSystem_Navil(){
	u16 CurPageId = 0;        
 	u8 curPageIdLen = 0;
 	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageId,(u8*)&curPageIdLen);
 	if(CurPageId == PAGE_TV_VIDEO_CONTROL || CurPageId == PAGE_TV_VIDEO_SET){
 	tvToModule_NotifySystem_JumpPage(PAGE_TV_VIDEO);
 	}
}

//来自keymodule的消息
void moduleToTV_FromKey_Message(u8* param, int len){
    u8 uCmd = param[1];//命令 keyvalue
    LOGD("moduleToTV_FromKey_Message______________uCmd:0x%x", uCmd);
		
	switch(uCmd){
    case 0x02://MENU
		moduleToTV_FromKey_Menu();
		break;
	case 0x03://AV 切到Mp3
		moudleToTV_FromKey_AV();
		break;
	case 0x38://SEEK_INC
	case 0x3b://TUNE_INC
		moduleToTV_FromKey_TuneSeek(0);
		break;
	case 0x39://SEEK_DEC
	case 0x3c://TUNE_DEC
		moduleToTV_FromKey_TuneSeek(1);
		break;
	}
}

//刹车状态
void moduleToTV_FromSystem_BrakeState(u8 nBrakeState){

	LOGD("moduleToTV_FromSystem_BrakeState+++++++nBrakeState: %x", nBrakeState);
	
    if(nBrakeState == 0x01){
	  pLocalParam->nIsBrakeState = 1;
	  
    }else {
         pLocalParam->nIsBrakeState = 0;
	 	 u16 CurPageId = 0;        
		 u8 curPageIdLen = 0;
		 getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageId,(u8*)&curPageIdLen);
		 if(CurPageId == PAGE_TV_VIDEO  || CurPageId == PAGE_TV_VIDEO_CONTROL || CurPageId == PAGE_TV_VIDEO_SET || CurPageId == PAGE_TV_NO_VIDEO){
		 	tvToModule_NotifySystem_JumpPage(PAGE_MENU);
		 }
    }
}

//是否有电视盒
void moduleToTV_FromSystem_TVModuleExited(u8 nExited){

	 LOGD("moduleToTV_FromSystem_TVModuleExited+++++++nIsTVModuleExite+++nExited: %d ", nExited);
	 u16 CurPageId = 0;        
	 u8 curPageIdLen = 0;
	 getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageId,(u8*)&curPageIdLen);
     if(0 == nExited){	 	
         	pLocalParam->nIsTVModuleExite = 0;
		 	if(CurPageId == PAGE_TV_VIDEO  || CurPageId == PAGE_TV_VIDEO_CONTROL || CurPageId == PAGE_TV_VIDEO_SET){
		 		tvToModule_NotifySystem_JumpPage(PAGE_TV_NO_VIDEO);
		 	}
     }
     else{
	  	pLocalParam->nIsTVModuleExite = 1;

	  	unsigned short curSound = 0;
		unsigned char curSoundLen = 2;
		getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8 *)&curSound, (u8 *)&curSoundLen);
		if (curSound == CHANNEL_TV_CTRL || curSound == CHANNEL_TV_VIDEO){
			if(CurPageId == PAGE_TV_NO_VIDEO  || CurPageId == PAGE_TV_VIDEO_CONTROL || CurPageId == PAGE_TV_VIDEO_SET)
				tvToModule_NotifySystem_JumpPage(PAGE_TV_VIDEO);
		}
			
	  	setDigitalData(CONTROLID_MENU_TV,0);
     }

}

//准备关机
void moduleToTV_FromSystem_PrepareToShupDown(){
    saveParameter(); 
}

//恢复出厂设置
void moduleToTV_FromSystem_ResetToDefaultSetting(){
    setDefaultParam();
    saveParameter(); 
}

void moduleToTV_FromSystem_ACCOn(){
}

void moduleToTV_FromSystem_ACCOff(){
}

void halToSystem_Galaxy_AccOn()
{
}
void halToSystem_Galaxy_AccOff()
{
}

void moudleToTV_FromKey_AV(){
	
    u16 nPageID = 0;
    u8 nPageIDLen = 0;
    getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&nPageID,(u8*)&nPageIDLen);
	
    switch(nPageID){//在TV模块下的页
	    case PAGE_TV_VIDEO:
	    case PAGE_TV_VIDEO_CONTROL:
	    case PAGE_TV_VIDEO_SET:
	    case PAGE_TV_NO_VIDEO:
                    tvToModule_NotifySystem_SwitchToModule(MODULE_ID_TV);
		    break;
	    default:
                    tvToModule_NotifySystem_JumpPage(PAGE_TV_VIDEO);
		    break;
    }
}

void moduleToTV_FromKey_Menu(){
   tvToModule_NotifySystem_JumpPage(PAGE_MENU);
}

void moduleToTV_FromKey_TuneSeek(u8 nFlag){
     if(1 == nFlag)
      tvToHal_KeyCtrl(Key_CH_DEC_DOWN);
     else
      tvToHal_KeyCtrl(Key_CH_INC_UP); 

     //不在TV页，要跳回到TV视频页
     u16 nPageID = 0;
     unsigned char nPageIDLen = 0;
     getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8 *)&nPageID, (u8 *)&nPageIDLen);
     switch(nPageID){
        case PAGE_TV_VIDEO:
	    case PAGE_TV_VIDEO_CONTROL:
	    case PAGE_TV_VIDEO_SET:
	    case PAGE_TV_NO_VIDEO:
		    break;//已经在TV页，则不用处理
	    default://不在TV页，要跳到TV页
                 tvToModule_NotifySystem_JumpPage(PAGE_TV_VIDEO);
		    break;
     }
}

void moduleToTV_FromAudiovideo_GetOsdVideoSetting(unsigned char type, unsigned char value){
	switch(type){
		case 0x00:
			setAnalogData(CONTROLID_TV_VIDEO_SET_COLOUR_GAUGE, value);
			break;
		case 0x01:
			setAnalogData(CONTROLID_TV_VIDEO_SET_CHROMINANCE_GAUGE, value);
			break;
		case 0x02:
			setAnalogData(CONTROLID_TV_VIDEO_SET_CONTRAST_GAUGE, value);
			break;
		case 0x03:
			setAnalogData(CONTROLID_TV_VIDEO_SET_BRIGHTNESS_GAUGE, value);
			break;
		default:
			break;
	}
}

void moduleToTV_FromAudiovideo_Message(unsigned char *param, unsigned char len){
	switch(param[0]){//  get the audiovideo mode
		case 0x11:
			moduleToTV_FromAudiovideo_GetOsdVideoSetting(param[1], param[2]);
			break;
		default:
			break;
	}
	
}

void moduleToTV_FromExternalCtrl_Message(unsigned char *param, unsigned char len)
{
	if(param[0]==0x01)
	{
		if(param[1]==0x01)
		{
			 appToTV_JumpPage_MouseUp(CONTROLID_MENU_TV);
		}
		else
		{
		}
	}
}


void moduleToTv_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;
    analyseAppMessage(param+1,len-1);   
}





