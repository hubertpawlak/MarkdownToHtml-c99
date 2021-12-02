#include "main.h"

int main(int argc, char *argv[])
{
  ArgFlags flags = getFlagsFromArgs(argc, argv);
  printf("ArgFlags: %d\n", flags);
  return 0;
}
