#include "np3.h"

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    self->facingLeft = self[-1].facingLeft;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
REDACTED
REDACTED
    if (self[-1].entityId != 0x44) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
REDACTED
REDACTED
REDACTED
static s32 D_801D3378;
static s32 D_801D337C;
static s32 D_801D3380;
static s32 D_801D3384;
static s32 D_801D3388;
STATIC_PAD_BSS(104);

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
REDACTED
REDACTED

void func_801CD734() {
    while (PadRead(0))
        func_801CD658();
REDACTED
        func_801CD658();
}

void func_801CD78C(Point32* src, s32 speed, s16 angle, Point32* dst) {
    if (g_CurrentEntity->facingLeft) {
REDACTED
REDACTED
    *dst = *src;
REDACTED
    dst->x -= speed * rsin(angle) * 16;
    dst->y += speed * rcos(angle) * 16;
REDACTED
REDACTED
REDACTED
    s16 angle = self->ext.GH_Props.rotZ;
REDACTED
REDACTED
    if (g_CurrentEntity->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
    src = self->ext.GH_Props.parent;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s16 angle = self->ext.GH_Props.rotZ;
REDACTED
REDACTED
    if (g_CurrentEntity->facingLeft != 0) {
REDACTED
REDACTED
    src = self->ext.GH_Props.parent;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    temp_a0 = ent1->ext.GH_Props.parent;
REDACTED
        temp_a0, temp_a0->ext.GH_Props.unk9E, temp_a0->ext.GH_Props.rotZ, ent1);
    func_801CD78C(
        ent1, ent2->ext.GH_Props.unk9E, ent2->ext.GH_Props.rotZ, ent2);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    temp_s0 = self->ext.GH_Props.parent;
REDACTED
        self, -self->ext.GH_Props.unk9E, self->ext.GH_Props.rotZ, temp_s0);
REDACTED
                  temp_s0->ext.GH_Props.rotZ, arg1);
REDACTED
REDACTED
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
REDACTED
REDACTED
    if (abs(*arg0 - arg1) < arg2) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s16 temp_t0 = arg1 - entity->ext.GH_Props.rotZ;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            temp_a0->ext.GH_Props.rotZ =
                temp_a0->ext.GH_Props.rotZ + temp_a0->ext.GH_Props.unkA6;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            temp_a0->ext.GH_Props.rotZ =
                temp_a0->ext.GH_Props.rotZ + temp_a0->ext.GH_Props.unkA6;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    g_api.CheckCollision(
        entity->posX.i.hi, (s16)(entity->posY.i.hi + collider->unk18), collider,
        0);
    if (collider->effects & 1) {
REDACTED
        if (collider->effects & 0x8000) {
            if (collider->effects & 0x4000) {
                if (g_CurrentEntity->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_CurrentEntity->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    entity->ext.GH_Props.unk88 = var_s0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (g_CurrentEntity->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (func_801CE120(entity, g_CurrentEntity->facingLeft) != 0) {
REDACTED
REDACTED
REDACTED
    if (func_801CE120(entity, g_CurrentEntity->facingLeft ^ 1) != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
