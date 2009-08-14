#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "starts_ends_with.h"

bool
string_starts_with(char *str, char *substr)
{
  do { 
    if (!*substr) {
      return true;
    }
  } while (*str++ == *substr++);

  return false;
}

void
test_starts_with()
{
  assert(string_starts_with("asdf", "") == true);
  assert(string_starts_with("asdf", "asdfasdf") == false);
  assert(string_starts_with("", "asdfasdf") == false);
  assert(string_starts_with("", "") == true);
}

bool
string_ends_with(char *str, char *substr)
{
  int l_str, l_substr;
  char *p_str, *p_substr;

  l_str    = strlen(str);
  l_substr = strlen(substr);

  if (l_substr > l_str) {
    return false;
  }
  
  p_str    = str    + l_str;
  p_substr = substr + l_substr;

  while (p_substr >= substr) {
    if (*p_substr-- != *p_str--) {
      return false;
    }
  }
  
  return true;
  
}

void
test_ends_with()
{
  assert(string_ends_with("asdf", "") == true);
  assert(string_ends_with("asdf", "asdfasdf") == false);
  assert(string_ends_with("", "asdfasdf") == false);
  assert(string_ends_with("", "") == true);
}

