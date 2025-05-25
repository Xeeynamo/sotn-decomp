#!/bin/bash

# Check if correct number of arguments are provided
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 input output"
    exit 1
fi

# ninja wants unix-compatible paths to find files, 
# but dosemu wants windows paths. So we have this
# wrapper to replace the slashes
in=$(echo "$1" | tr '/' '\\')
out=$(echo "$2" | tr '/' '\\')

# we need BUILD.BAT to define the path so GO32 works
dosemu -quiet -dumb -f ./dosemurc -K . -E "TOOLS\BUILDS\BUILD.BAT $in $out $3"
