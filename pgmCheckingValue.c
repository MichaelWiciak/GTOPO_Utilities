// Include the header file for this program
#include "pgmCheckingValue.h"
#include <math.h>

int checkArgs (int argCount, int targetCount){
  // If argCount = targetCount, return 1, else 0
  if (argCount != targetCount){
    return 1;
  }
  return 0;
}

int checkArgsErrors(int argc, char* filename){
  // Check if a usage string should be printed
  if (checkArgcUsageString(argc, filename)==0){
    return EXIT_NO_ERRORS;}
  // Check if three arguments were not supplied
  if (checkArgs(argc, 3)==1){
    // Invalid number of arguments, has to be 3
    printErrorStringAndDescription(EXIT_WRONG_ARG_COUNT, "");
    return EXIT_WRONG_ARG_COUNT;}
  // Since EXIT_NO_ERRORS is used by the Usage String exit and the file has to exit if usage string is printed
  // a different error code is returned
  return 999;
}

int checkIfTwoPGMFilesAreLogicallyIdentical(FileInfo *fileValues1, FileInfo *fileValues2){
  // Checks if the width, height of both files are identical
  if ((fileValues1->width) != (fileValues2->width) || (fileValues1->height) != (fileValues2->height)){
    return 1;}
  return 0;
}

int checkArgcUsageString(int argc, char* filename){
  if (checkArgs(argc, 1)==0){
    // If so, print usage string for that file
    printUsageString(filename);
    // and return error code 0 so no error as stated in the specification
    return EXIT_NO_ERRORS;}
  return 999;
}
int checkArgsErrorsForReduce(int argc, char* filename){
  // Check if usage string should be printed
  if (checkArgcUsageString(argc, filename)==0){
    return EXIT_NO_ERRORS;}
  // Check if there are four arguments
  if (checkArgs(argc, 4)==1){
    // If not, print error description and return error code
    printErrorStringAndDescription(EXIT_WRONG_ARG_COUNT, "");
    return EXIT_WRONG_ARG_COUNT;}
  return 999;
}

int checkArgsErrorsForAssemble(int argc, char* filename){
  if (checkArgcUsageString(argc, filename)==0){
    return EXIT_NO_ERRORS;}
  if (checkArgs(argc, 6)==0){
    // If not, print error description and return error code
    printErrorStringAndDescription(EXIT_WRONG_ARG_COUNT, "");
    return EXIT_WRONG_ARG_COUNT;}
  if ((argc-4)%5 != 0){
    printErrorStringAndDescription(EXIT_WRONG_ARG_COUNT, "");
    return EXIT_WRONG_ARG_COUNT;
  }
  return 999;
}

int checkArgsErrorsForAssembleReduced(int argc, char* filename){
  if (checkArgcUsageString(argc, filename)==0){
    return EXIT_NO_ERRORS;}
  if (checkArgs(argc, 7)==0){
    // If not, print error description and return error code
    printErrorStringAndDescription(EXIT_WRONG_ARG_COUNT, "");
    return EXIT_WRONG_ARG_COUNT;}
  if ((argc-5)%5 != 0){
    printErrorStringAndDescription(EXIT_WRONG_ARG_COUNT, "");
    return EXIT_WRONG_ARG_COUNT;
  }
  return 999;
}

int checkIfinteger(char* string){
  // Tries to convert a string to integer
  // Will return error if string provided cannot be converted or is less than or equal to 0
  int num = atoi(string);
  if (num==0||num<0){
    printErrorStringAndDescription(EXIT_MISCELLANEOUS, "Reduce factor is either not an integer or is less than 1");
    return EXIT_MISCELLANEOUS;
  }
  return EXIT_NO_ERRORS;
}
