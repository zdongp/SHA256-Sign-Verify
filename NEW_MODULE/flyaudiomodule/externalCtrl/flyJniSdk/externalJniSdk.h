#pragma once
#include "global.h"

class  CExternalJniSdk
{
	public:
		CExternalJniSdk();
		~CExternalJniSdk();

	public:		//Function
		void getSdkToModuleExternalMessage(u8 *p,int len);
		void analysSdkToExternalStatusMessage(u8 *buf,u8 len);
		void analysSdkToExternalContrlMessage(u8 *buf,u8 len);
};
