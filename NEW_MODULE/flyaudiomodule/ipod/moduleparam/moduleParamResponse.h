#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__

void moduleParameterInit(void);
void moduleParameterDeInit(void);
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);
void moduleParameterReInit(void);
int module_extendInterface(char *buffer, int len);
void updateTypeListInfo(u8* iSongName);
int isCurSong(int index,u8* songName);

//���IPOD��Ϣ����Ҫ��IPOD�γ��� ��ԭIPOD��Ϣ
void ClearIPODMessage();
void StartConnectIpod();
void setDefaultParam(void);

#endif
