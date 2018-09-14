#include <stdio.h>
#include <stdlib.h>
#include <param.h>
#include "pageID.h"
#include "global.h"
#include "otherModuleResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "timer_interface.h"
#include "appRequestCommand.h"

#include "halRequestFunction.h"
#include "moduleParamRequest.h"


int vol_flag = 0;
int drop_flag=0;
int LOWBETTERY_DISPLAY_TIME = 15000;  //  jing 2013-8-12 delimit low bettery display time (ms)
int LOWBETTERY_CLOSE_TIME = 3000;  //  jing 2013-8-12 delimit low bettery close time (ms)
const int LOWBETTERY_STATE = 105;   // jing 2013-11-13 set low bettery state Value
const int LOWBETTERY_MIN = 57;		// jing 2013-11-28 set min low bettery state value
int BETTERY_VALUE = 105;  //	jing 2013-11-13 set bettery value to save
int timer_set = 30000;  // jing 2013-11-13 set timer time
bool low_bettery_hal_switch = false;   //  jing 2013-11-13 set to record chick timer,if  = true means timer is setted
/*
 * 逻辑说明：接收到hal发的电压值低于LOWBETTERY_STATE才启动定时器定时timer_set毫秒，在timer_set毫秒后重新检测，
 * 当电压值还是低于LOWBETTERY_STATE时才通知UI显示下拉osd。并且设定时器LOWBETTERY_DISPLAY_TIME毫秒显示，
 * LOWBETTERY_DISPLAY_TIME毫秒隐藏。在hal发电压值上来时，开定时器，设low_bettery_hal_switch为ture，避免在timer_set时间
 * 内重新发电压值导致重新设定时器而永远未到时间。在电压值从高变低时，low_bettery_hal_switch设为false并关闭所有定时器
 * 且取消osd显示。
 * */


void OsdModule_OSD_CtrlDisplay(u8 *param, u8 len)
{

	u8 nLen = len-2;
	u8 *pBuf = (u8*)malloc(sizeof(u8)*(len+1));
	memset(pBuf,0,len+1);
	memcpy(pBuf,param,len);
	pBuf[len] = nLen;
	setOsdInfoControl(pBuf,len+1);
	free(pBuf); 
}

void anyModuleToOsdModue_Dispatch_Msg(u8 *param, u8 len)
{
	u8 bIsInBackCar = 0;
	u8 bIsInBackCarLen = 0;
	u16 CurPageID = 0;
	u8 CurPageIDLen = 0;

	getOtherModuleParam(MODULE_ID_BACK, BACK_CAR_STATE, &bIsInBackCar, &bIsInBackCarLen);
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen);

	LOGD("ToT123_CtrlDropingDownOSD_DisplayingOrHide--bIsInBackCar %d,curPageID=%d",bIsInBackCar,CurPageID);
    if((CurPageID==PAGE_BACK_VIDEO)||bIsInBackCar)return;

	u8 u8_OsdCmd = param[0];
	switch(u8_OsdCmd)
	{
	case 0x02:
		if(param[1] == 0x01)
		{
		    LOGD("vol_flag:%d",vol_flag);
			if(!vol_flag){
				vol_flag = 1;
				drop_flag=0;
				LOGD("Set vol osd Control display ");
				OsdModule_OSD_CtrlDisplay(param, len);
				ToT123_CtrlDropingDownOSD_DisplayingOrHide(param,len);
			}
//			DeleteTimer(OSD_TIMER_VOL_DROP_DOWN_DISPLAY);
//			SetTimer(3000,0, OSD_TIMER_VOL_DROP_DOWN_DISPLAY);
		}
		else{
			LOGD("OsdModule_OSD_CtrlDisplay");
			OsdModule_OSD_CtrlDisplay(param, len);
            
            ToT123_OSD_DisplayingValue(param,len);
            if(!drop_flag){
                drop_flag=1;
                vol_flag = 0;
			    ToT123_CtrlDropingDownOSD_DisplayingOrHide(param,len);
			}
			pLocalParam->uKey_OSDEvent = 1;
		}
		break;
	default:break;
	}
}


void CenterModuleToOsdModule_Dispatch_Msg(u8 *param, u8 len)
{
	u8 u8_Cmd = param[0];
	switch(u8_Cmd)
	{
	case 0x0F:
		if(vol_flag || drop_flag){
			//DeleteTimer(OSD_TIMER_VOL_DROP_DOWN_DISPLAY);
			vol_flag = 0;
			drop_flag = 0;

			pLocalParam->uKey_OSDEvent = 0;
		}
		else{
			pLocalParam->uKey_OSDEvent = 0;
		}
		LOGD("CenterModuleToOsdModule_Dispatch_Msg--vol_flag:0x%x drop_flag%d",vol_flag,drop_flag);
		AboutNewLogic_HideOrDisplayingOSD(0x00);
		setOsdHidden();
		break;
	default:
		break;
	}
	
}

//wen

void backCarToOsdModule_Dispatch_Msg(u8 *param, u8 len)
{
	u8 temBuf = param[0];
	switch(temBuf)
	{
	    case 0x00:
	    LOGD("%d",pLocalParam->osdsettime);
		if(pLocalParam->osdsettime == 1)
		{
			if(vol_flag || drop_flag){
				//DeleteTimer(OSD_TIMER_VOL_DROP_DOWN_DISPLAY);
				vol_flag = 0;
				drop_flag = 0;

				pLocalParam->uKey_OSDEvent = 0;
			}
			else{
				pLocalParam->uKey_OSDEvent = 0;
			}
			AboutNewLogic_HideOrDisplayingOSD(0x00);
			setOsdHidden();
		}
		break;
		case 0x01:   
		    BackcarVideoSetButton_OSDToHal(param[1],param[2]);
		break;
	    case 0x04:
	        BackcarVideoLCDColorSet_OSDToHal(param[1],param[2]);
	    break;
	    case 0x03:
	        BackcarVideoColorValue_OSDToHal(param[1],param[2]);
	    break;
	    case 0x05:
	        BackcarVideoWarningsDisplayingStatus_OSDToHal(param[1]);
	    break;
	}
}

void moduleToOsd_FromSystem_Message(u8 *param, u8 len){
	
	switch(param[0]){
	    case 0xE3://
		   {
				int iLeavePage = param[1]  + (param[2]<<8);
				int iEnterPage = param[3]  + (param[4]<<8);
				int iParam =param[5];
				Get_PageChangeMessage(iLeavePage,iEnterPage,iParam);
			}
			break;
	}
}

void moduleToOsd_FromAudioVideo_Message(u8* param,u8 len)
{
	if(param[0] != 0x02)
		return;
    switch(param[1])
    {
    case 0x1://volume
    	{
    		u8 volume = param[2];
    		SoundValue_OSDToHal(volume);
    	}
    	break;
    }
}

void moduleToOsd_FromMedia_Message(u8 *param, u8 len){
	if(param[0] == 0xEE){
		switch(param[1]){
				case (char)0x10://paly prev or next 
					setOsdBar();
				//	DeleteTimer(OSD_TIMER_VOL_DROP_DOWN_DISPLAY);
				//	SetTimer(3000,0, OSD_TIMER_VOL_DROP_DOWN_DISPLAY);
					break;
				default:
					break;
		}
	}
}

void Handle_SystemMessage()
{
 // SetTimer(3000,0,OSD_TIMER_BARCODE_DISPLAY);
}

// jing 2013-8-12 low bettery osd {
void Handle_Osd_Message(u8 *param, u8 len)
{
	LOGD("jing ------------ Handle_Osd_Message --- param[0] = %x ----- param[1] = %x ---  low_bettery_hal_switch = %d",param[0],param[1],low_bettery_hal_switch);
	BETTERY_VALUE = param[1];  // save hal bettery value
	if( (LOWBETTERY_MIN < BETTERY_VALUE) && (BETTERY_VALUE <= LOWBETTERY_STATE)  )
	{
		if(low_bettery_hal_switch == false)
		{
			LOGD("jing ------------ if  low_bettery_hal_switch == false ");
		//	SetTimer(timer_set,0,OSD_TIMER_LOWBETTERY_CHICK);  // set timer to make sure bettery state is low or not
			low_bettery_hal_switch = true;
		}

	}else if(BETTERY_VALUE > LOWBETTERY_STATE)
	{
		LOGD("jing ------------ else if  BETTERY_VALUE > LOWBETTERY_STATE  ------- BETTERY_VALUE = %d",BETTERY_VALUE);
		low_bettery_hal_switch = false;
//		DeleteTimer(OSD_TIMER_LOWBETTERY_CHICK); // delet chicker's timer
//		DeleteTimer(OSD_TIMER_LOWBETTERY_DISPLAY);  // deleter display osd's timer
//		DeleteTimer(OSD_TIMER_LOWBETTERY_OSD_CLOSE);  //  deleter close osd's timer
	}
}

void Handle_Bettery_Timer_ToChick(void)
{
	LOGD("jing ------------ Handle_Bettery_Timer_ToChick ");
	low_bettery_hal_switch = false;
	if( (LOWBETTERY_MIN < BETTERY_VALUE) && (BETTERY_VALUE <= LOWBETTERY_STATE) )
	{
//		DeleteTimer(OSD_TIMER_LOWBETTERY_CHICK); // delet chicker's timer
//		DeleteTimer(OSD_TIMER_LOWBETTERY_DISPLAY);  // deleter display osd's timer
//		DeleteTimer(OSD_TIMER_LOWBETTERY_OSD_CLOSE);  //  deleter close osd's timer
//		SetTimer(LOWBETTERY_DISPLAY_TIME,0,OSD_TIMER_LOWBETTERY_DISPLAY);  // set timer to display low bettery osd
		sendLowBetterOSD();  // sent message to UI to display low bettery osd
//		SetTimer(LOWBETTERY_CLOSE_TIME,0,OSD_TIMER_LOWBETTERY_OSD_CLOSE);  // set timer (3s later) to close low bettery osd

	}else
	{
//		DeleteTimer(OSD_TIMER_LOWBETTERY_CHICK); // delet chicker's timer
//		DeleteTimer(OSD_TIMER_LOWBETTERY_DISPLAY);  // deleter display osd's timer
//		DeleteTimer(OSD_TIMER_LOWBETTERY_OSD_CLOSE);  //  deleter close osd's timer
	}

}
// jing 2013-8-12 low bettery osd }



//T123_chipLogic

void ToT123_CtrlDropingDownOSD_DisplayingOrHide(u8 *param, u8 len)
{
    if(param[0] != 0x02)
    return;
    
    switch(param[1])
    {
        case 0x01:
        AboutNewLogic_HideOrDisplayingOSD(0x10);/*����*/
        break;
        case 0x39:
        case 0x42:
        AboutNewLogic_HideOrDisplayingOSD(0x11);/*�յ�*/
        break;
        case 0x10:
        AboutNewLogic_HideOrDisplayingOSD(0x12);/*DVD*/
        break;
        case 0x30:
        AboutNewLogic_HideOrDisplayingOSD(0x15);/*BT*/
        break;
        case 0x38:
        AboutNewLogic_HideOrDisplayingOSD(0x16);/*̥ѹ*/
        break;
        case 0x18:
        AboutNewLogic_HideOrDisplayingOSD(0x17);/*RADIO AM*/
        break;
        case 0xEE:
        AboutNewLogic_HideOrDisplayingOSD(0x14);
        break;

    }
}

void ToT123_OSD_DisplayingValue(u8 *param, u8 len)
{
    if(param[0] != 0x02)
    return;
    
    switch(param[1])
    {
        case 0x01:
        break;
        case 0x10:
        DVDplay_titleAndTrack_OSDToHal(&param[2],len-2);
        break;
        case 0x18:
        moduleToOsd_FromRadio_Message(param,len);
        break;
        case 0x30:
        BTcontectStatus_OSDToHal(&param[2]);
        break;
        case 0x38:
        moduleToOsd_FromTPMS_Message(param,len);
        break;
        case 0x39:
        case 0x42:
        moduleToOsd_FromAC_Message(&param[2]);
        break;
        case 0xEE:
        MediaPlay_TrackValue_OSDToHal(&param[2]);
        break;
    }
}

void audiovideoToOsdModule_ViewSwitch_Message(u8 *param, u8 len)
{
    switch(param[0])
    {
        case 0x03:
        ViewChannelSwitchOSDToHal(param[1]);
        break;
        case 0x04:
        {
            if(param[1]==0x00)
            {
                if(vol_flag)
                vol_flag = 0;
                if(drop_flag)
                drop_flag = 0;
            }
            AboutNewLogic_HideOrDisplayingOSD(param[1]);
        }
        break;
    }	
}


void moduleToOsd_FromTPMS_Message(u8 *param, u8 len)
{
    u8 tire = 0;
    u8 status=0xff;
    switch(param[2])
    {
           /* 
            case 0x00:
            tire=1;
            break;
            case 0x01:
            tire=2;
            break;
            case 0x02:
            tire=3;
            break;
            case 0x03:
            tire=4;
            break;*/
            case 0x10:
            tire=1;
            status=1;
            case 0x11:
            tire=2;
            status=1;
            case 0x12:
            tire=3;
            status=1;
            case 0x13:
            tire=4;
            status=1;
            break;
            case 0x20:
            tire=5;
            status=1;
            case 0x21:
            tire=6;
            status=1;
            case 0x22:
            tire=7;
            status=1;
            case 0x23:
            tire=8;
            status=1;
            break;
            case 0x30:
            tire=5;
            status=0;
            case 0x31:
            tire=6;
            status=0;
            case 0x32:
            tire=7;
            status=0;
            case 0x33:
            tire=8;
            status=0;
            break;
    }
    TPMS_TempsAndStatus_OSDToHal(tire,status);

}

void moduleToOsd_FromRadio_Message(u8 *param, u8 len)
{
   u16 value = param[3]+param[4]*256;
   u8 type = 0xFF;
   u8 Unit = 0xFF;
   if(param[2]==0x00)
   {
      type=0x00;
      Unit=0x01;
   }
   else if(param[2]==0x02)
   {
     type=0x01;
     Unit=0x00;
   }

   if(param[2]==0x00 || param[2]==0x02)
    Radio_Channel_Value_OSDToHal(type,value,Unit);
}

void moduleToOsd_FromDVD_Message(u8 *param, u8 len)
{
    switch(param[0])
    {
        case 0x00:
        dvdVideoSetButton_OSDToHal(param[1],param[2]);
        break;
        case 0x01:
        break;
        case 0x03:
        dvdVideoLCDColorSet_OSDToHal(param[1],param[2]);
        break;
        case 0x04:
        dvdVideoColorValue_OSDToHal(param[1],param[2]);
        break;
        case 0x05:
        dvdVideoPlayTimes_OSDToHal(&param[1]);
        break;
    }	
}

void moduleToOsd_FromAUX_Message(u8 *param, u8 len)
{
   switch(param[0])
    {
        case 0x00:
        AuxVideoLCDColorSet_OSDToHal(param[1],param[2]);
        break;
        case 0x01:
        AuxVideoColorValue_OSDToHal(param[1],param[2]);
        break;
        case 0x03:
        AuxVideoSetButton_OSDToHal(param[1],param[2]);
        break;
    }
}

void moduleToOsd_FromTV_Message(u8 *param, u8 len)
{
   switch(param[0])
    {
        case 0x01:
        TVVideoSetButton_OSDToHal(param[1],param[2]);
        break;
        case 0x03:
        TVVideoColorValue_OSDToHal(param[1],param[2]);
        break;
        case 0x04:
        TVVideoLCDColorSet_OSDToHal(param[1],param[2]);
        break;
    }
}

void moduleToOsd_FromDVR_Message(u8 *param, u8 len)
{
   switch(param[0])
    {
        case 0x00:
        dvrVideoSet_OSDToHal(param[1],param[2]);
        break;
        case 0x01:
        dvrVideoSetButton_OSDToHal(param[1],param[2]);
        break;
        case 0x04:
        dvrVideoPlaySet_OSDToHal(param[1],param[2]);
        break;
        case 0x03:
        dvrVideoYMDSet_OSDToHal(param[1],param[2]);
        break;
        case 0x06:
        dvrVideoYMDSet_OSDToHal(param[1],param[2]);
        break;
    }
}

void moduleToOsd_FromAC_Message(u8 *param)
{
    short nLeftTemp = param[0]*256+param[1];
    short nRightTemp = param[2]*256+param[3];
    u8 nUnit=0xFF;
    u8 nSpeed = param[4];
    u8 nACState = param[5];
    if(nLeftTemp==0x00)
    nLeftTemp=0xFFFD;
    if(nRightTemp==0x00)
    nRightTemp==0xFFFD;

    if(nLeftTemp==0x34)
    nLeftTemp=0xFFFE;
    if(nRightTemp==0x34)
    nRightTemp==0xFFFE;

    if(nLeftTemp==0x35)
    nLeftTemp=0xFFFF;
    if(nRightTemp==0x35)
    nRightTemp==0xFFFF;

    if(nUnit==0xFF)
    nUnit=0x00;

    if(nSpeed==1)
    nSpeed=0xFD;
    if(nSpeed==7)
    nSpeed=0xFE;
    if(nSpeed==0)
    nSpeed=0xFF;

    if(nACState==0)
    nACState=0;
    else
    nACState=1;
    
    ACMessage_OSDToHal(nLeftTemp,nRightTemp,nUnit,nSpeed,nACState);
}

void SetTimerOfHideOSD()
{
   KillTimerOfHideOSD();
   int iOsdContent = pLocalParam->m_nCurOSDContent;
   if (OSD_NoDisplay == iOsdContent)
   return;

   if (IsSubTitleOSD(iOsdContent))//���������OSDҳ
   {
	   //m_nTimerSubTitle = SetTimer(NULL,m_nTimerSubTitle,TIMEOUT_HIDE_SUBTITLE,TimerProc);
	   LOGD("set timer subtitle %d",iOsdContent);
	   SetTimer(TIMEOUT_HIDE_SUBTITLE,1, OSD_TIMER_DROP_DOWN_DISPLAY);
   }
   else if (iOsdContent == OSD_BACK)//����ǵ�����Ƶҳ
   {
	   //���ö�ʱ���
       KillTimerOfHideOSD();
   }
   else//����OSDҳ��Ҫ��ʱ���
   {
	   LOGD("set timer osd page display");
       //m_nTimerOSDPage = SetTimer(NULL,m_nTimerOSDPage,TIMEOUT_HIDE_OSDPAGE,TimerProc);
	   SetTimer(TIMEOUT_HIDE_OSDPAGE,1, OSD_TIMER_OSD_PAGE_DISPLAY);
   }
}

void KillTimerOfHideOSD()//ֹͣ��ʱ��
{
	LOGD("timer kill osd timer");
	//if(m_nTimerSubTitle)
	//{
		//KillTimer(NULL,m_nTimerSubTitle);
		DeleteTimer(OSD_TIMER_DROP_DOWN_DISPLAY);
	//    m_nTimerSubTitle = 0;
	//}
	//if (m_nTimerOSDPage)
	//{
		//KillTimer(NULL,m_nTimerOSDPage);
		DeleteTimer(OSD_TIMER_OSD_PAGE_DISPLAY);
	//	m_nTimerOSDPage = 0;
	//}
}
//��ʱ������
//void MyTimerProc(u32 nTimerID)
//{
//
//	   int iCurOSDContent = pLocalParam->m_nCurOSDContent;
//       if(m_nTimerSubTitle == nTimerID)
//       {
//           //KillTimer(NULL,m_nTimerSubTitle);
//    	   DeleteTimer(OSD_TIMER_VOL_DROP_DOWN_DISPLAY);
//
//           m_nTimerSubTitle = 0;
//		   if(IsSubTitleOSD(iCurOSDContent))
//           ShowHideOSD(iCurOSDContent,false);
//       }
//	   else if (pLocalParam->m_timerSettingVideo == nTimerID)
//	   {
//		   LOGD("\nosd get timer set video");
//		   TimerSetVideo();
//	   }
//	   else if (m_nTimerOSDPage == nTimerID)
//	   {
//		   //������ڲ�ͬ��OSDҳ�� �������Ӧ�ı���ҳ
//		   //KillTimer(NULL,m_nTimerOSDPage);
//		   m_nTimerOSDPage = 0;
//		   if (!IsSubTitleOSD(iCurOSDContent))
//		   {
//			   ShowHideOSD(iCurOSDContent,false);
//			   BackToBkGndPage();
//		   }
//	   }
//}

void ShowSubTitleCmdProc(int nNewOSDContent)//��ʾ����osd����
{
	 static int firstGetOSD=0;
	 if(firstGetOSD==0){
		firstGetOSD+=1;
		usleep(1000*300);
	 }
	LOGD("ShowSubTitleCmdProc %d",nNewOSDContent);
    int nCurOSDContent = pLocalParam->m_nCurOSDContent;
	if (nCurOSDContent == OSD_BACK)
	{
		return;
	}
    if(nNewOSDContent == nCurOSDContent)//��osdĿǰ������ʾ
    {
		SetTimerOfHideOSD();
        return;
    }

	//���ؾɵ�OSD���ݣ������Ӧ�ı���ҳ
	if(!IsSubTitleOSD(nCurOSDContent) &&  OSD_NoDisplay != nCurOSDContent)//������ڵ�OSD���ݲ�������OSD
	BackToBkGndPage();

	//������OSD
    //m_pTheApp->m_pCenterDriver->ShowHideOSD(nCurOSDContent,false);

    ShowHideOSD(nNewOSDContent,true);

    SetTimerOfHideOSD();
}
//����CenterModule,����osd��״̬
//void Set_TellCenterModuleSubOSDState()
//{
//	bool bHaveSubOSD = false;//�Ƿ�����ʾOSD
//	int iOSDContent = m_pTheApp->m_pCenterParam->m_nCurOSDContent;
//    bHaveSubOSD = IsSubTitleOSD(iOSDContent);
//    static bool bOldHaveSubOSD = false;
//	if (bHaveSubOSD == bOldHaveSubOSD)
//    return;
//	bOldHaveSubOSD = bHaveSubOSD;
//	unsigned char buf[] = {Module_CENTER,0xE0,CModuleApp::BoolToChar(bHaveSubOSD)};
//	MakeAndSendToModule(buf,3);
//}
void SetVideoSetting(unsigned char cParam)//����Driver����Ƶ��ɫ����
{
//	switch(cParam)
//	{
//		case 0x00://
//		case 0x01://
//		case 0x02://
//		case 0x03://
//		case 0x04://
//		case 0x05://
//		case 0x06://
//		case 0x07://
//			m_nVideoSettingItem = cParam;
//			TimerSetVideo();
//			m_timerSettingVideo = SetTimer(NULL,m_timerSettingVideo,200,TimerProc);
//		  break;
//		case 0x80://
//		case 0x81://
//		case 0x82://
//		case 0x83://
//		case 0x84://
//		case 0x85://
//		case 0x86://
//		case 0x87://
//			//m_timerSettingVideo = SetTimer(NULL,m_timerSettingVideo,200,TimerProc);
//			KillTimer(NULL,m_timerSettingVideo);
//			m_timerSettingVideo = 0;
//			break;
//	}

}
void TimerSetVideo()//�ö�ʱ������
{

//	byte cParam = (byte)pLocalParam->m_nVideoSettingItem;
//	map<byte,byte> mapParam;
//	mapParam[0x0] = 0x02;
//	mapParam[0x1] = 0x01;
//	mapParam[0x2] = 0x04;
//	mapParam[0x3] = 0x03;
//	mapParam[0x4] = 0x06;
//	mapParam[0x5] = 0x05;
//	mapParam[0x6] = 0x08;
//	mapParam[0x7] = 0x07;
//	if(mapParam.find(cParam) == mapParam.end())
//		return;
//	unsigned char buf[] = {Module_SOUND,0x11,mapParam[cParam]};
//	TRACE(L"\n set video %x",buf[2]);
//	MakeAndSendToModule(Module_SOUND,buf,3);
}

bool IsSubTitleOSD(int iOSDConnect)
{
    bool bHaveSubOSD = false;
	switch(iOSDConnect)
	{
	case OSD_AC_SubTitle:
	case OSD_Sound_SubTitle:
	case OSD_System_SubTitle:
	case OSD_Radio_SubTitle:
	case OSD_CDC_SubTitle:
	case OSD_DVD_SubTitle:
	case OSD_TPMS_SubTitle:
	case OSD_BT_SubTitle:
	case OSD_Media_SubTitle:
		bHaveSubOSD = true;
		break;
	default:
		bHaveSubOSD = false;
	}
	return bHaveSubOSD;
}
//���ûOSD�ı���ҳ
void BackToBkGndPage()
{

	u16 CurPageID = 0;
	u8 CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen);

	switch(CurPageID)
	{
	case  PAGE_TV_VIDEO_CONTROL:							//tv osd 0801
	case  PAGE_TV_VIDEO_SET:								//tv osd 0802
		osdToModule_NotifySystem_jumpPage(PAGE_TV_VIDEO);
		break;
	case PAGE_AUX_VIDEO_CONTROL:             				//aux osd 0d02
	case PAGE_AUX_VIDEO_SET:                                //aux osd 0d03
		osdToModule_NotifySystem_jumpPage(PAGE_AUX_VIDEO);
		break;
	case PAGE_DVD_VIDEO_CONTROL:                         	//dvd osd 0505
	case  PAGE_DVD_VIDEO_SET:                            	//dvd osd 0506
		osdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);
	   break;
	case PAGE_DRIVING_RECORD_MENU:                			//dvr osd 4001
	case PAGE_DRIVING_RECORD_TIME_SET:            			//dvr osd 4002
	case PAGE_DRIVING_RECORD_PALY:                			//dvr osd 4003
	case PAGE_DRIVING_RECORD_SET:                 			//dvr osd 4004
	case PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD:
	case PAGE_DRIVING_CHANGHE_DVR_SET_OSD:
		osdToModule_NotifySystem_jumpPage(PAGE_DRIVING_RECORD_VIDEO);
		break;
	}
}


void Get_DropDownOsdMessage(u8 osdContent)
{
    if(pLocalParam->bDropDownOSD_Switch == false)
    {
        u8 uAcgreePageHide_DropDownOsd = 0;
        u8 uAcgreePageHide_DropDownOsd_len = 1;
        getOtherModuleParam(MODULE_ID_CENTER, CENTER_AGREEPAGE_ISHIDE, (u8*)&uAcgreePageHide_DropDownOsd, &uAcgreePageHide_DropDownOsd_len);
        pLocalParam->bDropDownOSD_Switch = uAcgreePageHide_DropDownOsd;
    }
    
    if(pLocalParam->bDropDownOSD_Switch == false){
        u8 uKeyAction_DropDownOsd = 0;
        u8 uKeyAction_DropDownOsd_len = 1;
        getOtherModuleParam(MODULE_ID_KEY, KEYACTION_DROPDOWNOSD, (u8*)&uKeyAction_DropDownOsd, &uKeyAction_DropDownOsd_len);
        pLocalParam->bDropDownOSD_Switch = uKeyAction_DropDownOsd;

        if(osdContent == 0x10){
            pLocalParam->bDropDownOSD_Switch = true;
        }
    }


    LOGD("[%s] pLocalParam->bDropDownOSD_Switch:%d",__FUNCTION__,pLocalParam->bDropDownOSD_Switch);
    if(!pLocalParam->bDropDownOSD_Switch)return;

	u8 ucBackStatus = 0x00;
	int ucBackStatusLen = 0x00;
	getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackStatus,(u8*)&ucBackStatusLen);
	if(ucBackStatus == 0x01)
		return;
	
	switch(osdContent)
	{
	case 0x10:
		ShowSubTitleCmdProc(OSD_Sound_SubTitle);
		break;
	case 0x11:
		if(pLocalParam->bNoShowACosdState != 1){
			ShowSubTitleCmdProc(OSD_AC_SubTitle);
		}
		break;
	case 0x12:
		ShowSubTitleCmdProc(OSD_DVD_SubTitle);
		break;
	case 0x13:
		ShowSubTitleCmdProc(OSD_CDC_SubTitle);
		break;
	case 0x14:
		ShowSubTitleCmdProc(OSD_Media_SubTitle);
		break;
	case 0x15:
		ShowSubTitleCmdProc(OSD_BT_SubTitle);
		break;
	case 0x16:
		ShowSubTitleCmdProc(OSD_TPMS_SubTitle);
		break;
	case 0x17:
		ShowSubTitleCmdProc(OSD_Radio_SubTitle);
		break;
	default:
		break;
	}

}


void Get_SetOSDUIValue(u8* param,int len)
{
	SetOSDUIValue_OSDToHal(param,len);
	u8 cmd = param[0];
	switch(cmd)
	{
	case 0x30:
	case 0x31:
	case 0x40:
	case 0x41:
//	case 0x50:
//	case 0x51:
//	case 0x52:
//	case 0x53:
	case 0x60:
	case 0x61:
		SetTimerOfHideOSD();
	    break;
	case 0x21://color
//	 case 0x31:
//	 case 0x41:
//	 case 0x61:
		 SetTimerOfHideOSD();
		 //SetVideoSetting(param[1]);
		 break;
	}

}

void ShowOSDPage(int EnterPageId)
{
	static int oldEnterPageId = -1;
	if(oldEnterPageId == EnterPageId)
	   return;
	 oldEnterPageId = EnterPageId;
	 int nCurOSDContent = pLocalParam->m_nCurOSDContent;
	 switch (EnterPageId)
	    {
	    case PAGE_AUX_VIDEO_CONTROL: //Osd_cdc_menuҳ��
	    case PAGE_DRIVING_CHANGHE_DVR_SET_OSD:
	       ShowHideOSD(OSD_AUX_Menu,true);
	        break;
	    case PAGE_AUX_VIDEO_SET:  //Osd_cdc_colorҳ��
	    case PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD:
	       ShowHideOSD(OSD_AUX_Color,true);
	        break;
	    case PAGE_BACK_VIDEO:  //Osd_tv_hideҳ��
	       {
	    		ShowHideOSD(OSD_BACK,true);
	    		//usleep(1000*300);
	    		//ShowHideOSD(OSD_BACK,true);
	    		DeleteTimer(OSD_TIMER_COME_IN_BACK_CAR);
                SetTimer(300,1,OSD_TIMER_COME_IN_BACK_CAR);
	       }

	        break;
	    case PAGE_BACK_VIDEO_T123COLORSET_PAGE:
	        ShowHideOSD(OSD_BACK_Color,true);
	        break;
	    case PAGE_DVD_VIDEO_CONTROL: //Osd_tv_menuҳ��
	       ShowHideOSD(OSD_DVD_Menu,true);
	        break;
	    case  PAGE_DVD_VIDEO_SET	:  //Osd_tv_colorҳ��
	      ShowHideOSD(OSD_DVD_Color,true);
	        break;
	    case PAGE_DRIVING_RECORD_MENU://Osd_dvd_menuҳ��
	      ShowHideOSD(OSD_DVR_Menu,true);
	        break;
	    case PAGE_DRIVING_RECORD_TIME_SET: //Osd_dvd_colorҳ��
	      ShowHideOSD(OSD_DVR_TimeSet,true);
	        break;
	    case  PAGE_DRIVING_RECORD_SET: //Osd_aux_colorҳ��
	      ShowHideOSD(OSD_DVR_VideoSet,true);
	        break;
	    case PAGE_DRIVING_RECORD_PALY : //Osd_aux_menuҳ��
	      ShowHideOSD(OSD_DVR_Play,true);
	        break;
		case PAGE_TV_VIDEO_CONTROL://OSD ����ҳ��
	      ShowHideOSD(OSD_TV_Menu,true);
			break;
		case PAGE_TV_VIDEO_SET://OSD ����ҳ��
		      ShowHideOSD(OSD_TV_Color,true);
				break;
	    default:
	        {
	            if(OSD_NoDisplay == nCurOSDContent)
	                return;
	        }
	        break;
	    }

}
void HideOSDPage(int EnterPageId)
{
	static int oldEnterPageId = -1;
	if(oldEnterPageId == EnterPageId)
	return;
	oldEnterPageId = EnterPageId;

	int nCurOSDContent = pLocalParam->m_nCurOSDContent;
	KillTimerOfHideOSD();//�ص�����OSD�Ķ�ʱ��

	if(OSD_NoDisplay != nCurOSDContent)//����OSD������
    ShowHideOSD(nCurOSDContent,false);
	if(OSD_BACK == nCurOSDContent)
	{
		usleep(1000*300);
		ShowHideOSD(nCurOSDContent,false);
	}
}
void Get_PageChangeMessage(int LeavePageID,int EnterPageID,int Param){

	//��������OSD��ʾ��ص�����OSD�Ķ�ʱ��
	//Param 0表示切通道前  1表示切通道后
	LOGD("\nOsd get PageChange msg:  From %x,To %x,%d",LeavePageID,EnterPageID,Param);
	if(Param == 0)//
		HideOSDPage(EnterPageID);
	else if(Param == 1)
		ShowOSDPage(EnterPageID);


}

