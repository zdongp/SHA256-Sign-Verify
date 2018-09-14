#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "commonFunc.h"
#include "FlyProperties.h"

#include <unistd.h>
#include <string.h>


static int property_fd = -1; 
static unsigned long save_counts = 0;

struct __save_property_struct{
	char buf[MAX_STRING_LEN];
};
struct __save_property_struct save_property_struct[MAX_STRING_LINE];

static int open_property_file(int flag)
{
	if (property_fd < 0){
		property_fd = open(FLY_PROPERTY_PATH, flag, 0777);
		if (property_fd < 0){
			return - 1;
		}
	}

	return 0;
}

static int close_property_file(void)
{
	if (property_fd > 0){
		if(close(property_fd) < 0){
			return -1;
		}
		
		property_fd = -1;
	}
	
	return 0;
}

static int write_property_file(char *buf, unsigned long len)
{
	int ret=-1;
	if (property_fd > 0){
		ret = write(property_fd, buf, len);
		if (ret > 0){
			return ret; 
		}
	}
	
	return -1;
}

static unsigned long get_property_file_size(void)
{
	struct stat file_stat;
	if (!stat(FLY_PROPERTY_PATH, &file_stat))
		return file_stat.st_size;
	else 
		return 0;
}

static unsigned long __read_property_file(char *buf, unsigned long len)
{
	long long ret=-1;
	if (property_fd > 0){
		ret = read(property_fd, buf, len);
		if (ret > 0){
			return ret; 
		}
	}
	
	return 0;
}

static unsigned long read_property_file(char *buf, unsigned long len)
{
	unsigned long size;
	
	size = get_property_file_size();
	if (size > 0)
		return __read_property_file(buf, size);
	
	return 0;
}

static void save_tcc_fly_property(const char *key, const char *value, void *cookie)
{
	if (!strncmp(key, "fly.", 4))
	{
		if(!strncmp(key, "fly.android.", 12)){
		
		}
		else{
			char buf[MAX_STRING_LEN];
			memset(buf, '\0', sizeof(buf));
	
			strcpy(buf,key);
			strcat(buf,"=");
			strcat(buf,value);
			strcat(buf,"\n");
	
			memset(save_property_struct[save_counts].buf, '\0', 
				sizeof(save_property_struct[save_counts].buf));
			memcpy(save_property_struct[save_counts].buf,buf,sizeof(buf));
			save_counts++;
		}
	}
}

static void __deal_property_file_data(char *buf)
{
	char *pstr=NULL;
	char key[MAX_PROPERTY_KEY_LEN]={'\0'};
	char value[MAX_PROPERTY_VALUE_LEN] = {'\0'};
	unsigned long len = 0;

	pstr = strchr(buf,'=');
	if (pstr){
		len = pstr - buf;
		memcpy(key, buf,len);
		memcpy(value,&buf[len+1], (strlen(buf) - len + 1));
		property_set(key, value);
	}
}

static void deal_property_file_data(char *buf, unsigned long len)
{
	char *pstr = NULL;
	
	pstr = strtok(buf, "\n");
	while (pstr != NULL){
		__deal_property_file_data(pstr);
		pstr = strtok(NULL,"\n");
	}
}

int save_property(void)
{
	unsigned long i;

	property_list(save_tcc_fly_property, NULL);
	if (open_property_file(O_TRUNC|O_CREAT|O_WRONLY) == 0){
		for (i=0; i<save_counts; i++){
			write_property_file(save_property_struct[i].buf,strlen(save_property_struct[i].buf));
		}

		save_counts = 0;
		close_property_file();
	}
	
	return -1;
}

int set_property(void)
{
	
	char buf[MAX_STRING_LINE*MAX_STRING_LEN];
	unsigned long size = 0;
	
	if (open_property_file(O_RDONLY) == 0){
		size = read_property_file(buf, sizeof(buf));
		close_property_file();
	}

	if (size > 0)
		deal_property_file_data(buf, size);
	else 
		return -1;
		
	return 0;
}



