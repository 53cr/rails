#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "filters.h"

static bool /* Ugly, but fast! */
_is_space(char chr)
{
  if (chr > 13) {
    return (chr == 32);
  } else {
    return (chr == 9 || chr == 10 || chr == 12 || chr == 13);
  }
}

char *
string_squish(char *str)
{
  bool in_space = false;
  char *newstr = (char *)malloc((strlen(str)+1)*(sizeof (char)));
  char *cp;

  while (_is_space(*str)) {
    str++;
  }

  for (cp = newstr; *str != '\0'; str++) {
    if (_is_space(*str)) {
      if (!in_space) {
        in_space = true;
        *cp++ = ' ';
      }
    } else {
      in_space = false;
      *cp++ = *str;
    }
  }

  if (*(cp-1) == ' ') {
    *(cp-1) = '\0';
  }
  
  return newstr;
}
