// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitWerewolfAttackHitbox;
extern s8 werewolf_attack_hitboxes[][4];
extern u8 werewolf_attack_hitbox_indices[];
#ifdef VERSION_PSP
extern s32 E_ID(WEREWOLF);
#endif

void EntityWerewolfAttackHitbox(Entity* self) {
    s32 animCurFrame;
    s8* hitboxPtr;
    Entity* werewolf;

    if (!self->step) {
        InitializeEntity(g_EInitWerewolfAttackHitbox);
        self->animCurFrame = 0;
    }

    werewolf = self - 1;
    if (werewolf->entityId != E_ID(WEREWOLF)) {
        DestroyEntity(self);
        return;
    }

    animCurFrame = werewolf->animCurFrame;
    self->facingLeft = werewolf->facingLeft;
    self->posX.val = werewolf->posX.val;
    self->posY.val = werewolf->posY.val;

    hitboxPtr = *werewolf_attack_hitboxes;
    hitboxPtr += werewolf_attack_hitbox_indices[animCurFrame] * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}
