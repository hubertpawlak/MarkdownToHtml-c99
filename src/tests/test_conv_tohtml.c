#include <string.h>
#include "unity.h"
#include "../modules/conv.h"

FILE *inputFile = NULL;
FILE *outputFile = NULL;

char *inputStrings[] = {
    // h
    "# h1\n",
    "## h2\n",
    "### h3\n",
    "#### h4\n",
    "##### h5\n",
    "###### h6\n",
    "####### invalid h7\n",
    "###invalid without space\n",
    "#invalid without space\n",
    "# # h1 with a #\n",
    "#\n",
    "##\n",
    // br
    "\n",
    "\n",
    "a\n",
    "\n",
    // bius
    "not *i* symmetric\n",
    "not **b** symmetric\n",
    "not *outside *inside** symmetric\n",
    "not ~~s~~ symmetric\n",
    // link
    "[text](whatever)\n",
    "not [text](whatever) symmetric\n",
    // img
    "![alt](whatever)\n",
    "not ![alt](whatever) symmetric\n",
    // ul
    "- a\n",
    "- b\n",
    "- c\n",
    "      \n",
    // ol
    "9999. a\n",
    "1. b\n",
    "7. c\n",
    "1. d\n",
    "7123. e\n",
    "18231. f\n",
    "2. g\n",
    "      \n"
    // table
    "|a|   b| a + b   |\n",
    "|-|----|---|\n",
    "| 1 |2|3|\n",
    "|x|y|\n",
    "||empty tokens|are ignored|\n",
    "| | |expect |extra cell|\n",
    "|empty| |between|\n",
    "\n",
    // extra h1
    "# last line without newline",
};
char *outputStrings[] = {
    // h1
    "<h1>h1</h1>\n",
    "<h2>h2</h2>\n",
    "<h3>h3</h3>\n",
    "<h4>h4</h4>\n",
    "<h5>h5</h5>\n",
    "<h6>h6</h6>\n",
    "####### invalid h7\n",
    "###invalid without space\n",
    "#invalid without space\n",
    "<h1># h1 with a #</h1>\n",
    "<h1></h1>\n",
    "<h2></h2>\n",
    // br
    "<br />\n",
    "a\n",
    "<br />\n",
    // bius
    "not <i>i</i> symmetric\n",
    "not <b>b</b> symmetric\n",
    "not <i>outside <i>inside</i></i> symmetric\n",
    "not <s>s</s> symmetric\n",
    // link
    "<a href=\"whatever\">text</a>\n",
    "not <a href=\"whatever\">text</a> symmetric\n",
    // img
    "<img src=\"whatever\" alt=\"alt\" />\n",
    "not <img src=\"whatever\" alt=\"alt\" /> symmetric\n",
    // ul
    "<ul>\n",
    "<li>a</li>\n",
    "<li>b</li>\n",
    "<li>c</li>\n",
    "</ul>\n",
    "\n",
    // ol
    "<ol start=\"9999\">\n",
    "<li>a</li>\n",
    "<li>b</li>\n",
    "<li>c</li>\n",
    "<li>d</li>\n",
    "<li>e</li>\n",
    "<li>f</li>\n",
    "<li>g</li>\n",
    "</ol>\n",
    "\n",
    // table
    "<table>\n",
    "<tr><td>a</td><td>   b</td><td> a + b   </td></tr>\n",
    "<tr><td>-</td><td>----</td><td>---</td></tr>\n",
    "<tr><td> 1 </td><td>2</td><td>3</td></tr>\n",
    "<tr><td>x</td><td>y</td></tr>\n",
    "<tr><td>empty tokens</td><td>are ignored</td></tr>\n",
    "<tr><td> </td><td> </td><td>expect </td><td>extra cell</td></tr>\n",
    "<tr><td>empty</td><td> </td><td>between</td></tr>\n",
    "</table>\n",
    // extra h1
    "<h1>last line without newline</h1>\n",
};
const size_t nInputLines = sizeof(inputStrings) / sizeof(*inputStrings);
const size_t nOutputLines = sizeof(outputStrings) / sizeof(*outputStrings);

void setUp(void)
{
  // Create 2 temporary files with content to test
  inputFile = tmpfile();
  outputFile = tmpfile();
  for (size_t i = 0; i < nInputLines; i++)
  {
    fputs(inputStrings[i], inputFile);
  }
  rewind(inputFile); // Go back to the beginning just like after using fopen
}

void tearDown(void)
{
  fclose(inputFile);
  fclose(outputFile);
}

void test_conv_tohtml(void)
{
  int return_code = convertFileToHTML(inputFile, outputFile);
  TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, return_code);
  // Check file content
  const int lineBufferSize = 1 << 8;
  char *buffer = calloc(lineBufferSize, sizeof(char));
  char errorIndex[22] = {0};
  rewind(outputFile); // Go back to the beginning just like after using fopen
  // Check file line by line
  for (size_t i = 0; i < nOutputLines; i++)
  {
    fgets(buffer, sizeof(char[lineBufferSize]), outputFile); // Read line
    sprintf(errorIndex, "outputStrings[%zu]", i);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(outputStrings[i], buffer, errorIndex);
  }
  free(buffer);
}

int main()
{
  UNITY_BEGIN();
  // cppcheck-suppress preprocessorErrorDirective
  RUN_TEST(test_conv_tohtml);
  return UNITY_END();
}
