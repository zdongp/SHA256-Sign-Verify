#include "sha256.h"
#include <stdio.h>

void createHashFile(char const *filePath)
{
	uint32 H[8];
	int i;

	HashFile(filePath, H);
	FILE *fp = fopen("hash.txt", "wb+");
	for(i=0; i<8; i++)
	{
		printf("%08x", H[i]);
		fprintf(fp, "%08x", H[i]);
	}
	
	printf("\n");
}

int main(int argc, char const *argv[])
{
	createHashFile(argv[1]);
	return 0;
}



