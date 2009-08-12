#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// inflector //////////////////////////////
char *
inflector_underscore(char *str)
{
  char *newstr = malloc(strlen(str)*sizeof(char)*2);
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

char *
inflector_dasherize(char *str)
{
  char *newstr = malloc(strlen(str)*sizeof(char));
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
inflector_camelize(char *str, bool first_letter_uppercase)
{
  bool cap_next = first_letter_uppercase;
  char *newstr = malloc(strlen(str)*sizeof(char));
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


// starts_ends_with.rb //////////////////////////////
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

// access.rb //////////////////////////////
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

// filters.rb //////////////////////////////
bool /* Ugly, but fast! */
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
  char *newstr = (char *)malloc(strlen(str)*(sizeof (char)));
  char *cp;

  while (_is_space(*str)) {
    *str++;
  }

  for (cp = newstr; *str != NULL; *str++) {
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

