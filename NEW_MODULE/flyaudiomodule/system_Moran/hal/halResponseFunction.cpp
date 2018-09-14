#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <cutils/properties.h>
#include "types_def.h"
#include "commonFunc.h"
#include "global.h"
#include "pageID.h"
#include "param.h"
#include "controlID.h"
#include "stringID.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"
#include "appResponseFunction.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "moduleParamResponse.h"

//#include <cutils/properties.h>

#include "timer_interface.h"
#include "SteeringWheelStudy.h"

extern "C"{
#include "unicodestring.h"
};

static bool isHaveRadarData = false;

static void halToSystem_TimeInfo(u8 u8_Param)
{
  switch(u8_Param)
  	{
  	   case 1:
	   	System_NotifyAppEnterTimePage();
	   	break;
	   case 2:
	   	System_NotifyAppExitTimePage();
	   	break;
	   case 3:
	   	System_NotifyApp12_24();
	   	break;
	   case 4:
	   	System_NotifyApp_HourInc();
	   	break;
	   case 5:
	   	System_NotifyApp_HourDec();
	   	break;
	   case 6:
	   	System_NotifyApp_MutInc();
	   	break;
	   case 7:
	   	System_NotifyApp_MutDec();
	   	break;
		defualt:
			break;
  	}
}

static void halToSystem_Return_Ipol_Tv_Tpms(u8 u8_Param)
{
        pLocalParam->b_Sys_Ipod = u8_Param;
		if(pLocalParam->b_Sys_Ipod==1)
			{
		      setDigitalData(CONTROLID_MENU_IPOD,true);
		      setDigitalData(CONTROLID_MENU_TV,false);
		      setDigitalData(CONTROLID_MENU_TPMS,false);
		      setDigitalData(CONTROLID_SETUP_IPOD_SET_ON,true);
		      setDigitalData(CONTROLID_SETUP_TV_SET_ON,false);
			}
		else
			{
			  setDigitalData(CONTROLID_MENU_IPOD,false);
		      setDigitalData(CONTROLID_MENU_TV,true);
		      setDigitalData(CONTROLID_MENU_TPMS,true);
		      setDigitalData(CONTROLID_SETUP_IPOD_SET_ON,false);
		      setDigitalData(CONTROLID_SETUP_TV_SET_ON,true);
			}
		SendDeviceStateToOSDDebug();
}

void analyseHalMessage_SYSTEM(char resCmd, unsigned char *param, unsigned char len){
  	//LOGD("analyseHalMessage_SYSTEM: %x",resCmd);

	bool bRet = pLocalParam->m_clsSteeringWheelStudy.processHalMsg(resCmd, param, len);
	if (bRet)
	{
		LOGD("[%s] m_clsSteeringWheelStudy", __FUNCTION__);
		return;
	}

	switch(resCmd){

		case HALTOSYSTEM_INIT_CMD:
			halToSystem_InitCmd(param[0]);
			break;
		case HALTOSYSTEM_INIT_STATE:
			halToSystem_InitStatus(param[0]);
			break;
		case HALTOSYSTEM_BACKCAR_DETECT:
			halToSystem_BackCarDetectEnable(param[0]);
			break;
		case HALTOSYSTEM_LIGHT_DETECT:
			LOGD("HALTOSYSTEM_LIGHT_DETECT:0x%x",param[0]);
			halToSystem_LightDetectEnable(param[0]);
			break;
		case HALTOSYSTEM_DAY_NIGHT:
			LOGD("HALTOSYSTEM_DAY_NIGHT:0x%x",param[0]);
			halToSystem_DayOrNight(param[0]);
			break;
		case HALTOSYSTEM_EXT_AMPLIFIER:
			halToSystem_ExternalAmplifier(param[0]);
			break;
		case HALTOSYSTEM_LCD_BRIGHTNESS:
			LOGD("HALTOSYSTEM_LCD_BRIGHTNESS--0x%d 0x%d",param[0],param[1]);
			halToSystem_LCDBrightness(param);
			break;
		case HALTOSYSTEM_KEY_LEDBRIGHTNESS:
			halToSystem_LEDBrightness(param[0]);
			break;
		case HALTOSYSTEM_SPECIFIC_FUNC_STEEL_SWITCH:
			halToSystem_SpecialSteeringWheel(param[0]);
			break;
		case HALTOSYSTEM_RADIO_REGION:
			halToSystem_RadioConturyCode(param[0]);
			break;
		case HALTOSYSTEM_DEMO_MODE:
			halToSystem_DemoMode(param[0]);
			break;
		case HALTOSYSTEM_CUSTOM_STEELPANELDATA:
			halToSystem_ApplyUserDefinedWheelData(param[0]);
			break;
		case HALTOSYSTEM_STEELPANEL_LEARN_STATE:
			halToSystem_WheelStudyStatus(param[0]);
			break;
		case HALTOSYSTEM_DVD_REGION_CODE:
			halToSystem_DVDRegionCode(param[0]);
			break;
		case HALTOSYSTEM_FAN_CTRL:
		    LOGD("-----HALTOSYSTEM_FAN_CTRL--0x%d",param[0]);
		    halToSystem_FanCtrlMode(param[0]);
		    break;
		case HALTOSYSTEM_CPU_PERFORMANCE:
		    LOGD("-----HALTOSYSTEM_CPU_PERFORMANCE--0x%d",param[0]);
		    break;
		case HALTOSYSTEM_BRAKE_STATE:
			LOGD("HALTOSYSTEM_BRAKE_STATE:0x%x",param[0]);
			halToSystem_BrakeCarStatus(param[0]);
			break;
		case HALTOSYSTEM_BACKCAR_STATE	:
			LOGD("HALTOSYSTEM_BACKCAR_STATE:0x%x 0x%x",param[0],param[1]);
			halToSystem_BackCarStatus(param[0], param[1]);
			break;
		case HALTOSYSTEM_ACC_VOLTAGE:
			halToSystem_MagnitudeOfVoltage(param[0]);
			// change low bettery jing 2013-11-13
			halToSystem_battery_state(param[0]);
			break;
		case HALTOSYSTEM_CUR_STEELPANEL_NAME:
			LOGD("HALTOSYSTEM_CUR_STEELPANEL_NAME:%s",param);
			halToSystem_CurWheelName(param, len);
			break;
		case ALTOSYSTEM_TV_MODULE_EXIST:
			LOGD("------halToSystem_WhetherTVExist-----0x%x",param[0]);
			halToSystem_WhetherTVExist(param[0]);
			break;
		case ALTOSYSTEM_TPMS_MODULE_EXIST:
			halToSystem_WhetherTpmsExist(param[0]);
			break;
		case HALTOSYSTEM_3G_MODULE_EXIST:
			halToSystem_Whether3GPhoneExist(param[0]);
			break;
		case HALTOSYSTEM_AUX_VIDEO_SIGINAL:
			halToSystem_AuxVideo(param[0]);
			break;
		case HALTOSYSTEM_EXIT_IPOL:
			LOGD("HALTOSYSTEM_EXIT_IPOL:%x",param[0]);
			systemToModule_NotifyIpod_ExitIpol(param[0]);
			break;
		case HALTOSYSTEM_STANDBY_MODE:
			LOGD("HALTOSYSTEM_STANDBY_MODE:%x",param[0]);
			//halToSystem_StandbyStatus(param[0],param[1]);
			GetToSystem_StandbyStatus_New(param[0]);
			break;
		case HALTOSYSTEM_MCU_VERSION:
			LOGD("HALTOSYSTEM_MCU_VERSION:%s",param);
			halToSystem_MCU_Version(param, len);
			break;
		case HALTOSYSTEM_DVD_VERSION:
			halToSystem_DVD_Version(param, len);
			break;
		case HALTOSYSTEM_BT_VERSION:
			LOGD("HALTOSYSTEM_BT_VERSION:%s",param);
			halToSystem_BT_Version(param, len);
			break;
	    case HALTOSYSTEM_KEY_15S_GPS:
			halToSystem_Key_Gps(param,len);
			break;
			//2012-04-10
		case HALTOSYSTEM_RADAR_CAR_FRONT:
        case HALTOSYSTEM_RADAR_CAR_BEHIND:
        case HALTOSYSTEM_RADAR_CAR_INFO:
			LOGD("halToSystem_Radar_Info:0x%x",resCmd);
            halToSystem_Radar_Info(param,resCmd);
			break;
		//2012-06-26
		case HALTOSYSTEM_TIME_INFO:
			halToSystem_TimeInfo(param[0]);
			break;
		//2012 -07-30
		case HALTOSYSTEM_RETURN_IPOL_TV_TPMS:
			LOGD("HALTOSYSTEM_RETURN_IPOL_TV_TPMS:---param[0]:0x%x",param[0]);
			halToSystem_Return_Ipol_Tv_Tpms(param[0]);
			break;
		case HALTOSYSTEM_BATTERY_STATE:

		   	break;
		case HALTOSYSTEM_RETURN_DVR_TV_TPMS:
			LOGD("HALTOSYSTEM_RETURN_DVR_TV_TPMS:---param[0]:0x%x",param[0]);
			halToSystem_Return_Dvr_Tv_Tpms(param[0]);
			break;
		case HALTOSYSTEM_RETURN_CHOOSE_CARNAME:
			//halToSystem_Return_choose_CarName(param,len);
			halToSystem_Return_Setchoose_CarName(param,len);
			break;
		case 0xF0:
			halToSystem_Global_Circle_Ping(param[0]);
			//halToSystem_Debug_Info(param, len);//25
			break;
		case 0x45:
			//halToSystem_RealCarMode(param,len);
			halToSystem_SetRealCarMode(param,len);
			break;
		case 0x46:
			halToSystem_VIMCode(param,len);
			break;
		case 0x47:
			halToSystem_BarCode(param,len);
			break;
		case 0x31:
			halToSystem_WakeUpInfo(param[0]);
			break;
		case 0x51://G8II acc_state(LPC to Module)
			halToSystem_ACC_Status(param[0]);
			break;
		case 0x59://
			halToSystem_BatteryVolt_AnomalyMonitoring(param[0]);
			break;
		case 0x60:
			halToSystem_BatteryVolt_NewPassageway_aboutOnlinePrompt(param,len);
			break;
		case 0x61:
			halToSystem_NaviMixLowSwitch_Status(param[0]);
			break;
		case 0x62:
			halToSystem_LCDBrightness_Value(param[0]);
			break;
		case 0xFC:
			halToSystem_aboutAmbientLedMsg(param,len);
			break;
		case 0xFE:
			LOGD("-----zhq RETURN HalToSystem_TransparentChannel_Message --0x%x",resCmd);
			HalToSystem_TransparentChannel_Message(param);
			break;
		case 0xA7:
			HalToSystem_ShowDayOrNightMode_Message(param[0]);
			break;
		case HALTOSYSTEM_AUTO_ADJUST_SWITCH:
			HalToSystem_AutoAdjustmentSwitchOfScreenBrightnessStatus(param[0]);	
			break;
		case 0x23:
     		halToSystem_LCDBrightness_OnOrOff(param[0]);                     
    			 break;
		default:
			break;
	}
}

void halToSystem_Global_Circle_Ping(u8 state)
{
	//System_notifyApp_PingLoop(state);
	systemToHal_Notify_PingLoop_NewStructure(state);
}

void halToSystem_battery_state(u8 u8_Param)
{
	// 2013-8-10 --- jing  add low bettery osd
	systemToModule_NotifyOSD_Low_Bettery(u8_Param);  // jing  2013-8-12  low bettery osd
}

void halToSystem_Return_Dvr_Tv_Tpms(u8 u8_Param)
{
	LOGD("HALTOSYSTEM_DVROrTV:0x%x",u8_Param);
    if(pLocalParam->uDvrTvTpmsVisible==0){
    	setVisible(CONTROLID_SETUP_TV_DVR_SWITCH_ON,0x00);
    	setVisible(CONTROLID_SETUP_TV_DVR_SWITCH_OFF,0x00);
    	setVisible(CONTROLID_SETUP_TV_DVR_SWITCH_TEXT,0x00);

    	setVisible(CONTROLID_SETUP_TV_DVR_TPMS_SWITCH_UP,0x00);
    	setVisible(CONTROLID_SETUP_TV_DVR_TPMS_SWITCH_DOWN,0x00);
    	setVisible(CONTROLID_SETUP_TV_DVR_TPMS_DISPLAY_TEXT,0x00);

		setVisible(CONTROLID_SETUP_TPMS_RGB_SWITCH_UP,0x00);
    	setVisible(CONTROLID_SETUP_TPMS_RGB_SWITCH_DOWN,0x00);
    	setVisible(CONTROLID_SETUP_TPMS_RGB_SWITCH_TXT,0x00);
    	LOGD("pLocalParam->uDvrTvTpmsVisible==0,DVR ,TV,TPMS can not be seen");
    	return;
    }
    
	pLocalParam->m_eExternalDevice = (E_EXTERNAL_DEVICE)u8_Param;
	switch(pLocalParam->m_eExternalDevice)
	{
	case EXTERNAL_DEVICE_DVR:
		{
			setDigitalData(CONTROLID_SETUP_TV_DVR_SWITCH_ON,0);
			setDigitalData(CONTROLID_SETUP_TV_DVR_SWITCH_OFF,1);
			setStringText(CONTROLID_SETUP_TV_DVR_TPMS_DISPLAY_TEXT, STRING_SET_DVR);
		}
		break;
	case EXTERNAL_DEVICE_TV_TPMS:
		{
			setDigitalData(CONTROLID_SETUP_TV_DVR_SWITCH_ON,1);
			setDigitalData(CONTROLID_SETUP_TV_DVR_SWITCH_OFF,0);
			setStringText(CONTROLID_SETUP_TV_DVR_TPMS_DISPLAY_TEXT, STRING_SET_TV_OR_TPMS);
			
			setStringText(CONTROLID_SETUP_TPMS_RGB_SWITCH_TXT, STRING_SET_TV_OR_TPMS);//
		}
		break;
	case EXTERNAL_DEVICE_DNV:
		setStringText(CONTROLID_SETUP_TV_DVR_TPMS_DISPLAY_TEXT, STRING_ID_DNV_NAME);
		break;
	case EXTERNAL_DEVICE_AMBIENT_LED:
		setStringText(CONTROLID_SETUP_TPMS_RGB_SWITCH_TXT, STRING_ID_LED);
		break;
	}

	if(pLocalParam->m_eExternalDevice == EXTERNAL_DEVICE_DVR){
		DisplayAutoMateSwitchButtonUI(true);
	}
	else{
		DisplayAutoMateSwitchButtonUI(false);
	}

	if(pLocalParam->m_eExternalDevice == EXTERNAL_DEVICE_AMBIENT_LED)
	{
		setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_MAIN,0);
		setControllable(CONTROLID_SETUP_DVR_AMBIENT_LED_MAIN, 1);
	}
	else
	{
		setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_MAIN,2);
		setControllable(CONTROLID_SETUP_DVR_AMBIENT_LED_MAIN, 0);
		systemToHalAboutAmbientLed_Switch((u8)AMBIENT_LED_ON);
		pLocalParam->emAmbientLedSwitch = AMBIENT_LED_ON;
		DisplayUI_AmbientLed_SwitchButton((u8)pLocalParam->emAmbientLedSwitch);
	}
}

void DUMP(const char* msg, const char* buffer, const int length)
{
		int len = length * 3 + strlen(msg) + 1;
		char *out = (char*)malloc(len);
		if (!out) return ;

		memset(out, 0, sizeof(char) * len);
		snprintf(out, len, "%s:", msg);

		int i, j = strlen(msg);
		for (i = 0; i < length; i++)
			{
				snprintf(out + j, len - j, "%02X ", buffer[i]);
				j += 3;
			}
		LOGI("%s", out);
		free(out);
}

void halToSystem_Return_choose_CarName(u8 *param,u8 len)
{
	LOGD("[DYB->] halToSystem_Return_choose_CarName  param: [%s][%d]",param,len);
	//DUMP("[DYB->]: halToSystem_Return_choose_CarName", (char*)param, len);
	if(pLocalParam->cCarTypeVisible==0)
	{
		setVisible(CONTROLID_SETUP_CAR__MODEL_TEXT,0x00);
		setVisible(CONTROLID_SETUP_CAR__MODEL_UP,0x00);
		setVisible(CONTROLID_SETUP_CAR__MODEL_DOWN,0x00);
		setVisible(CONTROLID_SETUP_CAR__MODEL_OK,0x00);
		setVisible(CONTROLID_SETUP_CAR_MODEL_TEXT_BK,0x00);
		return ;
	}
	//setSerialData(CONTROLID_SETUP_CAR__MODEL_TEXT,param,len);
	halToSystem_ChooseCarMode(CONTROLID_SETUP_CAR__MODEL_TEXT,param,len);

	//ֻ�ڵ�һ�η��ص�ʱ����г���У���жϡ�
	static bool bCheck=0;
	if(bCheck == 0)
	{
		bCheck = 1;
		memcpy(pLocalParam->cChoseeCarMode,param,len);
	   	pLocalParam->cChoseeCarModeLen=len;
		pLocalParam->bChooseCarRecv=1;
		LOGD("pLocalParam->bRealCarRecv:%d,pLocalParam->initRecv:%d",pLocalParam->bRealCarRecv,pLocalParam->initRecv);
		//if(pLocalParam->bRealCarRecv == 1 && pLocalParam->initRecv == 1)
		//	SystemModule_CheckCarMode();
	}
}

void halToSystem_RealCarMode(u8 *pBuf,u8 len)
{
	LOGD("[DYB->>] halToSystem_RealCarMode  pBuf = [%s][%d], real = [%s][%d]",pBuf,len, pLocalParam->cRealCarMode,pLocalParam->cRealCarModeLen);
	//DUMP("[DYB]->>: halToSystem_RealCarMode ", (char*)pBuf, len);
	pLocalParam->bRealCarRecv=1;
	if(len != pLocalParam->cRealCarModeLen || memcmp(pLocalParam->cRealCarMode,pBuf,len) != 0)
	{
		memset(pLocalParam->cRealCarMode, 0, sizeof(pLocalParam->cRealCarMode));
		memcpy(pLocalParam->cRealCarMode,pBuf,len);
		pLocalParam->cRealCarModeLen=len;
		pLocalParam->bShowReviseCarModePage=true;
		LOGD("pLocalParam->bChooseCarRecv:%d,pLocalParam->initRecv:%d",pLocalParam->bChooseCarRecv,pLocalParam->initRecv);
		if(pLocalParam->bChooseCarRecv==1 && pLocalParam->initRecv == 1)
			SystemModule_CheckCarMode();
	}
	else
	{
		LOGD("[DYB] halToSystem_RealCarMod not enter if");
	}
}

void halToSystem_Return_Setchoose_CarName(u8 *param,u8 len)
{
	LOGD("[%s] param:[%s][%d]",__FUNCTION__,param,len);
	if(pLocalParam->cCarTypeVisible==0)
	{
		setVisible(CONTROLID_SETUP_CAR__MODEL_TEXT,0x00);
		setVisible(CONTROLID_SETUP_CAR__MODEL_UP,0x00);
		setVisible(CONTROLID_SETUP_CAR__MODEL_DOWN,0x00);
		setVisible(CONTROLID_SETUP_CAR__MODEL_OK,0x00);
		setVisible(CONTROLID_SETUP_CAR_MODEL_TEXT_BK,0x00);
		return ;
	}
	halToSystem_ChooseCarMode(CONTROLID_SETUP_CAR__MODEL_TEXT,param,len);

	static bool bCheck=0;
	if(bCheck == 0)
	{
		bCheck = 1;
		memset(pLocalParam->cChoseeCarMode,0,sizeof(pLocalParam->cChoseeCarMode));
		memcpy(pLocalParam->cChoseeCarMode,param,len);
	   	pLocalParam->cChoseeCarModeLen=len;
	}
}

void halToSystem_SetRealCarMode(u8 *pBuf,u8 len)
{
	LOGD("[%s] pBuf:[%s][%d], real:[%s][%d]",__FUNCTION__,pBuf,len, pLocalParam->cRealCarMode,pLocalParam->cRealCarModeLen);
	char property[PROPERTY_VALUE_MAX];
	property_get("persist.fly.car.select",property,"0");
	memset(pLocalParam->cChoseeCarMode,0,sizeof(pLocalParam->cChoseeCarMode));
	sscanf(property,"%s", pLocalParam->cChoseeCarMode);
	pLocalParam->cChoseeCarModeLen=strlen((char*)pLocalParam->cChoseeCarMode);
		
	LOGD("[%s] pBuf:[%s][%d], real:[%s][%d]",__FUNCTION__,pBuf,len, pLocalParam->cRealCarMode,pLocalParam->cRealCarModeLen);
	//if(len != pLocalParam->cRealCarModeLen || memcmp(pLocalParam->cRealCarMode,pBuf,len) != 0)
	if(len != pLocalParam->cChoseeCarModeLen || memcmp(pLocalParam->cChoseeCarMode,pBuf,len) != 0)
	{
		memset(pLocalParam->cRealCarMode, 0, sizeof(pLocalParam->cRealCarMode));
		memcpy(pLocalParam->cRealCarMode,pBuf,len);
		pLocalParam->cRealCarModeLen = len;
		SystemModuleParam_CheckCarMode()
;
	}
	else
	{
		LOGD("[%s] not enter if",__FUNCTION__);
	}
}

void halToSystem_VIMCode(u8 *pBuf,u8 len)
{
	LOGD("VIMCode:%s,len:%d",pBuf,len);
	systemToApp_SendVIMCode(pBuf,len);
}
void halToSystem_WakeUpInfo(u8 state)
{
	LOGD("halToSystem_WakeUpInfo~~state:0x%x",state);
	systemToApp_WakeUpInfo(state);
}
void halToSystem_InitCmd(u8 u8_Param) //Init Cmd
{

}
void halToSystem_InitStatus(u8 u8_Param) //Init Statusas
{
	systemToModule_NotifySoundModule_SysInitStatus(u8_Param);
}
void halToSystem_BackCarDetectEnable(u8 u8_Param) //Back Car Detect enable
{
    LOGD("halToSystem_BackCarDetectEnable u8_Param:%d",u8_Param);
	pLocalParam->b_Sys_BackCarDetectEnable= u8_Param;
}


void halToSystem_LightDetectEnable(u8 u8_Param) //Light Detect Enable
{
	LOGW("LightDetected:%d, DayNight:%d",u8_Param,pLocalParam->b_Sys_DayNight);
	pLocalParam->b_Sys_LightDetect = u8_Param; //Detect Light Or Not
	if(pLocalParam->b_Sys_LightDetect)
	{
		setDigitalData(CONTROLID_SETUP_LIGHT_LINE_CHECK_ON,true);
		setDigitalData(CONTROLID_MENU_DAYNIGHT,false);
	}
	else
	{
		setDigitalData(CONTROLID_SETUP_LIGHT_LINE_CHECK_ON,false);
		if(pLocalParam->b_Sys_DayNight)
		{
			setDigitalData(CONTROLID_MENU_DAYNIGHT,true);
		}
		else
		{
			setDigitalData(CONTROLID_MENU_DAYNIGHT,false);
		}

	}
}

void halToSystem_DayOrNight(u8 u8_Param) //Day Or Night Mode
{
	pLocalParam->b_Sys_DayNight = u8_Param;
	systemToModule_NotifyGps_DayOrNight(u8_Param);
	systemToModule_NotifyDNV_DayOrNight(u8_Param);
	System_notifyApp_EyeProtectionModeSwitch(u8_Param);
	
	if(pLocalParam->b_Sys_LightDetect)
		return;
	if(pLocalParam->b_Sys_DayNight)
	{
		setDigitalData(CONTROLID_SETUP_LIGHT_LINE_CHECK_ON,true);

	}
	else
	{
		setDigitalData(CONTROLID_SETUP_LIGHT_LINE_CHECK_ON,false);

	}

}
void halToSystem_ExternalAmplifier(u8 u8_Param)
{
	localParam.b_Sys_AmplifierStatus = u8_Param;
    if(localParam.b_Sys_AmplifierStatus)
	{
		setDigitalData(CONTROLID_SETUP_POWER_AMPLIFIER_OFF,false);
		setDigitalData(CONTROLID_SETUP_POWER_AMPLIFIER_ON,true);
	}
	else
	{
		setDigitalData(CONTROLID_SETUP_POWER_AMPLIFIER_ON,false);
		setDigitalData(CONTROLID_SETUP_POWER_AMPLIFIER_OFF,true);
	}
}

void halToSystem_LCDBrightness(u8 *Param)
{
    u8 u8_Param1 = Param[0];
    u8 u8_Param2 = Param[1];

	if(u8_Param1==0xFF)
	{
		pLocalParam->cBrightness_RangeValue = u8_Param2;
		halToSystem_Screen_Brightness( u8_Param2);
		return;
	}
	
   	g_clsSystem.sendToFlyJniSdkSystemBrightnessMessage(u8_Param1);
   	if(u8_Param1 == 0){
       if(pLocalParam->u8_Sys_CurLcdLight != 0){
	    	pLocalParam->u8_Sys_PreLcdLight = pLocalParam->u8_Sys_CurLcdLight;
			systemToApp_HidePull_DownBar();
       }
	}
	else
	{
	    pLocalParam->bSysStatusBarSet = false;
	}
	
	pLocalParam->u8_Sys_CurLcdLight = u8_Param1;
	if(u8_Param1!= 0)
		pLocalParam->u8_Sys_PreLcdLight = u8_Param1;
	setScreenBrightnessCtrl(u8_Param1);

	LOGD("halToSystem_LCDBrightness:CurPage:0x%x",getCurPage());
	if(u8_Param1)
	{

		systemToModule_NotifyKeyModule_WhetherLcdClose(false);
		//if(PAGE_BLACK == getCurPage())
		//{
			//anyModuleToSysModule_Switch_PrePage();
			//setShowCloseScreenOSD(0x00);
		//}
	}
	else
	{
		systemToModule_NotifyKeyModule_WhetherLcdClose(true);
		if(PAGE_BLACK != getCurPage())
		{
		     switch_Page(PAGE_BLACK);
		     //setShowCloseScreenOSD(0x01);
		}

	}
}

void halToSystem_LEDBrightness(u8 u8_Param)
{
    LOGD("halToSystem_LEDBrightness:0x%x",u8_Param);
	pLocalParam->u8_Sys_PanelLight_bef  = pLocalParam->u8_Sys_PanelLight;
	pLocalParam->u8_Sys_PanelLight = u8_Param;
	u8 ansiBuf[8];
	u8 *strAuto = (u8*)"Auto";
	memset(ansiBuf, 0, 8);
	if(u8_Param == 0xff)
	{
		memcpy(ansiBuf, strAuto, strlen((char*)strAuto));
		setVisible(CONTROLID_SETUP_SET_PANEL_LIGHT_GRAY_BAR,1);
		setVisible(CONTROLID_SETUP_SET_PANEL_LIGHT_BAR,0);
		setDigitalData(CONTROLID_SETUP_SET_PANEL_LIGHT_AUTO_BUTTON,1);
	}
	else
	{
		sprintf((char*)ansiBuf,"%d",u8_Param);
		setAnalogData(CONTROLID_SETUP_SET_PANEL_LIGHT_BAR,u8_Param-PANEL_LIGHT_MIN);
	}

	int nAnsiBufLen = strlen((char*)ansiBuf);
	u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
	memset(unicodeBuf, 0, nAnsiBufLen*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicodeBuf);
	setSerialData(CONTROLID_SETUP_PANEL_LIGHT_TEXT,unicodeBuf, nUnicodeBufLen*2);
	free(unicodeBuf);
}
void halToSystem_SpecialSteeringWheel(u8 u8_Param)
{
	LOGD("halToSystem_SpecialSteeringWheel u8_Param:%x",u8_Param);
	if (u8_Param)
	{
		pLocalParam->b_Sys_SpecialSteeringWheel = true;
		setDigitalData(CONTROLID_SETUP_WHEEL_LEARNING_ON_OFF,false);
	}
	else
	{
		pLocalParam->b_Sys_SpecialSteeringWheel = false;
		setDigitalData(CONTROLID_SETUP_WHEEL_LEARNING_ON_OFF,true);
	}
}

//-------------------2012-2-29(WheelStudy)-------------------



void halToSystem_RadioConturyCode(u8 u8_Param)
{
	pLocalParam->u8_Sys_RadioCountryCode= u8_Param;
	SystemToApp_DisplayRadioCountry();
	SystemToApp_ShowRadioCountry(u8_Param);

}
void halToSystem_DemoMode(u8 u8_Param)
{

}
void halToSystem_ApplyUserDefinedWheelData(u8 u8_Param)
{
	pLocalParam->u8_Sys_UserSteeringWheel = u8_Param;
	LOGD("halToSystem_ApplyUserDefinedWheelData---Param:0x%x",u8_Param);
		if(0x01 == pLocalParam->u8_Sys_UserSteeringWheel)
		{
			setControllable(CONTROLID_SETUP_WHEEL_CHOOSE_DOWM,0);
			setControllable(CONTROLID_SETUP_WHEEL_CHOOSE_UP,0);
			setAnalogData(CONTROLID_SETUP_WHEEL_CHOOSE_DOWM, (short)2);
			setAnalogData(CONTROLID_SETUP_WHEEL_CHOOSE_UP, (short)2);
			setDigitalData(CONTROLID_SETUP_WHEEL_LEARNING_ON_OFF, true);

		}
		else if(0x00== pLocalParam->u8_Sys_UserSteeringWheel)
		{
			setControllable(CONTROLID_SETUP_WHEEL_CHOOSE_DOWM,1);
			setControllable(CONTROLID_SETUP_WHEEL_CHOOSE_UP,1);
			setAnalogData(CONTROLID_SETUP_WHEEL_CHOOSE_DOWM, (short)0);
			setAnalogData(CONTROLID_SETUP_WHEEL_CHOOSE_UP, (short)0);
			setDigitalData(CONTROLID_SETUP_WHEEL_LEARNING_ON_OFF, false);
		}

}
void halToSystem_WheelStudyStatus(u8 u8_Param)
{
      LOGD("halToSystem_WheelStudyStatus~~~u8_Param:0x%x",u8_Param);
    	switch(u8_Param)
		{
		case 0x00:
		case 0x02:
			pLocalParam->b_Sys_WaitStudy= false;
			SystemModule_WheelDataFromRegest();
			break;
		case 0x01:
			pLocalParam->b_Sys_WaitStudy = true;
			break;
		default:
			break;
		}
	LOGD("halToSystem_WheelStudyStatus u8_Param:0x%x,b_Sys_WaitStudy:0x%x.\n",u8_Param,pLocalParam->b_Sys_WaitStudy);
}
void halToSystem_DVDRegionCode(u8 u8_Param)
{
	LOGD("halToSystem_DVDRegionCode");
	pLocalParam->u8_Sys_DVDRegionCode= u8_Param;
	SysteToApp_DisplayDVDRegionCode();
}
void halToSystem_BrakeCarStatus(u8 u8_Param)
{
	pLocalParam->b_Sys_BrakeCarStatus = u8_Param; //Brake Car Status
	LOGD("[%s] state=%d,cBreakCarEnable=%d",__FUNCTION__,u8_Param,pLocalParam->cBreakCarEnable);
	System_BrakeCarDetect_IsCanSeeVideo();
}

void System_BrakeCarDetect_IsCanSeeVideo()
{
    if(IsCanSwitchVideoPage_WhenTheBrakeDownTime(pLocalParam->cBreakCarEnable,pLocalParam->b_Sys_BrakeCarStatus))
    {
		systemToModule_NotifySomeModule_BrakeCarStatus(0x01);
		System_notifyApp_BrakeState(0x01);
    }
    else
    {
    	systemToModule_NotifySomeModule_BrakeCarStatus(0x00);
		System_notifyApp_BrakeState(0x00);
    }

}

void halToSystem_FanCtrlMode(u8 u8_Param)
{
    E_FAN_MODE emCmd = eFanModeHighPerformance;
    switch(u8_Param)
    {
        case 0x00:
            pLocalParam->eCurFanMode = eFanModeShutDown;
            emCmd = eFanModeShutDown;
            //systemToApp_FanMode(0);
        break;
        case 0x01:
            pLocalParam->eCurFanMode = eFanModeShutOpen;
            emCmd = eFanModeShutOpen;
            //systemToApp_FanMode(2);
        break;
        case 0x02:
            pLocalParam->eCurFanMode = eFanModeHighPerformance;
            emCmd = eFanModeHighPerformance;
            //systemToApp_FanMode(3);
        break;
        case 0x03:
            pLocalParam->eCurFanMode = eFanModeFitAuto;
            emCmd = eFanModeFitAuto;
            //systemToApp_FanMode(1);
        break;
        case 0x04:
            pLocalParam->eCurFanMode = eFanModeLowPower;
            emCmd = eFanModeLowPower;
            //systemToApp_FanMode(4);
        break;
        default:break;
    }

    if(emCmd != eFanModeHighPerformance){
        pLocalParam->ePreFanMode = emCmd;
    }
    
    SystemModuleToUI_aboutFanMode(pLocalParam->eCurFanMode);

}

void halToSystem_BackCarStatus(u8 u8_Status, u8 u8_Video)
{
	localParam.b_Sys_BackCarStatus = u8_Status;
	localParam.b_Sys_BackCarVideo = u8_Video;

	//systemToModule_NotifyBackModule_BackCarStatus(u8_Status, u8_Video);
	SendBackcarInfoAndDiaInStateToOSDDebug();
	g_clsSystem.sendToFlyJniSdkBackCarStatus(u8_Status);

	if(localParam.b_Sys_BackCarStatus == 0)
	{
		isHaveRadarData = false;
		localParam.b_Visible = false;
		localParam.f_Visible = false;
		systemToApp_BackVideo_CarRadarIsDisplay(0);
		Radar_Visible(false);
	}
}

void halToSystem_MagnitudeOfVoltage(u8 u8_Param)
{
    pLocalParam->ucBattery_Value = u8_Param;
	systemToModule_NotifyTPMSModule_MagnitudeOfVoltage(u8_Param);
}
void halToSystem_CurWheelName(u8 *pBuf, u8 u8_len)
{
	setSerialData(CONTROLID_SETUP_WHEEL_CHOOSE_TEXT,pBuf,u8_len);
}
void halToSystem_WhetherTVExist(u8 u8_Param)
{
	pLocalParam->u8_Sys_WhetherTVExist = u8_Param;
	LOGD("halToSystem_WhetherTVExist u8_Param:%x",u8_Param);
	systemToModule_NotifyTVModule_WhetherTVExist(u8_Param);
	SendDeviceStateToOSDDebug();
	
}
void halToSystem_WhetherTpmsExist(u8 u8_Param)
{
	//TPMS Exist Or Not
	pLocalParam->u8_Sys_WhetherTPMSExist = u8_Param;
	LOGD("halToSystem_WhetherTpmsExist u8_Param:%x",u8_Param);
	systemToModule_NotifyTPMSModule_WhetherTPMSExist(u8_Param);
	SendDeviceStateToOSDDebug();

}
void halToSystem_Whether3GPhoneExist(u8 u8_Param)
{

}

void halToSystem_AuxVideo(u8 u8_Param)
{
	LOGD("pLocalParam->u8_Sys_AUXVideo:0x%x pLocalParam->b_isAUX:%x",pLocalParam->u8_Sys_AUXVideo,pLocalParam->b_isAUX);

	if(pLocalParam->b_isAUX){
		if(pLocalParam->uModuleSystem_is_T123 == 1){
			pLocalParam->u8_Sys_AUXVideo = u8_Param; //Whether have AUX Video
			systemToModule_NotifyAUXModule_AUXVideo(u8_Param);
		}
	}
	else{
		return;
	}
	SendDeviceStateToOSDDebug();
}



void halToSystem_StandbyStatus(u8 u8_Param1,u8 u8_Param2)
{
	//Standby Status
	pLocalParam->u8_Sys_StandbyStatus = u8_Param1;
	pLocalParam->u8_Sys_StandbyStatus1 = u8_Param2;
	LOGD("[%s]---u8_Sys_StandbyStatus:0x%x  u8_Sys_StandbyStatus1:0x%x",__FUNCTION__,pLocalParam->u8_Sys_StandbyStatus,pLocalParam->u8_Sys_StandbyStatus1);
    systemToModule_NotifySomeModule_StandbyStatus(u8_Param1);
	if (pLocalParam->u8_Sys_StandbyStatus)
	{
	     if(u8_Param2){
		    System_ReturnAppStandyState(true);
			SetTimer(2000,1,STANDY_TIMER);
	     }
		 else{
             systemToHal_StandyState(pLocalParam->u8_Sys_StandbyStatus,pLocalParam->u8_Sys_StandbyStatus1);
			 systemToApp_Sound_Channel_Volume_Adjust(0x00,0x00);
		 }
		    
		 SetTimer(2000,1,DVD_SWITCH_TIMERID);
	}
	else
	{
	    LOGD("--halToSystem_StandbyStatus0--CurPage:0x%x",getCurPage());
	    if(getCurPage() == PAGE_STANDBY)
			systemToModule_NotifySystem_JumpPrePage();
			
		if(u8_Param2){
			systemToHal_StandyState(pLocalParam->u8_Sys_StandbyStatus,pLocalParam->u8_Sys_StandbyStatus1);
		    System_ReturnAppStandyState(false);
		}
		else{
			systemToHal_StandyState(pLocalParam->u8_Sys_StandbyStatus,pLocalParam->u8_Sys_StandbyStatus1);
		}
	}

}

void halToSystem_ACC_Status(u8 p)
{
	systemToModule_NotifyRemoteOnline_AccStatus(p);
}

void GetToSystem_StandbyStatus_New(u8 p)
{
	pLocalParam->uStandByStatus = p;
	systemToModule_NotifyRemoteOnline_StandbyStatus(p);
}

void halToSystem_MCU_Version(u8 *pBuf, u8 len)
{
	//NULL
	u8 *pAnsicBuf = (u8*)malloc(len+1);
	memset(pAnsicBuf, 0, len+1);
	memcpy(pAnsicBuf, pBuf, len);
	u8 *pUnicodeBuf = (u8*)malloc((len)*2+2);
	memset(pUnicodeBuf, 0, (len)*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(pAnsicBuf, (unicode16_t*)pUnicodeBuf);
	setSerialData(CONTROLID_COPYRIGHT_ACU,pUnicodeBuf,nUnicodeBufLen*2);
	free(pAnsicBuf);
	free(pUnicodeBuf);

}

void halToSystem_DVD_Version(u8 *pBuf, u8 len)
{
	u8 *pAnsicBuf = (u8*)malloc(len+1);
	memset(pAnsicBuf, 0, len+1);
	memcpy(pAnsicBuf, pBuf, len);
	u8 *pUnicodeBuf = (u8*)malloc(len*2+2);
	memset(pUnicodeBuf, 0, len*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(pAnsicBuf, (unicode16_t*)pUnicodeBuf);
	setSerialData(CONTROLID_COPYRIGHT_MPEG,pUnicodeBuf,nUnicodeBufLen*2);

	char property[PROPERTY_VALUE_MAX];
	sprintf(property,"%s", pAnsicBuf);
    property_set(FLY_SET_DVD_VERSION,property);
	
	free(pAnsicBuf);
	free(pUnicodeBuf);
}
void halToSystem_BT_Version(u8 *pBuf, u8 len)
{
	u8 *pAnsicBuf = (u8*)malloc(len+1);
	memset(pAnsicBuf, 0, len+1);
	memcpy(pAnsicBuf, pBuf, len);
	u8 *pUnicodeBuf = (u8*)malloc(len*2+2);
	memset(pUnicodeBuf, 0, len*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(pAnsicBuf, (unicode16_t*)pUnicodeBuf);
	setSerialData(CONTROLID_COPYRIGHT_BLUETOOTH,pUnicodeBuf,nUnicodeBufLen*2);
	free(pAnsicBuf);
	free(pUnicodeBuf);
}

void halToSystem_Key_Gps(u8 *pBuf,u8 len)
{
	u16 uCurId = getCurPage();
	if(uCurId != PAGE_BLACK){
		systemToGPSRun_NotifyGPS_15sJumpPage();
	}
}

void halToSystem_Debug_Info(u8 *pBuf, u8 len){
	setShowDebugInfo(pBuf, len);
}

void Radar_Visible(bool b)
{
	setVisible(CONTROLID_BACK_VIDEO_FL_ONE_RADAR,b);
	setVisible(CONTROLID_BACK_VIDEO_FL_TWO_RADAR,b);
	setVisible(CONTROLID_BACK_VIDEO_FR_ONE_RADAR,b);
	setVisible(CONTROLID_BACK_VIDEO_FR_TWO_RADAR,b);

	setVisible(CONTROLID_BACK_VIDEO_RL_ONE_RADAR,b);
	setVisible(CONTROLID_BACK_VIDEO_RL_TWO_RADAR,b);
	setVisible(CONTROLID_BACK_VIDEO_RR_ONE_RADAR,b);
	setVisible(CONTROLID_BACK_VIDEO_RR_TWO_RADAR,b);
}

void halToSystem_Radar_Info_F(u8* pBuf)
{
	//static u8 oldBuf[4] = {0xff,0xff,0xff,0xff};

	setUpdateUI(false);
	LOGD("halToSystem_Radar_Info_F f_Visible %x",pLocalParam->f_Visible);
	LOGD("halToSystem_Radar_Info_F b_old_buf :%x,%x,%x,%x",pLocalParam->m_cRadarData[0],pLocalParam->m_cRadarData[1],pLocalParam->m_cRadarData[2],pLocalParam->m_cRadarData[3]);
	LOGD("halToSystem_Radar_Info_F b_pBuf :   %x,%x,%x,%x",pBuf[0],pBuf[1],pBuf[2],pBuf[3]);
	systemGetRadarDataDeal(pBuf);
	
	if(pLocalParam->f_Visible == false)
	{
	  setVisible(CONTROLID_BACK_VIDEO_FL_ONE_RADAR,true);
	  setVisible(CONTROLID_BACK_VIDEO_FL_TWO_RADAR,true);
	  setVisible(CONTROLID_BACK_VIDEO_FR_ONE_RADAR,true);
	  setVisible(CONTROLID_BACK_VIDEO_FR_TWO_RADAR,true);
	  pLocalParam->f_Visible = true;

	}
    
	if(pLocalParam->m_cRadarData[0] != *pBuf)
	     {
	        systemToModule_NotifyOSD_backcar_RadarDirectAndLevel(0x01,*pBuf);
        	 setAnalogData(CONTROLID_BACK_VIDEO_FL_ONE_RADAR,*pBuf);
        	 pLocalParam->m_cRadarData[0] = *pBuf;
	     }
   if(pLocalParam->m_cRadarData[1] != *(pBuf+1))
		{
		    systemToModule_NotifyOSD_backcar_RadarDirectAndLevel(0x02,*(pBuf+1));
        	 setAnalogData(CONTROLID_BACK_VIDEO_FL_TWO_RADAR,*(pBuf+1));
        	 pLocalParam->m_cRadarData[1] = *(pBuf+1);
		 }
  if(pLocalParam->m_cRadarData[2] != *(pBuf+2))
    {
            systemToModule_NotifyOSD_backcar_RadarDirectAndLevel(0x04,*(pBuf+2));
        	 setAnalogData(CONTROLID_BACK_VIDEO_FR_ONE_RADAR,*(pBuf+2));
        	 pLocalParam->m_cRadarData[2] = *(pBuf+2);
		 }
   if(pLocalParam->m_cRadarData[3] != *(pBuf+3))
   {
            systemToModule_NotifyOSD_backcar_RadarDirectAndLevel(0x03,*(pBuf+3));
        	 setAnalogData(CONTROLID_BACK_VIDEO_FR_TWO_RADAR,*(pBuf+3));
        	 pLocalParam->m_cRadarData[3] = *(pBuf+3);
   }

   setUpdateUI(true);
	
}
void halToSystem_Radar_Info_FF(u8* pBuf)
{
	//static u8 oldBuf[4] = {0xff,0xff,0xff,0xff};
    	setUpdateUI(false);

		 if(pLocalParam->m_cRadarDataUI[0] != *pBuf)
	     {
        	 setAnalogData(CONTROLID_BACK_RADAR_FL_ONE_RADAR,*pBuf);
        	 pLocalParam->m_cRadarDataUI[0] = *pBuf;
	     }
         if(pLocalParam->m_cRadarDataUI[1] != *(pBuf+1))
		{
        	 setAnalogData(CONTROLID_BACK_RADAR_FL_TWO_RADAR,*(pBuf+1));
        	 pLocalParam->m_cRadarDataUI[1] = *(pBuf+1);
		 }
         if(pLocalParam->m_cRadarDataUI[2] != *(pBuf+2))
		 {
        	 setAnalogData(CONTROLID_BACK_RADAR_FR_ONE_RADAR,*(pBuf+2));
        	 pLocalParam->m_cRadarDataUI[2] = *(pBuf+2);
		 }
         if(pLocalParam->m_cRadarDataUI[3] != *(pBuf+3))
        {
        	 setAnalogData(CONTROLID_BACK_RADAR_FR_TWO_RADAR,*(pBuf+3));
        	 pLocalParam->m_cRadarDataUI[3] = *(pBuf+3);
        }

         setUpdateUI(true);
}

void halToSystem_Radar_Info_B(u8* pBuf)
{
        //static u8 oldBuf[4] = {0xff,0xff,0xff,0xff};
        
        setUpdateUI(false);
        LOGD("halToSystem_Radar_Info_B b_Visible %x",pLocalParam->b_Visible);
        LOGD("halToSystem_Radar_Info_B b_old_buf :%x,%x,%x,%x",pLocalParam->m_cRadarData[0],pLocalParam->m_cRadarData[1],pLocalParam->m_cRadarData[2],pLocalParam->m_cRadarData[3]);
        LOGD("halToSystem_Radar_Info_B b_pBuf :   %x,%x,%x,%x",pBuf[0],pBuf[1],pBuf[2],pBuf[3]);
        systemGetRadarDataDeal( pBuf);
	
         if(pLocalParam->b_Visible == false)
         {

         	  setVisible(CONTROLID_BACK_VIDEO_RL_ONE_RADAR,true);
			  setVisible(CONTROLID_BACK_VIDEO_RL_TWO_RADAR,true);
			  setVisible(CONTROLID_BACK_VIDEO_RR_ONE_RADAR,true);
			  setVisible(CONTROLID_BACK_VIDEO_RR_TWO_RADAR,true);
			  pLocalParam->b_Visible = true;

         }
         
         if(pLocalParam->m_cRadarData[4] != *(pBuf+0))
         {
        	 systemToModule_NotifyOSD_backcar_RadarDirectAndLevel(0x05,*pBuf);
        	 setAnalogData(CONTROLID_BACK_VIDEO_RL_ONE_RADAR,*pBuf);
        	 pLocalParam->m_cRadarData[4] = *(pBuf+0);
         }
         if(pLocalParam->m_cRadarData[5] != *(pBuf+1))
         {
        	 systemToModule_NotifyOSD_backcar_RadarDirectAndLevel(0x06,*(pBuf+1));
        	 setAnalogData(CONTROLID_BACK_VIDEO_RL_TWO_RADAR,*(pBuf+1));
        	 pLocalParam->m_cRadarData[5] = *(pBuf+1);
         }
         if(pLocalParam->m_cRadarData[6] != *(pBuf+2))
         {
            systemToModule_NotifyOSD_backcar_RadarDirectAndLevel(0x08,*(pBuf+2));
            setAnalogData(CONTROLID_BACK_VIDEO_RR_ONE_RADAR,*(pBuf+2));
            pLocalParam->m_cRadarData[6] = *(pBuf+2);
         }
         if(pLocalParam->m_cRadarData[7] != *(pBuf+3))
         {
        	 systemToModule_NotifyOSD_backcar_RadarDirectAndLevel(0x07,*(pBuf+3));
        	 setAnalogData(CONTROLID_BACK_VIDEO_RR_TWO_RADAR,*(pBuf+3));
        	 pLocalParam->m_cRadarData[7] = *(pBuf+3);
         }

		 setUpdateUI(true);

}
void halToSystem_Radar_Info_BB(u8* pBuf)
{
    //static u8 oldBuf[4] = {0xff,0xff,0xff,0xff};
    
     setUpdateUI(false);

	  if(pLocalParam->m_cRadarDataUI[4] != *(pBuf+0))
         {
        	 setAnalogData(CONTROLID_BACK_RADAR_RL_ONE_RADAR,*pBuf);
        	 pLocalParam->m_cRadarDataUI[4] = *(pBuf+0);
         }
         if(pLocalParam->m_cRadarDataUI[5] != *(pBuf+1))
         {
        	 setAnalogData(CONTROLID_BACK_RADAR_RL_TWO_RADAR,*(pBuf+1));
        	 pLocalParam->m_cRadarDataUI[5] = *(pBuf+1);
         }
         if(pLocalParam->m_cRadarDataUI[6] != *(pBuf+2))
         {
            setAnalogData(CONTROLID_BACK_RADAR_RR_ONE_RADAR,*(pBuf+2));
            pLocalParam->m_cRadarDataUI[6] = *(pBuf+2);
         }
         if(pLocalParam->m_cRadarDataUI[7] != *(pBuf+3))
         {
        	 setAnalogData(CONTROLID_BACK_RADAR_RR_TWO_RADAR,*(pBuf+3));
        	 pLocalParam->m_cRadarDataUI[7] = *(pBuf+3);
         }
		 setUpdateUI(true);
}

void systemGetRadarDataDeal(u8* pBuf){
	if(isHaveRadarData)
		return;

	if(pBuf[0]!=0 || pBuf[1]!=0 || pBuf[2] != 0 || pBuf[3]!=0)
	{
		systemToApp_BackVideo_CarRadarIsDisplay(1);
		systemToModule_NotifyOSD_IsHaveRadarData(1);
		isHaveRadarData = true;
		LOGD("------systemGetRadarDataDeal  isHaveRadarData=1");
	}
}

void halToSystem_Radar_Info_Car(u8* pBuf,u8 resCmd)
{
   switch(resCmd)
   	{
   	   case HALTOSYSTEM_RADAR_CAR_FRONT:
	   	    halToSystem_Radar_Info_FF(pBuf);
	   	    break;
	   case HALTOSYSTEM_RADAR_CAR_BEHIND:
	   	    halToSystem_Radar_Info_BB(pBuf);
	   	    break;
	   default:
	     	break;
   	}
}

void halToSystem_Radar_Info(u8* Buf,u8 resCmd)
{
  switch(resCmd)
  	{
  	  	case HALTOSYSTEM_RADAR_CAR_FRONT:
			halToSystem_Radar_Info_F(Buf);
			halToSystem_Radar_Info_FF(Buf);
			break;
        case HALTOSYSTEM_RADAR_CAR_BEHIND:
			halToSystem_Radar_Info_B(Buf);
			halToSystem_Radar_Info_BB(Buf);
			break;
        case HALTOSYSTEM_RADAR_CAR_INFO:
			//RadarInfo(Buf[0]);
			break;
		default:break;
  	}
}


/**************************************************************************************************************/
void analyseHalMessage_Global(char resCmd, unsigned char *param, unsigned char len){
	switch(resCmd){
		case 0x01:		// Power status
			break;
		case 0x02:		// working status
			break;
		case 0x11:		// \B7\B5\BBظı䣬ͬʱ\C7\E5\BFձ\EA־λ
			break;
		case 0x20:		// \C7\FD\B6\AF\D2쳣
			break;
		case 0x21:		// OSD Debug information
			{
				if(pLocalParam->DebugSwitch)
					return ;
				systemToModule_NotifyOSD_OSDDebug_Info(param, len);
			}
			break;
		default:
			break;
	}
}
//zhq add set triggertype text
void SetTriggerTypeStringText(int n)
{
	setStringText(CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_TEXT, STRINGID_SYSTEM_SETUP_BACKCAR_TRIGGER_AUTOMATIC + n);
}
void halToSystem_ReturnTriggerMessage(u8 *Param)
{
	u8 u8_Param1 = Param[1];
    u8 u8_Param2 = Param[2];
	u8 u8_Param0 = Param[0];
	LOGD("zhq[%s] u8_Param0=%x u8_Param1=%d  u8_Param2=%d  ",__FUNCTION__,Param[0],Param[1],Param[2]);
	
	if(u8_Param1 == 1 && u8_Param2 == 1)
	{
		pLocalParam->eSetupBackcarTriggerType = eSetupBackcarTriggerAutomatic;
		
	}
	if(u8_Param1 == 1 && u8_Param2 == 0)
	{
		pLocalParam->eSetupBackcarTriggerType = eSetupBackcarTriggerProtocol;
	}
	if(u8_Param1 == 0 && u8_Param2 == 1)
	{
		pLocalParam->eSetupBackcarTriggerType = eSetupBackcarTriggerLevel;
	}
	SetTriggerTypeStringText((int)pLocalParam->eSetupBackcarTriggerType);
}

void HalToSystem_TransparentChannel_Message(u8 *Param)
{
	u8 resCmd = Param[0];
	LOGD("zhq[%s] resCmd = %x  ",__FUNCTION__,Param[0]);
	switch(resCmd)
  	{
  	  	case HALTOSYSTEM_RETURN_TRIGGER_TYPE:
			halToSystem_ReturnTriggerMessage(Param);
			break;
        
		default:break;
  	}
}

void halToSystem_BatteryVolt_NewPassageway_aboutOnlinePrompt(u8 *param,int len)
{
	if(param[0] == 0x01)//ACC OFF
	{
		systemToModule_NotifyExtcarModule_CarBatteryVolt(&param[1]);
	}
	else if(param[0] == 0x00)//ACC ON
	{
	}
}

void halToSystem_NaviMixLowSwitch_Status(u8 p)
{
	pLocalParam->b_Sys_NaviMixLowSwitch = p;
	DisplaySysToUI_aboutNaviMixLow(p);
}

void halToSystem_aboutAmbientLedMsg(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x01:
			Get_AmbientLed_InitState(p[1]);
			break;
		case 0x02:
			Get_AmbientLed_SwitchState(p[1]);
			break;
		case 0x03:
			Get_AmbientLed_Dimming_Value(p[1]);
			break;
		case 0x04:
			Get_AmbientLed_RGB_Value(&p[1],len - 1);
			break;
		default:
			break;
	}
}

void Get_AmbientLed_InitState(u8 param)
{
	LOGD("------[%s]-----0x%x",__FUNCTION__,param);
	pLocalParam->uAmbientLedInitState = param;
}

void Get_AmbientLed_SwitchState(u8 param)
{
	LOGD("------[%s]-----0x%x",__FUNCTION__,param);
	pLocalParam->emAmbientLedSwitch = E_AMBIENT_LED_SWITCH(param);
	DisplayUI_AmbientLed_SwitchButton(param);
}

void Get_AmbientLed_Dimming_Value(u8 param)
{
	LOGD("------[%s]-----%d",__FUNCTION__,param);
	pLocalParam->uAmbientLedDimmValue = param;
	DisplayUI_AmbientLed_Dimming_bar_text(param);
}

void Get_AmbientLed_RGB_Value(u8 *param,u8 uLen)
{
	LOGD("------[%s]---RGB--(%d %d %d)--",__FUNCTION__,param[0],param[2],param[4]);
	LOGD("------[%s]-CYCLE--(%d %d %d)--",__FUNCTION__,param[1],param[3],param[5]);
	pLocalParam->uAmbientLedRValue[0] = param[0];
	pLocalParam->uAmbientLedRValue[1] = param[1];
	
	pLocalParam->uAmbientLedGValue[0] = param[2];
	pLocalParam->uAmbientLedGValue[1] = param[3];
	
	pLocalParam->uAmbientLedBValue[0] = param[4];
	pLocalParam->uAmbientLedBValue[1] = param[5];

	E_AMBIENT_LED_COMMISSION emT = GetTypeByLedCommissionMapping(param[0],param[2],param[4]);
	
	DisplayUI_AmbientLed_CommissionButton(emT);
	
	setRGBValueToUI(pLocalParam->uAmbientLedRValue[0],pLocalParam->uAmbientLedGValue[0],pLocalParam->uAmbientLedBValue[0]);
	int nTem = 0;
  	nTem += (int)((param[0] << 24) & 0xFF000000);
	nTem += (int)((param[2] << 16) & 0xFF0000);
	nTem += (int)((param[4] << 8) & 0xFF00);
	nTem += (int)(pLocalParam->uAmbientLedDimmValue & 0xFF);
	pLocalParam->uShowCurColorValue = nTem;
	if(emT == LED_COMMISSION_UNKNOWN)
	{
		memset(&pLocalParam->eSaveRGB_Dimming_value[0],0,sizeof(SAVE_RGB_DIMMING_VALUE));
		pLocalParam->eSaveRGB_Dimming_value[0] = saveCustomizeColorVale(param, nTem,pLocalParam->uAmbientLedDimmValue);
		setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_SHOW_CHOOSE_COLOR,nTem);
	}

	setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_PREVIEW_PAPER, nTem);
	setAnalogData(CONTROLID_SETUP_DVR_AMBIENT_LED_SHOW_CHANGED_COLOR, nTem);
}


void halToSystem_Screen_Brightness(u8 u8_Param)
{
    LOGD("halToSystem_Screen_Brightness:0x%x",u8_Param);

	u8 ansiBuf[8];
	memset(ansiBuf, 0, 8);
	sprintf((char*)ansiBuf,"%d",u8_Param);

	int nAnsiBufLen = strlen((char*)ansiBuf);
	u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
	memset(unicodeBuf, 0, nAnsiBufLen*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicodeBuf);
	setSerialData(CONTROLID_SET_SCREEN_BRIGHTNESS_TEXT,unicodeBuf, nUnicodeBufLen*2);
	free(unicodeBuf);
}

void HalToSystem_ShowDayOrNightMode_Message(u8 Param)
{
	u8 resCmd = Param;
	LOGD("[%s] Param = %x  ",__FUNCTION__,Param);
	g_clsSystem.sendToFlyJniSdkSystemDayOrNightStatus(resCmd);
	switch(resCmd)
  	{
  	  	case 0x00:
		{
			pLocalParam->curDayAndNightMode = eDayAndNight_Day;
			showDayOrNightModeStatus(0x00);
  	  	}
		break;
		case 0x01:
		{
			pLocalParam->curDayAndNightMode = eDayAndNight_Night;
			showDayOrNightModeStatus(0x01);
		}
		break;
		case 0x02:
		{
			pLocalParam->curDayAndNightMode = eDayAndNight_Auto;
			showDayOrNightModeStatus(0x02);
		}
		break;
		default:break;
  	}
}

void halToSystem_BatteryVolt_AnomalyMonitoring(u8 p)
{
	systemToModule_NotifyExtcarModule_CarBatteryVoltAnomalyMonitoring(p);
}

void halToSystem_BarCode(u8 *pBuf,u8 len)//New
{
	systemToModule_NotifyService_BarcodeInfors(pBuf,len);
}

void halToSystem_LCDBrightness_Value(u8 Param)
{
	pLocalParam->cBrightness_RangeValue = Param;
	g_clsSystem.sendToFlyJniSdkSystemBrightnessValueMessage(Param);
	halToSystem_Screen_Brightness( Param);
}
void halToSystem_LCDBrightness_OnOrOff(u8 param)
{
	if(pLocalParam->nScreenSwitchStatus == param)
		return;
	pLocalParam->nScreenSwitchStatus = param;
	if(param == 0x00)
	{
		systemToModule_NotifyKeyModule_WhetherLcdClose(true);
		systemToApp_HidePull_DownBar();
		if(PAGE_BLACK != getCurPage())
		{
			switch_Page(PAGE_BLACK);
		}
		
		g_clsSystem.sendToFlyJniSdkSystemBrightnessMessage(0x00);
	}
	else if(param == 0x01)
	{
		systemToModule_NotifyKeyModule_WhetherLcdClose(false);
		if(PAGE_BLACK == getCurPage())
		{
			anyModuleToSysModule_Switch_PrePage();
		}

		g_clsSystem.sendToFlyJniSdkSystemBrightnessMessage(pLocalParam->u8_Sys_CurLcdLight);
	}
}

void halToSystem_Radar_Info_L(u8* pBuf)
{
	//static u8 oldBuf[4] = {0xff,0xff,0xff,0xff};

	setUpdateUI(false);
	LOGD("halToSystem_Radar_Info_L f_Visible %x",pLocalParam->f_Visible);
	LOGD("halToSystem_Radar_Info_L b_old_buf :%x,%x,%x,%x",pLocalParam->m_cRadarData[8],pLocalParam->m_cRadarData[9],pLocalParam->m_cRadarData[10],pLocalParam->m_cRadarData[11]);
	LOGD("halToSystem_Radar_Info_L b_pBuf :   %x,%x,%x,%x",pBuf[0],pBuf[1],pBuf[2],pBuf[3]);
	systemGetRadarDataDeal(pBuf);
	
	if(pLocalParam->f_Visible == false)
	{
	  setVisible(CONTROLID_BACK_VIDEO_L_ONE_RADAR,true);
	  setVisible(CONTROLID_BACK_VIDEO_L_TWO_RADAR,true);
	  setVisible(CONTROLID_BACK_VIDEO_L_THREE_RADAR,true);
	  setVisible(CONTROLID_BACK_VIDEO_L_FOUR_RADAR,true);
	  pLocalParam->f_Visible = true;

	}
    
	if(pLocalParam->m_cRadarData[8] != *pBuf)
	{
		setAnalogData(CONTROLID_BACK_VIDEO_L_ONE_RADAR,*pBuf);
		pLocalParam->m_cRadarData[8] = *pBuf;
	}
	if(pLocalParam->m_cRadarData[9] != *(pBuf+1))
	{
		setAnalogData(CONTROLID_BACK_VIDEO_L_TWO_RADAR,*(pBuf+1));
		pLocalParam->m_cRadarData[9] = *(pBuf+1);
	}
	if(pLocalParam->m_cRadarData[10] != *(pBuf+2))
	{
		setAnalogData(CONTROLID_BACK_VIDEO_L_THREE_RADAR,*(pBuf+2));
		pLocalParam->m_cRadarData[10] = *(pBuf+2);
	}
	if(pLocalParam->m_cRadarData[11] != *(pBuf+3))
	{
		setAnalogData(CONTROLID_BACK_VIDEO_L_FOUR_RADAR,*(pBuf+3));
		pLocalParam->m_cRadarData[11] = *(pBuf+3);
	}

   	setUpdateUI(true);
	
}
void halToSystem_Radar_Info_LL(u8* pBuf)
{
	//static u8 oldBuf[4] = {0xff,0xff,0xff,0xff};
    	setUpdateUI(false);

	if(pLocalParam->m_cRadarDataUI[8] != *pBuf)
	 {
		 setAnalogData(CONTROLID_BACK_RADAR_L_ONE_RADAR,*pBuf);
		 pLocalParam->m_cRadarDataUI[8] = *pBuf;
	 }
         if(pLocalParam->m_cRadarDataUI[9] != *(pBuf+1))
	{
	    	 setAnalogData(CONTROLID_BACK_RADAR_L_TWO_RADAR,*(pBuf+1));
	    	 pLocalParam->m_cRadarDataUI[9] = *(pBuf+1);
	 }
         if(pLocalParam->m_cRadarDataUI[10] != *(pBuf+2))
	 {
        	 setAnalogData(CONTROLID_BACK_RADAR_L_THREE_RADAR,*(pBuf+2));
        	 pLocalParam->m_cRadarDataUI[10] = *(pBuf+2);
	}
        if(pLocalParam->m_cRadarDataUI[11] != *(pBuf+3))
        {
        	 setAnalogData(CONTROLID_BACK_RADAR_L_FOUR_RADAR,*(pBuf+3));
        	 pLocalParam->m_cRadarDataUI[11] = *(pBuf+3);
        }

         setUpdateUI(true);
}


void halToSystem_Radar_Info_R(u8* pBuf)
{
	//static u8 oldBuf[4] = {0xff,0xff,0xff,0xff};

	setUpdateUI(false);
	LOGD("halToSystem_Radar_Info_R f_Visible %x",pLocalParam->f_Visible);
	LOGD("halToSystem_Radar_Info_R b_old_buf :%x,%x,%x,%x",pLocalParam->m_cRadarData[12],pLocalParam->m_cRadarData[13],pLocalParam->m_cRadarData[14],pLocalParam->m_cRadarData[15]);
	LOGD("halToSystem_Radar_Info_R b_pBuf :   %x,%x,%x,%x",pBuf[0],pBuf[1],pBuf[2],pBuf[3]);
	systemGetRadarDataDeal(pBuf);
	
	if(pLocalParam->f_Visible == false)
	{
	  setVisible(CONTROLID_BACK_VIDEO_R_ONE_RADAR,true);
	  setVisible(CONTROLID_BACK_VIDEO_R_TWO_RADAR,true);
	  setVisible(CONTROLID_BACK_VIDEO_R_THREE_RADAR,true);
	  setVisible(CONTROLID_BACK_VIDEO_R_FOUR_RADAR,true);
	  pLocalParam->f_Visible = true;

	}
    
	if(pLocalParam->m_cRadarData[12] != *pBuf)
	{
        	 setAnalogData(CONTROLID_BACK_VIDEO_R_ONE_RADAR,*pBuf);
        	 pLocalParam->m_cRadarData[12] = *pBuf;
	}
   	if(pLocalParam->m_cRadarData[13] != *(pBuf+1))
	{
        	 setAnalogData(CONTROLID_BACK_VIDEO_R_TWO_RADAR,*(pBuf+1));
        	 pLocalParam->m_cRadarData[13] = *(pBuf+1);
	}
  	if(pLocalParam->m_cRadarData[14] != *(pBuf+2))
    	{
        	 setAnalogData(CONTROLID_BACK_VIDEO_R_THREE_RADAR,*(pBuf+2));
        	 pLocalParam->m_cRadarData[14] = *(pBuf+2);
	}
   	if(pLocalParam->m_cRadarData[15] != *(pBuf+3))
   	{
        	 setAnalogData(CONTROLID_BACK_VIDEO_R_FOUR_RADAR,*(pBuf+3));
        	 pLocalParam->m_cRadarData[15] = *(pBuf+3);
   	}
   	setUpdateUI(true);
	
}
void halToSystem_Radar_Info_RR(u8* pBuf)
{
    	setUpdateUI(false);

	if(pLocalParam->m_cRadarDataUI[12] != *pBuf)
	 {
		 setAnalogData(CONTROLID_BACK_RADAR_R_ONE_RADAR,*pBuf);
		 pLocalParam->m_cRadarDataUI[12] = *pBuf;
	 }
         if(pLocalParam->m_cRadarDataUI[13] != *(pBuf+1))
	{
        	 setAnalogData(CONTROLID_BACK_RADAR_R_TWO_RADAR,*(pBuf+1));
        	 pLocalParam->m_cRadarDataUI[13] = *(pBuf+1);
	}
        if(pLocalParam->m_cRadarDataUI[14] != *(pBuf+2))
	{
        	 setAnalogData(CONTROLID_BACK_RADAR_R_THREE_RADAR,*(pBuf+2));
        	 pLocalParam->m_cRadarDataUI[14] = *(pBuf+2);
	}
        if(pLocalParam->m_cRadarDataUI[15] != *(pBuf+3))
        {
        	 setAnalogData(CONTROLID_BACK_RADAR_R_FOUR_RADAR,*(pBuf+3));
        	 pLocalParam->m_cRadarDataUI[15] = *(pBuf+3);
        }
        setUpdateUI(true);
}

void HalToSystem_AutoAdjustmentSwitchOfScreenBrightnessStatus(u8 p)
{
	pLocalParam->uScreenBrightAutoSwtich = p;
	g_clsSystem.sendToFlyJniSdkSystemAutoLightStatus(p);
	if(p == 0x01)//open
	{
		DisplayScreenBrithnessAutoAdjustSwitchButtonUI(true);
	}
	else
	{
		DisplayScreenBrithnessAutoAdjustSwitchButtonUI(false);
	}
}
