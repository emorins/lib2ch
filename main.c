#include <stdio.h>
#include "lib2ch.h"

#define MAX_BUF 640000

int main(int argc, char *args[])
{
  if (argc != 4) {
    printf("usage: ./main [server] [boerd] [thread]\n");
    return -1;
  }
  
  int i = 0;
  Ch ch;
  lib2ch_init(&ch);

  Board board;
  lib2ch_board_init(&board, &ch, "kamome", "hikky");

  Thread *threads[1024];
  size_t board_size;
  board_size = lib2ch_get_threads(&board, threads);
  
  i = 0;
  /*
  while(1){
    if (threads[i] == NULL) break;
    printf("%d:%d=%s\n", i, threads[i]->no, threads[i]->title);
    i++;
  }
  */

  Response *responses[1024];
  size_t thread_size;
  thread_size =lib2ch_get_responses(threads[0], responses);

  i = 0;
  while(1){
    i++;
    if (responses[i] == NULL){
      printf("--------------%d\n", i);
      //      printf("%s\n", responses[i-1]->name);
      //      printf("%s\n", responses[i-1]->id);
      //      printf("%s\n", responses[i-1]->date);
      //      printf("%s\n", responses[i-1]->subject);
      //      printf("%s\n", responses[i-1]->mail);
      break;
    }
  }

 
  return 0;
}
