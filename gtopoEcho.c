#include <stdio.h>
#include <stdlib.h>
#include "pgmCheckingValue.h"
#include "pgmErrors.h"
#include "pgmRead.h"
#include "pgmWrite.h"

int main(int argc, char **argv)
	{
	// Check if correct number of arguments were provided
  if (checkArgcUsageString(argc, argv[0])==0){
    return EXIT_NO_ERRORS;}
  if (checkArgs(argc, 5)==1){
    // Invalid number of arguments
    printErrorStringAndDescription(EXIT_WRONG_ARG_COUNT, "");
    return EXIT_WRONG_ARG_COUNT;}
	// Open the input file and initialise it
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
	FILE *outputFile = fopen(argv[4], "w");
	// Write to file the content of input file
	code = writeToFile(outputFile, fileValues, argv[4], nImageBytes);
	// Check if it has written successfully
	if (code!=0){
		return code;}
	closeTheFile(outputFile);
	printSuccessString(argv[0]);
	return 0;
}
