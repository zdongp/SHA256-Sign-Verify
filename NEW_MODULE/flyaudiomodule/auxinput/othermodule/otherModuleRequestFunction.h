#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__

void auxToModule_NotifySystem_jumpPage(u16 pageID);
void auxToModule_NotifySystem_JumpPrePage(void);
void appToAux_VideoSet_ColorDec_MouseUp(void);
void appToAux_VideoSet_ColorInc_MouseUp(void);
void appToAux_VideoSet_ChrominanceDec_MouseUp(void);
void appToAux_VideoSet_ChrominanceInc_MouseUp(void);
void appToAux_VideoSet_ContrastDec_MouseUp(void);
void appToAux_VideoSet_ContrastInc_MouseUp(void);
void appToAux_VideoSet_BrightnessDec_MouseUp(void);
void appToAux_VideoSet_BrightnessInc_MouseUp(void);
void auxToModule_NotifySystem_SwitchToModule(unsigned char ucModule); //֪ͨSystem�л�Module(Moduleģ��FromModuleΪ:SystemModule)
/*void auxToModule_NotifySystem_SwitchToCurrentPage(unsigned short wCurPage);     //֪ͨSystem���õ�ǰҳ(Moduleģ��FromModuleΪ:SystemModule)
void auxToModule_NotifySystem_SwitchToPreviousPage();                 //֪ͨSystem����ǰһҳ(Moduleģ��FromModuleΪ:SystemModule)
*/
void auxToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(u8 swtich_button,u8 button_status);
void auxToModule_NotifyOSD_aboutT123_colorSet_Value(u8 setOptions,u8 value);
void auxToModule_NotifyOSD_aboutT123_VideoOSD_Button(u8 swtich_button,u8 button_status);
#endif