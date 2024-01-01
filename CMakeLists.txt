cmake_minimum_required(VERSION 3.10)

project(Sound)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)

set(SOURCE_FILES_PC
    src/pc/main.c
    src/pc/log.c
    src/pc/stubs.c
    src/pc/sotn.c
    src/pc/pc.c
    src/pc/sdl2.c
)

if(WIN32)
list(APPEND SOURCE_FILES_PC src/pc/plat_win.c)
else()
list(APPEND SOURCE_FILES_PC src/pc/plat_unix.c)
endif()

set(SOURCE_FILES_PSX_SDK
    src/main/psxsdk/libgpu/ext.c
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
    src/dra/lang_us.c
    src/dra/menu.c
    src/dra/5D6C4.c 
    src/dra/627C4.c
    src/dra/63ED4.c
    src/dra/91EBC.c
    src/dra/92F60.c
    src/dra/93290.c
    src/dra/93BDC.c
    src/dra/94F50.c
    src/dra/953A0.c
)

add_executable(${PROJECT_NAME} 
    ${SOURCE_FILES_PC}
    ${SOURCE_FILES_PSX_SDK}
    ${SOURCE_FILES_MOCK_SDK}
    ${SOURCE_FILES_3RD}
    ${SOURCE_FILES_DRA}
    )

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    include
    src/dra
    src/pc/3rd
    )

target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${SDL2_LIBRARIES}
    )

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    VERSION_PC
    PERMUTER
    NON_MATCHING
    DEMO_KEY_PTR=0
    _internal_version_us
    )
