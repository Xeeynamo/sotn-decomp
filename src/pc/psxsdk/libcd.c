#include <common.h>
#include <psxsdk/libcd.h>
#include <log.h>

#include <inttypes.h>
#include "cdc.h"
#include <stdio.h>

FILE* cd_fp = NULL;
bool reading = false;
const int sector_size = 2352;
int current_file = 0;
int current_channel = 0;

void OpenCd(char* filename) {
    cd_fp = fopen(filename, "rb");

    if (!cd_fp) {
        DEBUGF("Couldn't open CD.\n");
    }
}

int CdReading() { return reading; }

CdlCB CdReadyCallback(CdlCB func) {
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
    }

    return "";
}

#define DECODE_BCD(x) (((x) >> 4) * 10 + ((x)&0xF))

int CdPosToInt(CdlLOC* p) {
    return (75 * (60 * DECODE_BCD(p->minute) + DECODE_BCD(p->second))) +
           DECODE_BCD(p->sector) - 150;
}

int CdControl(u_char com, u_char* param, u_char* result) {
    DEBUGF("com %d %s", com, CdSyncModeToStr(com));

    if (!cd_fp) {
        DEBUGF("Cd not open.\n");
    }

    switch (com) {
    case CdlSetloc:
        CdlLOC* pos = (CdlLOC*)param;
        fseek(cd_fp, CdPosToInt(pos) * sector_size, SEEK_SET);
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
        uint8_t sector[sector_size];
        fread(sector, sizeof(uint8_t), sector_size, cd_fp);
        XA_ProcessSector(sector, &AudioBuffer);
    }
}
