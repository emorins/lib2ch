#include "common.h"
#include "connection.h"

#ifndef MAX_BUF
#define MAX_BUF 640000
#endif

typedef struct
{
  char bbs_menu_url[256];
  char user_agent[256];
  char host[256];
} Ch;

typedef struct
{
  char host[MAX_BUF];
} Thread;

typedef struct
{
  Ch *ch;
  char server[128];
  char name[128];
  Thread *threads[1024];
} Board;

typedef struct
{
  char host[MAX_BUF];
} Response;

int lib2ch_init(Ch *ch);
int lib2ch_board_init(Board *board, Ch *ch, char *server, char *name);
size_t lib2ch_get_threads(Board *board, char *buf);
size_t lib2ch_get_thread(char *buf, char *server, char *board, char *thread);
void stok(char *sua[1024], char *Busu, char *de);
