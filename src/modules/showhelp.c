#include "showhelp.h"

const char rawFormat[] = "  %%-%ds  %%s\n";

void showHelp(bool argsAreInvalid)
{
  char *format = calloc(strlen(rawFormat), sizeof(char));
  if (argsAreInvalid)
  {
    printf("Provided arguments are invalid.\n");
  }
  printf("Usage: ./program [OPTIONS]\n");
  printf("Options must be separate ex. \"-a -b -c\" not \"-abc\"\n");
  sprintf(format, rawFormat, HELP_PADDING);
  printf(format, "-h, --help", "Show how to use this program");
  printf(format, "-i, --input <file>", "Convert this file");
  printf(format, "-o, --output <file>", "Override default output filename");
  printf(format, "-f, --force", "Overwrite output file");
  printf(format, "--md", "Treat input file as Markdown");
  printf(format, "--html", "Treat input file as HTML");
  printf("Example: ./program -i file.md -o file.html\n");
  free(format);
}
