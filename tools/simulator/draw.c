#include <SDL2/SDL.h>
#include <game.h>

u8 vram[1024 * 1024];
extern SDL_Renderer* g_Renderer;

s32 GetColor(u16* palette, int colorIndex) {
    u16 ch = palette[colorIndex & 15];
    u32 r = ch & 0x1F;
    u32 g = (ch >> 5) & 0x1F;
    u32 b = (ch >> 10) & 0x1F;
    u32 a = ch & 0x7FFF;
    return (r << 3) | (g << 11) | (b << 19) | (a ? 0xFF000000 : 0);
}

int LoadImage(RECT* rect, u_long* p) {
    const int VRAM_STRIDE = 1024;
    s32 i;
    u16* src = (u16*)p;
    u16* dst = (u16*)(vram + rect->x * 2 + rect->y * VRAM_STRIDE * 2);

    for (i = 0; i < rect->h; i++) {
        memcpy(dst, src, rect->w * 2);
        dst += VRAM_STRIDE;
        src += rect->w;
    }

    return 1;
}

void DrawSprite(int x, int y, u8 w, u8 h, u8 u, u8 v, u8 tpage, u8 clut,
                u16 flags) {
    const uint32_t vram_stride = 2048;
    const uint32_t rmask = 0x000000FF;
    const uint32_t gmask = 0x0000FF00;
    const uint32_t bmask = 0x00FF0000;
    const uint32_t amask = 0xFF000000;

    int quadrant = (tpage >> 2) & 31;
    fflush(stdout);

    u32* pixels = malloc(256 * 256 * 4);
    if (pixels == NULL)
        return;

    u16* palette = (u16*)vram;
    palette += 240 / 2 * vram_stride; // palette start
    palette += (clut & 15) * 16;
    palette += ((clut >> 4) & 15) * vram_stride / 2;

    int sx, sy;
    for (sy = 0; sy < 256; sy++) {
        s32 quadX = 128 * (quadrant & 15);
        s32 quadY = vram_stride * 256 * (quadrant >> 4);
        u8* src = &vram[sy * vram_stride + quadX + quadY];
        u32* dst = &pixels[sy * 256];
        for (sx = 0; sx < 256; sx += 2) {
            u8 ch = src[sx >> 1];
            dst[sx + 1] = GetColor(palette, ch >> 4);
            dst[sx + 0] = GetColor(palette, ch & 15);
        }
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        pixels, 256, 256, 32, 256 * 4, rmask, gmask, bmask, amask);
    if (surface) {
        SDL_Texture* texture =
            SDL_CreateTextureFromSurface(g_Renderer, surface);
        if (texture) {
            SDL_Rect srcRect = {u, v, w, h};
            SDL_Rect dstRect = {x, y, w, h};
            SDL_Point pivot = {0, 0};
            SDL_RendererFlip flip = 0;
            if (flags & 2) {
                flip |= SDL_FLIP_HORIZONTAL;
            }
            SDL_RenderCopyEx(g_Renderer, texture, &srcRect, &dstRect, 0, &pivot,
                             flip);
            SDL_DestroyTexture(texture);
        } else {
            FntPrint("error creating texture:");
            FntPrint("%s", SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }
    free(pixels);
}

void DrawSpritePart(Entity* e, SpritePart* p) {
    if (e == NULL || p == NULL) {
        return;
    }

    DrawSprite(e->posX.i.hi + p->offsetx, e->posY.i.hi + p->offsety, p->width,
               p->height, p->left, p->top, p->tileset, p->clut, p->flags);
}

void DrawSpriteParts(Entity* e, SpriteParts* p) {
    s32 i;

    if (e == NULL || p == NULL) {
        return;
    }

    for (i = 0; i < p->count; i++) {
        DrawSpritePart(e, &p->parts[i]);
    }
}