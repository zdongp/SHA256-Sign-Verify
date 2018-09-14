#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__

void moduleParameterInit(void);
void moduleParameterDeInit(void);
void setDefaultParamters(void);
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);
void moduleParameterReInit(void);
int module_extendInterface(char *buffer, int len);

void ACModule_SetDefaultParam();
void publicAcSetDefaultParam();


void AirconditionModule_Process_AccOff();
void AirconditionMoudule_Process_AccOn();
void AirconditionModule_Process_Reset();
void AirconditionModule_Process_ResetDefault();
#endif
