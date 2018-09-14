#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__

int module_extendInterface(char *buffer, int len);
void moduleParameterInit(void);
void moduleParameterDeInit(void);
void ServiceModule_InitByConfig();
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);
void moduleParameterReInit(void);

void initRemoteOnlineParam();
void RemoteOnlineModule_SetDefaultParam();
void Car_AsynchResetSystemOn_a_RegularBasis_Processing(void);














#endif
