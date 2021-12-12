#include "main.h"

int main(int argc, char *argv[])
{
  // 0. Parse args and show help if something is wrong
  struct ParsedArgs parsedArgs = getParsedArgs(argc, argv);
  ArgFlags flags = parsedArgs.flags;
  char *inputFilename = parsedArgs.inputFile;
  char *outputFilename = parsedArgs.outputFile;
  if (flags == ARG_FLAG_SHOW_HELP)
  {
    showHelp(false);
  }
  else if (flags == ARG_FLAG_INVALID || flags == ARG_FLAG_NONE)
  {
    showHelp(true);
    exit(EXIT_FAILURE);
  }
  // 1. Input needs to be specified
  else if (flags & ARG_FLAG_OPEN_FILE)
  {
    // 2. Determine the way of conversion
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
      convType = determineConversionTypeFromExtension(inputFilename);
    }
    if (convType == CONVERSION_UNKNOWN)
    {
      printf("Conversion type couldn't be determined from file extension\n");
      exit(EXIT_FAILURE);
    }
    // 3. Determine the output filename if not provided
    if (!(flags & ARG_FLAG_CUSTOM_OUTPUT_FILE))
    {
      char *determinedOutputFilename = determineDefaultOutputFile(inputFilename, convType); // *This will allocate memory
      strncpy(outputFilename, determinedOutputFilename, FILENAME_MAX - 1);                  // Overwrite
      free(determinedOutputFilename);                                                       // * ...so it needs to be deallocated
    }
    // 4. Stop if output file exists and overwrite != enabled
    if (!(flags & ARG_FLAG_OVERWRITE_FILE) && fileExists(outputFilename))
    {
      printf("Output file (%s) already exists. Try changing the output file or force overwrite\n", outputFilename);
      exit(EXIT_FAILURE);
    }
    // 5. Read/write correct files
    convertFile(inputFilename, outputFilename, convType);
  }
  return EXIT_SUCCESS;
}
