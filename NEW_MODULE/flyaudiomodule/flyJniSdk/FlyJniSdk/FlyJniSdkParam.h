
#pragma once

#include "FlyApp.h"
#include "FlyModule.h"
#include "FlyHal.h"
#include "FlyParam.h"

#include "FlyJniSdkDefine.h"

#include "FlyJniSdkApp.h"
#include "FlyJniSdkModule.h"
#include "FlyJniSdkHal.h"
#include "FlyJniSdkParam.h"

/***********Message Type*********/
#define RESPONE_CHANGE_STATE 		0x00
#define CONTROL_MESSAGE			0x01


typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;


class CFlyJniSdkApp;
class CFlyJniSdkModule;
class CFlyJniSdkHal;
class CFlyJniSdkModuleBt;
class CFlyJniSdkModuleRadio;
//moupeng 2015/7/25
class CFlyJniSdkModuleAudioVideo;
//moupeng 2015/7/31
class CFlyJniSdkModuleDvd;

class CFlyJniSdkModuleSystem;
class CFlyJniSdkModuleKey;
class CFlyJniSdkModuleExtcar;
class CFlyJniSdkModuleFlyJniSdk;
class CFlyJniSdkModuleAc;
class CFlyJniSdkModuleMedia;
class CFlyJniSdkModuleAudioCtrl;
class CFlyJniSdkModuleExtcarHondaTsu;
class CFlyJniSdkModuleExternalCtrl;

class CFlyJniSdkParam : public CFlyParam
{
	SINGLETON_IMPLEMENT(CFlyJniSdkParam)
private:
	CFlyJniSdkParam(void);
public:
	 ~CFlyJniSdkParam(void);

	void init(void);
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);

	void readParameter(void);
	void saveParameter(void);

public:
	CFlyJniSdkModuleBt *m_pFlyJniSdkModuleBt;
	CFlyJniSdkModuleRadio *m_pFlyJniModuleRadio;
	//moupeng 2015/7/25
	CFlyJniSdkModuleAudioVideo *m_pFlyJniModuleAudioVideo;
	//moupeng 2015/7/31
	CFlyJniSdkModuleDvd *m_pFlyJniModuleDvd;
	//moupeng 2015/7/31
	CFlyJniSdkModuleSystem *m_pFlyJniModuleSystem;
	CFlyJniSdkModuleKey *m_pFlyJniModuleKey;
	CFlyJniSdkModuleExtcar *m_pFlyJniModuleExtcar;
	CFlyJniSdkModuleFlyJniSdk *m_pFlyJniModuleFlyJniSdk;
	CFlyJniSdkModuleAc *m_pFlyJniSdkModuleAc;
	CFlyJniSdkModuleMedia *m_pFlyJniSdkModuleMedia;
	CFlyJniSdkModuleAudioCtrl *m_pFlyJniSdkModuleAudioCtrl;
	CFlyJniSdkModuleExtcarHondaTsu *m_pFlyJniSdkModuleExtcarHondaTsu;
	CFlyJniSdkModuleExternalCtrl *m_pFlyJnisdkModuleExternalCtrl;
public:	
	uni16_size_t uni16_strlen(const unicode16_t *uni16);
	unicode16_t ansi_to_unicode16(const unsigned char ansi);
	uni16_size_t ansi_str_to_unicode16(const unsigned char *ansi, unicode16_t *uni16);
	unicode16_t * uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
	unicode16_t * uni16_strcat(unicode16_t *dest, const unicode16_t *src);
	uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);	

private:
	CFlyJniSdkApp *m_pFlyJniSdkApp;
	CFlyJniSdkModule *m_pFlyJniSdkModule;
	CFlyJniSdkHal *m_pFlyJniSdkHal;
	CFlyJniSdkParam *m_pFlyJniSdkParam;


	
};








