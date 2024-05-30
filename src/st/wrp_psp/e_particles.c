#include "../wrp/wrp.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_particles", func_psp_0923AD68);

void func_psp_0923B2F0();

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_particles", func_psp_0923B2F0);

extern u16 g_InitializeData0[];
extern u16 D_801810A0[];
extern u32 D_80181110[];
extern s16 D_801810B0[];

extern void (*D_091CF3A8)(int);
extern s32 D_091CF020;
void func_psp_0923AD68(Entity*);
s32 func_8018C160(Entity*, Entity*);

// worse with prototype
// u16 func_8018C1E0(u16 arg0, u16 arg1, u16 arg2);
void EntitySoulStealOrb(Entity* self) {
    u16 angle;
    Primitive* prim;
    s32 primIndex;
    s16* temp_d;
    u16 temp_a;
    Entity* player;

    if (D_091CF020 == 2) {
        D_091CF3A8 = &func_psp_0923B2F0;
        func_psp_0923AD68(self);
        return;
    }
    player = &PLAYER;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_InitializeData0);
            prim = &g_PrimBuf[primIndex];
            prim->drawMode = DRAW_HIDE;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->animSet = ANIMSET_DRA(0);
            angle = func_8018C160(self, &PLAYER);
            temp_a = 0;
            if (self->posY.i.hi > 112) {
                temp_a = 1;
            }
            if (self->posX.i.hi < PLAYER.posX.i.hi) {
                temp_a ^= 1;
            }
            if (temp_a) {
                angle -= D_801810A0[Random() & 7];
            } else {
                angle += D_801810A0[Random() & 7];
            }
            self->ext.soulStealOrb.angle = angle;
            self->ext.soulStealOrb.unk80 = 0x400;
            self->ext.soulStealOrb.unk7E = 0;
            self->hitboxState = 0;
            return;
        }
        DestroyEntity(self);
        break;

    case 1:
        self->ext.soulStealOrb.unk82++;
        if (self->ext.soulStealOrb.unk82 == 16) {
            self->hitboxState = 1;
        }
        if (self->hitFlags) {
            if (!g_Player.unk56) {
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
        // soulStealOrb.angle changed to u16
        angle = func_8018C160(self, &PLAYER);
        self->ext.soulStealOrb.angle = angle = func_8018C1E0(
            self->ext.soulStealOrb.unk7E, self->ext.soulStealOrb.angle, angle);
        UnkEntityFunc0(angle, self->ext.soulStealOrb.unk80);
        MoveEntity(self);
        prim = &g_PrimBuf[self->primIndex];
        AnimateEntity(&D_80181110, self);
        prim->tpage = 0x18;
        prim->clut = 0x194;
        angle = self->animCurFrame;
        angle = (angle - 1) * 8;
        temp_d = &D_801810B0[angle];
        prim->x0 = prim->x2 = self->posX.i.hi + *(temp_d++);
        prim->y0 = prim->y1 = self->posY.i.hi + *(temp_d++);
        prim->x1 = prim->x3 = prim->x0 + *(temp_d++);
        prim->y2 = prim->y3 = prim->y0 + *(temp_d++);
        prim->u0 = prim->u2 = *(temp_d++);
        prim->v0 = prim->v1 = *(temp_d++);
        prim->u1 = prim->u3 = *(temp_d++);
        prim->v2 = prim->v3 = *temp_d;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_DEFAULT;
        break;
    }
}

#include "../entity_enemy_blood.h"
