/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once
#include "FlyJniSdkParam.h"
//#include "FlyJniSdkModuleBt.h"

#define JNISDK_TIMER_ID_RADIO_JUMP_PAGE				0x00
#define TIMERS_ID_RADIO_JUMP_PAGE					800

#define JNISDK_TIMER_ID_A2DP_JUMP_PAGE				0x01
#define TIMERS_ID_A2DP_JUMP_PAGE					800

#define JNISDK_TIMER_ID_MIDEA_JUMP_PAGE				0x02
#define TIMERS_ID_MIDEA_JUMP_PAGE					1000


class CFlyJniSdkApp;
class CFlyJniSdkHal;
class CFlyJniSdkParam;
class CFlyJniSdkModule : public CFlyModule
{
	SINGLETON_IMPLEMENT(CFlyJniSdkModule)
public:
	CFlyJniSdkModule(void);
public:
	virtual ~CFlyJniSdkModule(void);

	moduleid_t locale_module_mid(void);
public:
	//��ʼ��
	void init(void);//��ĳ�ʼ��
	//ϵͳ֪ͨ
	void getAccOn(void);//�յ� acc on ��Ϣ
	void getAccOff(void);//�յ� acc off ��Ϣ
	void getReset(void);
	void getResetFactorySetting(void);
	void getSystemCodeStartInitModule(void);
	//
	void timerHandleProc(int timerId);
	int nativeTimerHandlerProcess(timer_t timerId);
	void getMyModuleParam(char id, u8 *p, u8 *pLen);
	void getSystemMessage(u8 *p, u8 len);
	void getAudioVideoMessage(u8 *p, u8 len);
	void getKeyMessage(u8 *p, u8 len);
	void getRadioMessage(u8 *p, u8 len);
	void getBtMessage(u8 *p, u8 len);
	//moupeng 2015/7/30
	void getDvdMessage(u8 *p,u8 len);
	void getExtcarMessage(u8 *p, u8 len);
	
	//->add your code here////////////////////////////////////////////////////
	//from system
	
	//from audio video
	//work
	//assist
	//set to module
	void setToFlyJniSdkService(u8 moduleId, u8 *p, u8 len);
	//<-add your code here////////////////////////////////////////////////////
	void sendToFlyJniSdkService(u8 moduleId, u8 *p, u8 len);	
	void getAcMessage(u8 *p, u8 len);
	void getMediaMessage(u8 *p, u8 len);

    void SdkToOtherModule_AudioCtrl_FromSourceSource(u8 cmd,u8 param);
    void SdkToOtherModule_aboutAudioCtrlCmd(u8 ToMode,u8 cmd,u8 param);


private:
	CFlyJniSdkApp    *m_pFlyJniSdkApp;
	CFlyJniSdkModule *m_pFlyJniSdkModule;
	CFlyJniSdkHal    *m_pFlyJniSdkHal;
	CFlyJniSdkParam  *m_pFlyJniSdkParam;
};
