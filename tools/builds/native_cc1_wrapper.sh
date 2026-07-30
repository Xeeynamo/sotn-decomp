#!/bin/sh

if [ "$#" -lt 4 ]; then
    echo "Usage: $0 compiler input output optimization" >&2
    exit 1
fi

compiler=$1
input=$2
output=$3
optimization=$4
out_log="${TMPDIR:-/tmp}/sotn-native-cc1-out-$$.log"

"$compiler" "-$optimization" -m2 -fsigned-char -quiet \
    "$input" -o "$output" >"$out_log" 2>&1
status=$?

# GCC 2.7 does not understand the linemarker emitted for stdc-predef.h by a
# modern host preprocessor. Suppress that harmless two-line warning.
sed '/^In file included from <command-line>:0:$/{N;/stdc-predef\.h:0: warning: unrecognized text at end of #line$/d}' \
    "$out_log"
rm -f "$out_log"

if [ "$status" -ne 0 ] || [ ! -s "$output" ]; then
    if [ "$status" -eq 0 ]; then
        status=1
        echo "Native compiler returned success but produced no output: $output" >&2
    fi
    exit "$status"
fi
