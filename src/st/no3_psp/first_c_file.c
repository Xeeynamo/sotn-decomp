// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no3/no3.h"

#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2E3BC;
extern LayoutEntity* D_8D2E490;

extern Overlay OVL_EXPORT(Overlay);

extern char cutscene_data_it[];
extern char cutscene_data_sp[];
extern char cutscene_data_fr[];
extern char cutscene_data_ge[];
extern char cutscene_data_en[];

extern u8* OVL_EXPORT(cutscene_data); // bss

#include "../get_lang_at.h"

extern s32 E_ID(LIGHTNING_THUNDER);
extern s32 E_ID(LIGHTNING_CLOUD);
#if defined(STAGE_IS_NO3)
static u8 D_80180EA0[] = {
    0x09, 0x04, 0x27, 0x28, 0x2A, 0x2C, 0x2F, 0x32, 0x36, 0x3F, 0x4A, 0x56,
    0x62, 0x6E, 0x7A, 0x00, 0x0C, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x37, 0x40, 0x4B, 0x57, 0x63, 0x6F, 0x7B, 0x01, 0x0E, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x38, 0x41, 0x4C, 0x58, 0x64, 0x70, 0x7C, 0x02,
    0x0F, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x39, 0x42, 0x4D, 0x59,
    0x65, 0x71, 0x7D, 0x03, 0x02, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
    0x3A, 0x43, 0x4E, 0x5A, 0x66, 0x72, 0x7E, 0x0A, 0x03, 0x12, 0x12, 0x12,
    0x12, 0x12, 0x12, 0x12, 0x12, 0x44, 0x4F, 0x5B, 0x67, 0x73, 0x7F, 0x0B,
    0x04, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x50, 0x5C,
    0x68, 0x74, 0x80, 0x0C, 0x0A, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
    0x12, 0x45, 0x51, 0x5D, 0x69, 0x75, 0x81, 0x0D, 0x0B, 0x12, 0x12, 0x12,
    0x12, 0x2E, 0x31, 0x34, 0x3C, 0x46, 0x52, 0x5E, 0x6A, 0x76, 0x82, 0x0E,
    0x10, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x35, 0x3D, 0x47, 0x53, 0x5F,
    0x6B, 0x77, 0x83, 0x0F, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
    0x3E, 0x48, 0x54, 0x60, 0x6C, 0x78, 0x84, 0x10, 0x12, 0x12, 0x12, 0x12,
    0x12, 0x12, 0x12, 0x12, 0x12, 0x49, 0x55, 0x61, 0x6D, 0x79, 0x85, 0x11};
#endif

static u8 lightningClutIndices[] = {
    #if defined(STAGE_IS_NO3)
        0x09, 0x04, 0x07, 0x00, 0x0C, 0x05, 0x08, 0x01, 0x0E, 0x05, 0x08, 0x02,
        0x0F, 0x06, 0x09, 0x03, 0x02, 0x12, 0x12, 0x0A, 0x03, 0x12, 0x12, 0x0B,
        0x04, 0x12, 0x12, 0x0C, 0x0A, 0x12, 0x12, 0x0D, 0x0B, 0x12, 0x12, 0x0E,
        0x10, 0x12, 0x12, 0x0F, 0x11, 0x12, 0x12, 0x10, 0x12, 0x12, 0x12, 0x11,
    #endif
        0x15, 0x17, 0x18, 0x17, 0x5C, 0x13, 0x14, 0x13, 0x5E, 0x15, 0x16, 0x15,
        0x17, 0x86, 0x87, 0x86, 0x49, 0x88, 0x89, 0x88, 0x14, 0x8A, 0x8B, 0x8A,
        0xFF, 0x00, 0x00, 0x00};

static u16 lightningAnim[] = {
    0x0104, 0x0002, 0x0102, 0x0002, 0x0102, 0x0002, 0x00FF, 0x0000};
#if defined(STAGE_IS_NO3)
static u16 D_80180FBC[] = {
    0x0108, 0x0208, 0x0308, 0x0408, 0x0508, 0x0608, 0x0708, 0x0808,
    0x0908, 0x0A08, 0x0B08, 0x0C08, 0x0D08, 0x0E08, 0x0F08, 0x00FF};
#endif
static u8 lightningThunderXY[][2] = {
    {0x88, 0x6C}, {0xC8, 0x30}, {0x30, 0x44}, {0x88, 0x6C}};

void EntityBackgroundLightning(Entity* self) {
    Entity* otherEnt;
    s32 animFrame;
    s32 randOf3;
    u8* clutIndices;
    s32 i;
#if defined(STAGE_IS_NO3)
    s32 clutDest;
    u8* var_s1;
    s32 playerRealX;
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.backgroundLightning.timer = 0x80;
        self->animCurFrame = 15;
#if defined(STAGE_IS_NO3)
        var_s1 = &D_80180EA0[0];
        for (i = 0; i < 12; i++) {
            clutDest = var_s1[0];
            animFrame = 15;
            animFrame = var_s1[animFrame];
            g_ClutIds[clutDest] = g_ClutIds[animFrame + 0x200];
            var_s1 += 16;
        }
        if (self->params & 256) {
            self->step = 4;
            break;
        }
        if (g_CastleFlags[CASTLE_TURNED_ON]) {
            self->params = 0;
        }
#else
        g_CastleFlags[CASTLE_TURNED_ON] |= 1;
        if (self->params & FLAG_DEAD) {
            self->step = 4;
            break;
        }
#endif
    case 1:
        switch (self->step_s) {
#if !defined(STAGE_IS_NO3)
        default:
            break;
#endif
        case 0:
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(E_ID(LIGHTNING_THUNDER), otherEnt);
                randOf3 = Random() & 3;
                otherEnt->posX.i.hi = lightningThunderXY[randOf3][0];
                otherEnt->posY.i.hi = lightningThunderXY[randOf3][1];
            }
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(E_ID(LIGHTNING_CLOUD), otherEnt);
                if (randOf3 > 2) {
                    randOf3 = 0;
                }
                otherEnt->params = randOf3;
            }
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(lightningAnim, self) == 0) {
                self->ext.backgroundLightning.timer = (Random() & 0x7F) + 0x40;
                self->step_s++;
            }
            clutIndices = &lightningClutIndices[0];
#if defined(STAGE_IS_NO3)
            if (!self->params) {
                clutIndices += 0x30;
            }
#endif
            for (animFrame = self->animCurFrame; *clutIndices != 0xFF;
                 clutIndices += 4) {
                i = *clutIndices;
                g_ClutIds[i] = g_ClutIds[(clutIndices + animFrame)[1] + 0x200];
            }

            if (animFrame == 1) {
                g_GpuBuffers[0].draw.r0 = 0x30;
                g_GpuBuffers[0].draw.g0 = 0x30;
                g_GpuBuffers[0].draw.b0 = 0x48;
                g_GpuBuffers[1].draw.r0 = 0x30;
                g_GpuBuffers[1].draw.g0 = 0x30;
                g_GpuBuffers[1].draw.b0 = 0x48;
            } else { // Same as case 2 right below
                g_GpuBuffers[0].draw.r0 = 0x10;
                g_GpuBuffers[0].draw.g0 = 8;
                g_GpuBuffers[0].draw.b0 = 0x38;
                g_GpuBuffers[1].draw.r0 = 0x10;
                g_GpuBuffers[1].draw.g0 = 8;
                g_GpuBuffers[1].draw.b0 = 0x38;
            }
            break;
        case 2:
            g_GpuBuffers[0].draw.r0 = 0x10;
            g_GpuBuffers[0].draw.g0 = 8;
            g_GpuBuffers[0].draw.b0 = 0x38;
            g_GpuBuffers[1].draw.r0 = 0x10;
            g_GpuBuffers[1].draw.g0 = 8;
            g_GpuBuffers[1].draw.b0 = 0x38;
            if (--self->ext.backgroundLightning.timer) {
                break;
            }
            SetSubStep(0);
            break;
        }
#if defined(STAGE_IS_NO3)
        if (self->params != 1) {
            break;
        }
        otherEnt = &PLAYER;
        playerRealX = g_Tilemap.scrollX.i.hi + otherEnt->posX.i.hi;
        if (playerRealX > 0x300) {
            g_CastleFlags[CASTLE_TURNED_ON] = 1;
            SetStep(2);
        }
#endif
        break;
#if defined(STAGE_IS_NO3)
    case 2:
        if (AnimateEntity(D_80180FBC, self) == 0) {
            self->params = 0;
            SetStep(1);
        }
        g_GpuBuffers[0].draw.r0 = 16;
        g_GpuBuffers[0].draw.g0 = 8;
        g_GpuBuffers[0].draw.b0 = 56;
        g_GpuBuffers[1].draw.r0 = 16;
        g_GpuBuffers[1].draw.g0 = 8;
        g_GpuBuffers[1].draw.b0 = 56;
        var_s1 = &D_80180EA0[0];
        for (i = 0; i < 12; i++) {
            clutDest = var_s1[0];
            animFrame = self->animCurFrame;
            animFrame = var_s1[animFrame];
            g_ClutIds[clutDest] = g_ClutIds[animFrame + 0x200];
            var_s1 += 16;
        }
        break;
#endif
    // careful, this is the outer switch!
    case 4:
        g_GpuBuffers[0].draw.r0 = 16;
        g_GpuBuffers[0].draw.g0 = 8;
        g_GpuBuffers[0].draw.b0 = 56;
        g_GpuBuffers[1].draw.r0 = 16;
        g_GpuBuffers[1].draw.g0 = 8;
        g_GpuBuffers[1].draw.b0 = 56;
    }
#if defined(STAGE_IS_NO3)
    if (self->params == 1) {
        switch (self->ext.backgroundLightning.unk84) {
        case 0:
            g_api.PlaySfx(SET_UNK_90);
            self->ext.backgroundLightning.unk84++;
            D_80097928 = 1;
            D_80097910 = MU_METAMORPHOSIS_III;
            break;
        case 1:
            if (g_api.func_80131F68() == false) {
                D_80097928 = 0;
                g_api.PlaySfx(D_80097910);
                self->ext.backgroundLightning.unk84++;
            }
            break;
        case 2:
            otherEnt = &PLAYER;
            playerRealX = g_Tilemap.scrollX.i.hi + otherEnt->posX.i.hi;
            if (playerRealX > 0x300) {
                g_api.PlaySfx(SET_UNK_90);
                D_80097928 = 1;
                D_80097910 = MU_DRACULAS_CASTLE;
                self->ext.backgroundLightning.unk84++;
            }
            break;
        case 3:
            if (g_api.func_80131F68() == false) {
                D_80097928 = 0;
                g_api.PlaySfx(D_80097910);
                self->ext.backgroundLightning.unk84++;
            }
            break;
        }
    }
#endif
}

extern s32 E_ID(ID_11);
extern s32 E_ID(ID_12);
extern s32 E_ID(ID_13);
extern s32 E_ID(ID_14);
extern s32 E_ID(GREY_PUFF);
extern s32 E_ID(ID_16);
extern s32 E_ID(BG_LIGHTNING);
extern s32 E_ID(ID_18);
extern s32 E_ID(ID_19);
extern s32 E_ID(ID_1A);
extern s32 E_ID(ID_1B);
extern s32 E_ID(ID_1C);
extern s32 E_ID(ID_1D);
extern s32 E_ID(CAVERN_DOOR_PLATFORM);
extern s32 E_ID(ID_1F);
extern s32 E_ID(ID_20);
extern s32 E_ID(ID_21);
extern s32 E_ID(ID_22);
extern s32 E_ID(ID_23);
extern s32 E_ID(ID_24);
extern s32 E_ID(ID_25);
extern s32 E_ID(ID_26);
extern s32 E_ID(FALLING_ROCK_2);
extern s32 E_ID(ID_28);
extern s32 E_ID(LIGHTNING_THUNDER);
extern s32 E_ID(LIGHTNING_CLOUD);
extern s32 E_ID(ID_2B);
extern s32 E_ID(ID_2C);
extern s32 E_ID(ID_2D);
extern s32 E_ID(ID_2E);
extern s32 E_ID(ID_2F);
extern s32 E_ID(ID_30);
extern s32 E_ID(ID_31);
extern s32 E_ID(ID_32);
extern s32 E_ID(ID_33);
extern s32 E_ID(ID_34);
extern s32 E_ID(SPLASH_WATER);
extern s32 E_ID(SURFACING_WATER);
extern s32 E_ID(SIDE_WATER_SPLASH);
extern s32 E_ID(SMALL_WATER_DROP);
extern s32 E_ID(WATER_DROP);
extern s32 E_ID(MERMAN2);
extern s32 E_ID(MERMAN_JUMP_WATER);
extern s32 E_ID(MERMAN2_UNK1);
extern s32 E_ID(HIGH_WATER_SPLASH);
extern s32 E_ID(MERMAN2_SPIT_FIRE);
extern s32 E_ID(MERMAN2_DYING);
extern s32 E_ID(MERMAN2_JUMP_AIR);
extern s32 E_ID(MERMAN);
extern s32 E_ID(MERMAN_SPIT_FIRE);
extern s32 E_ID(MERMAN_JUMP_AIR);
extern s32 E_ID(MERMAN_DYING);
extern s32 E_ID(ID_45);
extern s32 E_ID(ID_46);
extern s32 E_ID(BONE_SCIMITAR_HEAD);
extern s32 E_ID(ID_48);
extern s32 E_ID(ID_49);
extern s32 E_ID(ID_4A);
extern s32 E_ID(ID_4B);
extern s32 E_ID(ZOMBIE);
extern s32 E_ID(ID_4D);
extern s32 E_ID(ID_4E);
extern s32 E_ID(ID_4F);
extern s32 E_ID(ID_50);
extern s32 E_ID(ID_51);
extern s32 E_ID(ID_52);
extern s32 E_ID(ID_53);
extern s32 E_ID(ID_54);
extern s32 E_ID(ID_55);
extern s32 E_ID(ID_56);
extern s32 E_ID(ID_57);
extern s32 E_ID(ID_58);
extern s32 E_ID(ID_59);
extern s32 E_ID(ID_5A);
extern s32 E_ID(DEATH_SCYTHE);
extern s32 E_ID(ID_5C);
extern s32 E_ID(FALLING_ROCK);
extern s32 E_ID(DEATH_SCYTHE_SHADOW);
extern s32 E_ID(ID_5F);
extern s32 E_ID(FLYING_OWL_UNK60);
extern s32 E_ID(WARG_EXP_TRANSP);
extern s32 E_ID(WARG_EXP_OPAQUE);

void InitEntityIds(void) {
    E_ID(ID_11) = 0x11;
    E_ID(ID_12) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(ID_14) = 0x14;
    E_ID(GREY_PUFF) = 0x15;
    E_ID(ID_16) = 0x16;
    E_ID(BG_LIGHTNING) = 0x17;
    E_ID(ID_18) = 0x18;
    E_ID(ID_19) = 0x19;
    E_ID(ID_1A) = 0x1A;
    E_ID(ID_1B) = 0x1B;
    E_ID(ID_1C) = 0x1C;
    E_ID(ID_1D) = 0x1D;
    E_ID(CAVERN_DOOR_PLATFORM) = 0x1E;
    E_ID(ID_1F) = 0x1F;
    E_ID(ID_20) = 0x20;
    E_ID(ID_21) = 0x21;
    E_ID(ID_22) = 0x22;
    E_ID(ID_23) = 0x23;
    E_ID(ID_24) = 0x24;
    E_ID(ID_25) = 0x25;
    E_ID(ID_26) = 0x26;
    E_ID(FALLING_ROCK_2) = 0x27;
    E_ID(ID_28) = 0x28;
    E_ID(LIGHTNING_THUNDER) = 0x29;
    E_ID(LIGHTNING_CLOUD) = 0x2A;
    E_ID(ID_2B) = 0x2B;
    E_ID(ID_2C) = 0x2C;
    E_ID(ID_2D) = 0x2D;
    E_ID(ID_2E) = 0x2E;
    E_ID(ID_2F) = 0x2F;
    E_ID(ID_30) = 0x30;
    E_ID(ID_31) = 0x31;
    E_ID(ID_32) = 0x32;
    E_ID(ID_33) = 0x33;
    E_ID(ID_34) = 0x34;
    E_ID(SPLASH_WATER) = 0x35;
    E_ID(SURFACING_WATER) = 0x36;
    E_ID(SIDE_WATER_SPLASH) = 0x37;
    E_ID(SMALL_WATER_DROP) = 0x38;
    E_ID(WATER_DROP) = 0x39;
    E_ID(MERMAN2) = 0x3A;
    E_ID(MERMAN_JUMP_WATER) = 0x3B;
    E_ID(MERMAN2_UNK1) = 0x3C;
    E_ID(HIGH_WATER_SPLASH) = 0x3D;
    E_ID(MERMAN2_SPIT_FIRE) = 0x3E;
    E_ID(MERMAN2_DYING) = 0x3F;
    E_ID(MERMAN2_JUMP_AIR) = 0x40;
    E_ID(MERMAN) = 0x41;
    E_ID(MERMAN_SPIT_FIRE) = 0x42;
    E_ID(MERMAN_JUMP_AIR) = 0x43;
    E_ID(MERMAN_DYING) = 0x44;
    E_ID(ID_45) = 0x45;
    E_ID(ID_46) = 0x46;
    E_ID(BONE_SCIMITAR_HEAD) = 0x47;
    E_ID(ID_48) = 0x48;
    E_ID(ID_49) = 0x49;
    E_ID(ID_4A) = 0x4A;
    E_ID(ID_4B) = 0x4B;
    E_ID(ZOMBIE) = 0x4C;
    E_ID(ID_4D) = 0x4D;
    E_ID(ID_4E) = 0x4E;
    E_ID(ID_4F) = 0x4F;
    E_ID(ID_50) = 0x50;
    E_ID(ID_51) = 0x51;
    E_ID(ID_52) = 0x52;
    E_ID(ID_53) = 0x53;
    E_ID(ID_54) = 0x54;
    E_ID(ID_55) = 0x55;
    E_ID(ID_56) = 0x56;
    E_ID(ID_57) = 0x57;
    E_ID(ID_58) = 0x58;
    E_ID(ID_59) = 0x59;
    E_ID(ID_5A) = 0x5A;
    E_ID(DEATH_SCYTHE) = 0x5B;
    E_ID(ID_5C) = 0x5C;
    E_ID(FALLING_ROCK) = 0x5D;
    E_ID(DEATH_SCYTHE_SHADOW) = 0x5E;
    E_ID(ID_5F) = 0x5F;
    E_ID(FLYING_OWL_UNK60) = 0x60;
    E_ID(WARG_EXP_TRANSP) = 0x61;
    E_ID(WARG_EXP_OPAQUE) = 0x62;
}

void func_pspeu_09238360(void) {
    OVL_EXPORT(cutscene_data) = GetLangAt(
        0, (u8*)cutscene_data_en, (u8*)cutscene_data_fr, (u8*)cutscene_data_sp,
        (u8*)cutscene_data_ge, (u8*)cutscene_data_it);

    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2E3BC;
    g_pStObjLayoutVertical = &D_8D2E490;
    func_892A018();
    memcpy((u8*)&g_api, (u8*)&OVL_EXPORT(Overlay), sizeof(Overlay));
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityCastleDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityHeartRoomSwitch);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityHeartRoomGoldDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09239020);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityWeightsSwitch);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityPathBlockSmallWeight);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityPathBlockTallWeight);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09239940);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityCavernDoorLever);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityCavernDoorPlatform);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityCavernDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityTransparentWater);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityBackgroundBushes);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityBackgroundTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityStairwayPiece);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityFallingRock);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityMermanRockLeftSide);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityMermanRockRightSide);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityJewelSwordDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityFallingRock2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_0923C528);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityDeathSkySwirl);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityLightningThunder);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityLightningCloud);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityTrapDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_0923D348);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityExplosionPuffOpaque);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityPushAlucard);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityCastleDoorTransition);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityForegroundTree);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityUnkId50);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityBackgroundPineTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityUnkId52);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityCastleBridge);

// clumsy thing, linter splits the line which breaks INCLUDE_ASM
// clang-format off
INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityDistantBackgroundTrees);
// clang-format on

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityBackgroundCastleWall);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityFlyingOwlAndLeaves);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityFallingLeaf);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityRoomTransition2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityDeathStolenItem);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityDeath);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityDeathScythe);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityDeathScytheShadow);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityTilemapShufflerUnused);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityShuttingWindow);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityBreakable);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityCavernDoorVase);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityUnkId16);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09242C00);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09242CA0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09242FB8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09243040);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09243108);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09243168);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09243378);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_092433B0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09243748);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", NO3_EntityCutscene);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityLockCamera);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09245A58);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09245B78);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09245D10);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09245EA8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09245F18);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09245FA0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_092460E0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09246238);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_092462B0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09246338);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09246480);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", InitRoomEntities);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", UpdateRoomPosition);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", CreateEntityFromCurrentEntity);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09246978);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityBat);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityStageNamePopup);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09247BB8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", NO3_EntityRedDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", Random);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", Update);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", UpdateStageEntities);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_092493F8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09249590);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09249738);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09249878);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityFireWarg);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityUnkId30);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityUnkId31);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityExplosion3);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_0924C7A8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityFireWargWaveAttack);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityUnkId2F);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityFireWargDeathBeams);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_0924D9C0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityMerman2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityExplosion2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityMediumWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityMermanWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityFallingObject2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityHighWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityDeadMerman);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityMermanSpawner);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityMerman);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityMermanFireball);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityFallingObject);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", EntityMermanExplosion);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_092516E8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/first_c_file", func_pspeu_09251C70);
