/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "FlyParam.h"

CFlyParam::CFlyParam(void)
{
}

CFlyParam::~CFlyParam(void)
{
}

void CFlyParam::deInit(void)
{

}

void CFlyParam::readParameter(void)
{
	LOGD("[%s]", __FUNCTION__);
}

void CFlyParam::saveParameter(void)
{
	LOGD("[%s]", __FUNCTION__);
}

char CFlyParam::__intToChar(int value)
{
	if(value >= 0 && value <= 9)
	{
		return (value + '0');
	}
	else if(value >= 10 && value <=15)
	{
		return (value + 'A' - 10);
	}
	else
	{
		return '\0';
	}
}

char CFlyParam::__charToInt(u8 c)
{
	if(c >= '0' && c <= '9')
	{
		return (c - '0');
	}
	else if(c >= 'A' && c <= 'F')
	{
		return (c + 10 - 'A');
	}
	else
	{
		return 0;
	}
}

int CFlyParam::bufferToString(char *p, int len, char *str)
{
	int n;
	int i , j;
	if(len <= 0 || len >= (PROPERTY_VALUE_MAX / 2))
	{
		return -1;
	}

	for(i = 0, j = 0; i < len; i++, j += 2)
	{
		str[j]   = __intToChar((p[i] & 0xF0) >> 4);
		str[j+1] = __intToChar((p[i] & 0x0F));
	}
	str[2 * len] = '\0';

	return (2 * len + 1);
}

int CFlyParam::stringToBuffer(char *str, char *p)
{
	int str_len = strlen(str);

	if(str_len <= 0)
		return 0;

	int i , j;
	for(i = 0, j = 0; j < str_len; i++, j += 2)
	{
		p[i]  = __charToInt(str[j]) << 4;
		p[i] += __charToInt(str[j + 1]);
	}

	return (str_len / 2);
}

//视频显示设置
void CFlyParam::initFatherParam(void)
{
	LOGD("[%s]", __FUNCTION__);

	m_nTimerIdGoBackVideoPage = 0;//定时器ID

	m_nGlobalBrightnessLevel = 0;//屏幕亮度
	m_nGlobalContrastLevel = 0;//对比度
	m_nGlobalBackLightLevel = 0;//背光亮度
	m_nGlobalHueLevel = 0;//色彩
	m_nGlobalSaturationLevel = 0;//饱和度
}

//保存
void CFlyParam::readVideoDisplaySettings(void)
{
	LOGD("[%s]", __FUNCTION__);

	char property[PROPERTY_VALUE_MAX] = {0};

	//亮度
	memset(property, 0, sizeof(property));
	property_get(FLY_VIDEO_BRIGHTNESS_SAVE_NAME, property, "0");
	sscanf(property, "%d", &m_nGlobalBrightnessLevel);
//	LOGD("[%s] m_nGlobalBrightnessLevel = [%d]", __FUNCTION__, m_nGlobalBrightnessLevel);
	//对比度
	memset(property, 0, sizeof(property));
	property_get(FLY_VIDEO_CONTRAST_SAVE_NAME, property, "0");
	sscanf(property, "%d", &m_nGlobalContrastLevel);
//	LOGD("[%s] m_nGlobalContrastLevel = [%d]", __FUNCTION__, m_nGlobalContrastLevel);
	//背光亮度
	memset(property, 0, sizeof(property));
	property_get(FLY_VIDEO_BACKLIGHT_SAVE_NAME, property, "0");
	sscanf(property, "%d", &m_nGlobalBackLightLevel);
//	LOGD("[%s] m_nGlobalBackLightLevel = [%d]", __FUNCTION__, m_nGlobalBackLightLevel);
	//色彩
	memset(property, 0, sizeof(property));
	property_get(FLY_VIDEO_HUE_SAVE_NAME, property, "0");
	sscanf(property, "%d", &m_nGlobalHueLevel);
//	LOGD("[%s] m_nGlobalHueLevel = [%d]", __FUNCTION__, m_nGlobalHueLevel);
	//饱和度
	memset(property, 0, sizeof(property));
	property_get(FLY_VIDEO_SATURATION_SAVE_NAME, property, "0");
	sscanf(property, "%d", &m_nGlobalSaturationLevel);
//	LOGD("[%s] m_nGlobalSaturationLevel = [%d]", __FUNCTION__, m_nGlobalSaturationLevel);

}

void CFlyParam::saveVideoDisplaySettings(void)
{
	LOGD("[%s]", __FUNCTION__);

	char property[PROPERTY_VALUE_MAX] = {0};

	//亮度
	memset(property, 0, sizeof(property));
	sprintf(property, "%d", m_nGlobalBrightnessLevel);
	property_set(FLY_VIDEO_BRIGHTNESS_SAVE_NAME, property);
	LOGD("[%s] m_nGlobalBrightnessLevel = [%d]", __FUNCTION__, m_nGlobalBrightnessLevel);
	//对比度
	memset(property, 0, sizeof(property));
	sprintf(property, "%d", m_nGlobalContrastLevel);
	property_set(FLY_VIDEO_CONTRAST_SAVE_NAME, property);
	LOGD("[%s] m_nGlobalContrastLevel = [%d]", __FUNCTION__, m_nGlobalContrastLevel);
	//背光亮度
	memset(property, 0, sizeof(property));
	sprintf(property, "%d", m_nGlobalBackLightLevel);
	property_set(FLY_VIDEO_BACKLIGHT_SAVE_NAME, property);
	LOGD("[%s] m_nGlobalBackLightLevel = [%d]", __FUNCTION__, m_nGlobalBackLightLevel);
	//色彩
	memset(property, 0, sizeof(property));
	sprintf(property, "%d", m_nGlobalHueLevel);
	property_set(FLY_VIDEO_HUE_SAVE_NAME, property);
	LOGD("[%s] m_nGlobalHueLevel = [%d]", __FUNCTION__, m_nGlobalHueLevel);
	//饱和度
	memset(property, 0, sizeof(property));
	sprintf(property, "%d", m_nGlobalSaturationLevel);
	property_set(FLY_VIDEO_SATURATION_SAVE_NAME, property);
	LOGD("[%s] m_nGlobalSaturationLevel = [%d]", __FUNCTION__, m_nGlobalSaturationLevel);

}
