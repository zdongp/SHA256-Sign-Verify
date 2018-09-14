#include "BtBC6Adapter.h"
#include "BtHal.h"
#include "BtApp.h" 
#include "BtParam.h" 


CBtBC6Adapter::CBtBC6Adapter(void)
{
}

CBtBC6Adapter::~CBtBC6Adapter(void)
{
}

//初始化
void CBtBC6Adapter::init(CBtHal *p1,CBtApp *p2,CBtParam *p3)
{
	m_pBtHal = p1;
	m_pBtApp = p2;
	m_pBtParam = p3;
}

void CBtBC6Adapter::deInit(void)
{

}

void CBtBC6Adapter::analyseAnsCmd_(char *p, int len)
{
	if(len < 0)
		return;
	
	if(len > (256*3))
		len = (256*3);
		
	char szDebug[256*3] = {0};
	memcpy(szDebug, p, len);
	LOGD("%s [%s] [%s] len=%d",BT_VERSION_BC08,__FUNCTION__, szDebug,len);

	m_pBtHal->IsCanSendRequestCmd();

	bool bRet = false;

	bRet = hspAndHfpResponse(p, len+2);
	if (bRet)
		return;

	bRet = a2dpAndAvrcpResponse(p, len+2);
	if (bRet)
		return;

	bRet = phoneBookAndCallRecordResponse(p, len);
	if (bRet)
		return;

	bRet = sppVirtualSeriesResponse(p, len+2);
	if (bRet)
		return;

	bRet = sdpBtSearchResponse(p, len+2);
	if (bRet)
		return;

	bRet = otherResponse(p, len+2);
	if (bRet)
		return;
}

//应答指令
bool CBtBC6Adapter::hspAndHfpResponse(char *p, int len)//1.14 HSP HFP 应答
{
	bool bRet = true;

	if (!strncmp(p, "IA", 2))//HFP 断开
	{
		LOGD("[%s] IA HFP disconnect", __FUNCTION__);
		m_pBtHal->getHfpConnectStatus(HFP_CONNECT_STATUS_DISCONNECT);
	}
	else if (!strncmp(p, "IB", 2))//HFP 连接成功
	{
		LOGD("[%s] IB HFP connect success",__FUNCTION__);
		m_pBtHal->getHfpConnectStatus(HFP_CONNECT_STATUS_CONNECTED);
	}
	else if (!strncmp(p, "IC", 2))//去电
	{
		LOGD("[%s] IC callout",__FUNCTION__);
		if(len > 4)
		{
			if(strncmp(m_pBtParam->m_strTemOutNum,p + 2,len - 4))
			{
				if(m_pBtParam->nCallCount == CALLING_COUNT_FREE)
				{
					if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_FREE){
						m_pBtHal->getMultiCallState(MULTI_CALL_STATE_CALLING_ONLY);
					}
				}

				memset(m_pBtParam->m_strTemOutNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
				memcpy(m_pBtParam->m_strTemOutNum, p + 2, len - 4);
				memset(m_pBtParam->m_strTemOutName,0,PHONE_NUm_nNPUT_MAX_SIZE);
				m_pBtHal->getCallName(m_pBtParam->m_strTemOutNum,m_pBtParam->m_strTemOutName);
				
				m_pBtHal->getHfpPhoneNumCallInOrOut(BT_PHONE_STATUS_CALL_OUT,p + 2, len - 4);
				m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_CALL_OUT);
			}
		}
	}
	else if (!strncmp(p, "ID", 2))//来电显示
	{
		LOGD("[%s] ID caller ID display",__FUNCTION__);
		if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_CALLING_OR_WAITING || 
		   m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_MEETING_TEL)
		{
			g_pClsBtBC6Adapter->setToBtChipHandUpHandPhone();
			return false;
		}
		 	
		
		if(len > 4)
		{
			if(strncmp(m_pBtParam->m_strTemInNum,p + 2,len - 4))
			{
				memset(m_pBtParam->m_strTemInNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
				memcpy(m_pBtParam->m_strTemInNum, p + 2, len - 4);
				memset(m_pBtParam->m_strTemInName,0,PHONE_NUm_nNPUT_MAX_SIZE);
				m_pBtHal->getCallName(m_pBtParam->m_strTemInNum,m_pBtParam->m_strTemInName);
	
				m_pBtHal->getHfpPhoneNumCallInOrOut(BT_PHONE_STATUS_CALL_IN,p + 2, len - 4);
				m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_CALL_IN);
			}
		}
		else if(len == 4)
		{
			if(strncmp(m_pBtParam->m_strTemInNum, "unknown", 8))
			{
				memset(m_pBtParam->m_strTemInNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
				memcpy(m_pBtParam->m_strTemInNum, "unknown", 8);
				memset(m_pBtParam->m_strTemInName,0,PHONE_NUm_nNPUT_MAX_SIZE);
					
				m_pBtHal->getHfpPhoneNumCallInOrOut(BT_PHONE_STATUS_CALL_IN,"unknown", 8);
				m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_CALL_IN);
			}
		}
	}
	else if (!strncmp(p, "IE", 2))//Three Calling
	{
		LOGD("[%s] IE Waiting call !!",__FUNCTION__);
		if(len > 4)
		{
			if(strncmp(m_pBtParam->m_strTemWaitingNum,p + 2,len - 4))
			{
				memset(m_pBtParam->m_strTemWaitingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
				memcpy(m_pBtParam->m_strTemWaitingNum, p + 2, len - 4);
				memset(m_pBtParam->m_strTemWaitingName,0,PHONE_NUm_nNPUT_MAX_SIZE);
				m_pBtHal->getCallName(m_pBtParam->m_strTemWaitingNum,m_pBtParam->m_strTemWaitingName);

				if(!strncmp(m_pBtParam->str_CallInfor[0].cCaller_numb,p + 2,len - 4))
				{
					if(m_pBtParam->bSpecialHangUpIsStillOnHold)
						//g_pClsBtBC6Adapter->setToBtChipHangUpSpeakingAndReceiveAnother();
						g_pClsBtBC6Adapter->setToBtChipHangSpeakingAndReceiveAnother();
				}
				m_pBtParam->bSpecialHangUpIsStillOnHold = false;
			}
		}
		else if(len == 4)
		{
			memset(m_pBtParam->m_strTemWaitingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
			memcpy(m_pBtParam->m_strTemWaitingNum, "unknown", 8);
			memset(m_pBtParam->m_strTemWaitingName,0,PHONE_NUm_nNPUT_MAX_SIZE);
		}
	}
	else if (!strncmp(p, "IF", 2))//挂机
	{
		LOGD("[%s] IF Hang up",__FUNCTION__);
		m_pBtParam->nCallCount = CALLING_COUNT_FREE;
		m_pBtHal->getMultiCallState(MULTI_CALL_STATE_FREE);
		m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_FREE);
		m_pBtHal->setSyncCallRecordTimer();
	}
	else if (!strncmp(p, "IG", 2))//接听
	{
		LOGD("[%s] IG Answer",__FUNCTION__);
		if(m_pBtParam->m_eHfpAudioSource != HFP_AUDIO_SOURCE_CAR)
			m_pBtHal->getHfpDialingTransferPosStatus(BT_PHONE_STATUS_RECEIVE_PHONE);
		
		LOGD("m_pBtParam->em_MultiCallstate:%d,m_pBtParam->nCallCount:%d",m_pBtParam->em_MultiCallstate,m_pBtParam->nCallCount);
		if(m_pBtParam->nCallCount == CALLING_COUNT_FREE)
		{	
			m_pBtParam->nCallCount = CALLING_COUNT_ONLY;
			if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_FREE)
				m_pBtHal->getMultiCallState(MULTI_CALL_STATE_CALLING_ONLY);
		}

		if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_CALL_IN || m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_CALL_OUT)
		{
			
			char m_strCallingNum[PHONE_NUm_nNPUT_MAX_SIZE];
			memset(m_strCallingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
			
			if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_CALL_IN)
			{
				memcpy(m_strCallingNum,m_pBtParam->m_strTemInNum,strlen(m_pBtParam->m_strTemInNum));
			}
			else if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_CALL_OUT)
			{
				memcpy(m_strCallingNum,m_pBtParam->m_strTemOutNum,strlen(m_pBtParam->m_strTemOutNum));
			}

			int nLen = strlen(m_strCallingNum);
			
			if(nLen > 0)
			{
				m_pBtHal->getHfpBC8Calling(m_strCallingNum, nLen);
			}

			memset(m_strCallingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		}
	}
	else if (!strncmp(p, "IK", 2))//呼叫等待
	{
		LOGD("[%s] IK Call waiting",__FUNCTION__);
		memset(m_pBtParam->m_strTemCallingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		
		m_pBtHal->getMultiCallState(MULTI_CALL_STATE_CALLING_OR_WAITING);
		m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_CALL_IN_FROM_THIRD);
	}
	else if (!strncmp(p, "IL", 2))//挂断当前电话，接听等街中的电话成功
	{
		LOGD("[%s] IL Hang up the phone and Answer the waiting phone success.",__FUNCTION__);
		LOGD("m_pBtParam->em_MultiCallstate:%d,m_pBtParam->nCallCount:%d",m_pBtParam->em_MultiCallstate,m_pBtParam->nCallCount);
		if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_CALLING_OR_WAITING || 
			m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_MEETING_TEL)
		{
			m_pBtHal->getMultiCallState(MULTI_CALL_STATE_CALLING_ONLY);
		}

		if(m_pBtParam->nCallCount == CALLING_COUNT_MUTIL)
		{
			m_pBtParam->nCallCount = CALLING_COUNT_ONLY;
		}
		
		if(m_pBtParam->bHangUpAutoDailin){
			m_pBtParam->bHangUpAutoDailin = false;
			memset(m_pBtParam->m_strTemCallingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
			m_pBtParam->emTempHfpTalkingTransferSet = HFP_AUDIO_SOURCE_CAR;
			return bRet;
		}
	
		memset(m_pBtParam->m_strTemWaitingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		memset(m_pBtParam->m_strTemWaitingName,0,PHONE_NUm_nNPUT_MAX_SIZE);
		
		memset(m_pBtParam->m_strTemCallingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		m_pBtParam->emTempHfpTalkingTransferSet = HFP_AUDIO_SOURCE_CAR;
	}
	else if (!strncmp(p, "IM", 2))//进入电话会议
	{
		LOGD("[%s] IM Enter the conference call",__FUNCTION__);
		m_pBtHal->getMultiCallState(MULTI_CALL_STATE_MEETING_TEL);
		m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_CALL_MEETING);
	}
	else if (!strncmp(p, "IN", 2))
	{
		LOGD("[%s] IN For Multi-call is Calling or Waiting,HandUp one! ",__FUNCTION__);
		m_pBtHal->getMultiCallState(MULTI_CALL_STATE_CALLING_ONLY);
		if(m_pBtParam->nCallCount == CALLING_COUNT_MUTIL)
		{
			m_pBtParam->nCallCount = CALLING_COUNT_ONLY;
		}
		
		if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_TALKING && m_pBtParam->nCallCount == CALLING_COUNT_ONLY)
			g_pClsBtBC6Adapter->setToBtChipHangSpeakingAndReceiveAnother();
	}
	else if (!strncmp(p, "IR", 2))//去电或通话中的号码
	{
		LOGD("[%s] IR The calling phone number",__FUNCTION__);
		if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_MEETING_TEL)
		{
			if((!strncmp(p+2,m_pBtParam->tempMeetNum1, len-2)) || (!strncmp(p+2,m_pBtParam->tempMeetNum2, len-2)))
				return 0;
			else if(m_pBtParam->tempMeetNum1 == NULL)
				memcpy(m_pBtParam->tempMeetNum1,p+2,len-2);
			else
				memcpy(m_pBtParam->tempMeetNum2,p+2,len-2);
		}
		
		LOGD("m_pBtParam->em_MultiCallstate:%d,m_pBtParam->nCallCount:%d",m_pBtParam->em_MultiCallstate,m_pBtParam->nCallCount);
		if(m_pBtParam->nCallCount == CALLING_COUNT_FREE)
		{
			if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_FREE)
				m_pBtHal->getMultiCallState(MULTI_CALL_STATE_CALLING_ONLY);
		}
		
		if(len > 4)
		{
			m_pBtHal->getHfpBC8Calling(p + 2, len - 4);
			m_pBtHal->getHfpPhoneNumCallTalking(p + 2, len - 4);
		}
		else if(len == 4)
		{
			m_pBtHal->getHfpBC8Calling("unknown", 8);
			m_pBtHal->getHfpPhoneNumCallTalking("unknown", 8);
		}
	}
	else if(!strncmp(p,"T1",2))
	{
		LOGD("[%s] T1 Answer by phone",__FUNCTION__);
		m_pBtHal->getHfpDialingTransferPosStatus(BT_PHONE_STATUS_RECEIVE_PHONE);
	}
	else if(!strncmp(p,"T0",2))
	{
		LOGD("[%s] T0 Answer by bluetooth device",__FUNCTION__);
		m_pBtHal->getHfpDialingTransferPosStatus(BT_PHONE_STATUS_RECEIVE_BULETOOTH);
	}	
	else if (!strncmp(p, "IO", 2))//关闭、打开咪头
	{
		LOGD("[%s] IO Close or Open the microphone",__FUNCTION__);
		bool bMicOpenState = false;
		if (!strncmp(p, "IO0", 3))//mute
		{
			bMicOpenState = false;
		}
		else if(!strncmp(p, "IO1", 3))
		{
			bMicOpenState = true;
			
		}

		if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_TALKING){
			m_pBtHal->getHfpMicStatus(bMicOpenState);
		}
	}
	else if (!strncmp(p, "IV", 2))//HFP 连接中
	{
		LOGD("[%s] IV HFP connecting",__FUNCTION__);

		m_pBtHal->getHfpConnectStatus(HFP_CONNECT_STATUS_CONNECTING);
	}
	else if (!strncmp(p, "MC", 2))//蓝牙出声音
	{
		LOGD("[%s] MC Voice on bt",__FUNCTION__);
		m_pBtHal->getHfpDialingTransferPosStatus(BT_PHONE_STATUS_RECEIVE_BULETOOTH);
	}
	else if (!strncmp(p, "MD", 2))//手机出声音
	{
		LOGD("[%s] MD Voice on the phone",__FUNCTION__);
		m_pBtHal->getHfpDialingTransferPosStatus(BT_PHONE_STATUS_RECEIVE_PHONE);
	}
	else if (!strncmp(p, "KI", 2))//当前 spk 及 mic 音量
	{
		LOGD("[%s] KI Current volume of the spk and mic",__FUNCTION__);

		int nSpkVolume = 0, nMicVolume = 0;

		//nSpkVolume = p[2];
		nMicVolume = atoi(&p[2]);

		m_pBtHal->getHfpSpkAndMicVolume(nSpkVolume, nMicVolume);
	}

	else if (!strncmp(p, "MG", 2))//HFP 的状态
	{
		LOGD("[%s] MG The HFP state",__FUNCTION__);
	}
	else if (!strncmp(p, "FF", 2))//voice dailing fail
	{
		LOGD("[%s] voice dailing over",__FUNCTION__);
		m_pBtHal->getVoiceDialingStatus(0x00);
	}
	else if (!strncmp(p, "FS", 2))//voice dailing succese
	{
		LOGD("[%s] voice dailing succese",__FUNCTION__);

		m_pBtHal->getVoiceDialingStatus(0x01);
	}
	else if (!strncmp(p, "FC", 2))//voice dailing chance
	{
		LOGD("[%s] voice dailing chance",__FUNCTION__);
		m_pBtHal->getVoiceDialingStatus(0x00);
	}
	else if (!strncmp(p, "FT1", 3))//support voice dailing 
	{
		m_pBtHal->supportVoiceStatus(1);
	}
	else if (!strncmp(p, "FT2", 3))//donot support voice dailing 
	{
		m_pBtHal->supportVoiceStatus(0);
	}
	else
	{
		bRet = false;
	}

	return bRet;
}

bool CBtBC6Adapter::a2dpAndAvrcpResponse(char *p, int len)//1.15 A2dp/Avrcp 应答
{
	bool bRet = true;

	if (!strncmp(p, "MA", 2))//音乐暂停中、连接成功
	{
		m_pBtHal->GetA2DPPlayOrStopState_switch(1);
	}
	else if (!strncmp(p, "MB", 2))//音乐播放中
	{
		LOGD("[%s] MB A2dp/Avrcp music playing",__FUNCTION__);
		m_pBtHal->GetA2DPPlayOrStopState_switch(2);
	}
	else if (!strncmp(p, "MU", 2))//A2DP的状态
	{
		LOGD("[%s] MU A2dp State",__FUNCTION__);
		if(p[2] == '1'){
			m_pBtHal->getA2DPStatus(false);
		}
		else
		{
			m_pBtHal->getA2DPStatus(true);
		}
	}
	else if (!strncmp(p, "MI", 2))//歌曲信息
	{
		LOGD("[%s] MI Song information",__FUNCTION__);
		char singName[FLY_BT_MUSIC_INFOR_MAX_LEN]={0};
		char author[FLY_BT_MUSIC_INFOR_MAX_LEN]={0};
		int nFF1=0;
		nFF1=findCharIndex((unsigned char*)p,len,0xFF);
		//LOGD("[%s1] nFF1:%d",__FUNCTION__,nFF1);
		if(-1 != nFF1)
		{
		    //LOGD("[%s2] nFF1:%d",__FUNCTION__,nFF1);
			int singNameLen=nFF1-2;
			if(singNameLen > FLY_BT_MUSIC_INFOR_MAX_LEN)
				singNameLen = FLY_BT_MUSIC_INFOR_MAX_LEN;

			memcpy(singName,(p+2),singNameLen);
			//LOGD("[%s] singName:%s",__FUNCTION__,singName);
			int nFF2=0;
			nFF2=findCharIndex((unsigned char*)(p+nFF1+1),len-nFF1-1,0xFF);
			
			//LOGD("[%s] nFF2:%d",__FUNCTION__,nFF2);
			if(-1 != nFF2)
			{
				int authorLen=nFF2;
				//LOGD("[%s] authorLen:%d",__FUNCTION__,authorLen);
				if(authorLen > FLY_BT_MUSIC_INFOR_MAX_LEN)
					authorLen = FLY_BT_MUSIC_INFOR_MAX_LEN;
				
				memcpy(author,(p+nFF1+1),authorLen);
				//LOGD("[%s] author:%s",__FUNCTION__,author);
				m_pBtHal->getA2DPInfo(singName,singNameLen,author,authorLen,(char *)"",0);
				g_pClsBtJniSdk->sendToAppBtSongInfo(singName,author,(char *)"",singNameLen,authorLen,0);
			}
                    
			
		}
		
	}
	else if (!strncmp(p, "MY", 2))//A2DP断开
	{
	}
	else if (!strncmp(p, "ML", 2))//AVRCP的状态
	{
		LOGD("[%s] ML Avrcp state",__FUNCTION__);
	}
	else if((!strncmp(p, "M(", 2)) || (!strncmp(p, "M)", 2)) || 
		   (!strncmp(p, "M0", 2)) || (!strncmp(p, "M1", 2)) ||  
		   (!strncmp(p, "M2", 2)) || (!strncmp(p, "M3", 2)) ||
		   (!strncmp(p, "M4", 2)) || (!strncmp(p, "M5", 2)) ||
		   (!strncmp(p, "M6", 2)) ||(!strncmp(p, "M7", 2)))//song title/Author/Album
	{
		static char songTitle[FLY_BT_MUSIC_INFOR_MAX_LEN];
		static char author[FLY_BT_MUSIC_INFOR_MAX_LEN];
		static char album[FLY_BT_MUSIC_INFOR_MAX_LEN];
		static short nTotalCount = 0;
		static short nCurSongNumber = 0;
		static int nCurSongTotalTime = 0;
		static long int nCurSongPlayTime = 0;

		if(!strncmp(p, "M(", 2))
		{
			memset(songTitle,0,sizeof(songTitle));
			memset(author,0,sizeof(author));
			memset(album,0,sizeof(album));
			nTotalCount = 0;
			nCurSongNumber = 0;
			nCurSongTotalTime = 0;
			nCurSongPlayTime = 0;
		}
		
		if(!strncmp(p, "M0", 2))
		{
			if(len - 2 > 0){
				memcpy(songTitle,p + 2,len - 2);
			}
		}
		else if(!strncmp(p, "M1", 2))
		{
			if(len - 2 > 0){
				memcpy(author,p + 2,len - 2);
			}
		}
		else if(!strncmp(p, "M2", 2))
		{
			if(len - 2 > 0){
				memcpy(album,p + 2,len - 2);
			}
		}
		else if(!strncmp(p, "M3", 2))//The total number of songs
		{
			nCurSongNumber = atoi(&p[2]);
			m_pBtParam->musicCurSong = nTotalCount;
		}
		else if(!strncmp(p, "M4", 2))//Cur Song Number 
		{
			nTotalCount = atoi(&p[2]);
			m_pBtParam->musicTotal = nTotalCount;
		}
		else if(!strncmp(p, "M5", 2))//Song Genre
		{
		}
		else if(!strncmp(p, "M6", 2))//The song is playing long
		{
			nCurSongTotalTime = atoi(&p[2]);//ms
		}
		else if(!strncmp(p, "M7", 2))//Long playsing the current song
		{
			sscanf(&p[2],"%x",&nCurSongPlayTime);
			m_pBtHal->getSongPlayingTime(nCurSongPlayTime);
		}

		if(!strncmp(p, "M)", 2))
		{
			m_pBtHal->getA2DPInfo(songTitle,strlen(songTitle),author,strlen(author),album,strlen(album));
			m_pBtHal->getSongTrackInfor(nTotalCount,nCurSongNumber);
			m_pBtHal->getSongTotalTime(nCurSongTotalTime);
		}
	}
	else if(!strncmp(p, "M8", 2))//MUSIC FOLDER (<type>,<msb>,<lsb>,<display>)
	{
		LOGD("**********************************  M8 song FOLDER  ***********************************************");
	}
	else if(!strncmp(p, "M9", 2))//MUSIC FILE (<msb>,<lsb>,<display>)
	{
		LOGD("********************************  M9 song FILE  *************************************************");
	}
	else if(!strncmp(p, "Qa", 2))//operation music browsing
	{
		LOGD("[%s] Qa Support music browsing!!! ",__FUNCTION__);
		bool bTemp = false;
		if(p[2] == '1')
		{
			bTemp = true;
		}
	}
	else
	{
		bRet = false;
	}

	return bRet;
}

bool CBtBC6Adapter::phoneBookAndCallRecordResponse(char *p, int len)//1.16 电话本、通知记录应答
{
    //   LOGD("[%s]  p:%s  len:%d",__FUNCTION__,p,len);
	bool bRet = true;

	if (!strncmp(p, "PA", 2))//电话本同步状态
	{
		LOGD("[%s] PA Phonebook synchronous state . state:%c",__FUNCTION__,p[2]);

		m_pBtHal->getPhoneBookSyncStatus((p[2] == 1) ? true : false);
	}
	else if (!strncmp(p, "PF", 2))//电话条目
	{
		LOGD("[%s] PF The count of phonebook ",__FUNCTION__);

		char szUserName[PHONENUM_OR_PHONENAME_MAX_LEN];
		int nUserNameLen = 0;
		char szUserNo[PHONENUM_OR_PHONENAME_MAX_LEN];
		int nUserNoLen = 0;
		memset(szUserName,0,sizeof(szUserName));
		memset(szUserNo,0,sizeof(szUserNo));

		int nFF = findCharIndex((unsigned char*)p+2, len - 2, 0xFF);
		if (-1 != nFF)
		{
			char szTemName[PHONENUM_OR_PHONENAME_MAX_LEN];
			int nTemNameLen = nFF;
			if(nTemNameLen > PHONENUM_OR_PHONENAME_MAX_LEN)
				nTemNameLen = PHONENUM_OR_PHONENAME_MAX_LEN;
			nUserNoLen = len - nFF - 1 - 2;
			memset(szTemName,0,sizeof(szTemName));
			if(nFF!=0)
				memcpy(szTemName,p+2,nTemNameLen);
			else
				memcpy(szTemName,p + 2 + nFF + 1,nUserNoLen);
			m_pBtHal->AnalyzeContactsExtendedName(szTemName);
			m_pBtHal->ToUI_FormalityOfContacts(szUserName);
		//	m_pBtHal->InitContactsExtendedNameParamValue();
			nUserNameLen = strlen(szUserName);
			
			//nUserNoLen = len - nFF - 1 - 2;
			if(nUserNoLen < 0)return bRet;
			
			if(nUserNoLen > PHONENUM_OR_PHONENAME_MAX_LEN)
				nUserNoLen = PHONENUM_OR_PHONENAME_MAX_LEN;
			if(!strncmp(szUserNo,p + 2 + nFF + 1,nUserNoLen))
				return bRet;
			memcpy(szUserNo, p + 2 + nFF + 1, nUserNoLen);  
			m_pBtApp->SendPhoneNumToApp(p+2,len-2);   
			m_pBtHal->getPhoneBookOneItem(szUserName, nUserNameLen, szUserNo, nUserNoLen);

			LOGD("szUserNo: %s",szUserNo);
			m_pBtApp->m_pBtPhoneBookPages->getPhoneNumDetailInfo(szUserName, nUserNameLen, szUserNo, nUserNoLen);
			m_pBtHal->InitContactsExtendedNameParamValue();
		}
		
	}
	else if (!strncmp(p, "PD", 2))//通讯记录条目
	{
		LOGD("[%s] PD The count of calllog ",__FUNCTION__);

		char type;
		char szUserName[CALL_HISTORY_NAME_MAX_LEN] = {0};
		int nUserNameLen = 0;
		char szUserNo[CALL_HISTORY_NUMBER_MAX_LEN] = {0};
    	char time[CALL_HISTORY_TIME_MAX_LEN]={0};
		int nUserNoLen;
		int nUserTimeLen;

		int nFF1 = findCharIndex((unsigned char*)p + 3, len - 3, 0xFF);
		if (-1 != nFF1)
		{
			type=*((char*)(p+2));
			//LOGD("[%s] type:%c ",__FUNCTION__,type);

			char szTemName[CALL_HISTORY_NAME_MAX_LEN];
			int nTemNameLen = nFF1;
			if(nTemNameLen > CALL_HISTORY_NAME_MAX_LEN)
				nTemNameLen = CALL_HISTORY_NAME_MAX_LEN;
			
			
			memset(szTemName,0,sizeof(szTemName));
			memcpy(szTemName,p + 3,nTemNameLen);

			m_pBtHal->AnalyzeContactsExtendedName(szTemName);
			m_pBtHal->ToUI_FormalityOfContacts(szUserName);
			m_pBtHal->InitContactsExtendedNameParamValue();
			nUserNameLen = strlen(szUserName);
			//LOGD("[%s] szUserName:%s,nUserNameLen:%d ",__FUNCTION__,szUserName,nUserNameLen);

			int nFF2 = findCharIndex((unsigned char*)(p + 3 + nFF1 + 1), len - 3 - nFF1 - 1, 0xFF);
			if(-1 != nFF2)
			{
				nUserNoLen = nFF2;
				if(nUserNoLen > CALL_HISTORY_NUMBER_MAX_LEN)
					nUserNoLen = CALL_HISTORY_NUMBER_MAX_LEN;
							
				memcpy(szUserNo, p + 3 + nFF1 + 1, nUserNoLen);
				//LOGD("[%s] szUserNo:%s ,nUserNoLen:%d",__FUNCTION__,szUserNo,nUserNoLen);

				nUserTimeLen = len - 3 - nFF1 - 1 - nFF2 - 1;
				if(nUserTimeLen < 0)return true;
				
				if(nUserTimeLen > CALL_HISTORY_TIME_MAX_LEN)
					nUserTimeLen = CALL_HISTORY_TIME_MAX_LEN;
								
				memcpy(time, p + 3 + nFF1 + 1 + nFF2 + 1, nUserTimeLen);
				//LOGD("[%s] time:%s ,nUserTimeLen:%d",__FUNCTION__,time,nUserTimeLen);
			}
			if(nUserNoLen < 3)
			{
				nUserNoLen = 7;
				memcpy(szUserNo, "Unknown", nUserNoLen);
				//LOGD("szUserNo=%s nUserNoLen = %d",szUserNo,nUserNoLen);
			}

			m_pBtHal->newGetHistoryCallOneItem(type,szUserName, nUserNameLen, szUserNo, nUserNoLen,time,nUserTimeLen);
			//m_pBtApp->m_pCallRecordPages->showListHistoryCall();
		}

		m_pBtParam->m_bIsCallLogLoadFinish = false;

		//m_pBtApp->m_pCallRecordPages->showLoadingCallLogTips(1);
		//m_pBtApp->m_pBtPhoneBookPages->showLoadingPhoneBookTips(1);
	}
	else if (!strncmp(p, "PE", 2))
	{
		LOGD("[%s] PE  AllCallLog download finish",__FUNCTION__);
		m_pBtApp->m_pCallRecordPages->createListHistoryCall();	
		m_pBtApp->m_pCallRecordPages->showLoadingCallLogTips(0);

		m_pBtHal->callRecordDownloadFinish();

		m_pBtHal->syncInitPhoneBookAllTime();
		m_pBtParam->m_bSetBookTimeSign = true;
		m_pBtHal->syncInitPhoneBook();
		m_pBtParam->m_bIsCallLogLoadFinish = true;
	}
	else if(!strncmp(p,"PC",2))
	{
        LOGD("[%s] PC  Phonebook download finish",__FUNCTION__);
		m_pBtHal->PhonebookDownloadFinish();
		m_pBtApp->SendPhoneNumToAppEndTag();
	}
	else
	{
		bRet = false;
	}

	return bRet;
}

void CBtBC6Adapter::loadCallLog()
{
		setToBtChipSyncMissAnswerCallIn();
		m_pBtHal->clearListHistoryCall();	
}

bool CBtBC6Adapter::sppVirtualSeriesResponse(char *p, int len)//1.17 SPP 虚拟串口 应答
{
	bool bRet = true;

	if (!strncmp(p, "SR", 2))//SPP 通道状态
	{
		LOGD("[%s] SR  SPP channel state",__FUNCTION__);
	}
	else
	{
		bRet = false;
	}

	return bRet;
}

bool CBtBC6Adapter::sdpBtSearchResponse(char *p, int len)//1.22 SDP 蓝牙搜索应答
{
	bool bRet = true;

	if (!strncmp(p, "SF", 2))//搜索到的蓝牙设备
	{      
		m_pBtHal->getLocalBtDevice_SearchedDeviceCounts(p,len);
	}
	else if (!strncmp(p, "SH",2))//搜索结束 
	{
		m_pBtHal->getLocalBtDevice_SearchFinish();
	}
	else if (!strncmp(p, "AU",2))//BC8 pairing
	{
		char szPincode[128] = {0};
		int nPincodeLen = 0;
		char szPairingName[128] = {0};
		int nPairingNameLen = 0;
		int nDataLen = len-2;
		int nTo = Inside_FindIndexFromStr((u8 *)(p + 2),nDataLen,',',0);
		if(nTo > 0)
		{
			memcpy(szPincode,p+2,nTo);
			nPincodeLen = nTo;
		}

		if((nDataLen - nTo -1) > 0)
		{
			memcpy(szPairingName,p+2+nTo+1,nDataLen - nTo -1);
			nPairingNameLen = nDataLen - nTo -1;
		}
		
		m_pBtHal->getPairingModeInfors_Bi_directional(szPincode,nPincodeLen,szPairingName,nPairingNameLen);
		if(m_pBtParam->tempAutoMatetsg = true)
		{
			m_pBtParam->bIsPairBox = true;
		}
			
	}
	else
	{
		bRet = false;
	}

	return bRet;
}

bool CBtBC6Adapter::otherResponse(char *p, int len)//1.23 其他应答
{
	bool bRet = true;

	if (!strncmp(p, "MF", 2))//来电自动接听、模块上电自动重连设置
	{
		LOGD("[%s] MF  Answer incoming call/Power on reconnection",__FUNCTION__);	
		m_pBtHal->getLocalBtDeviceAutoConnectState(p, len);
	}
	else if (!strncmp(p, "MW", 2))//模块版本号
	{
		LOGD("[%s] MW  Module version:%s",__FUNCTION__,p+2);

		m_pBtHal->getLocalBtDeviceVersion(p + 2, len - 2 - 2);
	}
	else if (!strncmp(p, "MM", 2))//模块设备名
	{
		LOGD("[%s] MM  Module device name",__FUNCTION__);

		m_pBtHal->getLocalBtDeviceName(p + 2, len - 2 - 2);
	}
	else if (!strncmp(p, "MN", 2))//模块PIN码
	{
		LOGD("[%s] MN  Module PIN code",__FUNCTION__);

		m_pBtHal->getLocalBtDevicePinCode(p + 2, len - 2 - 2);
	}
	else if (!strncmp(p, "DB", 2))//模块设备地址
	{
		LOGD("[%s] DB  Module device address",__FUNCTION__);

		m_pBtHal->getLocalBtDeviceAddr(p + 2, len - 2 - 2);
	}
	else if (!strncmp(p, "MX", 2))//与模块配对过的蓝牙设备 
	{
		char szAddr[FLY_BT_PAIRING_ADDRS_MAX_LEN];
		memset(szAddr,0,sizeof(szAddr));
		
		char szName[FLY_BT_PAIRING_NAME_MAX_LEN];
		memset(szName,0,sizeof(szName));
		int nSzNameLen = 0;

		int index = p[2];
		memcpy(szAddr, p + 3, 12);

		nSzNameLen = len - 3 - 12 - 2;
		if(nSzNameLen > FLY_BT_PAIRING_NAME_MAX_LEN)
			nSzNameLen = FLY_BT_PAIRING_NAME_MAX_LEN;
		
		memcpy(szName, p + 3 + 12,nSzNameLen);

		LOGD("[%s] MX  Paired with the module of the Bluetooth device. index = [%d] add = [%s], name = [%s]",__FUNCTION__, index, szAddr, szName);
		
		m_pBtHal->getBtDeviceHasPaired(index, szAddr, 12, szName, nSzNameLen);
		
	}
	else if (!strncmp(p, "II", 2))//进入配对
	{
		LOGD("[%s] II  Enter pairing",__FUNCTION__);

		m_pBtHal->getBtPairStatus(true);
	}
	else if (!strncmp(p, "IJ", 2))//退出配对
	{
		LOGD("[%s] IJ  Exit pairing",__FUNCTION__);

		m_pBtHal->getBtPairStatus(false);
	}
	else if (!strncmp(p, "IS", 2))//蓝牙初始化完成
	{
		LOGD("[%s] IS  Bluetooth initialization complete",__FUNCTION__);

		m_pBtHal->getLocalBtDeviceInitFinished();
	}
	else if (!strncmp(p, "PS", 2))//手机信号强度、电池电量
	{
		LOGD("[%s] PS  Cell phone signal strength/Battery power",__FUNCTION__);
		
		m_pBtHal->getMobileSignalAndBattery(&p[2], &p[4]);
	}
	else if (!strncmp(p, "JH", 2))//当前已连接蓝牙设备地址
	{
		LOGD("[%s] JH  Currently connected Bluetooth device address",__FUNCTION__);
		m_pBtHal->getCurConnectedBtDeviceAddr(p + 2, len - 2 - 2);
	}
	else if (!strncmp(p, "SA", 2))//当前已连接蓝牙设备名字
	{
		LOGD("[%s] SA  Currently connected Bluetooth device name",__FUNCTION__);
		m_pBtHal->getCurConnectedBtDeviceName(p + 2, len - 2 - 2);
		m_pBtHal->BtDeviceNameOfThedeviceconnectedToTheinsidepagesAndtheRealPairIsNotTheSame();
	}
	else if (!strncmp(p, "GV", 2))
	{
		LOGD("[%s] GV MIC GAIN DATA.",__FUNCTION__);
		m_pBtHal->getBtDeviceMicGain(&p[2]);
	}
	else if(!strncmp(p, "OK", 2))
	{
		LOGD("[%s] OK.",__FUNCTION__);
		m_pBtHal->Message_GetDevice_OK();
	}
	else if(!strncmp(p, "A0", 2))//BC8 UsingwhichDevice
	{
		LOGD("[%s] A0.",__FUNCTION__);
	}
	else if(!strncmp(p, "Qs", 2))//BC8 ConnectedDeviceCounts
	{
		LOGD("[%s] Qs.",__FUNCTION__);
	}
	else
	{
		bRet = false;
	}

	return bRet;
	
}

//请求指令
void CBtBC6Adapter::setToBtChipAtCmd(char *p, int len)
{
	LOGD("[%s] p:%s len:%d", __FUNCTION__, p,len);
	int nAllLen = 0, s = 0;
	char szCmd[FLY_BT_DEVICE_TO_HAL_CMD_MAX_LEN] = {0};
	s = sizeof(szCmd);

	memcpy(szCmd,"AT#", 3);

	if(len > (FLY_BT_DEVICE_TO_HAL_CMD_MAX_LEN - 5))
		len = FLY_BT_DEVICE_TO_HAL_CMD_MAX_LEN - 5;
	
	memcpy(szCmd + 3, p, len);
	memcpy(szCmd + 3 + len, "\r\n", 2);

	nAllLen = 3 + len + 2;

	outPutUtf8StringToTerminal(szCmd, nAllLen);
	//写到串口
	m_pBtHal->setToHalBtMsg(szCmd, nAllLen);
}

//HSP/HFP
void CBtBC6Adapter::setToBtChipStartPairMode(void)
{
	setToBtChipAtCmd((char*)"CA", 2);
}

void CBtBC6Adapter::setToBtChipEndPairMode(void)
{
	setToBtChipAtCmd((char*)"CB", 2);
}

void CBtBC6Adapter::setToBtChipConnectHFP(void)//连接最后一个配对设备
{	
	setToBtChipAtCmd((char*)"CC", 2);
}

void CBtBC6Adapter::setToBtChipConnectHFP(int index)//连接配对列表<index>设备
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "CC%d", index);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipConnectHFP(char *p, int len)//连接指定地址设备
{
	char szCmd[64] = {0};
	int s = sizeof(szCmd);

	memcpy(szCmd, "CC", 2);
	memcpy(szCmd + 2, p, len);

	setToBtChipAtCmd(szCmd, len + 2);
}

void CBtBC6Adapter::setToBtChipDisConnectHFPAndA2DP(void)
{
	setToBtChipAtCmd((char*)"CD", 2);
	LOGD("FA SONG CD  CMD");
}

void CBtBC6Adapter::setToBtChipAnswerCallIn(void)
{
	setToBtChipAtCmd((char*)"CE", 2);
}

void CBtBC6Adapter::setToBtChipRefuseCallIn(void)
{
	setToBtChipAtCmd((char*)"CF", 2);
}

void CBtBC6Adapter::setToBtChipHangUpCall(void)
{
	LOGD("[%s] ",__FUNCTION__);
	setToBtChipAtCmd((char*)"CG", 2);
}

void CBtBC6Adapter::setToBtChipReDial(void)
{
	setToBtChipAtCmd((char*)"CH", 2);
}

void CBtBC6Adapter::setToBtChipStartVoiceDial(void)
{
	setToBtChipAtCmd((char*)"CI", 2);
}

void CBtBC6Adapter::setToBtChipCancleVoiceDial(void)
{
	setToBtChipAtCmd((char*)"CJ", 2);
}

void CBtBC6Adapter::setToBtChipMicrophoneOpenCloseSwitch(void)
{
	setToBtChipAtCmd((char*)"CM", 2);
}

void CBtBC6Adapter::setToBtChipVoiceDeviceSwitch(void)
{
	setToBtChipAtCmd((char*)"CO", 2);
}

void CBtBC6Adapter::setToBtChipVoiceSwitchToMobilePhone(void)
{
	setToBtChipAtCmd((char*)"CN", 2);
}

void CBtBC6Adapter::setToBtChipVoiceSwitchToBtChip(void)
{
	setToBtChipAtCmd((char*)"CP", 2);
}

void CBtBC6Adapter::setToBtChipVoiceSwitchToMicOpen(void)
{
	setToBtChipAtCmd((char*)"IC", 2);
}

void CBtBC6Adapter::setToBtChipVoiceSwitchToMicClose(void)
{
	setToBtChipAtCmd((char*)"IO", 2);
}

void CBtBC6Adapter::setToBtChipCtrlSpkVolume(int vol)
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "CK%d", vol);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipCtrlMicVolume(int vol)
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "CL%d", vol);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipCtrlGainData(void)
{
	setToBtChipAtCmd((char*)"UP/sdcard/doc", 13);
}
void CBtBC6Adapter::setToBtChipDialNum(char *p, int len)
{
    LOGD("[%s] [%s]",__FUNCTION__,p);
	char szCmd[64] = {0};
	int s = sizeof(szCmd);

	memcpy(szCmd, "CW", 2);
	memcpy(szCmd + 2, p, len);

	setToBtChipAtCmd(szCmd, len + 2);
}

void CBtBC6Adapter::setToBtChipDialNumMore(char *p, int len)//DTMF
{
	char szCmd[64] = {0};
	int s = sizeof(szCmd);

	memcpy(szCmd, "CX", 2);
	memcpy(szCmd + 2, p, len);

	setToBtChipAtCmd(szCmd, len + 2);
}

void CBtBC6Adapter::setToBtChipQueryHfpStatus(void)
{
	setToBtChipAtCmd((char*)"CY", 2);
}

void CBtBC6Adapter::setToBtChipHandUpHandPhone(void)//挂断挂起中、等待中的电话
{
	setToBtChipAtCmd((char*)"CQ", 2);
}

void CBtBC6Adapter::setToBtChipHangUpSpeakingAndReceiveAnother(void)//挂断当前电话，接听等待中的电话
{
	setToBtChipAtCmd((char*)"CR", 2);
}

void CBtBC6Adapter::setToBtChipHangSpeakingAndReceiveAnother(void)//挂起当前电话，接听挂起的电话 or Second_coming
{
	setToBtChipAtCmd((char*)"CS", 2);
}

void CBtBC6Adapter::setToBtChipStartMobilePhoneMeeting(void)
{
	setToBtChipAtCmd((char*)"CT", 2);
}
//A2DP
void CBtBC6Adapter::setToBtChipMusicPlay(void)
{
	setToBtChipAtCmd((char*)"MA", 2);
}

void CBtBC6Adapter::setToBtChipMusicPause(void)
{
	setToBtChipAtCmd((char*)"MB", 2);
}

void CBtBC6Adapter::setToBtChipMusicStop(void)
{
	setToBtChipAtCmd((char*)"MC", 2);
}

void CBtBC6Adapter::setToBtChipNextSong(void)
{
	setToBtChipAtCmd((char*)"MD", 2);
}

void CBtBC6Adapter::setToBtChipPreSong(void)
{
	setToBtChipAtCmd((char*)"ME", 2);
}

void CBtBC6Adapter::setToBtChipQueryA2dpStatus(void)
{
	setToBtChipAtCmd((char*)"MV", 2);
}

void CBtBC6Adapter::setToBtChipQueryAvrcpStatus(void)
{
	setToBtChipAtCmd((char*)"MO", 2);
}

void CBtBC6Adapter::setToBtChipConnectAvDeviceRecently(void)
{
	setToBtChipAtCmd((char*)"MI", 2);
}

void CBtBC6Adapter::setToBtChipDisConnectA2DP(void)
{
	setToBtChipAtCmd((char*)"DA", 2);
}

void CBtBC6Adapter::setToBtChipFastForward(int index)//1 work, 0 stop
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "MR%d", index);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipRewind(int index)//1 work, 0 stop
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "MT%d", index);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipQueryA2dpInfo(void)//<歌曲名><歌手><时间><列号><总歌曲数量>
{
	setToBtChipAtCmd((char*)"MK", 2);
}
void CBtBC6Adapter::setToBtChipA2dpMusicMute(void)
{
	setToBtChipAtCmd((char*)"VA", 2);
}
void CBtBC6Adapter::setToBtChipA2dpMusicUnmute(void)
{
	setToBtChipAtCmd((char*)"VB", 2);
}
//phone book, call record
void CBtBC6Adapter::setToBtChipSyncPhoneBookSIM(void)
{
	setToBtChipAtCmd((char*)"PA", 2);
}

void CBtBC6Adapter::setToBtChipSyncPhoneBookMobilePhone(void)
{
	setToBtChipAtCmd((char*)"PB", 2);
}

void CBtBC6Adapter::setToBtChipSyncAllCallLog(void)//同步手机内存中的已拨电话号码/本地保存
{
	LOGD("[%s]",__FUNCTION__);
	setToBtChipAtCmd((char*)"PX", 2);
}

void CBtBC6Adapter::setToBtChipSyncHaveDialRecord(void)//同步手机内存中的已拨电话号码/本地保存
{
	LOGD("[%s]",__FUNCTION__);
	setToBtChipAtCmd((char*)"PH", 2);
}

void CBtBC6Adapter::setToBtChipSyncHaveAnswerCallIn(void)//同步手机内存中的已接电话号码/本地保存
{
	LOGD("[%s]",__FUNCTION__);
	setToBtChipAtCmd((char*)"PI", 2);
}

void CBtBC6Adapter::setToBtChipSyncMissAnswerCallIn(void)//同步手机内存中的未接电话号码/本地保存
{
	LOGD("[%s]",__FUNCTION__);
	setToBtChipAtCmd((char*)"PJ", 2);
}

void CBtBC6Adapter::setToBtChipLoadNextNItem(int n)
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "PC%d", n);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipLoadPreNItem(int n)
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "PD%d", n);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipLoadAllItem(void)
{
	setToBtChipAtCmd((char*)"PX", 2);
}

void CBtBC6Adapter::setToBtChipLoadStop(void)
{
	setToBtChipAtCmd((char*)"PS", 2);
}

void CBtBC6Adapter::setToBtChipAgreeOppRequestAndStartLoad(void)
{
	setToBtChipAtCmd((char*)"PE", 2);
}

void CBtBC6Adapter::setToBtChipRefuseOppRequest(void)
{
	setToBtChipAtCmd((char*)"PG", 2);
}

void CBtBC6Adapter::setToBtChipLoadPause(void)
{
	setToBtChipAtCmd((char*)"PO", 2);
}

void CBtBC6Adapter::setToBtChipLoadResume(void)
{
	setToBtChipAtCmd((char*)"PQ", 2);
}

//1.7 SPP 蓝牙虚拟串口指令
void CBtBC6Adapter::setToBtChipConnectSPP(char *p, int len)
{
	char szCmd[64] = {0};
	int s = sizeof(szCmd);

	memcpy(szCmd, "SP", 2);
	memcpy(szCmd + 2, p, len);

	setToBtChipAtCmd(szCmd, len + 2);
}

void CBtBC6Adapter::setToBtChipDisconnectSPP(void)
{
	setToBtChipAtCmd((char*)"SH", 2);
}

void CBtBC6Adapter::setToBtChipDisconnectSPP(char *p, int len)
{
	char szCmd[64] = {0};
	int s = sizeof(szCmd);

	memcpy(szCmd, "SH", 2);
	memcpy(szCmd + 2, p, len);

	setToBtChipAtCmd(szCmd, len + 2);
}

void CBtBC6Adapter::setToBtChipQuerySppStatus(void)
{
	setToBtChipAtCmd((char*)"SY", 2);
}

void CBtBC6Adapter::setToBtChipQuerySppStatus(char *p, int len)
{
	char szCmd[64] = {0};
	int s = sizeof(szCmd);

	memcpy(szCmd, "SY", 2);
	memcpy(szCmd + 2, p, len);

	setToBtChipAtCmd(szCmd, len + 2);
}

//1.8 MAP 短信管理指令
//1.9 HID 触摸操控指令
//1.10 OPP/FTP 文件传输指令
//1.11 PAN 网络连接指令
//1.12 SDP 蓝牙搜索指令
void CBtBC6Adapter::setToBtChipStartSearchBtDevice(void)
{
	//setToBtChipAtCmd((char*)"SA", 2);
	setToBtChipAtCmd((char*)"SD", 2);
}

void CBtBC6Adapter::setToBtChipStopSearchBtDevice(void)
{
	//setToBtChipAtCmd((char*)"SB", 2);
	setToBtChipAtCmd((char*)"ST", 2);
}

/*void CBtBC6Adapter::setToBtChipConnectSearchDevice(char *p, int len)
{
	char szCmd[64] = {0};
	int s = sizeof(szCmd);

	memcpy(szCmd, "SC", 2);
	memcpy(szCmd + 2, p, len);

	setToBtChipAtCmd(szCmd, len + 2);
}
*/
//1.13 其它功能操作指令
void CBtBC6Adapter::setToBtChipResetBtChip(void)
{
	setToBtChipAtCmd((char*)"CZ", 2);
}

void CBtBC6Adapter::setToBtChipEraseDevicePairRecord(int index)//清除指定设备配对记录
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "CV%d", index);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipEraseDevicePairRecord(void)//清除所有配对记录
{
	LOGD("setToBtChipEraseDevicePairRecord");//TEST
	setToBtChipAtCmd((char*)"CV", 2);
}

void CBtBC6Adapter::setToBtChipQueryBtChipVersion(void)
{
       LOGD("[%s] MY",__FUNCTION__);
	setToBtChipAtCmd((char*)"MY", 2);
}

void CBtBC6Adapter::setToBtChipModifyBtChipName(char *p, int len)
{
	char szCmd[FLY_BT_DEVICE_NAME_MAX_LEN] = {0};
	int s = sizeof(szCmd);

	memcpy(szCmd, "MM", 2);

	if(len > (FLY_BT_DEVICE_NAME_MAX_LEN - 2))
		len = FLY_BT_DEVICE_NAME_MAX_LEN - 2;
	
	memcpy(szCmd + 2, p, len);

	setToBtChipAtCmd(szCmd, len + 2);
}

void CBtBC6Adapter::setToBtChipQueryBtChipName(void)
{
	setToBtChipAtCmd((char*)"MM", 2);
}

void CBtBC6Adapter::setToBtChipModifyBtChipPairCode(char *p, int len)
{
       LOGD("[%s] ,  PairCode: %s",__FUNCTION__,p);
	char szCmd[64] = {0};
	int s = sizeof(szCmd);

	memcpy(szCmd,"MN", 2);
	memcpy(szCmd + 2, p, len);

	setToBtChipAtCmd(szCmd, len + 2);
}

void CBtBC6Adapter::setToBtChipQueryBtChipPairCode(void)
{
	setToBtChipAtCmd((char*)"MN", 2);
}

void CBtBC6Adapter::setToBtChipQueryLocalBtMacAddr(void)
{
	setToBtChipAtCmd((char*)"DF", 2);
}

void CBtBC6Adapter::setToBtChipQueryHavePairDevices(void)
{
	setToBtChipAtCmd((char*)"MX", 2);
}

void CBtBC6Adapter::setToBtChipQueryAutoPickupAndAutoReconnect(void)
{
	setToBtChipAtCmd((char*)"MF", 2);
}

void CBtBC6Adapter::setToBtChipSetAutoConnect(bool bState)
{
	if (!bState)
	{
		setToBtChipCloseAutoConnectAfterPowerOn();
	}
	else
	{
		setToBtChipOpenAutoConnectAfterPowerOn();
	}
}

void CBtBC6Adapter::setToBtChipOpenAutoConnectAfterPowerOn(void)
{
	setToBtChipAtCmd((char*)"MG", 2);
}

void CBtBC6Adapter::setToBtChipCloseAutoConnectAfterPowerOn(void)
{
	setToBtChipAtCmd((char*)"MH", 2);
}

void CBtBC6Adapter::setToBtChipOpenAutoPickup(void)
{
	setToBtChipAtCmd((char*)"MP", 2);
}

void CBtBC6Adapter::setToBtChipCloseAutoPickup(void)
{
	setToBtChipAtCmd((char*)"MQ", 2);
}

void CBtBC6Adapter::setToBtChipOpenBt(void)
{
	setToBtChipAtCmd((char*)"P1", 2);
}

void CBtBC6Adapter::setToBtChipCloseBt(void)
{
	setToBtChipAtCmd((char*)"P0", 2);
}

void CBtBC6Adapter::setToBtChipQueryCurConnectBtDeviceMacAddr(void)
{
	setToBtChipAtCmd((char*)"QA", 2);
}

void CBtBC6Adapter::setToBtChipQueryCurConnectBtDeviceName(void)
{
	setToBtChipAtCmd((char*)"QB", 2);
}

void CBtBC6Adapter::setToBtChipQuerySpkAndMicVolume(void)
{
	setToBtChipAtCmd((char*)"QC", 2);
}

void CBtBC6Adapter::setToBtChipQueryBatteryPowerAndSignalQuantity(void)
{
	setToBtChipAtCmd((char*)"QD", 2);
}

void CBtBC6Adapter::setToBtChipMicGain(char p)
{
	char szCmd[5] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "GN%x", p);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipQueryMicGainValue(void)
{
	setToBtChipAtCmd((char*)"GN", 2);
}

int CBtBC6Adapter::findCharIndex(unsigned char *p, int len, unsigned char d)
{
	int i = 0;

	for (i = 0; i < len; i++)
	{
		if (p[i] == d)
		{
			return i;
		}
	}

	return -1;
		
}

int CBtBC6Adapter::Inside_FindIndexFromStr(const u8 *pSrc, int nSrcLen, u8 cLetter, int nStart){
	int i;
	for (i = nStart; i < nSrcLen; i++){
		if (cLetter == pSrc[i]){
			return i;
		}
	}
	return -1;
}



//BC8
void CBtBC6Adapter::setToBtChipSetCurUsingWhichDevice(int index)
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "A0%d", index);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipGetMusicBrowsingList(int nStart,int nEnd)
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "M1%x,%x", nStart,nEnd);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipChangeMusicWhichListPath(int nLevel,char *msb,char *lsb)
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "M2%x,%s,%s", nLevel,msb,lsb);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipSetWhichTheSong(char *msb,char *lsb)
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "M4%s,%s",msb,lsb);

	setToBtChipAtCmd(szCmd, len);
}

void CBtBC6Adapter::setToBtChipIsSupportMusicBrowsing(void)
{
	setToBtChipAtCmd((char*)"Qa", 2);
}

void CBtBC6Adapter::setToBtChipConnectedDeviceCounts(void)
{
	setToBtChipAtCmd((char*)"Qs", 2);
}

void CBtBC6Adapter::setToBtChipVoiceSwitchToMicOpenBC8(void)
{
	setToBtChipAtCmd((char*)"CM", 2);
}

void CBtBC6Adapter::setToBtChipEraseDevicePairRecord_BC8(void)//清除所有配对记录
{
	setToBtChipAtCmd((char*)"CV0", 3);
}

void CBtBC6Adapter::setToBtChipStartPairMode_BC8(void)
{
	setToBtChipAtCmd((char*)"AU1", 3);
}

void CBtBC6Adapter::setToBtChipEndPairMode_BC8(void)
{
	setToBtChipAtCmd((char*)"AU0", 3);
}

void CBtBC6Adapter::setToBtChipAvConnect_BC8(void)
{
	setToBtChipAtCmd((char*)"AC", 2);
}

void CBtBC6Adapter::setToBtChipAvDisConnect_BC8(void)
{
	setToBtChipAtCmd((char*)"AD", 2);
}

void CBtBC6Adapter::TestsetToBtChipSetCurUsingWhichDevice(char *p, int len)
{
	char szCmd[64] = {0};
	int len1 = snprintf(szCmd, sizeof(szCmd), "A0%s", p);

	setToBtChipAtCmd(szCmd, len + 2);
}

void CBtBC6Adapter::setWhetherTheBluetoothDeivceSupportsDualConnection(int index)
{
	char szCmd[16] = {0};
	int len = snprintf(szCmd, sizeof(szCmd), "EM%d", index);

	setToBtChipAtCmd(szCmd, len);

}

void CBtBC6Adapter::setSyncCallRecord(void)
{	
	setToBtChipSyncHaveAnswerCallIn();
}

void CBtBC6Adapter::setClearSyncCallRecord(void)
{	if(m_pBtParam->m_listHistoryCall.size() <= 0)
	{
		m_pBtParam->m_listHistoryCall.clear();
		m_pBtParam->m_listHistoryCall_Miss.clear();
		m_pBtParam->m_listHistoryCall_Dialed.clear();
		m_pBtParam->m_listHistoryCall_Riceived.clear();
		m_pBtApp->m_pCallRecordPages->showLoadingCallLogTips(0);
	}
}
