#ifndef __APP_REQUEST_FUNCTION_DVD_H__
#define __APP_REQUEST_FUNCTION_DVD_H__


void ipodToApp_SetSerialData_Ansi2Unicode(int controlId, u8 *pBuf, int nLen);

void ipodToApp_SetBrowseItemEnable(int item,bool bEnablePlay,bool bEnableSearch,u8 *pStr,int strLen);

void ipodToApp_SetBrowseItemHide();

void ipodToApp_DisplayTrackMessage(int iTrack,int iTrackSum);	

void ipodToApp_EnterFirstSearchPage();

void ipodToApp_SetCurrentTime(u8 *str,int strLen);

#endif
