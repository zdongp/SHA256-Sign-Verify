#ifndef __PARAM_H__
#define __PARAM_H__

//#define EMERGENCY

#define SIZE_SET_APPLY_COUNTS 5
#define SIZE_MAP_MAXLEN	32
#define STRING_MAX_LEN	128
#define PATH_STRING_MAX_LEN	128

#define USB_CAMERA_VIDEO_LEVEL 	10

#define USB_CAMERA_KEEP_TIMES_MIN 	2
#define USB_CAMERA_KEEP_TIMES_MAX 	10


enum E_DVR_USB_CAMERA_SET_VIDEO_TPYE{TPYE_VIDEO_COLOR = 0X01,TPYE_VIDEO_CHROMINANCE = 0X02,TPYE_VIDEO_BRIGHTNESS = 0X03,TPYE_VIDEO_CONTRAST_GAUGE = 0X04};

enum E_SELECT_CTRL{SELECT_CTRL_UP, SELECT_CTRL_DOWN, SELECT_CTRL_UNKNOW};
enum E_DVR_USB_CAMERA_RESOLUTION
{
	DVR_USB_CAMERA_RESOLUTION_480X272P = 0,
	DVR_USB_CAMERA_RESOLUTION_1280X720P = 1,
	DVR_USB_CAMERA_RESOLUTION_1920X1080P = 2,
	DVR_USB_CAMERA_RESOLUTION_640X480P = 3,
	DVR_USB_CAMERA_RESOLUTION_640X360P = 4,
	DVR_USB_CAMERA_RESOLUTION_400X480P = 5,
	DVR_USB_CAMERA_RESOLUTION_320X240P = 6
};
enum E_DVR_USB_CAMERA_RECORDING_TIMES{CAMERA_RECORDING_TIMES_2M = 2,CAMERA_RECORDING_TIMES_3M = 3,CAMERA_RECORDING_TIMES_5M = 5,CAMERA_RECORDING_TIMES_10M = 10};
enum E_DVR_USB_CAMERA_STORAGE_SIZE{CAMERA_STORAGE_SIZE_2G = 2,CAMERA_STORAGE_SIZE_4G = 4,CAMERA_STORAGE_SIZE_8G = 8,CAMERA_STORAGE_SIZE_16G = 16};
enum E_DVR_USB_CAMERA_STORAGE_PATH{CAMERA_STORAGE_PATH_SDCARD = 0,CAMERA_STORAGE_PATH_FLASH = 1};
enum E_DVR_USB_CAMERA_EXIST_DEVICE{CAMERA_NO_DEVICE = 0,CAMERA_YES_DEVICE = 1};
enum E_DVR_USB_CAMERA_BRAND{CAMERA_BRAND_UNKNOW = 0,CAMERA_BRAND_SONIX = 1};

#define D_IS_SUPPORT_RESOLUTION_MAX 7
#define STRING_CAMERA_RESOLUTION_480X272P "480x272"
#define STRING_CAMERA_RESOLUTION_1280X720P "1280x720"
#define STRING_CAMERA_RESOLUTION_1920X1080P "1920x1080"
#define STRING_CAMERA_RESOLUTION_640X480P "640x480"
#define STRING_CAMERA_RESOLUTION_640X360P "640x360"
#define STRING_CAMERA_RESOLUTION_400X480P "400x480"
#define STRING_CAMERA_RESOLUTION_320X240P "320x240"

#define DVRTOCAMERA_SET_VIDEOPARAM_INC 0
#define DVRTOCAMERA_SET_VIDEOPARAM_DEC 1

#define DVRTOCAMERA_VIDEOPARAM_COLOR 1
#define DVRTOCAMERA_VIDEOPARAM_CHROMINANCE 2
#define DVRTOCAMERA_VIDEOPARAM_BRIGHTNESS 3
#define DVRTOCAMERA_VIDEOPARAM_CONTRASTGAUGE 4


#define DVR_USB_CAMERA_FILE_PATH_FLASH "/storage/sdcard0/camera_rec/"
#define DVR_USB_CAMERA_FILE_PATH_SDCARD "/storage/sdcard1/camera_rec/"

#define DVR_USB_CAMERA_DEVICES_NUMBER 2
#define USB_CAMERA_WHICH_R 0 
#define USB_CAMERA_WHICH_F 1 

enum E_DVR_USB_CAMERA_WHICH_ROAD{
	USB_CAMERA_WHICH_ROAD_SINGLE, 
	USB_CAMERA_WHICH_ROAD_DOUBLE, 
	USB_CAMERA_WHICH_ROAD_EMERGENCY_COLLISION, 
	USB_CAMERA_WHICH_ROAD_UNKNOW
};

typedef struct {
	bool bIsUsbCameraRecording;
}dvr_usb_camera_which_one;

typedef struct {
	bool bIsChangHe;
	u8 uDvrModule_is_T123;
	bool bDVRDriverInit;
	bool bDVRModuleState;//Ä£¿éÊÇ·ñ´æÔÚ
	int	 m_iPresentMode;
	bool bEnterDVRModuleMark;
	bool bStopVideo;//Â¼ÖÆ¡¢ÔÝÍ£×´Ì¬
	u16  m_wCurrentPage;
	bool bMute;
	bool bPlayOrPause;
	bool bBrake;
	int m_LMode;

	bool m_bSystemStartNeedSyncTimeToDNV;

	int m_iUsbCameraSettingParam[SIZE_SET_APPLY_COUNTS];
	E_DVR_USB_CAMERA_RESOLUTION emUsbCameraResolution;
	E_DVR_USB_CAMERA_RECORDING_TIMES emUsbCameraRecordingTimes;
	E_DVR_USB_CAMERA_STORAGE_SIZE emUsbCameraStorageSize;
	E_DVR_USB_CAMERA_STORAGE_PATH emUsbCameraStoragePath;
	E_DVR_USB_CAMERA_EXIST_DEVICE emUsbCameraIsExistDevice;
	E_DVR_USB_CAMERA_BRAND emUsbCameraBrand;
	u8 uDvrIsSupportResolutions[D_IS_SUPPORT_RESOLUTION_MAX];
	int nDvrIsSupportResolutionsCounts;
	u8 uUsbCameraVideoColor_Level;
	u8 uUsbCameraVideoChrominance_Level;
	u8 uUsbCameraVideoBrightness_Level;
	u8 uUsbCameraVideoContrastGauge_Level;

	dvr_usb_camera_which_one stUsbCameraWhichOne[DVR_USB_CAMERA_DEVICES_NUMBER];
	E_DVR_USB_CAMERA_WHICH_ROAD emDvrUsbCameraWhichRoad;
	bool bCurIsUsbCameraRecording;
	bool bCurIsUsbCameraIsSdCard;
	bool bCurIsDvrInit;
	bool bCurIsSurportUsbCameraIsSdCard;

	E_DVR_USB_CAMERA_EXIST_DEVICE uIdIsDevice_F;
	E_DVR_USB_CAMERA_EXIST_DEVICE uIdIsDevice_R;

	u8 uCurEmergencyCollisionSwitchStatus;
	u8 uCurEmergencyCollisionKeepTimes;

	bool bCurIsUsbCameraVideoLock;
	
}dvr_local_param_t;

typedef struct{
	bool bDVRDriverInit;
	bool bDVRModuleState;//Ä£¿éÊÇ·ñ´æ
	int	 m_iPresentMode;
	bool bEnterDVRModuleMark;
	bool bStopVideo;//Â¼ÖÆ¡¢ÔÝÍ£×´Ì¬
	u16  m_wCurrentPage;//µ±Ç°Ò³
	bool bMute;
	bool bPlayOrPause;
	bool bBrake;
	int m_LMode;
}dvr_global_param_t;


extern dvr_local_param_t *pLocalParam;
extern dvr_global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);


void readUsbCameraRecording();

typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;
uni16_size_t uni16_strlen(const unicode16_t *uni16);
unicode16_t ansi_to_unicode16(const unsigned char ansi);
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src);
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);

int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
int enc_get_utf8_size(const unsigned char pInput);

#endif
