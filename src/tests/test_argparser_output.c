#include "unity.h"
#include "../modules/argparser.h"

void setUp(void) {}

void tearDown(void) {}

void test_output_file_flag(void)
{
  // This should fail
  // No output file
  {
    const int argc = 2;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "-o";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_INVALID, parsedArgs.flags);
  }
  {
    const int argc = 2;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "--output";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_INVALID, parsedArgs.flags);
  }
  // This should fail
  // No input file
  {
    const int argc = 3;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "-o";
    argv[2] = "example.html";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_INVALID, parsedArgs.flags);
  }
  {
    const int argc = 3;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "--output";
    argv[2] = "example.html";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_INVALID, parsedArgs.flags);
  }
  // This should work
  {
    const int argc = 5;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "--output";
    argv[2] = "example.html";
    argv[3] = "--input";
    argv[4] = "example.md";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_OPEN_FILE | ARG_FLAG_CUSTOM_OUTPUT_FILE, parsedArgs.flags);
  }
  {
    const int argc = 5;
    char *argv[argc];
    argv[0] = "prog";
    argv[1] = "-o";
    argv[2] = "example.html";
    argv[3] = "-i";
    argv[4] = "example.md";
    struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
    TEST_ASSERT_EQUAL_INT(ARG_FLAG_OPEN_FILE | ARG_FLAG_CUSTOM_OUTPUT_FILE, parsedArgs.flags);
  }
}

int main(void)
{
  UNITY_BEGIN();
  // cppcheck-suppress preprocessorErrorDirective
  RUN_TEST(test_output_file_flag);
  return UNITY_END();
}
