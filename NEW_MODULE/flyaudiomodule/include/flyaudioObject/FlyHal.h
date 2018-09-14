/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#ifndef __FLY_HAL_H__
#define __FLY_HAL_H__

#include "FlyParam.h"

class CFlyHal : public CFlyObject
{
public:
	CFlyHal(void);
	virtual ~CFlyHal(void);
public:
	/**
	 * init
	 * ��ʼ�������������������ڶ���֪ͨ����һ����֪ͨ��ʼ���������ڶ���֪ͨ��ʼ�� hal, ������֪ͨ��ʼ����ɣ�
	*/
	virtual void init(void) = 0;
	virtual void deInit(void);
	virtual void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam) = 0;
	virtual void analyseHalMessage(halid_t halId, u8 cmd, u8 *p, u8 len);
	virtual void analyseAgentMessage(moduleid_t id, u8 *p, u8 len);	

	void makeAndSendMessageToHal(moduleid_t halId, u8 *p, u32 len);






public:
	 halMessage_t m_stHalMessage;
	 //������
	 CFlyApp *m_pFlyApp;
	 CFlyModule *m_pFlyModule;
	 CFlyHal *m_pFlyHal;
	 CFlyParam *m_pFlyParam;
};

#endif
