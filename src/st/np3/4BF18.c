#include "np3.h"

s32 func_801CBF18(void) {
    Primitive* prim;
    s32 primIndex;
    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->animCurFrame = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        // yes this has to be written this way
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.prim = prim;
            for (; prim != NULL; prim = prim->next) {
                prim->tpage = 0x12;
                prim->clut = D_80180B14[3] + 1;
                prim->u0 = 72;
                prim->u1 = 72 + 40;
                prim->u2 = 72;
                prim->u3 = 72 + 40;

                if (g_CurrentEntity->facingLeft) {
                    prim->x0 = g_CurrentEntity->posX.i.hi + 13;
                    prim->x1 = prim->x0 - 40;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                } else {
                    prim->x0 = g_CurrentEntity->posX.i.hi - 13;
                    prim->x1 = prim->x0 + 40;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                }
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                prim->priority = g_CurrentEntity->zPriority;
                prim->drawMode = DRAW_UNK_400 | DRAW_COLORS | DRAW_UNK02;
                prim->p2 = 0;
            }
            prim = g_CurrentEntity->ext.prim;
            prim->v0 = 0x80;
            prim->v1 = prim->v0;
            prim->v2 = prim->v0 + 10;
            prim->v3 = prim->v2;
            prim->y0 = g_CurrentEntity->posY.i.hi - 0x10;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 10;
            prim->y3 = prim->y2;
            prim->p2 = 0;
            prim->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;

            prim->v0 = 138;
            prim->v1 = prim->v0;
            prim->v2 = 138 + 38;
            prim->v3 = prim->v2;
            prim->y0 = g_CurrentEntity->posY.i.hi - 6;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 38;
            prim->y3 = prim->y2;
        } else {
            return 1;
        }
        g_CurrentEntity->step_s++;
        break;
    case 1:
        prim = g_CurrentEntity->ext.prim;
        prim->r0 = prim->g0 = prim->b0 = 32;
        LOW(prim->r1) = LOW(prim->r0);
        prim->r2 = prim->g2 = prim->b2 = 160;
        LOW(prim->r3) = LOW(prim->r2);
        g_CurrentEntity->step_s++;
        break;
    case 2:
        prim = g_CurrentEntity->ext.prim;
        if (g_Timer % 6 == 0) {
            prim->y0++;
            prim->y1 = prim->y0;
        }
        if (g_Timer % 4 == 0) {
            prim->v0++;
            prim->v1 = prim->v0;
            prim->v2++;
            prim->v3 = prim->v2;
            prim->y3++;
            prim->y2 = prim->y3;
            prim->p2++;
            prim = prim->next;
            prim->v0++;
            prim->v1 = prim->v0;
            prim->y0++;
            prim->y1 = prim->y0;
        }
        if (prim->p2 <= 38) {
            break;
        }
        g_CurrentEntity->step_s++;
        break;
    case 3:
        prim = g_CurrentEntity->ext.prim;
        if (PrimDecreaseBrightness(prim, 6) == 0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("st/np3/nonmatchings/4BF18", EntityOwlKnight);

void func_801CD540(Entity* self) {
    s8* hitbox;
    s32 diff;

    if (self->step == 0) {
        InitializeEntity(D_80180B20);
    }

    self->facingLeft = self[-1].facingLeft;
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
        InitializeEntity(g_EInitGeneric);
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

void func_801CD78C(Point32* src, s32 speed, s16 angle, Point32* dst) {
    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }
    *dst = *src;

    dst->x -= speed * rsin(angle) * 16;
    dst->y += speed * rcos(angle) * 16;
}

void func_801CD83C(Entity* self) {
    s16 angle = self->ext.GH_Props.rotZ;
    Entity* src;

    if (g_CurrentEntity->facingLeft != 0) {
        angle = -angle;
    }

    src = self->ext.GH_Props.parent;
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
    s16 angle = self->ext.GH_Props.rotZ;
    Entity* src;

    if (g_CurrentEntity->facingLeft != 0) {
        angle = -angle;
    }
    src = self->ext.GH_Props.parent;
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

    temp_a0 = ent1->ext.GH_Props.parent;
    func_801CD78C(
        temp_a0, temp_a0->ext.GH_Props.unk9E, temp_a0->ext.GH_Props.rotZ, ent1);
    func_801CD78C(
        ent1, ent2->ext.GH_Props.unk9E, ent2->ext.GH_Props.rotZ, ent2);
}

void func_801CDA6C(Entity* self, s32 arg1) {
    Entity* temp_s0;

    temp_s0 = self->ext.GH_Props.parent;
    func_801CD78C(
        self, -self->ext.GH_Props.unk9E, self->ext.GH_Props.rotZ, temp_s0);
    func_801CD78C(temp_s0, -temp_s0->ext.GH_Props.unk9E,
                  temp_s0->ext.GH_Props.rotZ, arg1);
}

void func_801CDAC8(Entity* ent1, Entity* ent2) {
    Point32 sp10;
    s32 ratanX;
    s32 ratanY;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    Point32* parentPos;
    s16 temp_s6;

    parentPos = (Point32*)ent1->ext.GH_Props.parent;
    ratanX = ent2->posX.val - parentPos->x;
    if (g_CurrentEntity->facingLeft) {
        ratanX = -ratanX;
    }
    ratanY = ent2->posY.val - parentPos->y;
    temp_s6 = ratan2(-ratanX, ratanY);
    temp_s4 = ent1->ext.GH_Props.unk9E << 8;
    temp_s3 = ent2->ext.GH_Props.unk9E << 8;
    ratanX >>= 8;
    ratanY >>= 8;
    temp_s2 = SquareRoot0((ratanX * ratanX) + (ratanY * ratanY));
    if (((temp_s4 + temp_s3) << 8) < temp_s2) {
        temp_s2 = ((temp_s4 + temp_s3) << 8);
    }
    temp_s2 = (temp_s2 * temp_s4) / (temp_s4 + temp_s3);
    temp_s3 = (temp_s4 * temp_s4) - (temp_s2 * temp_s2);
    temp_s3 = SquareRoot0(temp_s3);
    temp_s6 += ratan2(temp_s3, temp_s2);
    ent1->ext.GH_Props.unkA4 = temp_s6;
    func_801CD78C(parentPos, ent1->ext.GH_Props.unk9E, temp_s6, &sp10);
    ratanX = ent2->posX.val - sp10.x;
    if (g_CurrentEntity->facingLeft) {
        ratanX = -ratanX;
    }
    ratanY = ent2->posY.val - sp10.y;
    ent2->ext.GH_Props.unkA4 = ratan2(-ratanX, ratanY);
}

bool func_801CDC80(s16* arg0, s16 arg1, s16 arg2) {
    if (abs(*arg0 - arg1) < arg2) {
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
    s16 temp_t0 = arg1 - entity->ext.GH_Props.rotZ;

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
            temp_a0->ext.GH_Props.rotZ =
                temp_a0->ext.GH_Props.rotZ + temp_a0->ext.generic.unkA6;
        }
        arg0++;
    }
}

void func_801CDE88(s16* arg0) {
    Entity* temp_a0;

    while (*arg0 != 0) {
        if (*arg0 != 0xFF) {
            temp_a0 = &g_CurrentEntity[*arg0];
            temp_a0->ext.GH_Props.rotZ =
                temp_a0->ext.GH_Props.rotZ + temp_a0->ext.generic.unkA6;
            func_801CD83C(temp_a0);
        }
        arg0++;
    }
}

void func_801CDF1C(s16 entIndices[], s16 arg1[][4], s32 arg2) {

    arg1 += (u16)g_CurrentEntity->ext.GH_Props.unkB0[arg2];

    if (g_CurrentEntity->ext.GH_Props.unkB0[arg2 + 2] == 0) {
        func_801CDD80(entIndices, arg1);
        *(arg2 + 2 + g_CurrentEntity->ext.GH_Props.unkB0) = arg1[0][0];
    }
    // I don't know why the reverse array indexing is needed, but it is. Darn.
    if (!(--((arg2 + 2)[g_CurrentEntity->ext.GH_Props.unkB0]))) {
        if (arg1[1][0] == 0) {
            g_CurrentEntity->ext.GH_Props.unkB0[arg2] = 0;
        } else {
            ++g_CurrentEntity->ext.GH_Props.unkB0[arg2];
        }
    }
}

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
                if (g_CurrentEntity->facingLeft != 0) {
                    var_s0 = 4;
                } else {
                    var_s0 = 2;
                }
            } else {
                if (g_CurrentEntity->facingLeft != 0) {
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
    if (g_CurrentEntity->facingLeft != 0) {
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

    if (func_801CE120(entity, g_CurrentEntity->facingLeft) != 0) {
        func_801CE1E8(7);
        return;
    }
    if (func_801CE120(entity, g_CurrentEntity->facingLeft ^ 1) != 0) {
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
