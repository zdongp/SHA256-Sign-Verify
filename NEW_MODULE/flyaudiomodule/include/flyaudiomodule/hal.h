#ifndef __HAL_H__
#define __HAL_H__


/*
#include <hardware/hardware.h>


struct fly_hw_module_t {
	struct hw_module_t common;
};

struct global_control_device_t{
	struct hw_device_t common;
	int (*global_read )( unsigned char *read_buf,  int buf_len);
	int (*global_write)( unsigned char *write_buf, int buf_len);
	int (*global_ioctl)( int cmd, unsigned char *arg);
	int (*global_close)();
} ;
*/


#define HAL_DEVICE_NAME_AUDIO 		"audio"
#define HAL_DEVICE_NAME_VIDEO 		"video"
#define HAL_DEVICE_NAME_RADIO 		"radio"
#define HAL_DEVICE_NAME_DVD   		"dvd"
#define HAL_DEVICE_NAME_BT    		"bt"
#define HAL_DEVICE_NAME_KEY   		"key"
#define HAL_DEVICE_NAME_SYSTEM 		"system"
#define HAL_DEVICE_NAME_EXDISPLAY 	"exdisplay"
#define HAL_DEVICE_NAME_XMRADIO 	"xmradio"
#define HAL_DEVICE_NAME_TPMS   		"tpms"
#define HAL_DEVICE_NAME_TV     		"tv"
#define HAL_DEVICE_NAME_GLOBAL 		"global"
#define HAL_DEVICE_NAME_AC     		"ac"
#define HAL_DEVICE_NAME_EXTCAR     	"FlyFA"
#define HAL_DEVICE_NAME_DVR			"dvr"
#define HAL_DEVICE_NAME_OSD			"flyosd"
#define HAL_DEVICE_NAME_DNV			"nv"
#define HAL_DEVICE_NAME_MODULE_ROUTE "moduleroute"
#define HAL_DEVICE_NAME_HONDA_TSU    "hondatsu"

#define HAL_ID_GLOBAL 			0x00
#define HAL_ID_SYSTEM 			0x01
#define HAL_ID_AUDIO 			0x02
#define HAL_ID_VIDEO 			0x03
#define HAL_ID_KEY   			0x04
#define HAL_ID_EXDISPLAY 		0x05
#define HAL_ID_OSD_BUTTEN 		0x06
#define HAL_ID_OSD_SETVIDEO		0x07

#define HAL_ID_RADIO 			0x10
#define HAL_ID_BACK             0x11
#define HAL_ID_DVD   			0x20
#define HAL_ID_BT    			0x30
#define HAL_ID_XMRADIO 			0x40
#define HAL_ID_TPMS   			0x50
#define HAL_ID_MODULE_ROUTE		0x51
#define HAL_ID_TV     			0x60
#define HAL_ID_AC     			0x70
#define HAL_ID_EXTCAR     		0x80
#define HAL_ID_EXTCAR_HONDA_RSU 0x81
#define HAL_ID_IPOD     		0x90
#define HAL_ID_BLCD         	0x91
#define HAL_ID_SERVICE			0xFF
#define HAL_ID_DVR				0x92
#define HAL_ID_NV				0x93
#define HAL_ID_AUTOMATE			0xF0

#endif
