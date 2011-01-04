#include "lib2ch.h"

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

int lib2ch_thread_init(Thread *thread, Board *board, char *title, int no)
{
  thread->board = board;
  strcpy(thread->title, title);
  thread->no = no;
  return 0;
}

size_t lib2ch_get_threads(Board *board, Thread *threads[1024])
{
  char url[MAX_BUF + 1];
  size_t size;
  char buf[MAX_BUF];
  sprintf(url, "http://%s.%s/%s/subject.txt", board->server, board->ch->host, board->name);
  size = connection(url, buf);
  connection_close();
  
  char *_threads[1024];
  lib2ch_stok(_threads, buf, "\n");
  int i = 0;
  while (1) {
    if (_threads[i] == NULL) {
      break;
    }
    char *_thread[1];
    lib2ch_stok(_thread, _threads[i], "<>");
    char *_title[1];
    lib2ch_stok(_title, _thread[1], "(");
    char *_no[1];
    lib2ch_stok(_no, _thread[0], ".");

    Thread thread;
    lib2ch_thread_init(&thread, board, _title[0], atoi(_no[0]));
    threads[i] = malloc(sizeof(thread) + 1);
    memcpy(threads[i], &thread, sizeof(thread));
    i = i + 1;
  }
  return size;
}

int lib2ch_response_init(Response *response, Thread *thread, char *name, char *mail, char *id, char *date, char *subject)
{
  response->thread = thread;
  strcpy(response->name, name);
  strcpy(response->mail, mail);
  strcpy(response->id, id);
  strcpy(response->date, date);
  strcpy(response->subject, subject);
  return 0;
}

size_t lib2ch_get_responses(Thread *thread, Response *responses[1024])
{
  char url[MAX_BUF + 1];
  size_t size;
  char buf[MAX_BUF];
  sprintf(url, "http://%s.%s/%s/dat/%d.dat", thread->board->server, thread->board->ch->host, thread->board->name, thread->no);
  size = connection(url, buf);
  connection_close();
  
  char *_responses[1024];
  lib2ch_stok(_responses, buf, "\n");

  int i = 0;
  while (1) {
    if (_responses[i] == NULL) {
      break;
    }
    char *_res[4];
    lib2ch_strstr(_res, _responses[i], "<>");
    char *_id[1];
    lib2ch_strstr(_id, _res[2], "ID:");

    Response response;
    lib2ch_response_init(&response, thread, _res[0], _res[1], _id[1], _id[0], _res[3]);
    responses[i] = malloc(sizeof(response) + 1);
    memcpy(responses[i], &response, sizeof(response));

    i = i + 1;
  }
  return size;
}

size_t lib2ch_get_thread(char *buf, char *server, char *board, char *thread)
{
  char target_url[MAX_BUF + 1];
  sprintf(target_url, "http://%s.2ch.net/%s/dat/%s.dat", server, board, thread);

  size_t dat_size;
  dat_size = connection(target_url, buf);

  connection_close();
  return dat_size;
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
