// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

#ifdef VERSION_PSP
extern s32 E_ID(ID_40);
#endif
extern u16 D_us_80181AA8[][2];
extern s32 D_us_80181AC8;

// This seems to be related to the Lesser Demon boss fight somehow, but not the
// Lesser Demon itself.
void func_us_801BB200(Entity* self) {
    s32 i;
    s32 params;
    s32 adjustedY;
    s32 upperParams;
    s32 tilePos;
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018095C);
        params = self->params & 0xFF;
        self->animCurFrame = params + 0xF;
        self->zPriority = 0x69;
        if (self->params & 0x100) {
            self->facingLeft = 1;
        }
        self->ext.et_801BB200.unk84 = 0;
        if (!self->params) {
            newEntity = self + 1;
            for (i = 1; i < 4; i++, newEntity++) {
                CreateEntityFromCurrentEntity(E_ID(ID_40), newEntity);
                newEntity->params = i;
            }
            for (i = 0; i < 4; i++, newEntity++) {
                CreateEntityFromCurrentEntity(E_ID(ID_40), newEntity);
                newEntity->params = i + 0x100;
            }
        }
        self->posY.i.hi = 0x258 - g_Tilemap.scrollY.i.hi;
        if (self->params & 0x100) {
            self->posX.i.hi = 0x2E0 - g_Tilemap.scrollX.i.hi;
        } else {
            self->posX.i.hi = 0x120 - g_Tilemap.scrollX.i.hi;
        }
        break;
    case 1:
        if ((D_us_80181AC8) && (!(self->params & 0xFF))) {
            self->step = 2;
        }
        if (self->ext.et_801BB200.unk84) {
            self->step = 2;
        }
        break;
    case 2:
        self->velocityY = FIX(4.0);
        self->step++;
        /* fallthrough */
    case 3:
        MoveEntity();
        self->velocityY += FIX(0.125);
        params = self->params & 0xFF;
        upperParams = self->params >> 8;
        adjustedY = ((3 - params) * 16) + 0x268 - (g_Tilemap.scrollY.i.hi);
        if (adjustedY < self->posY.i.hi) {
            if (params != 4) {
                newEntity = self + 1;
                newEntity->ext.et_801BB200.unk84 = 1;
            }
            self->posY.i.hi = adjustedY;
            tilePos = 0xBF2;
            if (self->params & 0x100) {
                g_api.PlaySfx(SFX_DOOR_CLOSE_B);
                tilePos = 0xC0D;
            }
            tilePos += ((3 - params) * 0x50);
            g_Tilemap.fg[tilePos] = D_us_80181AA8[7 - params][upperParams];
            self->velocityY = 0;
            self->step++;
        }
        break;
    case 4:
        if (!D_us_80181AC8) {
            self->step++;
        }
        break;
    case 5:
        tilePos = 0xBF2;
        params = self->params & 0xFF;
        upperParams = self->params >> 8;
        if (self->params & 0x100) {
            tilePos = 0xC0D;
        }
        tilePos += ((3 - params) * 0x50);
        g_Tilemap.fg[tilePos] = D_us_80181AA8[3 - params][upperParams];
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 3;
        }
        self->animCurFrame = 0;
        self->step++;
    case 6:
        break;
    }
}
