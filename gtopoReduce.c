#include <stdio.h>
#include <stdlib.h>
#include "pgmCheckingValue.h"
#include "pgmErrors.h"
#include "pgmRead.h"
#include "pgmWrite.h"
#include <math.h>

int main(int argc, char **argv){
	// Check if correct number of arguments were provided
  if (checkArgcUsageString(argc, argv[0])==0){
    return EXIT_NO_ERRORS;}
  if (checkArgs(argc, 6)==1){
    // Invalid number of arguments
    printErrorStringAndDescription(EXIT_WRONG_ARG_COUNT, "");
    return EXIT_WRONG_ARG_COUNT;}
	// Open the input file
  // initialises fileInfo struct with default values
	int code=0;
	FileInfo *fileValues = initialisationOfReadFileStruct();
  fileValues->width = atoi(argv[2]);
  fileValues->height = atoi(argv[3]);
	FILE *inputFile = fopen(argv[1], "r");
	// Read to file and check whether it has read successfully
	code = readFile(argv[1],fileValues, inputFile);
	if (code!=0){
		// If not, terminate with  error code
		return code;}
	long nImageBytes = fileValues->width * fileValues->height * sizeof(short);
	// Read image data
	code = readImageDataBinary(fileValues, nImageBytes, inputFile, argv[1]);
	// Check if successfully written imageData
	if (code !=0){
		return code;}
	closeTheFile(inputFile);
	// Open output file
  // Checks if the factor provided was an integer and terminate program if not
  code = checkIfinteger(argv[4]);
  if (code!=0){
    return code;}
  // Converts factor string to integer
  unsigned int factor = atoi(argv[4]);
  // Open file for writing
  FILE *outputFile = fopen(argv[5], "w");
  // Reduce the file and write to it
	code = writeASCIIDataInBinaryReduced(outputFile, fileValues, argv[5], nImageBytes, factor);
  //Check if successfully writteen to file
  if (code!=0){
    return code;}
  // Reduce perfomed correctly
  closeTheFile(outputFile);
  printSuccessString(argv[0]);
  return 0;
}
