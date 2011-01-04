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


  Board board;
  lib2ch_board_init(&board, &ch, "kamome", "hikky");
  printf("board=%s\n", board.server);
  printf("board=%s\n", board.name);

  Thread *threads[1024];
  size_t board_size;
  board_size = lib2ch_get_threads(&board, threads);
  printf("title=%s\nno=%d\n", threads[0]->title, threads[0]->no);
  printf("title=%s\nno=%d\n", threads[1]->title, threads[1]->no);
  printf("title=%s\nno=%d\n", threads[2]->title, threads[2]->no);


  Response *responses[1024];
  size_t thread_size;
  thread_size =lib2ch_get_responses(threads[0], responses);

  printf("%s\n", responses[0]->name);
  printf("%s\n", responses[0]->id);
  printf("%s\n", responses[0]->date);
  printf("%s\n", responses[0]->subject);
  printf("%s\n", responses[0]->mail);
  
  return 0;
}
