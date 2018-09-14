#define DEFAULT_VALUE_AC			20131106

int Ltemp_H = DEFAULT_VALUE_AC, Ltemp_L = DEFAULT_VALUE_AC, Rtemp_H = DEFAULT_VALUE_AC, Rtemp_L = DEFAULT_VALUE_AC;
int Speed = DEFAULT_VALUE_AC, AC,Auto,ModeUp = DEFAULT_VALUE_AC, ModeFront = DEFAULT_VALUE_AC, ModeDown,Max = DEFAULT_VALUE_AC;
int Rear = DEFAULT_VALUE_AC, Vane = DEFAULT_VALUE_AC, Off = DEFAULT_VALUE_AC,Dual = DEFAULT_VALUE_AC,LeftHeat = DEFAULT_VALUE_AC;
int RightHeat = DEFAULT_VALUE_AC;
int AC_MAX = DEFAULT_VALUE_AC, Rear_Lock = DEFAULT_VALUE_AC;
int AcMode = DEFAULT_VALUE_AC;

int otherModule_InitACData()
{
	Ltemp_H = DEFAULT_VALUE_AC, Ltemp_L = DEFAULT_VALUE_AC, Rtemp_H = DEFAULT_VALUE_AC, Rtemp_L = DEFAULT_VALUE_AC;
	Speed = DEFAULT_VALUE_AC, AC = DEFAULT_VALUE_AC, Auto = DEFAULT_VALUE_AC, ModeUp = DEFAULT_VALUE_AC, ModeFront = DEFAULT_VALUE_AC, ModeDown = DEFAULT_VALUE_AC, Max = DEFAULT_VALUE_AC, Rear = DEFAULT_VALUE_AC;
	Vane = DEFAULT_VALUE_AC, Off = DEFAULT_VALUE_AC, Dual = DEFAULT_VALUE_AC, LeftHeat = DEFAULT_VALUE_AC, RightHeat = DEFAULT_VALUE_AC;
	AC_MAX = DEFAULT_VALUE_AC,Rear_Lock = DEFAULT_VALUE_AC;
	AcMode = DEFAULT_VALUE_AC;

	return 0;
}

static void ReturnLTempToWince(u8 ltemp_H,u8 ltemp_L)
{
	u8 buff[] = {0x10,0x00,0x00};

	buff[1] = ltemp_H;
	buff[2] = ltemp_L;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],2);	
}

static void ReturnRTempToWince(u8 rtemp_H,u8 rtemp_L)
{
	u8 buff[] = {0x11,0x00,0x00};

	buff[1] = rtemp_H;
	buff[2] = rtemp_L;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],2);	
}

static void ReturnSpeedToWince(u8 speed)
{
	u8 buff[] = {0x12,0x00};

	buff[1] = speed;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);		
}
static void ReturnAcToWince(u8 ac)
{
	u8 buff[] = {0x13,0x00};

	buff[1] = ac;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);		
}
static void ReturnAutoToWince(u8 pauto)
{
	u8 buff[] = {0x14,0x00};

	buff[1] = pauto;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);			
}
static void ReturnModeUpToWince(u8 modeup)
{
	u8 buff[] = {0x15,0x00};

	buff[1] = modeup;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);			
}
static void ReturnModeFrontToWince(u8 modefront)
{
	u8 buff[] = {0x16,0x00};

	buff[1] = modefront;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);			
}

static void ReturnModeDownToWince(u8 modedown)
{
	u8 buff[] = {0x17,0x00};

	buff[1] = modedown;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);	
}

static void ReturnMaxToWince(u8 max)
{
	u8 buff[] = {0x18,0x00};

	buff[1] = max;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);	
}

static void ReturnRearToWince(u8 rear)
{
	u8 buff[] = {0x19,0x00};

	buff[1] = rear;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);	
}
static void ReturnVaneToWince(u8 vane)
{
	u8 buff[] = {0x1a,0x00};

	buff[1] = vane;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);	
}

static void ReturnOffToWince(u8 off)
{
	u8 buff[] = {0x1b,0x00};

	buff[1] = off;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);		
}

static void ReturnDualToWince(u8 dual)
{
	u8 buff[] = {0x1c,0x00};

	buff[1] = dual;
	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);		

}

static void ReturnleftHeatToWince(u8 leftHeat)
{
	u8 buff[] = {0x1d,0x00};

	buff[1] = leftHeat;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);	
}
static void ReturnRightHeatToWince(u8 rightHeat)
{
	u8 buff[] = {0x1e,0x00};

	buff[1] = rightHeat;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);		
}
static void ReturnAcMax(u8 acMax)
{
	u8 buff[] = {0x1f,0x00};

	buff[1] = acMax;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);	
}
static void ReturnRearLock(u8 rearLock)
{
	u8 buff[] = {0x20,0x00};

	buff[1] = rearLock;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);	
}
static void ReturnAcMode(u8 acMode)
{
	u8 buff[] = {0x21,0x00};

	buff[1] = acMode;

	analyseHalMessage_AIRCONDITION(buff[0],&buff[1],1);	
}

static void DealTuguanAcData(u8 *buf)
{
	LOGD("~~~DealTuguanAcData~~~buf[0]:%x,buf[1]:%x",buf[0],buf[1]);
	switch(buf[0])
	{
	case 0x5b://left temperature
		{
			LOGD("Ltemp_L = %X, Ltemp_H = %X .", Ltemp_L, Ltemp_H);
			if(Ltemp_L != (u8)(buf[1]*10))
			{
				Ltemp_L = buf[1]*10;
				Ltemp_H =(buf[1]*10)>>8;
				ReturnLTempToWince(Ltemp_H,Ltemp_L);		
			}
			else
				LOGD("ltemp_L not enter!");
		}
		break;
	case 0x61://right temperature
		{
			LOGD("Rtemp_L = %X, Rtemp_H = %X .",  Rtemp_L, Rtemp_H);
			if(Rtemp_L != (u8)(buf[1]*10))
			{
				Rtemp_L = buf[1]*10;
				Rtemp_H =(buf[1]*10)>>8;
				ReturnRTempToWince(Rtemp_H,Rtemp_L);
			}
			else
				LOGD("Rtemp_L not enter!");
		}
		break;
	case 0x6e://max
		if(Max != (buf[1] & 0x01))
		{
			Max = buf[1] & 0x01;
			ReturnMaxToWince(Max);
		}
		break;
	case 0x71://ac
		{
			LOGD("AC = %X", AC, buf[1]);
			if(AC != (buf[1]&0x01))
			{
				AC = buf[1] & 0x01;
				ReturnAcToWince(AC);
			
			}
		}
		break;	
	/*case 0x5d://auto
	case 0x63:
		{
			LOGD("Auto = %X", Auto, buf[1]);
			if((buf[1]&0xf0) == 0)
			{
				if(Auto != 0)
				{
					Auto =0;
					ReturnAutoToWince(0);
				}
			}
			else
			{
				if(buf[1] & 0x10)
				{
					if(Auto != 1)
					{
						Auto = 1;
						ReturnAutoToWince(1);
					}
				}
				else
				{
					if(Auto != 2)
					{
						Auto =2;
						ReturnAutoToWince(2);					
					}
				}
			}
		}
		break;*/
	case 0x64://AUTO
    	{
    	    LOGD("[%s] Auto = %X buf[0]:%x,buf[4]:%x",__FUNCTION__, Auto, buf[0],buf[4]);
    	    if(buf[4] == 0x01)//0FF
    	    {
    	    	if(Auto != 0)
				{
					Auto =0;
					ReturnAutoToWince(0);
				}
    	    }
    	    else if(buf[4] == 0x03)
    	    {
    	       	if(Auto != 1)
				{
					Auto = 1;
					ReturnAutoToWince(1);
				}
    	    }
    	}
    	break;
	case 0x55://dual
		{

			LOGD("Dual = %X .", Dual);
			if(( buf[1] ==0 )&&(buf[2] == 0))
			{
				if(Dual != 1)
				{
					Dual =1;
					ReturnDualToWince(1);
				}
			}
			else
			{
				if(Dual != 0)
				{
					Dual =0;
					ReturnDualToWince(0);
				}
			}
		}
		break;
	case 0x5e://mode
		LOGD("buf[2]=%x,buf[3]=%x,buf[4]=%x",buf[2],buf[3],buf[4]);
		if(buf[1] == 0xC)
		{
			if(ModeUp != 1)
			{
				ModeUp = 1;
				ReturnModeUpToWince(1);
			}
		}
		else
		{
			if(ModeUp != 0)
			{
				ModeUp = 0;
				ReturnModeUpToWince(0);
			}
		}
		if(buf[2] == 0xC)
		{
			if(ModeFront != 1)
			{
				ModeFront = 1;
				ReturnModeFrontToWince(1);
			}
		}
		else
		{
			if(ModeFront != 0)
			{
				ModeFront = 0;
				ReturnModeFrontToWince(0);
			}
		}
		if(buf[3] == 0xC)
		{
			if(ModeDown != 1)
			{
				ModeDown = 1;
				ReturnModeDownToWince(1);
			}
		}
		else
		{
			if(ModeDown != 0)
			{
				ModeDown = 0;
				ReturnModeDownToWince(0);
			}
		}
		if(buf[4] == 0x03)
		{
			if(Auto !=1)
			{
				Auto =1;
				ReturnAutoToWince(Auto);	
			}
		}
		else
		{
			if(Auto !=0)
			{
				Auto =0;
				ReturnAutoToWince(Auto);	
			}
		}
		break;
	case 0x5c://speed
	case 0x62:
		LOGD("Speed:%x",Speed);
		if(Speed != buf[1])
		{
			Speed = buf[1];
			ReturnSpeedToWince(buf[1]);
		}
		break;
	case 0x50://vane
		LOGD("Vane:%x",Vane);
		if(Vane != (buf[1]&1))
		{
			Vane = (buf[1]&0x01);
			ReturnVaneToWince(Vane);
		}
		break;
	case 0x51://vane
		LOGD("Vane:%x",Vane);
		if(buf[1])
		{
			if(Vane != 1)
			{
				Vane =1;
				ReturnVaneToWince(1);
			}
		}
		else
		{
			if(Vane != 0)
			{
				Vane =0;
				ReturnVaneToWince(0);
			}

		}
		break;
	case 0x58://rear
		LOGD("Rear:%x",Rear);
		if(Rear != (buf[1]&0x1))
		{
			Rear = buf[1]&0x1;
			ReturnRearToWince(Rear);
		}
		break;
	case 0x4d://off
	
		if(buf[1] & 0x10)
		{

			LOGD("off:%x", Off);
			if(Off != 0)
			{
				Off =0;
				ReturnOffToWince(0);

			}
		}
		else
		{

			LOGD("off:%x", Off);
			if(Off != 1)
			{
				Off =1;
				ReturnOffToWince(1);
			}
		}
		break;
	case 0x56:
		break;
	case 0x5f://◊Û◊˘“Œ\u0152”»»
		LOGD("LeftHeat:%x",LeftHeat);
		if(LeftHeat!= buf[1])
		{
			LeftHeat =buf[1];
			ReturnleftHeatToWince(buf[1]);
		}
		break;
	case 0x65://”“◊˘“Œ\u0152”»»
		LOGD("RightHeat:%x",RightHeat);
		if(RightHeat!= buf[1])
		{
			RightHeat =buf[1];
			ReturnRightHeatToWince(buf[1]);
		}
		break;
	case 0x67:
		if(buf[1] ==0)
		{
			LOGD("Rear_Lock:%x",Rear_Lock);
			if(Rear_Lock != 1)
			{
				Rear_Lock =1;
				ReturnRearLock(Rear_Lock);
			}
		}
		else
		{
			LOGD("Rear_Lock:%x",Rear_Lock);
			if(Rear_Lock != 0)
			{
				Rear_Lock =0;
				ReturnRearLock(Rear_Lock);
			}
		}
		break;	
	case 0x75:
		LOGD("AC_MAX:%x",AC_MAX);
		if(AC_MAX != buf[1])
		{
			AC_MAX = buf[1];
			ReturnAcMax(AC_MAX);
		}
		break;
	default:
		break;
	}

}

