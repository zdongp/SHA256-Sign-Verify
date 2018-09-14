#pragma once
#include "FlyJniSdkModule.h"

class CFlyJniSdkModuleAudioCtrl : public CFlyJniSdkModule
{
	public:
		CFlyJniSdkModuleAudioCtrl(void);
		virtual ~CFlyJniSdkModuleAudioCtrl(void);

	public:
		void analyseAudioCtrlAppMessageType(u8 *p, u8 len);

	private:
		void analyseAudioCtrlOperationMassage(u8 *p, u8 len);
		void setToCurPlaySourcePlayCtrl(u8 p);
		void setToCurPlaySourcePlayMode(u8 p);
};


