#include "rwrp.h"

// The white flying orbs of energy that Alucard summons as part of the Soul
// Steal spell
void EntitySoulStealOrb(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    u16 *temp_d, temp_e;
    s32 temp_a, temp_b;
    u16 angle;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_InitializeData0);
        g_PrimBuf[primIndex].blendMode = BLEND_VISIBLE;
        self->primIndex = primIndex;
        self->animSet = ANIMSET_DRA(0);
        self->flags |= FLAG_HAS_PRIMS;
        angle = func_8018E0E0(self, &PLAYER);
        temp_a = self->posY.i.hi < 113;
        temp_b = temp_a ^ 1;
        if (self->posX.i.hi < PLAYER.posX.i.hi) {
            temp_b = temp_a;
        }
        if (temp_b & 0xFFFF) {
            self->ext.soulStealOrb.angle = angle - D_801810A0[Random() & 7];
        } else {
            angle += D_801810A0[Random() & 7];
            self->ext.soulStealOrb.angle = angle;
        }
        self->ext.soulStealOrb.unk80 = 0x400;
        self->ext.soulStealOrb.unk7E = 0;
        self->hitboxState = 0;
        break;

    case 1:
        self->ext.soulStealOrb.unk82++;
        if (self->ext.soulStealOrb.unk82 == 16) {
            self->hitboxState = 1;
        }
        if (self->hitFlags != 0) {
            if (g_Player.unk56 == 0) {
                g_Player.unk56 = 1;
                g_Player.unk58 = 8;
            }
            DestroyEntity(self);
            return;
        }
        if (self->rotX < 0x100) {
            self->rotX = self->rotY += 0x10;
        }
        if (self->ext.soulStealOrb.unk7E < 0x200) {
            self->ext.soulStealOrb.unk7E += 2;
        }
        if (self->ext.soulStealOrb.unk80 < 0x800) {
            self->ext.soulStealOrb.unk80 += 4;
        }
        self->ext.soulStealOrb.angle = func_8018E160(
            self->ext.soulStealOrb.unk7E, (u16)self->ext.soulStealOrb.angle,
            0xffff & func_8018E0E0(self, &PLAYER));
        UnkEntityFunc0(self->ext.soulStealOrb.angle & 0xFFFF,
                       self->ext.soulStealOrb.unk80);
        MoveEntity(self); // argument pass necessary to match
        prim = &g_PrimBuf[self->primIndex];
        func_8018D6B0(&D_80181110, self);
        angle = (float)(u32)self; // !FAKE
        prim->tpage = 0x18;
        prim->clut = 0x194;
        temp_d = &D_801810B0[(u16)((8 * (u16)self->animCurFrame) - 8)];
        prim->x0 = prim->x2 = self->posX.i.hi + *(temp_d++);
        prim->y0 = prim->y1 = self->posY.i.hi + *(temp_d++);
        prim->x1 = prim->x3 = prim->x0 + *(temp_d++);
        prim->y2 = prim->y3 = prim->y0 + *(temp_d++);
        prim->u0 = prim->u2 = *(temp_d++);
        prim->v0 = prim->v1 = *(temp_d++);
        prim->u1 = prim->u3 = *(temp_d++);
        prim->v2 = prim->v3 = *(temp_d++);
        prim->priority = self->zPriority;
        prim->blendMode = 0;
        break;
    }
}

#include "../entity_enemy_blood.h"

void func_80194DD4(Entity* entity) {
    ObjInit2* objInit = &D_80181134[entity->params];

    if (entity->step == 0) {
        InitializeEntity(D_80180494);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->blendMode = objInit->blendMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotZ = 0x800;
            entity->drawFlags = (u8)(entity->drawFlags | FLAG_DRAW_ROTZ);
        }
    }
    func_8018D6B0(objInit->unk10, entity);
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/14590", BottomCornerText);

#include "../unk_prim_helper.h"

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/14590", func_801955D8);

#include "../find_first_unk_prim.h"

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/14590", func_80195758);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/14590", func_801957D4);

void func_8019585C(Primitive* prim) {
    prim->p1 = 0;
    prim->p2 = 0;
    prim->p3 = 0;
    prim->next->x1 = 0;
    prim->next->y1 = 0;
    prim->next->y0 = 0;
    prim->next->x0 = 0;
    prim->next->clut = 0;
    *(u16*)&prim->next->u0 = 0;
    *(u16*)&prim->next->b1 = 0;
    *(u16*)&prim->next->r1 = 0;
    *(u16*)&prim->next->u1 = 0;
    prim->next->tpage = 0;
    *(u16*)&prim->next->r2 = 0;
    *(u16*)&prim->next->b2 = 0;
    prim->next->u2 = 0;
    prim->next->v2 = 0;
    prim->next->r3 = 0;
    prim->next->b3 = 0;
    prim->next->x2 = 0;
    prim->next->y2 = 0;
}

void func_8019593C(Primitive* prim) {
    func_8019585C(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = 2;
    prim->next->blendMode = 0xA;
}

#include "../unk_poly_func_0.h"

#include "../unk_loop_func.h"
