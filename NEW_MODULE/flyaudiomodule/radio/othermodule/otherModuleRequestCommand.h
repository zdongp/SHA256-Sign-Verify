#ifndef __OTHER_MODULE_REQUEST_COMMAND_H__
#define __OTHER_MODULE_REQUEST_COMMAND_H__

void makeAndSendMessageToModule(unsigned char sendModuleId, unsigned char arrivedModuleId, unsigned char *buffer, int len);

void radioToModule_NotifySystem_JumpPage(u16 nPageId);//��ҳ����
void radioToModule_NotifySystem_JumpPrePage();

void radioToModule_JumpToOtherModule();

void radioToModule_AUXScreen_RadioStationName(u8 *pBuf, int nLen);
void radioToModule_AUXScreen_RadioRecord(u8 cRecord);
void radioToModule_AUXScreen_RadioChannel(u8 cChannel);
void radioToModule_AUXScreen_RadioFrequency(u16 wFreq);
void radioToModule_NotifyOsd_ShowTitle();
void radioToModule_NotifyOsd_ShowFrequecy(unsigned char type, unsigned short freq,u8 unit);
void radioToModule_NotifyAutoMate_State(char resCmd,u8 *param,u8 len);
void radioToModule_system_RadioArea(u8 code);
void radioToModule_AuxscreenFreRecordList(u8 nChannel,u8 list,u8 allNum,u16 *recordeList);
void initAuxscreenFreRecordList();


#endif
