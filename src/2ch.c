#include "2ch.h"

int lib2ch_init(Ch *ch)
{
  strcpy(ch->bbs_menu_url, "http://menu.2ch.net/bbsmenu.html");
  strcpy(ch->user_agent, "Monazilla/1.00 (lib2ch/1.00)");
  strcpy(ch->host, "2ch.net");
  return 0;
}

int lib2ch_board_init(Board *board, Ch *ch, char *server, char *name)
{
  board->ch = ch;
  strcpy(board->server, server);
  strcpy(board->name, name);
  return 0;
}

char thread_buf[MAX_BUF];
char *thread_list[1024];
int lib2ch_thread_init(Board *board)
{
  char url[MAX_BUF + 1];
  sprintf(url, "http://%s.%s/%s/subject.txt", board->server, board->ch->host, board->name);
  connection(url, thread_buf);
  connection_close();
  lib2ch_strstr(thread_list, thread_buf, "\n");
  return 0;
}

int lib2ch_set_thread(Thread *thread, Board *board, char *title, char *no)
{
  thread->board = board;
  strcpy(thread->title, title);
  strcpy(thread->no, no);
  return 0;
}

int lib2ch_get_thread(Board *board, Thread *thread)
{
  static int lib2ch_thread_offset = 0;
  if (thread_list[lib2ch_thread_offset + 1] == NULL) {
    return -1;
  }
  char *_thread[2];
  lib2ch_strstr(_thread, thread_list[lib2ch_thread_offset], "<>");
  char *_title[2];
  lib2ch_strstr(_title, _thread[1], " (");
  char *_no[2];
  lib2ch_strstr(_no, _thread[0], ".");

  lib2ch_set_thread(thread, board, _title[0], _no[0]);
  lib2ch_thread_offset++;
  return 0;
}

char response_buf[MAX_BUF];
char *response_list[1024];
int lib2ch_response_init(Thread *thread)
{
  char url[MAX_BUF + 1];
  sprintf(url, "http://%s.%s/%s/dat/%s.dat", thread->board->server, thread->board->ch->host, thread->board->name, thread->no);
  connection(url, response_buf);
  connection_close();
  lib2ch_strstr(response_list, response_buf, "\n");
  return 0;
}

int lib2ch_set_response(Response *response, Thread *thread, char *name, char *mail, char *id, char *date, char *subject)
{
  response->thread = thread;
  strcpy(response->name, name);
  strcpy(response->mail, mail);
  strcpy(response->id, id);
  strcpy(response->date, date);
  strcpy(response->subject, subject);
  return 0;
}

int lib2ch_get_response(Thread *thread, Response *response)
{
  static int lib2ch_response_offset = 0;

  if (response_list[lib2ch_response_offset + 1] == NULL) {
    return -1;
  }
  char *_res[5];
  lib2ch_strstr(_res, response_list[lib2ch_response_offset], "<>");
  char *_id[3];
  lib2ch_strstr(_id, _res[2], "ID:");

  lib2ch_set_response(response, thread, _res[0], _res[1], _id[1], _id[0], _res[3]);
  lib2ch_response_offset++;
  return 0;
}

void lib2ch_stok(char *sua[1024], char *Busu, char *de)
{
  char *tp;
  int i = 0;
  tp = strtok(Busu, de);
  sua[0] = tp;
  while (tp != NULL) {
    i++;
    tp = strtok(NULL, de);
    if (tp != NULL ) {
      sua[i] = tp;
    }
  }
}

void lib2ch_strstr(char *sua[1024], char *Busu, char *de)
{
  char *buf, *elem, *strp;
  int i = 0;

  elem = lib2ch_substr(Busu, de);
  sua[i] = Busu;
  while(elem != NULL){
    i++;
    strp = lib2ch_substr(elem, de);
    sua[i] = elem;
    elem = strp;
  }
}

char *lib2ch_substr(char *str, const char *delimstr)
{
  char *delim_point = strstr(str, delimstr);
  if(!delim_point) return NULL;

  *delim_point = '\0';
  return delim_point + strlen(delimstr);
}
