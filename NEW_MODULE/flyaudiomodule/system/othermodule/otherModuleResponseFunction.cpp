#include <stdio.h>
#include <stdlib.h>

#include "pageID.h"
#include "controlID.h"
#include "global.h"
#include "param.h"
#include "moduleParamResponse.h"
#include "moduleParamRequest.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"
#include "otherModuleResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "halResponseFunction.h"
#include "timer_interface.h"
#include "otherModuleRequestCommand.h"
#include "appResponseFunction.h"
//#include "FlyDefine.h"

#include <map>
using namespace std;
extern "C"{
#include "barcode_access.h"
};


static u16 u16_pageTable[SYS_MAX_PAGE_COUNT];
static int top = -1;
static int topp= -1;
static int len=0;
static char ModuleTable[dim(pLocalParam->c_ModuleTable)]={0x00};

static int top1 = -1;
static int nLen=0;
static int triggerhead1 = -1;
static int ntype=0;

static char ExternalDeviceTable[dim(pLocalParam->uSystemExterDeviceGroup)]={0};
static char BackCarTriggerType[dim(pLocalParam->uSystemBackcarTtiggerGroup)]={0};


char Inquiry_Device(char cmap)
{
    map<char,char> mapArray;
	mapArray['1']=0;//DVR
	mapArray['2']=1;//TPMS\TV
	mapArray['3']=2;//DNV
	mapArray['4']=3;//RGB
	return mapArray[cmap];
}

void insert_deviceToTable(char cDevice)
{
   if(top1 < nLen)
    {
		top1++;
		LOGD("top1:%d",top1);
		ExternalDeviceTable[top1] = cDevice;
	}
}
 void DevicedisplayTable()
{
    int i;
	LOGI("+++++=======================+++++");
	for(i = 0; i <= top1; i++){
		LOGI("+++++   ExternalDeviceTable[%d]: %d   +++++", i, ExternalDeviceTable[i]);
	}
	LOGI("+++++=======================+++++");
}
void InitDeviceTable()
{
    int i;
	for(i=0;i<dim(pLocalParam->uSystemExterDeviceGroup);i++)
	{
		if(pLocalParam->uSystemExterDeviceGroup[i]==0)
		{
		    LOGD("InitDeviceTable");
			DevicedisplayTable();
			break;

		}
		nLen++;
		LOGD("@@@@InitDeviceTable:%c",pLocalParam->uSystemExterDeviceGroup[i]);
		char RetDevice=Inquiry_Device(pLocalParam->uSystemExterDeviceGroup[i]);
		LOGD("InitDeviceTable------RetDevice:0x%x",RetDevice);
		insert_deviceToTable(RetDevice);
	}
}

void systemToHal_setExternalDevice()
{
	LOGD("[%s] pLocalParam->m_eExternalDevice:%x",__FUNCTION__,pLocalParam->m_eExternalDevice);
	if(pLocalParam->m_eExternalDevice == EXTERNAL_DEVICE_UNKNOW)
	{
		LOGD("[%s] ExternalDeviceTable[0]:%x",__FUNCTION__,ExternalDeviceTable[0]);
		systemToHal_SetDVROrTV(ExternalDeviceTable[0]);
	}
	else
	{
		systemToHal_SetDVROrTV(pLocalParam->m_eExternalDevice);
	}
}

void SwitchDevice(char cDevice)
{
    systemToHal_SetDVROrTV(cDevice);
}

bool getCurDeviceTop(int *nTop,char p)
{
	int i;
	for(i=0;i < EXTERNAL_DEVICE_COUNT;i++)
	{
		LOGD("[%s] i:%d",__FUNCTION__,i);
		if(p == ExternalDeviceTable[i])
		{
			*nTop = i;
			return true;
		}
	}

	return false;
}

void SetLastDevice(char cDevice)
{

	int nCount = 0xff;
	if(getCurDeviceTop(&nCount,cDevice))
	{
		LOGD("[%s] nCount:%d",__FUNCTION__,nCount);
		if(nCount == 0)
		{
			SwitchDevice(ExternalDeviceTable[top1]);
		}
		else
		{
			SwitchDevice(ExternalDeviceTable[nCount-1]);
		}
	}
}

void SetNextDevice(char cDevice)
{
  int nCount = 0xff;
  if(getCurDeviceTop(&nCount,cDevice))
  {
  	  LOGD("[%s] nCount:%d",__FUNCTION__,nCount);
	  if(nCount == top1)
	  {
		  SwitchDevice(ExternalDeviceTable[0]);
	  }
	  else
	  {
		  SwitchDevice(ExternalDeviceTable[nCount+1]);
	  }
  }
}



char Inquiry_Module(char cmap)
{
    map<char,char> mapArray;
	mapArray['1']=MODULE_ID_DVD;
	mapArray['2']=MODULE_ID_RADIO;
	mapArray['3']=MODULE_ID_MEDIA;
	mapArray['4']=MODULE_ID_IPOD;
	mapArray['5']=MODULE_ID_BT;
	mapArray['6']=MODULE_ID_AUX;
	mapArray['7']=MODULE_ID_TV;
	return mapArray[cmap];
}
void insert_moduleToTable(char cModule)
{
   if(topp < 7)
	{
		topp++;
		ModuleTable[topp] = cModule;
	}
}
 void displayTable()
{
   int i;
	LOGI("+++++=======================+++++");
	LOGI("+++++    MODULE TABLE LIST    +++++");
	for(i = 0; i <= topp; i++){
		LOGI("+++++   Table[%02d]: 0x%04x   +++++", i, ModuleTable[i]);
	}
	LOGI("+++++=======================+++++");
}
void InitModuleTable()
{
   int i;
	for(i=0;i<dim(pLocalParam->c_ModuleTable);i++)
	{
		if(pLocalParam->c_ModuleTable[i]==0)
		{
		    LOGD("InitModuleTable~~~~~~~~~~~~~~~");
			displayTable();
			break;

		}
		len++;
		LOGD("@@@@InitModuleTable:%c",pLocalParam->c_ModuleTable[i]);
		char RetModule=Inquiry_Module(pLocalParam->c_ModuleTable[i]);
		LOGD("InitModuleTable------RetModule:0x%x",RetModule);
		insert_moduleToTable(RetModule);
	}
}
void GetNextModule(char cModule)
{
   int i;
   for(i=0;i<(int)dim(ModuleTable);i++)
   	{
   	   if(ModuleTable[i]==cModule)
   	   	{
   	   	   LOGD("GetNextModule:i=%d",i);
   	   	   LOGD("GetNextModule:ModuleTable[i]=%x",ModuleTable[i]);
   	   	   LOGD("GetNextModule:dim(ModuleTable)-1=%x",(dim(ModuleTable)-1));
   	   	  if(i==dim(ModuleTable)-1)
   	   	  	{
		  	 BaseModuleSwitchPage(ModuleTable[0]);
			 break;
   	   	  	}
		  else
		  	{
		  	 BaseModuleSwitchPage(ModuleTable[++i]);
	         break;
		  	}
   	   	}
   	}
}
bool CheckModuleWhetherExist(char cModule)
{
   switch(cModule)
   	{
   	   case MODULE_ID_DVD:
	   	break;
	   case MODULE_ID_RADIO:
	   	break;
	   case MODULE_ID_MEDIA:
	   	break;
	   case MODULE_ID_IPOD:
	   	break;
	   case MODULE_ID_BT:
	   	break;
	   case MODULE_ID_AUX:
	   	break;
	   case MODULE_ID_TV:
	   	break;
	   	default:
			break;
   	}
   	return true;
}
void BaseModuleSwitchPage(char cModule)
{
   LOGD("BaseModuleSwitchPage:x%x  pLocalParam->b_Sys_BrakeCarStatus %d",cModule,pLocalParam->b_Sys_BrakeCarStatus);
  switch(cModule)
   	{
   	   case MODULE_ID_DVD:
	   		switch_Page(PAGE_DVD_MAIN);
	    	break;
	   case MODULE_ID_RADIO:
	   	    systemToModule_NotifyRadioModule_PressKey_AV();
	   	    switch_Page(PAGE_RADIO_MAIN);
			break;
	   case MODULE_ID_MEDIA:
	   	    switch_Page(PAGE_MEDIA);
	    	break;
	   case MODULE_ID_IPOD:
	   	    if(CheckModuleWhetherExist(MODULE_ID_IPOD))
   	       {
   	         switch_Page(PAGE_IPOD);
   	    	}
			else
			{
			  GetNextModule(MODULE_ID_IPOD);
			}
	    	break;
	   case MODULE_ID_BT:
	   	    if(Check_SupportA2DP())
	   	    	{
	   	          switch_Page(PAGE_BLUETOOTH_A2DP);
	   	    	}
			else
				{
				  GetNextModule(MODULE_ID_BT);
				}
	    	break;
	   case MODULE_ID_AUX:
	   		if(IsCanSwitchVideoPage_WhenTheBrakeDownTime(pLocalParam->cBreakCarEnable,pLocalParam->b_Sys_BrakeCarStatus))
	   		{
	   		    if(pLocalParam->u8_Sys_AUXVideo)
		    	{
		    		/*2014-2-11(������Ƶ���)*/
					systemToModule_NotifyAUXModule_AUXChecking();
		     		switch_Page(PAGE_AUX);
		    	}
				else
				{
					/*2014-2-11(������Ƶ���)*/
					systemToModule_NotifyAUXModule_AUXChecking();
					switch_Page(PAGE_AUX);
				}
	   		}
	   		else
	   		{
	   		    GetNextModule(MODULE_ID_AUX);
	   		}
	    	break;
	   case MODULE_ID_TV:
	   	    if(pLocalParam->u8_Sys_WhetherTVExist)
   	    	{
   	    	  	switch_Page(PAGE_TV_VIDEO);
   	    	}
			else
			{
	   	      	GetNextModule(MODULE_ID_TV);
			}
	    	break;
	    case 0x00:
	         BaseModuleSwitchPage(ModuleTable[0]);
	         break;
	   	default:
			break;
   	}
}
bool Check_SupportA2DP()
{
    u8 u8_SupportA2DP = 0;
	u8 nLen = 0;
	getOtherModuleParam(MODULE_ID_BT, BT_A2DP_SUPPORT, &u8_SupportA2DP, &nLen);
	if(u8_SupportA2DP)
	{
	   return true;
	}
	else
	{
	  return false;
	}

}
 void insert_pageToTable(u16 pageId)
{
	if(top < (SYS_MAX_PAGE_COUNT-1))
	{
		top++;
		u16_pageTable[top] = pageId;
	}
	else if(top>=19)
	{
		int i;
		for(i = 0; i < SYS_MAX_PAGE_COUNT-1; i++)
		{
		u16_pageTable[i] = u16_pageTable[i+1];
		}
		u16_pageTable[top] = pageId;
	}
	g_clsSystem.sendToFlyJniSdkCurPageID();
}

bool IsFlyPartyPage(u16 pageId){
	switch(pageId){
		case PAGE_THIRD_PAGE:
		case PAGE_MEDIA:
		case PAGE_GPS_PAGE:
		//case PAGE_3G_PAGE:
		case 0x00:
		case SYS_INVALID_PAGE:
		case PAGE_SPEECH_APP_MEDIA:
		case PAGE_DRIVING_FRONT_CAMERA_APP:
			return false;
		break;
		default:
			return true;
		break;
	}
}

u16 getLastFlyPage(){
      for(int i = top;i>=0;i-- ){
      	if(IsFlyPartyPage(u16_pageTable[i]))
      	{
      		return u16_pageTable[i];
      	}
      }
      return 0;
}

 u16 delete_pageFromTable(void){
	u16 ret_pageid;

	if(top < 0){
		ret_pageid = SYS_INVALID_PAGE;
	}
	else{
		ret_pageid = u16_pageTable[top];
		top--;
	}
	g_clsSystem.sendToFlyJniSdkCurPageID();
	return ret_pageid;
}

void empty_pageToTable()
{
	for(;top >= 0;top--){
		delete_pageFromTable();
	}
}

 u16 getCurPage(void){
	u16 ret_pageid;

	if(top < 0){
		ret_pageid = SYS_INVALID_PAGE;
	}
	else{
		ret_pageid = u16_pageTable[top];
	}

	return ret_pageid;
}

 u16 getPrePage(void){
	u16 ret_pageid;

	if(top <= 0){
		ret_pageid = SYS_INVALID_PAGE;
	}
	else{
		ret_pageid = u16_pageTable[top-1];
	}

	return ret_pageid;
}


static void changePage(u8 position1,u8 position2)
{
    u16 tempPage=u16_pageTable[position1];
	u16_pageTable[position1]=u16_pageTable[position2];
	u16_pageTable[position2]=tempPage;
}

 void SendPageTableToOSDDebug(void)
  {
	  char cDebugBuf1[256]={0x00,0x00};
	  int buf1Len=1;
	  char cDebugBuf2[256]={0x01,0x00};
	  int buf2Len=1;
	  
	  int nbegin=top<10?0:top-9; 
	  while(nbegin<=top)
	  {
		  if(nbegin<=top-5)
		  {
			  sprintf(&cDebugBuf1[buf1Len],"%04x ,",u16_pageTable[nbegin]);
			  buf1Len+=6;
		  }
		  else
		  {
			  sprintf(&cDebugBuf2[buf2Len],"%04x ,",u16_pageTable[nbegin]);
			  buf2Len+=6;
		  }
		 nbegin++;
	  }
	  u8 uDebugBuf1[256]={0};
	  u8 uDebugBuf2[256]={0};
	  memcpy(uDebugBuf1,cDebugBuf1,buf1Len);
	  memcpy(uDebugBuf2,cDebugBuf2,buf2Len);
	  LOGD("uDebugBuf1:%s",uDebugBuf1);
	  LOGD("uDebugBuf2:%s",uDebugBuf2);
	  makeAndSendMessageToModule(MODULE_ID_OSD,MODULE_ID_SYSTEM,uDebugBuf1,buf1Len);
	  makeAndSendMessageToModule(MODULE_ID_OSD,MODULE_ID_SYSTEM,uDebugBuf2,buf2Len);
  }

 void displayPageTable(void){
	int i;
	LOGI("+++++=======================+++++");
	LOGI("+++++    PAGE TABLE LIST    +++++");
	for(i = 0; i <= top; i++){
		LOGI("+++++   Table[%02d]: 0x%04x   +++++", i, u16_pageTable[i]);
	}
	SendPageTableToOSDDebug();
	LOGI("+++++=======================+++++");
}

bool isCanJump(u16 pageId)
{
   switch(pageId)
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
	case SYS_THIRD_PAGE_BACK: 
	case SYS_ENTER_HOME_PAGE:
	case SYS_INVALID_PAGE:
	case SYS_SET_PRE_PAGE: 
	case SYS_EQ_AUDIO_PRE_PAGE:
	     return false;
	break;
	default:
		return true;
	break;
   }
}

u16 getCurPageCanJumpTo()
{
	for(int i = top; i >= 0; i--)
	{
		u16 curPage = u16_pageTable[i];
		if(IsFlyPartyPage(curPage))
		{
			if(isCanJump(curPage))
			return curPage;
		}
	}
	
	return 0;
}

void androidKeyMessageDeliverControllor(u16 pageId){
	u8 bIsInBackCar = 0;
	u8 backStatusLen = 0;
	getOtherModuleParam(MODULE_ID_BACK, BACK_CAR_STATE, &bIsInBackCar, &backStatusLen);

	if(bIsInBackCar)
		systemToHal_SetAndroidKeyMessageDeliver(false);
	else
		systemToHal_SetAndroidKeyMessageDeliver(true);
}

static u16 process_Back_PrePage(u16 prePage){
	u16 toJumpPage;
	switch(prePage){
	case PAGE_BACK_VIDEO:
	case PAGE_BACK_FULL_VIDEO:
	case PAGE_BACK_NOVIDEO:
	case PAGE_BACK_FULL_VIDEO_CONTROL:
	case PAGE_DVD_VIDEO_SET:
	case PAGE_DVD_VIDEO_CONTROL:
	case PAGE_DVD_OPEN:
	case PAGE_AUX_VIDEO_CONTROL:
	case PAGE_AUX_VIDEO_SET:
	case PAGE_TV_VIDEO_CONTROL:
	case PAGE_TV_VIDEO_SET:
	case PAGE_STANDBY:
	case PAGE_GPS_PAGE:
	case PAGE_SPEECH_APP_MEDIA:
		toJumpPage = SYS_JUMP_PRE_PAGE;
		break;
	default:
		toJumpPage = prePage;
		break;
	}

	return toJumpPage;
}

static u16 process_General_PrePage(u16 prePage){
	u16 toJumpPage;
	switch(prePage){
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
	//case PAGE_GPS_PAGE:
	case PAGE_DRIVING_RECORD_MENU:
	case PAGE_DRIVING_RECORD_TIME_SET:
	case PAGE_DRIVING_RECORD_SET:
	case PAGE_DRIVING_RECORD_PALY:
	case PAGE_MATCHING_MODELS:
	case PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD:
	case PAGE_DRIVING_CHANGHE_DVR_SET_OSD:
	case PAGE_SPEECH_APP_MEDIA:
		toJumpPage = SYS_JUMP_PRE_PAGE;
		break;
	case PAGE_STANDBY:  // open by jing 2013-8-13
		if(pLocalParam->b_back)  //  if standby status is true , jump to PAGE_STANDBY .
		{
			toJumpPage = prePage;
			break;
		}else   // else is means if curPage is backcar , jump out of back and prepage is standby , then do nothing
		{
			toJumpPage = SYS_JUMP_PRE_PAGE;
		}
	break;
	default:
		{
			LOGD("process_General_PrePage u8_Sys_AUXVideo:%x prePage:%x",pLocalParam->u8_Sys_AUXVideo,prePage);
			if(pLocalParam->u8_Sys_AUXVideo == 1 && prePage == PAGE_AUX)
			{
				toJumpPage = SYS_JUMP_PRE_PAGE;
			}
			else if(prePage == PAGE_BLUETOOTH_NO_A2DP || prePage == PAGE_BLUETOOTH_A2DP)
			{
				toJumpPage = CurBtA2dpIsSupport_CheckBackKeyJumpPage(prePage);
			}
			else
			{
				toJumpPage = prePage;
			}
			break;
		}
	}

	return toJumpPage;
}

static u16 process_Setup_PrePage(u16 prePage){
	u16 toJumpPage;

	//if(pLocalParam->nSpecificSkin_PrePage==1)
	//{
	//	if(prePage == PAGE_THIRD_PAGE)
	//		return PAGE_FINISH_FLYAPP;
	//	return prePage;
	//}
	//else
	//{
		switch(prePage){
		case PAGE_SETUP_BEGIN:
		case PAGE_SETUP_BEGIN+1:
		case PAGE_SETUP_BEGIN+2:
		case PAGE_SETUP_BEGIN+3:
		case PAGE_SETUP_BEGIN+4:
		case PAGE_SETUP_BEGIN+5:
		case PAGE_SETUP_BEGIN+6:
		case PAGE_SETUP_BEGIN+7:
		case PAGE_SETUP_BEGIN+8:
		case PAGE_SETUP_BEGIN+9:
		case PAGE_SETUP_BEGIN+10:
		case PAGE_SETUP_BEGIN+11:
		case PAGE_SETUP_BEGIN+12:
		case PAGE_SETUP_BEGIN+13:
		case PAGE_SETUP_END:
		case PAGE_SYSTEM_WHEEL_LEARNING:
		//case PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_ONE:		
		case PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_TWO:		
		case PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_THREE:		
		case PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_FOUR:		
		case PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_FIVE:
		case PAGE_SYSTEM_SET_COMMON_SECOND_PAGE:
		case PAGE_SPEECH_APP_MEDIA:
			toJumpPage = SYS_SET_PRE_PAGE;
			break;
		default:
			if(prePage == PAGE_THIRD_PAGE)
				return PAGE_FINISH_FLYAPP;
			toJumpPage = prePage;
			break;
		}

		return toJumpPage;
	//}
}


u16 process_Back_PrePage_TUGUAN(u16 prePage){
	u16 toJumpPage;
	switch(prePage){
	case PAGE_BACK_VIDEO:
	case PAGE_BACK_NOVIDEO:
	case PAGE_BACK_FULL_VIDEO:
	case PAGE_BACK_FULL_VIDEO_CONTROL:
	case PAGE_DVD_VIDEO_SET:
	case PAGE_DVD_VIDEO_CONTROL:
	case PAGE_DVD_OPEN:
	case PAGE_AUX_VIDEO_CONTROL:
	case PAGE_AUX_VIDEO_SET:
	case PAGE_TV_VIDEO_CONTROL:
	case PAGE_TV_VIDEO_SET:
	case PAGE_STANDBY:
		toJumpPage = SYS_JUMP_PRE_PAGE;
		break;
	default:
		toJumpPage = prePage;
		break;
	}

	return toJumpPage;
}

static u16 process_EqAudio_PrePage(u16 prePage){
	u16 toJumpPage;

#ifdef MTK_3561_64

	switch(prePage){
	case PAGE_EQ:
	case PAGE_SOUND:
	case PAGE_AUDIO_SET_BOX:
	case PAGE_SPEECH_APP_MEDIA:
		toJumpPage = SYS_EQ_AUDIO_PRE_PAGE;
		break;
	default:
		toJumpPage = prePage;
		break;
	}

	return toJumpPage;

#else

	if(pLocalParam->nSpecificSkin_PrePage == 1)
	{
		return prePage;
	}
	else
	{
		switch(prePage){
		case PAGE_EQ:
		case PAGE_SOUND:
		case PAGE_AUDIO_SET_BOX:
			toJumpPage = SYS_EQ_AUDIO_PRE_PAGE;
			break;
		default:
			toJumpPage = prePage;
			break;
		}

		return toJumpPage;
	}
	
#endif
}
static u16 process_DVD_PrePage(u16 prePage)
{
   u16 toJumpPage;

	switch(prePage){
	case PAGE_AUX:
	case PAGE_AUX_VIDEO:
	case PAGE_AUX_VIDEO_CONTROL:
	case PAGE_AUX_VIDEO_SET:
	case PAGE_BACK_NOVIDEO:
	case PAGE_BACK_RADAR:
	case PAGE_BACK_VIDEO:
	case PAGE_BACK_FULL_VIDEO:
	case PAGE_BACK_FULL_VIDEO_CONTROL:
	case PAGE_DVD_VIDEO_SET:
	case PAGE_DVD_VIDEO_CONTROL:
	case PAGE_DVD_TRACKLIST:
	case PAGE_DVD_FOLDER:
	case PAGE_DVD_OPEN:
	case PAGE_DVD_VIDEO:
	case PAGE_BLACK:
	case PAGE_STANDBY:
	case PAGE_TV_NO_VIDEO:
	case PAGE_TV_VIDEO:
	case PAGE_TV_VIDEO_CONTROL:
	case PAGE_TV_VIDEO_SET:
	case PAGE_SPEECH_APP_MEDIA:
		toJumpPage = SYS_DVD_PAGE;
		break;
	default:
		toJumpPage = prePage;
		break;
	}

	return toJumpPage;
}

static u16 process_Personalization_PrePage(u16 prePage)
{
	u16 toJumpPage;

	switch(prePage){
	case PAGE_BLACK:
	case PAGE_STANDBY:
	case PAGE_GOLF_SETUP_PERSONALIZATION_1:
	case PAGE_GOLF_SETUP_PERSONALIZATION_2:
	case PAGE_TRAVEL_INFORMATION: 
	case PAGE_BLUE_SKIN_CAR_SETUP: 
	case PAGE_BLUE_SKIN_CAR_DRIVING_DATA:
	case PAGE_BLUE_SKIN_CAR_MAINTAIN: 
	case PAGE_BLUE_SKIN_CAR_TOYOTA_HISTORY_RECORD:
	case PAGE_BLUE_SKIN_CAR_HIGHLANDER_SETUP: 
	case PAGE_BLUE_SKIN_CAR_HIGHLANDER_PARKING:
	case PAGE_SPEECH_APP_MEDIA:
		toJumpPage = SYS_SETUP_PERSONALIZATION_PRE_PAGE;
		break;
	default:
		toJumpPage = prePage;
		break;
	}

	return toJumpPage;

}

static u16 process_Comfortable_Converient_PrePage(u16 prePage)
{
	u16 toJumpPage;

	switch(prePage){
		case PAGE_BLACK:
		case PAGE_STANDBY:
		case PAGE_TRAVEL_INFORMATION_CAR_SET1:
		case PAGE_TRAVEL_INFORMATION_COMFORTABLE_CONVENIENT_SET:
		case PAGE_SPEECH_APP_MEDIA:
			toJumpPage = SYS_SETUP_COMFORTABLE_CONVERIENT_PRE_PAGE;
			break;
		default:
			toJumpPage = prePage;
			break;
	}

	return toJumpPage;
}


static u16 process_Dvr_PrePage(u16 prePage){
	u16 toJumpPage;
	
	 switch(prePage){
	 case PAGE_AUX:
	 case PAGE_AUX_VIDEO:
	 case PAGE_AUX_VIDEO_CONTROL:
	 case PAGE_AUX_VIDEO_SET:
	 case PAGE_BACK_NOVIDEO:
	 case PAGE_BACK_RADAR:
	 case PAGE_BACK_VIDEO:
	 case PAGE_BACK_FULL_VIDEO:
	 case PAGE_BACK_FULL_VIDEO_CONTROL:
	 case PAGE_DVD_VIDEO_SET:
	 case PAGE_DVD_VIDEO_CONTROL:
	 case PAGE_DVD_TRACKLIST:
	 case PAGE_DVD_FOLDER:
	 case PAGE_DVD_OPEN:
	 case PAGE_DVD_VIDEO:
	 case PAGE_BLACK:
	 case PAGE_STANDBY:
	 case PAGE_TV_NO_VIDEO:
	 case PAGE_TV_VIDEO:
	 case PAGE_TV_VIDEO_CONTROL:
	 case PAGE_TV_VIDEO_SET:
	 	
	 case PAGE_DRIVING_RECORD_MENU:
	 case PAGE_DRIVING_RECORD_TIME_SET:
	 case PAGE_DRIVING_RECORD_SET:
	 case PAGE_DRIVING_RECORD_PALY:
	 case PAGE_DRIVING_RECORD_VIDEO:
	 case PAGE_DRIVING_RECORD_NO_SIGN:
	 case PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD:
	 case PAGE_DRIVING_CHANGHE_DVR_SET_OSD:
	 case PAGE_SPEECH_APP_MEDIA:
		 toJumpPage = SYS_DVR_PAGE;
		 break;
	 default:
		 toJumpPage = prePage;
		 break;
	 }
	
	 return toJumpPage;

}

static u16 process_Aux_PrePage(u16 prePage){
	u16 toJumpPage;

	switch(prePage){
	case PAGE_AUX:
	case PAGE_AUX_VIDEO:
	case PAGE_AUX_VIDEO_CONTROL:
	case PAGE_AUX_VIDEO_SET:
	case PAGE_BACK_NOVIDEO:
	case PAGE_BACK_RADAR:
	case PAGE_BACK_VIDEO:
	case PAGE_BACK_FULL_VIDEO:
	case PAGE_BACK_FULL_VIDEO_CONTROL:
	case PAGE_DVD_VIDEO_SET:
	case PAGE_DVD_VIDEO_CONTROL:
	case PAGE_DVD_OPEN:
	case PAGE_DVD_VIDEO:
	case PAGE_BLACK:
	case PAGE_STANDBY:
	case PAGE_TV_NO_VIDEO:
	case PAGE_TV_VIDEO:
	case PAGE_TV_VIDEO_CONTROL:
	case PAGE_TV_VIDEO_SET:
	case PAGE_SPEECH_APP_MEDIA:
		toJumpPage = SYS_AUX_TEMP_PAGE;
		break;
	default:
		toJumpPage = prePage;
		break;
	}

	return toJumpPage;
}

static u16 process_BtMusic_PrePage(u16 prePage){
	u16 toJumpPage;

	switch(prePage){
		case PAGE_AUX:
		case PAGE_AUX_VIDEO:
		case PAGE_AUX_VIDEO_CONTROL:
		case PAGE_AUX_VIDEO_SET:
		case PAGE_BACK_NOVIDEO:
		case PAGE_BACK_RADAR:
		case PAGE_BACK_VIDEO:
		case PAGE_BACK_FULL_VIDEO:
		case PAGE_BACK_FULL_VIDEO_CONTROL:
		case PAGE_DVD_VIDEO_SET:
		case PAGE_DVD_VIDEO_CONTROL:
		case PAGE_DVD_OPEN:
		case PAGE_DVD_VIDEO:
		case PAGE_BLACK:
		case PAGE_STANDBY:
		case PAGE_TV_NO_VIDEO:
		case PAGE_TV_VIDEO:
		case PAGE_TV_VIDEO_CONTROL:
		case PAGE_TV_VIDEO_SET:

		case PAGE_BLUETOOTH_A2DP:
		case PAGE_BLUETOOTH_NO_A2DP:
		case PAGE_SPEECH_APP_MEDIA:
		toJumpPage = SYS_BT_MUSIC_PAGE;
		break;
	default:
		toJumpPage = prePage;
		break;
	}
	return toJumpPage;
}
static u16 process_Bt_PrePage(u16 prePage){
	u16 toJumpPage;

	switch(prePage){
		case PAGE_AUX:
		case PAGE_AUX_VIDEO:
		case PAGE_AUX_VIDEO_CONTROL:
		case PAGE_AUX_VIDEO_SET:
		case PAGE_BACK_NOVIDEO:
		case PAGE_BACK_RADAR:
		case PAGE_BACK_VIDEO:
		case PAGE_BACK_FULL_VIDEO:
		case PAGE_BACK_FULL_VIDEO_CONTROL:
		case PAGE_DVD_VIDEO_SET:
		case PAGE_DVD_VIDEO_CONTROL:
		case PAGE_DVD_OPEN:
		case PAGE_DVD_VIDEO:
		case PAGE_BLACK:
		case PAGE_STANDBY:
		case PAGE_TV_NO_VIDEO:
		case PAGE_TV_VIDEO:
		case PAGE_TV_VIDEO_CONTROL:
		case PAGE_TV_VIDEO_SET:
		case PAGE_BLUETOOTH_MOBILE_RECORD:
		case PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_EGLISH:
		case PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME:
		case PAGE_BLUETOOTH_AUDIOVOX_PAIR_SETTING:
		case PAGE_BLUETOOTH_MAIN:
		case PAGE_BLUETOOTH_AUDIOVOX_SEARCH:
		case PAGE_BLUETOOTH_PAIRING_DIALOG_BOX:
		case PAGE_SPEECH_APP_MEDIA:
		{
			toJumpPage = SYS_BT_MAIN_PAGE;
		}
		break;
		default:
			toJumpPage = prePage;
		break;
	}

	return toJumpPage;
}

static u16 process_Parking_Assist_PrePage(u16 prePage){
	u16 toJumpPage;
	switch(prePage){
		case PAGE_AUX:
		case PAGE_AUX_VIDEO:
		case PAGE_AUX_VIDEO_CONTROL:
		case PAGE_AUX_VIDEO_SET:
		case PAGE_BLACK:
		case PAGE_STANDBY:
		case PAGE_SPEECH_APP_MEDIA:
		case PAGE_PARALLEL_PARK_PAGE:
		case PAGE_PERPENDICULAR_PARK_PAGE:
		case PAGE_PARK_OUT_ASSIST_PAGE:
		{
			toJumpPage = SYS_EXTCAR_PARKING_ASSIST_PAGE;
		}
		break;
		default:
			toJumpPage = prePage;
		break;
	}

	return toJumpPage;
}

static u16 process_MCS_PrePage(u16 prePage)
{
	u16 toJumpPage;
	switch(prePage){
		case PAGE_AUX:
		case PAGE_AUX_VIDEO:
		case PAGE_AUX_VIDEO_CONTROL:
		case PAGE_AUX_VIDEO_SET:
		case PAGE_BLACK:
		case PAGE_STANDBY:
		case PAGE_SPEECH_APP_MEDIA:
		case PAGE_MULTI_CONTOURED_SEATS_ADJUST:
		case PAGE_MULTI_CONTOURED_SEATS_MASSAGE:
		{
			toJumpPage = SYS_EXTCAR_MCS_PAGE;
		}
		break;
		default:
			toJumpPage = prePage;
		break;
	}

	return toJumpPage;

}

static u16 checkPrePageToJump(u16 pageID){
	u16 tmp_curPage = getCurPage();
	u16 tmp_prePage = getPrePage();
	u16 toJumpPage;

	LOGD("tmp_curPage:%x",tmp_curPage);
	if(tmp_curPage == PAGE_STANDBY)
		pLocalParam->u16_Sys_PrePage = PAGE_STANDBY;

	LOGD("pLocalParam->u16_Sys_PrePage:%x",pLocalParam->u16_Sys_PrePage);
	if(tmp_prePage == SYS_INVALID_PAGE){
		delete_pageFromTable();
		LOGD("SYS_INVALID_PAGE");
		return SYS_INVALID_PAGE;
	}

	delete_pageFromTable();

	LOGD("checkPrePageToJump tmp_prePage:%x",tmp_prePage);

	switch(pageID){
	case SYS_JUMP_PRE_PAGE:
		toJumpPage = process_General_PrePage(tmp_prePage);
		break;
	case SYS_SET_PRE_PAGE:
		toJumpPage = process_Setup_PrePage(tmp_prePage);
		break;
	case SYS_EQ_AUDIO_PRE_PAGE:
		toJumpPage = process_EqAudio_PrePage(tmp_prePage);
		break;
	case SYS_AUX_TEMP_PAGE:
		toJumpPage = process_Aux_PrePage(tmp_prePage);
		break;
	case SYS_BT_MUSIC_PAGE:
		toJumpPage = process_BtMusic_PrePage(tmp_prePage);
		break;
	case SYS_DVD_PAGE:
		toJumpPage = process_DVD_PrePage(tmp_prePage);
		break;
	case SYS_BACK_PAGE:
	    toJumpPage = process_Back_PrePage(tmp_prePage);
		break;
	case SYS_DVR_PAGE:
		toJumpPage = process_Dvr_PrePage(tmp_prePage);
		break;
	case SYS_SETUP_PERSONALIZATION_PRE_PAGE:
		toJumpPage = process_Personalization_PrePage(tmp_prePage);
		break;
	case SYS_SETUP_COMFORTABLE_CONVERIENT_PRE_PAGE:
		toJumpPage = process_Comfortable_Converient_PrePage(tmp_prePage);
		break;
	case SYS_BT_MAIN_PAGE:
		toJumpPage = process_Bt_PrePage(tmp_prePage);
		break;
	case SYS_EXTCAR_PARKING_ASSIST_PAGE:
		toJumpPage = process_Parking_Assist_PrePage(tmp_prePage);
		break;
	case SYS_EXTCAR_MCS_PAGE:
		toJumpPage = process_MCS_PrePage(tmp_prePage);
		break;
	default:
		toJumpPage = tmp_prePage;
		break;

	}

	return toJumpPage;
}

static u16 processThirdPageBack(void){
	delete_pageFromTable();
		return PAGE_FINISH_FLYAPP;
}

static u16 checkPageToJump(u16 pageid){	
	LOGD("checkPageToJump pageid:%x",pageid);
	u16 ToJumpPage = pageid;
	switch(pageid){
	case SYS_JUMP_PRE_PAGE:
	case SYS_SET_PRE_PAGE:
	case SYS_EQ_AUDIO_PRE_PAGE:
	case SYS_AUX_TEMP_PAGE:
	case SYS_BT_MUSIC_PAGE:
	case SYS_DVD_PAGE:
	case SYS_DVR_PAGE:
	case SYS_BACK_PAGE:
	case SYS_SETUP_PERSONALIZATION_PRE_PAGE:
	case SYS_SETUP_COMFORTABLE_CONVERIENT_PRE_PAGE:
	case SYS_BT_MAIN_PAGE:
	case SYS_EXTCAR_PARKING_ASSIST_PAGE:
	case SYS_EXTCAR_MCS_PAGE:
		ToJumpPage = checkPrePageToJump(pageid);
		ToJumpPage = checkPageToJump(ToJumpPage);
		break;
	case SYS_THIRD_PAGE_BACK:
	case PAGE_THIRD_PAGE:
		ToJumpPage = processThirdPageBack();
	    break;
	case SYS_ENTER_HOME_PAGE:
	case SYS_INVALID_PAGE:
		ToJumpPage = PAGE_MENU;
		break;
	//case PAGE_STANDBY:
	case PAGE_BLACK:
		if(pLocalParam->b_back){
			ToJumpPage = checkPrePageToJump(pageid);
			ToJumpPage = checkPageToJump(ToJumpPage);
		}
		else{
			ToJumpPage = pageid;
		}
		break;
	default:
		ToJumpPage = pageid;
		break;
	}

	return ToJumpPage;
}

bool verifyWhetherFinishedJumpPage(u16 pageId){
	bool bIsFinishedJumpPage = false;

	if(pLocalParam->b_Sys_ThirdPageBackMark){
		bIsFinishedJumpPage = true;
		return bIsFinishedJumpPage;
	}

	switch(pageId){
	case PAGE_THIRD_PAGE:
		if(!pLocalParam->b_Sys_ThirdPageMark)
			bIsFinishedJumpPage = false;
		else{
			bIsFinishedJumpPage = true;
			pLocalParam->b_Sys_ThirdPageMark = false;
		}
		break;
	case PAGE_MENU:
		if(!pLocalParam->b_Sys_HomePageMark)
			bIsFinishedJumpPage = false;
		else{
			pLocalParam->b_Sys_HomePageMark = false;
			bIsFinishedJumpPage = true;
		}
		break;
	case PAGE_MEDIA:
		bIsFinishedJumpPage = true;
		
		/*
	case PAGE_GPS_PAGE:
		if(!pLocalParam->b_Sys_GpsPageMark)
			bIsFinishedJumpPage = false;
		else{
			pLocalParam->b_Sys_GpsPageMark = false;
			bIsFinishedJumpPage = true;
		}
		break;*/
	default:
		bIsFinishedJumpPage = false;
		break;
	}

	return bIsFinishedJumpPage;
}


bool Check_WhetherCanJump(u16 u16_NewPageID)
{
	u16 PrePage=getPrePage();
	u8 ucMobileStatus=0;
	u8 nLen=0;
	getOtherModuleParam(MODULE_ID_BT,BT_MOBILE_STATUS,(u8*)&ucMobileStatus,&nLen);
	LOGD("Check_WhetherCanJump  ucMobileStatus=%d",ucMobileStatus);
	if((ucMobileStatus == 0x01 || ucMobileStatus == 0x02) && pLocalParam->nScreenSwitchStatus == 0)
	{
		systemToHal_SetScreenOnOrOff(0x01);
		return false;
	}
	
	if(pLocalParam->u8_Sys_CurLcdLight==0 && PrePage==PAGE_BLACK)
	{
  		if(u16_NewPageID!=PAGE_BLACK && u16_NewPageID!=PAGE_STANDBY &&u16_NewPageID!=PAGE_BACK_NOVIDEO&&u16_NewPageID!=PAGE_BACK_FULL_VIDEO
   			&&u16_NewPageID!=PAGE_BACK_FULL_VIDEO_CONTROL&&u16_NewPageID!=PAGE_BACK_VIDEO)
   			{
   				LOGD("Check_WhetherCanJump0 changePage:0x%x top=%d",u16_NewPageID,top);
   	 			changePage(top,top-1);
	 			displayPageTable();
				return true;
 			}
	}
	else
	{
		return false;
	}
}


void jumpToPage(u16 pageid){
	u16 u16_NewPageID=pageid;
	if(Check_WhetherCanJump(u16_NewPageID))
	{
		if(pLocalParam->nScreenSwitchStatus == 0 && getCurPage() == PAGE_BLACK)
		{
		}else{
			delete_pageFromTable();//�������ҳӦ��ʱҪɾ��
		}
		LOGD("Don't Jump!(Check_WhetherCanJump)");
		return;
	}	
	bool bIsFinishedJump = verifyWhetherFinishedJumpPage(pageid);

	LOGD("jumpToPage bIsFinishedJump:%x",bIsFinishedJump);
	LOGD("jumpToPage pLocalParam->u16_Sys_PrePage:%x",pLocalParam->u16_Sys_PrePage);
	if(pLocalParam->u16_Sys_PrePage == PAGE_STANDBY){
		SystemToSpecificModuleFromAudioVideoChannel(PAGE_STANDBY,getCurPage());
		pLocalParam->u16_Sys_PrePage = 0;
	}
	else
	{
		if(pageid==PAGE_FINISH_FLYAPP ||pageid==PAGE_FINISH_MEDIAAPP)
		{
			SystemToSpecificModuleFromAudioVideoChannel(PAGE_THIRD_PAGE,PAGE_MENU);
		}
		else if(pageid == PAGE_MENU)
		{
			SystemToSpecificModuleFromAudioVideoChannel(getCurPage(),PAGE_MENU);
		}
		else
		{
			if(pageid != PAGE_BACK_VIDEO)
				SystemToSpecificModuleFromAudioVideoChannel(getPrePage(),getCurPage());
		}
	}
	
	if(!bIsFinishedJump)
	{
		jumpPage(pageid);
	}
	
	LOGI("Jump to Page: 0x%04x, curPage: 0x%04x, prePage: 0x%04x",pageid,getCurPage(), getPrePage());
	displayPageTable();
}

u16 CurBtA2dpIsSupport_CheckBackKeyJumpPage(u16 pageId)
{
	u16 ToJumpPage = pageId;

	u8 u8_CurBtA2dpIsSupport = 0;
	u8 nLen2 = 0;
	getOtherModuleParam(MODULE_ID_BT,BT_A2DP_SUPPORT,(u8*)&u8_CurBtA2dpIsSupport,&nLen2);

	LOGD("[%s] u8_CurBtA2dpIsSupport:%x",__FUNCTION__,u8_CurBtA2dpIsSupport);
	if(u8_CurBtA2dpIsSupport == 0x01)
	{
		if(pageId == PAGE_BLUETOOTH_NO_A2DP)
		{
			ToJumpPage = PAGE_BLUETOOTH_A2DP;
		}
	}
	else
	{
		if(pageId == PAGE_BLUETOOTH_A2DP)
		{
			ToJumpPage = PAGE_BLUETOOTH_NO_A2DP;
		}
	}

	return ToJumpPage;

}

u16 getCurFlyPage()
{
	u16 ToJumpPage = getCurPage();

	if(ToJumpPage != 0 && ToJumpPage != SYS_INVALID_PAGE)
	{
		if(!IsFlyPartyPage(ToJumpPage))
		{
			delete_pageFromTable();
			ToJumpPage = getCurFlyPage();
		}
	}
	return ToJumpPage;
}

void switch_Page(u16 pageId){
	LOGD("switch_Page:pageId:%x----curPage:%x",pageId,getCurPage());

	if(pageId == 0)
		pageId = PAGE_MENU;
	
	pthread_mutex_lock(&pLocalParam->mutex);
	
	u16 toJumpPage = checkPageToJump(pageId);
	toJumpPage = CurBtA2dpIsSupport_CheckBackKeyJumpPage(toJumpPage);
	LOGD("switch_Page toJumpPage:0x%x",toJumpPage);
	if((pageId == PAGE_MENU) && (PAGE_THIRD_PAGE != getCurPage()))
	{
		insert_pageToTable(0xff04);
	}
	else if(	(pageId != PAGE_FINISH_FLYAPP)&&
		(pageId != PAGE_FINISH_GPSAPP)&&
		(pageId != PAGE_FINISH_MEDIAAPP)&&
		//(pageId != SYS_BT_MAIN_PAGE)&&
		(toJumpPage != getCurPage())&&
	   	(toJumpPage != SYS_JUMP_PRE_PAGE) &&
		(toJumpPage != SYS_EQ_AUDIO_PRE_PAGE) &&
		(toJumpPage != SYS_THIRD_PAGE_BACK) &&
		(toJumpPage != SYS_SET_PRE_PAGE) &&
		(toJumpPage != SYS_AUX_TEMP_PAGE) &&
		(toJumpPage != SYS_BT_MUSIC_PAGE)&&
		(toJumpPage != SYS_DVD_PAGE)&&
		(toJumpPage != SYS_DVR_PAGE)&&
		(toJumpPage != SYS_BACK_PAGE)&&
		(toJumpPage != PAGE_MENU)&&
		(toJumpPage != PAGE_FINISH_FLYAPP)&&
		(toJumpPage != PAGE_FINISH_GPSAPP)&&
		(toJumpPage != SYS_SETUP_PERSONALIZATION_PRE_PAGE)&&
		(toJumpPage != SYS_SETUP_COMFORTABLE_CONVERIENT_PRE_PAGE)&&
		(toJumpPage != SYS_BT_MAIN_PAGE)&&
		(toJumpPage != PAGE_FINISH_MEDIAAPP)){
			insert_pageToTable(toJumpPage);
	}
	
	jumpToPage(toJumpPage);
	appToSys_Setup_PowerVol_Bar_Jump_set(pLocalParam->u8_Sys_StartupVol);	
	pthread_mutex_unlock(&pLocalParam->mutex);
}



// DVD->RADIO->MEDIA->BT->IPOD->AUX->TV
void anyModuleToSysModule_Switch_Module(char cFromModule) //Switch Module
{
	GetNextModule(cFromModule);
}

//Switch Module, Page ,Pre Page
void anyModuleToSysModue_Dispatch_Msg(moduleid_t sendModuleId,char *pBuf, int nLen)
{
	char cCmdType = pBuf[0];
	LOGD("anyModuleToSysModue_Dispatch_Msg---0x%x %x %x",cCmdType,pBuf[1],pBuf[2]);
	switch(cCmdType)
	{
	    case 0x30:
	    	if(sendModuleId == MODULE_ID_SYSTEM)
				SystemMoudule_Process_AccOn();
           break;
	    case 0x31:
	    	if(sendModuleId == MODULE_ID_SYSTEM)
    			SystemModule_Process_AccOff();
		   break;
		case 0x81://Switch Module
			{
				char cModuleID = pBuf[1];
				anyModuleToSysModule_Switch_Module(cModuleID);
			}
			break;
		case 0x82: //Switch Page
			{
				short PageID = 0;
				memcpy(&PageID, &pBuf[1],2);
				LOGD("anyModuleToSysModue_Dispatch_Msg---PageID:0x%x",PageID);
				if((u16)PageID == 0xE000)
				{
					switch(getCurPage())
					{
						case PAGE_BACK_VIDEO:
						case PAGE_BACK_NOVIDEO:
						case PAGE_BACK_RADAR:
						case PAGE_BACK_FULL_VIDEO:
						case PAGE_BACK_FULL_VIDEO_CONTROL:
							break;
						default:
							System_notifyApp_OtaJumpPage(0x01);
							break;
					}
				}
				else
				{
					switch_Page(PageID);
				}
			}
			break;
		case 0x83: //Pre Page
			{				
			    if((sendModuleId==MODULE_ID_BACK) && pLocalParam->b_hal_radar)
			    {
			     		switch_Page(PAGE_BACK_NOVIDEO);
					if(pLocalParam->nScreenSwitchStatus == 0x00)
						systemToHal_SetScreenOnOrOff(0x01);
				}
			    else
			    {
					pLocalParam->b_back=true;
					anyModuleToSysModule_Switch_PrePage();
					pLocalParam->b_back=false;
				}
			}
			break;
	}
}

/*
u8 isDNVPage(void)
{
	u8  isDNVpage = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_DNV, FLY_DNV_PARAM_IS_DNV_PAGE, (u8*)&isDNVpage, &len);

	LOGD("[%s] isDNVpage = [0x%x]", __FUNCTION__, isDNVpage);

	return isDNVpage;
}
*/

bool isDNVpage(u16 pageId)
{
	bool bRet = false;

	if (pageId == PAGE_DNV_VIEW ||
	    pageId == PAGE_DNV_PLAY ||
	    pageId == PAGE_DNV_PAUSE ||
	    pageId == PAGE_DNV_MENU ||
	    pageId == PAGE_DNV_TIP ||
	    pageId == PAGE_DNV_SOFTWARE_VERSION ||
	    pageId == PAGE_DNV_VIEW_BACK_BROUND ||
	    pageId == PAGE_DNV_EMPTY_BLACK_PAGE)
		bRet = true;
	
	LOGD("[%s] %s", __FUNCTION__, bRet ? "yes" : "no");

	return bRet;
}

static u16 IsBrakeCarDetect_Switch_PrePage(u16 prePageId)
{
	switch(prePageId)
	{
		case PAGE_DVD_VIDEO://DVD
		case PAGE_DVD_VIDEO_SET:
		case PAGE_DVD_VIDEO_CONTROL:
			return PAGE_DVD_MAIN;
		break;
		case PAGE_TV_VIDEO://TV
		case PAGE_TV_VIDEO_CONTROL:
		case PAGE_TV_VIDEO_SET:
		case PAGE_TV_NO_VIDEO:
		case PAGE_AUX_VIDEO://AUX
		case PAGE_AUX_VIDEO_CONTROL:
		case PAGE_AUX_VIDEO_SET:
		 	return PAGE_MENU;
		break;
	}

	return 0;
}

void anyModuleToSysModule_Switch_PrePage() //Switch Pre Page
{
	u16 CurPage = getCurPage();
	u16 PrePage = getPrePage();
	
	if (isDNVpage(CurPage))
	{
		setToDNVbackKey();
		return;
	}
	else 
	{
		if (isDNVpage(PrePage))
			{
				setToDNVGoInto();
				return;
			}
	}

	u16 readyToJumpPage = 0;
	
	
    
	//////////////add 2013-4-10///////////////////
	if(PrePage == PAGE_BLACK)
	{
		if(CurPage != PAGE_BACK_VIDEO)
			systemToHal_SetScreenOnOrOff(0x01);
	}
	/////////////////////////////////////////////
	
	if(PrePage == PAGE_THIRD_PAGE || PrePage == PAGE_GPS_PAGE)
	{
			if(IsFlyPartyPage(CurPage))
			{
				//if(CurPage == PAGE_MATCHING_MODELS){
				//	delete_pageFromTable();
				//}

				switch(CurPage)
				{
					case PAGE_MATCHING_MODELS:
					case PAGE_BACK_VIDEO:
					case PAGE_BLUETOOTH_MAIN:
						delete_pageFromTable();
					break;
				}
				
				readyToJumpPage = PAGE_FINISH_FLYAPP;
			}
			else
			{
			   switch(CurPage)
			   {
					case PAGE_MEDIA:
					readyToJumpPage = PAGE_FINISH_MEDIAAPP;
					break;
					case PAGE_GPS_PAGE:
					readyToJumpPage = PAGE_FINISH_GPSAPP;
					break;
			   }
			}
    }
	else if(CurPage>=PAGE_SETUP_BEGIN && CurPage<=PAGE_SETUP_END || CurPage == PAGE_SYSTEM_SET_COMMON_SECOND_PAGE)
	{
		readyToJumpPage = SYS_SET_PRE_PAGE;
	}
	else if(CurPage == PAGE_EQ || CurPage == PAGE_SOUND  || CurPage == PAGE_AUDIO_SET_BOX)
	{
		readyToJumpPage = SYS_EQ_AUDIO_PRE_PAGE;
	}
	else if(CurPage == PAGE_GOLF_SETUP_PERSONALIZATION_1 || CurPage == PAGE_GOLF_SETUP_PERSONALIZATION_2
			|| CurPage == PAGE_TRAVEL_INFORMATION || CurPage == PAGE_BLUE_SKIN_CAR_SETUP || CurPage == PAGE_BLUE_SKIN_CAR_DRIVING_DATA
			|| CurPage == PAGE_BLUE_SKIN_CAR_MAINTAIN || CurPage == PAGE_BLUE_SKIN_CAR_TOYOTA_HISTORY_RECORD
			|| CurPage == PAGE_BLUE_SKIN_CAR_HIGHLANDER_SETUP || CurPage == PAGE_BLUE_SKIN_CAR_HIGHLANDER_PARKING)
	{
		readyToJumpPage = SYS_SETUP_PERSONALIZATION_PRE_PAGE;
	}
	else if(CurPage == PAGE_TRAVEL_INFORMATION_CAR_SET1 || CurPage == PAGE_TRAVEL_INFORMATION_COMFORTABLE_CONVENIENT_SET)
	{
		readyToJumpPage = SYS_SETUP_COMFORTABLE_CONVERIENT_PRE_PAGE;
	}
	else if(CurPage==PAGE_BLUETOOTH_A2DP || CurPage == PAGE_BLUETOOTH_NO_A2DP)
	{
		readyToJumpPage = SYS_BT_MUSIC_PAGE;
	}
	else if(CurPage == PAGE_DVD_OPEN || CurPage == PAGE_DVD_VIDEO_CONTROL
		    || CurPage == PAGE_DVD_TRACKLIST || CurPage == PAGE_DVD_FOLDER)
	{
		readyToJumpPage = SYS_DVD_PAGE;
	}
	else if(CurPage == PAGE_DRIVING_RECORD_MENU || CurPage == PAGE_DRIVING_RECORD_TIME_SET || CurPage == PAGE_DRIVING_RECORD_VIDEO
			|| CurPage == PAGE_DRIVING_RECORD_SET || CurPage == PAGE_DRIVING_RECORD_PALY || CurPage == PAGE_DRIVING_RECORD_NO_SIGN
			|| 	CurPage == PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD || CurPage == PAGE_DRIVING_CHANGHE_DVR_SET_OSD)
	{
		readyToJumpPage = SYS_DVR_PAGE;
	}
	else if(CurPage == PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_EGLISH ||CurPage==PAGE_BLUETOOTH_MOBILE_RECORD || 
		CurPage == PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME || CurPage == PAGE_BLUETOOTH_AUDIOVOX_PAIR_SETTING)
	{
		readyToJumpPage = SYS_BT_MAIN_PAGE;
	}
	else if(CurPage == PAGE_BLUETOOTH_MAIN)
	{
		if(pLocalParam->systemSkinType == 768)
			readyToJumpPage = SYS_BT_MAIN_PAGE;
		else
			readyToJumpPage = SYS_JUMP_PRE_PAGE;
	}

	else if( CurPage == PAGE_AIRCONDITION_SET || CurPage == PAGE_AIRCONDITION)
	{
		readyToJumpPage = SYS_BT_MAIN_PAGE;
	}
	else if(CurPage == PAGE_PARALLEL_PARK_PAGE || CurPage == PAGE_PERPENDICULAR_PARK_PAGE || CurPage == PAGE_PARK_OUT_ASSIST_PAGE)
	{
		readyToJumpPage = SYS_EXTCAR_PARKING_ASSIST_PAGE;
	}
	else if(CurPage == PAGE_MULTI_CONTOURED_SEATS_ADJUST || CurPage == PAGE_MULTI_CONTOURED_SEATS_MASSAGE)
	{
		readyToJumpPage = SYS_EXTCAR_MCS_PAGE;
	}
	else 
	{
		readyToJumpPage = SYS_JUMP_PRE_PAGE;
	}
	
	if(judgmentReturnHomePage(CurPage))
		readyToJumpPage = PAGE_MENU;
		
	if(!IsCanSwitchVideoPage_WhenTheBrakeDownTime(pLocalParam->cBreakCarEnable,pLocalParam->b_Sys_BrakeCarStatus)){
		LOGD("[%s] BreakCar:(%d,%d)",__FUNCTION__,pLocalParam->cBreakCarEnable,pLocalParam->b_Sys_BrakeCarStatus);
		LOGD("[%s] PrePage:%x",__FUNCTION__,PrePage);
		u16 temPageID = IsBrakeCarDetect_Switch_PrePage(PrePage);
		if(temPageID != 0)
		{
			readyToJumpPage = temPageID;
			System_notifyApp_DisplayBrakecarPromtBox(1);
		}
	}
    LOGD("anyModuleToSysModule_Switch_PrePage---readyToJumpPage:%x",readyToJumpPage);
	switch_Page(readyToJumpPage);
	
}

u8 SystemModule_InquiryCurModuleID()
{
	int u8_CurSoundMode = 0;
	u8 nLen = 0;
	getOtherModuleParam(MODULE_ID_AUDIOVIDEO,0x01,(u8*)&u8_CurSoundMode,&nLen);
	static u8 mapArray[][2] = {
			{CHANNEL_DVD_CTRL, MODULE_ID_DVD},
			{CHANNEL_DVD_VIDEO, MODULE_ID_DVD},
			{CHANNEL_RADIO, MODULE_ID_RADIO},
			{CHANNEL_AUX_CTRL, MODULE_ID_AUX},
			{CHANNEL_AUX_VIDEO, MODULE_ID_AUX},
			{CHANNEL_IPOD_CTRL, MODULE_ID_IPOD},
			{CHANNEL_IPOD_VIDEO, MODULE_ID_IPOD},
			{CHANNEL_MP3, MODULE_ID_MEDIA},
			{CHANNEL_TV_CTRL, MODULE_ID_TV},
			{CHANNEL_TV_VIDEO, MODULE_ID_TV}
		};

	int i=0;
	for(i=0; i<(int)dim(mapArray); i++)
	{
		if(u8_CurSoundMode == mapArray[i][0])
			return mapArray[i][1];
	}
	return mapArray[0][1];
}

void KeyModuleToSysModule_Dispatch_Msg(char *pBuf, int nLen)
{
   	u8 u8_KeyParam = pBuf[1];
   	u8 cmd = pBuf[2];

	LOGD("u8_KeyParam:0x%x",u8_KeyParam);
	 u16 curPage=getCurPage();
	if(pBuf[0] != 0x00)
		return;

	u8 bIsBackCarRadar = 0;
	u8 bIsBackCarRadarLen = 0;
	getOtherModuleParam(MODULE_ID_BACK, BACK_CAR_RADAR_STATUS, &bIsBackCarRadar, &bIsBackCarRadarLen);
	if(bIsBackCarRadar && curPage== PAGE_BACK_NOVIDEO)
	{
		if(u8_KeyParam != 0xF0 && u8_KeyParam !=0xF2){
			anyModuleToSysModule_Switch_PrePage();
		}
		return;
	}

	if(pLocalParam->nScreenSwitchStatus == 0x00)
	{
     		systemToHal_SetScreenOnOrOff(0x01);
	  	return;
	}

	switch(u8_KeyParam)
	{
		case SYSTEM_KEY_PARAM_SETUP:
			SystemModule_Process_KeyParam_Setup();
			break;
		case SYSTEM_KEY_PARAM_DIM:
			SystemModule_Process_KeyParam_Dim();
			break;
		case SYSTEM_KEY_PARAM_TUNEPRESS:
			SystemModule_Process_KeyParam_TunePress();
			break;
		case SYSTEM_KEY_PARAM_TUNEPRESSLONG:
			//SystemModule_Process_KeyParam_TunePressLong();
			break;
		case 0x03://AV_MP3 key
            		SystemModule_Process_KeyParam_AV();
			break;	
		case 0x14:
			SystemModule_Process_KeyParam_NIFO();
			break;
		case 0x01:/*G8II use the new stand-by mode.(LPC to Module)*/
			//SystemModule_FromKeyParam_KEYVAL_SLEEP_NewStandbyMode();
			SystemModule_FromKeyParam_KEYVAL_SLEEP();
			break;
		case 0x02:/*���ܷ���Զ�̿���*/
			SystemModule_FromKeyParam_SmartFan_Telecontrol(cmd);
			break;
		case 0x04:/*LCD����Զ�̿���*/
			SystemModule_FromKeyParam_LCD_Telecontrol(cmd);
			break;
		case 0x05:
		    SystemModule_FromKeyParam_FanMode_PerformanceSwitch(cmd);
		    break;
		case 0x06:
		    SystemModule_FromKeyParam_AntotoItsOpen(cmd);
		    break;
		case 0x10:	// NAVI key
			setPanelKeyToAndroid(0x00);
			break;
		case 0x11:	// DEST key
			setPanelKeyToAndroid(0x01);
			break;
		case 0x12:	// LOCAL key
			setPanelKeyToAndroid(0x02);
			break;
		case 0x4d:
		    if(pLocalParam->u8_Sys_CurLcdLight != 0)
				systemToHal_SetScreenOnOrOff(0x00);
		   //SystemModule_brightLCD(0);
		    break;
		case SYSTEM_KEY_PARAM_CUSTOM_APK_1:
		case SYSTEM_KEY_PARAM_CUSTOM_APK_2:
		case SYSTEM_KEY_PARAM_CUSTOM_APK_3:
			systemToApp_Open_Custom_Apk(u8_KeyParam - SYSTEM_KEY_PARAM_CUSTOM_APK_1);
			break;
		default:break;
	}
}

void SystemModule_Process_KeyParam_Setup()
{
	u16 u16_CurPageID = getCurPage();
	u16 u16_PrePageID = getPrePage();

	short PageBeginID =  CONTROLID_SETUP_JUMPPAGE_ONE >> 8;
	short PageEndID = (short)((CONTROLID_SETUP_JUMPPAGE_END >>8) & 0xFFFF);

	if(u16_CurPageID >= PageBeginID && u16_CurPageID <= PageEndID)
		anyModuleToSysModule_Switch_PrePage();
	else
		switch_Page(PAGE_SETUP_BEGIN);
}

void SystemModule_Process_KeyParam_Dim()
{
	unsigned char ucLCDBrightness = pLocalParam->u8_Sys_CurLcdLight;

	LOGD("SystemModule_Process_KeyParam_Dim:u8_Sys_CurLcdLight:0x%x",pLocalParam->u8_Sys_CurLcdLight);

	ucLCDBrightness++;
	if (ucLCDBrightness == 4)
		ucLCDBrightness = 0;

	systemToHal_SetLCDBrightness(ucLCDBrightness);
}

void SystemModule_Process_KeyParam_TunePress()
{
	if(getCurPage() == PAGE_SOUND)
		anyModuleToSysModule_Switch_PrePage();
	else
		switch_Page(PAGE_SOUND);
}

void SystemModule_Process_KeyParam_TunePressLong()
{
	if(getCurPage() == PAGE_TPMS)
		anyModuleToSysModule_Switch_PrePage();
	else
		switch_Page(PAGE_TPMS);
}

void SystemModule_Process_KeyParam_AV()
{
	if(getCurPage() == PAGE_THIRD_PAGE)
		systemToModule_NotifySystem_SwithModule(MODULE_ID_MEDIA);
	else
		switch_Page(PAGE_THIRD_PAGE);
}

void SystemModule_Process_KeyParam_NIFO()
{
	switch_Page(PAGE_COPYRIGHT);
}


void SystemModule_FromKeyParam_KEYVAL_SLEEP_NewStandbyMode()
{
	static bool bKeyVal_Sleep_Status=true;
	LOGD("bKeyVal_Sleep_Status:%x",bKeyVal_Sleep_Status);
	if(bKeyVal_Sleep_Status){
		bKeyVal_Sleep_Status=false;
		systemToModule_NotifyServiceModule_StandbyState(0x01);
	}
	else
	{
		bKeyVal_Sleep_Status=true;
		systemToModule_NotifyServiceModule_StandbyState(0x00);
	}
}

void SystemModule_FromKeyParam_KEYVAL_SLEEP()
{
	static bool bKeyVal_Sleep_Status=true;
	LOGD("bKeyVal_Sleep_Status:%x",bKeyVal_Sleep_Status);
	if(bKeyVal_Sleep_Status){
		bKeyVal_Sleep_Status=false;
		halToSystem_StandbyStatus(0x01,0x00);
		systemToModule_NotifyBtModule_aboutStandby(0x01);
		systemToModule_NotifySyncModule_aboutFastStandy_SyncMediaPlay(0x01);
	}
	else
	{
		bKeyVal_Sleep_Status=true;
		halToSystem_StandbyStatus(0x00,0x00);
		systemToModule_NotifyBtModule_aboutStandby(0x00);
		systemToModule_NotifySyncModule_aboutFastStandy_SyncMediaPlay(0x00);
	}
}


void SystemModule_FromKeyParam_SmartFan_Telecontrol(u8 cmd)
{
	if (cmd == 0x00)
	{
		pLocalParam->eCurFanMode = eFanModeShutDown;
	}
	else if (cmd == 0x01)
	{
		pLocalParam->eCurFanMode = eFanModeFitAuto;
	}
	else if(cmd == 0x02)
	{
	    pLocalParam->eCurFanMode = eFanModeShutOpen;
	}
	else if(cmd == 0x03)
	{
	    pLocalParam->eCurFanMode = eFanModeHighPerformance;
	}
	else if(cmd == 0x04)
	{
	    pLocalParam->eCurFanMode = eFanModeLowPower;
	}

    SystemModule_SetMachineInit_FanState();
    SystemModule_SetMachineInit_CPUState();
    
}

void SystemModule_FromKeyParam_FanMode_PerformanceSwitch(u8 cmd)
{
    switch(cmd)
    {
        case 0://low
        	 pLocalParam->eCurFanMode=eFanModeLowPower;
        break;
        case 1://mid
        	 pLocalParam->eCurFanMode=eFanModeFitAuto;
        break;
        case 2://high
        	 pLocalParam->eCurFanMode=eFanModeHighPerformance;
        break;
        default:break;
    }
    SystemModule_SetMachineInit_FanState();
    SystemModule_SetMachineInit_CPUState();
}

void SystemModule_FromKeyParam_AntotoItsOpen(u8 cmd)
{
    if(cmd == 0x01)
    {//antoto open,high performance ,fan high mode
    	 pLocalParam->eCurFanMode = eFanModeHighPerformance;
    }
    else
    {//antoto close,pre-performance,fan previous mode

    	 pLocalParam->eCurFanMode = pLocalParam->ePreFanMode;
    }
    SystemModule_SetMachineInit_FanState();
    SystemModule_SetMachineInit_CPUState();
}

void SystemModule_FromKeyParam_LCD_Telecontrol(u8 cmd)
{
	if(cmd == 0x00)
		systemToHal_SetScreenOnOrOff(0x00);
	else
		SystemModule_brightLCD(cmd);
}



//BackCar Disatch Msg
void BackCarModuleToSysModule_Dispatch_Msg(char *pBuf, int nLen)
{
	switch(pBuf[0])
	{
		case 0x01:
		{
			if(pBuf[1] == 0x01)
			{
				System_notifyApp_EyeProtectionModeSwitch((u8)PROTICTION_MODE_REVERSING);
			}
			else if(pBuf[1] == 0x00)
			{
				if(pLocalParam->b_Sys_DayNight == 0x00)
				{
					System_notifyApp_EyeProtectionModeSwitch((u8)PROTICTION_MODE_DAY);
				}
				else if(pLocalParam->b_Sys_DayNight == 0x01)
				{
					System_notifyApp_EyeProtectionModeSwitch((u8)PROTICTION_MODE_NIGHT);
				}
			}
		}
		break;
		case 0xf8:
		{
			 // jing  ֱ��ʹ��jumpPage����0705��UI��������system��ҳ����?������ӵ�ҳ���2013-7-24
			jumpPage(0x705); 
		}
		break;
		case 0x60:
			systemToHal_BackcarVisionAngle(pBuf[1]);
		break;
		case 0x70:
			DisplayUI_aboutBackCar_Line_Type(pBuf[1]);
			break;
		default:
		break;
	}

}


void ExtcarModuleToSysModule_Dispatch_Msg(u8 *pBuf, int nLen)
{
	LOGD("ExtcarModuleToSysModule_Dispatch_Msg pBuf[0]:%x,pBuf[1]:%x",pBuf[0],pBuf[1]);
	switch(pBuf[0])
	{
		case 0x00:
			appToSys_Setup_CarinfoVoice(pBuf[1]);
		break;
		case 0x02:
			g_clsSystem.sendToFlyJniSdkSystemFrontCameraApp(pBuf[1]);
		break;
		case 0x80:
		{
			switch(pBuf[1])
				{	
					case 0x00:
						RadarMsgDispose(pBuf+2,nLen-2);
						break;
					case 0x01:
						//RadarInfo(pBuf[2]);
						break;
				}
			
		}
		break;
		case 0x60:
		{
			if(pBuf[1] > 0){
				halToSystem_MagnitudeOfVoltage(pBuf[1]);
			}
		}
		break;
		case 0xb1://Prado
		{
			switch(pBuf[1])
			{
				case 0x00:
				{
					pLocalParam->bPrado_RadarSwitchKeyStatus = pBuf[2];
					LOGD("pLocalParam->bPrado_RadarSwitchKeyStatus:%d",pLocalParam->bPrado_RadarSwitchKeyStatus);
					break;
				}
				case 0x01:
				{
					pLocalParam->bPrado_RadarSwitchUiStatus = pBuf[2];
					LOGD("pLocalParam->bPrado_RadarSwitchUiStatus:%d",pLocalParam->bPrado_RadarSwitchUiStatus);
					break;
				}
				default:break;
			}
		}
		break;
		case 0xf0:
			analysePublicCarInfoToSystemSet(pBuf+1,nLen -1);
			break;
		default:break;
	}
}

void ExternalCtrlModuleToSysModule_Dispatch_Msg(u8 *pBuf, int nLen)
{
	switch(pBuf[0])
	{
		case 0x00:
		{
			if(pBuf[1] == 0)
			{
				ImprovingtheRecognitionRateOfMic_aboutFord(0x00);
			}
			else{
				ImprovingtheRecognitionRateOfMic_aboutFord(0x01);
			}
		}
		break;
		case 0x01:
		{
			if(pBuf[1]==0x01)
			{
				systemToModule_NotifySystem_JumpPage(PAGE_SETUP_BEGIN);
			}
			else
			{
				systemToModule_NotifySystem_JumpPrePage();
			}
		}
		break;
		case 0x02:
		{
			if(pBuf[1] == 0x01)
			{
				LOGD("systemToHal_SetDenoiseMode~~pBuf[2]:0x%x",pBuf[2]);
				systemToHal_SetDenoiseMode(pBuf[2]);
			}
		}
		break;
	}
}

void moduleToSystem_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;
    analyseAppMessage(param+1,len-1);   
}

void moduleToSystem_FromAudiovideo(u8 *param, int len)
{
	LOGD("[%s] param[0]:%x param[1]:%x %x %x %x",__FUNCTION__,param[0],param[1],param[2],param[3],param[4]);
	switch(param[0])
	{
		case 0x00:
			if(param[1] == 0x01){
				SystemModule_NavigationBootingRunMod();
			}
			break;
		case 0x01:
			NavigationBootingRunMod(param[1]);
			break;
		default:break;
	}
}

void moduleToSystem_FromRemoteOnline(u8 *param, int len)
{
	switch(param[0])
	{
		case 0x01:
			systemToHal_Notify_RemoteOnline_VoltageProtection(0x01);
		break;
		default:break;
	}
}

void moduleToSystem_FromDVR(u8 *param, int len)
{
	switch(param[0])
	{
		case 0x00:
		{
			//pLocalParam->uBackCarSetCvbsOrUSB = param[1];
			//DisplaySysToUI_aboutBackCarProtocolCVBSorUSB(param[1]);
		}
		break;
		default:break;
	}
}

void OsdModuleToSysModule_Dispatch_Msg(u8 *pBuf, int nLen)
{
//	LOGD("OsdModuleToSysModule_Dispatch_Msg:pLocalParam->DebugSwitch=%d",pLocalParam->DebugSwitch);
	if(pLocalParam->DebugSwitch == 0 || pLocalParam->osdDebugSwith == 0)
		return ;
	
	u8 uDebugBuf[256]={0};
	switch(pBuf[0])
	{
	}
		systemToModule_NotifyOSD_OSDDebug_Info(pBuf, nLen);
}


void RadarInfo(u8 param)
{

	systemToModule_NotifyBackModule_BackCarRadarStatus(param);
	LOGI("==========>halToSystem_Radar_Info:buf---0x%x",param);

	/*u16 curPage = pLocalParam->u16_Sys_CurPage;
	if((curPage == PAGE_BACK_NOVIDEO) || (curPage == PAGE_BACK_VIDEO))
		return ;*/
	 pLocalParam->b_hal_radar=param;
	SendBackcarInfoAndDiaInStateToOSDDebug();
	if(param==1)
	{
		if(getCurPage() != PAGE_BACK_NOVIDEO && getCurPage() != PAGE_BACK_VIDEO && 
			getCurPage() != PAGE_BACK_FULL_VIDEO && getCurPage() != PAGE_BACK_FULL_VIDEO_CONTROL)//������ʱ������ҳ
			{
			    int radarDataLen=sizeof(pLocalParam->m_cRadarData);
			    int radarDataUILen=sizeof(pLocalParam->m_cRadarDataUI);

			    memset(pLocalParam->m_cRadarData,0xff,radarDataLen);
			    memset(pLocalParam->m_cRadarDataUI,0xff,radarDataUILen);


			    switch_Page(PAGE_BACK_NOVIDEO);
			}
	}
	else if(param==0)
	{
	   if(getCurPage() != PAGE_BACK_NOVIDEO)
             return;
       anyModuleToSysModule_Switch_PrePage();
	}

}


void RadarMsgDispose(u8 *pBuf, int nLen)
{
	LOGD("RadarMsgDispose pBuf[0]=%d,%d,%d,%d,%d,",pBuf[0],pBuf[1],pBuf[2],pBuf[3],pBuf[4]);
	switch(pBuf[0])
	{
		case 0x00:
		{
			halToSystem_Radar_Info_F(pBuf+1);
			halToSystem_Radar_Info_FF(pBuf+1);
			g_clsSystem.sendToFlyJniSdkRadarDate(0x00,pBuf+1,nLen-1);
		}
		break;
		case 0x01:
		{
			halToSystem_Radar_Info_B(pBuf+1);
			halToSystem_Radar_Info_BB(pBuf+1);
			g_clsSystem.sendToFlyJniSdkRadarDate(0x01,pBuf+1,nLen-1);
		}
		break;
		case 0x02:
		{
			halToSystem_Radar_Info_L(pBuf+1);
			halToSystem_Radar_Info_LL(pBuf+1);
		}
		break;
		case 0x03:
			halToSystem_Radar_Info_R(pBuf+1);
			halToSystem_Radar_Info_RR(pBuf+1);
			break;
		default:break;
	}
}

void BlueModuleToSysModule_Dispatch_Msg(u8 *pBuf, int nLen)
{
	u8 u8_Cmd = pBuf[0];
	switch(u8_Cmd)
	{
		case 0x00:
		{
			if(pBuf[1] == 0)
			{
				ImprovingtheRecognitionRateOfMic_aboutFord(0x00);
			}
			else{
				ImprovingtheRecognitionRateOfMic_aboutFord(0x01);
			}
		}
		break;
		case 0x70:
		{
			LOGD("BlueModuleToSysModule_Dispatch_Msg");
			changePage(top,top-1);
			displayPageTable();
		}
		break;
		default:break;
	}
}

//Center Dispatch Msg
void CenterModuleToSysModule_Dispatch_Msg(char *pBuf, int nLen)
{
	u8 u8_Cmd = pBuf[0];
	u16 curPage = getCurPage();

	LOGD("CenterModuleToSysModule_Dispatch_Msg  u8_Cmd %x ",u8_Cmd);
	switch(u8_Cmd)
	{
		case 0x90:
			DisplayAllBarCode();
			break;
		case 0x84: //Back Page
			  anyModuleToSysModule_Switch_PrePage(); //Switch Pre Page
			 break;
		case 0x85: //Enter Third Page
			{
				if(curPage == PAGE_THIRD_PAGE)
					return;
				pLocalParam->b_Sys_ThirdPageMark = true;
				u16 ToPage = PAGE_THIRD_PAGE;
				switch_Page(ToPage);
			}
			 break;
		case 0x86: //Enter Home Page
			 {
				if(curPage == PAGE_MENU)
					return;
				pLocalParam->b_Sys_HomePageMark = true;
				switch_Page(SYS_ENTER_HOME_PAGE);
			 }
			break;
		case 0x87:	// Enter GPS Page
			{
				if(curPage == PAGE_GPS_PAGE)
					return;
				pLocalParam->b_Sys_GpsPageMark = true;
				u16 ToPage = PAGE_GPS_PAGE;

				switch_Page(ToPage);
			}
			break;
		case 0x89://close third page  2012-06-06
			{
				 u16 buf=(u16)((pBuf[1]<<8)&0xff00)+pBuf[2];
				 pLocalParam->u8_Sys_tempPage=buf;
			}
			break;
		case 0xF0:	// Debug key panel type
			systemToHal_SetDebugKeyPanelType(pBuf[1]);
			break;
		case 0xF2:
		{
		    if(pBuf[1] == 0){
		        pLocalParam->bSysStatusBarSet = true;
				systemToHal_SetScreenOnOrOff(0x00);
		    }
			else
				SystemModule_brightLCD(pBuf[1]);
		}
			break;
		case 0xF3:
		    if(pLocalParam->u8_Sys_CurLcdLight!=0)
				systemToHal_SetScreenOnOrOff(0x00);
			//SystemModule_brightLCD(0);
			break;
		case 0x00:
			if(pBuf[1] == 0x01){
				systemToHal_SetScreenOnOrOff(0x01);
		    }
			break;
		case 0x38:
			if(pBuf[1] == 1){
				pLocalParam->b_3G_DialIn = true;
			}
			else{
			    pLocalParam->b_3G_DialIn = false;
			}

			if(pLocalParam->nScreenSwitchStatus == 0 && getCurPage() == PAGE_BLACK)
			{
				systemToHal_SetScreenOnOrOff(0x01);
			}
			
			systemToHal_NotifySIMPhoneStatus(pBuf[1]);
			SendBackcarInfoAndDiaInStateToOSDDebug();
			break;

		case 0x02:
			systemToHal_Notify_PingLoop_NewStructure(pBuf[1]);
			systemToModule_NotifySyncModule_aboutFlySystem_OperatingNormal(pBuf[1]);
			break;
		case 0x03:
			SystemModule_TimeFormat(pBuf[1]);
			break;
		default:
			break;
	}
}

void DisplayAllBarCode()
{
	if(pLocalParam->b_Barcode == false) return;

	u8 buf[1024];

	//read_AllBarCode((char*)buf, 1024);

	int num = (char)buf[16];

	int i;
	for(i = 0; i < num; i++)
		setOneBarcode(&buf[64*i+17], 64);
}

void SystemToSpecificModuleFromAudioVideoChannel(u16 u16_LeavePage,u16 u16_EnterPage){
	LOGD("111");
	pthread_mutex_lock(&pLocalParam->mutex_notifyPageChange);

	systemToModule_NotifySomeModule_ChangePage(MODULE_ID_DNV,u16_LeavePage,u16_EnterPage,0);
	systemToModule_NotifySomeModule_ChangePage(MODULE_ID_OSD,u16_LeavePage,u16_EnterPage,0);
    systemToModule_NotifySomeModule_ChangePage(MODULE_ID_AUDIOVIDEO, u16_LeavePage,u16_EnterPage,0);
	systemToModule_NotifySomeModule_ChangePage(MODULE_ID_OSD,u16_LeavePage,u16_EnterPage,1);
	systemToModule_NotifySomeModule_ChangePage(MODULE_ID_SYNC,u16_LeavePage,u16_EnterPage,0);
	systemToModule_NotifySomeModule_ChangePage(MODULE_ID_EXTCAR,u16_LeavePage,u16_EnterPage,0);
	systemToModule_NotifySomeModule_ChangePage(MODULE_ID_BT,u16_LeavePage,u16_EnterPage,0);

	LOGD("222");
	u8 curModuleId = SystemModule_InquiryCurModuleID();
	LOGD("333");
	androidKeyMessageDeliverControllor(u16_EnterPage);
	LOGD("444");
	systemToModule_NotifySomeModule_ChangePage(curModuleId,u16_LeavePage,u16_EnterPage,0);
	LOGD("555");
	pthread_mutex_unlock(&pLocalParam->mutex_notifyPageChange);
}

/************zhq add backcar trigger type choise setting********************************************/

char Backcar_Trigger_Type(char cmap)
{
    map<char,char> mapArray;
	mapArray['1']=0;//Automatic
	mapArray['2']=1;//Protocol
	mapArray['3']=2;//Level
	return mapArray[cmap];
}
void Insert_TriggerTypeToTable(char cType)
{
   if(triggerhead1 < ntype)
    {
		triggerhead1++;
		LOGD("triggerhead1:%d",triggerhead1);
		BackCarTriggerType[triggerhead1] = cType;
	}
}

void TriggerTypedisplayTable()
{
    int i;
	LOGI("+++++=======================+++++");
	for(i = 0; i <= triggerhead1; i++){
		LOGI("+++++   ExternalDeviceTable[%d]: %d   +++++", i, BackCarTriggerType[i]);
	}
	LOGI("+++++=======================+++++");
}
void InitTriggerTypeTable()
{
    int i;
	for(i=0;i<dim(pLocalParam->uSystemBackcarTtiggerGroup);i++)
	{
		if(pLocalParam->uSystemBackcarTtiggerGroup[i]==0)
		{
		    LOGD("InitTriggerTypeTable");
			TriggerTypedisplayTable();
			break;

		}
		ntype++;
		LOGD("@@@@InitTriggerTypeTable:%c",pLocalParam->uSystemBackcarTtiggerGroup[i]);
		char RetTriggerType=Backcar_Trigger_Type(pLocalParam->uSystemBackcarTtiggerGroup[i]);
		LOGD("InitTriggerTypeTable------RetTriggerType:0x%x",RetTriggerType);
		Insert_TriggerTypeToTable(RetTriggerType);
	}
}

void systemToHal_setTriggerType()
{
	LOGD("[%s] pLocalParam->eSetupBackcarTriggerType:%x",__FUNCTION__,pLocalParam->eSetupBackcarTriggerType);
	if(pLocalParam->eSetupBackcarTriggerType == eSetupBackcarTriggerUnknow)
	{
		LOGD("[%s] BackCarTriggerType[0]:%x",__FUNCTION__,BackCarTriggerType[0]);
		systemToHal_SetBackcarTriggerType((E_SETUP_BACKCAR_TRIGGER)BackCarTriggerType[0]);
	}
	else
	{
		systemToHal_SetBackcarTriggerType((E_SETUP_BACKCAR_TRIGGER)pLocalParam->eSetupBackcarTriggerType);
	}
}

bool getCurTriggerTypeHead(int *nTop,char p)
{
	int i;
	for(i=0;i < 3;i++)
	{
		LOGD("[%s] i:%d",__FUNCTION__,i);
		if(p == BackCarTriggerType[i])
		{
			*nTop = i;
			return true;
		}
	}

	return false;
}
void SetLastTriggerType(char cType)
{

	int nCount = 0xff;
	if(getCurTriggerTypeHead(&nCount,cType))
	{
		LOGD("[%s] nCount:%d",__FUNCTION__,nCount);
		if(nCount == 0)
		{
			systemToHal_SetBackcarTriggerType((E_SETUP_BACKCAR_TRIGGER)BackCarTriggerType[triggerhead1]);
		}
		else
		{
			systemToHal_SetBackcarTriggerType((E_SETUP_BACKCAR_TRIGGER)BackCarTriggerType[nCount-1]);
		}
	}
}

void SetNextTriggerType(char cType)
{
  int nCount = 0xff;
  if(getCurTriggerTypeHead(&nCount,cType))
  {
  	  LOGD("[%s] nCount:%d",__FUNCTION__,nCount);
	  if(nCount == triggerhead1)
	  {
		  systemToHal_SetBackcarTriggerType((E_SETUP_BACKCAR_TRIGGER)BackCarTriggerType[0]);
	  }
	  else
	  {
		  systemToHal_SetBackcarTriggerType((E_SETUP_BACKCAR_TRIGGER)BackCarTriggerType[nCount+1]);
	  }
  }
}

void SystemModule_TimeFormat(u8 t)
{
	if(t == 0 || t == 1)
		pLocalParam->uSystemTimeFormat = t;
}

void analyseFormSdkMessage(u8 *param, int len)
{
	switch(param[0])
	{
		case 0x01:
		{
			if (param[1] == 0x01)
				systemToHal_SetScreenOnOrOff (0x00);
			else if (param[1] == 0x00) {
				systemToHal_SetScreenOnOrOff (0x01);
			}
		}
			break;
		case 0x02:
		{
			if(param[1] == 0x01||param[1] == 0x02||param[1] == 0x03)
				SystemModule_brightLCD(param[1]);

		}
			break;
		case 0x03:
			if(param[1] == 0x01)
				appToSys_Setup_MouseUp(CONTROLID_SETUP_JUMPPAGE_ONE);
			break;
		case 0x04:
		{
			if(param[1] == 0x00)
				g_clsSystem.sendToFlyJniSdkSystemBrightnessMessage(pLocalParam->u8_Sys_CurLcdLight);
			else if(param[1] == 0x01)
				g_clsSystem.sendToFlyJniSdkSystemBrightnessValueMessage(pLocalParam->cBrightness_RangeValue);
		}
			break;
		case 0x05:
		{
			if(param[1] == 0x01)
			{
				g_clsSystem.sendToFlyJniSdkRadarDate(0x00,pLocalParam->m_cRadarDataUI,4);
				g_clsSystem.sendToFlyJniSdkRadarDate(0x01,pLocalParam->m_cRadarDataUI+4,4);
			}
		}
			break;
		case 0x06:
			g_clsSystem.sdkToSystemJumpPage(param+1,len -1);
			break;
		case 0x07:
			SetDayAndNightMode(param[1]);
			break;
		case 0x08:
			systemToHal_SetScreenBrightnessSpecificValue(param[1]);
			break;
		case 0x09:
			g_clsSystem.sendToFlyJniSdkBackCarStatus(localParam.b_Sys_BackCarStatus);

			break;
		case 0x0a:
		{
			if(param[1] == 0x01)
				g_clsSystem.sendToFlyJniSdkCurPageID();
		}
			break;
		case 0x0b:
		{
			if(param[1] == 0x01)
				g_clsSystem.sendToFlyJniSdkSystemDayOrNightStatus(pLocalParam->curDayAndNightMode);
		}		
			break;
		case 0x0c:
		{
			if(param[1] == 0x01)
				g_clsSystem.sendToFlyJniSdkSystemAutoLightStatus(pLocalParam->uScreenBrightAutoSwtich);
		}
			break;
		case 0x0d:
		{
			if(param[1] == 0x01||param[1] == 0x00)
				systemToHal_AutoAdjustmentSwitchOfScreenBrightness(param[1]);
		}
			break;
		case 0x0e:
			g_clsSystem.analyseSdkSetLightAddOrRedValue(param+1,len-1);
			break;
		case 0xfe:
			systemToHal_SimulateKey(SYSTEMTOHAL_SIMKEY_RESET);
			break;
		default:break;
	}
}

void moduleToSystem_FromRadio(u8 *param, int len)
{
	switch(param[0])
	{
		case 0x01:
		{
			halToSystem_RadioConturyCode(param[1]);
		}
		break;
		default:break;
	}
}

void analysePublicCarInfoToSystemSet(u8 *p,u8 len)
{
	LOGD("[%s]   p[0]:%x  p[2]:%x",__FUNCTION__,p[0],p[2]);
	switch(p[0])
	{
		case 0x00://AmbientLed color set
			getAmbientLedColorValue(p[1]);
		break;
		case 0x01://AmbientLed brightness set
			getAmbientLedBrightnessValue(&p[1]);
		break;
		case 0x11:
			{
				if(p[1] == 0x00)
					showCurTempUnitType(p[2]);
				else if(p[1] == 0x05)
					showCurDistanceUnitType(p[2]);
			}
		break;
		case 0x12:
			{
				if(p[1] == 0x00)
				{
					pLocalParam->uCameraDelayTag = p[2];
					showCameraDelaySwitchStatus(p[2]);
				}	
			}
		break;
		case 0x16:
		{
			getExtcarPublicMultiContouredSeatsMessage(&p[1],len - 1);
		}
		break;
		default:break;
	}
}

void getAmbientLedColorValue(u8 param)
{
	DisplayUI_switch_AmbientLedColor_Ford(param);
	DisplayUI_AmbientLedColorTxt_Ford(param);
}


void getAmbientLedBrightnessValue(u8 *param)
{
	u16 MaxValue = param[0] + (param[1] << 8);
	u16 curValue = param[2] + (param[3] << 8);

	if(curValue > MaxValue)
		return;

	pLocalParam->fordAlmBrightnessMaxValue = MaxValue;

	if(curValue != 0)
	{
		DisplayUI_AmbientLedBrightnessEnable_Ford(true);
	}
	else
	{
		DisplayUI_AmbientLedBrightnessEnable_Ford(false);
		getAmbientLedColorValue(0);
	}
	
	Step_AmbientLedBrightnessScrollBar_Ford(MaxValue);
	DisplayUI_AmbientLedBrightnessValue_Ford(curValue);
	DisplayUI_AmbientLedBrightnessScrollBar_Ford(curValue);
}

void ImprovingtheRecognitionRateOfMic_aboutFord(u8 p)
{
    u8 uSpeechState = 0;
	u8 uSpeechStateLen = 0;
	getOtherModuleParam(MODULE_ID_EXTERNALCTRL,SPEECH_STATE,&uSpeechState,&uSpeechStateLen);

	u8 btPhoneStatus = 0;
	u8 btPhoneLen = 0;
	getOtherModuleParam(MODULE_ID_BT, BT_MOBILE_STATUS, (u8*)&btPhoneStatus, &btPhoneLen);

	LOGD("[%s] uSpeechState:%x btPhoneStatus:%x",__FUNCTION__,uSpeechState,btPhoneStatus);
	if(p == 0x01){//do
		systemToHal_NotifyMicUsingState(0x01);
	}
	else if(p == 0x00)//do not
	{
		if(btPhoneStatus == 0x00 && uSpeechState == 0x00)
			systemToHal_NotifyMicUsingState(0x00);
	}
}

void getExtcarPublicMultiContouredSeatsMessage(u8 *p,u8 len)
{
	LOGD("[MCS To Module]:%x %x %x",p[0],p[1],p[2]);
	switch(p[0])
	{
		case 0x00://Lower Lumbar Pressure Percentage
			SeatPressurePercentageLowerLumbar(p[1],p[2]);
			break;
		case 0x05://Middle Lumbar Pressure Percentage
			SeatPressurePercentageMiddleLumbar(p[1],p[2]);
			break;
		case 0x0A://Upper Lumbar Pressure Percentage
			SeatPressurePercentageUpperLumbar(p[1],p[2]);
			break;
		case 0x10://Lower Bolster Pressure Percentage
			SeatPressurePercentageLowerBolster(p[1],p[2]);
			break;
		case 0x15://Upper Bolster Pressure Percentage
			SeatPressurePercentageUpperBolster(p[1],p[2]);
			break;
		case 0x1A://Lumbar Massage Intensity
			SeatIntensityLumbarMassage(p[1],p[2]);
			break;
		case 0x20://Cushion Massage Intensity
			SeatIntensityCushionMassage(p[1],p[2]);
			break;
		case 0x25://Driver/Passager ActiveSeatControl
			SeatActiveSeatControlSelectMassage(p[1],p[2]);
			break;
		case 0x2a://Multi Contoured Seats Available
			SeatMultiCOntouredAvailableMassage(p[1]);
			break;
		default:break;
	}

	DeleteTimer(MCU_PAGE_TIMEOUT);
	if(getCurPage() == PAGE_MULTI_CONTOURED_SEATS_ADJUST || getCurPage() == PAGE_MULTI_CONTOURED_SEATS_MASSAGE)
	{
		SetTimer(TIMES_MCU_PAGE_TIMEOUT,1,MCU_PAGE_TIMEOUT);
	}
}

void SeatPressurePercentageUpperLumbar(u8 p1,u8 p2)
{
	pLocalParam->st_MCS[p1 - 1].uUL = p2;

	if(pLocalParam->uMCS_Available == 0x00)
		return;

	if(p1 != pLocalParam->selectSeatSide)
		return;

	setUpdateUI(0);
	UI_Display_Select(p1,p2);
	setUpdateUI(1);
}

void SeatPressurePercentageMiddleLumbar(u8 p1,u8 p2)
{
	pLocalParam->st_MCS[p1 - 1].uML = p2;

	if(pLocalParam->uMCS_Available == 0x00)
		return;

	if(p1 != pLocalParam->selectSeatSide)
		return;

	setUpdateUI(0);
	UI_Display_Select(p1,p2);
	setUpdateUI(1);

}

void SeatPressurePercentageLowerLumbar(u8 p1,u8 p2)
{
	pLocalParam->st_MCS[p1 - 1].uLL = p2;
	u8 side = pLocalParam->selectSeatSide;

	if(pLocalParam->uMCS_Available == 0x00)
		return;

	if(p1 != side)
		return;
	
	setUpdateUI(0);
	UI_Display_Select(p1,p2);
	setUpdateUI(1);
}

void SeatPressurePercentageUpperBolster(u8 p1,u8 p2)
{
	pLocalParam->st_MCS[p1 - 1].uUB = p2;
	u8 side = pLocalParam->selectSeatSide;

	if(pLocalParam->uMCS_Available == 0x00)
		return;

	if(p1 != side)
		return;

	setUpdateUI(0);
	UI_Display_Select(p1,p2);
	setUpdateUI(1);
}

void SeatPressurePercentageLowerBolster(u8 p1,u8 p2)
{
	pLocalParam->st_MCS[p1 - 1].uLB = p2;
	u8 side = pLocalParam->selectSeatSide;

	if(pLocalParam->uMCS_Available == 0x00)
		return;

	if(p1 != side)
		return;

	setUpdateUI(0);
	UI_Display_Select(p1,p2);
	setUpdateUI(1);
}

void SeatIntensityLumbarMassage(u8 p1,u8 p2)
{
	pLocalParam->st_MCS[p1 - 1].uLMI = p2;
	u8 side = pLocalParam->selectSeatSide;

	if(pLocalParam->uMCS_Available == 0x00)
		return;

	if(p1 != side)
		return;

	if(pLocalParam->st_MCS[side - 1].uChMk == 0x06){
		UI_Display_Massage_Passage_UpperLumbarSelectedState(1);
		UI_Display_Massage_Passage_LowerLumbarSelectedState(0);
	}
	else{
		UI_Display_Massage_Passage_UpperLumbarSelectedState(0);
	}
	
	UI_Display_Massage_Passage_UpperLumbarSet(p2);
	UI_Display_MassageIntensityLumbarAndCushion(p1);
}

void SeatIntensityCushionMassage(u8 p1,u8 p2)
{
	pLocalParam->st_MCS[p1 - 1].uCMI = p2;
	u8 side = pLocalParam->selectSeatSide;

	if(pLocalParam->uMCS_Available == 0x00)
		return;

	if(p1 != side)
		return;

	if(pLocalParam->st_MCS[side - 1].uChMk == 0x07){
		UI_Display_Massage_Passage_LowerLumbarSelectedState(1);
		UI_Display_Massage_Passage_UpperLumbarSelectedState(0);
	}
	else{
		UI_Display_Massage_Passage_LowerLumbarSelectedState(0);
	}
	
	UI_Display_Massage_Passage_LowerLumbarSet(p2);
	UI_Display_MassageIntensityLumbarAndCushion(p1);
}

void SeatSideMassage(u8 p)
{
	if(pLocalParam->uMCS_Available == 0x00)
		return;
	
	UI_Display_Select_Seats_Side(p);
}

void SeatActiveSeatControlSelectMassage(u8 p1,u8 p2)
{
	switch(p2)
	{
		case 0x00:
		break;
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
		{
			if(getCurPage() != PAGE_MULTI_CONTOURED_SEATS_ADJUST)
			{
				systemToModule_NotifySystem_JumpPage(PAGE_MULTI_CONTOURED_SEATS_ADJUST);

				if(pLocalParam->st_MCS[p1 - 1].uChMk == 0x06 || pLocalParam->st_MCS[p1 - 1].uChMk == 0x07)
				{
					UI_Display_MCS_MassageFunction_closing_PromptBox(1);
					SetTimer(TIMES_MCU_CLOSING_BOX,1,MCU_CLOSING_BOX);
				}
			}
		}
		break;
		case 0x06:
		case 0x07:
		{
			if(getCurPage() != PAGE_MULTI_CONTOURED_SEATS_MASSAGE)
			{
				systemToModule_NotifySystem_JumpPage(PAGE_MULTI_CONTOURED_SEATS_MASSAGE);
			}
		}
		break;
	}

	pLocalParam->selectSeatSide = p1;
	pLocalParam->st_MCS[p1 - 1].uChMk = p2;
	SeatSideMassage(p1);
	
	switch(p2)
	{
		case 0x00:
		break;
		case 0x01:
			SeatPressurePercentageLowerLumbar(p1,pLocalParam->st_MCS[p1 - 1].uLL);
		break;
		case 0x02:
			SeatPressurePercentageMiddleLumbar(p1,pLocalParam->st_MCS[p1 - 1].uML);
		break;
		case 0x03:
			SeatPressurePercentageUpperLumbar(p1,pLocalParam->st_MCS[p1 - 1].uUL);
		break;
		case 0x04:
			SeatPressurePercentageLowerBolster(p1,pLocalParam->st_MCS[p1 - 1].uLB);
		break;
		case 0x05:
			SeatPressurePercentageUpperBolster(p1,pLocalParam->st_MCS[p1 - 1].uUB);
		break;
		case 0x06:
			SeatIntensityLumbarMassage(p1,pLocalParam->st_MCS[p1 - 1].uLMI);
		break;
		case 0x07:
			SeatIntensityCushionMassage(p1,pLocalParam->st_MCS[p1 - 1].uCMI);
		break;
	}
}

void SeatMultiCOntouredAvailableMassage(u8 p)
{
	if(p == 0x00)//unAvailable
	{
		UI_Display_Adjust_UpperLumbarPre(21,2);
		UI_Display_Adjust_MidLumbarPre(21,2);
		UI_Display_Adjust_LowerLumbarPre(21,2);
		UI_Display_Adjust_UpperBolsterPre(21,2);
		UI_Display_Adjust_LowerBolsterPre(21,2);
		UI_Display_Adjust_DriverSide_State(0xFF);
		UI_Display_Adjust_PassengerSide_State(0xFF);
		UI_Display_Massage_Passage_UpperLumbarSet(0xFF);
		UI_Display_Massage_Passage_LowerLumbarSet(0xFF);
		UI_Display_Massage_Passage_DriverSide_State(0xFF);
		UI_Display_Massage_Passage_PassengerSide_State(0xFF);
		UI_Display_Select_Seats_Side(0xFF);
		UI_Display_Massage_Passage_UpperLumbarSelectedState(0);
		UI_Display_Massage_Passage_LowerLumbarSelectedState(0);
		
		UI_Display_MCS_MassageFunction_closing_PromptBox(0);
	}
	else if(p == 0x01)//Available
	{
	}

	pLocalParam->uMCS_Available = p;
}

void UI_Display_MassageIntensityLumbarAndCushion(u8 side)
{
	u8 lmi = pLocalParam->st_MCS[side - 1].uLMI;
	u8 cmi = pLocalParam->st_MCS[side - 1].uCMI;
	LOGD("[MCS Massage] %x %x %x",side,lmi,cmi);
	if(side == 1)//Driver
	{
		UI_Display_Massage_Passage_PassengerSide_State(0);
		
		switch(lmi)
		{
			case 0x00://NULL
			case 0x01://OFF
			{
				if(cmi == 0x01 || cmi == 0x00)//OFF
				{
					UI_Display_Massage_Passage_DriverSide_State(0);
				}
				else if(cmi == 0x02)//LOW
				{
					UI_Display_Massage_Passage_DriverSide_State(1);
				}
				else if(cmi == 0x03)//MID
				{
				}
				else if(cmi == 0x04)//HIGH
				{
					UI_Display_Massage_Passage_DriverSide_State(2);
				}
			}
			break;
			case 0x02://LOW
			{
				if(cmi == 0x01 || cmi == 0x00)//OFF
				{
					UI_Display_Massage_Passage_DriverSide_State(3);
				}
				else if(cmi == 0x02)//LOW
				{
					UI_Display_Massage_Passage_DriverSide_State(4);
				}
				else if(cmi == 0x03)//MID
				{
				}
				else if(cmi == 0x04)//HIGH
				{
					UI_Display_Massage_Passage_DriverSide_State(5);
				}
			}
			break;
			case 0x03://MID
			break;
			case 0x04://HIGH
			{
				if(cmi == 0x01 || cmi == 0x00)//OFF
				{
					UI_Display_Massage_Passage_DriverSide_State(6);
				}
				else if(cmi == 0x02)//LOW
				{
					UI_Display_Massage_Passage_DriverSide_State(7);
				}
				else if(cmi == 0x03)//MID
				{
				}
				else if(cmi == 0x04)//HIGH
				{
					UI_Display_Massage_Passage_DriverSide_State(8);
				}
			}
			break;
		}
	}
	else if(side == 2)//Passage
	{
		UI_Display_Massage_Passage_DriverSide_State(0);
		
		switch(lmi)
		{
			case 0x00://NULL
			case 0x01://OFF
			{
				if(cmi == 0x01 || cmi == 0x00)//OFF
				{
					UI_Display_Massage_Passage_PassengerSide_State(0);
				}
				else if(cmi == 0x02)//LOW
				{
					UI_Display_Massage_Passage_PassengerSide_State(1);
				}
				else if(cmi == 0x03)//MID
				{
				}
				else if(cmi == 0x04)//HIGH
				{
					UI_Display_Massage_Passage_PassengerSide_State(2);
				}
			}
			break;
			case 0x02://LOW
			{
				if(cmi == 0x01 || cmi == 0x00)//OFF
				{
					UI_Display_Massage_Passage_PassengerSide_State(3);
				}
				else if(cmi == 0x02)//LOW
				{
					UI_Display_Massage_Passage_PassengerSide_State(4);
				}
				else if(cmi == 0x03)//MID
				{
				}
				else if(cmi == 0x04)//HIGH
				{
					UI_Display_Massage_Passage_PassengerSide_State(5);
				}
			}
			break;
			case 0x03://MID
			break;
			case 0x04://HIGH
			{
				if(cmi == 0x01 || cmi == 0x00)//OFF
				{
					UI_Display_Massage_Passage_PassengerSide_State(6);
				}
				else if(cmi == 0x02)//LOW
				{
					UI_Display_Massage_Passage_PassengerSide_State(7);
				}
				else if(cmi == 0x03)//MID
				{
				}
				else if(cmi == 0x04)//HIGH
				{
					UI_Display_Massage_Passage_PassengerSide_State(8);
				}
			}
			break;
		}
	}
}

void UI_Display_Select(u8 p1,u8 p2)
{
	u8 select = pLocalParam->st_MCS[p1 - 1].uChMk;
	u8 side = pLocalParam->selectSeatSide;
	u8 swich = 0xFF;
	switch(select)
	{
		case 0x00:
			swich = 0x00;
		break;
		case 0x01:
			swich = 0x03;
		break;
		case 0x02:
			swich = 0x02;
		break;
		case 0x03:
			swich = 0x01;
		break;
		case 0x04:
			swich = 0x05;
		break;
		case 0x05:
			swich = 0x04;
		break;
	}
	if(side == 0x01){
		UI_Display_Adjust_DriverSide_State(swich);
		UI_Display_Adjust_PassengerSide_State(0x00);
	}
	else if(side == 0x02){
		UI_Display_Adjust_DriverSide_State(0x00);
		UI_Display_Adjust_PassengerSide_State(swich);
	}

	u8 ul = Seats_PercentageToIntegersValue(pLocalParam->st_MCS[p1 - 1].uUL);
	u8 ml = Seats_PercentageToIntegersValue(pLocalParam->st_MCS[p1 - 1].uML);
	u8 ll = Seats_PercentageToIntegersValue(pLocalParam->st_MCS[p1 - 1].uLL);
	u8 ub = Seats_PercentageToIntegersValue(pLocalParam->st_MCS[p1 - 1].uUB);
	u8 lb = Seats_PercentageToIntegersValue(pLocalParam->st_MCS[p1 - 1].uLB);

	u8 yIndex = 0xFF;
	switch(select)
	{
		case 0x03:
			{
				if(ul == 0xFF){
					return;
				}
				else if(ul == 0){
					yIndex = 0;
				}
				else{
				   yIndex = ul + 10;
				}
			}
			break;
		case 0x02:
			{
				if(ml == 0xFF){
					return;
				}
				else if(ml == 0){
					yIndex = 0;
				}
				else{
				   yIndex = ml + 10;
				}
			}
			break;
		case 0x01:
			{
				if(ll == 0xFF){
					return;
				}
				else if(ll == 0){
					yIndex = 0;
				}
				else{
				   yIndex = ll + 10;
				}
			}
			break;
		case 0x05:
			{
				if(ub == 0xFF){
					return;
				}
				else if(ub == 0){
					yIndex = 0;
				}
				else{
				   yIndex = ub + 10;
				}
			}
			break;
		case 0x04:
			{
				if(lb == 0xFF){
					return;
				}
				else if(lb == 0){
					yIndex = 0;
				}
				else{
				   yIndex = lb + 10;
				}
			}
			break;
	}

	if(select == 0x03)
		UI_Display_Adjust_UpperLumbarPre(yIndex,0x01);
	else
		UI_Display_Adjust_UpperLumbarPre(ul,0x00);	

	if(select == 0x02)
		UI_Display_Adjust_MidLumbarPre(yIndex,0x01);
	else
		UI_Display_Adjust_MidLumbarPre(ml,0x00);
	
	if(select == 0x01)
		UI_Display_Adjust_LowerLumbarPre(yIndex,0x01);
	else
		UI_Display_Adjust_LowerLumbarPre(ll,0x00);

	if(select == 0x05)
		UI_Display_Adjust_UpperBolsterPre(yIndex,0x01);
	else
		UI_Display_Adjust_UpperBolsterPre(ub,0x00);

	if(select == 0x04)
		UI_Display_Adjust_LowerBolsterPre(yIndex,0x01);
	else
		UI_Display_Adjust_LowerBolsterPre(lb,0x00);
}
