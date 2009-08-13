#pragma once

char *inflector_underscore(char *str);
char *inflector_parameterize(char *str, char *sep);
char *inflector_dasherize(char *str);
char *inflector_demodulize(char *str);
char *inflector_camelize(char *str, bool first_letter_uppercase);
