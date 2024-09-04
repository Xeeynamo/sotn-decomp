REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
// NOTE: There is an nz0/e_bloody_zombie.c which is almost exactly the same as
// this file. Would maybe be smart to try to de-duplicate. Could be marked as
// an Issue for someone to deal with later?

REDACTED
#include "sfx.h"
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
    Primitive* prim;
    s32 primIndex;
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_InitializeEntityData0);
REDACTED
REDACTED
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.bloodSplatter.prim = prim;
        } else {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim = FindFirstUnkPrim2(self->ext.bloodSplatter.prim, 2);
REDACTED
            self->ext.bloodSplatter.prim2 = prim;
            UnkPolyFunc2(prim);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->v0 = 0x30;
REDACTED
            prim->v2 = 0x30;
REDACTED
REDACTED
REDACTED
REDACTED
            LOH(prim->next->r2) = 0x10;
            LOH(prim->next->b2) = 0x10;
            LOW(prim->next->r1) = -0x6000;
REDACTED
            if (self->facingLeft) {
                LOW(prim->next->u0) = 0xA000;
REDACTED
                prim->next->x1 += 4;
REDACTED
                LOW(prim->next->u0) = 0xFFFF6000;
                LOH(prim->next->tpage) = -0x200;
                prim->next->x1 -= 4;
REDACTED
REDACTED
            prim->drawMode = 6;
REDACTED
REDACTED
        prim = FindFirstUnkPrim2(self->ext.bloodSplatter.prim, 2);
REDACTED
            self->ext.bloodSplatter.prim3 = prim;
            UnkPolyFunc2(prim);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->v1 = 0x40;
REDACTED
            prim->v3 = 0x40;

REDACTED
REDACTED
            LOH(prim->next->r2) = 8;
            LOH(prim->next->b2) = 0x10;
REDACTED
            LOW(prim->next->r1) = -0x8000;
            if (self->facingLeft) {
                LOW(prim->next->u0) = 0xC000;
                LOH(prim->next->tpage) = 0x200;
REDACTED
                LOW(prim->next->u0) = 0xFFFF4000;
                LOH(prim->next->tpage) = -0x200;
REDACTED
REDACTED
            prim->drawMode = 6;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim = self->ext.bloodSplatter.prim2;
        UnkPrimHelper(prim);
REDACTED
        if (g_Timer % 2) {
            LOH(prim->next->r2)++;
            LOH(prim->next->b2)++;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        LOW(prim->next->r1) += 0xC00;
REDACTED
        if (self->facingLeft) {
REDACTED
REDACTED
            prim->next->tpage -= 0x18;
REDACTED
REDACTED
        prim->next->b3 -= 2;
        if (UpdateAnimation(&D_8018268C, prim) == 0) {
            UnkPolyFunc0(prim);
REDACTED
REDACTED
        prim = self->ext.bloodSplatter.prim3;
        UnkPrimHelper(prim);
        LOH(prim->next->r2) += 2;
        LOH(prim->next->b2) += 2;
        if (prim->p1 > 3) {
            LOH(prim->next->b2) = 16;
REDACTED
REDACTED
        prim->next->b3 -= 3;
        if (prim->next->b3 > 240) {
            prim->next->b3 = 0;
REDACTED
REDACTED
        if (UpdateAnimation(&D_801826A4, prim) == 0) {
            UnkPolyFunc0(prim);
REDACTED
REDACTED
        if (self->ext.bloodSplatter.unk80++ > 128) {
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
        prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
        UnkPrimHelper(prim);
REDACTED
REDACTED
            UnkPolyFunc0(prim);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s16 primIndex;
    s16 facing;
REDACTED
REDACTED
    if (self->unk44 && self->step & 1) {
        PlaySfxPositional(NA_SE_EN_BLOODY_ZOMBIE_INJURED_SCREAM);
        PlaySfxPositional(NA_SE_EN_BLOODY_ZOMBIE_INJURED);
REDACTED
REDACTED
REDACTED
    if (self->flags & FLAG_DEAD && self->step < 8) {
        PlaySfxPositional(NA_SE_EN_BLOODY_ZOMBIE_DEATH_SCREAM);
        self->hitboxState = 0;
        self->flags &= ~FLAG_UNK_20000000;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->hitboxOffX = 1;
        self->hitboxOffY = 4;
REDACTED
REDACTED
REDACTED
REDACTED
        if (UnkCollisionFunc3(&D_801825D4) & 1) {
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
        UnkCollisionFunc2(D_801825E4);
REDACTED
        if (self->facingLeft == 0) {
            self->velocityX = FIX(-0.375);
REDACTED
            self->velocityX = FIX(0.375);
REDACTED
REDACTED
REDACTED
REDACTED
            self->facingLeft ^= 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        facing = GetSideToPlayer() & 1;
        if (PLAYER.facingLeft == facing && GetDistanceToPlayerX() < 128) {
            self->facingLeft = facing ^ 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
        UnkCollisionFunc2(D_801825E4);
REDACTED
        if (self->facingLeft != 0) {
            self->velocityX = FIX(0.75);
REDACTED
            self->velocityX = FIX(-0.75);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (GetDistanceToPlayerX() < 40) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (animStatus & 0x80 && self->animFrameIdx == 10) {
            PlaySfxPositional(SFX_WEAPON_SWISH_B);
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
                newEntity->facingLeft = GetSideToPlayer() & 1;
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
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x14);
            if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
REDACTED
            self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
            if (!(g_Timer % 8)) {
                PlaySfxPositional(NA_SE_EN_BLOODY_ZOMBIE_HEMORRHAGE);
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
REDACTED
                    newEntity->facingLeft = self->ext.generic.unk84.U8.unk0;
                    if (self->facingLeft != 0) {
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
                PlaySfxPositional(NA_SE_EN_BLOODY_ZOMBIE_HEMORRHAGE);
REDACTED
REDACTED
REDACTED
            if (!(g_Timer & 3)) {
                prim = FindFirstUnkPrim2(*(s32*)&self->ext.generic.unk7C, 2);
                if (prim != NULL) {
                    UnkPolyFunc2(prim);
                    prim->next->r3 = self->ext.generic.unk84.U8.unk0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->flags & FLAG_HAS_PRIMS) {
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
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
                if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            PlaySfxPositional(NA_SE_EN_EXPLOSIVE_DEATH);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->flags & FLAG_HAS_PRIMS) {
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
    if (self->animCurFrame > 10 && self->animCurFrame < 13) {
REDACTED
REDACTED
        *(s16*)&self->hitboxOffX = -12;
        self->hitboxOffY = -12;
REDACTED
REDACTED
REDACTED
        self->hitboxOffX = 1;
        self->hitboxOffY = 4;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_InitializeEntityData0);
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->hitboxState = 0;
REDACTED
            self->flags |= FLAG_HAS_PRIMS;
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
                prim->drawMode |= 0x37;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (CheckColliderOffsets(&D_801826C4, 0)) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityY += FIX(0.09375);
            self->posY.val += self->velocityY;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.FreePrimitives(self->primIndex);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
