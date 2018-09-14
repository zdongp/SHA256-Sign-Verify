#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__

void moduleParameterInit(void);
void moduleParameterDeInit(void);
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);
void moduleParameterReInit(void);
int module_extendInterface(char *buffer, int len);
void OSDModule_SetDefaultParam();

void OSDModuleParameterToT123_aboutLanguageType();

#endif
