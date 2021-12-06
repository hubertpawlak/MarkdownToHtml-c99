#include "unity.h"
#include "../modules/showhelp.h"

void setUp(void) {}

void tearDown(void) {}

void test_showhelp(void)
{
  // It should pass if the program doesn't crash
  showHelp(false);
  showHelp(true);
}

int main()
{
  UNITY_BEGIN();
  // cppcheck-suppress preprocessorErrorDirective
  RUN_TEST(test_showhelp);
  return UNITY_END();
}
