#include "np3.h"

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CB018);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CBF18);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CC2E0);

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CD658);

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CD83C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CD91C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDA14);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDA6C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDAC8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDC80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDD00);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDD80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDE10);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDE88);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDF1C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDFD8);

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


