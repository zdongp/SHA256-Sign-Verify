/*
	author: YanBin Deng
	  date: 2014/09/01  
*/

#pragma once

#include "FlyApp.h"
#include "FlyModule.h"
#include "FlyHal.h"
#include "FlyParam.h"

#include "FatApp.h"
#include "FatModule.h"
#include "FatHal.h"
#include "FatParam.h"

#define CMD_TO_AUTOMATE_MAX_LEN 256
#define CMD_TO_INFORS_MAX_LEN 100

typedef unsigned short		unicode16_t;
typedef int 	uni16_size_t;

class CFatApp;
class CFatModule;
class CFatHal;
class CFatParam : public CFlyParam
{
	SINGLETON_IMPLEMENT(CFatParam)
private:
	CFatParam(void);
public:
	 ~CFatParam(void);

	void init(void);
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);

	void readParameter(void);
	void saveParameter(void);

	uni16_size_t uni16_strlen(const unicode16_t *uni16);
	unicode16_t ansi_to_unicode16(const unsigned char ansi);
	uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);
	unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
	unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src);
	uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);

private:
	CFatApp *m_pFatApp;
	CFatModule *m_pFatModule;
	CFatHal *m_pFatHal;
	CFatParam *m_pFatParam;
};




