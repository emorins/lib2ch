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

size_t lib2ch_get_threads(Board *board, char *buf)
{
  char url[MAX_BUF + 1];
  size_t size;
  sprintf(url, "http://%s.%s/%s/subject.txt", board->server, board->ch->host, board->name);
  printf("%s\n", url);
  size = connection(url, buf);
  connection_close();
  
  char *threads[1024];
  stok(threads, buf, "\n");
  printf("test=%s\n", threads[10]);
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

void stok(char *sua[1024], char *Busu, char *de)
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
