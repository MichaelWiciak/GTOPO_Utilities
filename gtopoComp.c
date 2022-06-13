#include <stdio.h>
#include <stdlib.h>
#include "pgmCheckingValue.h"
#include "pgmErrors.h"
#include "pgmRead.h"
#include "pgmWrite.h"

int main(int argc, char **argv){
  // Check if argument number error occured
	if (checkArgcUsageString(argc, argv[0])==0){
    return EXIT_NO_ERRORS;}
  if (checkArgs(argc, 5)==1){
    // Invalid number of arguments
    printErrorStringAndDescription(EXIT_WRONG_ARG_COUNT, "");
    return EXIT_WRONG_ARG_COUNT;}
  // Creates fileInfo struct and sets it to default values
	int code;
  FileInfo *fileValues1 = initialisationOfReadFileStruct();
	fileValues1->width = atoi(argv[2]);
	fileValues1->height = atoi(argv[3]);
  // Open the input file
	FILE *inputFile1 = fopen(argv[1], "r");
	code = readFile(argv[1],fileValues1, inputFile1);
  // Check the file has been read properly
	if (code!=0){
		return code;}
  // Calculates the size of the file
	long nImageBytes1 = fileValues1->width * fileValues1->height * sizeof(short);
  // Read the file
  code = readImageDataBinary(fileValues1, nImageBytes1, inputFile1, argv[1]);
  // Check if the data could be read
	if (code !=0){
		return code;}
	closeTheFile(inputFile1);
  // Read file 2, same everything as above
  FileInfo *fileValues2 = initialisationOfReadFileStruct();
	fileValues2->width = atoi(argv[2]);
	fileValues2->height = atoi(argv[3]);
  FILE *inputFile2 = fopen(argv[4], "r");
  code = readFile(argv[4],fileValues2, inputFile2);
  if (code!=0){
    return code;}
  long nImageBytes2 = fileValues2->width * fileValues2->height * sizeof(short);
  code = readImageDataBinary(fileValues2, nImageBytes2, inputFile2, argv[4]);
  if (code !=0){
    return code;}
  closeTheFile(inputFile2);
  // Check if the two files are logically equivalent
  int count = checkIfTwoPGMFilesAreLogicallyIdentical(fileValues1, fileValues2);
  // Display the result
  printPGMCompOutput(count);
  return 0;
}
