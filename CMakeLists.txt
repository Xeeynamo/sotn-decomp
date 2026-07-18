cmake_minimum_required(VERSION 3.10)

project(sotn)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
endif()

if (MSVC)
    cmake_policy(SET CMP0091 NEW)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "$<$<CONFIG:Debug>:MultiThreadedDebugDLL>$<$<NOT:$<CONFIG:Debug>>:MultiThreadedDLL>")
endif()

# Overlay compatibility
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-implicit-function-declaration")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-incompatible-pointer-types")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-int-conversion")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-return-mismatch")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-return-type")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-implicit-function-declaration")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-return-type")
endif()

if(MSVC)
    add_compile_options(/J)  # Treat char as unsigned
else()
    add_compile_options(-funsigned-char)
endif()

find_program(SOTN_STR_BIN sotn_str
    PATHS ${CMAKE_SOURCE_DIR}/tools/sotn_str/target/release
    NO_DEFAULT_PATH)
if(NOT SOTN_STR_BIN)
    find_program(CARGO_BIN cargo)
    if(NOT CARGO_BIN)
        message(FATAL_ERROR
            "cargo is required to compile sotn_str\n"
            "https://doc.rust-lang.org/stable/cargo/getting-started/installation.html")
    endif()
    message(STATUS "sotn_str not found; building it with cargo")
    execute_process(
        COMMAND ${CARGO_BIN} build --release
                --manifest-path ${CMAKE_SOURCE_DIR}/tools/sotn_str/Cargo.toml
        RESULT_VARIABLE _sotn_str_build_result)
    if(NOT _sotn_str_build_result EQUAL 0)
        message(FATAL_ERROR "failed to build sotn_str")
    endif()
    find_program(SOTN_STR_BIN sotn_str
        PATHS ${CMAKE_SOURCE_DIR}/tools/sotn_str/target/release
        NO_DEFAULT_PATH)
    if(NOT SOTN_STR_BIN)
        message(FATAL_ERROR "sotn_str build succeeded but the binary was not found")
    endif()
endif()

set(_sotn_str_args "${SOTN_STR_BIN};cc")

# Allows to run the sotn_str pre-compiler only to selected targets
function(sotn_str_apply target)
    if(MSVC)
        sotn_str_apply_msvc(${target})
    else()
        set_target_properties(${target} PROPERTIES C_COMPILER_LAUNCHER "${_sotn_str_args}")
    endif()
endfunction()

# specific target for MSVC
function(sotn_str_apply_msvc target)
    get_target_property(_srcs ${target} SOURCES)
    file(GLOB_RECURSE _sotn_str_headers CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*.h")
    set(_inc "$<TARGET_PROPERTY:${target},INCLUDE_DIRECTORIES>")
    set(_def "$<TARGET_PROPERTY:${target},COMPILE_DEFINITIONS>")
    set(_inc_arg "$<$<BOOL:${_inc}>:/I$<JOIN:${_inc},;/I>>")
    set(_def_arg "$<$<BOOL:${_def}>:/D$<JOIN:${_def},;/D>>")

    set(_new_srcs "")
    foreach(_src ${_srcs})
        get_filename_component(_ext "${_src}" EXT)
        if(NOT _ext STREQUAL ".c")
            list(APPEND _new_srcs "${_src}")
            continue()
        endif()

        get_filename_component(_abs "${_src}" ABSOLUTE)
        file(RELATIVE_PATH _rel "${CMAKE_SOURCE_DIR}" "${_abs}")
        set(_out "${CMAKE_BINARY_DIR}/sotn_str_gen/${target}/${_rel}")
        get_filename_component(_out_dir "${_out}" DIRECTORY)

        get_source_file_property(_sdefs "${_src}" COMPILE_DEFINITIONS)
        set(_sdef_args "")
        if(_sdefs AND NOT _sdefs STREQUAL "NOTFOUND")
            foreach(_d ${_sdefs})
                list(APPEND _sdef_args "/D${_d}")
            endforeach()
        endif()

        add_custom_command(
            OUTPUT "${_out}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${_out_dir}"
            COMMAND "${CMAKE_C_COMPILER}" /nologo /E /DSOTN_STR "${_inc_arg}" "${_def_arg}" ${_sdef_args} "${_abs}" > "${_out}.i"
            COMMAND "${SOTN_STR_BIN}" process -f "${_out}.i" > "${_out}"
            DEPENDS "${_abs}" "${SOTN_STR_BIN}" ${_sotn_str_headers}
            COMMAND_EXPAND_LISTS
            VERBATIM
            COMMENT "sotn_str: re-encoding ${_rel}")
        list(APPEND _new_srcs "${_out}")
    endforeach()

    set_property(TARGET ${target} PROPERTY SOURCES "${_new_srcs}")
endfunction()

set(SOURCE_FILES_PC
    src/pc/main.c
    src/pc/stubs.c
    src/pc/sotn.c
    src/pc/replay.c
    src/pc/pc.c
    src/pc/io.c
    src/pc/sim_pc.c
    src/pc/pl_arc.c
    src/pc/pl_ric.c
    src/pc/servant_pc.c
    src/pc/stages/stage_loader.c
    src/pc/stages/overlay.c
    src/pc/weapon_pc.c
)

set(SOURCE_FILES_3RD
    src/pc/3rd/cJSON/cJSON.c
)

set(SOURCE_FILES_DRA
    src/dra/42398.c
    src/dra/game_handlers.c
    src/dra/pads.c
    src/dra/save_mgr.c
    src/dra/4A538.c
    src/dra/4AEA4.c
    src/dra/4B758.c
    src/dra/4CE2C.c
    src/dra/4DA70.c
    src/dra/collider.c
    src/dra/demo.c
    src/dra/5087C.c
    src/dra/lba_stage.c
    src/dra/config_us.c
    src/dra/menu.c
    src/dra/timeattack.c
    src/dra/5D5BC.c
    src/dra/5F60C.c
    src/dra/624DC.c
    src/dra/62DEC.c
    src/dra/d_37d8.c
    src/dra/66590.c
    src/dra/d_CD80.c
    src/dra/692E8.c
    src/dra/6BF64.c
    src/dra/alu_anim.c
    src/dra/6DF70.c
    src/dra/6E42C.c
    src/dra/6FDF8.c
    src/dra/70394.c
    src/dra/704D0.c
    src/dra/71830.c
    src/dra/7879C.c
    src/dra/7E4BC.c
    src/dra/d_DBD4.c
    src/dra/d_E294.c
    src/dra/d_10798.c
    src/dra/84B88.c
    src/dra/8A0A4.c
    src/dra/8BEF8.c
    src/dra/8C600.c
    src/dra/8D3E8.c
    src/dra/sound.c
    src/dra/sound_data.c
    src/dra/d_2217C.c
    src/dra/d_24CEC.c
    src/dra/d_2F324.c
    src/dra/d_2FE48.c
    src/dra/d_3B0D4.c
    src/dra/bss.c
)

set(SOURCE_FILES_RIC
    src/ric/pl_header.c
    src/ric/pl_main.c
    src/ric/pl_debug.c
    src/ric/pl_steps.c
    src/ric/pl_utils.c
    src/ric/pl_setstep.c
    src/ric/pl_collision.c
    src/ric/pl_blueprints.c
    src/ric/pl_whip.c
    src/ric/pl_subweapon_dummy.c
    src/ric/pl_subweapon_holywater.c
    src/ric/pl_subweapon_cross.c
    src/ric/pl_subweapons.c
    src/ric/2F8E8.c
    src/ric/319C4.c
    src/ric/spritebank0.c
    src/ric/spritebank1.c
    src/ric/spritebank2.c
    src/ric/spritebank3.c
    src/ric/pl_crash_cross.c
    src/ric/bss.c
    src/ric/d_18568.c
    src/ric/d_1859C.c
    src/ric/pl_anims.c
)

SET(SOURCE_FILES_MARIA
    src/maria/pl_header.c
    src/maria/pl_anims.c
    src/maria/pl_subweapons.c
    src/maria/pl_main.c
    src/maria/pl_debug.c
    src/maria/pl_steps.c
    src/maria/pl_setstep.c
    src/maria/pl_utils.c
    src/maria/pl_sensors.c
    src/maria/pl_collision.c
    src/maria/pl_blueprints.c
    src/maria/spritebank0.c
    src/maria/ovl_load.c
)

set(SOURCE_FILES_TT_000
    src/servant/tt_000/init.c
    src/servant/tt_000/bat.c
    src/servant/tt_000/servant_clutdata.c
    src/servant/tt_000/servant_spriteparts.c
    src/pc/servants/servant_000.c
)

set(SOURCE_FILES_TT_001
    src/servant/tt_001/init.c
    src/servant/tt_001/ghost.c
    src/servant/tt_001/servant_clutdata.c
    src/servant/tt_001/servant_spriteparts.c
    src/pc/servants/servant_001.c
)

set(SOURCE_FILES_TT_002
    src/servant/tt_002/init.c
    src/servant/tt_002/faerie.c
    src/servant/tt_002/faerie_spriteparts.c
    src/pc/servants/servant_002.c
)

set(SOURCE_FILES_STAGE_SEL
    src/pc/stages/stage_sel.c
    src/st/sel/bss.c
    src/st/sel/banks.c
    src/st/sel/764.c
    src/st/sel/CD54.c
    src/st/sel/sprites.c
    src/st/sel/F9A8.c
    src/st/sel/2C048.c
    src/st/sel/318CC.c
    src/st/sel/32D6C.c
    src/st/sel/34048.c
    src/st/sel/3410C.c
    src/st/sel/34B30.c
    src/st/sel/cutscene.c
    src/st/sel/cutscene_data.c
)

set(SOURCE_FILES_STAGE_CEN
    src/pc/stages/stage_cen.c
    src/st/cen/header.c
    src/st/cen/gen/e_laydef.c
    src/st/cen/e_init.c
    src/st/cen/gen/rooms.c
    src/st/cen/gen/e_layout.c
    src/st/cen/cutscene_data.c
    src/st/cen/stage_data.c
    src/st/cen/gen/sprites.c
    src/st/cen/background_block_init.c
    src/st/cen/e_room_bg.c
    src/st/cen/e_lock_camera.c
    src/st/cen/e_breakable.c
    src/st/cen/d_prize_drops.c
    src/st/cen/cutscene.c
    src/st/cen/e_chamber.c
    src/st/cen/e_maria.c
    src/st/cen/e_elevator.c
    src/st/cen/st_update.c
    src/st/cen/collision.c
    src/st/cen/create_entity.c
    src/st/cen/e_red_door_tiles.c
    src/st/cen/e_red_door.c
    src/st/cen/st_common.c
    src/st/cen/e_collect.c
    src/st/cen/e_misc.c
    src/st/cen/e_stage_name.c
    src/st/cen/e_particles.c
    src/st/cen/e_room_fg.c
    src/st/cen/popup.c
    src/st/cen/prim_helpers.c
)

set(SOURCE_FILES_STAGE_NZ0
    src/pc/stages/stage_nz0.c
    src/st/nz0/header.c
    src/st/nz0/bss.c
    src/st/nz0/gen/e_laydef.c
    src/st/nz0/e_init.c
    src/st/nz0/gen/rooms.c
    src/st/nz0/gen/e_layout.c
    src/st/nz0/cutscene_data.c
    src/st/nz0/stage_data.c
    src/st/nz0/gen/sprites.c
    src/st/nz0/background_block_init.c
    src/st/nz0/e_room_bg.c
    src/st/nz0/e_lock_camera.c
    src/st/nz0/e_breakable.c
    src/st/nz0/d_prize_drops.c
    src/st/nz0/e_red_eye_bust.c
    src/st/nz0/e_purple_brick.c
    src/st/nz0/e_left_secret_room_wall.c
    src/st/nz0/e_puzzle.c
    src/st/nz0/e_cannon.c
    src/st/nz0/e_elevator2.c
    src/st/nz0/e_nz0_room2.c
    src/st/nz0/e_life_max_tank.c
    src/st/nz0/e_blue_flame_table.c
    src/st/nz0/e_explosion_puff_opaque.c
    src/st/nz0/bossfight.c
    src/st/nz0/slogra.c
    src/st/nz0/gaibon.c
    src/st/nz0/e_elevator.c
    src/st/nz0/cutscene.c
    src/st/nz0/maria.c
    src/st/nz0/st_update.c
    src/st/nz0/collision.c
    src/st/nz0/create_entity.c
    src/st/nz0/e_red_door_tiles.c
    src/st/nz0/e_red_door.c
    src/st/nz0/st_common.c
    src/st/nz0/e_collect.c
    src/st/nz0/e_misc.c
    src/st/nz0/e_particles.c
    src/st/nz0/e_room_fg.c
    src/st/nz0/popup.c
    src/st/nz0/e_bone_scimitar.c
    src/st/nz0/e_axe_knight.c
    src/st/nz0/e_bloody_zombie.c
    src/st/nz0/e_skeleton.c
    src/st/nz0/e_spittle_bone.c
    src/st/nz0/e_subweapon_container.c
    src/st/nz0/e_blood_skeleton.c
    src/st/nz0/e_sealed_door.c
    src/st/nz0/e_stage_name.c
    src/st/nz0/prim_helpers.c
    src/st/nz0/e_life_up.c
)

set (SOURCE_FILES_STAGE_ST0
    src/pc/stages/stage_st0.c
    src/st/st0/header.c
    src/st/st0/bss.c
    src/st/st0/gen/e_laydef.c
    src/st/st0/e_init.c
    src/st/st0/gen/rooms.c
    src/st/st0/gen/e_layout.c
    src/st/st0/stage_data.c
    src/st/st0/gen/sprites.c
    src/st/st0/background_block_init.c
    src/st/st0/e_room_bg.c
    src/st/st0/e_lock_camera.c
    src/st/st0/2805C.c
    src/st/st0/cutscene.c
    src/st/st0/cutscene_data.c
    src/st/st0/2A218.c
    src/st/st0/2A8DC.c
    src/st/st0/title_card.c
    src/st/st0/2C564.c
    src/st/st0/2DAC8.c
    src/st/st0/prologue_scroll.c
    src/st/st0/3101C_psx.c
    src/st/st0/st_update.c
    src/st/st0/collision.c
    src/st/st0/create_entity.c
    src/st/st0/e_red_door_tiles.c
    src/st/st0/e_red_door.c
    src/st/st0/st_common.c
    src/st/st0/e_collect.c
    src/st/st0/e_misc.c
    src/st/st0/e_particles.c
    src/st/st0/e_room_fg.c
    src/st/st0/popup.c
    src/st/st0/3AB08.c
    src/st/st0/3C5C0.c
    src/st/st0/prim_helpers.c
    src/st/st0/3D8F0.c
    src/st/st0/e_bg_vortex.c
)

set(SOURCE_FILES_STAGE_WRP
    src/pc/stages/stage_wrp.c
    src/st/wrp/header.c
    src/st/wrp/sprite_banks.c
    src/st/wrp/cluts.c
    src/st/wrp/layers.c
    src/st/wrp/graphics_banks.c
    src/st/wrp/gen/e_laydef.c
    src/st/wrp/e_init.c
    src/st/wrp/background_block_init.c
    src/st/wrp/e_room_bg.c
    src/st/wrp/e_lock_camera.c
    src/st/wrp/e_breakable.c
    src/st/wrp/d_prize_drops.c
    src/st/wrp/gen/rooms.c
    src/st/wrp/gen/e_layout.c
    src/st/wrp/stage_data.c
    src/st/wrp/gen/us/sprites.c
    src/st/wrp/warp.c
    src/st/wrp/st_update.c
    src/st/wrp/collision.c
    src/st/wrp/create_entity.c
    src/st/wrp/e_red_door_tiles.c
    src/st/wrp/e_red_door.c
    src/st/wrp/st_common.c
    src/st/wrp/e_collect.c
    src/st/wrp/e_misc.c
    src/st/wrp/e_stage_name.c
    src/st/wrp/e_particles.c
    src/st/wrp/e_room_fg.c
    src/st/wrp/popup.c
    src/st/wrp/prim_helpers.c
    src/st/wrp/bss.c
)

SET(SOURCE_FILES_BOSS_BO4
    src/pc/bosses/boss_bo4.c
    src/boss/bo4/background_block_init.c
    src/boss/bo4/collision.c
    src/boss/bo4/create_entity.c
    src/boss/bo4/doors.c
    src/boss/bo4/dop_anim.c
    src/boss/bo4/doppleganger.c
    src/boss/bo4/doppleganger_anim.c
    src/boss/bo4/d_prize_drops.c
    src/boss/bo4/e_breakable.c
    src/boss/bo4/e_collect.c
    src/boss/bo4/e_init.c
    src/boss/bo4/e_life_up.c
    src/boss/bo4/e_lock_camera.c
    src/boss/bo4/e_misc.c
    src/boss/bo4/e_particles.c
    src/boss/bo4/e_red_door.c
    src/boss/bo4/e_red_door_tiles.c
    src/boss/bo4/e_room_bg.c
    src/boss/bo4/e_room_fg.c
    src/boss/bo4/e_stage_name.c
    src/boss/bo4/gen/e_laydef.c
    src/boss/bo4/gen/e_layout.c
    src/boss/bo4/gen/rooms.c
    src/boss/bo4/graphics_banks.c
    src/boss/bo4/header.c
    src/boss/bo4/layers.c
    src/boss/bo4/palette_def.c
    src/boss/bo4/popup.c
    src/boss/bo4/sprite_banks.c
    src/boss/bo4/prim_helpers.c
    src/boss/bo4/spritesheets.c
    src/boss/bo4/st_common.c
    src/boss/bo4/st_update.c
    src/boss/bo4/stage_data.c
    src/boss/bo4/unk_365FC.c
    src/boss/bo4/unk_45354.c
    src/boss/bo4/unk_46E7C.c
    src/boss/bo4/bss.c
)

set(SOURCE_FILES_WEAPON
    src/weapon/w_000.c
    src/weapon/w_002.c
    src/weapon/w_007.c
    src/weapon/w_012.c
    src/weapon/w_034.c
    src/weapon/w_037.c
    src/weapon/w_041.c
    src/weapon/w_045.c
    src/weapon/w_046.c
    src/weapon/w_051.c
    src/weapon/w_052.c
)

# WEAPON_ID needs to be a string and not just a number
set_source_files_properties(src/weapon/w_000.c PROPERTIES COMPILE_DEFINITIONS WEAPON_ID=w_000)
set_source_files_properties(src/weapon/w_002.c PROPERTIES COMPILE_DEFINITIONS WEAPON_ID=w_002)
set_source_files_properties(src/weapon/w_007.c PROPERTIES COMPILE_DEFINITIONS WEAPON_ID=w_007)
set_source_files_properties(src/weapon/w_012.c PROPERTIES COMPILE_DEFINITIONS WEAPON_ID=w_012)
set_source_files_properties(src/weapon/w_034.c PROPERTIES COMPILE_DEFINITIONS WEAPON_ID=w_034)
set_source_files_properties(src/weapon/w_037.c PROPERTIES COMPILE_DEFINITIONS WEAPON_ID=w_037)
set_source_files_properties(src/weapon/w_041.c PROPERTIES COMPILE_DEFINITIONS WEAPON_ID=w_041)
set_source_files_properties(src/weapon/w_045.c PROPERTIES COMPILE_DEFINITIONS WEAPON_ID=w_045)
set_source_files_properties(src/weapon/w_046.c PROPERTIES COMPILE_DEFINITIONS WEAPON_ID=w_046)
set_source_files_properties(src/weapon/w_051.c PROPERTIES COMPILE_DEFINITIONS WEAPON_ID=w_051)
set_source_files_properties(src/weapon/w_052.c PROPERTIES COMPILE_DEFINITIONS WEAPON_ID=w_052)

set(SOURCE_FILES_CORE
    ${SOURCE_FILES_DRA}
    ${SOURCE_FILES_RIC}
    ${SOURCE_FILES_WEAPON}
)
if (USE_PLAYER_MARIA)
    add_compile_definitions(USE_PLAYER_MARIA)
    list(APPEND SOURCE_FILES_CORE
            ${SOURCE_FILES_MARIA}
            src/pc/pl_maria.c)
endif()

add_subdirectory(tools/psyz/psyz)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES_PC}
    ${SOURCE_FILES_3RD}
    ${SOURCE_FILES_CORE})

target_include_directories(${PROJECT_NAME} PUBLIC
    include
    src/dra
    src/pc/3rd
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    _USE_MATH_DEFINES # needed for msvc
    VERSION_PC
    PERMUTER
    NON_MATCHING
    HARD_LINK
    _internal_version_us
    __psyz
)

target_include_directories(psyz PUBLIC tools/psyz/psyz/include)
target_compile_definitions(psyz PRIVATE __psyz)
psyz_strip_file_prefix(${PROJECT_NAME})
sotn_str_apply(${PROJECT_NAME})
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE psyz)
    set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS ON)
    if (MSVC)
        # Windows PE has no -rdynamic equivalent, and a DLL must resolve all
        # externals at link time.
        # Generates an export definition for overlays to where to link to.
        get_filename_component(_msvc_bindir "${CMAKE_C_COMPILER}" DIRECTORY)
        set(_sotn_def "${CMAKE_BINARY_DIR}/sotn_exports.def")
        add_custom_command(TARGET ${PROJECT_NAME} PRE_LINK
            COMMAND ${CMAKE_COMMAND}
                    -DDUMPBIN=${_msvc_bindir}/dumpbin.exe
                    -DOUT=${_sotn_def}
                    "-DINPUTS=$<TARGET_FILE:psyz>$<SEMICOLON>$<JOIN:$<TARGET_OBJECTS:${PROJECT_NAME}>,$<SEMICOLON>>"
                    -P ${CMAKE_SOURCE_DIR}/cmake/gen_export_def.cmake
            VERBATIM
            COMMENT "Generating export .def for overlay symbol resolution")
        set_property(TARGET ${PROJECT_NAME} APPEND_STRING
                     PROPERTY LINK_FLAGS " /DEF:${_sotn_def}")
    endif()
elseif (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE psyz m)
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-export_dynamic)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE psyz m ${CMAKE_DL_LIBS})
    target_link_options(${PROJECT_NAME} PRIVATE -rdynamic)
endif()

function(add_overlay name)
    add_library(${name} SHARED ${ARGN})
    set_target_properties(${name} PROPERTIES PREFIX "")

    target_include_directories(${name} PRIVATE
        include
        src/dra
        src/pc/3rd
        src/pc
    )

    target_compile_definitions(${name} PRIVATE
        _USE_MATH_DEFINES
        VERSION_PC
        PERMUTER
        NON_MATCHING
        HARD_LINK
        _internal_version_us
        __psyz
        OVERLAY_BUILD
    )

    # Overlays need to resolve the same libraries the main exec is linked to
    target_include_directories(${name} PRIVATE tools/psyz/psyz/include)
    if (WIN32)
        target_link_libraries(${name} PRIVATE ${PROJECT_NAME})
    elseif (APPLE)
        target_link_options(${name} PRIVATE -Wl,-undefined,dynamic_lookup)
    endif()

    psyz_strip_file_prefix(${name})
    sotn_str_apply(${name})
endfunction()

add_overlay(cen ${SOURCE_FILES_STAGE_CEN})
add_overlay(sel ${SOURCE_FILES_STAGE_SEL})
add_overlay(wrp ${SOURCE_FILES_STAGE_WRP})
add_overlay(nz0 ${SOURCE_FILES_STAGE_NZ0})
add_overlay(st0 ${SOURCE_FILES_STAGE_ST0})

add_overlay(tt_000 ${SOURCE_FILES_TT_000})
add_overlay(tt_001 ${SOURCE_FILES_TT_001})
add_overlay(tt_002 ${SOURCE_FILES_TT_002})
