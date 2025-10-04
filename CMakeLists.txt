cmake_minimum_required(VERSION 3.10)

project(sotn)

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

find_package(SDL2 REQUIRED)

set(SOURCE_FILES_PC
    src/pc/main.c
    src/pc/log.c
    src/pc/stubs.c
    src/pc/sotn.c
    src/pc/pc.c
    src/pc/io.c
    src/pc/str.c
    src/pc/sim_pc.c
    src/pc/pl_arc.c
    src/pc/pl_ric.c
    src/pc/servant_pc.c
    src/pc/stages/stage_loader.c
    src/pc/stages/stage_dummy.c
    src/pc/weapon_pc.c
    src/pc/psxsdk/PsyCross/src/gte/PsyX_GTE.cpp
    src/pc/psxsdk/PsyCross/src/gte/inline_c.c
    src/pc/psxsdk/PsyCross/src/gte/libgte_.c
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

set(WANT_LIBSND_LLE FALSE CACHE BOOL "Whether to append use LLE for libsnd")
set(SOURCE_FILES_LIBSND_LLE
    # libsnd
    src/main/psxsdk/libsnd/adsr.c
    src/main/psxsdk/libsnd/cres.c
    src/main/psxsdk/libsnd/decre.c
    src/main/psxsdk/libsnd/libsnd_i.h
    src/main/psxsdk/libsnd/next.c
    src/main/psxsdk/libsnd/pause.c
    src/main/psxsdk/libsnd/play.c
    src/main/psxsdk/libsnd/replay.c
    src/main/psxsdk/libsnd/scsmvol.c
    src/main/psxsdk/libsnd/scssattr.c
    src/main/psxsdk/libsnd/scssvol.c
    src/main/psxsdk/libsnd/seqinit.c
    src/main/psxsdk/libsnd/seqread.c
    src/main/psxsdk/libsnd/seskoff.c
    src/main/psxsdk/libsnd/seskon.c
    src/main/psxsdk/libsnd/sscall.c
    src/main/psxsdk/libsnd/ssclose.c
    src/main/psxsdk/libsnd/ssend.c
    src/main/psxsdk/libsnd/ssinit.c
    src/main/psxsdk/libsnd/ssinit_h.c
    src/main/psxsdk/libsnd/ssplay.c
    src/main/psxsdk/libsnd/ssquit.c
    src/main/psxsdk/libsnd/ssstart.c
    src/main/psxsdk/libsnd/sstable.c
    src/main/psxsdk/libsnd/sstick.c
    src/main/psxsdk/libsnd/ssvol.c
    src/main/psxsdk/libsnd/stop.c
    src/main/psxsdk/libsnd/tempo.c
    src/main/psxsdk/libsnd/ut_gpa.c
    src/main/psxsdk/libsnd/ut_gva.c
    src/main/psxsdk/libsnd/ut_rdel.c
    src/main/psxsdk/libsnd/ut_rdep.c
    src/main/psxsdk/libsnd/ut_rev.c
    src/main/psxsdk/libsnd/ut_rfb.c
    src/main/psxsdk/libsnd/ut_roff.c
    src/main/psxsdk/libsnd/ut_ron.c
    src/main/psxsdk/libsnd/ut_sva.c
    src/main/psxsdk/libsnd/vm_doff.c
    src/main/psxsdk/libsnd/vm_don.c
    src/main/psxsdk/libsnd/vm_vsu.c
    src/main/psxsdk/libsnd/vmanager.c
    src/main/psxsdk/libsnd/vs_mono.c
    src/main/psxsdk/libsnd/vs_srv.c
    src/main/psxsdk/libsnd/vs_vab.c
    src/main/psxsdk/libsnd/vs_vfb.c
    src/main/psxsdk/libsnd/vs_vh.c
    src/main/psxsdk/libsnd/vs_vtb.c
    src/main/psxsdk/libsnd/vs_vtbp.c
    src/main/psxsdk/libsnd/vs_vtc.c

    # libspu
    src/main/psxsdk/libspu/s_cb.c
    src/main/psxsdk/libspu/s_crwa.c
    src/main/psxsdk/libspu/s_dcb.c
    src/main/psxsdk/libspu/s_gva.c
    src/main/psxsdk/libspu/s_i.c
    src/main/psxsdk/libspu/s_ini.c
    src/main/psxsdk/libspu/s_it.c
    src/main/psxsdk/libspu/s_itc.c
    src/main/psxsdk/libspu/s_m_f.c
    src/main/psxsdk/libspu/s_m_init.c
    src/main/psxsdk/libspu/s_m_m.c
    src/main/psxsdk/libspu/s_m_util.c
    src/main/psxsdk/libspu/s_m_wsa.c
    src/main/psxsdk/libspu/s_n2p.c
    src/main/psxsdk/libspu/s_q.c
    src/main/psxsdk/libspu/s_r.c
    src/main/psxsdk/libspu/s_sav.c
    src/main/psxsdk/libspu/s_sca.c
    src/main/psxsdk/libspu/s_si.c
    src/main/psxsdk/libspu/s_sic.c
    src/main/psxsdk/libspu/s_sk.c
    src/main/psxsdk/libspu/s_snv.c
    src/main/psxsdk/libspu/s_sr.c
    src/main/psxsdk/libspu/s_srmp.c
    src/main/psxsdk/libspu/s_stm.c
    src/main/psxsdk/libspu/s_stsa.c
    src/main/psxsdk/libspu/s_sva.c
    src/main/psxsdk/libspu/s_w.c
    src/main/psxsdk/libspu/s_wp.c
    src/main/psxsdk/libspu/spu.c
    src/main/psxsdk/libspu/sr_gaks.c

    src/pc/psxsdk/emu.cpp
    src/pc/psxsdk/mednafen/spu.cpp
)
if(WANT_LIBSND_LLE)
    list(APPEND SOURCE_FILES_PSX_SDK ${SOURCE_FILES_LIBSND_LLE})
endif()

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
    src/dra/game_handlers.c
    src/dra/pads.c
    src/dra/save_mgr_pre.c
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
    src/dra/628AC.c
    src/dra/62DEC.c
    src/dra/62EB8.c
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
    src/servant/tt_000/bat.c
    src/servant/tt_000/servant_clutdata.c
    src/servant/tt_000/bat_animation_data.c
    src/servant/tt_000/bat_data.c
    src/servant/tt_000/servant_spriteparts.c
    src/servant/tt_000/servant_events.c
)

set(SOURCE_FILES_TT_001
    src/servant/tt_001/ghost.c
    src/servant/tt_001/servant_clutdata.c
    src/servant/tt_001/ghost_animation_data.c
    src/servant/tt_001/ghost_data.c
    src/servant/tt_001/servant_spriteparts.c
    src/servant/tt_001/servant_events.c
)

set(SOURCE_FILES_TT_002
    src/servant/tt_002/faerie.c
    src/servant/tt_002/faerie_ability_data.c
    src/servant/tt_002/faerie_animation_data.c
    src/servant/tt_002/faerie_data.c
    src/servant/tt_002/faerie_spriteparts.c
    src/servant/tt_002/servant_events.c
)

set(SOURCE_FILES_STAGE_SEL
    src/pc/stages/stage_sel.c
    src/st/sel/banks.c
    src/st/sel/CD54.c
    src/st/sel/2C048.c
    src/st/sel/33164.c
    src/st/sel/3410C.c
    src/st/sel/3585C.c
    src/st/sel/cutscene.c
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
    src/st/cen/DB18.c
    src/st/cen/d_prize_drops.c
    src/st/cen/cutscene.c
    src/st/cen/F890.c
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
    src/st/nz0/311C0.c
    src/st/nz0/337B4.c
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
    src/st/st0/gen/e_laydef.c
    src/st/st0/e_init.c
    src/st/st0/gen/rooms.c
    src/st/st0/gen/e_layout.c
    src/st/st0/stage_data.c
    src/st/st0/gen/sprites.c
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
    src/st/st0/3101C.c
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
    src/st/wrp/gen/sprites.c
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
    src/boss/bo4/header.c
    src/boss/bo4/popup.c
    src/boss/bo4/prim_helpers.c
    src/boss/bo4/spritesheets.c
    src/boss/bo4/st_common.c
    src/boss/bo4/st_update.c
    src/boss/bo4/tile_data.c
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

# organization is:
# two executables, sdl2 and null, plus a shared library "core"
# any executable links core (which is pc shared code + sotn psx code)
# the null backend is present to try and help with developing a backend-agnostic interface
# and for a basic "does it segfault" check in CI

# core library

set(SOURCE_FILES_CORE
    ${SOURCE_FILES_DRA}
    ${SOURCE_FILES_RIC}
    ${SOURCE_FILES_PC}
    ${SOURCE_FILES_PSX_SDK}
    ${SOURCE_FILES_MOCK_SDK}
    ${SOURCE_FILES_3RD}
    ${SOURCE_FILES_STAGE_SEL}
    ${SOURCE_FILES_STAGE_CEN}
    ${SOURCE_FILES_STAGE_NZ0}
    ${SOURCE_FILES_STAGE_ST0}
    ${SOURCE_FILES_BOSS_BO4}
    ${SOURCE_FILES_STAGE_WRP}
    ${SOURCE_FILES_WEAPON}
    ${SOURCE_FILES_TT_000}
    ${SOURCE_FILES_TT_001}
    ${SOURCE_FILES_TT_002}
)
if (USE_PLAYER_MARIA)
    add_compile_definitions(USE_PLAYER_MARIA)
    list(APPEND SOURCE_FILES_CORE
            ${SOURCE_FILES_MARIA}
            src/pc/pl_maria.c)
endif()

add_library(core ${SOURCE_FILES_CORE})

target_include_directories(core PUBLIC
    include
    src/dra
    src/pc/3rd
)

target_compile_definitions(core PUBLIC
    _USE_MATH_DEFINES # needed for msvc
    VERSION_PC
    PERMUTER
    NON_MATCHING
    HARD_LINK
    _internal_version_us
)

# sdl2 target
add_executable(${PROJECT_NAME}
    src/pc/sdl2.c
    src/pc/render_soft.c
    src/pc/render_shared.c
    src/pc/render_gl.c
    src/pc/psxsdk/mednafen/gpu.cpp
    src/pc/psxsdk/mednafen/gpu_line.cpp
    src/pc/psxsdk/mednafen/gpu_polygon.cpp
    src/pc/psxsdk/mednafen/gpu_sprite.cpp
    src/pc/sdl2_macros.c
)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} core)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} core m)
endif()
if(WANT_LIBSND_LLE)
    target_compile_definitions(core PRIVATE WANT_LIBSND_LLE=1)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WANT_LIBSND_LLE=1)
endif()

# null target
add_executable(${PROJECT_NAME}_null
    src/pc/null.c
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME}_null PRIVATE core)
else()
    target_link_libraries(${PROJECT_NAME}_null PRIVATE core m)
endif()
