#include "unity.h"
#include "../modules/argparser.h"

void setUp(void) {}

void tearDown(void) {}

void test_argparser_overwrite(void)
{
  // This should fail
  // No input file
  {
    const int argc = 2;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "--html";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_INVALID, parsedArgs.flags);
  }
  {
    const int argc = 2;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "--md";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_INVALID, parsedArgs.flags);
  }
  // This should pass
  {
    const int argc = 4;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "--html";
    argv[2] = "-i";
    argv[3] = "example.html";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_FORCE_HTML | ARG_FLAG_OPEN_FILE, parsedArgs.flags);
  }
  {
    const int argc = 4;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "--md";
    argv[2] = "-i";
    argv[3] = "example.md";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_FORCE_MARKDOWN | ARG_FLAG_OPEN_FILE, parsedArgs.flags);
  }
}

int main()
{
  UNITY_BEGIN();
  // cppcheck-suppress preprocessorErrorDirective
  RUN_TEST(test_argparser_overwrite);
  return UNITY_END();
}
