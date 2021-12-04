#include "unity.h"
#include "../modules/argparser.h"

void setUp(void) {}

void tearDown(void) {}

void test_input_file_flag(void)
{
  // This should work
  {
    const int argc = 3;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "-i";
    argv[2] = "example.md";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_OPEN_FILE, parsedArgs.flags);
  }
  {
    const int argc = 3;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "--input";
    argv[2] = "example.md";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_OPEN_FILE, parsedArgs.flags);
  }
  // This should fail
  // No input file
  {
    const int argc = 2;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "--input";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_INVALID, parsedArgs.flags);
  }
}

int main(void)
{
  UNITY_BEGIN();
  // cppcheck-suppress preprocessorErrorDirective
  RUN_TEST(test_input_file_flag);
  return UNITY_END();
}
