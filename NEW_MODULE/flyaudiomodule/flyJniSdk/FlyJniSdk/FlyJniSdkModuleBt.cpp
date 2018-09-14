#include "FlyJniSdkModuleBt.h"

bool sendConnectTag = false;
bool sendPhoneCallTag = false;
bool PhoneBookLoadTag = false;

CFlyJniSdkModuleBt::CFlyJniSdkModuleBt(void)
{
}

CFlyJniSdkModuleBt::~CFlyJniSdkModuleBt(void)
{
}

void CFlyJniSdkModuleBt::getBtMessage(u8 *p, u8 len)
{
	LOGD("[%s] cmd:%x", __FUNCTION__,p[0]);
	switch(p[0])
	{
        case 0x00:
			   onBlueToothPowerStatus( p[1]);
			   break;
		 case 0x01:
			   onBlueToothConnectStatus(p[1]);
			   if(sendConnectTag)
			  	 sendToAppBtConnectStatus(p[1]); //new protocol
			   break;
		 case 0x02:
		 	   onBlueToothPairStatus(p[1]);
			   break;
		 case 0x03:
			   onBlueToothPhoneStatus(p[1]);
			    if(sendPhoneCallTag)
			  	 sendToAppBtPhoneCallStatus(p[1]);//new protocol
			   break;   
	     case 0x07:
			   onBlueToothMusicTrank(&p[1],len-1);
			   break;
	     case 0x08:
			   onBlueToothMusicArtist(&p[1],len-1);
			   break;
	     case 0x09:
			   onBlueToothMusicAlbum(&p[1],len-1);
			   break;
		 case 0x0a:
		 	   onBlueToothMusicStatus(p[1]);
		 	   break;
		 case 0x0b:
		 	   onBlueToothSupportMusic(p[1]);
		 	   break;
		 case 0xE3:
			seekFlyJniSdkTokeySdk(p[1]);
		 break;
		 case 0xE4:
			tuneFlyJniSdkTokeySdk(p[1]);
		 break;
		 case 0xE5:
			steeringWheelBtKeyFlyJniSdkTokeySdk(p[1]);
		 break;
		 case 0xFF://MTK_BtApp
		 	getOtherModule_aboutBt_ToBtApp(&p[1],len-1);
		 break;
		 	 case 0x0d:
		 	onBlueToothPhoneBookInfo(&p[1],len - 1);
		 	break;
		case 0x0e:
			onBlueToothPhoneBookEndTag(p[1]);
			break;
		case 0x10:
			sendToAppPhoneBookLoadState(p[1]);
			break;
		case 0x11:
			sendToAppPhoneBookInfo(&p[1],len - 1);
	}
}

void CFlyJniSdkModuleBt::getAppCtrlMessage(u8 *p, u8 len)
{
	LOGD("[%s] Module_bt cmd:%x", __FUNCTION__,p[0]);
	switch(p[0])
	{
	case 0x00:
		
		break;
	case 0x01:
		
		break;
	case 0x02:
		
		break;

	case 0x03:
		
		break;
	case 0x04:
		
		break;
	case 0x05:
		{
			if(p[1] == 0 ||p[1] == 1)
				setToBlueToothHundUpOrAnswer(p[1]); 
		}
		break;
	case 0x06:
	{
			switch(p[1])
			{
			case 0x00:
				setToBlueToothPlayMusic();
				break;
			case 0x01:
				setToBlueToothPauseMusic();
				break;
			case 0x02:
				setToBlueToothStopMusic();
				break;
			case 0x03:
				setToBlueToothPreMusic();
				break;
			case 0x04:
				setToBlueToothNextMusic();
				break;
			}
		
	}
	break;
	case 0x10:
		setToBlueToothFromQujiaDial(&p[1],len-1);
	break;
	case 0x11:
		thirdPartyJumpSetPage();
		break;
	case 0x12:
		setToBlueToothFromHideBtPage(p[1]);
		break;
	case 0xFF://MTK_APP
		analysMtkAppBtstatus(p + 1, len - 1);
		break;
	}
}


void CFlyJniSdkModuleBt::onBlueToothConnectStatus(u8 p)
{
	LOGD("[%s] p:%x", __FUNCTION__,p);
	u8 szMsg[2] = {0x01, p};
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModuleBt::onBlueToothPairStatus(u8 p)
{   
	LOGD("[%s] p:%d", __FUNCTION__,p);
	u8 szMsg[2] = {0x02, p};
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModuleBt::onBlueToothPowerStatus(u8 p)
{
	LOGD("[%s] p:%x", __FUNCTION__,p);
	u8 szMsg[2] = {0x03, p};
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModuleBt::onBlueToothPhoneStatus(u8 p)
{
	LOGD("[%s] p:%x", __FUNCTION__,p);
	u8 szMsg[2] = {0x04, p};
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, sizeof(szMsg));
}


void CFlyJniSdkModuleBt::onBlueToothMusicStatus(u8 p)
{
	LOGD("[%s] p:%x", __FUNCTION__,p);
    u8 szMsg[2] = {0x05, p};
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModuleBt::onBlueToothCallingName(u8 *p, int len)
{
	LOGD("[%s] p:%s", __FUNCTION__,p);
    static u8 szMsg[256] = {0x00};
	szMsg[0] = 0x06;
	memcpy(szMsg + 1, p, len);
	szMsg[len+1]=0;
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, len + 2);
}
void CFlyJniSdkModuleBt::onBlueToothCallingNumber(u8 *p, int len)
{
	LOGD("[%s] p:%s", __FUNCTION__,p);
    static u8 szMsg[256] = {0x00};
	szMsg[0] = 0x07;
	memcpy(szMsg + 1, p, len);
	szMsg[len+1]=0;
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, len + 2);
}


//moupeng 2015/7/28
void CFlyJniSdkModuleBt::onBlueToothMusicTrank(u8 *p, int len)
{
	LOGD("[%s] p:%s", __FUNCTION__,p);
    static u8 szMsg[256] = {0x00};
	szMsg[0] = 0x08;
	szMsg[1]=0x01;
	memcpy(szMsg + 2, p, len);
	szMsg[len+2]=0;
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, len + 2);
}
void CFlyJniSdkModuleBt::onBlueToothMusicArtist(u8 *p, int len)
{
	LOGD("[%s] p:%s", __FUNCTION__,p);
    static u8 szMsg[256] = {0x00};
	szMsg[0] = 0x08;
	szMsg[1]=0x02;
	memcpy(szMsg + 2, p, len);
	szMsg[len+2]=0;
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, len + 2);
}

void CFlyJniSdkModuleBt::onBlueToothMusicAlbum(u8 *p, int len)
{
	LOGD("[%s] p:%s", __FUNCTION__,p);
    static u8 szMsg[256] = {0x00};
	szMsg[0] = 0x08;
	szMsg[1]=0x03;
	memcpy(szMsg + 2, p, len);
	szMsg[len+2]=0;
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, len + 2);
}

void CFlyJniSdkModuleBt::onBlueToothCallingMicState(u8 p)
{
	LOGD("[%s] p:%x", __FUNCTION__,p);
    u8 szMsg[2] = {0x09, p};
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, sizeof(szMsg));
}


void CFlyJniSdkModuleBt::onBlueToothSupportMusic(u8 p)
{
	LOGD("[%s] p:%x", __FUNCTION__,p);
    u8 szMsg[2] = {0x10, p};
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, sizeof(szMsg));
}





//控制项
void CFlyJniSdkModuleBt::setToBlueToothPowerOn(u8 p)					//调节蓝牙电源
{

}

void CFlyJniSdkModuleBt::setToBlueToothReceivePhoneCall()			//接听电话
{

}

void CFlyJniSdkModuleBt::setToBlueToothRejectPhoneCall()			//拒听电话
{

}

void CFlyJniSdkModuleBt::setToBlueToothPlayMusic()
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[1] = {0};
	buf[0] = 0x00;
	
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,1);
}

void CFlyJniSdkModuleBt::setToBlueToothPauseMusic()
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[1] = {0};
	buf[0] = 0x01;
	
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,1);
}

void CFlyJniSdkModuleBt::setToBlueToothStopMusic()
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[1] = {0};
	buf[0] = 0x02;

    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,1);
}

void CFlyJniSdkModuleBt::setToBlueToothPreMusic()
{
	LOGD("[%s]",__FUNCTION__);
	u8 buf[1] = {0};
	buf[0] = 0x03;

    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,1);
}

void CFlyJniSdkModuleBt::setToBlueToothNextMusic()
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[1] = {0};
	buf[0] = 0x04;
	
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,1);
}

void CFlyJniSdkModuleBt::setToBlueToothFromQujiaDial(u8 *p,int len)
{
    LOGD("[%s]  P:%s len:%x",__FUNCTION__,p,len);
	if(len >128)
		len = 128;
	u8 buf[129] = {0};
	buf[0] = 0x05;
	memcpy(buf+1,p,len);
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,len+1);
}

void CFlyJniSdkModuleBt::setToBlueToothHundUpOrAnswer(u8 param)
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[2] = {0};
	buf[0] = 0x06;
	buf[1] = param;
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,2);
}

void CFlyJniSdkModuleBt::thirdPartyJumpSetPage(void)
{
	LOGD("[%s]",__FUNCTION__);
	u8 buf[1] = {0};
	buf[0] = 0x07;
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,1);
}

void CFlyJniSdkModuleBt::setToBlueToothFromHideBtPage(u8 p)
{
    LOGD("[%s]  P:%x",__FUNCTION__,p);
	u8 buf[2] = {0};
	buf[0] = 0x08;
	buf[1] = p;
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,2);
}




/////////////////////////////////////////////////////////////////////////////////////////////////
//add new agreement
void CFlyJniSdkModuleBt::getOtherModule_aboutBt_ToBtApp(U8 *p,u8 nLen)
{
	int nBufLen = nLen + 1;
	u8 *pBuf = (u8*)malloc(nBufLen);

	if(pBuf == NULL)
		return;

	pBuf[0] = 0xff;
	memcpy(pBuf + 1,p,nLen);
	setToFlyJniSdkService(MODULE_ID_BT, pBuf, nBufLen);
	free(pBuf);
	pBuf = NULL;
}

//new add set control project
void CFlyJniSdkModuleBt::analysMtkAppBtstatus(u8 *p,u8 len)
{
	setToMTK_BlueToothToOtherModule_bt(p,len);
}

void CFlyJniSdkModuleBt::setToMTK_BlueToothToOtherModule_bt(u8 *p,u8 nLen)
{
	int nBufLen = nLen + 1;
	u8 *pBuf = (u8*)malloc(nBufLen);

	if(pBuf == NULL)
		return;

	pBuf[0] = 0xff;
	memcpy(pBuf + 1,p,nLen);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,pBuf,nBufLen);
	free(pBuf);
	pBuf = NULL;
}

void CFlyJniSdkModuleBt::mtkThirdPartyJumpSetPage(void)
{
	u8 pBuf[2] = {0};
	pBuf[0] = 0xff;
	pBuf[1] = 0x04;
	setToFlyJniSdkService(MODULE_ID_BT, pBuf, 2);
}

void CFlyJniSdkModuleBt::setToBlueToothFromMtkDial(u8 *p,int len)
{
    LOGD("[%s]  P:%s len:%x",__FUNCTION__,p,len);
	if(len >128)
		len = 128;
	u8 buf[129] = {0};
	buf[0] = 0xff;
	buf[1] = 0x16;
	memcpy(buf+2,p,len);
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,len+2);
}
///////////////////////////////////////////////////////////////////////////


void CFlyJniSdkModuleBt::seekFlyJniSdkTokeySdk(u8 p)
{
	u8 buf[2];
	buf[0] = 0x01;
	buf[1] = p;
	setToFlyJniSdkService(MODULE_ID_KEY, buf, 2);
}

void CFlyJniSdkModuleBt::tuneFlyJniSdkTokeySdk(u8 p)
{
	u8 buf[2];
	buf[0] = 0x02;
	buf[1] = p;
	setToFlyJniSdkService(MODULE_ID_KEY, buf, 2);
}

void CFlyJniSdkModuleBt::steeringWheelBtKeyFlyJniSdkTokeySdk(u8 p)
{
	u8 buf[2];
	buf[0] = 0x03;
	buf[1] = p;
	setToFlyJniSdkService(MODULE_ID_KEY, buf, 2);
}



//add phone book
void CFlyJniSdkModuleBt::onBlueToothPhoneBookInfo(u8 *p,int len)
{
	u8 szMsg[256*3];
	if(len >= 256 * 3)
		len = 256*3 -1;
    memset(szMsg,0,sizeof(szMsg));
	szMsg[0] = 0x20;
	memcpy(szMsg + 1,p,len);
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, len + 1);
	outPutLog(__FUNCTION__, "szMsg", szMsg, (len +1));
}

void CFlyJniSdkModuleBt::onBlueToothPhoneBookEndTag(u8 p)
{
	LOGD("[%s] p:%x", __FUNCTION__,p);
	u8 szMsg[2];
	szMsg[0] = 0x21;
	szMsg[1] = p;
	setToFlyJniSdkService(MODULE_ID_BT, szMsg, 2);
}

/******************************new protocal*******************************************/

void CFlyJniSdkModuleBt::analyseAppMessageType(u8 *p, u8 len)
{
	LOGD("[%s]	p[0]:%x --p[1]:%x len:%x",__FUNCTION__,p[0],p[1],len);
	switch(p[0])
	{
		case RESPONE_CHANGE_STATE:
			analyseReturnStatusMassage(p+1, len - 1);
			break;
		case CONTROL_MESSAGE:
			analyseControlBtOperationMassage(p+1, len - 1);
			break;
		default:break;
	}
}

void CFlyJniSdkModuleBt::analyseReturnStatusMassage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:		
			analyseSdkBtBasicInfo(p+1, len - 1);
			break;
		case 0x02:	//phone book Info	
			analyseSdkBtPhoneBookInfo(p+1, len - 1);
			break;
		case 0x03:
			setToBtGetBtSongInfo(p[1]);
			break;
		case 0x04:
			setToBtGetBtName(p[1]);
			break;
		case 0x05:
			setToBtGetBtMusicStatus(p[1]);
			break;
		case 0x06:
            setToBtGetBtRecetveSound(p[1]);
            break;
        case 0x07:
            setToBtGetBtMicStatus(p[1]);
            break;

		default:break;
	}
}
void CFlyJniSdkModuleBt::analyseControlBtOperationMassage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:
			setToBlueToothFromDial(p+1,len - 1);
			break;
		case 0x02:
			{
				if(p[1] == 0x01)
					setToBtSetBtJumpToBtMainPage();
			}
			break;
		case 0x03:
			{
				if(p[1] == 0x01|| p[1] == 0x00)
					setToBtSetBtAccONorOFF(p[1]);
			}
			break;
		case 0x04:
			{
				if(p[1] == 0x01){
					setToBtSetBtJumpToBtMusicPage(0x01);
				}
				else if(p[1] == 0x00){
					setToBtSetBtJumpToBtMusicPage(0x00);
				}
			}
			break;
		case 0x05:
			{
				setToBtSetBtMusicPlay(p[1]);
			}
		case 0x07:
			{
				if(p[1] == 0x01 ||p[1] == 0x00)
					setToBtSetBtHangUp(p[1]);
			}
			break;
		case 0x08:
			{
				setToBlueToothFromDialAndHideBtPage(p+1,len - 1);
			}
			break;
		case 0x09:
			{
				if(p[1] == 0x01)
					setToBtSetBtJumpToBtDevicePage();
			}
		break;
		case 0x0a:
			setToBtSetBtPhoneCallStatus(p[1]);
			break;
		default:break;
	}
}

void CFlyJniSdkModuleBt::analyseSdkBtBasicInfo(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:		//bt connect status
			{
				//sendConnectTag = true; 
				setToBtGetBtConnectStatus();
			}
			break;
		case 0x02:		//bt phone call status
			{
				//sendPhoneCallTag = true;
				setToBtGetBtPhoneCallStatus();
			}
			break;
		case 0x00:
				setToBtGetBtSwitchStatus();
			break;
		default:break;
	}
}

void CFlyJniSdkModuleBt::analyseSdkBtPhoneBookInfo(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:
			setToBtGetBtPhoneBookInfo();
			break;
		default:break;
	}
}

/*******************************BtToApp	Function*************************************/
void CFlyJniSdkModuleBt::sendToAppBtConnectStatus(u8 p)
{
	LOGD("[%s] p:%x", __FUNCTION__,p);
	u8 szMsg[4] = {0x00,0x01,0x01, p};
	sendToFlyJniSdkService(MODULE_SDK_BT, szMsg, 4);
}

void CFlyJniSdkModuleBt::sendToAppBtPhoneCallStatus(u8 p)
{
	LOGD("[%s] p:%x", __FUNCTION__,p);
	u8 szMsg[4] = {0x00, 0x01,0x02,p};
	sendToFlyJniSdkService(MODULE_SDK_BT, szMsg, 4);
}

void CFlyJniSdkModuleBt::sendToAppPhoneBookLoadState(u8 p)
{
	LOGD("[%s] p:%x", __FUNCTION__,p);
	u8 szMsg[4] = {0x00, 0x02,0x02,p};
	sendToFlyJniSdkService(MODULE_SDK_BT, szMsg, 4);
}

void CFlyJniSdkModuleBt::sendToAppPhoneBookInfo(u8 *p,int len)
{
	u8 szMsg[256*3];
	if(len >= 256 * 3)
		len = 256*3 -1;
    	memset(szMsg,0,sizeof(szMsg));
	szMsg[0] = 0x00;
	szMsg[1] = 0x02;
	szMsg[2] = 0x01;
	memcpy(szMsg + 3,p,len);
	sendToFlyJniSdkService(MODULE_SDK_BT, szMsg, len + 3);
	outPutLog(__FUNCTION__, "szMsg", szMsg, (len +3));
}
/**************************************end********************************************/
/*********************************getBtStatus*******************************************/
void CFlyJniSdkModuleBt::setToBtGetBtSwitchStatus()
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x00;
	buf[2] = 0x00;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,3);
}
void CFlyJniSdkModuleBt::setToBtGetBtConnectStatus()
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x00;
	buf[2] = 0x01;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,3);
}

void CFlyJniSdkModuleBt::setToBtGetBtPhoneCallStatus()
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x00;
	buf[2] = 0x02;
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,3);
}

void CFlyJniSdkModuleBt::setToBtGetBtPhoneBookInfo()
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x00;
	buf[2] = 0x03;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,3);
}

void CFlyJniSdkModuleBt::setToBtGetBtSongInfo(u8 param)
{
	if(param != 0x01)
		return;
    	LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x00;
	buf[2] = 0x04;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,3);
}

void CFlyJniSdkModuleBt::setToBtGetBtName(u8 param)
{
	if(param != 0x01)
		return;
    	LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x00;
	buf[2] = 0x05;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,3);
}

void CFlyJniSdkModuleBt::setToBtGetBtMusicStatus(u8 param)
{
	if(param != 0x01)
		return;
    	LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x00;
	buf[2] = 0x06;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,3);
}
void CFlyJniSdkModuleBt::setToBtGetBtRecetveSound(u8 param)
{
       if(param != 0x01)
               return;
       u8 buf[3] = {0};
       buf[0] = 0xfe;
       buf[1] = 0x00;
       buf[2] = 0x07;
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,3);
}
void CFlyJniSdkModuleBt::setToBtGetBtMicStatus(u8 param)
{
       if(param != 0x01)
               return;
       u8 buf[3] = {0};
       buf[0] = 0xfe;
       buf[1] = 0x00;
       buf[2] = 0x08;
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,3);
}

/**********************************************end******************************************************/

/*********************************setBt-Perform the operation Function*****************************************/
void CFlyJniSdkModuleBt::setToBtSetBtJumpToBtMainPage()
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x01;
	buf[2] = 0x01;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,3);
}
void CFlyJniSdkModuleBt::setToBlueToothFromDial(u8 *p,int len)
{
    LOGD("[%s]  P:%s len:%x",__FUNCTION__,p,len);
	if(len >128)
		len = 128;
	u8 buf[129] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x01;
	buf[2] = 0x02;
	memcpy(buf+3,p,len);
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,len+3);
}

void CFlyJniSdkModuleBt::setToBtSetBtAccONorOFF(u8 p)
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x01;
	buf[2] = 0x03;
	buf[3] = p;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,4);
}

void CFlyJniSdkModuleBt::setToBtSetBtJumpToBtMusicPage(u8 p)
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x01;
	buf[2] = 0x04;
	buf[3] = p;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,4);
}

void CFlyJniSdkModuleBt::setToBtSetBtHangUp(u8 p)
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x01;
	buf[2] = 0x07;
	buf[3] = p;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,4);
}

void CFlyJniSdkModuleBt::setToBlueToothFromDialAndHideBtPage(u8 *p,int len)
{
    LOGD("[%s]  P:%s len:%x",__FUNCTION__,p,len);
	if(len >128)
		len = 128;
	u8 buf[129] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x01;
	buf[2] = 0x08;
	memcpy(buf+3,p,len);
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,len+3);
}
void CFlyJniSdkModuleBt::setToBtSetBtJumpToBtDevicePage()
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[3] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x01;
	buf[2] = 0x09;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,3);
}

void CFlyJniSdkModuleBt::setToBtSetBtMusicPlay(u8 param)
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[4] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x01;
	buf[2] = 0x0a;
	buf[3] = param;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,4);
}

void CFlyJniSdkModuleBt::setToBtSetBtPhoneCallStatus(u8 param)
{
    LOGD("[%s]",__FUNCTION__);
	u8 buf[4] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x01;
	buf[2] = 0x0b;
	buf[3] = param;
    	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_BT,buf,4);
}

/***********************************end*********************************************/
