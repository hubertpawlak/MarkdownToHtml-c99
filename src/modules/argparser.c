#include "argparser.h"

int getFlagsFromArgs(int argc, char *argv[])
{
  int flags = ARG_FLAG_NONE;
  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
    {
      flags = ARG_FLAG_SHOW_HELP;
      break;
    }
    // starts with "-" but it is not a valid option
    else if (strncmp(argv[i], "-", 1) == 0)
    {
      // flags = ARG_FLAG_INVALID;
      flags = ARG_FLAG_SHOW_HELP;
      break;
    }
  }
  return flags;
}
