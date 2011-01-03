#define MAX_BUF 640000

char wr_buf[MAX_BUF+1];
int  wr_index;
CURL *curl;
iconv_t icd;

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

size_t connection(char *url, char *buf)
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
  icd = iconv_open("UTF-8", "Shift_JIS");
  
  p_src = wr_buf;
  p_dst = buf;
  n_src = strlen(wr_buf);
  n_dst = MAX_BUF - 1;

  iconv(icd, &p_src, &n_src, &p_dst, &n_dst);
  *p_dst = '\0';

  return n_dst;
}

void connection_close(void)
{
  curl_easy_cleanup(curl);
  iconv_close(icd);
}
