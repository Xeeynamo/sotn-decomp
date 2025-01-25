#include "common.h"
#include <psxsdk/libgpu.h>

u_short LoadTPage(u_long* pix, int tp, int abr, int x, int y, int w, int h) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.h = h;
    switch (tp) {
    case 0:
        rect.w = w / 4;
        break;
    case 1:
        rect.w = w / 2;
        break;
    case 2:
        rect.w = w;
        break;
    }
    LoadImage(&rect, pix);

    return GetTPage(tp, abr, x, y);
}

u_short LoadClut(u_long* clut, int x, int y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 256;
    rect.h = 1;
    LoadImage(&rect, clut);

    return GetClut(x, y);
}

DRAWENV* SetDefDrawEnv(DRAWENV* env, s32 x, s32 y, s32 w, s32 h) {
    env->clip.x = x;
    env->clip.y = y;
    env->clip.w = w;
    env->clip.h = h;
    env->ofs[0] = x;
    env->ofs[1] = y;
    env->tw.x = 0;
    env->tw.y = 0;
    env->tw.w = 0;
    env->tw.h = 0;
    env->r0 = 0;
    env->g0 = 0;
    env->b0 = 0;
    env->dtd = 1;
    env->dfe = h != 480;
    env->tpage = GetTPage(0, 0, 640, 0);
    env->isbg = 0;
    return env;
}

DISPENV* SetDefDispEnv(DISPENV* env, s32 x, s32 y, s32 w, s32 h) {
    env->disp.x = x;
    env->disp.y = y;
    env->disp.w = w;
    env->screen.x = 0;
    env->screen.y = 0;
    env->screen.w = 0;
    env->screen.h = 0;
    env->isrgb24 = 0;
    env->isinter = 0;
    env->pad1 = 0;
    env->pad0 = 0;
    env->disp.h = h;
    return env;
}
