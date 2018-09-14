#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"

dvr_local_param_t localParam;
dvr_local_param_t *pLocalParam = (dvr_local_param_t*)&localParam;

dvr_global_param_t globalParam;
dvr_global_param_t *pGlobalParam = (dvr_global_param_t*)&globalParam;

#include <commonFunc.h>
#define FLY_DVR_ISRECORDING "fly.dvr.isrecording"
#define FLY_DVR_USB_RESOLUTION "fly.dvr.usb.resolution"
#define FLY_DVR_USB_RECORDING_TIME "fly.dvr.usb.recordingtime"
#define FLY_DVR_USB_STORAGE_SIZE "fly.dvr.usb.storagesize"
#define FLY_DVR_USB_STORAGE_PATH "fly.dvr.usb.storagepath"
#define FLY_DVR_WHICH_ROAD "fly.dvr.which.road"

#define FLY_MODULE_IS_T123 "fly.module.is.T123"
#define FLY_DVR_DEVICE_CHANGHE "fly.is.changhe"

void initReadParameter(int filesize){
}

void initSaveParameter(void){

}

void readParameter(void){
	
	readUsbCameraRecording();

	char property[PROPERTY_VALUE_MAX];
	
	property_get(FLY_DVR_USB_RESOLUTION,property,"0xff");
	sscanf(property,"%d",&pLocalParam->emUsbCameraResolution);
	if(pLocalParam->emUsbCameraResolution == (E_DVR_USB_CAMERA_RESOLUTION)0xff)
	{
		pLocalParam->emUsbCameraResolution = DVR_USB_CAMERA_RESOLUTION_1280X720P;
	}

	property_get(FLY_DVR_WHICH_ROAD,property,"0");
	sscanf(property,"%d",&pLocalParam->emDvrUsbCameraWhichRoad);

	property_get(FLY_DVR_USB_RECORDING_TIME,property,"2");
	sscanf(property,"%d",&pLocalParam->emUsbCameraRecordingTimes);

	property_get(FLY_DVR_USB_STORAGE_SIZE,property,"4");
	sscanf(property,"%d",&pLocalParam->emUsbCameraStorageSize);

	property_get(FLY_DVR_USB_STORAGE_PATH,property,"0");
	sscanf(property,"%d",&pLocalParam->emUsbCameraStoragePath);

	property_get(FLY_DVR_DEVICE_CHANGHE,property,"0");
	sscanf(property,"%d",&pLocalParam->bIsChangHe);
	
	property_get(FLY_MODULE_IS_T123,property,"0");
	sscanf(property,"%d",&pLocalParam->uDvrModule_is_T123);
}

void saveParameter(void){
	char property[PROPERTY_VALUE_MAX];
   sprintf(property, "%d",pLocalParam->bCurIsUsbCameraRecording);
   property_set(FLY_DVR_ISRECORDING, property);

   sprintf(property, "%d",pLocalParam->emDvrUsbCameraWhichRoad);
   property_set(FLY_DVR_WHICH_ROAD, property);

	sprintf(property, "%d", pLocalParam->emUsbCameraResolution);
	property_set(FLY_DVR_USB_RESOLUTION, property);

	sprintf(property, "%d", pLocalParam->emUsbCameraRecordingTimes);
	property_set(FLY_DVR_USB_RECORDING_TIME, property);

	sprintf(property, "%d", pLocalParam->emUsbCameraStorageSize);
	property_set(FLY_DVR_USB_STORAGE_SIZE, property);

	sprintf(property, "%d", pLocalParam->emUsbCameraStoragePath);
	property_set(FLY_DVR_USB_STORAGE_PATH, property);
}

void readUsbCameraRecording()
{
	char property[PROPERTY_VALUE_MAX];
	property_get(FLY_DVR_ISRECORDING,property,"0");
	sscanf(property,"%d",&pLocalParam->bCurIsUsbCameraRecording);
}



int enc_get_utf8_size(const unsigned char pInput)
{
	unsigned char c = pInput;
	if(c < 0x80) return 1;
	if(c >= 0x80 && c < 0xC0) return -1;
	if(c >= 0xC0 && c < 0xE0) return 2;
	if(c >= 0xE0 && c < 0xF0) return 3;
	if(c >= 0xF0 && c < 0xF8) return 4;
	if(c >= 0xF8 && c < 0xFC) return 5;
	if(c >= 0xFC) return 6;

	return -1;
}

int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic)
{
    char b1, b2, b3, b4, b5, b6;

    *Unic = 0x0; // 
    int utfbytes = enc_get_utf8_size(*pInput);
    unsigned char *pOutput = (unsigned char *)Unic;

    switch(utfbytes)
    {
    case 1:
        *pOutput = *pInput;
        break;
    case 2:
        b1 = *pInput;
        b2 = *(pInput + 1);
        if ( (b2 & 0xC0) != 0x80 )
            return 0;
        *pOutput     = (b1 << 6) + (b2 & 0x3F);
        *(pOutput+1) = (b1 >> 2) & 0x07;
        break;
    case 3:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b2 << 6) + (b3 & 0x3F);
        *(pOutput+1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
        break;
    case 4:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b3 << 6) + (b4 & 0x3F);
        *(pOutput+1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
        *(pOutput+2) = ((b1 << 2) & 0x1C)  + ((b2 >> 4) & 0x03);
        break;
    case 5:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b4 << 6) + (b5 & 0x3F);
        *(pOutput+1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
        *(pOutput+2) = (b2 << 2) + ((b3 >> 4) & 0x03);
        *(pOutput+3) = (b1 << 6);
        break;
    case 6:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        b6 = *(pInput + 5);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)
                || ((b6 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b5 << 6) + (b6 & 0x3F);
        *(pOutput+1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
        *(pOutput+2) = (b3 << 2) + ((b4 >> 4) & 0x03);
        *(pOutput+3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
        break;
    default:
        return 0;
        break;
    }//switch(utfbytes)

    return utfbytes;
}


int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize)
{
	int nSrcLen = 0;
	int nDstLen = 0;
	u8 *pUtf8 = pInput;
	u8 *pUnic = pOutput;
	int nOneUtf8Len = 0;

	nOneUtf8Len = enc_get_utf8_size(*pUtf8);

	while(-1 != nOneUtf8Len)
	{
		unsigned long oneUnic = 0;
		enc_utf8_to_unicode_one(pUtf8, &oneUnic);

		nDstLen += 2;
		if (nOutputSize < nDstLen)//装不下，回退
		{
			nDstLen -= 2;
			break;
		}
		else
			memcpy(pUnic, &oneUnic, 2);

		nSrcLen += nOneUtf8Len;
		if (nSrcLen >= nInputLen)//解析完了，退出
		{
			break;
		}

		pUtf8 += nOneUtf8Len;
		pUnic += 2;

		nOneUtf8Len = enc_get_utf8_size(*pUtf8);
	}

	return nDstLen;
}
uni16_size_t uni16_strlen(const unicode16_t *uni16)
{
	return 0;
}
unicode16_t ansi_to_unicode16(const unsigned char ansi)
{
	return 0;
}
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16)
{
	int nSrcLen = strlen((char*)ansi);
	int nUni16Len = nSrcLen*2+2;
	int nRetLen = utf8_2_ucs2(ansi, nSrcLen, (u8*)uni16, nUni16Len);
	
	return (nRetLen/2);
}
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16)
{
	return 0;
}