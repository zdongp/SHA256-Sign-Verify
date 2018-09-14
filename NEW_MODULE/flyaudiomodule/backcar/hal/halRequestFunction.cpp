#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"

#include <flymoduleApi_internal.h>

void BackcarToHal_QueryBackcarVideoStatus(void)
{
	unsigned char buf[] = {0x00,0x00};

	makeAndSendMessageToHal(HAL_ID_BACK,buf,2);
}

void BackcarToHal_EnterPanoramicVideo(void)
{
	unsigned char buf[] = {0x01,0x00};
	makeAndSendMessageToHal(HAL_ID_BACK,buf,2);
}

void BackcarToHal_ExitPanoramicVideo(void)
{
	unsigned char buf[] = {0x02,0x00};

	makeAndSendMessageToHal(HAL_ID_BACK,buf,2);
}

void BackcarToHal_SelectVideo(char direction)
{
	unsigned char buf[] = {0x03,0x02};

	buf[1]= direction;

	makeAndSendMessageToHal(HAL_ID_BACK,buf,2);
}

void BackcarToHal_EnterFullScreen(void)
{
  unsigned char buf[] = {0x04,0x00};
	makeAndSendMessageToHal(HAL_ID_BACK,buf,2);
}

void BackcarToHal_ExitFullScreen(void)
{
   unsigned char buf[] = {0x05,0x00};
	makeAndSendMessageToHal(HAL_ID_BACK,buf,2);
}


