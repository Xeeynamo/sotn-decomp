// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdbool.h>

bool g_IsQuitRequested;   // controls whenever MainGame should quit
bool g_TimedExit = false; // should we exit after some time?
int g_TimeLimit = 0;      // number of frames before exiting
