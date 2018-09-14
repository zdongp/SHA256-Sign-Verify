#ifndef __OTHERMODULE_REQUEST_FUNCTION_H__
#define __OTHERMODULE_REQUEST_FUNCTION_H__

void blcdToModule_NotifySystem_JumpPage(u16 pageID);
void blcdToModule_NotifySystem_JumpPrePage(void);

void Set_DVD_PlayControl(char command)	;
void Set_CDC_PlayControl(char command);
void Set_TV_PlayControl(char command);
void Set_AUX_PlayControl(char command);

void Set_Mode(unsigned char mode);
//void SetDefaultParam();

void Set_SaveDataToRestart();
void Set_RestoreToFactoryDefaults();
#endif