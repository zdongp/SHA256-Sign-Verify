#include <stdio.h>
#include <stdlib.h>
//#include <cutils/properties.h>


#include "global.h"
#include "param.h"
#include "otherModuleResponseFunction.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "moduleParamRequest.h"
#include "pageID.h"
#include "otherModuleRequestFunction.h"

static bool bOperatnormal = true;
void moduleToSYNC_FromSystem_Message(unsigned char *param, unsigned char len)
{
	unsigned char cmd = param[0];
	switch(cmd){
	    case 0x00:
	      if(param[1] == 0x01)
	      {
	      		LOGD("moduleToSYNC_FromSystem_Message bOperatnormal:%x",bOperatnormal);
	        	if(bOperatnormal)
	        	{
	           	bOperatnormal = false;
	           	syncToHal_Command(SYNC_MODE,SYNC_CMD_0XFF,IR_SYNV_FLYSYSTEM_OPERATNORMAL);
	        	}
			}
	       break;
		case 0x01:
			{
				u8 n_IsAux = 0;
				u8 n_IsAuxLen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_IS_AUX,(u8*)&n_IsAux,&n_IsAuxLen);
				LOGD("moduleToSYNC_FromSystem_Message n_IsAux:%x c_ByMediaState:%x",n_IsAux,pLocalParam->c_ByMediaState);
				if(n_IsAux == 0)
				{
					short curSound = 0;
					unsigned char soundLen;
					getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&curSound,(u8 *)&soundLen);
					LOGD("curSound:%x",curSound);
					if(curSound == 0x05)
					{
						if(param[1] == 0x00)
						{
                            EnterSync();
						}
						else if(param[1] == 0x01)
					  	{
					  		LeaveSyncMedia();
					  	}
						
					}
					else
					{
						LeaveSyncMedia();
					}
				}
			}
			break;
		case 0x2C:// acc off
			break;
		case 0x2D:// acc on
			break;
		case 0xE3:{	// Page Change
			u16 leavePageID = param[1] + param[2] * 0x100;
			u16 enterPageID = param[3] + param[4] * 0x100;
			int pageParam = param[5];
			LOGD("moduleToSYNC_FromSystem_Message enterPageID:%x,leavePageID:%x",enterPageID,leavePageID);
			if(enterPageID == PAGE_SYNV_MENU)
			{
			    syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_ISSYNCPAGE);
			}
			else if(leavePageID == PAGE_SYNV_MENU)
			{
			    syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_NOTSYNCPAGE);
			}
		}
		break;
	}
}

void moduleToSYNC_FromCenter_Message(u8 *param,u8 len)
{
	switch(param[0])
		{
		case 0x00:
		{
			u8 n_IsAux = 0;
			u8 n_IsAuxLen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_IS_AUX,(u8*)&n_IsAux,&n_IsAuxLen);
			LOGD("moduleToSYNC_FromCenter_Message n_IsAux:%x c_ByMediaState:%x",n_IsAux,pLocalParam->c_ByMediaState);
			if(n_IsAux == 0)
			{
				short curSound = 0;
				unsigned char soundLen;
				getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&curSound,(u8 *)&soundLen);
				LOGD("curSound:%x",curSound);
				if(curSound == 0x05)
				{
					if(param[1] == 0x00)
					{
                        EnterSync();
					}
					else if(param[1] == 0x01)
					{
						LeaveSyncMedia();
					}
					
				}
				else
				{
					LeaveSyncMedia();
				}
			}
		}
		break;
		default:break;
		}
}

void moduleToSYNC_FromEXTCAR_Message(u8 *param,u8 len){
	u8 cmd = param[0];
	switch(cmd){
		case 0x01:
			analyseHalMessage_CarType_NEW_FOCUS(param+1,len-1);
		break;
		default:break;
	}
}

void moduleToSYNC_FromAudiovideo_Message(u8 *param,u8 len){
	switch(param[0]){
		case 0x00:
			moduleToSYNC_FromAudiovideo_Get_SoundVideoMode(param[1]);
		break;
		default:break;
	}
}

void moduleToSYNC_FromKey_Message(u8 *param,u8 len){
	switch(param[0]){
		case 0x00:
			moduleToSYNC_Fromkey_Get_KeyValue(param[1]);
		break;
		default:break;
	}
}

void moduleToSYNC_FromExternalCtrl_Message(u8 *param,u8 len)
{
	if(param[0]==0x01)
	{
		if(param[1]==0x01)
		{
				u8 n_IsAux = 0;
				u8 n_IsAuxLen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_IS_AUX,(u8*)&n_IsAux,&n_IsAuxLen);
				if(n_IsAux == 0){
					syncToModule_NotifySystem_JumpPage(PAGE_SYNV_MENU);	
				}
		}
		else
		{
		}
	}
}

void moduleToSYNC_FromAudiovideo_Get_SoundVideoMode(u8 param){
	pLocalParam->m_iSoundChannel = param;
	
	u8 n_IsAux = 0;
	u8 n_IsAuxLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_IS_AUX,(u8*)&n_IsAux,&n_IsAuxLen);
	LOGD("moduleToSYNC_FromAudiovideo_Get_SoundVideoMode n_IsAux:%x c_ByMediaState:%x pLocalParam->m_iSoundChannel:%x",n_IsAux,pLocalParam->c_ByMediaState,pLocalParam->m_iSoundChannel);
	if(n_IsAux == 0)
	{
		if(pLocalParam->m_iSoundChannel == 0x05)
		{
		    if(pLocalParam->c_ByMediaState != 0x01)
	        {
                EnterSync();
            }
		}
		else
		{
			LeaveSyncMedia();
		}
	}
}

void moduleToSYNC_Fromkey_Get_KeyValue(u8 param){
	LOGD("moduleToSYNC_Fromkey_Get_KeyValue param:%x",param);
	switch(param){
		case 0x38:/*��һ�����ҵ绰*/
			syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_SYNV_HANGUP_NEXTONE);
			syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_RELEASE_FINGER);
		break;	
		case 0x39:/*��һ�����ӵ绰*/
			syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_SYNV_CALLIN_LASTONE);
			syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_RELEASE_FINGER);
		break;	
		case 0x4b:/*������������*/
		{
		    //////////////////////////////////////////////////////////////////////////////////////////
		    //The current state of the media in sync, and then switch to 
		    //a non-sync voice channel page and press the steering wheel controls, 
		    //and this time do not jump sync page.
			unsigned short CurPageID = 0;
        	unsigned char CurPageIDLen = 0;
        	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
        	LOGD("moduleToSYNC_Fromkey_Get_KeyValue CurPageID:%x",CurPageID);
        	if(WhetherThePageCanSwitchChannels(CurPageID))
        	{
        	    LOGD("pLocalParam->c_ByMediaState:%x ",pLocalParam->c_ByMediaState);
    	        if(pLocalParam->c_ByMediaState == 0x01){
    		        if(CurPageID != PAGE_SYNV_MENU && CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_NOVIDEO &&  
        			CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)//������ʱ������ҳ
        			syncToModule_NotifySystem_JumpPage(PAGE_SYNV_MENU);
    			}
			}
			//////////////////////////////////////////////////////////////////////////////////////////
			
			syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_SPEECH);
			syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_RELEASE_FINGER);
		}
		break;
		case 0x4c:/*���������ر�*/
			syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_SYNV_QUITSPEECH);
		break;
		case 0x4e:/*���*/
			syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_FAST_FORWARD);
		break;
		case 0x4f:/*����*/
			syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_FAST_REWIND);
		break;
		case 0xff:/*����ָ��*/
			syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_RELEASE_FINGER);
		break;
		case 0x47:
			{
			u16 CurPageID = 0;
			u8	CurPageIDLen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
			if(CurPageID != PAGE_SYNV_MENU && CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_NOVIDEO &&  
			CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)//������ʱ������ҳ
				syncToModule_NotifySystem_JumpPage(PAGE_SYNV_MENU);
			}
			break;
		default:break;
	}
}

void moduleToSync_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;
    analyseAppMessage(param+1,len-1);   
}

void Sync_getStandbyState(u8 param)
{
	u8 n_IsAux = 0;
	u8 n_IsAuxLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_IS_AUX,(u8*)&n_IsAux,&n_IsAuxLen);
	LOGD("[%s] n_IsAux:%x c_ByMediaState:%x",__FUNCTION__,n_IsAux,pLocalParam->c_ByMediaState);
	if(n_IsAux == 0)
	{
		short curSound = 0;
		unsigned char soundLen;
		getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&curSound,(u8 *)&soundLen);
		LOGD("curSound:%x",curSound);
		if(curSound == 0x05)
		{
			if(param == 0x00)
			{
				EnterSync();
			}
			else if(param == 0x01)
			{
				LeaveSyncMedia();
			}
			
		}
		else
		{
			LeaveSyncMedia();
		}
	}

}

