#include "common.h"
#include "lib2ch.h"
#include "connection.h"

char wr_buf[MAX_BUF+1];
int  wr_index;
CURL *curl;

size_t write_data( void *buffer, size_t size, size_t nmemb, void *userp )
{
  int segsize = size * nmemb;
  if ( wr_index + segsize > MAX_BUF ) {
    *(int *)userp = 1;
    return 0;
  }
  memcpy( (void *)&wr_buf[wr_index], buffer, (size_t)segsize );
  wr_index += segsize;
  wr_buf[wr_index] = 0;
  return segsize;
}

int connection(char *url, char *buf)
{
  CURLcode res;
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
  res = curl_easy_perform(curl);
 
  char *p_src, *p_dst;
  size_t n_src, n_dst;
  strcpy(buf, wr_buf);
 
  return 0;
}

void connection_close(void)
{
  wr_index = 0;
  curl_easy_cleanup(curl);
}
