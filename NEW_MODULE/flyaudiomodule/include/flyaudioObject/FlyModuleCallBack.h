/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#ifndef __FLY_MODULE_CALL_BACK_H__
#define __FLY_MODULE_CALL_BACK_H__

void moduleParameterInit(void);
void moduleParameterReInit(void);

void readParameter(void);
void saveParameter(void);

moduleid_t locale_module_mid(void);
void getMyModuleParam(char id, u8 *p, u8 *pLen);

int module_extendInterface(char *p, int len);
void analyseAgentMessage(moduleid_t id, u8 *p, u8 len);
void analyseAppMessage(u8 *p, u8 len);
void analyseOtherModuleMessage(moduleid_t id, u8 *p, u8 len);
void analyseHalMessage(halid_t hid, u8 cmd, u8 *p, u8 len);
void analyseTimerHandleMessage(u8 *p, u8 len);

void timerHandleProc(int timerId);
void pageIdUiHaveGone(int pageId);

#endif