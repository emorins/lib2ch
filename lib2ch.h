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
  Ch *ch;
  char server[128];
  char name[128];
} Board;

typedef struct
{
  Board *board;
  char title[MAX_BUF];
  char no[MAX_BUF];
} Thread;

typedef struct
{
  Thread *thread;
  int no;
  char name[256];
  char mail[256];
  char id[256];
  char date[256];
  char subject[MAX_BUF];
} Response;

int lib2ch_init(Ch *ch);
int lib2ch_board_init(Board *board, Ch *ch, char *server, char *name);

int lib2ch_thread_init(Thread *thread, Board *board, char *title, char *no);
int lib2ch_get_threads(Board *board, Thread *thread[1024]);

int lib2ch_response_init(Thread *thread);
int lib2ch_set_response(Response *response, Thread *thread, char *name, char *mail, char *id, char *date, char *subject);
int lib2ch_get_response(Thread *thread, Response *responses);

void lib2ch_stok(char *sua[1024], char *Busu, char *de);
void lib2ch_strstr(char *sua[1024], char *Busu, char *de);
char *lib2ch_substr(char *str, const char *delimstr);
