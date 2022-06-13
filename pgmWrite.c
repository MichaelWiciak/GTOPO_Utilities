#include "pgmWrite.h"
#include <stdlib.h>
#include <stdio.h>
#include "pgmCheckingValue.h"
#include "pgmErrors.h"

int writeToFile(FILE *outputFile, FileInfo *fileValues, char* outputFileName, long nImageBytes){
  int code;
  // Check if file is empty
  if (access(outputFileName, W_OK) == -1){
		printErrorStringAndDescription(EXIT_BAD_INPUT_FILE, outputFileName);
		return EXIT_BAD_INPUT_FILE;}
  code = fileEmptyErrorCheck(outputFile, fileValues, outputFileName);
  if (code != EXIT_NO_ERRORS){
    // Terminate with error code
    return code;}
  // Write to file
  fwrite(fileValues->imageData, sizeof(short), fileValues->width * fileValues->height, outputFile);
  return 0;
}

int fileEmptyErrorCheck(FILE *outputFile, FileInfo *fileValues, char* outputFileName){
  // Check if the file provided is NULL
  if (outputFile == NULL){
    // Terminate with error code
    free(fileValues->imageData);
    printErrorStringAndDescription(EXIT_OUTPUT_FAILED, outputFileName);
    return EXIT_OUTPUT_FAILED;}
  return EXIT_NO_ERRORS;
}


int writeASCIIDataInBinaryReduced(FILE *outputFile, FileInfo *fileValues, char* outputFileName, long nImageBytes, int factor){
  if (access(outputFileName, W_OK) == -1){
    printErrorStringAndDescription(EXIT_BAD_INPUT_FILE, outputFileName);
    return EXIT_BAD_INPUT_FILE;}
  int code=0;
  // Check if the file is empty
  code = fileEmptyErrorCheck(outputFile, fileValues, outputFileName);
  if (code != EXIT_NO_ERRORS){
    return code;}
  int row=0, column=0;
  // Same as writeReducedASCII function but the data is written in binary format
  for (short *nextGrayValue = fileValues->imageData; nextGrayValue < fileValues->imageData + nImageBytes; nextGrayValue++){
    if (row%factor==0 && column%factor==0){
      fwrite(nextGrayValue, sizeof(short), 1, outputFile);}
    if (row==(fileValues->width-1)){
      row=0;
      column+=1;}
    else{
      row+=1;}}
  return 0;
}


int writeBetweenMaxMinBinary(FILE *outputFile, FileInfo *fileValues, char* outputFileName, long nImageBytes, int minRow, int maxRow, int minCol, int maxCol){
  // Check writing permissions
  if (access(outputFileName, W_OK) == -1){
    printErrorStringAndDescription(EXIT_BAD_INPUT_FILE, outputFileName);
    return EXIT_BAD_INPUT_FILE;}
  int code=0;
  // Check if the output file is empty
  code = fileEmptyErrorCheck(outputFile, fileValues, outputFileName);
  if (code != 0){
    return code;}
  int row=0, column=0;
  size_t sizeOfWritten;
  // Iterate through each ImageData value
  for (short *nextGrayValue = fileValues->imageData; nextGrayValue < fileValues->imageData + nImageBytes; nextGrayValue++){
    // if the coordinates are in range, write them
    if (row>=minRow && row<maxRow && column>=minCol && column<maxCol){
      //printf("Row: %i Column: %i\n", row, column);
      sizeOfWritten = fwrite(nextGrayValue, sizeof(short), 1, outputFile);
      if (sizeOfWritten<0){
        free(fileValues->imageData);
        printErrorStringAndDescription(EXIT_OUTPUT_FAILED, outputFileName);
        return EXIT_OUTPUT_FAILED;
      }}
    // Update coordinates accordingly
    if (column==(fileValues->width-1)){
      column=0;
      row+=1;}
    else{
      column+=1;}}
  return EXIT_NO_ERRORS;
}
