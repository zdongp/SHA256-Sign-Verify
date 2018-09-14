#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__

void initByConfig(void);

void audiovideoModule_ACCON_Init(void);
void audiovideoModule_Init_JumpPage(void);

void audiovideoModule_ACCON(void);
void audiovideoModule_ACCON_JumpPage(void);

void moduleParameterInit(void);
void moduleParameterDeInit(void);
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);

void moduleParameterReInit(void);
int module_extendInterface(char *buffer, int len);

void setDefaultParam(void);
void ReInitWhenAccOn(void);
void sendStartVolToHalWhenAccOn(void);
void sendStartVolToHalWhenInit(void);


int findSoundAndVideoChannel(int *newSoundChannel,int *newVideoChannel,int oldSoundVideoChannel);
int GetPageByChannel(u16 *pageID,int channel_param);

int findCombineSoundVideoChannel(int soundChannel,int videoChannel,int *newSoundVideoChannel);

void setVolumeAmplitude(void);
void initSoundVideoChannelWhenPowerOn();

int findCombineIsAndroidAudioChannel(int soundChannel,int videoChannel);
void InitAudioParamMakeAndSendMessageToHal();
#endif
