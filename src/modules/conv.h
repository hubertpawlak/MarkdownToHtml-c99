#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tohtml.h"
#include "tomd.h"

typedef enum ConversionType
{
  CONVERSION_UNKNOWN = 0,
  CONVERSION_MARKDOWN_TO_HTML = 1,
  CONVERSION_HTML_TO_MARKDOWN = 1 << 1,
} ConversionType;

ConversionType determineConversionTypeFromExtension(char *name);

char *determineDefaultOutputFile(char *inputFilename, ConversionType type);

int convertFile(char *inputFilename, char *outputFilename, ConversionType type);
