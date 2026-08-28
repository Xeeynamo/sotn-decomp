// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit D_us_8018064C;
extern s8 g_HarpyKickHitboxes[];
extern u8 g_HarpyKickHitboxIdx[];

void EntityHarpyKick(Entity* self) {
    register s32 animFrame;
    s8* hitbox;
    Entity* harpy;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018064C);
        /* fall through */
    case 1:
        harpy = self - 1;
        self->facingLeft = harpy->facingLeft;
        self->posX.val = harpy->posX.val;
        self->posY.val = harpy->posY.val;
        animFrame = harpy->animCurFrame;
#ifdef VERSION_PSP
        hitbox = g_HarpyKickHitboxes;
        animFrame = g_HarpyKickHitboxIdx[animFrame];
#else
        animFrame = g_HarpyKickHitboxIdx[animFrame];
        hitbox = g_HarpyKickHitboxes;
#endif
        hitbox += animFrame * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (harpy->entityId != E_UNK_1C) {
            DestroyEntity(self);
        }
        break;
    }
}
