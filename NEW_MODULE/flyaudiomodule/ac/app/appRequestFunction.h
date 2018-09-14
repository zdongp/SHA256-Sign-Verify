#ifndef __APP_REQUEST_FUNCTION_DVD_H__
#define __APP_REQUEST_FUNCTION_DVD_H__



void appRequest_refreshACDoor_PowerSupply(u8 state);
void appRequest_refreshAC_SYNC_Mode(u8 state);
void appRequest_refreshAOrCMode(u8 State);
void appRequest_refreshAcOffStatus(u8 state);
void appRequest_refreshColdMode(u8 mode);
void appRequest_refreshRearWindowsHeatMode(u8 mode);
void appRequest_refreshWindToWindowMode(u8 mode);
void appRequest_refreshOutRecycleMode(u8 mode);
void appRequest_refreshACDoor(u8 state);
void appRequest_refreshAutoMode(u8 mode);
void appRequest_refreshWindFace(u8 face);
void appRequest_refreshWindSpeedLevel(u8 level);
void appRequest_refreshuinnerLoopStatus(u8 state);
void appRequest_refreshDegreeCtrlMode(u8 mode);

void appRequest_refreshWindToFaceMode(u8 mode);
void appRequest_refreshWindToFeetMode(u8 mode);
void appRequest_refreshLeftSeatHeat(u8 p);
void appRequest_refreshRightSeatHeat(u8 p);


///////////////////////////////////fks/////////////////////////
void appRequest_fks_refreshLeftTemple(float t);
void appRequest_fks_refreshRightTemple(float t);
void appRequest_fks_refreshDownStatus(u8 state);
void appRequest_fks_refreshFrontStatus(u8 state);
void appRequest_fks_refreshAcMaxStatus(u8 state);
void appRequest_fks_refreshMaxUpStatus(u8 state);
///////////////////////////////////////////////////////////////


//////////////////////////////////TOYOTA////////////////////////
void appRequest_toyota_refreshAcSpeed(u8 speed);
void appRequest_toyota_refreshLeftTemple(int t);
void appRequest_toyota_refreshRightTemple(int t);
//////////////////////////////////////////////////////////////




///////////////////////////////////BYD//////////////////////////////////////
void appRequest_byd_refreshLeftTemprature(int degree);
void appRequest_byd_refreshRightTemprature(int degree);
void appRequest_byd_refreshCarGroundDegree(int degree);
void appRequest_byd_degree_num2string(int in, char *pOut);
////////////////////////////////////////////////////////////////////////////

////golf
void appRequest_golf_refreshLeftTemprature(int degree);
void appRequest_golf_refreshRightTemprature(int degree);
void appRequest_golf_degree_num2string(int in, char *pOut);
////golf


///////////////////////////////////CRV/////////////////////////////////

void appRequest_crv_refreshWindSpeedLevel(u8 level);
void appRequest_crv_refreshLeftTemprature(int degree);
void appRequest_crv_refreshRightTemprature(int degree);
void appRequest_crv_degree_num2string(int in, char *pOut);
//////////////////////////////////////////////////////////////////////





#endif

