#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__

void moduleParameterInit(void);
void moduleParameterDeInit(void);
void TpmsModule_SetDefaultParam();
void TpmsModule_InitByConfig();
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);

void moduleParameterReInit(void);
int module_extendInterface(char *buffer, int len);

void Set_SaveDataToRestart();
void Set_RestoreToFactoryDefaults();
void Get_Acc_off();
void Get_Acc_on();



#endif
