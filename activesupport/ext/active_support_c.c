#include "inflector.h"
#include "core_ext/string/starts_ends_with.h"
#include "core_ext/string/access.h"
#include "core_ext/string/filters.h"

#include "ruby.h"

void
Init_active_support_c()
{
  VALUE mActiveSupport = rb_define_module("ActiveSupport");
  VALUE cASC = rb_define_class_under(mActiveSupport, "ASC", rb_cObject);

  /* ActiveSupport::ASC.camelize("my_string") */
  rb_define_singleton_method(cASC, "camelize",     inflector_camelize,     2);
  rb_define_singleton_method(cASC, "demodulize",   inflector_demodulize,   1);
  rb_define_singleton_method(cASC, "dasherize",    inflector_dasherize,    1);
  rb_define_singleton_method(cASC, "foreign_key",  inflector_foreign_key,  2);
  rb_define_singleton_method(cASC, "ordinalize",   inflector_ordinalize,   1);
  rb_define_singleton_method(cASC, "parameterize", inflector_parameterize, 2);
  rb_define_singleton_method(cASC, "underscore",   inflector_underscore,   1);
}
