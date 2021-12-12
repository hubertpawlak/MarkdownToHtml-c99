#include "unity.h"
#include "../modules/fileexists.h"
void setUp(void) {}

void tearDown(void) {}

void test_fileexists_prevent_overwrite(void)
{
  TEST_ASSERT_EQUAL_INT(false, fileExists("unknownfile"));
  TEST_ASSERT_EQUAL_INT(true, fileExists("/dev/random"));
}

int main()
{
  UNITY_BEGIN();
  // cppcheck-suppress preprocessorErrorDirective
  RUN_TEST(test_fileexists_prevent_overwrite);
  return UNITY_END();
}
