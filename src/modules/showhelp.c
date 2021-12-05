#include "showhelp.h"

void showHelp(bool argsAreInvalid)
{
  if (argsAreInvalid)
  {
    printf("Provided arguments are invalid.\n");
  }
  printf("Usage: ./program [OPTIONS]\n");
  // TODO: Show available options
  printf("Example: ./program -i file.md -o file.html\n");
}
