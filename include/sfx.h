#ifndef SFX_H
#define SFX_H

/**
 * File: sfx.h
 * Description: SOTN Sound Effects
 *
 * Glossary:
 * NA = North America
 * JP = Japan
 * SE = Sound Effect
 * SY = System
 * PL = Player
 * WP = Weapon
 * EV = Environment
 * CS = Cutscene
 * IT = Item
 * EN = Enemy
 * VO = Voice
 * BO = Boss
 * DR = Dracula
 * DE = Death
 * SH = Shaft
 * ML = Master Librarian
 * FE = Ferryman
 * SU = Succubus
 * AL = Alucard
 * MA = Maria
 * RI = Richter
 * WO = Form of Wolf
 * BT = Form of Bat
 * MU = Music
 */

// playSfx flags
typedef enum { MONO_SOUND, STEREO_SOUND } soundMode;

enum SfxModes {
    SFX_MODE_CHANNELS_12_19,
    SFX_MODE_CHANNELS_22_23,
    SFX_MODE_RELEASE_22_23,
    SFX_MODE_CHANNELS_20_21,
    SFX_MODE_SCRIPT_NO_PAUSE = 5
};

#define SET_VOLUME_22_23 1
#define SET_SOUNDMODE_MONO 5
#define SET_SOUNDMODE_STEREO 6
#define SET_STOP_SEQ 7
#define SET_STOP_MUSIC 0xA
#define SET_UNK_0B 0xB
#define SET_UNK_0C 0xC
#define SET_SOUND_WAIT 0xD
#define SET_PAUSE_SFX_SCRIPTS 0xE
#define SET_UNPAUSE_SFX_SCRIPTS 0xF
#define SET_UNK_10 0x10
#define SET_UNK_11 0x11
#define SET_UNK_12 0x12
#define SET_UNK_80 0x80
#define SET_UNK_82 0x82
#define SET_UNK_90 0x90
#define SET_UNK_92 0x92
#define SET_RELEASE_RATE_HIGH_20_21 0xa1
#define SET_RELEASE_RATE_LOW_20_21 0xa3
#define SET_UNK_A6 0xA6
#define SET_RELEASE_RATE_LOW_22_23 0xa7
#define SET_KEY_ON_20_21 0xa4
#define SET_KEY_ON_22_23 0xa8

#define CD_SOUND_COMMAND_FADE_OUT_2 2
#define CD_SOUND_COMMAND_FADE_OUT_1 3
#define CD_SOUND_COMMAND_START_XA 4
#define CD_SOUND_COMMAND_6 6
#define CD_SOUND_COMMAND_7 7
#define CD_SOUND_COMMAND_8 8
#define CD_SOUND_COMMAND_10 10
#define CD_SOUND_COMMAND_12 12
#define CD_SOUND_COMMAND_14 14
#define CD_SOUND_COMMAND_16 16

// SEQ music tracks
// While there is unused SEQ data in DRA, LIB and DAI are the only two
// overlays that use sequenced music heard in-game.
//
// For the PSP port, the SEQ files were replaced with pre-recorded versions
// and saved as ATRAC3 streaming audio.  To reference these new audio streams,
// the loop points for "Lost Painting" and "Curse Zone" were also replaced.
// Reusing the loop point IDs makes sense as .AT3 files support looping.
enum SeqTracks {
    MU_SEQ_LIBRARIAN = 0x202,
    MU_SEQ_CONFESSIONAL_BELLS = 0x204,
    MU_SEQ_LIBRARIAN_PSP = 0x302,
    MU_SEQ_CONFESSIONAL_BELLS_PSP = 0x304
};

// XA music tracks
// LOOP_POINT means it starts playing from part way into the song
enum {
    // us: includes US build
    // jp: includes HD and PSP builds
    /* us:0x301, jp:0x301 */ MU_LOST_PAINTING = 0x301,
    /* us:0x302, jp:0x302 */ MU_LOST_PAINTING_LOOP_POINT,
    /* us:0x303, jp:0x303 */ MU_CURSE_ZONE,
    /* us:0x304, jp:0x304 */ MU_CURSE_ZONE_LOOP_POINT,
    /* us:0x305, jp:0x305 */ MU_REQUIEM_FOR_THE_GODS,
    /* us:0x306, jp:0x306 */ MU_REQUIEM_FOR_THE_GODS_LOOP_POINT,
    /* us:0x307, jp:0x307 */ MU_RAINBOW_CEMETERY,
    /* us:0x308, jp:0x308 */ MU_RAINBOW_CEMETERY_LOOP_POINT,
    /* us:0x309, jp:0x309 */ MU_WOOD_CARVING_PARTITA,
    /* us:0x30A, jp:0x30A */ MU_BLANK_30A,
    /* us:0x30B, jp:0x30B */ MU_CRYSTAL_TEARDROPS,
    /* us:0x30C, jp:0x30C */ MU_CRYSTAL_TEARDROPS_LOOP_POINT,
    /* us:0x30D, jp:0x30D */ MU_MARBLE_GALLERY,
    /* us:0x30E, jp:0x30E */ MU_MARBLE_GALLERY_LOOP_POINT,
    /* us:0x30F, jp:0x30F */ MU_DRACULAS_CASTLE,
    /* us:0x310, jp:0x310 */ MU_DRACULAS_CASTLE_LOOP_POINT,
    /* us:0x311, jp:0x311 */ MU_THE_TRAGIC_PRINCE,
    /* us:0x312, jp:0x312 */ MU_THE_TRAGIC_PRINCE_LOOP_POINT,
    /* us:0x313, jp:0x313 */ MU_TOWER_OF_MIST,
    /* us:0x314, jp:0x314 */ MU_TOWER_OF_MIST_LOOP_POINT,
    /* us:0x315, jp:0x315 */ MU_DOOR_OF_HOLY_SPIRITS,
    /* us:0x316, jp:0x316 */ MU_DOOR_OF_HOLY_SPIRITS_LOOP_POINT,
    /* us:0x317, jp:0x317 */ MU_DANCE_OF_PALES,
    /* us:0x318, jp:0x318 */ MU_DANCE_OF_PALES_LOOP_POINT,
    /* us:0x319, jp:0x319 */ MU_ABANDONED_PIT,
    /* us:0x31A, jp:0x31A */ MU_ABANDONED_PIT_LOOP_POINT,
    /* us:0x31B, jp:0x31B */ MU_HEAVENLY_DOORWAY,
    /* us:0x31C, jp:0x31C */ MU_BLANK_31C,
    /* us:0x31D, jp:0x31D */ MU_FESTIVAL_OF_SERVANTS,
    /* us:0x31E, jp:0x31E */ MU_FESTIVAL_OF_SERVANTS_LOOP_POINT,
    /* us:0x31F, jp:0x31F */ MU_DANCE_OF_ILLUSIONS,
    /* us:0x320, jp:0x320 */ MU_DANCE_OF_ILLUSIONS_LOOP_POINT,
    /* us:0x321, jp:0x321 */ MU_PROLOGUE,
    /* us:0x322, jp:0x322 */ MU_PROLOGUE_LOOP_POINT,
    /* us:0x323, jp:0x323 */ MU_WANDERING_GHOSTS,
    /* us:0x324, jp:0x324 */ MU_WANDERING_GHOSTS_LOOP_POINT,
    /* us:0x325, jp:0x325 */ MU_THE_DOOR_TO_THE_ABYSS,
    /* us:0x326, jp:0x326 */ MU_THE_DOOR_TO_THE_ABYSS_LOOP_POINT,
#if defined(VERSION_US)
    /* us:0x327           */ MU_METAMORPHOSIS,
    /* us:0x328           */ MU_METAMORPHOSIS_II,
    /* us:0x329           */ MU_METAMORPHOSIS_III,
#endif
    /* us:0x32A, jp:0x327 */ SE_INTRO_WIND,
    /* us:0x32B, jp:0x328 */ SE_INTRO_WIND_LOOP_POINT,
    /* us:0x32C, jp:0x329 */ SE_INTRO_WIND_QUIET,
    /* us:0x32D, jp:0x32A */ SE_INTRO_WIND_QUIET_LOOP_POINT,
    /* us:0x32E, jp:0x32B */ MU_DANCE_OF_GOLD,
    /* us:0x32F, jp:0x32C */ MU_DANCE_OF_GOLD_LOOP_POINT,
    /* us:0x330, jp:0x32D */ MU_ENCHANTED_BANQUET,
    /* us:0x331, jp:0x32E */ MU_ENCHANTED_BANQUET_LOOP_POINT,
    /* us:0x332, jp:0x32F */ MU_PRAYER,
    /* us:0x333, jp:0x330 */ MU_PRAYER_LOOP_POINT,
    /* us:0x334, jp:0x331 */ MU_DEATH_BALLAD,
    /* us:0x335, jp:0x332 */ MU_DEATH_BALLAD_LOOP_POINT,
    /* us:0x336, jp:0x333 */ MU_BLOOD_RELATIONS,
    /* us:0x337, jp:0x334 */ MU_BLOOD_RELATIONS_LOOP_POINT,
    /* us:0x338, jp:0x335 */ MU_FINAL_TOCATTA,
    /* us:0x339, jp:0x336 */ MU_FINAL_TOCATTA_LOOP_POINT,
    /* us:0x33A, jp:0x337 */ MU_BLACK_BANQUET,
    /* us:0x33B, jp:0x338 */ MU_BLACK_BANQUET_LOOP_POINT,
    /* us:0x33C, jp:0x339 */ MU_STAFF_CREDITS,
    /* us:0x33D, jp:0x33A */ MU_SILENCE,
    /* us:0x33E, jp:0x33B */ MU_LAND_OF_BENEDICTION,
    /* us:0x33F, jp:0x33C */ MU_NOCTURNE,
    /* us:0x340, jp:0x33D */ MU_MOONLIGHT_NOCTURNE,

#if defined(VERSION_US)
    // japanese intro: "Katsute ..."
    /* us:0x341           */ JP_VO_NARRATOR_KATSUTE,

    // japanese intro: "Soshite 5 nen no tsukihi ga nagareta"
    /* us:0x342           */ JP_VO_NARRATOR_SOSHITE,

    // japanese intro: "Akumajo Dracula X Gekka no Yasoukyoku"
    /* us:0x343           */ JP_VO_NARRATOR_AKUMAJO,

#elif defined(VERSION_PSP)
    __ALIGN_ID_341 = 0x341, // TODO check what this ID does on JP/HD/PSP
#endif

    // used for the japanese sound test, messages from the developers
    /* us:0x344, jp:0x342 */ JP_VO_FUKAMI_RIKA_MESSAGE,      // Fukami Rika
    /* us:0x345, jp:0x343 */ JP_VO_SHIINA_HEKIRU_MESSAGE,    // Shiina Hekiru
    /* us:0x346, jp:0x344 */ JP_VO_YANADA_KIYOYUKI_MESSAGE,  // Yanada Kiyoyuki
    /* us:0x347, jp:0x345 */ JP_VO_OKIAYU_RYOUTAROU_MESSAGE, // Okiayu Ryoutarou
    /* us:0x348, jp:0x346 */ JP_VO_SATOU_MASAHARU_MESSAGE,   // Satou Masaharu
    /* us:0x349, jp:0x347 */ JP_VO_WAKAMOTO_NORIO_MESSAGE,   // Wakamoto Norio
    /* us:0x34A, jp:0x348 */ JP_VO_YOKOYAMA_CHISA_MESSAGE,   // Yokoyama Chisa
    /* us:0x34B, jp:0x349 */ JP_VO_YANAMI_JYOUJI_MESSAGE,    // Yanami Jyouji

    // various voice actors saying konami
    /* us:0x34C           */ JP_VO_KONAMI_1,  // woman says konami
    /* us:0x34D           */ JP_VO_KONAMI_2,  // woman says konami
    /* us:0x34E           */ JP_VO_KONAMI_3,  // woman says konami
    /* us:0x34F           */ JP_VO_KONAMI_4,  // man says kona (mi cut off?)
    /* us:0x350           */ JP_VO_KONAMI_5,  // man says kona (mi cut off?)
    /* us:0x351           */ JP_VO_KONAMI_6,  // man says konami
    /* us:0x352           */ JP_VO_KONAMI_7,  // man says konami
    /* us:0x353           */ JP_VO_KONAMI_8,  // man says konami
    /* us:0x354           */ JP_VO_KONAMI_9,  // woman says konami
    /* us:0x355           */ JP_VO_KONAMI_10, // woman says konami
    /* us:0x356           */ JP_VO_KONAMI_11, // man says konami
    /* us:0x357           */ JP_VO_KONAMI_12, // man says konami

    /*           jp:0x391 */ VO_GAMEOVER_SUCCUBUS_TAUNT = 0x391,
    /*           jp:0x3CE */ VO_GAMEOVER_MARIA = 0x3CE,
    /*           jp:0x3DA */ VO_GAMEOVER_RICHTER_TAUNT_1 = 0x3DA,
    /*           jp:0x3DB */ VO_GAMEOVER_RICHTER_TAUNT_2 = 0x3DB,
    /*           jp:0x3DC */ VO_GAMEOVER_RICHTER_TAUNT_3 = 0x3DC,
    /*           jp:0x52E */ VO_GAMEOVER_DEATH_TAUNT_1 = 0x52E,
    /*           jp:0x52F */ VO_GAMEOVER_DEATH_TAUNT_2 = 0x52F,
    /*           jp:0x530 */ VO_GAMEOVER_DEATH_TAUNT_3 = 0x530,
};

// Prologue cutscene
#define NA_VO_RI_DIE_MONSTER 0x358 // Richter says "Die monster ..."
#define NA_VO_DR_IT_WAS_NOT 0x359  // Dracula says "It was not by my hand ..."
#define NA_VO_RI_TRIBUTE 0x35A     // Richter says "Tribute? ..."

#if defined(VERSION_PSP)
#define NA_VO_AL_INTERESTED 0x3A7 // Alucard says "I'm interested in this"
#define NA_VO_ML_THANKS 0x3AB     // Master Librarian says "Thank you"
#define NA_VO_ML_FAREWELL 0x3B0   // Master Librarian says "Farewell for now"
#else
#define NA_VO_AL_INTERESTED 0x3A9 // Alucard says "I'm interested in this"
#define NA_VO_ML_THANKS 0x3AD     // Master Librarian says "Thank you"
#define NA_VO_ML_FAREWELL 0x3B2   // Master Librarian says "Farewell for now"
#endif

#if defined(VERSION_US)
#define NA_VO_MA_IF_YOU_WEAR                                                   \
    0x3CE // Maria: If you wear these, you can see beyond evil illusions.

#define NA_VO_RI_IMPRESSIVE_WHIP                                               \
    0x3DA // Richter: Impressive, you were able to avoid my whip. Let's see how
          // you like this!
#define NA_VO_RI_IMPRESSIVE_ESCAPE                                             \
    0x3DB // Richter: Impressive, but you can't escape this.
#define NA_VO_RI_ONLY_THE_COUNT                                                \
    0x3DC // Richter: Hah, I knew it. Only the count is a true match for me.

#define NA_VO_AL_DEATH_DREAM_WORLD                                             \
    0x391 // Alucard: Death in the dream world will set your soul wandering for
          // eternity, demon.

// Fairy voiceovers
#define FAERIE_INTRO_LIFE 0x472    // "Thank you for giving me life"
#define FAERIE_INTRO_COMMAND 0x473 // "Your word is my command"
#define FAERIE_LETS_GO 0x476       // "Let's go!"
#define FAERIE_FOLLOW 0x479        // "I'll follow you anywhere"
#define FAERIE_WALL_HINT 0x47A     // "There is something funny about this wall"
#define FAERIE_SUSPICIOUS_HINT 0x48A // "This is really suspicious looking"
#define FAERIE_MIST_HINT 0x48E       // "If only you could transform into mist"
#define FAERIE_DARKNESS_HINT                                                   \
    0x492 // "Some animals can live in complete darkness"

// Demon voiceovers
#define DEMON_INTRO_COMMAND 0x4E8 // Command me, my lord and master
#define DEMON_INTRO_READY 0x4ED   // I'm ready to serve, master
#define DEMON_SWITCH_1 0x4EE // Hmm, a switch.  Why don't I press it and see?
#define DEMON_SWITCH_2 0x4EF // Hmm, this switch hasn't been pressed yet

#define JP_VO_SH_GROAN 0x52E      // Shaft groans
#define JP_VO_SH_SCREAM 0x52F     // Shaft screams
#define JP_VO_SH_SONO_TEIDO 0x530 // Shaft: Sono teido no chikara de tatakai...
#endif

#define NA_SE_EV_WATER_SPLASH 0x7C2
#define SFX_WATER_SURFACING 0x7C3

#define NA_SE_VO_DR_TAUNT_1 0x84F
#define NA_SE_VO_DR_TAUNT_2 0x850
#ifdef VERSION_PSP
#define NA_SE_VO_DR_HURT_1 0x85A
#else
#define NA_SE_VO_DR_HURT_1 0x853
#endif
#define NA_SE_VO_DR_HERE_IS_TRUE_POWER 0x855
#define NA_SE_VO_DR_GRANT_ME_POWER 0x857
#define NA_SE_VO_DR_PLAYTIME_IS_OVER 0x858
#define NA_SE_VO_DR_HURT_2 0x85B
#define NA_SE_VO_DR_HURT_3 0x85C
#define NA_SE_VO_DR_HURT_4 0x85D
// plays every 10 frames while using bible subweapon
#define BIBLE_SUBWPN_SWOOSH 0x8C3

// STAGE DAI
// Unknown SFX related to the priest
#define SFX_UNK_4E5 0x4E5
#define SFX_UNK_7BB 0x7BB

// STAGE DRE
#define NA_VO_SU_LAUGH 0x86E
// Blank, may be a leftover from the Jap version.
#define NA_VO_SU_BLANK 0x86F
#define NA_VO_SU_GRUNT_1 0x870
#define NA_VO_SU_GRUNT_2 0x872
#define NA_VO_SU_GRUNT_3 0x874
#define NA_VO_SU_HURT_1 0x879
#define NA_VO_SU_HURT_2 0x87A
#define NA_VO_SU_CRYSTAL_1 0x87C
#define NA_VO_SU_SUCK_YOU_DRY 0x876
#define NA_VO_SU_NO_SCREAM 0x87B
#define NA_VO_SU_DELICIOUS 0x8D1

// STAGE NO3 / NP3
#define NA_SE_EV_WINDOW_LATCH 0x79D
#define SE_DEATH_TAKES_ITEMS 0x7A0
#define NA_VO_DEATH_LAUGH 0x7A1
#define SE_ITEM_YOINK 0x7A2
#define SE_TREE_BRANCH_SNAP 0x7A4
#define SE_CASTLE_GATE_RISE 0x7A5

// STAGE NO4
#define SFX_OAR_ROW 0x7BF
#define SFX_WATER_BUBBLE 0x7C4

// BOSS BO4 - Doppleganger10 / RBO5 - Doppleganger40
#define SFX_RBO5_UNK_7AE 0x7AE
#define SFX_BO4_UNK_7CB 0x7CB
#define SFX_BO4_UNK_7CC 0x7CC
#define SFX_BO4_UNK_7D8 0x7D8
#define SFX_BO4_UNK_7D7 0x7D7
#define SFX_BO4_UNK_7D9 0x7D9
#define SFX_BO4_UNK_7DA 0x7DA
#define SFX_BO4_UNK_7DB 0x7DB
#define SFX_BO4_UNK_7DC 0x7DC
#define SFX_BO4_UNK_7DD 0x7DD
#define SFX_BO4_UNK_7DE 0x7DE
#define SFX_BO4_UNK_7DF 0x7DF
#define SFX_BO4_UNK_7E0 0x7E0
#define SFX_BO4_UNK_7E1 0x7E1
#define SFX_BO4_UNK_7E6 0x7E6
#define SFX_BO4_UNK_7E8 0x7E8

// BOSS RBO3 - Medusa
#define SFX_RBO3_UNK_7C5 0x7C5
#define SFX_RBO3_UNK_7C8 0x7C8
#define SFX_RBO3_UNK_7FB 0x7FB
#define SFX_RBO3_UNK_7FD 0x7FD
#define SFX_RBO3_UNK_7FE 0x7FE
#define SFX_RBO3_UNK_7FF 0x7FF
#define SFX_RBO3_UNK_801 0x801
#define SFX_RBO3_UNK_802 0x802
#define SFX_RBO3_UNK_804 0x804

// UNUSED SOUNDS
#define NA_VO_MAR_AIM_HEAD 0x87F

// The VAB IDs appear in large chunks so all sounds proceeding
// a vabid label comment will belong in that VAB group unless noted.
//
// vabid 0 = Shared or common sfx
// vabid 1 = Player VO sfx
// vabid 3 = Enemy sfx
// vabid 9 = All sequenced sfx (sounds that use multiple notes)
//
// Some enemy sfxIDs in vabID 3 can sound different depending on which
// overlay is loaded.  For example, Grave Keeper has three sound calls
// in ARE and CAT, but the VH files are different between them so 0x754
// plays a different sample in ARE.  0x709 is another example; the pitch
// is higher in NP3, but normal for RCHI and NZ0.

#ifdef VERSION_BETA
// MAD uses an earlier build and has different sfx IDs
enum Sfx {
    SFX_METAL_CLANG_E = 0x611, // Same ID as final
    SFX_WEAPON_STAB_B = 0x630,
    SFX_CANDLE_HIT = 0x635,
    SFX_DOOR_OPEN = 0x640,
    SFX_DOOR_CLOSE_A = 0x64D,
    SFX_HEART_PICKUP = 0x670,
    SFX_ITEM_PICKUP = 0x672,
    SFX_GOLD_PICKUP = 0x69D,
    SFX_WEAPON_HIT_A = 0x6DB
};
#else
enum Sfx {
    // vabid 0
    /* 0x601 */ SFX_HARPY_WING_FLAP = 0x601,
    /* 0x602 */ SFX_RIC_WHIP_RATTLE_A,
    /* 0x603 */ SFX_RIC_WHIP_RATTLE_B, // (B through E appear to be unused)
    /* 0x604 */ SFX_RIC_WHIP_RATTLE_C,
    /* 0x605 */ SFX_RIC_WHIP_RATTLE_D,
    /* 0x606 */ SFX_RIC_WHIP_RATTLE_E,
    /* 0x607 */ SFX_STONE_MOVE_A,
    /* 0x608 */ SFX_STONE_MOVE_B,
    /* 0x609 */ SFX_STONE_MOVE_C,
    /* 0x60A */ SFX_WEAPON_SWISH_A,
    /* 0x60B */ SFX_WEAPON_SWISH_B,
    /* 0x60C */ SFX_WEAPON_SWISH_C,
    /* 0x60D */ SFX_METAL_CLANG_A,
    /* 0x60E */ SFX_METAL_CLANG_B,
    /* 0x60F */ SFX_METAL_CLANG_C,
    /* 0x610 */ SFX_METAL_CLANG_D,
    /* 0x611 */ SFX_METAL_CLANG_E, // Stone Skull Hit
    /* 0x612 */ SFX_METAL_CLANG_F,
    /* 0x613 */ SFX_UNK_CROW,
    /* 0x614 */ SFX_ELECTRICITY,
    /* 0x615 */ SFX_SCRAPE_A,
    /* 0x616 */ SFX_SCRAPE_B,
    /* 0x617 */ SFX_SCRAPE_C, // Alucard backslide

    // vabid 9
    /* 0x618 */ SFX_UNK_618, // Referenced in ST0, TE1, TE2

    // vabid 0
    /* 0x619 */ SFX_GLASS_BREAK_A,
    /* 0x61A */ SFX_GLASS_BREAK_B,
    /* 0x61B */ SFX_GLASS_BREAK_C,
    /* 0x61C */ SFX_GLASS_BREAK_D,
    /* 0x61D */ SFX_GLASS_BREAK_E, // Vase Break
    /* 0x61E */ SFX_BAT_ECHO_A,
    /* 0x61F */ SFX_BAT_ECHO_B, // Alucard Echo of Bat
    /* 0x620 */ SFX_BAT_ECHO_C,
    /* 0x621 */ SFX_BAT_ECHO_D,
    /* 0x622 */ SFX_SKULL_BONK,
    /* 0x623 */ SFX_RIC_RSTONE_TINK, // Rebound Stone
    /* 0x624 */ SFX_SMALL_BURST,
    /* 0x625 */ SFX_ARROW_SHOT_A, // Magic Missile Shot
    /* 0x626 */ SFX_ARROW_SHOT_B,
    /* 0x627 */ SFX_ARROW_SHOT_C,
    /* 0x628 */ SFX_ARROW_SHOT_D,
    /* 0x629 */ SFX_SKELETON_DEATH_A,
    /* 0x62A */ SFX_SKELETON_DEATH_B, // Slinger
    /* 0x62B */ SFX_SKELETON_DEATH_C,
    /* 0x62C */ SFX_FIRE_SHOT,
    /* 0x62D */ SFX_WEAPON_STAB_A,
    /* 0x62E */ SFX_WEAPON_STAB_B,  // Common stab sfx
    /* 0x62F */ SFX_WEAPON_APPEAR,  // Item Crash, Neutron Bomb
    /* 0x630 */ SFX_UNK_BETA_630,   // (MAD, TE1, TE2, TE3, TE4, TE5)
    /* 0x631 */ SFX_DEATH_AMBIENCE, // BGM ambience during first Death cutscene
    /* 0x632 */ SFX_MAGIC_GLASS_BREAK, // Subweapon Container
    /* 0x633 */ SFX_UI_CONFIRM,
    /* 0x634 */ SFX_CANDLE_HIT,
    /* 0x635 */ SFX_TELEPORT_BANG_A, // Used when teleport starts
    /* 0x636 */ SFX_TELEPORT_BANG_B, // Teleport ends, also Warp Enter
    /* 0x637 */ SFX_SUC_APPEAR,      // Succubus reveal
    /* 0x638 */ SFX_UNK_SCRAPE_A,
    /* 0x639 */ SFX_UNK_SCRAPE_B,
    /* 0x63A */ SFX_UNK_SCRAPE_C,
    /* 0x63B */ SFX_UNK_UI_SELECT,
    /* 0x63C */ SFX_START_SLAM_A, // Dark Shield
    /* 0x63D */ SFX_START_SLAM_B, // Press Start, Door Open, Dracula Stomp, etc
    /* 0x63E */ SFX_START_SLAM_C,
    /* 0x63F */ SFX_ANIME_SWORD_A, // Sword Familiar
    /* 0x640 */ SFX_ANIME_SWORD_B, // Holy Rod ("Anime shing" element)
    /* 0x641 */ SFX_ANIME_SWORD_C,
    /* 0x642 */ SFX_DOOR_OPEN,
    /* 0x643 */ SFX_WALL_DEBRIS_A,
    /* 0x644 */ SFX_WALL_DEBRIS_B, // Warp Exit & Wall Break
    /* 0x645 */ SFX_WALL_DEBRIS_C,
    /* 0x646 */ SFX_STOMP_HARD_A,
    /* 0x647 */ SFX_STOMP_HARD_B, // Alucard Landing (Hard)
    /* 0x648 */ SFX_STOMP_HARD_C,
    /* 0x649 */ SFX_STOMP_HARD_D,
    /* 0x64A */ SFX_STOMP_HARD_E,
    /* 0x64B */ SFX_STOMP_SOFT_A, // Richter Landing (Hard)
    /* 0x64C */ SFX_STOMP_SOFT_B, // Alucard Landing (Normal)
    /* 0x64D */ SFX_SAVE_HEARTBEAT,
    /* 0x64E */ SFX_BAT_SCREECH,
    /* 0x64F */ SFX_DOOR_CLOSE_A,
    /* 0x650 */ SFX_DOOR_CLOSE_B,
    /* 0x651 */ SFX_UNK_UI_ERROR,
    /* 0x652 */ SFX_EXPLODE_FAST_A, // Explosion "stutter" effect
    /* 0x653 */ SFX_EXPLODE_FAST_B,
    /* 0x654 */ SFX_EXPLODE_A,
    /* 0x655 */ SFX_EXPLODE_B,
    /* 0x656 */ SFX_EXPLODE_C,
    /* 0x657 */ SFX_EXPLODE_D,
    /* 0x658 */ SFX_EXPLODE_E,
    /* 0x659 */ SFX_EXPLODE_F,
    /* 0x65A */ SFX_FM_EXPLODE_A, // FM synth explosion
    /* 0x65B */ SFX_FM_EXPLODE_B,
    /* 0x65C */ SFX_FM_EXPLODE_C,
    /* 0x65D */ SFX_FM_EXPLODE_D,
    /* 0x65E */ SFX_EXPLODE_SMALL, // Zombie death explosion
    /* 0x65F */ SFX_UNK_FIRE_WHOOSH,
    /* 0x660 */ SFX_FIREBALL_SHOT_A,
    /* 0x661 */ SFX_FIREBALL_SHOT_B,
    /* 0x662 */ SFX_FIREBALL_SHOT_C,
    /* 0x663 */ SFX_GUNSHOT,
    /* 0x664 */ SFX_THUNDER_A,
    /* 0x665 */ SFX_THUNDER_B,
    /* 0x666 */ SFX_THUNDER_C,
    /* 0x667 */ SFX_UNK_LOW_UI,
    /* 0x668 */ SFX_TRANSFORM,
    /* 0x669 */ SFX_MAGIC_WEAPON_APPEAR_A,
    /* 0x66A */ SFX_MAGIC_WEAPON_APPEAR_B,
    /* 0x66B */ SFX_WEAPON_BREAK,
    /* 0x66C */ SFX_BONE_SWORD_SWISH_A,
    /* 0x66D */ SFX_BONE_SWORD_SWISH_B,
    /* 0x66E */ SFX_BONE_SWORD_SWISH_C,
    /* 0x66F */ SFX_TELEPORT_BANG_SHORT_A,
    /* 0x670 */ SFX_TELEPORT_BANG_SHORT_B,
    /* 0x671 */ SFX_TELEPORT_BANG_SHORT_C,
    /* 0x672 */ SFX_NOISE_SWEEP_DOWN_A,
    /* 0x673 */ SFX_NOISE_SWEEP_DOWN_B,
    /* 0x674 */ SFX_BOING,
    /* 0x675 */ SFX_LEVER_METAL_BANG,
    /* 0x676 */ SFX_SWITCH_CLICK,
    /* 0x677 */ SFX_WEAPON_ENERGY,
    /* 0x678 */ SFX_WEAPON_HIT_A,
    /* 0x679 */ SFX_WEAPON_HIT_B,

    // vabid 9
    /* 0x67A */ SFX_HEART_PICKUP,
    /* 0x67B */ SFX_UI_MOVE,
    /* 0x67C */ SFX_ITEM_PICKUP,
    /* 0x67D */ SFX_UI_MP_FULL,
    /* 0x67E */ SFX_CANDLE_HIT_WHOOSH_A,
    /* 0x67F */ SFX_CANDLE_HIT_WHOOSH_B,
    /* 0x680 */ SFX_QUICK_STUTTER_EXPLODE_A,
    /* 0x681 */ SFX_RARE_FM_IMPACT, // RARE overlay only
    /* 0x682 */ SFX_KARMA_COIN_JINGLE,
    /* 0x683 */ SFX_QUICK_STUTTER_EXPLODE_B,
    /* 0x684 */ SFX_FM_THUNDER_EXPLODE,
    /* 0x685 */ SFX_GUNSHOT_HIGH,
    /* 0x686 */ SFX_UI_ERROR,
    /* 0x687 */ SFX_LEVEL_UP,
    /* 0x688 */ SFX_DEBUG_SELECT, // Low Heartbeat sfx used for Debug menu
    /* 0x689 */ SFX_WEAPON_SCRAPE_ECHO,
    /* 0x68A */ SFX_GLASS_BREAK_WHOOSH,
    /* 0x68B */ SFX_DRA_GLASS_BREAK, // "What is a man?!" wine glass shatter
    /* 0x68C */ SFX_WING_FLAP_A,
    /* 0x68D */ SFX_WING_FLAP_B,
    /* 0x68E */ SFX_HEALTH_PICKUP,
    /* 0x68F */ SFX_STUTTER_FIREBALL,
    /* 0x690 */ SFX_FM_EXPLODE_SWISHES,
    /* 0x691 */ SFX_SMALL_FLAME_IGNITE,
    /* 0x692 */ SFX_UNK_TRANSFORM,
    /* 0x693 */ SFX_STUTTER_EXPLODE_LOW,
    /* 0x694 */ SFX_FM_STUTTER_EXPLODE,
    /* 0x695 */ SFX_FAST_STUTTER_EXPLODE,
    /* 0x696 */ SFX_FM_MULTI_EXPLODE,
    /* 0x697 */ SFX_STUTTER_EXPLODE_A,
    /* 0x698 */ SFX_STUTTER_EXPLODE_B,
    /* 0x699 */ SFX_STUTTER_EXPLODE_C,
    /* 0x69A */ SFX_FM_EXPLODE_GLASS_ECHO,
    /* 0x69B */ SFX_BAT_WING_SWISHES,
    /* 0x69C */ SFX_BAT_SCREECH_SWISH, // Bat Death
    /* 0x69D */ SFX_MAGIC_SWITCH,
    /* 0x69E */ SFX_THROW_WEAPON_SWISHES,
    /* 0x69F */ SFX_THROW_WEAPON_MAGIC,
    /* 0x6A0 */ SFX_TRANSFORM_LOW, // (Alucard Bat/Mist Transform)
    /* 0x6A1 */ SFX_CLOCK_TICK,
    /* 0x6A2 */ SFX_DEATH_SWISH,
    /* 0x6A3 */ SFX_WATER_DAMAGE_SWISHES,
    /* 0x6A4 */ SFX_UI_TINK, // Also Rebound Stone Bounce
    /* 0x6A5 */ SFX_SKULL_KNOCK_A,
    /* 0x6A6 */ SFX_SKULL_KNOCK_B,
    /* 0x6A7 */ SFX_SKULL_KNOCK_C,
    /* 0x6A8 */ SFX_ALUCARD_SWORD_SWISH,
    /* 0x6A9 */ SFX_GOLD_PICKUP,
    /* 0x6AA */ SFX_MARIONETTE_RATTLE,
    /* 0x6AB */ SFX_SEED_SPIT,
    /* 0x6AC */ SFX_CANNON_EXPLODE,
    /* 0x6AD */ SFX_UI_ALERT_TINK,
    /* 0x6AE */ SFX_TINK_JINGLE, // Frozen Shade Shards, NO1 Telescope jingle
    /* 0x6AF */ SFX_GUARD_TINK,
    /* 0x6B0 */ SFX_GLASS_SHARDS, // (Succubus, Frozen Shade, Shamen Shield)
    /* 0x6B1 */ SFX_TRANSFORM_3X, // Karma Coin and shields
    /* 0x6B2 */ SFX_BIBLE_SCRAPE,
    /* 0x6B3 */ SFX_UNK_TICK,
    /* 0x6B4 */ SFX_UNK_RATTLE,
    /* 0x6B5 */ SFX_RIC_FLAME_WHIP,
    /* 0x6B6 */ SFX_UNK_FIRE_BURST,
    /* 0x6B7 */ SFX_LOW_CLOCK_TICK,
    /* 0x6B8 */ SFX_UNK_LOW_CLOCK_TICK,
    /* 0x6B9 */ SFX_UNK_METAL_TING,
    /* 0x6BA */ SFX_FAST_SWORD_SWISHES, // Sword of Dawn
    /* 0x6BB */ SFX_GRANDFATHER_CLOCK_TICK,
    /* 0x6BC */ SFX_MULTI_CLOCK_TICK,
    /* 0x6BD */ SFX_QUIET_STEPS,
    /* 0x6BE */ SFX_BLIPS_A,
    /* 0x6BF */ SFX_UNK_BLIPS_B,
    /* 0x6C0 */ SFX_BLIPS_C,
    /* 0x6C1 */ SFX_BLIPS_D, // Fleaman movement
    /* 0x6C2 */ SFX_DISCUS_LORD_EXPLODE,
    /* 0x6C3 */ SFX_SWISHES_ECHO_REPEAT,
    /* 0x6C4 */ SFX_SALOME_MAGIC_ATTACK,
    /* 0x6C5 */ SFX_MAGIC_NOISE_SWEEP,
    /* 0x6C6 */ SFX_BOSS_WING_FLAP,
    /* 0x6C7 */ SFX_WHIP_TWIRL_SWISH,
    /* 0x6C8 */ SFX_BONE_THROW,
    /* 0x6C9 */ SFX_CREAK,
    /* 0x6CA */ SFX_LOW_SKEL_EXPLODE,
    /* 0x6CB */ SFX_RED_SKEL_COLLAPSE,
    /* 0x6CC */ SFX_RED_SKEL_REBUILD,
    /* 0x6CD */ SFX_MULTI_NOISE_SWEEP_DOWN,
    /* 0x6CE */ SFX_SKEL_EXPLODE,
    /* 0x6CF */ SFX_EXPLODE_ECHO,
    /* 0x6D0 */ SFX_IGNITE_SWISHES,
    /* 0x6D1 */ SFX_SEED_BLIP,
    /* 0x6D2 */ SFX_DISSONANT_SCREECH,
    /* 0x6D3 */ SFX_RNO4_MAGIC_GLASS_BREAK,
    /* 0x6D4 */ SFX_PSWORD_TWIRL_ATTACK,
    /* 0x6D5 */ SFX_PSWORD_TWIRL, // Also Succubus Clone Spawn
    /* 0x6D6 */ SFX_CROW_CAW_PAIN,
    /* 0x6D7 */ SFX_CROW_CAW,
    /* 0x6D8 */ SFX_UNK_CLONE_DISAPPEAR,
    /* 0x6D9 */ SFX_BOSS_CLONE_DISAPPEAR,
    /* 0x6DA */ SFX_METAL_RATTLE_A,
    /* 0x6DB */ SFX_METAL_RATTLE_B,
    /* 0x6DC */ SFX_METAL_RATTLE_C,
    /* 0x6DD */ SFX_RAPID_SYNTH_BUBBLE,
    /* 0x6DE */ SFX_RAPID_SYNTH_BUBBLE_SHORT,
    /* 0x6DF */ SFX_CRASH_CROSS,
    /* 0x6E0 */ SFX_SAVE_COFFIN_SWISH,
    /* 0x6E1 */ SFX_RCEN_GLASS_BREAKS,
    /* 0x6E2 */ SFX_RIC_SUC_REVIVE, // RIC and SUC both use this
    /* 0x6E3 */ SFX_BUBBLE_BURST,
    /* 0x6E4 */ SFX_PENTAGRAM_ATTACK,
    /* 0x6E5 */ SFX_UNK_ANIME_EXPLODE,
    /* 0x6E6 */ SFX_LOW_SYNTH_BUBBLES,

    // vabid 1
    /* 0x6E7 */ SFX_VO_ALU_PAIN_A,
    /* 0x6E8 */ SFX_VO_ALU_PAIN_B,
    /* 0x6E9 */ SFX_VO_ALU_PAIN_C,
    /* 0x6EA */ SFX_VO_ALU_PAIN_D,
    /* 0x6EB */ SFX_VO_ALU_PAIN_E,
    /* 0x6EC */ SFX_VO_ALU_SILENCE,
    /* 0x6ED */ SFX_VO_ALU_YELL, // Elevator yell
    /* 0x6EE */ SFX_VO_ALU_ATTACK_A,
    /* 0x6EF */ SFX_VO_ALU_ATTACK_B,
    /* 0x6F0 */ SFX_VO_ALU_ATTACK_C,
    /* 0x6F1 */ SFX_VO_ALU_ATTACK_D,
    /* 0x6F2 */ SFX_VO_ALU_WHAT,
    /* 0x6F3 */ SFX_VO_ALU_DARK_META,
    /* 0x6F4 */ SFX_VO_ALU_SOUL_STEAL,
    /* 0x6F5 */ SFX_UNK_6F5,
    /* 0x6F6 */ SFX_VO_ALU_DEATH,
    /* 0x6F7 */ SFX_ALU_WOLF_BARK,
    /* 0x6F8 */ SFX_UNK_VO_ALU_WHOA,
    /* 0x6F9 */ SFX_VO_RIC_ATTACK_A,
    /* 0x6FA */ SFX_VO_RIC_ATTACK_B,
    /* 0x6FB */ SFX_VO_RIC_ATTACK_C,
    /* 0x6FC */ SFX_VO_RIC_ATTACK_YELL,
    /* 0x6FD */ SFX_UNK_6FD,
    /* 0x6FE */ SFX_UNK_6FE,
    /* 0x6FF */ SFX_VO_RIC_DEATH,
    /* 0x700 */ SFX_VO_RIC_HYDRO_STORM, // 0x700
    /* 0x701 */ SFX_VO_RIC_PAIN_A,
    /* 0x702 */ SFX_VO_RIC_PAIN_B,
    /* 0x703 */ SFX_VO_RIC_PAIN_C,
    /* 0x704 */ SFX_VO_RIC_PAIN_D,
    /* 0x705 */ SFX_RIC_WHIP_HIT,
    /* 0x706 */ SFX_RIC_WHIP_ATTACK,
    /* 0x707 */ SFX_RIC_SLIDE_SKID,
    /* 0x708 */ SFX_RIC_HYDRO_STORM_ATTACK,

    // vabid 3
    /* 0x709 */ SFX_SLOGRA_ROAR, // different pitch in NP3
    /* 0x70A */ SFX_SLOGRA_ROAR_DEFEAT,
    /* 0x70B */ SFX_SLOGRA_PAIN_A, // Used for Gaibon
    /* 0x70C */ SFX_SLOGRA_PAIN_B,
    /* 0x70D */ SFX_CORPSEWEED_ATTACK,
    /* 0x70E */ SFX_LESSER_DEMON_POISON,
    /* 0x70F */ SFX_VENUS_WEED_HURT,
    /* 0x710 */ SFX_VENUS_WEED_DEATH,
    /* 0x711 */ SFX_RNZ0_UNK_711,
    /* 0x712 */ SFX_UNUSED_712,
    /* 0x713 */ SFX_UNUSED_713,
    /* 0x714 */ SFX_FLYING_ZOMBIE_PAIN,
    /* 0x715 */ SFX_FLYING_ZOMBIE_DEATH,
    /* 0x716 */ SFX_FLYING_ZOMBIE_BODY_RIP,
    /* 0x717 */ SFX_RDAI_UNK_717,
    /* 0x718 */ SFX_VALHALLA_KNIGHT_NEIGH,
    /* 0x719 */ SFX_VALHALLA_KNIGHT_GALLOP,
    /* 0x71A */ SFX_TOAD_CROAK,
    /* 0x71B */ SFX_FROG_CROAK,
    /* 0x71C */ SFX_UNUSED_71C,
    /* 0x71D */ SFX_MERMAN_DEATH,
    /* 0x71E */ SFX_CLOAKED_KNIGHT_ATTACK,
    /* 0x71F */ SFX_CLOAKED_KNIGHT_UNK_71F, // referenced but no sound
    /* 0x720 */ SFX_CLOAKED_KNIGHT_DEATH,
    /* 0x721 */ SFX_NZ1_UNK_721,
    /* 0x722 */ SFX_NZ1_UNK_722,
    /* 0x723 */ SFX_NZ1_UNK_723,
    /* 0x724 */ SFX_RNO2_ANIME_SWORD,
    /* 0x725 */ SFX_MARIONETTE_LAUGH,
    /* 0x726 */ SFX_MARIONETTE_YELL,
    /* 0x727 */ SFX_UNUSED_727,
    /* 0x728 */ SFX_GREMLIN_HURT,
    /* 0x729 */ SFX_GREMLIN_DEATH,
    /* 0x72A */ SFX_HUNTING_GIRL_ATTACK,
    /* 0x72B */ SFX_HUNTING_GIRL_PAIN,
    /* 0x72C */ SFX_HUNTING_GIRL_DEATH,
    /* 0x72D */ SFX_VANDAL_SWORD_ATTACK,
    /* 0x72E */ SFX_VANDAL_SWORD_PAIN,
    /* 0x72F */ SFX_VANDAL_SWORD_DEATH,
    /* 0x730 */ SFX_STONE_ROSE_PAIN,
    /* 0x731 */ SFX_STONE_ROSE_DEATH,
    /* 0x732 */ SFX_RLIB_UNK_732,
    /* 0x733 */ SFX_FROZEN_SHADE_SCREAM,
    /* 0x734 */ SFX_LOSSOTH_NAPALM_GRUNT,
    /* 0x735 */ SFX_LOSSOTH_DEATH,
    /* 0x736 */ SFX_SALEM_WITCH_ATTACK,
    /* 0x737 */ SFX_SALEM_WITCH_HURT,
    /* 0x738 */ SFX_SALEM_WITCH_DEATH,
    /* 0x739 */ SFX_GHOST_ENEMY_HOWL,
    /* 0x73A */ SFX_ECTOPLASM_BOING,
    /* 0x73B */ SFX_ECTOPLASM_DEATH,
    /* 0x73C */ SFX_SPITTLEBONE_ACID_SPLAT,
    /* 0x73D */ SFX_RLIB_UNK_73D,

    // vabid 9
    /* 0x73E */ SFX_UNUSED_73E,

    // vabid 3
    /* 0x73F */ SFX_SKULL_LORD_DEATH,
    /* 0x740 */ SFX_GURKHA_ATTACK,
    /* 0x741 */ SFX_GURKHA_PAIN,
    /* 0x742 */ SFX_GURKHA_DEATH,
    /* 0x743 */ SFX_HAMMER_ATTACK,
    /* 0x744 */ SFX_HAMMER_PAIN,
    /* 0x745 */ SFX_HAMMER_DEATH,
    /* 0x746 */ SFX_BLOODY_ZOMBIE_PAIN,
    /* 0x747 */ SFX_BLOODY_ZOMBIE_DEATH,
    /* 0x748 */ SFX_BLOODY_ZOMBIE_BODY_HIT,
    /* 0x749 */ SFX_BLOODY_ZOMBIE_SPLATTER,
    /* 0x74A */ SFX_SALOME_ATTACK,
    /* 0x74B */ SFX_SALOME_PAIN,
    /* 0x74C */ SFX_SALOME_MEOW_SHORT,
    /* 0x74D */ SFX_SALOME_MEOW,
    /* 0x74E */ SFX_BLADE_ENEMY_ATTACK,
    /* 0x74F */ SFX_BLADE_ENEMY_PAIN,
    /* 0x750 */ SFX_BLADE_ENEMY_DEATH,
    /* 0x751 */ SFX_ARMOR_LORD_ATTACK,
    /* 0x752 */ SFX_ARMOR_LORD_FIRE_ATTACK,
    /* 0x753 */ SFX_ARMOR_LORD_DEATH,
    /* 0x754 */ SFX_GRAVE_KEEPER_GRAAH, // Audio is different in ARE
    /* 0x755 */ SFX_GRAVE_KEEPER_HIYAH, // Same audio in ARE and CAT
    /* 0x756 */ SFX_GRAVE_KEEPER_DEATH,
    /* 0x757 */ SFX_CTULHU_DEATH,
    /* 0x758 */ SFX_CTULHU_LAUGH,
    /* 0x759 */ SFX_CTULHU_ROAR,
    /* 0x75A */ SFX_ROCK_KNIGHT_ATTACK,
    /* 0x75B */ SFX_ROCK_KNIGHT_PAIN,
    /* 0x75C */ SFX_RNO4_UNK_75C,
    /* 0x75D */ SFX_ROCK_KNIGHT_DEATH,
    /* 0x75E */ SFX_PLATE_LORD_ATTACK,
    /* 0x75F */ SFX_PLATE_LORD_PAIN,
    /* 0x760 */ SFX_PLATE_LORD_DEATH,
    /* 0x761 */ SFX_PLATE_LORD_BALL_IMPACT,
    /* 0x762 */ SFX_CAT_UNK_762,
    /* 0x763 */ SFX_DISCUS_LORD_ATTACK,
    /* 0x764 */ SFX_DISCUS_LORD_DEATH,
    /* 0x765 */ SFX_DISCUS_BUZZ,
    /* 0x766 */ SFX_AXE_KNIGHT_ATTACK,
    /* 0x767 */ SFX_AXE_KNIGHT_DEATH,
    /* 0x768 */ SFX_HIPPOGRYPH_WING_FLAP,
    /* 0x769 */ SFX_HIPPOGRYPH_SQUAWK, // unused?
    /* 0x76A */ SFX_RDAI_UNK_76A,
    /* 0x76B */ SFX_FROZEN_HALF_DEATH, // normally, enemy attack sfx is first!
    /* 0x76C */ SFX_FROZEN_HALF_ATTACK,
    /* 0x76D */ SFX_FROZEN_HALF_MAXIMUM_POWER,

    // vabid 9
    /* 0x76E */ SFX_FROZEN_HALF_BLIZZARD, // sequenced sfx

    // vabid 3
    /* 0x76F */ SFX_UNUSED_76F, // blank space after switching vabid
    /* 0x770 */ SFX_SPEAR_GUARD_ATTACK,
    /* 0x771 */ SFX_SPEAR_GUARD_DEATH,
    /* 0x772 */ SFX_SPEAR_GUARD_UNUSED_MOVE, // not referenced

    // vabid 9
    /* 0x773 */ SFX_SPEAR_GUARD_MOVE, // sequenced version of 0x772

    // vabid 3
    /* 0x774 */ SFX_UNUSED_774,
    /* 0x775 */ SFX_HELLFIRE_BEAST_DEATH,
    /* 0x776 */ SFX_DIPLOCEPHALUS_ATTACK,
    /* 0x777 */ SFX_DIPLOCEPHALUS_PAIN,
    /* 0x778 */ SFX_DIPLOCEPHALUS_DEATH,
    /* 0x779 */ SFX_DIPLOCEPHALUS_STOMP, // also used by Plate Lord
    /* 0x77A */ SFX_GORGON_SNORT,
    /* 0x77B */ SFX_GORGON_ATTACK,
    /* 0x77C */ SFX_FLEA_RIDER_DEATH,
    /* 0x77D */ SFX_SWORD_LORD_SWIPE_ATTACK,
    /* 0x77E */ SFX_SWORD_LORD_STAB_ATTACK,
    /* 0x77F */ SFX_SWORD_LORD_DEATH,
    /* 0x780 */ SFX_WARG_DEATH_HOWL, // also used for Scylla Worm (phase 2)
    /* 0x781 */ SFX_WARG_PAIN,
    /* 0x782 */ SFX_WARG_ATTACK,
    /* 0x783 */ SFX_WARG_GROWL,
    SFX_UNK_797 = 0x797,
    SFX_CLOCK_BELL = 0x7A6,
    SFX_CLOCK_ROOM_TICK = 0x7A9,
    SFX_TELESCOPE_SHUTTER_CLICK = 0x7AC,
    SFX_ALU_ZZZ_SNORE,
    SFX_UNK_7AF = 0x7Af,
    SFX_ELEVATOR_DOOR = 0x7B1,
    SFX_ELEVATOR_SLAM = 0x7B3,
    SFX_ELEVATOR_START = 0x7B5,
    SFX_BAD_LUCK_JINGLE,
    SFX_NO1_BIRD_CYCLE,
    SFX_CHAPEL_BELL = 0x7BC,
    SFX_UNK_7BD = 0x7BD,
    SFX_UNK_7BE = 0x7BE,
    SFX_SCIFI_BLAST = 0x7D1,
    SFX_BOSS_DEFEATED,
    SFX_TELEPORT_SYNTH_UP = 0x8BA,
    SFX_TELEPORT_SYNTH_DOWN,
    SFX_BURNING_PHOTOGRAPH = 0x8BE,
    SFX_UI_NAME_ENTRY = 0x8CD,

    // Exclusive to Maria PSP
    /* 0x8E6 */ SFX_VO_MAR_8E6 = 0x8E6,
    /* 0x8E7 */ SFX_VO_MAR_ATTACK_C,
    /* 0x8E8 */ SFX_VO_MAR_8E8,
    /* 0x8E9 */ SFX_VO_MAR_8E9,
    /* 0x8EA */ SFX_VO_MAR_8EA,
    /* 0x8EB */ SFX_VO_MAR_8EB,
    /* 0x8EC */ SFX_VO_MAR_8EC,
    /* 0x8ED */ SFX_VO_MAR_8ED,
    /* 0x8EE */ SFX_VO_MAR_8EE,
    /* 0x8EF */ SFX_VO_MAR_8EF,
    /* 0x8F0 */ SFX_VO_MAR_8F0,
    /* 0x8F1 */ SFX_VO_MAR_8F1,
    /* 0x8F2 */ SFX_VO_MAR_PAIN_B,
    /* 0x8F3 */ SFX_VO_MAR_PAIN_C,
    /* 0x8F4 */ SFX_VO_MAR_PAIN_D,
    /* 0x8F5 */ SFX_VO_MAR_DEATH,
};

#endif

// related to SFX
typedef struct {
    /* 0x00 */ s16 sndId;
    /* 0x02 */ u16 sndVol;
    /* 0x04 */ s16 sndPan;
} SfxRingBufferItem;

#endif
