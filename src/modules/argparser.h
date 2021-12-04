#pragma once
#include <string.h>
#include <stdbool.h>

typedef enum ArgFlags
{
  ARG_FLAG_INVALID = -1,
  ARG_FLAG_NONE = 0,
  ARG_FLAG_SHOW_HELP = 1,
  ARG_FLAG_OPEN_FILE = 1 << 1,
  ARG_FLAG_OVERWRITE_FILE = 1 << 2,
  ARG_FLAG_FORCE_HTML = 1 << 3,
  ARG_FLAG_FORCE_MARKDOWN = 1 << 4,
  ARG_FLAG_CUSTOM_OUTPUT_FILE = 1 << 5,
} ArgFlags;

struct ParsedArgs
{
  ArgFlags flags;
  char inputFile[256];
  char outputFile[256];
};

struct ParsedArgs getParsedArgs(int argc, char *argv[]);
