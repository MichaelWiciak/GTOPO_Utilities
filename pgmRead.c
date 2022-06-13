#include "pgmRead.h"
#include <stdlib.h>
#include <stdio.h>
#include "pgmCheckingValue.h"
#include "pgmErrors.h"

FileInfo *initialisationOfReadFileStruct (){
  // Creates and initialises the fileInfo structure to default values
  FileInfo *output = (FileInfo*) malloc (sizeof(FileInfo));
  output->width=0;
  output->height=0;
  output->imageData=NULL;
  // Return the pointer to this structure
  return output;
}

void closeTheFile (FILE *file){
  // close the file supplied
  fclose(file);
}


int checkIfInputFileEmpty(FILE *inputFile, char* filename){
  if (inputFile == NULL){
    printErrorStringAndDescription(EXIT_BAD_INPUT_FILE, filename);
    return EXIT_BAD_INPUT_FILE;}
  return EXIT_NO_ERRORS;
}


int readFile(char* filename, FileInfo *fileValues, FILE *inputFile){
  if (access(filename, R_OK) == -1){
    printErrorStringAndDescription(EXIT_BAD_INPUT_FILE, filename);
    return EXIT_BAD_INPUT_FILE;
  }
  // Check if file supplied is empty
  int code = checkIfInputFileEmpty(inputFile, filename);
  if (code !=0){
    return code;}

  return EXIT_NO_ERRORS;
}

int checkIfImageDataIsNULL(FileInfo *fileValues, char* filename){
  // Check if imageData is null
  if (fileValues->imageData == NULL){
    // If yes, terminate with error code and printing description of error
    printErrorStringAndDescription(EXIT_BAD_IMAGE_MALLOC_FAILED, filename);
    return EXIT_BAD_IMAGE_MALLOC_FAILED;}
  return EXIT_NO_ERRORS;
}

int readImageDataBinary(FileInfo *fileValues, long nImageBytes, FILE *inputFile, char* filename){
  if (access(filename, R_OK) == -1){
    printErrorStringAndDescription(EXIT_BAD_INPUT_FILE, filename);
    return EXIT_BAD_INPUT_FILE;
  }
  // Allocate memory on the heap for imageData
  fileValues->imageData = (short *) malloc(nImageBytes);
  // Check if malloc function worked
  if (fileValues->imageData == NULL){
    printErrorStringAndDescription(EXIT_BAD_IMAGE_MALLOC_FAILED, filename);
    return EXIT_BAD_IMAGE_MALLOC_FAILED;
  }
  int code = checkIfImageDataIsNULL(fileValues, filename);
  if (code!= 0){
    // If not, terminate with error code, free memory and close file
    closeTheFile(inputFile);
    return code;}
  // Read the data
  fread(fileValues->imageData, 1, nImageBytes, inputFile);
  return EXIT_NO_ERRORS;
}
