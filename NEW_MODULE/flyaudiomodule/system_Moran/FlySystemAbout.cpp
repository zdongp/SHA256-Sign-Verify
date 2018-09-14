#include "FlySystemAbout.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
//#include <cutils/properties.h>
#include <sys/system_properties.h>
#include "types_def.h"
#include "commonFunc.h"
#include "global.h"
#include "pageID.h"
#include "param.h"
#include "controlID.h"
#include "stringID.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"
#include "appResponseFunction.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "moduleParamResponse.h"

CFlySystemAbout::CFlySystemAbout(void)
{
}

CFlySystemAbout::~CFlySystemAbout(void)
{
}

void CFlySystemAbout::updateSystemAbout(void)
{
	updateMCU();
	updateBarCode();
	updateBlueTooth();
	updateMPEG();
}

void CFlySystemAbout::updateMCU(void)
{
	LOGD("[%s]", __FUNCTION__);

	char szMCU[PROPERTY_VALUE_MAX] = {0};
	char szMCU_Time[PROPERTY_VALUE_MAX] = {0};
	memset(szMCU,0,sizeof(szMCU));
	memset(szMCU_Time,0,sizeof(szMCU_Time));

	property_get("fly.version.mcu", szMCU, "");
	property_get("fly.version.times",szMCU_Time, "");

	if ((0 == strcmp(szMCU, "")) && (0 == strcmp(szMCU_Time, "")))
	{
		char szCarCode[PROPERTY_VALUE_MAX] = {0};
		char szCarCodePath[PROPERTY_VALUE_MAX] = {0};
		char szMCUPath[PROPERTY_VALUE_MAX] = {0};

		property_get("persist.fly.car.select", szCarCode, "0");
		
		LOGD("[%s] car code = [%s]", __FUNCTION__, szCarCode);

		snprintf(szCarCodePath, sizeof(szCarCodePath), "%s/%s", "/flysystem/flyconfig", szCarCode);

		if(access(szCarCodePath, F_OK) == 0)
		{
			snprintf(szMCUPath, sizeof(szMCUPath), "%s/%s/mcu.txt", "/flysystem/flyconfig", szCarCode);
		}
		else
		{
			snprintf(szMCUPath, sizeof(szMCUPath), "%s/%s/mcu.txt", "/flysystem/flyconfig", "default");
		}

		int nRetTime = saveMcuTime("/flysystem/flytheme/mcu/mcu-version.txt");
		int nRet = saveMCU(szMCUPath);

		switch(nRet && nRetTime)
		{
		case 0:
			{
				property_get("fly.version.times",szMCU_Time, "-4");
				property_get("fly.version.mcu", szMCU, "-4");
				strcat(szMCU,szMCU_Time);
				setAnsiSerialData(CONTROLID_COPYRIGHT_ACU, (u8*)szMCU, strlen(szMCU));
			}
			break;
		case -1:
			setAnsiSerialData(CONTROLID_COPYRIGHT_ACU, (u8*)"-1", strlen("-1"));
			break;
		case -2:
			setAnsiSerialData(CONTROLID_COPYRIGHT_ACU, (u8*)"-2", strlen("-2"));
			break;
		case -3:
			setAnsiSerialData(CONTROLID_COPYRIGHT_ACU, (u8*)"-3", strlen("-3"));
			break;
		}
	}
	else
	{
		memset(pLocalParam->c_mcu,0,sizeof(pLocalParam->c_mcu));
		int nMcuF = strlen(szMCU);
		for(int i = 0;i < nMcuF;i++)
		{
			if(i == nMcuF-1 && szMCU[nMcuF-1] == 10){
			}
			else{
				pLocalParam->c_mcu[i] = szMCU[i];
			}
		}
		//strcpy(pLocalParam->c_mcu,szMCU);
		strcat(pLocalParam->c_mcu,szMCU_Time);
		
		LOGD("pLocalParam->c_mcu:%s",pLocalParam->c_mcu);
		setAnsiSerialData(CONTROLID_COPYRIGHT_ACU,(u8*)pLocalParam->c_mcu,100);
	}
}

void CFlySystemAbout::updateBarCode(void)
{
	//�� service ģ��
}

void CFlySystemAbout::updateBlueTooth(void)
{

}

void CFlySystemAbout::updateMPEG(void)
{

}
//MCU
int CFlySystemAbout::saveMCU(const char *pMCUpath)
{
	LOGD("[%s] the mcu path is [%s]", __FUNCTION__, pMCUpath);

	if(access(pMCUpath, F_OK) == -1)
	{
		LOGD("[%s] the mcu file do not exist", __FUNCTION__);
		return -1;
	}

	if(access(pMCUpath, R_OK) == -1)
	{
		LOGD("[%s] the mcu file can not read", __FUNCTION__);
		return -2;
	}

	FILE *pMCUFile = NULL;
	pMCUFile = fopen(pMCUpath, "r");
	if(pMCUFile == NULL) 
	{
		LOGD("[%s] open mcu file fail", __FUNCTION__);
		return -3;
	}

	char szMCUData[128] = {0};
	int nFileLen = 0, offset = 0;

	offset = fseek(pMCUFile, 0, SEEK_END);
	LOGD("[%s] offset = [%d]", __FUNCTION__, offset);

	nFileLen = ftell(pMCUFile);
	LOGD("[%s] nFileLen = [%d]", __FUNCTION__, nFileLen);

	offset = fseek(pMCUFile, 0, SEEK_SET);
	LOGD("[%s] offset = [%d]", __FUNCTION__, offset);

	int nLenRead = fread(szMCUData, sizeof(char), nFileLen, pMCUFile);
	LOGI("[%s] error code = [%d], nLenRead = [%d], MCU Data = [%s]", __FUNCTION__, ferror(pMCUFile), nLenRead, szMCUData);

	property_set("fly.version.mcu", szMCUData);
	
	fclose(pMCUFile);
	pMCUFile = NULL;

	return 0;
}

int CFlySystemAbout::saveMcuTime(const char *pMCUpath)
{
	LOGD("[%s] the mcu Time path is [%s]", __FUNCTION__, pMCUpath);

	if(access(pMCUpath, F_OK) == -1)
	{
		LOGD("[%s] the mcu Time file do not exist", __FUNCTION__);
		return -1;
	}

	if(access(pMCUpath, R_OK) == -1)
	{
		LOGD("[%s] the mcu Time file can not read", __FUNCTION__);
		return -2;
	}

	FILE *pMCUFile = NULL;
	pMCUFile = fopen(pMCUpath, "r");
	if(pMCUFile == NULL) 
	{
		LOGD("[%s] open mcu Time file fail", __FUNCTION__);
		return -3;
	}

	char szMCUData[128] = {0};
	int nFileLen = 0, offset = 0;

	offset = fseek(pMCUFile, 0, SEEK_END);
	LOGD("[%s] offset = [%d]", __FUNCTION__, offset);

	nFileLen = ftell(pMCUFile);
	LOGD("[%s] nFileLen = [%d]", __FUNCTION__, nFileLen);

	offset = fseek(pMCUFile, 0, SEEK_SET);
	LOGD("[%s] offset = [%d]", __FUNCTION__, offset);

	int nLenRead = fread(szMCUData, sizeof(char), nFileLen, pMCUFile);
	LOGI("[%s] error code = [%d], nLenRead = [%d], MCU  Time Data = [%s]", __FUNCTION__, ferror(pMCUFile), nLenRead, szMCUData);

	property_set("fly.version.times", szMCUData);
	
	fclose(pMCUFile);
	pMCUFile = NULL;

	return 0;
}

