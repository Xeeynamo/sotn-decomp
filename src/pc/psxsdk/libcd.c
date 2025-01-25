#include <common.h>
#include <psxsdk/libcd.h>
#include <log.h>

#include <inttypes.h>
#include "cdc.h"
#include <stdio.h>

extern FILE* cd_fp;
bool reading = false;
#define SECTOR_SIZE 2352
int current_file = 0;
int current_channel = 0;

int CdReading() { return reading; }

long CdReadyCallback(void (*func)(void)) {
    NOT_IMPLEMENTED;
    return func;
}

char* CdSyncModeToStr(int mode) {
    switch (mode) {
    case CdlNop:
        return "CdlNop";
    case CdlSetloc:
        return "CdlSetloc";
    case CdlPlay:
        return "CdlPlay";
    case CdlForward:
        return "CdlForward";
    case CdlBackward:
        return "CdlBackward";
    case CdlReadN:
        return "CdlReadN";
    case CdlSetfilter:
        return "CdlSetfilter";
    case CdlSetmode:
        return "CdlSetmode";
    case CdlGetTD:
        return "CdlGetTD";
    default:
        break;
    }

    return "";
}

#define DECODE_BCD(x) (((x) >> 4) * 10 + ((x) & 0xF))

int CdPosToInt(CdlLOC* p) {
    return (75 * (60 * DECODE_BCD(p->minute) + DECODE_BCD(p->second))) +
           DECODE_BCD(p->sector) - 150;
}

int CdControl(u_char com, u_char* param, u_char* result) {
    DEBUGF("com %d %s", com, CdSyncModeToStr(com));
    CdlLOC* pos;

    if (!cd_fp) {
        WARNF("Cd not open.\n");
        return 1;
    }

    switch (com) {
    case CdlSetloc:
        pos = (CdlLOC*)param;
        fseek(cd_fp, CdPosToInt(pos) * SECTOR_SIZE, SEEK_SET);
        break;
    case CdlReadN:
        reading = true;
        break;
    case CdlSetfilter:
        current_file = param[0];
        current_channel = param[1];
        break;
    }
    return 1;
}

int CdSync(int mode, u_char* result) {
    DEBUGF("mode %0d %s", mode, CdSyncModeToStr(mode));
    return CdlComplete;
}

int CdMix(CdlATV* vol) {
    NOT_IMPLEMENTED;
    return 0;
}

void ExecCd() {
    if (reading) {
        uint8_t sector[SECTOR_SIZE];
        fread(sector, sizeof(uint8_t), SECTOR_SIZE, cd_fp);
        XA_ProcessSector(sector, &AudioBuffer);
    }
}
