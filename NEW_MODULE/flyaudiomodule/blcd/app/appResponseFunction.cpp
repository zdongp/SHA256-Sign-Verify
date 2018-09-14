#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"


void appToAudioVideo_Blcd_Back_MouseDown(void){

}
void appToAudioVideo_MENUBLCD_MouseDown(void){

}


void appToAudioVideo_Blcd_Back_MouseUp(void){
	blcdToModule_NotifySystem_JumpPage(PAGE_MENU);
}

void appToAudioVideo_MENUBLCD_MouseUp(void){
	blcdToModule_NotifySystem_JumpPage(PAGE_BLCD);
}


void appToAudioVideo_PLAYPAUSE_MouseUp(void){
	switch (pLocalParam->getMode)
	{
	case emBlcdMode_DVD:
		if (SoundMode_DVD!=pLocalParam->audioMode)
		{
			/////////////////////测试 7-22/////////////////////////
			if (!pLocalParam->PlayState)
			{
				Set_DVD_PlayControl(0x15);
				pLocalParam->PlayState = 1;
			}
			else
			{
				Set_DVD_PlayControl(0x14);
				pLocalParam->PlayState = 0;
			}
		}
		break;
	case emBlcdMode_CDC:
		if (SoundMode_CDC!=pLocalParam->audioMode)
		{
			Set_CDC_PlayControl(0x00);
		}
		break;
	case emBlcdMode_TV:
		if (SoundMode_TV!=pLocalParam->audioMode)
		{
			//Set_DataDigital(FUNCID_BLCD_BTN_PLAY,false);
			//Set_Refresh(0);
			//m_pCtrlCenter->m_pCenterModule->Set_TV_PlayControl(0x0E);
		}
		break;
	case emBlcdMode_AUX:
		if (SoundMode_AUX!=pLocalParam->audioMode)
		{
			//Set_DataDigital(FUNCID_BLCD_BTN_PLAY,false);
			//Set_Refresh(0);
			//m_pCtrlCenter->m_pCenterModule->Set_AUX_PlayControl(0x00);
		}
		break;
	default:
		break;
	}
}

void appToAudioVideo_STOP_MouseUp(void){
	switch (pLocalParam->getMode)
	{
	case emBlcdMode_DVD:
		if (SoundMode_DVD!=pLocalParam->audioMode)
		{
			Set_DVD_PlayControl(0x17);
			Set_DVD_PlayControl(0x17);
			Set_DVD_PlayControl(0x17);
		}
		break;
	case emBlcdMode_CDC:
		if (SoundMode_CDC!=pLocalParam->audioMode)
		{
			Set_CDC_PlayControl(0x03);
		}
		break;
	case emBlcdMode_TV:
		if (SoundMode_TV!=pLocalParam->audioMode)
		{
			//Set_DataDigital(FUNCID_BLCD_BTN_STOP,false);
			//Set_Refresh(0);
			//m_pCtrlCenter->m_pCenterModule->Set_TV_PlayControl(0x0E);
		}
		break;
	case emBlcdMode_AUX:
		if (SoundMode_AUX!=pLocalParam->audioMode)
		{
			//Set_DataDigital(FUNCID_BLCD_BTN_STOP,false);
			//Set_Refresh(0);
			//m_pCtrlCenter->m_pCenterModule->Set_AUX_PlayControl(0x00);
		}
		break;
	default:
		break;
	}


}

void appToAudioVideo_PRE_MouseUp(void){
	switch (pLocalParam->getMode)   //返回后座娱乐的模式的值
	{
	case emBlcdMode_DVD:
		if (SoundMode_DVD!= pLocalParam->audioMode)
		{
			Set_DVD_PlayControl(0x18);
		}
		break;
	case emBlcdMode_CDC:
		if (SoundMode_CDC!=pLocalParam->audioMode)
		{
			Set_CDC_PlayControl(0x01);
		}
		break;
	case emBlcdMode_TV:
		if (SoundMode_TV!=pLocalParam->audioMode)
		{
			//Set_DataDigital(FUNCID_BLCD_BTN_PREVIOUS,false);
			//Set_Refresh(0);
			//Set_TV_PlayControl(0x05);
		}
		break;
	case emBlcdMode_AUX:
		if (SoundMode_AUX!=pLocalParam->audioMode)
		{
			//Set_DataDigital(FUNCID_BLCD_BTN_PREVIOUS,false);
			//Set_Refresh(0);
			//m_pCtrlCenter->m_pCenterModule->Set_AUX_PlayControl(0x00);
		}
		break;
	default:
		break;
	}	

}

void appToAudioVideo_NEXT_MouseUp(void){
	LOGD("getMode:%d , audioMode:%d",pLocalParam->getMode, pLocalParam->audioMode);
	switch (pLocalParam->getMode)
	{
	case emBlcdMode_DVD:
		if (SoundMode_DVD!=pLocalParam->audioMode)
		{
			Set_DVD_PlayControl(0x19);
		}
		break;
	case emBlcdMode_CDC:
		if (SoundMode_CDC!=pLocalParam->audioMode)
		{
			Set_CDC_PlayControl(0x02);
		}
		break;
	case emBlcdMode_TV:
		if (SoundMode_TV!=pLocalParam->audioMode)
		{
			//Set_DataDigital(FUNCID_BLCD_BTN_NEXT,false);
			//Set_Refresh(0);
			//m_pCtrlCenter->m_pCenterModule->Set_TV_PlayControl(0x0D);
		}
		break;
	case emBlcdMode_AUX:
		if (SoundMode_AUX!=pLocalParam->audioMode)
		{
			//Set_DataDigital(FUNCID_BLCD_BTN_NEXT,false);
			//Set_Refresh(0);
			//m_pCtrlCenter->m_pCenterModule->Set_AUX_PlayControl(0x00);
		}
		break;
	default:
		break;
	}

}

void appToAudioVideo_MAINDVD_MouseUp(void){
	pLocalParam->setMode= emSetBlcdMode_DVD;
	Set_Mode(emSetBlcdMode_DVD);

	pLocalParam->getMode=emBlcdMode_DVD;
	Show_Blcd_Mode();
	Set_Mode(emBlcdMode_DVD);

}

void appToAudioVideo_MAINCDCTV_MouseUp(void){
	/*
	if("点击时是CDC"){
		pLocalParam->setMode=emSetBlcdMode_CDC_TV;
		Set_Mode(emSetBlcdMode_CDC_TV);

		pLocalParam->getMode=emBlcdMode_CDC;
		Show_Blcd_Mode();
		Set_Mode(emBlcdMode_CDC);
		}
	else{
		pLocalParam->setMode=emSetBlcdMode_CDC_TV;
		Set_Mode(emSetBlcdMode_CDC_TV);

		pLocalParam->getMode=emBlcdMode_TV;
		Show_Blcd_Mode();
		Set_Mode(emBlcdMode_TV);
	}
	*/
}


void appToAudioVideo_PLAYPAUSE_MouseDown(void){

}

void appToAudioVideo_STOP_MouseDown(void){

}

void appToAudioVideo_PRE_MouseDown(void){

}

void appToAudioVideo_NEXT_MouseDown(void){

}

void appToAudioVideo_MAINDVD_MouseDown(void){

}

void appToAudioVideo_MAINCDCTV_MouseDown(void){

}


