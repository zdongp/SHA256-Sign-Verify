#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__
void setDefaultParam();
void initByConfig();
void moduleParameterInit(void);
void moduleParameterDeInit(void);
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);
void moduleParameterReInit(void);
int module_extendInterface(char *buffer, int len);


void TvModule_Process_AccOff();
void TvMoudule_Process_AccOn();
void TvModule_Process_Reset();
void TvModule_Process_ResetDefault();

#endif
