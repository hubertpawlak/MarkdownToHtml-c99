#pragma once

#define READ_BUFFERS 3
// Most programmers use some kind of code beautifier
// limiting the amount of characters in a single line
// so this should be more than enough
#define READ_CHUNK_SIZE (1 << 10)
#define MAX_OPEN_TAGS (1 << 8)

// This file contains only definitions shared by conversion modules
void conv_def(void);
