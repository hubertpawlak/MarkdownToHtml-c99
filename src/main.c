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
    exit(EXIT_FAILURE);
  }
  else if (flags & ARG_FLAG_OPEN_FILE)
  {
    ConversionType convType;
    if (flags & ARG_FLAG_FORCE_HTML)
    {
      convType = CONVERSION_HTML_TO_MARKDOWN;
    }
    else if (flags & ARG_FLAG_FORCE_MARKDOWN)
    {
      convType = CONVERSION_MARKDOWN_TO_HTML;
    }
    else
    {
      convType = determineConversionTypeFromExtension(parsedArgs.inputFile);
    }
    if (convType == CONVERSION_UNKNOWN)
    {
      printf("Conversion type couldn't be determined from file extension\n");
      exit(EXIT_FAILURE);
    }
  }
  return EXIT_SUCCESS;
}
