#!/bin/bash

DIR="$( cd "$( dirname "$0" )" && pwd )"
INPUT_DIR="${DIR}/test-files"
OUTPUT_DIR="${DIR}/out-files"

if [ -d $OUTPUT_DIR ]
then
    rm -r "$OUTPUT_DIR"
fi
mkdir -p "$OUTPUT_DIR"


for program in $(ls "$INPUT_DIR")
do
    echo "-------------------------------------------------"
    echo "Compiling ${INPUT_DIR}/${program}... "
    echo "-------------------------------------------------"
	./cpsl "${INPUT_DIR}/$program" "${OUTPUT_DIR}/${program%.*}.asm"
done

for assembly in $(ls "$OUTPUT_DIR")
do
    echo "-------------------------------------------------"
    echo "Let me show you ${OUTPUT_DIR}/${assembly}: "
    echo "-------------------------------------------------"
    cat "$OUTPUT_DIR/$assembly"
done

