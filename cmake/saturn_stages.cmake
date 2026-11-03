find_program(SATURN_STAGE_CARGO_BIN cargo)
if(NOT SATURN_STAGE_CARGO_BIN)
    message(FATAL_ERROR "cargo is required to convert the Saturn stages")
endif()
file(GLOB_RECURSE SATURN_STAGE_CONVERTER_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/tools/saturn/assets/src/*.rs")
set(SATURN_STAGE_SCALE_MODEL "raster" CACHE STRING
    "Saturn stage horizontal conversion model (raster or tile-groups)")
set_property(CACHE SATURN_STAGE_SCALE_MODEL PROPERTY STRINGS raster tile-groups)
option(SATURN_STAGE_ENTITY_LABELS
    "Draw Saturn stage entity IDs and params at their world positions" OFF)

enable_testing()

function(add_saturn_stage name source music test_stage)
    set(disc "${CMAKE_SOURCE_DIR}/disks/saturn")
    string(TOUPPER "${name}" upper)
    set(asset_dir "${SOTN_RUNTIME_DATA_DIR}/ST/${upper}")
    add_overlay(${name} src/pc/stages/stage_saturn.c)
    set(outputs
        "${asset_dir}/conversion-report.json"
        "${asset_dir}/saturn_stage_data.h"
        "${asset_dir}/masonry.chars.bin"
        "${asset_dir}/masonry.pal.bin"
        "${asset_dir}/music/audio.xa"
        "${asset_dir}/music/audio.cue"
        "${asset_dir}/music/xa_config.h"
        "${asset_dir}/music/xa_manifest.json")
    add_custom_command(
        OUTPUT ${outputs}
        COMMAND ${SATURN_STAGE_CARGO_BIN} run --release
                --manifest-path "${CMAKE_SOURCE_DIR}/tools/saturn/assets/Cargo.toml"
                -- map convert-psx
                "${disc}/${source}.PRG"
                "${disc}/${source}.MAP"
                "${asset_dir}"
                --scale-model "${SATURN_STAGE_SCALE_MODEL}"
        COMMAND ${SATURN_STAGE_CARGO_BIN} run --release
                --manifest-path "${CMAKE_SOURCE_DIR}/tools/saturn/assets/Cargo.toml"
                -- audio export-xa
                "${disc}/SD/${music}.PCM"
                "${asset_dir}/music"
                --file-number 25
                --channel 0
        DEPENDS
            ${SATURN_STAGE_CONVERTER_SOURCES}
            "${CMAKE_SOURCE_DIR}/tools/saturn/assets/Cargo.toml"
            "${disc}/${source}.PRG"
            "${disc}/${source}.MAP"
            "${disc}/${source}.CHR"
            "${disc}/SD/${music}.PCM"
            "${disc}/0.BIN"
            "${disc}/GAME.PRG"
            "${disc}/LOAD.MAP"
            "${disc}/RLOAD.MAP"
        VERBATIM
        COMMENT "Converting Saturn ${source} for its PC overlay slot")
    add_custom_target(${name}_pc_assets ALL DEPENDS ${outputs})
    add_dependencies(${PROJECT_NAME} ${name}_pc_assets)
    add_dependencies(${name} ${name}_pc_assets)
    target_compile_definitions(${name} PRIVATE
        SATURN_STAGE_ASSET_DIR="${asset_dir}"
        SATURN_STAGE_NATIVE_8X8)
    target_include_directories(${name} PRIVATE "${asset_dir}")
    if(SATURN_STAGE_ENTITY_LABELS)
        target_compile_definitions(${name} PRIVATE SATURN_STAGE_ENTITY_LABELS)
    endif()

    add_executable(${name}_room_test EXCLUDE_FROM_ALL
        src/pc/stages/stage_saturn_test.c
        src/pc/stages/stage_saturn.c)
    add_dependencies(${name}_room_test ${name}_pc_assets)
    target_compile_definitions(${name}_room_test PRIVATE
        SATURN_STAGE_ROOM_TEST
        ${test_stage}
        VERSION_PC
        _internal_version_us
        __psyz)
    target_include_directories(${name}_room_test PRIVATE
        include src/dra src/pc src/pc/stages tools/psyz/psyz/include "${asset_dir}")
    add_test(NAME ${name}_rooms COMMAND ${name}_room_test)
endfunction()

add_saturn_stage(stage15 STAGE_15 SD25 TEST_STAGE15)
add_saturn_stage(stage16 STAGE_16 SD26 TEST_STAGE16)
add_saturn_stage(rstage15 RSTAGE15 SD29 TEST_RSTAGE15)
add_saturn_stage(rstage16 RSTAGE16 SD2C TEST_RSTAGE16)
