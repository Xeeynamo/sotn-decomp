#include <unistd.h>
#include <SDL2/SDL.h>

#include "pc.h"
#include "dra.h"
#include "objects.h"
#include "psxsdk/cdc.h"

#define DISP_WIDTH 256
#define DISP_HEIGHT 256

SDL_Window* g_Window;
SDL_Renderer* g_Renderer;

void InitGame(void);
void MainGame(void);

void SDLAudioCallback(void* data, Uint8* buffer, int length) {
    int i = 0;
    while (i * 4 < length) {
        if (AudioBuffer.ReadPos < AudioBuffer.Size) {
            // emit until we have to generate again
            int32_t samples[2];

            GetCDAudio(samples);

            buffer[i * 4 + 1] = samples[0] >> 8;
            buffer[i * 4 + 0] = samples[0];

            // right
            buffer[i * 4 + 3] = samples[1] >> 8;
            buffer[i * 4 + 2] = samples[1];
            i += 1;
        } else if (CdReading()) {
            // generate more audio
            ExecCd();
        }
    }
}

int main(int argc, char* argv[]) {
    const char* filename;
    int ret;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        ERRORF("SDL_Init: %s", SDL_GetError());
        return 1;
    }

    if (argc < 2) {
        filename = "disks/sotn.us.bin";
    } else {
        filename = argv[1];
    }

    OpenCd(filename);

    SDL_AudioSpec spec;

    spec.freq = 44100;
    spec.format = AUDIO_S16;
    spec.channels = 2;
    spec.samples = 2048;
    spec.callback = SDLAudioCallback;

    SDL_AudioSpec obtained;
    SDL_AudioDeviceID device =
        SDL_OpenAudioDevice(NULL, false, &spec, &obtained, false);

    SDL_PauseAudioDevice(device, 0);

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
            InitGame();
            MainGame();
            SDL_DestroyRenderer(g_Renderer);
        }
        SDL_DestroyWindow(g_Window);
    }

    SDL_Quit();
    return ret;
}
