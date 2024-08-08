#include <common.h>
#include <log.h>
#include <game.h>
#include <stdlib.h>
#include "pc.h"
#include <assert.h>
#include <string.h>
#include "sdl_defs.h"

enum Renderers render_mode = RENDER_SOFT;

int SoftDrawSync(int mode);
DISPENV* SoftPutDispEnv(DISPENV* env);
void SoftSetDrawEnv(DR_ENV* dr_env, DRAWENV* env);
DRAWENV* SoftPutDrawEnv(DRAWENV* env);
void SoftDrawOTag(OT_TYPE* p);

int GlDrawSync(int mode);
DISPENV* GlPutDispEnv(DISPENV* env);
void GlSetDrawEnv(DR_ENV* dr_env, DRAWENV* env);
DRAWENV* GlPutDrawEnv(DRAWENV* env);
void GlDrawOTag(OT_TYPE* p);

int MyDrawSync(int mode) {
    if (render_mode == RENDER_SOFT) {
        return SoftDrawSync(mode);
    } else {
        return GlDrawSync(mode);
    }
    return 0;
}

DISPENV* MyPutDispEnv(DISPENV* env) {
    if (render_mode == RENDER_SOFT) {
        return SoftPutDispEnv(env);
    } else {
        return GlPutDispEnv(env);
    }
    return env;
}

void MySetDrawEnv(DR_ENV* dr_env, DRAWENV* env) {
    if (render_mode == RENDER_SOFT) {
        SoftSetDrawEnv(dr_env, env);
    } else {
        GlSetDrawEnv(dr_env, env);
    }
}

DRAWENV* MyPutDrawEnv(DRAWENV* env) {
    if (render_mode == RENDER_SOFT) {
        return SoftPutDrawEnv(env);
    } else {
        return GlPutDrawEnv(env);
    }

    return env;
}

void MyDrawOTag(OT_TYPE* p) {
    if (render_mode == RENDER_SOFT) {
        SoftDrawOTag(p);
    } else {
        GlDrawOTag(p);
    }
}

extern u8* GetFb();
extern u16 g_RawVram[VRAM_W * VRAM_H];

int MyLoadImage(RECT* rect, u_long* p) {
    {
        u16* mem = (u16*)p;
        u16* vram = g_RawVram;
        vram += rect->x + rect->y * VRAM_W;

        for (int i = 0; i < rect->h; i++) {
            memcpy(vram, mem, rect->w * 2);
            mem += rect->w;
            vram += VRAM_W;
        }
    }

    // copy to software vram
    {
        u16* mem = (u16*)p;
        u16* vram = GetFb();
        vram += rect->x + rect->y * VRAM_W;

        for (int i = 0; i < rect->h; i++) {
            memcpy(vram, mem, rect->w * 2);
            mem += rect->w;
            vram += VRAM_W;
        }
    }
    return 0;
}
