// SPDX-License-Identifier: AGPL-3.0-only
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
#include "sdl_defs.h"
#include "sdl2_macros.h"

extern bool g_IsQuitRequested;
extern u16 g_RawVram[VRAM_W * VRAM_H];
SDL_Window* g_Window = NULL;
SDL_Renderer* g_Renderer = NULL;
SDL_AudioSpec g_SdlAudioSpecs = {0};
SDL_AudioDeviceID g_SdlAudioDevice = {0};
DebugSdl g_DebugSdl = DEBUG_SDL_NONE;
SDL_Texture* g_VramTex = NULL;
int g_LastVramTexTpage = -1;
int g_LastVramTexClut = -1;
int g_WndWidth = -1;
int g_WndHeight = -1;

uint32_t GPU_Update(const int32_t sys_timestamp);

void ResetPlatform(void);
bool InitPlatform() {
    atexit(ResetPlatform);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) <
        0) {
        ERRORF("SDL_Init: %s", SDL_GetError());
        return false;
    }

    g_Window = SDL_CreateWindow(
        "SOTN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        DISP_WIDTH * SCREEN_SCALE, DISP_HEIGHT * SCREEN_SCALE,
        SDL_WINDOW_SHOWN);
    if (!g_Window) {
        ERRORF("SDL_CreateWindow: %s", SDL_GetError());
        return false;
    }

    g_Renderer = SDL_CreateRenderer(
        g_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!g_Renderer) {
        ERRORF("SDL_CreateRenderer: %s", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawBlendMode(g_Renderer, SDL_BLENDMODE_BLEND);

    g_VramTex = SDL_CreateTexture(g_Renderer, SDL_PIXELFORMAT_ABGR1555,
                                  SDL_TEXTUREACCESS_STREAMING, 256, 256);
    if (!g_VramTex) {
        ERRORF("unable to create VRAM texture: %s", SDL_GetError());
        return false;
    }
    SDL_SetTextureBlendMode(g_VramTex, SDL_BLENDMODE_BLEND);

    return true;
}

void ResetPlatform(void) {
    g_LastVramTexTpage = -1;
    g_LastVramTexClut = -1;
    if (g_VramTex) {
        SDL_DestroyTexture(g_VramTex);
        g_VramTex = NULL;
    }

    if (g_Renderer) {
        SDL_DestroyRenderer(g_Renderer);
        g_Renderer = NULL;
    }

    if (g_Window) {
        SDL_DestroyWindow(g_Window);
        g_Window = NULL;
    }

    SDL_Quit();
}

int MyResetGraph(int arg0) { return 0; }
void SoundRevCallback(void* userdata, u8* stream, int len);
void MyAudioCallback(void* data, Uint8* buffer, int length);
void SDLAudioCallback(void* data, Uint8* buffer, int length) {
#ifdef WANT_LIBSND_LLE
    SoundRevCallback(data, buffer, length);
#else
    MyAudioCallback(data, buffer, length);
#endif
}

void MySsInitHot(void) {
    SDL_AudioSpec specs = {0};
    specs.freq = 44100;
    specs.format = AUDIO_S16;
    specs.channels = 2;
    specs.samples = 2048;
    specs.callback = SDLAudioCallback;

    g_SdlAudioDevice =
        SDL_OpenAudioDevice(NULL, false, &specs, &g_SdlAudioSpecs, false);
    if (g_SdlAudioDevice == 0) {
        WARNF("SDL_OpenAudioDevice failed: %s", SDL_GetError());
        return;
    }
    INFOF("SDL audio device opened: %d", g_SdlAudioDevice);

    SDL_PauseAudioDevice(g_SdlAudioDevice, 0);
}

typedef struct {
    SDL_GameControllerButton sdlButton;
    unsigned int psxButton;
} ControllerButtonConfig;
static ControllerButtonConfig controller_set[] = {
    {SDL_CONTROLLER_BUTTON_A, PAD_CROSS},
    {SDL_CONTROLLER_BUTTON_B, PAD_CIRCLE},
    {SDL_CONTROLLER_BUTTON_X, PAD_SQUARE},
    {SDL_CONTROLLER_BUTTON_Y, PAD_TRIANGLE},
    {SDL_CONTROLLER_BUTTON_BACK, PAD_SELECT},
    {SDL_CONTROLLER_BUTTON_START, PAD_START},
    {SDL_CONTROLLER_BUTTON_LEFTSTICK, PAD_L3},
    {SDL_CONTROLLER_BUTTON_RIGHTSTICK, PAD_R3},
    {SDL_CONTROLLER_BUTTON_LEFTSHOULDER, PAD_L1},
    {SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, PAD_L2},
    {SDL_CONTROLLER_BUTTON_DPAD_UP, PAD_UP},
    {SDL_CONTROLLER_BUTTON_DPAD_DOWN, PAD_DOWN},
    {SDL_CONTROLLER_BUTTON_DPAD_LEFT, PAD_LEFT},
    {SDL_CONTROLLER_BUTTON_DPAD_RIGHT, PAD_RIGHT},
};
const int AxisTreshold = SDL_JOYSTICK_AXIS_MAX / 2;
static SDL_GameController* controllers[2] = {NULL, NULL};
void MyPadInit(int mode) {
    int num = SDL_NumJoysticks();
    if (num > 0) {
        controllers[0] = SDL_GameControllerOpen(0);
        if (num > 1) {
            controllers[1] = SDL_GameControllerOpen(1);
        }
    }
}

u_long MyPadRead(int id) {
    u_long pressed = 0;
    if (controllers[id]) {
        SDL_GameController* controller = &controllers[id];
        SDL_GameControllerUpdate();
        for (int i = 0; i < LEN(controller_set); i++) {
            if (SDL_GameControllerGetButton(
                    controller, controller_set[i].sdlButton)) {
                pressed |= controller_set[i].psxButton;
            }
        }

        if (SDL_GameControllerGetAxis(
                controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) > AxisTreshold) {
            pressed |= PAD_L2;
        }
        if (SDL_GameControllerGetAxis(
                controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > AxisTreshold) {
            pressed |= PAD_R2;
        }

        short x =
            SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
        short y =
            SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
        if (y < -AxisTreshold) {
            pressed |= PAD_UP;
        } else if (y > AxisTreshold) {
            pressed |= PAD_DOWN;
        }
        if (x < -AxisTreshold) {
            pressed |= PAD_LEFT;
        } else if (x > AxisTreshold) {
            pressed |= PAD_RIGHT;
        }
    }

    if (id == 0) { // the keyboard is only bounded to the first controller
        const u8* keyb = SDL_GetKeyboardState(NULL);
        if (keyb[SDL_SCANCODE_ESCAPE]) {
            g_IsQuitRequested = 1;
        }
        pressed |= keyb[SDL_SCANCODE_UP] ? PAD_UP : 0;
        pressed |= keyb[SDL_SCANCODE_DOWN] ? PAD_DOWN : 0;
        pressed |= keyb[SDL_SCANCODE_LEFT] ? PAD_LEFT : 0;
        pressed |= keyb[SDL_SCANCODE_RIGHT] ? PAD_RIGHT : 0;
        pressed |= keyb[SDL_SCANCODE_X] ? PAD_CROSS : 0;
        pressed |= keyb[SDL_SCANCODE_S] ? PAD_TRIANGLE : 0;
        pressed |= keyb[SDL_SCANCODE_Z] ? PAD_SQUARE : 0;
        pressed |= keyb[SDL_SCANCODE_D] ? PAD_CIRCLE : 0;
        pressed |= keyb[SDL_SCANCODE_BACKSPACE] ? PAD_SELECT : 0;
        pressed |= keyb[SDL_SCANCODE_RETURN] ? PAD_START : 0;
        pressed |= keyb[SDL_SCANCODE_Q] ? PAD_L1 : 0;
        pressed |= keyb[SDL_SCANCODE_R] ? PAD_R1 : 0;
        pressed |= keyb[SDL_SCANCODE_W] ? PAD_L2 : 0;
        pressed |= keyb[SDL_SCANCODE_E] ? PAD_R2 : 0;

        g_DebugSdl = DEBUG_SDL_NONE;
        if (keyb[SDL_SCANCODE_F5]) {
            g_DebugSdl = DEBUG_SDL_SHOW_VRAM_16bpp;
        }
        if (keyb[SDL_SCANCODE_F6]) {
            g_DebugSdl = DEBUG_SDL_SHOW_VRAM_8bpp;
        }
        if (keyb[SDL_SCANCODE_F7]) {
            g_DebugSdl = DEBUG_SDL_SHOW_VRAM_4bpp;
        }

        render_mode = RENDER_SOFT;
        if (keyb[SDL_SCANCODE_F8]) {
            render_mode = RENDER_GL;
        }

        handle_macros(keyb, &pressed);
    }

    return pressed;
}

int main(int argc, char* argv[]) {
    const char* filename;

    if (argc < 2) {
        filename = "disks/sotn.us.bin";
    } else if (argc == 2 && !strcmp(argv[1], "test")) {
#ifdef WANT_LIBSND_LLE
        run_tests();
#endif
    } else {
        filename = argv[1];
    }
    OpenCd(filename);

    if (InitGame()) {
        MainGame();
    }
    ResetGame();
}
