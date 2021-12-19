#include "tohtml_table.h"

bool detectAndProcessTableTag(char **buffers)
{
  static bool tableOpened = false; // Remember if <table> is opened
  char *buffer = buffers[READ_BUFFERS - 2];
  size_t bufferLen = strlen(buffer);
  // Check if line starts and ends with '|'
  bool thisLineHasTableCells = bufferLen > 2 && buffer[0] == '|' && &buffer[bufferLen - 1] - strrchr(buffer, '|') <= 2;
  if (thisLineHasTableCells)
  {
    char *tmpBuffer = calloc(bufferLen, sizeof(char));
    strcpy(tmpBuffer, buffer); // Copy buffer as strtok is destructive
    if (!tableOpened)
    {
      // Open <table> tag and add first <tr>
      strcpy(buffer, "<table>\n<tr>");
      tableOpened = true;
    }
    else
    {
      // Open another <tr>
      strcpy(buffer, "<tr>");
    }
    char *tableCellContent = NULL;
    while ((tableCellContent = strtok(tableCellContent ? NULL : tmpBuffer, "|")))
    {
      if (strcmp(tableCellContent, "\n") == 0) // Original line ends with "|\n"
      {
        // Close <tr> on \n
        strcat(buffer, "</tr>\n");
      }
      else
      {
        strcat(buffer, "<td>");
        strcat(buffer, tableCellContent);
        strcat(buffer, "</td>");
      }
      // Go to the next cell (strtok remembers last position)
    }
    free(tmpBuffer);
  }
  else if (tableOpened)
  {
    // Check if this line is blank (which means close <table> tag)
    // Because previous line had a table
    bool closeTag = true;
    for (size_t i = 0; i < bufferLen; i++)
    {
      if (!isspace(buffer[i]))
      {
        closeTag = false;
        break;
      }
    }
    if (closeTag)
    {
      strcpy(buffer, "</table>\n");
      tableOpened = false;
    }
  }
  return tableOpened; // Skip other exclusive checks
}
