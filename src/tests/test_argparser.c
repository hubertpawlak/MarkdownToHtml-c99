#include <stdio.h>
#include "unity.h"
#include "../modules/argparser.h"

void setUp(void) {}

void tearDown(void) {}

void test_no_flags(void)
{
  const int argc = 1;
  char *argv[argc];
  argv[0] = "prog";
  int flags = getFlagsFromArgs(argc, argv);
  TEST_ASSERT_EQUAL_INT(ARG_FLAG_NONE, flags);
}

void test_help_flag(void)
{
  const int argc = 2;
  char *argv[argc];
  argv[0] = "prog";
  argv[1] = "-h";
  int flags = getFlagsFromArgs(argc, argv);
  TEST_ASSERT_EQUAL_INT(ARG_FLAG_SHOW_HELP, flags);
}

int main(void)
{
  UNITY_BEGIN();
  // cppcheck-suppress preprocessorErrorDirective
  RUN_TEST(test_no_flags);
  RUN_TEST(test_help_flag);
  return UNITY_END();
}
