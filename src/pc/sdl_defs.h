// SPDX-License-Identifier: AGPL-3.0-only
#ifndef SDL_DEFS_H
#define SDL_DEFS_H
typedef enum {
    DEBUG_SDL_NONE,
    DEBUG_SDL_SHOW_VRAM_16bpp,
    DEBUG_SDL_SHOW_VRAM_8bpp,
    DEBUG_SDL_SHOW_VRAM_4bpp,
} DebugSdl;

enum Renderers { RENDER_SOFT, RENDER_GL };

extern enum Renderers render_mode;
#endif
