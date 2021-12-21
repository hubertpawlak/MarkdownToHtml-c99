#include "tohtml_imglink.h"

bool detectAndProcessImgAndLinkTags(char **buffers)
{
  bool detectedTag = false;
  char *buffer = buffers[READ_BUFFERS - 2];
  char *openingPtr = strchr(buffer, '[');   // Also check for '!' before
  char *separatorPtr = strchr(buffer, ']'); // Also check for '(' after
  char *closingPtr = strchr(buffer, ')');
  if (openingPtr != NULL &&
      separatorPtr != NULL &&
      closingPtr != NULL &&
      separatorPtr - openingPtr >= 2 && // [x]
      closingPtr - separatorPtr >= 3 && // ](x)
      separatorPtr[1] == '(')
  {
    detectedTag = true;
    bool isImg = false;
    if (openingPtr - buffer >= 1 && openingPtr[-1] == '!')
    {
      isImg = true;
    }
    // Split data into allocated buffers
    // pre + ![alt](src) + post
    char *preBuffer = calloc(openingPtr - buffer, sizeof(char));
    char *altBuffer = calloc(separatorPtr - openingPtr, sizeof(char));
    char *srcBuffer = calloc(closingPtr - &separatorPtr[1], sizeof(char));
    char *postBuffer = calloc(strlen(closingPtr), sizeof(char));
    strncpy(preBuffer, buffer, openingPtr - buffer - (isImg ? 1 : 0));
    strncpy(altBuffer, &openingPtr[1], separatorPtr - &openingPtr[1]);
    strncpy(srcBuffer, &separatorPtr[2], closingPtr - &separatorPtr[2]);
    strncpy(postBuffer, &closingPtr[1], strlen(closingPtr));
    // Merge using format
    char imgFormat[] = "%s<img src=\"%s\" alt=\"%s\" />%s";
    char hrefFormat[] = "%s<a href=\"%s\">%s</a>%s";
    sprintf(buffer,
            isImg ? imgFormat : hrefFormat,
            preBuffer, srcBuffer, altBuffer, postBuffer);
    // Free allocates buffers
    free(preBuffer);
    free(altBuffer);
    free(srcBuffer);
    free(postBuffer);
  }
  return detectedTag;
}
