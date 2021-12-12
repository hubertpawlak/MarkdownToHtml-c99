#include "fileexists.h"

bool fileExists(char *filename)
{
  // Linux-only function
  // This creates a TOCTOU race condition
  bool exists = false;
  if (access(filename, F_OK) == 0)
    exists = true;
  return exists;
}
