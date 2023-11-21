#include "pc.h"
#include "dra.h"
#include "sfx.h"
#include <SDL2/SDL.h>

extern SDL_Window* g_Window;
extern SDL_Renderer* g_Renderer;
bool g_IsQuitRequested;
int g_Frame = 0;

void SotnInit() { SoundInit(); }

void UpdateGame() {
    // SDL event handling
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            g_IsQuitRequested = 1;
            break;
        }
    }
    // Clear the renderer
    SDL_SetRenderDrawColor(g_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_Renderer);

    DEBUGF("-------------------- frame %d --------------------", g_Frame);
    if (g_Frame == 0) {
        INFOF("now playing '%s'", "MU_LOST_PAINTING");
        PlaySfx(MU_LOST_PAINTING);
    }

    // Update the renderer
    SDL_RenderPresent(g_Renderer);
    SDL_RenderSetScale(g_Renderer, SCREEN_SCALE, SCREEN_SCALE);
    g_Frame++;
}
