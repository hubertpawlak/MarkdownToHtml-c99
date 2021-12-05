#include "main.h"

int main(int argc, char *argv[])
{
  struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
  ArgFlags flags = parsedArgs.flags;
  if (flags == ARG_FLAG_SHOW_HELP)
  {
    showHelp(false);
  }
  else if (flags == ARG_FLAG_INVALID || flags == ARG_FLAG_NONE)
  {
    showHelp(true);
  }
  printf("ArgFlags: %d\n", parsedArgs.flags);
  printf("Input: %s\n", parsedArgs.inputFile);
  printf("Output: %s\n", parsedArgs.outputFile);
  return 0;
}
