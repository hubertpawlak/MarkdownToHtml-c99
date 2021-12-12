#include "tohtml_bius.h"

bool detectAndProcessBIUSTags(char **buffers)
{
  char *buffer = buffers[READ_BUFFERS - 2];
  BIUSTag detectedTag = BIUS_NONE;
  // Look for b, i, u tag
  char *firstAsterisk = strchr(buffer, '*');
  char *lastAsterisk = strrchr(buffer, '*');
  do
  {
    if (firstAsterisk == NULL || lastAsterisk == NULL || lastAsterisk - firstAsterisk <= 1)
    {
      break;
    }
    else
    {
      detectedTag++;
    }
  } while (firstAsterisk[detectedTag] == '*' &&
           lastAsterisk[-detectedTag] == '*' &&
           &lastAsterisk[-detectedTag] - &firstAsterisk[detectedTag] > 1 &&
           detectedTag < 7 && // 0b111
           detectedTag >= 0);
  if (detectedTag)
  {
    size_t bufferLen = strlen(buffer);
    size_t preBufferLen = bufferLen - strlen(firstAsterisk) + 1;
    size_t afterBufferLen = strlen(lastAsterisk);
    char *preBuffer = calloc(preBufferLen, sizeof(char));
    char *insideBuffer = calloc(bufferLen, sizeof(char));
    char *afterBuffer = calloc(afterBufferLen, sizeof(char));
    strncpy(preBuffer, buffer, bufferLen - strlen(firstAsterisk));
    strncpy(insideBuffer,
            firstAsterisk + detectedTag,
            (lastAsterisk - detectedTag) - (firstAsterisk + detectedTag) + 1);
    strcpy(afterBuffer, lastAsterisk + 1);
    // pre + <x>*3 + inside + </x>*3 + after
    char format[] = "%s%s%s%s%s%s%s%s%s";
    sprintf(buffer, format,
            preBuffer,
            (detectedTag & BIUS_I) ? "<i>" : "",
            (detectedTag & BIUS_B) ? "<b>" : "",
            (detectedTag & BIUS_U) ? "<u>" : "",
            insideBuffer,
            (detectedTag & BIUS_U) ? "</u>" : "",
            (detectedTag & BIUS_B) ? "</b>" : "",
            (detectedTag & BIUS_I) ? "</i>" : "",
            afterBuffer);
    free(preBuffer);
    free(insideBuffer);
    free(afterBuffer);
  }
  else
  {
    // Look for s tag
    char *firstTilde = strchr(buffer, '~');
    char *lastTilde = strrchr(buffer, '~');
    if (firstTilde != NULL &&
        lastTilde != NULL &&
        lastTilde - firstTilde >= 4 && // At least "~~x~~"
        strncmp(firstTilde, "~~", 2) == 0 &&
        strncmp(lastTilde - 1, "~~", 2) == 0)
    {
      detectedTag = BIUS_S; // Not used here, but used to determine returned bool
      size_t bufferLen = strlen(buffer);
      size_t preBufferLen = bufferLen - strlen(firstTilde) + 1;
      size_t afterBufferLen = strlen(lastTilde);
      char *preBuffer = calloc(preBufferLen, sizeof(char));
      char *insideBuffer = calloc(bufferLen, sizeof(char));
      char *afterBuffer = calloc(afterBufferLen, sizeof(char));
      strncpy(preBuffer, buffer, bufferLen - strlen(firstTilde));
      strncpy(insideBuffer,
              firstTilde + 2, // 2 because of "~~"
              (lastTilde - 2) - (firstTilde + 2) + 1);
      strcpy(afterBuffer, lastTilde + 1);
      // pre + <s> + inside + </s> + after
      char format[] = "%s%s%s%s%s";
      sprintf(buffer, format,
              preBuffer,
              "<s>",
              insideBuffer,
              "</s>",
              afterBuffer);
      free(preBuffer);
      free(insideBuffer);
      free(afterBuffer);
    }
  }
  return detectedTag > 0; // Run again?
}
