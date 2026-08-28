// SPDX-License-Identifier: AGPL-3.0-or-later
void func_us_80195AD8(void) {
    Entity* target;
    Entity* entities;
    s32 xDistance;
    s32 screenX;
    u32 status;
    s32 tempY;
    s32 choice;

    entities = g_Entities;

    if (g_CurrentEntity->ext.GH_Props.unk84 == 1) {
        target = g_CurrentEntity + 14;
    } else {
        target = g_CurrentEntity + 17;
    }

    xDistance = target->posX.i.hi - entities->posX.i.hi;
    if (g_CurrentEntity->facingLeft) {
        xDistance = -xDistance;
    }

    screenX = g_CurrentEntity->posX.i.hi + g_Tilemap.scrollX.i.hi;
    if (g_CurrentEntity->facingLeft) {
        screenX = 0x200 - screenX;
    }

    if (xDistance < -0x30) {
        func_801CE1E8(0xB);
        if (screenX < 0x140 && !(Random() & 3)) {
            func_801CE1E8(7);
        }
        if (!(Random() & 7)) {
            func_801CE1E8(0xC);
        }
        return;
    }

    choice = 5;
    if (screenX < 0xC0) {
        func_801CE1E8(7);
        return;
    }
    if (screenX > 0x1C0) {
        func_801CE1E8(5);
        return;
    }

    if (screenX < 0x180 && xDistance < 0x80) {
        choice = 7;
    }
    if (screenX > 0x100 && xDistance > 0xC0) {
        choice = 5;
    }

    status = g_Player.status;
    if (status & 3) {
        Entity* currentData = g_CurrentEntity + 3;

        xDistance = currentData->posX.i.hi - entities->posX.i.hi;
        tempY = currentData->posY.i.hi - entities->posY.i.hi;
        if (g_CurrentEntity->facingLeft) {
            xDistance = -xDistance;
        }

        if ((u32)xDistance < 0x70U && abs(tempY) < 0x70 && (status & 1)) {
            choice = 9;
        } else {
            choice = 0x16;
        }
        if (!(Random() & 7)) {
            choice = 0xC;
        }
    } else if (status & 0x2000) {
        if (entities->velocityY > 0) {
            choice = 0x16;
        } else {
            choice = 0xC;
        }
    } else {
        tempY = entities->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (tempY < 0x100) {
            if (Random() & 1) {
                choice = 0x16;
            } else {
                choice = 0xC;
            }
        } else {
            if (screenX > 0x100) {
                choice = 0xE;
            }
            if (xDistance < 0x70) {
                choice = 0x12;
            }
            if (xDistance < 0x40) {
                choice = 0x1A;
            }
            if (!(Random() & 3)) {
                choice = 0xC;
            }
        }
    }

    if (!(Random() & 0xF)) {
        choice = 5;
    }

    if (g_CurrentEntity->step == 5 || g_CurrentEntity->step == 7) {
        if (choice != g_CurrentEntity->step) {
            func_801CE1E8(choice);
        }
    } else {
        func_801CE1E8(choice);
    }
}
