#ifndef DEMO_H
#define DEMO_H

#ifndef DEMO_KEY_PTR
#define DEMO_KEY_PTR 0x801E8000
#endif

#define DEMO_KEY_LEN 3
#define DEMO_MAX_LEN 0x2000

typedef enum {
    Demo_None,
    Demo_PlaybackInit,
    Demo_Recording,
    Demo_End,
    Demo_Playback,
} DemoMode;

extern DemoMode g_DemoMode;

#endif // DEMO_H
