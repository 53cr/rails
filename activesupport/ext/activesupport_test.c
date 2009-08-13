#define BUILD_TEST
#include "CUnit/basic.h"

#include "inflector.h"
#include "core_ext/string/starts_ends_with.h"
#include "core_ext/string/access.h"
#include "core_ext/string/filters.h"

int
main()
{
  test_inflector();
}
