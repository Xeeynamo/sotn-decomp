#include <game.h>

int g_OtIdx;

POLY_G4* GetNextPolyG4() {
    POLY_G4* poly;

    if (g_GpuUsage.g4 >= LEN(g_CurrentBuffer->polyG4)) {
        return NULL;
    }
    if (g_OtIdx >= LEN(g_CurrentBuffer->ot)) {
        return NULL;
    }

    poly = &g_CurrentBuffer->polyG4[g_GpuUsage.g4++];
    poly->code &= 0xFC;
    AddPrim(&g_CurrentBuffer->ot[g_OtIdx++], poly);
    return poly;
}

void DbgBeginDrawMenu(void) { g_OtIdx = 0x1F0; }

void DbgEndDrawMenu(void) {}

void DbgDrawMenuRect(int x, int y, int w, int h) {
    POLY_G4* poly;

    // Draw border
    if (!(poly = GetNextPolyG4())) {
        return;
    }
    poly->x2 = poly->x0 = x;
    poly->y1 = poly->y0 = y;
    poly->x3 = poly->x1 = x + w;
    poly->y3 = poly->y2 = y + h;
    poly->r0 = poly->r1 = poly->r2 = poly->r3 = 255;
    poly->g0 = poly->g1 = poly->g2 = poly->g3 = 255;
    poly->b0 = poly->b1 = poly->b2 = poly->b3 = 255;
    AddPrim(&g_CurrentBuffer->ot[g_OtIdx++], poly);

    // Draw background
    if (!(poly = GetNextPolyG4())) {
        return;
    }
    poly->x2 = poly->x0 = x + 1;
    poly->y1 = poly->y0 = y + 1;
    poly->x3 = poly->x1 = x + w - 1;
    poly->y3 = poly->y2 = y + h - 1;
    poly->r0 = poly->r1 = poly->r2 = poly->r3 = 0;
    poly->g0 = poly->g1 = poly->g2 = poly->g3 = 0;
    poly->b0 = 176;
    poly->b1 = 128;
    poly->b2 = 80;
    poly->b3 = 32;
}

void DbgDrawCursor(int x, int y, int w, int h) {
    POLY_G4* poly;
    u8 blinkValue;

    if (g_blinkTimer & 0x20) {
        blinkValue = g_blinkTimer & 0x1F;
    } else {
        blinkValue = 0x1F - (g_blinkTimer & 0x1F);
    }
    blinkValue *= 4;
    blinkValue -= 0x80;

    if (!(poly = GetNextPolyG4())) {
        return;
    }
    poly->x2 = poly->x0 = x;
    poly->y1 = poly->y0 = y;
    poly->x3 = poly->x1 = x + w;
    poly->y3 = poly->y2 = y + h;
    poly->r0 = poly->r1 = poly->r2 = poly->r3 = blinkValue - 0x20;
    poly->g0 = poly->g1 = poly->g2 = poly->g3 = 0;
    poly->b0 = poly->b1 = poly->b2 = poly->b3 = 0;
}

Lba* DbgGetStageLba(int stageId) {
    Lba* lba = 0x800A3C40;
    return &lba[stageId];
}
