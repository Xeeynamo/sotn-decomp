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
# This wrapper is invoked as `sh dosemu_wrapper.sh`, ignoring the shebang, so
# stick to POSIX sh (no PIPESTATUS, no process substitution).
out_log="${TMPDIR:-/tmp}/sotn-dosemu-out-$$.log"
rc_file="${SOTN_DOSEMURC:-$(dirname "$0")/dosemurc}"
dosemu -quiet -dumb -o "$log_file" -f "$rc_file" -K . \
    -E "TOOLS\BUILDS\BUILD.BAT $in $out $3" >"$out_log" 2>&1
status=$?
# The bundled Cygnus GCC 2.7 doesn't understand the linemarker format used by
# the host's modern cpp to auto-include stdc-predef.h, so it emits this
# harmless two-line warning on every single compile. Filter it out.
# dosemu's output uses DOS line endings, so strip \r before matching $.
tr -d '\r' <"$out_log" | sed '/^In file included from <command-line>:0:$/{N;/stdc-predef\.h:0: warning: unrecognized text at end of #line$/d}'
rm -f "$out_log"

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
