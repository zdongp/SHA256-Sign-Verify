/*
	author: YanBin Deng
	  date: 2014/09/19
*/
#pragma once
#include "FlyPropertyDefine.h"

//////////////////////////////////////////////////////////////////////////
//��������
enum E_WIDGET_CTRL{WIDGET_CTRL_DISABLE,WIDGET_CTRL_ENABLE};
enum E_PIC_WIDGET_STATUS{PIC_WIDGET_STATUS_DEFAULT, PIC_WIDGET_STATUS_ACTIVATED, PIC_WIDGET_STATUS_DISABLE};
//
enum E_MOUSE_STATUS{MOUSE_STATUS_DOWN, MOUSE_STATUS_UP = 0x10,
	MOUSE_STATUS_TIMER = 0x20, MOUSE_STATUS_CMD = 0xFE, MOUSE_STATUS_UNKNOW};

//��ʱ������
#define TIMER_TYPE_ONE_TIME		0
#define TIMER_TYPE_CYCLE		1
//��ʱʱ��
#define TIME_INTERVAL_GO_BACK_VIDEO_PAGE_FROM_OSD_VIDEO	4000
//////////////////////////////////////////////////////////////////////////
//getMyModuleParam
//Aux
#define FLY_AUX_PARAM_SIGNAL		0x00
//backcar
#define FLY_BACK_CAR_PARAM_BACK_CAR_STATUS				0x01
#define FLY_BACK_CAR_PARAM_BACK_CAR_RADAR_STATUS		0x02
//audio video
#define FLY_AUDIO_VIDEO_PARAM_SOUND_CUR_CHANNEL			0x01
#define FLY_AUDIO_VIDEO_PARAM_SOUND_DEFAULT_CHANNEL		0x02
#define FLY_AUDIO_VIDEO_PARAM_SOUND_PRE_CHANNEL			0x03
#define FLY_AUDIO_VIDEO_PARAM_THREEMEDIA_PLAYSTATUS     0x04
//dnv
#define FLY_DNV_PARAM_IS_DNV_PAGE						0x01
//��Ƶ�����������
#define FLY_VIDEO_SETTING_ONE_STEP_INTERVAL		5//5
#define FLY_VIDEO_SETTING_MAX_VALUE				100
//////////////////////////////////////////////////////////////////////////
//�绰״̬
enum E_PHONE_STATUS{PHONE_STATUS_FREE, PHONE_STATUS_CALL_IN, PHONE_STATUS_CALL_OUT, PHONE_STATUS_SPEAKING,
	PHONE_STATUS_CALL_OUTING, PHONE_STATUS_UNINIT, PHONE_STATUS_UNKNOW};

enum E_EXTERNAL_DEVICE
{
	EXTERNAL_DEVICE_DVR,
	EXTERNAL_DEVICE_TV_TPMS,
	EXTERNAL_DEVICE_DNV,
	EXTERNAL_DEVICE_AMBIENT_LED,
	EXTERNAL_DEVICE_UNKNOW = 0xff
};








