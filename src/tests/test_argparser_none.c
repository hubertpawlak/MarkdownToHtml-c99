#include "unity.h"
#include "../modules/argparser.h"

void setUp(void) {}

void tearDown(void) {}

void test_no_flags(void)
{
  const int argc = 1;
  char *argv[argc];
  argv[0] = "prog";
  struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
  TEST_ASSERT_EQUAL_INT(ARG_FLAG_NONE, parsedArgs.flags);
}

int main()
{
  UNITY_BEGIN();
  // cppcheck-suppress preprocessorErrorDirective
  RUN_TEST(test_no_flags);
  return UNITY_END();
}
