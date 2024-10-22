#!/bin/bash

# A shell script that summarizes the number of directories and regular files

if [ $# -ne 1 ]; then
    echo "Usage: $0 <path>"
    echo "       where <path> is the file or root of the tree you want to summarize."
    exit 1
fi

# Use find and wc to get the counts
dir_count=$(find "$1" -type d | wc -l)
file_count=$(find "$1" -type f | wc -l)

# Print the results 
echo "There were $dir_count directories."
echo "There were $file_count regular files."
