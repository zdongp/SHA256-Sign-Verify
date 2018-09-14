/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#ifndef __FLY_MODULE_H__
#define __FLY_MODULE_H__

#include "FlyParam.h"

//函数声明
typedef int (*timer_handler_function)(timer_t timerId);

class CFlyApp;
class CFlyHal;
class CFlyParam;
class CFlyModule : public CFlyObject
{
public:
	CFlyModule(void);
	virtual ~CFlyModule(void);

	virtual moduleid_t locale_module_mid(void) = 0;//得到本模块 ID
public:
	virtual void init(void) = 0;//类初始化
	virtual void deInit(void);//类析化
	void moduleParameterInit(void);//参数初始化
	void moduleParameterReInit(void);//参数重新初始化
	virtual void getMyModuleParam(char id, u8 *p, u8 *pLen);//外部取本模块的共享参数
	int analyseFlyNativeServerMessage(char *p, u8 len);//消息中心分发模块发来的消息
	void analyseOtherModuleMessage(moduleid_t id, u8 *p, u8 len);//其它模块数据进来
	void analyseTimerHandleMessage(u8 *p, u8 len);
	virtual void timerHandleProc(int timerId);//java ui 定时器处理函数
	virtual void pageIdUiHaveGone(int pageId);
	//启动复位重要接口
	virtual void getSystemCodeStartInitModule();//冷启动起来初始化 module
	virtual void getSystemCodeStartInitModuleFinish();//冷启动起来初始化所有 module 结束
	virtual void getAccOn() = 0;//收到 acc on 消息
	virtual void getAccOff() = 0;//收到 acc off 消息
	virtual void getWakeUp();//收到唤醒消息
	virtual void getReset();//收到复位消息
	virtual void getResetFactorySetting();//收到恢复出厂设置消息
	virtual void getStandbyOn();
	virtual void getStandbyOff();
	//得到对应模块的消息
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
	 //跳页跳模块
	 void setPage(u16 id);//跳到指定页
	 void setPrePage(void);//跳前一页
	 void setNextModule(void);//跳转到下一模块（循环模块列表配置文件）
	 //定时器
	 void initNativeTimer(void);
	 int setNativeTimer(int time, int mode, int timerId);
	 int deleteNativeTimer(int timerId);
	 void setNativeTimerHandler(timer_handler_function func);
	 static int nativeTimerHandler(timer_t timerId);
	 virtual int nativeTimerHandlerProcess(timer_t timerId);
	 //MTK 视频色彩设置//////////////////////////////////////////////////////////
	 void setBrightnessLevel(int level); //屏幕亮度
	 void setContrastLevel(int level); //对比度
	 void setBackLightLevel(int level); //背光亮度
	 void setHueLevel(int level);//色彩
	 void setSaturation(int level); //饱和度
	 void setToAudioVideoVideoDisplaySetting(u8 p);
	 //发送消息源头
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
	 //非接口，内部逻辑处理
	 void setGoBackVideoPageTimer(void);
	 void killGoBackVideoPageTimer(void);
	 //assist
	 const char* getModuleNameString(u8 p); 
	 const char* getAudioChannelString(u8 p); 
	 const char* getAudioVideoChannelString(u8 p);
	 int channel2ModuleId(u8 p);
	//外部调用
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
	//消息参数
	moduleParam_t m_stModuleParam;
	moduleMessage_t m_stModuleMessage;
	//类桥梁
	CFlyApp *m_pFlyApp;
	CFlyModule *m_pFlyModule;
	CFlyHal *m_pFlyHal;
	CFlyParam *m_pFlyParam;
};

#endif

