#include <string.h>

#include "access.h"

char *
string_from(char *str, int position)
{
  int len = strlen(str);
  if (position > len) {
    return str+len;
  }
  return str + position;
}

char *
string_to(char *str, int position)
{
  int len = strlen(str);
  if (position > len) {
    return str;
  }
  str[position] = '\0';
  return str;
}
