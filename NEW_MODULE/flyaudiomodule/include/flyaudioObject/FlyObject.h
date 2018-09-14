/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#ifndef __FLY_OBJECT_H__
#define __FLY_OBJECT_H__

//system
#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <string.h>
#include <string>
#include <time.h> 
#include <stdio.h>
#include <android/log.h>
#include <commonFunc.h>
#include <ctype.h>
#include <stdarg.h>
#include <set>
#include <vector>
#include<queue>
#include <list>
#include <map>
//flyaudio
#include "global.h"
#include "FlyDefine.h"
#include "hal.h"
#include "messageQueue.h"
#include "moduleParamStruct.h"

using namespace std;

// �ú궨�����ڴ�����һ��
#define SINGLETON_IMPLEMENT(classname) \
public: \
static classname* GetInstance(void) \
{ \
	static classname instance; \
	return &instance; \
}

class CFlyObject
{
public:
	CFlyObject(void);
	virtual ~CFlyObject(void);

	//������Ϣ���
	void outPutLog(const char *pFunName, const char *pArgName, u8 *pArg, int len);
	void outPutProcessAndThreadId(void);

	int ucs2_2_utf8(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
	int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
	int ansi_str_to_unicode16(u8 *ansi, u16 *uni16);
private:
	int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput, int outSize);
	int enc_get_utf8_size(const unsigned char pInput);
	int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
};

#endif
