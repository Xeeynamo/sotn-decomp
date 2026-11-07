// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../zero.h"
#include "../game.h"

extern s32 DAT_06086088;
extern u32 g_randomNext;

static s32 MovieSkipped(void) { return 0; }

s32 (*sotn_satz_movie_entry(void))(void) { return MovieSkipped; }

static void sotn_satz_dump_objects(uint64_t frame) {
    static FILE* file;
    static int opened;
    Entity* e;
    int i;

    if (!opened) {
        const char* path = getenv("SOTN_SATZ_OBJECTS");
        opened = 1;
        file = path ? fopen(path, "w") : NULL;
        if (file) {
            fputs("frame\tslot\tid\tx\ty\tvx\tvy\tfacing\tstep\tstep_s\tanim\n",
                  file);
        }
    }
    if (!file) {
        return;
    }
    fprintf(file, "%llu\t-1\t%u\t%d\t%d\t0\t0\t0\t%u\t%u\t0\n",
            (unsigned long long)frame, DAT_0605cea0.unk2,
            g_Tilemap.scrollX.i.hi, g_Tilemap.scrollY.i.hi, DAT_0605cea0.unk0,
            DAT_0605cea0.unk2);
    fprintf(file, "%llu\t-2\t0\t%d\t%d\t%d\t%d\t0\t0\t0\t0\n",
            (unsigned long long)frame, DAT_06086088, (s32)g_Timer,
            (s32)g_randomNext, 0);
    for (i = 0; i < 256; i++) {
        e = &g_Entities[i];
        if (e->entityId == 0 && i != 0) {
            continue;
        }
        fprintf(file, "%llu\t%d\t%u\t%d\t%d\t%d\t%d\t%u\t%u\t%u\t%d\n",
                (unsigned long long)frame, i, e->entityId, e->posX.i.hi,
                e->posY.i.hi, e->velocityX, e->velocityY, e->facingLeft,
                e->step, e->step_s, e->animCurFrame);
    }
    fflush(file);
}

void func_06032E88(unsigned int value);

static void sotn_satz_cram_init(void) {
    const char* path = getenv("SOTN_SATZ_CRAM_INIT");
    unsigned char cram[0x1000];
    FILE* f;
    unsigned i;

    if (!path || !(f = fopen(path, "rb"))) {
        return;
    }
    if (fread(cram, 1, sizeof(cram), f) == sizeof(cram)) {
        for (i = 0; i < sizeof(cram); i += 2) {
            satz_bus_write(0x25F00000 + i, (cram[i] << 8) | cram[i + 1], 2);
        }
    }
    fclose(f);
}

static void sotn_satz_warp(void) {
    const char* warp = getenv("SOTN_SATZ_WARP");
    unsigned x, y, room;

    if (!warp) {
        warp = SATZ_STAGE_START;
    }
    if (!*warp) {
        return;
    }
    if (sscanf(warp, "%i %i %i", &x, &y, &room) != 3) {
        satz_die("SOTN_SATZ_WARP: want \"X Y ROOM\"");
    }
    g_RoomTeleports[0x48].x = x;
    g_RoomTeleports[0x48].y = y;
    g_RoomTeleports[0x48].roomId = room;
}

void sotn_satz_boot_override(void) {
    sotn_satz_cram_init();
    g_CurrentRoom.stageID = SATZ_STAGE_ID;
    g_PlayableCharacter = SATZ_PLAYER_ID;
    D_8006C374 = 0x48;
    DAT_06061dd0 = 1;
    sotn_satz_warp();
}

unsigned sotn_satz_updates;
int sotn_satz_voice = -1;
void sotn_satz_poll(void) {}

static uint64_t s_Frame;

int sotn_satz_extra_iteration(void) {
    static unsigned long long frames[64], used = ~0ull;
    static int count = -1;
    const char* list;
    char* end;
    int i;

    if (count < 0) {
        count = 0;
        for (list = getenv("SOTN_SATZ_EXTRA"); list && *list && count < 64;
             list = *end ? end + 1 : end) {
            frames[count++] = strtoull(list, &end, 10);
        }
    }
    for (i = 0; i < count; i++) {
        if (frames[i] == s_Frame && used != s_Frame) {
            used = s_Frame;
            return 1;
        }
    }
    return 0;
}

void __real_SCL_DisplayFrame(void);
void __wrap_SCL_DisplayFrame(void) {
    if (!sotn_satz_extra_iteration()) {
        __real_SCL_DisplayFrame();
    }
}

static void sotn_satz_lag(uint64_t frame) {
    static unsigned long long frames[64];
    static int count = -1;
    const char* list;
    char* end;
    int i;

    if (count < 0) {
        count = 0;
        for (list = getenv("SOTN_SATZ_LAG"); list && *list && count < 64;
             list = *end ? end + 1 : end) {
            frames[count++] = strtoull(list, &end, 10);
        }
    }
    for (i = 0; i < count; i++) {
        if (frames[i] == frame) {
            g_Timer++;
        }
    }
}

static void sotn_satz_sync_seeds(uint64_t frame) {
    static int count = -1;
    static unsigned long long at[8];
    static long long values[8][4];
    static int fields[8];
    const char* seeds;
    int i;

    if (count < 0) {
        count = 0;
        for (seeds = getenv("SOTN_SATZ_SEEDS"); seeds && *seeds && count < 8;
             seeds = strchr(seeds, ';')) {
            seeds += *seeds == ';';
            fields[count] =
                sscanf(seeds, "%llu %lld %lld %lld %lld", &at[count],
                       &values[count][0], &values[count][1], &values[count][2],
                       &values[count][3]) -
                1;
            count += fields[count] == 1 || fields[count] >= 3;
            if (!strchr(seeds, ';')) {
                break;
            }
        }
    }
    for (i = 0; i < count; i++) {
        if (frame != at[i]) {
            continue;
        }
        if (fields[i] == 1) {
            g_Timer = (u32)values[i][0];
            continue;
        }
        DAT_06086088 = (s32)values[i][0];
        g_randomNext = (u32)values[i][1];
        func_06032E88((unsigned int)values[i][2]);
        if (fields[i] == 4) {
            g_Timer = (u32)values[i][3];
        }
    }
}

uint32_t satz_mem_read(uint32_t address, int size);

static void sotn_satz_watch(uint64_t frame) {
    static int loaded;
    static unsigned long long frames[64];
    static unsigned addresses[64], lengths[64];
    static char names[64][32];
    static int count;
    const char* path;
    const char* dir;
    char out[512];
    FILE* f;
    int i;
    unsigned j;

    if (!loaded) {
        loaded = 1;
        path = getenv("SOTN_SATZ_WATCH");
        if (path && (f = fopen(path, "r"))) {
            while (count < 64 && fscanf(f, "%llu %x %x %31s", &frames[count],
                                        &addresses[count], &lengths[count],
                                        names[count]) == 4) {
                count++;
            }
            fclose(f);
        }
    }
    dir = getenv("SOTN_SATZ_WATCH_DIR");
    for (i = 0; i < count; i++) {
        if (frames[i] != frame) {
            continue;
        }
        snprintf(out, sizeof(out), "%s/%s_%06llu.bin", dir ? dir : ".",
                 names[i], (unsigned long long)frame);
        if ((f = fopen(out, "wb"))) {
            for (j = 0; j < lengths[i]; j++) {
                fputc((int)(addresses[i] >= 0x25F80000
                                ? satz_bus_read(addresses[i] + j, 1)
                                : satz_mem_read(addresses[i] + j, 1)),
                      f);
            }
            fclose(f);
        }
    }
}

void satz_app_frame(uint64_t frame) {
    s_Frame = frame;
    sotn_satz_watch(frame);
    sotn_satz_sync_seeds(frame);
    sotn_satz_lag(frame);
    sotn_satz_dump_objects(frame);

    static u32 last[9] = {~0u};
    u32 now[9] = {
        DAT_0605cea0.unk2,        DAT_0605cea0.unk0, g_CurrentRoom.stageID,
        (u32)g_PlayableCharacter, DAT_0605D770.unk2, DAT_0605D770.unk8,
        DAT_0605cd70.unk2,        DAT_0605cd70.unk0, g_CurrentRoom.unk4};

    if (memcmp(now, last, sizeof(now))) {
        fprintf(stderr,
                "frame %llu: st=%x sub=%x stage=%x chr=%x d772=%x d778=%x "
                "play=%x/%x layout=%x\n",
                (unsigned long long)frame, now[0], now[1], now[2], now[3],
                now[4], now[5], now[6], now[7], now[8]);
        memcpy(last, now, sizeof(now));
    }
    if (DAT_0605cea0.unk2 == 0x31 && DAT_0605cea0.unk0 >= 6) {
        DAT_0605D7F8 = 1;
    }
}
