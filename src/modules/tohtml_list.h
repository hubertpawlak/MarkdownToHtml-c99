#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "conv_def.h"

typedef enum ListTag
{
  LIST_NONE = 0,
  LIST_UNORDERED = 1,
  LIST_ORDERED = 2
} ListTag;

bool detectAndProcessListTag(char **buffers);
