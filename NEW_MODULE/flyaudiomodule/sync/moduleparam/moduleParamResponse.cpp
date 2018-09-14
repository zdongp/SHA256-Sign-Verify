#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleParamResponse.h"
#include "controlID.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "param.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"


void moduleParameterInit(void){
	
}

void moduleParameterDeInit(void){
}

void moduleParameterReInit(void){
}

int module_extendInterface(char *buffer, int len){
	LOGD("******************sync module_extendInterface:%x,%x",buffer[0],buffer[1]);
	switch(buffer[0]){
		case 0x1D:
			{
				if(buffer[1] == 0x00)//Standby on
				{
					Sync_getStandbyState(0x00);
				}
				else if(buffer[1] == 0x01)//Standby off
				{
					Sync_getStandbyState(0x01);
				}
   			}
			break;
		case 0x2C:
			if(buffer[1] == 0x00)//acc off
			{
				LOGD("sync************************acc off");
				//LeaveSyncMedia();
				pLocalParam->c_ByMediaState = 0x00;
				saveParameter();
			}
			if(buffer[1] == 0x01)//restart
			{
				LOGD("sync************************restart");
				//sLeaveSyncMedia();
				pLocalParam->c_ByMediaState = 0x00;
				saveParameter();
			}
			if(buffer[1] == 0x02)//default
			{
				LOGD("sync************************default");
				setDefaultParam();
				saveParameter();
			}
			break;
		case 0x2D://acc on
			if(buffer[1] == 0x00)
			{
				LOGD("sync************************acc on");
				//pLocalParam->b_SyncAble = false;
				//setAnalogData(CONTROLID_MENU_SYNV,2);
				//setControllable(CONTROLID_MENU_SYNV,false);
			}
			break;
		case 0xFD:
			{
				initByConfig();
			}
			break;
		default:break;
	}

	return 0;
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		default:break;
	}
}

void setDefaultParam(void){

	/************  新福克斯  ***********/
	pLocalParam->b_SyncAble = true;
	pLocalParam->c_ByMediaState = 0x00;
	pLocalParam->b_BtCallState = false;
	pLocalParam->m_bSpeech_ButtonValue = false;
	pLocalParam->m_iSoundChannel = -1;
	pLocalParam->bAutoJumpPrePage = false;
	DefaultParam_aboutSyncSetPageInfor();
}

void DefaultParam_aboutSyncSetPageInfor()
{
	pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4_len = 0;
	pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5_len = 0;

	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine1,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine2,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine3,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine4,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncTextLine5,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton1,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton2,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton3,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncButton4,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox2,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox3,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox4,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_curpage.cSyncCheckBox5,0,FILE_SYNC_TEXT_MAX_LEN);

	pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4_len = 0;
	pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5_len = 0;

	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine1,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine2,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine3,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine4,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncTextLine5,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton1,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton2,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton3,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncButton4,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox2,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox3,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox4,0,FILE_SYNC_TEXT_MAX_LEN);
	memset(pLocalParam->Sync_file_textandbutton_prepage.cSyncCheckBox5,0,FILE_SYNC_TEXT_MAX_LEN);

}

void initByConfig(void){
	setDefaultParam();
	InitConfig_Visible_setup();
	//syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_OUT_SYNCMEDIA);
	SendSYNCInfoToOSDDebug();
	//pLocalParam->b_SyncAble = false;
}

void recoverLastSet()			//恢复最后一次设置
{
}
