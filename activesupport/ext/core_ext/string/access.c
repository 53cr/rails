#include <assert.h>
#include <string.h>

#include "access.h"

char *
string_from(char *str, int position)
{
  int len = strlen(str);

  if (position < 0) {
    position += len; // -10 + 10 = 0
  }

  if (position > len || position < 0) {
    position = str + len;
  }
  
  return position;
}

void
test_string_from()
{
  char *test = "0123456789";
  assert(!strcmp(string_from(test, 0), "0123456789"));
  assert(!strcmp(string_from(test, 1), "123456789"));
  assert(!strcmp(string_from(test, 9), "9"));
  assert(!strcmp(string_from(test, 10), ""));
  assert(!strcmp(string_from(test, 15), ""));
  assert(!strcmp(string_from(test, -1), "9"));
  assert(!strcmp(string_from(test, -2), "89"));
  assert(!strcmp(string_from(test, -10), "0123456789"));
  assert(!strcmp(string_from(test, -11), ""));
  assert(!strcmp(string_from(test, -15), ""));
}

char *
string_to(char *str, int position)
{
  int len = strlen(str);
  char *ret;
  
  if (position < 0) {
    position += len;
  }

  if (position > len) {
    return str;
  } else if (position < 0) {
    return str+len;
  } else {
    ret = malloc((position+2)*sizeof(char));
    strncpy(ret, str, position+1);
    *(ret+position+1) = '\0';
    return ret;
  }
}

void
test_string_to()
{
  char *test = "0123456789";
  assert(!strcmp(string_to(test, 0), "0"));
  assert(!strcmp(string_to(test, 1), "01"));
  assert(!strcmp(string_to(test, 9), "0123456789"));
  assert(!strcmp(string_to(test, 10), "0123456789"));
  assert(!strcmp(string_to(test, 15), "0123456789"));
  assert(!strcmp(string_to(test, -1), "0123456789"));
  assert(!strcmp(string_to(test, -2), "012345678"));
  assert(!strcmp(string_to(test, -10), "0"));
  assert(!strcmp(string_to(test, -11), ""));
  assert(!strcmp(string_to(test, -15), ""));
}
