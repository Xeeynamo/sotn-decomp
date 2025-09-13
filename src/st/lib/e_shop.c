// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

// An inventory item consists of a category, which affects
// how the other fields are interpretted, an "unlock level",
// which is related to the number of things which have been
// accomplished in the castle (beating the game unlocks all),
// an item ID which corresponds to known item IDs, except for
// Jewel of Open, and the final item, which doesn't follow
// the pattern and doesn't appear in the shop
typedef struct {
    /* 0x0 */ u8 category;
    /* 0x1 */ u8 unlockLevel;
    /* 0x2 */ u16 itemId;
    /* 0x4 */ u32 price;
} InventoryItem;

typedef struct {
    /* 0x0 */ u16 category;
    /* 0x2 */ u16 itemId;
    /* 0x4 */ u32 price;
} ShopItem;

typedef enum {
    DRACULA_TACTICS,
    OLROX_TACTICS,
    DOPPLEGANGER10_TACTICS,
    GRANFALOON_TACTICS,
    MINOTAUR_WEREWOLF_TACTICS,
    SCYLLA_TACTICS,
    SLO_GAI_TACTICS,
    HIPPOGRYPH_TACTICS,
    BEELZEBUB_TACTICS,
    SUCCUBUS_TACTICS,
    KARASUMAN_TACTICS,
    TREVOR_GRANT_SYPHA_TACTICS,
    DEATH_TACTICS,
    CERBERUS_TACTICS,
    RICHTER_TACTICS,
    MEDUSA_TACTICS,
    THE_CREATURE_TACTICS,
    LESSER_DEMON_TACTICS,
    DOPPLEGANGER40_TACTICS,
    AKMODAN_II_TACTICS,
    DARKWING_BAT_TACTICS,
    GALAMOTH_TACTICS,
    MARIA_TACTICS = 0x1A,
    SHAFT_TACTICS,
    LORD_DRACULA_TACTICS,
} SHOP_TACTICS;

/// "documents" in the shop have their own
/// item index, separate from other items.
typedef enum {
    DOC_CASTLE_MAP,
    DOC_MAGIC_SCROLL_1,
    DOC_MAGIC_SCROLL_2,
    DOC_MAGIC_SCROLL_3,
    DOC_MAGIC_SCROLL_4,
    DOC_MAGIC_SCROLL_5,
    DOC_MAGIC_SCROLL_6,
    DOC_MAGIC_SCROLL_7,
    DOC_MAGIC_SCROLL_8,
} SHOP_DOCUMENTS;

/// the first 5 inventory categories are the same as
/// `EquipKind`. `EQUIP_RELIC` and `EQUIP_DOCUMENT` are
/// special and only used for inventory so far.
typedef enum {
    INVENTORY_HAND,
    INVENTORY_HEAD,
    INVENTORY_BODY,
    INVENTORY_CAPE,
    INVENTORY_ACCESSORY,
    INVENTORY_RELIC,
    INVENTORY_DOCUMENT,
} InventoryCategory;

static u16 D_us_80180E90[] = {
    0x0A9, 0x046, 0x040, 0x180, 0x06E, 0x01B, 0x04B, 0x0AF, 0x069, 0x01D, 0x051,
    0x0F6, 0x00D, 0x0B2, 0x0C1, 0x00B, 0x09D, 0x0FE, 0x09C, 0x031, 0x0F3, 0x010,
    0x028, 0x12F, 0x07C, 0x066, 0x130, 0x061, 0x055, 0x006, 0x0E9, 0x06C, 0x0B7,
    0x0FD, 0x016, 0x043, 0x126, 0x053, 0x05D, 0x0F7, 0x080, 0x058, 0x009, 0x06A,
    0x022, 0x0B4, 0x092, 0x06B, 0x063, 0x0FB, 0x105, 0x073, 0x072, 0x09E, 0x044,
    0x030, 0x081, 0x076, 0x11F, 0x0E3, 0x0D6, 0x014, 0x088, 0x0E4, 0x029, 0x12C,
    0x0D3, 0x042, 0x07A, 0x03D, 0x06F, 0x0E1, 0x0EF, 0x0CB, 0x0CE, 0x02D, 0x085,
    0x10F, 0x115, 0x017, 0x083, 0x0DD, 0x0BE, 0x0BC, 0x0BA, 0x04D, 0x118, 0x041,
    0x047, 0x16B, 0x15E, 0x032, 0x156, 0x071, 0x0A1, 0x106, 0x142, 0x127, 0x143,
    0x108, 0x11D, 0x078, 0x0A5, 0x00E, 0x0B6, 0x074, 0x131, 0x185, 0x025, 0x111,
    0x090, 0x182, 0x07E, 0x08D, 0x02B, 0x094, 0x0A7, 0x0C3, 0x08A, 0x0D8, 0x097,
    0x099, 0x026, 0x04F, 0x01F, 0x0EC, 0x10B, 0x188, 0x174, 0x16E, 0x172, 0x14E,
    0x148, 0x11C, 0x151, 0x144, 0x0E0, 0x0D9, 0x0E5, 0x133, 0x068, 0x0C6, 0x18C,
    0x164, 0x15F, 0x17B};

static const char* D_us_80180FB4[] = {
    "Destroyed by Richter in １７９２．（５ years ago）",
    "Revives due to blood soaked@bones．",
    "Vampire bats．@Feared as servants of evil．",
    "Indestructible spinning skull．",
    "Fresh corpses．@Magically animated．",
    "Legendary ””creature””．@Attacks all invaders．",
    "Magically animated skeleton．",
    "Wolves which guard castle @entrance．",
    "Ferocious skeleton @swordsman．",
    "Fireball−spitting Merman．@Largest of merman kind．",
    "４−legged skeleton．@Drips poison．",
    "Low level axe knight．",
    "Eastern Church soldiers @dispatched ３００ years ago．",
    "Bone−hurling skeleton．",
    "Possessed Ouija table．",
    "Boomerang wielding skeleton．",
    "Plant with razor−sharp @leaves．",
    "Fire−breathing flying demon．",
    "Low level flaming ghosts．",
    "Demonic puppet from Hell．",
    "Demon with enchanted spear．",
    "Nauseating two−headed @beast． Which is the head？",
    "Strange human−like creature．@Jumps like a flea．",
    "From Medusa’s hair．",
    "Novice of twin−bladed @combat．",
    "Skeletons equipped with @rifles．",
    "From Medusa’s hair．@Can petrify．",
    "Heavily armored knight with @iron ball．",
    "Mutated plant．@Seeds petrify．",
    "Well armored axe knight．",
    "Fire and ice demon．@Seems reluctant to fight．",
    "Skeleton archer equipped @with bow．",
    "Cannon built of white @dragon skulls．",
    "Shape−shifting demon．",
    "Local barnyard owl Mutated @by castle’s influence．",
    "Executed soldier’s head．@Hunting for vengeance．",
    "Snake living off Scylla．",
    "Animated ape skeleton．@Hurls wooden barrels．",
    "Armored warrior with @naginata．",
    "Book of beginner’s spells．",
    "Slow−flying skeleton warrior．",
    "Physical manifestations of @bodiless tormented souls．",
    "Knight armed with @Greatsword．",
    "Toad magically enlarged by @demonic baptism．",
    "Heavily armored undead @warrior．",
    "Armored guard．@Strong in perilous areas． ",
    "Headless skeleton．@Wields a rapier．",
    "Cave−dwelling frog．",
    "Ice−wielding female spirit．",
    "Book of ancient weapons．",
    "Giant skull spirit．",
    "Flesh−eating raven．",
    "Spirit of long−dead blue @raven．",
    "Plant with razor−sharp @leaves．",
    "Skeleton equipped with @spiked iron flail．",
    "Flea Man riding on specially @trained war−goose．",
    "Evil demon−sword． Causes @poltergeist phenomena．",
    "Naginata−wielding skeleton．",
    "Mythological sea monster．",
    "Invisible huntress spirit．",
    "Animated mud golem．",
    "Heavily armored knight @Attacks with trained owl．",
    "Evil demon−sword． Causes @poltergeist phenomena．",
    "Sword Lord wields sword @even when banished．",
    "Flea Man armed with axe and@shield．",
    "Part horse， lion and eagle．",
    "Giant skeleton．",
    "Monster made from gel．",
    "Master of twin−bladed @combat．",
    "Were panther skeleton．",
    "Grave Keeper．@Master of unarmed combat．",
    "Pyromaniacal gremlin．",
    "Creature with head of @woman and body of bird．",
    "Bull−headed monster．",
    "Shape−shifting lycanthrope．",
    "Portable skull shrine carried @by skeleton priests．",
    "Bloodthirsty undead knight @who eternally seeks combat．",
    "Mysterious cloaked @swordsman．",
    "Fish head guardian．",
    "Short magic−wielding demon．@Summons demonic allies．",
    "Searches among graves and @knows much wise lore．",
    "Ghost witches from Salem．",
    "Eldest Giant brother．@Wields two huge daggers．",
    "Giant brother．@Wields a gurkha knife．",
    "Giant brother．@Uses huge steel hammer．",
    "Discus−wielding armored @knight．",
    "Demon Lord of Ravens．",
    "Monster created from slimy @gel substance．",
    "Thunder−wielding demon．@Called ””Musician from Hell””．",
    "Watchdog of Hell．",
    "Master Fish−head．",
    "Magic−wielding vampire．@Rules upper part of castle．",
    "Female demon．@Invades men’s dreams．",
    "Gravestones possessed by @evil spirits of dead．",
    "Watered with human blood．",
    "The cowardly lion．",
    "Impaled man looking for brain．",
    "Nightmarish creature．@Composed of many．",
    "Monster nicknamed ””schmoo””．",
    "Heartless tin man．",
    "Holds countless poison seeds．",
    "Skeleton eternally chasing @his own skull．",
    "Bomb−tossing armored @knight．",
    "Zombies which attack even @when cut in half．",
    "Mutated insect．@Visible only to magicians．",
    "Expert at throwing weapons．",
    "Fiendishly accurate archer．",
    "Half−man， half−wolf．",
    "Liquid creature．@Takes black panther shape．",
    "Giant vampire bat．",
    "White dragon ridden by Flea @Man．",
    "Half−man， half−bull．",
    "Wields fearsome beam @weapon．",
    "Wyrm controlled by Flea Man．",
    "Animated skeleton of huge @dragon．",
    "Fireball−spitting wolf．",
    "Rock−tossing armored @knight．",
    "Angel archer．@Slew Amalaric of the Goths．",
    "Evil demon−sword． Causes @poltergeist phenomena．",
    "Skeleton with leaping attack．",
    "Skeleton mounted on Warg．",
    "Pre−intelligent bloodsucker @with long tongue for sucking．",
    "Evil mutated octopus．",
    "Flame demon．",
    "Armor plated war−beast．",
    "Gruesome Demon from Hell．",
    "Ancient egyptian mummy．",
    "Advanced Venus Weed．@Fed with demon blood．",
    "Shape−shifting demon．",
    "Snake−headed demoness @with gaze of stone．",
    "Made from the body parts @of powerful warriors．",
    "Zombie impersonating Grant．",
    "Zombie impersonating Trevor．",
    "Mischievous little demon．",
    "Zombie impersonating Sypha．",
    "Beelzebub Lord of Flies．",
    "Executioner of Hell．",
    "New−half ice spirit．@Servant of Galamoth．",
    "Young female witch．",
    "Master Vampire hunter．",
    "Rare bird．@Runs when sees people．",
    "Magical being with plan to @rule the netherworld．",
    "High level Armor Lord．",
    "Dracula’s close friend．",
    "Dark Priest of Dracula．",
    "Lord of Wallachia．@Father of Alucard．",
};
static u8 D_us_801811FC[] = {6, 3, 16, 4, -1, 0};
static u8 D_us_80181204[] = {10, 5, 10, 4, 10, 5, 1, 4, -1, 0};
static u8 D_us_80181210[] = {12, 14, 10, 15, 8, 16, 4, 17, -1, 0};
static u8 D_us_8018121C[] = {4,  16, 53, 19, 7,  18, 7,  19, 7,  18, 7,
                             19, 7,  18, 3,  19, 6,  16, 4,  17, -1, 0};
static u8 D_us_80181234[] = {7, 16, 6, 19, 6, 20, 7, 21, 8, 22, 4, 23, -1, 0};
static u8 D_us_80181244[] = {
    4,  22, 29, 21, 4,  20, 4, 19, 3,  16, 52, 17, 6,  16,
    10, 15, 7,  14, 10, 4,  9, 3,  52, 2,  11, 10, 7,  11,
    8,  12, 36, 13, 6,  12, 7, 11, 7,  10, 4,  2,  -1, 0};
static u8 D_us_80181270[] = {4, 22, 29, 21, 4, 20, 4, 19, 3, 16, 4, 17, -1, 0};
static u8 D_us_80181280[] = {6, 16, 10, 15, 7, 14, 10, 4, 9, 3, 4, 2, -1, 0};
static u8 D_us_80181290[] = {11, 10, 7, 11, 8, 12, 4, 13, -1, 0};
static u8 D_us_8018129C[] = {6, 12, 7, 11, 7, 10, 4, 2, -1, 0};
static u8 D_us_801812A8[] = {11, 2, 10, 6, 7, 7, 7, 8, 49, 9, 0, 0};
static u8 D_us_801812B4[] = {3, 8, 7, 7, 7, 6, 4, 2, 0, 0};
static u8 D_us_801812C0[] = {32, 4, 8, 3, 4, 2, -1, 0};
static u8 D_us_801812C8[] = {8, 2, 8, 24, 0, 0};
static u8 D_us_801812D0[] = {4, 41, 4, 42, -1, 0};
static u8* D_us_801812D8[] = {
    D_us_801811FC, D_us_80181204, D_us_80181210, D_us_8018121C, D_us_80181234,
    D_us_80181270, D_us_80181280, D_us_80181290, D_us_8018129C, D_us_801812A8,
    D_us_801812B4, D_us_801812C0, D_us_801812C8, D_us_801812D0};

#ifdef VERSION_PSP
extern s32 D_8C630D0;
extern s32 D_psp_08C630DC;
extern s32 E_ID(ID_25);
extern s32 E_ID(ID_27);
extern s32 E_ID(ID_28);
extern s32 E_ID(ID_29);
extern s32 E_ID(ID_2A);
extern s32 E_ID(ID_2D);
extern s32 E_ID(ID_2E);
extern s32 E_ID(ID_2F);
extern s32 E_ID(ID_48);
extern s32 E_ID(ID_4F);
extern s16 D_psp_092A4A10[];
extern u16 D_psp_092A4A78[];
extern s16 D_psp_092A4A88[];
extern u16 D_psp_092A4AA0[];
extern s16 D_psp_092A49B8[];
extern u8** D_psp_092A5F48;
extern u8** D_psp_092A5F98;
#endif

// bss
static u32 D_us_801D415C[64];
static u32 D_us_801D425C[64];
STATIC_PAD_BSS(8);
static ShopItem D_us_801D4364[75];
STATIC_PAD_BSS(8);

// This is probably EntityLibrarian, but I don't know for sure
void func_us_801AFE0C(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;

    switch (self->step) {
    case 0:
#ifdef VERSION_PSP
        func_psp_0925D4D0();
#endif
        InitializeEntity(D_us_80180824);
        if (player->posX.i.hi < 0x100) {
// I expect these two sounds to be the same, but 0x202 has not yet been defined.
// This leads me to think that the macro that has been defined for sfx 0x302
// is only accurate for PSX and does not align with the sfx for PSP here.
#ifdef VERSION_PSP
            g_api.PlaySfx(0x302);
#else
            g_api.PlaySfx(0x202);
#endif
        }
        if (g_CastleFlags[MET_LIBRARIAN]) {
            self->step = 8;
            break;
        }
#ifdef VERSION_PSP
        g_Player.padSim = PAD_LEFT | PAD_SIM_UNK20000;
        g_Player.demo_timer = 1;
#endif
        break;

    case 1:
        g_Entities[1].ext.entSlot1.unk0 = 1;
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = true;
        g_Player.padSim = PAD_LEFT;
        g_Player.demo_timer = 1;
        if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            g_Player.padSim = PAD_R1;
        } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
#ifdef VERSION_PSP
            g_Player.padSim = PAD_NONE;
#else
            g_Player.padSim = PAD_L1;
#endif
        } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
#ifdef VERSION_PSP
            g_Player.padSim = PAD_L1;
#else
            g_Player.padSim = PAD_R2;
#endif
        }
        g_Player.demo_timer = 1;
        SetStep(2);
        break;

    case 2:
        if (player->posX.i.hi > 0xE8) {
            if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
                g_Player.padSim = PAD_NONE;
                if (g_Timer & 1) {
                    if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
#ifdef VERSION_PSP
                        g_Player.padSim = PAD_R1 | PAD_SIM_UNK20000;
#else
                        g_Player.padSim = PAD_R1;
#endif
                    } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
#ifdef VERSION_PSP
                        g_Player.padSim = PAD_NONE | PAD_SIM_UNK20000;
#else
                        g_Player.padSim = PAD_L1;
#endif
                    } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
#ifdef VERSION_PSP
                        g_Player.padSim = PAD_L1 | PAD_SIM_UNK20000;
#else
                        g_Player.padSim = PAD_R2;
#endif
                    }
                }
            } else {
                g_Player.padSim = PAD_LEFT;
            }
        } else {
            g_CutsceneFlags |= 1;
            g_Player.padSim = PAD_NONE;
            player->posX.i.hi = 0xE8;
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;

    case 3:
        if (g_CutsceneFlags & 0x40) {
            if (player->posX.i.hi > 0x74) {
                g_Entities[1].ext.entSlot1.unk0 = 1;
                g_Player.padSim = PAD_LEFT;
            } else {
                player->posX.i.hi = 0x74;
                g_Player.padSim = PAD_NONE;
                self->step++;
            }
        } else {
            player->posX.i.hi = 0xE8;
        }
        g_Player.demo_timer = 1;
        break;

    case 4:
        g_Player.padSim = PAD_NONE | PAD_SIM_UNK20000;
        g_Player.demo_timer = 1;
        self->step++;
        break;

    case 5:
        g_CastleFlags[MET_LIBRARIAN] = 1;
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_MEET_MASTER_LIBRARIAN, TIMEATTACK_SET_RECORD);
        g_Player.demo_timer = 1;
        self->step++;
        /* fallthrough */
    case 6:
        if (g_CutsceneFlags & 0x100) {
            g_CutsceneFlags |= 0x2000;
            self->step = 0x10;
        } else {
            player->posX.i.hi = 0x74;
        }
        break;

    case 8:
        self->step++;
        /* fallthrough */
    case 9:
        if (player->posX.i.hi > 0xFF) {
            g_api.PlaySfx(CD_SOUND_COMMAND_7);
            DestroyEntity(self);
            return;
        }
        if (player->posX.i.hi < 0x75) {
            switch (self->step_s) {
            case 0:
                g_Entities[1].ext.entSlot1.unk0 = 1;
                g_PauseAllowed = false;
                g_unkGraphicsStruct.pauseEnemies = true;
                g_Player.padSim = PAD_NONE;
                g_Player.demo_timer = 16;
                self->step_s++;
                g_CutsceneFlags |= 1;
                break;

            case 1:
                if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
                    g_Player.padSim = PAD_NONE;
                    if (g_Timer & 1) {
                        if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                            g_Player.padSim = PAD_R1;
                        } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
#ifdef VERSION_PSP
                            g_Player.padSim = PAD_NONE;
#else
                            g_Player.padSim = PAD_L1;
#endif
                        } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
#ifdef VERSION_PSP
                            g_Player.padSim = PAD_L1;
#else
                            g_Player.padSim = PAD_R2;
#endif
                        }
                    }
                } else {
                    g_Player.padSim = PAD_LEFT;
                    self->step_s++;
                }
                g_Player.demo_timer = 1;
                break;

            case 2:
                g_Player.padSim = PAD_NONE;
                g_Player.demo_timer = 128;
                SetStep(10);
                break;
            }
            player->posX.i.hi = 0x74;
        }
        break;

    case 10:
        if (!g_Player.demo_timer && (g_Player.vram_flag & 1)) {
            g_Player.padSim = PAD_NONE | PAD_SIM_UNK20000;
            g_Player.demo_timer = 1;
            self->step++;
        }
        player->posX.i.hi = 0x74;
        break;

    case 11:
        g_Player.padSim = PAD_NONE | PAD_SIM_UNK20000;
        g_Player.demo_timer = 1;
        if (g_CutsceneFlags & 0x100) {
            g_CutsceneFlags |= 0x2000;
            self->step = 0x10;
        }
        break;

    case 16:
#ifdef VERSION_PSP
        g_PauseAllowed = false;
#endif
        g_Player.demo_timer = 32;
        g_Player.padSim = PAD_RIGHT;
        D_80097928 = 1;
        self->step++;
        break;

    case 17:
#ifdef VERSION_PSP
        g_PauseAllowed = false;
#endif
        if (!g_Player.demo_timer) {
#ifdef VERSION_PSP
            g_PauseAllowed = true;
#endif
            SetStep(9);
        }
        break;
    }
}

void EntityLibrarianChair(Entity* self) {
    Entity* newEnt;
    Entity* player = &PLAYER;
    Tilemap* tilemap = &g_Tilemap;

    if (self->step && (self->step < 11) && (g_SkipCutscene != 0) &&
        (g_IsCutsceneDone != 0)) {
        self->step = 11;
        self->animCurFrame = 2;
    }
    if (player->posX.i.hi < 0x38) {
        self->zPriority = 0xC0;
        if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
            GetPlayerCollisionWith(self, 16, 12, 2);
            // If the chair is not in step 16, and the player is high enough,
            // and moving upward, trigger a hit.
        } else if (self->step < 16 &&
                   ((player->posY.i.hi + tilemap->scrollY.i.hi) < 201) &&
                   F(player->velocityY).i.hi < 0) {
            SetStep(16);
            if (PLAYER.step == Player_HighJump) {
                g_Player.unk4A = 0x1C;
                if (PLAYER.step_s == 0) {
                    PLAYER.step_s = 1;
                    PLAYER.velocityY = FIX(-8);
                }
            }
            // Play chair jumping sound
            g_api.PlaySfx(SFX_QUICK_STUTTER_EXPLODE_B);
            self->ext.libraryChair.totalHits++;
            self->ext.libraryChair.consecutiveHits++;

            // At first hit, give Life Max Up.
            if (!(g_CastleFlags[LIBRARIAN_DROPS] & 1)) {
                newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEnt != NULL) {
                    CreateEntityFromCurrentEntity(E_PRIZE_DROP, newEnt);
                    newEnt->params = 23;
                    g_CastleFlags[LIBRARIAN_DROPS] |= 1;
                }
            }
            // Getting Axe Lord Armor requires hitting librarian 64 times.
            if (!(g_CastleFlags[LIBRARIAN_DROPS] & 2) &&
                (self->ext.libraryChair.totalHits >= 64)) {
                newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEnt != NULL) {
                    CreateEntityFromCurrentEntity(E_EQUIP_ITEM_DROP, newEnt);
                    newEnt->params = NUM_HAND_ITEMS + ITEM_AXE_LORD_ARMOR;
                    g_CastleFlags[LIBRARIAN_DROPS] |= 2;
                }
            }
            // Ring of Arcana requires 16 hits, without touching ground
            if (!(g_CastleFlags[LIBRARIAN_DROPS] & 4) &&
                (self->ext.libraryChair.consecutiveHits >= 16)) {
                newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEnt != NULL) {
                    CreateEntityFromCurrentEntity(E_EQUIP_ITEM_DROP, newEnt);
                    newEnt->params = NUM_HAND_ITEMS + ITEM_RING_OF_ARCANA;
                    g_CastleFlags[LIBRARIAN_DROPS] |= 4;
                }
            }
            // Dracula Tunic requires 24 hits, and inverted castle must be
            // unlocked.
            if (!(g_CastleFlags[LIBRARIAN_DROPS] & 8) &&
                (self->ext.libraryChair.consecutiveHits >= 24) &&
                (g_CastleFlags[INVERTED_CASTLE_UNLOCKED])) {
                newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEnt != NULL) {
                    CreateEntityFromCurrentEntity(E_EQUIP_ITEM_DROP, newEnt);
                    newEnt->params = NUM_HAND_ITEMS + ITEM_DRACULA_TUNIC;
                    g_CastleFlags[LIBRARIAN_DROPS] |= 8;
                }
            }
        }
    } else {
        self->zPriority = 0x80;
    }
    // If the player touches the ground, reset the frames airborne.
    if (g_Player.vram_flag & 1) {
        self->ext.libraryChair.consecutiveHits = 0;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->zPriority = 0x80;
        self->animSet = ANIMSET_OVL(11);
        self->animCurFrame = 2;
        self->palette = 0x210;
        self->unk5A = 0x48;
        self->ext.libraryChair.debugAnimID = 0;
        self->ext.libraryChair.timer = 0x20;
        self->flags &= ~FLAG_DESTROY_IF_OUT_OF_CAMERA;
        if (g_PlayableCharacter != PLAYER_ALUCARD) {
            self->facingLeft = 1;
            self->posX.i.hi -= 8;
        }
        g_CutsceneFlags = 0;
        g_IsCutsceneDone = 0;
        g_SkipCutscene = 0;
        break;
    case 1:
        if (g_CutsceneFlags & 2) {
            if (--self->ext.libraryChair.timer) {
                SetStep(2);
            }
        } else {
            if (g_CutsceneFlags & 0x80) {
                SetStep(9);
            }
        }
        break;
    case 2:
        if (AnimateEntity(D_us_801811FC, self) == 0) {
            SetStep(3);
        }
        break;
    case 3:
        AnimateEntity(D_us_80181204, self);
        if (g_CutsceneFlags & 4) {
            SetStep(4);
        }
        break;
    case 4:
        AnimateEntity(D_us_80181210, self);
        if (g_CutsceneFlags & 8) {
            SetStep(5);
        }
        break;
    case 5:
        AnimateEntity(D_us_8018121C, self);
        if (g_CutsceneFlags & 0x10) {
            SetStep(6);
        }
        break;
    case 6:
        AnimateEntity(D_us_80181234, self);
        if (g_CutsceneFlags & 0x20) {
            SetStep(7);
        }
        break;
    case 7:
        if (AnimateEntity(D_us_80181244, self) == 0) {
            SetStep(11);
        }
        break;
    case 9:
        if (AnimateEntity(D_us_801811FC, self) == 0) {
            SetStep(10);
        }
        break;
    case 10:
        if (AnimateEntity(D_us_801812C0, self) == 0) {
            SetStep(11);
        }
        break;
    case 11:
        if (g_CutsceneFlags & 0x800) {
            SetStep(12);
            self->ext.libraryChair.timer = 0x30;
        }
        if (g_CutsceneFlags & 0x1000) {
            SetStep(13);
        }
        break;
    case 12:
        AnimateEntity(D_us_801812C8, self);
        if (!--self->ext.libraryChair.timer) {
            g_CutsceneFlags &= ~0x800;
            self->animCurFrame = 2;
            SetStep(11);
        }
        if (g_CutsceneFlags & 0x1000) {
            self->animCurFrame = 2;
            SetStep(13);
        }
        break;
    case 13:
        break;
    case 16:
        AnimateEntity(D_us_801812D0, self);
        if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
            self->velocityY += FIX(3.0 / 8);
            if (self->velocityY > FIX(7)) {
                self->velocityY = FIX(7);
            }
            MoveEntity();
            GetPlayerCollisionWith(self, 16, 12, 0x12);
        } else {
            if (PLAYER.step == Player_HighJump && PLAYER.step_s == 0) {
                PLAYER.step_s = 1;
                PLAYER.velocityY = FIX(-8);
            }
            self->posY.i.hi = player->posY.i.hi - 0x1C;
            self->velocityY = player->velocityY;
        }
        if ((self->posY.i.hi + tilemap->scrollY.i.hi) >= 172) {
            self->posY.i.hi = 172 - tilemap->scrollY.i.hi;
            self->animCurFrame = 2;
            SetStep(1);
        }
        break;
    case 255:
        if (g_pads[0].tapped & PAD_UP) {
            if (self->ext.libraryChair.debugAnimID) {
                self->ext.libraryChair.debugAnimID--;
                self->pose = 0;
                self->poseTimer = 0;
            }
        } else if (g_pads[0].tapped & PAD_DOWN) {
            if (self->ext.libraryChair.debugAnimID != 0x10) {
                self->ext.libraryChair.debugAnimID++;
                self->pose = 0;
                self->poseTimer = 0;
            }
        }
        AnimateEntity(D_us_801812D8[self->ext.libraryChair.debugAnimID], self);
        break;
    }
}

#ifdef VERSION_PSP
extern const char** D_us_80181310;
#else
extern const char* D_us_80181310[] = {
    "\003"
    "Buy item",
    "\003"
    "Tactics",
    "\001"
    "Enemy list",
    "\001"
    "Sound test",
    "\006"
    "Exit",
    "\003"
    "Sell gem"};
#endif

static u8 D_us_80181328[] = {4, 0, 5, 1, 4};
static u8 D_us_80181330[] = {5, 0, 5, 1, 2, 4};
static u8 D_us_80181338[] = {6, 0, 5, 1, 2, 3, 4};
static u8* D_us_80181340[] = {D_us_80181328, D_us_80181330, D_us_80181338};

static InventoryItem D_us_8018134C[] = {
    // clang-format off
    { INVENTORY_RELIC,     0xFF, 0x0000,              500 }, // special case: Jewel of Open
    { INVENTORY_HAND,      0,    ITEM_POTION,         800 },
    { INVENTORY_HAND,      3,    ITEM_HIGH_POTION,    2000 },
    { INVENTORY_HAND,      5,    ITEM_ELIXIR,         8000 },
    { INVENTORY_HAND,      3,    ITEM_MANNA_PRISM,    4000 },
    { INVENTORY_HAND,      0,    ITEM_ANTIVENOM,      200 },
    { INVENTORY_HAND,      0,    ITEM_UNCURSE,        200 },
    { INVENTORY_HAND,      0,    ITEM_HAMMER,         200 },
    { INVENTORY_HAND,      0,    ITEM_MAGIC_MISSILE,  300 },
    { INVENTORY_HAND,      0,    ITEM_BWAKA_KNIFE,    400 },
    { INVENTORY_HAND,      1,    ITEM_BOOMERANG,      500 },
    { INVENTORY_HAND,      3,    ITEM_JAVELIN,        800 },
    { INVENTORY_HAND,      4,    ITEM_FIRE_BOOMERANG, 1000 },
    { INVENTORY_HAND,      4,    ITEM_SHURIKEN,       2400 },
    { INVENTORY_HAND,      6,    ITEM_CROSS_SHURIKEN, 5000 },
    { INVENTORY_HAND,      7,    ITEM_BUFFALO_STAR,   8000 },
    { INVENTORY_HAND,      7,    ITEM_FLAME_STAR,     15000 },
    { INVENTORY_HAND,      0,    ITEM_LIBRARY_CARD,   500 },
    { INVENTORY_HAND,      8,    ITEM_MEAL_TICKET,    2000 },
    { INVENTORY_HAND,      0,    ITEM_SABER,          1500 },
    { INVENTORY_HAND,      0,    ITEM_MACE,           2000 },
    { INVENTORY_HAND,      0,    ITEM_DAMASCUS_SWORD, 4000 },
    { INVENTORY_HAND,      5,    ITEM_FIREBRAND,      10000 },
    { INVENTORY_HAND,      5,    ITEM_ICEBRAND,       10000 },
    { INVENTORY_HAND,      5,    ITEM_THUNDERBRAND,   10000 },
    { INVENTORY_HAND,      5,    ITEM_HARPER,         12000 },
    { INVENTORY_HAND,      0,    ITEM_LEATHER_SHIELD, 400 },
    { INVENTORY_HAND,      0,    ITEM_IRON_SHIELD,    3980 },
    { INVENTORY_HEAD,      0,    ITEM_VELVET_HAT,     400 },
    { INVENTORY_HEAD,      0,    ITEM_LEATHER_HAT,    1000 },
    { INVENTORY_HEAD,      0,    ITEM_CIRCLET,        4000 },
    { INVENTORY_HEAD,      5,    ITEM_SILVER_CROWN,   12000 },
    { INVENTORY_BODY,      0,    ITEM_IRON_CUIRASS,   1500 },
    { INVENTORY_BODY,      0,    ITEM_STEEL_CUIRASS,  4000 },
    { INVENTORY_BODY,      0,    ITEM_DIAMOND_PLATE,  12000 },
    { INVENTORY_CAPE,      0,    ITEM_REVERSE_CLOAK,  2000 },
    { INVENTORY_CAPE,      0,    ITEM_ELVEN_CLOAK,    3000 },
    { INVENTORY_CAPE,      0,    ITEM_JOSEPHS_CLOAK,  30000 },
    { INVENTORY_ACCESSORY, 0,    ITEM_MEDAL,          3000 },
    { INVENTORY_ACCESSORY, 1,    ITEM_RING_OF_PALES,  4000 },
    { INVENTORY_ACCESSORY, 4,    ITEM_GAUNTLET,       8000 },
    { INVENTORY_ACCESSORY, 8,    ITEM_DUPLICATOR,     500000 },
    { INVENTORY_DOCUMENT,  0x80, DOC_CASTLE_MAP,      103 },
    { INVENTORY_DOCUMENT,  0x81, DOC_MAGIC_SCROLL_1,  500 },
    { INVENTORY_DOCUMENT,  0x82, DOC_MAGIC_SCROLL_2,  1500 },
    { INVENTORY_DOCUMENT,  0x83, DOC_MAGIC_SCROLL_3,  5000 },
    { INVENTORY_DOCUMENT,  0x84, DOC_MAGIC_SCROLL_4,  8000 },
    { INVENTORY_DOCUMENT,  0x85, DOC_MAGIC_SCROLL_5,  15000 },
    { INVENTORY_DOCUMENT,  0,    0x000A,              1000000 },
    // clang-format on
};

/// relic index
u16 D_us_801814D4[] = {16, 0};

// sellable items
ShopItem D_us_801814D8[] = {
    // clang-format off
    { INVENTORY_ACCESSORY, ITEM_ZIRCON,     150 },
    { INVENTORY_ACCESSORY, ITEM_AQUAMARINE, 800 },
    { INVENTORY_ACCESSORY, ITEM_TURQUOISE,  1500 },
    { INVENTORY_ACCESSORY, ITEM_ONYX,       3000 },
    { INVENTORY_ACCESSORY, ITEM_GARNET,     5000 },
    { INVENTORY_ACCESSORY, ITEM_OPAL,       8000 },
    { INVENTORY_ACCESSORY, ITEM_DIAMOND,    20000 },
    // clang-format on
};

// magic scroll index to spell ID
static u16 D_us_80181510[] = {
    // clang-format off
    SPELL_DARK_METAMORPHOSIS,
    SPELL_SUMMON_SPIRIT,
    SPELL_HELLFIRE,
    SPELL_TETRA_SPIRIT,
    SPELL_SOUL_STEAL,
    // clang-format on
};

static u16 D_us_8018151C[] = {0, 1, 2, 5, 6};

#ifdef VERSION_PSP
extern u8* OVL_EXPORT(cutscene_data_offset_four);
#else
extern u8 D_us_80183F64;
#endif

void* func_us_801B0C40(u8* pix, const char* str, s32 x, s32 y, s32 size) {
    const u16 DOUBLE_SPACE = 0x8140;
    const u16 RIGHT_DOUBLE_QUOTATION_MARK = 0x8168;

    const int FontWidth = 12;
    const int FontHeight = 16;
    const int FontStride = FontWidth / 2;

    s32 letterWidth;
    s32 i, j;
    s32 pos;
    s32 s_8;
    s32 s_6;
    u16 ch;
    u8* ptr;
    u8* chPix;
    u8 sp3f;

    s_6 = 0;
    ptr = pix;
    for (i = 0; i < (size * FontHeight) * 2; i++) {
        *ptr++ = 0;
    }
    while (true) {
        pos = 0;
        while (*str >= 8) {
            s_8 = 0;
#ifdef VERSION_PSP
            ch = g_api.func_psp_0913F960((char*)str, &sp3f);
#else
            ch = *str;
#endif
            str++;
            if (ch == '@') {
                break;
            }
            if (ch >= 'a' && ch <= 'z') {
                ch = ch + 0x8220;
            } else if (ch >= 'A' && ch <= 'Z') {
                ch = ch + 0x821F;
            } else if (ch == ' ') {
                ch = DOUBLE_SPACE;
                s_8 = 2;
            } else {
#ifdef VERSION_PSP
                if (sp3f > 1) {
                    str += sp3f - 1;
                }
            }
            chPix = (u8*)g_api.func_psp_0913FA28(ch, 1);
#else
                ch = *str++ | (ch << 8);
                if (ch == DOUBLE_SPACE) {
                    s_8 = 2;
                }
            }
            if (ch == RIGHT_DOUBLE_QUOTATION_MARK) {
                str += 2;
            }
            chPix = (u8*)g_api.func_80106A28(ch, 1);
#endif
            while (true) {
                if (ch == DOUBLE_SPACE) {
                    break;
                }
                for (i = 0; i < FontHeight; i++) {
                    if (chPix[i * FontStride]) {
                        break;
                    }
                }
                if (i != 16) {
                    break;
                }
                for (i = 0; i < FontHeight; i++) {
                    ptr = &chPix[i * FontStride];
                    for (j = 0; j < 5; j++) {
                        *(ptr + 0) = *(ptr + 1);
                        ptr += 1;
                    }
                    *ptr = 0;
                }
            }

            for (i = 0, letterWidth = 0; i < FontHeight; i++) {
                for (j = 0; j < FontStride; j++) {
                    if (chPix[i * FontStride + j] && (letterWidth < j)) {
                        letterWidth = j;
                    }
                }
            }
            for (i = 0; i < FontHeight; i++) {
                if (chPix[letterWidth + i * FontStride] & 0xF0) {
                    break;
                }
            }

            if (i != 16) {
                letterWidth++;
            }
            if (letterWidth < 6) {
                letterWidth++;
            }
            for (i = 0; i < FontHeight; i++) {
                ptr = &pix[pos + (i + (s_6 * FontHeight)) * size];
                *ptr++ = *chPix++;
                *ptr++ = *chPix++;
                *ptr++ = *chPix++;
                *ptr++ = *chPix++;
                *ptr++ = *chPix++;
                *ptr++ = *chPix++;
            }
            pos += letterWidth + s_8;
            if (pos >= size - 5) {
                break;
            }
        }
        LoadTPage(
            (u_long*)&pix[s_6 * FontHeight * size], 0, 0, x, y, size * 2, 0x10);
        if (!*str) {
            break;
        }
        s_6++;
        y += FontHeight;
        if (*str < 8) {
            str++;
        }
    }
    return &pix[(size << 4) << 1];
}

void func_us_801B0FBC(const char* str, u16 x, u16 y) {
    RECT rect;
    char ch;

loop:
    ch = *str++;
    if (ch) {
        if (ch == ' ') {
            x++;
            goto loop;
#ifdef VERSION_PSP
        } else if (ch == 0xCC) {
            ch = 0xBB;
#endif
        }
        rect.x = ((ch & 0x0F) << 1) + 0x380;
        rect.y = ((ch & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
        MoveImage(&rect, x, y);
        x += 2;
        goto loop;
    }
}

Primitive* func_us_801B1064(
    Primitive* prim, s16 x, s16 y, const char* str, u16 clut) {
    char buffer[64];
    u16 length;
    s32 i;
    char ch;
    char* chPtr;

    chPtr = buffer;
    length = 0;
    for (i = 0; i < 64; i++) {
        *chPtr++ = 0;
    }
    chPtr = buffer;
    while (true) {
        ch = *str++;
        if (ch == 0xFF) {
            ch = *str++;
            if (ch == 0) {
                break;
            }
        }
        *chPtr++ = ch;
        length++;
#ifdef VERSION_PSP
        ch = *str;
        if (ch == 0xFF) {
            str++;
            ch = *str++;
            if (ch == 0) {
                break;
            }
            if (ch != 0xFF) {
                *chPtr = ch;
            } else {
                str -= 2;
            }
        }
        chPtr++;
#endif
    }
    chPtr = buffer;
    if (!length) {
        return prim;
    }
    do {
        ch = *chPtr++;
#ifdef VERSION_PSP
        if (ch) {
            prim->clut = clut;
            prim->u0 = (s8)((ch & 0x0F) << 3);
            prim->v0 = (s8)((ch & 0xF0) >> 1);
            prim->drawMode = DRAW_DEFAULT;
            prim->x0 = x;
            prim->y0 = y;
            prim = prim->next;
        }
        ch = *chPtr++;
        if (ch) {
            prim->clut = clut;
            prim->u0 = (s8)((ch & 0x0F) << 3);
            prim->v0 = (s8)((ch & 0xF0) >> 1);
            prim->drawMode = DRAW_DEFAULT;
            prim->x0 = x;
            prim->y0 = y - 8;
            prim = prim->next;
        }
        if (ch >= 0xF0 && ch <= 0xFC) {
            x += 12;
        } else {
            x += 8;
        }
#else
        if (ch) {
            prim->clut = clut;
            prim->u0 = (s8)((ch & 0x0F) << 3);
            prim->v0 = (s8)((ch & 0xF0) >> 1);
            prim->drawMode = DRAW_DEFAULT;
            if (ch == CH('i') || ch == CH('l') || ch == CH('f') ||
                ch == CH('I')) {
                x--;
            } else if (ch == CH('\'')) {
                x -= 2;
            }
            prim->x0 = x;
            prim->y0 = y;
            prim = prim->next;
            if (ch == CH('i') || ch == CH('l')) {
                x += 7;
            } else if (ch == CH('\'')) {
                x += 6;
            } else {
                x += 8;
            }
        } else {
            x += 4;
        }
#endif

    } while (--length);

    return prim;
}

void func_us_801B11A0(s16 x, s16 y, u16 w, u16 h) {
    RECT rect;

    rect.x = x / 4;
    rect.y = y;
    rect.w = w / 4 + 1;
    rect.h = h + 1;
    ClearImage(&rect, 0, 0, 0);
}

static void func_us_801B1200(Primitive* prim, Primitive* otherPrim) {
    prim->x0 = otherPrim->x0;
    prim->y0 = otherPrim->y0;
    prim->x1 = otherPrim->x1;
    prim->y1 = otherPrim->y1;
    prim->drawMode = DRAW_DEFAULT;

    prim = prim->next;
    prim->x0 = otherPrim->x1;
    prim->y0 = otherPrim->y1;
    prim->x1 = otherPrim->x3;
    prim->y1 = otherPrim->y3;
    prim->drawMode = DRAW_DEFAULT;

    prim = prim->next;
    prim->x0 = otherPrim->x0;
    prim->y0 = otherPrim->y0;
    prim->x1 = otherPrim->x2;
    prim->y1 = otherPrim->y2;
    prim->drawMode = DRAW_DEFAULT;

    prim = prim->next;
    prim->x0 = otherPrim->x2;
    prim->y0 = otherPrim->y2;
    prim->x1 = otherPrim->x3;
    prim->y1 = otherPrim->y3;
    prim->drawMode = DRAW_DEFAULT;
}

void func_us_801B12D0(Entity* self, u16 arg1) {
    Primitive* prim2;
    Primitive* prim;
    s16 s_4;
    s16 posY;
    s16 posX;
    s32 i;
    s16 s_3;
    s16 temp_v1;
    s16 var_s4;

    prim = &g_PrimBuf[g_CurrentEntity->primIndex];
    prim = prim->next;
    prim2 = prim;
    for (i = 0; i < 4; i++) {
        prim = prim->next;
    }
    i = 0;
    s_3 = g_CurrentEntity->ext.et_801B15C0.unk86;
    s_4 = g_CurrentEntity->ext.et_801B15C0.unk80 * 0x10;
#ifdef VERSION_PSP
    if (arg1) {
        posY = (g_CurrentEntity->ext.et_801B15C0.unk7C * ((s_3 + 0x18) - s_4)) /
               24;
        posX = (g_CurrentEntity->ext.et_801B15C0.unk7C * -0x88) / 24;
#else
    if (arg1 & 1) {
        posY = (g_CurrentEntity->ext.et_801B15C0.unk7C * ((s_3 + 0x18) - s_4)) /
               24;
        posX = (g_CurrentEntity->ext.et_801B15C0.unk7C * -0x98) / 24;
#endif
    } else {
        posY = (g_CurrentEntity->ext.et_801B15C0.unk7C * ((s_3 + 0x40) - s_4)) /
               24;
        posX = 0;
    }
#ifdef VERSION_PSP
    for (; prim != NULL; i++) {
        prim->x0 = prim->x2 = posX + 0x94;
        prim->x1 = prim->x3 = posX + 0xEC;
#else
    if (arg1 & 0x10) {
        s32 temp = g_CurrentEntity->ext.et_801B15C0.unk7C;
        var_s4 = temp / 3;
    } else {
        var_s4 = 0;
    }
    for (; prim != NULL; i++) {
        prim->x0 = prim->x2 = posX + 0x96 + var_s4;
        prim->x1 = prim->x3 = posX + 0xEA - var_s4;
        if (i != 0) {
            prim->u0 = prim->u2 = var_s4;
            prim->u1 = prim->u3 = 0x54 - var_s4;
        }
#endif
        temp_v1 = (g_CurrentEntity->ext.et_801B15C0.unk7C * (s_4 + 2)) / 24;
        if (i != 0) {
            prim->v0 = prim->v1 = temp_v1;
        }
        prim->y0 = prim->y1 = (0x60 - s_3) + temp_v1 + posY;
        temp_v1 = (g_CurrentEntity->ext.et_801B15C0.unk7C *
                   (s_3 * 2 - (s_4 + 0x15))) /
                  24;
        if (i != 0) {
            prim->v2 = prim->v3 = s_3 * 2 - temp_v1;
        }
        prim->y2 = prim->y3 = (s_3 + 0x60) - temp_v1 + posY;
        if (i == 0) {
            func_us_801B1200(prim2, prim);
        }
        prim = prim->next;
    }
}

void func_us_801B15C0(Entity* self) {
    Entity* tempEntity;
    Primitive* otherPrim;
    Primitive* prim;
    s32 primIndex;
    s16 tempVar;
    s32 i;
    u16 tempVar2;
    char* ptr;
    s16 pad;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        primIndex = g_api.AllocPrimitives(PRIM_G4, 7);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            if (g_IsTimeAttackUnlocked) {
#ifdef VERSION_PSP
                self->params = 3;
#else
                self->params = 2;
#endif
            } else {
                self->params = 1;
            }
            ptr = D_us_80181340[self->params];
            self->ext.et_801B15C0.unk84 = *ptr++;
            for (i = 0; i < self->ext.et_801B15C0.unk84; i++) {
                self->ext.et_801B15C0.unk88[i] = *ptr++;
            }
            self->ext.et_801B15C0.unk86 = (self->ext.et_801B15C0.unk84 * 8) + 4;
            i = 0;
            prim = &g_PrimBuf[primIndex];
            for (; prim != NULL; i++) {
                prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0xC0;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 = 0x60;
                if (i == 0) {
                    PRED(prim) = 0x40;
                    PGRN(prim) = 0x10;
                    PBLU(prim) = 0x10;
#ifdef VERSION_PSP
                    prim->x0 = prim->x2 = 0x95;
                    prim->x1 = prim->x3 = 0xEC;
#else
                    prim->x0 = prim->x2 = 0x98;
                    prim->x1 = prim->x3 = 0xE8;
#endif
                    prim->priority = 0xC0;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 5) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = prim->r1 = 0x80;
                    prim->g0 = prim->g1 = 0x80;
                    prim->b0 = prim->b1 = 0x80;
                    prim->priority = 0xC1;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 5) {
                    PRED(prim) = 0;
                    PGRN(prim) = 0;
                    PBLU(prim) = 0x40;
                    prim->priority = 0xBF;
                    prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                } else if (i == 6) {
                    prim->type = PRIM_GT4;
                    prim->tpage = 0x10;
                    prim->clut = 0x1A1;
                    prim->u0 = prim->u2 = 0;
#ifdef VERSION_PSP
                    prim->u1 = prim->u3 = 0x58;
#else
                    prim->u1 = prim->u3 = 0x54;
#endif
                    prim->v0 = prim->v1 = 0;
                    prim->v2 = prim->v3 = self->ext.et_801B15C0.unk86 * 2;
                    prim->priority = 0xC1;
                    prim->drawMode = DRAW_HIDE;
                }
                prim = prim->next;
            }
#ifdef VERSION_PSP
            func_us_801B11A0(0, 0x100, 0x58, self->ext.et_801B15C0.unk86 * 2);
#else
            func_us_801B11A0(0, 0x100, 0x54, self->ext.et_801B15C0.unk86 * 2);
#endif
            return;
        }
        self->step = 0;
        break;

    case 1:
        for (i = 0; i < self->ext.et_801B15C0.unk84; i++) {
            ptr = D_us_80181310[self->ext.et_801B15C0.unk88[i]];
            tempVar = *ptr++;
            func_us_801B0FBC(ptr, tempVar, 0x108 + i * 16);
        }
        self->step++;
        break;

    case 2:
        if (g_CutsceneFlags & 0x200) {
            SetStep(3);
            self->ext.et_801B15C0.unk7C = 0;
            self->ext.et_801B15C0.unk7E = 0;
            self->ext.et_801B15C0.unk80 = 0;
            g_Settings.D_8003CB04 |= 8;
        }
        break;

    case 3:
        self->ext.et_801B15C0.unk7C++;
        self->ext.et_801B15C0.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        otherPrim = prim;
        for (i = 0; i < 4; i++) {
            prim = prim->next;
        }
        i = 0;
        tempVar2 = self->ext.et_801B15C0.unk86;
        for (; prim != NULL; i++) {
#ifdef VERSION_PSP
            tempVar = (self->ext.et_801B15C0.unk7C * 0x2C) / 0x20;
            if (tempVar > 0x2C) {
                tempVar = 0x2C;
            }
#else
            tempVar = (self->ext.et_801B15C0.unk7C * 0x2A) / 0x20;
            if (tempVar > 0x2A) {
                tempVar = 0x2A;
            }
#endif
            prim->x1 = tempVar + 0xC0;
            prim->x2 = 0xC0 - tempVar;
            tempVar = self->ext.et_801B15C0.unk7C * tempVar2 / 0x20;
            if (tempVar > tempVar2) {
                tempVar = tempVar2;
            }
            prim->y1 = 0x60 - tempVar;
            prim->y2 = tempVar + 0x60;
#ifdef VERSION_PSP
            tempVar = ((s16)self->ext.et_801B15C0.unk7C * 0x2C) / 0x40;
#else
            tempVar = ((s16)self->ext.et_801B15C0.unk7C * 0x2A) / 0x40;
#endif
            tempVar = (rcos(self->ext.et_801B15C0.unk7E) * tempVar) / 0x1000;
            prim->x0 = 0xC0 - tempVar;
            prim->x3 = tempVar + 0xC0;
            tempVar = ((s16)self->ext.et_801B15C0.unk7C * tempVar2) / 0x40;
            tempVar = (rcos(self->ext.et_801B15C0.unk7E) * tempVar) / 0x1000;
            prim->y0 = 0x60 - tempVar;
            prim->y3 = tempVar + 0x60;
            if (self->ext.et_801B15C0.unk7E >= 0x400 &&
                self->ext.et_801B15C0.unk7E < 0xC00) {
                if (i) {
                    prim->priority = 0xBF;
                    prim->drawMode = DRAW_DEFAULT;
                } else {
                    prim->priority = 0xC1;
                }
            } else {
                if (i) {
                    prim->priority = 0xC1;
                } else {
                    prim->priority = 0xBF;
                }
            }
            if (i == 0) {
                func_us_801B1200(otherPrim, prim);
            }
            prim = prim->next;
        }
        if (self->ext.et_801B15C0.unk7C == 0x40) {
            SetStep(4);
        }
        break;

    case 4:
        pad = g_pads[0].repeat;
        if (pad & PAD_DOWN) {
            if (self->ext.et_801B15C0.unk80 < self->ext.et_801B15C0.unk84 - 1) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B15C0.unk80++;
            }
        } else if (pad & PAD_UP) {
            if (self->ext.et_801B15C0.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B15C0.unk80--;
            }
        }
        pad = g_pads[0].tapped;
#ifdef VERSION_PSP
        if (pad & D_psp_08B42050) {
#else
        if (pad & PAD_CROSS) {
#endif
            switch (self->ext.et_801B15C0.unk88[self->ext.et_801B15C0.unk80]) {
            case 0:
                g_CutsceneFlags |= 0x400;
                tempEntity = self + 1;
                CreateEntityFromCurrentEntity(E_ID(ID_27), tempEntity);
                tempEntity++;
                CreateEntityFromCurrentEntity(E_ID(ID_28), tempEntity);
                tempEntity++;
                CreateEntityFromCurrentEntity(E_ID(ID_29), tempEntity);
                tempEntity++;
                CreateEntityFromCurrentEntity(E_ID(ID_2A), tempEntity);
                SetStep(5);
                g_api.PlaySfx(SFX_UI_CONFIRM);
                break;

            case 1:
                g_CutsceneFlags |= 0x400;
                tempEntity = self + 1;
                CreateEntityFromCurrentEntity(E_ID(ID_2D), tempEntity);
                SetStep(5);
                g_api.PlaySfx(SFX_UI_CONFIRM);
                break;

            case 2:
                g_CutsceneFlags |= 0x400;
                tempEntity = self + 1;
                CreateEntityFromCurrentEntity(E_ID(ID_2E), tempEntity);
                SetStep(5);
                g_api.PlaySfx(SFX_UI_CONFIRM);
                break;

            case 3:
                g_CutsceneFlags |= 0x400;
                tempEntity = self + 1;
                CreateEntityFromCurrentEntity(E_ID(ID_48), tempEntity);
                SetStep(5);
                g_api.PlaySfx(SFX_UI_CONFIRM);
                break;

            case 4:
                SetStep(6);
                g_api.PlaySfx(SFX_UI_CONFIRM);
                break;

            case 5:
                g_CutsceneFlags |= 0x400;
                tempEntity = self + 1;
                CreateEntityFromCurrentEntity(E_ID(ID_27), tempEntity);
                tempEntity->params = 1;
                tempEntity++;
                CreateEntityFromCurrentEntity(E_ID(ID_28), tempEntity);
                tempEntity++;
                CreateEntityFromCurrentEntity(E_ID(ID_29), tempEntity);
                tempEntity++;
                CreateEntityFromCurrentEntity(E_ID(ID_2A), tempEntity);
                SetStep(5);
                g_api.PlaySfx(SFX_UI_CONFIRM);
                break;

#ifdef VERSION_PSP
            case 6:
                g_CutsceneFlags |= 0x400;
                tempEntity = self + 1;
                CreateEntityFromCurrentEntity(E_ID(ID_4F), tempEntity);
                SetStep(5);
                g_api.PlaySfx(SFX_UI_CONFIRM);
                break;
#endif
            }
#ifdef VERSION_PSP
        } else if (g_pads[0].tapped & D_psp_08B42054) {
#else
        } else if (g_pads[0].tapped & PAD_TRIANGLE) {
#endif
            SetStep(6);
            g_api.PlaySfx(SFX_UI_CONFIRM);
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->y0 = prim->y1 = (0x64 - self->ext.et_801B15C0.unk86) +
                              self->ext.et_801B15C0.unk80 * 0x10;
        prim->y2 = prim->y3 = prim->y0 + 0x10;
        prim->drawMode = DRAW_COLORS;
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            if (g_api.func_80131F68()) {
                g_api.PlaySfx(SET_STOP_MUSIC);
                self->step_s++;
            } else {
                self->step_s++;
            }
            break;

        case 1:
            if (!g_api.func_80131F68()) {
                if (self->ext.et_801B15C0.unk80 != 4) {
                    g_api.PlaySfx(NA_VO_AL_INTERESTED);
                }
                if (!self->ext.et_801B15C0.unk80 ||
                    self->ext.et_801B15C0.unk80 == 1) {
                    self->ext.et_801B15C0.unk82 = 1;
                } else {
                    self->ext.et_801B15C0.unk82 = 0;
                }
#ifndef VERSION_PSP
                if (self->ext.et_801B15C0.unk80 < 3) {
                    self->ext.et_801B15C0.unk82 |= 0x10;
                }
#endif
                SetStep(9);
            }
            break;
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
#ifdef VERSION_PSP
            *OVL_EXPORT(cutscene_data_offset_four) = 0;
#else
            D_us_80183F64 = 0;
#endif
            if (g_api.func_80131F68()) {
                g_api.PlaySfx(SET_STOP_MUSIC);
                self->step_s++;
            } else {
                self->step_s++;
            }
            break;

        case 1:
            if (!g_api.func_80131F68()) {
                g_api.PlaySfx(NA_VO_ML_FAREWELL);
                self->ext.et_801B15C0.unk7C = 0x20;
                self->step_s++;
            }
            break;

        case 2:
            if (!--self->ext.et_801B15C0.unk7C) {
                SetStep(7);
                g_CutsceneFlags |= 0x100;
                g_PauseAllowed = true;
                g_unkGraphicsStruct.pauseEnemies = 0;
            }
            break;
        }
        break;

    case 7:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode = DRAW_HIDE;
        self->ext.et_801B15C0.unk7E = 0;
        self->ext.et_801B15C0.unk7C = 0x40;
        self->step++;
        break;

    case 8:
        self->ext.et_801B15C0.unk7C--;
        self->ext.et_801B15C0.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        otherPrim = prim;
        for (i = 0; i < 4; i++) {
            prim = prim->next;
        }
        i = 0;
        tempVar2 = self->ext.et_801B15C0.unk86;
        for (; prim != NULL; i++) {
#ifdef VERSION_PSP
            tempVar = (self->ext.et_801B15C0.unk7C * 0x2C) / 0x20;
            if (tempVar > 0x2C) {
                tempVar = 0x2C;
            }
#else
            tempVar = (self->ext.et_801B15C0.unk7C * 0x2A) / 0x20;
            if (tempVar > 0x2A) {
                tempVar = 0x2A;
            }
#endif
            prim->x3 = tempVar + 0xC0;
            prim->x0 = 0xC0 - tempVar;
            tempVar = (self->ext.et_801B15C0.unk7C * tempVar2) / 0x20;
            if (tempVar > tempVar2) {
                tempVar = tempVar2;
            }
            prim->y0 = 0x60 - tempVar;
            prim->y3 = tempVar + 0x60;
#ifdef VERSION_PSP
            tempVar = ((s16)self->ext.et_801B15C0.unk7C * 0x2C) / 0x40;
#else
            tempVar = ((s16)self->ext.et_801B15C0.unk7C * 0x2A) / 0x40;
#endif
            tempVar = rcos(self->ext.et_801B15C0.unk7E) * tempVar / 0x1000;
            prim->x2 = 0xC0 - tempVar;
            prim->x1 = tempVar + 0xC0;
            tempVar = ((s16)self->ext.et_801B15C0.unk7C * tempVar2) / 0x40;
            tempVar = rcos(self->ext.et_801B15C0.unk7E) * tempVar / 0x1000;
            prim->y1 = 0x60 - tempVar;
            prim->y2 = tempVar + 0x60;
            if (self->ext.et_801B15C0.unk7E >= 0x400 &&
                self->ext.et_801B15C0.unk7E < 0xC00) {
                if (i) {
                    prim->priority = 0xBF;
                } else {
                    prim->priority = 0xC1;
                }
            } else if (i) {
                prim->priority = 0xC1;
                if (self->ext.et_801B15C0.unk7E >= 0xC00) {
                    prim->drawMode = DRAW_HIDE;
                }
            } else {
                prim->priority = 0xBF;
            }
            if (i == 0) {
                if (self->ext.et_801B15C0.unk7C) {
                    func_us_801B1200(otherPrim, prim);
                } else {
                    otherPrim->drawMode = DRAW_HIDE;
                    otherPrim = otherPrim->next;
                    otherPrim->drawMode = DRAW_HIDE;
                    otherPrim = otherPrim->next;
                    otherPrim->drawMode = DRAW_HIDE;
                    otherPrim = otherPrim->next;
                    otherPrim->drawMode = DRAW_HIDE;
                }
            }
            prim = prim->next;
        }
        if (!self->ext.et_801B15C0.unk7C) {
            g_CutsceneFlags &= ~0x200;
            SetStep(2);
        }
        break;

    case 9:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode = DRAW_HIDE;
        self->ext.et_801B15C0.unk7C = 0;
        self->step++;
        break;

    case 10:
        self->ext.et_801B15C0.unk7C++;
        func_us_801B12D0(self, self->ext.et_801B15C0.unk82);
        if (self->ext.et_801B15C0.unk7C >= 0x18) {
            g_CutsceneFlags &= ~0x200;
            SetStep(11);
        }
        break;

    case 11:
        if (g_CutsceneFlags & 0x200) {
            SetStep(12);
            self->ext.et_801B15C0.unk7C = 0x18;
        }
        break;

    case 12:
        self->ext.et_801B15C0.unk7C--;
        func_us_801B12D0(self, self->ext.et_801B15C0.unk82);
        if (!self->ext.et_801B15C0.unk7C) {
            SetStep(4);
        }
        break;
    }
}

void func_us_801B245C(Primitive* arg0, u16 arg1, u16 arg2, u16 arg3, u16 arg4,
                      s32 arg5, s32 arg6) {
    Primitive* prim;
    s16 i;
    s16 offset;

    prim = arg0;
    for (i = 0; i < 6; i++) {
        arg0 = arg0->next;
    }
    for (i = 0; i < 2; i++) {
        offset = (rsin(arg1) * arg3) / 0x1000;
        if (i) {
            arg0->x1 = arg0->x3 = arg0->x0 + offset;
            if (arg5 & 1) {
                arg0->r0 = arg0->r1 = (arg2 / 2) + 0x30;
            } else {
                arg0->r0 = arg0->r1 = 0;
            }
            if (arg5 & 2) {
                arg0->r2 = arg0->r3 = (arg2 / 2) + 0x30;
            } else {
                arg0->r2 = arg0->r3 = 0;
            }
            if (arg5 & 4) {
                arg0->g0 = arg0->g1 = (arg2 / 2) + 0x30;
            } else {
                arg0->g0 = arg0->g1 = 0;
            }
            if (arg5 & 8) {
                arg0->g2 = arg0->g3 = (arg2 / 2) + 0x30;
            } else {
                arg0->g2 = arg0->g3 = 0;
            }
            if (arg5 & 0x10) {
                arg0->b0 = arg0->b1 = (arg2 / 2) + 0x30;
            } else {
                arg0->b0 = arg0->b1 = 0;
            }
            if (arg5 & 0x20) {
                arg0->b2 = arg0->b3 = (arg2 / 2) + 0x30;
            } else {
                arg0->b2 = arg0->b3 = 0;
            }
        } else {
            arg0->x0 = arg0->x2 = arg0->x1 - offset;
            if (arg5 & 1) {
                arg0->r0 = arg0->r1 = arg2 + 0x20;
            } else {
                arg0->r0 = arg0->r1 = 0;
            }
            if (arg5 & 2) {
                arg0->r2 = arg0->r3 = arg2 + 0x20;
            } else {
                arg0->r2 = arg0->r3 = 0;
            }
            if (arg5 & 4) {
                arg0->g0 = arg0->g1 = arg2 + 0x20;
            } else {
                arg0->g0 = arg0->g1 = 0;
            }
            if (arg5 & 8) {
                arg0->g2 = arg0->g3 = arg2 + 0x20;
            } else {
                arg0->g2 = arg0->g3 = 0;
            }
            if (arg5 & 0x10) {
                arg0->b0 = arg0->b1 = arg2 + 0x20;
            } else {
                arg0->b0 = arg0->b1 = 0;
            }
            if (arg5 & 0x20) {
                arg0->b2 = arg0->b3 = arg2 + 0x20;
            } else {
                arg0->b2 = arg0->b3 = 0;
            }
        }
        offset = (arg4 * rcos(g_CurrentEntity->ext.et_801B6F30.unk7E)) / 0x1000;
        if (i) {
            arg0->y1 = arg0->y0 - offset;
            arg0->y3 = arg0->y2 + offset;
            prim->x0 = arg0->x1;
            prim->y0 = arg0->y1;
            prim->x1 = arg0->x3;
            prim->y1 = arg0->y3;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        } else {
            arg0->y0 = arg0->y1 - offset;
            arg0->y2 = arg0->y3 + offset;
            prim->x0 = arg0->x0;
            prim->y0 = arg0->y0;
            prim->x1 = arg0->x2;
            prim->y1 = arg0->y2;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        prim->x0 = arg0->x0;
        prim->y0 = arg0->y0;
        prim->x1 = arg0->x1;
        prim->y1 = arg0->y1;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;

        prim->x0 = arg0->x2;
        prim->y0 = arg0->y2;
        prim->x1 = arg0->x3;
        prim->y1 = arg0->y3;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;

        if (arg6) {
            arg0->drawMode =
                DRAW_UNK_400 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        } else {
            arg0->drawMode = DRAW_UNK_400 | DRAW_COLORS;
        }
        arg0 = arg0->next;
    }
    for (i = 0; i < 2; i++) {
        offset = (rsin(arg1) * (arg3 - 8)) / 0x1000;
        if (i) {
            arg0->x1 = arg0->x3 = arg0->x0 + offset;
        } else {
            arg0->x0 = arg0->x2 = arg0->x1 - offset;
        }
        offset = (arg4 * rcos(arg1) * 3) / 0x4000;
        if (i) {
            arg0->y1 = arg0->y0 - offset;
            arg0->y3 = arg0->y2 + offset;
            PRED(arg0) = arg2 + 0x60;
            PGRN(arg0) = arg2 + 0x60;
            PBLU(arg0) = arg2 + 0x60;
        } else {
            arg0->y0 = arg0->y1 - offset;
            arg0->y2 = arg0->y3 + offset;
            PRED(arg0) = (arg2 * 2) + 0x40;
            PGRN(arg0) = (arg2 * 2) + 0x40;
            PBLU(arg0) = (arg2 * 2) + 0x40;
        }
#ifdef VERSION_PSP
        if (arg1 == 0x400) {
            if (i) {
                arg0->x1 = arg0->x3 = arg0->x0 + (arg0->u1 - arg0->u0);
            } else {
                arg0->x0 = arg0->x2 = arg0->x1 - (arg0->u1 - arg0->u0);
            }
            arg0->y2 = arg0->y3 = arg0->y0 + (arg0->v2 - arg0->v0);
        }
        arg0->drawMode = DRAW_DEFAULT;
#else
        arg0->drawMode = DRAW_COLORS;
#endif
        arg0 = arg0->next;
    }
}

u16 func_us_801B29C4(void) {
    InventoryItem* currentItem;
    ShopItem* shopItem;
    u8 itemLevel;
    u16 unlockLevel;
    u8 itemCount;
    s32 i;
    u8 spellIndex;

    shopItem = D_us_801D4364;
    currentItem = D_us_8018134C;
    unlockLevel = 0;
    if (g_CastleFlags[MET_MARIA_AFTER_HIPPOGRYPH]) {
        unlockLevel++;
    }
    if (g_CastleFlags[RICHTER_CS_AFTER_M_AND_W]) {
        unlockLevel++;
    }
    if (g_Status.relics[RELIC_SOUL_OF_BAT] & 1) {
        unlockLevel++;
    }
    if (g_CastleFlags[MET_MARIA_IN_CEN]) {
        unlockLevel++;
    }
    if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED]) {
        unlockLevel++;
    }
    if (g_CastleFlags[DEATH_FIGHT_CS]) {
        unlockLevel++;
    }
    if (g_api.TimeAttackController(
            TIMEATTACK_EVENT_GALAMOTH_DEFEAT, TIMEATTACK_GET_RECORD)) {
        unlockLevel++;
    }
    if (g_IsTimeAttackUnlocked) {
        unlockLevel = 8;
    }
    itemCount = 0;
    for (i = 0; i < LEN(D_us_8018134C) - 1; i++) {
        itemLevel = currentItem->unlockLevel;
        switch (itemLevel) {
        case 0xFF:
            if ((g_Status.relics[RELIC_JEWEL_OF_OPEN] & 1) == 0) {
                itemLevel = 0;
            }
            break;

        case 0x80:
            if (!g_CastleFlags[BOUGHT_CASTLE_MAP]) {
                itemLevel = 0;
            }
            break;

#ifdef VERSION_PSP
        case 0x86:
        case 0x87:
        case 0x88:
            if (itemLevel == 0x86) {
                if ((g_Status.relics[RELIC_SOUL_OF_WOLF] & 1) == 0) {
                    itemLevel = 0xFF;
                    break;
                }
                if ((g_Status.relics[RELIC_SKILL_OF_WOLF] & 1) == 0) {
                    itemLevel = 0xFF;
                    break;
                }
            } else if (itemLevel == 0x87) {
                if ((g_Status.relics[RELIC_SOUL_OF_BAT] & 1) == 0) {
                    itemLevel = 0xFF;
                    break;
                }
            } else if (itemLevel == 0x88) {
                if ((g_Status.relics[RELIC_SWORD_CARD] & 1) == 0) {
                    itemLevel = 0xFF;
                    break;
                }
                if (g_Status.statsFamiliars[FAM_STATS_SWORD].level < 50) {
                    itemLevel = 0xFF;
                    break;
                }
            }
#endif
        case 0x81:
        case 0x82:
        case 0x83:
        case 0x84:
        case 0x85:
            itemLevel -= 0x81;
            spellIndex = D_us_80181510[itemLevel];
            if (g_Status.spellsLearnt & (1 << spellIndex)) {
                itemLevel = 0xFF;
            } else {
                itemLevel = D_us_8018151C[itemLevel];
            }
            break;
        }
        if (itemLevel <= unlockLevel) {
            shopItem->category = currentItem->category;
            shopItem->itemId = currentItem->itemId;
            shopItem->price = currentItem->price;
            shopItem++;
            itemCount++;
        }
        currentItem++;
    }
    return itemCount - 7;
}

void func_us_801B2BE4(Entity* self) {
    Primitive* prim;
    s32 i;
    s16 itemId;
    s16 tempVar;
    ShopItem* ptr;
    s32 primIndex;

#ifndef VERSION_PSP
    if (g_CastleFlags[MET_MARIA_AFTER_HIPPOGRYPH]) {
        FntPrint("HIP ");
    }
    if (g_CastleFlags[RICHTER_CS_AFTER_M_AND_W]) {
        FntPrint("ARE ");
    }
    if (g_Status.relics[RELIC_SOUL_OF_BAT] & RELIC_FLAG_FOUND) {
        FntPrint("BAT ");
    }
    if (g_CastleFlags[MET_MARIA_IN_CEN]) {
        FntPrint("CEN ");
    }
    if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED]) {
        FntPrint("REV ");
    }
    if (g_CastleFlags[DEATH_FIGHT_CS]) {
        FntPrint("DET ");
    }
    if (g_api.TimeAttackController(
            TIMEATTACK_EVENT_GALAMOTH_DEFEAT, TIMEATTACK_GET_RECORD)) {
        FntPrint("GAR ");
    }
    FntPrint("\n");
#endif

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 0xD);
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            while (prim != NULL) {
                if (i < 6) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = prim->r1 = 0x80;
                    prim->g0 = prim->g1 = 0x80;
                    prim->b0 = prim->b1 = 0x80;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 8) {
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x18;
                    prim->y2 = prim->y3 = 0x78;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 10) {
                    prim->type = PRIM_GT4;
#ifdef VERSION_PSP
                    prim->tpage = 0x110;
#else
                    prim->tpage = 0x114;
#endif
                    prim->u0 = prim->u2 = (i - 8) * 0x6C + 8;
                    prim->u1 = prim->u3 = prim->u0 + 0x6C;
                    prim->v0 = prim->v1 = 0xD;
                    prim->v2 = prim->v3 = 0x61;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x1E;
                    prim->y2 = prim->y3 = 0x72;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 10) {
                    prim->x0 = prim->x2 = 0x11;
                    prim->x1 = prim->x3 = 0xEF;
                    prim->y0 = prim->y1 = 0x2B;
                    prim->y2 = prim->y3 = 0x37;
                    PRED(prim) = 0x40;
                    PGRN(prim) = 0x10;
                    PBLU(prim) = 0x10;
                    prim->priority = 0x1FB;
                    prim->drawMode = DRAW_HIDE;
                } else {
                    prim->type = PRIM_GT4;
                    prim->tpage = 0x1E;
                    prim->clut = 0x17F;
                    prim->u0 = prim->u2 = 0x58;
                    prim->u1 = prim->u3 = 0x60;
                    prim->v0 = prim->v1 = (i - 11) * 8 + 0x70;
                    prim->v2 = prim->v3 = 0x78 - (i - 11) * 8;
                    prim->x0 = prim->x2 = 0x7C;
                    prim->x1 = prim->x3 = prim->x0 + 8;
                    prim->y0 = prim->y1 = (i - 11) * 0x60 + 0x14;
                    prim->y2 = prim->y3 = prim->y0 + 8;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                }
                prim = prim->next;
                i++;
            }
        }
        break;

    case 1:
        if (g_CutsceneFlags & 0x400) {
            SetStep(2);
            if (self->params) {
                // if showing the selling menu
                ptr = D_us_801814D8;
            } else {
                // if showing the buying menu
                self->ext.et_801B6F30.unk88 = func_us_801B29C4();
                ptr = D_us_801D4364;
            }
            for (i = 0; i < LEN(D_us_801D425C); i++) {
                itemId = ptr->itemId;
                switch (ptr->category) {
                case INVENTORY_HAND:
                    tempVar = g_Status.equipHandCount[itemId];
                    if (g_Status.equipment[LEFT_HAND_SLOT] == itemId) {
                        tempVar++;
                    }
                    if (g_Status.equipment[RIGHT_HAND_SLOT] == itemId) {
                        tempVar++;
                    }
                    D_us_801D425C[i] = 99 - tempVar;
                    break;

                case INVENTORY_HEAD:
                    tempVar = g_Status.equipBodyCount[itemId];
                    if (g_Status.equipment[HEAD_SLOT] == itemId) {
                        tempVar++;
                    }
                    D_us_801D425C[i] = 99 - tempVar;
                    break;

                case INVENTORY_BODY:
                    tempVar = g_Status.equipBodyCount[itemId];
                    if (g_Status.equipment[ARMOR_SLOT] == itemId) {
                        tempVar++;
                    }
                    D_us_801D425C[i] = 99 - tempVar;
                    break;

                case INVENTORY_CAPE:
                    tempVar = g_Status.equipBodyCount[itemId];
                    if (g_Status.equipment[CAPE_SLOT] == itemId) {
                        tempVar++;
                    }
                    D_us_801D425C[i] = 99 - tempVar;
                    break;

                case INVENTORY_ACCESSORY:
                    tempVar = g_Status.equipBodyCount[itemId];
                    if (self->params) {
                        D_us_801D425C[i] = tempVar;
                    } else {
                        if (g_Status.equipment[ACCESSORY_1_SLOT] == itemId) {
                            tempVar++;
                        }
                        if (g_Status.equipment[ACCESSORY_2_SLOT] == itemId) {
                            tempVar++;
                        }
                        D_us_801D425C[i] = 99 - tempVar;
                        break;
                    }
                    break;

                case INVENTORY_RELIC:
                    itemId = D_us_801814D4[itemId];
                    if (g_Status.relics[itemId] & RELIC_FLAG_FOUND) {
                        D_us_801D425C[i] = 0;
                    } else {
                        D_us_801D425C[i] = 1;
                    }
                    break;

                default:
                    D_us_801D425C[i] = 1;
                    break;
                }
                if (D_us_801D425C[i]) {
                    D_us_801D415C[i] = 1;
                } else {
                    D_us_801D415C[i] = 0;
                }
                ptr++;
            }
            self->ext.et_801B6F30.unk7C = 0;
            self->ext.et_801B6F30.unk7E = 0;
            self->ext.et_801B6F30.unk80 = 0;
            self->ext.et_801B6F30.unk82 = 0;
        }
        break;

    case 2:
        self->ext.et_801B6F30.unk7C++;
        self->ext.et_801B6F30.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x74, 0x20, 8, 1);
        if (self->ext.et_801B6F30.unk7C == 0x10) {
            if (self->params) {
                SetStep(5);
            } else {
                SetStep(3);
            }
        }
        break;

    case 3:
        tempVar = g_pads[0].repeat;
        FntPrint("kosuu %x\n", self->ext.et_801B6F30.unk82);
        if (tempVar & PAD_DOWN) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80++;
            } else if (
                self->ext.et_801B6F30.unk82 < self->ext.et_801B6F30.unk88) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82++;
            }
        } else if (tempVar & PAD_UP) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80--;
            } else if (self->ext.et_801B6F30.unk82) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82--;
            }
        } else if (tempVar & (PAD_R1 | PAD_R2)) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80 = 6;
            } else if (
                self->ext.et_801B6F30.unk82 < self->ext.et_801B6F30.unk88) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82 += 7;
                if (self->ext.et_801B6F30.unk82 > self->ext.et_801B6F30.unk88) {
                    self->ext.et_801B6F30.unk82 = self->ext.et_801B6F30.unk88;
                }
            }
        } else if (tempVar & (PAD_L1 | PAD_L2)) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80 = 0;
            } else if (self->ext.et_801B6F30.unk82) {
                g_api.PlaySfx(SFX_UI_MOVE);
                if (self->ext.et_801B6F30.unk82 > 7) {
                    self->ext.et_801B6F30.unk82 -= 7;
                } else {
                    self->ext.et_801B6F30.unk82 = 0;
                }
            }
        }
        itemId = self->ext.et_801B6F30.unk82 + self->ext.et_801B6F30.unk80;
        if (tempVar & PAD_RIGHT) {
            if (D_us_801D415C[itemId] < D_us_801D425C[itemId]) {
                g_api.PlaySfx(SFX_UI_MOVE);
                D_us_801D415C[itemId]++;
            }
        } else if (tempVar & PAD_LEFT) {
            if (D_us_801D415C[itemId] > 1) {
                g_api.PlaySfx(SFX_UI_MOVE);
                D_us_801D415C[itemId]--;
            }
        }
        tempVar = g_pads[0].tapped;
#ifdef VERSION_PSP
        if (tempVar & D_psp_08B42050) {
#else
        if (tempVar & PAD_CROSS) {
#endif
            if (g_Status.gold <
                    D_us_801D415C[itemId] * D_us_801D4364[itemId].price ||
                !D_us_801D415C[itemId]) {
                g_api.PlaySfx(SFX_UI_ERROR);
            } else {
                g_Status.gold -=
                    D_us_801D415C[itemId] * D_us_801D4364[itemId].price;
                switch (D_us_801D4364[itemId].category) {
                case INVENTORY_HAND:
                    tempVar = EQUIP_HAND;
                    break;
                case INVENTORY_HEAD:
                    tempVar = EQUIP_HEAD;
                    break;
                case INVENTORY_BODY:
                    tempVar = EQUIP_ARMOR;
                    break;
                case INVENTORY_CAPE:
                    tempVar = EQUIP_CAPE;
                    break;
                case INVENTORY_ACCESSORY:
                    tempVar = EQUIP_ACCESSORY;
                    break;
                }
                if (D_us_801D4364[itemId].category < NUM_EQUIP_KINDS) {
                    for (i = 0; i < D_us_801D415C[itemId]; i++) {
                        g_api.AddToInventory(D_us_801D4364[itemId].itemId,
                                             (enum EquipKind)tempVar);
                    }
                } else {
                    if (D_us_801D4364[itemId].category == INVENTORY_RELIC) {
                        g_api.func_800FE044(
                            D_us_801814D4[D_us_801D4364[itemId].itemId],
                            0x2000);
                    } else {
                        if (D_us_801D4364[itemId].itemId) {
                            g_api.LearnSpell(
                                D_us_80181510[D_us_801D4364[itemId].itemId -
                                              1]);
                        } else {
                            // castle map
                            g_api.func_800F2288(0);
                            g_CastleFlags[BOUGHT_CASTLE_MAP] = 1;
                        }
                    }
                }
                D_us_801D425C[itemId] -= D_us_801D415C[itemId];
                if (D_us_801D425C[itemId]) {
                    D_us_801D415C[itemId] = 1;
                } else {
                    D_us_801D415C[itemId] = 0;
                }
                SetStep(4);
                g_api.PlaySfx(SFX_UI_CONFIRM);
            }
#ifdef VERSION_PSP
        } else if (tempVar & D_psp_08B42054) {
#else
        } else if (tempVar & PAD_TRIANGLE) {
#endif
            SetStep(7);
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 10; i++) {
            prim = prim->next;
        }
        prim->y0 = prim->y1 = (self->ext.et_801B6F30.unk80 * 0xC) + 0x1F;
        prim->y2 = prim->y3 = prim->y0 + 0xC;
        prim->drawMode = DRAW_COLORS;

        prim = prim->next;
        if (self->ext.et_801B6F30.unk82) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }

        prim = prim->next;
        if (self->ext.et_801B6F30.unk82 < self->ext.et_801B6F30.unk88) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            if (g_api.func_80131F68()) {
                g_api.PlaySfx(SET_STOP_MUSIC);
                self->step_s++;
            } else {
                self->step_s++;
            }
            break;

        case 1:
            if (!g_api.func_80131F68()) {
                g_CutsceneFlags |= 0x800;
                g_api.PlaySfx(NA_VO_ML_THANKS);
                SetStep(3);
            }
            break;
        }
        break;

    case 5:
        tempVar = g_pads[0].repeat;
        if (tempVar & PAD_DOWN) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80++;
            } else if (self->ext.et_801B6F30.unk82 < 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82++;
            }
        } else if (tempVar & PAD_UP) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80--;
            } else if (self->ext.et_801B6F30.unk82) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82--;
            }
        }
        itemId = self->ext.et_801B6F30.unk82 + self->ext.et_801B6F30.unk80;
        if (tempVar & PAD_RIGHT) {
            if (D_us_801D415C[itemId] < D_us_801D425C[itemId]) {
                g_api.PlaySfx(SFX_UI_MOVE);
                D_us_801D415C[itemId]++;
            }
        } else if (tempVar & PAD_LEFT) {
            if (D_us_801D415C[itemId] > 1) {
                g_api.PlaySfx(SFX_UI_MOVE);
                D_us_801D415C[itemId]--;
            }
        }
        tempVar = g_pads[0].tapped;
#ifdef VERSION_PSP
        if (tempVar & D_psp_08B42050) {
#else
        if (tempVar & PAD_CROSS) {
#endif
            if (D_us_801D415C[itemId] == 0) {
                g_api.PlaySfx(SFX_UI_ERROR);
            } else {
                g_Status.gold +=
                    D_us_801D415C[itemId] * D_us_801814D8[itemId].price;
                if (g_Status.gold > 999999) {
                    g_Status.gold = 999999;
                }
                ptr = &D_us_801814D8[itemId];
                g_Status.equipBodyCount[ptr->itemId] -= D_us_801D415C[itemId];
                D_us_801D425C[itemId] -= D_us_801D415C[itemId];
                D_us_801D415C[itemId] = 0;
                SetStep(6);
                g_api.PlaySfx(SFX_UI_CONFIRM);
            }
#ifdef VERSION_PSP
        } else if (tempVar & D_psp_08B42054) {
#else
        } else if (tempVar & PAD_TRIANGLE) {
#endif
            SetStep(7);
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 10; i++) {
            prim = prim->next;
        }
        prim->y0 = prim->y1 = (self->ext.et_801B6F30.unk80 * 0xC) + 0x1F;
        prim->y2 = prim->y3 = prim->y0 + 0xC;
        prim->drawMode = DRAW_COLORS;

        prim = prim->next;
        if (self->ext.et_801B6F30.unk82) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }

        prim = prim->next;
        if (self->ext.et_801B6F30.unk82 < 0) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            if (g_api.func_80131F68()) {
                g_api.PlaySfx(SET_STOP_MUSIC);
                self->step_s++;
            } else {
                self->step_s++;
            }
            break;

        case 1:
            if (!g_api.func_80131F68()) {
                g_CutsceneFlags |= 0x800;
                g_api.PlaySfx(NA_VO_ML_THANKS);
                SetStep(5);
            }
            break;
        }
        break;

    case 7:
        if ((g_CutsceneFlags & 0x200) == 0) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 10; i++) {
                prim = prim->next;
            }
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            prim->drawMode = DRAW_HIDE;
            self->ext.et_801B6F30.unk7E = 0x400;
            self->ext.et_801B6F30.unk7C = 0x10;
            self->step++;
            g_CutsceneFlags |= 0x200;
        }
        break;

    case 8:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x74, 0x20, 8, 1);
        if (self->ext.et_801B6F30.unk7C == 1) {
            g_CutsceneFlags &= ~0x400;
        }
        if (!self->ext.et_801B6F30.unk7C) {
            DestroyEntity(self);
        }
        break;
    }
}

Primitive* func_us_801B3EC8(Primitive* prim, u32 number, u16 maxDigits) {
    s32 i;
    s32 currentDigit;

    bool hasADigit = false;
    for (currentDigit = maxDigits - 1; currentDigit >= 0; currentDigit--) {
        u32 digitValue = number;
        for (i = 0; i < currentDigit; i++) {
            digitValue /= 10;
        }
        if (digitValue != 0) {
            if (digitValue < 10) {
                prim->u0 = digitValue * 8;
                prim->v0 = 8;
            } else {
                prim->u0 = 0x28;
                prim->v0 = 0x10;
            }
            for (i = 0; i < currentDigit; i++) {
                digitValue *= 10;
            }
            number -= digitValue;
            hasADigit = true;
            prim->drawMode = DRAW_DEFAULT;
        } else if (hasADigit || currentDigit == 0) {
            prim->u0 = 0;
            prim->v0 = 8;
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
    }
    return prim;
}

Primitive* func_us_801B3FB4(
    Primitive* prim, const char* str, u16 length, s32 arg3) {
    char ch;
    s32 i;
    u32 max;
    const char* chPtr;

    chPtr = str;
    max = 0;
    for (i = 0; i < length; i++) {
#ifdef VERSION_PSP
        if (*chPtr == 0xFF) {
            break;
        }
        chPtr++;
        max++;
    }
    for (i = 0; i < max; i++) {
#endif
        ch = *str++;
        prim->u0 = (ch & 0x0F) << 3;
        prim->v0 = (ch & 0xF0) >> 1;
        if (arg3 != 0) {
            prim->drawMode = DRAW_DEFAULT;
        }
        prim = prim->next;
    }
#ifdef VERSION_PSP
    for (; i < length; i++) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
#endif
    return prim;
}

#ifdef VERSION_PSP
extern const char** D_us_80181528;
#else
static const char* D_us_80181528[] = {"ATT", "DEF"};
#endif

static u16 D_us_80181530[] = {
    -0x012, -0x022, -0x00A, -0x022, -0x012, -0x01A, -0x00A, -0x01A, -0x02E,
    0x01A,  -0x026, 0x01A,  -0x01E, 0x01A,  -0x016, 0x01A,  -0x006, 0x01A,
    0x002,  0x01A,  0x00A,  0x01A,  0x012,  0x01A,  0x01A,  0x01A,  0x022,
    0x01A,  0x02A,  0x01A,  0x032,  0x01A,  -0x016, 0x010,  -0x00E, 0x010,
    -0x006, 0x010,  0x002,  0x010,  0x00A,  0x010,  0x012,  0x010,  0x01A,
    0x010,  0x01A,  0x010,  0x022,  0x010,  0x02A,  0x010,  0x032,  0x010,
    0x002,  -0x022, 0x00A,  -0x022, 0x012,  -0x022, 0x01A,  -0x023, 0x022,
    -0x022, 0x02A,  -0x022, 0x032,  -0x022, 0x002,  -0x01A, 0x00A,  -0x01A,
    0x012,  -0x01A, 0x01A,  -0x01B, 0x022,  -0x01A, 0x02A,  -0x01A, 0x032,
    -0x01A, 0x002,  -0x00E, 0x00A,  -0x00E, 0x012,  -0x00E, 0x01A,  -0x00F,
    0x022,  -0x00E, 0x02A,  -0x00E, 0x032,  -0x00E, -0x036, -0x002, -0x02E,
    -0x002, -0x026, -0x002, -0x01A, -0x002, -0x012, -0x002, -0x00A, -0x002,
    0x006,  -0x002, 0x00E,  -0x002, 0x016,  -0x002, 0x022,  -0x002, 0x02A,
    -0x002, 0x032,  -0x002, -0x036, 0x006,  -0x02E, 0x006,  -0x026, 0x006,
    -0x01A, 0x006,  -0x012, 0x006,  -0x00A, 0x006,  0x006,  0x006,  0x00E,
    0x006,  0x016,  0x006,  0x022,  0x006,  0x02A,  0x006,  0x032,  0x006};
static char D_us_80181650[] = {
    CH(' '), CH(' '), CH(' '), CH(' '), CH('R'), CH('L'), CH('R'), CH('L')};
static char D_us_80181658[] = {
    SQUARE, CIRCLE, CROSS, TRIANGLE, CH('2'), CH('1'), CH('1'), CH('2')};

#ifdef VERSION_PSP
extern char* D_us_80181660;
extern char* D_us_80181668;
extern char** D_us_80181674;
#else
static char D_us_80181660[] = {
    CIRCLE, SQUARE, CIRCLE, SQUARE, CH('G'), CH('O'), CH('L'), CH('D')};
static char D_us_80181668[] = {
    // clang-format off
    CH('S'), CH('T'), CH('R'),
    CH('C'), CH('O'), CH('N'),
    CH('I'), CH('N'), CH('T'),
    CH('L'), CH('C'), CH('K')
    // clang-format on
};
static char* D_us_80181674[] = {
    _S("Number"), _S("Equipped"), _S("Not equipped"), _S("うれるこすう")};
#endif

static u16 D_us_80181684[] = {0xE4, 0xB0, 0xEC, 0xB0};

void func_us_801B4010(u16* arg0) {
    *arg0++ = g_Status.equipment[0];
    *arg0++ = g_Status.equipment[1];
    *arg0++ = g_Status.equipment[2];
    *arg0++ = g_Status.equipment[3];
    *arg0++ = g_Status.equipment[4];
    *arg0++ = g_Status.equipment[5];
    *arg0 = g_Status.equipment[6];
}

void func_us_801B4080(u16* arg0) {
    g_Status.equipment[0] = *arg0++;
    g_Status.equipment[1] = *arg0++;
    g_Status.equipment[2] = *arg0++;
    g_Status.equipment[3] = *arg0++;
    g_Status.equipment[4] = *arg0++;
    g_Status.equipment[5] = *arg0++;
    g_Status.equipment[6] = *arg0;
}

void func_us_801B40F0(u16* arg0) {
    *arg0 = g_Status.attackHands[0];
    arg0 += 2;
    *arg0 = g_Status.attackHands[1];
    arg0 += 2;
    *arg0 = g_Status.defenseEquip;
    arg0 += 2;
    *arg0 = g_Status.statsBase[0] + g_Status.statsEquip[0];
    arg0 += 2;
    *arg0 = g_Status.statsBase[1] + g_Status.statsEquip[1];
    arg0 += 2;
    *arg0 = g_Status.statsBase[2] + g_Status.statsEquip[2];
    arg0 += 2;
    *arg0 = g_Status.statsBase[3] + g_Status.statsEquip[3];
}

Primitive* func_us_801B4194(Primitive* prim) {
    Primitive* prim2;
    s32 i;
    u16* ptr;

    prim = func_us_801B1064(prim, 0xAA, 0xB0, D_us_80181674[0], 0x196);
    prim2 = prim;
    ptr = D_us_80181684;
    for (i = 0; i < 2; i++) {
        prim2->x0 = *ptr++;
        prim2->y0 = *ptr++;
        prim2 = prim2->next;
    }
    return prim;
}

void func_us_801B420C(Primitive* prim, Entity* arg1) {
    u16 index;
    s16 x0;
    s16 x1, y1;
    ShopItem* shopItem;
    s16* condition;
    u16 stats[14];
    u16 equipment[7];
    s16 maxDigits;
    s32 i, j;
    s16 itemId;
    s16 number;
    u16* ptr;
    Primitive* primA;
    Primitive* primB;
    s16 y0;

    for (i = 0; i < 11; i++) {
        prim = prim->next;
    }
    for (i = 0; i < 8; i++) {
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
    }
    prim = func_us_801B3EC8(prim, g_Status.gold, 8);
    index = arg1->ext.et_801B6F30.unk80 + arg1->ext.et_801B6F30.unk82;
#ifdef VERSION_PSP
    condition = 0;
    if (arg1->params) {
        shopItem = &D_us_801814D8[index];
        condition = D_psp_092A4A88;
        primA = prim;
        ptr = D_psp_092A4A78;
        prim = func_us_801B3FB4(prim, D_us_80181674[0], 8, 1);
        primB = prim;
        x0 = 0x28;
        y0 = 0x10;
        prim = func_us_801B3EC8(prim, D_us_801D425C[index], 2);
    } else {
        shopItem = &D_us_801D4364[index];
        primA = prim;
        if (shopItem->category < INVENTORY_RELIC) {
            ptr = D_psp_092A4A78;
            prim = func_us_801B3FB4(prim, D_us_80181674[0], 12, 1);
            condition = D_psp_092A4A88;
            primB = prim;
            x0 = 0x28;
            y0 = 0x10;
            prim = func_us_801B3EC8(prim, 99 - D_us_801D425C[index], 2);
        } else {
            ptr = D_psp_092A4AA0;
            if (D_us_801D425C[index] != 0) {
                prim = func_us_801B3FB4(prim, D_us_80181674[2], 12, 1);
            } else {
                prim = func_us_801B3FB4(prim, D_us_80181674[1], 12, 1);
            }
        }
    }
    x1 = *ptr++;
    y1 = *ptr++;
    for (i = 0; i < 12; i++) {
        primA->x0 = x1 + 0xBA + i * 8;
        primA->y0 = y1 + 0xA0;
        primA = primA->next;
    }
    if (condition) {
        for (i = 0; i < 2; i++) {
            primB->x0 = x0 + 0xBA + i * 8;
            primB->y0 = y0 + 0xA0;
            primB = primB->next;
        }
    }
#else
    primA = prim;
    for (i = 0; i < 11; i++) {
        primA->drawMode = DRAW_HIDE;
        primA = primA->next;
    }
    if (arg1->params) {
        shopItem = &D_us_801814D8[index];
        prim =
            func_us_801B3EC8(func_us_801B4194(prim), D_us_801D425C[index], 2);
    } else {
        shopItem = &D_us_801D4364[index];
        if (shopItem->category < INVENTORY_RELIC) {
            prim = func_us_801B3EC8(
                func_us_801B4194(prim), 99 - D_us_801D425C[index], 2);
        } else {
            if (D_us_801D425C[index] != 0) {
                prim =
                    func_us_801B1064(prim, 0x9A, 0xB0, D_us_80181674[2], 0x196);
            } else {
                prim =
                    func_us_801B1064(prim, 0xB6, 0xB0, D_us_80181674[1], 0x196);
            }
        }
    }
    prim = primA;
#endif
    func_us_801B4010(equipment);
    func_us_801B40F0(stats);
    itemId = shopItem->itemId;
    switch (shopItem->category) {
    case INVENTORY_HAND:
        g_Status.equipment[LEFT_HAND_SLOT] = itemId;
        g_Status.equipment[RIGHT_HAND_SLOT] = itemId;
        break;
    case INVENTORY_HEAD:
        g_Status.equipment[HEAD_SLOT] = itemId;
        break;
    case INVENTORY_BODY:
        g_Status.equipment[ARMOR_SLOT] = itemId;
        break;
    case INVENTORY_CAPE:
        g_Status.equipment[CAPE_SLOT] = itemId;
        break;
    case INVENTORY_ACCESSORY:
        g_Status.equipment[ACCESSORY_1_SLOT] = itemId;
        g_api.func_800F53A4();
        func_us_801B40F0(stats + 1);
        func_us_801B4080(equipment);
        g_Status.equipment[ACCESSORY_2_SLOT] = itemId;
        g_api.func_800F53A4();
        i = 3;
        ptr = stats + 1;
        maxDigits = *ptr - g_Status.attackHands[0];
        ptr += 4;
        maxDigits += *ptr - g_Status.defenseEquip;
        if (maxDigits < 0) {
            i++;
        } else if (maxDigits == 0) {
            ptr += 2;
            maxDigits = *ptr - (g_Status.statsBase[0] + g_Status.statsEquip[0]);
            ptr += 2;
            maxDigits +=
                *ptr - (g_Status.statsBase[1] + g_Status.statsEquip[1]);
            ptr += 2;
            maxDigits +=
                *ptr - (g_Status.statsBase[2] + g_Status.statsEquip[2]);
            ptr += 2;
            maxDigits +=
                *ptr - (g_Status.statsBase[3] + g_Status.statsEquip[3]);
            if (maxDigits < 0) {
                i++;
            }
        }
        func_us_801B4080(equipment);
        (g_Status.equipment + 2)[i] = itemId;
        break;
    case INVENTORY_RELIC:
        break;
    }
    g_api.func_800F53A4();
    func_us_801B40F0(stats + 1);
    func_us_801B4080(equipment);
    g_api.func_800F53A4();
    ptr = stats;
    for (i = 0; i < 3; i++) {
#ifdef VERSION_PSP
        primA = prim;
        for (j = 0; j < 7; j++) {
            prim->x0 = D_psp_092A49B8[j * 2 + (i * 7) * 2] + 0xBA;
            prim->y0 = D_psp_092A49B8[j * 2 + (i * 7) * 2 + 1] + 0xA0;
            prim = prim->next;
        }
        prim = primA;
#endif
        maxDigits = *ptr++;
        prim = func_us_801B3EC8(prim, maxDigits, 3);
        if (!arg1->params) {
            maxDigits -= *ptr;
            if (maxDigits) {
                if (maxDigits > 0) {
                    prim->u0 = 0x28;
                } else {
                    prim->u0 = 0x18;
                }
            } else {
                prim->u0 = 0x20;
            }
            prim->v0 = 0x70;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
            prim = func_us_801B3EC8(prim, *ptr++, 3);
        } else {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
#ifdef VERSION_PSP
            ptr++;
#endif
        }
    }
    if (!arg1->params) {
        for (i = 0; i < 4; i++) {
            maxDigits = *ptr++;
            number = *ptr++;
#ifdef VERSION_PSP
            primA = prim;
            for (j = 0; j < 6; j++) {
                prim->x2 = prim->x0 =
                    D_psp_092A4A10[j * 2 + (i * 6) * 2] + 0xBA;
                prim->y1 = prim->y0 =
                    D_psp_092A4A10[j * 2 + (i * 6) * 2 + 1] + 0xA0;
                prim->x3 = prim->x1 = prim->x0 + 8;
                prim->y3 = prim->y2 = prim->y0 + 8;
                prim->v1 = prim->u1 = 8;
                prim->type = PRIM_SPRT;
                prim->clut = 0x196;
                prim->tpage = 0x1E;
                prim->priority = 0x11;
                prim = prim->next;
            }
            prim = primA;
#endif
            if (maxDigits != number) {
                prim = func_us_801B3FB4(prim, &D_us_80181668[i * 3], 3, 1);
                if (maxDigits > number) {
                    number = maxDigits - number;
                    maxDigits = 2;
                    if (number / 10 == 0) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                        maxDigits = 1;
                    }
                    prim->u0 = 0x68;
                } else {
                    number -= maxDigits;
                    maxDigits = 2;
                    if (number / 10 == 0) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                        maxDigits = 1;
                    }
                    prim->u0 = 0x58;
                }
                prim->v0 = 0;
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
                prim = func_us_801B3EC8(prim, number, maxDigits);
            } else {
                for (j = 0; j < 6; j++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
            }
            if (prim == NULL) {
                break;
            }
        }
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801B4830(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 j;
    s32 count;
    u16* var_s4;
    const char* name;
    Entity* tempEntity;
    u8* unused;

    tempEntity = self - 1;
    switch (self->step) {
    case 0:
#ifdef VERSION_PSP
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x84);
#else
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x53);
#endif
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            count = 0x49;
            j = 0;
            while (prim != NULL) {
                if (i < 6) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = prim->r1 = 0x80;
                    prim->g0 = prim->g1 = 0x80;
                    prim->b0 = prim->b1 = 0x80;
                    prim->priority = 0xC0;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 8) {
                    prim->type = PRIM_G4;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0xBA;
                    prim->y0 = prim->y1 = 0x76;
                    prim->y2 = prim->y3 = 0xCA;
                    prim->priority = 0xBF;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 10) {
                    prim->type = PRIM_GT4;
#ifdef VERSION_PSP
                    prim->tpage = 0x110;
#else
                    prim->tpage = 0x114;
#endif
                    prim->u0 = prim->u2 = (i - 9) * 0x3A + 0xBA;
                    prim->u1 = prim->u3 = prim->u0 + 0x3A;
                    prim->v0 = prim->v1 = 0x7E;
                    prim->v2 = prim->v3 = prim->v0 + 0x44;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0xBA;
                    prim->y0 = prim->y1 = 0x7E;
                    prim->y2 = prim->y3 = 0xC2;
                    prim->priority = 0xC0;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 10) {
#ifdef VERSION_PSP
                    func_us_801B11A0(0x50, 0x100, 0x24, 0x20);
#else
                    func_us_801B11A0(0x60, 0x100, 0x24, 0x20);
#endif
                    prim->clut = 0x1A1;
                    prim->tpage = 0x10;
#ifdef VERSION_PSP
                    prim->u0 = 0x50;
#else
                    prim->u0 = 0x60;
#endif
                    prim->v0 = 0;
                    prim->u1 = 0x24;
                    prim->v1 = 0x20;
                    prim->x0 = 0x80;
                    prim->y0 = 0x7E;
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                    var_s4 = D_us_80181530;
                } else if (i < 15) {
                    if (i == 11) {
                        D_us_80181660[0] =
                            D_us_80181650[g_Settings.buttonConfig[0]];
                        D_us_80181660[1] =
                            D_us_80181658[g_Settings.buttonConfig[0]];
                        D_us_80181660[2] =
                            D_us_80181650[g_Settings.buttonConfig[1]];
                        D_us_80181660[3] =
                            D_us_80181658[g_Settings.buttonConfig[1]];
                        func_us_801B3FB4(prim, D_us_80181660, 8, 0);
                    }
                    prim->x0 = *var_s4++ + 0xBA;
                    prim->y0 = *var_s4++ + 0xA0;
                    j++;
                    if (g_Settings.buttonConfig[(i - 11) / 2] < 4) {
                        if ((i - 11) & 1) {
                            prim->x0 -= 4;
                        }
                    }
                    prim->clut = 0x196;
                    prim->tpage = 0x1E;
                    prim->u1 = 8;
                    prim->v1 = 8;
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                } else {
                    prim->x0 = *var_s4++ + 0xBA;
                    prim->y0 = *var_s4++ + 0xA0;
                    j++;
                    prim->clut = 0x196;
                    prim->tpage = 0x1E;
                    prim->u1 = 8;
                    prim->v1 = 8;
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                }
                prim = prim->next;
                i++;
#ifdef VERSION_PSP
                if (j >= count) {
                    break;
                }
#endif
            }
#ifdef VERSION_PSP
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
#endif
        }
        break;

    case 1:
        if (!self->step_s) {
            unused = g_Pix[0];
            for (i = 0; i < 2; i++) {
                name = D_us_80181528[i];
#ifdef VERSION_PSP
                func_us_801B0FBC(name, 0x17, 0x104 + i * 16);
#else
                func_us_801B0FBC(name, 0x1A, 0x104 + i * 16);
#endif
            }
            self->step_s++;
        } else if (g_CutsceneFlags & 0x400) {
            SetStep(2);
            self->ext.et_801B6F30.unk7C = 0x10;
        }
        break;

    case 2:
        if (!--self->ext.et_801B6F30.unk7C) {
            prim = &g_PrimBuf[self->primIndex];
            func_us_801B420C(prim, tempEntity);
            for (i = 0; i < 10; i++) {
                prim = prim->next;
            }
            for (i = 0; i < 7; i++) {
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
            SetStep(3);
            self->ext.et_801B6F30.unk7C = 0;
            self->ext.et_801B6F30.unk7E = 0;
        }
        break;

    case 3:
        self->ext.et_801B6F30.unk7C++;
        self->ext.et_801B6F30.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x42, 0x18, 0x32, 1);
        if (self->ext.et_801B6F30.unk7C == 0x10) {
            SetStep(4);
        }
        break;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B420C(prim, tempEntity);
        if ((g_CutsceneFlags & 0x400) == 0) {
            self->ext.et_801B6F30.unk7E = 0x400;
            self->ext.et_801B6F30.unk7C = 0x10;
            SetStep(8);
        }
        break;

    case 8:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x42, 0x18, 0x32, 1);
        if (!self->ext.et_801B6F30.unk7C) {
            for (i = 0; i < 10; i++) {
                prim = prim->next;
            }
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            SetStep(9);
        }
        break;

    case 9:
        DestroyEntity(self);
        return;
    }
}

#ifdef VERSION_PSP
extern const char** D_us_8018168C;
#else
static const char* D_us_8018168C[] = {
    "Basic map of Dracula’s castle", "Contains ””Dark Metamorphosis””",
    "Contains ””Summon Spirit””",    "Contains ””Hellfire””",
    "Contains ””Tetra Spirits””",    "Contains ””Soul Steal””"};
#endif

void func_us_801B4ED4(s16 index, u16 arg1) {
    const char* desc;
    u16 itemId;
    ShopItem* shopItem;
    unsigned char* unused;

    if (arg1) {
        shopItem = &D_us_801814D8[index];
    } else {
        shopItem = &D_us_801D4364[index];
    }
    itemId = shopItem->itemId;
    switch (shopItem->category) {
    case INVENTORY_HAND:
        desc = g_api.equipDefs[itemId].description;
        g_api.LoadEquipIcon(g_api.equipDefs[itemId].icon,
                            g_api.equipDefs[itemId].iconPalette, 0x1F);
        break;
    case INVENTORY_HEAD:
    case INVENTORY_BODY:
    case INVENTORY_CAPE:
    case INVENTORY_ACCESSORY:
        desc = g_api.accessoryDefs[itemId].description;
        g_api.LoadEquipIcon(g_api.accessoryDefs[itemId].icon,
                            g_api.accessoryDefs[itemId].iconPalette, 0x1F);
        break;
    case INVENTORY_RELIC:
        itemId = D_us_801814D4[itemId];
        desc = g_api.relicDefs[itemId].desc;
        g_api.LoadEquipIcon(g_api.relicDefs[itemId].icon,
                            g_api.relicDefs[itemId].iconPalette, 0x1F);
        break;
    case INVENTORY_DOCUMENT:
        desc = D_us_8018168C[itemId];
        if (itemId) {
            itemId = 0x112;
        } else {
            itemId = 0x111;
        }
        g_api.LoadEquipIcon(itemId, 0x118, 0x1F);
        break;
    default:
        desc = *D_us_80181528;
        break;
    }
    unused = &g_Pix[0][0x1000];
    itemId = 2;
    func_us_801B0C40(&g_Pix[0][0x800], desc, 2, 0x184, 0x7E);
}

void func_us_801B5068(Entity* self) {
    Primitive* prim;
    Primitive* otherPrim;
    s32 primIndex;
    s32 i;
    s16 offset;
    Entity* tempEntity;

    tempEntity = self - 2;
#ifdef VERSION_PSP
    func_psp_09264E08();
#endif
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 7);
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            for (; prim != NULL; i++) {
                if (i < 4) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = prim->r1 = 0x80;
                    prim->g0 = prim->g1 = 0x80;
                    prim->b0 = prim->b1 = 0x80;
                    prim->priority = 0xBE;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 4) {
                    func_us_801B11A0(0, 0x180, 0xF0, 0x16);
                    prim->clut = 0x1A1;
                    prim->tpage = 0x10;
                    prim->u0 = prim->u2 = 0;
                    prim->u1 = prim->u3 = 0xF0;
                    prim->v0 = prim->v1 = 0x80;
                    prim->v2 = prim->v3 = 0x96;
                    prim->priority = 0xBE;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 5) {
                    prim->type = PRIM_G4;
                    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
                    prim->g0 = prim->g1 = 0x20;
                    prim->g2 = prim->g3 = 0x40;
                    prim->b0 = prim->b1 = 0;
                    prim->b2 = prim->b3 = 0;
                    prim->priority = 0xBD;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 6) {
                    prim->tpage = 0x1A;
                    prim->clut = 0x1EF;
                    prim->x0 = prim->x2 = 0x49;
                    prim->x1 = prim->x3 = 0x57;
                    prim->y0 = prim->y1 = 0x96;
                    prim->y2 = prim->y3 = 0xA4;
                    prim->u0 = prim->u2 = 0x71;
                    prim->u1 = prim->u3 = prim->u0 + 0xE;
                    prim->v0 = prim->v1 = 0xB1;
                    prim->v2 = prim->v3 = prim->v0 + 0xE;
                    prim->priority = 0xC0;
                    prim->drawMode = DRAW_HIDE;
                }
                prim = prim->next;
            }
        }
        break;

    case 1:
        if (!self->step_s) {
            self->ext.et_801B6F30.unk80 = 0;
            func_us_801B4ED4(0, tempEntity->params);
            self->step_s++;
        } else if (g_CutsceneFlags & 0x400) {
            SetStep(2);
            self->ext.et_801B6F30.unk7C = 0x18;
        }
        break;

    case 2:
        if (!--self->ext.et_801B6F30.unk7C) {
            SetStep(3);
            self->ext.et_801B6F30.unk7C = 0x10;
            self->ext.et_801B6F30.unk7E = 0;
        }
        break;

    case 3:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        otherPrim = prim;
        for (i = 0; i < 4; i++) {
            prim = prim->next;
        }
#ifdef VERSION_PSP
        i = 0;
        if (self->ext.et_801B6F30.unk7C == 0) {
            for (; i < 2; i++) {
                prim->x0 = prim->x2 = 8;
                prim->x1 = prim->x3 = prim->x0 + 0xF0;
                prim->y0 = prim->y1 = 0xC9;
                prim->y2 = prim->y3 = prim->y0 + 0x16;
                if (i) {
                    prim->drawMode =
                        DRAW_UNK_400 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                    func_us_801B1200(otherPrim, prim);
                } else {
                    prim->drawMode = DRAW_DEFAULT;
                }
                prim = prim->next;
            }
        } else {
            for (; i < 2; i++) {
                offset = (rcos(self->ext.et_801B6F30.unk7E) * 16) / 0x1000;
                prim->x0 = offset + 8;
                prim->x2 = 8 - offset;
                prim->x1 = 0xF8 - offset;
                prim->x3 = offset + 0xF8;
                offset = (rsin(self->ext.et_801B6F30.unk7E) * 11) / 0x1000;
                prim->y0 = prim->y1 = 0xD4 - offset;
                prim->y2 = prim->y3 = offset + 0xD4;
                if (i) {
                    prim->drawMode =
                        DRAW_UNK_400 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                    func_us_801B1200(otherPrim, prim);
                } else {
                    prim->drawMode = DRAW_DEFAULT;
                }
                prim = prim->next;
            }
        }
#else
        for (i = 0; i < 2; i++) {
            offset = (rcos(self->ext.et_801B6F30.unk7E) * 16) / 0x1000;
            prim->x0 = offset + 8;
            prim->x2 = 8 - offset;
            prim->x1 = 0xF8 - offset;
            prim->x3 = offset + 0xF8;
            offset = (rsin(self->ext.et_801B6F30.unk7E) * 11) / 0x1000;
            prim->y0 = prim->y1 = 0xD4 - offset;
            prim->y2 = prim->y3 = offset + 0xD4;
            if (i) {
                prim->drawMode =
                    DRAW_UNK_400 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                func_us_801B1200(otherPrim, prim);
            } else {
                prim->drawMode = DRAW_DEFAULT;
            }
            prim = prim->next;
        }
#endif
        if (!self->ext.et_801B6F30.unk7C) {
            SetStep(4);
        }
        break;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 6; i++) {
            prim = prim->next;
        }
        if (D_us_801D425C[self->ext.et_801B6F30.unk80]) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        if (!self->step_s) {
            if (self->ext.et_801B6F30.unk80 !=
                (tempEntity->ext.et_801B6F30.unk80 +
                 tempEntity->ext.et_801B6F30.unk82)) {
                func_us_801B11A0(0, 0x180, 0xF0, 0x16);
                prim->drawMode = DRAW_HIDE;
                self->step_s = 1;
            }
        } else {
            self->ext.et_801B6F30.unk80 = tempEntity->ext.et_801B6F30.unk80 +
                                          tempEntity->ext.et_801B6F30.unk82;
            func_us_801B4ED4(self->ext.et_801B6F30.unk80, tempEntity->params);
            self->step_s = 0;
        }
        if ((g_CutsceneFlags & 0x400) == 0) {
            prim->drawMode = DRAW_HIDE;
            SetStep(7);
            self->ext.et_801B6F30.unk7C = 0x10;
        }
        break;

    case 7:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        otherPrim = prim;
        for (i = 0; i < 4; i++) {
            prim = prim->next;
        }
        for (i = 0; i < 2; i++) {
            offset = (rcos(self->ext.et_801B6F30.unk7E) * 16) / 0x1000;
            prim->x0 = offset + 8;
            prim->x2 = 8 - offset;
            prim->x1 = 0xF8 - offset;
            prim->x3 = offset + 0xF8;
            offset = (rsin(self->ext.et_801B6F30.unk7E) * 11) / 0x1000;
            prim->y0 = prim->y1 = 0xD4 - offset;
            prim->y2 = prim->y3 = offset + 0xD4;
            if (i) {
                prim->drawMode =
                    DRAW_UNK_400 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                func_us_801B1200(otherPrim, prim);
            } else {
                prim->drawMode = DRAW_DEFAULT;
            }
            prim = prim->next;
        }
        if (!self->ext.et_801B6F30.unk7C) {
            func_us_801B11A0(0, 0x180, 0xF0, 0x16);
            DestroyEntity(self);
        }
        break;
    }
}

#ifdef VERSION_PSP
extern char* D_us_801816A4;
extern const char** D_us_801816AC;
extern const char** D_us_801816B0;
#else
static char D_us_801816A4[] = {
    CH('S'), CH('O'), CH('L'), CH('D'), CH(' '), CH('O'), CH('U'), CH('T')};
static const char* D_us_801816AC[] = {_S("Jewel of Open")};
static const char* D_us_801816B0[] = {
    _S("Castle map"),     _S("Magic scroll 1"), _S("Magic scroll 2"),
    _S("Magic scroll 3"), _S("Magic scroll 4"), _S("Magic scroll 5")};
#endif

void func_us_801B56E4(Entity* self) {
    Entity* tempEntity;
    s32 primIndex;
    s32 i, j;
    ShopItem* shopItem;
    DRAWENV drawEnv;
    DR_ENV* dr_env;
    RECT clipRect = {.x = 0x100, .y = 0x100, .w = 0x100, .h = 0x100};
    const char* name;
    Primitive* prim;
    Primitive* prim2;
    s16 posX, posY;
    s16 itemId;
    s16 index;
    s32 count;
    u32 price;

    tempEntity = self - 3;
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x13A);
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env != NULL) {
                prim->type = PRIM_ENV;
                prim->priority = 0x10;
                prim->drawMode = DRAW_DEFAULT;
                drawEnv = g_CurrentBuffer->draw;
                drawEnv.isbg = 1;
                drawEnv.clip = clipRect;
#ifdef VERSION_PSP
                drawEnv.ofs[0] = 0;
#else
                drawEnv.ofs[0] = 0x100;
#endif
                drawEnv.ofs[1] = 0x100;
                SetDrawEnv(dr_env, &drawEnv);
            } else {
                self->step = 0;
                return;
            }
            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env != NULL) {
                prim->type = PRIM_ENV;
                prim->priority = 0x12;
                prim->drawMode = DRAW_UNK_800;
            } else {
                self->step = 0;
                return;
            }
            prim = prim->next;
            while (prim != NULL) {
                prim->clut = 0x196;
                prim->tpage = 0x1E;
                prim->u1 = prim->v1 = 8;
                prim->priority = 0x11;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        }
        break;

    case 1:
        if (g_CutsceneFlags & 0x400) {
            if (tempEntity->params) {
                SetStep(4);
            } else {
                SetStep(2);
            }
        }
        break;

    case 2:
        posY = tempEntity->ext.et_801B56E4.unk84 + 16;
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
        index = tempEntity->ext.et_801B56E4.unk82;
        posY = 16;
        for (i = 0; i < 8; i++) {
            if (i == 7 && !tempEntity->ext.et_801B56E4.unk84) {
                break;
            }
            if (tempEntity->params) {
                shopItem = &D_us_801814D8[index];
            } else {
                shopItem = &D_us_801D4364[index];
            }
            itemId = shopItem->itemId;
            switch (shopItem->category) {
            case INVENTORY_HAND:
                name = g_api.equipDefs[itemId].name;
                break;
            case INVENTORY_HEAD:
            case INVENTORY_BODY:
            case INVENTORY_CAPE:
            case INVENTORY_ACCESSORY:
                name = g_api.accessoryDefs[itemId].name;
                break;
            case INVENTORY_RELIC:
                name = D_us_801816AC[itemId];
                break;
            case INVENTORY_DOCUMENT:
                name = D_us_801816B0[itemId];
                break;
            default:
                name = *D_us_80181528;
                break;
            }
            prim = func_us_801B1064(prim, 8, posY, name, 0x196);
            if (D_us_801D415C[index] != 0) {
                posX = 0x7E;
                prim->clut = 0x196;
                prim->u0 = 0x40;
                prim->v0 = 0x28;
                prim->drawMode = DRAW_DEFAULT;
                prim->x0 = posX;
                prim->y0 = posY;
                prim = prim->next;
                posX += 8;
                prim2 = prim;
                for (j = 0; j < 2; j++) {
                    prim->clut = 0x196;
                    prim->x0 = posX;
                    prim->y0 = posY;
                    prim = prim->next;
                    posX += 8;
                }
                func_us_801B3EC8(prim2, D_us_801D415C[index], 2);
                posX += 10;
                prim2 = prim;
                price = shopItem->price * D_us_801D415C[index];
                for (j = 0; j < 8; j++) {
                    if (g_Status.gold < price) {
                        prim->clut = 0x191;
                    } else {
                        prim->clut = 0x196;
                    }
                    prim->x0 = posX;
                    prim->y0 = posY;
                    prim = prim->next;
                    posX += 8;
                }
                func_us_801B3EC8(prim2, price, 8);
            } else {
#ifdef VERSION_PSP
                posX = 0x80;
                count = 16;
                prim2 = prim;
                for (j = 0; j < count; j++) {
#else
                posX = 0x96;
                prim2 = prim;
                for (j = 0; j < 8; j++) {
#endif
                    prim->clut = 0x196;
                    prim->x0 = posX;
                    prim->y0 = posY;
                    prim = prim->next;
                    posX += 8;
                }
#ifdef VERSION_PSP
                func_us_801B3FB4(prim2, D_us_801816A4, count, 1);
#else
                func_us_801B3FB4(prim2, D_us_801816A4, LEN(D_us_801816A4), 1);
#endif
            }
            posY += 12;
            index++;
        }
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if ((g_CutsceneFlags & 0x400) == 0) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            SetStep(3);
        }
        break;

    case 3:
        DestroyEntity(self);
        return;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
        index = tempEntity->ext.et_801B56E4.unk82;
        posY = 0x10;
        for (i = 0; i < 7; i++) {
            shopItem = &D_us_801814D8[index];
            name = g_api.accessoryDefs[shopItem->itemId].name;
            if (D_us_801D425C[index] != 0) {
                itemId = 0x196;
            } else {
                itemId = 0x191;
            }
            prim = func_us_801B1064(prim, 8, posY, name, itemId);
            posX = 0x7E;
            prim->clut = itemId;
            prim->u0 = 0x40;
            prim->v0 = 0x28;
            prim->drawMode = DRAW_DEFAULT;
            prim->x0 = posX;
            prim->y0 = posY;
            prim = prim->next;
            posX += 8;
            prim2 = prim;
            for (j = 0; j < 2; j++) {
                prim->clut = itemId;
                prim->x0 = posX;
                prim->y0 = posY;
                prim = prim->next;
                posX += 8;
            }
            func_us_801B3EC8(prim2, D_us_801D415C[index], 2);
            posX += 10;
            prim2 = prim;
            price = shopItem->price * D_us_801D415C[index];
            for (j = 0; j < 8; j++) {
                prim->clut = itemId;
                prim->x0 = posX;
                prim->y0 = posY;
                prim = prim->next;
                posX += 8;
            }
            func_us_801B3EC8(prim2, price, 8);
            posY += 12;
            index++;
        }
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if ((g_CutsceneFlags & 0x400) == 0) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            SetStep(3);
        }
        break;
    }
}

void func_us_801B5F18(Entity* self) {
    Entity* tempEntity = &g_Entities[192];
    CreateEntityFromCurrentEntity(E_ID(ID_25), tempEntity);
    self->step++;
#ifdef VERSION_PSP
    *OVL_EXPORT(cutscene_data_offset_four) = 0;
#else
    D_us_80183F64 = 0;
#endif
    if (D_8003C730 == 2) {
        D_8003C730 = 0;
#ifdef VERSION_PSP
        *OVL_EXPORT(cutscene_data_offset_four) = 1;
#else
        D_us_80183F64 = 1;
#endif
    }
}

void func_us_801B5F84(Entity* self) {
    Entity* player = &PLAYER;
    s16 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        if (g_PlayableCharacter) {
            self->step++;
        } else if ((player->posY.i.hi + g_Tilemap.scrollY.i.hi) < 0x100 &&
                   player->posX.i.hi > 0xC0) {
            D_80097928 = 1;
            D_80097910 = 0;
        }
        break;

    case 1:
        if (D_8003C730 != 2) {
            self->hitboxWidth = 0x10;
            self->hitboxHeight = 0x20;
            if (player->posX.i.hi > 0xE0) {
                posY = player->posY.i.hi + g_Tilemap.scrollY.i.hi;
                if (posY >= 0x60 && posY < 0xA0) {
                    func_us_801B5F18(self);
                }
            }
        } else {
            func_us_801B5F18(self);
        }
        break;

    case 2:
        break;
    }
}

void func_us_801B60C8(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        break;

    case 1:
        GetPlayerCollisionWith(self, 8, 0x48, 1);
        break;
    }
}

static const char* D_us_801816C8[] = {
    _S("Dracula"),
    _S("Olrox"),
    _S("Doppleganger10"),
    _S("Granfaloon"),
    _S("Minotaur&Werewolf"),
    _S("Scylla"),
    _S("Slogra&Gaibon"),
    _S("Hippogryph"),
    _S("Beelzebub"),
    _S("Succubus"),
    _S("Karasuman"),
    _S("Trevor&Grant&Sypha"),
    _S("Death"),
    _S("Cerberus"),
    _S("Richter Belmont"),
    _S("Medusa"),
    _S("The Creature"),
    _S("Lesser Demon"),
    _S("Doppleganger40"),
    _S("Akmodan II"),
    _S("Darkwing Bat"),
    _S("Galamoth"),
    _S("カ"),
    _S("カ"),
    _S("カ"),
    _S("カ"),
    _S("カ"),
    _S("Shaft"),
    _S("Lord Dracula")};

static ShopItem D_us_8018173C[] = {
    // clang-format off
    {0, DRACULA_TACTICS,            200},
    {0, SLO_GAI_TACTICS,            500},
    {0, DOPPLEGANGER10_TACTICS,     700},
    {0, HIPPOGRYPH_TACTICS,         1000},
    {0, SCYLLA_TACTICS,             1200},
    {0, MINOTAUR_WEREWOLF_TACTICS,  1400},
    {0, KARASUMAN_TACTICS,          1800},
    {0, SUCCUBUS_TACTICS,           2000},
    {0, CERBERUS_TACTICS,           2200},
    {0, OLROX_TACTICS,              2500},
    {0, GRANFALOON_TACTICS,         2800},
    {0, RICHTER_TACTICS,            3000},
    {0, DARKWING_BAT_TACTICS,       3500},
    {0, AKMODAN_II_TACTICS,         3500},
    {0, MEDUSA_TACTICS,             3500},
    {0, THE_CREATURE_TACTICS,       3500},
    {0, DEATH_TACTICS,              4000},
    {0, DOPPLEGANGER40_TACTICS,     4500},
    {0, TREVOR_GRANT_SYPHA_TACTICS, 5000},
    {0, BEELZEBUB_TACTICS,          6000},
    {0, GALAMOTH_TACTICS,           7000},
    {0, SHAFT_TACTICS,              8500},
    {0, LORD_DRACULA_TACTICS,       10000},
    // clang-format on
};

static char D_us_801817F4[] = _S("--------------");
static char D_us_80181804[] = {
    CH('-'), CH('-'), CH('-'), CH('-'), CH('-'), CH('-'), CH('-'), CH('-')};

void func_us_801B6124(Primitive* prim, Entity* arg1) {
    s16 posX, posY;
    u16 clut;
    s32 i, j;
    u16 itemId;
    u16 itemMask;
    u16 itemIndex;
    u32 price;
    Primitive* prim2;
    ShopItem* enemyTactics;

#ifdef VERSION_PSP
    g_Settings.D_8003CB00 |= 1;
#endif
    itemIndex = arg1->ext.et_801B6F30.unk82;
    posY = 16;
    for (i = 0; i < g_CurrentEntity->ext.et_801B6F30.unk84; i++) {
        enemyTactics = &D_us_8018173C[itemIndex];
        itemId = enemyTactics->itemId;
        itemMask = g_CastleFlags[(itemId >> 3) + ENEMY_TACTICS_180];
#ifdef VERSION_PSP
        if (D_8C630D0) {
            itemMask |= (1 << (itemId & 7));
        }
#endif
        if (itemMask & (1 << (itemId & 7))) {
            enemyTactics->category = 2;
            enemyTactics->price = 0;
        } else {
            enemyTactics->category = 0;
        }
#ifdef VERSION_PSP
        price = 0;
#endif
        if (g_Settings.D_8003CB00 & (1 << itemId)) {
            price = enemyTactics->price;
            clut = 0x196;
            if (g_Status.gold < price) {
                clut = 0x183;
            }
#ifdef VERSION_PSP
            prim =
                func_us_801B1064(prim, 8, posY, D_us_801816C8[itemIndex], clut);
#else
            prim = func_us_801B1064(prim, 8, posY, D_us_801816C8[itemId], clut);
#endif
            enemyTactics->category++;
        } else {
            clut = 0x191;
            prim = func_us_801B1064(prim, 8, posY, D_us_801817F4, 0x191);
        }
        posX = 0x80;
        prim2 = prim;
        for (j = 0; j < 8; j++) {
            prim->clut = clut;
            prim->x0 = posX;
            prim->y0 = posY;
            prim = prim->next;
            posX += 8;
        }
        if (enemyTactics->category) {
            func_us_801B3EC8(prim2, price, 8);
        } else {
            func_us_801B3FB4(prim2, D_us_80181804, 8, 1);
        }
        itemIndex++;
        posY += 12;
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801B6324(Entity* self) {
    DRAWENV drawEnv;
    DR_ENV* dr_env;
    Primitive* prim;
    s32 primIndex;
    s16 itemID;
    s32 i;
    s32 var_v1;
    u16 pads;

    RECT clipRect = {.x = 0x100, .y = 0x100, .w = 0x100, .h = 0x100};
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x140);
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            for (; prim != NULL; i++) {
                if (i < 6) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = prim->r1 = 0x80;
                    prim->g0 = prim->g1 = 0x80;
                    prim->b0 = prim->b1 = 0x80;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 8) {
                    prim->type = PRIM_G4;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x16;
                    prim->y2 = prim->y3 = 0x7A;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 10) {
                    prim->type = PRIM_GT4;
#ifdef VERSION_PSP
                    prim->tpage = 0x110;
#else
                    prim->tpage = 0x114;
#endif
                    prim->u0 = prim->u2 = (i - 8) * 0x5C + 8;
                    prim->u1 = prim->u3 = prim->u0 + 0x5C;
                    prim->v0 = prim->v1 = 0xD;
                    prim->v2 = prim->v3 = 0x61;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x1E;
                    prim->y2 = prim->y3 = 0x72;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 10) {
                    prim->type = PRIM_G4;
                    prim->x0 = prim->x2 = 0x21;
                    prim->x1 = prim->x3 = 0xDF;
                    prim->y0 = prim->y1 = 0x2B;
                    prim->y2 = prim->y3 = 0x37;
                    PRED(prim) = 0x40;
                    PGRN(prim) = 0x10;
                    PBLU(prim) = 0x10;
                    prim->priority = 0x1FB;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 13) {
                    prim->type = PRIM_GT4;
                    prim->tpage = 0x1E;
                    prim->clut = 0x17F;
                    prim->u0 = prim->u2 = 0x58;
                    prim->u1 = prim->u3 = 0x60;
                    prim->v0 = prim->v1 = (i - 11) * 8 + 0x70;
                    prim->v2 = prim->v3 = 0x78 - (i - 11) * 8;
                    prim->x0 = prim->x2 = 0x7C;
                    prim->x1 = prim->x3 = prim->x0 + 8;
                    prim->y0 = prim->y1 = (i - 11) * 0x60 + 0x14;
                    prim->y2 = prim->y3 = prim->y0 + 8;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 13) {
                    dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
                    if (dr_env != NULL) {
                        prim->type = PRIM_ENV;
                        prim->priority = 0x10;
                        prim->drawMode = DRAW_DEFAULT;
                        drawEnv = g_CurrentBuffer->draw;
                        drawEnv.isbg = 1;
                        drawEnv.clip = clipRect;
#ifdef VERSION_PSP
                        drawEnv.ofs[0] = 0;
#else
                        drawEnv.ofs[0] = 0x100;
#endif
                        drawEnv.ofs[1] = 0x100;
                        SetDrawEnv(dr_env, &drawEnv);
                    } else {
                        self->step = 0;
                        g_api.FreePrimitives(self->primIndex);
                        self->flags &= ~FLAG_HAS_PRIMS;
                        return;
                    }
                    prim = prim->next;
                    dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
                    if (dr_env != NULL) {
                        prim->type = PRIM_ENV;
                        prim->priority = 0x12;
                        prim->drawMode = DRAW_UNK_800;
                    } else {
                        self->step = 0;
                        g_api.FreePrimitives(self->primIndex);
                        self->flags &= ~FLAG_HAS_PRIMS;
                        return;
                    }
                } else {
                    prim->clut = 0x196;
                    prim->tpage = 0x1E;
                    prim->u1 = prim->v1 = 8;
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                }
                prim = prim->next;
            }
        }
        break;

    case 1:
        if (g_CutsceneFlags & 0x400) {
            SetStep(2);
            var_v1 = 0;
            for (i = 0; i < LEN(D_us_8018173C); i++) {
                itemID = D_us_8018173C[i].itemId;
#ifdef VERSION_PSP
                if (D_8C630D0) {
                    g_Settings.D_8003CB00 |= (1 << itemID);
                }
#endif
                if (g_Settings.D_8003CB00 & (1 << itemID)) {
                    var_v1 = i;
                }
            }
            var_v1 += 1;
            if (var_v1 > 7) {
                var_v1 -= 7;
                self->ext.et_801B6F30.unk84 = 7;
                self->ext.et_801B6F30.unk86 = var_v1;
            } else {
                self->ext.et_801B6F30.unk84 = var_v1;
                self->ext.et_801B6F30.unk86 = 0;
            }
            self->ext.et_801B6F30.unk7C = 0;
            self->ext.et_801B6F30.unk7E = 0;
            self->ext.et_801B6F30.unk80 = 0;
            self->ext.et_801B6F30.unk82 = 0;
        }
        break;

    case 2:
        self->ext.et_801B6F30.unk7C++;
        self->ext.et_801B6F30.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x64, 0x20, 0x2C, 1);
        for (i = 0; i < 15; i++) {
            prim = prim->next;
        }
        func_us_801B6124(prim, self);
        if (self->ext.et_801B6F30.unk7C == 0x10) {
            SetStep(3);
        }
        break;

    case 3:
        pads = g_pads[0].repeat;
        if (pads & PAD_DOWN) {
            if (self->ext.et_801B6F30.unk80 <
                (self->ext.et_801B6F30.unk84 - 1)) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80++;
            } else if (
                self->ext.et_801B6F30.unk82 < self->ext.et_801B6F30.unk86) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82++;
            }
        } else if (pads & PAD_UP) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80--;
            } else if (self->ext.et_801B6F30.unk82) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82--;
            }
        }
        pads = g_pads[0].tapped;
#ifdef VERSION_PSP
        if (pads & D_psp_08B42050) {
#else
        if (pads & PAD_CROSS) {
#endif
            itemID =
                (self->ext.et_801B6F30.unk82 + self->ext.et_801B6F30.unk80);
            switch (D_us_8018173C[itemID].category) {
            case 0:
                g_api.PlaySfx(SFX_UI_ERROR);
                break;

            case 1:
                if (g_Status.gold < D_us_8018173C[itemID].price) {
                    g_api.PlaySfx(SFX_UI_ERROR);
                } else {
                    g_Status.gold -= D_us_8018173C[itemID].price;
                    itemID = D_us_8018173C[itemID].itemId;
                    g_CastleFlags[(itemID >> 3) + ENEMY_TACTICS_180] |=
                        (1 << (itemID & 7));
                    SetStep(4);
                    g_api.PlaySfx(SFX_UI_CONFIRM);
                }
                break;

            case 2:
            case 3:
                SetStep(4);
                g_api.PlaySfx(SFX_UI_CONFIRM);
                break;
            }
#ifdef VERSION_PSP
        } else if (pads & D_psp_08B42054) {
#else
        } else if (pads & PAD_TRIANGLE) {
#endif
            SetStep(7);
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 10; i++) {
            prim = prim->next;
        }
        prim->y0 = prim->y1 = self->ext.et_801B6F30.unk80 * 0xC + 0x1F;
        prim->y2 = prim->y3 = prim->y0 + 0xC;
        prim->drawMode = DRAW_COLORS;
        prim = prim->next;
        if (self->ext.et_801B6F30.unk82) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        if (self->ext.et_801B6F30.unk82 < self->ext.et_801B6F30.unk86) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        prim = prim->next;
        prim = prim->next;
        func_us_801B6124(prim, self);
        break;

    case 4:
#ifdef VERSION_PSP
        D_psp_08C630DC =
            self->ext.et_801B6F30.unk82 + self->ext.et_801B6F30.unk80;
#endif
        D_80097C98 = D_us_8018173C[self->ext.et_801B6F30.unk82 +
                                   self->ext.et_801B6F30.unk80]
                         .itemId -
                     0x80000000;
        break;

    case 7:
        if ((g_CutsceneFlags & 0x200) == 0) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 10; i++) {
                prim = prim->next;
            }
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            self->ext.et_801B6F30.unk7E = 0x400;
            self->ext.et_801B6F30.unk7C = 0x10;
            self->step++;
            g_CutsceneFlags |= 0x200;
        }
        break;

    case 8:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x64, 0x20, 0x2C, 1);
        if (!self->ext.et_801B6F30.unk7C) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 15; i++) {
                prim = prim->next;
            }
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            SetStep(9);
        }
        break;

    case 9:
        g_CutsceneFlags &= ~0x400;
        DestroyEntity(self);
        break;
    }
}

static char D_us_8018180C[] = _S("--------------");

void func_us_801B6E20(Primitive* prim, Entity* arg1) {
    s16 posX, posY;
    u16 enemyIndex;
    s32 i;
    u16 enemyId;
    u16 enemyMask;

    enemyIndex = arg1->ext.et_801B6F30.unk82 * 2;
    posY = 4;
    for (i = 0; i < 14; i++) {
        if ((i & 1) == 0) {
#ifdef VERSION_PSP
            posY += 12;
            posX = 4;
#else
            posX = 0;
            posY += 12;
#endif
        } else {
            posX = 0x78;
        }
        enemyId = D_us_80180E90[enemyIndex];
        if (enemyId != 0xFFFF) {
            enemyMask = g_CastleFlags[(enemyIndex >> 3) + ENEMY_LIST_190];
            if (enemyMask & (1 << (enemyIndex & 7))) {
                prim = func_us_801B1064(
                    prim, posX, posY, g_api.enemyDefs[enemyId].name, 0x196);
            } else {
                prim = func_us_801B1064(prim, posX, posY, D_us_8018180C, 0x191);
            }
        }
        enemyIndex++;
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801B6F30(Entity* self) {
    DRAWENV drawEnv;
    DR_ENV* dr_env;
    Primitive* prim;
    s32 primIndex;
    s16 enemyIndex;
    s32 i;
    u16 pads;
    Entity* tempEntity;

    RECT clipRect = {.x = 0x100, .y = 0x100, .w = 0x100, .h = 0x100};
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x140);
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            for (; prim != NULL; i++) {
                if (i < 6) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = prim->r1 = 0x80;
                    prim->g0 = prim->g1 = 0x80;
                    prim->b0 = prim->b1 = 0x80;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 8) {
                    prim->type = PRIM_G4;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x16;
                    prim->y2 = prim->y3 = 0x7A;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 10) {
                    prim->type = PRIM_GT4;
#ifdef VERSION_PSP
                    prim->tpage = 0x110;
                    prim->u0 = prim->u2 = (i - 8) * 0x74 + 4;
#else
                    prim->tpage = 0x114;
                    prim->u0 = prim->u2 = (i - 8) * 0x74;
#endif
                    prim->u1 = prim->u3 = prim->u0 + 0x74;
                    prim->v0 = prim->v1 = 0xD;
                    prim->v2 = prim->v3 = 0x61;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x1E;
                    prim->y2 = prim->y3 = 0x72;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 10) {
                    prim->type = PRIM_G4;
                    prim->y0 = prim->y1 = 0x2B;
                    prim->y2 = prim->y3 = 0x37;
#ifdef VERSION_PSP
                    PRED(prim) = 0x40;
                    PGRN(prim) = 0x10;
                    PBLU(prim) = 0x10;
#else
                    PRED(prim) = 0;
                    PGRN(prim) = 0x20;
                    PBLU(prim) = 0x40;
#endif
                    prim->priority = 0x1FB;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 13) {
                    prim->type = PRIM_GT4;
                    prim->tpage = 0x1E;
                    prim->clut = 0x17F;
                    prim->u0 = prim->u2 = 0x58;
                    prim->u1 = prim->u3 = 0x60;
                    prim->v0 = prim->v1 = (i - 11) * 8 + 0x70;
                    prim->v2 = prim->v3 = 0x78 - (i - 11) * 8;
                    prim->x0 = prim->x2 = 0x7C;
                    prim->x1 = prim->x3 = prim->x0 + 8;
                    prim->y0 = prim->y1 = (i - 11) * 0x60 + 0x14;
                    prim->y2 = prim->y3 = prim->y0 + 8;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 13) {
                    dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
                    if (dr_env != NULL) {
                        prim->type = PRIM_ENV;
                        prim->priority = 0x10;
                        prim->drawMode = DRAW_DEFAULT;
                        drawEnv = g_CurrentBuffer->draw;
                        drawEnv.isbg = 1;
                        drawEnv.clip = clipRect;
#ifdef VERSION_PSP
                        drawEnv.ofs[0] = 0;
#else
                        drawEnv.ofs[0] = 0x100;
#endif
                        drawEnv.ofs[1] = 0x100;
                        SetDrawEnv(dr_env, &drawEnv);
                    } else {
                        self->step = 0;
                        g_api.FreePrimitives(self->primIndex);
                        self->flags &= ~FLAG_HAS_PRIMS;
                        return;
                    }
                    prim = prim->next;
                    dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
                    if (dr_env != NULL) {
                        prim->type = PRIM_ENV;
                        prim->priority = 0x13;
                        prim->drawMode = DRAW_UNK_800;
                    } else {
                        self->step = 0;
                        g_api.FreePrimitives(self->primIndex);
                        self->flags &= ~FLAG_HAS_PRIMS;
                        return;
                    }
                } else {
                    prim->clut = 0x196;
                    prim->tpage = 0x1E;
                    prim->u1 = prim->v1 = 8;
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                }
                prim = prim->next;
            }
            self->ext.et_801B6F30.unk80 = 0;
            self->ext.et_801B6F30.unk82 = 0;
            self->ext.et_801B6F30.unk84 = 0;
        }
        break;

    case 1:
        if (g_CutsceneFlags & 0x400) {
            SetStep(2);
            self->ext.et_801B6F30.unk7C = 0;
            self->ext.et_801B6F30.unk7E = 0;
            g_CastleFlags[ENEMY_LIST_190] |= 1;
        }
        break;

    case 2:
        self->ext.et_801B6F30.unk7C++;
        self->ext.et_801B6F30.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x7C, 0x20, 7, 1);
        for (i = 0; i < 15; i++) {
            prim = prim->next;
        }
        func_us_801B6E20(prim, self);
        if (self->ext.et_801B6F30.unk7C == 0x10) {
            SetStep(3);
        }
        break;

    case 3:
        pads = g_pads[0].repeat;
        if (pads & PAD_DOWN) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80++;
            } else if (self->ext.et_801B6F30.unk82 < 0x42) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82++;
            }
        } else if (pads & PAD_UP) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80--;
            } else if (self->ext.et_801B6F30.unk82) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82--;
            }
        }
        if (pads & (PAD_R1 | PAD_R2)) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80 = 6;
            } else if (self->ext.et_801B6F30.unk82 < 0x42) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82 += 7;
                if (self->ext.et_801B6F30.unk82 > 0x42) {
                    self->ext.et_801B6F30.unk82 = 0x42;
                }
            }
        } else {
            if (pads & (PAD_L1 | PAD_L2)) {
                if (self->ext.et_801B6F30.unk80 > 0) {
                    g_api.PlaySfx(SFX_UI_MOVE);
                    self->ext.et_801B6F30.unk80 = 0;
                } else if (self->ext.et_801B6F30.unk82) {
                    g_api.PlaySfx(SFX_UI_MOVE);
                    if (self->ext.et_801B6F30.unk82 > 7) {
                        self->ext.et_801B6F30.unk82 -= 7;
                    } else {
                        self->ext.et_801B6F30.unk82 = 0;
                    }
                }
            }
        }
        if (pads & (PAD_LEFT | PAD_RIGHT)) {
            if (self->ext.et_801B6F30.unk84) {
                self->ext.et_801B6F30.unk84 = 0;
            } else {
                self->ext.et_801B6F30.unk84 = 1;
            }
            g_api.PlaySfx(SFX_UI_MOVE);
        }
        pads = g_pads[0].tapped;
#ifdef VERSION_PSP
        if (pads & D_psp_08B42050) {
#else
        if (pads & PAD_CROSS) {
#endif
            enemyIndex =
                (self->ext.et_801B6F30.unk82 + self->ext.et_801B6F30.unk80) *
                    2 +
                self->ext.et_801B6F30.unk84;
            if (g_CastleFlags[(enemyIndex >> 3) + ENEMY_LIST_190] &
                (1 << (enemyIndex & 7))) {
                g_api.PlaySfx(SFX_UI_CONFIRM);
                SetStep(4);
            } else {
                g_api.PlaySfx(SFX_UI_ERROR);
            }
#ifdef VERSION_PSP
        } else if (pads & D_psp_08B42054) {
#else
        } else if (pads & PAD_TRIANGLE) {
#endif
            SetStep(7);
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 10; i++) {
            prim = prim->next;
        }
        if (!self->ext.et_801B6F30.unk84) {
            prim->x0 = prim->x2 = 9;
            prim->x1 = prim->x3 = 0x80;
        } else {
            prim->x0 = prim->x2 = 0x80;
            prim->x1 = prim->x3 = 0xF7;
        }
        prim->y0 = prim->y1 = self->ext.et_801B6F30.unk80 * 0xC + 0x1F;
        prim->y2 = prim->y3 = prim->y0 + 0xC;
        prim->drawMode = DRAW_COLORS;
        prim = prim->next;
        if (self->ext.et_801B6F30.unk82) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        if (self->ext.et_801B6F30.unk82 < 0x42) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        prim = prim->next;
        prim = prim->next;
        func_us_801B6E20(prim, self);
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            if (g_api.func_80131F68()) {
                g_api.PlaySfx(SET_STOP_MUSIC);
            }
            self->step_s++;
            break;

        case 1:
            if (!g_api.func_80131F68()) {
                if ((g_CutsceneFlags & 0x200) == 0) {
                    prim = &g_PrimBuf[self->primIndex];
                    for (i = 0; i < 10; i++) {
                        prim = prim->next;
                    }
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                    prim->drawMode = DRAW_HIDE;
                    self->ext.et_801B6F30.unk7E = 0x400;
                    self->ext.et_801B6F30.unk7C = 0x10;
                    SetStep(5);
                }
            }
            break;
        }
        break;

    case 5:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
#ifdef VERSION_PSP
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C, 0x7C, 0x20, 7, 1);
#else
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C, 0x74, 0x20, 7, 1);
#endif
        if (!self->ext.et_801B6F30.unk7C) {
            for (i = 0; i < 6; i++) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            for (i = 0; i < 9; i++) {
                prim = prim->next;
            }
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            tempEntity = self + 1;
            CreateEntityFromCurrentEntity(E_ID(ID_2F), tempEntity);
            tempEntity->params =
                (self->ext.et_801B6F30.unk82 + self->ext.et_801B6F30.unk80) *
                    2 +
                self->ext.et_801B6F30.unk84;
            g_CutsceneFlags &= ~0x400;
            SetStep(1);
        }
        break;

    case 7:
        if ((g_CutsceneFlags & 0x200) == 0) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 10; i++) {
                prim = prim->next;
            }
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            self->ext.et_801B6F30.unk7E = 0x400;
            self->ext.et_801B6F30.unk7C = 0x10;
            self->step++;
            g_CutsceneFlags |= 0x200;
        }
        break;

    case 8:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x74, 0x20, 7, 1);
        if (!self->ext.et_801B6F30.unk7C) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 15; i++) {
                prim = prim->next;
            }
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            SetStep(9);
        }
        break;

    case 9:
        g_CutsceneFlags &= ~0x400;
        DestroyEntity(self);
        break;
    }
}

#ifdef VERSION_PSP
extern const char** D_us_8018181C;
extern const char** D_us_8018187C;
#else
static const char* D_us_8018181C[] = {
    _S("None"),
    _S("だいハート"),
    _S("$1"),
    _S("$25"),
    _S("$50"),
    _S("$100"),
    _S("$250"),
    _S("$400"),
    _S("$700"),
    _S("$1000"),
    _S("$2000"),
    _S("$5000"),
    _S("ハートのうつわ"),
    _S("にく"),
    _S("ナイフ(サブ)"),
    _S("Axe"),
    _S("クロス(サブ)"),
    _S("せいすい(サブ)"),
    _S("とけい(サブ)"),
    _S("バイブル(サブ)"),
    _S("けんじのいし(サブ)"),
    _S("ビブーティ(サブ)"),
    _S("アグネアのぶき(サブ)"),
    _S("ライフアップポーション")};
static const char* D_us_8018187C[] = {
    _S("HOL"), _S("DRK"), _S("FIR"), _S("THU"), _S("ICE"), _S("H2O"),
    _S("STN"), _S("PSN"), _S("CUR"), _S("CUT"), _S("HIT")};
#endif

static u16 D_us_801818A8[] = {
    ELEMENT_HOLY,  ELEMENT_DARK,  ELEMENT_FIRE,  ELEMENT_THUNDER,
    ELEMENT_ICE,   ELEMENT_WATER, ELEMENT_STONE, ELEMENT_POISON,
    ELEMENT_CURSE, ELEMENT_CUT,   ELEMENT_HIT};

#ifdef VERSION_PSP
extern const char** D_us_801818C0;
#else
static const char* D_us_801818C0[] = {
    _S("LV"),         _S("HP"),       "$EF",       _S("Exp"),
    _S("Drop Items"), _S("No."),      "\x1F\x1F",  _S("Strong VS."),
    _S("Immune"),     _S("Weak VS."), _S("Absorb")};
#endif

static const char* D_us_801818EC[] = {_S("????????")};
static const char* D_us_801818F0[] = {_S("????")};

const char* func_us_801B7C94(u16 itemId) {
    const char* name;
    if (itemId >= 0x80) {
        itemId -= 0x80;
        if (itemId < NUM_HAND_ITEMS) {
            name = g_api.equipDefs[itemId].name;
        } else {
            itemId -= NUM_HAND_ITEMS;
            name = g_api.accessoryDefs[itemId].name;
        }
    } else {
        name = D_us_8018181C[itemId];
    }
    return name;
}

Primitive* func_us_801B7D10(Primitive* prim, u16 arg1, s16 posY) {
    s16 x = 0x84;
    s16 y = 8;
    s32 i;
    if ((arg1 & ELEMENT_ALL) == 0) {
        prim = func_us_801B1064(prim, 0x84, posY, D_us_8018181C[0], 0x159);
    } else {
        for (i = 0; i < LEN(D_us_801818A8); i++) {
            if (arg1 & D_us_801818A8[i]) {
                prim = func_us_801B1064(prim, x, posY, D_us_8018187C[i], 0x15C);
                x += 0x1C;
            }
        }
    }
    return prim;
}

void func_us_801B7DF8(Primitive* prim, Entity* arg1, s16 enemyId) {
    s16 posX, posY;
    s32 i;
    EnemyDef* enemyDef;
    u8 params;
    u16 clut;

    enemyDef = &g_api.enemyDefs[enemyId];
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    posX = 0x80;
    posY = 0x34;
    prim = func_us_801B1064(
        prim, posX, posY, D_us_801818C0[7], 0x196); // "Strong VS."
    prim = func_us_801B7D10(prim, enemyDef->strengths, 0x3D);
    posY += 0x14;
    prim =
        func_us_801B1064(prim, posX, posY, D_us_801818C0[8], 0x196); // "Immune"
    prim = func_us_801B7D10(prim, enemyDef->immunes, 0x51);
    posY += 0x14;
    prim = func_us_801B1064(
        prim, posX, posY, D_us_801818C0[9], 0x196); // "Weak VS."
    prim = func_us_801B7D10(prim, enemyDef->weaknesses, 0x65);
    posY += 0x14;
    prim = func_us_801B1064(
        prim, posX, posY, D_us_801818C0[10], 0x196); // "Absorb"
    prim = func_us_801B7D10(prim, enemyDef->absorbs, 0x79);

    posX = 0x18;
    prim = func_us_801B1064(prim, posX, 0x28, enemyDef->name, 0x196);

    posX += 0xA0;
    prim = func_us_801B1064(prim, posX, 0x28, D_us_801818C0[5], 0x196); // "No."

    posX = 0xD0;
    func_us_801B3EC8(prim, arg1->params + 1, 3);
    for (i = 0; i < 3; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = 0x28;
        prim = prim->next;
        posX += 8;
    }
    posX = 0x1C;
    prim = func_us_801B1064(prim, posX, 0x34, D_us_801818C0[0], 0x196); // "LV"
    posX += 0x12;
    if (arg1->params) {
        func_us_801B3EC8(prim, enemyDef->level, 2);
    } else {
        func_us_801B3FB4(prim, D_us_801818C0[6], 2, 1); // "??"
    }
    for (i = 0; i < 2; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = 0x34;
        if (prim->drawMode != DRAW_HIDE) {
            posX += 8;
        }
        prim = prim->next;
    }
    posX = 0x44;
    prim = func_us_801B1064(prim, posX, 0x34, D_us_801818C0[1], 0x196); // "HP"
    posX += 0x12;
    if (enemyDef->hitPoints > 9999) {
        func_us_801B3FB4(prim, D_us_801818F0[0], 4, 1); // "????"
    } else {
        func_us_801B3EC8(prim, enemyDef->hitPoints, 4);
    }
    for (i = 0; i < 4; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = 0x34;
        if (prim->drawMode != DRAW_HIDE) {
            posX += 8;
        }
        prim = prim->next;
    }
    posX = 0x80;
    prim = func_us_801B1064(prim, posX, 0xA6, D_us_801818C0[3], 0x196); // "Exp"
    posX += 0x1C;
    func_us_801B3EC8(prim, enemyDef->exp, 4);
    for (i = 0; i < 4; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = 0xA6;
        prim = prim->next;
        posX += 8;
    }
    posX = 0x80;
    prim = func_us_801B1064(
        prim, posX, 0x85, D_us_801818C0[4], 0x196); // "Drop Items"
    posX = enemyDef->uncommonItemId;
    if (posX != 0) {
        clut = 0x196;
    } else {
        clut = 0x159;
    }
    prim = func_us_801B1064(prim, 0x84, 0x8F, func_us_801B7C94(posX), clut);
    params = arg1->params;
    if ((g_CastleFlags[(params >> 3) + ENEMY_LIST_RAREDROP_1B0] &
         (1 << (params & 7))) ||
        !enemyDef->rareItemId) {
        prim = func_us_801B1064(
            prim, 0x84, 0x99, func_us_801B7C94(enemyDef->rareItemId), clut);
    } else {
        prim = func_us_801B1064(
            prim, 0x84, 0x99, D_us_801818EC[0], 0x196); // "????????"
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801B8234(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s16 enemyIndex;
    u16 enemyId;
    u16 pads;
    u8* pix;
    char* s3;
    EnemyDef* enemyDef;
    s32 pad[12];

    enemyId = D_us_80180E90[self->params];
    switch (self->step) {
    case 0:
#ifdef VERSION_PSP
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0xAE);
#else
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x86);
#endif
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            for (; prim != NULL; i++) {
                if (i < 6) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = prim->r1 = 0x80;
                    prim->g0 = prim->g1 = 0x80;
                    prim->b0 = prim->b1 = 0x80;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 8) {
                    prim->type = PRIM_G4;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x1E;
                    prim->y2 = prim->y3 = 0xDE;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
#ifdef VERSION_PSP
                } else if (i < 10) {
                    prim->type = PRIM_GT4;
                    prim->tpage = 0x110;
                    prim->u0 = prim->u2 = (i - 9) * 0x78 + 0x80;
                    prim->u1 = prim->u3 = prim->u0 + 0x78;
                    prim->v0 = prim->v1 = 0x26;
                    prim->v2 = prim->v3 = prim->v0 + 0xB0;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x26;
                    prim->y2 = prim->y3 = 0xD6;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 10) {
                    prim->type = PRIM_GT4;
                    prim->tpage = 0x2110;
                    prim->u0 = prim->u2 = 0x20;
                    prim->u1 = prim->u3 = prim->u0 + 0x5F;
                    prim->v0 = prim->v1 = 0;
                    prim->v2 = prim->v3 = prim->v0 + 0x6F;
                    prim->x0 = prim->x2 = 0x1C;
                    prim->x1 = prim->x3 = prim->x0 + (prim->u1 - prim->u0);
                    prim->y0 = prim->y1 = 0x3C;
                    prim->y2 = prim->y3 = prim->y0 + (prim->v2 - prim->v0);
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 11) {
                    prim->tpage = 0x10;
                    prim->clut = 0x1A1;
                    prim->u0 = 0;
                    prim->v0 = 0x80;
                    prim->u1 = 0x80;
                    prim->v1 = 0x40;
                    prim->x0 = 0x84;
                    prim->y0 = 0x38;
                    prim->priority = 0x12;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 12) {
                    prim->tpage = 0x10;
                    prim->clut = 0x1A1;
                    prim->u0 = 0;
                    prim->v0 = 0xC0;
                    prim->v1 = 0x20;
                    prim->u1 = 0xF0;
                    prim->x0 = 0xA;
                    prim->y0 = 0xB4;
                    prim->priority = 0x12;
                    prim->drawMode = DRAW_HIDE;
#else
                } else if (i < 10) {
                    prim->type = PRIM_GT4;
                    prim->tpage = 0x114;
                    prim->u0 = prim->u2 = (i - 9) * 0x70 + 0x80;
                    prim->u1 = prim->u3 = prim->u0 + 0x70;
                    prim->v0 = prim->v1 = 0x26;
                    prim->v2 = prim->v3 = prim->v0 + 0xB0;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x26;
                    prim->y2 = prim->y3 = 0xD6;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 10) {
                    prim->tpage = 0x110;
                    prim->u0 = 0x20;
                    prim->v0 = 0;
                    prim->u1 = 0x60;
                    prim->v1 = 0x70;
                    prim->x0 = 0x18;
                    prim->y0 = 0x3C;
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 11) {
                    prim->tpage = 0x10;
                    prim->clut = 0x1A1;
                    prim->u0 = 0;
                    prim->v0 = 0xC0;
                    prim->v1 = 0x20;
                    prim->u1 = 0xF0;
                    prim->x0 = 0x18;
                    prim->y0 = 0xB4;
                    prim->priority = 0x12;
                    prim->drawMode = DRAW_HIDE;
#endif
                } else {
                    prim->clut = 0x196;
                    prim->tpage = 0x1E;
                    prim->u1 = prim->v1 = 8;
                    prim->priority = 0x12;
                    prim->drawMode = DRAW_HIDE;
                }
                prim = prim->next;
            }
        }
        break;

    case 1:
        switch (self->step_s) {
        case 0:
            self->step_s++;
            break;

        case 1:
            if (g_api.LoadMonsterLibrarianPreview(self->params)) {
                self->step_s++;
            }
            break;

        case 2:
            if (!g_IsUsingCd) {
                self->step_s++;
            }
            break;

        case 3:
            func_us_801B11A0(0, 0x180, 0x100, 0x60);
            pix = g_Pix[0];
#ifdef VERSION_PSP
            for (i = 0; i < 4; i++) {
                s3 = D_psp_092A5F98[i];
            }
            enemyDef = &g_api.enemyDefs[enemyId];
            s3 = D_psp_092A5F48[self->params];
            func_us_801B0C40(pix, s3, 0, 0x1C0, 0x6E);
            s3 = D_psp_092A5F40[self->params];
            func_us_801B0C40(pix, s3, 0, 0x1D0, 0x6E);
#else
            s3 = D_us_80180FB4[self->params];
            func_us_801B0C40(pix, s3, 0, 0x1C0, 0x6E);
#endif
            self->step_s++;
            break;

        case 4:
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 10; i++) {
                prim = prim->next;
            }
            func_us_801B7DF8(prim, self, enemyId);
            self->ext.et_801B6F30.unk7C = 0;
            self->ext.et_801B6F30.unk7E = 0;
            SetStep(2);
        }
        break;

    case 2:
        self->ext.et_801B6F30.unk7C++;
        self->ext.et_801B6F30.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
#ifdef VERSION_PSP
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x80, 0x20, 7, 0);
#else
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x78, 0x20, 7, 0);
#endif
        if (self->ext.et_801B6F30.unk7C == 0x10) {
            SetStep(3);
        }
        break;

    case 3:
        pads = g_pads[0].repeat;
        if (pads & PAD_RIGHT) {
#ifdef VERSION_PSP
            for (enemyIndex = self->params + 1; enemyIndex < 0x94;
                 enemyIndex++) {
#else
            for (enemyIndex = self->params + 1; enemyIndex < 0x92;
                 enemyIndex++) {
#endif
                if (g_CastleFlags[(enemyIndex >> 3) + ENEMY_LIST_190] &
                        (1 << (enemyIndex & 7)) &&
                    D_us_80180E90[self->params] != 0xFFFF) {
                    self->params = enemyIndex;
                    SetStep(4);
                    break;
                }
            }
        } else if (pads & PAD_LEFT) {
            for (enemyIndex = self->params - 1; enemyIndex >= 0; enemyIndex--) {
                if (g_CastleFlags[(enemyIndex >> 3) + ENEMY_LIST_190] &
                        (1 << (enemyIndex & 7)) &&
                    D_us_80180E90[self->params] != 0xFFFF) {
                    self->params = enemyIndex;
                    SetStep(4);
                    break;
                }
            }
        }
        pads = g_pads[0].tapped;
#ifdef VERSION_PSP
        if (pads & D_psp_08B42054) {
#else
        if (pads & PAD_TRIANGLE) {
#endif
            SetStep(7);
        }
        break;

    case 4:
        self->ext.et_801B6F30.unk7E = 0x400;
        self->ext.et_801B6F30.unk7C = 0x10;
        SetStep(5);
        break;

    case 5:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
#ifdef VERSION_PSP
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C, 0x80, 0x20, 7, 0);
#else
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C, 0x74, 0x20, 7, 0);
#endif
        if (!self->ext.et_801B6F30.unk7C) {
            SetStep(1);
        }
        break;

    case 7:
        if ((g_CutsceneFlags & 0x200) == 0) {
            self->ext.et_801B6F30.unk7E = 0x400;
            self->ext.et_801B6F30.unk7C = 0x10;
            self->step++;
        }
        break;

    case 8:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
#ifdef VERSION_PSP
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x80, 0x20, 7, 0);
#else
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x74, 0x20, 7, 0);
#endif
        if (!self->ext.et_801B6F30.unk7C) {
            g_CutsceneFlags |= 0x400;
            DestroyEntity(self);
        }
        break;
    }
}

#ifdef VERSION_PSP
extern const char** D_us_801818F4;
#else
static const char* D_us_801818F4[] = {
    _S("Metamorphosis 1"),
    _S("Prologue"),
    _S("Dance of Illusions"),
    _S("Moonlight Nocturne"),
    _S("Prayer"),
    _S("Dracula's Castle"),
    _S("Dance of Gold"),
    _S("Marble Gallery"),
    _S("Tower of Mist"),
    _S("Wood Carving Partita"),
    _S("Door of Holy Spirits"),
    _S("Festival of Servants"),
    _S("Land of Benediction"),
    _S("Requiem for the Gods"),
    _S("Crystal Teardrop"),
    _S("Abandoned Pit"),
    _S("Rainbow Cemetery"),
    _S("Silence"),
    _S("Lost Painting"),
    _S("Dance of Pales"),
    _S("Curse Zone"),
    _S("Enchanted Banquet"),
    _S("Wandering Ghosts"),
    _S("The Tragic Prince"),
    _S("Door to the Abyss"),
    _S("Heavenly Doorway"),
    _S("Death Ballad"),
    _S("Blood Relations"),
    _S("Metamorphosis 2"),
    _S("Finale Toccata"),
    _S("Black Banquet"),
    _S("Metamorphosis 3"),
    _S("I am the wind"),
};
#endif

static u16 D_us_80181978[] = {
    MU_METAMORPHOSIS,
    MU_PROLOGUE,
    MU_DANCE_OF_ILLUSIONS,
    MU_MOONLIGHT_NOCTURNE,
    MU_PRAYER,
    MU_DRACULAS_CASTLE,
    MU_DANCE_OF_GOLD,
    MU_MARBLE_GALLERY,
    MU_TOWER_OF_MIST,
    MU_WOOD_CARVING_PARTITA,
    MU_DOOR_OF_HOLY_SPIRITS,
    MU_FESTIVAL_OF_SERVANTS,
    MU_LAND_OF_BENEDICTION,
    MU_REQUIEM_FOR_THE_GODS,
    MU_CRYSTAL_TEARDROPS,
    MU_ABANDONED_PIT,
    MU_RAINBOW_CEMETERY,
    MU_SILENCE,
    MU_LOST_PAINTING,
    MU_DANCE_OF_PALES,
    MU_CURSE_ZONE,
    MU_ENCHANTED_BANQUET,
    MU_WANDERING_GHOSTS,
    MU_THE_TRAGIC_PRINCE,
    MU_THE_DOOR_TO_THE_ABYSS,
    MU_HEAVENLY_DOORWAY,
    MU_DEATH_BALLAD,
    MU_BLOOD_RELATIONS,
    MU_METAMORPHOSIS_II,
    MU_FINAL_TOCATTA,
    MU_BLACK_BANQUET,
    MU_METAMORPHOSIS_III,
    MU_STAFF_CREDITS,
};

void func_us_801B8958(Primitive* prim, Entity* self) {
    s16 posY;
    s32 i, j;

    posY = 16;
    j = self->ext.et_801B6F30.unk82;
    for (i = 0; i < 7; i++, j++) {
        prim = func_us_801B1064(prim, 16, posY, D_us_801818F4[j], 0x196);
        posY += 12;
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801B8A00(Entity* self) {
    DRAWENV drawEnv;
    DR_ENV* dr_env;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    u16 pads;
    s16 sfxIndex;
    u8* pix;

    RECT clipRect = {.x = 0x100, .y = 0x100, .w = 0x100, .h = 0x100};
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x140);
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
#ifdef VERSION_PSP
            self->ext.et_801B6F30.unk86 = 0;
#endif
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            for (; prim != NULL; i++) {
                if (i < 6) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = prim->r1 = 0x80;
                    prim->g0 = prim->g1 = 0x80;
                    prim->b0 = prim->b1 = 0x80;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 8) {
                    prim->type = PRIM_G4;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x16;
                    prim->y2 = prim->y3 = 0x7A;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 10) {
                    prim->type = PRIM_GT4;
#ifdef VERSION_PSP
                    prim->tpage = 0x110;
#else
                    prim->tpage = 0x114;
#endif
                    prim->u0 = prim->u2 = (i - 8) * 0x6C + 8;
                    prim->u1 = prim->u3 = prim->u0 + 0x6C;
                    prim->v0 = prim->v1 = 0xE;
                    prim->v2 = prim->v3 = 0x62;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x1E;
                    prim->y2 = prim->y3 = 0x72;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 10) {
                    prim->type = PRIM_G4;
                    prim->y0 = prim->y1 = 0x4B;
                    prim->y2 = prim->y3 = 0x57;
#ifdef VERSION_PSP
                    PRED(prim) = 0x40;
                    PGRN(prim) = 0x10;
                    PBLU(prim) = 0x10;
#else
                    PRED(prim) = 0;
                    PGRN(prim) = 0x20;
                    PBLU(prim) = 0x40;
#endif
                    prim->priority = 0x1FB;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 13) {
                    prim->type = PRIM_GT4;
                    prim->tpage = 0x1E;
                    prim->clut = 0x17F;
                    prim->u0 = prim->u2 = 0x58;
                    prim->u1 = prim->u3 = 0x60;
                    prim->v0 = prim->v1 = (i - 11) * 8 + 0x70;
                    prim->v2 = prim->v3 = 0x78 - (i - 11) * 8;
                    prim->x0 = prim->x2 = 0x7C;
                    prim->x1 = prim->x3 = prim->x0 + 8;
                    prim->y0 = prim->y1 = (i - 11) * 0x60 + 0x14;
                    prim->y2 = prim->y3 = prim->y0 + 8;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 13) {
                    dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
                    if (dr_env != NULL) {
                        prim->type = PRIM_ENV;
                        prim->priority = 0x10;
                        prim->drawMode = DRAW_DEFAULT;
                        drawEnv = g_CurrentBuffer->draw;
                        drawEnv.isbg = 1;
                        drawEnv.clip = clipRect;
#ifdef VERSION_PSP
                        drawEnv.ofs[0] = 0;
#else
                        drawEnv.ofs[0] = 0x100;
#endif
                        drawEnv.ofs[1] = 0x100;
                        SetDrawEnv(dr_env, &drawEnv);
                    } else {
                        self->step = 0;
                        g_api.FreePrimitives(self->primIndex);
                        self->flags &= ~FLAG_HAS_PRIMS;
                        return;
                    }
                    prim = prim->next;
                    dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
                    if (dr_env != NULL) {
                        prim->type = PRIM_ENV;
                        prim->priority = 0x13;
                        prim->drawMode = DRAW_UNK_800;
                    } else {
                        self->step = 0;
                        g_api.FreePrimitives(self->primIndex);
                        self->flags &= ~FLAG_HAS_PRIMS;
                        return;
                    }
#ifdef VERSION_PSP
                } else if (i == 14) {
                    prim->tpage = 0x10;
                    prim->clut = 0x1A1;
                    prim->u0 = 0;
                    prim->v0 = 0x80;
                    prim->u1 = 0xE0;
                    prim->v1 = 0x20;
                    prim->x0 = 0x10;
                    prim->y0 = 0x14;
                    prim->priority = 0x12;
                    prim->drawMode = DRAW_HIDE;
#endif
                } else {
                    prim->clut = 0x196;
                    prim->tpage = 0x1E;
                    prim->u1 = prim->v1 = 8;
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                }
                prim = prim->next;
            }
            self->ext.et_801B6F30.unk80 = 0;
            self->ext.et_801B6F30.unk82 = 0;
#ifdef VERSION_PSP
            self->ext.et_801B6F30.unk84 = 0;
#endif
        }
        break;

    case 1:
#ifdef VERSION_PSP
        if (!self->step_s) {
            func_us_801B11A0(0, 0x180, 0x100, 0x60);
            pix = g_Pix[0];
            pix = func_psp_09269FF0(D_psp_092A4CC8, pix, 0, 0x180);
            self->step_s++;
            break;
        }
#endif
        if (g_CutsceneFlags & 0x400) {
            SetStep(2);
            self->ext.et_801B6F30.unk7C = 0;
            self->ext.et_801B6F30.unk7E = 0;
        }
        break;

    case 2:
        self->ext.et_801B6F30.unk7C++;
        self->ext.et_801B6F30.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x74, 0x20, 7, 1);
        for (i = 0; i < 15; i++) {
            prim = prim->next;
        }
#ifdef VERSION_PSP
        func_psp_0926ADD8(prim, self);
#else
        func_us_801B8958(prim, self);
#endif
        if (self->ext.et_801B6F30.unk7C == 0x10) {
            g_api.PlaySfx(SET_STOP_SEQ);
            SetStep(3);
        }
        break;

    case 3:
#ifdef VERSION_PSP
        pads = g_pads[0].repeat;
        if (pads & PAD_DOWN) {
            if (self->ext.et_801B6F30.unk80 < 3) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80++;
            }
        } else if (pads & PAD_UP) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80--;
            }
        }
        if (pads & (PAD_LEFT | PAD_RIGHT)) {
            if (self->ext.et_801B6F30.unk84) {
                self->ext.et_801B6F30.unk84 = 0;
            } else {
                self->ext.et_801B6F30.unk84 = 1;
            }
            g_api.PlaySfx(SFX_UI_MOVE);
        }
#else
        pads = g_pads[0].repeat;
        if (pads & PAD_DOWN) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80++;
            } else if (self->ext.et_801B6F30.unk82 < 0x1A) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82++;
            }
        } else if (pads & PAD_UP) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80--;
            } else if (self->ext.et_801B6F30.unk82) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82--;
            }
        }
        if (pads & (PAD_R1 | PAD_R2)) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80 = 6;
            } else if (self->ext.et_801B6F30.unk82 < 0x1A) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82 += 7;
                if (self->ext.et_801B6F30.unk82 > 0x1A) {
                    self->ext.et_801B6F30.unk82 = 0x1A;
                }
            }
        } else if (pads & (PAD_L1 | PAD_L2)) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80 = 0;
            } else if (self->ext.et_801B6F30.unk82) {
                g_api.PlaySfx(SFX_UI_MOVE);
                if (self->ext.et_801B6F30.unk82 > 7) {
                    self->ext.et_801B6F30.unk82 -= 7;
                } else {
                    self->ext.et_801B6F30.unk82 = 0;
                }
            }
        }
#endif
        pads = g_pads[0].tapped;
#ifdef VERSION_PSP
        if (pads & D_psp_08B42050) {
#else
        if (pads & PAD_CROSS) {
#endif
            g_api.PlaySfx(SFX_UI_CONFIRM);
            SetStep(4);
#ifdef VERSION_PSP
        } else if (pads & D_psp_08B42054) {
#else
        } else if (pads & PAD_TRIANGLE) {
#endif
            SetStep(6);
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 10; i++) {
            prim = prim->next;
        }
#ifdef VERSION_PSP
        if (!self->ext.et_801B6F30.unk84) {
            prim->x0 = prim->x2 = 0x11;
            prim->x1 = prim->x3 = 0x80;
        } else {
            prim->x0 = prim->x2 = 0x80;
            prim->x1 = prim->x3 = 0xEF;
        }
        prim->y0 = prim->y1 = self->ext.et_801B6F30.unk80 * 12 + 0x3F;
#else
        prim->x0 = prim->x2 = 0x11;
        prim->x1 = prim->x3 = 0xEF;
        prim->y0 = prim->y1 = self->ext.et_801B6F30.unk80 * 12 + 0x1E;
#endif
        prim->y2 = prim->y3 = prim->y0 + 12;
        prim->drawMode = DRAW_COLORS;
        prim = prim->next;
#ifdef VERSION_PSP
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim->drawMode = DRAW_HIDE;
#else
        if (self->ext.et_801B6F30.unk82) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        if (self->ext.et_801B6F30.unk82 < 0x1A) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
#endif
        prim = prim->next;
        prim = prim->next;
        prim = prim->next;
#ifdef VERSION_PSP
        func_psp_0926ADD8(prim, self);
#else
        func_us_801B8958(prim, self);
#endif
        break;

    case 4:
#ifdef VERSION_PSP
        switch (self->step_s) {
        case 0:
            func_892A620(1, 1);
            g_api.PlaySfx(SET_STOP_MUSIC);
            self->ext.et_801B6F30.unk86 = 1;
            self->step_s++;
            break;

        case 1:
            if (!g_api.func_80131F68() && (g_CutsceneFlags & 0x200) == 0) {
                sfxIndex = self->ext.et_801B6F30.unk84 +
                           self->ext.et_801B6F30.unk80 * 2;
                g_api.PlaySfx(D_us_80181978[sfxIndex]);
                SetStep(3);
            }
            break;
        }
        break;
#else
        FntPrint("step_s %x\n", self->step_s);
        switch (self->step_s) {
        case 0:
            g_api.PlaySfx(SET_STOP_MUSIC);
            self->poseTimer = 0x30;
            self->step_s++;
            break;

        case 1:
            if (!--self->poseTimer) {
                self->step_s++;
            }
            break;

        case 2:
            if (!g_api.func_80131F68() && (g_CutsceneFlags & 0x200) == 0) {
                sfxIndex =
                    self->ext.et_801B6F30.unk80 + self->ext.et_801B6F30.unk82;
                g_api.PlaySfx(D_us_80181978[sfxIndex]);
                SetStep(3);
            }
            break;
        }
        break;
#endif

    case 6:
        if (g_api.func_80131F68()) {
            g_api.PlaySfx(SET_STOP_MUSIC);
        }
        self->step++;
        break;

    case 7:
        if ((g_CutsceneFlags & 0x200) == 0) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 10; i++) {
                prim = prim->next;
            }
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            self->ext.et_801B6F30.unk7E = 0x400;
            self->ext.et_801B6F30.unk7C = 0x10;
            self->step++;
            g_api.PlaySfx(0x202);
            g_CutsceneFlags |= 0x200;
        }
        break;

    case 8:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x74, 0x20, 7, 1);
        if (!self->ext.et_801B6F30.unk7C) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 15; i++) {
                prim = prim->next;
            }
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            SetStep(9);
        }
        break;

    case 9:
#ifdef VERSION_PSP
        if (self->ext.et_801B6F30.unk86) {
            g_api.PlaySfx(0x302);
        }
#endif
        g_CutsceneFlags &= ~0x400;
        DestroyEntity(self);
        return;
    }
}
