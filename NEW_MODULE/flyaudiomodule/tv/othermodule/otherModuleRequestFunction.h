#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__


void tvToModule_NotifySystem_JumpPage(u16 nPageId);//跳到指定页
void tvToModule_NotifySystem_JumpPrePage();//跳到前一页
void tvToModule_NotifySystem_SwitchToModule(u8 nModuleID);//切换到另一个模块

void tvToModule_NotifyOSD_aboutT123_VideoOSD_Button(u8 swtich_button,u8 button_status);
void tvToModule_NotifyOSD_aboutT123_colorSet_Value(u8 setOptions,u8 value);
void tvToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(u8 swtich_button,u8 button_status);
#endif
