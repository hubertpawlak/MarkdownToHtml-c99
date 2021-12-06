#include "unity.h"
#include "../modules/conv.h"

char *outputFile = NULL;

void setUp(void) {}

void tearDown(void)
{
  // Free allocated outputFile to prevent memory leaks!
  free(outputFile);
}

void test_conv_default_output_md_to_html(void)
{
  outputFile = determineDefaultOutputFile("test.md", CONVERSION_MARKDOWN_TO_HTML);
  TEST_ASSERT_EQUAL_STRING("test.html", outputFile);
}
void test_conv_default_output_html_to_md(void)
{
  outputFile = determineDefaultOutputFile("test.html", CONVERSION_HTML_TO_MARKDOWN);
  TEST_ASSERT_EQUAL_STRING("test.md", outputFile);
}
void test_conv_default_output_forced_txt_md_to_html(void)
{
  outputFile = determineDefaultOutputFile("test.txt", CONVERSION_MARKDOWN_TO_HTML);
  TEST_ASSERT_EQUAL_STRING("test.html", outputFile);
}
void test_conv_default_output_forced_txt_html_to_md(void)
{
  outputFile = determineDefaultOutputFile("test.txt", CONVERSION_HTML_TO_MARKDOWN);
  TEST_ASSERT_EQUAL_STRING("test.md", outputFile);
}
void test_conv_default_output_noext_txt_md_to_html(void)
{
  outputFile = determineDefaultOutputFile("test", CONVERSION_MARKDOWN_TO_HTML);
  TEST_ASSERT_EQUAL_STRING("test.html", outputFile);
}
void test_conv_default_output_noext_txt_html_to_md(void)
{
  outputFile = determineDefaultOutputFile("test", CONVERSION_HTML_TO_MARKDOWN);
  TEST_ASSERT_EQUAL_STRING("test.md", outputFile);
}

int main()
{
  UNITY_BEGIN();
  // cppcheck-suppress preprocessorErrorDirective
  RUN_TEST(test_conv_default_output_md_to_html);
  RUN_TEST(test_conv_default_output_html_to_md);
  RUN_TEST(test_conv_default_output_forced_txt_md_to_html);
  RUN_TEST(test_conv_default_output_forced_txt_html_to_md);
  RUN_TEST(test_conv_default_output_noext_txt_md_to_html);
  RUN_TEST(test_conv_default_output_noext_txt_html_to_md);
  return UNITY_END();
}
