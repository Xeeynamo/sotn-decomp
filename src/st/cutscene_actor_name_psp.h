// SPDX-License-Identifier: AGPL-3.0-or-later

// st0 uses a union for g_Dialogue
#ifdef STAGE_IS_ST0
#define G_DIALOGUE g_Dialogue.std
#else
#define G_DIALOGUE g_Dialogue
#endif

#ifdef VERSION_PSP
extern u8 actor_name_len_en[];
extern u8 actor_name_len_fr[];
extern u8 actor_name_len_sp[];
extern u8 actor_name_len_ge[];
extern u8 actor_name_len_it[];

extern u16 actor_names_en[];
extern u16 actor_names_fr[];
extern u16 actor_names_sp[];
extern u16 actor_names_ge[];
extern u16 actor_names_it[];

// Creates primitives for the actor name at the head of the dialogue
void DrawCutsceneActorName(u16 actorIndex, Entity* self, u16* actorNames,
                           u8* arg3, u8* arg4, s32 nActors) {
#else
void DrawCutsceneActorName(u16 actorIndex, Entity* self) {
#endif
    Primitive* prim;
    u16 ch;
    u16 i;
    s16 x;
    u8* actorNameLength;
    u16 actorNameStartIndex;
    u16* actorName;
    s32 primIndex;
    u8* len;

#ifdef VERSION_HD
    primIndex = g_api.AllocPrimitives(PRIM_SPRT, actor_prims[actorIndex]);
#else
    // Create a certain amount of sprites based on the actor name's letter count
    actorNameLength =
        (u8*)GetLang(actor_name_len_en, actor_name_len_fr, actor_name_len_sp,
                     actor_name_len_ge, actor_name_len_it);
    ch = actorNameLength[arg3[actorIndex]];
    primIndex = g_api.AllocPrimitives(PRIM_SPRT, ch);
#endif

    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }

#ifdef VERSION_PSP
    // Pre-calculate primitives that renders the actor's name
    x = 0x38;
#endif
    G_DIALOGUE.primIndex[1] = primIndex;
    prim = &g_PrimBuf[primIndex];
#ifdef VERSION_HD
    x = 0x38;
    len = &actor_name_len;
    actorNameStartIndex = 0;
    for (i = 0; i < actorIndex; i++) {
        actorNameStartIndex += *len & 0x7F;
        len++;
    };
    actorName = &actor_names[actorNameStartIndex];
#else
    len = actorNameLength;
    actorNameStartIndex = 0;
    for (i = 0; i < arg3[actorIndex]; i++) {
        actorNameStartIndex += actorNameLength[i];
    }
    actorNames = (u16*)GetLang(
        (u8*)actor_names_en, (u8*)actor_names_fr, (u8*)actor_names_sp,
        (u8*)actor_names_ge, (u8*)actor_names_it);
    actorName = &actorNames[actorNameStartIndex];
#endif
    while (prim) {
        prim->type = PRIM_SPRT;
        prim->tpage = 0x1E;
        prim->clut = 0x196;
        ch = *actorName++;
        prim->u0 = (s8)((ch & 0xF) * FONT_W);
        prim->v0 = (s8)((ch & 0xF0) >> 1);
        prim->u1 = prim->v1 = FONT_W;
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_HIDE;
        prim->x0 = x;
        prim->y0 = G_DIALOGUE.startY + 6;
        if (ch & 0xF000) {
            prim = prim->next;
            prim->type = PRIM_SPRT;
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            if (ch & 0x4000) {
                prim->u0 = 0x78;
            } else {
                prim->u0 = 0x70;
            }
            prim->v0 = 0x48;
            prim->u1 = prim->v1 = FONT_W;
            prim->priority = 0x1FF;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = x;
            prim->y0 = G_DIALOGUE.startY - 2;
        }
        x += FONT_GAP;
        prim = prim->next;
    }
}
