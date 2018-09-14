#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

#define KEY_AV		0X03
#define KEY_SEEK_INC	0X38
#define KEY_SEEK_DEC	0X39
#define KEY_TUNE_INC	0X3B
#define KEY_TUNE_DEC	0X3C

void moduleToExternalCtrl_AnalyseModuleCommand_key(u8 *p,u8 len);

void ExternalctrlModule_IsJumpPrePage(void);
void FromKey_GetPanelKey(u8 p);
void moduleToExternalCtrl_AnalyseModuleCommand_Bt(u8 *p,u8 len);
void moduleToExternalCtrl_AnalyseModuleCommand_backcar(u8 *p,u8 len);
void moduleToExternalCtrl_AnalyseModuleCommand_system(u8 *p,u8 len);
void moduleToExternalCtrl_AnalyseModuleCommand_center(u8 *p,u8 len);
void moduleToExternalCtrl_AnalyseModuleCommand_Audiovideo(u8 *p,u8 len);

void setTagExternalCtrlToApp_CtrlVoiceSwitch(u8 p);

#endif
