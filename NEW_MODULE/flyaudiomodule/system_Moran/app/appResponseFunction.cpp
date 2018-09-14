#include <stdio.h>
#include <stdlib.h>
//#include <cutils/properties.h>

#include "global.h"
#include "controlID.h"
#include "param.h"
#include "pageID.h"
#include "stringID.h"

#include "types_def.h"
#include "commonFunc.h"
#include "halRequestFunction.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "moduleParamRequest.h"
#include "halResponseFunction.h"
#include "timer_interface.h"
#include "appResponseCommand.h"
#include "appResponseFunction.h"

//#include "FlySystemAbout.h"

extern "C"{
#include "unicodestring.h"
};

void appToSys_Menu_SetUp_MouseUp(void)
{
	switch_Page(PAGE_SETUP_BEGIN);
//	moduleOpenDev();
}

void appToSys_Menu_Style_MouseUp(void)
{
	switch_Page(PAGE_SYSTEM_STYLE);
}
void appToSys_Menu_DayNight_MouseUp(void)
{
	
}
void appToSys_Menu_NightDay_MouseUp(u8 buf)
{
	  LOGD("pLocalParam->b_Sys_LightDetect:0x%x-----buf:0x%x",pLocalParam->b_Sys_LightDetect,buf);
	  if(pLocalParam->b_Sys_LightDetect)
			return;
	  if(buf)
	  	{
		systemToHal_DayOrNight(0x01);
	  	}
	  else
	  	{
	  	 systemToHal_DayOrNight(0x00);
	  	}
}

void appToSys_Menu_Off_MouseUp(void)
{
	systemToHal_SetLCDBrightness(SYSTEMTOHAL_LCDBRIGHTNESS_BLACK);
}
void appToSys_Menu_Dark_MouseUp(void)
{
	systemToHal_SetLCDBrightness(SYSTEMTOHAL_LCDBRIGHTNESS_LOW);
}
void appToSys_Menu_Middle_MouseUp(void)
{
	systemToHal_SetLCDBrightness(SYSTEMTOHAL_LCDBRIGHTNESS_MIDDLE);
}
void appToSys_Menu_Light_MouseUp(void)
{
	systemToHal_SetLCDBrightness(SYSTEMTOHAL_LCDBRIGHTNESS_HIGH);
}

void appToSys_Menu_High_Light_MouseUp(void)
{
	systemToHal_SetLCDBrightness(SYSTEMTOHAL_LCDBRIGHTNESS_HIGH_HIGH);
}


//Set Up Jump Page Begin or End
void appToSys_Setup_JumpPage_MouseUp(short PageID) //Jump Page
{
	systemToModule_NotifySystem_JumpPage(PageID);
}

void appToSys_Setup_Back_MouseUp()
{
	systemToModule_NotifySystem_JumpPrePage();
}


//Setup Next Pre Page
void appToSys_Setup_PrevPage_MouseUp(void)
{
	systemToModule_NotifySystem_JumpPage(PAGE_SETUP_BEGIN);		
}

void appToSys_Setup_NextPage_MouseUp(void)
{
	systemToModule_NotifySystem_JumpPage(PAGE_SYSTEM_SET_COMMON_SECOND_PAGE);
}

//Setup System 
void appToSys_Setup_Info_MouseUp(void)
{
	pLocalParam->m_flySystemAbout.updateSystemAbout();

	switch_Page(PAGE_COPYRIGHT);
}
void appToSys_Setup_Screen_MouseUp(void)
{
	
}
void appToSys_Setup_SysReset_MouseUp(void)
{
    appToUiDialogDisplaying_aboutSysReset(true);
}
void appToSys_Setup_SysResetDialogOKOrCANCEL_MouseUp(u8 state )
{
    appToUiDialogDisplaying_aboutSysReset(false);
	if(state == 0)
		systemToHal_SimulateKey(SYSTEMTOHAL_SIMKEY_RESET);
}

void appToUiDialogDisplaying_aboutSysReset(bool bSign)
{
	setUpdateUI(false);
	setVisible(CONTROLID_SETUP_RESTART_DIALOG, bSign);
	setVisible(CONTROLID_SETUP_RESTART_DIALOG_TEXT, bSign);
	setVisible(CONTROLID_SETUP_RESTART_DIALOG_OK, bSign);
	setVisible(CONTROLID_SETUP_RESTART_DIALOG_CANCEL, bSign);
	setUpdateUI(true);

}

void appToSys_Setup_SysUpdate_MouseUp(void)
{
	appToUiDialogDisplaying_aboutSysUpdate(true);
}

void appToUiDialogDisplaying_aboutSysUpdate(bool bSign)
{
	setUpdateUI(false);
	setVisible(CONTROLID_SETUP_UPDATE_DIALOG, bSign);
	setVisible(CONTROLID_SETUP_UPDATE_DIALOG_TEXT, bSign);
	setVisible(CONTROLID_SETUP_UPDATE_DIALOG_OK, bSign);
	setVisible(CONTROLID_SETUP_UPDATE_DIALOG_CANCEL, bSign);
	setUpdateUI(true);

}

void appToSys_Setup_SysRestoreFactory_MouseUp()
{
    appToUiDialogDisplaying_aboutRestoreFactory(true);
}

void appToUiDialogDisplaying_aboutRestoreFactory(bool bSign)
{
	setUpdateUI(false);
	setVisible(CONTROLID_SETUP_SYSTEM_FACTORY_SETTINGS_BOX, bSign);
	setVisible(CONTROLID_SETUP_SYSTEM_FACTORY_SETTINGS_TEXT, bSign);
	setVisible(CONTROLID_SETUP_SYSTEM_FACTORY_SETTINGS_OK, bSign);
	setVisible(CONTROLID_SETUP_SYSTEM_FACTORY_SETTINGS_CANCEL, bSign);
	setUpdateUI(true);

}

void appToSys_Setup_SysRestoreFactoryOKOrCANCEL_MouseUp(u8 state)
{
    appToUiDialogDisplaying_aboutRestoreFactory(false);
    if(state == 0)
    systemToHal_FactorySetting();
}


void appToSys_Setup_SysUpdateDialogOKOrCANCEL_MouseUp(u8 state)
{
    appToUiDialogDisplaying_aboutSysUpdate(false);
	if(state == 0)
		systemToHal_SetSystemUpdate();
}

void appToSys_Setup_SysCarModulesOKOrCANCEL_MouseUp(u32 controlID)
{	
	DisplayingOrHidingSysCarModules(false);
	if(controlID == CONTROLID_SETUP_CAR_MODELS_DIALOG_OK){
		systemToModule_NotifyServiceModule_ChangeCarMode(1);
		systemToHal_SimulateKey(SYSTEMTOHAL_CARMODEL_OK);
	}
}

void appToSys_Setup_CarModelChoose_Up_MouseUp()
{
	systemToHal_SimulateKey(SYSTEMTOHAL_CARMODEL_INC);
}

void appToSys_Setup_CarModelChoose_Down_MouseUp()
{
	systemToHal_SimulateKey(SYSTEMTOHAL_CARMODEL_DEC);
}

void appToSys_Setup_CarModelChoose_OK_MouseUp()
{
	DisplayingOrHidingSysCarModules(true);
}


void appToSys_MatchingModulePageOkOrCancel_MouseUp(u32 ctrlId)
{
	systemToModule_NotifySystem_JumpPrePage();	
	LOGD("appToSys_MatchingModulePageOkOrCancel_MouseUp:ctrlId=0x%x",ctrlId);
	
	if(ctrlId == CONTROLID_MATCHING_MODELS_PAGE_OK)
	{
		LOGD("pLocalParam->cRealCarMode=%s,pLocalParam->cRealCarModeLen=%d",pLocalParam->cRealCarMode,pLocalParam->cRealCarModeLen);
		
		systemToHal_SetCarMode(pLocalParam->cRealCarMode,pLocalParam->cRealCarModeLen);
		systemToModule_NotifyServiceModule_ChangeCarMode(1);
		systemToHal_SimulateKey(SYSTEMTOHAL_SIMKEY_RESET);
	}
	else
	{
		LOGD("pLocalParam->cChoseeCarMode=%s,pLocalParam->cChoseeCarModeLen=%d",pLocalParam->cChoseeCarMode,pLocalParam->cChoseeCarModeLen);
		pLocalParam->bShowReviseCarModePage=false;
		systemToHal_SetCarMode(pLocalParam->cChoseeCarMode,pLocalParam->cChoseeCarModeLen);

		memset(pLocalParam->cRealCarMode, 0, sizeof(pLocalParam->cRealCarMode));
		memcpy(pLocalParam->cRealCarMode,pLocalParam->cChoseeCarMode,pLocalParam->cChoseeCarModeLen);
		pLocalParam->cRealCarModeLen = pLocalParam->cChoseeCarModeLen;
		
		systemToHal_SimulateKey(SYSTEMTOHAL_SIMKEY_RESET);
	}
}


/***************************************************************************/
void appToSys_SetLCD_MouseUp(u32 ctrlId,u8 *param,u8 paramLen)
{
	switch(ctrlId)
	{
		case CONTROLID_SETUP_BRIGHTNESS_DOWN:
			switch_Page(PAGE_SYSTEM_BRIGHTNESS_ADJUSTMENT);
			break;
		case CONTROLID_SETUP_BRIGHTNESS_DIM_UP:
		case CONTROLID_SETUP_BRIGHTNESS_DIM_DOWN:
			appToSys_Set_Brightness_Dim_UpOrDown(ctrlId);
			break;
		case CONTROLID_SETUP_BRIGHTNESS_MODERATE_UP:
		case CONTROLID_SETUP_BRIGHTNESS_MODERATE_DOWN:
			appToSys_Set_Brightness_Moderate_UpOrDown(ctrlId);
			break;
		case CONTROLID_SETUP_BRIGHTNESS_BRIGHT_UP:
		case CONTROLID_SETUP_BRIGHTNESS_BRIGHT_DOWN:
			appToSys_Set_Brightness_Bright_UpOrDown(ctrlId);
		break;
		case CONTROLID_SETUP_BRIGHTNESS_GUNDONDTIAO:
			appToSys_set_Brightness_scrolling(param,paramLen);
		break;
		case CONTROLID_SETUP_BRIGHTNESS_SET_BACK:
			anyModuleToSysModule_Switch_PrePage();	
		break;
		default:break;
	}
}

void appToSys_Set_Brightness_Dim_UpOrDown(u32 ctrlId)
{
	if(1 == pLocalParam->cBrightness_Dim)
	{
		if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_DIM_UP)
		{

			++pLocalParam->cBrightness_Dim;
		}
		else if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_DIM_DOWN)
		{
			pLocalParam->cBrightness_Dim = 33;
		}
	}
	else if(33== pLocalParam->cBrightness_Dim)
	{
		if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_DIM_UP)
		{

			pLocalParam->cBrightness_Dim = 1;
		}
		else if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_DIM_DOWN)
		{
			--pLocalParam->cBrightness_Dim;
		}
	}
	else if(pLocalParam->cBrightness_Dim>1 && pLocalParam->cBrightness_Dim<33)
	{
		if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_DIM_UP)
		{

			++pLocalParam->cBrightness_Dim;
		}
		else if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_DIM_DOWN)
		{
			--pLocalParam->cBrightness_Dim;
		}
	}

	//systemToHal_Set_LCDBrightness_Rank(pLocalParam->cBrightness_Dim);
	appToSys_Set_Brightness_Displaying(CONTROLID_SETUP_BRIGHTNESS_DIM_TEXT,pLocalParam->cBrightness_Dim);
}

void appToSys_Set_Brightness_Moderate_UpOrDown(u32 ctrlId)
{
	if(34 == pLocalParam->cBrightness_Moderate)
	{
		if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_MODERATE_UP)
		{

			++pLocalParam->cBrightness_Moderate;
		}
		else if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_MODERATE_DOWN)
		{
			pLocalParam->cBrightness_Moderate = 66;
		}
	}
	else if (66== pLocalParam->cBrightness_Moderate)
	{
		if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_MODERATE_UP)
		{
			pLocalParam->cBrightness_Moderate = 34;
		}
		else if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_MODERATE_DOWN)
		{
			--pLocalParam->cBrightness_Moderate;
		}
	}
	else if(pLocalParam->cBrightness_Moderate>34 && pLocalParam->cBrightness_Moderate<66)
	{
		if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_MODERATE_UP)
		{

			++pLocalParam->cBrightness_Moderate;
		}
		else if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_MODERATE_DOWN)
		{
			--pLocalParam->cBrightness_Moderate;
		}
	}

	//systemToHal_Set_LCDBrightness_Rank(pLocalParam->cBrightness_Moderate);
	appToSys_Set_Brightness_Displaying(CONTROLID_SETUP_BRIGHTNESS_MODERATE_TEXT,pLocalParam->cBrightness_Moderate);
}

void appToSys_Set_Brightness_Bright_UpOrDown(u32 ctrlId)
{

	if(67 == pLocalParam->cBrightness_Bright)
	{
		if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_BRIGHT_UP)
		{

			++pLocalParam->cBrightness_Bright;
		}
		else if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_BRIGHT_DOWN)
		{
			pLocalParam->cBrightness_Bright = 100;
		}
	}
	else if (100 == pLocalParam->cBrightness_Bright)
	{
		if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_BRIGHT_UP)
		{

			pLocalParam->cBrightness_Bright = 67;
		}
		else if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_BRIGHT_DOWN)
		{
			--pLocalParam->cBrightness_Bright;
		}
	}
	else if(pLocalParam->cBrightness_Bright>67 && pLocalParam->cBrightness_Bright<100)
	{
		if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_BRIGHT_UP)
		{

			++pLocalParam->cBrightness_Bright;
		}
		else if(ctrlId == CONTROLID_SETUP_BRIGHTNESS_BRIGHT_DOWN)
		{
			--pLocalParam->cBrightness_Bright;
		}
	}

	//systemToHal_Set_LCDBrightness_Rank(pLocalParam->cBrightness_Bright);
	appToSys_Set_Brightness_Displaying(CONTROLID_SETUP_BRIGHTNESS_BRIGHT_TEXT,pLocalParam->cBrightness_Bright);
}

void appToSys_set_Brightness_scrolling(u8 *param,u8 paramLen)
{
	int pos = 0;
	pos += (int)((param[0] << 24) & 0xFF000000);
	pos += (int)((param[1] << 16) & 0xFF0000);
	pos += (int)((param[2] << 8) & 0xFF00);
	pos += (int)(param[3] & 0xFF); 

	LOGD("******************** pos:%d",pos);
	systemToHal_Set_LCDBrightness_Rank(pos+1);
}

void appToUI_Set_Brightness(u8 param1,u8 param2)
{

	if(param2>=1 && param2<=100)
	{
		LOGD("****************** param2:%d",param2);
		setAnalogData(CONTROLID_SETUP_BRIGHTNESS_GUNDONDTIAO,param2-1);
	}


	if(param2 >= 1 && param2 < 34)
	{
		pLocalParam->u8_Sys_CurLcdLight=1;
		setScreenBrightnessCtrl(1);
	}
	else if(param2 >= 34 && param2 < 67)
	{
		pLocalParam->u8_Sys_CurLcdLight=2;
		setScreenBrightnessCtrl(2);
	}
	else if(param2 >= 67 && param2 <= 100)
	{
		pLocalParam->u8_Sys_CurLcdLight=3;
		setScreenBrightnessCtrl(3);
	}
	
}

void appToSys_Set_Brightness_Displaying(u32 CtrlID,u8 param)
{
	
	u8 ansiBuf[16];
	memset(ansiBuf, 0, 16);
	sprintf((char*)ansiBuf,"%d",param);
	int nAnsiBufLen = strlen((char*)ansiBuf);
	u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
	memset(unicodeBuf, 0, nAnsiBufLen*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicodeBuf);
	setSerialData(CtrlID,unicodeBuf,nUnicodeBufLen*2);
	free(unicodeBuf);
	
	/*
	u8 tmpbuffer[8];
	u8 buffer[16];
	u8 len = 0;
  	memset(tmpbuffer, 0x00, 8);
	memset(buffer, 0x00, 16);
		
	sprintf((char*)tmpbuffer, " %d%% ", param);
	len = strlen((char*)tmpbuffer);
	
	ansi_str_to_unicode16(tmpbuffer, (unicode16_t*)buffer);
	setSerialData(CtrlID, buffer,2*len);
	*/
	
}

/********************************************************/

//倒车模式
void clickSettingNormalPageBackCarMode(u8 p/*1 u, 0 d*/)
{
	int n = 2;
	int t = pLocalParam->m_eBackCarMode;
	t = (p == 1) ? ( (t + 1) % n ) : ((t + n - 1) % n);
	pLocalParam->m_eBackCarMode = (E_BACKCAR_MODE)t;

	LOGD("[%s] pLocalParam->m_eBackCarMode  = [%d]", __FUNCTION__, pLocalParam->m_eBackCarMode);
	//setToHalBackCarMode(t);
	switch(pLocalParam->m_eBackCarMode)
	{
	case BACKCAR_MODE_NORMAL:
		setStringText(CONTROLID_SYSTEM_TEXT_BACK_CAR, STRINGID_SYSTEM_BACKCAR_MODE_NORMAL);
		break;
	case BACKCAR_MODE_FAST:
		setStringText(CONTROLID_SYSTEM_TEXT_BACK_CAR, STRINGID_SYSTEM_BACKCAR_MODE_FAST);
		break;
	}
}


//Setup Steering Wheel
void appToSys_Setup_WheelChoose_Up_MouseUp(void)
{
	systemToHal_SimulateKey(SYSTEMTOHAL_SIMKEY_STEELWHEEL_INC);
}
void appToSys_Setup_WheelChoose_Down_MouseUp(void)
{
	systemToHal_SimulateKey(SYSTEMTOHAL_SIMKEY_STEELWHEEL_DEC);
}


void appToSys_Setup_WheelLearn_MouseUp(void)
{
	switch_Page(PAGE_SYSTEM_WHEEL_LEARNING);
}
void appToSys_Setup_WheelLearn_ON_MouseUp(void)
{
	systemToHal_SetUserWheelPanelData(SYSTEMTOHAL_CUSTOMSTEELPANEL_ON);
}
void appToSys_Setup_WheelLearn_OFF_MouseUp(void)
{
	systemToHal_SetUserWheelPanelData(SYSTEMTOHAL_CUSTOMSTEELPANEL_OFF);
}
	
//-------------------2012-2-29------------------------------
void appToSys_Setup_WheelLearn_Mode(void)
{
    LOGD("appToSys_Setup_WheelLearn_Mode-pLocalParam->m_cCurClearKey:0x%x",pLocalParam->m_cCurClearKey);
	if(pLocalParam->b_Sys_WaitStudy&&pLocalParam->m_emClearKey == emClear_Mode)
		{
         SystemTohal_CancelWheelStudy ();
		}
	else if(pLocalParam->m_cCurClearKey == 0xFF)
		{
	        SystemTohal_StudyWheelData(0x00);
	    }
	else
	{
		pLocalParam->m_cCurClearKey = 0xFF;

	}
}


void appToSys_Setup_WheelLearn_Mute(void){
	if(pLocalParam->b_Sys_WaitStudy&&pLocalParam->m_emClearKey ==emClear_Mute){
     SystemTohal_CancelWheelStudy ();
		}else if(pLocalParam->m_cCurClearKey == 0xFF){
		 SystemTohal_StudyWheelData(0X03);
	}else{
		pLocalParam->m_cCurClearKey = 0xFF;
	}

}
void appToSys_Setup_WheelLearn_Seek_inc(void){
	if(pLocalParam->b_Sys_WaitStudy&&pLocalParam->m_emClearKey ==emClear_Seek_INC){
		 SystemTohal_CancelWheelStudy ();
			}else if(pLocalParam->m_cCurClearKey == 0xFF){
			 SystemTohal_StudyWheelData(0X01);
		}else{
			pLocalParam->m_cCurClearKey = 0xFF;
		}

}
void appToSys_Setup_WheelLearn_Seek_dec(void){
	if(pLocalParam->b_Sys_WaitStudy&&pLocalParam->m_emClearKey ==emClear_Seek_DEC){
		 SystemTohal_CancelWheelStudy ();
			}else if(pLocalParam->m_cCurClearKey == 0xFF){
			 SystemTohal_StudyWheelData(0X02);
		}else{
			pLocalParam->m_cCurClearKey = 0xFF;
		}

}			
void appToSys_Setup_WheelLearn_vol_inc(void){
	
	if(pLocalParam->b_Sys_WaitStudy&&pLocalParam->m_emClearKey ==emClear_Vol_INC ){
		 SystemTohal_CancelWheelStudy ();
			}else if(pLocalParam->m_cCurClearKey == 0xFF){
			 SystemTohal_StudyWheelData(0x04);
		}else{
			pLocalParam->m_cCurClearKey = 0xFF;
		}

}
void appToSys_Setup_WheelLearn_vol_dec(void){
	if(pLocalParam->b_Sys_WaitStudy&&pLocalParam->m_emClearKey ==emClear_Vol_DEC ){
     SystemTohal_CancelWheelStudy ();
		}else if(pLocalParam->m_cCurClearKey == 0xFF){
		 SystemTohal_StudyWheelData(0x05);
	}else{
		pLocalParam->m_cCurClearKey = 0xFF;
	}
}
void appToSys_Setup_WheelLearn_bt_hand_up(void)
{
   if(pLocalParam->b_Sys_WaitStudy&&pLocalParam->m_emClearKey ==emClear_bt_handup){
     SystemTohal_CancelWheelStudy ();
		}else if(pLocalParam->m_cCurClearKey == 0xFF){
		 SystemTohal_StudyWheelData(0x07);
	}else{
		pLocalParam->m_cCurClearKey = 0xFF;
	}
}
void appToSys_Setup_WheelLearn_bt_call_in(void)
{
   LOGD("appToSys_Setup_WheelLearn_bt_call_in-pLocalParam->m_cCurClearKey:0x%x",pLocalParam->m_cCurClearKey);
   if(pLocalParam->b_Sys_WaitStudy&&pLocalParam->m_emClearKey ==emClear_bt_callin)
   	{
     SystemTohal_CancelWheelStudy ();
    }
   else if(pLocalParam->m_cCurClearKey == 0xFF)
    {
	 SystemTohal_StudyWheelData(0x06);
	}
   else
	{
		pLocalParam->m_cCurClearKey = 0xFF;
	}
}

void appToSys_Setup_WheelLearn_Apply(void){
	if(0x01==pLocalParam->u8_Sys_UserSteeringWheel)
		{
			switch_Page(PAGE_SETUP_BEGIN+4);
		}
	else
		{
		   systemToHal_SetUserWheelPanelData(0x01);
		  switch_Page(PAGE_SETUP_BEGIN+4);
		}
}
void appToSys_Setup_WheelLearn_Back(void)
{
	anyModuleToSysModule_Switch_PrePage();
}

void appToSys_Setup_WheelLearn_Delete(void)
{
      LOGD("appToSys_Setup_WheelLearn_Delete");
      systemToHal_ClearWheelPanelData(0x00);
	  systemToHal_ClearWheelPanelData(0x01);
	  systemToHal_ClearWheelPanelData(0x02);
	  systemToHal_ClearWheelPanelData(0x03);
	  systemToHal_ClearWheelPanelData(0x04);
	  systemToHal_ClearWheelPanelData(0x05);
	  systemToHal_ClearWheelPanelData(0x06);
	  systemToHal_ClearWheelPanelData(0x07);
}


void apptoSys_hadleDown(u32 ctrlId,u8 u8_MouseStatus,u8 *param,u8 paramLen)

{
    switch(ctrlId)
    	{
    	    case CONTROLID_SYSTEM_WHEEL_LEARNING_MODE:
			case CONTROLID_SYSTEM_WHEEL_LEARNING_MUTE:
			case CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_DEC:
			case CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_INC:
			case CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_DEC:
			case CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_INC:
			case CONTROLID_SYSTEM_WHEEL_LEARNING_BT_HAND_UP:
			case CONTROLID_SYSTEM_WHEEL_LEARNING_BT_CALL_IN:
				appToSys_handleWheel_CtrlDown(ctrlId);
				break;
			case CONTROLID_SETUP_BRIGHTNESS_GUNDONDTIAO:
				appToSys_SetLCD_MouseUp(ctrlId,param,paramLen);
				break;
			/*
			case CONTROLID_SETUP_DVR_AMBIENT_LED_R_SCROLL_BAR:
			case CONTROLID_SETUP_DVR_AMBIENT_LED_G_SCROLL_BAR:
			case CONTROLID_SETUP_DVR_AMBIENT_LED_B_SCROLL_BAR:
			{
				LOGD("appToSys_handledown --ctrlId:%x-- param[0]: %d    param[1]: %d param[2]: %d param[3]: %d",ctrlId,param[0],param[1],param[2],param[3]);
				setR_G_B_BarValue(param[3],ctrlId - CONTROLID_SETUP_DVR_AMBIENT_LED_R_SCROLL_BAR);
			}
			break;
			case CONTROLID_SETUP_DVR_AMBIENT_LED_DIMMING_SCROLL_BAR:
			{
				LOGD("appToSys_handledown --ctrlId:%x-- param[0]: %d    param[1]: %d param[2]: %d param[3]: %d",ctrlId,param[0],param[1],param[2],param[3]);
				systemToHalAboutAmbientLed_Dimming(param[3]);
			}
			break;
			*/
			//MULTI CONTOURED SEATS ADJUST	0x2073
			case CONTROLID_MULTI_CONTOURED_SEATS_JUMP_PAGE_BUTTON:
				appToSys_Setup_MCS_Main_JumpPage_Touch_Screen(0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_BUTTON:
				appToSys_Setup_MCS_Adjust_JumpPage_Touch_Screen(0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_SCROLL_BAR:
				appToSys_Setup_MCS_Adjust_UpperLumbarPre_SCROLL_BAR_Touch_Screen(0x00);
			break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_DEC:
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_INC:
				appToSys_Setup_MCS_Adjust_UpperLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_DEC,0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_SCROLL_BAR:
				appToSys_Setup_MCS_Adjust_MidLumbarPre_SCROLL_BAR_Touch_Screen(0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_DEC:
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_INC:
				appToSys_Setup_MCS_Adjust_MidLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_DEC,0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_SCROLL_BAR:
				appToSys_Setup_MCS_Adjust_LowerLumbarPre_SCROLL_BAR_Touch_Screen(0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_DEC:
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_INC:
				appToSys_Setup_MCS_Adjust_LowerLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_DEC,0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_SCROLL_BAR:
				appToSys_Setup_MCS_Adjust_UpperBolsterPre_SCROLL_BAR_Touch_Screen(0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_DEC:
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_INC:
				appToSys_Setup_MCS_Adjust_UpperBolsterPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_DEC,0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_SCROLL_BAR:
				appToSys_Setup_MCS_Adjust_LowerBolsterPre_SCROLL_BAR_Touch_Screen(0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_DEC:
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_INC:
				appToSys_Setup_MCS_Adjust_LowerBolsterPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_DEC,0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_BUTTON:
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_STATE_ICON:
				appToSys_Setup_MCS_Adjust_DriverSide_Touch_Screen(0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_BUTTON:
			case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_STATE_ICON:
				appToSys_Setup_MCS_Adjust_PassengerSide_Touch_Screen(0x00);
				break;
			//MULTI CONTOURED SEATS MASSAGE		0x2074
			case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_BUTTON:
				appToSys_Setup_MCS_Passage_JumpPage_Touch_Screen(0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_CLOSE:
			case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_LOW:	
			case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_HIGH:
				appToSys_Setup_MCS_Passage_UpperLumbarSet_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_CLOSE,0x00);
				break;	
			case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_CLOSE:	
			case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_LOW:	
			case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_HIGH:
				appToSys_Setup_MCS_Passage_LowerLumbarSet_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_CLOSE,0x00);
				break;
			case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_BUTTON:
			case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_STATE_ICON:
				appToSys_Setup_MCS_Passage_DriverSide_Touch_Screen(0x00);
				break;			
			case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_BUTTON:	
			case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_STATE_ICON:
				appToSys_Setup_MCS_Passage_PassengerSide_Touch_Screen(0x00);
				break;
		   default:
				break;
    	}
}
void appTosys_handleResetSystem(u32 ctrlId)
{
      
      
}
void appTosys_handleSwitchPage(u32 ctrlId)
{
      
      
}
void appToSys_handleWheel_CtrlDown(u32 CtrlId)
{

   switch(CtrlId)
   	{
   	   case CONTROLID_SYSTEM_WHEEL_LEARNING_MODE:
	   	    pLocalParam->m_emClearKey=emClear_Mode;
	   	    setAnalogData(CONTROLID_SYSTEM_WHEEL_LEARNING_MODE,1);
			break;
	   case CONTROLID_SYSTEM_WHEEL_LEARNING_MUTE:
	   	    pLocalParam->m_emClearKey=emClear_Mute;
	   	    setAnalogData(CONTROLID_SYSTEM_WHEEL_LEARNING_MUTE,1);
			break;
	   case CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_DEC:
	   	    pLocalParam->m_emClearKey=emClear_Seek_DEC;
	   	    setAnalogData(CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_DEC,1);
			break;
	   case CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_INC:
	   	    pLocalParam->m_emClearKey=emClear_Seek_INC;
	   	    setAnalogData(CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_INC,1);
			break;
	   case CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_DEC:
	   	    pLocalParam->m_emClearKey=emClear_Vol_DEC;
	   	    setAnalogData(CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_DEC,1);
			break;
	   case CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_INC:
	   	    pLocalParam->m_emClearKey=emClear_Vol_INC;
	   	    setAnalogData(CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_INC,1);
			break;
	   case CONTROLID_SYSTEM_WHEEL_LEARNING_BT_HAND_UP:
	   	    pLocalParam->m_emClearKey=emClear_bt_handup;
	   	    setAnalogData(CONTROLID_SYSTEM_WHEEL_LEARNING_BT_HAND_UP,1);
			break;
	   case CONTROLID_SYSTEM_WHEEL_LEARNING_BT_CALL_IN:
	   	    pLocalParam->m_emClearKey=emClear_bt_callin;
	   	    setAnalogData(CONTROLID_SYSTEM_WHEEL_LEARNING_BT_CALL_IN,1);
			break;
	 default:
		   	break;
   	}
   LOGD("appToSys_handleWheel_CtrlDown ctrlID:0x%x,m_emClearKey:0x%x\n",CtrlId,pLocalParam->m_emClearKey);
}
void appToSys_handleWheel_CtrlUp(u32 ctrlId)
{
  
   LOGD("appToSys_handleWheel_CtrlUp ctrlID:0x%x,m_emClearKey:0x%x\n",ctrlId,pLocalParam->m_emClearKey);
   
    pLocalParam->m_cCurClearKey=0xFF;
	switch(ctrlId)
		{
	case CONTROLID_SYSTEM_WHEEL_LEARNING_MODE:                                      
         appToSys_Setup_WheelLearn_Mode();
	     break;
    case CONTROLID_SYSTEM_WHEEL_LEARNING_MUTE:
         appToSys_Setup_WheelLearn_Mute();
	     break;
    case CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_INC:
         appToSys_Setup_WheelLearn_Seek_inc();
	     break;
	case CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_DEC:
		appToSys_Setup_WheelLearn_Seek_dec();
		 break;
	case CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_INC:
		appToSys_Setup_WheelLearn_vol_inc();
 		break;
 	case CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_DEC:
		appToSys_Setup_WheelLearn_vol_dec();
		break;
	case CONTROLID_SYSTEM_WHEEL_LEARNING_BT_HAND_UP:
		appToSys_Setup_WheelLearn_bt_hand_up();
		break;
	case CONTROLID_SYSTEM_WHEEL_LEARNING_BT_CALL_IN:
		appToSys_Setup_WheelLearn_bt_call_in();
		break;
    default:
		break;
		}
}
void appToSys_handleUp(u32 ctrlId,u8 u8_MouseStatus,u8 *param,u8 paramLen)
{
   LOGD("appToSys_handleUp----0x%x u8_MouseStatus:0x%x",ctrlId,u8_MouseStatus);
   LOGD("pLocalParam->b_enable_ipol:0x%x",pLocalParam->b_enable_ipol);
   LOGD("pLocalParam->b_enable_tv:0x%x",pLocalParam->b_enable_tv);
   LOGD("pLocalParam->CarName:%s",pLocalParam->CarName);

	if(ctrlId > CONTROLID_SELECTION_CAR_TYPE_START && ctrlId < CONTROLID_SELECTION_CAR_TYPE_LAST_ONE)
	{
		analyseSelectionCarTypeMessage(ctrlId - CONTROLID_SELECTION_CAR_TYPE_START);
		return;
	}
    switch(ctrlId)
    	{
		
		case CONTROLID_SETUP_JUMPPAGE_ONE:
		case CONTROLID_SETUP_JUMPPAGE_TWO:
		case CONTROLID_SETUP_JUMPPAGE_THREE:
		case CONTROLID_SETUP_JUMPPAGE_FOUR:
		case CONTROLID_SETUP_JUMPPAGE_FIVE:
			appToSys_Setup_MouseUp(ctrlId);
			break;
		case CONTROLID_SETUP_BACK:
			appToSys_Setup_Back_MouseUp();
			break;


		//PAGE1
    	/*   ������Ƶ*/
    	//case CONTROLID_SETUP_BACK_VIDEO_ON:
		//	if(u8_MouseStatus == SYS_SETUP_ON)
		//	{
		//		appToSys_Setup_BackCarCamaera_ON_MouseUp();
		//	}
		//	else
		//	{
		//	
		//		appToSys_Setup_BackCarCamaera_OFF_MouseUp();
		//	}
		//	break;

        case CONTROLID_SETUP_BACK_VIDEO_ON:
            if(u8_MouseStatus == SYS_SETUP_ON)
            {
                UiDisplay_System_BackCarVideoSwitch(1);
            }
            else
            {
                    
                UiDisplay_System_BackCarVideoSwitch(0);
            }
            break;

        case CONTROLID_SETUP_BACKVIDEO_REFLINEDISPALY_SET:
            if(u8_MouseStatus == SYS_SETUP_ON)
            {
                	appToSys_Setup_BackCarRefLineDisplay_IS_MouseUp();
            }
            else
            {
                	appToSys_Setup_BackCarRefLineDisplay_NO_MouseUp();
            }
        break;
		case CONTROLID_SETUP_BACK_CAR_SHOW_OR_HIDE:
			appToSys_Setup_BackCarRefLineDisplaySwitch_MouseUp();
		break;
		case CONTROLID_SETUP_BACKVIDEO_TRACE_LINE_DISPALY_SET:
			  if(u8_MouseStatus == SYS_SETUP_ON)
            {
                appToSys_Setup_BackCarTraceLineDisplay_IS_MouseUp();
            }
            else
            {
            
                appToSys_Setup_BackCarTraceLineDisplay_NO_MouseUp();
            }
			break;
		/*  ��尴�������*/
		case CONTROLID_SETUP_PANEL_LIGHT_UP:
			appToSys_Setup_PanelLight_Up_MouseUp();
			break;
		case CONTROLID_SETUP_PANEL_LIGHT_DOWN:
			appToSys_Setup_PanelLight_Down_MouseUp();
			break;
		case CONTROLID_SETUP_DVR_PROTOCOL_MODE_UP:
		case CONTROLID_SETUP_DVR_PROTOCOL_MODE_DOWN:
			appToSys_Setup_Dvr_set_protocol_mode();
			break;

		/*��������*/
		case CONTROLID_SETUP_POWER_VOL_UP:
			appToSys_Setup_PowerVol_Up_MouseUp();
			break;
		case CONTROLID_SETUP_POWER_VOL_DOWN:
			appToSys_Setup_PowerVol_Down_MouseUp();
			break;
		/*����ɢ�ȷ��ȿ���*/
		case CONTROLID_SETUP_SMART_FAN_DOWN:
			appToSys_Setup_System_Fan_Down();
			break;
		case CONTROLID_SETUP_SMART_FAN_UP:
			appToSys_Setup_System_Fan_Up();
			break;
		/*�����ƿ����*/
		case CONTROLID_SETUP_VOLTAGE_PROTECTION_UP:
			appToSys_Setup_System_VoltageProtection_Up();
			break;
		case CONTROLID_SETUP_VOLTAGE_PROTECTION_DOWN:
			appTSys_Setup_System_VoltageProtection_Down();
			break;
        case CONTROLID_SYSTEM_BTN_BACK_CAR_UP:
             clickSettingNormalPageBackCarMode(1);
             break;
        case CONTROLID_SYSTEM_BTN_BACK_CAR_DOWN:
             clickSettingNormalPageBackCarMode(0);
             break;
		//zhq add setup backcar trigger
		case CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_UP:
		case CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_DOWN:
			 appToSys_Setup_Backcar_TriggerType_UpOrDownSwitch(ctrlId - CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_UP);
			 break;

		//PAGE 2 
		/*DVD����*/
		case CONTROLID_SETUP_DVD_REGION_SET_UP:	
			appToSys_Setup_DvdRegionCode_Up_MouseUp();
			break;
		case CONTROLID_SETUP_DVD_REGION_SET_DOWN:
			appToSys_Setup_DvdRegionCode_Down_MouseUp();
			break;
		/*���������*/
		case CONTROLID_SETUP_MULTINATIONAL_RADIO_UP:
			appToSys_Setup_MultiRadio_Down_MouseUp();
			break;
		case CONTROLID_SETUP_MULTINATIONAL_RADIO_DOWN:
			appToSys_Setup_MultiRadio_Up_MouseUp();
			break;
		/*������Ϣ����������ʾ*/
		case CONTROLID_SETUP_CARINFO_AUDIO_CUE_ON_OFF:
			if(u8_MouseStatus == SYS_SETUP_ON)
			{
		
				appToSys_Setup_CarinfoAudioCueON();
			}
			else
			{
				appToSys_Setup_CarinfoAudioCueOFF();
			}
			break;
		//PAGE 3
		//PAGE4
		/*�Զ�ת������Ϣ����*/
		case CONTROLID_SETUP_AUTO_INFOGPS_ON:
			if(u8_MouseStatus == SYS_SETUP_ON)
			{
				appToSys_Setup_AutoGPS_ON_MouseUp();
			}
			else
			{
				appToSys_Setup_AutoGPS_OFF_MouseUp();
			}
			break;
		/*GPS������ʾ*/
		case CONTROLID_SETUP_GPS_VOICE_PROMPT_ON:
		if(u8_MouseStatus == SYS_SETUP_ON)
		{
			appToSys_Setup_GPSVoicePrompt_ON_MouseUp();
		}
		else
		{
			appToSys_Setup_GPSVoicePrompt_OFF_MouseUp();
		}
		break;
		/*Ĭ�ϵ������*/
		case CONTROLID_SETUP_DEFAULT_NAVIGATION_UP:
		case CONTROLID_SETUP_DEFAULT_NAVIGATION_DOWN:
			appToSys_Setup_Default_NaviGation(ctrlId-CONTROLID_SETUP_DEFAULT_NAVIGATION_UP);
			break;
		case CONTROLID_SETUP_DYNAMIC_LOGO_STYLE_UP:
		case CONTROLID_SETUP_DYNAMIC_LOGO_STYLE_DOWN:
			appToSys_Setup_DynamicLogoStyle(ctrlId - CONTROLID_SETUP_DYNAMIC_LOGO_STYLE_UP);
			break;



		//PAGE 5
		/*������ѡ��*/
		case CONTROLID_SETUP_WHEEL_CHOOSE_UP:
			appToSys_Setup_WheelChoose_Up_MouseUp();
			break;
		case CONTROLID_SETUP_WHEEL_CHOOSE_DOWM:
			appToSys_Setup_WheelChoose_Down_MouseUp();
			break;
		/*������ѧϰ*/
		case CONTROLID_SETUP_WHEEL_LEARNING:
			appToSys_Setup_WheelLearn_MouseUp();
			break;
		case CONTROLID_SETUP_WHEEL_LEARNING_ON_OFF:
			{
				LOGD("u8_MouseStatus---0x%x",u8_MouseStatus);
				if(u8_MouseStatus==SYS_SETUP_ON)
				{
					systemToHal_SetUserWheelPanelData(0x01);
				}
				else
				{
					systemToHal_SetUserWheelPanelData(0x00);
				}
			}
		    break;
		case CONTROLID_SYSTEM_WHEEL_LEARNING_MODE:
	    case CONTROLID_SYSTEM_WHEEL_LEARNING_MUTE:
		case CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_INC:
		case CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_DEC:
		case CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_INC:
		case CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_DEC:
		case CONTROLID_SYSTEM_WHEEL_LEARNING_BT_HAND_UP:
		case CONTROLID_SYSTEM_WHEEL_LEARNING_BT_CALL_IN:
			 appToSys_handleWheel_CtrlUp(ctrlId);
			 break;
		case CONTROLID_SYSTEM_WHEEL_LEARNING_APPLY:
			appToSys_Setup_WheelLearn_Apply();
		    break;
        case CONTROLID_SYSTEM_WHEEL_LEARNING_DELETE:
            appToSys_Setup_WheelLearn_Delete();
		    break;
	    case CONTROLID_SYSTEM_WHEEL_LEARNING_BACK:
			appToSys_Setup_WheelLearn_Back();
			break;
		/*����*/
		case CONTROLID_SETUP_CAR__MODEL_UP:
			appToSys_Setup_CarModelChoose_Up_MouseUp();
			break;
		case CONTROLID_SETUP_CAR__MODEL_DOWN:
			appToSys_Setup_CarModelChoose_Down_MouseUp();
			break;
		case CONTROLID_SETUP_CAR__MODEL_OK:
			appToSys_Setup_CarModelChoose_OK_MouseUp();
			break;
		case CONTROLID_SETUP_CAR_MODELS_DIALOG_OK:
		case CONTROLID_SETUP_CAR_MODELS_DIALOG_CANCEL:
			appToSys_Setup_SysCarModulesOKOrCANCEL_MouseUp(ctrlId);
			break;
		/*ϵͳ��λ*/
		case CONTROLID_SETUP_SYSTEM_RESET:
			if(pLocalParam->b_Timer)
				return;
			LOGD("---SYSTEM RESET DIALOG =%d",pLocalParam->bShowSystemDialog);
			if(!pLocalParam->bShowSystemDialog)return;
			appToSys_Setup_SysReset_MouseUp();
			pLocalParam->bShowSystemDialog=false;
			break;
		case CONTROLID_SETUP_RESTART_DIALOG_OK:
		case CONTROLID_SETUP_RESTART_DIALOG_CANCEL:
			pLocalParam->bShowSystemDialog=true;
			appToSys_Setup_SysResetDialogOKOrCANCEL_MouseUp(ctrlId-CONTROLID_SETUP_RESTART_DIALOG_OK);
			break;
		/*ϵͳ��*/
		case CONTROLID_SETUP_SYSTEM_UPDATE:
			if(!pLocalParam->bShowSystemDialog)return;
			appToSys_Setup_SysUpdate_MouseUp();
			pLocalParam->bShowSystemDialog=false;
			break;
		case CONTROLID_SETUP_UPDATE_DIALOG_OK:
		case CONTROLID_SETUP_UPDATE_DIALOG_CANCEL:
			pLocalParam->bShowSystemDialog=true;
			appToSys_Setup_SysUpdateDialogOKOrCANCEL_MouseUp(ctrlId-CONTROLID_SETUP_UPDATE_DIALOG_OK);
			break;
		case CONTROLID_SETUP_SYSTEM_FACTORY_SETTINGS_BUTTON:
			if(!pLocalParam->bShowSystemDialog)return;
		    appToSys_Setup_SysRestoreFactory_MouseUp();
		    pLocalParam->bShowSystemDialog=false;
		    break;
        case CONTROLID_SETUP_SYSTEM_FACTORY_SETTINGS_OK:
        case CONTROLID_SETUP_SYSTEM_FACTORY_SETTINGS_CANCEL:
        	   pLocalParam->bShowSystemDialog=true;
            appToSys_Setup_SysRestoreFactoryOKOrCANCEL_MouseUp(ctrlId-CONTROLID_SETUP_SYSTEM_FACTORY_SETTINGS_OK);
            break;
		/*��Ϣ*/
		case CONTROLID_SETUP_SYSTEM_COPYRIGHT:
			if(!pLocalParam->bShowSystemDialog)return;
			appToSys_Setup_Info_MouseUp();
			break;
		case CONTROLID_COPYRIGHT:
			appToSys_Copyright_MouseUp();
			break;
		case CONTROLID_COPYRIGHT_BACK:
			appToSys_Copyright_Back_MouseUp();
			break;
			



	 
	   //\BD\F8\C8\EB\C9\E8\D6\C3ҳ\B0\B4ť
	    case CONTROLID_MENU_SETTING:
		     appToSys_Menu_SetUp_MouseUp();
		     break;
	    case CONTROLID_MENU_STYLE:
		     appToSys_Menu_Style_MouseUp();
		     break;	
	    case CONTROLID_MENU_OFF:
		     appToSys_Menu_Off_MouseUp();
		     break;
        case CONTROLID_MENU_DARK:
		     appToSys_Menu_Dark_MouseUp();
	         break;
		case CONTROLID_MENU_MIDDLE:
		     appToSys_Menu_Middle_MouseUp();
		     break;
	    case CONTROLID_MENU_LIGHT:
		     appToSys_Menu_Light_MouseUp();
		     break;
		case CONTROLID_MENU_HIGH_LIGHT:
		     appToSys_Menu_High_Light_MouseUp();
		     break;
		case CONTROLID_MENU_DAYNIGHT:
		     appToSys_Menu_NightDay_MouseUp(u8_MouseStatus);
			 break;
		case CONTROLID_SETUP_AUDIO_AUTO_SOUND_ON_OFF:
			if(u8_MouseStatus == SYS_SETUP_ON)
			{
				appToSys_Setup_AUDIO_AUTO_SOUND_ON_MouseUp();
			}
			else
			{
				appToSys_Setup_AUDIO_AUTO_SOUND_OFF_MouseUp();
			}
			break;
		case CONTROLID_SETUP_LIGHT_LINE_CHECK_ON:
			if(u8_MouseStatus == SYS_SETUP_ON)
			{
				appToSys_Setup_LightDetect_ON_MouseUp();
			}
			else
			{
				appToSys_Setup_LightDetect_OFF_MouseUp();
			}
			break;
		case CONTROLID_SETUP_BRAKE_LINE_CHECK_ON:
			if(u8_MouseStatus == SYS_SETUP_ON)
			{
				appToSys_Setup_BrakeCarDetect_ON_MouseUp();	
			}
			else
			{
				appToSys_Setup_BrakeCarDetect_OFF_MouseUp();
			}
			break;
			//\B9\A6\B7ŷŴ\F3\C6\F7
		case CONTROLID_SETUP_POWER_AMPLIFIER_ON:
			if(u8_MouseStatus == SYS_SETUP_ON)
			{
				appToSys_Setup_Amplifier_ON_MouseUp();
			}
			else
			{
				appToSys_Setup_Amplifier_OFF_MouseUp();
			}
			break;
			//\C3\E6\B0尴\BC\FC\B5\C6\C1\C1\B6\C8

		//Setup MutiMedia
		
		case CONTROLID_SETUP_IPOD_SET_ON:
			if(pLocalParam->b_enable_ipol== SYS_SETUP_ON)
			{
				appToSys_Setup_IpodSet_ON_MouseUp();
				pLocalParam->b_enable_ipol=0;
				pLocalParam->b_enable_tv=1;
			}
			else
			{
				appToSys_Setup_IpodSet_OFF_MouseUp();
				pLocalParam->b_enable_ipol=1;
				pLocalParam->b_enable_tv=0;
			}
			break;

		case CONTROLID_SETUP_TV_SET_ON:
			if(pLocalParam->b_enable_tv== SYS_SETUP_ON)
			{
				appToSys_Setup_TVSet_ON_MouseUp();
				pLocalParam->b_enable_tv=0;
				pLocalParam->b_enable_ipol=1;
			}
			else
			{
				appToSys_Setup_TVSet_OFF_MouseUp();
				pLocalParam->b_enable_tv=1;
				pLocalParam->b_enable_ipol=0;
			}
			break;
 		
		case CONTROLID_SETUP_TV_DVR_SWITCH_ON:
			if(pLocalParam->uDvrTvTpmsVisible!=0)
			appToSys_Setup_TvOrDvrSwitchON_MouseUp();
			break;
		case CONTROLID_SETUP_TV_DVR_SWITCH_OFF:
			appToSys_Setup_TvOrDvrSwitchOFF_MouseUp();
			break;
        case CONTROLID_SETUP_TV_DVR_TPMS_SWITCH_UP:
        case CONTROLID_SETUP_TV_DVR_TPMS_SWITCH_DOWN:
                appToSys_Setup_TV_DVR_TPMS_UpOrDownSwitch(ctrlId - CONTROLID_SETUP_TV_DVR_TPMS_SWITCH_UP);
            break;
		 case CONTROLID_SETUP_TPMS_RGB_SWITCH_UP:
		 case CONTROLID_SETUP_TPMS_RGB_SWITCH_DOWN:
		 	appToSys_Setup_TV_DVR_TPMS_UpOrDownSwitch(ctrlId - CONTROLID_SETUP_TPMS_RGB_SWITCH_UP);
			break;

		case CONTROLID_MATCHING_MODELS_PAGE_OK:
		case CONTROLID_MATCHING_MODELS_PAGE_CANCEL:
			appToSys_MatchingModulePageOkOrCancel_MouseUp(ctrlId);
			break;
		/*����ҳ���ȵ���*/
		case CONTROLID_SETUP_BRIGHTNESS_DOWN:
		case CONTROLID_SETUP_BRIGHTNESS_DIM_UP:
		case CONTROLID_SETUP_BRIGHTNESS_DIM_DOWN:
		case CONTROLID_SETUP_BRIGHTNESS_MODERATE_UP:
		case CONTROLID_SETUP_BRIGHTNESS_MODERATE_DOWN:
		case CONTROLID_SETUP_BRIGHTNESS_BRIGHT_UP:
		case CONTROLID_SETUP_BRIGHTNESS_BRIGHT_DOWN:
		case CONTROLID_SETUP_BRIGHTNESS_SET_BACK:
			appToSys_SetLCD_MouseUp(ctrlId,param,paramLen);
			break;
        case CONTROLID_SETUP_GPS_FUNCTION_NAV_UP:
        case CONTROLID_SETUP_GPS_FUNCTION_NAV_DOWN:
            appToSys_Setup_GPS_BOOT_RUN_UpOrDownSwitch(ctrlId - CONTROLID_SETUP_GPS_FUNCTION_NAV_UP);
        break;
        case CONTROLID_SYSTEM_BACKVIDEO_REFLINE_SWITHCPAGE_BACK:
            systemToModule_NotifySystem_JumpPrePage();
        break;
        case CONTROLID_SETUP_BOOTON_ISAUTOPLAY:
            if(u8_MouseStatus == SYS_SETUP_ON)
			{
				appToSys_Setup_BootOn_IsAutoPlay_ON_MouseUp();
			}
			else
			{
			
				appToSys_Setup_BootOn_IsAutoPlay_OFF_MouseUp();
			}
        break;
		case CONTROLID_SETUP_FUNCTION_UP:
				appToSys_Setup_PrevPage_MouseUp();
		break;
		case CONTROLID_SETUP_FUNCTION_DOWN:
				appToSys_Setup_NextPage_MouseUp();
		break;
		case CONTROLID_SYSTEM_SETUP_AUTOMATE_SWITCH_TO_DVR:
			if(u8_MouseStatus == SYS_SETUP_ON)
			{
				appToSys_Setup_IsAutoMate_ON_MouseUp();
			}
			else
			{
			
				appToSys_Setup_IsAutoMate_OFF_MouseUp();
			}
		break;
		case CONTROLID_SYSTEM_SETUP_AUTOMATE_SWITCH_TO_DVR_BACK:
			systemToModule_NotifySystem_JumpPrePage();
		break;
		// setting system
		case CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_UP:
		case CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_DOWN:
			appToSys_Setup_BackCar_CVBS_Or_USB_MouseUp(ctrlId - CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_UP);
		break;
		case CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_OK:
			appToSys_Setup_BackCar_CVBS_Or_USB_OK_MouseUp();
		break;
		case CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_PROMPT_SURE:
		case CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_PROMPT_CANCEL:
			appToSys_Setup_SysBACKCAR_SET_CVBS_OR_USB_PROMPT_OKOrCANCEL_MouseUp(ctrlId - CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_PROMPT_SURE);
		break;
		case CONTROLID_SETUP_NAVI_MIX_LOW_SWITCH:
		if(u8_MouseStatus == SYS_SETUP_ON)
		{
			appToSys_Setup_NaviMixLow_ON_MouseUp();
		}
		else
		{
			appToSys_Setup_NaviMixLow_OFF_MouseUp();
		}
		break;
		//AMBIENT_LED
		case CONTROLID_SETUP_DVR_AMBIENT_LED_MAIN:
			appToSys_AmbientLed_SetUp_MouseUp();
		break;
		case CONTROLID_SETUP_DVR_AMBIENT_LED_MAIN_BACK:
			appToSys_AmbientLed_Back_MouseUp();
		break;		
		case CONTROLID_SETUP_DVR_AMBIENT_LED_SWITCH:
			appToSys_AmbientLed_Switch_MouseUp();
		break;
		//Commission
		case CONTROLID_SETUP_DVR_AMBIENT_LED_WARM_RED:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_HAPPY_ORANGE:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_LIVELY_YELLOW:	
		case CONTROLID_SETUP_DVR_AMBIENT_LED_FRESH_GREEN:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_WORRY_BLUE:	
		case CONTROLID_SETUP_DVR_AMBIENT_LED_MYSTERIOUS_PURPLE:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_ACACIA_RED:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_ROMANTIC_PINK:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_FRESH_BLUE:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_PURE_WHITE:
			appToSys_AmbientLed_Commission_MouseUp(ctrlId - CONTROLID_SETUP_DVR_AMBIENT_LED_WARM_RED);
		break;		
		//R
		case CONTROLID_SETUP_DVR_AMBIENT_LED_R_DEC:	
		case CONTROLID_SETUP_DVR_AMBIENT_LED_R_INC:
			appToSys_AmbientLed_R_MouseUp(ctrlId - CONTROLID_SETUP_DVR_AMBIENT_LED_R_DEC,AMBIENT_LED_R);
		break;
		//G
		case CONTROLID_SETUP_DVR_AMBIENT_LED_G_DEC:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_G_INC:
			appToSys_AmbientLed_G_MouseUp(ctrlId - CONTROLID_SETUP_DVR_AMBIENT_LED_G_DEC,AMBIENT_LED_G);
		break;
		//B
		case CONTROLID_SETUP_DVR_AMBIENT_LED_B_DEC:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_B_INC:
			appToSys_AmbientLed_B_MouseUp(ctrlId - CONTROLID_SETUP_DVR_AMBIENT_LED_B_DEC,AMBIENT_LED_B);
		break;
		//DIMMING
		case CONTROLID_SETUP_DVR_AMBIENT_LED_DIMMING_DEC:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_DIMMING_INC:
			appToSys_AmbientLed_DIMMING_MouseUp(ctrlId - CONTROLID_SETUP_DVR_AMBIENT_LED_DIMMING_DEC);
		break;
		case CONTROLID_SETUP_DVR_AMBIENT_LED_CUSTOMIZE:
		{
			if(pLocalParam->eSaveRGB_Dimming_value[0].uAmbientLedSaveRValue[0] &&
				pLocalParam->eSaveRGB_Dimming_value[0].uAmbientLedSaveRValue[1]&&
				pLocalParam->eSaveRGB_Dimming_value[0].uAmbientLedSaveGValue[0]&&
				pLocalParam->eSaveRGB_Dimming_value[0].uAmbientLedSaveGValue[1]&&
				pLocalParam->eSaveRGB_Dimming_value[0].uAmbientLedSaveBValue[0]&&
				pLocalParam->eSaveRGB_Dimming_value[0].uAmbientLedSaveBValue[1])
			return;
			setCustomizeColorAndDimming(pLocalParam->eSaveRGB_Dimming_value[0]);
		}
		break;
		case CONTROLID_SETUP_DVR_AMBIENT_LED_JUMP_TO_RGB_PAGE:
		{
			jumpToPageSetRGB();
		}
		break;
		case CONTROLID_SETUP_DVR_AMBIENT_LED_RGB_PAGE_BACK:
		{
			systemToModule_NotifySystem_JumpPrePage();
		}
		break;
		case CONTROLID_SETUP_DVR_AMBIENT_LED_R_SCROLL_BAR:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_G_SCROLL_BAR:
		case CONTROLID_SETUP_DVR_AMBIENT_LED_B_SCROLL_BAR:
		{
			LOGD("appToSys_handleTimer --ctrlId:%x-- param[0]: %d    param[1]: %d param[2]: %d param[3]: %d",ctrlId,param[0],param[1],param[2],param[3]);
			pLocalParam->showGRB_Dimming_tag = true;
			setR_G_B_BarValue(param[3],ctrlId - CONTROLID_SETUP_DVR_AMBIENT_LED_R_SCROLL_BAR);
		}
		break;
		case CONTROLID_SETUP_DVR_AMBIENT_LED_DIMMING_SCROLL_BAR:
		{
			LOGD("appToSys_handleTimer --ctrlId:%x-- param[0]: %d    param[1]: %d param[2]: %d param[3]: %d",ctrlId,param[0],param[1],param[2],param[3]);
			pLocalParam->showGRB_Dimming_tag = true;
			systemToHalAboutAmbientLed_Dimming(param[3]);
		}
		break;
		case CONTROLID_SET_SCREEN_BRIGHTNESS_INC:
		case CONTROLID_SET_SCREEN_BRIGHTNESS_DEC:
			{
				appToSys_Set_Screen_Brightness_value(ctrlId - CONTROLID_SET_SCREEN_BRIGHTNESS_INC);
			}
			break;
		case CONTROLID_SETUP_BACK_CAR_LINE_IN:
			systemToModule_NotifySystem_JumpPage(PAGE_SYSTEM_SET_BACK_CAR_LINE_CHOOSE_PAGE);
		break;
		case CONTROLID_SETUP_BACK_CAR_BACK:
			systemToModule_NotifySystem_JumpPrePage();
			break;
		case CONTROLID_SETUP_BACK_CAR_CURVE_LINE:
		case CONTROLID_SETUP_BACK_CAR_TRAPEZOID:
		case CONTROLID_SETUP_BACK_CAR_FORK:
			ToUI_BackCarVideo_TraceType_System(ctrlId - CONTROLID_SETUP_BACK_CAR_CURVE_LINE);
		break;
		case CONTROLID_MAIN_PAGE_ACC_OFF:
			SystemModule_FromKeyParam_KEYVAL_SLEEP();
		break;
		case CONTROLID_SET_DAY_AND_NIGHT_MODE_DAY:
		case CONTROLID_SET_DAY_AND_NIGHT_MODE_NIGHT:
		case CONTROLID_SET_DAY_AND_NIGHT_MODE_AUTO:
		{
			SetDayAndNightMode(ctrlId - CONTROLID_SET_DAY_AND_NIGHT_MODE_DAY);
		}
		break;
		case CONTROLID_SETUP_REVERSE_CAMERA_USB:
		case CONTROLID_SETUP_REVERSE_CAMERA_CVBS:
			{
				appToSys_Setup_Reverse_Camera_MouseUp(ctrlId - CONTROLID_SETUP_REVERSE_CAMERA_USB);
			}
			break;
		case CONTROLID_SETUP_SET_PANEL_LIGHT_BAR:
			{
				appToSys_Setup_Panel_Light_Bar_MouseUp(param[3]);
			}
			break;
		case CONTROLID_SETUP_SET_PANEL_LIGHT_AUTO_BUTTON:
			{
				appToSys_Setup_Panel_Light_Button_MouseUp();
			}
			break;
		case CONTROLID_SETUP_RADIO_CHINA:            	
		case CONTROLID_SETUP_RADIO_RUSSIA :             	
		case CONTROLID_SETUP_RADIO_THAILAND:            
		case CONTROLID_SETUP_RADIO_KOREA:              	
		case CONTROLID_SETUP_RADIO_S_AMER_2:             
		case CONTROLID_SETUP_RADIO_S_AMER_1:             
		case CONTROLID_SETUP_RADIO_USA:
			{
				appToSys_Setup_Radio_Area_Selection_MouseUp(ctrlId - CONTROLID_SETUP_RADIO_CHINA);
			}
			break;
		case CONTROLID_SETUP_SET_BOOT_VOLUME_BAR:
			{
				int pos = 0;
				pos += (int)((param[0] << 24) & 0xFF000000);
				pos += (int)((param[1] << 16) & 0xFF0000);
				pos += (int)((param[2] << 8) & 0xFF00);
				pos += (int)(param[3] & 0xFF);
				int temp = pLocalParam->Start_minVol + pos;
				appToSys_Setup_PowerVol_Bar_Mouse_Up(temp);
			}
			break;
		case CONTROLID_SETUP_SET_BOOT_VOLUME_FOLLOW_BUTTON:
			{
				if(pLocalParam->u8_Sys_StartupVol != 0xff)
					appToSys_Setup_PowerVol_Bar_MouseUp(0xff);
				else 
					appToSys_Setup_PowerVol_Bar_MouseUp(pLocalParam->u8_Sys_StartupVol_bef);
			}
			break;
		case CONTROLID_SETUP_BOOT_ANIMATION_WATER_DROPS:
		case CONTROLID_SETUP_BOOT_ANIMATION_WATER_WAVE:
		case CONTROLID_SETUP_BOOT_ANIMATION_WATER_FLASH:
			appToSys_Setup_Default_Boot_Animation(ctrlId - CONTROLID_SETUP_BOOT_ANIMATION_WATER_DROPS);
		break;

		case CONTROLID_START_THE_MAP_BY_DEFAULT_BAIDU:
			setDefault_Boot_Nav_Baidu();
			break;
		case CONTROLID_START_THE_MAP_BY_DEFAULT_KAY_RUCHER:
			setDefault_Boot_Nav_KaiLiDe();
			break;
		case CONTROLID_START_THE_MAP_BY_DEFAULT_GAODE:
			setDefault_Boot_Nav_GaoDe();
			break;
		case CONTROLID_START_THE_MAP_BY_DEFAULT_TENXU:
			setDefault_Boot_Nav_TengXun();
			break;
		case CONTROLID_BOOT_RUN_NAV_FOLLOW:
		case CONTROLID_BOOT_RUN_NAV_ON:
		case CONTROLID_BOOT_RUN_NAV_OFF:
			appToSystem_Setup_Boot_Run_Nav_status(ctrlId - CONTROLID_BOOT_RUN_NAV_FOLLOW);
		case CONTROLID_SETUP_CAMERA_DELAYS_WITCH:
			{
				if(pLocalParam->uCameraDelayTag)
					systemToModule_NotifyExtcar_SetCameraDelay(0x00);
				else
					systemToModule_NotifyExtcar_SetCameraDelay(0x01);
			}
			break;
		case CONTROLID_SETUP_TEMP_UNIT_DISPLAY_C:
		case CONTROLID_SETUP_TEMP_UNIT_DISPLAY_F:
			systemToModule_NotifyExtcar_SetTempUnit(ctrlId - CONTROLID_SETUP_TEMP_UNIT_DISPLAY_C);
			break;
		case CONTROLID_SETUP_SOUND_CHANNEL_PAGE_BACK:
			appToSys_Sound_Channel_Back();
			break;
		case CONTROLID_SETUP_SOUND_CHANNEL_PAGE_ENTER:			
			appToSys_Sound_Channel_MouseUp();
			break;	
		case CONTROLID_SETUP_SOUND_CHANNEL_PAGE_MEDIA_BAR:	
		case CONTROLID_SETUP_SOUND_CHANNEL_PAGE_RING_BAR:
		case CONTROLID_SETUP_SOUND_CHANNEL_PAGE_CALL_BAR:	
		case CONTROLID_SETUP_SOUND_CHANNEL_PAGE_GPS_BAR:
			{
				analyseAppToSystemSoundChannelMessage(ctrlId,param[3]);
				showSoundChannelVolume_Bar(ctrlId,param[3]);
			}
			break;
		case CONTROLID_SETUP_THIRD_PARTY_DAIL_OPTION_UP:
		case CONTROLID_SETUP_THIRD_PARTY_DAIL_OPTION_DOWN:
			thirdDailingOption();
		break;
		case CONTROLID_SETUP_DESKTOP_NAVIGATION_MAP_INFOR_SWITCH_SYNC:
		if(u8_MouseStatus == SYS_SETUP_ON)
		{
			appToSys_Setup_DesktopNavigationMapInformationsSyncSwitch_ON_MouseUp();
		}
		else
		{
			appToSys_Setup_DesktopNavigationMapInformationsSyncSwitch_OFF_MouseUp();
		}
		break;
		case CONTROLID_SET_SCREEN_BRIGHTNESS_AUTOMATIC_ADJUSTMENT_SWTICH:
		if(u8_MouseStatus == SYS_SETUP_ON)
		{
			appToSys_Setup_ScreenBrithnessAutoAdjust_Switch_MouseUp(0x01);
		}
		else
		{
			appToSys_Setup_ScreenBrithnessAutoAdjust_Switch_MouseUp(0x00);
		}
		break;
		case CONTROLID_SETUP_AMBIENT_LED_MAIN_PAGE:
			switch_Page(PAGE_SYSTEM_SET_LED_RGB_PAGE);
			break;
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_ORANGE:
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_RED:
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_SOFT_BLUE:
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_ICE_BLUE:
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_BLUE:
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_PURPLE:
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_GREEN:
			appToSys_Setup_AmbientLedColorSet_MouseUp(ctrlId);
			break;
		case CONTROLID_SETUP_AMBIENT_LED_BRIGHTNESS_SCROLL_BAR:
			{
				int pos = 0;
				pos += (int)((param[0] << 24) & 0xFF000000);
				pos += (int)((param[1] << 16) & 0xFF0000);
				pos += (int)((param[2] << 8) & 0xFF00);
				pos += (int)(param[3] & 0xFF);
				appToSys_Setup_Ambient_Led_Brightness_Bar_Mouse_Up(pos);
			}	
			break;
		case CONTROLID_SETUP_CARINFO_UINT_DISTANCE_KM:
		case CONTROLID_SETUP_CARINFO_UINT_DISTANCE_MILES:
			appToSys_Setup_DistanceUint_Mouse_Up(ctrlId - CONTROLID_SETUP_CARINFO_UINT_DISTANCE_KM);
			break;

		//MULTI CONTOURED SEATS ADJUST	0x2073
		case CONTROLID_MULTI_CONTOURED_SEATS_JUMP_PAGE_BUTTON:
			//appToSys_Setup_MCS_Main_JumpPage_Touch_Screen(0x00);
			appToSys_Setup_MCS_Main_JumpPage_Touch_Screen(0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_BUTTON:
			//appToSys_Setup_MCS_Adjust_JumpPage_Touch_Screen(0x00);
			appToSys_Setup_MCS_Adjust_JumpPage_Touch_Screen(0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_SCROLL_BAR:			
			//appToSys_Setup_MCS_Adjust_UpperLumbarPre_SCROLL_BAR_Touch_Screen(0x00);
			appToSys_Setup_MCS_Adjust_UpperLumbarPre_SCROLL_BAR_Touch_Screen(0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_DEC:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_INC:
			appToSys_Setup_MCS_Adjust_UpperLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_DEC,0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_SCROLL_BAR:
			//appToSys_Setup_MCS_Adjust_MidLumbarPre_SCROLL_BAR_Touch_Screen(0x00);
			appToSys_Setup_MCS_Adjust_MidLumbarPre_SCROLL_BAR_Touch_Screen(0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_DEC:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_INC:
			appToSys_Setup_MCS_Adjust_MidLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_DEC,0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_SCROLL_BAR:
			//appToSys_Setup_MCS_Adjust_LowerLumbarPre_SCROLL_BAR_Touch_Screen(0x00);
			appToSys_Setup_MCS_Adjust_LowerLumbarPre_SCROLL_BAR_Touch_Screen(0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_DEC:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_INC:
			appToSys_Setup_MCS_Adjust_LowerLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_DEC,0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_SCROLL_BAR:
			//appToSys_Setup_MCS_Adjust_UpperBolsterPre_SCROLL_BAR_Touch_Screen(0x00);
			appToSys_Setup_MCS_Adjust_UpperBolsterPre_SCROLL_BAR_Touch_Screen(0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_DEC:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_INC:
			appToSys_Setup_MCS_Adjust_UpperBolsterPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_DEC,0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_SCROLL_BAR:
			//appToSys_Setup_MCS_Adjust_LowerBolsterPre_SCROLL_BAR_Touch_Screen(0x00);
			appToSys_Setup_MCS_Adjust_LowerBolsterPre_SCROLL_BAR_Touch_Screen(0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_DEC:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_INC:
			appToSys_Setup_MCS_Adjust_LowerBolsterPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_DEC,0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_BUTTON:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_STATE_ICON:
			//appToSys_Setup_MCS_Adjust_DriverSide_Touch_Screen(0x00);
			appToSys_Setup_MCS_Adjust_DriverSide_Touch_Screen(0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_BUTTON:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_STATE_ICON:
			//appToSys_Setup_MCS_Adjust_PassengerSide_Touch_Screen(0x00);
			appToSys_Setup_MCS_Adjust_PassengerSide_Touch_Screen(0x01);
			break;
		//MULTI CONTOURED SEATS MASSAGE		0x2074
		case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_BUTTON:
			//appToSys_Setup_MCS_Passage_JumpPage_Touch_Screen(0x00);
			appToSys_Setup_MCS_Passage_JumpPage_Touch_Screen(0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_CLOSE:
		case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_LOW:	
		case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_HIGH:
			//appToSys_Setup_MCS_Passage_UpperLumbarSet_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_CLOSE,0x00);
			appToSys_Setup_MCS_Passage_UpperLumbarSet_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_CLOSE,0x01);
			break;	
		case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_CLOSE:	
		case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_LOW:	
		case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_HIGH:
			//appToSys_Setup_MCS_Passage_LowerLumbarSet_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_CLOSE,0x00);
			appToSys_Setup_MCS_Passage_LowerLumbarSet_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_CLOSE,0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_BUTTON:
		case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_STATE_ICON:
			//appToSys_Setup_MCS_Passage_DriverSide_Touch_Screen(0x00);
			appToSys_Setup_MCS_Passage_DriverSide_Touch_Screen(0x01);
			break;			
		case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_BUTTON:	
		case CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_STATE_ICON:
			//appToSys_Setup_MCS_Passage_PassengerSide_Touch_Screen(0x00);
			appToSys_Setup_MCS_Passage_PassengerSide_Touch_Screen(0x01);
			break;
		/*PAGE_SYSTEM_SET_SELECTION_CAR_TYPE_PAGE*/
		case CONTROLID_SELECTION_CAR_TYPE_JUMP:
			analyseSelectionCarTypeMessage(pLocalParam->uCurCartype);
			switch_Page(PAGE_SYSTEM_SET_SELECTION_CAR_TYPE_PAGE);
			break;		
		case CONTROLID_SELECTION_CAR_TYPE_CONFIRM:	
			showOrHideCarTypeBox(true);
			break;
		case CONTROLID_SELECTION_CAR_TYPE_CANCEL_BUTTEN:
			showOrHideCarTypeBox(false);
			analyseSelectionCarTypeMessage(pLocalParam->uCurCartype);
			break;
		case CONTROLID_SELECTION_CAR_TYPE_CONFIRM_BUTTEN:
			confirmSelectionCurCarType();
			break;
		default:break;
		
    	}
    	
}

void appToSys_handleCancel(u32 ctrlId,u8 u8_MouseStatus,u8 *param,u8 paramLen)
{
	switch(ctrlId)
	{
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_DEC:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_INC:
			appToSys_Setup_MCS_Adjust_UpperLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_DEC,0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_DEC:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_INC:
			appToSys_Setup_MCS_Adjust_MidLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_DEC,0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_DEC:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_INC:
			appToSys_Setup_MCS_Adjust_LowerLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_DEC,0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_DEC:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_INC:
			appToSys_Setup_MCS_Adjust_UpperBolsterPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_DEC,0x01);
			break;
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_DEC:
		case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_INC:
			appToSys_Setup_MCS_Adjust_LowerBolsterPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_DEC,0x01);
			break;
		default:break;
	}

}

void appToSys_handleTimer(u32 ctrlId,u8 u8_MouseStatus,u8 *param,u8 paramLen)
{
	switch(ctrlId)
	{
	    	    case CONTROLID_SYSTEM_WHEEL_LEARNING_MODE:
			    case CONTROLID_SYSTEM_WHEEL_LEARNING_MUTE:
				case CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_INC:
				case CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_DEC:
				case CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_INC:
				case CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_DEC:
				case CONTROLID_SYSTEM_WHEEL_LEARNING_BT_HAND_UP:
				case CONTROLID_SYSTEM_WHEEL_LEARNING_BT_CALL_IN:
					 SystemModule_Timer_WheelData_Clear();
					 break;
			    case CONTROLID_SETUP_SYSTEM_RESET:
					 LOGD("SYSTEM_RESET");
					 systemToHal_FactorySetting();
					 break;
			    case 0x020142:
					 switch_Page(PAGE_SETUP_END);
					 break;
				case CONTROLID_SETUP_24_HOUR_CLOCK_ON:
				    	appTosys_Setup_OsdDebugInfo_switch();		// Osd debug information switch 
				     break;
				//case CONTROLID_SETUP_24_HOUR_CLOCK_OFF:
				//	 appTosys_Setup_ModuleDebugInfo_switch();   /*Module OSD ������Ϣ��ʾ*/
				//	 break;
				case CONTROLID_SETUP_BACKCAR_VIDEO_CAMERA_CONTRID:
				        systemToModule_NotifySystem_JumpPage(PAGE_SYSTEM_BACKVIDEO_REFLINE_SWITCH);
				     break;
				case CONTROLID_SETUP_PANEL_LIGHT_UP:
					 appToSys_Setup_PanelLight_Up_MouseUp();
					 break;
				case CONTROLID_SETUP_PANEL_LIGHT_DOWN:
					 appToSys_Setup_PanelLight_Down_MouseUp();
					 break;
				case CONTROLID_SETUP_POWER_VOL_UP:
			         appToSys_Setup_PowerVol_Up_MouseUp();
			         break;
		        case CONTROLID_SETUP_POWER_VOL_DOWN:
			         appToSys_Setup_PowerVol_Down_MouseUp();
			         break;
			    case CONTROLID_SETUP_DEMO:
			    	 appToSys_Setup_Demo();
			    	 break;
			    case CONTROLID_SETUP_BRIGHTNESS_DIM_UP:
				case CONTROLID_SETUP_BRIGHTNESS_DIM_DOWN:
				case CONTROLID_SETUP_BRIGHTNESS_MODERATE_UP:
				case CONTROLID_SETUP_BRIGHTNESS_MODERATE_DOWN:
				case CONTROLID_SETUP_BRIGHTNESS_BRIGHT_UP:
				case CONTROLID_SETUP_BRIGHTNESS_BRIGHT_DOWN:
				case CONTROLID_SETUP_BRIGHTNESS_GUNDONDTIAO:
					appToSys_SetLCD_MouseUp(ctrlId,param,paramLen);
					break;
				case CONTROLID_SYSTEM_SETUP_RADIO_EARE_TIMES_BUTTON:
					systemToModule_NotifySystem_JumpPage(PAGE_SYSTEM_SET_STEER_AUTOMATE_SWITCH_PAGE);
					break;
				case CONTROLID_SETUP_DVR_AMBIENT_LED_R_SCROLL_BAR:
				case CONTROLID_SETUP_DVR_AMBIENT_LED_G_SCROLL_BAR:
				case CONTROLID_SETUP_DVR_AMBIENT_LED_B_SCROLL_BAR:
				{
					LOGD("appToSys_handleTimer --ctrlId:%x-- param[0]: %d    param[1]: %d param[2]: %d param[3]: %d",ctrlId,param[0],param[1],param[2],param[3]);
					pLocalParam->showGRB_Dimming_tag = false;
					setR_G_B_BarValue(param[3],ctrlId - CONTROLID_SETUP_DVR_AMBIENT_LED_R_SCROLL_BAR);
				}
				break;
				case CONTROLID_SETUP_DVR_AMBIENT_LED_DIMMING_SCROLL_BAR:
				{
					LOGD("appToSys_handleTimer --ctrlId:%x-- param[0]: %d    param[1]: %d param[2]: %d param[3]: %d",ctrlId,param[0],param[1],param[2],param[3]);
					pLocalParam->showGRB_Dimming_tag = false;
					systemToHalAboutAmbientLed_Dimming(param[3]);
				}
				break;
				case CONTROLID_SETUP_SET_PANEL_LIGHT_BAR:
				{
					u8 nTemp = param[3] + PANEL_LIGHT_MIN;
					showPanelLightValue(nTemp);
				}
				break;
				case CONTROLID_SETUP_SOUND_CHANNEL_PAGE_MEDIA_BAR:	
				case CONTROLID_SETUP_SOUND_CHANNEL_PAGE_RING_BAR:
				case CONTROLID_SETUP_SOUND_CHANNEL_PAGE_CALL_BAR:	
				case CONTROLID_SETUP_SOUND_CHANNEL_PAGE_GPS_BAR:
				{
					setSoundChannelVolumeValue(ctrlId,param[3]);
					analyseAppToSystemSoundChannelMessage(ctrlId,param[3]);
				}
				break;
				case CONTROLID_SETUP_SET_BOOT_VOLUME_BAR:
				{
					int pos = 0;
					pos += (int)((param[0] << 24) & 0xFF000000);
					pos += (int)((param[1] << 16) & 0xFF0000);
					pos += (int)((param[2] << 8) & 0xFF00);
					pos += (int)(param[3] & 0xFF);
					int temp = pLocalParam->Start_minVol + pos;
					appToSys_Setup_PowerVol_Bar_Mouse_Time(temp);
				}
				break;
				case CONTROLID_SETUP_AMBIENT_LED_BRIGHTNESS_SCROLL_BAR:
				{
					int pos = 0;
					pos += (int)((param[0] << 24) & 0xFF000000);
					pos += (int)((param[1] << 16) & 0xFF0000);
					pos += (int)((param[2] << 8) & 0xFF00);
					pos += (int)(param[3] & 0xFF);
					appToSys_Setup_Ambient_Led_Brightness_Bar_Mouse_Time(pos);
				}	
				break;
				//MULTI CONTOURED SEATS ADJUST	0x2073
				case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_DEC:
				case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_INC:
					//appToSys_Setup_MCS_Adjust_UpperLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_DEC,0x02);
					break;
				case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_DEC:
				case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_INC:
					//appToSys_Setup_MCS_Adjust_MidLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_DEC,0x02);
					break;
				case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_DEC:
				case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_INC:
					//appToSys_Setup_MCS_Adjust_LowerLumbarPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_DEC,0x02);
					break;
				case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_DEC:
				case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_INC:
					//appToSys_Setup_MCS_Adjust_UpperBolsterPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_DEC,0x02);
					break;
				case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_DEC:
				case CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_INC:
					//appToSys_Setup_MCS_Adjust_LowerBolsterPre_Touch_Screen(ctrlId - CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_DEC,0x02);
					break;
			  	default:break;
	    }
}

	//Setup Communication
	//Setup Function
	void appToSys_Setup_BackCarCamaera_ON_MouseUp(void)
	{
		systemToHal_BackCarDetected(SYSTEMTOHAL_BACKCARDETECT_ENABLE);
	}
	void appToSys_Setup_BackCarCamaera_OFF_MouseUp(void)
	{
		systemToHal_BackCarDetected(SYSTEMTOHAL_BACKCARDETECT_DISABLE);
	}

	void appToSys_Setup_BackCarRefLineDisplay_IS_MouseUp()
	{
		pLocalParam->eBackVideoRefLineIsDisplay = eLineState_IsShow;
		systemToModule_NotifyBackModule_BackCarVideoRefLineDisplaySet(1);

		if(pLocalParam->eBackVideoTraceLineIsDisplay == eLineState_IsShow)
		{
			systemToModule_NotifyBackModule_BackCarVideoTraceLineDisplaySet(1);
		}

		DisplayBackcarReflineSwitch(1);
		DisplayNewBackcarReflineSwitch(0);
	}
	
	void appToSys_Setup_BackCarRefLineDisplay_NO_MouseUp()
	{
		pLocalParam->eBackVideoRefLineIsDisplay = eLineState_NoShow;
		systemToModule_NotifyBackModule_BackCarVideoRefLineDisplaySet(0);
		systemToModule_NotifyBackModule_BackCarVideoTraceLineDisplaySet(0);

		DisplayBackcarReflineSwitch(0);
		DisplayNewBackcarReflineSwitch(1);
	}

	void DisplayBackcarReflineSwitch(u8 p)
	{
		setDigitalData(CONTROLID_SETUP_BACKVIDEO_REFLINEDISPALY_SET, p);
	}

	void DisplayNewBackcarReflineSwitch(u8 p)
	{
		setDigitalData(CONTROLID_SETUP_BACK_CAR_SHOW_OR_HIDE, p);
	}

	void appToSys_Setup_BackCarRefLineDisplaySwitch_MouseUp()
	{
		E_BACKCAR_HASREDLINE_STATE em = pLocalParam->eBackVideoRefLineIsDisplay;
		if(em == eLineState_NoShow)
		{
			pLocalParam->eBackVideoRefLineIsDisplay = eLineState_IsShow;
			systemToModule_NotifyBackModule_BackCarVideoRefLineDisplaySet(1);

			if(pLocalParam->eBackVideoTraceLineIsDisplay == eLineState_IsShow)
			{
				systemToModule_NotifyBackModule_BackCarVideoTraceLineDisplaySet(1);
			}

			DisplayBackcarReflineSwitch(1);
			DisplayNewBackcarReflineSwitch(0);
		}
		else if(em == eLineState_IsShow)
		{
			pLocalParam->eBackVideoRefLineIsDisplay = eLineState_NoShow;
			systemToModule_NotifyBackModule_BackCarVideoRefLineDisplaySet(0);
			systemToModule_NotifyBackModule_BackCarVideoTraceLineDisplaySet(0);

			DisplayBackcarReflineSwitch(0);
			DisplayNewBackcarReflineSwitch(1);
		}
	}
	
	void appToSys_Setup_BackCarTraceLineDisplay_IS_MouseUp()
	{
	    pLocalParam->eBackVideoTraceLineIsDisplay = eLineState_IsShow;
	    setDigitalData(CONTROLID_SETUP_BACKVIDEO_TRACE_LINE_DISPALY_SET, true);

		if(pLocalParam->eBackVideoRefLineIsDisplay == eLineState_IsShow){
        	systemToModule_NotifyBackModule_BackCarVideoTraceLineDisplaySet(1);
		}
	}
	void appToSys_Setup_BackCarTraceLineDisplay_NO_MouseUp()
	{
	    pLocalParam->eBackVideoTraceLineIsDisplay = eLineState_NoShow;
	    setDigitalData(CONTROLID_SETUP_BACKVIDEO_TRACE_LINE_DISPALY_SET, false);
	    systemToModule_NotifyBackModule_BackCarVideoTraceLineDisplaySet(0);
	}
	void appToSys_Setup_LightDetect_ON_MouseUp(void)
	{
		systemToHal_LightDetected(SYSTEMTOHAL_LIGHTDETECT_ENABLE);
	}
	void appToSys_Setup_LightDetect_OFF_MouseUp(void)
	{
		systemToHal_LightDetected(SYSTEMTOHAL_LIGHTDETECT_DISABLE);
	}

	void appToSys_Setup_BrakeCarDetect_ON_MouseUp(void)
	{
	    setDigitalData(CONTROLID_SETUP_BRAKE_LINE_CHECK_ON,true);

        pLocalParam->cBreakCarEnable = true;
        System_BrakeCarDetect_IsCanSeeVideo();

	}
	void appToSys_Setup_BrakeCarDetect_OFF_MouseUp(void)
	{
	    setDigitalData(CONTROLID_SETUP_BRAKE_LINE_CHECK_ON,false);

		pLocalParam->cBreakCarEnable = false;
		System_BrakeCarDetect_IsCanSeeVideo();
	}

	bool IsCanSwitchVideoPage_WhenTheBrakeDownTime(u8 uCmd1,u8 uCmd2)
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
    		return true;
    	}   
 
	}

	void appToSys_Setup_Amplifier_ON_MouseUp(void)
	{
		systemToHal_SetExternalAmplifier(0x01);
	}
	void appToSys_Setup_Amplifier_OFF_MouseUp(void)
	{
		systemToHal_SetExternalAmplifier(0x00);
	}
	
	void appToSys_Setup_PanelLight_Up_MouseUp(void)
	{
		if(pLocalParam->u8_Sys_PanelLight == 0xff)
			pLocalParam->u8_Sys_PanelLight = 3;
		pLocalParam->u8_Sys_PanelLight++;
		if (pLocalParam->u8_Sys_PanelLight > 20)
			pLocalParam->u8_Sys_PanelLight = 0xff;
		systemToHal_KeyLedBrightness(pLocalParam->u8_Sys_PanelLight);
	}
	void appToSys_Setup_PanelLight_Down_MouseUp(void)
	{
		if (pLocalParam->u8_Sys_PanelLight == 0xFF)
			pLocalParam->u8_Sys_PanelLight = 21;
		pLocalParam->u8_Sys_PanelLight--;
		if (pLocalParam->u8_Sys_PanelLight < 4)
			pLocalParam->u8_Sys_PanelLight = 0xff;
		systemToHal_KeyLedBrightness(pLocalParam->u8_Sys_PanelLight);
	}

	//#include "otherModuleRequestCommand.h"
	//Setup Power Vol
	void appToSys_Setup_PowerVol_Up_MouseUp(void)
	{
		//u8 buf[] = {0x2c, 0};//������
		//makeAndSendMessageToModule(MODULE_ID_SYSTEM, MODULE_ID_DVR, buf, 2);
		
	  	if(pLocalParam->osdDebugSwith)
	  		pLocalParam->DebugSwitch = true;
				
		int iVol = pLocalParam->u8_Sys_StartupVol;
		u8 ansiBuf[16];
		memset(ansiBuf, 0, 16);
		u8 *pStrLastValume = (u8*)"Last Volume";
		LOGD("LocalParam->MaxVol:%x",pLocalParam->Start_MaxVol);
		if(pLocalParam->Start_MaxVol == iVol)
		{
			pLocalParam->u8_Sys_StartupVol = 255;
			memcpy(ansiBuf, pStrLastValume, strlen((char*)pStrLastValume));
		}
		else if (255 == iVol)
		{
			pLocalParam->u8_Sys_StartupVol = pLocalParam->Start_minVol;
			sprintf((char*)ansiBuf,"%d",pLocalParam->u8_Sys_StartupVol);
		}
		else 
		{
			++pLocalParam->u8_Sys_StartupVol;
			sprintf((char*)ansiBuf,"%d",pLocalParam->u8_Sys_StartupVol);
		}
		int nAnsiBufLen = strlen((char*)ansiBuf);
		u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
		memset(unicodeBuf, 0, nAnsiBufLen*2+2);
		int nUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicodeBuf);
		setSerialData(CONTROLID_SETUP_POWER_VOL_TEXT,unicodeBuf,nUnicodeBufLen*2);
		systemToModule_NotifySoundModule_StartupVol(pLocalParam->u8_Sys_StartupVol);
		free(unicodeBuf);
		
	}
	void appToSys_Setup_PowerVol_Down_MouseUp(void)
	{
		pLocalParam->DebugSwitch=false;
	    LOGD("LocalParam->Start_MaxVol:%d",pLocalParam->Start_MaxVol);
		int iVol = pLocalParam->u8_Sys_StartupVol;
		u8 ansiBuf[16];
		memset(ansiBuf, 0, 16);
		u8 *pStrLastValume = (u8*)"Last Volume";
		if(pLocalParam->Start_minVol== iVol)
		{
			pLocalParam->u8_Sys_StartupVol = 255;
			memcpy(ansiBuf, pStrLastValume, strlen((char*)pStrLastValume));
		}
		else if (255 == iVol)
		{
			pLocalParam->u8_Sys_StartupVol = pLocalParam->Start_MaxVol;
			sprintf((char*)ansiBuf,"%d",pLocalParam->u8_Sys_StartupVol);
		}
		else 
		{
			--pLocalParam->u8_Sys_StartupVol;
			sprintf((char*)ansiBuf,"%d",pLocalParam->u8_Sys_StartupVol);
		}
		int nAnsiBufLen = strlen((char*)ansiBuf);
		u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
		memset(unicodeBuf, 0, nAnsiBufLen*2+2);
		int nUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicodeBuf);
		setSerialData(CONTROLID_SETUP_POWER_VOL_TEXT,unicodeBuf,nUnicodeBufLen*2);
		systemToModule_NotifySoundModule_StartupVol(pLocalParam->u8_Sys_StartupVol);
		free(unicodeBuf);
		LOGD("pLocalParam->u8_Sys_StartupVol:%x",pLocalParam->u8_Sys_StartupVol);
		LOGD("pLocalParam->defaultVol:%d",pLocalParam->Start_defaultVol);
	}

	void appToSys_Setup_Demo(void)
	{
		systemToHal_EnterDemoMode(1);
	}

	//Setup Multimedia
	void appToSys_Setup_IpodSet_ON_MouseUp(void)
	{
		systemToHal_SetTVOrIpol(0x01);
	}
	void appToSys_Setup_IpodSet_OFF_MouseUp(void)
	{
		systemToHal_SetTVOrIpol(0x00);
	}
	void appToSys_Setup_TVSet_ON_MouseUp(void)
	{
		systemToHal_SetTVOrIpol(0x00);
	}
	void appToSys_Setup_TVSet_OFF_MouseUp(void)
	{
		systemToHal_SetTVOrIpol(0x01);
	}

	void appToSys_Setup_DvdRegionCode_Up_MouseUp(void)
	{
		systemToHal_SimulateKey(SYSTEMTOHAL_SIMKEY_DVDREGION_INC);
		
	}
	void appToSys_Setup_DvdRegionCode_Down_MouseUp(void)
	{
		systemToHal_SimulateKey(SYSTEMTOHAL_SIMKEY_DVDREGION_DEC);
	}


	void appToSys_Setup_MultiRadio_Up_MouseUp(void)
	{
		systemToHal_SimulateKey(SYSTEMTOHAL_SIMKEY_RADIOCOUNTRY_INC);
		
	}
	void appToSys_Setup_MultiRadio_Down_MouseUp(void)
	{
		systemToHal_SimulateKey(SYSTEMTOHAL_SIMKEY_RADIOCOUNTRY_DEC);
		
	}


	//Setup GPSRun
	void appToSys_Setup_AutoGPS_ON_MouseUp(void)
	{
		pLocalParam->b_Sys_AutoRunGPS = true; //Auto Run 
		setDigitalData(CONTROLID_SETUP_AUTO_INFOGPS_ON,true);
		systemToGPSRun_NotifyGPSRun_AutoRunMsg(true);
	}
	void appToSys_Setup_AutoGPS_OFF_MouseUp(void)
	{
		pLocalParam->b_Sys_AutoRunGPS = false; //Auto Run 
		setDigitalData(CONTROLID_SETUP_AUTO_INFOGPS_ON,false);
		systemToGPSRun_NotifyGPSRun_AutoRunMsg(false);

	}
	void appToSys_Setup_AUDIO_AUTO_SOUND_ON_MouseUp()
	{
		pLocalParam->b_Sys_Auto_AutoSound = true; 
		setDigitalData(CONTROLID_SETUP_AUDIO_AUTO_SOUND_ON_OFF,true);
		//System_notifyApp_AUTO_SOUND_ON(0x01);
	}
	void appToSys_Setup_AUDIO_AUTO_SOUND_OFF_MouseUp()
	{
		pLocalParam->b_Sys_Auto_AutoSound = false;
		setDigitalData(CONTROLID_SETUP_AUDIO_AUTO_SOUND_ON_OFF,false);
		//System_notifyApp_AUTO_SOUND_ON(0x00);
	}
	void appToSys_Setup_GPSVoicePrompt_ON_MouseUp(void)
	{
		pLocalParam->b_Sys_GPSVoicePrompt= true;
		setDigitalData(CONTROLID_SETUP_GPS_VOICE_PROMPT_ON,true);
		systemToModule_NotifySoundModule_GPSVoicePrompt(0x01);
	}
	void appToSys_Setup_GPSVoicePrompt_OFF_MouseUp(void)
	{
		pLocalParam->b_Sys_GPSVoicePrompt= false;
		setDigitalData(CONTROLID_SETUP_GPS_VOICE_PROMPT_ON,false);
		systemToModule_NotifySoundModule_GPSVoicePrompt(0x00);
	}

	//Setup Time
	


	//Setup Style
	void appToSys_Setup_SysStyleSet_MouseUp(void)
	{

	}
	void appToSys_Setup_LanguageSet_MouseUp(void)
	{

	}
	//Copyright
	void appToSys_Copyright_MouseUp(void)
	{
		switch_Page(PAGE_COPYRIGHT);
	}

	void appToSys_Copyright_Back_MouseUp(void)
	{
	   
		anyModuleToSysModule_Switch_PrePage();
	}

	void appTosys_Setup_OsdDebugInfo_switch(void){
		pLocalParam->osdDebugSwith=true;
		systemToModule_NotifyOSD_OSDDebugInfo_Switch();
		systemToHal_SimulateKey(0x05);	// DEBUG
	}
	void appToSys_Setup_MouseUp(u32 controlID)
	{
		switch(controlID)
		{
			case CONTROLID_SETUP_JUMPPAGE_ONE:
				switch_Page(0x201);
				break;
			case CONTROLID_SETUP_JUMPPAGE_TWO:
				{
					appToSys_Setup_PowerVol_Bar_Jump_set(pLocalParam->u8_Sys_StartupVol);
					switch_Page(0x202);
				}
				break;
 			case CONTROLID_SETUP_JUMPPAGE_THREE:
 				switch_Page(0x203);
 				break;
 			case CONTROLID_SETUP_JUMPPAGE_FOUR:
 				switch_Page(0x204);
 				break;
 			case CONTROLID_SETUP_JUMPPAGE_FIVE:

 				switch_Page(0x205);
 				break;
 			default:break;
 		}
	}

void appToSys_Setup_TV_DVR_TPMS_UpOrDownSwitch(int nParam)
{
	//u8 s = ((pLocalParam->m_eExternalDevice + 1) % 3) & 0xFF;
	//systemToHal_SetDVROrTV(s);
    LOGD("app pLocalParam->m_eExternalDevice:%d",pLocalParam->m_eExternalDevice);
	if(nParam == 0)
	{
	    SetLastDevice(pLocalParam->m_eExternalDevice);
	}
	else
	{
	    SetNextDevice(pLocalParam->m_eExternalDevice);
	}
}

void ToUI_SwitchOne_about_SetupIsRunningNavigationStr(int nParam)
{
    switch(nParam)
    {
        case 0:
            setStringText(CONTROLID_SETUP_GPS_FUNCTION_NAV_TEXT,STRING_CARINFO_GOLD_SETUP_RUNNING_NAVIGATION_AUTO);
        break;
        case 1:
            setStringText(CONTROLID_SETUP_GPS_FUNCTION_NAV_TEXT,STRING_CARINFO_GOLD_SETUP_RUNNING_NAVIGATION_YES);
        break;
        case 2:
            setStringText(CONTROLID_SETUP_GPS_FUNCTION_NAV_TEXT,STRING_CARINFO_GOLD_SETUP_RUNNING_NAVIGATION_NO);
        break;
    }
}

void appToSys_Setup_GPS_BOOT_RUN_UpOrDownSwitch(int nParam)
{
    if(nParam == 0)//UP
    {
        if(pLocalParam->nNavigationBootingRunMod == 0)
        {
            pLocalParam->nNavigationBootingRunMod = 2;
        }
        else if(pLocalParam->nNavigationBootingRunMod == 1)
        {
            pLocalParam->nNavigationBootingRunMod = 0;
        }
        else if(pLocalParam->nNavigationBootingRunMod == 2)
        {
            pLocalParam->nNavigationBootingRunMod = 1;
        }
    }
    else//Down 
    {
        if(pLocalParam->nNavigationBootingRunMod == 0)
        {
            pLocalParam->nNavigationBootingRunMod = 1;
        }
        else if(pLocalParam->nNavigationBootingRunMod == 1)
        {
            pLocalParam->nNavigationBootingRunMod = 2;
        }
        else if(pLocalParam->nNavigationBootingRunMod == 2)
        {
            pLocalParam->nNavigationBootingRunMod = 0;
        }
    }

    ToUI_SwitchOne_about_SetupIsRunningNavigationStr(pLocalParam->nNavigationBootingRunMod);
    
}

void appToSys_Setup_BootOn_IsAutoPlay(int nParam)
{
    LOGD("nParam:%d",nParam);
    if(nParam == 0)
    {
        setDigitalData(CONTROLID_SETUP_BOOTON_ISAUTOPLAY,false);
    }
    else
    {
        setDigitalData(CONTROLID_SETUP_BOOTON_ISAUTOPLAY,true);
    }
}

void appToSys_Setup_BootOn_IsAutoPlay_ON_MouseUp()
{
    localParam.u8BootOnIsAutoPlay = 1;
    appToSys_Setup_BootOn_IsAutoPlay(1);
}
void appToSys_Setup_BootOn_IsAutoPlay_OFF_MouseUp()
{
    localParam.u8BootOnIsAutoPlay = 0;
    appToSys_Setup_BootOn_IsAutoPlay(0);
}


void appToSys_Setup_TvOrDvrSwitchON_MouseUp(void)
{
	systemToHal_SetDVROrTV(0x01);
}
void appToSys_Setup_TvOrDvrSwitchOFF_MouseUp(void)
{
	systemToHal_SetDVROrTV(0x00);
}	
void appToSys_Setup_CarinfoAudioCueON(void)
{
	pLocalParam->b_Sys_VoicePrompt = true;
	setDigitalData(CONTROLID_SETUP_CARINFO_AUDIO_CUE_ON_OFF,true);

	systemToModule_NotifyExtcarModule_CarInforVoiceStatus(true);
}
void appToSys_Setup_CarinfoAudioCueOFF(void)
{
	pLocalParam->b_Sys_VoicePrompt = false;
	setDigitalData(CONTROLID_SETUP_CARINFO_AUDIO_CUE_ON_OFF,false);

	systemToModule_NotifyExtcarModule_CarInforVoiceStatus(false);
}

void appToSys_Setup_CarinfoVoice(u8 state)
{
	pLocalParam->b_Sys_VoicePrompt = state;
	setDigitalData(CONTROLID_SETUP_CARINFO_AUDIO_CUE_ON_OFF,state);
}

void DisplayingOrHidingSysCarModules(u8 state)
{
	setUpdateUI(false);
	setVisible(CONTROLID_SETUP_CAR_MODELS_DIALOG, state);
	setVisible(CONTROLID_SETUP_CAR_MODELS_DIALOG_TEXT, state);
	setVisible(CONTROLID_SETUP_CAR_MODELS_DIALOG_OK, state);
	setVisible(CONTROLID_SETUP_CAR_MODELS_DIALOG_CANCEL, state);
	setUpdateUI(true);
}

void appToSys_Setup_Default_NaviGation(int nParam)
{
	LOGD("1pLocalParam->NaviNub:%x pLocalParam->nNaviCount:%x",pLocalParam->NaviNub,pLocalParam->nNaviCount);

    if(pLocalParam->nNaviCount <= 0)return;
    
	if(nParam == 0)
	{
    	if(pLocalParam->NaviNub == 0)
    		pLocalParam->NaviNub=pLocalParam->nNaviCount;
    	pLocalParam->NaviNub=(pLocalParam->NaviNub-1)%pLocalParam->nNaviCount;
	}
	else if(nParam == 1)
	{
	    pLocalParam->NaviNub=(pLocalParam->NaviNub+1)%pLocalParam->nNaviCount;
	}
	
	LOGD("2pLocalParam->NaviNub:%x",pLocalParam->NaviNub);
    u32 strID=pLocalParam->naviList[pLocalParam->NaviNub].NaviNameStrID;
    if(strID != 0 && pLocalParam->naviList[pLocalParam->NaviNub].NaviMark == 1)
    {
    	LOGD("3strID:%x",strID);
    	setStringText(CONTROLID_SETUP_DEFAULT_NAVIGATION_TEXT,strID);
	}
	else
	{
	    LOGD("4NaviNameStr:%s",pLocalParam->naviList[pLocalParam->NaviNub].NaviNameStr);
	    int nAnsiBufLen = strlen(pLocalParam->naviList[pLocalParam->NaviNub].NaviNameStr);
	    systemCallParrotBT_aboutSerialDataUIFunction(CONTROLID_SETUP_DEFAULT_NAVIGATION_TEXT,(u8*)pLocalParam->naviList[pLocalParam->NaviNub].NaviNameStr,nAnsiBufLen);
      	//setAnsiSerialData(CONTROLID_SETUP_DEFAULT_NAVIGATION_TEXT, (u8*)pLocalParam->naviList[pLocalParam->NaviNub].NaviNameStr, nAnsiBufLen);
	}
	appToSys_Setup_Default_NaviGation_Ok();

	u8 PackNameLen = strlen((char *)pLocalParam->naviList[pLocalParam->NaviNub].NaviPackName);
	u8 ClassNameLen = strlen((char *)pLocalParam->naviList[pLocalParam->NaviNub].NaviClassName);
	System_notifyApp_ChoiceNavigationMapInformations(pLocalParam->naviList[pLocalParam->NaviNub].NaviPackName,PackNameLen,pLocalParam->naviList[pLocalParam->NaviNub].NaviClassName,ClassNameLen);
}

void appToSys_Setup_Default_NaviGation_Ok(void )
{
	char property[PROPERTY_VALUE_MAX];
	sprintf(property,"%s", pLocalParam->naviList[pLocalParam->NaviNub].NaviPackName);
    property_set("fly.flyui.gpspackage",property);

	sprintf(property,"%s", pLocalParam->naviList[pLocalParam->NaviNub].NaviClassName);
    property_set("fly.flyui.gpsclass",property);
	 g_clsSystem.sendToFlyJniSdkDefualtNaviChange();
	
}

void appToSys_Setup_DynamicLogoStyle(int nParam)
{
	LOGD("1pLocalParam->uLogoSetNub:%x pLocalParam->nLogoStyleCount:%x",pLocalParam->uLogoSetNub,pLocalParam->nLogoStyleCount);
	if(pLocalParam->nLogoStyleCount <= 0)return;

	if(nParam == 0)
	{
		if(pLocalParam->uLogoSetNub == 0)
			pLocalParam->uLogoSetNub=pLocalParam->nLogoStyleCount;
		pLocalParam->uLogoSetNub=(pLocalParam->uLogoSetNub-1)%pLocalParam->nLogoStyleCount;
	}
	else if(nParam == 1)
	{
		pLocalParam->uLogoSetNub=(pLocalParam->uLogoSetNub+1)%pLocalParam->nLogoStyleCount;
	}

	LOGD("2pLocalParam->uLogoSetNub:%x",pLocalParam->uLogoSetNub);
	u32 strID=pLocalParam->st_LogoStyle[pLocalParam->uLogoSetNub].cLogoStyleNameStrID;
	if(strID != 0 && pLocalParam->st_LogoStyle[pLocalParam->uLogoSetNub].cLogoStyleMark == 1)
	{
		LOGD("3strID:%x",strID);
		setStringText(CONTROLID_SETUP_DYNAMIC_LOGO_STYLE_TXT,strID);
	}
	else
	{
		LOGD("LogoStylesNameStr:%s",pLocalParam->st_LogoStyle[pLocalParam->uLogoSetNub].cLogoStylesNameStr);
		int nAnsiBufLen = strlen(pLocalParam->st_LogoStyle[pLocalParam->uLogoSetNub].cLogoStylesNameStr);
		systemCallParrotBT_aboutSerialDataUIFunction(CONTROLID_SETUP_DYNAMIC_LOGO_STYLE_TXT,(u8*)pLocalParam->st_LogoStyle[pLocalParam->uLogoSetNub].cLogoStylesNameStr,nAnsiBufLen);
	}

	appToSys_Setup_Default_DynamicLogoStyle_Ok();
}

void appToSys_Setup_Default_DynamicLogoStyle_Ok(void)
{
	char property[PROPERTY_VALUE_MAX];
	sprintf(property,"%d", pLocalParam->st_LogoStyle[pLocalParam->uLogoSetNub].cLogoStyleNameStrID);
   	property_set("persist.bootanim.type",property);
}

void appToSys_Setup_Default_Navigation_ShowHide(void)
{
	if(pLocalParam->cNavigationVisible==0)
	{
		LOGD("appToSys_Setup_Default_Navigation_ShowHide  IS HIDE_");
		setVisible(CONTROLID_DEFAULT_NAVIGATION_SOFTWARE,0x00);
		setVisible(CONTROLID_SETUP_DEFAULT_NAVIGATION_TEXT,0x00);
		setVisible(CONTROLID_SETUP_DEFAULT_NAVIGATION_UP,0x00);
		setVisible(CONTROLID_SETUP_DEFAULT_NAVIGATION_DOWN,0x00);
	}
}

void appToSys_Setup_System_Fan_Up(void)
{
	LOGD("[DYB]: appToSys_Setup_System_Fan_Up, pLocalParam->eCurFanMode = [%d]", pLocalParam->eCurFanMode);
	/*
	if (pLocalParam->eCurFanMode == eFanModeLowPower)
	{
		pLocalParam->eCurFanMode = eFanModeFitAuto;
		systemToHal_SetFanMode(0x03);
		systemToHal_SetCPU_PerformanceMode(0x01);
	}
	else if(pLocalParam->eCurFanMode == eFanModeFitAuto)
	{
		pLocalParam->eCurFanMode = eFanModeHighPerformance;
	    systemToHal_SetFanMode(0x02);
	    systemToHal_SetCPU_PerformanceMode(0x02);
	}
	else if (pLocalParam->eCurFanMode == eFanModeHighPerformance)
	{
 		pLocalParam->eCurFanMode = eFanModeShutOpen;
		systemToHal_SetFanMode(0x01);
	}
	else if(pLocalParam->eCurFanMode == eFanModeShutOpen)
	{
	 	pLocalParam->eCurFanMode = eFanModeShutDown;
		systemToHal_SetFanMode(0x00);
	}
	else if(pLocalParam->eCurFanMode == eFanModeShutDown)
	{
	 	pLocalParam->eCurFanMode = eFanModeLowPower;
		systemToHal_SetFanMode(0x04);
		systemToHal_SetCPU_PerformanceMode(0x00);
	}*/

	if (pLocalParam->eCurFanMode == eFanModeShutDown)
	{
		pLocalParam->eCurFanMode = eFanModeLowPower;
		systemToHal_SetFanMode(0x04);
		systemToHal_SetCPU_PerformanceMode(0x00);
	}
	else if(pLocalParam->eCurFanMode == eFanModeLowPower)
	{
	    pLocalParam->eCurFanMode = eFanModeShutDown;
		systemToHal_SetFanMode(0x00);
	}


	SystemModuleToUI_aboutFanMode(pLocalParam->eCurFanMode);
}

void appToSys_Setup_System_Fan_Down(void)
{
	LOGD("[DYB]: appToSys_Setup_System_Fan_Down pLocalParam->eCurFanMode = [%d]", pLocalParam->eCurFanMode);
    /*
	if (pLocalParam->eCurFanMode == eFanModeShutDown)
	{
		pLocalParam->eCurFanMode = eFanModeShutOpen;
		systemToHal_SetFanMode(0x01);
	}
	else if(pLocalParam->eCurFanMode == eFanModeShutOpen)
	{
		pLocalParam->eCurFanMode = eFanModeHighPerformance;
	    systemToHal_SetFanMode(0x02);
	    systemToHal_SetCPU_PerformanceMode(0x02);

	}
	else if(pLocalParam->eCurFanMode == eFanModeHighPerformance)
	{
		pLocalParam->eCurFanMode = eFanModeFitAuto;
		systemToHal_SetFanMode(0x03);
		systemToHal_SetCPU_PerformanceMode(0x01);
	}
	else if(pLocalParam->eCurFanMode = eFanModeFitAuto)
	{
	    pLocalParam->eCurFanMode = eFanModeLowPower;
		systemToHal_SetFanMode(0x04);
		systemToHal_SetCPU_PerformanceMode(0x00);
	}
	else if(pLocalParam->eCurFanMode = eFanModeLowPower)
	{
	    pLocalParam->eCurFanMode = eFanModeShutDown;
		systemToHal_SetFanMode(0x00);
	}*/

    
	if (pLocalParam->eCurFanMode == eFanModeShutDown)
	{
		pLocalParam->eCurFanMode = eFanModeLowPower;
		systemToHal_SetFanMode(0x04);
		systemToHal_SetCPU_PerformanceMode(0x00);
	}
	else if(pLocalParam->eCurFanMode == eFanModeLowPower)
	{
	    pLocalParam->eCurFanMode = eFanModeShutDown;
		systemToHal_SetFanMode(0x00);
	}

	SystemModuleToUI_aboutFanMode(pLocalParam->eCurFanMode);
	
}


void SystemModuleToUI_aboutFanMode(E_FAN_MODE FanMode)
{
	if(FanMode == eFanModeShutDown)
	{
		setStringText(CONTROLID_SETUP_SMART_FAN_TEXT, STRINGID_SYSTEM_SETTING_FAN_SHUTDOWN_MOD);
	}
	else if (FanMode == eFanModeShutOpen)
	{
		setStringText(CONTROLID_SETUP_SMART_FAN_TEXT, STRINGID_SYSTEM_SETTING_FAN_SHUTOPEN_MOD);
	}
	else if(FanMode == eFanModeHighPerformance)
	{
	    setStringText(CONTROLID_SETUP_SMART_FAN_TEXT, STRINGID_SYSTEM_SETTING_FAN_PERFORMANCE_MOD);
	}
	else if (FanMode == eFanModeFitAuto)
	{
		
	}
	else if(FanMode == eFanModeLowPower)
	{
	    setStringText(CONTROLID_SETUP_SMART_FAN_TEXT, STRINGID_SYSTEM_SETTING_FAN_AUTO_MOD);
	}


}

void UI_DVR_Protocol_Mode()
{
	int nMap[7] = {0};
	nMap[e_Is_ProTocol] = STRINGID_SYSTEM_SETUP_DVR_IS_PROTOCOL_MODE;
	nMap[e_No_ProTocol] = STRINGID_SYSTEM_SETUP_DVR_NO_PROTOCOL_MODE;
	if(pLocalParam->eDvrProtocolMode < 7)
		setStringText(CONTROLID_SETUP_DVR_PROTOCOL_MODE_TXT, nMap[pLocalParam->eDvrProtocolMode]);
}

void Set_Dvr_ProtocolMode(u8 p)
{
	UI_DVR_Protocol_Mode();
}

void appToSys_Setup_Dvr_set_protocol_mode()
{
	E_DVR_PROTOCOL_MODE eTemp = pLocalParam->eDvrProtocolMode;
	if(eTemp == e_Is_ProTocol)
	{
		eTemp = e_No_ProTocol;
	}
	else if(eTemp == e_No_ProTocol)
	{
		eTemp = e_Is_ProTocol;
	}

	pLocalParam->eDvrProtocolMode = eTemp;
	Set_Dvr_ProtocolMode((u8)pLocalParam->eDvrProtocolMode);
}

void appToSys_Setup_System_VoltageProtection_Up(void)
{
	LOGD("[DYB0219]:  appToSys_Setup_System_VoltageProtection_Up pLocalParam->eVoltageProtectionMode = [%d]", pLocalParam->eVoltageProtectionMode);

	if (pLocalParam->eVoltageProtectionMode == eVoltageProtectionModeHigh)
	{
		pLocalParam->eVoltageProtectionMode = eVoltageProtectionModeLow;
		setStringText(CONTROLID_SETUP_VOLTAGE_PROTECTION_TEXT, STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_LOW);
		systemToHal_SetVoltageProtection(eVoltageProtectionModeLow);
	}
	else if(pLocalParam->eVoltageProtectionMode == eVoltageProtectionModeMid)
	{
		pLocalParam->eVoltageProtectionMode = eVoltageProtectionModeHigh;
		setStringText(CONTROLID_SETUP_VOLTAGE_PROTECTION_TEXT, STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_HIGH);
		systemToHal_SetVoltageProtection(eVoltageProtectionModeHigh);
	}
	else if(pLocalParam->eVoltageProtectionMode == eVoltageProtectionModeLow)
	{
		pLocalParam->eVoltageProtectionMode = eVoltageProtectionModeMid;
		setStringText(CONTROLID_SETUP_VOLTAGE_PROTECTION_TEXT, STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_MID);
		systemToHal_SetVoltageProtection(eVoltageProtectionModeMid);
	}
	
}

void appTSys_Setup_System_VoltageProtection_Down(void)
{
	LOGD("[DYB0219]:  appTSys_Setup_System_VoltageProtection_Down pLocalParam->eVoltageProtectionMode = [%d]", pLocalParam->eVoltageProtectionMode);

	if (pLocalParam->eVoltageProtectionMode == eVoltageProtectionModeHigh)
	{
		pLocalParam->eVoltageProtectionMode = eVoltageProtectionModeMid;
		setStringText(CONTROLID_SETUP_VOLTAGE_PROTECTION_TEXT, STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_MID);
		systemToHal_SetVoltageProtection(eVoltageProtectionModeMid);
		
	}
	else if(pLocalParam->eVoltageProtectionMode == eVoltageProtectionModeMid)
	{
		pLocalParam->eVoltageProtectionMode = eVoltageProtectionModeLow;
		setStringText(CONTROLID_SETUP_VOLTAGE_PROTECTION_TEXT, STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_LOW);
		systemToHal_SetVoltageProtection(eVoltageProtectionModeLow);
	}
	else if(pLocalParam->eVoltageProtectionMode == eVoltageProtectionModeLow)
	{
		pLocalParam->eVoltageProtectionMode = eVoltageProtectionModeHigh;
		setStringText(CONTROLID_SETUP_VOLTAGE_PROTECTION_TEXT, STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_HIGH);
		systemToHal_SetVoltageProtection(eVoltageProtectionModeHigh);
	}
	
}

void UiDisplay_System_BackCarVideoSwitch(u8 uParam)
{
    if(uParam == 1)
    {
        pLocalParam->uBackCarVideoSwitch_Status = 1;
        setDigitalData(CONTROLID_SETUP_BACK_VIDEO_ON, true);
    }
    else
    {
        pLocalParam->uBackCarVideoSwitch_Status = 0;
        setDigitalData(CONTROLID_SETUP_BACK_VIDEO_ON,false);
    }
}


/************zhq add backcar trigger type choise setting********************************************/

void appToSys_Setup_Backcar_TriggerType_UpOrDownSwitch(int nParam)
{
    LOGD("app pLocalParam->eSetupBackcarTriggerType:%d",pLocalParam->eSetupBackcarTriggerType);
	if(nParam == 0)
	{
	    SetLastTriggerType(pLocalParam->eSetupBackcarTriggerType);
	}
	else
	{
	    SetNextTriggerType(pLocalParam->eSetupBackcarTriggerType);
	}
}

void DisplayAutoMateSwitchButtonUI(bool status)
{
	setDigitalData(CONTROLID_SYSTEM_SETUP_AUTOMATE_SWITCH_TO_DVR, status);
}

void appToSys_Setup_IsAutoMate_ON_MouseUp(void)
{
	DisplayAutoMateSwitchButtonUI(true);
	systemToHal_SetDVROrTV(0);
}

void appToSys_Setup_IsAutoMate_OFF_MouseUp(void)
{
	DisplayAutoMateSwitchButtonUI(false);
	systemToHal_SetDVROrTV(1);
}

void appToSys_Setup_NaviMixLow_ON_MouseUp()
{
	systemToHal_SetNaviMixLow(1);
}

void appToSys_Setup_NaviMixLow_OFF_MouseUp()
{
	systemToHal_SetNaviMixLow(0);
}

void DisplaySysToUI_aboutNaviMixLow(bool b)
{
	setDigitalData(CONTROLID_SETUP_NAVI_MIX_LOW_SWITCH,b);
}

void systemToHalAboutAmbientLed_Init(u8 p)
{
	u8 szMsg[2] = {0x01, 0x00};
	szMsg[1] = p;
	systemToHal_AboutAmbientLedMsg(szMsg,2);
}

void systemToHalAboutAmbientLed_Switch(u8 p)
{
	u8 szMsg[2] = {0x02, 0x00};
	szMsg[1] = p;
	systemToHal_AboutAmbientLedMsg(szMsg,2);
}

void systemToHalAboutAmbientLed_Dimming(u8 p)
{
	u8 szMsg[2] = {0x03, 0x00};
	szMsg[1] = p;
	systemToHal_AboutAmbientLedMsg(szMsg,2);
}

void systemToHalAboutAmbientLed_SetRGB(u8 *p,u8 len)
{
	u8 szMsg[7] = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	if(len <= 7)
	{
		memcpy(szMsg + 1,p,len);
		systemToHal_AboutAmbientLedMsg(szMsg,7);
	}
}

void appToSys_AmbientLed_SetUp_MouseUp(void)
{
	switch_Page(PAGE_SYSTEM_SET_AMBIENT_LED_PAGE);

	//systemToHalAboutAmbientLed_Init(0x01);
}

void appToSys_AmbientLed_Back_MouseUp(void)
{
	systemToModule_NotifySystem_JumpPrePage();
}

void appToSys_AmbientLed_Switch_MouseUp(void)
{
	if(pLocalParam->uAmbientLedInitState == 0)
	{
		E_AMBIENT_LED_SWITCH emT = pLocalParam->emAmbientLedSwitch;
		if(emT == AMBIENT_LED_ON)
		{
			systemToHalAboutAmbientLed_Switch((u8)AMBIENT_LED_OFF);
			
			pLocalParam->emAmbientLedSwitch = AMBIENT_LED_OFF;//
		}
		else if(emT == AMBIENT_LED_OFF)
		{
			systemToHalAboutAmbientLed_Switch((u8)AMBIENT_LED_ON);
			
			pLocalParam->emAmbientLedSwitch = AMBIENT_LED_ON;//
		}

		DisplayUI_AmbientLed_SwitchButton((u8)pLocalParam->emAmbientLedSwitch);//
	}
}

static 	int LedCommissionMapping[][3] = {
		{203,0,1},     //WARM_RED
		{242,105,15},  //HAPPY_ORANGE
		{204,204,0},  	//LIVELY_YELLOW
		{0,204,0},	   //FRESH_GREEN
		{3,139,225},	//WORRY_BLUE
		{102,0,204},  //MYSTERIOUS_PURPLE
		{204,0,204},  //ACACIA_RED
		{250,7,109},  //ROMANTIC_PINK
		{0,204,204},  //FRESH_BLUE
		{237,228,228} //PURE_WHITE
};

bool GetRGBByLedCommissionMapping(u8 *R,u8 *G,u8 *B,u8 uTPYE)
{
	int i=0;
	int nCount = 0;
	nCount = (sizeof(LedCommissionMapping)/sizeof(LedCommissionMapping[0]));
	for(i=0;i < nCount;i++)
	{
		if(i == uTPYE)
		{
			*R = LedCommissionMapping[i][0];
			*G = LedCommissionMapping[i][1];
			*B = LedCommissionMapping[i][2];
			return true;
		}
	}

	return false;
}

E_AMBIENT_LED_COMMISSION GetTypeByLedCommissionMapping(u8 r,u8 g,u8 b)
{
	int i=0;
	int nCount = 0;
	nCount = (sizeof(LedCommissionMapping)/sizeof(LedCommissionMapping[0]));
	for(i=0;i < nCount;i++)
	{
		if(r == LedCommissionMapping[i][0] && g == LedCommissionMapping[i][1] && b == LedCommissionMapping[i][2])
		{
			return E_AMBIENT_LED_COMMISSION(i);
		}
	}

	return LED_COMMISSION_UNKNOWN;
}


void appToSys_AmbientLed_Commission_MouseUp(u8 p)
{
	switch((E_AMBIENT_LED_COMMISSION)p)
	{
		case LED_COMMISSION_WARM_RED:
		case LED_COMMISSION_HAPPY_ORANGE:
		case LED_COMMISSION_LIVELY_YELLOW:
		case LED_COMMISSION_FRESH_GREEN:
		case LED_COMMISSION_WORRY_BLUE:	
		case LED_COMMISSION_MYSTERIOUS_PURPLE:
		case LED_COMMISSION_ACACIA_RED:
		case LED_COMMISSION_ROMANTIC_PINK:
		case LED_COMMISSION_FRESH_BLUE:
		case LED_COMMISSION_PURE_WHITE:
		{
			if(pLocalParam->uAmbientLedInitState == 0 && pLocalParam->emAmbientLedSwitch == AMBIENT_LED_ON)
			{
				AmbientLed_setCommissionValue(p);
			}
		}
		break;
		default:
		break;
	}
}

void appToSys_AmbientLed_R_MouseUp(u8 p,E_AMBIENT_LED_RGB em)
{
	if(pLocalParam->uAmbientLedInitState == 0 && pLocalParam->emAmbientLedSwitch == AMBIENT_LED_ON)
	{
		int tempR = pLocalParam->uAmbientLedRValue[0];
		LOGD("p: %d R: %d",p,pLocalParam->uAmbientLedRValue[0]);
		if(p == 0)
		{
			tempR--;
			if(tempR < AMBIENT_LED_RGB_MIN)
				tempR = AMBIENT_LED_RGB_MAX;
		}
		else if(p == 1)
		{
			tempR++;
			if(tempR > AMBIENT_LED_RGB_MAX)
				tempR = AMBIENT_LED_RGB_MIN;
		}
		u8 TP[6] = {0};
		TP[0] = tempR;
		TP[1] = 0;
		TP[2] = pLocalParam->uAmbientLedGValue[0];
		TP[3] = 0;
		TP[4] = pLocalParam->uAmbientLedBValue[0];
		TP[5] = 0;
		systemToHalAboutAmbientLed_SetRGB(TP,6);
		
	}
}

void appToSys_AmbientLed_G_MouseUp(u8 p,E_AMBIENT_LED_RGB em)
{
	if(pLocalParam->uAmbientLedInitState == 0 && pLocalParam->emAmbientLedSwitch == AMBIENT_LED_ON)
	{
		u8 tempG = pLocalParam->uAmbientLedGValue[0];
		if(p == 0)
		{
			tempG--;
			if(tempG < AMBIENT_LED_RGB_MIN)
				tempG = AMBIENT_LED_RGB_MAX;
		}
		else if(p == 1)
		{
			tempG++;
			if(tempG > AMBIENT_LED_RGB_MAX)
				tempG = AMBIENT_LED_RGB_MIN;
		}
		u8 TP[6] = {0};
		TP[0] = pLocalParam->uAmbientLedRValue[0];
		TP[1] = 0;
		TP[2] = tempG;
		TP[3] = 0;
		TP[4] = pLocalParam->uAmbientLedBValue[0];
		TP[5] = 0;
		systemToHalAboutAmbientLed_SetRGB(TP,6);
		
	}
}

void appToSys_AmbientLed_B_MouseUp(u8 p,E_AMBIENT_LED_RGB em)
{
	if(pLocalParam->uAmbientLedInitState == 0 && pLocalParam->emAmbientLedSwitch == AMBIENT_LED_ON)
	{
		u8 tempB = pLocalParam->uAmbientLedBValue[0];
		if(p == 0)
		{
			tempB--;
			if(tempB < AMBIENT_LED_RGB_MIN)
				tempB = AMBIENT_LED_RGB_MAX;
		}
		else if(p == 1)
		{
			tempB++;
			if(tempB > AMBIENT_LED_RGB_MAX)
				tempB = AMBIENT_LED_RGB_MIN;
		}
		u8 TP[6] = {0};
		TP[0] = pLocalParam->uAmbientLedRValue[0];
		TP[1] = 0;
		TP[2] = pLocalParam->uAmbientLedGValue[0];
		TP[3] = 0;
		TP[4] = tempB;
		TP[5] = 0;
		systemToHalAboutAmbientLed_SetRGB(TP,6);
		
	}
}

void appToSys_AmbientLed_DIMMING_MouseUp(u8 p)
{
	if(pLocalParam->uAmbientLedInitState == 0 && pLocalParam->emAmbientLedSwitch == AMBIENT_LED_ON)
	{
		u8 uTem = pLocalParam->uAmbientLedDimmValue;
		if(p == 0)
		{
			if(uTem == AMBIENT_LED_DIMMING_MIN)
			{
				uTem = AMBIENT_LED_DIMMING_MAX;
			}
			else
			{
				uTem--;
			}
		}
		else if(p == 1)
		{
			if(uTem == AMBIENT_LED_DIMMING_MAX)
			{
				uTem =AMBIENT_LED_DIMMING_MIN;
			}
			else
			{
				uTem++;
			}
		}
		systemToHalAboutAmbientLed_Dimming(uTem);
	}
}

void DisplayUI_AmbientLed_SwitchButton(u8 p)
{
	setDigitalData(CONTROLID_SETUP_DVR_AMBIENT_LED_SWITCH,p);
}

void DisplayUI_AmbientLed_CommissionButton(E_AMBIENT_LED_COMMISSION em)
{
	switch(em)
	{
		case LED_COMMISSION_WARM_RED:
		case LED_COMMISSION_HAPPY_ORANGE:
		case LED_COMMISSION_LIVELY_YELLOW:
		case LED_COMMISSION_FRESH_GREEN:
		case LED_COMMISSION_WORRY_BLUE:	
		case LED_COMMISSION_MYSTERIOUS_PURPLE:
		case LED_COMMISSION_ACACIA_RED:
		case LED_COMMISSION_ROMANTIC_PINK:
		case LED_COMMISSION_FRESH_BLUE:
		case LED_COMMISSION_PURE_WHITE:
		{
			pLocalParam->emAmbientLedCommission = em;
			setDigitalData(CONTROLID_SETUP_DVR_AMBIENT_LED_CUSTOMIZE,0);
			for(int i = 0; i < 10; i++)
			{
				if(i == (u8)em)
				{
					setDigitalData(CONTROLID_SETUP_DVR_AMBIENT_LED_WARM_RED+i,1);
					continue;
				}
				else
				{
					setDigitalData(CONTROLID_SETUP_DVR_AMBIENT_LED_WARM_RED+i,0);
				}
			}
		}
		break;
		case LED_COMMISSION_UNKNOWN:
		{
			for(int i = 0; i < 10; i++)
			{
				setDigitalData(CONTROLID_SETUP_DVR_AMBIENT_LED_WARM_RED+i,0);
			}
			setDigitalData(CONTROLID_SETUP_DVR_AMBIENT_LED_CUSTOMIZE,1);
		}
		break;
		default:
		break;
	}
}

void DisplayUI_AmbientLed_PreviewPaper(u8 p)
{
	setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_PREVIEW_PAPER,p);
}

void DisplayUI_AmbientLed_R_bar_text(u8 p)
{
	if(pLocalParam->showGRB_Dimming_tag == true)
		setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_R_SCROLL_BAR,p);
	char TempStr[10] = {0};
	unicode16_t uTempStr[20];
	sprintf(TempStr, "%d", p);
	int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
	setSerialData(CONTROLID_SETUP_DVR_AMBIENT_LED_R_TEXT,(u8*)uTempStr,len*2);
}

void DisplayUI_AmbientLed_G_bar_text(u8 p)
{
	if(pLocalParam->showGRB_Dimming_tag == true)
		setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_G_SCROLL_BAR,p);
	char TempStr[10] = {0};
	unicode16_t uTempStr[20];
	sprintf(TempStr, "%d", p);
	int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
	setSerialData(CONTROLID_SETUP_DVR_AMBIENT_LED_G_TEXT,(u8*)uTempStr,len*2);
}

void DisplayUI_AmbientLed_B_bar_text(u8 p)
{
	if(pLocalParam->showGRB_Dimming_tag == true)
		setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_B_SCROLL_BAR,p);

	char TempStr[10] = {0};
	unicode16_t uTempStr[20];
	sprintf(TempStr, "%d", p);
	int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
	setSerialData(CONTROLID_SETUP_DVR_AMBIENT_LED_B_TEXT,(u8*)uTempStr,len*2);
}

void DisplayUI_AmbientLed_Dimming_bar_text(u8 p)
{
	if(pLocalParam->showGRB_Dimming_tag == true)
		setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_DIMMING_SCROLL_BAR,p);

	char TempStr[10] = {0};
	unicode16_t uTempStr[20];
	sprintf(TempStr, "%d", p);
	int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
	setSerialData(CONTROLID_SETUP_DVR_AMBIENT_LED_DIMMING_TEXT,(u8*)uTempStr,len*2);
}

void AmbientLed_setCommissionValue(u8 p)
{
	u8 uR = 0;
	u8 uG = 0;
	u8 uB = 0;
	if(GetRGBByLedCommissionMapping(&uR,&uG,&uB,p))
	{
		u8 TP[6] = {0};
		TP[0] = uR;
		TP[1] = 0;
		TP[2] = uG;
		TP[3] = 0;
		TP[4] = uB;
		TP[5] = 0;
		LOGD("[%d %d %d (%d)]",uR,uG,uB,p);
		systemToHalAboutAmbientLed_SetRGB(TP,6);

		DisplayUI_AmbientLed_CommissionButton((E_AMBIENT_LED_COMMISSION)p);
	}
}

void appToSys_Setup_BackCar_CVBS_Or_USB_MouseUp(u8 p)
{
	//if(pLocalParam->uBackCarSetCvbsOrUSB == 0)
	//{
	//	systemToModule_NotifyDVR_setBackCarProtocol_CVBS_or_USB(1);
	//}
	//else if(pLocalParam->uBackCarSetCvbsOrUSB == 1)
	//{
	//	systemToModule_NotifyDVR_setBackCarProtocol_CVBS_or_USB(0);
	//}
	
	u8 uT = pLocalParam->uSetCvbsOrUSBTemp;
	//u8 uT = pLocalParam->uBackCarSetCvbsOrUSB;

	if(uT == 0)
	{
		uT = 1;
		DisplaySysToUI_aboutBackCarProtocolCVBSorUSB(0);
	}
	else if(uT == 1)
	{
		uT = 0;
		DisplaySysToUI_aboutBackCarProtocolCVBSorUSB(1);
	}

	pLocalParam->uSetCvbsOrUSBTemp = uT;
	//pLocalParam->uBackCarSetCvbsOrUSB = uT;
	//System_notifyApp_cvbsOrUsbSwitch(pLocalParam->uBackCarSetCvbsOrUSB);
}

void DisplaySysToUI_aboutBackCarProtocolCVBSorUSB(u8 p)
{
	if(p == 0)//USB
	{
		setStringText(CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_TXT, STRINGID_SYSTEM_SETUP_BACKCAR_PROTOCOL_USB);
	}
	else if(p == 1)//CVBS
	{
		setStringText(CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_TXT, STRINGID_SYSTEM_SETUP_BACKCAR_PROTOCOL_CVBS);
	}
}

void appToSys_Setup_BackCar_CVBS_Or_USB_OK_MouseUp()
{
	DisplayingOrHidingSysUI_aboutReversingCameraEquipment(true);
}

void appToSys_Setup_SysBACKCAR_SET_CVBS_OR_USB_PROMPT_OKOrCANCEL_MouseUp(u8 p)
{
	DisplayingOrHidingSysUI_aboutReversingCameraEquipment(false);
	if(p == 0){//sure
		if(pLocalParam->uBackCarSetCvbsOrUSB != pLocalParam->uSetCvbsOrUSBTemp)
		{
			pLocalParam->uBackCarSetCvbsOrUSB = pLocalParam->uSetCvbsOrUSBTemp;
			System_notifyApp_cvbsOrUsbSwitch(pLocalParam->uBackCarSetCvbsOrUSB);
			systemToHal_SimulateKey(SYSTEMTOHAL_SIMKEY_RESET);
		}
	}
	else if(p == 1)//cancel
	{
		pLocalParam->uSetCvbsOrUSBTemp = pLocalParam->uBackCarSetCvbsOrUSB;
		DisplaySysToUI_aboutBackCarProtocolCVBSorUSB(!pLocalParam->uBackCarSetCvbsOrUSB);
		DisPlayingReverseCameraType(pLocalParam->uBackCarSetCvbsOrUSB);
	}
}

void setRGBValueToUI(u8 pR,u8 pG,u8 pB)
{
	DisplayUI_AmbientLed_R_bar_text(pR);
	DisplayUI_AmbientLed_G_bar_text(pG);
	DisplayUI_AmbientLed_B_bar_text(pB);
} 


void setR_G_B_BarValue(u8 temp,u8 tag )
{
	u8 TP[6] = {0};
	switch(tag)
	{
		case 0x00:  //red
		{
			TP[0] = temp;
			TP[1] = 0;
			TP[2] = pLocalParam->uAmbientLedGValue[0];
			TP[3] = 0;
			TP[4] = pLocalParam->uAmbientLedBValue[0];
			TP[5] = 0;
			systemToHalAboutAmbientLed_SetRGB(TP,6);
		}
		break;
		case 0x04: //Blu
		{
			TP[0] = pLocalParam->uAmbientLedRValue[0];
			TP[1] = 0;
			TP[2] = pLocalParam->uAmbientLedGValue[0];
			TP[3] = 0;
			TP[4] = temp;
			TP[5] = 0;
			systemToHalAboutAmbientLed_SetRGB(TP,6);
		}
		break;
		case 0x08:  //Gre
		{
			TP[0] = pLocalParam->uAmbientLedRValue[0];
			TP[1] = 0;
			TP[2] = temp;
			TP[3] = 0;
			TP[4] = pLocalParam->uAmbientLedBValue[0];
			TP[5] = 0;
			systemToHalAboutAmbientLed_SetRGB(TP,6);
		}
		break;
	}
}

void jumpToPageSetRGB()
{
	switch_Page(PAGE_SYSTEM_SET_LED_RGB_PAGE);
	setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_SHOW_CUR_COLOR, pLocalParam->uShowCurColorValue );
	setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_SHOW_CHANGED_COLOR, pLocalParam->uShowCurColorValue );
}
void setCustomizeColorAndDimming(SAVE_RGB_DIMMING_VALUE t)
{
	u8 TP[6] = {0};
	TP[0] = t.uAmbientLedSaveRValue[0];
	TP[1] = t.uAmbientLedSaveRValue[1];
	TP[2] = t.uAmbientLedSaveGValue[0];
	TP[3] = t.uAmbientLedSaveGValue[1];
	TP[4] = t.uAmbientLedSaveBValue[0];
	TP[5] = t.uAmbientLedSaveBValue[1];
	systemToHalAboutAmbientLed_SetRGB(TP,6);
}

SAVE_RGB_DIMMING_VALUE saveCustomizeColorVale(u8 *param,u8 nTem,u8 nDimming)
{
	SAVE_RGB_DIMMING_VALUE temp ;
	memset(&temp, 0, sizeof(SAVE_RGB_DIMMING_VALUE));
	temp.uAmbientLedSaveRValue[0] = param[0];
	temp.uAmbientLedSaveRValue[1] = param[1];
	
	temp.uAmbientLedSaveGValue[0] = param[2];
	temp.uAmbientLedSaveGValue[1] = param[3];
	
	temp.uAmbientLedSaveBValue[0] = param[4];
	temp.uAmbientLedSaveBValue[1] = param[5];
	temp.uShowCurSaveColorValue = nTem;
	return temp;
}

void initCustomizeColorButen()
{
	int nTem = 0;
  	nTem += (int)((pLocalParam->eSaveRGB_Dimming_value[0].uAmbientLedSaveRValue[0]  <<  24) & 0xFF000000);
	nTem += (int)((pLocalParam->eSaveRGB_Dimming_value[0].uAmbientLedSaveGValue[0] << 16) & 0xFF0000);
	nTem += (int)((pLocalParam->eSaveRGB_Dimming_value[0].uAmbientLedSaveBValue[0] << 8) & 0xFF00);
	nTem += (int)(pLocalParam->uAmbientLedDimmValue & 0xFF);
	setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_SHOW_CHOOSE_COLOR,nTem);
}
void appToSys_Set_Screen_Brightness_value(u8 p)
{
	
	u8 uTem = pLocalParam->cBrightness_RangeValue;
	if(p == 1)
	{
		if(uTem == AMBIENT_SCREEN_BRIGHTNESS_MIN)
		{
			uTem = AMBIENT_SCREEN_BRIGHTNESS_MAX;
		}
		else
		{
			uTem--;
		}
	}
	else if(p == 0)
	{
		if(uTem == AMBIENT_SCREEN_BRIGHTNESS_MAX)
		{
			uTem = AMBIENT_SCREEN_BRIGHTNESS_MIN;
		}
		else
		{
			uTem++;
		}
	}

	systemToHal_SetScreenBrightnessValue(uTem);
}

void ToUI_BackCarVideo_TraceType_System(u8 em)
{
	DisplayUI_aboutBackCar_Line_Type(em);
	systemToModule_NotifyBackModule_BackCarVideoTraceLine_Type_Set(em);
}

void DisplayUI_aboutBackCar_Line_Type(u8 p)
{
	switch(p)
	{
		case 0x00:
			setDigitalData(CONTROLID_SETUP_BACK_CAR_CURVE_LINE,1);
			setDigitalData(CONTROLID_SETUP_BACK_CAR_TRAPEZOID,0);
			setDigitalData(CONTROLID_SETUP_BACK_CAR_FORK,0);
		break;
		case 0x01:
			setDigitalData(CONTROLID_SETUP_BACK_CAR_TRAPEZOID,1);
			setDigitalData(CONTROLID_SETUP_BACK_CAR_CURVE_LINE,0);
			setDigitalData(CONTROLID_SETUP_BACK_CAR_FORK,0);
		break;
		case 0x02:
			setDigitalData(CONTROLID_SETUP_BACK_CAR_FORK,1);
			setDigitalData(CONTROLID_SETUP_BACK_CAR_TRAPEZOID,0);
			setDigitalData(CONTROLID_SETUP_BACK_CAR_CURVE_LINE,0);
		break;
		default:
		break;
	}
}

void DisplayingOrHidingSysUI_aboutReversingCameraEquipment(u8 state)
{
	setUpdateUI(false);
	setVisible(CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_PROMPT_BOX, state);
	setVisible(CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_PROMPT_TEXT_1, state);
	setVisible(CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_PROMPT_TEXT_2, state);
	setVisible(CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_PROMPT_SURE, state);
	setVisible(CONTROLID_SYSTEM_BACKCAR_SET_CVBS_OR_USB_PROMPT_CANCEL, state);
	setUpdateUI(true);
}
void SetDayAndNightMode(u8 buf)
{
	  LOGD("pLocalParam->curDayAndNightMode:0x%x-----buf:0x%x",pLocalParam->curDayAndNightMode,buf);
	  if(pLocalParam->curDayAndNightMode == buf)
	  	return;
	  switch(buf)
	  {
	  	case 0x00:
			setSystemToHal_DayOrNight(0x00);
		break;
	  	case 0x01:
			setSystemToHal_DayOrNight(0x01);
		break;
		case 0x02:
			setSystemToHal_DayOrNight(0x02);
		break;
		default:break;
	  }
}
void DisPlayingReverseCameraType(u8 p)
{
	switch(p)
	{
		case 0x00:
		{
			setDigitalData(CONTROLID_SETUP_REVERSE_CAMERA_USB,true);
			setDigitalData(CONTROLID_SETUP_REVERSE_CAMERA_CVBS,false);
		}
		break;
		case 0x01:
		{
			setDigitalData(CONTROLID_SETUP_REVERSE_CAMERA_USB,false);
			setDigitalData(CONTROLID_SETUP_REVERSE_CAMERA_CVBS,true);
		}
		break;
		default:break;
	}
}

void appToSys_Setup_Reverse_Camera_MouseUp(u8 p)
{
	if(p == pLocalParam->uSetCvbsOrUSBTemp)
		return;
	pLocalParam->uSetCvbsOrUSBTemp = p;
	DisPlayingReverseCameraType(p);
}

void appToSys_Setup_Panel_Light_Bar_MouseUp(u8 param)
{
	if(param > 17 ||param < 0)
		return;
	u8 nTemp = param + PANEL_LIGHT_MIN;
	systemToHal_KeyLedBrightness(nTemp);
}

void appToSys_Setup_Panel_Light_Button_MouseUp()
{
	LOGD("[%s] :%x",__FUNCTION__,pLocalParam->u8_Sys_PanelLight);
	if(pLocalParam->u8_Sys_PanelLight == 0xff)
	{
		setVisible(CONTROLID_SETUP_SET_PANEL_LIGHT_GRAY_BAR,0);
		setVisible(CONTROLID_SETUP_SET_PANEL_LIGHT_BAR,1);
		setDigitalData(CONTROLID_SETUP_SET_PANEL_LIGHT_AUTO_BUTTON,0);
		systemToHal_KeyLedBrightness(pLocalParam->u8_Sys_PanelLight_bef);
	}
	else
		systemToHal_KeyLedBrightness(0xff);
}

void showPanelLightValue(u8 param)
{
	u8 ansiBuf[8];
	u8 *strAuto = (u8*)"Auto";
	memset(ansiBuf, 0, 8);
	if(param == 0xff)
		memcpy(ansiBuf, strAuto, strlen((char*)strAuto));
	else
		sprintf((char*)ansiBuf,"%d",param);

	int nAnsiBufLen = strlen((char*)ansiBuf);
	u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
	memset(unicodeBuf, 0, nAnsiBufLen*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicodeBuf);
	setSerialData(CONTROLID_SETUP_PANEL_LIGHT_TEXT,unicodeBuf, nUnicodeBufLen*2);
}

void appToSys_Setup_Radio_Area_Selection_MouseUp(u8 param)
{
	LOGD("[%s] param:%x -----%x",__FUNCTION__,param,pLocalParam->u8_Sys_RadioCountryCode);
	if(param == pLocalParam->u8_Sys_RadioCountryCode)
		return;
	systemToRadioHal_SetRadioArea(param);
}

void appToSys_Setup_PowerVol_Bar_MouseUp(u8 param)
{
  	if(pLocalParam->osdDebugSwith)
  		pLocalParam->DebugSwitch = true;
	if((param > pLocalParam->Start_MaxVol || param < pLocalParam->Start_minVol) && param != 0xff)
		return;
	if(pLocalParam->u8_Sys_StartupVol != 0xff)
		pLocalParam->u8_Sys_StartupVol_bef = pLocalParam->u8_Sys_StartupVol;
	pLocalParam->u8_Sys_StartupVol = param;
	u8 ansiBuf[16];
	memset(ansiBuf, 0, 16);
	u8 *pStrLastValume = (u8*)"Last Volume";
	if(param == 0xFF)
	{
		memcpy(ansiBuf, pStrLastValume, strlen((char*)pStrLastValume));
		setVisible(CONTROLID_SETUP_SET_BOOT_VOLUME_BAR,0);
		setVisible(CONTROLID_SETUP_SET_BOOT_VOLUME_GRAY_BAR,1);
		setDigitalData(CONTROLID_SETUP_SET_BOOT_VOLUME_FOLLOW_BUTTON,0);
	}
	else
	{
		sprintf((char*)ansiBuf,"%d",pLocalParam->u8_Sys_StartupVol);
		setVisible(CONTROLID_SETUP_SET_BOOT_VOLUME_GRAY_BAR,0);
		setVisible(CONTROLID_SETUP_SET_BOOT_VOLUME_BAR,1);
		setAnalogData(CONTROLID_SETUP_SET_BOOT_VOLUME_BAR,param -pLocalParam->Start_minVol);
		setDigitalData(CONTROLID_SETUP_SET_BOOT_VOLUME_FOLLOW_BUTTON,1);
	}

	int nAnsiBufLen = strlen((char*)ansiBuf);
	u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
	memset(unicodeBuf, 0, nAnsiBufLen*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicodeBuf);
	setSerialData(CONTROLID_SETUP_POWER_VOL_TEXT,unicodeBuf,nUnicodeBufLen*2);
	if(param != 0xFF){
		setSerialData(CONTROLID_SETUP_SET_BOOT_VOLUME_TXT_NEW,unicodeBuf,nUnicodeBufLen*2);
		}
	systemToModule_NotifySoundModule_StartupVol(pLocalParam->u8_Sys_StartupVol);
	free(unicodeBuf);
	
}


void appToSys_Setup_PowerVol_Bar_Jump_set(u8 param)
{
	u8 ansiBuf[16];
	memset(ansiBuf, 0, 16);
	u8 *pStrLastValume = (u8*)" ";
	if(param == 0xFF)
	{
		memcpy(ansiBuf, pStrLastValume, strlen((char*)pStrLastValume));
		setVisible(CONTROLID_SETUP_SET_BOOT_VOLUME_BAR,0);
		setVisible(CONTROLID_SETUP_SET_BOOT_VOLUME_GRAY_BAR,1);
	}
	else
	{
		sprintf((char*)ansiBuf,"%d",param);
		setVisible(CONTROLID_SETUP_SET_BOOT_VOLUME_GRAY_BAR,0);
		setVisible(CONTROLID_SETUP_SET_BOOT_VOLUME_BAR,1);
		setAnalogData(CONTROLID_SETUP_SET_BOOT_VOLUME_BAR,param -pLocalParam->Start_minVol);
	}
}





void appToSys_Setup_PowerVol_Bar_Mouse_Time(u8 param)
{
	u8 ansiBuf[16];
	memset(ansiBuf, 0, 16);
	sprintf((char*)ansiBuf,"%d",param);
	int nAnsiBufLen = strlen((char*)ansiBuf);
	u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
	memset(unicodeBuf, 0, nAnsiBufLen*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicodeBuf);
	setSerialData(CONTROLID_SETUP_POWER_VOL_TEXT,unicodeBuf,nUnicodeBufLen*2);
	setSerialData(CONTROLID_SETUP_SET_BOOT_VOLUME_TXT_NEW,unicodeBuf,nUnicodeBufLen*2);
	free(unicodeBuf);
}

void appToSys_Setup_PowerVol_Bar_Mouse_Up(u8 param)
{
	pLocalParam->u8_Sys_StartupVol_bef = pLocalParam->u8_Sys_StartupVol;
	pLocalParam->u8_Sys_StartupVol = param;
	u8 ansiBuf[16];
	memset(ansiBuf, 0, 16);
	sprintf((char*)ansiBuf,"%d",param);
	int nAnsiBufLen = strlen((char*)ansiBuf);
	u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
	memset(unicodeBuf, 0, nAnsiBufLen*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicodeBuf);
	setSerialData(CONTROLID_SETUP_POWER_VOL_TEXT,unicodeBuf,nUnicodeBufLen*2);
	setSerialData(CONTROLID_SETUP_SET_BOOT_VOLUME_TXT_NEW,unicodeBuf,nUnicodeBufLen*2);
	systemToModule_NotifySoundModule_StartupVol(pLocalParam->u8_Sys_StartupVol);
	free(unicodeBuf);
}


void systemToApp_SetPowerVol_BarMaxValue()
{
	u16 barMax = 0;
	u16 minValue = 0;
	u16 maxValue = 0;
	minValue =  pLocalParam->Start_minVol;
	maxValue = pLocalParam->Start_MaxVol;
	barMax = maxValue - minValue;
	LOGD("barMax:%d",barMax);
	setProgressRange(CONTROLID_SETUP_SET_BOOT_VOLUME_BAR, barMax);
}

void appToSys_Setup_Default_Boot_Animation(u8 param)
{
	showDefault_Boot_Animation_Button(param + 1);
	setDefault_Boot_Animation_Prop(param + 1);
}

void showDefault_Boot_Animation_Button(u8 param)
{
	switch(param)
	{
		case 0x01:
			{
				setDigitalData(CONTROLID_SETUP_BOOT_ANIMATION_WATER_DROPS,1);
				setDigitalData(CONTROLID_SETUP_BOOT_ANIMATION_WATER_WAVE,0);
				setDigitalData(CONTROLID_SETUP_BOOT_ANIMATION_WATER_FLASH,0);
			}
			break;
		case 0x02:
			{
				setDigitalData(CONTROLID_SETUP_BOOT_ANIMATION_WATER_DROPS,0);
				setDigitalData(CONTROLID_SETUP_BOOT_ANIMATION_WATER_WAVE,1);
				setDigitalData(CONTROLID_SETUP_BOOT_ANIMATION_WATER_FLASH,0);
			}
			break;
		case 0x03:
			{
				setDigitalData(CONTROLID_SETUP_BOOT_ANIMATION_WATER_DROPS,0);
				setDigitalData(CONTROLID_SETUP_BOOT_ANIMATION_WATER_WAVE,0);
				setDigitalData(CONTROLID_SETUP_BOOT_ANIMATION_WATER_FLASH,1);
			}
			break;
		default:
			LOGD("[%s] param:%x",__FUNCTION__,param);
			break;
	}
}
 void setDefault_Boot_Animation_Prop(u8 param)
 {
 	char property[PROPERTY_VALUE_MAX];
	sprintf(property,"%d", param);
   	property_set("persist.bootanim.type",property);
 }

  void getDefault_Boot_Animation_Prop()
 {
 	int param;
 	char property[PROPERTY_VALUE_MAX];
	property_get("persist.bootanim.type",property,"3");
	sscanf(property,"%d",&param);
	showDefault_Boot_Animation_Button(param);
 }

void showDayOrNightModeStatus(u8 buf)
{
	switch(buf)
	{
		case 0x00:
		{
			setDigitalData(CONTROLID_SET_DAY_AND_NIGHT_MODE_DAY,1);
			setDigitalData(CONTROLID_SET_DAY_AND_NIGHT_MODE_NIGHT,0);
			setDigitalData(CONTROLID_SET_DAY_AND_NIGHT_MODE_AUTO,0);
		}
		break;
		case 0x01:
		{
			setDigitalData(CONTROLID_SET_DAY_AND_NIGHT_MODE_DAY,0);
			setDigitalData(CONTROLID_SET_DAY_AND_NIGHT_MODE_NIGHT,1);
			setDigitalData(CONTROLID_SET_DAY_AND_NIGHT_MODE_AUTO,0);
		}
		break;
		case 0x02:
		{
			setDigitalData(CONTROLID_SET_DAY_AND_NIGHT_MODE_DAY,0);
			setDigitalData(CONTROLID_SET_DAY_AND_NIGHT_MODE_NIGHT,0);
			setDigitalData(CONTROLID_SET_DAY_AND_NIGHT_MODE_AUTO,1);
		}
		break;
		default:break;
	}
}
void appToSys_Sound_Channel_MouseUp(void)
{
	switch_Page(PAGE_SYSTEM_SET_SOUND_CHANNEL_PAGE);
	//systemToHalAboutAmbientLed_Init(0x01);
}

void appToSystem_Setup_Boot_Run_Nav_status(u8 param)
{
	if(pLocalParam->nNavigationBootingRunMod == param)
		return;
	pLocalParam->nNavigationBootingRunMod = param;
	ToUI_SwitchOne_about_SetupIsRunningNavigationStr(pLocalParam->nNavigationBootingRunMod);
	showBoot_Run_Nav_status(param);
}


void showBoot_Run_Nav_status(u8 param)
{
	int i;
	for(i = 0;i < 3;i ++)
	{
		if(param == i)
			setDigitalData(CONTROLID_BOOT_RUN_NAV_FOLLOW + i,1);
		else
			setDigitalData(CONTROLID_BOOT_RUN_NAV_FOLLOW + i,0);
	}
}

void setDefault_Boot_Nav_Baidu()
{
	showDefault_Boot_Nav(0x00);
	pLocalParam->NaviNub = 0;
	appToSys_Setup_Default_NaviGation(-1);

}

void setDefault_Boot_Nav_KaiLiDe()
{
	showDefault_Boot_Nav(0x03);
	pLocalParam->NaviNub = 3;
	appToSys_Setup_Default_NaviGation(-1);
}
void setDefault_Boot_Nav_GaoDe()
{
	showDefault_Boot_Nav(0x02);
	pLocalParam->NaviNub = 2;
	appToSys_Setup_Default_NaviGation(-1);
}
void setDefault_Boot_Nav_TengXun()
{
	showDefault_Boot_Nav(0x01);
	pLocalParam->NaviNub = 1;
	appToSys_Setup_Default_NaviGation(-1);
}

void showDefault_Boot_Nav(u8 param)
{
	int i;
	for(i = 0;i < 4;i ++)
	{
		if(param == i)
			setDigitalData(CONTROLID_START_THE_MAP_BY_DEFAULT_BAIDU + i,1);
		else
			setDigitalData(CONTROLID_START_THE_MAP_BY_DEFAULT_BAIDU + i,0);
	}
}
void showCurTempUnitType(u8 param)
{
	if(param == 0x00)
	{
		setDigitalData(CONTROLID_SETUP_TEMP_UNIT_DISPLAY_C,1);
		setDigitalData(CONTROLID_SETUP_TEMP_UNIT_DISPLAY_F,0);
	}
	else
	{
		setDigitalData(CONTROLID_SETUP_TEMP_UNIT_DISPLAY_C,0);
		setDigitalData(CONTROLID_SETUP_TEMP_UNIT_DISPLAY_F,1);
	}
}

void showCurDistanceUnitType(u8 param)
{
	if(param == 0x00)
	{
		setDigitalData(CONTROLID_SETUP_CARINFO_UINT_DISTANCE_KM,1);
		setDigitalData(CONTROLID_SETUP_CARINFO_UINT_DISTANCE_MILES,0);
	}
	else
	{
		setDigitalData(CONTROLID_SETUP_CARINFO_UINT_DISTANCE_KM,0);
		setDigitalData(CONTROLID_SETUP_CARINFO_UINT_DISTANCE_MILES,1);
	}
}

void showCameraDelaySwitchStatus(u8 param)
{
	if(param == 0x00)
		setDigitalData(CONTROLID_SETUP_CAMERA_DELAYS_WITCH,0);
	else 
		setDigitalData(CONTROLID_SETUP_CAMERA_DELAYS_WITCH,1);
}

void appToSys_Sound_Channel_Back(void)
{
	systemToModule_NotifySystem_JumpPrePage();
}

void analyseAppToSystemSoundChannelMessage(u32 ctrlId,u8 param)
{
	u8 n = (ctrlId -CONTROLID_SETUP_SOUND_CHANNEL_PAGE_MEDIA_BAR )/2 + 1;
	if(ctrlId == CONTROLID_SETUP_SOUND_CHANNEL_PAGE_CALL_BAR)
		param = param + 10;
	systemToApp_Sound_Channel_Volume_Adjust(n,param);
}

void showSoundChannelVolume_Bar( u32 ctrlId,u8 p)
{
	setAnalogData(ctrlId,p);
	setSoundChannelVolumeValue(ctrlId,p);
}
void setSoundChannelVolumeValue(u32 ctrlId,u8 p)
{
	char TempStr[10] = {0};
	if(ctrlId == CONTROLID_SETUP_SOUND_CHANNEL_PAGE_CALL_BAR)
		p = p + 10;
	unicode16_t uTempStr[20];
	sprintf(TempStr, "%d", p);
	int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
	setSerialData(ctrlId + 1,(u8*)uTempStr,len*2);
}
void thirdDailingOption()
{
	if(pLocalParam->curDailingOption == 0x00)
		pLocalParam->curDailingOption = 0x01;
	else if(pLocalParam->curDailingOption == 0x01)
		pLocalParam->curDailingOption = 0x00;
	showThirdDailingOption(pLocalParam->curDailingOption);
	saveThirdDailingOption();
}

void showThirdDailingOption(u8 p)
{
	switch(p)
	{
		case 0x01:
			setStringText(CONTROLID_SETUP_THIRD_PARTY_DAIL_OPTION_TXT, STRINGID_SYSTEM_SETUP_THIRD_PARTY_DAIL_OPTION_3G);
			break;
		case 0x00:
			setStringText(CONTROLID_SETUP_THIRD_PARTY_DAIL_OPTION_TXT, STRINGID_SYSTEM_SETUP_THIRD_PARTY_DAIL_OPTION_BT);
			break;
		default:break;
	}
}
void saveThirdDailingOption()
{
	char property[PROPERTY_VALUE_MAX];
	sprintf(property,"%d",pLocalParam->curDailingOption);
	property_set("fly.flyui.unifiedcall",property);
}

void appToSys_Setup_DesktopNavigationMapInformationsSyncSwitch_ON_MouseUp(void)
{
	DisplayDesktopNavigationMapInformationsSyncSwitchButtonUI(true);
	System_notifyApp_DesktopNavigationMapInformationsSyncSwitchState(0);
	pLocalParam->uDesktopNivaInforSwitch = 0;
}

void appToSys_Setup_DesktopNavigationMapInformationsSyncSwitch_OFF_MouseUp(void)
{
	DisplayDesktopNavigationMapInformationsSyncSwitchButtonUI(false);
	System_notifyApp_DesktopNavigationMapInformationsSyncSwitchState(1);
	pLocalParam->uDesktopNivaInforSwitch = 1;
}

void DisplayDesktopNavigationMapInformationsSyncSwitchButtonUI(bool b)
{
	setDigitalData(CONTROLID_SETUP_DESKTOP_NAVIGATION_MAP_INFOR_SWITCH_SYNC, b);
}

void appToSys_Setup_ScreenBrithnessAutoAdjust_Switch_MouseUp(u8 p)
{
	systemToHal_AutoAdjustmentSwitchOfScreenBrightness(p);
}

void DisplayScreenBrithnessAutoAdjustSwitchButtonUI(bool b)
{
	setDigitalData(CONTROLID_SET_SCREEN_BRIGHTNESS_AUTOMATIC_ADJUSTMENT_SWTICH, b);
}

void appToSys_Setup_AmbientLedColorSet_MouseUp(u32 ctrlID)
{
	u8 param = 0xFF;
	param = AmbientLed_ID_To_Data(ctrlID);
	if(param != 0xFF)
		systemToModule_NotifyExtcarModule_AmbientLedColor_HighModelFord(param);
}

u8 AmbientLed_ID_To_Data(u32 ID)
{
	u8 p = 0xFF;
	switch(ID)
	{
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_ORANGE:
			p = 0x02;
		break;
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_RED:
			p = 0x04;
		break;
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_SOFT_BLUE:
			p = 0x03;
		break;
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_ICE_BLUE:
			p = 0x01;
		break;
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_BLUE:
			p = 0x06;
		break;
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_PURPLE:
			p = 0x07;
		break;
		case CONTROLID_SETUP_AMBIENT_LED_COLOR_GREEN:
			p = 0x05;
		break;
		default:break;
	}

	return p;
}

void DisplayUI_switch_AmbientLedColor_Ford(u8 p)
{
	switch(p)
	{
		case 0x02:
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ORANGE,1);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_RED,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_SOFT_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ICE_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_PURPLE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_GREEN,0);
		break;
		case 0x04:
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ORANGE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_RED,1);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_SOFT_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ICE_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_PURPLE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_GREEN,0);
		break;
		case 0x03:
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ORANGE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_RED,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_SOFT_BLUE,1);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ICE_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_PURPLE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_GREEN,0);
		break;
		case 0x01:
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ORANGE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_RED,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_SOFT_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ICE_BLUE,1);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_PURPLE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_GREEN,0);
		break;
		case 0x06:
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ORANGE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_RED,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_SOFT_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ICE_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_BLUE,1);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_PURPLE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_GREEN,0);
		break;
		case 0x07:
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ORANGE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_RED,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_SOFT_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ICE_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_PURPLE,1);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_GREEN,0);
		break;
		case 0x05:
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ORANGE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_RED,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_SOFT_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ICE_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_PURPLE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_GREEN,1);
		break;
		case 0x00:
		case 0xFF:
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ORANGE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_RED,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_SOFT_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_ICE_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_BLUE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_PURPLE,0);
			setDigitalData(CONTROLID_SETUP_AMBIENT_LED_COLOR_GREEN,0);
			break;
		default:break;
	}
}

void DisplayUI_AmbientLedColorTxt_Ford(u8 p)
{
	u32 stringID = 0xFF;
	switch(p)
	{
		case 0x02:
			stringID = STRING_CAR_AMBIENT_LED_COLOR_ORANGE;
		break;
		case 0x04:
			stringID = STRING_CAR_AMBIENT_LED_COLOR_RED;
		break;
		case 0x03:
			stringID = STRING_CAR_AMBIENT_LED_COLOR_SOFT_BLUE;
		break;
		case 0x01:
			stringID = STRING_CAR_AMBIENT_LED_COLOR_ICE_BLUE;
		break;
		case 0x06:
			stringID = STRING_CAR_AMBIENT_LED_COLOR_BLUE;
		break;
		case 0x07:
			stringID = STRING_CAR_AMBIENT_LED_COLOR_VIDLET;
		break;
		case 0x05:
			stringID = STRING_CAR_AMBIENT_LED_COLOR_GREEN;
		break;
		case 0x00:
			stringID = STRING_CAR_AMBIENT_LED_COLOR_CLOSE;
			break;
		default:break;
	}

	if(stringID != 0xFF)
		setStringText(CONTROLID_SETUP_AMBIENT_LED_COLOR_TXT,stringID);
}

void DisplayUI_AmbientLedBrightnessValue_Ford(u16 param)
{
	char szMsg[20] = {0};
	sprintf(szMsg, "(%d%%)", param);
	setAnsiSerialData(CONTROLID_SETUP_AMBIENT_LED_BRIGHTNESS_VALUE, (u8*)szMsg, strlen(szMsg));
}

void Step_AmbientLedBrightnessScrollBar_Ford(u32 max)
{
	setProgressRange(CONTROLID_SETUP_AMBIENT_LED_BRIGHTNESS_SCROLL_BAR,max);
}

void DisplayUI_AmbientLedBrightnessScrollBar_Ford(u32 param)
{
	setAnalogData(CONTROLID_SETUP_AMBIENT_LED_BRIGHTNESS_SCROLL_BAR,param);
}

void appToSys_Setup_Ambient_Led_Brightness_Bar_Mouse_Time(u16 p)
{
	DisplayUI_AmbientLedBrightnessValue_Ford(p);
}

void appToSys_Setup_Ambient_Led_Brightness_Bar_Mouse_Up(u16 p)
{
	u8 szMsg[4] = {0xFF,0xFF,0xFF,0xFF};
	memcpy(&szMsg[0],&pLocalParam->fordAlmBrightnessMaxValue,2);
	memcpy(&szMsg[2],&p,2);

	DisplayUI_AmbientLedBrightnessValue_Ford(p);
	DisplayUI_AmbientLedBrightnessScrollBar_Ford(p);
	systemToModule_NotifyExtcarModule_AmbientLedBrightness_HighModelFord(szMsg);
}

void DisplayUI_AmbientLedBrightnessEnable_Ford(bool b)
{
	setUpdateUI(false);
	setVisible(CONTROLID_SETUP_AMBIENT_LED_BRIGHTNESS_SCROLL_BAR,b);
	setVisible(CONTROLID_SETUP_AMBIENT_LED_BRIGHTNESS_TXT,b);
	setVisible(CONTROLID_SETUP_AMBIENT_LED_BRIGHTNESS_VALUE,b);
	setUpdateUI(true);
}

void appToSys_Setup_DistanceUint_Mouse_Up(u8 p)
{
	systemToModule_NotifyExtcarModule_DistanceUnit_HighModelFord(p);
}

void appToSys_Setup_MCS_Main_JumpPage_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = pLocalParam->st_MCS[side - 1].uChMk;
	cmd = 0x00;

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	
	setMultiContouredSeats_Control(side,select,cmd,state);

	if(s == 0)//DOWN
	{
	}
	else if(s == 1)//UP
	{
		switch(select)
		{
			case 0x01:
			case 0x02:
			case 0x03:
			case 0x04:
			case 0x05:
				systemToModule_NotifySystem_JumpPage(PAGE_MULTI_CONTOURED_SEATS_ADJUST);
			break;
			case 0x06:
			case 0x07:
				systemToModule_NotifySystem_JumpPage(PAGE_MULTI_CONTOURED_SEATS_MASSAGE);
			break;
		}
		
	}
}

void appToSys_Setup_MCS_Adjust_JumpPage_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x02;
	cmd = 0x00;

	u8 curSelect = pLocalParam->st_MCS[side - 1].uChMk;
	switch(curSelect)
	{
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
			return;
		break;
	}

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void appToSys_Setup_MCS_Adjust_UpperLumbarPre_SCROLL_BAR_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x03;
	cmd = 0x00;

	if(pLocalParam->st_MCS[side - 1].uChMk == select)
		return;

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void appToSys_Setup_MCS_Adjust_UpperLumbarPre_Touch_Screen(u8 p,u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x03;
	if(p == 0)//DEC
	{
		cmd = 0x03;
	}
	else if(p == 1)//INC
	{
		cmd = 0x02;
	}

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}

	setMultiContouredSeats_Control(side,select,cmd,state);
}

void UI_Display_Adjust_UpperLumbarPre(u8 p1,u8 p2)
{
	if(p1 == 21)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_SCROLL_BAR, 0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_SCROLL_BAR, 1);
	}
	
	setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_SCROLL_BAR,p1);
	setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_LUMBAR_PRE_ICON,p2);
}

void appToSys_Setup_MCS_Adjust_MidLumbarPre_SCROLL_BAR_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x02;
	cmd = 0x00;

	if(pLocalParam->st_MCS[side - 1].uChMk == select)
		return;

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void appToSys_Setup_MCS_Adjust_MidLumbarPre_Touch_Screen(u8 p,u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x02;
	if(p == 0)//DEC
	{
		cmd = 0x03;
	}
	else if(p == 1)//INC
	{
		cmd = 0x02;
	}

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}

	setMultiContouredSeats_Control(side,select,cmd,state);
}

void UI_Display_Adjust_MidLumbarPre(u8 p1,u8 p2)
{
	if(p1 == 21)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_SCROLL_BAR, 0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_SCROLL_BAR, 1);
	}
	
	setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_SCROLL_BAR,p1);
	setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_MID_LUMBAR_PRE_ICON,p2);
}

void appToSys_Setup_MCS_Adjust_LowerLumbarPre_SCROLL_BAR_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x01;
	cmd = 0x00;

	if(pLocalParam->st_MCS[side - 1].uChMk == select)
		return;

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void appToSys_Setup_MCS_Adjust_LowerLumbarPre_Touch_Screen(u8 p,u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x01;
	if(p == 0)//DEC
	{
		cmd = 0x03;
	}
	else if(p == 1)//INC
	{
		cmd = 0x02;
	}

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}

	setMultiContouredSeats_Control(side,select,cmd,state);
}

void UI_Display_Adjust_LowerLumbarPre(u8 p1,u8 p2)
{
	if(p1 == 21)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_SCROLL_BAR, 0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_SCROLL_BAR, 1);
	}
	setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_SCROLL_BAR,p1);
	setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_LUMBAR_PRE_ICON,p2);
}

void appToSys_Setup_MCS_Adjust_UpperBolsterPre_SCROLL_BAR_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x05;
	cmd = 0x00;

	if(pLocalParam->st_MCS[side - 1].uChMk == select)
		return;

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void appToSys_Setup_MCS_Adjust_UpperBolsterPre_Touch_Screen(u8 p,u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x05;
	if(p == 0)//DEC
	{
		cmd = 0x03;
	}
	else if(p == 1)//INC
	{
		cmd = 0x02;
	}

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}

	setMultiContouredSeats_Control(side,select,cmd,state);
}

void UI_Display_Adjust_UpperBolsterPre(u8 p1,u8 p2)
{
	if(p1 == 21)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_SCROLL_BAR, 0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_SCROLL_BAR, 1);
	}
	
	setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_SCROLL_BAR,p1);
	setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_UPPER_BOLSTER_PRE_ICON,p2);
}

void appToSys_Setup_MCS_Adjust_LowerBolsterPre_SCROLL_BAR_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x04;
	cmd = 0x00;

	if(pLocalParam->st_MCS[side - 1].uChMk == select)
		return;

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void appToSys_Setup_MCS_Adjust_LowerBolsterPre_Touch_Screen(u8 p,u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x04;
	if(p == 0)//DEC
	{
		cmd = 0x03;
	}
	else if(p == 1)//INC
	{
		cmd = 0x02;
	}

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}

	setMultiContouredSeats_Control(side,select,cmd,state);
}

void UI_Display_Adjust_LowerBolsterPre(u8 p1,u8 p2)
{
	if(p1 == 21)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_SCROLL_BAR, 0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_SCROLL_BAR, 1);
	}
	
	setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_SCROLL_BAR,p1);
	setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_LOWER_BOLSTER_PRE_ICON,p2);
}

void appToSys_Setup_MCS_Adjust_DriverSide_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = 0x01;
	//if(pLocalParam->selectSeatSide == side)
	//	return;
	
	u8 selected = pLocalParam->st_MCS[0].uChMk;
	if(selected != 0x06 && selected != 0x07){
		select = 0X02;
	}
	else{
		select = selected;
	}
	
	cmd = 0x00;

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void UI_Display_Adjust_DriverSide_State(u8 p)
{
	if(p == 0xFF)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_STATE_ICON, 0);
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_STATE_ICON,0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_STATE_ICON, 1);
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_STATE_ICON,p);
	}
}

void appToSys_Setup_MCS_Adjust_PassengerSide_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = 0x02;
	//if(pLocalParam->selectSeatSide == side)
	//	return;
	
	u8 selected = pLocalParam->st_MCS[1].uChMk;
	if(selected != 0x06 && selected != 0x07){
		select = selected;
	}
	else{
		select = 0x02;
	}
	
	cmd = 0x00;

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void UI_Display_Adjust_PassengerSide_State(u8 p)
{
	if(p == 0xFF)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_STATE_ICON, 0);
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_STATE_ICON,0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_STATE_ICON, 1);
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_STATE_ICON,p);
	}
}

void appToSys_Setup_MCS_Passage_JumpPage_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x07;
	cmd = 0x00;

	/*
	u8 curSelect = pLocalParam->st_MCS[side - 1].uChMk;
	switch(curSelect)
	{
		case 0x06:
		case 0x07:
			return;
		break;
	}
	*/

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void appToSys_Setup_MCS_Passage_UpperLumbarSet_Touch_Screen(u8 p,u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x06;
	if(p == 0)//close
	{
		cmd = 0x04;
	}
	else if(p == 1)//low
	{
		cmd = 0x05;
	}
	else if(p == 2)//mid
	{
		cmd = 0x06;
	}
	else if(p == 3)//high
	{
		cmd = 0x07;
	}

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void UI_Display_Massage_Passage_UpperLumbarSelectedState(u8 p)
{
	setVisible(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_SELECTED_STATE,p);	
}

void UI_Display_Massage_Passage_UpperLumbarSet(u8 p)
{
	setUpdateUI(0);

	if(p == 0xFF)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_CLOSE, 0);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_LOW, 0);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_HIGH, 0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_CLOSE, 1);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_LOW, 1);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_HIGH, 1);
	}
	
	switch(p)
	{
		case 1://close
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_CLOSE,1);		
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_LOW,0);
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_HIGH,0);
		break;
		case 2://low
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_CLOSE,0);		
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_LOW,1);
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_HIGH,0);
		break;
		case 3://mid
		break;
		case 4://high
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_CLOSE,0);		
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_LOW,0);
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_HIGH,1);
		break;
		case 0x00:
		case 0xFF:
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_CLOSE,0);		
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_LOW,0);
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_UPPER_LUMBAR_HIGH,0);
		break;
	}
	setUpdateUI(1);
}

void appToSys_Setup_MCS_Passage_LowerLumbarSet_Touch_Screen(u8 p,u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = pLocalParam->selectSeatSide;
	select = 0x07;
	if(p == 0)//close
	{
		cmd = 0x04;
	}
	else if(p == 1)//low
	{
		cmd = 0x05;
	}
	else if(p == 2)//mid
	{
		cmd = 0x06;
	}
	else if(p == 3)//high
	{
		cmd = 0x07;
	}

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void UI_Display_Massage_Passage_LowerLumbarSelectedState(u8 p)
{
	setVisible(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_SELECTED_STATE,p);
}

void UI_Display_Massage_Passage_LowerLumbarSet(u8 p)
{
	setUpdateUI(0);

	if(p == 0xFF)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_CLOSE, 0);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_LOW, 0);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_HIGH, 0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_CLOSE, 1);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_LOW, 1);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_HIGH, 1);
	}
	
	switch(p)
	{
		case 1://close
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_CLOSE,1);		
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_LOW,0);
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_HIGH,0);
		break;
		case 2://low
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_CLOSE,0);		
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_LOW,1);
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_HIGH,0);
		break;
		case 3://mid
		break;
		case 4://high
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_CLOSE,0);		
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_LOW,0);
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_HIGH,1);
		break;
		case 0xFF:
		case 0x00:
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_CLOSE,0);		
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_LOW,0);
		setDigitalData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_LOWER_LUMBAR_HIGH,0);
		break;
	}
	setUpdateUI(1);
}

void appToSys_Setup_MCS_Passage_DriverSide_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = 0x01;
	//if(pLocalParam->selectSeatSide == side)
	//	return;

	u8 selected = pLocalParam->st_MCS[0].uChMk;
	if(selected == 0x06 || selected == 0x07){
		select = selected;
	}
	else{
		select = 0x02;
	}
	
	cmd = 0x00;

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);
}

void UI_Display_Massage_Passage_DriverSide_State(u8 p)
{
	LOGD("[MCS Massage]:%x",p);
	if(p == 0xFF)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_STATE_ICON, 0);
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_STATE_ICON,0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_STATE_ICON, 1);
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_STATE_ICON,p);
	}
}

void appToSys_Setup_MCS_Passage_PassengerSide_Touch_Screen(u8 s)
{
	u8 side = 0xFF;
	u8 select = 0xFF;
	u8 cmd = 0xFF;
	u8 state = 0xFF;

	side = 0x02;
	//if(pLocalParam->selectSeatSide == side)
	//	return;
	
	u8 selected = pLocalParam->st_MCS[1].uChMk;
	if(selected == 0x06 || selected == 0x07){
		select = selected;
	}
	else{
		select = 0x02;
	}
	
	cmd = 0x00;

	if(s == 0)//DOWN
	{
		state = 0x01;
	}
	else if(s == 1)//UP
	{
		state = 0x02;
	}
	setMultiContouredSeats_Control(side,select,cmd,state);

}

void UI_Display_Massage_Passage_PassengerSide_State(u8 p)
{
	if(p == 0xFF)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_STATE_ICON, 0);
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_STATE_ICON,0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_STATE_ICON, 1);
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_STATE_ICON,p);
	}
}

void UI_Display_Select_Seats_Side(u8 p)
{
	setUpdateUI(0);
	if(p == 0xFF)
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_BUTTON, 0);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_BUTTON, 0);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_BUTTON, 0);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_BUTTON, 0);
	}
	else
	{
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_BUTTON, 1);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_BUTTON, 1);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_BUTTON, 1);
		setControllable(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_BUTTON, 1);
	}
	
	if(p == 0x01)//Driver Side
	{
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_BUTTON,1);
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_BUTTON,0);
		
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_BUTTON,1);	
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_BUTTON,0);
	}
	else if(p == 0x02)//Passanger
	{
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_BUTTON,1);	
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_BUTTON,0);
		
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_BUTTON,1);	
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_BUTTON,0);
	}
	else if(p == 0xFF)
	{
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_PASSENGER_SIDE_BUTTON,0);	
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_ADJUST_DRIVER_SIDE_BUTTON,0);
		
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_PASSENGER_SIDE_BUTTON,0);	
		setAnalogData(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_DRIVER_SIDE_BUTTON,0);
	}
	setUpdateUI(1);
}

u8 Seats_PercentageToIntegersValue(u8 p)
{
	u8 t = 0xFF;
	
	if(p == 0xFF)
	t = 0;
	else if(p >= 0 && p <= 10)
	t = 1;
	else if(p >= 11 && p <= 20)
	t = 2;
	else if(p >= 21 && p <= 30)
	t = 3;
	else if(p >= 31 && p <= 40)
	t = 4;
	else if(p >= 41 && p <= 50)
	t = 5;
	else if(p >= 51 && p <= 60)
	t = 6;
	else if(p >= 61 && p <= 70)
	t = 7;
	else if(p >= 71 && p <= 80)
	t = 8;
	else if(p >= 81 && p <= 90)
	t = 9;
	else if(p >= 91 && p <= 100)
	t = 10;

	return t;
}

void UI_Display_MCS_MassageFunction_closing_PromptBox(u8 p)
{
	setVisible(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_FUNCTION_CLOSE_PROMPT_BOX,p);
	setVisible(CONTROLID_MULTI_CONTOURED_SEATS_MASSAGE_FUNCTION_CLOSE_PROMPT_BOX_TXT,p);
}

void showOrHideCarTypeBox(bool param)
{
	setUpdateUI(false);
	setVisible(CONTROLID_SELECTION_CAR_TYPE_CONFIRM_BOX,param);		
	setVisible(CONTROLID_SELECTION_CAR_TYPE_CONFIRM_TXT,param);			
	setVisible(CONTROLID_SELECTION_CAR_TYPE_CONFIRM_BUTTEN,param);
	setVisible(CONTROLID_SELECTION_CAR_TYPE_CANCEL_BUTTEN,param);
	setUpdateUI(true);	
}

void analyseSelectionCarTypeMessage(u8 param)
{
	LOGD("[%s] param:%x",__FUNCTION__,param);
	
	setAnalogData( CONTROLID_SELECTION_CAR_TYPE_START+ pLocalParam->uCurSelectionCarType,0x00);
	setAnalogData( CONTROLID_SELECTION_CAR_TYPE_START+ param,0x01);
	if(pLocalParam->uCurCartype == param)
		setStringText(CONTROLID_SELECTION_CAR_TYPE_CUR_TYPE_TXT, CONTROLID_SELECTION_CAR_TYPE_START + param);
	else
              showOrHideCarTypeBox(true);
	pLocalParam->uCurSelectionCarType = param;
}

void confirmSelectionCurCarType()
{
	showOrHideCarTypeBox(false);
	if(pLocalParam->uCurCartype == pLocalParam->uCurSelectionCarType)
		return;
	pLocalParam->uCurCartype = pLocalParam->uCurSelectionCarType;
	writeParam_aboutCarTypeSelection();
	systemToHal_SetSelectionCarTypeOption(pLocalParam->uCurCartype);
}
