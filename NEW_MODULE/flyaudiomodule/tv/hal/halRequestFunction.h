#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__
#define TVTOHAL_IR_PLAY     0x14
#define TVTOHAL_IR_PAUSE    0x15

void tvToHal_KeyCtrl(u8 nKey);//按键控制
void tvToHal_Init();//初始化
void tvToHal_ImitateKeyCtrl(u8 nKey);//模拟按键
void tvToHal_Debug();//调试模式
void tvToHal_VideoSetting(u8 nCmdParam);//命令参数
void tvToHal_IR(unsigned char IR_key);

#endif
