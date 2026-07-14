# Generates a linker .def file that re-exports every defined external symbol
# found in the given object files / static libraries. This is the MSVC
# equivalent of -rdynamic / -export_dynamic on Linux/macOS: it lets overlay
# DLLs resolve engine functions and global data against the host exe's
# import library, without having to hand-maintain an export list.
#
# Usage:
#   cmake -DDUMPBIN=<path-to-dumpbin.exe> -DOUT=<output.def> "-DINPUTS=a;b;c" \
#         -P gen_export_def.cmake

if(NOT DUMPBIN)
    message(FATAL_ERROR "gen_export_def.cmake: DUMPBIN not set")
endif()
if(NOT OUT)
    message(FATAL_ERROR "gen_export_def.cmake: OUT not set")
endif()
if(NOT DEFINED INPUTS)
    message(FATAL_ERROR "gen_export_def.cmake: INPUTS not set")
endif()

set(_symbols "")

foreach(_input ${INPUTS})
    execute_process(
        COMMAND "${DUMPBIN}" /SYMBOLS "${_input}"
        OUTPUT_VARIABLE _dumpbin_out
        RESULT_VARIABLE _dumpbin_result
        ERROR_VARIABLE _dumpbin_err
    )
    if(NOT _dumpbin_result EQUAL 0)
        message(FATAL_ERROR "dumpbin /SYMBOLS failed on ${_input}: ${_dumpbin_err}")
    endif()

    # Escape ';' so the multi-line output survives being turned into a CMake list.
    string(REPLACE ";" "\\;" _dumpbin_out "${_dumpbin_out}")
    string(REPLACE "\n" ";" _dumpbin_lines "${_dumpbin_out}")

    foreach(_line ${_dumpbin_lines})
        # A symbol is a real definition if it lives in a numbered section
        # (SECTn, e.g. code/initialized data), or if it's an uninitialized
        # global (a C tentative definition), which dumpbin reports as
        # "<index> <nonzero-size> UNDEF ... External | name" - "UNDEF" here
        # just means "no explicit section yet", not "unresolved". A truly
        # unresolved reference is UNDEF with a zero value/size.
        if(_line MATCHES "External")
            if(_line MATCHES "^[0-9A-Fa-f]+ +([0-9A-Fa-f]+) +(SECT[0-9A-Fa-f]+|UNDEF)")
                set(_value "${CMAKE_MATCH_1}")
                set(_section "${CMAKE_MATCH_2}")
                set(_is_def FALSE)
                if(_section MATCHES "^SECT")
                    set(_is_def TRUE)
                elseif(NOT _value MATCHES "^0+$")
                    set(_is_def TRUE)
                endif()
                if(_is_def)
                    string(REGEX MATCH "\\| ([^ \t\r]+)[ \t\r]*$" _match "${_line}")
                    if(CMAKE_MATCH_1)
                        set(_name "${CMAKE_MATCH_1}")
                        if(_name MATCHES "^[A-Za-z][A-Za-z0-9_]*$")
                            list(APPEND _symbols "${_name}")
                        endif()
                    endif()
                endif()
            endif()
        endif()
    endforeach()
endforeach()

list(REMOVE_DUPLICATES _symbols)
list(SORT _symbols)

set(_def_content "EXPORTS\n")
foreach(_name ${_symbols})
    string(APPEND _def_content "    ${_name}\n")
endforeach()

file(WRITE "${OUT}" "${_def_content}")
list(LENGTH _symbols _symbols_count)
message(STATUS "gen_export_def.cmake: wrote ${OUT} with ${_symbols_count} exported symbols")
