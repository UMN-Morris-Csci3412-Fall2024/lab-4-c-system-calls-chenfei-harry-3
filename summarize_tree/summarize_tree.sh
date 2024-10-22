#!/bin/bash

# A shell script that summarizes the number of directories and regular files

if [ $# -ne 1 ]; then
    echo "Usage: $0 <path>"
    exit 1
fi

# Use find and wc to get the counts
dir_count=$(find "$1" -type d | wc -l)
file_count=$(find "$1" -type f | wc -l)

# Print the results with precise formatting using printf
echo "Processed all the files from $1."
printf "There were %d directories.\n" $((dir_count - 1))
printf "There were %d regular files.\n" $file_count
