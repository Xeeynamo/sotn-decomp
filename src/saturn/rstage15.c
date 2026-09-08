// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "rstage15.h"

#include "rstage15.h"

INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DC040, func_060DC040);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DC1A8, func_060DC1A8);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DC2A4, func_060DC2A4);
void func_060DC3A4(Entity* self) {
    SpriteObject* sprite;
    s32 frameOffset;

    if (self->step == 0) {
        TekiInit(self, 5);
        self->step++;
        sprite = CreateSpriteObject(
            g_RStage15SpriteBank16.allocationIndex,
            g_RStage15SpriteBank16.flags, g_RStage15SpriteBank16.images, 1);
        self->unk0 = sprite;
        self->animCurFrame = 0x2A;
        frameOffset = 0x2A * sizeof(SaturnSpriteFrameHeader*);
        func_0600AFA8(
            sprite,
            *(SaturnSpriteFrameHeader**)((u8*)g_RStage15SpriteBank16Frames +
                                         frameOffset));
        sprite->zPriority = 0x6A;
        self->step = 0x100;
        func_06079BB4(self);
    }
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DC434, func_060DC434);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DC580, func_060DC580);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DCA30, func_060DCA30);
void func_060DCC10(s32 unused, s16 amount) {
    g_unkGraphicsStruct.D_80097448 = amount;
    if (amount > 4) {
        g_unkGraphicsStruct.D_8009744C = amount - 4;
    } else {
        g_unkGraphicsStruct.D_8009744C = 0;
    }
    g_unkGraphicsStruct.D_80097450 = amount;
}
void func_060DCC44(s32 poseFlags, s16* height, u16* offsetY) {
    if (poseFlags & 0x27) {
        if (poseFlags & 0x20) {
            *height = 0x14;
            if (poseFlags & 4) {
                *height = 0xA;
            }
            *offsetY = -*height + 0x19;
        } else if (poseFlags & 3) {
            *height = 0xC;
            *offsetY = 0xFFF9;
        } else if (poseFlags & 4) {
            *height = 0x14;
            *offsetY = 5;
        }
    } else {
        *height = 0x28;
        *offsetY = 0xFFF1;
    }
}

INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DCCA4, func_060DCCA4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DCD58, func_060DCD58);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DCF08, func_060DCF08);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DD0A0, func_060DD0A0);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DD488, func_060DD488);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DD60C, func_060DD60C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DD780, func_060DD780);
void func_060DD988(Entity* self) {
    s32 primIndex;

    switch (self->step) {
    case 0:
        TekiInit(self, 3);
        self->step++;
        primIndex = AllocPrimitives(0x8002, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        func_060DDB98(self);
        break;
    case 1:
        MoveEntity(self);
        self->velocityY -= self->ext.glowParticle.gravity;
        break;
    }

    func_060DDA34(self);
    if (self->ext.glowParticle.unk88 <= 0x82) {
        DestroyEntity(self);
    }
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DDA34, func_060DDA34);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DDB98, func_060DDB98);
void func_060DDD10(Entity* self) {
    s32 primIndex;

    switch (self->step) {
    case 0:
        TekiInit(self, 3);
        self->step++;
        primIndex = AllocPrimitives(3, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        func_060DDE68(self);
        break;
    case 1:
        MoveEntity(self);
        self->velocityY -= self->ext.glowParticle.gravity;
        break;
    }

    func_060DDDB8(self);
    if (self->ext.glowParticle.b <= 7U) {
        DestroyEntity(self);
    }
}
void func_060DDDB8(Entity* self) {
    Primitive* prim;
    s16 x;
    s16 y;

    x = self->posX.i.hi;
    y = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x3 = x;
    prim->x1 = prim->x2 = x + 1;
    prim->y0 = prim->y1 = y;
    prim->y2 = prim->y3 = y + 1;
    if (self->ext.glowParticle.b > 7) {
        self->ext.glowParticle.r -= 6;
        self->ext.glowParticle.g -= 6;
        self->ext.glowParticle.b -= 8;
        prim->unk6 =
            ((self->ext.glowParticle.b << 10) +
             (self->ext.glowParticle.g << 5) + self->ext.glowParticle.r) -
            0x8000;
    }
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DDE68, func_060DDE68);
void func_060DDFD4(Entity* self) {
    s32 primIndex;

    if (self->step == 0) {
        TekiInit(self, 3);
        self->step++;
        primIndex = AllocPrimitives(3, 0x21);
        if (primIndex == -1) {
            DestroyEntity(self);
        } else {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            func_060DE144(self);
        }
    } else {
        --self->ext.effectTimer.timer;
        if (self->ext.effectTimer.timer == 0) {
            DestroyEntity(self);
        } else {
            func_060DE064(self);
        }
    }
}
void func_060DE064(Entity* self) {
    Primitive* prim;
    char* base;
    Stage15GouraudState* state;
    s16* topLeftY;
    s16* topRightY;
    s16* bottomLeftY;
    s32 offset;
    u16 shade;
    s16 y;

    prim = &g_PrimBuf[self->primIndex];
    if (prim != NULL) {
        do {
            offset = (u16)prim->unk1C * sizeof(Stage15GouraudState);
            base = (char*)SpGourTbl;
            state = (Stage15GouraudState*)(base + offset);
            prim->unk8--;
            if (prim->unk8 < 0) {
                prim->drawMode |= 8;
            }
            state->posY.i.hi = prim->y0;
            state->posY.val += state->velocityY;
            if (state->velocityY < FIX(-0.5)) {
                if (prim->unkA > 3) {
                    prim->unkA -= 4;
                }
                shade = prim->unkA / 8;
                prim->unk6 =
                    ((shade << 8) << 2) + (shade << 5) + shade - 0x8000;
            } else {
                state->velocityY += FIX(-0.21875);
            }
            topLeftY = &prim->y0;
            topRightY = &prim->y1;
            y = state->posY.i.hi;
            *topLeftY = *topRightY = y;
            bottomLeftY = &prim->y2;
            *bottomLeftY = prim->y3 = y;
            prim = prim->next;
        } while (prim != NULL);
    }
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE144, func_060DE144);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE268, func_060DE268);
void func_060DE40C(Entity* self) {
    switch (self->step) {
    case 0:
        TekiInit(self, 5);
        self->step++;
        self->primIndex = AllocPrimitives(0, 5);
        if (self->primIndex == -1) {
            DestroyEntity(self);
        } else {
            self->flags |= FLAG_HAS_PRIMS;
            func_060DE4CC(self);
            self->ext.et_060DE40C.path = &DAT_060EE52C[self->params * 0x10];
            self->ext.et_060DE40C.spanX = g_Tilemap.hSize * 0x140;
            self->ext.et_060DE40C.spanY = g_Tilemap.vSize << 8;
        }
        return;
    case 1:
        func_060DE560(self);
        return;
    }
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE4CC, func_060DE4CC);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE560, func_060DE560);
void func_060DE654(Entity* self) {
    if (DAT_0605cd70.unk0 == 3) {
        SetVdp2BackgroundColorRgb(6, 0, 5);
    }
    if (self->step == 0) {
        TekiInit(self, 4);
        self->step++;
        SetVdp2BackgroundColorRgb(6, 0, 5);
    }
}

const u16 DAT_060DE6B0[] = {
    0x0415, 0x1010, 0x10FF, 0x0000, 0x0412, 0x1010, 0x10FF, 0x0000,
    0x0411, 0x1010, 0x10FF, 0x0000, 0x0417, 0x1010, 0xFF00, 0x0009,
    0x0414, 0x1010, 0xFF00, 0x0009, 0x0412, 0x1510, 0xFF00, 0x0009,
    0x0411, 0x1010, 0xFF00, 0x0009, 0x0415, 0x10FF, 0x0000, 0x0009,
    0x0412, 0x15FF, 0x0000, 0x0009, 0x0411, 0xFF00,
};
void func_060DE6FC(u16 arg0) {
    Entity* entity;
    Entity* current;
    Collider collider;

    entity = g_CurrentEntity;
    if (entity->velocityY < 0) {
        CheckCollision(
            entity->posX.val, entity->posY.val - FIX(7), &collider, 0);
        if (collider.effects & 5) {
            entity->velocityY = 0;
        }
    }

    CheckCollision(entity->posX.val, entity->posY.val + FIX(8), &collider, 0);
    if (arg0) {
        if (!(collider.effects & 5)) {
            MoveEntity(entity);
            func_06079BE4(entity);
            return;
        }

        entity->velocityX = 0;
        entity->velocityY = 0;
        if (collider.effects & 4) {
            entity->posY.val += FIX(0.125);
        } else {
            entity->posY.val += collider.unk18;
        }
        entity->posY.i.hi++;
        entity->posY.i.lo = 0;
    } else if (!(collider.effects & 5)) {
        MoveEntity(entity);
        current = g_CurrentEntity;

        if (current->velocityY >= 0) {
            current->ext.equipItemDrop.fallSpeed +=
                current->ext.equipItemDrop.gravity;
            current->velocityX = current->ext.equipItemDrop.fallSpeed;
            if (current->velocityX == FIX(1) || current->velocityX == FIX(-1)) {
                current->ext.equipItemDrop.gravity =
                    -current->ext.equipItemDrop.gravity;
            }
        }

        if (current->velocityY < FIX(0.25)) {
            current->velocityY += FIX(0.125);
        }
    }
}
void func_060DE808(u16 cardIndex) {
    Entity* self;
    Entity* player;
    PlayerStatus* status;
    s16 subWeaponId;
    u16 params;

    self = g_CurrentEntity;
    PlaySfx(0x67C);

    status = &g_Status;
    params = status->subWeapon;
    player = g_Entities;
    subWeaponId = DAT_060EE880[cardIndex];
    status->subWeapon = subWeaponId;

    if (params == subWeaponId) {
        params = 1;
        self->unk6D[0] = 0x10;
    } else {
        params = g_RStage15AlucardSubweaponIds[params];
        self->unk6D[0] = 0x60;
    }

    if (params != 0) {
        self->params = params;
        self->posY.i.hi = player->posY.i.hi + 0x0C;
        SetStep(7);
        self->unk0->flags |= 8;
        self->ext.subweaponCard.unk86 = 5;
        self->velocityY = FIX(-2.5);

        if (player->facingLeft != 1) {
            self->velocityX = FIX(-2.5);
            return;
        }
        self->velocityX = FIX(2.5);
    } else {
        DestroyEntity(self);
    }
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE8E4, func_060DE8E4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DF140, func_060DF140);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DFE20, func_060DFE20);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E0160, func_060E0160);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E0774, func_060E0774);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E0DE4, func_060E0DE4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E0E3C, func_060E0E3C);
#include "set_entity_collision_tiles.h"

const u16 DAT_060E1278[] = {0xCCCC, 0xCCCD};
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E127C, func_060E127C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E1950, func_060E1950);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E1AB8, func_060E1AB8);
void func_060E1C20(Entity* self) {
    Entity* entity;

    switch (self->step) {
    case 0:
        TekiInit(self, 2);
        self->step++;
        self->ext.explosionEmitter.parentId =
            self->ext.explosionEmitter.parent->entityId;
        /* fall through */
    case 1:
        if (self->ext.explosionEmitter.timer++ > 4U) {
            entity = AllocEntity(&g_Entities[0xE0], &g_Entities[0x100]);
            if (entity != NULL) {
                CreateEntityFromEntity(2, self, entity);
                entity->entityId = 2;
                entity->pfnUpdate = func_060E1950;
                entity->params = self->params;
            }
            self->ext.explosionEmitter.timer = 0;
        }

        self->posX.i.hi = self->ext.explosionEmitter.parent->posX.i.hi;
        self->posY.i.hi = self->ext.explosionEmitter.parent->posY.i.hi;
        if (self->ext.explosionEmitter.parent->entityId !=
            self->ext.explosionEmitter.parentId) {
            DestroyEntity(self);
        }
        break;
    }
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E1D0C, func_060E1D0C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E1E78, func_060E1E78);
#define SPAWN_DESTRUCT_ANIM_ID 19
#include "spawn_destruct_anim.h"
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E20C8, func_060E20C8);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E21A8, func_060E21A8);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E2494, func_060E2494);
#include "init_solid_prop.h"
void func_060E2A78(void) { DestroyEntity(); }
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E2A90, func_060E2A90);
#include "save_device_probe.h"
u16 func_060E3874(s32 minX, s32 maxX) {
    u16 result;

    g_Player.unk7A = 1;
    if (PLAYER.step != 0 || (result = PLAYER.step_s, result != 1) ||
        PLAYER.posX.i.hi < minX || PLAYER.posX.i.hi > maxX) {
        result = 0;
    }
    return result;
}
void func_060E38B8(void) {
    g_Player.padSim = PAD_UP;
    g_Player.demo_timer = 1;
}
void func_060E38D8(Entity* self) {
    Primitive* prim = self->ext.save.unk10;
    s32 i;

    for (i = 0; i < 9; i++) {
        prim->x3 = 0;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E3904, func_060E3904);
void func_060E3D08(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_060E3D58(arg1, arg3);
    func_060E3F18(arg1, arg2, arg3);
    func_060E4064(arg0, arg1, arg3);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E3D58, func_060E3D58);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E3F18, func_060E3F18);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E4064, func_060E4064);

void func_060E4368(s32 arg0, s32 arg1, s32 arg2) {
    func_060E43A4(arg1, arg2);
    func_060E4474(arg0, arg1, arg2);
}
extern s32 DAT_060485e0[];
extern s32 DAT_060F34D0[];
extern s32 DAT_060F34E0[];
extern MthMatrixTbl DAT_06061DF0;
extern void SetCurrentMatrixBinAngle(s32* pos, s32* angle);
extern void TransformAndProjectPoints(
    s32* src, s32* dst, s32 count, MthMatrixTbl* matrixTbl);

void func_060E43A4(s32 scale, s32 unused) {
    s32* base;
    s32* srcX;
    s32* dstX;
    s32* srcY;
    s32* dstY;
    s32 factor;
    s32 scaledZ;
    s32 i;
    s32 last;

    base = DAT_060485e0;
    srcX = g_RStage15Entity08ModelVertices14[0];
    dstX = base;
    factor = scale << 8;
    i = 0;
    last = 13;
    srcY = srcX + 1;
    dstY = dstX + 1;
    do {
        *dstX = *srcX * factor;
        i++;
        dstY[0] = srcY[0] * factor;
        srcX += 3;
        scaledZ = srcY[1] * factor;
        dstX += 3;
        srcY += 3;
        dstY[1] = scaledZ;
        dstY += 3;
    } while (i <= last);

    SetCurrentMatrixBinAngle(DAT_060F34D0, DAT_060F34E0);

    DAT_06061DF0.current->val[0][0] = DAT_06061DF0.current->val[0][0] * 5 / 4;
    DAT_06061DF0.current->val[0][1] = DAT_06061DF0.current->val[0][1] * 5 / 4;
    DAT_06061DF0.current->val[0][2] = DAT_06061DF0.current->val[0][2] * 5 / 4;

    TransformAndProjectPoints(
        base, (s32*)((char*)base + 0x408), 0xE, &DAT_06061DF0);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E4474, func_060E4474);
void func_060E45E0(Entity* entity) {
    entity->unk0 = CreateSpriteObject(
        g_RStage15SpriteBank22.allocationIndex, g_RStage15SpriteBank22.flags,
        g_RStage15SpriteBank22Images, 3);
    SyncSpriteObjectPosUnchecked(entity, g_RStage15Entity15SpawnOffset);
    entity->step = 1;
}
void func_060E4630(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, DAT_060EF1A8[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E4668, func_060E4668);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E519C, func_060E519C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E540C, func_060E540C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E56F4, func_060E56F4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E6750, func_060E6750);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E6878, func_060E6878);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E76C4, func_060E76C4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E78B4, func_060E78B4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E7AC4, func_060E7AC4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E7C3C, func_060E7C3C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E7E60, func_060E7E60);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E823C, func_060E823C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E854C, func_060E854C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E88A0, func_060E88A0);
void func_060E8A54(Entity* entity) {
    entity->unk0 = CreateSpriteObject(
        g_RStage15SpriteBank25.allocationIndex, g_RStage15SpriteBank25.flags,
        g_RStage15SpriteBank25Images, 2);
    SyncSpriteObjectPosUnchecked(entity, DAT_060F1A26);
    entity->step = 1;
}
void func_060E8AA4(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, DAT_060F2670[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E8ADC, func_060E8ADC);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E8EFC, func_060E8EFC);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E9104, func_060E9104);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E9284, func_060E9284);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E98F0, func_060E98F0);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E9D28, func_060E9D28);
void func_060EA0B0(Entity* entity) {
    entity->unk0 = CreateSpriteObject(
        g_RStage15SpriteBank26.allocationIndex, g_RStage15SpriteBank26.flags,
        g_RStage15SpriteBank26Images, 1);
    SyncSpriteObjectPosUnchecked(entity, DAT_060F288E);
    entity->step = 1;
}
void func_060EA100(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F2B4C[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EA138, func_060EA138);
void func_060EA578(Entity* entity) {
    entity->unk0 = CreateSpriteObject(
        g_RStage15SpriteBank27.allocationIndex, g_RStage15SpriteBank27.flags,
        g_RStage15SpriteBank27Images, 1);
    SyncSpriteObjectPosUnchecked(entity, DAT_060F2C32);
    entity->step = 1;
}
void func_060EA5C8(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F2D68[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EA600, func_060EA600);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EAE6C, func_060EAE6C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EAFF8, func_060EAFF8);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EB150, func_060EB150);
void func_060EB4A4(Entity* entity, s16 step) {
    entity->velocityX = 0;
    entity->velocityY = 0;
    entity->pose = 0;
    entity->poseTimer = 0;
    entity->step = step;
    entity->step_s = 0;
}

const u16 DAT_060EB4CA = 0x0009;
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EB4CC, func_060EB4CC);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EB550, func_060EB550);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EC174, func_060EC174);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EC274, func_060EC274);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EC374, func_060EC374);
