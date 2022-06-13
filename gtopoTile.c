#include <stdio.h>
#include <stdlib.h>
#include "pgmCheckingValue.h"
#include "pgmErrors.h"
#include "pgmRead.h"
#include "pgmWrite.h"
#include <math.h>
#include <unistd.h>

int main(int argc, char **argv){
  // Check argument count supplied is correct
	if (checkArgcUsageString(argc, argv[0])==0){
    return EXIT_NO_ERRORS;}
  // Check for a bad templace
  if ((!strstr(argv[5], "<row>"))|| (!strstr(argv[5], "<column>"))){
    printf("ERROR: Miscellaneous (Bad template)");
    return EXIT_MISCELLANEOUS;
  }
	// initialises fileInfo struct with default values
  FileInfo *fileValues = initialisationOfReadFileStruct();
	fileValues->width = atoi(argv[2]);
	fileValues->height = atoi(argv[3]);
  // Opens input file and reads it
	int code=0;
  FILE *inputFile = fopen(argv[1], "r");
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
  div_t output;
  // Calculate the new height and width of a tile
  output = div(fileValues->width, factor);
  int widthAdjusted = output.quot;
  output = div(fileValues->height, factor);
  int heightAdjusted = output.quot;
  int minRow=0, maxRow=heightAdjusted, minCol=0, maxCol=widthAdjusted;
  // Calculate the names of the tiled images
  char filename[1000];
  int len = strlen(argv[5]);
  char base[100] = {'\0'};
  int exitFlag=0;
  for (int i=0; i < len && exitFlag==0; i++){
    if ((argv[5][i] != '<') || (argv[5][i+1] != 'r')){
      strncat(base, &argv[5][i], 1);}
    else {
      exitFlag=1;}}
  // Write the data into the tiled output image
  for (int i=0; i<factor; i++){
    // calculate the rows and columns for each file
    minCol=0;
    maxCol=widthAdjusted;
    for (int j=0; j<factor; j++){
      // write that range to the filename
      sprintf(filename, "%s%i_%i.dem", base  , i, j);
      FILE *outputFile = fopen(filename, "w");
      // Check reading writs for that tile name
      if (access(filename, W_OK) != 0){
        printErrorStringAndDescription(EXIT_BAD_INPUT_FILE, filename);
        return EXIT_BAD_INPUT_FILE;}
      // Check if outputFile is not a valid pointer
      if (outputFile == NULL){
        printErrorStringAndDescription(EXIT_BAD_INPUT_FILE, filename);
        free(fileValues->imageData);
        return EXIT_BAD_INPUT_FILE;}
      code = writeBetweenMaxMinBinary(outputFile, fileValues, filename, nImageBytes, minRow, maxRow, minCol, maxCol);
      if (code!=0){
        return code;}
      // update the column
      maxCol+= widthAdjusted;
      minCol+= widthAdjusted;
      closeTheFile(outputFile);}
  	// update the height
    minRow+=heightAdjusted;
    maxRow+=heightAdjusted;}
  // Program successfull finished
  printSuccessString(argv[0]);
  return 0;
}
