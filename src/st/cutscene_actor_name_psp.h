// SPDX-License-Identifier: AGPL-3.0-or-later
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
                           u8* arg3, s32* arg4, s32 nActors) {
    Primitive* prim;
    u16 ch;
    u16 i;
    s16 x;
    u8* actorNameLength;
    u16 actorNameStartIndex;
    u16* actorName;
    s32 primIndex;
    u8* len;

    // Create a certain amount of sprites based on the actor name's letter count
    actorNameLength =
        (u8*)GetLang(actor_name_len_en, actor_name_len_fr, actor_name_len_sp,
                     actor_name_len_ge, actor_name_len_it);
    ch = actorNameLength[arg3[actorIndex]];
    primIndex = g_api.AllocPrimitives(PRIM_SPRT, ch);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }

    // Pre-calculate primitives that renders the actor's name
    x = 0x38;
    g_Dialogue.primIndex[1] = primIndex;
    prim = &g_PrimBuf[primIndex];
    len = actorNameLength;
    actorNameStartIndex = 0;
    for (i = 0; i < arg3[actorIndex]; i++) {
        actorNameStartIndex += actorNameLength[i];
    }
    actorNames = (u16*)GetLang(
        (u8*)actor_names_en, (u8*)actor_names_fr, (u8*)actor_names_sp,
        (u8*)actor_names_ge, (u8*)actor_names_it);
    actorName = &actorNames[actorNameStartIndex];
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
        prim->y0 = g_Dialogue.startY + 6;
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
            prim->y0 = g_Dialogue.startY - 2;
        }
        x += FONT_GAP;
        prim = prim->next;
    }
}
