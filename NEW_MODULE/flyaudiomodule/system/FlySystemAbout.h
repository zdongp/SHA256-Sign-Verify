#pragma once

class CFlySystemAbout
{
public:
	CFlySystemAbout(void);
	~CFlySystemAbout(void);

	void updateSystemAbout(void);
	void updateMCU(void);
	void updateBarCode(void);
	void updateBlueTooth(void);
	void updateMPEG(void);

	int saveMCU(const char *id_mcu);
	int saveMcuTime(const char *pMCUpath);

};
