#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleID.h"
#include "param.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "timer_interface.h"


//��ָ��ҳ
void auxToModule_NotifySystem_jumpPage(u16 PageId){
	 
     u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&PageId,2);
     makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_SYSTEM,buf,3);
}

//��ǰһҳ
void auxToModule_NotifySystem_JumpPrePage(void){
     u8 buf[] = {0x83,0x00};
     makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_SYSTEM,buf,3);
}

void appToAux_VideoSet_ColorDec_MouseUp(void){
	unsigned char buf[] = {0x11, 0x02};
	makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_AUDIOVIDEO,buf,2);
}

void appToAux_VideoSet_ColorInc_MouseUp(void){
	unsigned char buf[] = {0x11, 0x01};
	makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_AUDIOVIDEO,buf,2);
}

void appToAux_VideoSet_ChrominanceDec_MouseUp(void){
	unsigned char buf[] = {0x11, 0x04};
	makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_AUDIOVIDEO,buf,2);
}

void appToAux_VideoSet_ChrominanceInc_MouseUp(void){
	unsigned char buf[] = {0x11, 0x03};
	makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_AUDIOVIDEO,buf,2);
}

void appToAux_VideoSet_ContrastDec_MouseUp(void){
	unsigned char buf[] = {0x11, 0x06};
	makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_AUDIOVIDEO,buf,2);
}

void appToAux_VideoSet_ContrastInc_MouseUp(void){
	unsigned char buf[] = {0x11, 0x05};
	makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_AUDIOVIDEO,buf,2);
}

void appToAux_VideoSet_BrightnessDec_MouseUp(void){
	unsigned char buf[] = {0x11, 0x08};
	makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_AUDIOVIDEO,buf,2);
}

void appToAux_VideoSet_BrightnessInc_MouseUp(void){
	unsigned char buf[] = {0x11, 0x07};
	makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_AUDIOVIDEO,buf,2);
}

void auxToModule_NotifySystem_SwitchToModule(unsigned char ucModule){
	unsigned char buf[2] = {SwitchModuleCmd,ucModule};
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_SYSTEM,buf,2);
}


void auxToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(u8 swtich_button,u8 button_status)
{
	u8 buf[] = {0X31,0x00,0x00};
	buf[1]=swtich_button;
	buf[2]=button_status;
	makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_OSD,buf,3);
}

void auxToModule_NotifyOSD_aboutT123_colorSet_Value(u8 setOptions,u8 value)
{
	u8 buf[] = {0X01,0x00,0x00};
	buf[1]=setOptions;
	buf[2]=value;
	makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_OSD,buf,3);

}

void auxToModule_NotifyOSD_aboutT123_VideoOSD_Button(u8 swtich_button,u8 button_status)
{
	u8 buf[] = {0X30,0x00,0x00};
	buf[1] = swtich_button;
	buf[2] = button_status;
	makeAndSendMessageToModule(MODULE_ID_AUX,MODULE_ID_OSD,buf,3);

}

