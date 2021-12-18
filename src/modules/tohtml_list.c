#include "tohtml_list.h"

bool detectAndProcessListTag(char **buffers)
{
  static ListTag detectedListType = LIST_NONE; // Remember to close opened tag
  char *buffer = buffers[READ_BUFFERS - 2];
  char *tmpBuffer = NULL;
  switch (detectedListType)
  {
  case LIST_NONE:
    // Try to open ol/ul tag
    if (strncmp(buffer, "- ", 2) == 0)
    {
      detectedListType = LIST_UNORDERED;
      size_t bufferLen = strlen(buffer);
      tmpBuffer = calloc(strlen(buffer), sizeof(char));
      strncpy(tmpBuffer, &buffer[2], bufferLen - 2 - (buffer[bufferLen - 1] == '\n' ? 1 : 0)); // Skip "- " and "\n"
      sprintf(buffer, "<ul>\n<li>%s</li>\n", tmpBuffer);
    }
    else
    {
      // ol?
      char *dotPtr = strchr(buffer, '.');
      if (dotPtr != NULL && dotPtr - buffer >= 1)
      {
        bool isValid = true;
        for (long i = 0; i < dotPtr - buffer; i++)
        {
          if (!isdigit(buffer[i]))
          {
            isValid = false;
            break;
          }
        }
        if (isValid)
        {
          detectedListType = LIST_ORDERED;
          // Extract <li> content
          char *afterDotSpace = &dotPtr[2];
          size_t afterDotSpaceLen = strlen(afterDotSpace);
          tmpBuffer = calloc(strlen(buffer), sizeof(char));
          strncpy(tmpBuffer, afterDotSpace, afterDotSpaceLen - (afterDotSpace[afterDotSpaceLen - 1] == '\n' ? 1 : 0)); // Skip "N." and "\n"
          // Extract counter start
          char *beforeDotBuffer = calloc(dotPtr - buffer, sizeof(char));
          strncpy(beforeDotBuffer, buffer, dotPtr - buffer);
          sprintf(buffer, "<ol start=\"%s\">\n<li>%s</li>\n", beforeDotBuffer, tmpBuffer);
          free(beforeDotBuffer);
        }
      }
    }
    break;
  case LIST_ORDERED:
  case LIST_UNORDERED:; // Make the compiler happy
    // Continue list <li>...</li>
    // There is no need to redetect <li>
    // as detectedListType is static (list tag is still open)
    tmpBuffer = calloc(strlen(buffer), sizeof(char));
    size_t bufferLen = strlen(buffer);
    if (strncmp(buffer, "- ", 2) == 0)
    {
      strncpy(tmpBuffer, &buffer[2], bufferLen - 2 - (buffer[bufferLen - 1] == '\n' ? 1 : 0)); // Skip "- " and "\n"
      sprintf(buffer, "<li>%s</li>\n", tmpBuffer);
    }
    else
    {
      char *dotPtr = strchr(buffer, '.');
      char *afterDotSpace = &dotPtr[2];
      size_t afterDotSpaceLen = strlen(afterDotSpace);
      if (dotPtr != NULL && isspace(dotPtr[1]))
      {
        // Copy buffer to prevent overwriting
        strncpy(tmpBuffer, afterDotSpace, afterDotSpaceLen - (afterDotSpace[afterDotSpaceLen - 1] == '\n' ? 1 : 0));
        // Ignore everything before the dot and the dot itself
        sprintf(buffer, "<li>");
        strncat(buffer, tmpBuffer, afterDotSpaceLen - (afterDotSpace[afterDotSpaceLen - 1] == '\n' ? 1 : 0));
        strcat(buffer, "</li>\n");
      }
    }
    // Try to close tag
    char *nextBuffer = buffers[READ_BUFFERS - 1];
    size_t nextBufferLen = strlen(nextBuffer);
    bool closeTag = true;
    for (size_t i = 0; i < nextBufferLen; i++)
    {
      if (!isspace(nextBuffer[i]))
      {
        closeTag = false;
        break;
      }
    }
    if (closeTag)
    {
      if (detectedListType == LIST_ORDERED)
      {
        strcat(buffer, "</ol>\n");
      }
      else
      {
        strcat(buffer, "</ul>\n");
      }
      detectedListType = LIST_NONE; // This will cause other check for exclusive tags to run
    }
    break;
  default:
    break;
  }
  // Free allocated buffer
  if (tmpBuffer != NULL)
  {
    free(tmpBuffer);
  }
  return detectedListType != LIST_NONE;
}
