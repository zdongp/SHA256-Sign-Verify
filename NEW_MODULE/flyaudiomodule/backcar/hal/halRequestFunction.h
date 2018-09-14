#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__



void BackcarToHal_EnterPanoramicVideo(void);
void BackcarToHal_ExitPanoramicVideo(void);
void BackcarToHal_EnterFullScreen(void);
void BackcarToHal_ExitFullScreen(void);
void BackcarToHal_QueryBackcarVideoStatus(void);
void BackcarToHal_SelectVideo(char direction);

#endif
