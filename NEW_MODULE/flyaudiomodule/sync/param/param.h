#ifndef __PARAM_H__
#define __PARAM_H__

#define FILE_SYNC_TEXT_MAX_LEN 300

typedef struct{
	char cSyncTextLine1[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncTextLine2[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncTextLine3[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncTextLine4[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncTextLine5[FILE_SYNC_TEXT_MAX_LEN];
	
	char cSyncButton1[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncButton2[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncButton3[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncButton4[FILE_SYNC_TEXT_MAX_LEN];

	char cSyncCheckBox2[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncCheckBox3[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncCheckBox4[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncCheckBox5[FILE_SYNC_TEXT_MAX_LEN];

	char cSyncTextLine1_len;
	char cSyncTextLine2_len;
	char cSyncTextLine3_len;
	char cSyncTextLine4_len;
	char cSyncTextLine5_len;
	
	char cSyncButton1_len;
	char cSyncButton2_len;
	char cSyncButton3_len;
	char cSyncButton4_len;

	char cSyncCheckBox2_len;
	char cSyncCheckBox3_len;
	char cSyncCheckBox4_len;
	char cSyncCheckBox5_len;
	
}file_sync_text_curpage;

typedef struct{
	char cSyncTextLine1[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncTextLine2[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncTextLine3[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncTextLine4[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncTextLine5[FILE_SYNC_TEXT_MAX_LEN];
	
	char cSyncCheckBox2[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncCheckBox3[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncCheckBox4[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncCheckBox5[FILE_SYNC_TEXT_MAX_LEN];
	
	char cSyncButton1[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncButton2[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncButton3[FILE_SYNC_TEXT_MAX_LEN];
	char cSyncButton4[FILE_SYNC_TEXT_MAX_LEN];

	char cSyncTextLine1_len;
	char cSyncTextLine2_len;
	char cSyncTextLine3_len;
	char cSyncTextLine4_len;
	char cSyncTextLine5_len;

	char cSyncButton1_len;
	char cSyncButton2_len;
	char cSyncButton3_len;
	char cSyncButton4_len;

	char cSyncCheckBox2_len;
	char cSyncCheckBox3_len;
	char cSyncCheckBox4_len;
	char cSyncCheckBox5_len;
	
}file_sync_text_prepage;


typedef struct {
	bool b_SyncAble;
	u8 c_ByMediaState;
	bool b_BtCallState;
	bool m_bSpeech_ButtonValue;
	int m_iSoundChannel;

	bool bAutoJumpPrePage;
	
	file_sync_text_curpage Sync_file_textandbutton_curpage;
	file_sync_text_prepage Sync_file_textandbutton_prepage;
}sync_local_param_t;



typedef struct{
}sync_global_param_t;

extern sync_local_param_t *pLocalParam;
extern sync_global_param_t *pGlobalParam;

void readParameter(void);
void saveParameter(void);


typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;
uni16_size_t uni16_strlen(const unicode16_t *uni16);
unicode16_t ansi_to_unicode16(const unsigned char ansi);
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src);
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);


int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
int enc_get_utf8_size(const unsigned char pInput);

#endif
