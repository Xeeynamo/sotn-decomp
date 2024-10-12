// SPDX-License-Identifier: AGPL-3.0-or-later
#include <common.h>
#include <log.h>
#include <game.h>
#include <stdlib.h>
#ifdef _MSC_VER
#define SDL_MAIN_HANDLED
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "pc.h"
#include <assert.h>
#include "sdl_defs.h"

extern SDL_Renderer* g_Renderer;
extern bool g_IsQuitRequested;
extern int g_WndWidth;
extern int g_WndHeight;
extern SDL_Window* g_Window;

u8* GetPix();
u8* GetFb();
extern u8* GetFb();
void SoftDrawSyncCallback();
u32 get_cs(s16 arg0, s16 arg1);
u32 get_ce(s16 arg0, s16 arg1);
int get_mode(int dfe, int dtd, int tpage);
u32 get_ofs(s16 arg0, s16 arg1);
u32 get_tw(RECT* arg0);

#define CLAMP(value, low, high)                                                \
    value < low ? low : (value > high ? high : value)

u32 D_8002C26C = 0;
void GPU_Init(bool pal_clock_and_tv);
void GPU_StartFrameC();

int32_t prev_update = 0;
void GPU_Power(void);
int power = 0;

extern void GPU_Write(const u32 timestamp, u32 A, u32 V);

void CopyVram(void) {
    SDL_Texture* t =
        SDL_CreateTexture(g_Renderer, SDL_PIXELFORMAT_ABGR1555,
                          SDL_TEXTUREACCESS_STREAMING, VRAM_W, VRAM_H);

    u16* pixels;
    int pitch = VRAM_STRIDE;
    SDL_LockTexture(t, NULL, (void**)&pixels, &pitch);

    u16* pix = GetFb();

    memcpy(pixels, pix, VRAM_W * VRAM_H * 2);

    SDL_UnlockTexture(t);

    // x, y, w, h
    SDL_Rect rsrc = {0, 0, 1024, 512};
    SDL_Rect rdst = {0, 0, 1024, 512};
    SDL_RenderCopy(g_Renderer, t, &rsrc, &rdst);

    SDL_DestroyTexture(t);
}

extern struct InitGameParams g_GameParams;
int SoftDrawSync(int mode) {
    CopyVram();

    SDL_RenderPresent(g_Renderer);
    SDL_RenderSetScale(g_Renderer, g_GameParams.scale, g_GameParams.scale);

    // SDL event handling
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            g_IsQuitRequested = 1;
            break;
        }
    }

    MyDrawSyncCallback(mode);

    return 0;
}

DISPENV* SoftPutDispEnv(DISPENV* env) {
    int w = env->disp.w * g_GameParams.scale;
    int h = env->disp.h * g_GameParams.scale;
    if (g_WndWidth == w && g_WndHeight == h) {
        return env;
    }

    s32 var_s1 = 0x08000000;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0_2;

    if (env->isrgb24 != 0) {
        var_s1 |= 0x10;
    }
    if (env->isinter != 0) {
        var_s1 |= 0x20;
    }
    // if (D_8002C270 != 0) {
    // var_s1 |= 0x80;
    // }
    temp_v1_2 = env->disp.w;
    if (temp_v1_2 >= 0x119) {
        if (temp_v1_2 < 0x161) {
            var_s1 |= 1;
        } else if (temp_v1_2 < 0x191) {
            var_s1 |= 0x40;
        } else if (temp_v1_2 < 0x231) {
            var_s1 |= 2;
        } else {
            var_s1 |= 3;
        }
    }
    temp_v1_3 = env->disp.h;
    var_v0_2 = temp_v1_3 < 0x121;
    if (env->pad0 == 0) {
        var_v0_2 = temp_v1_3 < 0x101;
    }
    if (var_v0_2 == 0) {
        var_s1 |= 0x24;
    }
    GPU_Write(0, 4, var_s1);
    GPU_Update(128);

    g_WndWidth = w;
    g_WndHeight = h;
    SDL_SetWindowSize(g_Window, w, h);
    return env;
}

void SoftSetDrawEnv(DR_ENV* dr_env, DRAWENV* env) {
    RECT temp;
    s32 var_t0;
    u16 var_v1;
    u32 D_8002C26C = 0;

    dr_env->code[0] = get_cs(env->clip.x, env->clip.y);
    dr_env->code[1] =
        get_ce(env->clip.w + env->clip.x - 1, env->clip.y + env->clip.h - 1);
    dr_env->code[2] = get_ofs(env->ofs[0], env->ofs[1]);
    dr_env->code[3] = get_mode(env->dfe, env->dtd, env->tpage);
    dr_env->code[4] = get_tw(&env->tw);
    dr_env->code[5] = 0xE6000000;

    var_t0 = 7;
    if (env->isbg != 0) {
        temp.x = env->clip.x;
        temp.y = env->clip.y;
        temp.w = env->clip.w;
        temp.h = env->clip.h;
        temp.w = CLAMP(temp.w, 0, 1023);

        if (temp.h >= 0) {
            if ((D_8002C26C != 0 && temp.h >= 1024) ||
                (D_8002C26C == 0 && temp.h >= 512)) {
                if (D_8002C26C != 0) {
                    var_v1 = 1023;
                } else {
                    var_v1 = 511;
                }
            } else {
                var_v1 = temp.h;
            }
        } else {
            var_v1 = 0;
        }

        temp.h = var_v1;
        if ((temp.x & 0x3F) || (temp.w & 0x3F)) {
            temp.x -= env->ofs[0];
            temp.y -= env->ofs[1];
            *((s32*)dr_env + var_t0++) =
                0x60000000 | env->b0 << 0x10 | env->g0 << 8 | env->r0;
            *((s32*)dr_env + var_t0++) = *(s32*)&temp.x;
            *((s32*)dr_env + var_t0++) = *(s32*)&temp.w;
            temp.x += env->ofs[0];
            temp.y += env->ofs[1];
        } else {
            *((s32*)dr_env + var_t0++) =
                0x02000000 | env->b0 << 0x10 | env->g0 << 8 | env->r0;
            *((s32*)dr_env + var_t0++) = *(s32*)&temp.x;
            *((s32*)dr_env + var_t0++) = *(s32*)&temp.w;
        }
    }

    *((u8*)&(dr_env->tag) + 3) = var_t0 - 1;
}

u32 get_cs(s16 arg0, s16 arg1) {
    s32 var_v0;
    s32 var_v1;

    arg0 = CLAMP(arg0, 0, 1023);

    if (arg1 >= 0) {
        if ((D_8002C26C != 0 && arg1 >= 1024) ||
            (D_8002C26C == 0 && arg1 >= 512)) {
            if (D_8002C26C != 0) {
                arg1 = 1023;
            } else {
                arg1 = 511;
            }
        }
    } else {
        arg1 = 0;
    }

    if (D_8002C26C == 0) {
        var_v1 = (arg1 & 0x3FF) << 0xA;
        var_v0 = arg0 & 0x3FF;
    } else {
        var_v1 = (arg1 & 0xFFF) << 0xC;
        var_v0 = arg0 & 0xFFF;
    }
    return var_v1 | (var_v0 | 0xE3000000);
}

u32 get_ce(s16 arg0, s16 arg1) {
    s16 var_a1;
    s16 var_v0_2;
    s32 var_v0;
    s32 var_v1;

    var_a1 = arg1;
    if (arg0 >= 0) {
        var_v0_2 = arg0;
        if (arg0 >= 0x400) {
            var_v0_2 = 0x3FF;
        }
    } else {
        var_v0_2 = 0;
    }
    if (var_a1 >= 0) {
        if (D_8002C26C != 0) {
            if (var_a1 < 0x400) {

            } else {
                goto block_9;
            }
        } else if (var_a1 >= 0x200) {
        block_9:
            var_a1 = 0x1FF;
            if (D_8002C26C != 0) {
                var_a1 = 0x3FF;
            }
        }
    } else {
        var_a1 = 0;
    }
    if (D_8002C26C == 0) {
        var_v1 = (var_a1 & 0x1FF) << 0xA;
        var_v0 = var_v0_2 & 0x3FF;
    } else {
        var_v1 = (var_a1 & 0xFFF) << 0xC;
        var_v0 = var_v0_2 & 0xFFF;
    }
    return var_v1 | (var_v0 | 0xE4000000);
}

int get_mode(int dfe, int dtd, int tpage) {
    if (D_8002C26C) {
        return (dtd ? 0xE1000800 : 0xE1000000) | (dfe ? 0x1000 : 0) |
               (tpage & 0x27FF);
    } else {
        return (dtd ? 0xE1000200 : 0xE1000000) | (dfe ? 0x400 : 0) |
               (tpage & 0x1FF);
    }
}

u32 get_ofs(s16 arg0, s16 arg1) {
    s32 var_v0;
    s32 var_v1;

    if (D_8002C26C == 0) {
        var_v1 = (arg1 & 0x7FF) << 0xB;
        var_v0 = arg0 & 0x7FF;
    } else {
        var_v1 = (arg1 & 0xFFF) << 0xC;
        var_v0 = arg0 & 0xFFF;
    }
    return var_v1 | (var_v0 | 0xE5000000);
}

u32 get_tw(RECT* arg0) {
    u32 pad[4];

    if (arg0 != 0) {
        pad[0] = (u8)arg0->x >> 3;
        pad[2] = (s32)(-arg0->w & 0xFF) >> 3;
        pad[1] = (u8)arg0->y >> 3;
        pad[3] = (s32)(-arg0->h & 0xFF) >> 3;
        return (pad[1] << 0xF) | 0xE2000000 | (pad[0] << 0xA) | (pad[3] << 5) |
               pad[2];
    }
    return 0;
}

DRAWENV* SoftPutDrawEnv(DRAWENV* env) {
    if (env->isbg) {
        SDL_SetRenderDrawColor(g_Renderer, env->r0, env->g0, env->b0, 255);
    }

    SoftSetDrawEnv(&env->dr_env, env);
    env->dr_env.tag |= 0xFFFFFF;

    GPU_Write(0, 0, env->dr_env.code[0]);
    GPU_Write(0, 0, env->dr_env.code[1]);
    GPU_Write(0, 0, env->dr_env.code[2]);
    GPU_Write(0, 0, env->dr_env.code[3]);
    GPU_Write(0, 0, env->dr_env.code[4]);
    GPU_Write(0, 0, env->dr_env.code[5]);
    GPU_Write(0, 0, env->dr_env.code[6]);
    GPU_Write(0, 0, env->dr_env.code[7]);
    GPU_Write(0, 0, env->dr_env.code[8]);
    GPU_Write(0, 0, env->dr_env.code[9]);
    GPU_Write(0, 0, env->dr_env.code[10]);
    GPU_Write(0, 0, env->dr_env.code[11]);
    GPU_Write(0, 0, env->dr_env.code[12]);
    GPU_Write(0, 0, env->dr_env.code[13]);
    GPU_Write(0, 0, env->dr_env.code[14]);

    for (int i = 0; i < 16; i++) {
        GPU_Update(128);
    }

    return env;
}

void SoftDrawOTag(OT_TYPE* p) {

    if (!power) {
        GPU_Init(0);
        GPU_Power();
        power = true;
    }
    POLY_G4* g4;
    POLY_GT4* gt4;
    LINE_G2* lg2;
    SPRT* sp;
    SPRT_16* sp16;
    TILE* tile;
    DR_MODE* drMode;

    GPU_StartFrameC();

    for (size_t n = 0; (u_long)p != 0xffffff; n++, p = (OT_TYPE*)p->tag) {
        P_TAG* tag = (P_TAG*)p;
        if (tag->len == 0) {
            continue;
        }

        u8 code = tag->code & ~3;
        int num_updates = 0;

        switch (code) {
        case 0x00:
            break;
        case 0x38:
            g4 = (POLY_G4*)tag;
            GPU_Write(0, 0, *(u32*)&g4->r0); // 4
            GPU_Write(0, 0, *(u32*)&g4->x0); // 8
            GPU_Write(0, 0, *(u32*)&g4->r1); // C
            GPU_Write(0, 0, *(u32*)&g4->x1); // 10
            GPU_Write(0, 0, *(u32*)&g4->r2); // 14
            GPU_Write(0, 0, *(u32*)&g4->x2); // 18
            GPU_Write(0, 0, *(u32*)&g4->r3); // 1C
            GPU_Write(0, 0, *(u32*)&g4->x3); // 20
            num_updates = 8;
            break;
        case 0x3C:
            gt4 = (POLY_GT4*)tag;
            GPU_Write(0, 0, *(u32*)&gt4->r0); // 4
            GPU_Write(0, 0, *(u32*)&gt4->x0); // 8
            GPU_Write(0, 0, *(u32*)&gt4->u0); // C
            GPU_Write(0, 0, *(u32*)&gt4->r1); // 10
            GPU_Write(0, 0, *(u32*)&gt4->x1); // 14
            GPU_Write(0, 0, *(u32*)&gt4->u1); // 18
            GPU_Write(0, 0, *(u32*)&gt4->r2); // 1c
            GPU_Write(0, 0, *(u32*)&gt4->x2); // 20
            GPU_Write(0, 0, *(u32*)&gt4->u2); // 24
            GPU_Write(0, 0, *(u32*)&gt4->r3); // 28
            GPU_Write(0, 0, *(u32*)&gt4->x3); // 2c
            GPU_Write(0, 0, *(u32*)&gt4->u3); // 30
            num_updates = 12;
            break;
        case 0x50:
            lg2 = (LINE_G2*)tag;
            GPU_Write(0, 0, *(u32*)&lg2->r0);
            GPU_Write(0, 0, *(u32*)&lg2->x0);
            GPU_Write(0, 0, *(u32*)&lg2->r1);
            GPU_Write(0, 0, *(u32*)&lg2->x1);
            num_updates = 4;
            break;
        case 0x60:
            tile = (TILE*)tag;
            GPU_Write(0, 0, *(u32*)&tile->r0);
            GPU_Write(0, 0, *(u32*)&tile->x0);
            GPU_Write(0, 0, *(u32*)&tile->w);
            num_updates = 3;
            break;
        case 0x64:
            sp = (SPRT*)tag;
            GPU_Write(0, 0, *(u32*)&sp->r0);
            GPU_Write(0, 0, *(u32*)&sp->x0);
            GPU_Write(0, 0, *(u32*)&sp->u0);
            GPU_Write(0, 0, *(u32*)&sp->w);
            num_updates = 4;
            break;
        case 0x7C:
            sp16 = (SPRT_16*)tag;
            GPU_Write(0, 0, *(u32*)&sp16->r0);
            GPU_Write(0, 0, *(u32*)&sp16->x0);
            GPU_Write(0, 0, *(u32*)&sp16->u0);
            num_updates = 3;
            break;
        case 0xE0:
            drMode = (DR_MODE*)tag;
            GPU_Write(0, 0, drMode->code[0]);
            GPU_Write(0, 0, drMode->code[1]);
            num_updates = 2;
            break;
        default:
            WARNF("SoftDrawOTag: code %02X not supported", code);
            break;
        }
        for (int i = 0; i < num_updates; i++) {
            GPU_Update(128);
        }
    }
}

int MyMoveImage(RECT* rect, int x, int y) {
    u32 param[5];

    param[0] = 0x04FFFFFF;
    param[1] = 0x80000000;
    param[2] = LOW(rect->x);
    param[3] = (u16)y << 0x10 | (u16)x;
    param[4] = LOW(rect->w);

    for (int i = 0; i < 5; i++) {
        GPU_Write(0, 0, param[i]);
        GPU_Update(128);
    }
    return 0;
}
