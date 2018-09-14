/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#ifndef __FLY_APP_H__
#define __FLY_APP_H__

#include "FlyParam.h"

//�����Android��������UIЭ��.doc
#define UI_CONTROL_TYPE_DIGITAL		0x00   //������
#define UI_CONTROL_TYPE_ANALOG		0x01   //ģ����
#define UI_CONTROL_TYPE_SERIAL		0x02   //������ 
#define UI_CONTROL_TYPE_PARAMSET	0xFF   //��������
#define UI_CONTROL_TYPE_AGENT       0x03

class CFlyApp : public CFlyObject
{
public:
	CFlyApp(void);
	virtual ~CFlyApp(void);
public:
		/**
	 * init
	 * 初始化函数，冷启动起来第二次通知（第一次是通知初始化参数，第二次通知初始化 hal, 第三次通知初始化完成）
	*/
	virtual void init(void) = 0;
	virtual void deInit(void);
	virtual void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam) = 0;
	/**
	 * analyseAppMessage
	 * UI 的点击事件
	*/
	void analyseAppMessage(u8 *p, u8 len);
	/**
	 * analyseAgentMessage
	 * 来自 flyAudioService, 最终是 MTK 的服务, 如 DVD, BT, Aux
	*/
	void analyseAgentMessage(moduleid_t id, u8 *p, u8 len);
    virtual void processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	virtual void appCmdCtrl(u8 *p, u8 len);
	/**
	 * setDigitalData
	 * 控制控件的两种状态，比如两张图片的控制，默认为 false 态
	*/
	void setDigitalData(u32 id, bool b);
	/**
	 * setAnalogData
	 * 控制有多种状态的控件, 是 setDigitalData 的超级
	*/
	void setAnalogData(u32 id, u32 a);
	/**
	 * setGroupNumber
	 * 设置显示第几组图片
	 * 例如：DVD中的Folder_ITEM就是这样控制，0为空，1为文件夹，2为文件，3为正在播放
	 */
	void setGroupNumber(u32 id, u8 i);
	/**
	 * setProgressRange：
	 * 设置滚动条的最大值，其对应设置滚动条位置值是用 setAnalogData()
	 */
	void setProgressRange(u32 id, int r);	// 原来是setValues()

/**
	 * setSerialData
	 * 传送 unicode 字符串
	*/
	void setSerialData(u32 id, u8 *p, u32 len);
	/**
	 * setAnsiSerialData
	 * 传送 Ansi 字符串
	*/
	void setAnsiSerialData(u32 id, u8 *p, u32 len);
	/**
	 * setUtf8SerialData
	 * 传送 utf8 字符串
	*/
	void setUtf8String(u32 id, u8 *p, u32 len);//新接口，setUtf8SerialData接口不够健壮
	void setUtf8SerialData(u32 id, u8 *p, u32 len);
	/**
	 * setStringById
	 * 设置对应 ID 的字符串 
	*/
	void setStringById(u32 id, u32 stringId);
    
    
    void setMixedExternalAppVoiceState(u8 status);
    //balance 
    void setExProgressSinglePos(u32 ctrlId, u8 direct, int pos);
	/**
	 * setVisible
	 * 设置对像可不可见
	*/
	void setVisible(u32 id, bool b);
	/**
	 * setCtrlEnable
	 * 设置对像能不能控
	*/
	void setCtrlEnable(u32 id, bool b);
	/**
	 * setUpdateUI
	 * 设置刷新，比如先设置为 false 关掉刷新，然后把各个对象的状态传给 UI, 然后设置为 true 打开刷新，即可全部一起刷新
	*/
	void setUpdateUI(bool b);
	void setCommand(u32 id, u8 *p, u32 len);
	//定时器
	/**
	 * setTimer
	 * JNI回调函数：请求创建新的Timer
	 * @param moduleId：模块号
	 * @param timeOut：定时器时间,单位为毫秒
	 * @param mode：0为启动一次定时器，1为循环定时器
	 * @return int：返回定时器ID号
	*/
	int setTimer(int moduleID, int timeOut, int timerMode);
	/**
	 * killTimer
	 * JNI回调函数：取消定时器
	 * @param timerId：定时器ID号
	 * @return int：0:成功
	*/
	int killTimer(int timerID);

    //通知ＵＩ　写play属性
    void setPlayEnable(bool b);



private:
	/*
	 * setPage
	 * JNI回调函数：跳页
	 * @pageId: 页ID，两字节 
	 * @return int: 0 成功，-1 失败 
	*/
	int setPage(int pageId);


public:
    int setVolume(int type,int value,int flags1);
	void makeAndSendMessageToUI(u32 id, u8 ctrlType, u8 *p, u32 len);
	void makeAndSendToAgent(u8 id, u8 *inBuf, u32 inLen, u8 *outBuf, u32 outLen);

	// assist
	const char* getMouseMessageType(u8 p);

	//color setting page
	void clickColorSettingPageCtrlBackGround(E_MOUSE_STATUS e);
	//饱和度
	void clickColorSettingPageHueUp(E_MOUSE_STATUS e);
	void clickColorSettingPageHueDown(E_MOUSE_STATUS e);
	//色调
	void clickColorSettingPageSaturationUp(E_MOUSE_STATUS e);
	void clickColorSettingPageSaturationDown(E_MOUSE_STATUS e);
	//对比度
	void clickColorSettingPageContrastUp(E_MOUSE_STATUS e);
	void clickColorSettingPageContrastDown(E_MOUSE_STATUS e);
	//亮度
	void clickColorSettingPageBrightnessUp(E_MOUSE_STATUS e);
	void clickColorSettingPageBrightnessDown(E_MOUSE_STATUS e);

public:
	appMessage_t m_stAppMessage;
	agentMessage_t m_stAgentMessage;
	//������
	CFlyApp *m_pFlyApp;
	CFlyModule *m_pFlyModule;
	CFlyHal *m_pFlyHal;
	CFlyParam *m_pFlyParam;
};

#endif
