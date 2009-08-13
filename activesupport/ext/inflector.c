#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "inflector.h"

char *
inflector_underscore(char *str)
{
  char *newstr = malloc((strlen(str)*2+1)*sizeof(char));
  char *cp;
  char prev = '\0';

  for (cp=newstr; *str != '\0'; prev=*str++) {

    // replace :: with /
    if (*str == ':' && *(str+1) == ':') {
      *cp++ = '/';
      str++;
    } else {
      
      if ((isupper(prev) && isupper(*str) && islower(*(str+1)))
          || ((islower(prev)||isdigit(prev)) && isupper(*str))) {
        *cp++ = '_';
      }
      
      if (*str == '-') {
        *cp++ = '_';
      } else {
        *cp++ = tolower(*str);
      }
    }
  }
  *cp = '\0';
  return newstr;
}

char * //FIXME Pretty sure this is segfaulting.
inflector_parameterize(char *str, char *sep)
{
  bool separated = true;
  int sep_len = strlen(sep);
  char *newstr = malloc((strlen(str)*strlen(sep)+1)*sizeof(char));
  char *cp;
  

  for (cp=newstr; *str != '\0'; str++) {
    if (isalnum(*str) || *str == '-' || *str == '_' || *str == '+') {
      separated = false;
      *cp++ = tolower(*str);
    } else { 
      if (!separated && *(str+1) != '\0') { // catch end case too...
        separated = true;
        strncpy(cp, sep, sep_len);
        cp += sep_len;
      }
    }
  }
  *cp = '\0';

  // cp points to the end of the return string.
  // Get rid of trailing separators, if any.
  if (strlen(sep)) {
    while (!strncmp(sep, cp-sep_len, sep_len)) {
      cp -= sep_len;
      *cp = '\0';
    }
  }
  
  return newstr;
}

char *
inflector_dasherize(char *str)
{
  char *newstr = malloc((strlen(str)+1)*sizeof(char));
  char *cp;

  for (cp=newstr; *str != '\0'; str++) {
    if (*str == '_') {
      *cp++ = '-';
    } else {
      *cp++ = *str;
    }
  }
  *cp = '\0';
  return newstr;
}

    char *
    inflector_demodulize(char *str)
    {
      char *last_part;
      
      for (last_part=str; *str != '\0'; str++) {
        if (*str == ':' && *(str+1) == ':') {
          last_part = str+2;
        }
      }
      return strdup(last_part);
    }

char *
inflector_camelize(char *str, bool first_letter_uppercase)
{
  bool cap_next = first_letter_uppercase;
  char *newstr = malloc((strlen(str)*2+1)*sizeof(char));
  char *cp;

  for (cp=newstr; *str != '\0'; str++) {
    if (*str == '/') {
      cap_next = true;
      *cp++ = ':';
      *cp++ = ':';
    } else if (*str == '_') {
      cap_next = true;
      /* Skip over -- don't print anything. */
    } else {
      if (cap_next) {
        *cp++ = toupper(*str);
        cap_next = false;
      } else {
        *cp++ = tolower(*str);
      }
    }
  }
  *cp = '\0';
  return newstr;
}
