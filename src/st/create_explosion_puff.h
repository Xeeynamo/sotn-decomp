// SPDX-License-Identifier: AGPL-3.0-or-later

#ifdef VERSION_PSP
extern s32 E_ID(EXPLODE_PUFF_OPAQUE);
#endif

void CreateExplosionPuff() {
    Entity* puff;
    s32 rand3 = Random() & 3; // Random puff style 0, 1, 2
    s16 initAngle = ((Random() & 0xF) << 8) - ROT(180);
    s32 i;

    for (i = 0; i < 6; i++) {
        puff = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (puff != NULL) {
            CreateEntityFromEntity(
                E_ID(EXPLODE_PUFF_OPAQUE), g_CurrentEntity, puff);
            puff->params = 2;
            puff->ext.opaquePuff.speed = 6 - i;
            puff->ext.opaquePuff.angle = initAngle;
            puff->ext.opaquePuff.puffStyle = rand3;
        }
    }
}
