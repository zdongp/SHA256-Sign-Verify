#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "paramID.h"
#include "pageID.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"
#include "moduleParamResponse.h"
#include "moduleParamRequest.h"
#include "timer_interface.h"
#include "controlID.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"


void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len)
{
	switch(sendModuleId){
		case MODULE_ID_SYSTEM:
			OtherModuleToBackCar_AnalyseSystem(param, len);
			break;
		case MODULE_ID_KEY:
			OtherModuleToBackCar_AnalyseKey(param, len);
			break;
		case MODULE_ID_BT:
			OtherModuleToBackCar_AnalyseBluetooth(param, len);
			break;
		case MODULE_ID_AUDIOVIDEO:
			OtherModuleToBackCar_AnalyseAudiovideo(param, len);
			break;
		case MODULE_ID_OSD:
		    OtherModuleToBackCar_AnalyseOsd(param, len);
		    break;
		case MODULE_ID_AUTOMATE: 
		    OtherModuleToBackCar_AnalyseAutomate(param, len);
		    break;
		case MODULE_ID_EXTCAR:
			Get_Extcar_Message_Public(param,len);
			break;
		default:break;
	}
}

void OtherModuleToBackCar_AnalyseBluetooth(unsigned char * pBuf,int nLen)
{
   switch(pBuf[0])
   	{
   	   case 0x85:
	   		Get_Bluetooth_PhoneState(pBuf, nLen);
	   	break;
	   case 0x86:
	   		Get_Bluetooth_CallInfro(pBuf, nLen);
	   	break;
		default:break;
   	}
}

void moduleToBackCar_FromAudiovideo_GetOsdVideoSetting(unsigned char type, unsigned char value)
{
	LOGD("backcar video  type = %x, value = %d",type, value);
	switch(type){
		case 0x00:
			setAnalogData(CONTROLID_BACK_VIDEO_SET_TONE, value);
			break;
		case 0x01:
			setAnalogData(CONTROLID_BACK_VIDEO_SET_SATURATION, value);
			break;
		case 0x02:
			setAnalogData(CONTROLID_BACK_VIDEO_SET_CONTRAST, value);
			break;
		default:break;
	}

}

void OtherModuleToBackCar_AnalyseAudiovideo(unsigned char * pBuf,int nLen)
{
	switch(pBuf[0])
	 {
		case 0x11:
			moduleToBackCar_FromAudiovideo_GetOsdVideoSetting(pBuf[1], pBuf[2]);
		 break;
		 default:break;
	 }

}

void OtherModuleToBackCar_AnalyseOsd(unsigned char * pBuf,int nLen)
{
	switch(pBuf[0])
	 {
		case 0x00:
            if(pBuf[1] == 0x00)
            {
                BackcarVideo_BackGroundColor_Set(false);
            }
		 break;
		 default:break;
	 }

}

void OtherModuleToBackCar_AnalyseAutomate(unsigned char * pBuf,int nLen)
{
    #include "appResponseCommand.h"

    if(pBuf[0] != 0xff)
    return;
    analyseAppMessage(pBuf+1,nLen-1);
}

void get_Radar_BackCarStatus(unsigned char status){
	pLocalParam->bIsBackCarRadarCanSee = status;
}

void OtherModuleToBackCar_AnalyseSystem(unsigned char * pBuf,int nLen)
{
    LOGD("[%s] pBuf[0]:%x,pBuf[1]:%x",__FUNCTION__,pBuf[0],pBuf[1]);
	switch(pBuf[0])
	{
	case 0x10://ϵͳ��λ 0x10 0x00
		break;
	case 0x14://�ָ��������� 0x14 0x00
		{
			pLocalParam->cCurPosOfLine = 1;
			ModuleParamResponse_WriteData();
		}
		break;
	case 0x21:
		Get_SystemVideoState(pBuf[1], pBuf[2]);
		break;
	case 0x22:
		 BackcarToApp_Displaying_RedWarningLine(pBuf[1]);
	    backCarToModule_NotifyOSD_aboutT123_BackCarVideoRefLineDisplay(pBuf[1]);
	    break;
	case 0x23:
		BackcarToApp_Displaying_TraceLine_SetButton(pBuf[1]);
		break;
	case 0x30:
		Get_SystemWakeUp();
		break;
	case 0x31:
		Get_SystemSleep();
		break;
	case 0x43:
		get_Radar_BackCarStatus(pBuf[1]);
		break;
	case 0x2C:	// acc off
		Get_SystemAccOff();
		break;
	case 0x2D:	// acc on
		Get_SystemAccOn();
		break;
	case 0x24:
		Get_System_Video_TraceType(pBuf[1]);
		break;
	default:
		break;
	}

}

void OtherModuleToBackCar_AnalyseKey(unsigned char * pBuf,int nLen)
{
	switch (pBuf[0]) //����
	{
	  case 0x49:
		pLocalParam->EnterAllScreen=0;
		BackcarToHal_ExitPanoramicVideo();
		break;
	}
}

bool IsCanJumpBackVidePage(u8 uCmd1,u8 uCmd2)
{
	if(uCmd1)
	{
		if(uCmd2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}	
}


void Get_SystemVideoState(u8 bIsBacking, u8 bIsHaveVideo)//��Ƶ״̬
{
	LOGD("%x %x    %x %x",bIsBacking,pLocalParam->bIsInBackCar,bIsHaveVideo,pLocalParam->bBackVideostate);
	if((bIsBacking == pLocalParam->bIsInBackCar) && (bIsHaveVideo == pLocalParam->bBackVideostate))
		return;
		
	pLocalParam->bIsInBackCar = bIsBacking;
	pLocalParam->bBackstate = bIsBacking;
	pLocalParam->bBackVideostate = bIsHaveVideo;
	LOGD("pLocalParam->bIsInBackCar:%d",pLocalParam->bIsInBackCar);
	
	makeAndSendBackCarState(pLocalParam->bBackstate);

	if (bIsBacking == 1)
    {
	   //�����ڵ���
	   	LOGD("bIsHaveVideo+++++++++++++++++++++++++++++++++++++0x%x",bIsHaveVideo);
				
	   	u8 bIsBackCarDetecteEnable = 1;
	    u8 nLen = 1;
	    getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_SET_BACKCAR_DETECTEENABLE_STATUS, (u8*)&bIsBackCarDetecteEnable, (u8*)&nLen);
	   	LOGD("bIsBackCarDetecteEnable+++++++++++++++++++++++++++++++++++++0x%x",bIsBackCarDetecteEnable);

		bool bTempVideoStatus = IsCanJumpBackVidePage(bIsBackCarDetecteEnable,pLocalParam->bBackVideostate);
		LOGD("bTempVideoStatus+++++++++++++++++++++++++++++++++++++0x%x",bTempVideoStatus);
		
		//if (bIsBackCarDetecteEnable == 1)//�������Ƶ��ȥ��OSDҳ
		if(bTempVideoStatus == true)
		{
			if(pLocalParam->cBackcarWarnTextTime != 0)
			{
				IsDisplaying_WarnintLineText(pLocalParam->uTempWarningDontShow);
			}
			
			backCarToModule_NotifyOSD(true);
			LOGD("pLocalParam->c_carName:%s, Warning Text Show time =%x",pLocalParam->c_carName,pLocalParam->cBackcarWarnTextTime);

			if(bIsHaveVideo == 0xff)/*In the case of reversing the standby machine, reverse video out there, but reversing the start screen will flash twice the normal black again*/
			    return;

          if(strncmp(pLocalParam->c_carName,"SUBARU",6))
			{
				u8 bIsBackCarRefLineEnable = 1;
		       u8 nLen0 = 1;
		       getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_SET_BackVideoRefLineEnable, (u8*)&bIsBackCarRefLineEnable, (u8*)&nLen0);
		       LOGD("Get_SystemVideoState bIsBackCarRefLineEnable:%x",bIsBackCarRefLineEnable);
        	    if(bIsBackCarRefLineEnable == 1)
        	    {
        	       backCarToModule_NotifyOSD_aboutT123_BackCarVideoRefLineDisplay(1);
        	    }

				backCarToModule_NotifySystem_ActualReversingState(0x01);
			   backCarToModule_NotifySystem_JumpPage(PAGE_BACK_VIDEO);

				LOGD("[%s] pLocalParam->bBackcarThreeAngle:%x",__FUNCTION__,pLocalParam->bBackcarThreeAngle);
			   if(pLocalParam->bBackcarThreeAngle)
			   {
			   		LOGD("[%s] pLocalParam->nBackVisionAngle:%x",__FUNCTION__,pLocalParam->nBackVisionAngle);
			       backcarToModule_NotifySystem_VisionAngle(pLocalParam->nBackVisionAngle);
				   backcarToModule_NotifyOSD_aboutT123_VideoOSDSetButton(0x20+(pLocalParam->nBackVisionAngle-0x01),0x01);
			   }

			   DeleteTimer(BACK_OSD_TIMER_HIDDEN_DISPLAY);
			   if(pLocalParam->cBackcarWarnTextTime!=0)
			   {
				   int times = pLocalParam->cBackcarWarnTextTime*1000;
			       SetTimer(times,1,BACK_OSD_TIMER_HIDDEN_DISPLAY);
			   }


			}
			else
			{
			   backCarToModule_NotifySystem_JumpPage(PAGE_BACK_FULL_VIDEO_CONTROL);
			   DeleteTimer(BACK_OSD_TIMER_HIDDEN_DISPLAY);
			   SetTimer(3000,1,BACK_OSD_TIMER_HIDDEN_DISPLAY);
			}
			backCarToModule_NotifySystem_AlarmBackCar(true);
			BackcarToHal_SelectVideo(pLocalParam->saveBackCar);
	        setAnalogData(CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_WHICH_IMG,((short)pLocalParam->saveBackCar)-1);

			pLocalParam->EnterAllScreen=0;
			LOGD("pLocalParam->udialin:%x",pLocalParam->udialin);
			if(pLocalParam->udialin){//�������紦��
				BackcarToApp_Inside_ActShowAnswerBox(true);
			}

		}
		//else if (bIsBackCarDetecteEnable == 0)//���û����Ƶ����ȥ������Ƶ��ʾҳ
		else if (bTempVideoStatus == false)
		{
			LOGD("pLocalParam->c_carName:%s",pLocalParam->c_carName);
			if(strncmp(pLocalParam->c_carName,"PRADO_",6) == 0)
			{
				 u8 bIsPradoRadarKeySwtichState = 1;
			    u8 nLen = 1;
			    getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_PRADO_RADAR_KEY_SWITCH_STATUS, (u8*)&bIsPradoRadarKeySwtichState, (u8*)&nLen);
				 u8 bIsPradoRadarUiSwtichState = 1;
			    u8 nLen1 = 1;
			    getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_PRADO_RADAR_UI_SWITCH_STATUS, (u8*)&bIsPradoRadarUiSwtichState, (u8*)&nLen1);
				LOGD("(%d %d)",bIsPradoRadarKeySwtichState,bIsPradoRadarUiSwtichState);
				if(bIsPradoRadarKeySwtichState == 0 || bIsPradoRadarUiSwtichState == 0)
				{	
				}
				else
				{
					backCarToModule_NotifySystem_JumpPage(PAGE_BACK_NOVIDEO);
				}
			}
			else
			{
				backCarToModule_NotifyOSD(true);
				backCarToModule_NotifySystem_JumpPage(PAGE_BACK_NOVIDEO);
			}
		}
		backCarToModule_NotifyExternalctrl_VoiceSwitchCtrl(0x00);
    }
    else if (bIsBacking == 0)
    {
   		// jing send 0705 to UI to undisplay that backcar vedio's red osd line 2013-7-24
		//  jing ����0705��UI��UI���ص�����Ƶ�ĺ�ɫosd�� 2013-7-24
		//backCarToModule_NotifySystem_Out_BackCar_RedOsd();

		setVisible(CONTROLID_REVERSING_VIDEO_PARK_CAR_BODY_ICON,0);
		setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_FIRST,0);
		setVisible(CONTROLID_REVERSING_VIDEO_PARK_TXT_LINE_SECOND,0);
			
		backCarToModule_NotifySystem_ActualReversingState(0x00);
		BackcarVideo_IsShowVideoColorButton(false);
		pLocalParam->EnterAllScreen=0;
        BackcarToHal_ExitPanoramicVideo();

		//���˳�����
		u16 curPage = 0;
		unsigned char curPageLen = 2;
		getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);
		
		u16 prePage = 0;
		unsigned char prePageLen = 2;
		getOtherModuleParam(MODULE_ID_SYSTEM, PREV_PAGE, (u8 *)&prePage, (u8 *)&prePageLen);

		u16 supportA2dp = 0;
		unsigned char supportA2dpLen = 1;
		getOtherModuleParam(MODULE_ID_BT, BT_A2DP_SUPPORT, (u8 *)&supportA2dp, (u8 *)&supportA2dpLen);

		u16 btConnectState = 0;
		unsigned char btConnectStateLen = 1;
		getOtherModuleParam(MODULE_ID_BT, BT_HF_CONNECT_STATUS, (u8 *)&btConnectState, (u8 *)&btConnectStateLen);

		u16 btPhoneState = 0;
		unsigned char btPhoneStateLen = 1;
		getOtherModuleParam(MODULE_ID_BT, BT_MOBILE_STATUS, (u8 *)&btPhoneState, (u8 *)&btPhoneStateLen);
        LOGD("curPage:%x ,prePage:%x ,supportA2dp:%d ,btConnectState:%d,btPhoneState=%d",curPage,prePage,supportA2dp,btConnectState,btPhoneState);
		
		if (PAGE_BACK_VIDEO == curPage || PAGE_BACK_NOVIDEO == curPage||curPage==PAGE_BACK_FULL_VIDEO||curPage==PAGE_BACK_FULL_VIDEO_CONTROL||curPage==PAGE_BACK_RADAR)//���ϴ�״̬�ڵ���������Ҫ�˳�
		{
			if(pLocalParam->bIsIsrCountry == 1)
			{
				if(PAGE_BLUETOOTH_NO_A2DP == prePage && supportA2dp == 1 && btConnectState == 1)
				{
					backCarToModule_NotifySystem_JumpPage(PAGE_BLUETOOTH_A2DP);
				}
				else if(PAGE_BLUETOOTH_A2DP == prePage && supportA2dp == 0 && btConnectState == 0)
				{
					backCarToModule_NotifySystem_JumpPage(PAGE_BLUETOOTH_NO_A2DP);
				}
				else{
			   		backCarToModule_NotifySystem_JumpPrePage();
				}
			}
			else
			{
				if(prePage == PAGE_BLACK)
					backCarToModule_NotifySystem_JumpPrePage();
				
			  	else if(btPhoneState == 1 || btPhoneState == 2 ||btPhoneState == 3)
			  	{
					backCarToModule_NotifySystem_JumpPage(PAGE_BLUETOOTH_MAIN);
			  	}
				else if(PAGE_BLUETOOTH_NO_A2DP == prePage && supportA2dp == 1 && btConnectState == 1)
					backCarToModule_NotifySystem_JumpPage(PAGE_BLUETOOTH_A2DP);
				
				else if(PAGE_BLUETOOTH_A2DP == prePage && supportA2dp == 0 && btConnectState == 0)
					backCarToModule_NotifySystem_JumpPage(PAGE_BLUETOOTH_NO_A2DP);
				
				else
			   		backCarToModule_NotifySystem_JumpPrePage();
			}
		}
		else
		{
			backCarToModule_NotifySystem_JumpPage(PAGE_MENU);
		} 			
		BackcarToApp_Inside_ActShowAnswerBox(false);//�������紦��
		backCarToModule_NotifyExternalctrl_VoiceSwitchCtrl(0x01);
    }

}

void Get_SystemWakeUp(void)
{
	ModuleParamResponse_InitByConfig();
}

void Get_SystemSleep(void)
{
	ModuleParamResponse_WriteData();
}

void Get_SystemAccOn(void)
{
	ModuleParamResponse_InitParam();
	ModuleParamResponse_ReadData();
	ModuleParamResponse_InitByConfig();
}
void Get_SystemAccOff(void)
{
	ModuleParamResponse_WriteData();
}

void Get_System_Video_TraceType(u8 p)
{
	setToUI_BackCarLine_Type(p);
	pLocalParam->e_Backcar_TraceType = (Em_Backcar_TraceType)p;
}

void Get_Extcar_Message_Public(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0xf0:
			analysePublicCarInfoToBackCarSet(p+1,len-1);
			break;
		default:break;
	}
}
void analysePublicCarInfoToBackCarSet(u8 *p,u8 len)
{
	LOGD("[%s]   p[0]:%x  p[2]:%x",__FUNCTION__,p[0],p[2]);
	switch(p[0])
	{
		case 0x12:
			{
				if(p[1] == 0x05)
				{
					pLocalParam->uVideoZoomInOrOut = p[2];
					showVideoZoomInOrOutStatus(p[2]);
				}	
			}
		break;
		default:break;
	}
}


