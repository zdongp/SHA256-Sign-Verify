#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <commonFunc.h>
#include <ctype.h>
#include <string.h>

#include "global.h"
#include "param.h"
#include "moduleParamResponse.h"

//#include "CNotifyAndResponseFlyJniSdk.h"

CNotifyAndResponseFlyJniSdk  g_clsNotifyAndResponseFlyJniSdk ;
radio_local_param_t localParam;
radio_local_param_t *pLocalParam = (radio_local_param_t*)&localParam;

radio_global_param_t globalParam;
radio_global_param_t *pGlobalParam = (radio_global_param_t*)&globalParam;


#define CHAR_LEN 8
#define DEFINE_NAME_LEN 32
#define SAVE_NAME_LEN 64

#define FLY_RADIO_RADIOCHANNEL    								"fly.radio.eRadioChannel"
#define FLY_RADIO_RADIOISPOWERON                                "fly.radio.Radio.bIspoweron"
#define FLY_RADIO_AFSTATE										"fly.radio.Radio.afState"
#define FLY_RADIO_TASTATE                                       "fly.radio.Radio.taState"

#define FLY_RADIO_RADIOCHANNELRECORD1_CURFREQUENCY    			"fly.radio.Record1.wCurFreq"
#define FLY_RADIO_RADIOCHANNELRECORD1_RADIOFRERECORD    		"fly.radio.Record1.wFreqRecord"
#define FLY_RADIO_RADIOCHANNELRECORD1_CURRECORDINDEX   			"fly.radio.Record1.cCurIndex"
#define FLY_RADIO_RADIOCHANNELRECORD1_CURECORDNUM    			"fly.radio.Record1.cCurNum"
#define FLY_RADIO_RADIOCHANNELRECORD1_FREQRECORDSTATE 			"fly.radio.Record1.bFreqState"
#define FLY_RADIO_RADIOCHANNELRECORD1_CURPAGE 					"fly.radio.Record1.curPage"
#define FLY_RADIO_RADIOCHANNELRECORD1_TOTALPAGES 				"fly.radio.Record1.totalPages"


#define FLY_RADIO_RADIOCHANNELRECORD2_CURFREQUENCY    			"fly.radio.Record2.wCurFreq"
#define FLY_RADIO_RADIOCHANNELRECORD2_RADIOFRERECORD    		"fly.radio.Record2.wFreqRecord"
#define FLY_RADIO_RADIOCHANNELRECORD2_CURRECORDINDEX   			"fly.radio.Record2.cCurIndex"
#define FLY_RADIO_RADIOCHANNELRECORD2_CURECORDNUM    			"fly.radio.Record2.cCurNum"
#define FLY_RADIO_RADIOCHANNELRECORD2_FREQRECORDSTATE 			"fly.radio.Record2.bFreqState"
#define FLY_RADIO_RADIOCHANNELRECORD2_CURPAGE 					"fly.radio.Record2.curPage"
#define FLY_RADIO_RADIOCHANNELRECORD2_TOTALPAGES 				"fly.radio.Record2.totalPages"


#define FLY_RADIO_RADIOCHANNELRECORD3_CURFREQUENCY    			"fly.radio.Record3.wCurFreq"
#define FLY_RADIO_RADIOCHANNELRECORD3_RADIOFRERECORD    		"fly.radio.Record3.wFreqRecord"
#define FLY_RADIO_RADIOCHANNELRECORD3_CURRECORDINDEX   			"fly.radio.Record3.cCurIndex"
#define FLY_RADIO_RADIOCHANNELRECORD3_CURECORDNUM    			"fly.radio.Record3.cCurNum"
#define FLY_RADIO_RADIOCHANNELRECORD3_FREQRECORDSTATE 			"fly.radio.Record3.bFreqState"
#define FLY_RADIO_RADIOCHANNELRECORD3_CURPAGE 					"fly.radio.Record3.curPage"
#define FLY_RADIO_RADIOCHANNELRECORD3_TOTALPAGES 				"fly.radio.Record3.totalPages"
#define FLY_RADIO_RADIOCHANNELRECORD3_SENSITIVITY               "fly.radio.Record3.sensitivity"
#define FLY_RADIO_RADIOCHANNELRECORD3_TA                     "fly.radio.Record3.ta"
#define FLY_RADIO_RADIOCHANNELRECORD3_AF                     "fly.radio.Record3.af"
#define FLY_RADIO_TAAF_VISIBLE                               "fly.radio.taaf.visible"

#define FLY_SET_RADIOCOUNTRYCODE    "fly.set.b_Sys_RadioCountryCode"

char __intToChar(char value){
	if(value >= 0 && value <= 9){
		return (value+0x30);
	}
	else if(value >= 10 && value <=15){
		return (value + 0x37);
	}
	else{
		return '\0';
		LOGD("*************0*****************");
	}
}

char __charToInt(char ch){
	if(ch >= '0' && ch <= '9'){
		return (ch-0x30);
	}
	else if(ch >= 'A' && ch <= 'F'){
		return (ch-0x37);
	}
	else{
		LOGD("*************0*****************");
		return 0;
	}
}

int bufferToString(char *buffer, int len, char *str)
	{
		int n;
		int i , j;
		if(len <= 0 || len >= (PROPERTY_VALUE_MAX/2)){
			return -1;
		}

		for(i = 0, j=0; i < len; i++,j+=2){
			str[j] = __intToChar((buffer[i]&0xF0)>>4);
			str[j+1] = __intToChar((buffer[i]&0x0F));
		}
		str[2*len] = '\0';
		return (2*len+1);
	}

int u16bufferToString(u16 *buffer, int len, char *str)
	{
		int n;
		int i , j;
		if(len <= 0 || len >= (PROPERTY_VALUE_MAX/4)){
			LOGD("*************u16bufferToString******len***********-1");
			return -1;
		}

		for(i = 0, j=0; i < len; i++,j+=4){
			str[j] = __intToChar((buffer[i]&0xF000)>>12);
			str[j+1] = __intToChar((buffer[i]&0x0F00)>>8);
			str[j+2] = __intToChar((buffer[i]&0x00F0)>>4);
			str[j+3] = __intToChar((buffer[i]&0x000F));
		}
		str[4*len] = '\0';
		return (4*len+1);
	}

int stringToU16buffer(char *str, u16 *buffer)
{
	int str_len = strlen(str);
	LOGD("*************stringToU16buffer*****************%d",str_len);
	if(str_len <= 0)
		return 0;
	int i , j;
	for(i = 0, j=0; j < str_len; i++, j+=4){
		buffer[i] = __charToInt(str[j])<<12;
		buffer[i] += __charToInt(str[j+1])<<8;
		buffer[i] += __charToInt(str[j+2])<<4;
		buffer[i] += __charToInt(str[j+3]);
	}

	return (str_len/4);
}



int stringToBuffer(char *str, char *buffer)
{
	int str_len = strlen(str);
	if(str_len <= 0)
		return 0;
	int i , j;
	for(i = 0, j=0; j < str_len; i++, j+=2){
		buffer[i] = __charToInt(str[j])<<4;
		buffer[i] += __charToInt(str[j+1]);
	}

	return (str_len/2);
}

/*void readParameter(void)
{

	int value = 0;
	ModuleParamResponse_InitParam();

	char property[PROPERTY_VALUE_MAX];

	property_get(FLY_RADIO_RADIOCHANNEL,property,"0");	// default FM1(0)
	sscanf(property,"%d", &pLocalParam->eRadioChannel);
	property_get(FLY_RADIO_RADIOISPOWERON,property,"1");//radio on/off
	sscanf(property,"%d",&pLocalParam->bIsRadioPowerOn);
	property_get(FLY_RADIO_AFSTATE,property,"0");//radio on/off
	sscanf(property,"%d",&pLocalParam->afState);
	property_get(FLY_RADIO_TASTATE,property,"0");//radio on/off
	sscanf(property,"%d",&pLocalParam->taState);

	property_get(FLY_RADIO_RADIOCHANNELRECORD1_CURFREQUENCY,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[0].wCurFrequency);
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_CURRECORDINDEX,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[0].cCurRecordIndex);
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_CURECORDNUM,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[0].cCurRecordNum);
	char buffer[CHANNEL_RECORD_NUM];
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_RADIOFRERECORD, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[0].wRadioFreqRecord, buffer, 2*CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_FREQRECORDSTATE, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[0].bRadioFreqRecordState, buffer, CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_CURPAGE,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[0].curPage);
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_TOTALPAGES,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[0].totalPages);






	property_get(FLY_RADIO_RADIOCHANNELRECORD2_CURFREQUENCY,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[1].wCurFrequency);
	property_get(FLY_RADIO_RADIOCHANNELRECORD2_CURRECORDINDEX,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[1].cCurRecordIndex);
	property_get(FLY_RADIO_RADIOCHANNELRECORD2_CURECORDNUM,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[1].cCurRecordNum);
	property_get(FLY_RADIO_RADIOCHANNELRECORD2_RADIOFRERECORD, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[1].wRadioFreqRecord, buffer, 2*CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}
	property_get(FLY_RADIO_RADIOCHANNELRECORD2_FREQRECORDSTATE, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[1].bRadioFreqRecordState, buffer, CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}
	property_get(FLY_RADIO_RADIOCHANNELRECORD2_CURPAGE,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[1].curPage);
	property_get(FLY_RADIO_RADIOCHANNELRECORD2_TOTALPAGES,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[1].totalPages);






	property_get(FLY_RADIO_RADIOCHANNELRECORD3_CURFREQUENCY,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[2].wCurFrequency);
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_CURRECORDINDEX,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[2].cCurRecordIndex);
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_CURECORDNUM,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[2].cCurRecordNum);
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_RADIOFRERECORD, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[2].wRadioFreqRecord, buffer, 2*CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_FREQRECORDSTATE, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[2].bRadioFreqRecordState, buffer, CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_CURPAGE,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[2].curPage);
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_TOTALPAGES,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[2].totalPages);

}*/

/*
void saveParameter(void)
{
	LOGD("radio      saveParameter");
	char property[PROPERTY_VALUE_MAX];

	sprintf(property,"%d", pLocalParam->eRadioChannel);
	property_set(FLY_RADIO_RADIOCHANNEL,property);
	sprintf(property,"%d",pLocalParam->bIsRadioPowerOn);
	property_set(FLY_RADIO_RADIOISPOWERON,property);
	sprintf(property,"%d",pLocalParam->afState);
	property_set(FLY_RADIO_AFSTATE,property);
	sprintf(property,"%d",pLocalParam->taState);
	property_set(FLY_RADIO_TASTATE,property);



	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[0].wCurFrequency);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_CURFREQUENCY,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[0].cCurRecordIndex);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_CURRECORDINDEX,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[0].cCurRecordNum);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_CURECORDNUM,property);
	bufferToString((char *)pLocalParam->stszRadioChannelRecord[0].wRadioFreqRecord,2*CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE,property);
	LOGD("pLocalParam->stszRadioChannelRecord[0].wRadioFreqRecord %s", pLocalParam->stszRadioChannelRecord[0].wRadioFreqRecord);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_RADIOFRERECORD, property);
	bufferToString((char *)pLocalParam->stszRadioChannelRecord[0].bRadioFreqRecordState, CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE, property);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_FREQRECORDSTATE, property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[0].curPage);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_CURPAGE,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[0].totalPages);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_TOTALPAGES,property);


	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[1].wCurFrequency);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_CURFREQUENCY,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[1].cCurRecordIndex);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_CURRECORDINDEX,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[1].cCurRecordNum);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_CURECORDNUM,property);
	bufferToString((char *)pLocalParam->stszRadioChannelRecord[1].wRadioFreqRecord,2*CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE,property);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_RADIOFRERECORD, property);
	bufferToString((char *)pLocalParam->stszRadioChannelRecord[1].bRadioFreqRecordState, CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE, property);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_FREQRECORDSTATE, property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[1].curPage);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_CURPAGE,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[1].totalPages);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_TOTALPAGES,property);




	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[2].wCurFrequency);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_CURFREQUENCY,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[2].cCurRecordIndex);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_CURRECORDINDEX,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[2].cCurRecordNum);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_CURECORDNUM,property);
	bufferToString((char *)pLocalParam->stszRadioChannelRecord[2].wRadioFreqRecord,2*CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE,property);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_RADIOFRERECORD, property);
	bufferToString((char *)pLocalParam->stszRadioChannelRecord[2].bRadioFreqRecordState, CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE, property);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_FREQRECORDSTATE, property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[2].curPage);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_CURPAGE,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[2].totalPages);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_TOTALPAGES,property);


}
*/



void saveParameter(void)
{
	LOGD("radio 	 saveParameter");
	char property[PROPERTY_VALUE_MAX];

	sprintf(property,"%d", pLocalParam->eRadioChannel);
	property_set(FLY_RADIO_RADIOCHANNEL,property);
	sprintf(property,"%d",pLocalParam->bIsRadioPowerOn);
	property_set(FLY_RADIO_RADIOISPOWERON,property);
	sprintf(property,"%d",pLocalParam->afState);
	property_set(FLY_RADIO_AFSTATE,property);
	sprintf(property,"%d",pLocalParam->taState);
	property_set(FLY_RADIO_TASTATE,property);

	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[0].wCurFrequency);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_CURFREQUENCY,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[0].cCurRecordIndex);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_CURRECORDINDEX,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[0].cCurRecordNum);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_CURECORDNUM,property);
	char channelName1[DEFINE_NAME_LEN] = FLY_RADIO_RADIOCHANNELRECORD1_RADIOFRERECORD;
	char channelState1[DEFINE_NAME_LEN] = FLY_RADIO_RADIOCHANNELRECORD1_FREQRECORDSTATE;
	char saveFreq[SAVE_NAME_LEN];
	char saveState[SAVE_NAME_LEN];
	for(int i = 0; i < pLocalParam->stszRadioChannelRecord[0].totalPages; i++)
	{
		char char_i[CHAR_LEN];
		sprintf(char_i,"%d", i);
		strcpy(saveFreq,channelName1);
		strcat(saveFreq,char_i);

		memset(property,0,PROPERTY_VALUE_MAX);
		bufferToString((char *)&pLocalParam->stszRadioChannelRecord[0].wRadioFreqRecord[i * CHANNEL_RECORD_NUM], 2*CHANNEL_RECORD_NUM ,property);
		property_set(saveFreq, property);

		strcpy(saveState,channelState1);
		strcat(saveState,char_i);
		bufferToString((char *)&pLocalParam->stszRadioChannelRecord[0].bRadioFreqRecordState[i * CHANNEL_RECORD_NUM], 2*CHANNEL_RECORD_NUM ,property);
		property_set(saveState, property);
	}
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[0].curPage);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_CURPAGE,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[0].totalPages);
	property_set(FLY_RADIO_RADIOCHANNELRECORD1_TOTALPAGES,property);


	//---------------------------------------FM2---------------------------------------------
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[1].wCurFrequency);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_CURFREQUENCY,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[1].cCurRecordIndex);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_CURRECORDINDEX,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[1].cCurRecordNum);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_CURECORDNUM,property);
	char channelName2[32] = FLY_RADIO_RADIOCHANNELRECORD2_RADIOFRERECORD;
	char channelState2[32] = FLY_RADIO_RADIOCHANNELRECORD2_FREQRECORDSTATE;
	for(int i = 0; i < pLocalParam->stszRadioChannelRecord[1].totalPages; i++)
	{
		char char_i[CHAR_LEN];
		sprintf(char_i,"%d", i);


		strcpy(saveFreq,channelName2);
		strcat(saveFreq,char_i);

		memset(property,0,PROPERTY_VALUE_MAX);
		bufferToString((char *)&pLocalParam->stszRadioChannelRecord[1].wRadioFreqRecord[i * CHANNEL_RECORD_NUM], 2*CHANNEL_RECORD_NUM ,property);
		property_set(saveFreq, property);


		strcpy(saveState,channelState2);
		strcat(saveState,char_i);
		bufferToString((char *)&pLocalParam->stszRadioChannelRecord[1].bRadioFreqRecordState[i * CHANNEL_RECORD_NUM], 2*CHANNEL_RECORD_NUM ,property);
		property_set(saveState, property);
	}
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[1].curPage);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_CURPAGE,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[1].totalPages);
	property_set(FLY_RADIO_RADIOCHANNELRECORD2_TOTALPAGES,property);


	//-----------------------------------------AM---------------------------------------
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[2].wCurFrequency);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_CURFREQUENCY,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[2].cCurRecordIndex);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_CURRECORDINDEX,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[2].cCurRecordNum);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_CURECORDNUM,property);
	char channelName3[32] = FLY_RADIO_RADIOCHANNELRECORD3_RADIOFRERECORD;
	char channelState3[32] = FLY_RADIO_RADIOCHANNELRECORD3_FREQRECORDSTATE;
	for(int i = 0; i < pLocalParam->stszRadioChannelRecord[2].totalPages; i++)
	{
		char char_i[CHAR_LEN];
		sprintf(char_i,"%d", i);
		strcpy(saveFreq,channelName3);
		strcat(saveFreq,char_i);

		memset(property,0,PROPERTY_VALUE_MAX);
		bufferToString((char *)&pLocalParam->stszRadioChannelRecord[2].wRadioFreqRecord[i * CHANNEL_RECORD_NUM], 2*CHANNEL_RECORD_NUM ,property);
		property_set(saveFreq, property);

		strcpy(saveState,channelState3);
		strcat(saveState,char_i);
		bufferToString((char *)&pLocalParam->stszRadioChannelRecord[2].bRadioFreqRecordState[i * CHANNEL_RECORD_NUM], 2*CHANNEL_RECORD_NUM ,property);
		property_set(saveState, property);
	}
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[2].curPage);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_CURPAGE,property);
	sprintf(property,"%d", pLocalParam->stszRadioChannelRecord[2].totalPages);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_TOTALPAGES,property);

	sprintf(property,"%d", pLocalParam->sensitivitystate);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_SENSITIVITY,property);

	sprintf(property,"%d", pLocalParam->radioTAstate);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_TA,property);

	sprintf(property,"%d", pLocalParam->radioAFstate);
	property_set(FLY_RADIO_RADIOCHANNELRECORD3_AF,property);

	sprintf(property,"%d", pLocalParam->cTAAFVisible);
	property_set(FLY_RADIO_TAAF_VISIBLE,property);

}



void readParameter(void)
{
	int value = 0;
	ModuleParamResponse_InitParam();

	char property[PROPERTY_VALUE_MAX];

	property_get(FLY_RADIO_RADIOCHANNEL,property,"0");	// default FM1(0)
	sscanf(property,"%d", &pLocalParam->eRadioChannel);
	property_get(FLY_RADIO_RADIOISPOWERON,property,"1");//radio on/off
	sscanf(property,"%d",&pLocalParam->bIsRadioPowerOn);
	property_get(FLY_RADIO_AFSTATE,property,"0");//radio on/off
	sscanf(property,"%d",&pLocalParam->afState);
	property_get(FLY_RADIO_TASTATE,property,"0");//radio on/off
	sscanf(property,"%d",&pLocalParam->taState);

	property_get(FLY_RADIO_RADIOCHANNELRECORD1_CURFREQUENCY,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[0].wCurFrequency);
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_CURRECORDINDEX,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[0].cCurRecordIndex);
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_CURECORDNUM,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[0].cCurRecordNum);
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_CURPAGE,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[0].curPage);
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_TOTALPAGES,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[0].totalPages);

	property_get(FLY_SET_RADIOCOUNTRYCODE,property,"7");
	sscanf(property,"%hhd", &pLocalParam->u8RadioCountryCode);

	/*
	char buffer[CHANNEL_RECORD_NUM];
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_FREQRECORDSTATE, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[0].bRadioFreqRecordState, buffer, CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}
	property_get(FLY_RADIO_RADIOCHANNELRECORD1_RADIOFRERECORD, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[0].wRadioFreqRecord, buffer, 2*CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}


	*/
	char channelName1[32] = FLY_RADIO_RADIOCHANNELRECORD1_RADIOFRERECORD;
	char channelState1[32] = FLY_RADIO_RADIOCHANNELRECORD1_FREQRECORDSTATE;
	for(int i = 0; i < pLocalParam->stszRadioChannelRecord[0].totalPages; i++)
	{
			char char_i[CHAR_LEN];
			sprintf(char_i,"%d", i);

			char readFreq[64];
			strcpy(readFreq,channelName1);
			strcat(readFreq,char_i);

			char buffer[2*CHANNEL_RECORD_NUM];
			u16 num[2*CHANNEL_RECORD_NUM];
			property_get(readFreq, property, NULL);
			value = stringToBuffer(property, buffer);
			if(value > 0)
			{
				memcpy(num, buffer, 2*CHANNEL_RECORD_NUM );
				int index = i * CHANNEL_RECORD_NUM;
				for(int j = 0; j < CHANNEL_RECORD_NUM; j++)
				{
					pLocalParam->stszRadioChannelRecord[0].wRadioFreqRecord[index + j] = num[j];
				}

			}

			char readState[64];
			strcpy(readState,channelState1);
			strcat(readState,char_i);
			property_get(readState, property, NULL);
			value = stringToBuffer(property, buffer);
			if(value > 0)
			{

				int index = i * CHANNEL_RECORD_NUM;
				for(int j = 0; j < CHANNEL_RECORD_NUM; j++)
				{
					pLocalParam->stszRadioChannelRecord[0].bRadioFreqRecordState[index + j] = buffer[j];
				}

			}

	}

	property_get(FLY_RADIO_RADIOCHANNELRECORD2_CURFREQUENCY,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[1].wCurFrequency);
	property_get(FLY_RADIO_RADIOCHANNELRECORD2_CURRECORDINDEX,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[1].cCurRecordIndex);
	property_get(FLY_RADIO_RADIOCHANNELRECORD2_CURECORDNUM,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[1].cCurRecordNum);
	property_get(FLY_RADIO_RADIOCHANNELRECORD2_CURPAGE,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[1].curPage);
	property_get(FLY_RADIO_RADIOCHANNELRECORD2_TOTALPAGES,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[1].totalPages);
	char channelName2[32] = FLY_RADIO_RADIOCHANNELRECORD2_RADIOFRERECORD;
	char channelState2[32] = FLY_RADIO_RADIOCHANNELRECORD2_FREQRECORDSTATE;
	for(int i = 0; i < pLocalParam->stszRadioChannelRecord[1].totalPages; i++)
	{
			char char_i[CHAR_LEN];
			sprintf(char_i,"%d", i);

			char readFreq[64];
			strcpy(readFreq,channelName2);
			strcat(readFreq,char_i);

			char buffer[2*CHANNEL_RECORD_NUM];
			u16 num[2*CHANNEL_RECORD_NUM];
			property_get(readFreq, property, NULL);
			value = stringToBuffer(property, buffer);
			if(value > 0)
			{
				memcpy(num, buffer, 2*CHANNEL_RECORD_NUM );
				int index = i * CHANNEL_RECORD_NUM;
				for(int j = 0; j < CHANNEL_RECORD_NUM; j++)
				{
					pLocalParam->stszRadioChannelRecord[1].wRadioFreqRecord[index + j] = num[j];
				}

			}

			char readState[64];
			strcpy(readState,channelState2);
			strcat(readState,char_i);
			property_get(readState, property, NULL);
			value = stringToBuffer(property, buffer);
			if(value > 0)
			{

				int index = i * CHANNEL_RECORD_NUM;
				for(int j = 0; j < CHANNEL_RECORD_NUM; j++)
				{
					pLocalParam->stszRadioChannelRecord[1].bRadioFreqRecordState[index + j] = buffer[j];
				}

			}
	}

	/*
	property_get(FLY_RADIO_RADIOCHANNELRECORD2_RADIOFRERECORD, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[1].wRadioFreqRecord, buffer, 2*CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}

	property_get(FLY_RADIO_RADIOCHANNELRECORD2_FREQRECORDSTATE, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[1].bRadioFreqRecordState, buffer, CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}
	*/
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_CURFREQUENCY,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[2].wCurFrequency);
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_CURRECORDINDEX,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[2].cCurRecordIndex);
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_CURECORDNUM,property,NULL);
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[2].cCurRecordNum);
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_CURPAGE,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[2].curPage);
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_TOTALPAGES,property,"1");
	sscanf(property,"%d", &pLocalParam->stszRadioChannelRecord[2].totalPages);
	char channelName3[32] = FLY_RADIO_RADIOCHANNELRECORD3_RADIOFRERECORD;
	char channelState3[32] = FLY_RADIO_RADIOCHANNELRECORD3_FREQRECORDSTATE;
	for(int i = 0; i < pLocalParam->stszRadioChannelRecord[2].totalPages; i++)
	{
			char char_i[CHAR_LEN];
			sprintf(char_i,"%d", i);

			char readFreq[64];
			strcpy(readFreq,channelName3);
			strcat(readFreq,char_i);


			char buffer[2*CHANNEL_RECORD_NUM];
			u16 num[2*CHANNEL_RECORD_NUM];
			property_get(readFreq, property, NULL);
			value = stringToBuffer(property, buffer);
			if(value > 0)
			{
				memcpy(num, buffer, 2*CHANNEL_RECORD_NUM );
				int index = i * CHANNEL_RECORD_NUM;
				for(int j = 0; j < CHANNEL_RECORD_NUM; j++)
				{
					pLocalParam->stszRadioChannelRecord[2].wRadioFreqRecord[index + j] = num[j];
				}

			}

			char readState[64];
			strcpy(readState,channelState3);
			strcat(readState,char_i);
			property_get(readState, property, NULL);
			value = stringToBuffer(property, buffer);
			if(value > 0)
			{

				int index = i * CHANNEL_RECORD_NUM;
				for(int j = 0; j < CHANNEL_RECORD_NUM; j++)
				{
					pLocalParam->stszRadioChannelRecord[2].bRadioFreqRecordState[index + j] = buffer[j];
				}

			}
	}
	/*
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_RADIOFRERECORD, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[2].wRadioFreqRecord, buffer, 2*CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}

	property_get(FLY_RADIO_RADIOCHANNELRECORD3_FREQRECORDSTATE, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->stszRadioChannelRecord[2].bRadioFreqRecordState, buffer, CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE);
	}
*/
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_SENSITIVITY,property,"0");
	sscanf(property,"%hhd", &pLocalParam->sensitivitystate);
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_TA,property,"0");
	sscanf(property,"%hhd", &pLocalParam->radioTAstate);
	property_get(FLY_RADIO_TAAF_VISIBLE,property,"0");
	sscanf(property,"%hhd", &pLocalParam->cTAAFVisible);
	property_get(FLY_RADIO_RADIOCHANNELRECORD3_AF,property,"255");
	sscanf(property,"%hhd", &pLocalParam->radioAFstate);
	if(pLocalParam->cTAAFVisible == 1)
	{
		if(pLocalParam->radioAFstate == 0xff || pLocalParam->radioAFstate == 0x01)
		{
			pLocalParam->radioAFstate = 1;
		}
		else 
		{
			pLocalParam->radioAFstate = 0;
		}
	}
	else 
	{
		pLocalParam->radioAFstate = 0;
	}
}





int enc_get_utf8_size(const unsigned char pInput)
{
	unsigned char c = pInput;
	if(c < 0x80) return 1;
	if(c >= 0x80 && c < 0xC0) return -1;
	if(c >= 0xC0 && c < 0xE0) return 2;
	if(c >= 0xE0 && c < 0xF0) return 3;
	if(c >= 0xF0 && c < 0xF8) return 4;
	if(c >= 0xF8 && c < 0xFC) return 5;
	if(c >= 0xFC) return 6;

	return -1;
}

int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic)
{
    char b1, b2, b3, b4, b5, b6;

    *Unic = 0x0;// �� *Unic ��ʼ��Ϊȫ��
    int utfbytes = enc_get_utf8_size(*pInput);
    unsigned char *pOutput = (unsigned char *)Unic;

    switch(utfbytes)
    {
    case 1:
        *pOutput = *pInput;
        break;
    case 2:
        b1 = *pInput;
        b2 = *(pInput + 1);
        if ( (b2 & 0xC0) != 0x80 )
            return 0;
        *pOutput     = (b1 << 6) + (b2 & 0x3F);
        *(pOutput+1) = (b1 >> 2) & 0x07;
        break;
    case 3:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b2 << 6) + (b3 & 0x3F);
        *(pOutput+1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
        break;
    case 4:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b3 << 6) + (b4 & 0x3F);
        *(pOutput+1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
        *(pOutput+2) = ((b1 << 2) & 0x1C)  + ((b2 >> 4) & 0x03);
        break;
    case 5:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b4 << 6) + (b5 & 0x3F);
        *(pOutput+1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
        *(pOutput+2) = (b2 << 2) + ((b3 >> 4) & 0x03);
        *(pOutput+3) = (b1 << 6);
        break;
    case 6:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        b6 = *(pInput + 5);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)
                || ((b6 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b5 << 6) + (b6 & 0x3F);
        *(pOutput+1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
        *(pOutput+2) = (b3 << 2) + ((b4 >> 4) & 0x03);
        *(pOutput+3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
        break;
    default:
        return 0;
        break;
    }//switch(utfbytes)

    return utfbytes;
}


int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize)
{
	int nSrcLen = 0;
	int nDstLen = 0;
	u8 *pUtf8 = pInput;
	u8 *pUnic = pOutput;
	int nOneUtf8Len = 0;

	nOneUtf8Len = enc_get_utf8_size(*pUtf8);

	while(-1 != nOneUtf8Len)
	{
		unsigned long oneUnic = 0;
		enc_utf8_to_unicode_one(pUtf8, &oneUnic);

		nDstLen += 2;
		if (nOutputSize < nDstLen)//װ���£�����
		{
			nDstLen -= 2;
			break;
		}
		else
			memcpy(pUnic, &oneUnic, 2);

		nSrcLen += nOneUtf8Len;
		if (nSrcLen >= nInputLen)//�������ˣ��˳�
		{
			break;
		}

		pUtf8 += nOneUtf8Len;
		pUnic += 2;

		nOneUtf8Len = enc_get_utf8_size(*pUtf8);
	}

	return nDstLen;
}


uni16_size_t uni16_strlen(const unicode16_t *uni16)
{
	return 0;
}
unicode16_t ansi_to_unicode16(const unsigned char ansi)
{
	return 0;
}
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16)
{
	int nSrcLen = strlen((char*)ansi);
	int nUni16Len = nSrcLen*2+2;
	int nRetLen = utf8_2_ucs2(ansi, nSrcLen, (u8*)uni16, nUni16Len);
	
	return (nRetLen/2);
}
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16)
{
	return 0;
}

