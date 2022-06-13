#include <stdio.h>
#include <stdlib.h>
#include "pgmCheckingValue.h"
#include "pgmErrors.h"
#include "pgmRead.h"
#include "pgmWrite.h"

int main(int argc, char **argv)
	{
	// Check if correct number of arguments were provided
  if (checkArgcUsageString(argc, argv[0])==0 && argc==1){
    return EXIT_NO_ERRORS;}
  if (checkArgs(argc, 8)==1){
    // Invalid number of arguments
    printErrorStringAndDescription(EXIT_WRONG_ARG_COUNT, "");
    return EXIT_WRONG_ARG_COUNT;}
	// Open the input file and initalise the provided values correctly
	int sea = atoi(argv[5]);
	int hill = atoi(argv[6]);
	int mountain = atoi(argv[7]);
	int code=0;
	FileInfo *fileValues = initialisationOfReadFileStruct();
  fileValues->width = atoi(argv[2]);
  fileValues->height = atoi(argv[3]);
	FILE *inputFile = fopen(argv[1], "r");
	// Read to file and check whether it has read successfully
	code = readFile(argv[1],fileValues, inputFile);
	if (code!=0){
		// If not, terminate with error code
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
	char outputHolder;
	for (int heightIndex=0;heightIndex< fileValues->height; heightIndex++){
		for (int widthIndex=0; widthIndex< fileValues->width; widthIndex++){
			// Fetch the value of imageData at a specific index
			int pixelIndex = heightIndex * fileValues->width + widthIndex;
			short value = fileValues->imageData[pixelIndex];
			// Convert the value from little endian to big endian
			value = htons(value);
			// Decide what the calculated value represents in terms of a symbol
			if (value == -9999){
				printf(" ");
				outputHolder = ' ';}
			else if (value <= sea){
				printf(" ");
				outputHolder = ' ';}
			else if (value > sea && value <= hill){
				printf(".");
				outputHolder = '.';}
			else if (hill < value && value <= mountain){
				printf("^");
				outputHolder = '^';}
			else if (value > mountain){
				printf("A");
				outputHolder = 'A';}
			// Put that calculated value into the imageData and output File
			fileValues->imageData[pixelIndex] = outputHolder;
			fprintf(outputFile, "%c", outputHolder);}
		// Reached end of line so put into the file an end of line symbol
		outputHolder = '\n';
		fprintf(outputFile, "%c", outputHolder);
		printf("\n");}
	// gtopoPrintLand worked correctly so output correct output messages
	closeTheFile(outputFile);
	printSuccessString(argv[0]);
	return 0;
}
