#ifndef __PAGE_ID_H__
#define __PAGE_ID_H__

#define PAGE_BLACK 									0x0001
#define PAGE_STANDBY  								0x0002
#define PAGE_GPS_WAITING  							0x0003
#define PAGE_MENU 									0x000F

// MODULE_ID_AUDIOVIDEO 0x01
#define PAGE_EQ  									0x0100
#define PAGE_SOUND  								0x0101
#define PAGE_AUDIO_SET  							0x0102
#define PAGE_AUDIO_SET_BOX  						0x0103


//MODULE_ID_SYSTEM  0x02
#define PAGE_SETUP_BEGIN  							0x0201
//...
#define PAGE_SETUP_END  							0x020F
#define PAGE_COPYRIGHT  							0x0210
#define PAGE_SET_TIME  								0x0211
#define PAGE_SYSTEM_STYLE							0X0212
#define PAGE_SYSTEM_WHEEL_LEARNING 					0x0213


/*���ȵ���ҳ��*/
#define PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_ONE		0x0213
#define PAGE_SYSTEM_BRIGHTNESS_ADJUSTMENT 			0x0214
#define PAGE_SYSTEM_BACKVIDEO_REFLINE_SWITCH 		0x0215
#define PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_TWO		0x0216
#define PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_THREE		0x0217
#define PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_FOUR		0x0218
#define PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_FIVE		0x0219
#define PAGE_SYSTEM_SET_STEER_AUTOMATE_SWITCH_PAGE    0x021a
#define PAGE_SYSTEM_SET_AMBIENT_LED_PAGE		0x021b
#define PAGE_SYSTEM_SET_LED_RGB_PAGE		0x021c
#define PAGE_SYSTEM_SET_BACK_CAR_LINE_CHOOSE_PAGE    0x021d
//MultiContouredSeats
#define PAGE_MULTI_CONTOURED_SEATS_ADJUST	0x021e
#define PAGE_MULTI_CONTOURED_SEATS_MASSAGE	0x021f


/*����ƥ��ҳ��*/
#define PAGE_MATCHING_MODELS 	                    0x0220  

#define PAGE_SYSTEM_SET_COMMON_SECOND_PAGE			0x0221

#define PAGE_SYSTEM_SET_SOUND_CHANNEL_PAGE				0x0222
#define PAGE_SYSTEM_SET_SELECTION_CAR_TYPE_PAGE		0x0223

// MODULE_ID_KEY   0x03

// MODULE_ID_RADIO 0x04
#define PAGE_RADIO_MAIN  							0x0400

//#define PAGE_RADIO_SCAN  							0x0401
#define	PAGE_RADIO_NUMBER							0x0401   //输入频道 �?12.12.29�?

// MODULE_ID_DVD 0x05
#define PAGE_DVD_MAIN  								0x0500
#define PAGE_DVD_OPEN  								0x0501
#define PAGE_DVD_TRACKLIST  						0x0502
#define PAGE_DVD_FOLDER  							0x0503
#define PAGE_DVD_VIDEO  							0x0504
#define PAGE_DVD_VIDEO_CONTROL  					0x0505
#define PAGE_DVD_VIDEO_SET  						0x0506

// MODULE_ID_TPMS 0x06
#define PAGE_TPMS  									0x0600
#define PAGE_TPMS_SET  								0x0601
#define PAGE_TPMS_EXSET  							0x0602

// MODULE_ID_BACK 0x07
#define PAGE_BACK_NOVIDEO  							0x0700
#define PAGE_BACK_VIDEO								0x0701
#define PAGE_BACK_RADAR								0x0702
#define PAGE_BACK_FULL_VIDEO 	 					0x0703
#define PAGE_BACK_FULL_VIDEO_CONTROL 	 			0x0704
#define PAGE_PARALLEL_PARK_PAGE						0x0707
#define PAGE_PERPENDICULAR_PARK_PAGE				0x0708
#define PAGE_PARK_OUT_ASSIST_PAGE					0x0709
#define PAGE_BACK_VIDEO_T123COLORSET_PAGE			0x0710//

// MODULE_ID_TV 0x08
#define PAGE_TV_VIDEO  								0x0800
#define PAGE_TV_VIDEO_CONTROL  						0x0801
#define PAGE_TV_VIDEO_SET  							0x0802
#define PAGE_TV_NO_VIDEO 							0x0803

// MODULE_ID_BT 0x09
#define PAGE_BLUETOOTH_MAIN  						0x0900
#define PAGE_BLUETOOTH_RECORD  						0x0901
#define PAGE_BLUETOOTH_MOBILE_RECORD				0x0902
#define PAGE_BLUETOOTH_A2DP							0x0903
#define PAGE_BLUETOOTH_NO_A2DP						0x0904


#define PAGE_BLUETOOTH_AUDIOVOX_CODE	            0x0905//20140723parrot
#define PAGE_BLUETOOTH_AUDIOVOX_PAIR_FALSE	        0x0906
#define PAGE_BLUETOOTH_AUDIOVOX_SEARCH	            0x0907
#define PAGE_BLUETOOTH_AUDIOVOX_CONTACTS	        0x0908
#define PAGE_BLUETOOTH_AUDIOVOX_BEYBOARD	        0x0909
#define PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME	    0x090a
#define PAGE_BLUETOOTH_AUDIOVOX_PAIR_SETTING        0x090b
#define PAGE_BLUETOOTH_AUDIOVOX_BTNAME_EDITOR       0x090e
#define PAGE_BLUETOOTH_AUDIOVOX_KEYBOARD_HEBREW 	0x090f
#define PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_EGLISH 		0x0910
#define PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_ISRAEL		0x0911
#define PAGE_BLUETOOTH_AUDIOVOX_BTMIC_PARAM_SETPAGE		0x0913
#define PAGE_BLUETOOTH_PHONEPAIR		            0x0920

//BC8
#define PAGE_BLUETOOTH_PAIRING_DIALOG_BOX	0x0921
#define PAGE_BLUETOOTH_A2DP_MUSIC_BROWSING	0x0925
#define PAGE_BLUETOOTH_A2DP_MUSIC_NO_BROWSING	0x0926
#define PAGE_BLUETOOTH_CONNECTION_SWITCH_PAGE	0x0927
//ENGLISH AND ISRAEL RANK PAGE
#define PAGE_BLUETOOTH_PHONE_BOOK_ENGLISH_RANK_PAGE	0x0930
#define PAGE_BLUETOOTH_PHONE_BOOK_ISRAEL_RANK_PAGE	0x0931

//English rank phone book
#define PAGE_BLUETOOTH_PHONE_BOOK_ENGLISH_RANK_PAGE	0x0930
#define PAGE_BLUETOOTH_PHONE_BOOK_ISRAEL_RANK_PAGE	0x0931



// MODULE_ID_IPOD 0x0A
#define PAGE_IPOD  									0x0A00
#define PAGE_IPOD_SEARCH  							0x0A01

// MODULE_ID_MEDIA 0x0B
#define PAGE_MEDIA  								0x0B00
#define PAGE_MEDIA_SEARCH  							0x0B01

// MODULE_ID_BLCD 0x0C
#define PAGE_BLCD  									0x0C00

// MODULE_ID_AUX 0x0D
#define PAGE_AUX  									0x0D00
#define PAGE_AUX_VIDEO  							0x0D01
#define PAGE_AUX_VIDEO_CONTROL  					0X0D02
#define PAGE_AUX_VIDEO_SET  						0x0D03

//MODULE_ID_AC 0x10
#define PAGE_AIRCONDITION  							0x1000
#define PAGE_AIRCONDITION_SET  							0x1001


// MODULE_ID_GPS 0x11
#define PAGE_GPS_PAGE								0x1110

//MODULE_ID_EXTCAR 0x20
//#define PAGE_MAINTENANCE  						0x2000
#define PAGE_MAINTENANCE  							0x2000
#define PAGE_TEST_CARPAGE1                          0x2001
#define PAGE_TRAVEL_INFORMATION  					0x2001
#define PAGE_TRAVEL_INFORMATION_HISTORICAL_RECORD  	0x2002
#define PAGE_TRAVEL_INFORMATION_CAR_SET1  			0x2003
#define PAGE_TRAVEL_INFORMATION_COMFORTABLE_CONVENIENT_SET  	0x2004

//-->golf car
//#define PAGE_GOLF_CARINFO_MIAN
#define PAGE_GOLF_DRIVING_DATA                                                0x2020//                                                                  ÐÐÊ»ÊýŸÝÒ³
#define PAGE_GOLF_MAINTANIN                                                   0x2021//                                                                       ±£ÑøÒ³
#define PAGE_GOLF_SETUP                                                       0x2022//                                                                                 ÉèÖÃÒ³Ö÷Ò³
#define PAGE_GOLF_SETUP_ECS_SYSTEM                                            0x2023//                                                              ECSÏµÍ³žšÖúºÍÂÖÌ¥Ò³
#define PAGE_GOLF_SETUP_PILOT_PREV                                            0x2024//                                                                  ŒÝÊ»Ô±žšÖúÏµÍ³µÄÉÏÒ»Ò³
#define PAGE_GOLF_SETUP_PILOT_NEXT                                            0x2025//                                                                 ŒÝÊ»Ô±žšÖúÏµÍ³µÄÏÂÒ»Ò³
#define PAGE_GOLF_SETUP_PARKING                                               0x2026//                                                                       ×€³µºÍµ÷³µÒ�?
#define PAGE_GOLF_SETUP_LIGHT_PREV                                            0x2027//                                                                 µÆ¹âµÄÉÏÒ»Ò³
#define PAGE_GOLF_SETUP_LIGHT_NEXT                                            0x2028//                                                                  µÆ¹âµÄÏÂÒ»Ò³
#define PAGE_GOLF_SETUP_UNIT                                                  0x2029//                                                                                    µ¥Î» Ò³
#define PAGE_GOLF_SETUP_REARVIEW_MIRROR                                       0x202a//                                                               ºóÊÓŸµºÍ¹ÎË®Æ÷Ò³
#define PAGE_GOLF_SETUP_AIR_WINDOW                                            0x202b//                                                                      ¿Õµ÷ºÍŽ°¿Ú¿ª¹ØÉèÖÃÒ³
#define PAGE_GOLF_SETUP_MULTI_FUNCTION_PREV                                   0x202c//                                                         ¶à¹ŠÄÜÏÔÊŸÉÏÒ»Ò³
#define PAGE_GOLF_SETUP_MULTI_FUNCTION_NEXT                                   0x202d//                                                        ¶à¹ŠÄÜÏÔÊŸÏÂÒ»Ò³
#define PAGE_GOLF_SETUP_FACTORY_SETTINGS_PREV                                 0x202e//                                                      ³ö³§ÉèÖÃÉÏÒ»Ò³
#define PAGE_GOLF_SETUP_FACTORY_SETTINGS_NEXT                                 0x202f//                                                      ³ö³§ÉèÖÃÏÂÒ»Ò³
//<!--golf car

//---->CAMRY
#define PAGE_CAMRY_CARSET_PERSONALIZATION 0x2036	// ���Ϳ���������Ϣ��������ҳ 
#define PAGE_CAMRY_CARSET_PERSONALIZATION_DOORLOCK 0x2035 // ���Ϳ���������Ϣ��������ҳ
#define PAGE_CAMRY_CARSET_PERSONALIZATION_CLIMATE 0x2032 //  ��������ҳ
#define PAGE_CAMRY_CARSET_PERSONALIZATION_LIGHTS 0x2033 //  ��������ҳ
#define PAGE_CAMRY_AFTERSETTEHCAMERAGUIDELINE 0x2034 // ��������ҳ

#define PAGE_TRAVEL_INFORMATION_CAR_PUBLIC_SET 	0x203a

#define PAGE_GOLF_SETUP_DRIVING_MOD 0x2040
#define PAGE_GOLF_SETUP_PERSONALIZATION_1 0x2041
#define PAGE_GOLF_SETUP_PERSONALIZATION_2 0x2042

//NEW PAGEID (3561 blue_skin)
//#define PAGE_BLUE_SKIN_CAR_MAIN	0x2060
#define PAGE_BLUE_SKIN_CAR_SETUP 	0x2061
#define PAGE_BLUE_SKIN_CAR_DRIVING_DATA 	0x2062
#define PAGE_BLUE_SKIN_CAR_MAINTAIN 			0x2063
#define PAGE_BLUE_SKIN_CAR_TOYOTA_HISTORY_RECORD 	0x2065
#define PAGE_BLUE_SKIN_CAR_HIGHLANDER_SETUP 	0x2066
#define PAGE_BLUE_SKIN_CAR_HIGHLANDER_PARKING	0x2067



//MODULE_ID_SYNV   0x30
#define PAGE_SYNV_MENU  							0x3001//2013-4-27 UPDATE


#define PAGE_THIRD_PAGE	  							0xFF04 //����ҳ

//MODULE_ID_DVR   0x40
#define PAGE_DRIVING_RECORD_MENU  	    0x4001
#define PAGE_DRIVING_RECORD_TIME_SET  	0x4002
#define PAGE_DRIVING_RECORD_SET      	0x4003
#define PAGE_DRIVING_RECORD_PALY     	0x4004//2013-6-26 
#define PAGE_DRIVING_RECORD_VIDEO	    0x4005 
#define PAGE_DRIVING_RECORD_NO_SIGN  	0x4006

#define PAGE_DRIVING_USB_CAMERA_SET  	0x4007
#define PAGE_DRIVING_USB_CAMERA_FOLDER    0x4008
#define PAGE_DRIVING_USB_CAMERA_EMERGENCY_COLLISION    0x4009

#define PAGE_DRIVING_CHANGHE_DVR_SET_OSD  	0x400a
#define PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD  	0x400b

#define PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD_changhe  	0x400c
#define PAGE_DRIVING_RECORD_VIDEO_changhe   	0x400d
#define PAGE_DRIVING_NO_SUPPORT_USB_CAMERA  	0x400f

#define PAGE_DRIVING_FRONT_CAMERA_APP  	0x407f

/*
-------------------------------------------------------------------------------						
			时间�?2015-3-13 17�?9
			
			产品�?保千里电子（DNV�?
			
			文档�?保千里夜视系统与导航配合规格�?Ver1.21（丰田）
-------------------------------------------------------------------------------
*/

#define PAGE_DNV_VIEW					0x5000				//导航夜视界面主页    
#define PAGE_DNV_PLAY					0x5001				//播放界面�?
#define PAGE_DNV_PAUSE					0x5002				//暂停界面�?
#define PAGE_DNV_MENU					0x5003				//菜单界面�?
#define PAGE_DNV_TIP					0x5004
#define PAGE_DNV_SOFTWARE_VERSION		0x5005
#define PAGE_DNV_VIEW_BACK_BROUND		0x5006				//VIEW 页背景触摸页
#define PAGE_DNV_DEVICE_SETTING_TIP		0x5007
#define PAGE_DNV_EMPTY_BLACK_PAGE		0x5008
#define PAGE_OTHER_DVR_BACKGROUND		0x500d
#define PAGE_OTHER_DVR_MAIN				0x500e
#define PAGE_OTHER_DVR_COLOR_SET		0x500f

//speech_app_media_page
#define PAGE_SPEECH_APP_MEDIA		0xFC00


#endif
