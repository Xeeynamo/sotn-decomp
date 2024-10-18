// SPDX-License-Identifier: AGPL-3.0-or-later
void MakeExplosions(void) {
    s32 temp_s3;
    s8 temp_s4;
    Entity* entity;
    s32 i;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, g_CurrentEntity, entity);
            // EntityExplosion does not seem to use these values.
            entity->ext.destructAnim.unk85 = 6 - i;
            entity->ext.destructAnim.unk80 = temp_s3;
            entity->ext.destructAnim.unk84 = temp_s4;
        }
    }
}
