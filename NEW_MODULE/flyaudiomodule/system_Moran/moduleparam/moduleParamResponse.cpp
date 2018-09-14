#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <linux/kernel.h>
#include <errno.h>
#include <sys/ioctl.h>
//#include <cutils/properties.h>

#include "types_def.h"
#include "commonFunc.h"
#include "param.h"
#include "global.h"
#include "controlID.h"
#include "stringID.h"
#include "moduleParamResponse.h"
#include "pageID.h"
#include "appRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "appResponseFunction.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"
#include "timer_interface.h"
#include "halResponseFunction.h"
#include "timer_interface.h"
#include "otherModuleResponseFunction.h"

#include <android/log.h>
//#include <cutils/properties.h>
#include <ctype.h>
#include "tinyxml.h"

extern "C"{
#include "flyopen.h"
#include "unicodestring.h"
};
#include "tinyxml.h"


static u16 tempPageId;

#define FLY_DNV_PARAM_IS_DNV_PAGE						0x01

void handAppPage(u16 pageID)
{
	LOGD("---handAppPage  0x%x--",pageID);
	switch(pageID)
	{
		case PAGEACTION_ENTER_FLYAPP:
		{
			LOGD("[%s] getCurPage():%x",__FUNCTION__,getCurPage());
			if(getCurPage() == 0xff04)
			{
				return;
			}
			if(!IsFlyPartyPage(getCurPage()))
			{
				//delete_pageFromTable();
				//u16 uCurPageID = getCurPage();
				//u16 TempPageId = CurBtA2dpIsSupport_CheckBackKeyJumpPage(uCurPageID);

				u16 TempPageId = getCurFlyPage();	
				TempPageId = CurBtA2dpIsSupport_CheckBackKeyJumpPage(TempPageId);
				LOGD("[%s]----TempPageId:%x",__FUNCTION__,TempPageId);
				if(judgmentReturnHomePage(getCurPage()))
					TempPageId = PAGE_MENU;
				switch(TempPageId)
				{
					case PAGE_BACK_VIDEO:
					case PAGE_BACK_NOVIDEO:
					case PAGE_BACK_RADAR:
					case PAGE_BACK_FULL_VIDEO:
					case PAGE_BACK_FULL_VIDEO_CONTROL:
					case PAGE_DVD_VIDEO_SET:
					case PAGE_DVD_VIDEO_CONTROL:
					case PAGE_DVD_OPEN:
					case PAGE_AUX_VIDEO_CONTROL:
					case PAGE_AUX_VIDEO_SET:
					case PAGE_TV_VIDEO_CONTROL:
					case PAGE_TV_VIDEO_SET:
					case PAGE_BLACK:
					case PAGE_STANDBY:
					case 0x00:
					case PAGE_FINISH_FLYAPP:
		            case PAGE_FINISH_GPSAPP:
		            case PAGE_FINISH_MEDIAAPP:
					case PAGE_PARALLEL_PARK_PAGE:
					case PAGE_PERPENDICULAR_PARK_PAGE:
					case PAGE_PARK_OUT_ASSIST_PAGE:
					case PAGE_MULTI_CONTOURED_SEATS_ADJUST:
					case PAGE_MULTI_CONTOURED_SEATS_MASSAGE:
						switch_Page(PAGE_MENU);
					break;
					default:
						switch_Page(TempPageId);
					break;
				}
			
			}
		}
			break;
		case PAGEACTION_BACK_KEY:
			anyModuleToSysModule_Switch_PrePage();
			break;
		case PAGEACTION_ENTER_THIRDAPP:
			if(getCurPage() != PAGE_THIRD_PAGE)
			{
				insert_pageToTable(PAGE_THIRD_PAGE);
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			break;
		case PAGEACTION_ENTER_MEDIAAPP:
			if(getCurPage() != PAGE_MEDIA){
				insert_pageToTable(PAGE_MEDIA);
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			break;
		case PAGEACTION_ENTER_GPSAPP:
			if(getCurPage() != PAGE_GPS_PAGE){
				insert_pageToTable(PAGE_GPS_PAGE);
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			break;
		case PAGEACTION_ENTER_3GPHONEAPP:
			break;
		case PAGEACTION_ENTER_DDBOX_CARLIFE_APP:
			if(getCurPage() != PAGE_THIRD_PAGE)
			{
				insert_pageToTable(PAGE_THIRD_PAGE);
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			systemToModule_NotifyAudiovideo_SetThirdChannel();
			break;
		case PAGE_SPEECH_APP_MEDIA:
			if(getCurPage() != PAGE_SPEECH_APP_MEDIA){
				insert_pageToTable(PAGE_SPEECH_APP_MEDIA);
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			break;
		case PAGE_BLUETOOTH_MAIN:
			if(getCurPage() != PAGE_BLUETOOTH_MAIN){
				insert_pageToTable(PAGE_BLUETOOTH_MAIN);
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			break;
		case PAGE_BLUETOOTH_A2DP:
			if(getCurPage() != PAGE_BLUETOOTH_A2DP){
				insert_pageToTable(PAGE_BLUETOOTH_A2DP);
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			break;
		case PAGE_BLUETOOTH_NO_A2DP:
			if(getCurPage() != PAGE_BLUETOOTH_NO_A2DP){
				insert_pageToTable(PAGE_BLUETOOTH_NO_A2DP);
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			break;
		case PAGE_DRIVING_RECORD_VIDEO:
			if(getCurPage() != PAGE_DRIVING_RECORD_VIDEO){
				insert_pageToTable(PAGE_DRIVING_RECORD_VIDEO);
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			break;
		case PAGE_DRIVING_RECORD_NO_SIGN:
			if(getCurPage() != PAGE_DRIVING_RECORD_NO_SIGN){
				insert_pageToTable(PAGE_DRIVING_RECORD_NO_SIGN);
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			break;
		case PAGEACTION_SPECIAL_PREPAGE_DVR_LIST:
			switch_Page(PAGE_DRIVING_RECORD_VIDEO);
			break;
		case PAGEACTION_ENTER_NO_NAVIGATION_APP:
		case PAGEACTION_ENTER_NO_SPEECH_APP:
			if(getCurPage() == (pageID -1))
			{
				delete_pageFromTable();
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			break;
		case PAGE_DRIVING_FRONT_CAMERA_APP:
			if(getCurPage() != PAGE_DRIVING_FRONT_CAMERA_APP){
				insert_pageToTable(PAGE_DRIVING_FRONT_CAMERA_APP);
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
			}
			break;
		default:
			LOGD("continue,page is throw!!!!!!!!!!!!!!!!!");
			break;
	}
	
	displayPageTable();
	
}

void *readAppPage(void *argv)
{
	short int *pPageID = (short int*)&tempPageId;
	while(1){
		c_read_dev(pLocalParam->fd,pPageID);
		LOGD("tempPageId:%x",tempPageId);
		handAppPage(tempPageId);
	}
	return NULL;
}

void openDev()
{
  pthread_t thread_id;
  int fd = -1;
  LOGW("Enter open /dev/flysemdriver ");
  while(pLocalParam->fd  < 0){
	  pLocalParam->fd = open_device("/dev/flysemdriver", O_RDWR);
	  LOGW("/dev/flysemdriver open %s, err:%s", pLocalParam->fd  < 0?"failed":"true", strerror(errno));
	  usleep(100);
   }
  int re_pthread=pthread_create(&thread_id, NULL, &readAppPage, NULL);
  LOGD("re_pthread:%x",re_pthread);
}

void moduleParameterInit(void){
	//SystemModule_SetDefaultParam();
	
}

void moduleParameterDeInit(void){

}

void moduleParameterReInit(void)
{
   LOGD("&&&&&&&&&&&&&&&&&&&& system moduleParameterReInit");
}

//2012-03-14
void SystemModule_Process_AccOff()
{
	LOGD("[%s]-getCurPage():%x-",__FUNCTION__,getCurPage());
	if(getCurPage()== PAGE_THIRD_PAGE)
		pLocalParam->b_NeedLaunchThirdApp = true;
	else
		pLocalParam->b_NeedLaunchThirdApp = false;
	LOGD("settimer pLocalParam->b_NeedLaunchThirdApp:%x",pLocalParam->b_NeedLaunchThirdApp);
	char property[PROPERTY_VALUE_MAX];
	sprintf(property,"%d", pLocalParam->b_NeedLaunchThirdApp);
    property_set(FLY_SET_NEEDLAUNCH,property);
    
	saveParameter();
	DeleteTimer(AUX_TIME_DISPLAY);
}

void SystemMoudule_Process_AccOn()
{
	LOGD("SystemMoudule_Process_AccOn");
	LOGD("SystemMoudule_Process_AccOn CurPage:0x%x",getCurPage());
	LOGD("SystemMoudule_Process_AccOn PrePage:0x%x",getPrePage());
	systemToApp_getTimeFormat();
	if(pLocalParam->eBackVideoRefLineIsDisplay == eLineState_NoShow)
	{
		appToSys_Setup_BackCarRefLineDisplay_NO_MouseUp();
	}
	else
	{
		appToSys_Setup_BackCarRefLineDisplay_IS_MouseUp();
	}

	if(pLocalParam->eBackVideoTraceLineIsDisplay == eLineState_NoShow)
	{
	    appToSys_Setup_BackCarTraceLineDisplay_NO_MouseUp();
	}
	else
	{
	    appToSys_Setup_BackCarTraceLineDisplay_IS_MouseUp();
	}

	//systemToHal_setExternalDevice();
	systemToHal_setTriggerType();
	Set_Dvr_ProtocolMode((u8)pLocalParam->eDvrProtocolMode);
	getDefault_Boot_Animation_Prop();
	systemToApp_SetPowerVol_BarMaxValue();
	analyseSelectionCarTypeMessage(pLocalParam->uCurCartype);
	//SetTimer(2000,1,ACCON_STOP_DYNAMICLOGO);
   	/*
   	LOGD("pLocalParam->nNavigationBootingRunMod:%d",pLocalParam->nNavigationBootingRunMod);
   	if(pLocalParam->nNavigationBootingRunMod == 1)
   	{
   	   	switch_Page(PAGE_GPS_PAGE);
    	usleep(2000*1000);
   	}
   	else if(pLocalParam->nNavigationBootingRunMod == 2)
   	{
   	}
   	else if(pLocalParam->nNavigationBootingRunMod == 0)
   	{    
   	    char property[PROPERTY_VALUE_MAX];
        pLocalParam->b_Gps_Runing = true;
        property_get(FLY_GPS_RUNING,property,"0");
        sscanf(property,"%d", &pLocalParam->b_Gps_Runing);
   	    LOGD("pLocalParam->b_Gps_Runing:%d",pLocalParam->b_Gps_Runing);
       	if(pLocalParam->b_Gps_Runing){
       		switch_Page(PAGE_GPS_PAGE);
        	usleep(2000*1000);
        }
    }
    */

   	//�������������״̬Ϊ1   ����ҳ������HOMEҳ��
	if(1 == pLocalParam->u8_Sys_StandbyStatus)
			switch_Page(PAGE_STANDBY);
	//edited by chengzihong 20140813
    //else
    //	switch_Page(PAGE_MENU);
    //  property_set("ctl.stop","bootanim");
	

	/*//25
	char property[24];
	pLocalParam->b_Gps_Runing = true;
	property_get(FLY_GPS_RUNING,property,"0");
	sscanf(property,"%d", &pLocalParam->b_Gps_Runing);
	LOGD("pLocalParam->b_Gps_Runing:%d",pLocalParam->b_Gps_Runing);
	if(pLocalParam->b_Gps_Runing){
		switch_Page(PAGE_GPS_PAGE);
		usleep(2000*1000);
	}

	property_get(FLY_SET_NEEDLAUNCH,property,"0");
	sscanf(property,"%d", &pLocalParam->b_NeedLaunchThirdApp);
	LOGD("---SystemMoudule_Process_AccOn--%x-------",pLocalParam->b_NeedLaunchThirdApp);
	if(pLocalParam->b_NeedLaunchThirdApp){
		jumpPage(0xFF11);
		usleep(3000*1000);
	}
	else
	{
		switch_Page(PAGE_MENU);
	}
	
	if(getCurPage() == PAGE_BACK_RADAR || getPrePage() == PAGE_BACK_RADAR)
	{
		pLocalParam->b_back=true;
	   	anyModuleToSysModule_Switch_PrePage();
	   	pLocalParam->b_back=false;
	}

	property_set("ctl.stop","bootanim");//2013-05-28�رն�̬LOGO
	SetTimer(2000,1,ACCON_STOP_DYNAMICLOGO);//2013-05-09
	*/
	
	SetTimer(1000,0,AUX_TIME_DISPLAY);
	DisplaySysToUI_aboutBackCarProtocolCVBSorUSB(!pLocalParam->uBackCarSetCvbsOrUSB);
	System_notifyApp_cvbsOrUsbSwitch(pLocalParam->uBackCarSetCvbsOrUSB);
	DisPlayingReverseCameraType(pLocalParam->uBackCarSetCvbsOrUSB);

	systemToHal_InquireCurBrakeStatue();
	setSystemToHal_DayOrNight(pLocalParam->curDayAndNightMode);
	systemToApp_Sound_Channel_Volume_Adjust(0x00,0x00);
	System_notifyApp_DesktopNavigationMapInformationsSyncSwitchState(pLocalParam->uDesktopNivaInforSwitch);
}

void SystemModule_NavigationBootingRunMod()
{
  	LOGD("[%s] pLocalParam->nNavigationBootingRunMod:%d",__FUNCTION__,pLocalParam->nNavigationBootingRunMod);
   	if(pLocalParam->nNavigationBootingRunMod == 1)
   	{
   	   	switch_Page(PAGE_GPS_PAGE);
    	if(strncmp(pLocalParam->str_WhichProject,"G8II-KOREA",10) == NULL)
		{
		}
		else
		{
    		//usleep(2000*1000);
		}
   	}
   	else if(pLocalParam->nNavigationBootingRunMod == 2)
   	{
   	}
   	else if(pLocalParam->nNavigationBootingRunMod == 0)
   	{    
   	    char property[PROPERTY_VALUE_MAX];
        pLocalParam->b_Gps_Runing = true;
        property_get(FLY_GPS_RUNING,property,"0");
        sscanf(property,"%hhd", &pLocalParam->b_Gps_Runing);
   	    LOGD("pLocalParam->b_Gps_Runing:%d",pLocalParam->b_Gps_Runing);
       	if(pLocalParam->b_Gps_Runing){
       		switch_Page(PAGE_GPS_PAGE);

			if(strncmp(pLocalParam->str_WhichProject,"G8II-KOREA",10) == NULL)
			{
			}
			else
			{
		    	//usleep(2000*1000);
			}
        }
    }

}

void NavigationBootingRunMod(u8 p)
{
	int nT = 0x00;
	if(pLocalParam->naviList[pLocalParam->NaviNub].NaviNameStrID == 131501)
	{
		nT = 0x01;
	}
	LOGD("[%s] (p:%d Navi:%d nT:%d)",__FUNCTION__,p,pLocalParam->NaviNub,nT);

	char property[PROPERTY_VALUE_MAX];
   	pLocalParam->b_Gps_Runing = true;
   	property_get(FLY_GPS_RUNING,property,"0");
   	sscanf(property,"%hhd", &pLocalParam->b_Gps_Runing);
	LOGD("[%s] pLocalParam->b_Gps_Runing:%d",__FUNCTION__,pLocalParam->b_Gps_Runing);
	LOGD("[%s] pLocalParam->nNavigationBootingRunMod:%d",__FUNCTION__,pLocalParam->nNavigationBootingRunMod);
   	if( (pLocalParam->nNavigationBootingRunMod == 1) || ((pLocalParam->nNavigationBootingRunMod == 0)&&(pLocalParam->b_Gps_Runing)) )
   	{
   	   	switch_Page(PAGE_GPS_PAGE);

		if(strncmp(pLocalParam->str_WhichProject,"G8II-KOREA",10) == NULL)
		{
		}
		else
		{
    		//usleep(2000*1000);
    		
    		if(p == 0x00)//ACC
    		{
    			if(nT == 0x01)//AMAP
    			{
    				//usleep(6000*1000);
    			}
				else
				{
					//usleep(6000*1000);
				}
    		}
			else if(p == 0x01)//INIT
			{
    			//usleep(4000*1000);
			}
		}
   	}
}

void SystemModule_Process_Reset()
{
    LOGD("SystemModule_Process_Reset");
	saveParameter();
}

void SystemModule_Process_ResetDefault()
{
    LOGD("SystemModule_Process_ResetDefault");
	SystemModule_SetDefaultParam();
	//2012-06-09 ��ֹ��λup��Ϣ
	pLocalParam->b_Timer=true;
	saveParameter();
}

void SystemModule_SetDefaultParam()
{
	LOGD("SystemModule_SetDefaultParam");
	//system_local_param_t
	memset(pLocalParam->str_WhichProject,0,sizeof(pLocalParam->str_WhichProject));
	pLocalParam->uBackCarVideoSwitch_Status = 1;
	localParam.u8BootOnIsAutoPlay = 1;
	localParam.b_Sys_LightDetect = true; //Detect Light Or Not
	localParam.b_Sys_DayNight = false;//Day Or Night State

	localParam.u8_Sys_PanelLight = 0xff; //Panel Key Light
	localParam.u8_Sys_PanelLight_bef = 0x14;
	//Startup Vol
	localParam.u8_Sys_StartupVol = 0;
	localParam.u8_Sys_StartupVol_bef = 0;

	//LCD
	localParam.u8_Sys_CurLcdLight = 3; //LCD Light
	pLocalParam->bSysStatusBarSet = false;
	//Standby Status
	localParam.u8_Sys_StandbyStatus = 0;
	localParam.u8_Sys_StandbyStatus1= 0;
	localParam.b_Sys_AmplifierStatus = false; //FactoryAmplifier State

	//Brake Car
	pLocalParam->cBreakCarEnable = 0;
	localParam.b_Sys_BrakeCarStatus = false; //Brake Car Status

	//GPS Run
	localParam.b_Sys_AutoRunGPS = false; //Auto Run
	localParam.b_Sys_GPSVoicePrompt = true;
	pLocalParam->b_Sys_Auto_AutoSound = true;

	//zhq DNV
	localParam.m_bSupportDNV = true;
	
	//Back Car
	localParam.b_Sys_BackCarDetectEnable = true;
	localParam.b_Sys_BackCarStatus = false;
	localParam.b_Sys_BackCarVideo = false;
	int radarDataLen=sizeof(pLocalParam->m_cRadarData);
	memset(pLocalParam->m_cRadarData,0xff,radarDataLen);
	int radarDataUILen=sizeof(pLocalParam->m_cRadarDataUI);
	memset(pLocalParam->m_cRadarDataUI,0xff,radarDataUILen);
	pLocalParam->m_radarCar=0;
	//Aux Video Status
	//localParam.u8_Sys_AuxVideo = 0;

	//Set Ipos Or Aux
	localParam.b_Sys_Ipod = false; //Ipod Or Aux
	localParam.b_Sys_TVOrXM = true; //TV or XM

	//SteeringWheel
	localParam.b_Sys_SpecialSteeringWheel = false;
	localParam.u8_Sys_UserSteeringWheel = 0;
	localParam.b_Sys_WaitStudy = false; //Wait Study

    int len=sizeof(pLocalParam->m_cWheelKey);
	memset(pLocalParam->m_cWheelKey,0,len);
	pLocalParam->m_cCurClearKey=0xFF;
	pLocalParam->m_emClearKey=emClear_NO;

    pLocalParam->c_ModuleTable[0]=1;
    pLocalParam->c_ModuleTable[1]=2;
    pLocalParam->c_ModuleTable[2]=3;
    pLocalParam->c_ModuleTable[3]=4;
    pLocalParam->c_ModuleTable[4]=5;
    pLocalParam->c_ModuleTable[5]=6;
    pLocalParam->c_ModuleTable[6]=7;

	//Radio Coountry Code
	localParam.u8_Sys_RadioCountryCode = 0;
	//DVD Region Code
	localParam.u8_Sys_DVDRegionCode = 0;

	//TV Exist Or Not
	localParam.u8_Sys_WhetherTVExist = 0;
	//TPMS Exist Or Not
	localParam.u8_Sys_WhetherTPMSExist = 0;
	localParam.u8_Sys_AUXVideo = 0; //Whether have AUX Video

	//Set Time
	localParam.b_Sys_HourPerDay_24 = true; //24

	memset(localParam.u16_Sys_PrePageArray,0,sizeof(localParam.u16_Sys_PrePageArray));
	localParam.u16_Sys_PrePageArray[0][0] = PAGE_BACK_VIDEO;
	localParam.u16_Sys_PrePageArray[0][1] = PAGE_MENU;
	localParam.u16_Sys_PrePageArray[1][0] = PAGE_BACK_NOVIDEO;
	localParam.u16_Sys_PrePageArray[1][1] = PAGE_MENU;

	memset(localParam.u16_Sys_PageTable, PAGE_MENU, sizeof(localParam.u16_Sys_PageTable));
	localParam.n_Sys_PageTable_Pos = -1;
	localParam.n_Sys_PageTableCount = 0;

	localParam.b_Sys_ThirdPageMark = false;
	localParam.b_Sys_HomePageMark = false;
	localParam.b_Sys_ThirdPageBackMark = false;
	localParam.b_Sys_GpsPageMark = false;
	//2011-03-13
	localParam.b_Sys_ThridPageBackNoHomePageMark = false;

	//localParam.u16_Sys_PrePage = 0; //Pre Page
	pLocalParam->u16_Sys_PrePage = 0;
	localParam.u16_Sys_SwitchTempPage = 0;//Temp Page

    localParam.brightness=3;
	localParam.b_Timer=false;
	localParam.b_Barcode=false;
	localParam.b_Visible=false;
	localParam.f_Visible = false;
	localParam.b_enable_ipol=true;
	localParam.u8_Sys_tempPage=0;
	localParam.b_enable_tv=false;
	localParam.fd=-1;
	localParam.b_back=false;

	pLocalParam->b_3G_DialIn = false;
	pLocalParam->b_Gps_Runing = true;
	pLocalParam->b_NeedLaunchThirdApp = false;
	pLocalParam->b_isAUX = 1;
	pLocalParam->m_eExternalDevice = EXTERNAL_DEVICE_UNKNOW;

	pLocalParam->uDvrTvTpmsVisible=1;
	pLocalParam->cNavigationVisible=1;
	pLocalParam->cSystemUpdateMode=0;
	pLocalParam->b_Sys_VoicePrompt = true;
	//localParam.b_SetTimer_AccOn = false;
	pLocalParam->NaviNub=0;
	pLocalParam->DebugSwitch=false;
	pLocalParam->osdDebugSwith=false;
	memset(pLocalParam->cChoseeCarMode,0,128);
	pLocalParam->cChoseeCarModeLen=0;
	memset(pLocalParam->cRealCarMode,0,128);
	pLocalParam->cRealCarModeLen=0;
	pLocalParam->bShowReviseCarModePage=true;

	// system setting page
	pLocalParam->eCurFanMode = eFanModeLowPower;
	pLocalParam->eVoltageProtectionMode = eVoltageProtectionModeHigh;//2014-5-15
	pLocalParam->eSetupBackcarTriggerType = eSetupBackcarTriggerUnknow; //zhq add
	pLocalParam->nSpecificSkin_PrePage = 0;
	pLocalParam->bRealCarRecv=0;
	pLocalParam->bChooseCarRecv=0;
	pLocalParam->initRecv=0;

	pLocalParam->cBrightness_Dim=1;
	pLocalParam->cBrightness_Moderate=34;
	pLocalParam->cBrightness_Bright=67;	
	pLocalParam->cBrightness_RangeValue=0xff;
	
	pLocalParam->cDvdRegion=6;
	pLocalParam->cRadioCountry=0;
	pLocalParam->cCarMatchShow=1;
	pLocalParam->cCarTypeVisible=1;
	pLocalParam->cCarAlarmVisible=1;
	pLocalParam->bShowSystemDialog=true;
	pLocalParam->nNaviCount=0;
	pLocalParam->nNavigationBootingRunMod = 255;

	pLocalParam->eBackVideoRefLineIsDisplay = eLineState_Unkown;
	pLocalParam->eBackVideoTraceLineIsDisplay = eLineState_Unkown;

	memset(pLocalParam->uc_MEPG,0,100);
	memset(pLocalParam->uc_UUID,0,100);
	pLocalParam->ucBattery_Value = 0;

	pLocalParam->uSystemExterDeviceGroup[0]=1;
	pLocalParam->uSystemExterDeviceGroup[1]=2;
	pLocalParam->uSystemExterDeviceGroup[2]=3;
	pLocalParam->uSystemExterDeviceGroup[3]=4;
	pLocalParam->uSystemExterDeviceGroup[4]=5;
	pLocalParam->uSystemExterDeviceGroup[5]=6;
	pLocalParam->uSystemExterDeviceGroup[6]=7;

	pLocalParam->uSystemBackcarTtiggerGroup[0]=1;
	pLocalParam->uSystemBackcarTtiggerGroup[1]=2;
	pLocalParam->uSystemBackcarTtiggerGroup[2]=3;
	pLocalParam->uSystemBackcarTtiggerGroup[3]=4;
	pLocalParam->uSystemBackcarTtiggerGroup[4]=5;

	pLocalParam->m_eBackCarMode = BACKCAR_MODE_NORMAL;
	pLocalParam->bHomePageOSDCanDrop = true;

	pLocalParam->uStandByStatus = 0x00;

	pLocalParam->uLogoSetNub = 0;
	pLocalParam->nLogoStyleCount = 0;
	pLocalParam->b_Sys_NaviMixLowSwitch = true;
	pLocalParam->eDvrProtocolMode = e_Unkown_ProTocol;

	pLocalParam->uAmbientLedInitState = 0;
	pLocalParam->emAmbientLedSwitch = AMBIENT_LED_ON;
	pLocalParam->uAmbientLedDimmValue = 150;
	memset(pLocalParam->uAmbientLedRValue,0,2);
	memset(pLocalParam->uAmbientLedGValue,0,2);
	memset(pLocalParam->uAmbientLedBValue,0,2);
	pLocalParam->emAmbientLedCommission = LED_COMMISSION_WARM_RED;

	pLocalParam->uSystemTimeFormat = 0;
	pLocalParam->uBackCarSetCvbsOrUSB = 0;
	pLocalParam->uShowCurColorValue = 0;
	memset(pLocalParam->eSaveRGB_Dimming_value,0,(SAVE_RGB_NUM * sizeof(SAVE_RGB_DIMMING_VALUE) ));
	pLocalParam->showGRB_Dimming_tag = true;
	pLocalParam->curDayAndNightMode = eDayAndNight_UNKOWN;
	pLocalParam->curBackCarLineType = 255;
	pLocalParam->curDailingOption = 0;
	pLocalParam->uCameraDelayTag = 0x00;
	pLocalParam->uDesktopNivaInforSwitch = 2;
	pLocalParam->systemSkinType = 0;
	pLocalParam->nPageCount = 0;
	pLocalParam->nScreenSwitchStatus = 0xff;
	pLocalParam->uScreenBrightAutoSwtich = 0;
	pLocalParam->fordAlmBrightnessMaxValue = 0xFFFF;

	memset(pLocalParam->st_MCS,0,(SEAT_COUNT * sizeof(SAVE_MCS_ADJUST_MASSAGE_VALUE) ));
	//pLocalParam->selectSeatSide = 0xFF;
	pLocalParam->selectSeatSide = 0x01;
	pLocalParam->uMCS_Available = 0x00;
	pLocalParam->uCurCartype = 0x01;
	pLocalParam->uCurSelectionCarType = 0x01;
}

void SystemModule_InitByConfig()
{
	LOGD("(Jooph)SystemModule_InitByConfig+++++++++++++++\n");
	
	pthread_mutex_init(&pLocalParam->mutex, 0);
	pthread_mutex_init(&pLocalParam->mutex_notifyPageChange, 0);
	setSystemToHal_DayOrNight(pLocalParam->curDayAndNightMode);

	systemToApp_getTimeFormat();
	systemToApp_BackVideo_CarRadarIsDisplay(0);

	UiDisplay_System_BackCarVideoSwitch(pLocalParam->uBackCarVideoSwitch_Status);
	appToSys_Setup_BootOn_IsAutoPlay(localParam.u8BootOnIsAutoPlay);

	ToUI_SwitchOne_about_SetupIsRunningNavigationStr(pLocalParam->nNavigationBootingRunMod);
	showBoot_Run_Nav_status(pLocalParam->nNavigationBootingRunMod);
	//��ȡ�����б�XML�ͳ�ʼ������
	ReadAllNaviNameAndPath();
	ReadAllNaviNameAndFlyapdataConfigPath();
	appToSys_Setup_Default_NaviGation(-1);
	showDefault_Boot_Nav(pLocalParam->NaviNub);
	appToSys_Setup_Default_Navigation_ShowHide();

	ReadLogoStyleFile();
	appToSys_Setup_DynamicLogoStyle(-1);
	
	// fan
	SystemModule_SetMachineInit_FanState();
	//cpu
	SystemModule_SetMachineInit_CPUState();
	// voltage
	SystemModule_initVoltageProtection();

    initBackModeUI();
	//zhq add initTrigger
	SystemModule_Init_TriggerType_SetVisible();
	InitTriggerTypeTable();
	systemToHal_setTriggerType();
	
    	setToHalBackCarMode((u8)pLocalParam->m_eBackCarMode);
	ReadAllReturnToHomeForPageList();
	//readParameter();
	if(pLocalParam->b_Sys_AutoRunGPS) //Auto run
	{
		setDigitalData(CONTROLID_SETUP_AUTO_INFOGPS_ON,true);
		systemToModule_NotifySomeModule_GPSAutoRunStatus(0x01);//To Key and Center GPS Run Status
		systemToGPSRun_NotifyGPSRun_AutoRunMsg(0x01);
	}
	else
	{
		setDigitalData(CONTROLID_SETUP_AUTO_INFOGPS_ON,false);
		systemToModule_NotifySomeModule_GPSAutoRunStatus(0x00);//To Key and Center GPS Run Status
		systemToGPSRun_NotifyGPSRun_AutoRunMsg(0x00);
	}

	
	if(pLocalParam->b_Sys_Auto_AutoSound)
	{
		setDigitalData(CONTROLID_SETUP_AUDIO_AUTO_SOUND_ON_OFF,true);
		System_notifyApp_AUTO_SOUND_ON(0x01);
	}
	else
	{
		setDigitalData(CONTROLID_SETUP_AUDIO_AUTO_SOUND_ON_OFF,false);
		System_notifyApp_AUTO_SOUND_ON(0x00);
	}
	
	if(pLocalParam->b_Sys_GPSVoicePrompt) //GPS voice Prompt
	{
		setDigitalData(CONTROLID_SETUP_GPS_VOICE_PROMPT_ON,true);
		systemToModule_NotifySoundModule_GPSVoicePrompt(0x01);
	}
	else
	{
		setDigitalData(CONTROLID_SETUP_GPS_VOICE_PROMPT_ON,false);
		systemToModule_NotifySoundModule_GPSVoicePrompt(0x00);
	}
	
	if(pLocalParam->b_Sys_Ipod)
	{
		appToSys_Setup_IpodSet_ON_MouseUp();
	}
	else
	{
		appToSys_Setup_TVSet_ON_MouseUp();
	}

	//VoicePrompt   ON or  OFF
	if(pLocalParam->b_Sys_VoicePrompt)
	{
		appToSys_Setup_CarinfoAudioCueON();
	}
	else
	{
		appToSys_Setup_CarinfoAudioCueOFF();
	}
	
	//--------------------------------------------
	//Brake car Detect
	LOGD("[%s] pLocalParam->cBreakCarEnable:%d",__FUNCTION__,pLocalParam->cBreakCarEnable);
	if(pLocalParam->cBreakCarEnable)
	{
		appToSys_Setup_BrakeCarDetect_ON_MouseUp();
	}
	else
	{
		appToSys_Setup_BrakeCarDetect_OFF_MouseUp();
	}
	
	//Amplifer
	if(pLocalParam->b_Sys_AmplifierStatus)
	{
		appToSys_Setup_Amplifier_ON_MouseUp();
	}
	else
	{
		appToSys_Setup_Amplifier_OFF_MouseUp();
	}
	
	//Pannel LED light
	if(pLocalParam->u8_Sys_PanelLight<=3 || pLocalParam->u8_Sys_PanelLight>20)
	{
		pLocalParam->u8_Sys_PanelLight = 0xFF;
	}
	
    appToUiDialogDisplaying_aboutSysReset(false);
    appToUiDialogDisplaying_aboutSysUpdate(false);
	appToUiDialogDisplaying_aboutRestoreFactory(false);

	DisplayingOrHidingSysCarModules(false);
	
	systemToHal_KeyLedBrightness(pLocalParam->u8_Sys_PanelLight);
	//Light Detect
	systemToHal_LightDetected(pLocalParam->b_Sys_LightDetect);
	//Back Car Detect
	LOGD("pLocalParam->b_Sys_BackCarDetectEnable:%d",pLocalParam->b_Sys_BackCarDetectEnable);
	systemToHal_BackCarDetected(pLocalParam->b_Sys_BackCarDetectEnable);

	/*��ӦHALҪ�󣬳�ʼ������,�ɵײ㷴������(�����������̿ز��˵ļ�������)*/
	//systemToHal_WheelPanelSpecificFuncSwitch(pLocalParam->b_Sys_SpecialSteeringWheel);

	//Startup Volume
	SystemModuleToUI_aboutStartupVolume();
	//Panel LED Light
	SystemModuleToUI_aboutPanelLight();

	halToSystem_ApplyUserDefinedWheelData(pLocalParam->u8_Sys_UserSteeringWheel);
	
	systemToHal_Init(0x01);

	//****************LCD*****************//
	LOGD("SystemModule_InitByConfig:pLocalParam->u8_Sys_CurLcdLight:0x%x",pLocalParam->u8_Sys_CurLcdLight);
	//if(pLocalParam->u8_Sys_CurLcdLight==0)pLocalParam->u8_Sys_CurLcdLight=3;
	//setScreenBrightnessCtrl(pLocalParam->u8_Sys_CurLcdLight);
	//systemToHal_SetLCDBrightness(pLocalParam->u8_Sys_CurLcdLight);
	
	systemToHal_Global_Init(0x01);

	SystemModule_WheelDataFromRegest();
	//2012-06-18
	//SystemModule_ReadBarCode();
	SetTimer(1000,0,AUX_TIME_DISPLAY);
	//2012-07-24
	//SystemModule_ReadUUID();
	//2014-10-17����
	//SystemModule_ReadDeviceNode_aboutUUID();

	SystemModule_ReadMCU();
	
	InitModuleTable();
	InitDeviceTable();

	systemToHal_setExternalDevice();

	SendDeviceStateToOSDDebug();
	SendBackcarInfoAndDiaInStateToOSDDebug();

//	char property[PROPERTY_VALUE_MAX];
//	property_get(" m",property,"0");
//	sscanf(property,"%s", pLocalParam->cChoseeCarMode);
//	pLocalParam->cChoseeCarModeLen=strlen((char*)pLocalParam->cChoseeCarMode);
//	pLocalParam->cRealCarModeLen=strlen((char*)pLocalParam->cRealCarMode);
//	LOGD("pLocalParam->cRealCarModeLen:%d",pLocalParam->cRealCarModeLen);

	SystemModule_ReadParam_aboutMPEG();
	SystemModuleToUI_setVisible();

	if(pLocalParam->eBackVideoRefLineIsDisplay == eLineState_NoShow)
	{
		appToSys_Setup_BackCarRefLineDisplay_NO_MouseUp();
	}
	else
	{
		appToSys_Setup_BackCarRefLineDisplay_IS_MouseUp();
	}

	if(pLocalParam->eBackVideoTraceLineIsDisplay == eLineState_NoShow)
	{
	    appToSys_Setup_BackCarTraceLineDisplay_NO_MouseUp(); 
	}
	else
	{
	    appToSys_Setup_BackCarTraceLineDisplay_IS_MouseUp();
	}
	
	pLocalParam->bShowSystemDialog=true;

	systemToApp_AllowReadParam(true);
	systemToHal_InquireCurBrakeStatue();

	systemToHal_SetNaviMixLow(pLocalParam->b_Sys_NaviMixLowSwitch);
	Set_Dvr_ProtocolMode((u8)pLocalParam->eDvrProtocolMode);
	
	DisplaySysToUI_aboutBackCarProtocolCVBSorUSB(!pLocalParam->uBackCarSetCvbsOrUSB);
	DisPlayingReverseCameraType(pLocalParam->uBackCarSetCvbsOrUSB);
	System_notifyApp_cvbsOrUsbSwitch(pLocalParam->uBackCarSetCvbsOrUSB);
	DisplayingOrHidingSysUI_aboutReversingCameraEquipment(false);

	systemToHalAboutAmbientLed_Init(0x01);
	DisplayUI_AmbientLed_SwitchButton((u8)pLocalParam->emAmbientLedSwitch);
	DisplayUI_AmbientLed_CommissionButton(pLocalParam->emAmbientLedCommission);
	initCustomizeColorButen();
	//systemToHal_SetScreenBrightnessValue(pLocalParam->cBrightness_RangeValue);
	 SystemToApp_ShowRadioCountry(pLocalParam->u8_Sys_RadioCountryCode);
	 getDefault_Boot_Animation_Prop();
	 systemToApp_SetPowerVol_BarMaxValue();
	systemToApp_Sound_Channel_Volume_Adjust(0x00,0x00);

	showThirdDailingOption(pLocalParam->curDailingOption);
	System_notifyApp_DesktopNavigationMapInformationsSyncSwitchState(pLocalParam->uDesktopNivaInforSwitch);
	DisplayDesktopNavigationMapInformationsSyncSwitchButtonUI(!pLocalParam->uDesktopNivaInforSwitch);
	//systemToHal_SetScreenBrightnessSpecificValue(pLocalParam->cBrightness_RangeValue);
	analyseSelectionCarTypeMessage(pLocalParam->uCurCartype);
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){

	LOGD("[%s]  paramId= [0x%x]",  __FUNCTION__,paramId);

	switch(paramId){
		case CUR_PAGE: //Cur Page
			if(param)
			{
				*(u16*)param = getCurPage();
				*paramLen = 2;
			}
			break;
		case PREV_PAGE: //Pre Page
			if(param)
			{
				*(u16*)param = getPrePage();
				*paramLen = 2;
			}
			break;
		case LCD_STATE: //LCD Status
		{
			if(pLocalParam->nScreenSwitchStatus == 0x00)
				*(u8*)param = 0x00;
			else
				*(u8*)param = pLocalParam->u8_Sys_CurLcdLight;
			*paramLen = 1;
		}
			break;
		case SLEEP_STATE: //Standby Status
			*(u8*)param = pLocalParam->u8_Sys_StandbyStatus;
			*paramLen = 1;
			break;
		case SYS_TV_EXIST_STATE_DEVICE: //Whether TV Exist
			*(u8*)param = pLocalParam->u8_Sys_WhetherTVExist;
			*paramLen = 1;
			break;
		case SYSTEM_AUX_VIDEO_STATE: //Whether AUX Video
			*(u8*)param = pLocalParam->u8_Sys_AUXVideo;
			*paramLen = 1;
			break;
		case DIALIN_3G:
			*param = pLocalParam->b_3G_DialIn;
			*paramLen = sizeof(bool);
			break;
		case SYSTEM_IS_AUX://�Ƿ���AUX
			*param = pLocalParam->b_isAUX;
			*paramLen = sizeof(bool);
			break;
		case SYSTEM_TRIGGER_TYPE:
			*param = pLocalParam->eSetupBackcarTriggerType;
			*paramLen = 1;
			break;
		case SYSTEM_IS_DVRORTV:
			*param = pLocalParam->m_eExternalDevice;
			*paramLen = 1;
			break;
		case SYSTEM_SET_OPTION_EXTCAR_VOICE_PROMPT_STATUS:
			*param = pLocalParam->b_Sys_VoicePrompt;
			*paramLen = sizeof(bool);
			break;
		case SYSTEM_SET_BACKCAR_DETECTEENABLE_STATUS:
		    *param = pLocalParam->uBackCarVideoSwitch_Status;
		    *paramLen = sizeof(bool);
		    break;
		case SYSTEM_SET_STARTUPVOL:
			*param = pLocalParam->u8_Sys_StartupVol;
			*paramLen = 1;
			 break;
		case SYSTEM_SET_DNV_DETECTEENABLE_STATUS:    // zhq   dnv
		    *param = pLocalParam->m_bSupportDNV;
		    *paramLen = sizeof(bool);
			LOGD("SYSTEM_SET_DNV_DETECTEENABLE_STATUS=[0x%x] ",  SYSTEM_SET_DNV_DETECTEENABLE_STATUS);
			break;
		case SYSTEM_SET_BackVideoRefLineEnable:
	        *(u8*)param = (u8)pLocalParam->eBackVideoRefLineIsDisplay;
	        *paramLen = 1;
	        break;
	    case MCU_INFO:
	        memcpy(param,(u8*)pLocalParam->c_mcu,strlen(pLocalParam->c_mcu));
	        *paramLen = strlen(pLocalParam->c_mcu);
	    break;
        case MEPG_INFO:
            memcpy(param,pLocalParam->uc_MEPG,strlen((char *)pLocalParam->uc_MEPG));
            *paramLen = strlen((char *)pLocalParam->uc_MEPG);
        break;
        case FID_INFO: //UUID
            memcpy(param,pLocalParam->uc_UUID,strlen((char *)pLocalParam->uc_UUID));
            *paramLen = strlen((char *)pLocalParam->uc_UUID);
        break;
        case BATTERY_VALUE:
            *param = pLocalParam->ucBattery_Value;
            *paramLen = sizeof(u8);
        break;
        case SYSTEM_PARAM_ID_BACKMODE:
            *(u8*)param = (u8)pLocalParam->m_eBackCarMode;
            *paramLen = 1;
            break;
		case SYSTEM_HOMEPAGE_OSD_VISIBLE:
            *(u8*)param = (u8)pLocalParam->bHomePageOSDCanDrop;
            *paramLen = 1;
            break;
		case SYSTEM_BRAKECAR_STATUS:
			*(u8*)param = (u8)pLocalParam->b_Sys_BrakeCarStatus;
			*paramLen = 1;
			break;
		case SYSTEM_PRADO_RADAR_KEY_SWITCH_STATUS:
			*(u8*)param = (u8)pLocalParam->bPrado_RadarSwitchKeyStatus;
			*paramLen = 1;
			break;
		case SYSTEM_PRADO_RADAR_UI_SWITCH_STATUS:
			*(u8*)param = (u8)pLocalParam->bPrado_RadarSwitchUiStatus;
			*paramLen = 1;
			break;
		case SYSTEM_STANDBY_STATUS:
			*(u8*)param = (u8)pLocalParam->uStandByStatus;
			*paramLen = 1;
			break;
		case SYSTEM_DVR_PROTOCOL_MODE:
			*(u8*)param = (u8)pLocalParam->eDvrProtocolMode;
			*paramLen = 1;
		break;
		case SYSTEM_CVBS_OR_USB_SWITCH:
			*(u8*)param = (u8)pLocalParam->uBackCarSetCvbsOrUSB;
			*paramLen = 1;
		break;
		default:break;
	}
}

int module_extendInterface(char *buffer, int len)
{
   char extenCmd = buffer[0];
   char extenParam = buffer[1];
   LOGD("*******************system module_extendInterface:%x,%x",extenCmd,extenParam);
   switch(extenCmd)
   {
	   case 0x1D:
		   {
			   if(extenParam == 0x00)//Standby on
			   {
				   halToSystem_StandbyStatus(0x00,0x00);
			   }
			   else if(extenParam == 0x01)//Standby off
			   {
				   halToSystem_StandbyStatus(0x01,0x00);
			   }
		   }
		   break;
		case 0x2C: //ACC Off Or Reset Or Default
			{
				if(extenParam == 0x00) //Acc Off
				{		
					SystemModule_Process_AccOff();
				}
				else if(extenParam == 0x01)
				{
					SystemModule_Process_Reset();
				}
				else if(extenParam == 0x02)
				{
					SystemModule_Process_ResetDefault();
				}
			}
			break;
		case 0x2D: //ACC On
			{
				SystemMoudule_Process_AccOn();
			}
			break;
		case 0xFD:
			{
				openDev();
				SystemModule_InitByConfig();
	    		//initTimerCenter(&TimerHandlerCenter);
			}
			break;
		case 0xFE:
			{
				//pLocalParam->initRecv=1;
				//if(pLocalParam->bRealCarRecv == 1 && pLocalParam->bChooseCarRecv == 1)
					//SystemModule_CheckCarMode();
			}
			break;
		default:break;
   	}
   	
   return 0;
}



void ReadAllNaviNameAndPath()
{
	TiXmlElement* rootElement1;
	TiXmlElement* rootElement2;
	TiXmlDocument doc;


    if(!doc.LoadFile(NAVILIST_FILE_PATH)) 
    	return ;
    //pLocalParam->nNaviCount=NAVICOUNT;
    rootElement1 = doc.RootElement();
    rootElement2=rootElement1->FirstChildElement("Navi");

	 char NaviDisMark = 0;
    char NaviNameStr[128]={0};
    char NaviNameStrID[128]={0};
    char NaviPackName[128]={0};
    char NaviClassName[128]={0};
    int count =0;
    while(rootElement2 != NULL)
    {
    	NaviDisMark = 0;
       memset(NaviNameStr,0,128);
    	memset(NaviNameStrID,0,128);
    	memset(NaviPackName,0,128);
    	memset(NaviClassName,0,128);

        LOGD("33333333333:%s %s",rootElement2->Attribute("MapNameStr"),rootElement2->Attribute("Name"));
		
        if(rootElement2->Attribute("DisplayMark") == NULL)
        {
        }
        else
        {
			char cTempMark[5]={0};
     		strcpy(cTempMark, rootElement2->Attribute("DisplayMark"));
			NaviDisMark = atoi(cTempMark);
        }

        if(rootElement2->Attribute("MapNameStr") == NULL)
        {
            memset(NaviNameStr,0,128);
        }
        else
        {
            strcpy(NaviNameStr, rootElement2->Attribute("MapNameStr"));
        }

        if(rootElement2->Attribute("Name") == NULL)
        {
            memset(NaviNameStrID,0,128);
        }
        else
        {
            strcpy(NaviNameStrID, rootElement2->Attribute("Name"));
        }

        if(rootElement2->Attribute("PackName") == NULL)
        {
            memset(NaviPackName,0,128);
        }
        else
        {
    	    strcpy(NaviPackName, rootElement2->Attribute("PackName"));
    	}

    	if(rootElement2->Attribute("ClassName") == NULL)
    	{
    	    memset(NaviClassName,0,128);
    	}
    	else
    	{
    	    strcpy(NaviClassName, rootElement2->Attribute("ClassName"));
    	}

		pLocalParam->naviList[count].NaviMark = NaviDisMark;
    	memcpy(pLocalParam->naviList[count].NaviNameStr,NaviNameStr,sizeof(NaviNameStr));
    	pLocalParam->naviList[count].NaviNameStrID=atoi(NaviNameStrID);
    	memcpy(pLocalParam->naviList[count].NaviPackName,NaviPackName,sizeof(NaviPackName));
    	memcpy(pLocalParam->naviList[count].NaviClassName,NaviClassName,sizeof(NaviClassName));

    		
    	LOGD("nub:%d NaviDisMark:%d,NaviNameStrId:%s,NaviPackName:%s",count,NaviDisMark,NaviNameStrID,NaviPackName);
    	rootElement2=rootElement2->NextSiblingElement();
    	pLocalParam->nNaviCount=count+1;
    	count++;	
    	LOGD("Navi count is pLocalParam->nNaviCount=%d",pLocalParam->nNaviCount);
    }


    LOGD("+++++++");
	for(int i=0;i < pLocalParam->nNaviCount;i++)
	{
	    LOGD("NaviNameStr:%s strID:%x NaviPackName:%s NaviClassName:%s",pLocalParam->naviList[i].NaviNameStr,pLocalParam->naviList[i].NaviNameStrID,pLocalParam->naviList[i].NaviPackName,pLocalParam->naviList[i].NaviClassName);
	}
	LOGD("+++++++");
}

void ReadAllNaviNameAndFlyapdataConfigPath()
{

    TiXmlElement* rootElement1;
    TiXmlElement* rootElement2;
    TiXmlDocument doc;

    if(!doc.LoadFile(NAVILIST_FILE__FLYAPDATA_PATH)) 
        return;

    //pLocalParam->nNaviCount=NAVICOUNT;
    rootElement1 = doc.RootElement();
    rootElement2=rootElement1->FirstChildElement("Navi");

	 char NaviDisMark = 0;
    char NaviNameStr[128]={0};
    char NaviNameStrID[128]={0};
    char NaviPackName[128]={0};
    char NaviClassName[128]={0};
    int count =pLocalParam->nNaviCount;
    while(rootElement2 != NULL)
    {
    	NaviDisMark = 0;
       memset(NaviNameStr,0,128);
    	memset(NaviNameStrID,0,128);
    	memset(NaviPackName,0,128);
    	memset(NaviClassName,0,128);

        if(rootElement2->Attribute("DisplayMark") == NULL)
        {
        }
        else
        {
			char cTempMark[5]={0};
     		strcpy(cTempMark, rootElement2->Attribute("DisplayMark"));
			NaviDisMark = atoi(cTempMark);
        }

        if(rootElement2->Attribute("MapNameStr") == NULL)
        {
            memset(NaviNameStr,0,128);
        }
        else
        {
            strcpy(NaviNameStr, rootElement2->Attribute("MapNameStr"));
        }

        if(rootElement2->Attribute("Name") == NULL)
        {
            memset(NaviNameStrID,0,128);
        }
        else
        {
            strcpy(NaviNameStrID, rootElement2->Attribute("Name"));
        }

        if(rootElement2->Attribute("PackName") == NULL)
        {
            memset(NaviPackName,0,128);
        }
        else
        {
    	    strcpy(NaviPackName, rootElement2->Attribute("PackName"));
    	}

    	if(rootElement2->Attribute("ClassName") == NULL)
    	{
    	    memset(NaviClassName,0,128);
    	}
    	else
    	{
    	    strcpy(NaviClassName, rootElement2->Attribute("ClassName"));
    	}

		pLocalParam->naviList[count].NaviMark = NaviDisMark;
    	memcpy(pLocalParam->naviList[count].NaviNameStr,NaviNameStr,sizeof(NaviNameStr));
    	pLocalParam->naviList[count].NaviNameStrID=atoi(NaviNameStrID);
    	memcpy(pLocalParam->naviList[count].NaviPackName,NaviPackName,sizeof(NaviPackName));
    	memcpy(pLocalParam->naviList[count].NaviClassName,NaviClassName,sizeof(NaviClassName));
    		
    	LOGD("ReadAllNaviNameAndFlyapdataConfigPath nub:%d NaviDisMark:%d,NaviNameStrId:%s,NaviPackName:%s",count,NaviDisMark,NaviNameStrID,NaviPackName);
    	rootElement2=rootElement2->NextSiblingElement();
    	pLocalParam->nNaviCount=count+1;
    	count++;
    	LOGD("ReadAllNaviNameAndFlyapdataConfigPath Navi count is pLocalParam->nNaviCount=%d",pLocalParam->nNaviCount);
    }
}



void SystemModule_CheckCarMode(void)

{
	//��ʵ����Ϊ�ղ���У����ʾ����
	if(pLocalParam->cCarMatchShow==0)return;  //no show
	pLocalParam->initRecv=0;
	pLocalParam->bChooseCarRecv=0;
	pLocalParam->bRealCarRecv=0;
	u8 cNullCarMode[128]={0};
	memcpy(cNullCarMode,"00000",5);
	LOGD("pLocalParam->cRealCarMode:%s",pLocalParam->cRealCarMode);
	if(memcmp(pLocalParam->cRealCarMode,cNullCarMode,5) == 0)
		return;

	
	unicode16_t unicBuffer[256]={0};
	int uniclen = 0;
	if (pLocalParam->cRealCarModeLen != 0)
		uniclen =	ansi_str_to_unicode16(pLocalParam->cRealCarMode,unicBuffer);
	
	//LOGD("[DYB] uniclen = %d ", uniclen);
	//LOGD("[DYB] pLocalParam->bShowReviseCarModePage:%d",pLocalParam->bShowReviseCarModePage);	
	LOGD("[DYB] (%s %d %s %d)",pLocalParam->cRealCarMode,pLocalParam->cRealCarModeLen,pLocalParam->cChoseeCarMode, pLocalParam->cChoseeCarModeLen);
	//if( pLocalParam->bShowReviseCarModePage && 
	// (uniclen *  2 != pLocalParam->cChoseeCarModeLen || memcmp(unicBuffer,pLocalParam->cChoseeCarMode,uniclen*2) != 0)
	//	)
	if(pLocalParam->cRealCarModeLen != pLocalParam->cChoseeCarModeLen || memcmp(pLocalParam->cRealCarMode,pLocalParam->cChoseeCarMode,pLocalParam->cRealCarModeLen) != 0)
	{
		LOGD("[DYB]: car style auto fit  enter.");
		systemToModule_NotifySystem_JumpPage(PAGE_MATCHING_MODELS);
		setSerialData(CONTROLID_MATCHING_MODELS_PAGE_CURRENT_MODELS_TEXT,(u8*)unicBuffer,uniclen*2);
		//setSerialData(CONTROLID_MATCHING_MODELS_PAGE_MODIFY_MODELS_TEXT,pLocalParam->cChoseeCarMode,pLocalParam->cChoseeCarModeLen);
		halToSystem_ChooseCarMode(CONTROLID_MATCHING_MODELS_PAGE_MODIFY_MODELS_TEXT,pLocalParam->cChoseeCarMode,pLocalParam->cChoseeCarModeLen);
	}
	else
	{
		LOGD("[DYB]: car style auto fit  do not enter.");
	}
}

void SystemModuleParam_CheckCarMode(void)

{
	u8 cNullCarMode[128]={0};
	memcpy(cNullCarMode,"00000",5);
	LOGD("[%s] (Real:%s %d choose:%s %d)",__FUNCTION__,pLocalParam->cRealCarMode,pLocalParam->cRealCarModeLen,pLocalParam->cChoseeCarMode, pLocalParam->cChoseeCarModeLen);
	if(memcmp(pLocalParam->cRealCarMode,cNullCarMode,5) == 0)
		return;
	
	if(pLocalParam->cRealCarModeLen != pLocalParam->cChoseeCarModeLen || memcmp(pLocalParam->cRealCarMode,pLocalParam->cChoseeCarMode,pLocalParam->cRealCarModeLen) != 0)
	{
		LOGD("car style auto fit  enter.");

		u16 uTemCurPageId = getCurPage();
		if(uTemCurPageId != PAGE_MATCHING_MODELS && uTemCurPageId != PAGE_BACK_NOVIDEO && uTemCurPageId != PAGE_BACK_VIDEO){
			systemToModule_NotifySystem_JumpPage(PAGE_MATCHING_MODELS);
		}
		halToSystem_ChooseCarMode(CONTROLID_MATCHING_MODELS_PAGE_CURRENT_MODELS_TEXT,pLocalParam->cRealCarMode,pLocalParam->cRealCarModeLen);
		halToSystem_ChooseCarMode(CONTROLID_MATCHING_MODELS_PAGE_MODIFY_MODELS_TEXT,pLocalParam->cChoseeCarMode,pLocalParam->cChoseeCarModeLen);
	}
	else
	{
		LOGD("car style auto fit  do not enter.");
	}
}

void halToSystem_ChooseCarMode(int ctrID,u8 *pBuf, u8 len)
{
	u8 *pAnsicBuf = (u8*)malloc(len+1);
	memset(pAnsicBuf, 0, len+1);
	memcpy(pAnsicBuf, pBuf, len);
	u8 *pUnicodeBuf = (u8*)malloc((len)*2+2);
	memset(pUnicodeBuf, 0, (len)*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(pAnsicBuf, (unicode16_t*)pUnicodeBuf);
	setSerialData(ctrID,pUnicodeBuf,nUnicodeBufLen*2);
	free(pAnsicBuf);
	free(pUnicodeBuf);

}


void SystemModule_initVoltageProtection()
{
	if (pLocalParam->eVoltageProtectionMode == eVoltageProtectionModeMid)
	{
		setStringText(CONTROLID_SETUP_VOLTAGE_PROTECTION_TEXT, STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_MID);
		systemToHal_SetVoltageProtection(eVoltageProtectionModeMid);
	}
	else if(pLocalParam->eVoltageProtectionMode == eVoltageProtectionModeLow)
	{
		setStringText(CONTROLID_SETUP_VOLTAGE_PROTECTION_TEXT, STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_LOW);
		systemToHal_SetVoltageProtection(eVoltageProtectionModeLow);
	}
	else
	{
		setStringText(CONTROLID_SETUP_VOLTAGE_PROTECTION_TEXT, STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_HIGH);
		systemToHal_SetVoltageProtection(eVoltageProtectionModeHigh);
	}
}

void SystemModule_SetMachineInit_FanState()
{
    SystemModuleToUI_aboutFanMode(pLocalParam->eCurFanMode);
    LOGD("SystemModule_setMachineInit_FanState pLocalParam->eCurFanMode=%d",pLocalParam->eCurFanMode);
	if(pLocalParam->eCurFanMode == eFanModeShutDown)
	{
		systemToHal_SetFanMode(0x00);
	}
	else if (pLocalParam->eCurFanMode == eFanModeShutOpen)
	{
		systemToHal_SetFanMode(0x01);
	}
    else if(pLocalParam->eCurFanMode == eFanModeHighPerformance)
    {
        systemToHal_SetFanMode(0x02);
	}
	else if (pLocalParam->eCurFanMode == eFanModeFitAuto)
	{
		//systemToHal_SetFanMode(0x03);
		systemToHal_SetFanMode(0x04);
	}
	else if (pLocalParam->eCurFanMode == eFanModeLowPower)
	{
		systemToHal_SetFanMode(0x04);
	}
	
}

void SystemModule_SetMachineInit_CPUState()
{
    LOGD("SystemModule_SetMachineInit_CPUState pLocalParam->eCurFanMode=%d",pLocalParam->eCurFanMode);
	if(pLocalParam->eCurFanMode == eFanModeShutDown)
	{
	}
	else if (pLocalParam->eCurFanMode == eFanModeShutOpen)
	{
	}
    else if(pLocalParam->eCurFanMode == eFanModeHighPerformance)
    {
        systemToHal_SetCPU_PerformanceMode(0x02);
	}
	else if (pLocalParam->eCurFanMode == eFanModeFitAuto)
	{
		systemToHal_SetCPU_PerformanceMode(0x01);
	}
	else if (pLocalParam->eCurFanMode == eFanModeLowPower)
	{
		systemToHal_SetCPU_PerformanceMode(0x00);
	}

}

void initBackModeUI(void)
{
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


void SystemModule_ReadParam_aboutMPEG()
{
    char property[PROPERTY_VALUE_MAX];
	u8 dvdVirsion[128] = {0};
	property_get(FLY_SET_DVD_VERSION,property,"");
	sscanf(property,"%s", dvdVirsion);
	int dvdVirsionLen=strlen((char*)dvdVirsion);
	memcpy(pLocalParam->uc_MEPG,dvdVirsion,sizeof(dvdVirsion));
	LOGD("dvdVirsion:%s,dvdVirsionLen:%d",dvdVirsion,dvdVirsionLen);
	if(dvdVirsionLen != 0)
	{
		u8 pUnicodedvdVirsion[256] = {0};
		int UnicodedvdVirsionLen = ansi_str_to_unicode16(dvdVirsion, (unicode16_t*)pUnicodedvdVirsion);
		setSerialData(CONTROLID_COPYRIGHT_MPEG,pUnicodedvdVirsion,UnicodedvdVirsionLen*2);
	}

}

void SystemModuleToUI_DisplayingUUID(char *buf)
{
    u8 *pAnsicBuf = (u8*)malloc(READ_UUID_LENGTH);
    memset(pAnsicBuf, 0, READ_UUID_LENGTH);
    memcpy(pAnsicBuf, buf, sizeof(buf));
    memcpy(pLocalParam->uc_UUID, buf, sizeof(buf));
    u8 *pUnicodeBuf = (u8*)malloc(READ_UUID_LENGTH*2+2);
    memset(pUnicodeBuf, 0, READ_UUID_LENGTH*2+2);
    int nUnicodeBufLen = ansi_str_to_unicode16(pAnsicBuf, (unicode16_t*)pUnicodeBuf);
    
    setSerialData(CONTROLID_COPYRIGHT_UUID,pUnicodeBuf,nUnicodeBufLen*2);
    
    free(pAnsicBuf);
    free(pUnicodeBuf);
}




void SystemModule_ReadDeviceNode_aboutUUID()
{
	int handle,bytes;
    
	if(access("/data/lidbg/uuid", F_OK) == -1)
	{
		LOGI("/data/lidbg/uuid file not exists");
		return;
	}

	if(access("/data/lidbg/uuid", W_OK) == -1)
	{
		LOGI("You can't write the /data/lidbg/uuid file!");
		return;
	}
	
	if(((handle = open("/data/lidbg/uuid", O_RDWR))) == -1)
	{
		LOGD("Error open the /data/lidbg/uuid file.");
		close(handle);
		return;
	}

	char *buf = (char*)malloc(READ_UUID_LENGTH);
	if((bytes = read(handle,buf,strlen(buf))) == -1)
	{
		LOGD("Error write to the file.");
	}
	
	LOGD("Read %d bytes to the file(/data/lidbg/uuid).",bytes);
	SystemModuleToUI_DisplayingUUID(buf);
	
	free(buf);
	buf=NULL;
	
	close(handle);

}


void SystemModuleToUI_aboutStartupVolume()
{
	u8 ansiBuf[16];
	memset(ansiBuf, 0, 16);
	u8 *pStrLastValume = (u8*)"Last Volume";
	if(255 == pLocalParam->u8_Sys_StartupVol)
	{
		memcpy(ansiBuf, pStrLastValume, strlen((char*)pStrLastValume));
	}
	else if (pLocalParam->u8_Sys_StartupVol <pLocalParam->Start_minVol || pLocalParam->u8_Sys_StartupVol > pLocalParam->Start_MaxVol)
	{
		pLocalParam->u8_Sys_StartupVol = pLocalParam->Start_defaultVol;
		sprintf((char*)ansiBuf,"%d",pLocalParam->u8_Sys_StartupVol);
	}
	else
	{
		sprintf((char*)ansiBuf,"%d",pLocalParam->u8_Sys_StartupVol);
	}

	int nAnsiBufLen = strlen((char*)ansiBuf);
	u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
	memset(unicodeBuf, 0, nAnsiBufLen*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicodeBuf);
	setSerialData(CONTROLID_SETUP_POWER_VOL_TEXT,unicodeBuf,nUnicodeBufLen*2);
	//systemToModule_NotifySoundModule_StartupVol(pLocalParam->u8_Sys_StartupVol);
	appToSys_Setup_PowerVol_Bar_MouseUp(pLocalParam->u8_Sys_StartupVol);
	LOGD("pLocalParam->u8_Sys_StartupVol----%d",pLocalParam->u8_Sys_StartupVol);
	free(unicodeBuf);
}

void SystemModuleToUI_aboutPanelLight()
{
	u8 ansiLedBuf[8];
	memset(ansiLedBuf, 0, 8);
	u8 *strAuto = (u8*)"Auto";
	
	if(pLocalParam->u8_Sys_PanelLight >20)
	{
		pLocalParam->u8_Sys_PanelLight = 0xFF;
		memcpy(ansiLedBuf, strAuto, strlen((char*)strAuto));
		setAnalogData(CONTROLID_SETUP_SET_PANEL_LIGHT_BAR,0);
	}
	else
	{
		sprintf((char*)ansiLedBuf,"%d",pLocalParam->u8_Sys_PanelLight);
		setAnalogData(CONTROLID_SETUP_SET_PANEL_LIGHT_BAR,pLocalParam->u8_Sys_PanelLight);
	}

	int nAnsiLedBufLen = strlen((char*)ansiLedBuf);
	u8 *unicodeLedBuf = (u8*)malloc(nAnsiLedBufLen*2+2);
	memset(unicodeLedBuf, 0, nAnsiLedBufLen*2+2);
	int nUnicodeLedBufLen = ansi_str_to_unicode16(ansiLedBuf, (unicode16_t*)unicodeLedBuf);
	setSerialData(CONTROLID_SETUP_PANEL_LIGHT_TEXT,unicodeLedBuf, nUnicodeLedBufLen*2);
	free(unicodeLedBuf);
}

void SystemModuleToUI_setVisible(void)
{
	if(pLocalParam->cCarAlarmVisible==0)
	{
		setVisible(CONTROLID_SETUP_CARINFO_ALARM_TEXT_BK,0x00);
		setVisible(CONTROLID_SETUP_AUDIO_AUTO_SOUND_ON_OFF,0x00);
		setVisible(CONTROLID_SETUP_CARINFO_AUDIO_CUE_ON_OFF,0x00);
	}
	if(pLocalParam->cCarTypeVisible==0)
	{
		setVisible(CONTROLID_SETUP_CAR__MODEL_TEXT,0x00);
		setVisible(CONTROLID_SETUP_CAR__MODEL_UP,0x00);
		setVisible(CONTROLID_SETUP_CAR__MODEL_DOWN,0x00);
		setVisible(CONTROLID_SETUP_CAR__MODEL_OK,0x00);
		setVisible(CONTROLID_SETUP_CAR_MODEL_TEXT_BK,0x00);

	}

}

void SystemModule_Init_TriggerType_SetVisible()
{
	LOGD("[%s] pLocalParam->uSystemBackcarTtiggerGroup=%d",__FUNCTION__,pLocalParam->uSystemBackcarTtiggerGroup);
	if(strcmp(pLocalParam->uSystemBackcarTtiggerGroup,"0") == 0)
	{
		setVisible(CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_UP,0x00);
    	setVisible(CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_DOWN,0x00);
    	setVisible(CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_CONTROL,0x00);
		setVisible(CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_TEXT,0x00);
	}
	else
	{
		setVisible(CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_UP,0x01);
    	setVisible(CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_DOWN,0x01);
    	setVisible(CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_CONTROL,0x01);
		setVisible(CONTROLID_SYSTEM_SETUP_BACKCAR_TRIGGER_TEXT,0x01);
		
	}
}

void ReadLogoStyleFile()
{
	TiXmlElement* rootElement1;
	TiXmlElement* rootElement2;
	TiXmlDocument doc;


    if(!doc.LoadFile(STYLE_LOGO_LIST_FILE_PATH)) 
    	return ;
    
    rootElement1 = doc.RootElement();
    rootElement2 = rootElement1->FirstChildElement("Bootanimation");

	char LogoStyleDisMark = 0;
   	char LogoStyleNameStr[128]={0};
   	char LogoStyleNameStrID[128]={0};
   	int count =0;
    while(rootElement2 != NULL)
    {
    	LogoStyleDisMark = 0;
       memset(LogoStyleNameStr,0,sizeof(LogoStyleNameStr));
    	memset(LogoStyleNameStrID,0,sizeof(LogoStyleNameStrID));

        LOGD("(%s %s)",rootElement2->Attribute("Name"),rootElement2->Attribute("NunberID"));
		
        if(rootElement2->Attribute("DisplayMark") == NULL)
        {
        }
        else
        {
			char cTempMark[5]={0};
     		strcpy(cTempMark, rootElement2->Attribute("DisplayMark"));
			LogoStyleDisMark = atoi(cTempMark);
        }

        if(rootElement2->Attribute("Name") == NULL)
        {
            memset(LogoStyleNameStr,0,sizeof(LogoStyleNameStr));
        }
        else
        {
            strcpy(LogoStyleNameStr, rootElement2->Attribute("Name"));
        }

        if(rootElement2->Attribute("NunberID") == NULL)
        {
            memset(LogoStyleNameStrID,0,sizeof(LogoStyleNameStrID));
        }
        else
        {
            strcpy(LogoStyleNameStrID, rootElement2->Attribute("NunberID"));
        }

		pLocalParam->st_LogoStyle[count].cLogoStyleMark = LogoStyleDisMark;
    	memcpy(pLocalParam->st_LogoStyle[count].cLogoStylesNameStr,LogoStyleNameStr,sizeof(LogoStyleNameStr));
    	pLocalParam->st_LogoStyle[count].cLogoStyleNameStrID=atoi(LogoStyleNameStrID);
    		
    	LOGD("count:%d LogoStyleDisMark:%d,LogoStyleNameStrID:%s",count,LogoStyleDisMark,LogoStyleNameStrID);
    	rootElement2=rootElement2->NextSiblingElement();
    	pLocalParam->nLogoStyleCount = count+1;
    	count++;	
    	LOGD("LOGO count is pLocalParam->nLogoStyleCount=%d",pLocalParam->nLogoStyleCount);
    }


    LOGD("+++++++");
	for(int i=0;i < pLocalParam->nLogoStyleCount;i++)
	{
	    LOGD("LogoNameStr:%s strID:%x ",pLocalParam->st_LogoStyle[i].cLogoStylesNameStr,pLocalParam->st_LogoStyle[i].cLogoStyleNameStrID);
	}
	LOGD("+++++++");
}


void ReadAllReturnToHomeForPageList()
{
	TiXmlElement* rootElement1;
	TiXmlElement* rootElement2;
	TiXmlDocument doc;

	if(!doc.LoadFile(RETURN_HOME_PAGE_FILE_PATH)) 
	return ;
	rootElement1 = doc.RootElement();
	rootElement2=rootElement1->FirstChildElement("Page");
	char PageStrID[128]={0};
	int count =0;
	memset(pLocalParam->pageStrIdList,0,sizeof(pLocalParam->pageStrIdList));
	pLocalParam->nPageCount = 0;
	while(rootElement2 != NULL)
	{
		if(rootElement2->Attribute("PageId") == NULL)
		{
			memset(PageStrID,0,128);
		}
		else
		{
			strcpy(PageStrID, rootElement2->Attribute("PageId"));
		}
		sscanf(PageStrID,"%x",&pLocalParam->pageStrIdList[count]);
		LOGD("%s count:%d pageId:0x%x",__FUNCTION__,count,pLocalParam->pageStrIdList[count]);
		rootElement2=rootElement2->NextSiblingElement();
		pLocalParam->nPageCount=count+1;
		count++;
	}
}

bool judgmentReturnHomePage(u16 curPage)
{
	if(pLocalParam->nPageCount > 0)
	{
		for(int i = 0;i < pLocalParam->nPageCount;i++)
		{
			if(pLocalParam->pageStrIdList[i] == curPage)
			{
				return true;
			}
		}
		return false;
	}
	else 
		return false;
}