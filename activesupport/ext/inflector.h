#pragma once
#include <stdbool.h>

#ifdef BUILD_TEST
void test_inflector();
#endif

char *inflector_underscore(char *str);
char *inflector_parameterize(char *str, char *sep);
char *inflector_dasherize(char *str);
char *inflector_demodulize(char *str);
char *inflector_camelize(char *str, bool first_letter_uppercase);
char *inflector_foreign_key(char *str, bool use_underscore);
char *inflector_ordinalize(int n);
