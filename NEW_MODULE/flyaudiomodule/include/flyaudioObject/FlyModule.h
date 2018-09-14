/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#ifndef __FLY_MODULE_H__
#define __FLY_MODULE_H__

#include "FlyParam.h"

//��������
typedef int (*timer_handler_function)(timer_t timerId);

class CFlyApp;
class CFlyHal;
class CFlyParam;
class CFlyModule : public CFlyObject
{
public:
	CFlyModule(void);
	virtual ~CFlyModule(void);

	virtual moduleid_t locale_module_mid(void) = 0;//�õ���ģ�� ID
public:
	virtual void init(void) = 0;//���ʼ��
	virtual void deInit(void);//������
	void moduleParameterInit(void);//������ʼ��
	void moduleParameterReInit(void);//�������³�ʼ��
	virtual void getMyModuleParam(char id, u8 *p, u8 *pLen);//�ⲿȡ��ģ��Ĺ������
	int analyseFlyNativeServerMessage(char *p, u8 len);//��Ϣ���ķַ�ģ�鷢������Ϣ
	void analyseOtherModuleMessage(moduleid_t id, u8 *p, u8 len);//����ģ�����ݽ���
	void analyseTimerHandleMessage(u8 *p, u8 len);
	virtual void timerHandleProc(int timerId);//java ui ��ʱ��������
	virtual void pageIdUiHaveGone(int pageId);
	//������λ��Ҫ�ӿ�
	virtual void getSystemCodeStartInitModule();//������������ʼ�� module
	virtual void getSystemCodeStartInitModuleFinish();//������������ʼ������ module ����
	virtual void getAccOn() = 0;//�յ� acc on ��Ϣ
	virtual void getAccOff() = 0;//�յ� acc off ��Ϣ
	virtual void getWakeUp();//�յ�������Ϣ
	virtual void getReset();//�յ���λ��Ϣ
	virtual void getResetFactorySetting();//�յ��ָ�����������Ϣ
	virtual void getStandbyOn();
	virtual void getStandbyOff();
	//�õ���Ӧģ�����Ϣ
	virtual void getAutoMateMessage(u8 *p, u8 len);
	virtual void getAudioVideoMessage(u8 *p, u8 len);
	virtual void getSystemMessage(u8 *p, u8 len);
	virtual void getKeyMessage(u8 *p, u8 len);
	virtual void getRadioMessage(u8 *p, u8 len);
	virtual void getDvdMessage(u8 *p, u8 len);
	virtual void getTpmsMessage(u8 *p, u8 len);
	virtual void getBackCarMessage(u8 *p, u8 len);
	virtual void getTvMessage(u8 *p, u8 len);
	virtual void getBtMessage(u8 *p, u8 len);
	virtual void getAcMessage(u8 *p, u8 len);
	virtual void getGpsMessage(u8 *p, u8 len);
	virtual void getExtcarMessage(u8 *p, u8 len);
	virtual void getSyncMessage(u8 *p, u8 len);
	virtual void getDvrMessage(u8 *p, u8 len);
	virtual void getIpodMessage(u8 *p, u8 len);
	virtual void getMediaMessage(u8 *p, u8 len);
	virtual void getBlcdMessage(u8 *p, u8 len);
	virtual void getAuxMessage(u8 *p, u8 len);
	virtual void getAuxScreenMessage(u8 *p, u8 len);
	virtual void getOsdMessage(u8 *p, u8 len);
	virtual void getExternalctrlMessage(u8 *p, u8 len);
	virtual void getTimerMessage(u8 *p, u8 len);
	virtual void getCenterMessage(u8 *p, u8 len);
	virtual void getServiceMessage(u8 *p, u8 len);
	virtual void getFlyJniSdkMessage(u8 *p, u8 len);
	 //��ҳ��ģ��
	 void setPage(u16 id);//����ָ��ҳ
	 void setPrePage(void);//��ǰһҳ
	 void setNextModule(void);//��ת����һģ�飨ѭ��ģ���б������ļ���
	 //��ʱ��
	 void initNativeTimer(void);
	 int setNativeTimer(int time, int mode, int timerId);
	 int deleteNativeTimer(int timerId);
	 void setNativeTimerHandler(timer_handler_function func);
	 static int nativeTimerHandler(timer_t timerId);
	 virtual int nativeTimerHandlerProcess(timer_t timerId);
	 //MTK ��Ƶɫ������//////////////////////////////////////////////////////////
	 void setBrightnessLevel(int level); //��Ļ����
	 void setContrastLevel(int level); //�Աȶ�
	 void setBackLightLevel(int level); //��������
	 void setHueLevel(int level);//ɫ��
	 void setSaturation(int level); //���Ͷ�
	 void setToAudioVideoVideoDisplaySetting(u8 p);
	 //������ϢԴͷ
	 void makeAndSendMessageToModule(u8 id, u8 arrivedModuleId, u8 *p, u8 len);
	 void getOtherModuleParam(u8 moduleId, u8 id, u8 *p, u8 *pLen);
	 u16 getCurPageId(void);
	 u16 getPrePageId(void);
	 u8 getCurExternalDeviceId(void);
	 u16 getCurAudioVideoChannel(void);
	 u16 getLastAudioVideoMediaChannel(void);
	 u16 getDefaultAudioVideoChannel(void);
	 bool getBackCarStatus(void);
	 bool getBackCarRadarStatus(void);
	 bool getSystemStandbyStatus(void);
	 u8 getSystemScreenStatus(void);
	 bool isAuxSelected(void);
     bool isTpmsSelected(void);
	 //�ǽӿڣ��ڲ��߼�����
	 void setGoBackVideoPageTimer(void);
	 void killGoBackVideoPageTimer(void);
	 //assist
	 const char* getModuleNameString(u8 p); 
	 const char* getAudioChannelString(u8 p); 
	 const char* getAudioVideoChannelString(u8 p);
	 int channel2ModuleId(u8 p);
	//�ⲿ����
	 void outCallBack_moduleParameterInit(void);
	 void outCallBack_moduleParameterReInit(void);

	 void outCallBack_readParameter(void);
	 void outCallBack_saveParameter(void);

	 moduleid_t outCallBack_locale_module_mid(void);
	 void outCallBack_getMyModuleParam(char id, u8 *p, u8 *pLen);
	
	 int outCallBack_analyseFlyNativeServerMessage(char *p, int len);
	 void outCallBack_analyseAgentMessage(moduleid_t id, u8 *p, u8 len);
	 void outCallBack_analyseAppMessage(u8 *p, u8 len);
	 void outCallBack_analyseOtherModuleMessage(moduleid_t id, u8 *p, u8 len);
	 void outCallBack_analyseHalMessage(halid_t hid, u8 cmd, u8 *p, u8 len);
	void outCallBack_analyseTimerHandleMessage(u8 *p, u8 len);
	 void outCallBack_timerHandleProc(int timerId);
	 void outCallBack_pageIdUiHaveGone(int timerId);
public:
	//��Ϣ����
	moduleParam_t m_stModuleParam;
	moduleMessage_t m_stModuleMessage;
	//������
	CFlyApp *m_pFlyApp;
	CFlyModule *m_pFlyModule;
	CFlyHal *m_pFlyHal;
	CFlyParam *m_pFlyParam;
};

#endif

