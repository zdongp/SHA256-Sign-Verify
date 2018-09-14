#pragma once
#include "FlyJniSdkModule.h"

class CFlyJniSdkModule;
class CFlyJniSdkModuleDvd:public CFlyJniSdkModule
{
public:
	 CFlyJniSdkModuleDvd(void);
	virtual ~CFlyJniSdkModuleDvd(void);
	void getAppCtrlMessage(u8 *p, u8 len);
	void getDvdMessage(u8 *p, u8 len);
	void onDvdPlayStatus(u8 p);
	void onDvdTitleAndTrack(u8 *p,u8 len);
	void onDvdCurrentTime(u8 *p,u8 len);
	void onDvdDvdDiscAndFileType(u8 *p,u8 len);
    void onDvdDevState(u8 p);

	void CtrlDvdPalyStatus(u8 p);
	void setToDvdPlay(u8 p);
	void setToDvdPause(u8 p);
	void setToDvdNext(u8 p);
	void setToDvdLast(u8 p);
	
};