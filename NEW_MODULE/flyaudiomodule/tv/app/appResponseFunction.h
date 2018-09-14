#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

void appToTV_CtrlMenu_MouseUp(u32 nFuncID);//控制页的弹起事件
void appToTV_VideoSet_MouseUp(u32 nFuncID);//视频设置的弹起事件
void appToTV_JumpPage_MouseUp(u32 nFuncID);//跳页弹起事件

void appToTV_VideoOSD_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType);
void appToTV_VideoOSDColorSet_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType);

#endif
