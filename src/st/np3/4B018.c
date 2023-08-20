#include "np3.h"

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", EntityOwl);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CBF18);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", EntityOwlKnight);

void func_801CD540(Entity* self) {
    s8* hitbox;
    s32 diff;

    if (self->step == 0) {
        InitializeEntity(D_80180B20);
    }

    self->facing = self[-1].facing;
    self->posX.i.hi = self[-1].posX.i.hi;
    self->posY.i.hi = self[-1].posY.i.hi;
    hitbox = D_80182914;
    diff = D_80182935[self[-1].animCurFrame];

    diff -= 4;
    if (diff < 0) {
        diff = 0;
    }

    hitbox += diff * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
    if (self[-1].entityId != 0x44) {
        DestroyEntity(self);
    }
}

void func_801CD620(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180A6C);
    }
}

void func_801CD658(void) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint("a:%x\n", D_801D3378);
    FntPrint("b:%x\n", D_801D337C);
    FntPrint("c:%x\n", D_801D3380);
    FntPrint("d:%x\n", D_801D3384);
    FntPrint("e:%x\n", D_801D3388);
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

void func_801CD734() {
    while (PadRead(0))
        func_801CD658();
    while (!PadRead(0))
        func_801CD658();
}

void func_801CD78C(Entity* src, s32 speed, s16 angle, Entity* dst) {
    if (g_CurrentEntity->facing != 0) {
        angle = -angle;
    }

    //! FAKE:
    (*(Point32*)dst) = (*(Point32*)src);

    (*(Point32*)dst).x -= speed * rsin(angle) * 16;
    (*(Point32*)dst).y += speed * rcos(angle) * 16;
}

void func_801CD83C(Entity* self) {
    s16 angle = self->ext.GH_Props.unk9C;
    Entity* src;

    if (g_CurrentEntity->facing != 0) {
        angle = -angle;
    }

    src = self->ext.GH_Props.unkA0;
    self->posX.val = src->posX.val;
    self->posY.val = src->posY.val;
    self->posX.val -= self->ext.GH_Props.unk9E * rsin(angle) * 16;
    self->posY.val += self->ext.GH_Props.unk9E * rcos(angle) * 16;
    if (self->ext.GH_Props.unkA8 != 0) {
        FntPrint("CAUTION!! WARNING_A AT %x\n", self->animCurFrame);
    }
    self->ext.GH_Props.unkA8 |= 1;
}

void func_801CD91C(Entity* self) {
    s16 angle = self->ext.GH_Props.unk9C;
    Entity* src;

    if (g_CurrentEntity->facing != 0) {
        angle = -angle;
    }
    src = self->ext.GH_Props.unkA0;
    src->posX.val = self->posX.val;
    src->posY.val = self->posY.val;
    src->posX.val -= -self->ext.GH_Props.unk9E * rsin(angle) * 16;
    src->posY.val =
        -self->ext.GH_Props.unk9E * rcos(angle) * 16 + src->posY.val;
    if (self->ext.GH_Props.unkA8 != 0) {
        FntPrint("CAUTION!! WARNING_B AT %x\n", self->animCurFrame);
    }
    self->ext.GH_Props.unkA8 |= 1;
}

void func_801CDA14(Entity* ent1, Entity* ent2) {
    Entity* temp_a0;

    temp_a0 = ent1->ext.GH_Props.unkA0;
    func_801CD78C(temp_a0, temp_a0->ext.GH_Props.unk9E,
                  temp_a0->ext.GH_Props.unk9C, ent1);
    func_801CD78C(
        ent1, ent2->ext.GH_Props.unk9E, ent2->ext.GH_Props.unk9C, ent2);
}

void func_801CDA6C(Entity* self, s32 arg1) {
    Entity* temp_s0;

    temp_s0 = self->ext.GH_Props.unkA0;
    func_801CD78C(
        self, -self->ext.GH_Props.unk9E, self->ext.GH_Props.unk9C, temp_s0);
    func_801CD78C(temp_s0, -temp_s0->ext.GH_Props.unk9E,
                  temp_s0->ext.GH_Props.unk9C, arg1);
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDAC8);

bool func_801CDC80(s16* arg0, s16 arg1, s16 arg2) {
    s32 var_v1 = *arg0 - arg1;
    s32 ret;

    if (ABS(var_v1) < arg2) {
        *arg0 = arg1;
        return true;
    }

    if (arg1 < *arg0) {
        *arg0 = *arg0 - arg2;
    }

    if (*arg0 < arg1) {
        *arg0 = arg2 + *arg0;
    }

    return false;
}

void func_801CDD00(Entity* entity, s16 arg1, s16 arg2) {
    s16 temp_t0 = arg1 - entity->ext.GH_Props.unk9C;

    if (temp_t0 > 0x800) {
        temp_t0 -= 0x1000;
    }

    if (temp_t0 < -0x800) {
        temp_t0 += 0x1000;
    }

    do {
        entity->ext.GH_Props.unkA4 = arg1;
        entity->ext.GH_Props.unkA6 = temp_t0 / arg2;
    } while (0);
}

void func_801CDD80(s16* arg0, Entity* arg1) {
    s16* posY = arg1->posY.val;

    while (*arg0 != 0) {
        if (*arg0 != 0xFF) {
            func_801CDD00(&g_CurrentEntity[*arg0], *posY, arg1->posX.val);
        }
        arg0++;
        posY++;
    }
}

void func_801CDE10(s16* arg0) {
    Entity* temp_a0;

    while (*arg0 != 0) {
        if (*arg0 != 0xFF) {
            temp_a0 = &g_CurrentEntity[*arg0];
            temp_a0->ext.GH_Props.unk9C =
                temp_a0->ext.GH_Props.unk9C + temp_a0->ext.generic.unkA6;
        }
        arg0++;
    }
}

void func_801CDE88(s16* arg0) {
    Entity* temp_a0;

    while (*arg0 != 0) {
        if (*arg0 != 0xFF) {
            temp_a0 = &g_CurrentEntity[*arg0];
            temp_a0->ext.GH_Props.unk9C =
                temp_a0->ext.GH_Props.unk9C + temp_a0->ext.generic.unkA6;
            func_801CD83C(temp_a0);
        }
        arg0++;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDF1C);

void func_801CDFD8(Entity* self, s32 arg1) {
    if (self->ext.et_801CDFD8.unkB4 == 0) {
        func_801CDD00(self, self->ext.et_801CDFD8.unkA4, arg1);
        self->ext.et_801CDFD8.unkB4 = arg1;
    }
    self->ext.et_801CDFD8.unkB4--;
    self->ext.et_801CDFD8.unk9C += self->ext.et_801CDFD8.unkA6;
    func_801CD83C(self);
}

void func_801CE04C(Entity* entity, Collider* collider) {
    s16 var_s0 = 0;

    g_api.CheckCollision(
        entity->posX.i.hi, (s16)(entity->posY.i.hi + collider->unk18), collider,
        0);
    if (collider->effects & 1) {
        var_s0 = 1;
        if (collider->effects & 0x8000) {
            if (collider->effects & 0x4000) {
                if (g_CurrentEntity->facing != 0) {
                    var_s0 = 4;
                } else {
                    var_s0 = 2;
                }
            } else {
                if (g_CurrentEntity->facing != 0) {
                    var_s0 = 2;
                } else {
                    var_s0 = 4;
                }
            }
        }
    }
    entity->ext.generic.unk88.S16.unk0 = var_s0;
}

s32 func_801CE120(Entity* self, s32 facing) {
    Collider collider;
    s32 x = self->posX.i.hi;
    s32 y = self->posY.i.hi + 9;
    s32 ret = 0;

    if (facing != 0) {
        x += 64;
    } else {
        x -= 64;
    }

    g_api.CheckCollision(x, y - 6, &collider, 0);
    if (collider.effects & 1) {
        ret |= 2;
    }

    g_api.CheckCollision(x, y + 6, &collider, 0);
    if (!(collider.effects & 1)) {
        ret |= 4;
    }

    return ret;
}

void func_801CE1E8(s16 step) {
    s32 i;

    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;

    for (i = 0; i < 4; i++) {
        g_CurrentEntity->ext.GH_Props.unkB0[i] = 0;
        g_CurrentEntity->ext.GH_Props.unkB0[i + 2] = 0;
    }
}

void func_801CE228(s16 step) {
    s32 i;

    for (i = 0; i < 4; i++) {
        g_CurrentEntity->ext.GH_Props.unkB0[i] = 0;
        g_CurrentEntity->ext.GH_Props.unkB0[i + 2] = 0;
    }
}

void func_801CE258(s16* arg0) {
    Entity* entity;

    while (*arg0 != 0) {
        entity = &g_CurrentEntity[*arg0];
        if (entity->ext.GH_Props.unkA8 == 0) {
            func_801CD83C(entity);
        }
        arg0++;
    }
}

void func_801CE2CC(s16* arg0) {
    s16* var_s0;

    func_801CD91C(&g_CurrentEntity[arg0[1]]);
    func_801CD91C(&g_CurrentEntity[arg0[0]]);
    func_801CD83C(&g_CurrentEntity[arg0[2]]);
    func_801CD83C(&g_CurrentEntity[arg0[3]]);

    for (arg0 += 4; *arg0 != 0; arg0++) {
        if (*arg0 != 0xFF) {
            func_801CD83C(&g_CurrentEntity[*arg0]);
        }
    }
}

void func_801CE3FC(s16* arg0) {
    s16* var_s0;
    s16 var_v0;
    s32 i;

    for (i = 0, var_s0 = arg0; i < 4; i++) {
        func_801CD83C(&g_CurrentEntity[*var_s0]);
        var_s0++;
    }

    for (arg0 += 4; *arg0 != 0; arg0++) {
        if (*arg0 != 0xFF) {
            func_801CD83C(&g_CurrentEntity[*arg0]);
        }
    }
}

s32 func_801CE4CC(Entity* self) {
    Entity* entity;
    s32 step;
    s32 x;

    if (g_CurrentEntity->ext.et_801CE4CC.unk8E != 0) {
        g_CurrentEntity->ext.et_801CE4CC.unk8E--;
    }

    x = self->posX.i.hi - PLAYER.posX.i.hi;
    if (g_CurrentEntity->facing != 0) {
        x = -x;
    }

    if (x < -16) {
        func_801CE1E8(10);
        return;
    }

    if (g_CurrentEntity->ext.et_801CE4CC.unk84 == 1) {
        entity = g_CurrentEntity + 10;
    } else {
        entity = g_CurrentEntity + 13;
    }

    if (func_801CE120(entity, g_CurrentEntity->facing) != 0) {
        func_801CE1E8(7);
        return;
    }
    if (func_801CE120(entity, g_CurrentEntity->facing ^ 1) != 0) {
        func_801CE1E8(5);
        return;
    }

    if (g_CurrentEntity->step == 8) {
        if (x < 80) {
            step = 5;
        } else {
            step = 8;
        }
    } else {
        if (x < 80) {
            step = 7;
        } else {
            step = 5;
        }
        if (x > 160) {
            step = 8;
        }
    }

    if ((g_CurrentEntity->ext.et_801CE4CC.unk8E == 0) && (x < 96)) {
        g_CurrentEntity->ext.et_801CE4CC.unk8E = 3;
        step = 6;
    }
    if (step != g_CurrentEntity->step) {
        func_801CE1E8(step);
    }
    if (g_CurrentEntity->step == 7) {
        if (step == 5) {
            g_CurrentEntity->ext.et_801CE4CC.unkB0 = 1;
        }
    }
}
