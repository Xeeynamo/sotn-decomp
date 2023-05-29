#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <game.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_SCALE 4
#define DISP_WIDTH 256
#define DISP_HEIGHT 256

void SotnInit(void);
void SotnUpdate(void);
void SotnRender(void);

TTF_Font* g_Font;
SDL_Window* g_Window;
SDL_Renderer* g_Renderer;
int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    g_Window =
        SDL_CreateWindow("SOTN simulator", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, DISP_WIDTH * SCREEN_SCALE,
                         DISP_HEIGHT * SCREEN_SCALE, SDL_WINDOW_SHOWN);
    if (!g_Window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    g_Renderer = SDL_CreateRenderer(
        g_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!g_Renderer) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        SDL_DestroyWindow(g_Window);
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
               TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Load font
    g_Font = TTF_OpenFont("font.ttf", 12);
    if (!g_Font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(g_Renderer);
        SDL_DestroyWindow(g_Window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    int quit = 0;
    SDL_Event event;

    SotnInit();
    while (!quit) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(g_Renderer, 0, 0, 0, 255);
        SDL_RenderClear(g_Renderer);

        // Game stuff
        SotnUpdate();
        SotnRender();

        // Update the renderer
        SDL_RenderPresent(g_Renderer);
        SDL_RenderSetScale(g_Renderer, SCREEN_SCALE, SCREEN_SCALE);
    }

    TTF_CloseFont(g_Font);
    TTF_Quit();

    SDL_DestroyRenderer(g_Renderer);
    SDL_DestroyWindow(g_Window);
    SDL_Quit();

    return 0;
}

// Function to render text on the screen
void PrintText(const char* text, int x, int y, unsigned int color) {
    if (!g_Font) {
        printf("Font not initialized\n");
        return;
    }

    SDL_Color fontColor = *(SDL_Color*)&color;
    fontColor.a = 0xFF;
    fontColor.r = 0xFF;
    fontColor.g = 0xFF;
    fontColor.b = 0xFF;

    SDL_Surface* surface = TTF_RenderText_Blended(g_Font, text, fontColor);
    if (!surface) {
        printf("Failed to create surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(g_Renderer, surface);
    if (!texture) {
        printf("Failed to create texture! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    textRect.w = surface->w;
    textRect.h = surface->h;

    SDL_RenderCopy(g_Renderer, texture, NULL, &textRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
