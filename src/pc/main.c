#include <unistd.h>
#include <SDL2/SDL.h>

#include "pc.h"
#include "dra.h"
#include "objects.h"

#define DISP_WIDTH 256
#define DISP_HEIGHT 256

SDL_Window* g_Window;
SDL_Renderer* g_Renderer;

void MainGame(void);

int main() {
    int ret;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ERRORF("SDL_Init: %s", SDL_GetError());
        return 1;
    }

    g_Window = SDL_CreateWindow(
        "SOTN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        DISP_WIDTH * SCREEN_SCALE, DISP_HEIGHT * SCREEN_SCALE,
        SDL_WINDOW_SHOWN);
    if (!g_Window) {
        ERRORF("SDL_CreateWindow: %s", SDL_GetError());
        ret = 1;
    } else {
        g_Renderer = SDL_CreateRenderer(
            g_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!g_Renderer) {
            ERRORF("SDL_CreateRenderer: %s", SDL_GetError());
            ret = 1;
        } else {
            MainGame();
            SDL_DestroyRenderer(g_Renderer);
        }
        SDL_DestroyWindow(g_Window);
    }

    SDL_Quit();
    return ret;
}
