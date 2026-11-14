// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo1.h"

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", EntityBreakable);

typedef struct {
    s16 eArrayOffset;
    s16 eArrayParentOffset;
    u16 length;
    u16 unused;
    u16 zOffset;
    u16 unkAC;
} BeezelbubPartsInit;

extern s32 D_us_80180630;
extern s32 D_us_80180634;
extern BeezelbubPartsInit D_us_8018063C[];
extern s16 D_us_801806F0[];
extern s16 D_us_8018070C[];
extern unkStr_801CDD80 D_us_80180770[];
extern unkStr_801CDD80 D_us_801807D0[];
extern AnimateEntityFrame D_us_80180840[];
extern s8 D_us_8018088C[][4];
extern u8 D_us_801808D0[];
extern EInit g_EInitBeezelbub;
extern s32 g_BossMgrState;

void func_801CE1E8(s32 step);
void polarPlacePartsList(s16* offsets);
void polarPlacePartsWithAngvel(s16* entOffsets);
void func_801CDF1C(s16 entIndices[], unkStr_801CDD80* arg1, s32 arg2);
void CreateDeathFlames(void);

void func_us_801923A8(Entity* self) {
    Entity* ent;
    Entity* part;
    BeezelbubPartsInit* parts;
    s16* ptr;
    s8* hitbox;
    s32 i;
    s32 count;
    s32 y;
    Collider col;

    FntPrint("boss_life %x\n", D_us_80180630);
    if ((self->flags & FLAG_DEAD) && self->step != 4) {
        func_801CE1E8(4);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBeezelbub);
        self->animCurFrame = 0x14;
        self->ext.beezelbub.hitPoints = self->hitPoints;
        D_us_80180630 = self->hitPoints;
        D_us_80180634 = 0;
        hitbox = D_us_8018088C[0];
        hitbox += D_us_801808D0[self->animCurFrame] * 4;
        self->hitboxOffX = hitbox[0];
        self->hitboxOffY = hitbox[1];
        self->hitboxWidth = hitbox[2];
        self->hitboxHeight = hitbox[3];
        parts = D_us_8018063C;
        part = self;
        for (i = 0; parts->eArrayOffset; parts++, i++) {
            ent = self + parts->eArrayOffset;
            CreateEntityFromCurrentEntity(E_ID(UNK_17), ent);
            ent->ext.GH_Props.length = parts->length;
            ent->ext.GH_Props.parent = self + parts->eArrayParentOffset;
            ent->ext.GH_Props.unkAC = parts->unkAC;
            ent->params = i;
            ent->zPriority = self->zPriority + parts->zOffset;
            ent->nextPart = part;
            part = ent;
        }
        self->nextPart = part;
        ent = self + 24;
        CreateEntityFromCurrentEntity(E_ID(UNK_18), ent);
        ent->ext.GH_Props.parent = self;
        func_801CE1E8(1);
        // fallthrough
    case 1:
        polarPlacePartsList(D_us_801806F0);
        if (g_BossMgrState & BOSS_MGR_FIGHT_ON) {
            func_801CE1E8(2);
        }
        break;
    case 2:
    case 3:
        if (!self->ext.beezelbub.timer) {
            g_api.PlaySfx(SFX_BEELZEBUB_FLY_BUZZ);
            self->ext.beezelbub.timer = 0x180;
            count = D_us_80180634 + 2;
            for (i = 0; i < count; i++) {
                ent = AllocEntity(&g_Entities[128], &g_Entities[152]);
                if (ent != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_19), ent);
                    ent->params = i & 1;
                    ent->rotate = (ROT(360) / count) * i;
                    ent->ext.GH_Props.parent = self;
                    ent->posY.i.hi = (i / 2) << 6;
                    if (i & 1) {
                        ent->posX.i.hi = self->posX.i.hi + 0xC0;
                    } else {
                        ent->posX.i.hi = self->posX.i.hi - 0xC0;
                    }
                    ent->zPriority = self->zPriority;
                }
            }
        }
        self->ext.beezelbub.timer--;
        ptr = D_us_8018070C;
        switch (self->step) {
        case 2:
            AnimateEntity(D_us_80180840, self);
            func_801CDF1C(ptr, D_us_801807D0, 0);
            polarPlacePartsWithAngvel(ptr);
            polarPlacePartsList(D_us_801806F0);
            if (self->hitFlags & 3) {
                g_api.PlaySfx(SFX_BEELZEBUB_PAIN);
                func_801CE1E8(3);
            }
            break;
        case 3:
            func_801CDF1C(ptr, D_us_80180770, 0);
            polarPlacePartsWithAngvel(ptr);
            polarPlacePartsList(D_us_801806F0);
            if (!self->ext.beezelbub.unkB4[0] &&
                !self->ext.beezelbub.unkB0[0]) {
                func_801CE1E8(2);
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            D_us_80180630 = -1;
            g_BossMgrState |= BOSS_MGR_DEFEAT;
            self->hitboxState = 0;
            self->drawFlags |= ENTITY_ROTATE;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.015625);
            self->rotate += 1;
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_EXPLODE_A);
            }
            if (!(g_Timer & 3)) {
                ent = AllocEntity(&g_Entities[80], &g_Entities[248]);
                if (ent != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_1D), self, ent);
                    ent->posY.i.hi -= Random() & 0xF;
                    ent->posX.i.hi -= 0x20 - (Random() & 0x3F);
                    ent->zPriority = self->zPriority + 1;
                }
                CreateDeathFlames();
            }
            y = self->posY.i.hi + 0x18 + g_Tilemap.scrollY.i.hi;
            if (y > 0x1C0) {
                self->ext.beezelbub.timer = 0x80;
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
                self->step_s++;
            }
            break;
        case 2:
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_EXPLODE_A);
                for (i = 0; i < 12; i++) {
                    ent = AllocEntity(&g_Entities[80], &g_Entities[248]);
                    if (ent != NULL) {
                        CreateEntityFromEntity(E_ID(UNK_1D), self, ent);
                        ent->rotate = ((Random() & 0x7F) << 4) - ROT(90);
                        ent->zPriority = self->zPriority + 1;
                        ent->params = 3;
                    }
                }
            }
            if (!--self->ext.beezelbub.timer) {
                self->ext.beezelbub.timer = 0x40;
                self->step_s++;
            }
            break;
        case 3:
            if (self->ext.beezelbub.timer < 0x30) {
                self->animCurFrame = 0;
            }
            ent = AllocEntity(&g_Entities[80], &g_Entities[248]);
            if (ent != NULL) {
                CreateEntityFromEntity(E_ID(UNK_1D), self, ent);
                ent->zPriority = self->zPriority + 1;
                ent->params = 4;
                ent->posY.i.hi += 0x10;
            }
            if (!--self->ext.beezelbub.timer) {
                self->step_s++;
            }
            break;
        case 4:
            g_BossMgrState |= BOSS_MGR_TERMINATED;
            break;
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
    }

    for (ptr = D_us_801806F0; *ptr; ptr++) {
        ent = self + *ptr;
        ent->ext.GH_Props.unkA8 = 0;
    }
    if (self->flags & FLAG_DEAD) {
        return;
    }
    if (D_us_80180630 < 0) {
        D_us_80180630 = 1;
    }
    if (D_us_80180630 != self->ext.beezelbub.hitPoints && self->step != 3) {
        func_801CE1E8(3);
    }
    count = self->hitPoints - self->ext.beezelbub.hitPoints;
    D_us_80180630 += count;
    self->ext.beezelbub.hitPoints = self->hitPoints = D_us_80180630;
}

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_us_80192C5C);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_us_80192F84);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_us_801936FC);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_us_80193C2C);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_us_80193E24);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_us_80194108);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_us_8019ED80_from_rbo2);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", polarPlacePartsWithAngvel);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_801CDD00);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_801CDD80);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_801CDF1C);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_801CE1E8);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_801CE228);

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", polarPlacePartsList);

void CreateDeathFlames(void) {
    Entity* entity;
    s32 i;
    s32 style;
    s16 angle;

    style = Random() & 3;
    angle = ((Random() & 0xF) << 8) - ROT(180);
    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID(UNK_1D), g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.deathFlames.unk89 = 6 - i;
            entity->ext.deathFlames.angle = angle;
            entity->ext.deathFlames.unk88 = style;
            entity->zPriority = g_CurrentEntity->zPriority + 1;
        }
    }
}

INCLUDE_ASM("boss/rbo1/nonmatchings/unk_12274", func_us_801947E4);
