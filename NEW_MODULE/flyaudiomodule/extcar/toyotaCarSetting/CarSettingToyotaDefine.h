#ifndef __CAR_CARSETTINGS_DEFINE_H__
#define __CAR_CARSETTINGS_DEFINE_H__

#define CAMRY "CAMRY"


enum E_CARSET_SPEED_AUTOLOCK_STATE{SPEED_OFF,SPEED_ON,SPEED_UNKNOW};
enum E_CARSET_HEADLIGHT_SENTIVITY{SENTIVITY_WEAKEST=1,SENTIVITY_WEAK,SENTIVITY_MODERATE,SENTIVITY_STRONG,SENTIVITY_MOST,SENTIVITY_UNKNOW};
enum E_CARSET_INTERTIORLIGHT_TIMER{TIME_7_5=1,TIME_15,TIME_30,TIME_CLOSE,TIME_UNKNOW};
enum E_CARSET_DOOR_UNLOCK_SWITCH{DOOR_UNLOCK_ALL,DOOR_UNLOCK_DRITVER,DOOR_UNLOCK_UNKNOW};
enum E_CARSET_ELECTRONICTOSYSKEY_STATE{ELECTRONICTOSYSKEY_OFF,ELECTRONICTOSYSKEY_ON,ELECTRONICTOSYSKEY_UNKNOW};
enum E_CARSET_LOCKSTATE_PILOTLAMP_STATE{PILOTLAMP_OFF,PILOTLAMP_ON,PILOTLAMP_UNKNOW};
enum E_CARSET_OUT_P_AUTOLOCK_STATE{OUT_P_OFF,OUT_P_ON,OUT_P_UNKNOW};
enum E_CARSET_IN_P_AUTOLOCK_STATE{IN_P_OFF,IN_P_ON,IN_P_UNKNOW};
enum E_CARSET_DRIVERDOOR_AUTOUNLOCK_STATE{DRIVERDOOR_AUTOUNLOCK_OFF, DRIVERDOOR_AUTOUNLOCK_ON, DRIVERDOOR_AUTOUNLOCK_UNKNOW};
enum E_CARSET_BACKCAR_GUIDELINESET{GUIDELINESET_1=2, GUIDELINESET_2=4,GUIDELINESET_3=6,GUIDELINESET_UNKNOW};
enum E_CARSET_TELECONTROL_2SEP_AUTOUNLOCK_STATE{TELECONTROL_2SEP_OFF,TELECONTROL_2SEP_ON,TELECONTROL_2SEP_UNKNOW};
enum E_CARSET_AUTO_ACMODE_STATE{ACMODE_OFF,ACMODE_ON,ACMODE_UNKNOW};
enum E_CARSET_EFFECTIVE_VENTILATMODE_STATE{VENTILATMODE_OFF,VENTILATMODE_ON,VENTILATMODE_UNKNOW};
enum E_CAR_DANGER_WARNING_LAMP_STATE{DANGER_WARNING_LAMP_OFF,DANGER_WARNING_LAMP_ON,DANGER_WARNING_LAMP_UNKNOW = 0xFF};
enum E_CAR_DRIVING_REMOTE_DIPPED_LAMP_STATE{DRIVING_LAMP=1,DIPPED_LAMP=2,REMOTE_LAMP=3,DRIVING_REMOTE_DIPPED_LAMP_UNKNOW = 0xFF};
enum E_CAR_BRAKE_TAIL_LAMP_STATE{BRAKE_TAIL_LAMP_OFF,BRAKE_TAIL_LAMP_ON,BRAKE_TAIL_LAMP_UNKNOW = 0xFF};
enum E_CAR_CORNERING_LAMP_STATE{CORNERING_LAMP_OFF,CORNERING_LAMP_LEFT,CORNERING_LAMP_RIGHT,CORNERING_LAMP_UNKNOW = 0xFF};
enum E_CAR_GEARS_STATE{GEARS_N,GEARS_P,GEARS_R,GEARS_D,GEARS_M,GEARS_UNKNOW = 0xFF};
enum E_CAR_ENGINE_STATE{ENGINE_STOP,ENGINE_START,ENGINE_UNKNOW = 0xFF};
enum E_CAR_OIL_CONSUMPTION_ALARM_STATE{OIL_STATE_NORMAL,OIL_STATE_WARNING,OIL_STATE_UNKNOW = 0xFF};

#endif
