#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


char* readFile(char const *filePath)
{
  struct stat statFile;
  size_t size, n;
  char *file = (char *)filePath;

  stat(file, &statFile);
  size = statFile.st_size;

  FILE *stream = fopen(file, "rb");

  char *buffer = (char *)malloc(size);
  if(!buffer)
    return NULL;

  while(1)
    {
      n = fread(buffer, 1, size, stream);
      if(n==0)
        {
          if(ferror(stream))
            {
              printf("fread stream error\n");
              free(buffer);
              return NULL;
            }
          goto dap;
        }

      if(feof(stream))
        goto dap;
    }

  dap:;

  return buffer;
}
/*
int main(int argc, char const *argv[])
{
  size_t sizeFile;
  char *buf = readFile(argv[1], &sizeFile);

  int i=0;
  while(i<sizeFile)
    printf("%x", buf[i++]);

  printf("\nsize=%d strlen=%d\n", (int)sizeFile, (int)strlen(buf));
  free(buf);
  return 0;
}
*/