#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__

void keyToModule_DispatchPanelKey(int nDispatchBySoundMode,unsigned char cToMode,unsigned char cParameter);
void keyToModule_SendPanelKey(unsigned char cToMode,unsigned char cKeyValue);
void keyToModule_NotifyBACK_ExitAllScreen(void);
void SendKeyValueToOSDDebug(u8 keyVal);
void keyToSystemModule_About_SmartFan_Telecontrol(u8 param);
void keyToSystemModule_About_LCD_Telecontrol(u8 param);
void keyToSystemModule_About_FanMode_PerformanceSwitch(u8 param);
void keyToSystemModule_About_AntotoItsOpen(u8 param);
void keyToExtcarModule_Notify_Prado_KeyInfo(u8 param);

void keyToExtcarModule_NotifyExternalCtrl_SpeechKeyInfo(u8 p);



#endif
