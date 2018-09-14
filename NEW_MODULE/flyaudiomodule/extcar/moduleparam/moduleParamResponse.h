#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__

void moduleParameterInit(void);
void moduleParameterDeInit(void);
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);
void moduleParameterReInit(void);
int module_extendInterface(char *buffer, int len);
void setDefaultParam(void);
void recoverLastSet(void);
void initByConfig(void);

void initCarInfoData();
void AccOffCarInfoData();
void initPublicExtcarSetPage(u8 param1,u8 param2,u8 param3);

#endif
