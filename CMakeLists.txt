cmake_minimum_required(VERSION 3.10)

project(Sound)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
  set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
  set(CMAKE_BUILD_TYPE Debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-implicit-function-declaration")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-return-type")
endif()

find_package(SDL2 REQUIRED)

set(SOURCE_FILES_PC
    src/pc/log.c
    src/pc/stubs.c
    src/pc/sotn.c
    src/pc/pc.c
    src/pc/str.c
    src/pc/sim_pc.c
    src/pc/pl_ric.c
    src/pc/stage_dummy.c
)

if(WIN32)
list(APPEND SOURCE_FILES_PC src/pc/plat_win.c)
else()
list(APPEND SOURCE_FILES_PC src/pc/plat_unix.c)
endif()

set(SOURCE_FILES_PSX_SDK
    src/main/psxsdk/libgpu/ext.c
    src/main/psxsdk/libgpu/prim.c
)

set(SOURCE_FILES_MOCK_SDK
    src/pc/psxsdk/libapi.c
    src/pc/psxsdk/libetc.c
    src/pc/psxsdk/libgpu.c
    src/pc/psxsdk/libgte.c
    src/pc/psxsdk/libgs.c
    src/pc/psxsdk/libcd.c
    src/pc/psxsdk/libcard.c
    src/pc/psxsdk/libspu.c
    src/pc/psxsdk/libsnd.c
    src/pc/psxsdk/cdc.c
)

set(SOURCE_FILES_3RD
   src/pc/3rd/cJSON/cJSON.c
)

set(SOURCE_FILES_DRA
    src/dra/42398.c
    src/dra/play.c
    src/dra/loading.c
    src/dra/pads.c
    src/dra/save_mgr_pre.c
    src/dra/save_mgr.c
    src/dra/4A538.c
    src/dra/collider.c
    src/dra/demo.c
    src/dra/5087C.c
    src/dra/lba_stage.c
    src/dra/config_us.c
    src/dra/menu.c
    src/dra/5D5BC.c
    src/dra/627C4.c
    src/dra/63ED4.c
    src/dra/692E8.c
    src/dra/6D59C.c
    src/dra/704D0.c
    src/dra/71830.c
    src/dra/72BB0.c
    #src/dra/75F54.c # unable to link it, the file needs to be splitted
    #src/dra/7A4D0.c # loads of unimplemented calls and symbols
    src/dra/7E4BC.c
    src/dra/d_DBD4.c
    src/dra/d_E294.c
    src/dra/843B0.c
    #src/dra/8D3E8.c # countless unimplemented symbols
    src/dra/90264.c
    src/dra/91EBC.c
    src/dra/92F60.c
    src/dra/93290.c
    src/dra/93BDC.c
    src/dra/94F50.c
    src/dra/953A0.c
)

set(SOURCE_FILES_STAGE_SEL
    src/pc/stage_sel.c
    src/st/sel/banks.c
    src/st/sel/CD54.c
    src/st/sel/2C048.c
    src/st/sel/33164.c
    src/st/sel/3410C.c
    src/st/sel/3585C.c
    src/st/sel/3642C.c
)

# organization is:
# two executables, sdl2 and null, plus a shared library "core"
# any executable links core (which is pc shared code + sotn psx code)
# the null backend is present to try and help with developing a backend-agnostic interface
# and for a basic "does it segfault" check in CI

# core library

set(SOURCE_FILES_CORE
    ${SOURCE_FILES_DRA}
    ${SOURCE_FILES_PC}
    ${SOURCE_FILES_PSX_SDK}
    ${SOURCE_FILES_MOCK_SDK}
    ${SOURCE_FILES_3RD}
    ${SOURCE_FILES_DRA}
    ${SOURCE_FILES_STAGE_SEL}
)

add_library(core ${SOURCE_FILES_CORE})

target_include_directories(core PRIVATE
    include
    src/dra
    src/pc/3rd
    )

target_compile_definitions(core PRIVATE
    _USE_MATH_DEFINES # needed for msvc
    VERSION_PC
    PERMUTER
    NON_MATCHING
    HARD_LINK
    DEMO_KEY_PTR=0
    _internal_version_us
    )

# sdl2 target

add_executable(${PROJECT_NAME}
    src/pc/sdl2.c
    )

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    include
    src/dra
    src/pc/3rd
    )

if (WIN32)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES} core)
else()
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES} core m)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    _USE_MATH_DEFINES # needed for msvc
    VERSION_PC
    PERMUTER
    NON_MATCHING
    HARD_LINK
    DEMO_KEY_PTR=0
    _internal_version_us
    )

# null target

add_executable(${PROJECT_NAME}_null
    src/pc/null.c
    )

target_include_directories(${PROJECT_NAME}_null PRIVATE
    include
    src/dra
    src/pc/3rd
    )

if (WIN32)
target_link_libraries(${PROJECT_NAME}_null PRIVATE
    core)
else()
target_link_libraries(${PROJECT_NAME}_null PRIVATE
    core m)
endif()

target_compile_definitions(${PROJECT_NAME}_null PRIVATE
    _USE_MATH_DEFINES # needed for msvc
    VERSION_PC
    PERMUTER
    NON_MATCHING
    HARD_LINK
    DEMO_KEY_PTR=0
    _internal_version_us
    )
