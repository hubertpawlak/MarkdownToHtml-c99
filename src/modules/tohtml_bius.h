#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "conv_def.h"

typedef enum BIUSTag
{
  BIUS_S = -1,   // This tag is special "~~"
  BIUS_NONE = 0, // The rest works like a bitmask
  BIUS_I = 1,
  BIUS_B = 1 << 1,
  BIUS_U = 1 << 2,
} BIUSTag;

bool detectAndProcessBIUSTags(char **buffers);
