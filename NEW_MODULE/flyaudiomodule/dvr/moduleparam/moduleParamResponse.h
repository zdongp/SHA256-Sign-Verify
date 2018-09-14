#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__


#define  BACK2RECORD	'I'		//0x49 //���ص�¼��ģʽ
#define  DVR_RECORD		'O'		//0x4F // ¼��ȡ��¼��
#define  MUTE			'V'		//0x56// ¼��������
#define  FILE_PLAYBACK	'Z'		// 0x5A  //�ļ��ط�
#define  LOCK_FILE		'H'		//�ļ�����
#define  VIDEO_SET		'C'		//0x43 //���롢�����˳��˵�����
#define  TIME_SET       'G'		// ���롢�����˳�ʱ������

#define SET_ENSURE			 'E'		//ʱ�������һ��
#define PLAY				 'B'		//0x42// ���š���ͣ
#define PAUSE				 0x53		//��ͣ ������S ����

#define DELETE_Voide		 0x51		// ɾ��
#define PREV				 0x4C		// ��һ������һ��¼��
#define NEXT				 0x52		// ��һ������һ��¼��


#define SAVE_SET			 'I'		  //�������� ����¼��ģʽ
#define UP					0x44		  // ���ϡ��佹
#define DOWN				0x4A		  // ���¡��佹

#define DetectingMode		 0x4D		  // ģʽ���
#define VideoMode			 0x00		  //¼��ģʽ
#define RePlayMode			 0x01		  //�ط�ģʽ���ļ������
#define SetTimeMode			 0x02		  //ʱ������ģʽ
#define SetVideoMode		 0x03		  //ʱ������ģʽ

void moduleParameterInit(void);
void moduleParameterDeInit(void);
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);
void initByConfig(void);
void SetDefaultParam();
void moduleParameterReInit(void);
int module_extendInterface(char *buffer, int len);
void init_Camera_Recording(u8 state);

#endif
