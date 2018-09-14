#include "FlyJniSdkModuleRadio.h"

#include <stdio.h>
#include <stdlib.h>

CFlyJniSdkModuleRadio::CFlyJniSdkModuleRadio(void)
{
}

CFlyJniSdkModuleRadio::~CFlyJniSdkModuleRadio(void)
{
}

void CFlyJniSdkModuleRadio::getRadioMessage(u8 *p, u8 len)
{
	LOGD("[%s] cmd:%x", __FUNCTION__,p[0]);
	switch(p[0])
	{
		case 0x00:
			break;
		case 0x01:
			if( p[1] == 0)
			{
			g_mFreSection= 0x01; 
		       }
		       else{
			g_mFreSection= 0x00;
		       }	
			break;
		case 0x02:
			break;
	}

	switch(p[0])
	{
		case 0x00:
			onRadioPowerStatus( p[1]);
			break;
		case 0x01:
			onRadioFrequencySection( p[1]);
			break;
		case 0x02:
			onRadioFrequency(p,len);
			break;
	}
}

void CFlyJniSdkModuleRadio::getAppCtrlMessage(u8 *p, u8 len)
{
	LOGD("[%s] Module_radio cmd:%x", __FUNCTION__,p[0]);
	switch(p[0])
	{
	case 0x01:
		setToRadioPowerOn(p[1]);	
		break;
	case 0x02:
		setToRadioChannel(p[1]);
		break;
	case 0x03:
		setToRadioFrequencyOfChannel(p+1);
		break;
	case 0x04:
		setToRadioSensitivity(p[1]);
		break;
	case 0x05:
		if (p[1] == 0x00)
		{
			setToRadioStartScanFrequency(p[1]);
		}
		else if(p[1] == 0x01)
		{
			setToRadioNextStationScan(p[1]);
		}
		else if(p[1] == 0x02)
		{
			setToRadioPreStationScan(p[1])	;
		}
		break;
	case 0x06:
		break;
	case 0x07:
		break;
	case 0x08:
		if(p[1] == 0x00)
		{
			setToRadioPreFrequency(p[1]);//������������һƵ��
		}
		else if(p[1] == 0x01)
		{
			setToRadioNextFrequency(p[1]);//������������һƵ
		}
		break;
	}
}


void CFlyJniSdkModuleRadio::onRadioPowerStatus(u8 nStatus)				//��������Դ״̬����
{	
	LOGD("[%s] nStatus:%d",__FUNCTION__,nStatus);
	u8 status;
	if(nStatus == 1){
		status = 0x00;
	}
	else{
		status = 0x01;
	}
	u8 szMsg[2] = {0x01,status};
	setToFlyJniSdkService(MODULE_ID_RADIO, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModuleRadio::onRadioFrequencySection(u8 p)			//������Ƶ�μ���
{
	LOGD("[%s] p:%d",__FUNCTION__,p);
	if( p == 0){
		g_mFreSection= 0x01; 
	}
	else{
		g_mFreSection= 0x00;
	}
	u8 szMsg[2] = {0x02,g_mFreSection};
	setToFlyJniSdkService(MODULE_ID_RADIO, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModuleRadio::onRadioFrequency(u8* p,u8 len)				//��������ǰƵ�ʼ���
{	
	u8 szMsg[6] = {0};
	szMsg[0] = 0x03;
	szMsg[1] = g_mFreSection;
	szMsg[2] = *(p+2);
	szMsg[3] = *(p+1);
	u16 frenum = (((u16)szMsg[3])|(u16)szMsg[2]<<8);
	LOGD("[%s] g_mFreSection:%d frenum:%d",__FUNCTION__,g_mFreSection,frenum);
	setToFlyJniSdkService(MODULE_ID_RADIO, szMsg, sizeof(szMsg));
}

//������
void CFlyJniSdkModuleRadio::setToRadioPowerOn(u8 nStatus)				//�������������ص�Դ
{
	LOGD("[%s] nStatus:%d",__FUNCTION__,nStatus);
	u8 buf[2] = {0};
	buf[0] = 0x01;
	buf[1] = nStatus;
	
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_RADIO,buf,2);
}

void CFlyJniSdkModuleRadio::setToRadioNextStationScan(u8 nStatus)				//������������һ��̨
{
	LOGD("[%s] nStatus:%d",__FUNCTION__,nStatus);
	u8 buf[32] = {0};
	buf[0] = 0x02;
	buf[1] = nStatus;
	 makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_RADIO,buf,2);
}

void CFlyJniSdkModuleRadio::setToRadioPreStationScan(u8 nStatus)				//������������һ��̨
{
	LOGD("[%s] nStatus:%d",__FUNCTION__,nStatus);
	u8 buf[32] = {0};
	buf[0] = 0x03;
	buf[1] = nStatus;
	 makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_RADIO,buf,2);
}

void CFlyJniSdkModuleRadio::setToRadioStartScanFrequency(u8 p)		//��������ʼɨ��Ƶ��
{	
	LOGD("[%s] p:%d",__FUNCTION__,p);
	u8 buf[2] = {0};
	buf[0] = 0x04;
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_RADIO,buf,2);
}

void CFlyJniSdkModuleRadio::setToRadioPreFrequency(u8 nStatus)//������������һƵ��
{
	LOGD("[%s] nStatus:%d",__FUNCTION__,nStatus);
	u8 buf[32] = {0};
	buf[0] = 0x05;
	buf[1] = nStatus;
	 makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_RADIO,buf,2);

}

void CFlyJniSdkModuleRadio::setToRadioNextFrequency(u8 nStatus)//������������һƵ��
{
	LOGD("[%s] nStatus:%d",__FUNCTION__,nStatus);
	u8 buf[32] = {0};
	buf[0] = 0x06;
	buf[1] = nStatus;
	 makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_RADIO,buf,2);

}

void CFlyJniSdkModuleRadio::setToRadioChannel(u8 nStatus)	
{
	LOGD("[%s] nStatus:%d",__FUNCTION__,nStatus);
	u8 buf[2] = {0};
	buf[0] = 0x07;
	buf[1] = nStatus;
	
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_RADIO,buf,2);
}

void CFlyJniSdkModuleRadio::setToRadioFrequencyOfChannel(u8 *param)				//����������Ƶ��
{
	LOGD("[%s] param:%s",__FUNCTION__,param);
	u8 buf[6] = {0};
	buf[0] = 0x08;
	memcpy(&buf[1],param,5);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_RADIO,buf,6);
}

void CFlyJniSdkModuleRadio::setToRadioSensitivity(int p)				//����������������
{
	LOGD("[%s] p:%d",__FUNCTION__,p);
	u8 buf[2] = {0};
	buf[0] = 0x09;
	buf[1] = p;
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_RADIO,buf,2);
}


void CFlyJniSdkModuleRadio::setToRadioStopScanFrequency(int p)		//������ֹͣɨ��Ƶ��
{

}


/******************new pro*********************/
void CFlyJniSdkModuleRadio::analyseRadioAppMessageType(u8 *p, u8 len)
{
	LOGD("[%s]	p[0]:%x --p[1]:%x len:%x",__FUNCTION__,p[0],p[1],len);
	switch(p[0])
	{
		case RESPONE_CHANGE_STATE:
			analyseRadioInfoReturnStatusMassage(p+1, len - 1);
			break;
		case CONTROL_MESSAGE:
			analyseControlRadioOperationMassage(p+1, len - 1);
			break;
		default:break;
	}
}
void CFlyJniSdkModuleRadio::analyseRadioInfoReturnStatusMassage(u8 *buf ,u8 len)
{
	switch(buf[0])
	{
		case 0x00:
			{
				if(buf[1] == 0x00)
				{
					sendToRadioGetRadioInfo(0x01);
					sendToRadioGetRadioInfo(0x02);
				}
			}
			break;
		default:break;
	}
}
void CFlyJniSdkModuleRadio::analyseControlRadioOperationMassage(u8 *buf ,u8 len)
{
	switch(buf[0])
	{
		case 0x01:
			{
				if(buf[1] == 0x00||buf[1] == 0x01||buf[1] == 0x02)
					sendToRadioSetONorOFF(buf[1]);
			}
			break;
		case 0x02:
			if(buf[1] == 0x01 || buf[1] == 0x00)
			{
				sendToRadioSetFmOrAm(buf[1]);
			}
			break;
		case 0x03:
			{
				if(buf[1] == 0x00||buf[1] == 0x01)
				{
					sendToRadioSetFmOrAmAndValue(buf+1,3);
				}
			}
			break;
		case 0x04:
			sendToRadioSetRadioScan(buf[1]);
			break;
		default:break;
	}
}
void CFlyJniSdkModuleRadio::sendToRadioGetRadioInfo(u8 param)
{
	u8 buf[] = {0xfe,0x00, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_RADIO, buf, 3);
}


void CFlyJniSdkModuleRadio::sendToRadioSetONorOFF(u8 param)
{
	u8 buf[] = {0xfe,0x01, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_RADIO, buf, 3);
}
void CFlyJniSdkModuleRadio::sendToRadioSetFmOrAm(u8 param)
{
	u8 buf[] = {0xfe,0x02, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_RADIO, buf, 3);
}
void CFlyJniSdkModuleRadio::sendToRadioSetFmOrAmAndValue(u8 *param,int len)
{
	u8 buf[16] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x03;
	if(len > 14)
		len =14;
	memcpy(buf+2,param,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_RADIO, buf, len+2);
}
void CFlyJniSdkModuleRadio::sendToRadioSetRadioScan(u8 param)
{
	u8 buf[] = {0xfe,0x04, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_RADIO, buf, 3);
}

