
#ifndef __FLY_PROPERTY_DEFINE_H__
#define __FLY_PROPERTY_DEFINE_H__

// Ù–‘√˚◊÷
//audio video
#define FLY_VIDEO_BRIGHTNESS_SAVE_NAME		"fly.v.brightness"		
#define FLY_VIDEO_CONTRAST_SAVE_NAME		"fly.v.contrast"	
#define FLY_VIDEO_BACKLIGHT_SAVE_NAME		"fly.v.backlight"	
#define FLY_VIDEO_HUE_SAVE_NAME				"fly.v.hue"	
#define FLY_VIDEO_SATURATION_SAVE_NAME		"fly.v.saturation"	
#define FLY_SET_GPSVOICEPROMPT      "fly.set.b_Sys_GPSVoicePrompt"

#define FLY_AV_CURRENTPAGDID        "fly.av.currentpageid"

#define FLY_AV_SOUNDMODE    		"fly.av.soundMode"
#define FLY_MODULE_TABLE            "fly.module.switch"

#define FLY_AV_GIS_VOLUME           "fly.av.gisVolume"
#define FLY_AV_VOLUME				"fly.av.volume"
#define FLY_AV_BALANCE      		"fly.av.balance"
#define FLY_AV_FADER        		"fly.av.fader"
#define FLY_AV_SOUNDPOS				"fly.av.soundPos"

#define FLY_AV_TREB  				"fly.av.treb"
#define FLY_AV_MID					"fly.av.mid"
#define FLY_AV_BASS					"fly.av.bass"
#define FLY_AV_LOUDNESS				"fly.av.loudness"

#define FLY_AV_TREBPOS				"fly.av.trebPos"
#define FLY_AV_MIDPOS				"fly.av.midPos"
#define FLY_AV_BASSPOS				"fly.av.bassPos"
#define FLY_AV_LOUDNESSPOS 			"fly.av.loudnessPos"

#define FLY_AV_IMEQ					"fly.av.EQ"
#define FLY_AV_EQVALUE				"fly.av.EQValue"
#define FLY_AV_EQUSER1				"fly.av.EQUser1"
#define FLY_AV_EQUSER2				"fly.av.EQUser2"
#define FLY_AV_EQUSER3				"fly.av.EQUser3"
#define FLY_AV_FINETURNINGVALUE 	"fly.av.fineTurningValue"

#define FLY_AV_PREIMEQCONTROL       "fly.av.preEQControl"

#ifdef MSM_8625
#define FLY_TPYE_VERSION 			"fly.tpye.version"
#define FLY_SET_CHANNEL  			"fly.set.channel"
#define FLY_VOL_MAX             "fly.vol.startup.max"
#else
#define FLY_TPYE_VERSION 			"ro.fly.tpye.version"
#define FLY_SET_CHANNEL  			"ro.fly.set.channel"
#define FLY_VOL_MAX             "ro.fly.vol.startup.max"
#endif

#define FLY_MODULE_AUDIO_VIDEO_LOUDNESS_SWITCH	"fly.module.audio.video.loudness.switch"

#define FLY_MIXING_SWITCH  "fly.mixing.switch"


#endif
