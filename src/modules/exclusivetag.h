#pragma once
#include <stdbool.h>

void processExclusiveTag(bool (*tagProcessor)(char **), bool *skipThisFunction, char **buffers);
