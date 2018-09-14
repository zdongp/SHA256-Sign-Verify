#include <stdio.h>
#include <stdlib.h>
#include "param.h"
#include "global.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"
#include "appRequestCommand.h"
#include "halRequestFunction.h"

void otherModuleInit(void){

}

void otherModuleDeInit(void){

}


/*
  OSD不用区分是哪个某块发送过来的消息,处理好下面三类消息

  *跳页通知
  *设置UI属性
  *下拉OSD请求
*/
void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len)
{
        LOGD("Module_osd [%s] sendModuleId:%x,param[0]:%x,param[1]:%x ,param[2]:%x",__FUNCTION__,sendModuleId,param[0],param[1],param[2]);

        u8 cmd = param[0];
        if(param[0]==0x16 && sendModuleId==MODULE_ID_EXTERNALCTRL)
        {
        	pLocalParam->bOnSystemPage=param[1];
        	LOGD("pLocalParam->bOnSystemPage =%d",pLocalParam->bOnSystemPage);
        }
        switch(cmd)
        {
        case 0xE3://跳页通知
        	if(sendModuleId == MODULE_ID_SYSTEM)
        	{
        		int iLeavePage = param[1]  + (param[2]<<8);
				int iEnterPage = param[3]  + (param[4]<<8);
				int iParam =param[5];
				Get_PageChangeMessage(iLeavePage,iEnterPage,iParam);
        	}
			break;
        case 0x01://显示隐藏 OSD请求
           {
        	   LOGD("[%s] param[1]:%x,From module:%x",__FUNCTION__,param[1],sendModuleId);
        	   if(sendModuleId == MODULE_ID_SYSTEM && param[1]== 0x10) return;
               if(pLocalParam->bOnSystemPage)return;
        	   Get_DropDownOsdMessage(param[1]);
           }
           break;

        case 0x40:  //0x40 Low battery value from system module be sent always
        {
        	if(sendModuleId == MODULE_ID_TV)
        		 Get_SetOSDUIValue(param,len);
        }
        	break;
        case 0x04:
        	break;
       case 0x0F:
        {
        	if(sendModuleId == MODULE_ID_CENTER && param[1]== 0x00){

                 if(pLocalParam->m_nCurOSDContent != OSD_BACK)
                 {
                	 ShowHideOSD(pLocalParam->m_nCurOSDContent,false);
                 }
        		 
        		 setOsdHidden();
        	}
        }
        break;
        case 0x27:
            {
            	if(sendModuleId == MODULE_ID_SYSTEM){
            		pLocalParam->m_haveRadar = param[1];
            		if(pLocalParam->m_nCurOSDContent==OSD_BACK)
            			Set_DisplayOSDPage(OSDPAGE_BACK_RADAR_CAR);
            	}
            }
        	break;
        case (char)0xFF://turn on 0r off
        	{
        		if(sendModuleId == MODULE_ID_SYSTEM)
       			    pLocalParam->osddebuginfo_switch = 1;
        	}
        		break;
       	case (char)0xFE://msg
       		{
       		     if(sendModuleId == MODULE_ID_SYSTEM){
        	          LOGI("OSD DEBUG INFO:%s",&param[1]);
        	          sendOsdDebugInfo(&param[1], len-1);
       		     }
       		}
        	break;
        case 0x00:
            {
                if(sendModuleId == MODULE_ID_GPS)
                {
                    LOGD("LanguageToT123:%x %x",param[1],param[2]);
                    pLocalParam->nLanguageType = param[2];
                    Get_SetOSDUIValue(&param[1],len-1);
                }
            }
            break;
        default:
             Get_SetOSDUIValue(param,len);
           break;
        }

	//设置UI属性



//    LOGD("OSD----------------->>>>>>>>>>%d %d %d",sendModuleId,param[0],param[1]);
//	switch(sendModuleId){
//
//		case MODULE_ID_MEDIA: // jing 2013-8-2 mp3 osd
//			moduleToOsd_FromMedia_Message(param,len);
//			break;
//		case MODULE_ID_SYSTEM:
//			moduleToOsd_FromSystem_Message(param, len);
//			break;
////		case MODULE_ID_CENTER:
////			CenterModuleToOsdModule_Dispatch_Msg(param, len);
////			break;
////		case MODULE_ID_BACK:
////			backCarToOsdModule_Dispatch_Msg(param,len);
////			break;
//
////		//T123
//		case MODULE_ID_AUDIOVIDEO:
//		    //audiovideoToOsdModule_ViewSwitch_Message(param,len);
//			moduleToOsd_FromAudioVideo_Message(param, len);
//		break;
//
//
//	    case MODULE_ID_DVD:
//	        moduleToOsd_FromDVD_Message(param,len);
//		break;
//		case MODULE_ID_DVR:
//		    moduleToOsd_FromDVR_Message(param,len);
//		break;
//		case MODULE_ID_TV:
//		    moduleToOsd_FromTV_Message(param,len);
//		break;
//		case MODULE_ID_AUX:
//		    moduleToOsd_FromAUX_Message(param,len);
//	    break;
//		default:break;
//	}

}


