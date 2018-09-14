#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
//#include <cutils/properties.h>
#include <ctype.h>
#include <android/log.h>
#include "types_def.h"
#include "commonFunc.h"
#include "halResponseFunction.h"
#include "param.h"
#include "controlID.h"
#include "otherModuleResponseFunction.h"
#include "pageID.h"
#include "appRequestCommand.h"
#include "halRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "timer_interface.h"
#include "moduleParamResponse.h"
extern "C"{
#include "unicodestring.h"
#include "barcode_access.h"
//#include "productinfo_access.h"
};


//������ѧϰ

#define FLY_MODULE_IS_T123 "fly.module.is.T123"
#define FLY_MODULE_WHICH_PROJECT 	"fly.module.whichProject"

#define KB_AV			            "fly.stStudy.AV"
#define KB_MUTE			            "fly.stStudy.MUTE"
#define KB_VOL_INC		            "fly.stStudy.VOL_INC"
#define KB_VOL_DEC		            "fly.stStudy.VOL_DEC"
#define KB_SEEK_INC		            "fly.stStudy.SEEK_INC"
#define KB_SEEK_DEC		            "fly.stStudy.SEEK_DEC"
#define KB_CALL_INOUT	            "fly.stStudy.CALL_INOUT"
#define KB_CALL_REJECT	            "fly.stStudy.CALL_REJECT"


#define FLY_SET_LIGHTDETECT         "fly.set.b_Sys_LightDetect"
#define FLY_SET_DAYNIGHT            "fly.set.b_Sys_DayNight"

#define FLY_SET_PANELLIGHT          "fly.set.b_Sys_PanelLight"
#define FLY_SET_PANELLIGHT_BEFORE          "fly.set.b_Sys_PanelLight_before"

#define FLY_SET_FIRSTSTARTUPVOL     "fly.set.first_StartupVol"
#define FLY_SET_FIRSTSTARTUPVOL_BEF     "fly.set.first_StartupVol_bef"

#define FLY_SET_LCDLIGHT            "fly.set.b_Sys_LcdLight"

#define FLY_SET_STANDBYSTATUS       "fly.set.b_Sys_StandbyStatus"
#define FLY_SET_AMPLIFIERSTATUS     "fly.set.b_Sys_AmplifierStatus"
#define FLY_SET_AUTORUNGPS          "fly.set.b_Sys_AutoRunGPS"
#define FLY_SET_GPSVOICEPROMPT      "fly.set.b_Sys_GPSVoicePrompt"
#define FLY_SET_BACKCARDETECTENABLE "fly.set.b_Sys_backCarCheck"
#define FLY_SET_BACKCARSTATUS       "fly.set.b_Sys_BackCarStatus"
#define FLY_SET_BACKCARVIDEO        "fly.set.b_Sys_BackCarVideo"
#define FLY_SET_AUXVIDEO            "fly.set.b_Sys_AuxVideo"

#define FLY_SET_AUTO_AUTOSOUND		"fly.set.b_Sys_Auto_AutoSound"

#define FLY_SET_IPODORAUX           "fly.set.b_Sys_IpodOrAux"
#define FLY_SET_TVORXM              "fly.set.b_Sys_TVOrXM"
#define FLY_SET_SPECIALSTEERINGWHEEL "fly.set.b_Sys_SpecialSteeringWheel"
#define FLY_SET_USERSTEERINGWHEEL   "fly.set.b_Sys_UserSteeringWheel"
#define FLY_SET_WAITSTUDY           "fly.set.b_Sys_WaitStudy"
#define FLY_SET_RADIOCOUNTRYCODE    "fly.set.b_Sys_RadioCountryCode"
#define FLY_SET_DVDREGIONCODE       "fly.set.b_Sys_DVDRegionCode"
#define FLY_SET_WHETHERTVEXIST      "fly.set.b_Sys_WhetherTVExist"
#define FLY_SET_WHETHERTPMSEXIST    "fly.set.b_Sys_WhetherTPMSExist"
#define FLY_SET_HOURPERDAY_24       "fly.set.b_Sys_HourPerDay_24"
#define FLY_SET_CURCLEARKEY         "fly.set.u_curclearkey"

#define FLY_VOL_MAX                 "fly.vol.startup.max"
#define FLY_VOL_DEFUALT             "fly.vol.startup.default"
#define FLY_VOL_MIN                 "fly.vol.startup.min"
#define FLY_MODULE_TABLE            "fly.module.switch"
#define FLY_TPYE_VERSION 			"fly.tpye.version"
#define FLY_SET_CHANNEL  			"fly.set.channel"
#define FLY_ISAUX					"fly.flyui.aux"
#define FLY_CARNAME          		"fly.carName"

#define FLY_MCU                     "fly.mcu.version"
#define FLY_SET_DVRORTV             "fly.set.b_Sys_DVROrTV"
#define FLY_DEFAULT_CONFIG_EXTERDEV   "fly.moduleconfig.switchExterDev"
#define FLY_SET_VOICEPROMPT         "fly.set.b_Sys_VoicePrompt"
#define FLY_SET_NAVINUB             "fly.set.NaviNub"
#define FLY_SET_BSHOWREVISECARMODEPAGE "fly.set.bShowReviseCarModePage"
#define FLY_SET_CREALCARMODE        "fly.set.cRealCarMode"
#define FLY_SPECIFICSKIN_PREPAGE	"fly.specificSkin.prePage" /*MSM_8625ï¿œï¿œï¿œÚºÚºï¿œÆ€ï¿œï¿œ×šï¿œï¿œ*/

#define FLY_BRIGHTNESS_DIM           "fly.set.brightness.dim"
#define FLY_BRIGHTNESS_MODERATE      "fly.set.brightness.moderate"
#define FLY_BRIGHTNESS_BRIGHT        "fly.set.brightness.bright"
#define FLY_BRIGHTNESS_RANGEVALUE	 "fly.set.brightness.rangevalue"
#define FLY_DVR_TV_TPMS_VISIBLE    "fly.flyui.dvr.tvtpms"
#define FLY_SET_UPDATE_MODE       "fly.set.update.mode"
#define FLY_NAVIGATION_VISIBLE     "fly.flyui.navigation.visible"

#define FLY_FLYUI_DVD_REGION         "fly.flyui.dvd.region"
#define FLY_FLYUI_RADIO_COUNTRY      "fly.flyui.radio.country"
#define FLY_FLYUI_CARTYPE_VISIBLE    "fly.flyui.cartype.visible"
#define FLY_FLYUI_CARMATCH_SHOW      "fly.flyui.carmatch.show"
#define FLY_FLYUI_CARALARM_VISIBLE    "fly.flyui.alarm.visible"
#define FLY_SET_BREAKCAR_ENABLE        "fly.set.breakcar.enable"
#define FLY_SET_NAVIGATION_BOOTRUNMOD  "fly.set.navigation.bootrunmod"
#define FLY_SET_BACK_REFLINEDISPLAY    "fly.set.back.refliendispaly"
#define FLY_SET_BACKCAR_HASREDLINE     "fly.backcar.hasredline"
#define FLY_SET_BOOTON_ISAUTOPLAY      "fly.booton.isautopaly"
#define FLY_SET_BACK_CAR_MODE			"fly.set.backcar.mode"
#define FLY_SET_BACKCAR_VIDEOSWITCH		"fly.set.backcar.videoswtich"
#define FLY_SET_BACK_TRACE_LINEDISPLAY  "fly.set.back.traceline"

//zhq dnv
#define FLY_SET_DNVSUPPORT       "fly.set.m_bSupportDNV"


// system setting page
#define FLY_SET_SYSTEM_FAN			"fly.set.system.fan"
#define FLY_SET_SYSTEM_VOLTAGE_PROTECTION_MODE		"fly.set.system.voltage.protection.mode"

//zhq add checktype
#define FLY_SET_SYSTEM_BACKCAR_TRIGGER_TYPE		"fly.set.system.triggertype"
#define FLY_SET_SYSTEM_BACKCAR_TRIGGER_TYPE_CONFIG		"fly.System.TriggerConfig"

#define FLY_DEFAULT_NAVI_RUNMOD "fly.default.navi.runmod"

#define FLY_HOMEPAGE_OSD_VISIBLE        "fly.homepage.osd.visible"
#define FLY_SET_LOGO_STYLE_NUB             "fly.set.logoStyle.Nub"
#define FLY_SET_NAVI_MIX_LOW             "fly.set.navi.mixlow"

#define FLY_SET_LED_SWTICH  "fly.set.led.switch"
#define FLY_SET_LED_COMMISSION "fly.set.led.commiss"

#define FLY_DVR_PROTOCOL_MODE_CONFIG		"fly.dvr.protocolMode.config"
#define FLY_DVR_SET_PROTOCOL_MODE		"fly.dvr.protocol.mode"

#define FLY_DVR_SAVE_LED_RGB_DIMMING		"fly.dvr.save.led.rgb.dimming"

#define FLY_SET_CVBS_USB_SWITCH_CONFIG             "fly.set.cvsb.switconfig"
//#define FLY_SET_CVBS_USB_SWITCH             "fly.set.cvsb.swit"
#define FLY_SET_CVBS_USB_SWITCH             "persist.set.cvsb.swit"

#define FLY_SET_DAY_OR_NIGHT_MODE		"fly.set.day.or.night.mode"

#define FLY_FLYUI_UNIFIEDCALL		"fly.flyui.unifiedcall"
#define FLY_DESKTOP_NAVI_INFOR_SYNC_SWITCH "fly.conf.dtp.navi.switch"
#define FLY_DESKTOP_NAVI_SWITCH  "persist.desktop.navi.switch"

#define FLY_SYSTEM_PAGE_TYPE  "fly.system.page.type"
#define CONFIG_SCREEN_BRIGHT_AUTO_SWITCH "fly.config.screen.autoswitch"
#define FLY_SCREEN_BRIGHT_AUTO_SWITCH "fly.screen.autoswitch"

#define FLY_SET_CUR_CAR_DEFAULT_TYPE             "fly.set.cur.car.default.type"
#define FLY_SET_CUR_CAR_TYPE             "fly.set.cur.car.type"


system_local_param_t localParam;
system_local_param_t *pLocalParam = (system_local_param_t*)&localParam;

system_global_param_t globalParam;
system_global_param_t *pGlobalParam = (system_global_param_t*)&globalParam;

CNotifyAndResponseFlyJniSdk g_clsSystem;

void readParameter(void)
{
	    SystemModule_SetDefaultParam();
		readParam_aboutCvbsOrUsb();

		char property[PROPERTY_VALUE_MAX];

		property_get(FLY_SYSTEM_PAGE_TYPE,property,"0");
		sscanf(property,"%d",&pLocalParam->systemSkinType);

		property_get(FLY_MODULE_IS_T123,property,"0");
	  	sscanf(property,"%d",&pLocalParam->uModuleSystem_is_T123);

		property_get(FLY_MODULE_WHICH_PROJECT,property,"0");
		sscanf(property,"%s",pLocalParam->str_WhichProject);
		
		property_get(FLY_SET_BACKCAR_VIDEOSWITCH, property, "1");
        sscanf(property,"%d", &pLocalParam->uBackCarVideoSwitch_Status);
        LOGD("[%s] pLocalParam->uBackCarVideoSwitch_Status = [%d]", __FUNCTION__, pLocalParam->uBackCarVideoSwitch_Status);
        
        property_get(FLY_SET_BOOTON_ISAUTOPLAY,property,"1");
        sscanf(property,"%d", &localParam.u8BootOnIsAutoPlay);
        LOGD("readParameter----localParam.u8BootOnIsAutoPlay:%d",localParam.u8BootOnIsAutoPlay);

   		int nNaviParam = 0;
		property_get(FLY_DEFAULT_NAVI_RUNMOD,property,"2");
		sscanf(property,"%d", &nNaviParam);

        property_get(FLY_SET_NAVIGATION_BOOTRUNMOD,property,"255");
       	sscanf(property,"%d", &pLocalParam->nNavigationBootingRunMod);
		if(pLocalParam->nNavigationBootingRunMod == 255){
			pLocalParam->nNavigationBootingRunMod = nNaviParam;
		}
       	LOGD("readParameter----pLocalParam->nNavigationBootingRunMod:0x%x",pLocalParam->nNavigationBootingRunMod);

		property_get(FLY_SET_CURCLEARKEY,property,"255");
		sscanf(property,"%hhd", &pLocalParam->m_cCurClearKey);
		LOGD("readParameter----pLocalParam->m_cCurClearKey:0x%x",pLocalParam->m_cCurClearKey);

		//property_get(FLY_SET_LCDLIGHT,property,"3");
		//sscanf(property,"%hhd", &pLocalParam->u8_Sys_CurLcdLight);
		//LOGD("++++++pLocalParam->u8_Sys_CurLcdLight---0x%x",pLocalParam->u8_Sys_CurLcdLight);

		property_get(FLY_SET_LIGHTDETECT,property,"1");
		sscanf(property,"%hhd", &pLocalParam->b_Sys_LightDetect);

		property_get(FLY_SET_DAYNIGHT,property,"0");
		sscanf(property,"%hhd", &pLocalParam->b_Sys_DayNight);

		property_get(FLY_SET_PANELLIGHT,property,"255");
		sscanf(property,"%hhd", &pLocalParam->u8_Sys_PanelLight);

		property_get(FLY_SET_PANELLIGHT_BEFORE,property,"255");
		sscanf(property,"%hhd", &pLocalParam->u8_Sys_PanelLight_bef);

		property_get(FLY_SET_STANDBYSTATUS,property,"0");
		sscanf(property,"%hhd", &pLocalParam->b_Sys_SpecialSteeringWheel);

		property_get(FLY_SET_AMPLIFIERSTATUS,property,"0");
		sscanf(property,"%hhd", &pLocalParam->b_Sys_AmplifierStatus);
        
        property_get(FLY_SET_BREAKCAR_ENABLE,property,"0");
		sscanf(property,"%hhd", &pLocalParam->cBreakCarEnable);
        LOGD("read---cBreakCarEnable=%d",pLocalParam->cBreakCarEnable);

		property_get(FLY_SET_AUTORUNGPS,property,"0");
		sscanf(property,"%hhd", &pLocalParam->b_Sys_AutoRunGPS);

		
		property_get(FLY_SET_AUTO_AUTOSOUND,property,"0");
		sscanf(property,"%d", &pLocalParam->b_Sys_Auto_AutoSound);

		property_get(FLY_SET_GPSVOICEPROMPT,property,"1");
		sscanf(property,"%hhd", &pLocalParam->b_Sys_GPSVoicePrompt);


		property_get(FLY_SET_BACKCARDETECTENABLE,property,"1");
		sscanf(property,"%hhd", &pLocalParam->b_Sys_BackCarDetectEnable);


		property_get(FLY_SET_BACKCARVIDEO,property,"0");
		sscanf(property,"%hhd", &pLocalParam->b_Sys_BackCarVideo);


		property_get(FLY_SET_AUXVIDEO,property,"0");
		sscanf(property,"%hhd", &pLocalParam->u8_Sys_AuxVideo);


		property_get(FLY_SET_IPODORAUX,property,"0");

		sscanf(property,"%hhd", &pLocalParam->b_Sys_Ipod);
		LOGD("pLocalParam->b_Sys_Ipod:0x%x",pLocalParam->b_Sys_Ipod);
		property_get(FLY_SET_TVORXM,property,"1");
		sscanf(property,"%hhd", &pLocalParam->b_Sys_TVOrXM);


		property_get(FLY_SET_SPECIALSTEERINGWHEEL,property,"0");
		sscanf(property,"%hhd", &pLocalParam->b_Sys_SpecialSteeringWheel);

		property_get(FLY_SET_USERSTEERINGWHEEL,property,"0");
		sscanf(property,"%hhd", &pLocalParam->u8_Sys_UserSteeringWheel);

		property_get(FLY_SET_WAITSTUDY,property,"0");
		sscanf(property,"%hhd", &pLocalParam->b_Sys_WaitStudy);

		property_get(FLY_SET_RADIOCOUNTRYCODE,property,"0");
		sscanf(property,"%hhd", &pLocalParam->u8_Sys_RadioCountryCode);

		property_get(FLY_SET_DVDREGIONCODE,property,"0");
		sscanf(property,"%hhd", &pLocalParam->u8_Sys_DVDRegionCode);

		//property_get(FLY_SET_WHETHERTVEXIST,property,"0");
		//sscanf(property,"%hhd", &pLocalParam->u8_Sys_WhetherTVExist);

		property_get(FLY_SET_WHETHERTPMSEXIST,property,"1");
		sscanf(property,"%hhd", &pLocalParam->u8_Sys_WhetherTPMSExist);

		//property_get(FLY_SET_AUXVIDEO,property,"0");
		//sscanf(property,"%hhd", &pLocalParam->u8_Sys_AUXVideo);

		property_get(FLY_VOL_MAX,property,"40");
		sscanf(property,"%d",&pLocalParam->Start_MaxVol);


	//***************************************************
		property_get(FLY_VOL_MIN,property,"10");
		sscanf(property,"%d",&pLocalParam->Start_minVol);

		property_get(FLY_VOL_DEFUALT,property,"15");
		sscanf(property,"%d",&pLocalParam->Start_defaultVol);



		property_get(FLY_SET_FIRSTSTARTUPVOL,property,"0");
		sscanf(property,"%hhd",&pLocalParam->u8_Sys_StartupVol);

		if(0==pLocalParam->u8_Sys_StartupVol)
		{
			pLocalParam->u8_Sys_StartupVol=pLocalParam->Start_defaultVol;
		}

		property_get(FLY_SET_FIRSTSTARTUPVOL_BEF,property,"0");
		sscanf(property,"%hhd",&pLocalParam->u8_Sys_StartupVol_bef);

		if(0==pLocalParam->u8_Sys_StartupVol_bef)
		{
			pLocalParam->u8_Sys_StartupVol_bef=pLocalParam->Start_defaultVol;
		}
		
		property_get(FLY_CARNAME,property,"0");
		sscanf(property,"%s",&pLocalParam->CarName);

		////-------------------add----2013-4-19--------------------------------//
		property_get(FLY_TPYE_VERSION,property,"0");
		sscanf(property,"%d",&pLocalParam->Car_type_version);

		property_get(FLY_SET_CHANNEL,property,"0");
		sscanf(property,"%d",&pLocalParam->Default_channel);
		////------------------------------------------------------------------//

        property_get(FLY_MODULE_TABLE,property,"0");
		sscanf(property,"%s",&pLocalParam->c_ModuleTable);
		LOGD("pLocalParam->c_ModuleTable:%s",pLocalParam->c_ModuleTable);

        property_get(FLY_ISAUX,property,"1");
		sscanf(property,"%d",&pLocalParam->b_isAUX);
		LOGD("pLocalParam->b_isAUX %d",pLocalParam->b_isAUX);

		
        property_get(FLY_DEFAULT_CONFIG_EXTERDEV,property,"0");
        sscanf(property,"%s", &pLocalParam->uSystemExterDeviceGroup);

		int t = 0;
		property_get(FLY_SET_DVRORTV,property,"255");
		sscanf(property,"%d", &t);
		pLocalParam->m_eExternalDevice = (E_EXTERNAL_DEVICE)t;
		LOGD("pLocalParam->m_eExternalDevice %d",pLocalParam->m_eExternalDevice);
		
		property_get(FLY_DVR_TV_TPMS_VISIBLE,property,"1");
		sscanf(property,"%d", &pLocalParam->uDvrTvTpmsVisible);
		LOGD("pLocalParam->uDvrTvTpms %d",pLocalParam->uDvrTvTpmsVisible);

		property_get(FLY_NAVIGATION_VISIBLE,property,"1");
		sscanf(property,"%d", &pLocalParam->cNavigationVisible);
		LOGD("pLocalParam->cNavigationVisible %d",pLocalParam->cNavigationVisible);

		property_get(FLY_SET_UPDATE_MODE,property,"0");
		sscanf(property,"%d", &pLocalParam->cSystemUpdateMode);
		LOGD("pLocalParam->cSystemUpdateMode %d",pLocalParam->cSystemUpdateMode);

		property_get(FLY_SET_VOICEPROMPT,property,"1");
		sscanf(property,"%d", &pLocalParam->b_Sys_VoicePrompt);
		LOGD("pLocalParam->b_Sys_VoicePrompt %d",pLocalParam->b_Sys_VoicePrompt);
		
		property_get(FLY_SET_NAVINUB,property,"0");
		sscanf(property,"%d", &pLocalParam->NaviNub);
		LOGD("pLocalParam->NaviNub %d",pLocalParam->NaviNub);

		
		property_get(FLY_SET_BSHOWREVISECARMODEPAGE,property,"1");
		sscanf(property,"%d", &pLocalParam->bShowReviseCarModePage);
		LOGD("ppLocalParam->bShowReviseCarModePage %d",pLocalParam->bShowReviseCarModePage);

		property_get(FLY_SET_CREALCARMODE,property,"0");
		sscanf(property,"%s", pLocalParam->cRealCarMode);
		LOGD("pLocalParam->cRealCarMode %s",pLocalParam->cRealCarMode);
		
		pLocalParam->cRealCarModeLen=strlen((char*)pLocalParam->cRealCarMode);
		LOGD("pLocalParam->cRealCarModeLen:%d",pLocalParam->cRealCarModeLen);

		//zhq  DNV
		property_get(FLY_SET_DNVSUPPORT,property,"1");
		sscanf(property,"%d", &pLocalParam->m_bSupportDNV);
		LOGD("[%s]  pLocalParam->m_bSupportDNV= %d",  __FUNCTION__,pLocalParam->m_bSupportDNV);
		
		// system setting page
		property_get(FLY_SET_SYSTEM_FAN,property,"4");
		sscanf(property,"%d", &pLocalParam->eCurFanMode);
		LOGD("pLocalParam->eCurFanMode %d",pLocalParam->eCurFanMode);

		property_get(FLY_SET_SYSTEM_VOLTAGE_PROTECTION_MODE,property,"0");
		sscanf(property,"%d", &pLocalParam->eVoltageProtectionMode);
		LOGD("pLocalParam->eVoltageProtectionMode %d",pLocalParam->eVoltageProtectionMode);
		//zhq add checktype
		int a = 0;
		property_get(FLY_SET_SYSTEM_BACKCAR_TRIGGER_TYPE,property,"3");
		sscanf(property,"%d", &a);
		pLocalParam->eSetupBackcarTriggerType = (E_SETUP_BACKCAR_TRIGGER)a;
		LOGD("pLocalParam->eSetupBackcarTriggerType %d",pLocalParam->eSetupBackcarTriggerType);

		property_get(FLY_SET_SYSTEM_BACKCAR_TRIGGER_TYPE_CONFIG,property,"0");
        	sscanf(property,"%s", &pLocalParam->uSystemBackcarTtiggerGroup);
		LOGD("pLocalParam->uSystemBackcarTtiggerGroup %d",pLocalParam->uSystemBackcarTtiggerGroup);
		
		property_get(FLY_SPECIFICSKIN_PREPAGE,property,"0");
		sscanf(property,"%d", &pLocalParam->nSpecificSkin_PrePage);
		LOGD("pLocalParam->nSpecificSkin_PrePage %d",pLocalParam->nSpecificSkin_PrePage);
		
		
		property_get("persist.fly.car.select",property,"0");		
		sscanf(property,"%s", pLocalParam->cChoseeCarMode);
		pLocalParam->cChoseeCarModeLen=strlen((char*)pLocalParam->cChoseeCarMode);

		property_get(FLY_BRIGHTNESS_DIM,property,"1");
		sscanf(property,"%d", &pLocalParam->cBrightness_Dim);
		
		property_get(FLY_BRIGHTNESS_MODERATE,property,"34");
		sscanf(property,"%d", &pLocalParam->cBrightness_Moderate);
		
		property_get(FLY_BRIGHTNESS_BRIGHT,property,"67");
		sscanf(property,"%d", &pLocalParam->cBrightness_Bright);

		//property_get(FLY_BRIGHTNESS_RANGEVALUE,property,"65");
		//sscanf(property,"%d", &pLocalParam->cBrightness_RangeValue);
		
		property_get(FLY_FLYUI_DVD_REGION,property,"6");
		sscanf(property,"%d", &pLocalParam->cDvdRegion);

		property_get(FLY_FLYUI_RADIO_COUNTRY,property,"0");
		sscanf(property,"%d", &pLocalParam->cRadioCountry);

		property_get(FLY_FLYUI_CARTYPE_VISIBLE,property,"1");
		sscanf(property,"%d", &pLocalParam->cCarTypeVisible);

		property_get(FLY_FLYUI_CARMATCH_SHOW,property,"1");
		sscanf(property,"%d", &pLocalParam->cCarMatchShow);


		property_get(FLY_FLYUI_CARALARM_VISIBLE,property,"1");
		sscanf(property,"%d", &pLocalParam->cCarAlarmVisible);

	        static u8 u_BackCarHasredLine = 2;
	        property_get(FLY_SET_BACKCAR_HASREDLINE,property,"2");
	        sscanf(property,"%d", &u_BackCarHasredLine);

	        property_get(FLY_SET_BACK_REFLINEDISPLAY,property,"2");
	        sscanf(property,"%d", &pLocalParam->eBackVideoRefLineIsDisplay);

	        if(pLocalParam->eBackVideoRefLineIsDisplay == eLineState_Unkown)
	        {
	            if(u_BackCarHasredLine == 0)
	            {
	                pLocalParam->eBackVideoRefLineIsDisplay = eLineState_NoShow;
	            }
	            else
	            {
	                pLocalParam->eBackVideoRefLineIsDisplay = eLineState_IsShow;
	            }
	        }

		property_get(FLY_SET_BACK_TRACE_LINEDISPLAY,property,"0");
        	sscanf(property,"%d", &pLocalParam->eBackVideoTraceLineIsDisplay);
		
	        //åèœŠæš¡åŒ
	        property_get(FLY_SET_BACK_CAR_MODE, property, "0");
	        sscanf(property,"%d", &pLocalParam->m_eBackCarMode);
	        LOGD("[%s] pLocalParam->m_eBackCarMode = [%d]", __FUNCTION__, pLocalParam->m_eBackCarMode);
		
		property_get(FLY_HOMEPAGE_OSD_VISIBLE,property,"1");
		sscanf(property,"%d", &pLocalParam->bHomePageOSDCanDrop);
        //    SystemModule_WheelDataFromRegest();

		property_get(FLY_SET_LOGO_STYLE_NUB,property,"0");
		sscanf(property,"%d", &pLocalParam->uLogoSetNub);
		LOGD("pLocalParam->uLogoSetNub %d",pLocalParam->uLogoSetNub);

		property_get(FLY_SET_NAVI_MIX_LOW,property,"1");
		sscanf(property,"%d", &pLocalParam->b_Sys_NaviMixLowSwitch);

		property_get(FLY_SET_LED_SWTICH,property,"0");
		sscanf(property,"%d", &pLocalParam->emAmbientLedSwitch);

		property_get(FLY_SET_LED_COMMISSION,property,"0");
		sscanf(property,"%d", &pLocalParam->emAmbientLedCommission);

		static u8 u_TemDvrProtocolMode = 2;
		property_get(FLY_DVR_PROTOCOL_MODE_CONFIG, property, "2");
		sscanf(property,"%d", &u_TemDvrProtocolMode);
		
		property_get(FLY_DVR_SET_PROTOCOL_MODE, property, "2");
		sscanf(property,"%d", &pLocalParam->eDvrProtocolMode);
		
		if(pLocalParam->eDvrProtocolMode == e_Unkown_ProTocol)
		{
			if(u_TemDvrProtocolMode == 0)
				pLocalParam->eDvrProtocolMode = e_Is_ProTocol;
			else
				pLocalParam->eDvrProtocolMode = e_No_ProTocol;
		}

		u8 buff[21] = {0};
		int value = 0;
		property_get(FLY_DVR_SAVE_LED_RGB_DIMMING, property, NULL);
		value = stringToBuffer(property, (char *)buff);
		if(value > 0)
		{
			for(int i = 0;i < SAVE_RGB_NUM ;i++)
			{
				pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveRValue[0] = *(buff+(i*7+0));
				pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveRValue[1] = *(buff+(i*7+1));
				pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveGValue[0] = *(buff+(i*7+2));
				pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveGValue[1] = *(buff+(i*7+3));
				pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveBValue[0] = *(buff+(i*7+4));
				pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveBValue[1] = *(buff+(i*7+5));
				pLocalParam->eSaveRGB_Dimming_value[i].uShowCurSaveColorValue = *(buff+(i*7+6));
			}
		}
		property_get(FLY_SET_DAY_OR_NIGHT_MODE,property,"2");
		sscanf(property,"%d", &pLocalParam->curDayAndNightMode);
		
		property_get(FLY_FLYUI_UNIFIEDCALL, property, "0");
		sscanf(property,"%hhd", &pLocalParam->curDailingOption);

		static u8 u_TemSyncInforSwitch = 2;
		property_get(FLY_DESKTOP_NAVI_INFOR_SYNC_SWITCH, property, "2");
		sscanf(property,"%hhd", &u_TemSyncInforSwitch);

		property_get(FLY_DESKTOP_NAVI_SWITCH,property,"2");
		sscanf(property,"%hhd",&pLocalParam->uDesktopNivaInforSwitch);
		LOGD("pLocalParam->uDesktopNivaInforSwitch: %x u_TemSyncInforSwitch: %x",pLocalParam->uDesktopNivaInforSwitch,u_TemSyncInforSwitch);
		if(pLocalParam->uDesktopNivaInforSwitch == 2)
		{
			if(u_TemSyncInforSwitch == 1)
				pLocalParam->uDesktopNivaInforSwitch = 0;
			else
				pLocalParam->uDesktopNivaInforSwitch = 1;
		}

		static u8 u_TemScreenAutoSwitch = 2;
		property_get(CONFIG_SCREEN_BRIGHT_AUTO_SWITCH, property, "2");
		sscanf(property,"%hhd", &u_TemScreenAutoSwitch);

		property_get(FLY_SCREEN_BRIGHT_AUTO_SWITCH,property,"2");
		sscanf(property,"%hhd",&pLocalParam->uScreenBrightAutoSwtich);
		if(pLocalParam->uScreenBrightAutoSwtich == 2)
		{
			if(u_TemScreenAutoSwitch == 1)
				pLocalParam->uScreenBrightAutoSwtich = 1;
			else
				pLocalParam->uScreenBrightAutoSwtich = 0;
		}

		u8 defaltCarType = 0x02;
		property_get(FLY_SET_CUR_CAR_DEFAULT_TYPE,property,"2");
		sscanf(property,"%hhd",&defaltCarType);
		
		property_get(FLY_SET_CUR_CAR_TYPE,property,"255");
		sscanf(property,"%hhd",&pLocalParam->uCurCartype);
		if(pLocalParam->uCurCartype == 0xff)
		{
			pLocalParam->uCurCartype = defaltCarType;
		}
		pLocalParam->uCurSelectionCarType = pLocalParam->uCurCartype;
    	LOGD("SYSTEM READ PARAM END");
}
void SystemModule_WheelDataFromRegest()
{

  SystemModule_WheelDataFromRegest_Key(KB_MUTE,CONTROLID_SYSTEM_WHEEL_LEARNING_MUTE);
  SystemModule_WheelDataFromRegest_Key(KB_VOL_INC,CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_INC);
  SystemModule_WheelDataFromRegest_Key(KB_VOL_DEC,CONTROLID_SYSTEM_WHEEL_LEARNING_VOL_DEC);
  SystemModule_WheelDataFromRegest_Key(KB_SEEK_INC,CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_INC);
  SystemModule_WheelDataFromRegest_Key(KB_SEEK_DEC,CONTROLID_SYSTEM_WHEEL_LEARNING_SEEK_DEC);
  SystemModule_WheelDataFromRegest_Key(KB_AV,CONTROLID_SYSTEM_WHEEL_LEARNING_MODE);
  SystemModule_WheelDataFromRegest_Key(KB_CALL_INOUT,CONTROLID_SYSTEM_WHEEL_LEARNING_BT_CALL_IN);
  SystemModule_WheelDataFromRegest_Key(KB_CALL_REJECT,CONTROLID_SYSTEM_WHEEL_LEARNING_BT_HAND_UP);
}
void SystemModule_WheelDataFromRegest_Key(char * buf,u32 ContorlID)
{
  char property[PROPERTY_VALUE_MAX];
  char u_Temp[8];
  memset(u_Temp,0,sizeof(char)*8);
  property_get(buf,property,"0");
  sscanf(property,"%s",u_Temp);
  if(property[0]=='0')
  	{
  	   setAnalogData(ContorlID,0);
  	}
  else if(property[0]=='1')
  	{
  	   setAnalogData(ContorlID,(short)2);
  	}

}
 void saveParameter(void)
 {
	 writeParam_aboutCvbsOrUsb();

     char property[PROPERTY_VALUE_MAX];
     sprintf(property,"%d", localParam.u8BootOnIsAutoPlay);
     property_set(FLY_SET_BOOTON_ISAUTOPLAY,property);
     LOGD("saveParameter----localParam.u8BootOnIsAutoPlay:%d",localParam.u8BootOnIsAutoPlay);
 
	 sprintf(property,"%d", pLocalParam->nNavigationBootingRunMod);
     property_set(FLY_SET_NAVIGATION_BOOTRUNMOD,property);
     LOGD("saveParameter----pLocalParam->nNavigationBootingRunMod:0x%x",pLocalParam->nNavigationBootingRunMod);

	 sprintf(property,"%d", pLocalParam->b_Sys_LightDetect);
     property_set(FLY_SET_LIGHTDETECT,property);

	 sprintf(property,"%d", pLocalParam->m_cCurClearKey);
     property_set(FLY_SET_CURCLEARKEY,property);
	 LOGD("saveParameter----pLocalParam->m_cCurClearKey:0x%x",pLocalParam->m_cCurClearKey);
	 sprintf(property,"%d", pLocalParam->b_Sys_DayNight);
	 property_set(FLY_SET_DAYNIGHT,property);

	 sprintf(property,"%d", pLocalParam->u8_Sys_PanelLight);
	 property_set(FLY_SET_PANELLIGHT,property);

	sprintf(property,"%d", pLocalParam->u8_Sys_PanelLight_bef);
	 property_set(FLY_SET_PANELLIGHT_BEFORE,property);
	 
	 LOGD("saveParameter********pLocalParam->u8_Sys_PanelLight:0x%x",pLocalParam->u8_Sys_PanelLight);
	 sprintf(property,"%d", pLocalParam->u8_Sys_StartupVol);
	 property_set(FLY_SET_FIRSTSTARTUPVOL,property);

	 sprintf(property,"%d", pLocalParam->u8_Sys_StartupVol_bef);
	 property_set(FLY_SET_FIRSTSTARTUPVOL_BEF,property);

	 
	 LOGD("pLocalParam->u8_Sys_StartupVol----%d",pLocalParam->u8_Sys_StartupVol);
	// sprintf(property,"%d", pLocalParam->u8_Sys_CurLcdLight);
	// property_set(FLY_SET_LCDLIGHT,property);
	// LOGD("pLocalParam->u8_Sys_CurLcdLight----%d",pLocalParam->u8_Sys_CurLcdLight);
	 sprintf(property,"%d", pLocalParam->u8_Sys_StandbyStatus);
	 property_set(FLY_SET_STANDBYSTATUS,property);

	 sprintf(property,"%d", pLocalParam->b_Sys_AmplifierStatus);
	 property_set(FLY_SET_AMPLIFIERSTATUS,property);

	 sprintf(property,"%d", pLocalParam->b_Sys_AutoRunGPS);
	 property_set(FLY_SET_AUTORUNGPS,property);

	 sprintf(property,"%d", pLocalParam->b_Sys_Auto_AutoSound);
	 property_set(FLY_SET_AUTO_AUTOSOUND,property);

	 sprintf(property,"%d", pLocalParam->b_Sys_GPSVoicePrompt);
	 property_set(FLY_SET_GPSVOICEPROMPT,property);

	 sprintf(property,"%d", pLocalParam->b_Sys_BackCarDetectEnable);
	 property_set(FLY_SET_BACKCARDETECTENABLE,property);

	 sprintf(property,"%d", pLocalParam->b_Sys_BackCarStatus);
	 property_set(FLY_SET_BACKCARSTATUS,property);

	 sprintf(property,"%d", pLocalParam->b_Sys_BackCarVideo);
	 property_set(FLY_SET_BACKCARVIDEO,property);

	 sprintf(property,"%d", pLocalParam->u8_Sys_AuxVideo);
	 property_set(FLY_SET_AUXVIDEO,property);

	 sprintf(property,"%d", pLocalParam->b_Sys_Ipod);
	 property_set(FLY_SET_IPODORAUX,property);

	 sprintf(property,"%d", pLocalParam->b_Sys_TVOrXM);
	 property_set(FLY_SET_TVORXM,property);

	 sprintf(property,"%d", pLocalParam->b_Sys_SpecialSteeringWheel);
	 property_set(FLY_SET_SPECIALSTEERINGWHEEL,property);

	 sprintf(property,"%d", pLocalParam->u8_Sys_UserSteeringWheel);
	 property_set(FLY_SET_USERSTEERINGWHEEL,property);
	 LOGD("saveparam--->%x",pLocalParam->u8_Sys_UserSteeringWheel);
	 sprintf(property,"%d", pLocalParam->b_Sys_WaitStudy);
	 property_set(FLY_SET_WAITSTUDY,property);

	 sprintf(property,"%d", pLocalParam->u8_Sys_RadioCountryCode);
	 property_set(FLY_SET_RADIOCOUNTRYCODE,property);

	 sprintf(property,"%d", pLocalParam->u8_Sys_DVDRegionCode);
	 property_set(FLY_SET_DVDREGIONCODE,property);

	 //sprintf(property,"%d", pLocalParam->u8_Sys_WhetherTVExist);
	 //property_set(FLY_SET_WHETHERTVEXIST,property);

	 sprintf(property,"%d", pLocalParam->u8_Sys_WhetherTPMSExist);
	 property_set(FLY_SET_WHETHERTPMSEXIST,property);


	 sprintf(property,"%d", pLocalParam->b_Sys_HourPerDay_24);
	 property_set(FLY_SET_HOURPERDAY_24,property);

	 sprintf(property,"%d", pLocalParam->m_eExternalDevice);
	 property_set(FLY_SET_DVRORTV,property);

	 sprintf(property,"%d", pLocalParam->uDvrTvTpmsVisible);
	 property_set(FLY_DVR_TV_TPMS_VISIBLE,property);

	 sprintf(property,"%d", pLocalParam->cNavigationVisible);
	 property_set(FLY_NAVIGATION_VISIBLE,property);

	 sprintf(property,"%d", pLocalParam->cSystemUpdateMode);
	 property_set(FLY_SET_UPDATE_MODE,property);

	 sprintf(property,"%d", pLocalParam->b_Sys_VoicePrompt);
	 property_set(FLY_SET_VOICEPROMPT,property);

	 sprintf(property,"%d", pLocalParam->NaviNub);
	 property_set(FLY_SET_NAVINUB,property);

	 sprintf(property,"%d", pLocalParam->bShowReviseCarModePage);
	 property_set(FLY_SET_BSHOWREVISECARMODEPAGE,property);

	 
	 sprintf(property,"%s", pLocalParam->cRealCarMode);
	 property_set(FLY_SET_CREALCARMODE,property);

	//zhq DNV
	sprintf(property,"%d", pLocalParam->m_bSupportDNV);
	property_set(FLY_SET_DNVSUPPORT,property);
	LOGD("[%s]  pLocalParam->m_bSupportDNV= %d",  __FUNCTION__,pLocalParam->m_bSupportDNV);

	 // system setting page
	sprintf(property,"%d", pLocalParam->eCurFanMode);
	property_set(FLY_SET_SYSTEM_FAN,property);
	LOGD("set: pLocalParam->eCurFanMode %d",pLocalParam->eCurFanMode);

	sprintf(property,"%d", pLocalParam->eVoltageProtectionMode);
	property_set(FLY_SET_SYSTEM_VOLTAGE_PROTECTION_MODE,property);
	LOGD("set: pLocalParam->eVoltageProtectionMode %d",pLocalParam->eVoltageProtectionMode);
	//zhq add checktype 
	sprintf(property,"%d", pLocalParam->eSetupBackcarTriggerType);
	property_set(FLY_SET_SYSTEM_BACKCAR_TRIGGER_TYPE,property);
	LOGD("set: pLocalParam->eSetupBackcarTriggerType %d",pLocalParam->eSetupBackcarTriggerType);

	
	sprintf(property,"%d", pLocalParam->cBrightness_Dim);
	property_set(FLY_BRIGHTNESS_DIM,property);
	
	sprintf(property,"%d", pLocalParam->cBrightness_Moderate);
	property_set(FLY_BRIGHTNESS_MODERATE,property);
	
	sprintf(property,"%d",pLocalParam->cBrightness_Bright);
	property_set(FLY_BRIGHTNESS_BRIGHT,property);

	//sprintf(property,"%d",pLocalParam->cBrightness_RangeValue);
	//property_set(FLY_BRIGHTNESS_RANGEVALUE,property);

	sprintf(property,"%d",pLocalParam->cDvdRegion);
	property_set(FLY_FLYUI_DVD_REGION,property);

	sprintf(property,"%d",pLocalParam->cRadioCountry);
	property_set(FLY_FLYUI_RADIO_COUNTRY,property);

	sprintf(property,"%d",pLocalParam->cCarTypeVisible);
	property_set(FLY_FLYUI_CARTYPE_VISIBLE,property);

	sprintf(property,"%d",pLocalParam->cCarMatchShow);
	property_set(FLY_FLYUI_CARMATCH_SHOW,property);

	sprintf(property,"%d",pLocalParam->cCarAlarmVisible);
	property_set(FLY_FLYUI_CARALARM_VISIBLE,property);

	sprintf(property,"%d",pLocalParam->cBreakCarEnable);
	property_set(FLY_SET_BREAKCAR_ENABLE,property);

    sprintf(property,"%d",pLocalParam->eBackVideoRefLineIsDisplay);
    property_set(FLY_SET_BACK_REFLINEDISPLAY,property);

    sprintf(property,"%d",pLocalParam->eBackVideoTraceLineIsDisplay);
    property_set(FLY_SET_BACK_TRACE_LINEDISPLAY,property);

    //åèœŠæš¡åŒ
	sprintf(property,"%d",pLocalParam->m_eBackCarMode);
	property_set(FLY_SET_BACK_CAR_MODE,property);
	LOGD("[%s] pLocalParam->m_eBackCarMode = [%d]", __FUNCTION__, pLocalParam->m_eBackCarMode);

    sprintf(property,"%d",pLocalParam->uBackCarVideoSwitch_Status);
	property_set(FLY_SET_BACKCAR_VIDEOSWITCH,property);
	LOGD("[%s] pLocalParam->uBackCarVideoSwitch_Status = [%d]", __FUNCTION__, pLocalParam->uBackCarVideoSwitch_Status);

	sprintf(property,"%d",pLocalParam->uLogoSetNub);
	property_set(FLY_SET_LOGO_STYLE_NUB,property);
	LOGD("pLocalParam->uLogoSetNub %d",pLocalParam->uLogoSetNub);

	sprintf(property,"%d",pLocalParam->b_Sys_NaviMixLowSwitch);
	property_set(FLY_SET_NAVI_MIX_LOW,property);

	sprintf(property,"%d",pLocalParam->emAmbientLedSwitch);
	property_set(FLY_SET_LED_SWTICH,property);
			
	sprintf(property,"%d",pLocalParam->emAmbientLedCommission);
	property_set(FLY_SET_LED_COMMISSION,property);

	sprintf(property,"%d",pLocalParam->eDvrProtocolMode);
	property_set(FLY_DVR_SET_PROTOCOL_MODE,property);
	
	sprintf(property,"%d",pLocalParam->curDayAndNightMode);
	property_set(FLY_SET_DAY_OR_NIGHT_MODE,property);

	u8 buff[21];
	memset(buff,0,21);
	for(int i = 0;i < SAVE_RGB_NUM ;i++)
	{
		*(buff+(i*7+0)) = pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveRValue[0];
		*(buff+(i*7+1)) = pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveRValue[1];
		*(buff+(i*7+2)) = pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveGValue[0];
		*(buff+(i*7+3)) = pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveGValue[1];
		*(buff+(i*7+4))= pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveBValue[0];
		*(buff+(i*7+5))= pLocalParam->eSaveRGB_Dimming_value[i].uAmbientLedSaveBValue[1];
		*(buff+(i*7+6)) = pLocalParam->eSaveRGB_Dimming_value[i].uShowCurSaveColorValue;
	}
	bufferToString((char *)buff, SAVE_RGB_NUM * 7, property);
	char str[42] = {0};
	memcpy(str,property,42);
	LOGD("buffToString:  %s",str);
	property_set(FLY_DVR_SAVE_LED_RGB_DIMMING, property);

	sprintf(property,"%hhd",pLocalParam->uDesktopNivaInforSwitch);
	property_set(FLY_DESKTOP_NAVI_SWITCH,property);

	sprintf(property,"%hhd",pLocalParam->uScreenBrightAutoSwtich);
	property_set(FLY_SCREEN_BRIGHT_AUTO_SWITCH,property);
}
void SystemModule_Timer_WheelData_Clear()
{
   enum emWheelClear emkey=pLocalParam->m_emClearKey;
   switch(emkey)
   	{
   	   case emClear_Mode:
	        pLocalParam->m_cCurClearKey=0x00;
	        break;
	   case emClear_Mute:
	        pLocalParam->m_cCurClearKey=0x03;
	        break;
	   case emClear_Seek_INC:
	        pLocalParam->m_cCurClearKey=0x01;
	        break;
	   case emClear_Seek_DEC:
	        pLocalParam->m_cCurClearKey=0x02;
	        break;
	   case emClear_Vol_INC:
	        pLocalParam->m_cCurClearKey=0x04;
	        break;
	   case emClear_Vol_DEC:
	        pLocalParam->m_cCurClearKey=0x05;
	        break;
	   case emClear_bt_callin:
	   	    pLocalParam->m_cCurClearKey=0x06;
			break;
	   case emClear_bt_handup:
	   	    pLocalParam->m_cCurClearKey=0x07;
			break;
		case emClear_NO:
	        pLocalParam->m_cCurClearKey=0xff;
	        break;
	   default:
	   	break;
   	}
   systemToHal_ClearWheelPanelData(emkey);

}
void SystemModule_Dispatch_SystemReset(void)
{



}


//#define INFOR
#ifdef INFOR
void SystemModule_ReadBarCode()
{
	int exis_code=prepare_BarCode();
	pLocalParam->b_Barcode=exis_code;
	LOGD("pLocalParam->b_Barcode=%d",pLocalParam->b_Barcode);
	if(pLocalParam->b_Barcode)
	{
		//Handle_BarCode(); 20141027-chz
		//SetTimer(5000,1,OSD_TIMER_BARCODE_SYS_DISPLAY);
	}
	else
	{
		// Handle_NOBarCode();
		// SetTimer(5000,1,OSD_TIMER_BARCODE_SYS_DISPLAY);
	}
}
void SystemModule_ReadUUID()
{
	char buf[READ_UUID_LENGTH]={0x00};
	char buffer[]={0x00};
	//--------enable read -------
	LOGD("prepare_to_read_pifo...\n");
	if(prepare_to_read_pifo(READ_INFO_KEY)<0){
		LOGD("prepare_to_read_pifo failed!\n");
		return;
	}

	//---------ProductSerialNumber---------
	//read
	read_ProductSerialNumber(buf,READ_UUID_LENGTH);
	LOGD("ProductSerialNumber:%s\n",buf);

	int i;
	for(i=0;i<READ_UUID_LENGTH;i++)
	{
		if(buf[i]=='\n')
		{
			buffer[i]=0;
			break;
		}
		buffer[i]=buf[i];
	}

    SystemModuleToUI_DisplayingUUID(buffer);

	unprepare_pifo();
}

void deleteSpecialCharacters(char *str,char ch)
{
    char * p=str;
    int i=0;
    while( (*p) != 0 ){ 
        if((*p) != ch){
            str[i++]=*p;
        }  
        p++;   
    }  
    str[i]=0;
}

void Handle_BarCode()
{
   char buff[READ_BARCODE_LENGTH]={0x00};

	LOGD("```Handle_BarCode`````:read_BarCode");
   int len=read_BarCode(buff,READ_BARCODE_LENGTH);

   u8 *pAnsicBuf = (u8*)malloc(READ_BARCODE_LENGTH);

   memset(pAnsicBuf, 0, READ_BARCODE_LENGTH);
   memcpy(pAnsicBuf, buff, len);

   u8 *pUnicodeBuf = (u8*)malloc(READ_BARCODE_LENGTH*2+2);
   memset(pUnicodeBuf, 0, READ_BARCODE_LENGTH*2+2);

   int nUnicodeBufLen = ansi_str_to_unicode16(pAnsicBuf, (unicode16_t*)pUnicodeBuf);

   setSerialData(CONTROLID_COPYRIGHT_BARCODE,pUnicodeBuf,nUnicodeBufLen*2);

   LOGD("---system-----handle_BarCode read lenth=%d, barcode is :%s",len,buff);

   free(pAnsicBuf);
   free(pUnicodeBuf);
}
#endif

void SystemModule_ReadMCU()
{
	memset(pLocalParam->c_mcu,0,sizeof(pLocalParam->c_mcu));
	
	char cMcuF[PROPERTY_VALUE_MAX];
	memset(cMcuF,0,sizeof(cMcuF));
	property_get("fly.version.mcu",cMcuF,"");
	int nMcuF = strlen(cMcuF);
	for(int i =0;i < nMcuF;i++)
	{
		if(i == nMcuF-1 && cMcuF[nMcuF-1] == 10){
		}
		else{
			pLocalParam->c_mcu[i] = cMcuF[i];
		}
	}

	char cMcuTime[PROPERTY_VALUE_MAX];
	memset(cMcuTime,0,sizeof(cMcuTime));
	property_get("fly.version.times",cMcuTime,"");
	
	//memcpy(pLocalParam->c_mcu,cMcuF,strlen(cMcuF)-1);
	strcat(pLocalParam->c_mcu,cMcuTime);

	LOGD("pLocalParam->c_mcu:%s",pLocalParam->c_mcu);
	halToSystem_MCU_Version((u8*)pLocalParam->c_mcu,100);
}


int enc_get_utf8_size(const unsigned char pInput)
{
	unsigned char c = pInput;
	if(c < 0x80) return 1;
	if(c >= 0x80 && c < 0xC0) return -1;
	if(c >= 0xC0 && c < 0xE0) return 2;
	if(c >= 0xE0 && c < 0xF0) return 3;
	if(c >= 0xF0 && c < 0xF8) return 4;
	if(c >= 0xF8 && c < 0xFC) return 5;
	if(c >= 0xFC) return 6;

	return -1;
}

int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic)
{
	// b1 ±íÊŸUTF-8±àÂëµÄpInputÖÐµÄžß×ÖœÚ, b2 ±íÊŸŽÎžß×ÖœÚ, ...
    char b1, b2, b3, b4, b5, b6;

    *Unic = 0x0; // 
    int utfbytes = enc_get_utf8_size(*pInput);
    unsigned char *pOutput = (unsigned char *)Unic;

    switch(utfbytes)
    {
    case 1:
        *pOutput = *pInput;
        break;
    case 2:
        b1 = *pInput;
        b2 = *(pInput + 1);
        if ( (b2 & 0xC0) != 0x80 )
            return 0;
        *pOutput     = (b1 << 6) + (b2 & 0x3F);
        *(pOutput+1) = (b1 >> 2) & 0x07;
        break;
    case 3:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b2 << 6) + (b3 & 0x3F);
        *(pOutput+1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
        break;
    case 4:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b3 << 6) + (b4 & 0x3F);
        *(pOutput+1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
        *(pOutput+2) = ((b1 << 2) & 0x1C)  + ((b2 >> 4) & 0x03);
        break;
    case 5:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b4 << 6) + (b5 & 0x3F);
        *(pOutput+1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
        *(pOutput+2) = (b2 << 2) + ((b3 >> 4) & 0x03);
        *(pOutput+3) = (b1 << 6);
        break;
    case 6:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        b6 = *(pInput + 5);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)
                || ((b6 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b5 << 6) + (b6 & 0x3F);
        *(pOutput+1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
        *(pOutput+2) = (b3 << 2) + ((b4 >> 4) & 0x03);
        *(pOutput+3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
        break;
    default:
        return 0;
        break;
    }//switch(utfbytes)

    return utfbytes;
}


int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize)
{
	int nSrcLen = 0;
	int nDstLen = 0;
	u8 *pUtf8 = pInput;
	u8 *pUnic = pOutput;
	int nOneUtf8Len = 0;

	nOneUtf8Len = enc_get_utf8_size(*pUtf8);

	while(-1 != nOneUtf8Len)
	{
		unsigned long oneUnic = 0;
		enc_utf8_to_unicode_one(pUtf8, &oneUnic);

		nDstLen += 2;
		if (nOutputSize < nDstLen)
		{
			nDstLen -= 2;
			break;
		}
		else
			memcpy(pUnic, &oneUnic, 2);

		nSrcLen += nOneUtf8Len;
		if (nSrcLen >= nInputLen)
		{
			break;
		}

		pUtf8 += nOneUtf8Len;
		pUnic += 2;

		nOneUtf8Len = enc_get_utf8_size(*pUtf8);
	}

	return nDstLen;
}

uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16)
{
	int nSrcLen = strlen((char*)ansi);
	int nUni16Len = nSrcLen*2+2;
	int nRetLen = utf8_2_ucs2(ansi, nSrcLen, (u8*)uni16, nUni16Len);
	
	return (nRetLen/2);
}

int bufferToString(char *buffer, int len, char *str)
	{
		int n;
		int i , j;
		char buf =0x00;
		char buf1 = 0x00;
		if(len <= 0 || len >= (PROPERTY_VALUE_MAX/2)){
			return -1;
		}

		for(i = 0, j=0; i < len; i++,j+=2){
			buf = buffer[i] & 0xF0;
			buf = buf >> 4;
			buf1 = buffer[i] & 0x0F;
			str[j] = __intToChar(buf);
			str[j+1] = __intToChar(buf1);
		}
		str[2*len] = '\0';

		return (2*len+1);
	}

int stringToBuffer(char *str, char *buffer)
{
	int str_len = strlen(str);
	if(str_len <= 0)
		return 0;
	int i , j;
	for(i = 0, j=0; j < str_len; i++, j+=2){
		buffer[i] = __charToInt(str[j])<<4;
		buffer[i] += __charToInt(str[j+1]);
	}

	return (str_len/2);
}

char __intToChar(char value){
	if(value >= 0 && value <= 9){
		return (value+0x30);
	}
	else if(value >= 10 && value <=15){
		return (value + 0x37);
	}
	else{
		return '\0';
		LOGD("*************0*****************");
	}
}

char __charToInt(char ch){
	if(ch >= '0' && ch <= '9'){
		return (ch-0x30);
	}
	else if(ch >= 'A' && ch <= 'F'){
		return (ch-0x37);
	}
	else{
		LOGD("*************0*****************");
		return 0;
	}
}

void readParam_aboutCvbsOrUsb()
{
	char property[PROPERTY_VALUE_MAX];

	static u8 uTem = 2;
	property_get(FLY_SET_CVBS_USB_SWITCH,property,"2");
	sscanf(property,"%hhd", &uTem);

	if(uTem == 2)
	{
		static u8 uTemConfig = 2;
		property_get(FLY_SET_CVBS_USB_SWITCH_CONFIG, property, "2");
		sscanf(property,"%hhd", &uTemConfig);
		if(uTemConfig == 1)
		{
			uTem = 1;
		}
		else
		{
			uTem = 0;
		}
	}

	pLocalParam->uBackCarSetCvbsOrUSB = uTem;
	pLocalParam->uSetCvbsOrUSBTemp = uTem;
}

void writeParam_aboutCvbsOrUsb()
{
	char property[PROPERTY_VALUE_MAX];
	sprintf(property,"%hhd", pLocalParam->uBackCarSetCvbsOrUSB);
	property_set(FLY_SET_CVBS_USB_SWITCH,property);
}

void writeParam_aboutCarTypeSelection()
{
	char property[PROPERTY_VALUE_MAX];
	sprintf(property,"%hhd", pLocalParam->uCurCartype);
	property_set(FLY_SET_CUR_CAR_TYPE,property);
}
