#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__

void moduleParameterInit(void);
void moduleParameterDeInit(void);
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);

void ModuleParamResponse_InitByConfig(void);
void ModuleParamResponse_InitParam(void);
void ModuleParamResponse_ReadData(void);
void ModuleParamResponse_WriteData(void);
void moduleParameterReInit(void);
int module_extendInterface(char *buffer, int len);
void ModuleRadio_setButtonVisible();
void InitParamMakeAndSendMessageToHal();
void ModuleParamRadioIDChangePara(u8 iID);
void ModuleParamDefaultFreqToUI(void);
void ModuleParam_RadioInitUI(void);

#endif
