#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appResponseCommand.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"
#include "halRequestFunction.h"
#include "halResponseFunction.h"
#include "unistd.h"
#include "timer_interface.h"

extern CCarInfoCarSettingToyota gclsCarInforCarSettings;

void appInit(void){

}

void appDeInit(void){

}

void analyseAppMessage(unsigned char *buffer, unsigned char len){
       int ctrlId = 0;
       char ctrlType;
       unsigned char paramLen;
       unsigned char *param;
       u8 u8_MouseStatus = 0;

       ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
       ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
       ctrlId += (int)((buffer[2] << 8) & 0xFF00);
       ctrlId += (int)(buffer[3] & 0xFF);

       ctrlType = buffer[4];
       u8_MouseStatus = buffer[5];
       paramLen = len - 5;
       param = &buffer[5];

       LOGD("extcar 2015 AppToExtcar_ctrlType:ctrlId:0x%x.ctrlType:%x u8_MouseStatus:%x\n",ctrlId,ctrlType,u8_MouseStatus);

		//if (CONTROLIDTRAVEL_CARINFO_GOLD_PRADO_TRAVEL_INFORMATION == ctrlId)
		//{
		//	pLocalParam->m_pCarInfo = new CCarInfoToyotaPrado();
		//	pLocalParam->m_pCarInfo->initCarInfo();
		//	pLocalParam->m_pCarInfo->runCarInfo();

		//	u8 prado = 0xB1;
		//	u8 szMsg[16] = {0};
		//	memset(szMsg, 0, sizeof(szMsg));
		//	szMsg[0] = 0x01;
		//	szMsg[1] = 1 | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);  
		//	szMsg[2] = 1 | (1 << 1) | (1 << 4);
		//	szMsg[3] = 33;
		//	szMsg[4] = 88;
		//	szMsg[6] = 99;
		//	analyseHalMessage_EXTCAR(prado, szMsg, 9);

		//	memset(szMsg, 0, sizeof(szMsg));
		//	szMsg[0] = 0x02;
		//	szMsg[1] = 3 | (2 << 3) | (1 << 5) | (1 << 6) | (1 << 7);
		//	szMsg[2] = 1 | (1 << 4);
		//	szMsg[3] = 2 | (2 << 4);
		//	szMsg[4] = 1 | (1 << 4);
		//	analyseHalMessage_EXTCAR(prado, szMsg, 5);

		//	memset(szMsg, 0, sizeof(szMsg));
		//	szMsg[0] = 0x03;
		//	szMsg[1] = 1;
		//	szMsg[2] = 30;
		//	analyseHalMessage_EXTCAR(prado, szMsg, 5);

		//	memset(szMsg, 0, sizeof(szMsg));
		//	szMsg[0] = 0x04;
		//	szMsg[1] = 3;
		//	szMsg[2] = 3 | (1 << 7);//treb
		//	szMsg[3] = 3 | (1 << 7);//mid
		//	szMsg[4] = 4;//bass
		//	szMsg[5] = 5;//bal
		//	szMsg[6] = 6;//fad
		//	analyseHalMessage_EXTCAR(prado, szMsg, 7);

		//	
		//}

	   if (pLocalParam->m_pCarInfo)
	   {
		   bool bRet = false;
		   bRet = pLocalParam->m_pCarInfo->pages(ctrlId, ctrlType, param, paramLen);
		   if (bRet)
			   return;
	   }


	   bool bRet = false;
       bRet = gclsCarInforCarSettings.pages(ctrlId, ctrlType, param, paramLen);
	   if (bRet)
		  return;
	 
      switch(ctrlType)
      {
       case UIACTION_MOUSEUP:
           appToExtcar_MouseUp(ctrlId,u8_MouseStatus,param);
           break;
		case UIACTION_MOUSEDOWN:
			appToExtcar_MouseDown(ctrlId,u8_MouseStatus);
       default:
       break;
      }
}

void appToExtcar_MouseDown(u32 ctrlId,u8 u8_MouseStatus)
{
	bool bRet = false;
	bRet = appToExtcar_golf_setDrivingMode_MouseDown(ctrlId);
	if (bRet == true)
		return;

}

void appToExtcar_MouseUp(u32 ctrlId,u8 u8_MouseStatus,u8 *param)
{
	switch(ctrlId)
	{
		/****************************  ������  ************************************/

		/* ��ҳ��ť */
		case CONTROLID_MENU_DRIVING_INFORMATION:
			//thebug
			//halToExtcar_IsShowSteerInfo(1);
			LOGD("pLocalParam->isShowSteerInfo----%d",pLocalParam->isShowSteerInfo);
 			if(pLocalParam->isShowSteerInfo)
			{
				extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION);
			}
			break;
		case CONTROLID_MENU_DRIVING_INFORMATION_VOLKSWAGEN:
			{
				extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION);
				//SetTimer(3000, 0, EXTCAR_TIMER_ID_TEST);
			}
			break;


		case CONTROLIDTRAVEL_INFORMATION_CAR_SET:
			extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION_CAR_SET1);
			break;
		case CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD:
			extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION_HISTORICAL_RECORD);
			break;
		case CONTROLIDTRAVEL_INFORMATION_BACK:
			//thebug
			//extcarToApp_SetExtcarMenuDisable();
			extcarToModule_NotifySystem_jumpPage(PAGE_MENU);
			break;
		case CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_BACK:
		case CONTROLIDTRAVEL_INFORMATION_CAR_SET_BACK:
			//extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION);
			extcarToModule_NotifySystem_jumpPrePage();
			break;
		/*��extcarҳ������¼*/
		case CONTROLIDTRAVEL_INFORMATION_DELETE:
			break;
		/* ���ð�ť */
		case CONTROLIDTRAVEL_INFORMATION_CAR_SET_SPEED_SENSOR_ON:
			if(u8_MouseStatus == SETUP_ON)
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_SPEED_SENSOR_ON,SETUP_ON);
				pLocalParam->speedLock = SETUP_ON;
				extcarToHal_SetSpeedLockState(SETUP_ON);
			}
			else
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_SPEED_SENSOR_ON,SETUP_OFF);
				pLocalParam->speedLock = SETUP_OFF;
				extcarToHal_SetSpeedLockState(SETUP_OFF);
			}
			break;
		case CONTROLIDTRAVEL_INFORMATION_CAR_SET_SHIFT_LINKAGE_ON:
			if(u8_MouseStatus == SETUP_ON)
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_SHIFT_LINKAGE_ON,SETUP_ON);
				pLocalParam->shiftLock = SETUP_ON;
				extcarToHal_SetShiftLockState(SETUP_ON);
			}
			else
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_SHIFT_LINKAGE_ON,SETUP_OFF);
				pLocalParam->shiftLock = SETUP_OFF;
				extcarToHal_SetShiftLockState(SETUP_OFF);
			}
			break;
		case CONTROLIDTRAVEL_INFORMATION_CAR_SET_P_GEAR_LINKAGE_ON:
			if(u8_MouseStatus == SETUP_ON)
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_P_GEAR_LINKAGE_ON,SETUP_ON);
				pLocalParam->pModeUnlock = SETUP_ON;
				extcarToHal_SetPModeUnlockState(SETUP_ON);
			}
			else
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_P_GEAR_LINKAGE_ON,SETUP_OFF);
				pLocalParam->pModeUnlock = SETUP_OFF;
				extcarToHal_SetPModeUnlockState(SETUP_OFF);
			}
			break;
		case CONTROLIDTRAVEL_INFORMATION_CAR_SET_TOW_UNLOCKED_ON:
			if(u8_MouseStatus == SETUP_ON)
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_TOW_UNLOCKED_ON,SETUP_ON);
				pLocalParam->dPressUnlock = SETUP_ON;
				extcarToHal_SetDPressUnlockState(SETUP_ON);
			}
			else
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET_TOW_UNLOCKED_ON,SETUP_OFF);
				pLocalParam->dPressUnlock = SETUP_OFF;
				extcarToHal_SetDPressUnlockState(SETUP_OFF);
			}
			break;
		case CONTROLIDTRAVEL_INFORMATION_CAR_SET2_KEY_START_ON:
			if(u8_MouseStatus == SETUP_ON)
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET2_KEY_START_ON,SETUP_ON);
				pLocalParam->carLock = SETUP_ON;
				extcarToHal_SetCarLockState(SETUP_ON);
			}
			else
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_CAR_SET2_KEY_START_ON,SETUP_OFF);
				pLocalParam->carLock = SETUP_OFF;
				extcarToHal_SetCarLockState(SETUP_OFF);
			}
			break;
		case CONTROLIDTRAVEL_INFORMATION_CAR_SET_LIGHT_SENSITIVITY_ON:
			extcarToApp_SetUp_LightSensitivity_INC();
			break;
		case CONTROLIDTRAVEL_INFORMATION_CAR_SET_LIGHT_SENSITIVITY_OFF:
			extcarToApp_SetUp_LightSensitivity_DEC();
			break;
		/* ��ʷ��¼ҳ�湦�ܰ�ť */
		case CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_UPDATE:
			extcarToApp_SetUp_HistoryUpdate();
			break;
		case CONTROLIDTRAVEL_INFORMATION_HISTORICAL_RECORD_DELETE:
			extcarToApp_SetUp_HistoryClear();
			break;
		case CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_ZIDON:
		{
			if(u8_MouseStatus == SETUP_ON)
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_ZIDON,SETUP_ON);
				
				if(pLocalParam->AutomaticalAcOrEffectVentilat == 0x40)
				extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(0xc0);
				else if(pLocalParam->AutomaticalAcOrEffectVentilat == 0x00)
				extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(0x80);
			}
			else 
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_ZIDON,SETUP_OFF);
				
				if(pLocalParam->AutomaticalAcOrEffectVentilat == 0x80)
				extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(0x00);
				else if(pLocalParam->AutomaticalAcOrEffectVentilat == 0xc0)
				extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(0x40);
			}
		}
		break;
		case CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_YOUXIAO:
		{
			if(u8_MouseStatus == SETUP_ON)
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_YOUXIAO,SETUP_ON);
				
				if(pLocalParam->AutomaticalAcOrEffectVentilat == 0x80)
				extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(0xc0);
			 	else if(pLocalParam->AutomaticalAcOrEffectVentilat == 0x00)
				extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(0x40);
			}
			else
			{
				setDigitalData(CONTROLIDTRAVEL_INFORMATION_NEW_CRV4_YOUXIAO,SETUP_OFF);
				
				if(pLocalParam->AutomaticalAcOrEffectVentilat == 0x40)
				extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(0x00);
				else if(pLocalParam->AutomaticalAcOrEffectVentilat == 0xc0)
				extcarToHal_Set_AutomaticallyAcModel_EffectiveVentilation(0x80);
			}
		}
		break;
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE1:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE2:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE3:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE4:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE5:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE6:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE7:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE8:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE9:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE10:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE11:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE12:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE13:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE14:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE15:
		case CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE16:
		{
			u16 testCarPage=PAGE_TEST_CARPAGE1+(ctrlId-CONTROLIDTRAVEL_INFORMATION_TEST_CARPAGE1)/0x100;
			LOGD("testCarPage=0x%x",testCarPage);
			extcarToModule_NotifySystem_jumpPage(testCarPage);
			pLocalParam->testCarPage=testCarPage;
		}
		break;
		case CONTROLIDTRAVEL_INFORMATION_TEST_NEXT:
			if(pLocalParam->testCarPage<PAGE_TEST_CARPAGE1+15)
				extcarToModule_NotifySystem_jumpPage(++pLocalParam->testCarPage);
			break;
		case CONTROLIDTRAVEL_INFORMATION_TEST_PREV:
			if(pLocalParam->testCarPage>PAGE_TEST_CARPAGE1)
				extcarToModule_NotifySystem_jumpPage(--pLocalParam->testCarPage);
			break;
		case CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_CARINFORVOICEPRT:
			extcarToApp_about_CarInforVoicePrompt();
			break;
		case CONTROLIDTRAVEL_CARINFO_CAROLA_SET_OILPOINT_UP:
			appToExtcar_carola_set_oilConsumeUnit(SELECT_CTRL_UP);
			break;
		case CONTROLIDTRAVEL_CARINFO_CAROLA_SET_OILPOINT_DOWN:
			appToExtcar_carola_set_oilConsumeUnit(SELECT_CTRL_DOWN);
			break;
	/***************Public Extcar Info**************/
		case CONTROLIDTRAVEL_CARINFO_PUBLIC_SET_DOWN:
			extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION_CAR_PUBLIC_SET);
			break;
		case CONTROLIDTRAVEL_CARINFO_PUBLIC_SET_BACK:
			extcarToModule_NotifySystem_jumpPrePage();
			break;
		case CONTROLIDTRAVEL_CARINFO_PUBLIC_ELECTRONUC_BOOSTER_UP:
			{
				if(pLocalParam->tagBoosterMode == 0x00)
					setPublicElectronicBoosterMode (0x01);
				else if(pLocalParam->tagBoosterMode == 0x01)
					setPublicElectronicBoosterMode (0x00);
			}
			break;
		case CONTROLIDTRAVEL_CARINFO_PUBLIC_ELECTRONUC_BOOSTER_DOWN:
			{
				if(pLocalParam->tagBoosterMode == 0x00)
					setPublicElectronicBoosterMode (0x01);
				else  if(pLocalParam->tagBoosterMode == 0x01)
					setPublicElectronicBoosterMode (0x00);
			}
			break;
		case CONTROLIDTRAVEL_CARINFO_PUBLIC_REMOTE_PADLOCK_UP:
			{
				if(pLocalParam->tagLocFeedback == 0x00)
					setPublicRemoteControlLocFeedback(0x01);
				else if(pLocalParam->tagLocFeedback == 0x01)
					setPublicRemoteControlLocFeedback(0x00);
			}
			break;
		case CONTROLIDTRAVEL_CARINFO_PUBLIC_REMOTE_PADLOCK_DOWN:
			{
				if(pLocalParam->tagLocFeedback == 0x00)
					setPublicRemoteControlLocFeedback(0x01);
				else if(pLocalParam->tagLocFeedback == 0x01)
					setPublicRemoteControlLocFeedback(0x00);
			}
			break;
		case CONTROLIDTRAVEL_CARINFO_PUBLIC_SET_SHUT_DOWN_UNLOCK:
			{
				if(pLocalParam->tagShutDownUnlock == 0x01)
					setPublicShutDownTheUnlock(0x00);
				else if(pLocalParam->tagShutDownUnlock == 0x00)
					setPublicShutDownTheUnlock(0x01);
			}
			break;
		case CONTROLIDTRAVEL_CARINFO_PUBLIC_SET_REMOVE_HEAT_POSITION:
			{
				if(pLocalParam->tagPositionAfterLock == 0x01)
					setPublicPositionAfterLocking(0x00);
				else if(pLocalParam->tagPositionAfterLock == 0x00)
					setPublicPositionAfterLocking(0x01);
			}
			break;
		default:break;
	}
	//ŽóÖÚÍšÓÃÉèÖÃÒ³
	bool bRet = false;
	bRet = rx5_normalSettingPage(ctrlId,MOUSE_MSG_UP,param);
	if (bRet == true)
		return;
	
	bRet = daZhong_normalSettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//////////////////////////////////////////////////////////////////////////
	//ÐÐÊ»ÊýŸÝÒ³
	bRet =  golf_driveDataPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//±£ÑøÒ³
	bRet = false;
	bRet =  golf_maintenanceInfoPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//ÉèÖÃÒ³
	bRet = false;
	bRet =  golf_settingMainPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//ESCÏµÍ³
	bRet = false;
	bRet =  golf_escSystemSettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//ŒÝÊ»Ô±žšÖúÏµÍ³1
	bRet = false;
	bRet =  golf_driveAssistSystemASettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//ŒÝÊ»Ô±žšÖúÏµÍ³2
	bRet = false;
	bRet =  golf_driveAssistSystemBSettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//×€³µºÍµ÷³µ
	bRet = false;
	bRet =  golf_parkingSystemSettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//µÆ¹â1
	bRet = false;
	bRet =  golf_lightSystemASettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//µÆ¹â2
	bRet = false;
	bRet =  golf_lightSystemBSettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//µ¥Î»
	bRet = false;
	bRet =  golf_unitSettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//ºóÊÓŸµºÍ¹ÎË®Æ÷
	bRet = false;
	bRet =  golf_backMirrorAndWiperSettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//³µÃÅºÍ¿Õµ÷
	bRet = false;
	bRet =  golf_doorSettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//¶à¹ŠÄÜÏÔÊŸ1
	bRet = false;
	bRet =  golf_multipleFuncDisplayASettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//¶à¹ŠÄÜÏÔÊŸ2
	bRet = false;
	bRet =  golf_multipleFuncDisplayBSettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//»ÖžŽ³ö³§ÉèÖÃ1
	bRet = false;
	bRet =  golf_recoveryFactoryASettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//»ÖžŽ³ö³§ÉèÖÃ2
	bRet = false;
	bRet =  golf_recoveryFactoryBSettingPage(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;

	bRet = false;
	bRet = appToExtcar_golf_setDrivingMode_MouseUp(ctrlId);
	if(bRet == true)
		return;

	bRet = false;
	bRet = appToExtcar_blue_skin_tables_MouseUp(ctrlId);
	if(bRet == true)
		return;

	bRet =  appToExtcar_Parking_Assist_Page(ctrlId,MOUSE_MSG_UP);
	if (bRet == true)
		return;
	//////////////////////////////////////////////////////////////////////////
}
bool daZhong_normalSettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{

	case CONTROLIDTRAVEL_CARINFO_GOLD_MAIN_CAR_SMALL_SCREEN:	//µ±Ç°ÐÐÕþÇøÓòÃû³Æ,µÀÂ·Ãû³ÆÏÞÖÆÓë·ñ
		appToExtcar_daZhong_set_iSSendChineseToCarScreen();
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
//////////////////////////////////////////////////////////////////////////
bool golf_driveDataPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_DRIVING_DATA:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_DRIVING_DATA);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_LEFT:
		appToExtcar_golf_set_DriveDataFromSomeTime(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_DRIVING_DATA_RIGHT:
		appToExtcar_golf_set_DriveDataFromSomeTime(SELECT_CTRL_DOWN);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_maintenanceInfoPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MAINTAIN:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_MAINTANIN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_MAINTAIN_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_settingMainPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_ECS_SYSTEM:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_ECS_SYSTEM);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_JSY_SYSTEM:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_PILOT_PREV);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_SHUNTING:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_PARKING);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_LIGHT_PREV);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_UNIT);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_WIPRES:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_REARVIEW_MIRROR);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOS:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_AIR_WINDOW);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTIFUNCTION:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_MULTI_FUNCTION_PREV);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_FACTORY_SETTINGS_PREV);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_escSystemSettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_ECS_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SYSTEM_ON:
		appToExtcar_golf_set_escSystemActivation(ESC_SYSTEM_ACTIVATION_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SYSTEM_OFF:
		appToExtcar_golf_set_escSystemActivation(ESC_SYSTEM_ACTIVATION_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SYSTEM_CHECKBOX:
		appToExtcar_golf_set_escSystemActivation((pLocalParam->eEscSystemActivation == ESC_SYSTEM_ACTIVATION_YES)
			? ESC_SYSTEM_ACTIVATION_NO : ESC_SYSTEM_ACTIVATION_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_ON:
		appToExtcar_golf_set_carSpeedWarning(CAR_SPEED_WARNING_YES, SELECT_CTRL_UNKNOW);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_OFF:
		appToExtcar_golf_set_carSpeedWarning(CAR_SPEED_WARNING_NO, SELECT_CTRL_UNKNOW);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_ALARM_CHECKBOX:
		appToExtcar_golf_set_carSpeedWarning((pLocalParam->eCarSpeedWarning == CAR_SPEED_WARNING_YES)
			? CAR_SPEED_WARNING_NO : CAR_SPEED_WARNING_YES, SELECT_CTRL_UNKNOW);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_UNITS_ON:
		appToExtcar_golf_set_carSpeedWarning(pLocalParam->eCarSpeedWarning, SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_MIAN_ECS_SPEED_UNITS_OFF:
		appToExtcar_golf_set_carSpeedWarning(pLocalParam->eCarSpeedWarning, SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_SETTING:
		appToExtcar_golf_set_tireType(0);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_CANCLE:
		appToExtcar_golf_set_tireTypeNo();
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_SETUP_ECS_TIRE_ENTER:
		appToExtcar_golf_set_tireTypeYes();
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_driveAssistSystemASettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_PREV:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_PILOT_PREV);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_NEXT:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_PILOT_NEXT);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT1_ON:
		appToExtcar_golf_set_preAssistSystemActivation(PRE_ASSIST_SYSTEM_ACTIVATION_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT1_OFF:
		appToExtcar_golf_set_preAssistSystemActivation(PRE_ASSIST_SYSTEM_ACTIVATION_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_CHECKBOX_1:
		appToExtcar_golf_set_preAssistSystemActivation((pLocalParam->ePreAssistSystemActivation == PRE_ASSIST_SYSTEM_ACTIVATION_YES)
			? PRE_ASSIST_SYSTEM_ACTIVATION_NO : PRE_ASSIST_SYSTEM_ACTIVATION_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT2_ON:
		appToExtcar_golf_set_fatigueReconizeSystemActivation(FATIGUE_RECONIZE_SYSTEM_ACTIVATION_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT2_OFF:
		appToExtcar_golf_set_fatigueReconizeSystemActivation(FATIGUE_RECONIZE_SYSTEM_ACTIVATION_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_CHECKBOX_5:
		appToExtcar_golf_set_fatigueReconizeSystemActivation((pLocalParam->eFatigueReconizeSystemActivation == FATIGUE_RECONIZE_SYSTEM_ACTIVATION_YES)
			? FATIGUE_RECONIZE_SYSTEM_ACTIVATION_NO : FATIGUE_RECONIZE_SYSTEM_ACTIVATION_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT3_ON:
		appToExtcar_golf_set_driverAssistSystemLastSelectGap(LAST_SELECT_GAP_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TXT3_OFF:
		appToExtcar_golf_set_driverAssistSystemLastSelectGap(LAST_SELECT_GAP_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_CHECKBOX_4:
		appToExtcar_golf_set_driverAssistSystemLastSelectGap((pLocalParam->eLastSelectGap == LAST_SELECT_GAP_YES)
			? LAST_SELECT_GAP_NO : LAST_SELECT_GAP_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_DISTANCE_UP:
		appToExtcar_golf_set_driverAssistSystemGap(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_DISTANCE_DOWN:
		appToExtcar_golf_set_driverAssistSystemGap(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TRAVEL_PROGRAM_UP:
		appToExtcar_golf_set_driverAssistSystemdDriveMode(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_TRAVEL_PROGRAM_DOWN:
		appToExtcar_golf_set_driverAssistSystemdDriveMode(SELECT_CTRL_DOWN);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_driveAssistSystemBSettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_BACK2:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_THE_FRONT_ON:
		appToExtcar_golf_set_preAssistSystemWarning(PRE_ASSIST_SYSTEM_WARNING_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_THE_FRONT_OFF:
		appToExtcar_golf_set_preAssistSystemWarning(PRE_ASSIST_SYSTEM_WARNING_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_CHECKBOX_2:
		appToExtcar_golf_set_preAssistSystemWarning((pLocalParam->ePreAssistSystemWarning == PRE_ASSIST_SYSTEM_WARNING_YES)
			? PRE_ASSIST_SYSTEM_WARNING_NO : PRE_ASSIST_SYSTEM_WARNING_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_SHOW_ON:
		appToExtcar_golf_set_preAssistSystemGapWarning(PRE_ASSIST_SYSTEM_GAP_WARNING_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_SHOW_OFF:
		appToExtcar_golf_set_preAssistSystemGapWarning(PRE_ASSIST_SYSTEM_GAP_WARNING_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PILOT_CHECKBOX_3:
		appToExtcar_golf_set_preAssistSystemGapWarning((pLocalParam->ePreAssistSystemGapWarning == PRE_ASSIST_SYSTEM_GAP_WARNING_YES)
			? PRE_ASSIST_SYSTEM_GAP_WARNING_NO : PRE_ASSIST_SYSTEM_GAP_WARNING_YES);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_parkingSystemSettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_AUTOMATIC_ACTIVATION_ON:
		appToExtcar_golf_set_backCarSystemActivation(REVERSE_CAR_SYSTEM_AUTO_ACTIVATION_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_AUTOMATIC_ACTIVATION_OFF:
		appToExtcar_golf_set_backCarSystemActivation(REVERSE_CAR_SYSTEM_AUTO_ACTIVATION_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_AUTOMATIC_CHECKBOX:
		appToExtcar_golf_set_backCarSystemActivation((pLocalParam->eReverseCarSystemAutoActivation == REVERSE_CAR_SYSTEM_AUTO_ACTIVATION_YES)
			? REVERSE_CAR_SYSTEM_AUTO_ACTIVATION_NO : REVERSE_CAR_SYSTEM_AUTO_ACTIVATION_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_FRONT_VOLUME_UP:
		appToExtcar_golf_set_backCarSystemPreAudio(AUDIO_TYPE_YL, SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_FRONT_VOLUME_DOWN:
		appToExtcar_golf_set_backCarSystemPreAudio(AUDIO_TYPE_YL, SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_FRONT_PITCH_UP:
		appToExtcar_golf_set_backCarSystemPreAudio(AUDIO_TYPE_YD, SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_FRONT_PITCH_DOWN:
		appToExtcar_golf_set_backCarSystemPreAudio(AUDIO_TYPE_YD, SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_REAR_VOLUME_UP:
		appToExtcar_golf_set_backCarSystemRearAudio(AUDIO_TYPE_YL, SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_REAR_VOLUME_DOWN:
		appToExtcar_golf_set_backCarSystemRearAudio(AUDIO_TYPE_YL, SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_REAR_PITCH_UP:
		appToExtcar_golf_set_backCarSystemRearAudio(AUDIO_TYPE_YD, SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_REAR_PITCH_DOWN:
		appToExtcar_golf_set_backCarSystemRearAudio(AUDIO_TYPE_YD, SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_PARKING_RADAR_RING_DOOR:
		appToExtcar_golf_set_radarRingDoor();
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_lightSystemASettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TURN_ON_TIME_UP:
		appToExtcar_golf_set_lightSystemConnect(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TURN_ON_TIME_DOWN:
		appToExtcar_golf_set_lightSystemConnect(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_LIGHTS_ON:
		appToExtcar_golf_set_lightSystemAuto(LIGHT_SYSTEM_AUTO_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_LIGHTS_OFF:
		appToExtcar_golf_set_lightSystemAuto(LIGHT_SYSTEM_AUTO_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_CHECKBOX_1:
		appToExtcar_golf_set_lightSystemAuto((pLocalParam->eLightSystemAuto == LIGHT_SYSTEM_AUTO_YES)
			? LIGHT_SYSTEM_AUTO_NO : LIGHT_SYSTEM_AUTO_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TURN_LIGHTS_ON:
		appToExtcar_golf_set_lightSystemDirection(LIGHT_SYSTEM_DIRECTION_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TURN_LIGHTS_OFF:
		appToExtcar_golf_set_lightSystemDirection(LIGHT_SYSTEM_DIRECTION_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_CHECKBOX_2:
		appToExtcar_golf_set_lightSystemDirection((pLocalParam->eLightSystemDirection == LIGHT_SYSTEM_DIRECTION_YES)
			? LIGHT_SYSTEM_DIRECTION_NO : LIGHT_SYSTEM_DIRECTION_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TRAVEL_MODE_UP:
		appToExtcar_golf_set_lightSystemDriveRule(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_TRAVEL_MODE_DOWN:
		appToExtcar_golf_set_lightSystemDriveRule(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_METER_UP:
		appToExtcar_golf_set_lightSystemMeter(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_METER_DOWN:
		appToExtcar_golf_set_lightSystemMeter(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_PREV:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_LIGHT_PREV);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_NEXT:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_LIGHT_NEXT);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_lightSystemBSettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_BACK2:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_CAR_ENVIRONMENT_UP:
		appToExtcar_golf_set_lightSystemDoor(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_CAR_ENVIRONMENT_DOWN:
		appToExtcar_golf_set_lightSystemDoor(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_FOOT_SPACE_UP:
		appToExtcar_golf_set_lightSystemFeet(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_FOOT_SPACE_DOWN:
		appToExtcar_golf_set_lightSystemFeet(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_RETURN_HOME_MODE_UP:
		appToExtcar_golf_set_lightSystemGoHome(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_RETURN_HOME_MODE_DOWN:
		appToExtcar_golf_set_lightSystemGoHome(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_HOME_MODE_UP:
		appToExtcar_golf_set_lightSystemLeaveHome(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_LIGHT_HOME_MODE_DOWN:
		appToExtcar_golf_set_lightSystemLeaveHome(SELECT_CTRL_DOWN);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_unitSettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_TEMPERATURE_UP:
		appToExtcar_golf_set_degreeUnit(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_TEMPERATURE_DOWN:
		appToExtcar_golf_set_degreeUnit(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_VOLUME_UP:
		appToExtcar_golf_set_volumeUnit(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_VOLUME_DOWN:
		appToExtcar_golf_set_volumeUnit(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_FUEL_CONSUM_PTION_UP:
		appToExtcar_golf_set_oilConsumeUnit(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_FUEL_CONSUM_PTION_DOWN:
		appToExtcar_golf_set_oilConsumeUnit(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_DISTANCE_UP:
		appToExtcar_golf_set_distanceUnit(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_DISTANCE_DOWN:
		appToExtcar_golf_set_distanceUnit(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_SPEED_UP:
		appToExtcar_golf_set_speedUnit(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_UNIT_SPEED_DOWN:
		appToExtcar_golf_set_speedUnit(SELECT_CTRL_DOWN);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_backMirrorAndWiperSettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_IN_THE_FOLD_HAS_PARKING_ON:
		appToExtcar_golf_set_backMirror(2, MIRRORS_IN_THE_FOLD_HAS_PARKING_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_IN_THE_FOLD_HAS_PARKING_OFF:
		appToExtcar_golf_set_backMirror(2, MIRRORS_IN_THE_FOLD_HAS_PARKING_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REARVIEW_MIRROR_ON:
		appToExtcar_golf_set_backMirror(1, BACK_MIRROR_SYNC_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REARVIEW_MIRROR_OFF:
		appToExtcar_golf_set_backMirror(1, BACK_MIRROR_SYNC_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_CHECKBOX_1:
		appToExtcar_golf_set_backMirror(1, (pLocalParam->eBackMirrorSync == BACK_MIRROR_SYNC_YES)
			? BACK_MIRROR_SYNC_NO : BACK_MIRROR_SYNC_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REVERSE_GEAR_ON:
		appToExtcar_golf_set_backMirror(0, BACK_MIRROR_REVERSE_CAR_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REVERSE_GEAR_OFF:
		appToExtcar_golf_set_backMirror(0, BACK_MIRROR_REVERSE_CAR_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_CHECKBOX_2:
		appToExtcar_golf_set_backMirror(0, (pLocalParam->eBackMirrorReverseCar == BACK_MIRROR_REVERSE_CAR_YES)
			? BACK_MIRROR_REVERSE_CAR_NO : BACK_MIRROR_REVERSE_CAR_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_RAIN_ON:
		appToExtcar_golf_set_autoWiper(WIPER_AUTO_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_RAIN_OFF:
		appToExtcar_golf_set_autoWiper(WIPER_AUTO_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_CHECKBOX_3:
		appToExtcar_golf_set_autoWiper((pLocalParam->eWiperAuto == WIPER_AUTO_YES)
			? WIPER_AUTO_NO : WIPER_AUTO_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REAR_WINDOW_ON:
		appToExtcar_golf_set_backWiperWhenBackCar(BACK_WIN_CLEAN_REVERSE_CAR_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_REAR_WINDOW_OFF:
		appToExtcar_golf_set_backWiperWhenBackCar(BACK_WIN_CLEAN_REVERSE_CAR_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MIRRORS_CHECKBOX_4:
		appToExtcar_golf_set_backWiperWhenBackCar((pLocalParam->eBackWinCleanReverseCar == BACK_WIN_CLEAN_REVERSE_CAR_YES)
			? BACK_WIN_CLEAN_REVERSE_CAR_NO : BACK_WIN_CLEAN_REVERSE_CAR_YES);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_doorSettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_OPEN_WINDOW_CONVENIENT_UP:
		appToExtcar_golf_set_windowCtrl(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_OPEN_WINDOW_CONVENIENT_DOWN:
		appToExtcar_golf_set_windowCtrl(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_CENTRAL_UP:
		appToExtcar_golf_set_unlockDoor(SELECT_CTRL_UP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_CENTRAL_DOWN:
		appToExtcar_golf_set_unlockDoor(SELECT_CTRL_DOWN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_AUTOMATIC_LOCKING_ON:
		appToExtcar_golf_set_autoLockDoor(DOOR_AUTO_LOCK_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_AUTOMATIC_LOCKING_OFF:
		appToExtcar_golf_set_autoLockDoor(DOOR_AUTO_LOCK_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_ON_OFF_CHECKBOX:
		appToExtcar_golf_set_autoLockDoor((pLocalParam->eDoorAutoLock == DOOR_AUTO_LOCK_YES)
			? DOOR_AUTO_LOCK_NO : DOOR_AUTO_LOCK_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_AUTOMATIC_AIR_CIRCATION_ON:
		appToExtcar_golf_set_airCtrl(AIR_CONDITION_OPEN);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_AIR_WINDOW_AUTOMATIC_AIR_CIRCATION_OFF:
		appToExtcar_golf_set_airCtrl(AIR_CONDITION_CLOSE);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_multipleFuncDisplayASettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CURRENT_FUEL_ON:
		appToExtcar_golf_set_functionDisplay(0, OIL_CONSUME_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CURRENT_FUEL_OFF:
		appToExtcar_golf_set_functionDisplay(0, OIL_CONSUME_SELECT_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_1:
		appToExtcar_golf_set_functionDisplay(0, (pLocalParam->eOilConsumeSelect == OIL_CONSUME_SELECT_YES)
			? OIL_CONSUME_SELECT_NO : OIL_CONSUME_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_AVERAGE_FUEL_ON:
		appToExtcar_golf_set_functionDisplay(1, OIL_AVG_CONSUME_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_AVERAGE_FUEL_OFF:
		appToExtcar_golf_set_functionDisplay(1, OIL_AVG_CONSUME_SELECT_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_2:
		appToExtcar_golf_set_functionDisplay(1, (pLocalParam->eOilAvgConsumeSelect == OIL_AVG_CONSUME_SELECT_YES)
			? OIL_AVG_CONSUME_SELECT_NO : OIL_AVG_CONSUME_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_COZY_ON:
		appToExtcar_golf_set_cozyEconomyTipDisplay(2, COZY_DEVICE_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_COZY_OFF:
		appToExtcar_golf_set_cozyEconomyTipDisplay(2, COZY_DEVICE_SELECT_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_3:
		appToExtcar_golf_set_cozyEconomyTipDisplay(2, (pLocalParam->eCozyDeviceSelect == COZY_DEVICE_SELECT_YES)
			? COZY_DEVICE_SELECT_NO : COZY_DEVICE_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_ECONOMY_ON:
		appToExtcar_golf_set_cozyEconomyTipDisplay(1, ECONOMY_DRIVE_TIP_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_ECONOMY_OFF:
		appToExtcar_golf_set_cozyEconomyTipDisplay(1, ECONOMY_DRIVE_TIP_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_4:
		appToExtcar_golf_set_cozyEconomyTipDisplay(1, (pLocalParam->eEconomyDriveTip == ECONOMY_DRIVE_TIP_YES)
			? ECONOMY_DRIVE_TIP_NO : ECONOMY_DRIVE_TIP_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_TRAVEL_TIME_ON:
		appToExtcar_golf_set_functionDisplay(2, DRIVE_TIME_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_TRAVEL_TIME_OFF:
		appToExtcar_golf_set_functionDisplay(2, DRIVE_TIME_SELECT_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_5:
		appToExtcar_golf_set_functionDisplay(2, (pLocalParam->eDriveTimeSelect == DRIVE_TIME_SELECT_YES)
			? DRIVE_TIME_SELECT_NO : DRIVE_TIME_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_PREV:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_MULTI_FUNCTION_PREV);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_NEXT:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_MULTI_FUNCTION_NEXT);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_multipleFuncDisplayBSettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_BACK2:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_MILEAGE_ON:
		appToExtcar_golf_set_functionDisplay(3, DRIVE_DISTANCE_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_MILEAGE_OFF:
		appToExtcar_golf_set_functionDisplay(3, DRIVE_DISTANCE_SELECT_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_6:
		appToExtcar_golf_set_functionDisplay(3, (pLocalParam->eDriveDistanceSelect == DRIVE_DISTANCE_SELECT_YES)
			? DRIVE_DISTANCE_SELECT_NO : DRIVE_DISTANCE_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_AVERAGE_SPEED_ON:
		appToExtcar_golf_set_functionDisplay(4, AVG_SPEED_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_AVERAGE_SPEED_OFF:
		appToExtcar_golf_set_functionDisplay(4, AVG_SPEED_SELECT_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_7:
		appToExtcar_golf_set_functionDisplay(4, (pLocalParam->eAvgSpeedSelect == AVG_SPEED_SELECT_YES)
			? AVG_SPEED_SELECT_NO : AVG_SPEED_SELECT_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_DIGTAL_ON:
		appToExtcar_golf_set_functionDisplay(5, DIGIT_SPEED_DISPLAY_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_DIGTAL_OFF:
		appToExtcar_golf_set_functionDisplay(5, DIGIT_SPEED_DISPLAY_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_8:
		appToExtcar_golf_set_functionDisplay(5, (pLocalParam->eDigitSpeedDisplay == DIGIT_SPEED_DISPLAY_YES)
			? DIGIT_SPEED_DISPLAY_NO : DIGIT_SPEED_DISPLAY_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_SPEED_ALARM_ON:
		appToExtcar_golf_set_functionDisplay(6, CAR_SPEED_WARNING_DISPLAY_YES);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_SPEED_ALARM_OFF:
		appToExtcar_golf_set_functionDisplay(6, CAR_SPEED_WARNING_DISPLAY_NO);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_MULTI_FUNCTION_CHECKBOX_9:
		appToExtcar_golf_set_functionDisplay(6, (pLocalParam->eCarSpeedWarningDisplay == CAR_SPEED_WARNING_DISPLAY_YES)
			? CAR_SPEED_WARNING_DISPLAY_NO : CAR_SPEED_WARNING_DISPLAY_YES);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_recoveryFactoryASettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_BACK:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_PREV:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_FACTORY_SETTINGS_PREV);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_NEXT:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP_FACTORY_SETTINGS_NEXT);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_RESET1:
		appToExtcar_golf_set_recoverySetting(RECOVERY_SETTING_TYPE_ALL);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_RESET2:
		appToExtcar_golf_set_recoverySetting(RECOVERY_SETTING_TYPE_LIGHT);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_RESET3:
		appToExtcar_golf_set_recoverySetting(RECOVERY_SETTING_TYPE_OPEN_AND_CLOSE);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_RESET4:
		appToExtcar_golf_set_recoverySetting(RECOVERY_SETTING_TYPE_STOP_AND_START_CAR);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_RESET5:
		appToExtcar_golf_set_recoverySetting(RECOVERY_SETTING_TYPE_MUCH_FUNCTION_DISPLAY);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_OK:
		appToExtcar_golf_set_recoverySettingYes();
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_CANCEL:
		appToExtcar_golf_set_recoverySettingNo();
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}
bool golf_recoveryFactoryBSettingPage(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_BACK2:
		extcarToModule_NotifySystem_jumpPage(PAGE_GOLF_SETUP);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_PILOT_TXT:
		appToExtcar_golf_set_recoverySetting(RECOVERY_SETTING_TYPE_DRIVER_ASSIST_SYSTEM);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_TXT2:
		appToExtcar_golf_set_recoverySetting(RECOVERY_SETTING_DRIVE_DATA_FROM_START);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_TXT3:
		appToExtcar_golf_set_recoverySetting(RECOVERY_SETTING_DRIVE_DATA_FROM_LONG_TIME);
		break;
	case CONTROLIDTRAVEL_CARINFO_GOLF_MIAN_SETUP_FACTORY_SETTINGS_REARVIEW_MIRROR_TXT:
		appToExtcar_golf_set_recoverySetting(RECOVERY_SETTING_TYPE_BACK_MIRROR_AND_WIPER);
		break;
	default:
		bRet = false;
		break;
	}
	return bRet;
}

bool appToExtcar_Parking_Assist_Page(u32 objID, E_MOUSE_MSG e)
{
	bool bRet = true;
	switch(objID)
	{
		case CONTROLID_PARALLEL_PARK_SWITCH_BUTTON:
			setPublicFord_Parking_Assist_Mode(0x01);
			break;
		case CONTROLID_PERPENDICULAR_PARK_SWITCH_BUTTON:
			setPublicFord_Parking_Assist_Mode(0x02);
			break;
		case CONTROLID_PARK_OUT_ASSIST_PARK_SWITCH_BUTTON:
			setPublicFord_Parking_Assist_Mode(0x03);
			break;
		case CONTROLID_PARK_CLOSE_SWITCH_BUTTON:
			setPublicFord_Parking_Assist_Mode(0x00);
			break;
		default:
			bRet = false;
			break;
	}
	return bRet;
}

//////////////////////////////////////////////////////////////////////////


bool rx5_normalSettingPage(u32 objID, E_MOUSE_MSG e,u8 *param)
{
	bool bRet = true;
	switch(objID)
	{
		case CONTROLIDTRAVEL_SET_AUXILIARY_DRIVING:
			extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION_CAR_SET1);
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT:
			extcarToModule_NotifySystem_jumpPage(PAGE_TRAVEL_INFORMATION_COMFORTABLE_CONVENIENT_SET);
			break;
		case CONTROLIDTRAVEL_SET_SPEED_LIMIT_ALARM_SWITCH:
			appToExtcar_set_speed_limit_alarm_switch();
			break;
		case CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_INC:
		case CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_DEC:
		case CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_TXT:
			appToExtcar_set_alarmSpeedValue(objID - CONTROLIDTRAVEL_SET_ALARM_SPEED_PARAMETER_INC);
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_TRUNK_OPENING_DEGREE_INC:
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_TRUNK_OPENING_DEGREE_DEC:
			appToExtcar_set_trunk_opening_degree(objID - CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_TRUNK_OPENING_DEGREE_INC);
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_LAMP_SWITCH:
			appToExtcar_set_welcome_lamp_switch();
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_30S:
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_60S:
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_90S:
			appToExtcar_set_welcome_lamp_OpenTime(objID - CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_WELCOME_OPEN_LAMP_TIME_30S);
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_SWITCH:
			appToExtcar_set_company_home_lamp_switch();
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_30S:
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_60S:
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_90S:
			appToExtcar_set_company_home_lamp_OpenTime(objID - CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_LAMP_COMPANY_HOME_TIME_30S);
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_VEHICLE_LIGHTS_WHISTLES:
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_VEHICLE_ONLY_WHISTLES:
			appToExtcar_set_vehicle_mode(objID - CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_VEHICLE_LIGHTS_WHISTLES);
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_DRIVING_AUTOMATIC_LATCH_SWITCH:
			appToExtcar_set_driving_automatic_latch_switch();
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_FLAMEOUT_AUTOMATIC_LATCH_SWITCH:
			appToExtcar_set_flameout_automatic_latch_switch();
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEY_UNLOCK_ALL_DOOR:
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEY_UNLOCK_MAIN_DRIVING:
			appToExtcar_set_key_unlock_door(objID - CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEY_UNLOCK_ALL_DOOR);
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEYLESS_UNLOCK_ALL_DOOR:
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEYLESS_UNLOCK_MAIN_DRIVING:
			appToExtcar_set_keyLess_unlock_door(objID - CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_KEYLESS_UNLOCK_ALL_DOOR);
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_HIGH:
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_MID:
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_LOW:
			appToExtcar_set_AC_automatic_mode_flow(objID - CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_AC_AUTOMATIC_MODE_FLOW_HIGH);
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_F_B_DEFROST_FOG_LINKAGE_SWITCH:
			appToExtcar_set_F_B_Defrost_Fog_Linkage_switch();
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_MIRROR_AUTOMATIC_OPEN_SWITHCH:
			appToExtcar_set_Mirror_automatic_open_switch();
			break;
		case CONTROLIDTRAVEL_SET_COMFORTABLE_CONVENIENT_TRUNK_OPEN_LEVEL:
			{
				LOGD("appToExtcar_MouseUp LEVEL -- param[0]: %d    param[1]: %d param[2]: %d param[3]: %d",param[0],param[1],param[2],param[3]);
				if((param[3]+pLocalParam->uTrunkDegreeMin) <= pLocalParam->uTrunkDegreeMax)
					setPublicTrunkOpenLevelBar(pLocalParam->uTrunkDegreeMin,pLocalParam->uTrunkDegreeMax,pLocalParam->uTrunkDegreeStep,param[3]);
			}
			break;
		default:
			bRet = false;
			break;
	}
	
	return bRet;
}

