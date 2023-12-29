#include "envloader.h"

short SearchFileCharSize(char* path_p)
{
  FILE* file_p;
  file_p = fopen(path_p, "r");

  fseek(file_p, 0, SEEK_END);
  int fileSize = ftell(file_p);
  fclose(file_p);

  return fileSize;
}

// It will return -1 if file is not found
// It will return  0 if file is found
int LoadDotenv(Dotenv* dotenv, char* path_p)
{
  FILE* file_p;
  file_p = fopen(path_p, "r");

  if(file_p == NULL){
    fclose(file_p);
    return NOTFOUND;
  }

  short fileSize = SearchFileCharSize(path_p);
  char* fileData_s = (char*)malloc(fileSize * sizeof(char));
  short fileDataIndex = 0;

  while(fgets(fileData_s, fileSize, file_p))
  {
    if(fileDataIndex >= DOTENV_MAX_LINES) break;
    if(fileData_s[0] == '#') continue;
    
    short dataLength = strlen(fileData_s);

    if(dataLength >= DOTENV_LINE_SIZE_LIMIT){
      printf("Ignoring line %d! Exceeding line size limit of %d", fileDataIndex+1, DOTENV_LINE_SIZE_LIMIT);
    }

    char dataVarName[128] = "";
    char dataVarValue[128] = "\0";

    short isDataVarValue = 0;
    short dataVarValueStartsAt = 1;

    for(int i = 0; i <= dataLength ; i++)
    { 
      if(fileData_s[i] == '='){
        isDataVarValue = 1;
        dataVarValueStartsAt = i + 1;
        continue;
      }
      if(isDataVarValue == 1){
        dataVarValue[i - dataVarValueStartsAt] = fileData_s[i];
      }else{
        dataVarName[i] = fileData_s[i];
      }
    }
    
    strcpy(dotenv->Names[fileDataIndex], dataVarName);
    strcpy(dotenv->Values[fileDataIndex], dataVarValue);

    fileDataIndex ++;
  }
  
  free(fileData_s);
  dotenv->Length = fileDataIndex;

  fclose(file_p);
  return FOUND;
}

char* GetDotenv(Dotenv* dotenv, char* name){
  for(int i = 0; i <= dotenv->Length; i++)
  {
    if(strcmp(dotenv->Names[i], name) == 0){
      return dotenv->Values[i];
    }
  }

  return "";
}