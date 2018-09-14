#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "pageID.h"


//#include "moduleParamResponse.h"

static 	int arrayMapping[][3] = {
		{1,0,CHANNEL_DVD_CTRL},
		{1,1,CHANNEL_DVD_VIDEO},
		{2,0,CHANNEL_CDC_CTRL},
		{2,2,CHANNEL_CDC_VIDEO},
		{3,0,CHANNEL_RADIO},
		{4,0,CHANNEL_AUX_CTRL},
		{4,4,CHANNEL_AUX_VIDEO},
		{5,0,CHANNEL_IPOD_CTRL},
		{5,5,CHANNEL_IPOD_VIDEO},
		{6,0,CHANNEL_TV_CTRL},
		{6,6,CHANNEL_TV_VIDEO},
		{7,0,CHANNEL_MP3},
	//	{8,0,CHANNEL_SRADIO},
		{9,0,CHANNEL_BT},
		{0x11,0,CHANNEL_DVR_CTRL},
		{0x11,0x11,CHANNEL_DVR_VIDEO},
		//{0x0C,0x0C,CHANNEL_BACK_VIDEO}
		{0x0D,0x0D,CHANNEL_BACK_VIDEO},
		{0x0C,0,CHANNEL_THREECHANNEL},
		{0x16,0,CHANNEL_SPEECH_MEDIA_CTRL}
};

int findSoundAndVideoChannel(int *newSoundChannel,int *newVideoChannel,int oldSoundVideoChannel)
{
	int i=0;
	int nCount = 0;
	nCount = (sizeof(arrayMapping)/sizeof(arrayMapping[0]));
	for(i=0;i<nCount;i++)
	{
		if (arrayMapping[i][2] == oldSoundVideoChannel)
		{
			*newSoundChannel = arrayMapping[i][0];  //9
			*newVideoChannel = arrayMapping[i][1];	//0
			return true;
		}
	}

	return false;
}

void moduleToBlcd_FromBlcd_SetSoundVideoChannel(u8 param){  //0X0D
	int newSoundChannel = -1;
	int newVideoChannel = -1;

	findSoundAndVideoChannel(&newSoundChannel,&newVideoChannel,param);
	
	LOGD("(Jooph.Lew)Set SoundChannel:0x%x,VideoChannel:0x%x.+++++++++++++\n",newSoundChannel,newVideoChannel);
	if(newSoundChannel != -1)
		blcdToHal_SetSoundChannel(newSoundChannel); //9
	if(newVideoChannel != -1)
		blcdToHal_SetVideoChannel(newVideoChannel); //0
}



void moduleToBlcd_FromSystem_Message(unsigned char *param, unsigned char len){
	
	unsigned char ucSystemCmd = param[0];
	switch(ucSystemCmd)
	{
	case 0x10: //复位 保存注册表
		Set_SaveDataToRestart();
		break;
	case 0x14: //恢复出厂设置
		Set_RestoreToFactoryDefaults(); 
		break;
	default:
		break;
	}
}

void moduleToBlcd_FromAudiovideo_Message(unsigned char *param, unsigned char len){
	unsigned char ucSoundCmd = param[0]; //Sound Cmd
	if(ucSoundCmd != 0x00)
		return;
	unsigned char ucSoundMode = param[1];
	LOGD("moduleToBlcd_FromAudiovideo_Message ucSoundMode:%x",ucSoundMode);
	DispatchProcessSoundCmd(ucSoundMode);

}

void moduleToBlcd_FromKey_Message(unsigned char *param, unsigned char len){
	if(param[0] != 0x00) //buf[0] KeyCmd:0x00
		return;
	unsigned char ucKeyCmdParam = param[1]; //KeyCmdParam
	DispatchProcessKeyCmd(ucKeyCmdParam);

}
void moduleToBlcd_FromDvd_Message(unsigned char *param, unsigned char len){
	//unsigned char ucDVDCmd = buf[0]; 
	//DispatchProcessSoundCmd(ucDVDCmd);
}

void moduleToBlcd_FromExternalCtrl_Message(unsigned char *param, unsigned char len)
{
	if(param[0]==0x01)
	{
		if(param[1]==0x01)
		{
			blcdToModule_NotifySystem_JumpPage(PAGE_BLCD);
		}
		else
		{
		}
	}
}

void moduleToBlcd_FromAutomate_Message(unsigned char *param, unsigned char len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;

    analyseAppMessage(param+1,len-1);
}

/*
void AnalyseModuleCommand_CDC(unsigned char* param,int len)
{
    unsigned char ucCDCCmd = param[0]; 
	switch (ucCDCCmd)
	{
	case 0:	//选碟处理
		{
			unsigned char ucData = param[1];
			Get_CDC_DISC_Select(ucData);
			break;
		}
	case 6://返回cdc盒 各碟片状态
		{
			char cDisc=param[1];
			char cState=param[2];
			if (0x00==cState)
				Get_CDC_DISC_Open();
			break;
		}  
	case 7://返回CDC盒 各碟片类型	
		{
			char cDisc=param[1];
			char cType=param[2];
			Get_CDC_DISC_Type(cDisc,cType);
			break;
		}
	default:
		break;
	}
}

*/


// Dispatch Process Cmd From SoundModule
void DispatchProcessSoundCmd(unsigned char ucState)
{
	pLocalParam->audioMode = ucState;
	Show_Blcd_Mode();
}

void DispatchProcessKeyCmd(unsigned char ucCmd)
{
    
}

/*
void  Get_CDC_DISC_Select(char disk)
{
	pLocalParam->CDCType.ActiveDisk=disk;
	if (emBlcdMode_CDC==pLocalParam->getMode && SoundMode_CDC!=pLocalParam->audioMode)
		Show_CDC_Disc();
}

void Show_CDC_Disc()
{
	u8 * str;
	unicode16_t uniBuffer[96];
	uni16_size_t uniLen = 0;
	for(int i = 0;i<6;i++)
	{
		str = CDC_GetDiscStr(i+1);
		uniLen = ansi_str_to_unicode16(str, uniBuffer);
		setSerialData(FUNCID_BLCD_TXTBTN_1+ i, (u8*)uniBuffer, 2*uniLen)
		setDigitalData(FUNCID_BLCD_TXTBTN_1+i,0);
		setAnalogData(FUNCID_BLCD_TXTBTN_1+i,(short)0);
	}
	char activeDisc=pLocalParam->CDCType.ActiveDisk;
	setDigitalData(FUNCID_BLCD_TXTBTN_1+activeDisc-1,1);
	setAnalogData(FUNCID_BLCD_TXTBTN_1+activeDisc-1,1);
}

u8 CDC_GetDiscStr(char discNumber)
{
	static u8 buff[9] = {discNumber,0};
	u8 *str =  buff;
	switch (pLocalParam->CDCType.CDCDiskType[discNumber-1])
	{
	case 0: //no disc
		memcpy(&buff[1]," ",strlen(" "));
		break;
	case 1:	//cd
		memcpy(&buff[1],"CD",strlen("CD"));
		break;
	case 2:	//vcd
		memcpy(&buff[1],"VCD",strlen("VCD"));
		break;
	case 3:	//svcd
		memcpy(&buff[1],"SVCD",strlen("SVCD"));
		break;
	case 4:	//mp3
		memcpy(&buff[1],"MP3",strlen("MP3"));
		break;
	case 5:	//dvd
		memcpy(&buff[1],"DVD",strlen("DVD"));
		str.Format(L"%d. DVD",discNumber);
		break;	
	case 6: //UNKNOWN DISC
		memcpy(&buff[1],"UNKNOWN",strlen("UNKNOWN"));
		//str.Format(L"%d. UNKNOWN DISC ",discNumber);
		break;
	}
	return str;
}

void Get_CDC_DISC_Open()
{
	if (emBlcdMode_CDC==pLocalParam->getMode && SoundMode_CDC!=pLocalParam->audioMode)
		Clean_CDC_Disc();
}

void Clean_CDC_Disc(){
	u8 * str="";
	unicode16_t uniBuffer[96];
	uni16_size_t uniLen = 0;
	uniLen = ansi_str_to_unicode16(str, uniBuffer);
	for(int i = 0;i<6;i++)
	{
		setSerialData(FUNCID_BLCD_TXTBTN_1+ i,(u8*)uniBuffer, 2*uniLen);
		setDigitalData(FUNCID_BLCD_TXTBTN_1+i,0);
		setAnalogData(FUNCID_BLCD_TXTBTN_1+i,0);
	}
}

void Get_CDC_DISC_Type(char disk,char type)
{
	pLocalParam->CDCType.CDCDiskType[disk-1]=type;
	if (emBlcdMode_CDC==pLocalParam->getMode && SoundMode_CDC!=pLocalParam->audioMode)
		Show_CDC_Disc(disk);
}

*/
