#include "connection.c"

#ifndef MAX_BUF
#define MAX_BUF 640000
#endif

size_t lib2ch_get_thread(char *buf, char *server, char *board, char *thread)
{
  char target_url[MAX_BUF + 1];
  sprintf(target_url, "http://%s.2ch.net/%s/dat/%s.dat", server, board, thread);

  size_t dat_size;
  dat_size = connection(target_url, buf);

  connection_close();
  return dat_size;
}
