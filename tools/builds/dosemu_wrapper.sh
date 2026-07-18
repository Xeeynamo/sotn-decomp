#!/bin/bash

# Check if the required arguments are provided.
if [ "$#" -lt 3 ]; then
    echo "Usage: $0 input output optimization"
    exit 1
fi

# ninja wants unix-compatible paths to find files, 
# but dosemu wants windows paths. So we have this
# wrapper to replace the slashes
in=$(echo "$1" | tr '/' '\\')
out=$(echo "$2" | tr '/' '\\')

# We need BUILD.BAT to define the path so GO32 works. DOSEMU normally writes
# emulator failures only to its log, so use a per-process log and surface it
# when the compiler fails instead of leaving CI with an unexplained exit 33.
log_file="${TMPDIR:-/tmp}/sotn-dosemu-$$.log"
dosemu -quiet -dumb -o "$log_file" -f ./dosemurc -K . \
    -E "TOOLS\BUILDS\BUILD.BAT $in $out $3"
status=$?

if [ "$status" -ne 0 ] || [ ! -s "$2" ]; then
    if [ "$status" -eq 0 ]; then
        status=1
        echo "DOSEMU compiler returned success but produced no output: $2" >&2
    fi
    echo "DOSEMU compiler failed with exit $status: $1 -> $2" >&2
    if [ -f "$log_file" ]; then
        echo "DOSEMU log:" >&2
        tail -100 "$log_file" >&2
    fi
    exit "$status"
fi

rm -f "$log_file"
