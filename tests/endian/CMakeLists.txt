add_executable(sotn_endian_tests
    test_endian.c
    common/test_endian_utils.c
    common/test_types.c
)

option(SOTN_ENDIAN_SANITIZERS
       "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

target_include_directories(sotn_endian_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(sotn_endian_tests PRIVATE
    VERSION_PC
    PERMUTER
    NON_MATCHING
    HARD_LINK
    _internal_version_us
    __psyz
    NO_LOGS
)

if(MSVC)
    target_compile_options(sotn_endian_tests PRIVATE /W4)
else()
    target_compile_options(sotn_endian_tests PRIVATE
        -Wall
        -Wextra
        -Werror
        -funsigned-char
    )
    if(SOTN_ENDIAN_SANITIZERS)
        target_compile_options(sotn_endian_tests PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
        )
        target_link_options(sotn_endian_tests PRIVATE
            -fsanitize=address,undefined
        )
    endif()
endif()

add_test(NAME endian.contracts COMMAND sotn_endian_tests)
