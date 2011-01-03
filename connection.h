#define MAX_BUF 640000

size_t write_data( void *buffer, size_t size, size_t nmemb, void *userp );
size_t connection(char *url, char *buf);
void connection_close(void);
