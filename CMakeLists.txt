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

    # silenced warnings required for PS1 matching
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-missing-braces")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-function")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-implicit-function-declaration")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-incompatible-pointer-types")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-int-conversion")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-return-mismatch")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-return-type")

    # Warnings promoted to errors that directly address underlying issues
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=return-local-addr")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=sizeof-array-argument")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=switch-bool")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=unused-result")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=pointer-compare")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=div-by-zero")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=overflow")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=shift-count-negative")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=shift-count-overflow")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=discarded-qualifiers")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=stringop-overflow")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=stringop-overread")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=switch-outside-range")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=switch-unreachable")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=builtin-declaration-mismatch")
endif()

if(MSVC)
    add_compile_options(/J)  # Treat char as unsigned
else()
    add_compile_options(-funsigned-char)
endif()

find_program(CARGO_BIN cargo)
if(NOT CARGO_BIN)
    message(FATAL_ERROR
        "cargo is required to compile sotn_str\n"
        "https://doc.rust-lang.org/stable/cargo/getting-started/installation.html")
endif()

# prevent sotn_str binary type conflicts when working with containers
set(SOTN_STR_TARGET_DIR "${CMAKE_BINARY_DIR}/sotn_str")
set(SOTN_STR_BIN
    "${SOTN_STR_TARGET_DIR}/release/sotn_str${CMAKE_EXECUTABLE_SUFFIX}")
add_custom_command(
    OUTPUT "${SOTN_STR_BIN}"
    COMMAND ${CMAKE_COMMAND} -E env
            "CARGO_TARGET_DIR=${SOTN_STR_TARGET_DIR}"
            "${CARGO_BIN}" build --release
            --manifest-path "${CMAKE_SOURCE_DIR}/tools/sotn_str/Cargo.toml"
    DEPENDS
        "${CMAKE_SOURCE_DIR}/tools/sotn_str/Cargo.toml"
        "${CMAKE_SOURCE_DIR}/tools/sotn_str/Cargo.lock"
        "${CMAKE_SOURCE_DIR}/tools/sotn_str/src/main.rs"
    VERBATIM
    COMMENT "Building host sotn_str")
add_custom_target(sotn_str_host DEPENDS "${SOTN_STR_BIN}")

set(_sotn_str_args "${SOTN_STR_BIN};cc")

# Allows to run the sotn_str pre-compiler only to selected targets
function(sotn_str_apply target)
    add_dependencies(${target} sotn_str_host)
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
    src/pc/spawn_point.c
    src/pc/pc.c
    src/pc/cutscene_pc.c
    src/pc/io.c
    src/pc/sim_pc.c
    src/pc/pl_arc.c
    src/pc/pl_ric.c
    src/pc/servant_pc.c
    src/pc/stages/overlay.c
    src/pc/weapon_pc.c
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
    src/ric/spritebanks.c
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
    src/maria/spritebanks.c
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

set(SOURCE_FILES_STAGE_ARE
    src/pc/stages/stage_are.c
    src/st/are/header.c
    src/st/are/sprite_banks.c
    src/st/are/palette_def.c
    src/st/are/layers.c
    src/st/are/graphics_banks.c
    src/st/are/gen/e_laydef.c
    src/st/are/e_init.c
    src/st/are/background_block_init.c
    src/st/are/e_red_door_tiles.c
    src/st/are/d_prize_drops.c
    src/st/are/gen/rooms.c
    src/st/are/gen/e_layout.c
    src/st/are/gfx_data.c
    src/st/are/tilemaps.c
    src/st/are/gen/us/sprites.c
    src/st/are/e_room_bg.c
    src/st/are/e_lock_camera.c
    src/st/are/e_breakable.c
    src/st/are/e_boss_torch.c
    src/st/are/e_boss_doors.c
    src/st/are/e_cavern_door.c
    src/st/are/e_elevator.c
    src/st/are/e_fountain_water.c
    src/st/are/e_secrets.c
    src/st/are/e_background_door_rubble.c
    src/st/are/e_explosion_puff_opaque.c
    src/st/are/st_update.c
    src/st/are/st_collision.c
    src/st/are/create_entity.c
    src/st/are/e_red_door.c
    src/st/are/st_common.c
    src/st/are/e_collect.c
    src/st/are/e_misc.c
    src/st/are/e_stage_name.c
    src/st/are/e_particles.c
    src/st/are/e_room_fg.c
    src/st/are/popup.c
    src/st/are/e_blade_master.c
    src/st/are/e_blade_soldier.c
    src/st/are/e_bone_musket.c
    src/st/are/e_owl_knight.c
    src/st/are/e_valhalla_knight.c
    src/st/are/e_blue_axe_knight.c
    src/st/are/e_armor_lord.c
    src/st/are/e_hunting_girl.c
    src/st/are/e_paranthropus.c
    src/st/are/e_flea_armor.c
    src/st/are/e_flea_man.c
    src/st/are/e_bone_scimitar.c
    src/st/are/e_plate_lord.c
    src/st/are/e_plate_lord_2.c
    src/st/are/e_grave_keeper.c
    src/st/are/e_mist_door.c
    src/st/are/prim_helpers.c
    src/st/are/bss.c
)

set(SOURCE_FILES_STAGE_CAT
    src/pc/stages/stage_cat.c
    src/st/cat/header.c
    src/st/cat/sprite_banks.c
    src/st/cat/palette_def.c
    src/st/cat/layers.c
    src/st/cat/graphics_banks.c
    src/st/cat/gen/e_laydef.c
    src/st/cat/e_init.c
    src/st/cat/e_red_door_tiles.c
    src/st/cat/background_block_init.c
    src/st/cat/d_prize_drops.c
    src/st/cat/gen/rooms.c
    src/st/cat/gen/e_layout.c
    src/st/cat/gfx_data.c
    src/st/cat/tilemaps.c
    src/st/cat/unused_sprites.c
    src/st/cat/gen/us/sprites.c
    src/st/cat/e_room_bg.c
    src/st/cat/e_lock_camera.c
    src/st/cat/e_breakable.c
    src/st/cat/e_spike_room_light_switch.c
    src/st/cat/e_spikes.c
    src/st/cat/unk_3872C.c
    src/st/cat/unk_38AD0.c
    src/st/cat/e_elevator.c
    src/st/cat/e_secrets.c
    src/st/cat/unk_3A164.c
    src/st/cat/e_coffin.c
    src/st/cat/unk_3ACF4.c
    src/st/cat/unk_3B4CC.c
    src/st/cat/st_update.c
    src/st/cat/st_collision.c
    src/st/cat/create_entity.c
    src/st/cat/e_red_door.c
    src/st/cat/st_common.c
    src/st/cat/e_misc.c
    src/st/cat/e_collect.c
    src/st/cat/e_lava.c
    src/st/cat/e_cavern_background.c
    src/st/cat/e_bone_ark.c
    src/st/cat/e_stage_name.c
    src/st/cat/e_lava_glow.c
    src/st/cat/e_discus_lord.c
    src/st/cat/e_hellfire_beast.c
    src/st/cat/e_particles.c
    src/st/cat/e_room_fg.c
    src/st/cat/popup.c
    src/st/cat/giantbro_helpers.c
    src/st/cat/e_lossoth.c
    src/st/cat/e_grave_keeper.c
    src/st/cat/e_tombstone.c
    src/st/cat/e_gremlin.c
    src/st/cat/e_slime.c
    src/st/cat/e_wereskeleton.c
    src/st/cat/e_thornweed_corpseweed.c
    src/st/cat/e_blood_skeleton.c
    src/st/cat/prim_helpers.c
)

set(SOURCE_FILES_STAGE_NO2
    src/pc/stages/stage_no2.c
    src/st/no2/header.c
    src/st/no2/gen/e_laydef.c
    src/st/no2/e_init.c
    src/st/no2/gen/rooms.c
    src/st/no2/gen/e_layout.c
    src/st/no2/gen/sprites.c
    src/st/no2/graphics_banks.c
    src/st/no2/layers.c
    src/st/no2/palette_def.c
    src/st/no2/sprite_banks.c
    src/st/no2/tilemaps.c
    src/st/no2/stage_data.c
    src/st/no2/background_block_init.c
    src/st/no2/e_room_bg.c
    src/st/no2/e_lock_camera.c
    src/st/no2/e_breakable.c
    src/st/no2/d_prize_drops.c
    src/st/no2/st_update.c
    src/st/no2/collision.c
    src/st/no2/create_entity.c
    src/st/no2/e_red_door_tiles.c
    src/st/no2/e_red_door.c
    src/st/no2/st_common.c
    src/st/no2/e_collect.c
    src/st/no2/e_misc.c
    src/st/no2/e_stage_name.c
    src/st/no2/e_particles.c
    src/st/no2/e_room_fg.c
    src/st/no2/popup.c
    src/st/no2/prim_helpers.c
    src/st/no2/33D8C.c
    src/st/no2/34DA4.c
    src/st/no2/372E8.c
    src/st/no2/37580.c
    src/st/no2/giantbro_helpers_2.c
    src/st/no2/blade.c
    src/st/no2/e_background_house.c
    src/st/no2/e_bloody_zombie.c
    src/st/no2/e_life_up.c
    src/st/no2/e_owl_knight.c
    src/st/no2/e_prisoner.c
    src/st/no2/e_sealed_door.c
    src/st/no2/e_secrets.c
    src/st/no2/e_skelerang.c
    src/st/no2/e_spectral_sword.c
    src/st/no2/e_spikes.c
    src/st/no2/e_valhalla_knight.c
    src/st/no2/giantbro_helpers.c
    src/st/no2/gurkha.c
    src/st/no2/hammer.c
)

set(SOURCE_FILES_STAGE_CHI
    src/pc/stages/stage_chi.c
    src/st/chi/dt_header.c
    src/st/chi/gen/e_laydef.c
    src/st/chi/e_init.c
    src/st/chi/background_block_init.c
    src/st/chi/e_red_door_tiles.c
    src/st/chi/e_lock_camera.c
    src/st/chi/en_breakable.c
    src/st/chi/en_demon_switch_wall.c
    src/st/chi/en_breakable_wall.c
    src/st/chi/en_falling_stairs.c
    src/st/chi/dt_prize_drops.c
    src/st/chi/st_update.c
    src/st/chi/st_collision.c
    src/st/chi/en_red_door.c
    src/st/chi/ut_common.c
    src/st/chi/en_collect.c
    src/st/chi/en_misc.c
    src/st/chi/en_particles.c
    src/st/chi/en_room_foreground.c
    src/st/chi/e_salem_witch.c
    src/st/chi/e_gremlin.c
    src/st/chi/e_thornweed_corpseweed.c
    src/st/chi/en_venus_weed.c
    src/st/chi/gen/rooms.c
    src/st/chi/gen/e_layout.c
    src/st/chi/stage_data.c
    src/st/chi/gen/sprites.c
    src/st/chi/en_debug_cerberus_gate.c
    src/st/chi/en_stage_name.c
    src/st/chi/ut_prim_helpers.c
    src/st/chi/e_room_bg.c
    src/st/chi/ut_create_entity.c
    src/st/chi/en_popup.c
    src/st/chi/bss.c
)

set(SOURCE_FILES_STAGE_DAI
    src/pc/stages/stage_dai.c
    src/st/dai/header.c
    src/st/dai/gen/e_laydef.c
    src/st/dai/e_init.c
    src/st/dai/gen/rooms.c
    src/st/dai/gen/e_layout.c
    src/st/dai/gen/us/sprites.c
    src/st/dai/gfx_data.c
    src/st/dai/graphics_banks.c
    src/st/dai/layers.c
    src/st/dai/palette_def.c
    src/st/dai/pal_stained_glass.c
    src/st/dai/sprite_banks.c
    src/st/dai/tilemaps.c
    src/st/dai/background_block_init.c
    src/st/dai/e_room_bg.c
    src/st/dai/e_room_bg_2.c
    src/st/dai/e_lock_camera.c
    src/st/dai/e_breakable.c
    src/st/dai/d_prize_drops.c
    src/st/dai/cutscene_data.c
    src/st/dai/st_update.c
    src/st/dai/st_collision.c
    src/st/dai/create_entity.c
    src/st/dai/e_red_door_tiles.c
    src/st/dai/e_red_door.c
    src/st/dai/st_common.c
    src/st/dai/e_collect.c
    src/st/dai/e_misc.c
    src/st/dai/e_stage_name.c
    src/st/dai/e_particles.c
    src/st/dai/e_room_fg.c
    src/st/dai/e_room_fg_2.c
    src/st/dai/popup.c
    src/st/dai/prim_helpers.c
    src/st/dai/e_bat.c
    src/st/dai/e_bell.c
    src/st/dai/e_bone_halberd.c
    src/st/dai/e_bone_pillar.c
    src/st/dai/e_chair.c
    src/st/dai/e_clouds.c
    src/st/dai/e_confessional.c
    src/st/dai/e_corner_guard.c
    src/st/dai/e_crow.c
    src/st/dai/e_cutscene_actors.c
    src/st/dai/e_cutscene_dialogue.c
    src/st/dai/e_dai_no2_shortcut.c
    src/st/dai/e_end_chime.c
    src/st/dai/e_gargoyle.c
    src/st/dai/e_hunting_girl.c
    src/st/dai/e_mist_door.c
    src/st/dai/e_sealed_door.c
    src/st/dai/e_skelerang.c
    src/st/dai/e_spectral_sword.c
    src/st/dai/e_spikes.c
    src/st/dai/e_stained_glass.c
    src/st/dai/e_tower_exit.c
    src/st/dai/e_winged_guard.c
)

set(SOURCE_FILES_STAGE_NP3
    src/pc/stages/stage_np3.c
    src/st/np3/header.c
    src/st/np3/gen/us/e_laydef.c
    src/st/np3/e_init.c
    src/st/np3/gen/rooms.c
    src/st/np3/gen/us/e_layout.c
    src/st/np3/gen/sprites.c
    src/st/np3/stage_data.c
    src/st/np3/background_block_init.c
    src/st/np3/e_room_bg.c
    src/st/np3/e_lock_camera.c
    src/st/np3/e_breakable.c
    src/st/np3/d_prize_drops.c
    src/st/np3/st_update.c
    src/st/np3/collision.c
    src/st/np3/create_entity.c
    src/st/np3/e_red_door_tiles.c
    src/st/np3/e_red_door.c
    src/st/np3/st_common.c
    src/st/np3/e_collect.c
    src/st/np3/e_misc.c
    src/st/np3/e_stage_name.c
    src/st/np3/e_particles.c
    src/st/np3/e_room_fg.c
    src/st/np3/popup.c
    src/st/np3/prim_helpers.c
    src/st/np3/bss.c
    src/st/np3/giantbro_helpers_2.c
    src/st/np3/d_water_data.c
    src/st/np3/water_effects.c
    src/st/np3/entrance_weights.c
    src/st/np3/e_background_bushes_trees.c
    src/st/np3/e_background_lightning.c
    src/st/np3/e_bat.c
    src/st/np3/blade.c
    src/st/np3/e_bloody_zombie.c
    src/st/np3/e_bone_scimitar.c
    src/st/np3/e_castle_door.c
    src/st/np3/e_cavern_door.c
    src/st/np3/e_explosion_puff_opaque.c
    src/st/np3/e_heartroom.c
    src/st/np3/e_jewel_sword_puzzle.c
    src/st/np3/e_merman.c
    src/st/np3/e_merman2.c
    src/st/np3/e_owl_knight.c
    src/st/np3/e_shutting_window.c
    src/st/np3/e_sky_entities.c
    src/st/np3/e_stairway.c
    src/st/np3/e_tilemap_shuffler.c
    src/st/np3/e_transparent_water.c
    src/st/np3/e_trapdoor.c
    src/st/np3/e_unkId16.c
    src/st/np3/e_zombie.c
    src/st/np3/gaibon.c
    src/st/np3/slogra.c
    src/st/np3/giantbro_helpers.c
    src/st/np3/gurkha.c
    src/st/np3/hammer.c
)

set(SOURCE_FILES_STAGE_NO4
    src/pc/stages/stage_no4.c
    src/st/no4/header.c
    src/st/no4/gen/e_laydef.c
    src/st/no4/e_init.c
    src/st/no4/background_block_init.c
    src/st/no4/e_red_door_tiles.c
    src/st/no4/e_lock_camera.c
    src/st/no4/e_breakable.c
    src/st/no4/first_c_file.c
    src/st/no4/e_ferryman.c
    src/st/no4/48248.c
    src/st/no4/482B8.c
    src/st/no4/e_secrets.c
    src/st/no4/e_bat.c
    src/st/no4/d_prize_drops.c
    src/st/no4/e_killer_fish.c
    src/st/no4/cutscene.c
    src/st/no4/st_update.c
    src/st/no4/collision.c
    src/st/no4/create_entity.c
    src/st/no4/e_red_door.c
    src/st/no4/st_common.c
    src/st/no4/e_collect.c
    src/st/no4/e_misc.c
    src/st/no4/e_stage_name.c
    src/st/no4/e_particles.c
    src/st/no4/e_room_fg.c
    src/st/no4/e_room_bg.c
    src/st/no4/popup.c
    src/st/no4/e_toad.c
    src/st/no4/e_frog.c
    src/st/no4/e_fishhead.c
    src/st/no4/e_frozen_shade.c
    src/st/no4/e_spear_guard.c
    src/st/no4/e_bone_archer.c
    src/st/no4/e_skeleton_ape.c
    src/st/no4/prim_helpers.c
    src/st/no4/gen/rooms.c
    src/st/no4/gen/e_layout.c
    src/st/no4/cutscene_data.c
    src/st/no4/stage_data.c
    src/st/no4/gen/sprites.c
)

set(SOURCE_FILES_STAGE_NO0
    src/pc/stages/stage_no0.c
    src/st/no0/header.c
    src/st/no0/gen/e_laydef.c
    src/st/no0/e_init.c
    src/st/no0/e_red_door_tiles.c
    src/st/no0/e_room_bg.c
    src/st/no0/e_lock_camera.c
    src/st/no0/e_breakable.c
    src/st/no0/e_elevator.c
    src/st/no0/42A34.c
    src/st/no0/e_explosion_puff_opaque.c
    src/st/no0/d_prize_drops.c
    src/st/no0/st_update.c
    src/st/no0/collision.c
    src/st/no0/create_entity.c
    src/st/no0/e_red_door.c
    src/st/no0/e_room_fg.c
    src/st/no0/e_particles.c
    src/st/no0/st_common.c
    src/st/no0/e_collect.c
    src/st/no0/e_misc.c
    src/st/no0/4C750.c
    src/st/no0/clock_room.c
    src/st/no0/4E2E0.c
    src/st/no0/e_stage_name.c
    src/st/no0/e_diplocephalus.c
    src/st/no0/e_diplocephalus_tail.c
    src/st/no0/e_skelerang.c
    src/st/no0/e_plate_lord.c
    src/st/no0/e_plate_lord_2.c
    src/st/no0/e_ghost.c
    src/st/no0/e_marionette.c
    src/st/no0/e_slinger.c
    src/st/no0/e_stone_rose.c
    src/st/no0/e_ctulhu.c
    src/st/no0/ctulhu_shockwave_data.c
    src/st/no0/e_axe_knight.c
    src/st/no0/e_ouija_table.c
    src/st/no0/e_flea_man.c
    src/st/no0/e_skeleton.c
    src/st/no0/e_sealed_door.c
    src/st/no0/prim_helpers.c
    src/st/no0/popup.c
    src/st/no0/gen/rooms.c
    src/st/no0/gen/e_layout.c
    src/st/no0/stage_data.c
    src/st/no0/gen/sprites.c
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

set(SOURCE_FILES_STAGE_RNO0
    src/pc/stages/stage_rno0.c
    src/st/rno0/create_entity.c
    src/st/rno0/e_misc.c
    src/st/rno0/layers.c
    src/st/rno0/palette_def.c
    src/st/rno0/sprite_banks.c
    src/st/rno0/graphics_banks.c
    src/st/rno0/stage_data.c
    src/st/rno0/tilemaps.c
    src/st/rno0/e_red_door.c
    src/st/rno0/e_red_door_tiles.c
    src/st/rno0/e_room_fg.c
    src/st/rno0/st_common.c
    src/st/rno0/st_update.c
    src/st/rno0/gen/e_laydef.c
    src/st/rno0/gen/e_layout.c
    src/st/rno0/gen/rooms.c
    src/st/rno0/gen/us/sprites.c)

set(SOURCE_FILES_STAGE_RNO4
    src/pc/stages/stage_rno4.c
    src/st/rno4/create_entity.c
    src/st/rno4/e_red_door.c
    src/st/rno4/e_red_door_tiles.c
    src/st/rno4/e_room_fg.c
    src/st/rno4/st_common.c
    src/st/rno4/st_update.c
    src/st/rno4/unk_44B0C.c
    src/st/rno4/gen/rooms.c
    src/st/rno4/stage_data.c)

set(SOURCE_FILES_STAGE_RNO3
    src/pc/stages/stage_rno3.c
    src/st/rno3/create_entity.c
    src/st/rno3/e_misc.c
    src/st/rno3/layers.c
    src/st/rno3/palette_def.c
    src/st/rno3/sprite_banks.c
    src/st/rno3/graphics_banks.c
    src/st/rno3/stage_data.c
    src/st/rno3/tilemaps.c
    src/st/rno3/e_red_door.c
    src/st/rno3/e_red_door_tiles.c
    src/st/rno3/e_room_fg.c
    src/st/rno3/st_common.c
    src/st/rno3/st_update.c
    src/st/rno3/gen/e_laydef.c
    src/st/rno3/gen/e_layout.c
    src/st/rno3/gen/us/rooms.c
    src/st/rno3/gen/us/sprites.c)

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

set(SOURCE_FILES_STAGE_DRE
    src/pc/stages/stage_dre.c
    src/st/dre/header.c
    src/st/dre/gen/e_laydef.c
    src/st/dre/e_init.c
    src/st/dre/gen/rooms.c
    src/st/dre/gen/e_layout.c
    src/st/dre/gen/us/sprites.c
    src/st/dre/gfx_banks.c
    src/st/dre/gfx_data.c
    src/st/dre/layers.c
    src/st/dre/palette_def.c
    src/st/dre/sprite_banks.c
    src/st/dre/tilemaps.c
    src/st/dre/background_block_init.c
    src/st/dre/e_room_bg.c
    src/st/dre/e_lock_camera.c
    src/st/dre/e_breakable.c
    src/st/dre/d_prize_drops.c
    src/st/dre/st_update.c
    src/st/dre/collision.c
    src/st/dre/create_entity.c
    src/st/dre/e_red_door_tiles.c
    src/st/dre/e_red_door.c
    src/st/dre/st_common.c
    src/st/dre/e_collect.c
    src/st/dre/e_misc.c
    src/st/dre/e_stage_name.c
    src/st/dre/e_particles.c
    src/st/dre/e_room_fg.c
    src/st/dre/popup.c
    src/st/dre/prim_helpers.c
    src/st/dre/e_background_clouds.c
    src/st/dre/e_background_house.c
    src/st/dre/e_cutscene_actors.c
    src/st/dre/e_cutscene_dialogue.c
    src/st/dre/e_succubus.c
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

SET(SOURCE_FILES_BOSS_BO1
    src/pc/bosses/boss_bo1.c
    src/boss/bo1/background_block_init.c
    src/boss/bo1/bss.c
    src/boss/bo1/collision.c
    src/boss/bo1/create_entity.c
    src/boss/bo1/d_prize_drops.c
    src/boss/bo1/e_breakable.c
    src/boss/bo1/e_collect.c
    src/boss/bo1/e_explosion_flame.c
    src/boss/bo1/e_granfaloon.c
    src/boss/bo1/e_init.c
    src/boss/bo1/e_life_up.c
    src/boss/bo1/e_lock_camera.c
    src/boss/bo1/e_misc.c
    src/boss/bo1/e_particles.c
    src/boss/bo1/e_red_door.c
    src/boss/bo1/e_red_door_tiles.c
    src/boss/bo1/e_room_bg.c
    src/boss/bo1/e_room_fg.c
    src/boss/bo1/e_stage_name.c
    src/boss/bo1/gen/e_laydef.c
    src/boss/bo1/gen/e_layout.c
    src/boss/bo1/gen/rooms.c
    src/boss/bo1/gen/us/sprites.c
    src/boss/bo1/graphics_banks.c
    src/boss/bo1/header.c
    src/boss/bo1/layers.c
    src/boss/bo1/palette_def.c
    src/boss/bo1/popup.c
    src/boss/bo1/prim_helpers.c
    src/boss/bo1/sprite_banks.c
    src/boss/bo1/stage_data.c
    src/boss/bo1/stage_palettes.c
    src/boss/bo1/st_common.c
    src/boss/bo1/st_update.c
    src/boss/bo1/unk_210A8.c
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

set(SOURCE_FILES_STAGE_RWRP
    src/pc/stages/stage_rwrp.c
    src/st/rwrp/header.c
    src/st/rwrp/sprite_banks.c
    src/st/rwrp/palette_def.c
    src/st/rwrp/layers.c
    src/st/rwrp/graphics_banks.c
    src/st/rwrp/gen/e_laydef.c
    src/st/rwrp/e_init.c
    src/st/rwrp/gen/rooms.c
    src/st/rwrp/gen/e_layout.c
    src/st/rwrp/gen/us/sprites.c
    src/st/rwrp/stage_data.c
    src/st/rwrp/background_block_init.c
    src/st/rwrp/e_room_bg.c
    src/st/rwrp/e_lock_camera.c
    src/st/rwrp/e_breakable.c
    src/st/rwrp/d_prize_drops.c
    src/st/rwrp/warp.c
    src/st/rwrp/st_update.c
    src/st/rwrp/collision.c
    src/st/rwrp/create_entity.c
    src/st/rwrp/e_red_door_tiles.c
    src/st/rwrp/e_red_door.c
    src/st/rwrp/st_common.c
    src/st/rwrp/e_collect.c
    src/st/rwrp/e_misc.c
    src/st/rwrp/e_stage_name.c
    src/st/rwrp/e_particles.c
    src/st/rwrp/e_room_fg.c
    src/st/rwrp/popup.c
    src/st/rwrp/prim_helpers.c
    src/st/rwrp/bss.c
)

set(SOURCE_FILES_STAGE_NO3
    src/pc/stages/stage_no3.c
    src/st/no3/header.c
    src/st/no3/gen/e_laydef.c
    src/st/no3/e_init.c
    src/st/no3/gen/rooms.c
    src/st/no3/gen/e_layout.c
    src/st/no3/gen/sprites.c
    src/st/no3/graphics_banks.c
    src/st/no3/layers.c
    src/st/no3/palette_def.c
    src/st/no3/sprite_banks.c
    src/st/no3/tilemaps.c
    src/st/no3/stage_data.c
    src/st/no3/background_block_init.c
    src/st/no3/e_room_bg.c
    src/st/no3/e_lock_camera.c
    src/st/no3/e_breakable.c
    src/st/no3/d_prize_drops.c
    src/st/no3/cutscene.c
    src/st/no3/st_update.c
    src/st/no3/collision.c
    src/st/no3/create_entity.c
    src/st/no3/e_red_door_tiles.c
    src/st/no3/e_red_door.c
    src/st/no3/st_common.c
    src/st/no3/e_collect.c
    src/st/no3/e_misc.c
    src/st/no3/e_stage_name.c
    src/st/no3/e_particles.c
    src/st/no3/e_room_fg.c
    src/st/no3/popup.c
    src/st/no3/prim_helpers.c
    src/st/no3/d_water_data.c
    src/st/no3/e_background_bushes_trees.c
    src/st/no3/e_background_lightning.c
    src/st/no3/e_bat.c
    src/st/no3/e_bone_scimitar.c
    src/st/no3/e_castle_door.c
    src/st/no3/e_cavern_door.c
    src/st/no3/e_death.c
    src/st/no3/e_death_sky_swirl.c
    src/st/no3/e_explosion_puff_opaque.c
    src/st/no3/e_fire_warg.c
    src/st/no3/e_heartroom.c
    src/st/no3/e_jewel_sword_puzzle.c
    src/st/no3/e_merman.c
    src/st/no3/e_merman2.c
    src/st/no3/entrance_weights.c
    src/st/no3/e_outdoor_ents.c
    src/st/no3/e_shutting_window.c
    src/st/no3/e_sky_entities.c
    src/st/no3/e_stairway.c
    src/st/no3/e_tilemap_shuffler.c
    src/st/no3/e_transparent_water.c
    src/st/no3/e_trapdoor.c
    src/st/no3/e_unkId16.c
    src/st/no3/e_warg.c
    src/st/no3/e_zombie.c
    src/st/no3/water_effects.c
)

set(SOURCE_FILES_STAGE_LIB
    src/pc/stages/stage_lib.c
    src/st/lib/header.c
    src/st/lib/palette_def.c
    src/st/lib/layers.c
    src/st/lib/graphics_banks.c
    src/st/lib/gen/e_laydef.c
    src/st/lib/e_init.c
    src/st/lib/background_block_init.c
    src/st/lib/e_red_door_tiles.c
    src/st/lib/d_prize_drops.c
    src/st/lib/gen/rooms.c
    src/st/lib/gen/e_layout.c
    src/st/lib/stage_data.c
    src/st/lib/tilemaps.c
    src/st/lib/gen/sprites.c
    src/st/lib/e_room_bg.c
    src/st/lib/e_lock_camera.c
    src/st/lib/e_breakable.c
    src/st/lib/first_c_file.c
    src/st/lib/e_library_bg.c
    src/st/lib/e_shop.c
    src/st/lib/cutscene.c
    src/st/lib/e_candle_table.c
    src/st/lib/unk_3B200.c
    src/st/lib/unk_3B53C.c
    src/st/lib/e_lesser_demon.c
    src/st/lib/e_chair.c
    src/st/lib/st_update.c
    src/st/lib/collision.c
    src/st/lib/create_entity.c
    src/st/lib/e_red_door.c
    src/st/lib/e_room_fg.c
    src/st/lib/st_common.c
    src/st/lib/e_misc.c
    src/st/lib/e_collect.c
    src/st/lib/e_bloody_zombie.c
    src/st/lib/e_flying_zombie.c
    src/st/lib/e_stage_name.c
    src/st/lib/e_particles.c
    src/st/lib/popup.c
    src/st/lib/e_dhuron.c
    src/st/lib/e_ectoplasm.c
    src/st/lib/e_thornweed_corpseweed.c
    src/st/lib/e_skeleton.c
    src/st/lib/e_mist_door.c
    src/st/lib/e_flea_armor.c
    src/st/lib/e_flea_man.c
    src/st/lib/e_mudman.c
    src/st/lib/prim_helpers.c
    src/st/lib/e_spellbook_magic_tome.c
    src/st/lib/e_life_up.c
)

set(SOURCE_FILES_STAGE_MAD
    src/pc/stages/stage_mad.c
    src/st/mad/header.c
    src/st/mad/sprite_banks.c
    src/st/mad/palette_def.c
    src/st/mad/layers.c
    src/st/mad/graphics_banks.c
    src/st/mad/gen/e_laydef.c
    src/st/mad/e_init.c
    src/st/mad/background_block_init.c
    src/st/mad/e_red_door_tiles.c
    src/st/mad/e_lock_camera.c
    src/st/mad/e_breakable.c
    src/st/mad/st_update.c
    src/st/mad/collision.c
    src/st/mad/e_red_door.c
    src/st/mad/st_common.c
    src/st/mad/e_collect.c
    src/st/mad/d_prize_drops.c
    src/st/mad/e_misc.c
    src/st/mad/e_particles.c
    src/st/mad/e_room_fg.c
    src/st/mad/gen/rooms.c
    src/st/mad/gen/e_layout.c
    src/st/mad/stage_data.c
    src/st/mad/pal.c
    src/st/mad/tilemaps.c
    src/st/mad/tiledef_1.c
    src/st/mad/gen/sprites.c
    src/st/mad/D8C8.c
    src/st/mad/e_room_bg.c
    src/st/mad/create_entity.c
    src/st/mad/e_stage_name.c
    src/st/mad/popup.c
    src/st/mad/prim_helpers.c
    src/st/mad/bss.c
)

set(SOURCE_FILES_CORE
    ${SOURCE_FILES_DRA}
    ${SOURCE_FILES_RIC}
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
    ${SOURCE_FILES_CORE})

target_include_directories(${PROJECT_NAME} PUBLIC
    include
    src/dra
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
psyz_title(${PROJECT_NAME} "Castlevania: Symphony of the Night")
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
        src/pc
        src/st/${name}
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

add_overlay(sel ${SOURCE_FILES_STAGE_SEL})
add_overlay(are ${SOURCE_FILES_STAGE_ARE})
add_overlay(cat ${SOURCE_FILES_STAGE_CAT})
add_overlay(no2 ${SOURCE_FILES_STAGE_NO2})
add_overlay(chi ${SOURCE_FILES_STAGE_CHI})
add_overlay(dai ${SOURCE_FILES_STAGE_DAI})
add_overlay(np3 ${SOURCE_FILES_STAGE_NP3})
add_overlay(no4 ${SOURCE_FILES_STAGE_NO4})
add_overlay(no0 ${SOURCE_FILES_STAGE_NO0})
add_overlay(rno0 ${SOURCE_FILES_STAGE_RNO0})
add_overlay(rno4 ${SOURCE_FILES_STAGE_RNO4})
add_overlay(rno3 ${SOURCE_FILES_STAGE_RNO3})
add_overlay(cen ${SOURCE_FILES_STAGE_CEN})
add_overlay(nz0 ${SOURCE_FILES_STAGE_NZ0})
add_overlay(wrp ${SOURCE_FILES_STAGE_WRP})
add_overlay(dre ${SOURCE_FILES_STAGE_DRE})
add_overlay(st0 ${SOURCE_FILES_STAGE_ST0})
add_overlay(rwrp ${SOURCE_FILES_STAGE_RWRP})
add_overlay(no3 ${SOURCE_FILES_STAGE_NO3})
add_overlay(lib ${SOURCE_FILES_STAGE_LIB})
add_overlay(mad ${SOURCE_FILES_STAGE_MAD})
add_overlay(bo1 ${SOURCE_FILES_BOSS_BO1})

foreach(id 000 002 007 008 012 034 035 037 040 041 043 045 046 050 051 052)
    add_overlay(w0_${id} src/weapon/w_${id}.c)
    target_compile_definitions(w0_${id} PRIVATE WEAPON0)
    add_overlay(w1_${id} src/weapon/w_${id}.c)
    target_compile_definitions(w1_${id} PRIVATE WEAPON1)
endforeach()

add_overlay(tt_000 ${SOURCE_FILES_TT_000})
add_overlay(tt_001 ${SOURCE_FILES_TT_001})
add_overlay(tt_002 ${SOURCE_FILES_TT_002})
