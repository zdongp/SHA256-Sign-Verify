  #ifndef __PARAM_ID_H__
#define __PARAM_ID_H__

// SYSTEM��0x02��
#define LCD_STATE					0x01		/* ����״̬ */
#define	 SLEEP_STATE					0x02		/* ���״̬ */
#define SYS_TV_EXIST_STATE_DEVICE	0x03		/*TV���Ƿ����*/
#define SYSTEM_AUX_VIDEO_STATE		0X04        /*����������Ƶ״̬*/
#define DIALIN_3G					0x05		/*3G�Ƿ�����*/
#define IS_INGPS_STATE				0x06 
#define SYSTEM_IS_AUX				0x07		/*�Ƿ����AUX*/
#define SYSTEM_IS_DVRORTV			0x08        /*TV or DVR*/
#define SYSTEM_SET_OPTION_EXTCAR_VOICE_PROMPT_STATUS       0x09        /*�г���Ϣ������ʾ*/
#define SYSTEM_SET_BACKCAR_DETECTEENABLE_STATUS 0X10 /*����������Ƶ����*/
#define SYSTEM_SET_BackVideoRefLineEnable	0x11
#define SYSTEM_SET_STARTUPVOL       0x0A       /* startup volume*/
#define SYSTEM_PARAM_ID_BACKMODE	 0x0B
#define CUR_PAGE					0xF0		/*��ǰҳ*/
#define PREV_PAGE					0xF1		/*ǰһҳ*/
#define SYSTEM_SET_DNV_DETECTEENABLE_STATUS 0xF2
#define	 MCU_INFO					0x12
#define MEPG_INFO					0x13
#define FID_INFO					0x14 //UUID
#define BATTERY_VALUE				0x15
#define SYSTEM_TRIGGER_TYPE			0x20 // trigger type
#define SYSTEM_HOMEPAGE_OSD_VISIBLE	 0x21 // 
#define SYSTEM_BRAKECAR_STATUS	 0x22 // 
#define SYSTEM_PRADO_RADAR_KEY_SWITCH_STATUS	 0x23 // 
#define SYSTEM_PRADO_RADAR_UI_SWITCH_STATUS  0x24
#define SYSTEM_STANDBY_STATUS  0x25
#define SYSTEM_DVR_PROTOCOL_MODE  0x26
#define SYSTEM_CVBS_OR_USB_SWITCH 0x27



// AUDIOVIDEO��0x01��
#define	SOUND_CHANNEL				0x01		/*��ǰ��� */
#define DEFAULT_CHANNEL       		0x02        /*Ĭ��ͨ��*/
#define OLD_SOUND_CHANNEL			0x03		/*ǰһ��ͨ��*/
#define MEDIA_PLAY_STATE            0x04        /*Media����״̬*/
#define SOUND_CARD_STATE            0x05        /*��״̬*/
#define IS_CANJUMPAUX				0x06        /*���������Ƿ��ܽ���AUX*/
#define CUR_VOLUME					0x07
#define CUR_EQUALIZER				0x08
#define CUR_FRONT_REAR_BALANCE		0x09
#define CUR_LEFT_RIGHT_BALANCE		0x0a
#define MAX_VOLUME					0x0b
#define LAST_MEDIA_CHANNEL					0x0c


// KEY��0x03��
#define	KEYACTION_DROPDOWNOSD		0x01
//CENTER
#define	CENTER_AGREEPAGE_ISHIDE		0x01

// RADIO��0x04��
#define CUR_CHANNEL					0x01
#define CUR_FREQ					0x02

// DVD��0x05��
#define CUR_PLAY_STATUS 			0x01
#define CUR_DISC_TYPE				0x02
#define CUR_TRACK_NUM				0x03
#define CUR_CHAPTER_NUM				0x04


// TMPS��0x06��
#define PAIR_STATUS					0x01

// BACK������Ƶ��0x07��
#define	BACK_CAR_STATE				0x01		/* ����״̬ */
#define	BACK_CAR_RADAR_STATUS		0x02

// TV��0x08��

// BLUETOOTH��0x09��
#define BT_A2DP_SUPPORT             0x01       /*A2DP Support state */
#define BT_MOBILE_STATUS            0X02       /*�����绰״̬*/
#define BT_POWER_STATUS				0x03
#define BT_HF_CONNECT_STATUS		0x04
#define BT_VERSION_INFO   0x05
#define BT_ADDR   0x06
#define BT_NATIONAL_NAME		       0x07
#define BT_IS_PAIR_BOX		       0x08


// IPOD��0x0A��
#define	IPOD_DEVICE_EXIST_STATE		0x01		/* �Ƿ���IPOD����״̬ */

// MEDIA��0x0B��
#define	MEDIA_PLAY_STATUS			0x01
#define	MEDIA_CUR_TRACK				0x02
#define MEDIA_USB1_STATUS           0x03


// BLCD��0x0C��

// AUX��0x0D��

//OSD
#define OSD_EVENT					0x01

//AUXSCREEN��0x0E��
#define	AUXSCREEN_EXIST_STATE	0x01			/* �Ƿ��и���С�� */

//-->EXTCAR
#define EXTCAR_PARAM_DZ_SCREEN_RECEIVE_CHINESE	0x01
#define EXTCAR_CAR_MODELS 0x02
#define EXTCAR_CAR_GEARS 0x03
#define EXTCAR_CAR_PARKING_ACTIVETY_STATE 0x04

//<--

//SYNC
// CENTER��0xFE��
//SERVICE
#define BARCODE_INFO				0x01
#define IMEI_INFO					0x02
#define CAR_MAC_INFO				0x03
#define WIFI_CONNECT_STATUS		0x04
#define NETWORK_SIGNAL_WIFI		0x05
#define NETWORK_SIGNAL_4G		0x06
#define WLAN_MAC_INFO				0x07
#define MEMORY_USAGE_SD1			0x08
#define SDCARD1_STATUS			0x09
#define TOTAL_SIZE_SD1			0x0A
#define MEMORY_USAGE_SD0			0x0B
#define TOTAL_SIZE_SD0			0x0C
#define NETWORK_WIFI_STATUS		0x0D
#define NETWORK_4G_STATUS			0x0E


//DVR

//speech
#define SPEECH_STATE				0x01

#endif
