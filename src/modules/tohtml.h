#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "exclusivetag.h"
#include "tohtml_h.h"
#include "tohtml_br.h"
#include "tohtml_bius.h"
#include "tohtml_imglink.h"
#include "tohtml_list.h"
#include "conv_def.h"

size_t readFreshChunkAndWriteOldestBuffer(char **buffers, FILE *inputFile, FILE *outputFile);

int convertFileToHTML(FILE *inputFile, FILE *outputFile);
