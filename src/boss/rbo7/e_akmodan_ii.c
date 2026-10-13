// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo7.h"

extern EInit g_EInitInteractable;

// unused
static s16 sensors_unused[][2] = {{0, 32}, {0, 4}, {16, -4}, {-32, 0}};
s16 D_us_801805DC[] = {0, 32, 8, 0};
AnimateEntityFrame D_us_801805E4[] = {
    POSE(16, 16, 0), POSE(16, 1, 0), POSE(16, 16, 0), POSE(16, 1, 0), POSE_END};
AnimateEntityFrame D_us_801805F0[] = {
    POSE(64, 3, 0), POSE(2, 5, 0), POSE(43, 6, 0),
    POSE(3, 7, 0),  POSE(21, 8, 0), POSE_END};
AnimateEntityFrame D_us_801805FC[] = {
    POSE(7, 9, 0),  POSE(7, 10, 0), POSE(7, 11, 0), POSE(7, 12, 0),
    POSE(7, 13, 0), POSE(7, 12, 0), POSE(7, 11, 0), POSE(7, 10, 0),
    POSE_LOOP(0)};
AnimateEntityFrame D_us_80180610[] = {
    POSE(3, 14, 0), POSE(10, 15, 0), POSE(3, 14, 0), POSE_END};
AnimateEntityFrame D_us_80180618[] = {
    POSE(6, 17, 0), POSE(36, 18, 0), POSE(4, 19, 0), POSE(32, 20, 0),
    POSE_END};
AnimateEntityFrame D_us_80180624[] = {
    POSE(5, 21, 0), POSE(5, 22, 0), POSE(5, 23, 0), POSE(5, 24, 0),
    POSE(5, 25, 0), POSE(5, 26, 0), POSE(5, 27, 0), POSE(5, 28, 0),
    POSE_LOOP(0)};
AnimateEntityFrame D_us_80180638[] = {
    POSE(4, 29, 0), POSE(21, 30, 0), POSE_END};
AnimateEntityFrame D_us_80180640[] = {
    POSE(4, 32, 0), POSE(17, 33, 0), POSE(4, 34, 0), POSE(4, 35, 0),
    POSE(4, 36, 0), POSE(4, 37, 0),  POSE(4, 38, 0), POSE(4, 39, 0),
    POSE(12, 40, 0), POSE(4, 39, 0), POSE(4, 38, 0), POSE(4, 37, 0),
    POSE(4, 36, 0), POSE(4, 35, 0),  POSE(4, 34, 0), POSE(4, 33, 0),
    POSE(4, 32, 0), POSE_END};
AnimateEntityFrame D_us_80180664[] = {
    POSE(2, 1, 0), POSE(2, 8, 0), POSE(2, 9, 0), POSE(2, 10, 0),
    POSE(2, 11, 0), POSE_END};
AnimateEntityFrame D_us_80180670[] = {
    POSE(2, 8, 0),  POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0),
    POSE(2, 10, 0), POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0),
    POSE_LOOP(0)};
AnimateEntityFrame D_us_80180684[] = {
    POSE(2, 12, 0), POSE(2, 13, 0), POSE(2, 14, 0), POSE_END};
static AnimateEntityFrame anim_flame[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(4, 3, 0),  POSE(4, 4, 0),
    POSE(4, 5, 0),  POSE(4, 6, 0),  POSE(4, 5, 0),  POSE(4, 4, 0),
    POSE(4, 5, 0),  POSE(4, 6, 0),  POSE(4, 7, 0),  POSE(4, 8, 0),
    POSE(4, 7, 0),  POSE(4, 8, 0),  POSE(4, 9, 0),  POSE(3, 10, 0),
    POSE(3, 11, 0), POSE(3, 12, 0), POSE(3, 13, 0), POSE(3, 14, 0),
    POSE(3, 15, 0), POSE(3, 16, 0), POSE(3, 17, 0), POSE(3, 18, 0),
    POSE(2, 19, 0), POSE(2, 20, 0), POSE(2, 21, 0), POSE(2, 22, 0),
    POSE(2, 23, 0), POSE(2, 24, 0), POSE_END};
// x, y pairs; the asm reads the y column as D_us_801806CC + 2
s16 D_us_801806CC[][2] = {
    {-26, -14}, {-24, 0}, {-32, 0}, {-30, -8}, {-16, -8}, {-18, -8}, {-16, -8},
    {-8, -8},   {8, -8},  {16, -8}, {18, -8},  {16, -8},  {-18, -8}, {-18, -8}};
s8 D_us_80180704[][4] = {{0, 0, 0, 0},   {4, -4, 4, 36},  {4, 0, 4, 32},
                         {4, 8, 4, 24},  {-4, 0, 4, 32},  {-4, 4, 4, 28},
                         {12, 0, 4, 32}};
u8 D_us_80180720[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3,
                      3, 1, 4, 4, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 4, 2, 6, 6, 2, 2, 2, 2, 2, 2, 0, 0, 0};
static s8 D_us_8018074C[][4] = {{0, 0, 0, 0},     {-20, -4, 4, 4},
                                {-16, -4, 8, 4},  {-16, -4, 16, 4},
                                {-24, -4, 16, 4}, {-32, -4, 24, 4}};
static u8 D_us_80180764[] = {0, 1, 2, 3, 4, 5, 0, 0};
#ifdef VERSION_PSP
char D_pspeu_09255468[] = "step %x\n";
char D_pspeu_09255478[] = "step_s %x\n";
char D_pspeu_09255488[] = "NO DR_ENV \n";
char D_pspeu_09255498[] = "timer %x\n";
char D_pspeu_092554A8[] = "charal %x\n";
char D_pspeu_092554B8[] = "tsukami %x\n";
#endif

INCLUDE_ASM("boss/rbo7/nonmatchings/e_akmodan_ii", func_us_801940B4);

INCLUDE_ASM("boss/rbo7/nonmatchings/e_akmodan_ii", func_us_801957C0);

extern EInit D_us_80180444;

void EntityHarpyKick(Entity* self) {
    s32 animFrame;
    s8* hitbox;
    Entity* harpy;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180444);
        /* fall through */
    case 1:
        harpy = self - 1;
        self->facingLeft = harpy->facingLeft;
        self->posX.val = harpy->posX.val;
        self->posY.val = harpy->posY.val;

        animFrame = harpy->animCurFrame;
        animFrame -= 0x23;
        if (animFrame < 0) {
            animFrame = 0;
        }

        hitbox = D_us_8018074C[0];
        animFrame = D_us_80180764[animFrame];
        hitbox += animFrame * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;

        if (harpy->entityId != E_ID(UNK_19)) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("boss/rbo7/nonmatchings/e_akmodan_ii", func_us_80195A8C);

extern EInit D_us_80180450;
extern s32 g_BossMgrState;

void func_us_80195D04(Entity* self) {
    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180450);
        self->animSet = 5;
        self->palette += 0x8000;
        self->unk5A = 0;
        self->blendMode = BLEND_TRANSP;
        self->velocityY = FIX(-0.375);
        self->hitboxWidth = self->hitboxHeight = 3;
        /* fall through */
    case 1:
        MoveEntity();
        if (self->pose > 25) {
            self->hitboxState = 0;
        }
        if (!AnimateEntity(anim_flame, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

static AnimateEntityFrame D_us_8018076C[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(3, 3, 0),  POSE(3, 4, 0),
    POSE(3, 5, 0),  POSE(3, 6, 0),  POSE(3, 7, 0),  POSE(3, 8, 0),
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE_END};

void EntityCtulhuDeath(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 14;
        self->unk5A = 121;
        self->drawFlags = ENTITY_OPACITY;
        if (self->params) {
            self->palette = 0x2EE;
            self->opacity = 8;
            self->blendMode = BLEND_TRANSP | BLEND_SUB;
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        } else {
            self->palette = 0x2E4;
            self->zPriority += 2;
            self->opacity = 0x14;
            self->blendMode = BLEND_TRANSP | BLEND_ADD;
        }
        /* fall through */
    case 1:
        self->posY.val -= FIX(1);
        if (!AnimateEntity(D_us_8018076C, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
