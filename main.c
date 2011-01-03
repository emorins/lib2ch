#include <stdio.h>
#include "lib2ch.h"

#define MAX_BUF 640000

int main(int argc, char *args[])
{
  if (argc != 4) {
    printf("usage: ./main [server] [boerd] [thread]\n");
    return -1;
  }
  
  Ch ch;
  lib2ch_init(&ch);
  printf("ch=%s\n", ch.host);

  Board board;
  lib2ch_board_init(&board, &ch, "kamome", "hikky");
  printf("board=%s\n", board.server);

  char buf[MAX_BUF + 1];
  size_t size;
  size = lib2ch_get_threads(&board, buf);
  printf("%s\n%d\n", buf, (int)size);
 

  char    dat_text[MAX_BUF + 1];
  size_t  dat_size;
  dat_size = lib2ch_get_thread(dat_text, args[1], args[2], args[3]);
  printf("%s\n%d", dat_text, (int)dat_size);
  return 0;
}
