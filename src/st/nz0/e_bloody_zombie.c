REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
extern u16 g_EBloodyZombieInit[];
static s16 sensors_ground[4][2] = {{0, 28}, {0, 4}, {8, -4}, {-16, 0}};
static u16 sensors_move[][2] = {{0, 28}, {8, 0}};
static u8 anim_walk[] = {0x04, 0x02, 0x0D, 0x03, 0x0A, 0x02, 0x0A, 0x01,
                         0x0D, 0x04, 0x0A, 0x01, 0x06, 0x02, 0x00, 0x00};
static u8 anim_attack[] = {
    0x04, 0x05, 0x04, 0x06, 0x03, 0x07, 0x02, 0x08, 0x02, 0x09, 0x04, 0x08,
    0x02, 0x0A, 0x02, 0x0B, 0x02, 0x0C, 0x02, 0x0D, 0x02, 0x0E, 0x02, 0x0F,
    0x0C, 0x10, 0x02, 0x11, 0x02, 0x12, 0x02, 0x13, 0xFF, 0x00};
static u8 anim_hit[] = {
    0x01, 0x16, 0x01, 0x14, 0x01, 0x15, 0x01, 0x14, 0x02, 0x15,
    0x03, 0x14, 0x04, 0x15, 0x08, 0x14, 0x02, 0x16, 0xFF, 0x00};
static u8 anim_die[] = {
    0x01, 0x16, 0x01, 0x14, 0x01, 0x15, 0x01, 0x14, 0x02, 0x15, 0x03, 0x14,
    0x04, 0x15, 0x28, 0x14, 0x06, 0x17, 0x05, 0x18, 0x05, 0x19, 0x05, 0x1A,
    0x05, 0x1B, 0x02, 0x1C, 0x02, 0x1D, 0x02, 0x1E, 0x02, 0x1F, 0x02, 0x1E,
    0x02, 0x1F, 0x02, 0x1E, 0x02, 0x1F, 0x02, 0x1E, 0x02, 0x1F, 0x02, 0x1E,
    0x02, 0x1F, 0x02, 0x1E, 0x02, 0x1F, 0x02, 0x1E, 0x02, 0x1F, 0x02, 0x1E,
    0x02, 0x1F, 0x02, 0x1E, 0x02, 0x1F, 0x02, 0x1E, 0xFF, 0x00};
static u8 anim_chase[] = {0x02, 0x02, 0x06, 0x03, 0x04, 0x02, 0x04, 0x01,
                          0x06, 0x04, 0x04, 0x01, 0x02, 0x02, 0x00, 0x00};
static u8 D_8018238C[] = {
    0x08, 0x40, 0x20, 0x0F, 0x0F, 0x08, 0x50, 0x20, 0x0F, 0x0F, 0x08,
    0x60, 0x20, 0x0F, 0x0F, 0x08, 0x70, 0x20, 0x0F, 0x0F, 0xFF, 0x00};
static u8 D_801823A4[] = {
    0x04, 0x20, 0x00, 0x1F, 0x1F, 0x04, 0x40, 0x00, 0x1F, 0x1F, 0x04,
    0x60, 0x00, 0x1F, 0x1F, 0x04, 0x00, 0x20, 0x1F, 0x1F, 0x04, 0x20,
    0x20, 0x1F, 0x0F, 0x04, 0x20, 0x30, 0x1F, 0x0F, 0xFF, 0x00};
static s16 D_801823C4[][2] = {{0x0000, 0x0000}, {0x00FF, 0x0000}};
static u8 unused[] = {0x06, 0x01, 0x04, 0x01, 0x04, 0x02, 0x06, 0x03,
                      0x05, 0x04, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00};

REDACTED
    Primitive* prim;
    s32 primIndex;
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_InitializeEntityData0);
        break;
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
        self->step++;
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
        if (UpdateAnimation(&D_8018238C, prim) == 0) {
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
        if (UpdateAnimation(&D_801823A4, prim) == 0) {
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
static void func_801C53AC(Primitive* prim) {
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
    s32 animStatus;
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
    case BLOODY_ZOMBIE_INIT:
        InitializeEntity(g_EBloodyZombieInit);
        self->hitboxOffX = 1;
        self->hitboxOffY = 4;
REDACTED
REDACTED
REDACTED
    case BLOODY_ZOMBIE_UNK_2:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
REDACTED
REDACTED
REDACTED
REDACTED
    case BLOODY_ZOMBIE_WALK:
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        AnimateEntity(anim_walk, self);
        UnkCollisionFunc2(sensors_move);
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
                CreateEntityFromEntity(E_func_801C5D20, self, newEntity);
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
    case BLOODY_ZOMBIE_CHASE:
        if (AnimateEntity(anim_chase, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
        UnkCollisionFunc2(sensors_move);
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
                CreateEntityFromEntity(E_func_801C5D20, self, newEntity);
                if (self->facingLeft != 0) {
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
    case BLOODY_ZOMBIE_ATTACK:
        animStatus = AnimateEntity(anim_attack, self);
        if (animStatus & 0x80 && self->animFrameIdx == 10) {
            PlaySfxPositional(SFX_WEAPON_SWISH_B);
REDACTED
        if (animStatus == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
    case BLOODY_ZOMBIE_TAKE_HIT:
REDACTED
            // Splat blood
REDACTED
REDACTED
                CreateEntityFromEntity(E_BLOOD_SPLATTER, self, newEntity);
                newEntity->facingLeft = GetSideToPlayer() & 1;
REDACTED
REDACTED
REDACTED
REDACTED
        if (AnimateEntity(anim_hit, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    case BLOODY_ZOMBIE_DYING:
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
                    CreateEntityFromEntity(E_BLOOD_SPLATTER, self, newEntity);
                    newEntity->facingLeft = self->ext.generic.unk84.U8.unk0;
                    if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                self->ext.generic.unk84.U8.unk0 ^= 1;
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
                self->ext.generic.unk84.U8.unk0 ^= 1;
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
        if (AnimateEntity(anim_die, self) == 0) {
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
            self->ext.generic.unk80.modeS16.unk0 = 64;
REDACTED
            PlaySfxPositional(NA_SE_EN_EXPLOSIVE_DEATH);
REDACTED
REDACTED
REDACTED
REDACTED
    case BLOODY_ZOMBIE_DESTROY:
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
        if (CheckColliderOffsets(&D_801823C4, 0) != 0) {
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
