// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

extern u16 D_us_80180F1A[];

void func_us_801C59E0(Entity* self, s16 arg1) {
    Entity* newEntity;

    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (newEntity != NULL) {
        CreateEntityFromCurrentEntity(E_SURFACING_WATER, newEntity);

        if (self->ext.et_surfacingWater.unk90 & 2) {
            newEntity->posY.i.hi = 288 - g_Tilemap.scrollY.i.hi;
        } else {
            newEntity->posY.i.hi = 176 - g_Tilemap.scrollY.i.hi;
        }

        if (self->facingLeft != 0) {
            newEntity->posX.i.hi += arg1;
        } else {
            newEntity->posX.i.hi -= arg1;
        }

        newEntity->params = 0x8000;
        newEntity->params = *D_us_80180F1A << 8 | 0x8000;
        newEntity->ext.et_surfacingWater.unk88 = 0x17;
        newEntity->zPriority = 0x9B;
        self->ext.et_surfacingWater.unk8C = 8;
    }
}

INCLUDE_ASM("st/no4/nonmatchings/e_ferryman", func_us_801C5AD4);

INCLUDE_ASM("st/no4/nonmatchings/e_ferryman", func_us_801C5C7C);

void func_us_801C6CEC(Entity* self) {

    Entity* prev = self - 1;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x1C;
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->zPriority = 0x9A;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
    }
    self->posX.i.hi = prev->posX.i.hi;
    self->rotate = prev->rotate;
    if (self->facingLeft != 0) {
        self->posX.i.hi += 4;
    } else {
        self->posX.i.hi -= 4;
    }
    self->posY.i.hi = prev->posY.i.hi;
}

INCLUDE_ASM("st/no4/nonmatchings/e_ferryman", func_us_801C6DA8);

INCLUDE_ASM("st/no4/nonmatchings/e_ferryman", func_us_801C7204);

INCLUDE_ASM("st/no4/nonmatchings/e_ferryman", func_us_801C726C);

INCLUDE_ASM("st/no4/nonmatchings/e_ferryman", func_us_801C789C);

void func_us_801C7FA4(void) {}

extern u16 D_us_801817E8;

void func_us_801C7FAC(void) {
    s32 i;
    Tilemap* tileMap = &g_Tilemap;
    s16 offset = 0x595;
    u16* var_a2 = &D_us_801817E8;

    for (i = 0; i < 7; i++) {
        *(tileMap->fg + offset) = *var_a2++;
        offset++;
        *(tileMap->fg + offset) = *var_a2++;
        offset = offset + 0xCF;
    }
}

void func_us_801C801C(Entity* self) {
    Entity* newEnt;
    s16 offsetY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        if (g_CastleFlags[BOATMAN_GATE_OPEN]) {
            func_us_801C7FAC();
            DestroyEntity(self);
            return;
        }
        self->animCurFrame = 24;
        return;
    case 1:
        if (g_CastleFlags[BOATMAN_GATE_OPEN]) {
            GetPlayerCollisionWith(self, 16, 56, 3);
            func_us_801C7FAC();
            self->ext.et_surfacingWater.unk80 = 0;
            self->step++;
            return;
        }
        break;
    case 2:
        if (!(self->ext.et_surfacingWater.unk80++ & 15)) {
            PlaySfxPositional(SFX_STONE_MOVE_C);
        }

        self->posY.i.hi--;
        offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

        if (offsetY >= 125) {
            if (self->ext.et_surfacingWater.unk7C) {
                self->ext.et_surfacingWater.unk7C--;
            } else {
                newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEnt != NULL) {
                    CreateEntityFromCurrentEntity(E_SURFACING_WATER, newEnt);
                    newEnt->posY.i.hi = 176 - g_Tilemap.scrollY.i.hi;
                    newEnt->posX.i.hi = (s16)(newEnt->posX.i.hi - 16) +
                                        (self->ext.et_surfacingWater.unk7E * 8);
                    newEnt->params = 0x8000;
                    newEnt->ext.et_surfacingWater.unk88 = 23;
                    newEnt->zPriority = 155;
                }

                self->ext.et_surfacingWater.unk7E++;
                if (self->ext.et_surfacingWater.unk7E >= 5) {
                    self->ext.et_surfacingWater.unk7E = 0;
                }
                self->ext.et_surfacingWater.unk7C = 1;
            }
        }

        GetPlayerCollisionWith(self, 16, 60, 3);

        if (offsetY < 36) {
            DestroyEntity(self);
        }
    }
}

void func_us_801C8248(Entity* self) {
    s32 posX;
    s32 posY;

    if (g_api.TimeAttackController(
            TIMEATTACK_EVENT_SUCCUBUS_DEFEAT, TIMEATTACK_GET_RECORD)) {
        posX = self->posX.val;
        posY = self->posY.val;
        CreateEntityFromCurrentEntity(E_HEART_DROP, self);
        self->params = 10;
        self->posX.val = posX;
        self->posY.val = posY;
    }
}
