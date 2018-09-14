#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "halResponseFunction.h"

extern "C"{
#include "unicodestring.h"
};


//App Init
void systemToApp_Init()
{
	
}
void SystemToApp_DisplayRadioCountry(void)
{

	u8 *pAnsiBuf = (u8 *)"Unknow";
    LOGD("RADIO COUNTRY =%x",pLocalParam->cRadioCountry);
	if(pLocalParam->u8_Sys_RadioCountryCode==0 && pLocalParam->cRadioCountry!=0)
		pLocalParam->u8_Sys_RadioCountryCode = pLocalParam->cRadioCountry;
	LOGD("SystemToApp_DisplayRadioCountry u8_Sys_RadioCountryCode:%x",pLocalParam->u8_Sys_RadioCountryCode);
	switch(pLocalParam->u8_Sys_RadioCountryCode)
	{
	case emCode_KOREA:
		pAnsiBuf = (u8*)"KOREA";
		break;
	case emCode_THAILAND:
		pAnsiBuf = (u8*)"Thailand";
		break;
	case emCode_SAMER_2:
		pAnsiBuf = (u8*)"S.Amer-2";
		break;
	case emCode_CHINA: 
		pAnsiBuf = (u8*)"CHINA";
		break;
	case emCode_SAMER_1:
		pAnsiBuf = (u8*)"S.Amer-1";
		break;
	case emCode_USA:
		pAnsiBuf = (u8*)"USA";
		break;
	case emCode_RUSSIA:
		pAnsiBuf = (u8*)"Russia";
		break;
	case 7:
		pAnsiBuf = (u8*)"Israel";
		break;
	case 8:
		pAnsiBuf = (u8*)"GCC";
		break;
	default:
		break;
	}
	int nAnsiBufLen = strlen((char*)pAnsiBuf);
	u8 *pUnicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
	memset(pUnicodeBuf, 0, nAnsiBufLen*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(pAnsiBuf, (unicode16_t*)pUnicodeBuf);
	setSerialData(CONTROLID_SETUP_MULTINATIONAL_RADIO_TEXT,pUnicodeBuf,nUnicodeBufLen*2);
	free(pUnicodeBuf);
	
}

void SysteToApp_DisplayDVDRegionCode()
{
	u8 ansicDvdCode = pLocalParam->u8_Sys_DVDRegionCode;
	u8 ansicBuf[4];
	memset(ansicBuf, 0, 4);
	sprintf((char*)ansicBuf,"%d",ansicDvdCode);

	int nAnsiBufLen = strlen((char*)ansicBuf);
	LOGD("SYSTEM----ansicDvdCode=%d--,param=%d---",ansicDvdCode,pLocalParam->cDvdRegion);
	if(ansicDvdCode==6 && pLocalParam->cDvdRegion==10){
		u8* ansicBuf2=(u8*)"Multi Zone";
		u8  nAnsiBufLen2=(u8)strlen("Multi Zone");
		u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen2*2+2);
		memset(unicodeBuf, 0, nAnsiBufLen2*2+2);
		int nUnicodeBufLen = ansi_str_to_unicode16(ansicBuf2, (unicode16_t*)unicodeBuf);


		setSerialData(CONTROLID_SETUP_DVD_REGION_SET_TEXT, unicodeBuf, nUnicodeBufLen*2);
		free(unicodeBuf);
        return ;
	}
	u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
	memset(unicodeBuf, 0, nAnsiBufLen*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(ansicBuf, (unicode16_t*)unicodeBuf);
	

	setSerialData(CONTROLID_SETUP_DVD_REGION_SET_TEXT, unicodeBuf, nUnicodeBufLen*2);
	free(unicodeBuf);

}
void System_NotifyAppEnterTimePage()
{
 
}

void System_NotifyAppExitTimePage()
{
  
}


void System_Set_RARBackCar_Contorl()
{
   
}
void systemToApp_SendVIMCode(u8 *pBuf,u8 len)
{
	u8 param[128] = {0x41,0x00};
	memcpy(&param[1],pBuf,len);
	setCommand(0x00000000, param, len+1);
}

void systemToApp_WakeUpInfo(u8 status)
{
	u8 param[128] = {0x43,0x00};
	param[1]=status;
	setCommand(0x00000000, param, 2);
}

void systemToApp_FanMode(u8 status)
{
	u8 param[128] = {0x45,0x00};
	param[1]=status;
	setCommand(0x00000000, param, 2);
}

void systemToApp_AllowReadParam(u8 status)
{
	u8 param[2] = {0x48,0x00};
	param[1]=status;
	setCommand(0x00000000, param, 2);
}

void systemToApp_HidePull_DownBar(void)
{
	u8 param[2] = {0xF4,0x00};
	setCommand(0x00000000, param, 2);
}


void systemToApp_BackVideo_CarRadarIsDisplay(u8 status)
{
	if(pLocalParam->uModuleSystem_is_T123 == 0){
		setVisible(CONTROLID_BACK_VIDEO_CAR_RADAR,(int)status);
	}
    //setVisible(CONTROLID_BACK_VIDEO_CAR_RADAR,(int)status);
    //systemToModule_NotifyOSD_backcar_carRadar_SwitchRadarcarPage(status);
    //systemToModule_NotifyOSD_backcar_carRadar_DisplayingAndHander(status);
}

void SystemToApp_ShowRadioCountry( u8 param)
{
	int i;
	for (i = 0; i < RADIO_AREA_NUM; i++)
	{
		if(param == i)
			setDigitalData(CONTROLID_SETUP_RADIO_CHINA + param,1);
		else
			setDigitalData(CONTROLID_SETUP_RADIO_CHINA + i,0);
	}
}
void systemToApp_Sound_Channel_Volume_Adjust(u8 nChannel,u8 nValue)
{
	u8 buf[3] = {0xA6,nChannel,nValue};
	setCommand(0x00000000, buf, 3);
}

void systemToApp_Open_Custom_Apk(u8 nValue)
{
	u8 buf[2] = {0xA7,nValue};
	setCommand(0x00000000, buf, 2);
}

