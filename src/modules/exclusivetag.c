#include "exclusivetag.h"

void processExclusiveTag(bool (*tagProcessor)(char **), bool *skipThisFunction, char **buffers)
{
  if (*skipThisFunction)
  {
    return;
  }
  *skipThisFunction = (*tagProcessor)(buffers);
}
