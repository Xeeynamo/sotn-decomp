set(SOURCE_FILES_STAGE_SATURN15
    src/pc/stages/stage_saturn15.c)

add_overlay(stage15 ${SOURCE_FILES_STAGE_SATURN15})

find_program(STAGE15_CARGO_BIN cargo)
if(NOT STAGE15_CARGO_BIN)
    message(FATAL_ERROR "cargo is required to convert Saturn Stage 15")
endif()
file(GLOB_RECURSE STAGE15_CONVERTER_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/tools/saturn/assets/src/*.rs")
set(STAGE15_ASSET_DIR "${SOTN_RUNTIME_DATA_DIR}/ST/STAGE15")
set(STAGE15_SCALE_MODEL "raster" CACHE STRING
    "Stage 15 horizontal conversion model (raster or tile-groups)")
set_property(CACHE STAGE15_SCALE_MODEL PROPERTY STRINGS raster tile-groups)
option(STAGE15_ENTITY_LABELS
    "Draw Stage 15 entity IDs and params at their world positions" OFF)

add_custom_command(
    OUTPUT "${STAGE15_ASSET_DIR}/conversion-report.json"
           "${STAGE15_ASSET_DIR}/stage15_data.h"
           "${STAGE15_ASSET_DIR}/stage15_masonry.chars.bin"
           "${STAGE15_ASSET_DIR}/stage15_masonry.pal.bin"
           "${STAGE15_ASSET_DIR}/music/audio.xa"
           "${STAGE15_ASSET_DIR}/music/audio.cue"
           "${STAGE15_ASSET_DIR}/music/xa_config.h"
           "${STAGE15_ASSET_DIR}/music/xa_manifest.json"
    COMMAND ${STAGE15_CARGO_BIN} run --release
            --manifest-path "${CMAKE_SOURCE_DIR}/tools/saturn/assets/Cargo.toml"
            -- map convert-psx
            "${CMAKE_SOURCE_DIR}/disks/saturn/STAGE_15.PRG"
            "${CMAKE_SOURCE_DIR}/disks/saturn/STAGE_15.MAP"
            "${STAGE15_ASSET_DIR}"
            --scale-model "${STAGE15_SCALE_MODEL}"
    COMMAND ${STAGE15_CARGO_BIN} run --release
            --manifest-path "${CMAKE_SOURCE_DIR}/tools/saturn/assets/Cargo.toml"
            -- audio export-xa
            "${CMAKE_SOURCE_DIR}/disks/saturn/SD/SD25.PCM"
            "${STAGE15_ASSET_DIR}/music"
            --file-number 25
            --channel 0
    DEPENDS
        ${STAGE15_CONVERTER_SOURCES}
        "${CMAKE_SOURCE_DIR}/tools/saturn/assets/Cargo.toml"
        "${CMAKE_SOURCE_DIR}/disks/saturn/STAGE_15.PRG"
        "${CMAKE_SOURCE_DIR}/disks/saturn/STAGE_15.MAP"
        "${CMAKE_SOURCE_DIR}/disks/saturn/STAGE_15.CHR"
        "${CMAKE_SOURCE_DIR}/disks/saturn/SD/SD25.PCM"
        "${CMAKE_SOURCE_DIR}/disks/saturn/0.BIN"
        "${CMAKE_SOURCE_DIR}/disks/saturn/GAME.PRG"
        "${CMAKE_SOURCE_DIR}/disks/saturn/LOAD.MAP"
    VERBATIM
    COMMENT "Converting Saturn Stage 15 for its PC overlay slot")

add_custom_target(stage15_pc_assets ALL
    DEPENDS "${STAGE15_ASSET_DIR}/conversion-report.json"
            "${STAGE15_ASSET_DIR}/stage15_data.h"
            "${STAGE15_ASSET_DIR}/stage15_masonry.chars.bin"
            "${STAGE15_ASSET_DIR}/stage15_masonry.pal.bin"
            "${STAGE15_ASSET_DIR}/music/audio.xa"
            "${STAGE15_ASSET_DIR}/music/audio.cue"
            "${STAGE15_ASSET_DIR}/music/xa_config.h"
            "${STAGE15_ASSET_DIR}/music/xa_manifest.json")
add_dependencies(${PROJECT_NAME} stage15_pc_assets)
add_dependencies(stage15 stage15_pc_assets)
target_compile_definitions(stage15 PRIVATE
    STAGE15_ASSET_DIR="${STAGE15_ASSET_DIR}"
    STAGE15_NATIVE_8X8)
target_include_directories(stage15 PRIVATE "${STAGE15_ASSET_DIR}")
if(STAGE15_ENTITY_LABELS)
    target_compile_definitions(stage15 PRIVATE STAGE15_ENTITY_LABELS)
endif()
