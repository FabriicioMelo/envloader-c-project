#ifndef _ENVLOADER_H
#define _ENVLOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DOTENV_MAX_LINES 128
#define DOTENV_LINE_SIZE_LIMIT 128

#define NOTFOUND 0
#define FOUND 1

typedef struct Dotenv
{
  char Names[DOTENV_MAX_LINES][DOTENV_LINE_SIZE_LIMIT];
  char Values[DOTENV_MAX_LINES][DOTENV_LINE_SIZE_LIMIT];
  short Length;
}Dotenv;

int LoadDotenv(struct Dotenv* dotenv, char* path);
char* GetDotenv(struct Dotenv* dotenv, char* name);

#endif