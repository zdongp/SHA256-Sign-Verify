#include <stdio.h>
#include <stdlib.h>

#include "global.h"


#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleID.h"

//��ָ��ҳ
void dvdToModule_NotifySystem_jumpPage(u16 PageId){
	 u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&PageId,2);
     makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_SYSTEM,buf,3);
}
//��ǰһҳ
void dvdToModule_NotifySystem_JumpPrePage(void){
	 u8 buf[] = {0x83,0x00};
     makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_SYSTEM,buf,2);
}

void dvdToModule_NotifySystem_SwitchModule(void)//����AV KEY
{
	unsigned char buff[] =  {0x81,MODULE_ID_DVD};
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_SYSTEM,buff,2);
}
/////////////////////////////////////////////////
void dvdToModule_NotifyAuxscreen_TitleTrack(short title, short track){
	unsigned char buf[] = {0x20,0x00,0x00,0x00,0x00};
	memcpy(&buf[1],&title,2);
	memcpy(&buf[3],&track,2);
	makeAndSendMessageToModule(MODULE_ID_DVD, MODULE_ID_AUXSCREEN, buf, 5);
}

void dvdToModule_NotifyAuxscreen_Time(int time){
	unsigned char buff[] = {0x21, 0x00, 0x00, 0x00, 0x00};

	memcpy(&buff[1], &time, 4);
	makeAndSendMessageToModule(MODULE_ID_DVD, MODULE_ID_AUXSCREEN, buff, 5);
}

void dvdToModule_NotifyAuxscreen_DiscInfo(char discType, char fileType){
	unsigned char buff[] = {0x22, discType, fileType};
	makeAndSendMessageToModule(MODULE_ID_DVD, MODULE_ID_AUXSCREEN, buff, 3);
}

void dvdToModule_NotifyAuxscreen_PlayState(char state){
	unsigned char buff[] = {0x23, state};
	makeAndSendMessageToModule(MODULE_ID_DVD, MODULE_ID_AUXSCREEN, buff, 2);
}

void dvdToModule_NotifyAuxscreen_DeviceState(char state){
	unsigned char buff[] = {0x24, state};
	makeAndSendMessageToModule(MODULE_ID_DVD, MODULE_ID_AUXSCREEN, buff, 2);
}
void dvdToModule_NotifyAuxscreen_TotalTime(int time){
	unsigned char buff[] = {0x26, 0x00, 0x00, 0x00, 0x00};
	memcpy(&buff[1], &time, 4);
	makeAndSendMessageToModule(MODULE_ID_DVD, MODULE_ID_AUXSCREEN, buff, 5);
 }


////////////////////////////////////
void dvdToModule_NotifyOSD_aboutT123_VideoOSD_Button(u8 swtich_button,u8 button_status)
{
	u8 buf[] = {0X60,0x00,0x00};
	buf[1]=swtich_button;
	buf[2]=button_status;
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_OSD,buf,3);

}

void audioVideoToModule_NotifyOsd_ShowDVDTitle()
{
	u8 buf[] = {0x01, 0x12};
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_OSD,buf,2);
}
void audioVideoToModule_NotifyOsd_DVDTitleValue(unsigned char type,u16 title,u16 track){
	u8 buf[] = {0x12,0x00,0x00,0x00,0x00,0x00};
	buf[1] = type;
	buf[2] = title&0x00ff;
	buf[3] = u8((title&0xff00)>>8);
	buf[4] = track&0x00ff;
	buf[5] = u8((track&0xff00)>>8);
	
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_OSD,buf,6);
}

void dvdToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(u8 swtich_button,u8 button_status)
{
	u8 buf[] = {0X61,0x00,0x00};
	buf[1]=swtich_button;
	buf[2]=button_status;
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_OSD,buf,3);
}

void dvdToModule_NotifyOSD_aboutT123_colorSet_Value(u8 setOptions,u8 value)
{
	u8 buf[] = {0X04,0x00,0x00};
	buf[1]=setOptions;
	buf[2]=value;
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_OSD,buf,3);

}

void dvdToModule_NotifyOSD_aboutT123_playtimes_Value(int timeValue)
{
	u8 buf[10] = {0x6A,0x00};
	//memcpy(&buf[1],&timeValue,4);
	buf[1] =  timeValue&0x000000ff;
	buf[2] = (timeValue&0x0000ff00)>>8;
	buf[3] = (timeValue&0x00ff0000)>>16;
	buf[4] = (timeValue&0xff000000)>>24;
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_OSD,buf,5);
}


