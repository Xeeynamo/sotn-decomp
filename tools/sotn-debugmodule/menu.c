#include "debugmode.h"

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

    if (g_Timer & 0x20) {
        blinkValue = g_Timer & 0x1F;
    } else {
        blinkValue = 0x1F - (g_Timer & 0x1F);
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

int DbgGetMenuItemCount(DbgMenuCtrl* ctrl) {
    int i;

    for (i = 0; ctrl->items[i].action != NULL; i++) {
    }
    return i;
}

void DbgMenuCtrlInit(DbgMenuCtrl* ctrl) {
    DbgMenuItem* item;
    int i;

    ctrl->nItems = DbgGetMenuItemCount(ctrl);
    for (i = 0; i < ctrl->nItems; i++) {
        item = &ctrl->items[i];
        if (item->param < item->min) {
            item->param = item->min;
        } else if (item->param >= item->max) {
            item->param = item->max - 1;
        }
    }
    ctrl->option = 0;
}

void DbgMenuNavigate(DbgMenuCtrl* ctrl) {
    DbgMenuItem* item;
    int prevParam;

    if (!ctrl->isInit) {
        DbgMenuCtrlInit(ctrl);
        ctrl->isInit = true;
    }

    DbgDrawMenuRect(4, 44, ctrl->menuWidth + 10, 8 + ctrl->nItems * 8);
    DbgDrawCursor(9, 48 + ctrl->option * 8, ctrl->menuWidth, 8);

    item = &ctrl->items[ctrl->option];
    prevParam = item->param;
    if (g_pads[0].tapped & PAD_L1) {
        item->param -= ctrl->pageScroll;
    }
    if (g_pads[0].tapped & PAD_R1) {
        item->param += ctrl->pageScroll;
    }
    if (g_pads[0].repeat & PAD_LEFT) {
        item->param--;
    }
    if (g_pads[0].repeat & PAD_RIGHT) {
        item->param++;
    }
    if (item->param < item->min) {
        item->param = item->max;
    } else if (item->param > item->max) {
        item->param = item->min;
    }

    switch (item->kind) {
    case DbgMenu_ActionOnInput:
        if (g_pads[0].tapped & PAD_CROSS && item->action) {
            item->action(item->param);
        }
        break;
    case DbgMenu_ActionOnChange:
        if (item->param != prevParam) {
            item->action(item->param);
        }
        break;
    case DbgMenu_ActionOnFrame:
        item->action(item->param);
        break;
    }

    if (g_pads[0].tapped & PAD_UP) {
        ctrl->option--;
        if (ctrl->option < 0) {
            ctrl->option = ctrl->nItems - 1;
        }
        PLAY_MENU_SOUND();
    }
    if (g_pads[0].tapped & PAD_DOWN) {
        ctrl->option++;
        if (ctrl->option >= ctrl->nItems) {
            ctrl->option = 0;
        }
        PLAY_MENU_SOUND();
    }
}

Lba* DbgGetStageLba(int stageId) {
    Lba* lba = 0x800A3C40;
    return &lba[stageId];
}
