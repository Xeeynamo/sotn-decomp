// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "game.h"

extern void (*g_MainGame)();
extern CdlFILE main_cdlFile;
extern u8 main_cdlMode[];
extern s32 main_fd;

void main(void) {
    ResetCallback();
    InitHeap((void*)0x801F0000, 0x7800); // force build
    CdInit();

    g_GameState = Game_Boot;

    do {
        main_fd = open("sim:c:\\bin\\dra.bin", 1);
    } while (main_fd == -1 && --g_GameState != Game_Init);

    if (g_GameState != Game_Init) {
        read(main_fd, (void*)DRA_PRG_PTR, 0x130000);
        close(main_fd);
        g_UseDisk = 0;
        main_fd = open("sim:c:\\bin\\dra.bio", 1);

        if (main_fd != -1) {
            g_UseDisk = 2;
        }

        do {
            main_fd = open("sim:c:\\bin\\f_map.bin", 1);
        } while (main_fd < 0);

        read(main_fd, (void*)CASTLE_MAP_PTR, 0x8000);
        close(main_fd);
    } else {
    main_search_loop_1:
        while (!CdSearchFile(&main_cdlFile, "\\DRA.BIN;1")) {
        }

        *main_cdlMode = CdlModeSpeed | CdlModeSpeedNormal;
        CdControl(CdlSetmode, main_cdlMode, NULL);

        while (CdSync(1, NULL) != 2) {
        }

        g_GameState = (main_cdlFile.size + 0x7ff) >> 0xB;
        CdControl(CdlSetloc, &main_cdlFile, NULL);
        CdRead(g_GameState, (u32*)DRA_PRG_PTR, 0x80);
        // block until read is complete
        main_fd = CdReadSync(0, NULL);
        if (main_fd < 0) {
            goto main_search_loop_1;
        }

        g_UseDisk = 1;

    main_search_loop_2:
        if (!CdSearchFile(&main_cdlFile, "\\F_MAP.BIN;1")) {
            goto main_search_loop_2;
        } else {
            g_GameState = (main_cdlFile.size + 0x7ff) >> 0xB;
        }
        CdControl(CdlSetloc, &main_cdlFile, NULL);
        CdRead(g_GameState, (u32*)CASTLE_MAP_PTR, 0x80);
        // block until read is complete
        main_fd = CdReadSync(0, NULL);

        if (main_fd < 0) {
            goto main_search_loop_2;
        }
    }
    g_MainGame();
}

const char a0123456789abcd[] = "0123456789ABCDEF\0\0\0\0";
