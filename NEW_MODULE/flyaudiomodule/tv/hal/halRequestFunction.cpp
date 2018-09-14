#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"

#include <flymoduleApi_internal.h>

//初始化
void tvToHal_Init(){
     u8 buf[] = {0x01,0x01};
     makeAndSendMessageToHal(HAL_ID_TV,buf,2);
}

void tvToHal_KeyCtrl(u8 nKey){
     u8 buf[] = {0x03,nKey};
     makeAndSendMessageToHal(HAL_ID_TV,buf,2);
}

//模拟按键
void tvToHal_ImitateKeyCtrl(u8 nKey){
     u8 buf[] = {0x03,nKey};
     makeAndSendMessageToHal(HAL_ID_TV,buf,2);
}
//调试模式
void tvToHal_Debug(){
     u8 buf[] = {0xFF,0x00};
     makeAndSendMessageToHal(HAL_ID_TV,buf,2);
}
//命令参数
void tvToHal_VideoSetting(u8 nCmdParam)
{
     u8 buf[] = {0x11,nCmdParam};
     makeAndSendMessageToHal(HAL_ID_VIDEO,buf,2);
}

void tvToHal_IR(unsigned char IR_key){
	LOGI(" Device Control instruction IR:%d", IR_key);

	unsigned char buf[] = {0x10, IR_key};
	makeAndSendMessageToHal(HAL_ID_TV,buf, 2);
}


