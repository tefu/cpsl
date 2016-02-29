#!/bin/bash

DIR="$( cd "$( dirname "$0" )" && pwd )"
INPUT_DIR="${DIR}/test-files"
ASSEMBLY_DIR="${DIR}/asm-files"
OUTPUT_DIR="${DIR}/my-output"
EXPECTED_OUTPUT_DIR="${DIR}/expected-output"
MARSJAR=Mars4_4.jar

info () {
  printf "\r  [ \033[00;34m..\033[0m ] $1\n"
}

user () {
  printf "\r  [ \033[0;33m??\033[0m ] $1\n"
}

success () {
  printf "\r\033[2K  [ \033[00;32mOK\033[0m ] $1\n"
}

fail () {
  printf "\r\033[2K  [\033[0;31mFAIL\033[0m] $1\n"
  echo ''
}

compare_output () {
  FILE_DIFF=$(diff -y -W 72 $1 $2)
  if [ $? -ne 0 ]; then
    fail "Diff didn't match for $3"
    echo "$FILE_DIFF"
  else
    success "Diff matched for $3!"
  fi
}

create_dir() {
    if [ -d $1 ]
    then
        rm -r "$1"
    fi
    mkdir -p "$1"
}

create_dir "$ASSEMBLY_DIR"
create_dir "$OUTPUT_DIR"



for program in $(ls "$INPUT_DIR")
do
    info "Compiling ${INPUT_DIR}/${program}... "
	./cpsl "${INPUT_DIR}/$program" "${ASSEMBLY_DIR}/${program%.*}.asm"
done

for assembly in $(ls "$ASSEMBLY_DIR")
do
    info "Running ${assembly}..."
    OUT_FILE="${assembly%.asm}.out"
    java -Djava.awt.headless=true -jar "${DIR}/${MARSJAR}" me ic nc 1000000 "$ASSEMBLY_DIR/$assembly" 2> stderr.txt > "$OUTPUT_DIR/$OUT_FILE"
    compare_output "$OUTPUT_DIR/$OUT_FILE" "$EXPECTED_OUTPUT_DIR/$OUT_FILE" $assembly
done
