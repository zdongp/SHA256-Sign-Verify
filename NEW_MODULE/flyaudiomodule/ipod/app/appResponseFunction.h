#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

//void appToIpod_Parameter(unsigned char *param, unsigned char paramLen);

void appToIpod_MainNext_MouseUp();
void appToIpod_MainPrev_MouseUp();

void appToIpod_MainPlayPause_MouseUp();

void appToIpod_MainShuffle_MouseUp();

void appToIpod_MainRPT_MouseUp();

void appToIpod_EnterSearchPage();
void appToIpod_BrowseReturn();

void appToIpod_SearchItem_MouseUp(int index);

void appToIpod_PlayItem_MouseUp(int index);
void appToIpod_BrowseItem(int index);

void appToIpod_SearchNextPage_MouseUp();

void appToIpod_SearchPrevPage_MouseUp();

void appToIpod_SearchGauge_MouseUp(u8 *buffer,u8 len);

void appToIpod_MainConnected_MouseUp();
#endif
