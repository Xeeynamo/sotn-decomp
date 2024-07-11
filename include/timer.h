#ifndef TIMER_H
#define TIMER_H

extern u32 g_GameTimer; // Increases when unpaused
extern u32 g_Timer; // Increases continuously
extern s32 g_MapCursorTimer;

// mask for g_Timer
#define RENDERFLAGS_NOSHADOW 2

#endif // TIMER_H
