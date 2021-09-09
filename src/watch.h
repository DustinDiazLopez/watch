#ifndef WATCH_H
#define WATCH_H

#include <windows.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_FILES 256
#define CMD_LENGTH 1024
#define CMD_QUOTE '\''

static int32_t findMatchingQuote(int32_t argc, char *argv[], int32_t startIndex, char *matching);
static FILETIME getLastWriteTime(const char *filename);
static BOOL changed(char *argv[], FILETIME *lastModified, int32_t index);

static void printUsage()
{
  printf("Missing argument:");
  printf("\nUsage: \n\twatch [sleep] '[cmd]' [...files]");
  printf("\nExample: \n\twatch 750 'g++ -O2 file.cpp' file.cpp file2.cpp");
  printf("\nLIMITS:");
  printf("\n\tFiles with spaces is not supported");
  printf("\n\tMax files: %d (modify source code if you want more [line #: %d]) \n\t\treason: didn't want to dynamically allocate memory",
         MAX_FILES,
         5);
}

static void printLicense()
{
  printf("\nwatch  Copyright (C) 2021  DustinDiazLopez\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions. For more details about warranty and/or conditions\nplease visit: https://github.com/DustinDiazLopez/watch/blob/main/LICENSE\n\n");
}

#endif