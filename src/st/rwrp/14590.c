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

void func_801951F0(Primitive* arg0) {
    SVECTOR sp10; // FAKE, not really an svector
    SVECTOR stackpad;
    SVECTOR sp20;
    VECTOR trans1;
    SVECTOR sp38;
    SVECTOR sp40;
    SVECTOR sp48;
    SVECTOR sp50;
    MATRIX m;
    SVECTOR rot;
    u8 temp_v1_2;

    rot = D_80188DE8;
    if (arg0->p3 & 8) {
        // Fake logic here, sp10 is not an SVECTOR but it matches.
        // tried using an f32 but couldn't get it to work.
        sp10.vy = arg0->next->x1;
        sp10.vx = arg0->next->y1;
        LOW(sp10.vx) += LOW(arg0->next->u0);
        arg0->next->x1 = sp10.vy;
        arg0->next->y1 = sp10.vx;
        LOW(arg0->next->x0) += LOW(arg0->next->r1);
    }
    temp_v1_2 = arg0->next->b3;
    LOH(arg0->r0) = LOH(arg0->r1) = LOH(arg0->r2) = LOH(arg0->r3) =
        temp_v1_2 | (temp_v1_2 << 8);
    arg0->b0 = arg0->b1 = arg0->b2 = arg0->b3 = temp_v1_2;
    trans1.vx = 0;
    trans1.vy = 0;
    trans1.vz = 0x400 - LOH(arg0->next->u1);
    RotMatrix(&rot, &m);
    if (arg0->p3 & 0x20) {
        sp20.vx = arg0->next->x3;
        sp20.vy = arg0->next->y3;
        RotMatrixX(sp20.vx, &m);
        RotMatrixY(sp20.vy, &m);
    }
    sp20.vz = arg0->next->tpage;
    RotMatrixZ(sp20.vz, &m);
    TransMatrix(&m, &trans1);
    if (arg0->p3 & 0x10) {
        trans1.vx = (s32)arg0->next->x2;
        trans1.vy = (s32)arg0->next->y2;
        trans1.vz = 0x1000;
        ScaleMatrix(&m, &trans1);
    }
    SetRotMatrix(&m);
    SetTransMatrix(&m);
    SetGeomScreen(0x400);
    SetGeomOffset(arg0->next->x1, arg0->next->y0);
    sp38.vx = -LOH(arg0->next->r2) / 2;
    sp38.vy = -LOH(arg0->next->b2) / 2;
    sp38.vz = 0;
    sp40.vx = LOH(arg0->next->r2) / 2;
    sp40.vy = -LOH(arg0->next->b2) / 2;
    sp40.vz = 0;
    sp48.vx = -LOH(arg0->next->r2) / 2;
    sp48.vy = LOH(arg0->next->b2) / 2;
    sp48.vz = 0;
    sp50.vx = LOH(arg0->next->r2) / 2;
    sp50.vy = LOH(arg0->next->b2) / 2;
    sp50.vz = 0;
    gte_ldv0(&sp38);
    gte_rtps();
    gte_stsxy(&arg0->x0);
    gte_ldv0(&sp40);
    gte_rtps();
    gte_stsxy(&arg0->x1);
    gte_ldv0(&sp48);
    gte_rtps();
    gte_stsxy(&arg0->x2);
    gte_ldv0(&sp50);
    gte_rtps();
    gte_stsxy(&arg0->x3);
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/14590", func_801955D8);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/14590", func_80195728);

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
