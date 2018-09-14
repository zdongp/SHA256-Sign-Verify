#pragma once
#include "FlyJniSdkModule.h"

class CFlyJniSdkModule;
class CFlyJniSdkModuleExtcarHondaTsu:public CFlyJniSdkModule
{
	public:
		 CFlyJniSdkModuleExtcarHondaTsu(void);
		virtual ~CFlyJniSdkModuleExtcarHondaTsu(void);
	public:
		void analyseExtcarHondaTsuAppMessageType(u8 *p, u8 len);
		void analyseExtcarHondaTsuMassage(u8 *p, u8 len);
		void sendToextcarHondaTsuData(u8 *param,int len);
};

