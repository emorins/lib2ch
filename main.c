#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <iconv.h>
#include "lib2ch.c"

#define MAX_BUF 640000

int main(int argc, char *args[])
{
  if (argc != 4) {
    printf("usage: ./main [server] [boerd] [thread]\n");
    return -1;
  }
  
  char    dat_text[MAX_BUF + 1];
  size_t  dat_size;
  dat_size = lib2ch_get_thread(dat_text, args[1], args[2], args[3]);

  printf("%s\n%d", dat_text, (int)dat_size);
  return 0;
}
