#ifndef __HAL_REQUEST_FUNCTION_H__
#define __HAL_REQUEST_FUNCTION_H__


void ipodToHal_SetConnectPing();

void ipodToHal_QueryIPODType();
void ipodToHal_QueryIPODName();

void ipodToHal_EnterAIRMode();


void ipodToHal_LeaveAIRMode();

void ipodToHal_SetMusicControl();

void ipodToHal_SetTypeMode(int iType,unsigned int iItem);
void ipodToHal_QueryTypeSum(int iType);
void ipodToHal_QueryTypeItemString(int iType,unsigned int iStartnum,unsigned int iNum);

void ipodToHal_SetTimeState();

void ipodToHal_QueryTypeListIndex();

void ipodToHal_QueryCurrentPositionMusicName(unsigned int iNumber);

void ipodToHal_QueryCurrentPositionArtist(unsigned int iNumber);

void ipodToHal_QueryCurrentPositionAlbum(unsigned int iNumber);

void ipodToHal_SetStartReturnTime();

void ipodToHal_SetStopReturnTime();

void ipodToHal_SetFirstItemPlay();

void ipodToHal_SetPlayListPlay(unsigned int iNumber);

void ipodToHal_SetPlayPause();

void ipodToHal_SetStop();

void ipodToHal_SetSkipSuperior();
void ipodToHal_SetSkipNext();

void ipodToHal_SetFFwd();
void ipodToHal_SetFRwd();

void ipodToHal_SetStopFFRW();

void ipodToHal_QueryShuffleMode();

void ipodToHal_SetShuffleMode(int iShuffleMode);

void ipodToHal_QueryRepeatMode();


void ipodToHal_SetRepeatMode(int iRepeatMode);

void ipodToHal_QueryCurPlayListSongSum();

void ipodToHal_SetCurrentPositionPlay(unsigned int iNumber);

void ipodToHal_SetBrowseItem(int iType,unsigned int item);


#endif
