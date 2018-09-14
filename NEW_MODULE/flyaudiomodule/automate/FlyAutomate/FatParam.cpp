/*
	author: YanBin Deng
	  date: 2014/09/01  
*/

#include "FatParam.h"

extern CFlyModule *g_pFlyModule;

CFatParam::CFatParam(void)
{
}

CFatParam::~CFatParam(void)
{
}

void CFatParam::init(void)
{

}

void CFatParam::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
{
	m_pFatApp	 = (CFatApp *)pFlyApp; 
	m_pFatModule = (CFatModule *)pFlyModule; 
	m_pFatHal	 = (CFatHal *)pFlyHal; 
	m_pFatParam  = (CFatParam *)pFlyParam; 

	m_pFlyApp    = pFlyApp;
	m_pFlyModule = pFlyModule;
	m_pFlyHal    = pFlyHal;
	m_pFlyParam  = pFlyParam;
}

void CFatParam::readParameter(void)
{
	LOGD("[%s]", __FUNCTION__);

	
}

void CFatParam::saveParameter(void)
{
	LOGD("[%s]", __FUNCTION__);

	
}

uni16_size_t CFatParam::uni16_strlen(const unicode16_t *uni16)
{
	return 0;
}
unicode16_t CFatParam::ansi_to_unicode16(const unsigned char ansi)
{
	return 0;
}
uni16_size_t CFatParam::ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16)
{
	int nSrcLen = strlen((char*)ansi);
	int nUni16Len = nSrcLen*2+2;
	int nRetLen = utf8_2_ucs2(ansi, nSrcLen, (u8*)uni16, nUni16Len);
	
	return (nRetLen/2);
}
unicode16_t *CFatParam::uni16_strcpy(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
unicode16_t * CFatParam::uni16_strcat(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
uni16_size_t CFatParam::utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16)
{
	return 0;
}


