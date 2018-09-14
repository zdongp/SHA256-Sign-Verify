#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "pageID.h"

#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "moduleParamResponse.h"
#include "otherModuleRequestCommand.h"
#include "appResponseFunction.h"
#include "moduleParamRequest.h"
#include "timer_interface.h"

void Get_BrakeState(u8 state)
{
	if(state == 0x01)
	{
		LOGD("DVR Get_BrakeState-0x01-!bBrake--m_iPresentMode--!bPlayOrPause:%x,%x,%x",!pLocalParam->bBrake,pLocalParam->m_iPresentMode,!pLocalParam->bPlayOrPause);
		if((!pLocalParam->bBrake) && (pLocalParam->m_iPresentMode == RePlayMode) && (!pLocalParam->bPlayOrPause))
		{
			Set_DVR_SoftWareImitateKeyCtrl(PLAY);
			pLocalParam->bPlayOrPause = true;
		}
	}
	else//不可进入视频，在视频里就要暂停视频
	{
		LOGD("DVR Get_BrakeState--bBrake--m_iPresentMode--bPlayOrPause:%x,%x,%x",pLocalParam->bBrake,pLocalParam->m_iPresentMode,pLocalParam->bPlayOrPause);
		if((pLocalParam->bBrake) && (pLocalParam->m_iPresentMode == RePlayMode) && (pLocalParam->bPlayOrPause))
		{
			Set_DVR_SoftWareImitateKeyCtrl(PAUSE);
			pLocalParam->bPlayOrPause = false;
		}
	}
}

void IsInDVRMode(u8 *param)
{
	bool bLeave = false;
	bool bEnter = false;

	u16 uLeavePageID = (u16)((param[1]<<8)&0xff00)+param[0];
	u16 uEnterPageID = (u16)((param[3]<<8)&0xff00)+param[2];

	LOGD("IsInDVRMode  uLeavePageID:%x  uEnterPageID:%x",uLeavePageID,uEnterPageID);
	
	switch(uLeavePageID)
	{
		case PAGE_DRIVING_RECORD_MENU:
		case PAGE_DRIVING_RECORD_TIME_SET:
		case PAGE_DRIVING_RECORD_SET:
		case PAGE_DRIVING_RECORD_PALY:
		case PAGE_DRIVING_RECORD_VIDEO:
		case PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD:
		case PAGE_DRIVING_CHANGHE_DVR_SET_OSD:
			bLeave = true;
		break;
		default:break;
	}

	switch(uEnterPageID)
	{
		case PAGE_DRIVING_RECORD_MENU:
		case PAGE_DRIVING_RECORD_TIME_SET:
		case PAGE_DRIVING_RECORD_SET:
		case PAGE_DRIVING_RECORD_PALY:
		case PAGE_DRIVING_RECORD_VIDEO:
		case PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD:
		case PAGE_DRIVING_CHANGHE_DVR_SET_OSD:
			bEnter= true;
		break;
		default:
			pLocalParam->bEnterDVRModuleMark = false;
		break;
	}

	if(bLeave && !bEnter)
	{
		LeaveDVR();
	}
	else if(bEnter && !bLeave)
	{
		EnterDVR();
	}

}

void LeaveDVR()
{
	LOGD("LeaveDVR pLocalParam->m_iPresentMode:%x",pLocalParam->m_iPresentMode);
	switch(pLocalParam->m_iPresentMode)
	{
		case VideoMode:
		break;
		case RePlayMode:
			Set_DVR_SoftWareImitateKeyCtrl(PAUSE);
		break;
		case SetTimeMode:
		case SetVideoMode:
		break;
	}
	
	pLocalParam->bEnterDVRModuleMark = false;
	pLocalParam->m_LMode = pLocalParam->m_iPresentMode;
}

void EnterDVR()
{
	LOGD("EnterDVR bEnterDVRModuleMark:%x  m_iPresentMode:%x bPlayOrPause:%x",pLocalParam->bEnterDVRModuleMark,pLocalParam->m_iPresentMode,pLocalParam->bPlayOrPause);
	if(!pLocalParam->bEnterDVRModuleMark)
	{
		Set_DVR_SoftWareImitateKeyCtrl(DetectingMode);
		switch(pLocalParam->m_iPresentMode)
		{
			case VideoMode:
			break;
			case RePlayMode:
				if(pLocalParam->bPlayOrPause)
				{
					Set_DVR_SoftWareImitateKeyCtrl(PLAY);
					pLocalParam->bPlayOrPause = true;
				}
			break;
			case SetTimeMode:
			case SetVideoMode:
			break;
		}
	}

	pLocalParam->bEnterDVRModuleMark = true;
}

void KeyMsgAV()
{
	u8 buf[] = {0x81,MODULE_ID_DVR};
	makeAndSendMessageToModule(MODULE_ID_DVR,MODULE_ID_SYSTEM,buf,2);
}

void KeyMsgSEEK_TUNE_INC()
{
	if(pLocalParam->m_iPresentMode == RePlayMode)
	{
		Set_DVR_SoftWareImitateKeyCtrl(NEXT);
	}
}

void KeyMsgSEEK_TUNE_DEC()
{
	if(pLocalParam->m_iPresentMode == RePlayMode)
	{
		Set_DVR_SoftWareImitateKeyCtrl(PREV);
	}

}


void moduleToDVR_FromSystem_Message(unsigned char *param, unsigned char len){

	unsigned char ucSystemCmd = param[0];
	switch(ucSystemCmd)
	{
		case 0x09:
			Get_BrakeState(param[1]);
		break;
		case 0x10: //复位 保存注册表
			saveParameter();
		break;
		case 0x14: //恢复出厂设置
		{
			SetDefaultParam();
			saveParameter();
		}
		break;
		case 0x30: //ACC ON
		{
			if(!pLocalParam->bDVRModuleState)
			{
				dvrToApp_SetDVRMenuDisable();
			}

			Set_DVR_SoftWareImitateKeyCtrl(DetectingMode);
		}
		break;
		case 0x31: //to  ------->> module_extendInterface
		break;
		case 0x40:
			SetToHal_DVR_BackCar_Carema_Protocol_CVBS_OR_USB(param[1]);
		break;
		case 0x2D://进入、退出DVRMODULE
			IsInDVRMode(param+1);
		break;

		//>>>>>>>>>>>>>>>>>>>测试>>>>>>>>>>>>//
		//case 0x2c:
		//	appToDvr_Menu_Button_MouseUp();
		//break;
		default:break;
	}
}

void moduleToDVR_FromAudiovideo_Message(unsigned char *param, unsigned char len){
	u8 cmd = param[0];
	u8 uSoundMod = param[1];
	switch(cmd)
	{
		case 0x00:
			if(param[1] == CHANNEL_DVR_CTRL || param[1] == CHANNEL_DVR_VIDEO){
				EnterDVR();
			}
			else{
				LeaveDVR();
			}
		break;
		case 0x01:
			moduleToDvr_FromAudiovideo_GetVolumeOsdCtrl();
		break;
		default:break;
	}

}

void moduleToDVR_FromKey_Message(unsigned char *param, unsigned char len){

	if(param[0] != 0x00)
		return;
	unsigned char ucKeyCmdParam = param[1]; 
	
	switch(ucKeyCmdParam)
	{
		case 0x03://KEY_AV
			KeyMsgAV();
		break;
		case 0x38://KEY_SEEK_INC
		case 0x3B://KEY_TUNE_INC
			KeyMsgSEEK_TUNE_INC();
		break;
		case 0x39://KEY_SEEK_DEC
		case 0x3C://KEY_TUNE_DEC	
			KeyMsgSEEK_TUNE_DEC();
		break;
		default:break;
	}

}

void moduleToDVR_FromBT_Message(unsigned char *param, unsigned char len)
{
	if(param[0] == 0x06)
	{
		bool bSwitchFlag = true;
		switch(param[1])
		{
			case 0x00:
			{
				LOGD("moduleToDVR_FromBT_Message --0x00--!bSwitchFlag--m_iPresentMode--!bPlayOrPause:%x,%x,%x",!bSwitchFlag,pLocalParam->m_iPresentMode,!pLocalParam->bPlayOrPause);
				if((!bSwitchFlag) && (pLocalParam->m_iPresentMode == RePlayMode) && (!pLocalParam->bPlayOrPause))
				{
					Set_DVR_SoftWareImitateKeyCtrl(PLAY);
					pLocalParam->bPlayOrPause = true;
				}
				bSwitchFlag = true;
			}
			break;
			case 0x01:
			case 0x02:
			{
				LOGD("moduleToDVR_FromBT_Message--0x01-0x02--bSwitchFlag--m_iPresentMode--bPlayOrPause:%x,%x,%x",bSwitchFlag,pLocalParam->m_iPresentMode,pLocalParam->bPlayOrPause);
				if((bSwitchFlag) && (pLocalParam->m_iPresentMode == RePlayMode) && (pLocalParam->bPlayOrPause))
				{
					Set_DVR_SoftWareImitateKeyCtrl(PAUSE);
				}
				bSwitchFlag = false;
			}
			break;
			default:break;
		}
	}
}

void moduleToDvr_FromAudiovideo_GetVolumeOsdCtrl()
{
	u16 curpage = 0;
	u8 len = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&curpage, &len);
	if(curpage == PAGE_DRIVING_RECORD_MENU || curpage == PAGE_DRIVING_RECORD_PALY || curpage == PAGE_DRIVING_RECORD_SET || curpage == PAGE_DRIVING_RECORD_TIME_SET || curpage == PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD || curpage == PAGE_DRIVING_CHANGHE_DVR_SET_OSD)
	{
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
	}
}


void moduleToDvr_FromExternalCtrl_Message(unsigned char *param,unsigned char len)
{
    
    if(param[0] == 0x00)
    {
    }
	else if(param[0] == 0x01)
	{
		if(param[1] == 0x01)
		{
			appToDvr_Menu_Button_MouseUp();
		}
		else
		{
		}
	}

}

void moduleToDvr_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;
    analyseAppMessage(param+1,len-1);   
}

void moduleToDvr_FromCenter(u8 *param, int len)
{
	if(pLocalParam->uDvrModule_is_T123 == 0)
	{
		if(param[0] == 0)
		{
			if(param[1] == 0)//ON
			{
				readUsbCameraRecording();
				InitDriver();
			}
			else if(param[1] == 1)//OFF
			{
				saveParameter();
				pLocalParam->bCurIsDvrInit = false;
			}
		}
	}
}