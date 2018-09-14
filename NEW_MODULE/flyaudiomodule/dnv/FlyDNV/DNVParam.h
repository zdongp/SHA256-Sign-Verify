/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once

#include "FlyApp.h"
#include "FlyModule.h"
#include "FlyHal.h"
#include "FlyParam.h"

#include "DNVDefine.h"

#include "DNVApp.h"
#include "DNVModule.h"
#include "DNVHal.h"
#include "DNVParam.h"

typedef unsigned short		unicode16_t;
typedef int 	uni16_size_t;

class CDNVApp;
class CDNVModule;
class CDNVHal;
class CDNVParam : public CFlyParam
{
	SINGLETON_IMPLEMENT(CDNVParam)
private:
	CDNVParam(void);
public:
	 ~CDNVParam(void);

	void init(void);
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);

	void readParameter(void);
	void saveParameter(void);

public:
	uni16_size_t uni16_strlen(const unicode16_t *uni16);
	unicode16_t ansi_to_unicode16(const unsigned char ansi);
	uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);
	unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
	unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src);
	uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);

private:
	CDNVApp *m_pDNVApp;
	CDNVModule *m_pDNVModule;
	CDNVHal *m_pDNVHal;
	CDNVParam *m_pDNVParam;
};






