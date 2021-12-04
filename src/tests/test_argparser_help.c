#include "unity.h"
#include "../modules/argparser.h"

void setUp(void) {}

void tearDown(void) {}

void test_help_flag(void)
{
  {
    const int argc = 2;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "-h";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_SHOW_HELP, parsedArgs.flags);
  }
  {
    const int argc = 2;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "--help";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_SHOW_HELP, parsedArgs.flags);
  }
}

int main()
{
  UNITY_BEGIN();
  // cppcheck-suppress preprocessorErrorDirective
  RUN_TEST(test_help_flag);
  return UNITY_END();
}
