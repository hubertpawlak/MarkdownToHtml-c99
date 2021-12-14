#include "tohtml.h"

size_t readFreshChunkAndWriteOldestBuffer(char **buffers, FILE *inputFile, FILE *outputFile)
{
  static size_t readLines = 0; // This will increment on each read and remain the same on failure
  // Unshift strings
  for (size_t i = 0; i < READ_BUFFERS - 1; i++) // Start with [0]<=[1], end with [n-2]<=[n-1]
  {
    strncpy(buffers[i], buffers[i + 1], READ_CHUNK_SIZE - 1);
  }
  // No magic numbers
  const size_t nextChunkIndex = READ_BUFFERS - 1;
  // Allocate new buffer and read chunk
  bool success = (fgets(buffers[nextChunkIndex], READ_CHUNK_SIZE, inputFile) != NULL && ferror(inputFile) == 0);
  if (success)
    readLines++;
  else
  {
    // Next chunk doesn't exist
    // Set first byte to '\0' to prevent loops/errors in some functions
    memset(buffers[READ_BUFFERS - 1], '\0', 1);
  }
  // Write oldest buffer to outputFile
  // Helper functions MUST only modify buffers
  if (strlen(buffers[0]) > 0)
  {
    fputs(buffers[0], outputFile);
  }
  return readLines;
}

int convertFileToHTML(FILE *inputFile, FILE *outputFile)
{
  char **buffers = malloc(READ_BUFFERS * sizeof(*buffers)); // Read buffers [prev, current, next]
  // Allocate read buffers
  for (size_t i = 0; i < READ_BUFFERS; i++)
  {
    buffers[i] = calloc(READ_CHUNK_SIZE, sizeof(char));
  }
  // Detect tags and write to outputFile
  const size_t currentChunkIndex = READ_BUFFERS - 2;
  size_t processedLines = 0; // Make sure every buffer is processed
  while (processedLines < readFreshChunkAndWriteOldestBuffer(buffers, inputFile, outputFile))
  {
    size_t chunkLen = strlen(buffers[currentChunkIndex]);
    // Skip empty buffer
    if (chunkLen == 0)
    {
      continue;
    }
    processedLines++;
    // Pass all buffers to helper functions to detect and process whole chunks
    bool skipThisFunction = false;
    processExclusiveTag(detectAndProcessHTag, &skipThisFunction, buffers);  // h[1-6]
    processExclusiveTag(detectAndProcessBrTag, &skipThisFunction, buffers); // br
    // processExclusiveTag(detectAndProcessTableTag, &skipThisFunction, buffers); // table
    // https://en.cppreference.com/w/c/string/byte/strtok
    while (detectAndProcessBIUSTags(buffers)) // b,i,u,s
    {
    }
    while (detectAndProcessImgAndLinkTags(buffers)) // img, a
    {
    }
  }
  // Free read buffers
  for (size_t i = 0; i < READ_BUFFERS; i++)
  {
    free(buffers[i]);
  }
  free(buffers);
  return EXIT_SUCCESS;
}
