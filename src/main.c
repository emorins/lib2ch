#include <stdio.h>
#include "lib2ch.h"

#define MAX_BUF 640000

int main(int argc, char *args[])
{
  /*
  if (argc != 4) {
    printf("usage: ./main [server] [boerd] [thread]\n");
    return -1;
  }
  */
  
  Ch ch;
  lib2ch_init(&ch);

  Board board;
  lib2ch_board_init(&board, &ch, "kamome", "hikky");

  Thread thread;
  lib2ch_thread_init(&board);
  while (1){
    if (lib2ch_get_thread(&board, &thread) == -1) {
      break;
    }
    printf("%s:%s\n", thread.no, thread.title);
  }
  
  Response response;
  lib2ch_response_init(&thread);
  while (1){
    if (lib2ch_get_response(&thread, &response) == -1) {
      break;
    }
    printf("%s:%s\n", response.name, response.subject);
  }
  

  return 0;
}
