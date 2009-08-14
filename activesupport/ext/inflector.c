#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "inflector.h"

#ifdef BUILD_TEST
void
test_inflector()
{
  CU_ASSERT_STRING_EQUAL("a","a");
}
#endif

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

char *
inflector_parameterize(char *str, char *sep)
{
  bool separated = true;
  int sep_len = strlen(sep);
  char *newstr;
  if (sep_len == 0) {
    newstr = malloc((strlen(str)+1)*sizeof(char));
  } else {
    newstr = malloc((strlen(str)*sep_len+1)*sizeof(char));
  }
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

char *
inflector_foreign_key(char *str, bool use_underscore)
{
  int len = strlen(str);
  char *ret = malloc((2*len+1)*sizeof(char));
  char *temp = inflector_underscore(inflector_demodulize(str));
  char *cp = ret;
  
  while (*cp++ = *temp++) ;

  if (use_underscore) {
    strcpy(cp-1, "_id");
  } else {
    strcpy(cp-1, "id");
  }

  return ret;
}

	
char *
_itoa(int n) {

  char tmp_char;
  int  temp;
  char *result = malloc(32*sizeof(char));
  char *ptr = result;
  char *ptr1 = result;
  
  do {
    temp = n;
    n /= 10;
    *ptr++ = "9876543210123456789" [9 + (temp - n * 10)];
  } while (n);
  
  // Apply negative sign
  if (temp < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while(ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}

char *
inflector_ordinalize(int n)
{
  char *word = _itoa(n);
  int len = strlen(word);
  realloc(word, (len+3)*sizeof(char));

  int x = n%100;
  if ((x > 10) && (x < 14)) {
    strcpy(word+len, "th");
  } else {
    switch(n % 10) {
    case 1:
      strcpy(word+len, "st");
      break;
    case 2:
      strcpy(word+len, "nd");
      break;
    case 3:
      strcpy(word+len, "rd");
      break;
    default:
      strcpy(word+len, "th");
    }
  }
  return word;
}
