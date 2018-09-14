#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__

int moduleToKey_AnalyseModuleCommand_System(unsigned char* buf,int len);
int moduleToKey_AnalyseModuleCommand_Sound(unsigned char* buf,int len);
int moduleToKey_AnalyseModuleCommand_Sync(unsigned char * buf,int len); 
int moduleToKey_AnalyseModuleCommand_Key(unsigned char * buf,int len); 
void moduleToKey_AnalyseModuleCommand_ExternalCtrl(unsigned char * buf,int len);

void moduleToKey_GetChannel(unsigned char cSoundMode);
void ModuleToKey_AccOn();
void ModuleToKey_AccOff();
void analyseSdkToKeyDedicate_information(u8 *param,int len);
#endif