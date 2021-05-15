#include "hashtable_error.h"

char ht_last_error[BUFSIZ] = {0};

void ht_set_last_error(const char *file, int line, const char *func, char *fmt, ...)
{
  va_list ap;
  char msg[BUFSIZ - 256] = {0};

  memset(ht_last_error, 0x00, sizeof(ht_last_error));

  va_start(ap, fmt);
  vsnprintf(msg, sizeof(msg), fmt, ap);
  va_end(ap);

  snprintf(ht_last_error, sizeof(ht_last_error), "%s(%d line, %s): %s", file, line, func, msg);
}
