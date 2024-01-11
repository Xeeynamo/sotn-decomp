#include <common.h>
#include <stdarg.h>
#include <stdio.h>
#include <log.h>
#include "psxsdk/cdc.h"

bool g_IsQuitRequested; // controls whenever MainGame should quit

FILE* cd_fp = NULL;
void OpenCd(char* filename) {
    cd_fp = fopen(filename, "rb");

    if (!cd_fp) {
        DEBUGF("Couldn't open CD.\n");
    }
}

int CdReading();
void ExecCd();
void MyAudioCallback(void* data, u8* buffer, int length) {
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

int MyFntPrint(const char* fmt, va_list arg) {
    char buf[256];
    vsnprintf(buf, sizeof(buf), fmt, arg);
    INFOF(buf);
}

u_long* MyFntFlush(int id) {
    fflush(stderr);
    return 0;
}
