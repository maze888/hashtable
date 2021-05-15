#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define HT_SET_ERROR(...) ht_set_last_error(__FILE__, __LINE__, __func__, __VA_ARGS__);

extern char ht_last_error[BUFSIZ];

void ht_set_last_error(const char *file, int line, const char *func, char *fmt, ...);
