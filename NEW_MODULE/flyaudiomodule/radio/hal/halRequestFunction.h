#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__
//以下定义发往 hal 的消息

void radioTohal_InitCmd(u8 nState);//初始化命令
void radioTohal_ImitateKey(u8 nState);//模拟按键
void radioTohal_Frequency(u16 nFrequency);//设置收音机频率
void radioTohal_Frequency_Inc(u8 nState);//频率增加
void radioTohal_Frequency_Dec(u8 nState);//频率减少
void radioTohal_ScanCtrl(u8 nState);//扫描控制
void radioTohal_RadioSwitch_Power(u8 nState);//收音机开关
void radioTohal_RadioSwitch_AF(u8 nState);//AF 开关
void radioTohal_RadioSwitch_TA(u8 nState);//TA 开关
void radioTohal_RadioDebugText(u8 nState);//Debug 通道
void rdaioToHal_Scan(int cmd);
void radioTohal_Frequency2(u16 nFrequency);

void radioTohal_SetSensitivity(u8 state);
void radioTohal_SetChannelAndFre(u8 nChannel,u16 nFrequency);

void radioTohal_InitParamCmd(u8 *param,int len);

#endif













