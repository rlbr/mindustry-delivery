#!/usr/bin/bash

mkdir output
find . -maxdepth 1 -mindepth 1 -name "*.c" -print | while read c_file; do
    outname=$(basename "${c_file}" | sed 's/c$/masm/g')
    c2logic -O 2 -o "output/${outname}" "${c_file}"
done
