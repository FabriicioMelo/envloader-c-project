#include <stdio.h>
#include <stdbool.h>
#include <envloader.h>

int main()
{
  char* path = ".test.env";
  Dotenv dotenv;

  bool envExists = LoadDotenv(&dotenv, path);

  if(!envExists){
    printf("Path has not been found!");
    return 0;
  }

  printf("SOMEVAR: %s", GetDotenv(&dotenv, "SOMEVAR"));
  printf("ANOTHERVAR: %s", GetDotenv(&dotenv, "ANOTHERVAR"));

  return 0;
}