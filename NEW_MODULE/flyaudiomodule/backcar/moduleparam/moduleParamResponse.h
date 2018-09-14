#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__


void moduleParameterInit(void);
void moduleParameterReInit(void);
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);


void ModuleParamResponse_InitByConfig(void);
void ModuleParamResponse_InitParam();
void ModuleParamResponse_ReadData(void);
void ModuleParamResponse_WriteData(void);


int module_extendInterface(char *buffer, int len);


#endif
