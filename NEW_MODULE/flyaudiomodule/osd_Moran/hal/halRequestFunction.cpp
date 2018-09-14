#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"
#include <flymoduleApi_internal.h>

#include "otherModuleResponseFunction.h"
#include "appRequestCommand.h"
#include <param.h>
#include "moduleParamRequest.h"

//T123Chip
void AboutNewLogic_HideOrDisplayingOSD(u8 param)
{	
    u8 buf[]={0x01,0x00};
    if(param != 0x00)
    {
        buf[1]=param;
    }

    LOGD("T123 HideOrDisplayingOSD buf[1]:%x",buf[1]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf, 2);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,2);
}

void SoundValue_OSDToHal(u8 param)
{
    u8 buf[]={0x10,0x00};
    if(param != 0x00)
    {
        buf[1]=param;
    }

    LOGD("T123 Sound Value ToHal buf[1]:%x",buf[1]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf, 2);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,2);

}

void ACMessage_OSDToHal(short nLeftTemp,short nRightTemp,u8 nUnit,u8 nSpeed,u8 nACState)
{
    u8 buf[10]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    buf[0]=0x11;
    buf[2]=(nLeftTemp&0xFF00)>>8;
    buf[1]=nLeftTemp&0x00FF;
    buf[4]=(nRightTemp&0xFF00)>>8;
    buf[3]=nRightTemp&0x00FF;
    buf[5]=nUnit;
    buf[6]=nSpeed;
    buf[7]=nACState;
    LOGD("T123 AC Message To Hal leftTemp rightTemp unit speed power:%d %d %d %d %d",buf[1]+buf[2]*256,buf[3]+buf[4]*256,buf[5],buf[6],buf[7]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf, 8);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,8);

}

void DVDplay_titleAndTrack_OSDToHal(u8 *param,int len)
{
    u8 buf[10]={0x00};
    buf[0]=0x12;
    memcpy(&buf[1],&param[0],1);
    buf[1]=param[0];
    buf[2]=param[4];
    buf[3]=param[3];
    buf[4]=param[2];
    buf[5]=param[1];
    LOGD("T123 DVD osd titleAndTrack To Hal disctype:%d title:%d track:%d",buf[1],buf[2]+buf[3]*256,buf[4]+buf[5]*256);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf, 6);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,6);

}

void CDC_TitleTrackTimesValue_OSDToHal(u8 title,u16 track)
{
    u8 buf[256]={0};
    buf[0]=0x13;
    buf[1]=title;
    memcpy(&buf[2],&track,2);
    LOGD("T123 CD TitleTrackTimesValue To Hal:%x",buf[1]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf, 4);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,4);
}

void MediaPlay_TrackValue_OSDToHal(u8 *param)
{
    u8 buf[10]={0};
    buf[0]=0x14;
    buf[2]=param[0];
    buf[1]=param[1];
    buf[4]=param[2];
    buf[3]=param[3];
   
    LOGD("T123 Media Track To Hal:%x %x",buf[1]+buf[2]*256,buf[3]+buf[4]*256);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf, 5);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,5);

}

void BTcontectStatus_OSDToHal(u8 *param)
{
    u8 buf[10]={0x00,0x00};
    buf[0]=0x15;
    memcpy(&buf[1],param,1);
    LOGD("T123  BT contect status:%d  a2dp Track To Hal Current_Trac:%d Total_Track:%d",buf[1]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,2);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,2);

}

void TPMS_TempsAndStatus_OSDToHal(u8 tire,u8 status)
{
    u8 buf[]={0x16,0x00,0x03};
    buf[1]=tire;
    buf[2]=status;
    LOGD("T123 TPMS TempsAndStatus To Hal:%d %d",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void Radio_Channel_Value_OSDToHal(u8 type,u16 value,u8 unit)
{ 
    u8 buf[]={0x17,0x00,0x00,0x00,0x00};
    buf[1]=type;
	memcpy(&buf[2],&value,2);
    buf[4]=unit;
    LOGD("T123 Radio Channel Value To Hal:%d",value);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,5);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,5);
}


void BackcarVideoSetButton_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x20,0x00,0x03};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 BackcarVideo SetButton To Hal:%x %x",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void BackcarVideoLCDColorSet_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x21,0x00,0x03};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 BackcarVideo LCDColorSet To Hal:%x %x",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void BackcarVideoColorValue_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x00,0x00};
    if(param1 != 0x00)
    {
        buf[0]=param1;
        buf[1]=param2;
        LOGD("T123 BackcarVideo ContrastValue To Hal:%x",buf[1]);
        //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,2);
		OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,2);
    }

}

void BackcarVideoRaderDisplaying_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x26,0x00,0x00};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 BackcarVideo RaderDisplaying To Hal:%x %x",buf[1], buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);
}

void BackcarVideoCarDisplayingStatus_OSDToHal(u8 param)
{
    u8 buf[]={0x27,0x00};
    buf[1]=param;
    LOGD("T123 BackcarVideo CarDisplayingStatus To Hal:%x",buf[1]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,2);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,2);
}

void BackcarVideoWarningsDisplayingStatus_OSDToHal(u8 param)
{
    u8 buf[]={0x28,0x00};
    buf[1]=param;
    LOGD("T123 BackcarVideo WarningsDisplayingStatus To Hal:%x",buf[1]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,2);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,2);
}


void AuxVideoSetButton_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x30,0x00,0x03};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 AuxVideo SetButton To Hal:%x %x",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void AuxVideoLCDColorSet_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x31,0x00,0x03};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 AuxVideo LCDColorSet To Hal:%x %x",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void AuxVideoColorValue_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x00,0x00};
    if(param1 !=0x00)
    {
    buf[0]=param1;
    buf[1]=param2;
    LOGD("T123 AuxVideo ColorValue To Hal:%x %x ",buf[0],buf[1]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,2);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,2);
    }


}


void TVVideoSetButton_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x40,0x00,0x03};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 TVVideo SetButton To Hal:%x %x",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void TVVideoLCDColorSet_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x41,0x00,0x03};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 TVVideo LCDColorSet To Hal:%x %x",buf[1],buf[2]);
   // makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void TVVideoColorValue_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x00,0x00};
    if(param1 != 0x00)
    {
    buf[0]=param1;
    buf[1]=param2;
    LOGD("T123 TVVideo ColorValue To Hal:%x %x ",buf[0],buf[1]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,2);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,2);
    }

}


void dvrVideoSetButton_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x50,0x00,0x03};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 dvrVideo SetButton To Hal:%x %x",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void dvrVideoPlaySet_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x51,0x00,0x03};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 dvrVideo PlaySet To Hal:%x %x",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void dvrVideoYMDSet_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x52,0x00,0x00};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 dvrVideo YMDSet To Hal:%x %x",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void dvrVideoSet_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x53,0x00,0x00};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 dvrVideo Set To Hal:%x %x",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}


void dvdVideoSetButton_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x60,0x00,0x03};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 dvdVideo SetButton To Hal:%x %x",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void dvdVideoPlayTimes_OSDToHal(u8 *param)
{
    u8 buf[10]={0x00};
    buf[0]=0x6A;
    memcpy(&buf[1],param,4);
    LOGD("T123 dvdVideo PlayTimes To Hal:%d",buf[1]+buf[2]*256+buf[3]*256*256+buf[4]*256*256*256);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,5);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,5);
}

void dvdVideoLCDColorSet_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x61,0x00,0x03};
    buf[1]=param1;
    buf[2]=param2;
    LOGD("T123 dvdVideo LCDColorSet To Hal:%x %x",buf[1],buf[2]);
    //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,3);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN, buf,3);

}

void dvdVideoColorValue_OSDToHal(u8 param1,u8 param2)
{
    u8 buf[]={0x00,0x00};
    if(param1 != 0x00)
    {
        buf[0]=param1;
        buf[1]=param2;
        LOGD("T123 dvdVideo ColorValue To Hal:%x %x ",buf[0],buf[1]);
        //makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,2);
		OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN,buf,2);
    }

}

void ViewChannelSwitchOSDToHal(u8 param)
{
    u8 buf[]={0x01,0x00};
    if(param != 0x00)
    {
        buf[1]=param;
    }

    LOGD("T123 Viewchannel Switch To Hal buf[1]:%x",buf[1]);
    //makeAndSendMessageToHal(HAL_ID_OSD_SETVIDEO, buf, 2);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_SETVIDEO,buf,2);
}

void ShowHideOSD(int nOSDContent,bool bShowFlag)
{
	 //byte cShowWayFlag = GetShowOSDWagFlag(nOSDContent,bShowFlag);//�л���ʽ  0���л� 1���� 2 ����

    LOGD("ShowHideOSD:%x %x",nOSDContent,bShowFlag);
     if (bShowFlag)//��ʾ
     {
    	 pLocalParam->m_nCurOSDContent = nOSDContent;
    	 LOGD("ShowHideOSD pLocalParam->m_nCurOSDContent:%x",pLocalParam->m_nCurOSDContent);
    	 switch(nOSDContent){
    	 case OSD_DVR_Menu:
    	 case OSD_DVR_VideoSet:
    	 case OSD_DVR_Play:
    	 case OSD_DVR_TimeSet:
    		 break;
    	 default :
    		 SetTimerOfHideOSD();
    		 break;
    	 }
     }
     else
     {
    	 pLocalParam->m_nCurOSDContent = OSD_NoDisplay;
     }
	 //Set_TellCenterModuleSubOSDState();//����CenterModule,����osd��״̬

	 if (!bShowFlag)//���������
	 {
         Set_DisplayOSDPage(OSDPAGE_HIDEOSD);
		 return;
	 }

     switch (nOSDContent)
     {
             case OSD_Sound_SubTitle:
				 Set_DisplayOSDPage(OSDPAGE_SOUND_TITLE);
                 break;
             case OSD_AC_SubTitle:
            	 Set_DisplayOSDPage(OSDPAGE_AC_TITLE);
            	 break;
		     case OSD_DVD_SubTitle:
			     Set_DisplayOSDPage(OSDPAGE_DVD_TITLE);
			     break;
             case OSD_CDC_SubTitle:
				 Set_DisplayOSDPage(OSDPAGE_CDC_TITLE);
                 break;
             case OSD_Media_SubTitle:
				 Set_DisplayOSDPage(OSDPAGE_MEDIA_TITLE);
                 break;
             case OSD_BT_SubTitle:
				 Set_DisplayOSDPage(OSDPAGE_BT_TITLE);
                 break;
             case OSD_TPMS_SubTitle:
				 Set_DisplayOSDPage(OSDPAGE_TPMS_TITLE);
                 break;
             case OSD_Radio_SubTitle:
				 Set_DisplayOSDPage(OSDPAGE_RADIO_TITLE);
                 break;
             case OSD_System_SubTitle:
                 //�򿪲��ڴ˴���
//                 if(!bShowFlag)//�ر�
//                     Set_SendCmd(Module_SYSTEM,0x82,0);
                 break;

             case OSD_BACK:
				 {
					 if(pLocalParam->bBackcarThreeAngle){
						LOGD("Honda guang jiao back car ");
						u8 bOSDIsBackCarRefLineEnable = 1;
                	    u8 nLen = 1;
                	    getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_SET_BackVideoRefLineEnable, (u8*)&bOSDIsBackCarRefLineEnable, (u8*)&nLen);
                	    LOGD("Module_0SD bOSDIsBackCarRefLineEnable:%d",bOSDIsBackCarRefLineEnable);
                	    if(bOSDIsBackCarRefLineEnable == 1)
                	    {
						    Set_DisplayOSDPage(OSDPAGE_BACK_GUANGJIAO);
						}
					 }
					 else{

						 if(pLocalParam->m_haveRadar)
							  Set_DisplayOSDPage(OSDPAGE_BACK_RADAR_CAR);
						 else
							  Set_DisplayOSDPage(OSDPAGE_BACK);
					 }
				 }
            	break;
			 case OSD_BACK_Color:
				 Set_DisplayOSDPage(OSDPAGE_BACK_COLOR);
				 break;
             case OSD_AUX_Menu:
				 Set_DisplayOSDPage(OSDPAGE_AUX_MENU);
                 break;
             case OSD_AUX_Color:
				 Set_DisplayOSDPage(OSDPAGE_AUX_COLOR);
                 break;
             case OSD_TV_Menu:
				 Set_DisplayOSDPage(OSDPAGE_TV_MENU);
                 break;
             case OSD_TV_Color:
				 Set_DisplayOSDPage(OSDPAGE_TV_COLOR);
                 break;
             case OSD_DVR_Menu:
           		 Set_DisplayOSDPage(OSDPAGE_DVR_MENU);
                 break;
              case OSD_DVR_VideoSet:
           		 Set_DisplayOSDPage(OSDPAGE_DVR_VIDEOSET);
                 break;
             case OSD_DVR_Play:
				 Set_DisplayOSDPage(OSDPAGE_DVR_PLAY);
                 break;
             case OSD_DVR_TimeSet:
				Set_DisplayOSDPage(OSDPAGE_DVR_TIMESET);
                 break;
             case OSD_DVD_Menu:
				 Set_DisplayOSDPage(OSDPAGE_DVD_MENU);
                 break;
             case OSD_DVD_Color:
				 Set_DisplayOSDPage(OSDPAGE_DVD_COLOR);
                 break;
     }
	 osdModuleToAPP_Notify_SubtitleInfo(nOSDContent);
}



void Set_DisplayOSDPage(unsigned char cPageFlag)//������ʾ�������osdҳ
{
	 LOGD("\nDisplay OSDPage %x",cPageFlag);
	 unsigned char buf[] = {0x01,cPageFlag};
	// MakeAndSendToDriver(buf,3);
	// makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, buf,2);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN,buf,2);
}


void SetOSDUIValue_OSDToHal(u8* param,int len)
{
    LOGD("SetOSDUIValue_OSDToHal:%x %x %x",param[0],param[1],param[2]);
	//makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN, param,len);
	OsdMsgTheAdapterEntrance(HAL_ID_OSD_BUTTEN,param,len);
}

void makeAndSendMessageToUI(u8* param,int len)
{
	if(len <= 0)
		return;
	
	u8 buf[50] = {0};
	
	if(len > 49)
		len = 49;
	
	int nBufLen = len + 1;
	buf[0] = 0x50;
	memcpy(buf + 1,param,len);
	
	setCommand(0x00,buf,nBufLen);
}

void OsdMsgTheAdapterEntrance(moduleid_t halId,u8* param,int len)
{
	if(pLocalParam->uModuleOsd_is_T123 == 1)
    {
    	switch(param[1]) 
		{ 
			case OSDPAGE_HIDEOSD: 
			case OSDPAGE_SOUND_TITLE: 
			case OSDPAGE_AC_TITLE: 
			case OSDPAGE_DVD_TITLE: 
			case OSDPAGE_CDC_TITLE: 
			case OSDPAGE_MEDIA_TITLE: 
			case OSDPAGE_BT_TITLE: 
			case OSDPAGE_TPMS_TITLE: 
			case OSDPAGE_RADIO_TITLE: 
				makeAndSendMessageToUI(param,len); 
			break; 
		}
		makeAndSendMessageToHal(halId, param,len);
	}
	else
	{
		makeAndSendMessageToUI(param,len);
	}
}


