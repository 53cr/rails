#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "inflector.h"

//FIXME: Find proper malloc sizes.

char *
inflector_underscore(char *str)
{
  char *newstr = malloc(strlen(str)*sizeof(char)*2+5);
  char *cp;
  char prev = NULL;

  for (cp=newstr; *str != NULL; prev=*str++) {

    // replace :: with /
    if (*str == ':' && *(str+1) == ':') {
      *cp++ = '/';
      *str++;
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
  char *newstr = malloc(strlen(str)*strlen(sep)*sizeof(char)+5);
  char *cp;

  for (cp=newstr; *str != NULL; *str++) {
    if (isalnum(*str) || *str == '-' || *str == '_' || *str == '+') {
      separated = false;
      *cp++ = tolower(*str);
    } else { 
      if (!separated && *(str+1) != '\0') { // catch end case too...
        separated = true;
        memcpy(cp, sep, sep_len);
        cp = cp+sep_len;
      }
    }
  }
  
  *cp = '\0';
  return newstr;
}

char *
inflector_dasherize(char *str)
{
  char *newstr = malloc(strlen(str)*sizeof(char)+5);
  char *cp;

  for (cp=newstr; *str != NULL; *str++) {
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
  
  for (last_part=str; *str != NULL; *str++) {
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
  char *newstr = malloc(strlen(str)*sizeof(char)+5);
  char *cp;

  for (cp=newstr; *str != NULL; *str++) {
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
