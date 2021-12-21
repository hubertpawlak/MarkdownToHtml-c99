#include "tohtml_h.h"

bool detectAndProcessHTag(char **buffers)
{
  bool isValid = true;
  char *buffer = buffers[READ_BUFFERS - 2];
  size_t bufferLen = strlen(buffer);
  size_t hashtags = 0; // Both counter and cursor position
  while (hashtags < bufferLen && hashtags <= 6)
  {
    if (buffer[hashtags] != '#')
    {
      if (!isspace(buffer[hashtags]))
      {
        isValid = false;
      }
      break;
    }
    hashtags++;
  }
  if (isValid && hashtags > 0 && hashtags <= 6)
  {
    char *format = "<h%zu>%s</h%zu>\n";
    if (bufferLen == hashtags || bufferLen == hashtags + 1)
    {
      // Empty tag
      sprintf(buffer, format, hashtags, "", hashtags);
    }
    else
    {
      // Tag with content
      // TODO: realloc EVERY BUFFER with size ((strlen/chunksize)+1)*chunks everytime it's needed
      char *tmpBuffer = calloc(bufferLen - hashtags, sizeof(char));
      strncpy(tmpBuffer,
              // Skip text that made the tag valid
              &buffer[hashtags + 1],
              // Ignore newline (and #'s that were ignored)
              buffer[bufferLen - 1] == '\n' ? bufferLen - hashtags - 2 : bufferLen - hashtags - 1);
      sprintf(buffer, format, hashtags, tmpBuffer, hashtags);
      free(tmpBuffer);
    }
  }
  else
  {
    isValid = false;
  }
  return isValid;
}
