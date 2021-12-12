#include "conv.h"

ConversionType determineConversionTypeFromExtension(char *name)
{
  ConversionType type = CONVERSION_UNKNOWN;
  // Check where is the last dot
  char *lastDotLocation = strrchr(name, '.');
  // Skip extension check if there is no extension
  if (lastDotLocation != NULL)
  {
    // Match extension
    if (strcmp(lastDotLocation, ".md") == 0)
      type = CONVERSION_MARKDOWN_TO_HTML;
    else if (strcmp(lastDotLocation, ".html") == 0)
      type = CONVERSION_HTML_TO_MARKDOWN;
  }
  return type;
}

#define LONGEST_EXTENSION 6 // ".html"

char *determineDefaultOutputFile(char *inputFilename, ConversionType type)
{
  // Check if ConversionType is provided
  if (!(type & (CONVERSION_HTML_TO_MARKDOWN | CONVERSION_MARKDOWN_TO_HTML)))
  {
    // This should never happen as there are checks before calling this function
    printf("INTERNAL: Conversion type wasn't provided to determine output filename\n");
    exit(EXIT_FAILURE);
  }
  // Derive output filename from input filename
  size_t inputFilenameLen = strlen(inputFilename);
  char *outputFilename = NULL;
  char newExtension[LONGEST_EXTENSION] = {0};
  // 1. Set newExtension (based on ConversionType)
  if (type == CONVERSION_HTML_TO_MARKDOWN)
  {
    strcpy(newExtension, ".md");
  }
  else if (type == CONVERSION_MARKDOWN_TO_HTML)
  {
    strcpy(newExtension, ".html");
  }
  // 2. Look for inputFilename extension to ignore
  char *lastDotLocation = strrchr(inputFilename, '.');
  if (lastDotLocation != NULL)
  {
    inputFilenameLen -= strlen(lastDotLocation);
  }
  // 3. Calloc outputFilename (inputFilenameLen w/o ext + newExtension)
  outputFilename = calloc(inputFilenameLen + strlen(newExtension) + 1, sizeof(char)); // +1 is required for '\0'
  strncpy(outputFilename, inputFilename, inputFilenameLen);                           // Copy part that won't be changed
  strcat(outputFilename, newExtension);                                               // Append new extension
  return outputFilename;
}

int convertFile(char *inputFilename, char *outputFilename, ConversionType convType)
{
  // 1. Open files
  FILE *input = fopen(inputFilename, "r");
  if (!input)
  {
    printf("Input file (%s) is not readable. Please check the provided path and/or read permissions.\n", inputFilename);
    return EXIT_FAILURE;
  }
  FILE *output = fopen(outputFilename, "w");
  if (!output)
  {
    printf("Output file (%s) is not writable. Please check the provided path and/or read permissions.\n", outputFilename);
    fclose(input);
    return EXIT_FAILURE;
  }
  // 2. Pass file handler to the right converter
  if (convType == CONVERSION_MARKDOWN_TO_HTML)
  {
    convertFileToHTML(input, output);
  }
  if (convType == CONVERSION_HTML_TO_MARKDOWN)
  {
    convertFileToMD(input, output);
  }
  fclose(input);
  fclose(output);
  return EXIT_SUCCESS;
}
