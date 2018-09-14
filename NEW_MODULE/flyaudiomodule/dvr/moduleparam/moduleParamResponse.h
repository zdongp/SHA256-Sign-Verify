#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__


#define  BACK2RECORD	'I'		//0x49 //返回到录制模式
#define  DVR_RECORD		'O'		//0x4F // 录像、取消录像
#define  MUTE			'V'		//0x56// 录音、静音
#define  FILE_PLAYBACK	'Z'		// 0x5A  //文件回放
#define  LOCK_FILE		'H'		//文件加锁
#define  VIDEO_SET		'C'		//0x43 //进入、保存退出菜单设置
#define  TIME_SET       'G'		// 进入、保存退出时间设置

#define SET_ENSURE			 'E'		//时间进入下一项
#define PLAY				 'B'		//0x42// 播放、暂停
#define PAUSE				 0x53		//暂停 不能用S 代替

#define DELETE_Voide		 0x51		// 删除
#define PREV				 0x4C		// 上一曲（上一个录像）
#define NEXT				 0x52		// 下一曲（下一个录像）


#define SAVE_SET			 'I'		  //保存设置 返回录像模式
#define UP					0x44		  // 向上、变焦
#define DOWN				0x4A		  // 向下、变焦

#define DetectingMode		 0x4D		  // 模式检测
#define VideoMode			 0x00		  //录制模式
#define RePlayMode			 0x01		  //回放模式（文件浏览）
#define SetTimeMode			 0x02		  //时间设置模式
#define SetVideoMode		 0x03		  //时间设置模式

void moduleParameterInit(void);
void moduleParameterDeInit(void);
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);
void initByConfig(void);
void SetDefaultParam();
void moduleParameterReInit(void);
int module_extendInterface(char *buffer, int len);
void init_Camera_Recording(u8 state);

#endif
