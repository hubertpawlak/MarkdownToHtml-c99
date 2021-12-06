#include "unity.h"
#include "../modules/conv.h"
void setUp(void) {}

void tearDown(void) {}

void test_conv_type(void)
{
  TEST_ASSERT_EQUAL_INT(CONVERSION_MARKDOWN_TO_HTML, determineConversionTypeFromExtension("test.md"));
  TEST_ASSERT_EQUAL_INT(CONVERSION_HTML_TO_MARKDOWN, determineConversionTypeFromExtension("test.html"));
  TEST_ASSERT_EQUAL_INT(CONVERSION_UNKNOWN, determineConversionTypeFromExtension("testmd"));
  TEST_ASSERT_EQUAL_INT(CONVERSION_UNKNOWN, determineConversionTypeFromExtension("testhtml"));
}

int main()
{
  UNITY_BEGIN();
  // cppcheck-suppress preprocessorErrorDirective
  RUN_TEST(test_conv_type);
  return UNITY_END();
}
