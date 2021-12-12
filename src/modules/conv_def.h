#pragma once

#define READ_BUFFERS 3
#define READ_CHUNK_SIZE (1 << 8)
#define MAX_OPEN_TAGS (1 << 8)

// This file contains only definitions shared by conversion modules
void conv_def(void);
