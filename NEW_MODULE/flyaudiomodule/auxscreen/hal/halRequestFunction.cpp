#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"
#include "moduleParamRequest.h"

#include <flymoduleApi_internal.h>
#include <time.h>

//��ʼ��
void auxScreenToHal_Init(){
    u8 buf[] = {0x01,0x01};
    makeAndSendMessageToHal(HAL_ID_EXDISPLAY,buf,2);
}
//ģ�ⰴ��
void auxScreenToHal_EmulateKey(u8 nKey){
    u8 buf[] = {0x03,nKey};
    makeAndSendMessageToHal(HAL_ID_EXDISPLAY,buf,2);
}
//���ڲ���ģ��
void auxScreenToHal_PlayingModule(u8 nModule){
   u8 buf[] = {0x11,nModule};
   makeAndSendMessageToHal(HAL_ID_EXDISPLAY,buf,2);
}
//������Ϣ
void auxScreenToHal_PlayingInfo(u8* buf,int len){
   makeAndSendMessageToHal(HAL_ID_EXDISPLAY,buf,len);
}


//��������
void auxScreenToHal_PlayVolume(unsigned char vol){
	unsigned char buf[] = { 0x80, vol};

	//makeAndSendMessageToHal(MODULE_ID_AUXSCREEN,buf,2);
	makeAndSendMessageToHal(HAL_ID_EXDISPLAY,buf,2);
}

//ʱ��
void auxScreenToHal_TimeInfo(u8* buf,int len)
{
	   makeAndSendMessageToHal(HAL_ID_EXDISPLAY,buf,len);
}

//��������Ϣ
void auxScreenToHal_GPSInfo(u8* buf,int len)
{
	//-->¹ýÂË
	    //LOGD("auxScreenToHal_GPSInfo,buf[0]=%x",buf[0]);
		int nCanSendChinese = 1;
		int nLen = 0;
		switch(buf[0])
		{
		case 0x07:
		case 0x08:
		case 0x15:
		case 0x88:
		case 0x89:
			getOtherModuleParam(MODULE_ID_EXTCAR, EXTCAR_PARAM_DZ_SCREEN_RECEIVE_CHINESE, (u8 *)&nCanSendChinese, (u8 *)&nLen);

			break;
		}
		if (nCanSendChinese == 0)
		{
			LOGD("[DYB] GPS RETURN.");
			return;
		}
	    else
			LOGD("[DYB] GPS ID = [%X]", buf[0]);
		//<--

	struct tm *ptm;
	long ts;
	ts = time(NULL);
	ptm=localtime(&ts);

	u8 hour = (u8)(ptm->tm_hour);
	u8 min  = (u8)(ptm->tm_min);
	u8 sec  = (u8)(ptm->tm_sec);
	LOGD("************Set_CurTime**********hour:%d min:%d sec:%d",hour,min,sec);
	
	u8 proto_conver = 0xFF;
	int ana_len=len;
	switch(buf[0])
	{
		/*�����µ�����Ϣ*/
		case 0x01:/*ת�䷽��*/
		{
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];
			switch(buf1)
			{
				case 0:
					buf1 = 1;
				break;
				case 1:
					buf1 = 5;
				break;
				case 2:
					buf1 = 3;
				break;
				case 3:
					buf1 = 7;
				break;
				case 4:
					buf1 = 12;
				break;
				case 5:
					buf1 = 2 ;
				break;
				case 6:
					buf1 = 4;
				break;
				default:break;
			}
			proto_conver = 0x01;
			ana_len=1+1;
			memcpy(buf+1,&buf1,1);
			LOGD("**********1111111***%d",buf1);
		}
		break;
		case 0x02:/*�����յ���ľ���*/
		{
			int buf1 = (buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4])*10;//dm
			proto_conver = 0x02;
			ana_len=4+1;	
			memcpy(buf+1,&buf1,4);
			LOGD("**********2222222***%d",buf1);
		}
		break;
		case 0x03:/*��ǰ����Ŀ�ĵصľ���*/
		{
			proto_conver = 0x04;
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];//m
			ana_len=4+1;
			memcpy(buf+1,&buf1,4);
			LOGD("**********3333333***%d",buf1);
		}
		break;
		case 0x04:/*��������Ŀ�ĵ�֮����ܾ���*/
		{
			proto_conver = 0x05;
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];//m
			ana_len=4+1;
			memcpy(buf+1,&buf1,4);
			LOGD("**********4444444***%d",buf1);
		}
		break;
		case 0x05:/*����Ŀ�ĵ�ʣ��ʱ��*/
		{
			proto_conver = 0x06;/*����Ŀ�ĵ�ʱ���*/
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4]+hour*3600+min*60+sec;
			int hour1=buf1/3600;
			int min1=(buf1%3600)/60;
			ana_len=2+1;
			memcpy(buf+1,&hour1,1);
			memcpy(buf+2,&min1,1);
			LOGD("*********55hour1***%d",hour1);
			LOGD("**********55min1***%d",min1);
		}
		break;
		case 0x06:/*��������Ŀ�ĵ���ʱ��*/
		{
			proto_conver = 0x07;
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];//s
			int hour1=buf1/3600;
			int min1=(buf1%3600)/60;
			ana_len=2+1;
			memcpy(buf+1,&hour1,1);
			memcpy(buf+2,&min1,1);
			LOGD("**********66hour1***%d",hour1);
			LOGD("**********66min1***%d",min1);
		}
		break;
		case 0x07:/*��ǰ��·����*/
		{
		proto_conver = 0x08;
		}
		break;
		case 0x08:/*��һ��·����*/
		{
		proto_conver = 0x09;
		}
		break;
		case 0x09:/*��ǰ��·����*/
		break;
		case 0x10:/*��ǰ����*/
		break;
		case 0x11:/*��ǰ����*/
		{
			proto_conver = 0x0C;
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];//km/h
			ana_len=1+1;
			memcpy(buf+1,&buf1,1);
			LOGD("**********0x11***%d",buf1);
		}
		break;
		case 0x12:/*��ǰGPS�Ƕ�*/
		{
			proto_conver = 0x0B;
		}
		break;
		case 0x13:/*�����������*/
		break;
		case 0x14:/*����������*/
		break;
		case 0x15:/*��ǰ�����������*/
		break;
		case 0x16:/*�������ת����Ϣ��ֵ*/
		break;
		case 0x20:/*��ʻ��λ*/
		{
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];
			proto_conver = 0x00;
			ana_len=1+1;
			memcpy(buf+1,&buf1,1);
			LOGD("**********0x20***%d",buf1);
		}
		break;
		case 0x88:/*utf8�ĵ�ǰ��·���*/
		{
			proto_conver = 0x88;
		}
		break;
		case 0x89:/*utf8����һ����·���*/
		{
			proto_conver = 0x89;
		}
		break;
		default:break;
	}
	if(proto_conver == 0xFF)
		return;
	u8 pBuffer[ana_len+1];
	memset(pBuffer,0,sizeof(pBuffer));
	pBuffer[0]=0xB0;
	pBuffer[1]=proto_conver;
	memcpy(&pBuffer[2],buf+1,ana_len-1);
	makeAndSendMessageToHal(HAL_ID_EXDISPLAY,pBuffer,ana_len+1);
	
	LOGD("**********start*********");
	for(int i = 0;i<ana_len+1;i++)
	{
		LOGD("(%d)%x",i,pBuffer[i]);
	}
	LOGD("***********end*********");
	
}



void auxScreenToHal_GaodeMap_GPSInfo(u8* buf,int len)
{
	int nCanSendChinese = 1;
	int nLen = 0;
	switch(buf[0])
	{
		case 0x00:
		case 0x01:
		case 0x88:
		case 0x89:
			getOtherModuleParam(MODULE_ID_EXTCAR, EXTCAR_PARAM_DZ_SCREEN_RECEIVE_CHINESE, (u8 *)&nCanSendChinese, (u8 *)&nLen);

			break;
	}
	if (nCanSendChinese == 0)
	{
		LOGD("GPS RETURN.");
		return;
	}
	else
		LOGD("GPS ID = [%X]", buf[0]);

	struct tm *ptm;
	long ts;
	ts = time(NULL);
	ptm=localtime(&ts);

	u8 hour = (u8)(ptm->tm_hour);
	u8 min  = (u8)(ptm->tm_min);
	u8 sec  = (u8)(ptm->tm_sec);
	//LOGD("************Set_CurTime**********hour:%d min:%d sec:%d",hour,min,sec);
	
	u8 proto_conver = 0xFF;
	int ana_len=len;
	switch(buf[0])
	{
		case 0x00:
			proto_conver = 0x08;
			LOGD("*******0X00******buf+1=%s",buf+1);
			break;
		case 0x01:
			proto_conver = 0x09;
			LOGD("*******0X01******buf+1=%s",buf+1);
			break;
		case 0x02:
			break;
		case 0x03:
			break;
		case 0x04:
			break;
		case 0x05:
			break;
		case 0x06:
			break;
		case 0x07:
			break;
		case 0x08:
		{
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];
			switch(buf1)
			{
				case 2:
					buf1 = 2;
				break;
				case 3:
					buf1 = 3;
				break;
				case 4:
					buf1 = 4;
				break;
				case 5:
					buf1 = 5;
				break;
				case 7:
					buf1 = 7;
				break;
				case 8:
					buf1 = 12;
				break;
				case 9:
					buf1 = 1;
				break;
				case 17:
					buf1 = 13;
				break;
				case 18:
					buf1 = 14;
				break;
				case 19:
					buf1 = 15;
				break;
				case 20:
					buf1 = 16;
				break;
				case 21:
					buf1 = 17;
				break;
				case 22:
					buf1 = 18;
				break;
				case 23:
					buf1 = 19;
				break;
				case 24:
					buf1 = 20;
				break;
				default:
					buf1 = 0;
				break;
			}
			proto_conver = 0x01;
			ana_len=1+1;
			memcpy(buf+1,&buf1,1);
			LOGD("**********0x08***%d",buf1);
		}
			break;
		case 0x09:
		{
			proto_conver = 0x04;
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];//m
			ana_len=4+1;
			memcpy(buf+1,&buf1,4);
			LOGD("**********0x09***%d",buf1);
		}
			break;
		case 0x0a:
		{
				
			u8 pBuffer[ana_len+1];
			memset(pBuffer,0,sizeof(pBuffer));
			pBuffer[0]=0xB0;
			pBuffer[1]=0x0D;
			memcpy(&pBuffer[2],buf+1,ana_len-1);
			makeAndSendMessageToHal(HAL_ID_EXDISPLAY,pBuffer,ana_len+1);
				
			LOGD("************Set_CurTime**********hour:%d min:%d sec:%d",hour,min,sec);
			proto_conver = 0x06;
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4]+hour*3600+min*60+sec;
			int hour1=buf1/3600;
			int min1=(buf1%3600)/60;
			if(hour1 >= 24)
				hour1 = hour1%24;
			ana_len=2+1;
			memcpy(buf+1,&hour1,1);
			memcpy(buf+2,&min1,1);
			LOGD("*********0x0chour1***%d",hour1);
			LOGD("**********0x0cmin1***%d",min1);
		}
			break;
		case 0x0b:
		{
			int buf1 = (buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4])*10;//dm
			proto_conver = 0x02;
			ana_len=4+1;	
			memcpy(buf+1,&buf1,4);
			LOGD("**********0x0b***%d",buf1);
		}
			break;
		case 0x0c:
			break;
		case 0x0d:
		{
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];
			LOGD("**********0x0d***%d",buf1);
			switch(buf1)
			{
				case 0:
					buf1 = 0;
				break;
				case 45:
					buf1 = 2;
				break;
				case 90:
					buf1 = 4;
				break;
				case 135:
					buf1 = 6;
				break;
				case 180:
					buf1 = 8;
				break;
				case 225:
					buf1 = 10;
				break;
				case 270:
					buf1 = 12;
				break;
				case 315:
					buf1 = 14;
				break;
				default:
				{
					if(buf1 > 0 && buf1 < 45)
					{
						buf1 = 1;
					}
					else if(buf1 > 45 && buf1 < 90)
					{
						buf1 = 3;
					}
					else if(buf1 > 90 && buf1 < 135)
					{
						buf1 = 5;
					}
					else if(buf1 > 135 && buf1 < 180)
					{
						buf1 = 7;
					}
					else if(buf1 > 180 && buf1 < 225)
					{
						buf1 = 9;
					}
					else if(buf1 > 225 && buf1 < 270)
					{
						buf1 = 11;
					}
					else if(buf1 > 270 && buf1 < 315)
					{
						buf1 = 13;
					}
					else if(buf1 > 315 && buf1 < 360)
					{
						buf1 = 15;
					}
				}
				break;
			}
			proto_conver = 0x00;
			ana_len=1+1;
			memcpy(buf+1,&buf1,1);
			LOGD("**********0x0d***%d",buf1);
		}
			break;
		case 0x0e:
			break;
		case 0x0f:
			break;
		case 0x10:
		{
			proto_conver = 0x0C;
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];//km/h
			ana_len=1+1;
			memcpy(buf+1,&buf1,1);
			LOGD("**********0x10***%d",buf1);
		}
			break;
		case 0x11:
			break;
		case 0x12:
			break;
		case 0x13:
			break;
		case 0x14:
			break;
		case 0x15:
		{
			proto_conver = 0x05;
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];//m
			ana_len=4+1;
			memcpy(buf+1,&buf1,4);
			LOGD("**********0x15***%d",buf1);
		}
			break;
		case 0x16:
		{
			LOGD("************Set_CurTime**********hour:%d min:%d sec:%d",hour,min,sec);
			proto_conver = 0x07;
			int buf1 = buf[1]*256*256*256+buf[2]*256*256+buf[3]*256+buf[4];//s
			int hour1=buf1/3600;
			int min1=(buf1%3600)/60;
			ana_len=2+1;
			memcpy(buf+1,&hour1,1);
			memcpy(buf+2,&min1,1);
			LOGD("**********0x16hour1***%d",hour1);
			LOGD("**********0x16min1***%d",min1);
		}
			break;
		case 0x17:
			break;
		case 0x18:
			break;
		case 0x19:
			break;
		case 0x21:
		{
			proto_conver = 0xf0;
		}
			break;
		case 0x22:
			proto_conver = 0x03;
			break;
		case 0x88:
		{
			proto_conver = 0x88;
		}
		break;
		case 0x89:
		{
			proto_conver = 0x89;
		}
		break;
		default:break;
	}
	
	if(proto_conver == 0xFF)
		return;
	
	u8 pBuffer[ana_len+1];
	memset(pBuffer,0,sizeof(pBuffer));
	pBuffer[0]=0xB0;
	pBuffer[1]=proto_conver;
	memcpy(&pBuffer[2],buf+1,ana_len-1);
	makeAndSendMessageToHal(HAL_ID_EXDISPLAY,pBuffer,ana_len+1);
	
}




















