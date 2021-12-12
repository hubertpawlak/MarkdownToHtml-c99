#include "tohtml_br.h"

bool detectAndProcessBrTag(char **buffers)
{
  // Check if line contains only blank chars
  bool isValid = true;
  char *buffer = buffers[READ_BUFFERS - 2];
  char *prevBuffer = buffers[READ_BUFFERS - 3];
  int len = strlen(buffer);
  for (int i = 0; i < len; i++)
  {
    if (!isspace(buffer[i]))
    {
      isValid = false;
    }
  }
  if (isValid)
  {
    if (strncmp(prevBuffer, "<br />\n", 8) == 0 || prevBuffer[0] == '\0')
    {
      // Do not add more than one
      buffer[0] = '\0';
    }
    else
    {
      strcpy(buffer, "<br />\n");
    }
  }
  return isValid;
}
