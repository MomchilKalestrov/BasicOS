#ifndef __STRING_H
#define __STRING_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

size_t string_length(const char *);
void string_reverse(char *, size_t);
bool string_compare(char *, char * second);
void string_convert(char *, int32_t);

#endif