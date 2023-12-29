#include <stdio.h>
#include "envloader.h"

int main()
{
  char* path = ".test.env";
  Dotenv dotenv;

  if(LoadDotenv(&dotenv, path) == NOTFOUND){
    printf("Path has not been found!");
    return 0;
  }

  printf("SOMEVAR: %s", GetDotenv(&dotenv, "SOMEVAR"));
  printf("ANOTHERVAR: %s\n", GetDotenv(&dotenv, "ANOTHERVAR"));

  return 0;
}