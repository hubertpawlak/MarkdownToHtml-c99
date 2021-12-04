#include "argparser.h"

bool skipNextArg = false;

struct ParsedArgs getParsedArgs(int argc, char *argv[])
{
  ArgFlags flags = ARG_FLAG_NONE;
  struct ParsedArgs parsedArgs = {flags, "", ""};
  // Check args one by one
  for (int i = 1; i < argc; i++)
  {
    if (skipNextArg)
    {
      skipNextArg = false;
      continue;
    }
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
    {
      flags = ARG_FLAG_SHOW_HELP;
      break;
    }
    else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0)
    {
      flags += ARG_FLAG_OPEN_FILE;
      // and get the filename from next arg
      if (i + 1 < argc)
      {
        skipNextArg = true;
        strncpy(parsedArgs.inputFile, argv[i + 1], 255);
      }
      else
      {
        flags = ARG_FLAG_INVALID;
        break;
      }
    }
    else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)
    {
      flags += ARG_FLAG_CUSTOM_OUTPUT_FILE;
      // and get the filename from next arg
      if (i + 1 < argc)
      {
        skipNextArg = true;
        strncpy(parsedArgs.outputFile, argv[i + 1], 255);
      }
      else
      {
        flags = ARG_FLAG_INVALID;
        break;
      }
    }
    else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--force") == 0)
    {
      flags += ARG_FLAG_OVERWRITE_FILE;
    }
    else if (strcmp(argv[i], "--html") == 0)
    {
      flags += ARG_FLAG_FORCE_HTML;
    }
    else if (strcmp(argv[i], "--md") == 0)
    {
      flags += ARG_FLAG_FORCE_MARKDOWN;
    }
    // starts with "-" but it is not a valid option
    else if (strncmp(argv[i], "-", 1) == 0)
    {
      flags = ARG_FLAG_INVALID;
      break;
    }
  }
  // Check if some tags have their required partner
  if (!(flags & ARG_FLAG_OPEN_FILE))
  {                                                                                                                      // Required
    if (flags & (ARG_FLAG_CUSTOM_OUTPUT_FILE | ARG_FLAG_OVERWRITE_FILE | ARG_FLAG_FORCE_HTML | ARG_FLAG_FORCE_MARKDOWN)) // By
    {
      flags = ARG_FLAG_INVALID;
    }
  }
  // Prepare struct to return
  parsedArgs.flags = flags;
  return parsedArgs;
}
