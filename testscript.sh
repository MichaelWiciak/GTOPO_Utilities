#!/bin/bash
make

test_gtopoEcho_noFilesProvided(){
    output=$(./gtopoEcho)
    if [ "$output" = "Usage: ./gtopoEcho inputFile width height outputFile" ]; then
        echo "PASSED gtopoEcho UsageStringTest"
    else
        echo "FAILED gtopoEcho UsageStringTest"
    fi;
    echo -e "\n"
}

test_gtopoComp_noFilesProvided(){
    output=$(./gtopoComp)
    if [ "$output" = "Usage: ./gtopoComp firstFile width height secondFile" ]; then
        echo "PASSED gtopoComp UsageStringTest"
    else
        echo "FAILED gtopoComp UsageStringTest"
    fi;
    echo -e "\n"
}

test_gtopoReduce_noFilesProvided(){
    output=$(./gtopoReduce)
    if [ "$output" = "Usage: ./gtopoReduceinput width height reduction_factor output" ]; then
        echo "PASSED gtopoReduce UsageStringTest"
    else
        echo "FAILED gtopoReduce UsageStringTest"
    fi;
    echo -e "\n"
}

test_gtopoTile_noFilesProvided(){
    output=$(./gtopoTile)
    if [ "$output" = "Usage: ./gtopoTile inputFile width height tiling_factoroutputFile_<row>_<column>" ]; then
        echo "PASSED gtopoTile UsageStringTest"
    else
        echo "FAILED gtopoTile UsageStringTest"
    fi;
    echo -e "\n"
}

test_gtopoAssemble_noFilesProvided(){
    output=$(./gtopoAssemble)
    if [ "$output" = "Usage: ./gtopoAssemble outputFile width height (row column inputFile widthheight)+" ]; then
        echo "PASSED gtopoAssemble UsageStringTest"
    else
        echo "FAILED gtopoAssemble UsageStringTest"
    fi;
    echo -e "\n"
}

test_gtopoPrintLand_noFilesProvided(){
    output=$(./gtopoPrintLand)
    if [ "$output" = "Usage: ./gtopoPrintLand inputFile width height outputFile sea hill mountain" ]; then
        echo "PASSED gtopoPrintLand UsageStringTest"
    else
        echo "FAILED gtopoPrintLand UsageStringTest"
    fi;
    echo -e "\n"
}

test_gtopoAssembleReduce_noFilesProvided(){
    output=$(./gtopoAssembleReduce)
    if [ "$output" = "Usage: ././gtopoAssembleReduce outputArray.gtopo width height (row column inputArray.gtopowidthheight)+" ]; then
        echo "PASSED gtopoAssembleReduce UsageStringTest"
    else
        echo "FAILED gtopoAssembleReduce UsageStringTest"
    fi;
    echo -e "\n"
}

test_gtopoAssembleReduce_noFilesProvided
test_gtopoPrintLand_noFilesProvided
test_gtopoAssemble_noFilesProvided
test_gtopoTile_noFilesProvided
test_gtopoReduce_noFilesProvided
test_gtopoComp_noFilesProvided
test_gtopoEcho_noFilesProvided

make clean
