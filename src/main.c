#include "main.h"

int main(int argc, char *argv[])
{
  struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
  printf("ArgFlags: %d\n", parsedArgs.flags);
  printf("Input: %s\n", parsedArgs.inputFile);
  printf("Output: %s\n", parsedArgs.outputFile);
  return 0;
}
