#include "pgmErrors.h"
#include <stdio.h>
#include <string.h>

void printErrorStringAndDescription (int errorCode, char* fileNameWithError){
  // Note: fileNameWithError can be just a description in string format
  // Prints out the error description based on errorCode provided
  switch (errorCode) {
    case 1:
      printf("ERROR: Bad Argument Count \t Programme given wrong # of arguments\n");
      break;
    case 2:
      printf("ERROR: Bad File Name (%s) \t Programme failed to open a file stream\n", fileNameWithError);
      break;
    case 3:
      printf("ERROR: Bad Magic Number (%s)\tProgramme failed on a magic number\n", fileNameWithError);
      break;
    case 4:
      printf("ERROR: Bad Comment Line (%s)\t Programme failed on comment line\n", fileNameWithError);
      break;
    case 5:
      printf("ERROR: Bad Dimensions (%s)\t Programme failed on image dimensions\n", fileNameWithError);
      break;
    case 6:
      printf("ERROR: Bad Max Gray Value (%s)\t Programme failed on max gray values\n", fileNameWithError);
      break;
    case 7:
      printf("ERROR: Image Malloc Failed \t Malloc failed for image allocation\n");
      break;
    case 8:
      printf("ERROR: Bad Data (%s) \t Programme failed when reading in data\n", fileNameWithError);
      break;
    case 9:
      printf("ERROR: Output Failed (%s) \t Programme failed during output\n", fileNameWithError);
      break;
    case 10:
      printf("ERROR: Bad Layout \t Layout file for assembly went wrong\n");
      break;
    case 100:
      printf("ERROR: Miscellaneous \t(%s)\n", fileNameWithError);
      break;
  }

}

void printUsageString (char* programName){
  // Prints out the usage string for every executable program
  if (strcmp("./gtopoEcho", programName)==0){
    printf("Usage: ./gtopoEcho inputFile width height outputFile\n");
  }
  else if (strcmp("./gtopoComp", programName)==0){
    printf("Usage: ./gtopoComp firstFile width height secondFile\n");
  }
  else if (strcmp("./gtopoReduce", programName)==0){
    printf("Usage: ./gtopoReduceinput width height reduction_factor output\n");
  }
  else if (strcmp("./gtopoTile", programName)==0){
    printf("Usage: ./gtopoTile inputFile width height tiling_factoroutputFile_<row>_<column>\n");
  }
  else if (strcmp("./gtopoAssemble", programName)==0){
    printf("Usage: ./gtopoAssemble outputFile width height (row column inputFile widthheight)+\n");
  }
  else if (strcmp("./gtopoPrintLand", programName)==0){
    printf("Usage: ./gtopoPrintLand inputFile width height outputFile sea hill mountain\n");
  }
  else if (strcmp("./gtopoAssembleReduce", programName)==0){
    printf("Usage: ././gtopoAssembleReduce outputArray.gtopo width height (row column inputArray.gtopowidthheight)+\n");
  }
}

void printPGMCompOutput (int count){
  // Prints out a message for pgmComp based on count
  if (count==0){
    printf("IDENTICAL\tgtopoComp\tThe two files were identical\n");
  }
  else if (count==1){
    printf("DIFFERENT\tgtopoComp\tThe two files were not identical\n");
  }
}

void printSuccessString (char* programName){
  // Prints out the usage string for every executable program
  if (strcmp("./gtopoEcho", programName)==0){
    printf("ECHOED\t gtopoEcho\t Programme echoed the input\n");
  }
  else if (strcmp("./gtopoReduce", programName)==0){
    printf("REDUCED\t gtopoReduce\t The file was successfully reduced in size\n");
  }
  else if (strcmp("./gtopoTile", programName)==0){
    printf("TILED\t gtopoTile\t The tiles were successfully written\n");
  }
  else if (strcmp("./gtopoAssemble", programName)==0){
    printf("ASSEMBLED\t gtopoAssemble\t The full image was written\n");
  }
  else if (strcmp("./gtopoPrintLand", programName)==0){
    printf("PRINTED\t gtopoPrintLand\t The image was printed to file\n");
  }
}
