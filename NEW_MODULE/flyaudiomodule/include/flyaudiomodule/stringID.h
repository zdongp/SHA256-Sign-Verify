#ifndef __STRING_ID_H__
#define __STRING_ID_H__


#define STRINGID_RADIO_INPUT_NUMBER                 0x00040101/* ������Ƶ��Ƶ��*/
#define STRINGID_RADIO_INPUT_ERROR 					0x00040102/* ��������ȷ��Ƶ��*/


/* For BLUETOOTH */
#define STRINGID_BT_INPUT_PHONE_NUMBER				0x00090001  /* 请输入电话号码 */
#define STRINGID_BT_NOTICE_TEXT						0x00090002  /* 提示 */
#define STRINGID_BT_SEARCHES_DEVICES				0x00090003  /* 请用手机搜索蓝牙设备 */
#define STRINGID_BT_DEVICES_NAME					0x00090004  /* 设备名称 */
#define STRINGID_BT_PASSWORD						0x00090005  /* 密码 */
#define STRINGID_BT_CALL_IN							0x00090006  /* 去电中... */
#define STRINGID_BT_CALL_OUT						0x00090007  /* 来电中... */
#define STRINGID_BT_UPGRADE                         0x00090008	/*蓝牙升级*/
#define STRINGID_BT_NO_FUNTION                      0x00090009	/*该手机不支持此功能*/
#define STRINGID_BT_UPDATE_READY                    0x00090010	//准备升级
#define STRINGID_BT_UPDATE_UPGRADING                0x00090011	//正在升级中
#define STRINGID_BT_UPDATE_ERROR                    0x00090012	//升级出错
#define STRINGID_BT_UPDATE_COMPLETE                 0x00090013	//升级完成
#define STRINGID_BT_UPDATE_NOT_DETECTED             0x00090014	//没有检测到有蓝牙升级
#define STRINGID_BT_DELETE_ALL                      0x0009000A	/*全部删除*/
#define STRINGID_BT_OK                        		0x0009000B	/*确定*/
#define STRINGID_BT_CANCEL                        	0x0009000C	/*取消*/
#define STRINGID_BT_UNKONW_NUMBER					0x0009000D	//未知来电
//20140723parrot
#define STRINGID_BT__DEVICE_DELETE_ALL              0x0009000E
#define STRINGID_BT__DEVICE_DELETE_ONE              0x0009000F
#define STRINGID_BT__DEVICE_FIRST_DISCONNECT        0x0009001A
//�ؼ�ID=0x090a14
#define STRINGID_BT__DEVICE_DELETE_DEVICE_ERROR 	0x0009001B //Delete device error
#define STRINGID_BT__DEVICE_CONNECTED_DEVICES       0x0009001C//Connected devices  
#define STRINGID_BT__DEVICE_DEVICE_IS_DISCONNECTED  0x0009001D//Device is disconnected
#define STRINGID_BT__DEVICE_CONNECTING_TO_DEVICE    0x0009001F//Connecting to device  
#define STRINGID_BT__DEVICE_CONNECTION_FAILED       0x0009002A//Connection Failed 
#define STRINGID_BT__DEVICE_DEVICE_NOT_FOUND        0x0009002B//Device not Found 
//�ؼ�ID=0x090711
#define STRINGID_BT__DEVICE_INQUIRING               0x0009002C//Inquiring...
#define STRINGID_BT__DEVICE_DEVICES_FOUND           0x0009002D// Devices Found(%d) 
#define STRINGID_BT__DEVICE_INQUIRY_TERMINATES_DEVICES_FOUND    0x0009002E// Inquiry terminates,Devices Found(%d)
#define STRINGID_BT__DEVICE_INQUIRY_ERROR_PLEASE_RETRY_LATER	0x0009002F//Inquiry error,please retry later! 
#define STRINGID_BT__DEVICE_REFLESH_ERROR_BUSY_RETRY_LATER	0x00090701//Reflesh error,device busy,please retry later! 

#define STRINGID_BT__DEVICE_ALREADY_PAIRED      0x0009003A//The device is already paired! Whether you need to connect?
#define STRINGID_BT__DEVICE_TURNED_OFF      	0x0009004A//Bluetooth device is turned off,please turn on it!

#define STRINGID_BT__PARAM_MIC1       0x00090B00
#define STRINGID_BT__PARAM_MIC2       0x00090B01
#define STRINGID_BT__PARAM_MIC3       0x00090B02

#define STRINGID_BT__DEVICE_CALL_LOG_LOADING 0x00090A21
#define STRINGID_BT__DEVICE_CONTACTS_LOADING 0x00090831

#define STRINGID_BT__DEVICE_MANYPEOPLECALL_WAITING 0x00090051
#define STRINGID_BT__DEVICE_MANYPEOPLECALL_DIALED  0x00090052
#define STRINGID_BT__DEVICE_PAIRING_CONNECTION_BEGIN 0x00090053 //Pairing connection...
#define STRINGID_BT__DEVICE_PAIRING_CONNECTION_ERROR 0x00090054 //Pairing connection failed!
#define STRINGID_BT__DEVICE_CONNECTED_DEVICES_THE_LARGEST_1  0x00090055 //The current number of connected devices has been the largest,
#define STRINGID_BT__DEVICE_CONNECTED_DEVICES_THE_LARGEST_2  0x00090056 //please disconnect one of the reconnection.



//dvd osd
#define STRINGID_DVD_VIDEO_CONTROL_MAINMENU			0x00050501  /* 主菜单 */
#define STRINGID_DVD_VIDEO_CONTROL_MENU				0x00050502  /* 菜单 */
#define STRINGID_DVD_VIDEO_CONTROL_AUDIO			0x00050503  /* 音频 */
#define STRINGID_DVD_VIDEO_CONTROL_SUBTITLE			0x00050504  /* 字幕 */
#define STRINGID_DVD_VIDEO_CONTROL_SET				0x00050505  /* 设置 */
#define STRINGID_TPMS_TEMPERATURE_UNITS_C           0x00060100	//温度单位	
#define STRINGID_TPMS_TEMPERATURE_UNITS_F           0x00060101	//温度单位	
#define STRINGID_TPMS_PRESSURE_UNITS_KPA            0x00060102	//压力单位	
#define STRINGID_TPMS_PRESSURE_UNITS_PSI            0x00060103	//压力单位	
#define STRINGID_TPMS_RING                      	0x00060104	
#define STRINGID_TPMS_OFF                        	0x00060105	
#define STRINGID_TPMS_TEXTWARNING                   0x00060106	
#define STRINGID_TPMS_MAIN_FL_LOWBATTERY			0x00060110
#define STRINGID_TPMS_MAIN_FR_LOWBATTERY			0x00060111
#define STRINGID_TPMS_MAIN_RL_LOWBATTERY			0x00060112
#define STRINGID_TPMS_MAIN_RR_LOWBATTERY			0x00060113
#define STRINGID_TPMS_MAIN_FL_TEMPERATURE_ALARM		0x00060114
#define STRINGID_TPMS_MAIN_FR_TEMPERATURE_ALARM		0x00060115
#define STRINGID_TPMS_MAIN_RL_TEMPERATURE_ALARM		0x00060116
#define STRINGID_TPMS_MAIN_RR_TEMPERATURE_ALARM		0x00060117
#define STRINGID_TPMS_MAIN_FL_TIRE_PRESSURE_HIGHT	0x00060118
#define STRINGID_TPMS_MAIN_FR_TIRE_PRESSURE_HIGHT	0x00060119
#define STRINGID_TPMS_MAIN_RL_TIRE_PRESSURE_HIGHT	0x0006011A
#define STRINGID_TPMS_MAIN_RR_TIRE_PRESSURE_HIGHT	0x0006011B
#define STRINGID_TPMS_MAIN_FL_TIRE_PRESSURE_LOW		0x0006011C
#define STRINGID_TPMS_MAIN_FR_TIRE_PRESSURE_LOW		0x0006011D
#define STRINGID_TPMS_MAIN_RL_TIRE_PRESSURE_LOW		0x0006011E
#define STRINGID_TPMS_MAIN_RR_TIRE_PRESSURE_LOW		0x0006011F

#define STRINGID_TPMS_PRESSURE_UNITS_BAR            			0x00060120

//sync butten
#define STRINGID_SYNC_MENU_PLAY 					0x0030010b
#define STRINGID_SYNC_MENU_PAUSE					0x0030010c
#define STRINGID_SYNC_MENU_MUTE 					0x0030010d


// system
// car info
#define STRINGID_CAR_INFO_HAND_LOCKER_CLOSE				0x00200132
#define STRINGID_CAR_INFO_HAND_LOCKER_OPEN				0x00200133						
#define STRINGID_CAR_INFO_OPEN							0x00200130
#define STRINGID_CAR_INFO_CLOSE							0x00200131
#define STRINGID_CAR_INFO_FOOT_STEP_ON					0x00200134
#define STRINGID_CAR_INFO_FOOT_STEP_OUT					0x00200135
#define STRINGID_CAR_INFO_CLEAN_WATER_NORMAL			0x00200136
#define STRINGID_CAR_INFO_CLEAN_WATER_NON				0x00200137

#define STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_HIGH	0x00020102
#define STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_MID	0x00020103
#define STRINGID_SYSTEM_SETTING_VOLTAGE_PROTECTION_LOW	0x00020104

#define STRINGID_SYSTEM_SETTING_FAN_SHUTDOWN_MOD 		0x00020105
#define STRINGID_SYSTEM_SETTING_FAN_SHUTOPEN_MOD 		0x00020106
#define STRINGID_SYSTEM_SETTING_FAN_PERFORMANCE_MOD 	0x00020107
#define STRINGID_SYSTEM_SETTING_FAN_AUTO_MOD 			0x00020108
#define STRINGID_SYSTEM_BACKCAR_MODE_NORMAL				0x20109
#define STRINGID_SYSTEM_BACKCAR_MODE_FAST				0x2010a

#define STRINGID_SYSTEM_SETUP_THIRD_PARTY_DAIL_OPTION_3G 	0x022101
#define STRINGID_SYSTEM_SETUP_THIRD_PARTY_DAIL_OPTION_BT 	0x022102


#define STRINGID_CAR_INFO_ELECTRONIC_BOOSTER_COMFORTABLE_MODE				0x203a0100
#define STRINGID_CAR_INFO_ELECTRONIC_BOOSTER_MOVE_MODE							0x203a0101

#define STRINGID_CAR_INFO_REMOTE_CONTROL_LOCK_RING								0x203a0400
#define STRINGID_CAR_INFO_REMOTE_CONTROL_LOCK_NO_RING							0x203a0401

//zhq add setup backcar trigger
#define STRINGID_SYSTEM_SETUP_BACKCAR_TRIGGER_AUTOMATIC	0x0002010b
#define STRINGID_SYSTEM_SETUP_BACKCAR_TRIGGER_PROTOCOL	0x0002010c
#define STRINGID_SYSTEM_SETUP_BACKCAR_TRIGGER_LEVEL	    0x0002010d


#define STRINGID_SYSTEM_SETUP_BACKCAR_PROTOCOL_CVBS	0x00021500 //CVBS
#define STRINGID_SYSTEM_SETUP_BACKCAR_PROTOCOL_USB	   	0x00021501 //USB

#define STRINGID_SYSTEM_SETUP_DVR_IS_PROTOCOL_MODE	    	0x00021521
#define STRINGID_SYSTEM_SETUP_DVR_NO_PROTOCOL_MODE	    	0x00021522


// GOLF -->

//0520ŒÓ ÖØÖÃ×Ö·ûŽ®
#define STRING_CARINFO_GOLD_START                     	0x202000 //×ÔÆô¶¯Æð
#define STRING_CARINFO_GOLD_REFUELING                 	0x202001 //×ÔŒÓÓÍÆð
#define STRING_CARINFO_GOLD_LONG                      	0x202002 //³€Ê±Œä

#define	STRING_SET_TV_OR_TPMS							0x202003
#define	STRING_SET_DVR									0x202004
#define STRING_ID_DNV_NAME								0x202005
#define STRING_ID_LED								    0x21b02

#define CARINFO_GOLD_SETUP_INIT_NA                      0x202020 // N/A
#define STRING_CARINFO_DATA_UNKNOW                   	0x202021 // --

//0607 ±£ÑøÒ³
#define CARINFO_GOLD_MAINTAIN_EXCEED_DAYS 				0x202100
#define CARINFO_GOLD_MAINTAIN_REMAIN_DAYS 				0x202101
#define CARINFO_GOLD_MAINTAIN_EXCEED_MILEAGE 			0x202102
#define CARINFO_GOLD_MAINTAIN_REMAIN_MILEAGE 			0x202103
#define CARINFO_GOLD_MAINTAIN_EXCEED_MAINTENANCE_DYAS 	0x202104
#define CARINFO_GOLD_MAINTAIN_REMAIN_MAINTENANCE_DYAS 	0x202105
#define CARINFO_GOLD_MAINTAIN_EXCEED_MAINTENANCE_MILEAGE 0x202106
#define CARINFO_GOLD_MAINTAIN_REMAIN_MAINTENANCE_MILEAGE 0x202107

//³µŸà£º
#define   STRING_CARINFO_GOLD_SETUP_CAR_DISTANT_1        0x202400      // Œ«Ð¡
#define   STRING_CARINFO_GOLD_SETUP_CAR_DISTANT_2        0x202401       //  Ð¡
#define   STRING_CARINFO_GOLD_SETUP_CAR_DISTANT_3        0x202402       // ÖÐµÈ
#define   STRING_CARINFO_GOLD_SETUP_CAR_DISTANT_4        0x202403        //Žó
#define   STRING_CARINFO_GOLD_SETUP_CAR_DISTANT_5        0x202404        // Œ«Žó
//ÐÐÊ»³ÌÐò£º
#define   STRING_CARINFO_GOLD_SETUP_DRVING_PROGRAM_1     0x202405      //Ÿ­ŒÃ
#define   STRING_CARINFO_GOLD_SETUP_DRVING_PROGRAM_2     0x202406     //±ê×Œ
#define   STRING_CARINFO_GOLD_SETUP_DRVING_PROGRAM_3     0x202407     //ÔË¶¯
//œÓÍšÊ±Œä£º
#define   STRING_CARINFO_GOLD_SETUP_CONNEC_TIME_1        0x202700  //ÌáÇ°
#define   STRING_CARINFO_GOLD_SETUP_CONNEC_TIME_2        0x202701  //ÊÊÊ±
#define   STRING_CARINFO_GOLD_SETUP_CONNEC_TIME_3        0x202702  //ÑÓºó
//ÂÃÐÐÄ£Êœ£º
#define   STRING_CARINFO_GOLD_SETUP_DRVING_SIDE_1        0x202703     //¿¿ÓÒÐÐÊ»
#define   STRING_CARINFO_GOLD_SETUP_DRVING_SIDE_2        0x202704     //¿¿×óÐÐÊ»

//Boot up and is running navigation
#define   STRING_CARINFO_GOLD_SETUP_RUNNING_NAVIGATION_YES    0x202705 
#define   STRING_CARINFO_GOLD_SETUP_RUNNING_NAVIGATION_NO     0x202706
#define   STRING_CARINFO_GOLD_SETUP_RUNNING_NAVIGATION_AUTO   0x202707

#define STRING_CARINFO_GOLD_SETUP_DISTANCE_KM		0x202901
#define STRING_CARINFO_GOLD_SETUP_DISTANCE_MI		0x202902
#define STRING_CARINFO_GOLD_SETUP_SPEED_KM_H		0x202903
#define STRING_CARINFO_GOLD_SETUP_SPEED_MP_H		0x202904

//³µŽ°±ãœÝ¿ªÆô£º
#define   STRING_CARINFO_GOLD_SETUP_CARWINDOW_OPEN_1     0x202b00    //ŒÝÊ»Ô±²à³µŽ°
#define   STRING_CARINFO_GOLD_SETUP_CARWINDOW_OPEN_2     0x202b01    //È«²¿³µŽ°
#define   STRING_CARINFO_GOLD_SETUP_CARWINDOW_OPEN_3     0x202b02    //  ¹Ø±Õ
//ÖÐÑëÃÅËø£º
#define   STRING_CARINFO_GOLD_SETUP_DOOR_LOCK_1          0x202b03   //µ¥žö³µÃÅ
#define   STRING_CARINFO_GOLD_SETUP_DOOR_LOCK_2          0x202b04    //È«²¿³µÃÅ
#define   STRING_CARINFO_GOLD_SETUP_DOOR_LOCK_3          0x202b05    // ³µÁŸ²à

#define CARINFO_GOLD_SETUP_RESET_ALL                     0x202e00                //žŽÎ»ËùÓÐÉèÖÃ?
#define CARINFO_GOLD_SETUP_RESET_CAR_LIGHT               0x202e01                //ÖØÖÃ³µµÆ?
#define CARINFO_GOLD_SETUP_RESET_ONOFF                   0x202e02                //ÖØÖÃŽò¿ªºÍ¹Ø±Õ?
#define CARINFO_GOLD_SETUP_RESET_PARKING_AND_DISPATCH    0x202e03                //ÖØÖÃ×€³µºÍµ÷³µ?
#define CARINFO_GOLD_SETUP_RESET_MULTIFUNCTION_DISPLAY   0x202e04              //ÖØÖÃ¶à¹ŠÄÜÏÔÊŸ?
#define CARINFO_GOLD_SETUP_RESET_DRIVER_AUXILIARY_SYSTEMS 0x202e05             //ÖØÖÃŒÝÊ»Ô±žšÖúÏµÍ³?
#define CARINFO_GOLD_SETUP_RESET_DRVING_DATA_FROM_START   0x202e06              //ÖØÖÃ¡°×ÔÆô¶¯ÒÔºó¡±µÄÐÐÊ»ÊýŸÝ?
#define CARINFO_GOLD_SETUP_RESET_DRVING_DATA_FROM_LONGTIME   0x202e07          //ÖØÖÃ¡°³€Ê±Œä¡±µÄÐÐÊ»ÊýŸÝ?
#define CARINFO_GOLD_SETUP_RESET_BACK_MIRROR_AND_WINDOWSHIELD_WIPER  0x202e08  //ÖØÖÃºóÊÓŸµºÍ¹ÎË®Æ÷?

// GOLF <!--

//NEW CAMRY
//��������ҳ��ƴ�������
#define STRING_CARINFO_HEADLIGHT_OPENSENSITIVITY_WEAKEST 0x203300 //  ����          
#define STRING_CARINFO_HEADLIGHT_OPENSENSITIVITY_WEAK 0x203301 //  �� 
#define STRING_CARINFO_HEADLIGHT_OPENSENSITIVITY_MODERATE 0x203302//   ����         
#define STRING_CARINFO_HEADLIGHT_OPENSENSITIVITY_STRONG 0x203303 //  ǿ
#define STRING_CARINFO_HEADLIGHT_OPENSENSITIVITY_MOST 0x203304 //  ��ǿ  
#define STRING_CARINFO_INTERIORLIGHTS_TIMER_7_5 0x203305  // 7.5S 
#define STRING_CARINFO_INTERIORLIGHTS_TIMER_15 0x203306  // 15S          
#define STRING_CARINFO_INTERIORLIGHTS_TIMER_30 0x203307  // 30S
#define STRING_CARINFO_INTERIORLIGHTS_TIMER_CLOSE 0x203308  // �ر� 

#define STRING_CARINFO_DOORUNLOCK_ALL 0x203309  // ȫ������
#define STRING_CARINFO_DOORUNLOCK_DRIVER 0x20330a  // ��ʻԱ���� 

#define STRING_CARINFOR_OIL_CONSUMPTION_ALARM_NORMAR 0x203603
#define STRING_CARINFOR_OIL_CONSUMPTION_ALARM_WARNING  0x203604

#define STRING_CAR_DRTVING_MOD_COMFORT 0x204000
#define STRING_CAR_DRTVING_MOD_STANDARD 0x204001
#define STRING_CAR_DRTVING_MOD_SPORT 0x204002
#define STRING_CAR_DRTVING_MOD_LOW_OIL 0x204003

#define STRING_CAR_AMBIENT_LED_COLOR_CLOSE 0x021c00
#define STRING_CAR_AMBIENT_LED_COLOR_ORANGE 0x021c03
#define STRING_CAR_AMBIENT_LED_COLOR_RED 0x021c04
#define STRING_CAR_AMBIENT_LED_COLOR_SOFT_BLUE 0x021c05
#define STRING_CAR_AMBIENT_LED_COLOR_ICE_BLUE 0x021c06
#define STRING_CAR_AMBIENT_LED_COLOR_BLUE 0x021c07
#define STRING_CAR_AMBIENT_LED_COLOR_VIDLET 0x021c08
#define STRING_CAR_AMBIENT_LED_COLOR_GREEN 0x021c09

/*PAGE_SYSTEM_SET_SELECTION_CAR_TYPE_PAGE*/
#define STRING_CONTROLID_SELECTION_CAR_TYPE_855A11	0x022311
#define STRING_CONTROLID_SELECTION_CAR_TYPE_855A12	0x022312
#define STRING_CONTROLID_SELECTION_CAR_TYPE_855A13	0x022313
#define STRING_CONTROLID_SELECTION_CAR_TYPE_855A14	0x022314
#define STRING_CONTROLID_SELECTION_CAR_TYPE_855A15	0x022315
#define STRING_CONTROLID_SELECTION_CAR_TYPE_855A16	0x022316
#define STRING_CONTROLID_SELECTION_CAR_TYPE_855A17	0x022317


// dnv

#define DNV_BOX_CHECK_DELETE_CUR_FILE 0x00500001
#define DNV_BOX_CHECK_FORMAT_TF_CARD 0x00500002
#define DNV_TIP_BEGIN_DELETE_CUR_FILE 0x00500003
#define DNV_TIP_DELETE_CUR_FILE_FINISH 0x00500004
#define DNV_TIP_BEGIN_FORMAT_TF_CARD   0x00500005
#define DNV_TIP_FORMAT_TF_CARD_FINISH 0x00500006
#define DNV_TIP_OPERATION_FAIL 0x00500007

//DVR
#define STRING_DRIVING_USB_CAREMA_SET_RESOLUTION_720P  0x00400700
#define STRING_DRIVING_USB_CAREMA_SET_RESOLUTION_1080P  0x00400701
#define STRING_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_2MIN  0x00400702
#define STRING_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_3MIN  0x00400703
#define STRING_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_5MIN  0x00400704
#define STRING_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_10MIN  0x00400705
#define STRING_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_2G  0x00400706
#define STRING_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_4G  0x00400707
#define STRING_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_8G  0x00400708
#define STRING_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_16G  0x00400709

#define STRING_DRIVING_USB_CAREMA_SWITCH_ROAD_SINGLE 0x400711
#define STRING_DRIVING_USB_CAREMA_SWITCH_ROAD_DOUBLE 0x400712
#define STRING_DRIVING_USB_CAREMA_SWITCH_ROAD_EMERGENCY_COLLISION 0x400713

#define STRING_DRIVING_USB_CAREMA_FORMAT_CARD_WHETHER 0x400714
#define STRING_DRIVING_USB_CAREMA_FORMAT_CARD_NO_SD 0x400715
#define STRING_DRIVING_USB_CAREMA_FORMAT_CARD_DOING 0x400716
#define STRING_DRIVING_USB_CAREMA_FORMAT_CARD_DONE 0x400717
#define STRING_DRIVING_USB_CAREMA_FORMAT_CARD_ERROR 0x400718



//RADIO
#define STRINGID_RADIO_OPEN 		0x0040001
#define STRINGID_RADIO_CLOSE 	0x0040002



				
//PAGE_PARALLEL_PARK_PAGE					0x0707	
//PAGE_PERPENDICULAR_PARK_PAGE				0x0708
#define STRINGID_PARK_SCANING_PARKING_SPOT_LEFT_SIDE 	0x070701
#define STRINGID_PARK_SCANING_PARKING_SPOT_RIGHT_SIDE 	0x070702
#define STRINGID_PARK_SPOT_FOUND 				0x070703	
#define STRINGID_PARK_DRIVE_FORWORD 			0x070704	
#define STRINGID_PARK_SELECT_LEFT_SIDE_SCANING  0x070705	
#define STRINGID_PARK_SELECT_RIGHT_SIDE_SCANING 0x070706
#define STRINGID_PARK_STOP_VEHICLE 				0x070707	
#define STRINGID_PARK_REMOVE_HANDS_SHIFT_TO_REVERSE 0x070708

//PAGE_PARK_OUT_ASSIST_PAGE	
#define STRINGID_PARK_SELECT_SIDE_PARKING_SPOT 	0x070901
#define STRINGID_PARK_LEFT_SIDE 				0x070902	
#define STRINGID_PARK_RIGHT_SIDE 				0x070903
#define STRINGID_PARK_REMOVE_HANDS 				0x070904
#define STRINGID_PARK_SHIFT_TO_REVERSE 			0x070905	
#define STRINGID_PARK_SHIFT_TO_DRIVE_FORWORD 	0x070906

//PAGE_PARALLEL_PARK_PAGE_VIDEO	
#define STRINGID_PARK_PARALLEL_PARK 	 0x070521	
#define STRINGID_PARK_PERPENDICULAR_PARK 0x070522	
#define STRINGID_PARK_OUT_ASSIST_PARK 	 0x070523	
#define STRINGID_PARK_ACTIVE_PARK_VIDEO  0x070524	
#define STRINGID_PARK_STOP_VEHICLE_REMOVE_HANDS  0x070525	
#define STRINGID_PARK_REVERSING_READY_STOP_VEHICLE 0x070526	
#define STRINGID_PARK_STOP_VEHICLE_SHIFT_TO_DRIVE_FORWORD   0x070527	
#define STRINGID_PARK_STOP_VEHICLE_SHIFT_TO_REVERSE  0x070528	
#define STRINGID_PARK_FINISHED  					 0x070529	
#define STRINGID_PARK_PAGE_VIDEO_REMOVE_HANDS_SHIFT_TO_REVERSE	 0x07052a	
#define STRINGID_PARK_REMOVE_HANDS_SHIFT_TO_DRIVE_FORWORD	 0x07052b	
#define STRINGID_PARK_REMOVE_DRIVING_FORWORD_READY_STOP_VEHICLE	 0x07052c	
#define STRINGID_PARK_REMOVE_PLEASE_CONTROL_THE_STEERING_WHEEL	 0x07052d	
#define STRINGID_PARK_REMOVE_PLEASE_GET_OUT_OF_THR_REVERSE_GEAR	 0x07052e	










#endif