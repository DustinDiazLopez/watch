#include "watch.h"

static int32_t findMatchingQuote(int32_t argc, char *argv[], int32_t startIndex, char *matching)
{
  for (int i = startIndex, j = 0; i < argc; i++)
  {
    const int len = strlen(argv[i]);
    for (int j = 0; j < len; j++)
    {
      const char c = argv[i][j];
      if (c == '\0')
      {
        continue;
      }

      if (i == startIndex && j == 0)
        continue;

      if (c == CMD_QUOTE)
      {
        *matching++ = '\0';
        return i;
      }
      else
      {
        *matching++ = c;
      }
    }
    *matching++ = ' ';
  }
  return -1;
}

static FILETIME getLastWriteTime(const char *filename)
{
  WIN32_FIND_DATA findData = {0};
  HANDLE fileHanlde = FindFirstFileA(filename, &findData);
  FILETIME lastWriteTime = {0};
  if (fileHanlde != INVALID_HANDLE_VALUE)
  {
    lastWriteTime = findData.ftLastWriteTime;
    FindClose(fileHanlde);
  }

  return lastWriteTime;
}

static BOOL changed(char *argv[], FILETIME *lastModified, int32_t index)
{
  FILETIME time = getLastWriteTime(argv[index]);
  if (CompareFileTime(&lastModified[index], &time) != 0)
  {
    lastModified[index] = time;
    return TRUE;
  }

  return FALSE;
}

int main(int argc, char *argv[])
{
  printLicense();
 
  if (argc < 3)
  {
    printUsage();
    return 0;
  }

  const int32_t MS = atoi(argv[1]);
  char cmd[CMD_LENGTH];
  int32_t cmdEndIdx = findMatchingQuote(argc, argv, 2, cmd);

  const int32_t filesStartIdx = cmdEndIdx + 1;

  FILETIME lastModified[MAX_FILES];
  printf("\rInitilizing watch... (please wait)\n");
  for (int32_t i = filesStartIdx; i < argc; ++i)
  {
    lastModified[i] = getLastWriteTime(argv[i]);
    Sleep(100);
  }

  BOOL animate = TRUE;
  for (;;)
  {
    printf("\rWatching%s", animate ? "." : "...");
    animate = !animate;
    for (int32_t i = filesStartIdx; i < argc; ++i)
    {
      if (changed(argv, lastModified, i))
      {
        printf("\rDetected changes");
        printf("\nExecuting: '%s'\n", cmd);
        system(cmd);
      }
    }
    Sleep(MS);
  }
}