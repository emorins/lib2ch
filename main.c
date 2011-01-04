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

  Thread *threads[1024];
  lib2ch_get_threads(&board, threads);
  
  int i = 0;
  while(1){
    if (threads[i] == NULL) break;
    printf("%d:%s=%s\n", i, threads[i]->no, threads[i]->title);
    i++;
    }
  
  Response response;
  lib2ch_response_init(threads[0]);

  while (1){
    if (lib2ch_get_response(threads[0], &response) == -1) {
      break;
    }
    printf("%s:%s\n", response.name, response.subject);
  }

  return 0;
}
