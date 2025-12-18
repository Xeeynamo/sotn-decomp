#ifndef SFX_H
#define SFX_H

#include "types.h"

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
#define SET_UNK_13 0x13
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

// XA music tracks
// LOOP_POINT means it starts playing from part way into the song
enum {
    /* jp:0x203 */ SD_SEQ_LIBRARY = 0x203,

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
#define NA_VO_AL_DEATH_DREAM_WORLD                                             \
    0x391 // Alucard: Death in the dream world will set your soul wandering for
          // eternity, demon.
#define NA_VO_AL_INTERESTED 0x3A9 // Alucard says "I'm interested in this"
#define NA_VO_ML_THANKS 0x3AD     // Master Librarian says "Thank you"
#define NA_VO_ML_FAREWELL 0x3B2   // Master Librarian says "Farewell for now"
#define NA_VO_MA_IF_YOU_WEAR                                                   \
    0x3CE // Maria: If you wear these, you can see beyond evil illusions.

#define NA_VO_RI_IMPRESSIVE_WHIP                                               \
    0x3DA // Richter: Impressive, you were able to avoid my whip. Let's see how
          // you like this!
#define NA_VO_RI_IMPRESSIVE_ESCAPE                                             \
    0x3DB // Richter: Impressive, but you can't escape this.
#define NA_VO_RI_ONLY_THE_COUNT                                                \
    0x3DC // Richter: Hah, I knew it. Only the count is a true match for me.
#endif

// Fairy voiceovers
#if defined(VERSION_PSP)
#define FAERIE_INTRO_LIFE 0x470    // "Thank you for giving me life"
#define FAERIE_INTRO_COMMAND 0x471 // "Your word is my command"
#define FAERIE_LETS_GO 0x474       // "Let's go!"
#define FAERIE_FOLLOW 0x477        // "I'll follow you anywhere"
#define FAERIE_WALL_HINT 0x478     // "There is something funny about this wall"
#define FAERIE_SUSPICIOUS_HINT 0x488 // "This is really suspicious looking"
#define FAERIE_MIST_HINT 0x48C       // "If only you could transform into mist"
#define FAERIE_DARKNESS_HINT                                                   \
    0x490 // "Some animals can live in complete darkness"
#else
#define FAERIE_INTRO_LIFE 0x472    // "Thank you for giving me life"
#define FAERIE_INTRO_COMMAND 0x473 // "Your word is my command"
#define FAERIE_LETS_GO 0x476       // "Let's go!"
#define FAERIE_FOLLOW 0x479        // "I'll follow you anywhere"
#define FAERIE_WALL_HINT 0x47A     // "There is something funny about this wall"
#define FAERIE_SUSPICIOUS_HINT 0x48A // "This is really suspicious looking"
#define FAERIE_MIST_HINT 0x48E       // "If only you could transform into mist"
#define FAERIE_DARKNESS_HINT                                                   \
    0x492 // "Some animals can live in complete darkness"
#endif

// STAGE DAI
// Unknown SFX related to the priest
#define SFX_UNK_4E5 0x4E5

// Demon voiceovers
#if defined(VERSION_US)
#define DEMON_INTRO_COMMAND 0x4E8 // Command me, my lord and master
#define DEMON_INTRO_READY 0x4ED   // I'm ready to serve, master
#define DEMON_SWITCH_1 0x4EE // Hmm, a switch.  Why don't I press it and see?
#define DEMON_SWITCH_2 0x4EF // Hmm, this switch hasn't been pressed yet

#define JP_VO_SH_GROAN 0x52E      // Shaft groans
#define JP_VO_SH_SCREAM 0x52F     // Shaft screams
#define JP_VO_SH_SONO_TEIDO 0x530 // Shaft: Sono teido no chikara de tatakai...
#endif

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
    // SEQ music tracks
    // While there is unused SEQ data in DRA, LIB and DAI are the only two
    // overlays that use sequenced music heard in-game.
    //
    // For the PSP port, the SEQ files were replaced with pre-recorded versions
    // and saved as ATRAC3 streaming audio.  To reference these new audio
    // streams, the loop points for "Lost Painting" and "Curse Zone" were also
    // replaced.  Reusing the loop point IDs makes sense as .AT3 files support
    // looping.
    MU_SEQ_LIBRARIAN = 0x202,
    MU_SEQ_CONFESSIONAL_BELLS = 0x204,
    MU_SEQ_LIBRARIAN_PSP = 0x302,
    MU_SEQ_CONFESSIONAL_BELLS_PSP = 0x304,

    // Common sfxIDs (0x601-0x6E6)

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
    /* 0x624 */ SFX_SALEM_WITCH_CURSE_ATTACK,
    /* 0x625 */ SFX_ARROW_SHOT_A, // Magic Missile Shot
    /* 0x626 */ SFX_ARROW_SHOT_B,
    /* 0x627 */ SFX_ARROW_SHOT_C,
    /* 0x628 */ SFX_ARROW_SHOT_D,
    /* 0x629 */ SFX_SKELETON_DEATH_A, // Paranthropus
    /* 0x62A */ SFX_SKELETON_DEATH_B, // Slinger
    /* 0x62B */ SFX_SKELETON_DEATH_C,
    /* 0x62C */ SFX_FIRE_SHOT,
    /* 0x62D */ SFX_WEAPON_STAB_A,
    /* 0x62E */ SFX_WEAPON_STAB_B,  // Common stab sfx
    /* 0x62F */ SFX_WEAPON_APPEAR,  // Item Crash, Neutron Bomb
    /* 0x630 */ SFX_UNK_BETA_630,   // (MAD, TE1, TE2, TE3, TE4, TE5)
    /* 0x631 */ SFX_DEATH_AMBIENCE, // BGM ambience during first Death cutscene
    /* 0x632 */ SFX_SUBWEAPON_CONTAINER_BREAK,
    /* 0x633 */ SFX_UI_CONFIRM,
    /* 0x634 */ SFX_CANDLE_HIT,
    /* 0x635 */ SFX_TELEPORT_BANG_A, // Used when teleport starts
    /* 0x636 */ SFX_TELEPORT_BANG_B, // Teleport ends, also Warp Enter
    /* 0x637 */ SFX_SUC_APPEAR,      // Succubus reveal
    /* 0x638 */ SFX_UNUSED_SCRAPE_A,
    /* 0x639 */ SFX_UNUSED_SCRAPE_B,
    /* 0x63A */ SFX_UNUSED_SCRAPE_C,
    /* 0x63B */ SFX_UNUSED_UI_SELECT,
    /* 0x63C */ SFX_START_SLAM_A, // Dark Shield
    /* 0x63D */ SFX_START_SLAM_B, // Press Start, Door Open, Dracula Stomp, etc
    /* 0x63E */ SFX_UNUSED_START_SLAM_C,
    /* 0x63F */ SFX_ANIME_SWORD_A, // Sword Familiar
    /* 0x640 */ SFX_ANIME_SWORD_B, // Holy Rod ("Anime shing" element)
    /* 0x641 */ SFX_ANIME_SWORD_C,
    /* 0x642 */ SFX_DOOR_OPEN,
    /* 0x643 */ SFX_WALL_DEBRIS_A,
    /* 0x644 */ SFX_WALL_DEBRIS_B, // Warp Exit & Wall Break
    /* 0x645 */ SFX_WALL_DEBRIS_C,
    /* 0x646 */ SFX_STOMP_HARD_A,
    /* 0x647 */ SFX_STOMP_HARD_B, // Alucard Landing (Hard)
    /* 0x648 */ SFX_STOMP_HARD_C, // Blade, Gurkha and more large enemies
    /* 0x649 */ SFX_STOMP_HARD_D, // Flea Armor, Sword Lord
    /* 0x64A */ SFX_STOMP_HARD_E, // Maria, Venus Weed, Flea Armor, Sword Lord
    /* 0x64B */ SFX_STOMP_SOFT_A, // Richter Landing (Hard)
    /* 0x64C */ SFX_STOMP_SOFT_B, // Alucard Landing (Normal)
    /* 0x64D */ SFX_SAVE_HEARTBEAT,
    /* 0x64E */ SFX_BAT_SCREECH,
    /* 0x64F */ SFX_DOOR_CLOSE_A,
    /* 0x650 */ SFX_DOOR_CLOSE_B,   // Lesser Demon, Doppleganger
    /* 0x651 */ SFX_UNK_UI_ERROR,   // TE1, TE2, TE4, TE5
    /* 0x652 */ SFX_EXPLODE_FAST_A, // Explosion "stutter" effect
    /* 0x653 */ SFX_EXPLODE_FAST_B,
    /* 0x654 */ SFX_EXPLODE_A,
    /* 0x655 */ SFX_EXPLODE_B,
    /* 0x656 */ SFX_UNUSED_EXPLODE_C,
    /* 0x657 */ SFX_EXPLODE_D, // Blade, Gurkha, Hammer
    /* 0x658 */ SFX_EXPLODE_E, // Tombstone, Yorick
    /* 0x659 */ SFX_EXPLODE_F,
    /* 0x65A */ SFX_FM_EXPLODE_A, // FM synth explosion (Ape barrel and DRE)
    /* 0x65B */ SFX_FM_EXPLODE_B,
    /* 0x65C */ SFX_UNUSED_FM_EXPLODE_C,
    /* 0x65D */ SFX_FM_EXPLODE_D,             // Hammer, Lesser Demon
    /* 0x65E */ SFX_EXPLODE_SMALL,            // Zombie death explosion
    /* 0x65F */ SFX_PSP_MARIA_CARDINAL_CRASH, // unused in PSX
    /* 0x660 */ SFX_FIREBALL_SHOT_A,
    /* 0x661 */ SFX_FIREBALL_SHOT_B,
    /* 0x662 */ SFX_FIREBALL_SHOT_C, // Merman, Scylla
    /* 0x663 */ SFX_SALEM_WITCH_CURSE_PROJ,
    /* 0x664 */ SFX_THUNDER_A, // Iron Shield
    /* 0x665 */ SFX_THUNDER_B,
    /* 0x666 */ SFX_UNUSED_THUNDER_C,
    /* 0x667 */ SFX_UNK_TE3_LOW_UI,
    /* 0x668 */ SFX_TRANSFORM,
    /* 0x669 */ SFX_MAGIC_WEAPON_APPEAR_A,
    /* 0x66A */ SFX_MAGIC_WEAPON_APPEAR_B,
    /* 0x66B */ SFX_AXE_KNIGHT_WEAPON_BREAK,
    /* 0x66C */ SFX_BONE_SWORD_SWISH_A, // Runesword
    /* 0x66D */ SFX_BONE_SWORD_SWISH_B,
    /* 0x66E */ SFX_BONE_SWORD_SWISH_C,        // Blade, Discus Lord
    /* 0x66F */ SFX_UNK_TELEPORT_BANG_SHORT_A, // TE1, TE5
    /* 0x670 */ SFX_TELEPORT_BANG_SHORT_B,     // RCEN and all beta overlays
    /* 0x671 */ SFX_UNUSED_TELEPORT_BANG_SHORT_C,
    /* 0x672 */ SFX_NOISE_SWEEP_DOWN_A,
    /* 0x673 */ SFX_NOISE_SWEEP_DOWN_B, // Slime
    /* 0x674 */ SFX_FROG_TOAD_TONGUE,
    /* 0x675 */ SFX_LEVER_METAL_BANG,
    /* 0x676 */ SFX_SWITCH_CLICK,
    /* 0x677 */ SFX_RUNESWORD_ATTACK,
    /* 0x678 */ SFX_WEAPON_HIT_A,
    /* 0x679 */ SFX_UNK_TE3_WEAPON_HIT_B,

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
    /* 0x685 */ SFX_BONE_MUSKET_SHOT,
    /* 0x686 */ SFX_UI_ERROR,
    /* 0x687 */ SFX_LEVEL_UP,
    /* 0x688 */ SFX_DEBUG_SELECT, // Low Heartbeat sfx used for Debug menu
    /* 0x689 */ SFX_WEAPON_SCRAPE_ECHO,
    /* 0x68A */ SFX_RIC_HOLY_WATER_ATTACK,
    /* 0x68B */ SFX_DRA_GLASS_BREAK, // "What is a man?!" wine glass shatter
    /* 0x68C */ SFX_WING_FLAP_A,
    /* 0x68D */ SFX_WING_FLAP_B,
    /* 0x68E */ SFX_HEALTH_PICKUP,
    /* 0x68F */ SFX_OUIJA_TABLE_DEATH,
    /* 0x690 */ SFX_FM_EXPLODE_SWISHES,
    /* 0x691 */ SFX_SMALL_FLAME_IGNITE,
    /* 0x692 */ SFX_UNK_TE1_TRANSFORM,
    /* 0x693 */ SFX_STUTTER_EXPLODE_LOW,  // Bloody Zombie, Venus Weed
    /* 0x694 */ SFX_FM_STUTTER_EXPLODE,   // Flying Zombie, Plate Lord
    /* 0x695 */ SFX_FAST_STUTTER_EXPLODE, // Axe Knight, Sword Lord
    /* 0x696 */ SFX_SWORD_LORD_EXPLODE,
    /* 0x697 */ SFX_STUTTER_EXPLODE_A, // Spectral Sword, Warg, Slogra
    /* 0x698 */ SFX_STUTTER_EXPLODE_B, // Diplocephalus, Stone Rose
    /* 0x699 */ SFX_STUTTER_EXPLODE_C, // Diplocephalus
    /* 0x69A */ SFX_ALU_HOLY_WATER_ATTACK,
    /* 0x69B */ SFX_BAT_WING_SWISHES,  // Monster vial 2
    /* 0x69C */ SFX_BAT_SCREECH_SWISH, // Bat Death
    /* 0x69D */ SFX_MAGIC_SWITCH, // Lightning/Ice, Maria animals, NZ0 switch
    /* 0x69E */ SFX_THROW_WEAPON_SWISHES, // Bwaka knife, Boomerang, and more
    /* 0x69F */ SFX_RIC_CRASH_CROSS,
    /* 0x6A0 */ SFX_TRANSFORM_LOW, // (Alucard Bat/Mist Transform)
    /* 0x6A1 */ SFX_STOPWATCH_TICK,
    /* 0x6A2 */ SFX_DEATH_SWISH,
    /* 0x6A3 */ SFX_RAPID_SCRAPE_3X,   // Damage taken, TNT fuse
    /* 0x6A4 */ SFX_UI_SUBWEAPON_TINK, // Memory Card UI, 3 subweapons, F.Shade
    /* 0x6A5 */ SFX_SKULL_KNOCK_A,     // Dhuron
    /* 0x6A6 */ SFX_SKULL_KNOCK_B,     // Bone Pillar, Skull Lord
    /* 0x6A7 */ SFX_UNUSED_SKULL_KNOCK_C,
    /* 0x6A8 */ SFX_ALUCARD_SWORD_SWISH,
    /* 0x6A9 */ SFX_GOLD_PICKUP,
    /* 0x6AA */ SFX_MARIONETTE_RATTLE,
    /* 0x6AB */ SFX_SEED_SPIT,
    /* 0x6AC */ SFX_CANNON_EXPLODE,
    /* 0x6AD */ SFX_UI_ALERT_TINK,
    /* 0x6AE */ SFX_TINK_JINGLE, // Frozen Shade Shards, NO1 Telescope jingle
    /* 0x6AF */ SFX_GUARD_TINK,
    /* 0x6B0 */ SFX_GLASS_SHARDS, // Succubus, Frozen Shade, Shamen Shield
    /* 0x6B1 */ SFX_TRANSFORM_3X, // Karma Coin and shields
    /* 0x6B2 */ SFX_BIBLE_SCRAPE,
    /* 0x6B3 */ SFX_UNK_TE1_TICK,
    /* 0x6B4 */ SFX_UNK_TE2_RATTLE,
    /* 0x6B5 */ SFX_RIC_FLAME_WHIP,
    /* 0x6B6 */ SFX_UNK_TE2_FIRE_BURST,
    /* 0x6B7 */ SFX_LOW_CLOCK_TICK,
    /* 0x6B8 */ SFX_UNK_TE3_LOW_CLOCK_TICK,
    /* 0x6B9 */ SFX_UNUSED_METAL_TING,
    /* 0x6BA */ SFX_FAST_SWORD_SWISHES, // Sword of Dawn, Bone Halberd
    /* 0x6BB */ SFX_BONE_MUSKET_RELOAD,
    /* 0x6BC */ SFX_SKELERANG_CATCH,
    /* 0x6BD */ SFX_QUIET_STEPS, // Maria Cat, ARE, RCAT
    /* 0x6BE */ SFX_BLIPS_A,     // Toad
    /* 0x6BF */ SFX_UNUSED_BLIPS_B,
    /* 0x6C0 */ SFX_BLIPS_C, // Fleaman, Frog
    /* 0x6C1 */ SFX_BLIPS_D, // Fleaman
    /* 0x6C2 */ SFX_DISCUS_LORD_EXPLODE,
    /* 0x6C3 */ SFX_HIPPOGRYPH_FIRE_ATTACK, // Also Maria Dragon Crash
    /* 0x6C4 */ SFX_SALOME_MAGIC_ATTACK,
    /* 0x6C5 */ SFX_MAGIC_NOISE_SWEEP, // Armor Lord, Maria Turtle Crash
    /* 0x6C6 */ SFX_BOSS_WING_FLAP,
    /* 0x6C7 */ SFX_WHIP_TWIRL_SWISH, // Many enemies
    /* 0x6C8 */ SFX_BONE_THROW, // Wereskeleton, Flea Armor, Slogra, and more
    /* 0x6C9 */ SFX_BONE_CREAK, // Bone Archer, Wereskeleton
    /* 0x6CA */ SFX_FLEA_ARMOR_EXPLODE,
    /* 0x6CB */ SFX_RED_SKEL_COLLAPSE,
    /* 0x6CC */ SFX_RED_SKEL_REBUILD,
    /* 0x6CD */ SFX_MULTI_NOISE_SWEEP_DOWN, // ARE only
    /* 0x6CE */ SFX_CORNER_GUARD_DEATH,
    /* 0x6CF */ SFX_TOMBSTONE_MOVE,
    /* 0x6D0 */ SFX_FLEA_RIDER_EXPLODE,
    /* 0x6D1 */ SFX_STONE_ROSE_SEED,
    /* 0x6D2 */ SFX_VENUS_WEED_CHARGE_ATTACK,
    /* 0x6D3 */ SFX_RNO4_MAGIC_GLASS_BREAK,
    /* 0x6D4 */ SFX_PSWORD_TWIRL_ATTACK,
    /* 0x6D5 */ SFX_PSWORD_TWIRL, // Also Succubus Clone Spawn
    /* 0x6D6 */ SFX_CROW_DEATH,
    /* 0x6D7 */ SFX_CROW_CAW,
    /* 0x6D8 */ SFX_UNUSED_CLONE_DISAPPEAR,
    /* 0x6D9 */ SFX_BOSS_CLONE_DISAPPEAR,
    /* 0x6DA */ SFX_METAL_RATTLE_A,     // Ferryman
    /* 0x6DB */ SFX_METAL_RATTLE_B,     // RNZ1 and beta overlays
    /* 0x6DC */ SFX_METAL_RATTLE_C,     // RNZ1
    /* 0x6DD */ SFX_RAPID_SYNTH_BUBBLE, // LIB Lesser Demon
    /* 0x6DE */ SFX_RAPID_SYNTH_BUBBLE_SHORT,
    /* 0x6DF */ SFX_CRASH_CROSS,
    /* 0x6E0 */ SFX_SAVE_COFFIN_SWISH,
    /* 0x6E1 */ SFX_RCEN_GLASS_BREAKS,
    /* 0x6E2 */ SFX_RIC_SUC_REVIVE, // RIC and SUC both use this
    /* 0x6E3 */ SFX_SCYLLA_BUBBLE_BURST,
    /* 0x6E4 */ SFX_PENTAGRAM_ATTACK,
    /* 0x6E5 */ SFX_UNUSED_ANIME_EXPLODE,
    /* 0x6E6 */ SFX_LOW_SYNTH_BUBBLES, // Shaft Orb

    // Player sfx (0x6E7-0x708)

    // vabid 1
    /* 0x6E7 */ SFX_VO_ALU_PAIN_A,
    /* 0x6E8 */ SFX_VO_ALU_PAIN_B,
    /* 0x6E9 */ SFX_VO_ALU_PAIN_C,
    /* 0x6EA */ SFX_VO_ALU_PAIN_D,
    /* 0x6EB */ SFX_VO_ALU_PAIN_E,
    /* 0x6EC */ SFX_VO_ALU_SILENCE, // this was originally pain grunt #6
    /* 0x6ED */ SFX_VO_ALU_YELL,    // Elevator drop or thrown by boss
    /* 0x6EE */ SFX_VO_ALU_ATTACK_A,
    /* 0x6EF */ SFX_VO_ALU_ATTACK_B,
    /* 0x6F0 */ SFX_VO_ALU_ATTACK_C,
    /* 0x6F1 */ SFX_VO_ALU_ATTACK_D,
    /* 0x6F2 */ SFX_VO_ALU_WHAT,
    /* 0x6F3 */ SFX_VO_ALU_DARK_META,
    /* 0x6F4 */ SFX_VO_ALU_SOUL_STEAL,
    /* 0x6F5 */ SFX_UNUSED_6F5,
    /* 0x6F6 */ SFX_VO_ALU_DEATH,
    /* 0x6F7 */ SFX_ALU_WOLF_BARK,
    /* 0x6F8 */ SFX_UNUSED_VO_ALU_WHOA,
    /* 0x6F9 */ SFX_VO_RIC_ATTACK_A,
    /* 0x6FA */ SFX_VO_RIC_ATTACK_B,
    /* 0x6FB */ SFX_VO_RIC_ATTACK_C,
    /* 0x6FC */ SFX_VO_RIC_ATTACK_YELL,
    /* 0x6FD */ SFX_UNUSED_6FD,
    /* 0x6FE */ SFX_UNUSED_6FE,
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

    // Enemy and misc sfx (0x709-0x8F5)

    // vabid 3
    /* 0x709 */ SFX_SLOGRA_ROAR, // different pitch in NP3
    /* 0x70A */ SFX_SLOGRA_ROAR_DEFEAT,
    /* 0x70B */ SFX_SLOGRA_PAIN_A, // Used for Gaibon
    /* 0x70C */ SFX_SLOGRA_PAIN_B,
    /* 0x70D */ SFX_CORPSEWEED_ATTACK,
    /* 0x70E */ SFX_LESSER_DEMON_POISON,
    /* 0x70F */ SFX_VENUS_WEED_HURT,
    /* 0x710 */ SFX_VENUS_WEED_DEATH,
    /* 0x711 */ SFX_UNK_RNZ0_711,
    /* 0x712 */ SFX_UNUSED_712,
    /* 0x713 */ SFX_UNUSED_713,
    /* 0x714 */ SFX_FLYING_ZOMBIE_PAIN,
    /* 0x715 */ SFX_FLYING_ZOMBIE_DEATH,
    /* 0x716 */ SFX_FLYING_ZOMBIE_BODY_RIP,
    /* 0x717 */ SFX_UNK_RDAI_717,
    /* 0x718 */ SFX_VALHALLA_KNIGHT_NEIGH,
    /* 0x719 */ SFX_VALHALLA_KNIGHT_GALLOP,
    /* 0x71A */ SFX_TOAD_CROAK,
    /* 0x71B */ SFX_FROG_CROAK,
    /* 0x71C */ SFX_UNUSED_71C,
    /* 0x71D */ SFX_MERMAN_DEATH,
    /* 0x71E */ SFX_CLOAKED_KNIGHT_ATTACK,
    /* 0x71F */ SFX_UNK_CLOAKED_KNIGHT_71F, // referenced but no sound
    /* 0x720 */ SFX_CLOAKED_KNIGHT_DEATH,
    /* 0x721 */ SFX_UNK_NZ1_721,
    /* 0x722 */ SFX_UNK_NZ1_722,
    /* 0x723 */ SFX_UNK_NZ1_723,
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
    /* 0x732 */ SFX_UNK_RLIB_732,
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
    /* 0x73D */ SFX_UNK_RLIB_73D,

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
    /* 0x75C */ SFX_UNK_RNO4_75C,
    /* 0x75D */ SFX_ROCK_KNIGHT_DEATH,
    /* 0x75E */ SFX_PLATE_LORD_ATTACK,
    /* 0x75F */ SFX_PLATE_LORD_PAIN,
    /* 0x760 */ SFX_PLATE_LORD_DEATH,
    /* 0x761 */ SFX_PLATE_LORD_BALL_IMPACT,
    /* 0x762 */ SFX_BONE_ARK_CHARGE_ATTACK,
    /* 0x763 */ SFX_DISCUS_LORD_ATTACK,
    /* 0x764 */ SFX_DISCUS_LORD_DEATH,
    /* 0x765 */ SFX_DISCUS_BUZZ,
    /* 0x766 */ SFX_AXE_KNIGHT_ATTACK,
    /* 0x767 */ SFX_AXE_KNIGHT_DEATH,
    /* 0x768 */ SFX_HIPPOGRYPH_WING_FLAP,
    /* 0x769 */ SFX_HIPPOGRYPH_SQUAWK, // unused?
    /* 0x76A */ SFX_UNK_RDAI_76A,
    /* 0x76B */ SFX_FROZEN_HALF_DEATH,
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
    /* 0x784 */ SFX_UNK_RNO4_784,
    /* 0x785 */ SFX_WEREWOLF_SPIN_ATTACK,
    /* 0x786 */ SFX_MINOTAUR_ATTACK,
    /* 0x787 */ SFX_MINOTAURUS_JUMP_ATTACK,
    /* 0x788 */ SFX_MINOTAUR_BREATH_ATTACK,
    /* 0x789 */ SFX_UNK_BO2_789,
    /* 0x78A */ SFX_HARPY_ATTACK,
    /* 0x78B */ SFX_HARPY_DEATH,
    /* 0x78C */ SFX_MUDMAN_ATTACK,
    /* 0x78D */ SFX_SPELLBOOK_DEATH, // also used by Magic Tome
    /* 0x78E */ SFX_MAGIC_TOME_ATTACK,
    /* 0x78F */ SFX_LESSER_DEMON_SWIPE_ATTACK,
    /* 0x790 */ SFX_MALACHI_ROLLING_ORB,
    /* 0x791 */ SFX_FIRE_DEMON_ATTACK_CHARGE,
    /* 0x792 */ SFX_OWL_KNIGHT_TAUNT, // "Have at you!"
    /* 0x793 */ SFX_OWL_KNIGHT_ATTACK,
    /* 0x794 */ SFX_OWL_KNIGHT_REACT, // reaction to his pet dying (how sad!)
    /* 0x795 */ SFX_OWL_KNIGHT_DEATH,
    /* 0x796 */ SFX_OWL_DEATH,
    /* 0x797 */ SFX_WATERFALL_LOOP,
    /* 0x798 */ SFX_UNK_TE4_798,
    /* 0x799 */ SFX_UNK_TE4_799,
    /* 0x79A */ SFX_UNK_TE4_79A,
    /* 0x79B */ SFX_UNK_TE4_79B,
    /* 0x79C */ SFX_UNUSED_79C,
    /* 0x79D */ SFX_SHUTTING_WINDOW,
    /* 0x79E */ SFX_UNUSED_79E,
    /* 0x79F */ SFX_UNK_TE3_79F,
    /* 0x7A0 */ SFX_DEATH_TAKES_ITEMS,
    /* 0x7A1 */ SFX_DEATH_LAUGH,
    /* 0x7A2 */ SFX_ITEM_YOINK,
    /* 0x7A3 */ SFX_UNUSED_7A3,

    // vabid 9
    /* 0x7A4 */ SFX_TREE_BRANCH_SNAP,
    /* 0x7A5 */ SFX_CASTLE_GATE_RISE,

    // vabid 3
    /* 0x7A6 */ SFX_CLOCK_ROOM_BELL,
    /* 0x7A7 */ SFX_UNUSED_7A7,
    /* 0x7A8 */ SFX_UNUSED_7A8,

    // vabid 9
    /* 0x7A9 */ SFX_CLOCK_ROOM_TICK,

    // vabid 3
    /* 0x7AA */ SFX_ELEVATOR_GEARS_LOOP,
    /* 0x7AB */ SFX_UNK_TE2_7AB,
    /* 0x7AC */ SFX_TELESCOPE_SHUTTER_CLICK,
    /* 0x7AD */ SFX_ALU_ZZZ_SNORE,
    /* 0x7AE */ SFX_DOP_DOOR_OPEN, // clone of 0x7CB & sounds different in NO1
    /* 0x7AF */ SFX_RAIN_LOOP,
    /* 0x7B0 */ SFX_UNK_TE5_7B0,
    /* 0x7B1 */ SFX_ELEVATOR_DOOR,
    /* 0x7B2 */ SFX_UNK_TE4_7B2,
    /* 0x7B3 */ SFX_ELEVATOR_SLAM,
    /* 0x7B4 */ SFX_UNK_TE4_7B4,

    // vabid 9
    /* 0x7B5 */ SFX_ELEVATOR_START,
    /* 0x7B6 */ SFX_BAD_LUCK_JINGLE,
    /* 0x7B7 */ SFX_NO1_BIRD_CYCLE,

    // vabid 3
    /* 0x7B8 */ SFX_UNK_TE2_7B8,
    /* 0x7B9 */ SFX_UNK_TE2_7B9,
    /* 0x7BA */ SFX_UNK_TE2_7BA,
    /* 0x7BB */ SFX_CONFESS_GHOST_CURTAIN_PULL,

    // vabid 9
    /* 0x7BC */ SFX_CHAPEL_BELL,

    // vabid 3
    /* 0x7BD */ SFX_WOODEN_BRIDGE_EXPLODE,
    /* 0x7BE */ SFX_UNK_NO4_7BE, // unused exploding bridge debris?
    /* 0x7BF */ SFX_OAR_ROW,
    /* 0x7C0 */ SFX_DUNGEON_PRISONER_RATTLE,
    /* 0x7C1 */ SFX_CLOCK_TOWER_GEAR,
    /* 0x7C2 */ SFX_WATER_SPLASH_JUMP,
    /* 0x7C3 */ SFX_WATER_SPLASH_MOVE,
    /* 0x7C4 */ SFX_WATER_BUBBLE,

    // Boss sounds start here

    /* 0x7C5 */ SFX_BOSS_LARGE_FLAMES, // Cerberus BG Fire (BO1 different)
    /* 0x7C6 */ SFX_B07_STOMP,         // BO0 different, no sound in BO1
    /* 0x7C7 */ SFX_BO1_UNK_7C7,       // Granfaloon, Beelzebub, Galamoth
    /* 0x7C8 */ SFX_MEDUSA_WEAPON_SWING,
    /* 0x7C9 */ SFX_UNUSED_7C9,
    /* 0x7CA */ SFX_BO0_UNK_7CA,
    /* 0x7CB */ SFX_DOPPLEGANGER_DOOR_OPEN,
    /* 0x7CC */ SFX_DOPPLEGANGER_APPEAR,
    /* 0x7CD */ SFX_GRANFALOON_APPEAR,
    /* 0x7CE */ SFX_SHAFT_DEATH,
    /* 0x7CF */ SFX_SHAFT_FIRE_ATTACK, // also used by Cerberus
    /* 0x7D0 */ SFX_UNUSED_7D0,
    /* 0x7D1 */ SFX_SCIFI_BLAST, // Photon Torpedo sfx from "Star Trek"

    // vabid 9
    /* 0x7D2 */ SFX_BOSS_DEFEATED,
    /* 0x7D3 */ SFX_DRACULA_FLY_IN,

    // vabid 3
    /* 0x7D4 */ SFX_UNK_TE1_7D4,
    /* 0x7D5 */ SFX_BEELZEBUB_FLY_BUZZ,
    /* 0x7D6 */ SFX_UNUSED_7D6,
    /* 0x7D7 */ SFX_VO_DOP_PAIN_A,
    /* 0x7D8 */ SFX_VO_DOP_PAIN_B,
    /* 0x7D9 */ SFX_VO_DOP_PAIN_C,
    /* 0x7DA */ SFX_VO_DOP_PAIN_D,
    /* 0x7DB */ SFX_VO_DOP_PAIN_E,
    /* 0x7DC */ SFX_VO_DOP_PAIN_F, // unique to Doppleganger
    /* 0x7DD */ SFX_VO_DOP_YELL,
    /* 0x7DE */ SFX_VO_DOP_ATTACK_A,
    /* 0x7DF */ SFX_VO_DOP_ATTACK_B,
    /* 0x7E0 */ SFX_VO_DOP_ATTACK_C,
    /* 0x7E1 */ SFX_VO_DOP_ATTACK_D,
    /* 0x7E2 */ SFX_UNUSED_VO_DOP_WHAT,
    /* 0x7E3 */ SFX_UNUSED_7E3,
    /* 0x7E4 */ SFX_UNUSED_7E4,
    /* 0x7E5 */ SFX_UNUSED_7E5,
    /* 0x7E6 */ SFX_VO_DOP_DEATH,
    /* 0x7E7 */ SFX_UNUSED_7E7,
    /* 0x7E8 */ SFX_DOP_SUBWEAPON_TINK,
    /* 0x7E9 */ SFX_UNUSED_7E9,
    /* 0x7EA */ SFX_THE_CREATURE_HAMMER,
    /* 0x7EB */ SFX_THE_CREATURE_ATTACK,
    /* 0x7EC */ SFX_THE_CREATURE_DEATH,
    /* 0x7ED */ SFX_UNUSED_7ED,
    /* 0x7EE */ SFX_UNUSED_7EE,
    /* 0x7EF */ SFX_DEATH_PAIN_A,
    /* 0x7F0 */ SFX_DEATH_ATTACK, // "Take that!"
    /* 0x7F1 */ SFX_DEATH_SCYTHE_ATTACK,
    /* 0x7F2 */ SFX_DEATH_BALL_ATTACK, // "Death Ball!"
    /* 0x7F3 */ SFX_DEATH_YOURE_STRONG_INDEED,
    /* 0x7F4 */ SFX_DEATH_BUT_NOW_YOU_WILL_DIE,
    /* 0x7F5 */ SFX_UNUSED_7F5,
    /* 0x7F6 */ SFX_UNUSED_7F6,
    /* 0x7F7 */ SFX_DEATH_PAIN_B,
    /* 0x7F8 */ SFX_DEATH_PAIN_C,
    /* 0x7F9 */ SFX_UNK_TE2_7F9,
    /* 0x7FA */ SFX_DEATH_SCYTHE_SWISH,
    /* 0x7FB */ SFX_MEDUSA_STONE,
    /* 0x7FC */ SFX_UNUSED_MEDUSA_OOH_WHOA,
    /* 0x7FD */ SFX_MEDUSA_VENOM,
    /* 0x7FE */ SFX_MEDUSA_ATTACK_A,
    /* 0x7FF */ SFX_MEDUSA_ATTACK_B,
    /* 0x800 */ SFX_UNUSED_MEDUSA_ATTACK_C,
    /* 0x801 */ SFX_MEDUSA_PAIN_A,
    /* 0x802 */ SFX_MEDUSA_PAIN_B,
    /* 0x803 */ SFX_UNUSED_MEDUSA_OH_NO,
    /* 0x804 */ SFX_MEDUSA_DEATH, // "I'm petrified!"
    /* 0x805 */ SFX_SCYLLA_ATTACK_YELL,
    /* 0x806 */ SFX_SCYLLA_ATTACK_DIE,
    /* 0x807 */ SFX_SCYLLA_PAIN,
    /* 0x808 */ SFX_SCYLLA_DEATH,
    /* 0x809 */ SFX_SCYLLA_WYRM_ATTACK,
    /* 0x80A */ SFX_SCYLLA_WYRM_WALL_DEBRIS,
    /* 0x80B */ SFX_GRANFALOON_LASER_ATTACK,
    /* 0x80C */ SFX_UNUSED_GRANFALOON_SCREAM_A, // "Insane Tantrum" stock sfx
    /* 0x80D */ SFX_UNUSED_GRANFALOON_SCREAM_B, // Screams replaced with 0x8C0
    /* 0x80E */ SFX_GRANFALOON_BODIES_FALL,
    /* 0x80F */ SFX_GALAMOTH_ELECTRICITY,
    /* 0x810 */ SFX_UNUSED_GALAMOTH_810, // possibly unused Galamoth sounds
    /* 0x811 */ SFX_UNUSED_GALAMOTH_811,
    /* 0x812 */ SFX_FAKE_SYPHA_ATTACK, // (laughs)
    /* 0x813 */ SFX_FAKE_SYPHA_PAIN,   // "Don't..."
    /* 0x814 */ SFX_FAKE_SYPHA_DEATH,

    // vabid 9
    /* 0x815 */ SFX_FAKE_TREVOR_BLOOD_CROSS,

    // vabid 3
    /* 0x816 */ SFX_OLROX_BAT_ATTACK,
    /* 0x817 */ SFX_OLROX_TRANSFORM, // also used during death animation
    /* 0x818 */ SFX_OLROX_ATTACK,    // "Take that!"
    /* 0x819 */ SFX_OLROX_MONSTER_PAIN,

    // vabid 9
    /* 0x81A */ SFX_OLROX_LASER_ATTACK,

    // vabid 3
    /* 0x81B */ SFX_AKMODAN_II_PAIN,
    /* 0x81C */ SFX_AKMODAN_II_DEATH,
    /* 0x81D */ SFX_AKMODAN_II_ARM_STRETCH,
    /* 0x81E */ SFX_AKMODAN_II_MOVE,
    /* 0x81F */ SFX_AKMODAN_II_DISSOLVE,
    /* 0x820 */ SFX_UNK_RNZ1_DEBRIS_820,
    /* 0x821 */ SFX_UNK_RNZ1_EXPLODE_821,
    /* 0x822 */ SFX_UNK_RNZ1_EXPLODE_822,
    /* 0x823 */ SFX_UNK_RNZ1_SWISH_823,
    /* 0x824 */ SFX_UNK_RNZ1_WIND_824,
    /* 0x825 */ SFX_BOSS_RIC_WHIP_ATTACK, // also Fake Trevor
    /* 0x826 */ SFX_BOSS_RIC_SLIDE_SKID,
    /* 0x827 */ SFX_BOSS_RIC_ITEM_CRASH_ATTACK, // Lightning and Bible
    /* 0x828 */ SFX_BOSS_RIC_HYDRO_STORM,
    /* 0x829 */ SFX_BOSS_RIC_HOLY_CROSS,
    /* 0x82A */ SFX_UNUSED_BOSS_RIC_EVIL_LAUGH,
    /* 0x82B */ SFX_BOSS_RIC_LAUGH, // plays at the end of first phase
    /* 0x82C */ SFX_BOSS_RIC_ATTACK_A,
    /* 0x82D */ SFX_BOSS_RIC_ATTACK_B,
    /* 0x82E */ SFX_BOSS_RIC_ATTACK_C,
    /* 0x82F */ SFX_BOSS_RIC_ATTACK_D,
    /* 0x830 */ SFX_BOSS_RIC_HYDRO_STORM_RAIN,
    /* 0x831 */ SFX_UNUSED_831,
    /* 0x832 */ SFX_UNUSED_832,
    /* 0x833 */ SFX_UNUSED_833,
    /* 0x834 */ SFX_BOSS_RIC_DASH_ATTACK, // "You fool!"
    /* 0x835 */ SFX_UNUSED_835,
    /* 0x836 */ SFX_BOSS_RIC_PAIN_A,
    /* 0x837 */ SFX_BOSS_RIC_PAIN_B,
    /* 0x838 */ SFX_BOSS_RIC_PAIN_C,
    /* 0x839 */ SFX_BOSS_RIC_PAIN_D,
    /* 0x83A */ SFX_BOSS_RIC_PAIN_E,
    /* 0x83B */ SFX_BOSS_RIC_PAIN_F,
    /* 0x83C */ SFX_UNUSED_BOSS_RIC_CURSES,       // "Curses!"
    /* 0x83D */ SFX_UNUSED_BOSS_RIC_INSOLENT_PUP, // "Insolent pup!"
    /* 0x83E */ SFX_BOSS_RIC_DEATH,
    /* 0x83F */ SFX_UNUSED_83F,
    /* 0x840 */ SFX_SHAFT_ATTACK_A,
    /* 0x841 */ SFX_UNUSED_SHAFT_ATTACK_B,
    /* 0x842 */ SFX_UNUSED_SHAFT_ATTACK_C,
    /* 0x843 */ SFX_UNUSED_SHAFT_ATTACK_D,
    /* 0x844 */ SFX_UNUSED_SHAFT_ATTACK_E,
    /* 0x845 */ SFX_SHAFT_ATTACK_DEMONIC_BLESSING,
    /* 0x846 */ SFX_UNUSED_SHAFT_LAUGH_A,
    /* 0x847 */ SFX_UNUSED_SHAFT_DISINTEGRATE,
    /* 0x848 */ SFX_UNUSED_SHAFT_PAIN_A,
    /* 0x849 */ SFX_UNUSED_SHAFT_PAIN_B,
    /* 0x84A */ SFX_UNUSED_SHAFT_PAIN_C,
    /* 0x84B */ SFX_UNUSED_SHAFT_DEATH,
    /* 0x84C */ SFX_SHAFT_ORB_BOUNCE, // also used by The Creature
    /* 0x84D */ SFX_SHAFT_ORB_BREAK,
    /* 0x84E */ SFX_UNUSED_SHAFT_LAUGH_B,
    /* 0x84F */ SFX_DRACULA_LAUGH_A, // different in RBO6
    /* 0x850 */ SFX_DRACULA_LAUGH_B,
    /* 0x851 */ SFX_UNUSED_DRACULA_ATTACK_A,
    /* 0x852 */ SFX_UNUSED_DRACULA_ATTACK_B,
    /* 0x853 */ SFX_DRACULA_FIREBALL_ATTACK,
    /* 0x854 */ SFX_DRACULA_SQUISH_GRUNT, // RBO6 only
    /* 0x855 */ SFX_DRACULA_HERE_IS_TRUE_POWER,
    /* 0x856 */ SFX_UNK_ST0_856,
    /* 0x857 */ SFX_DRACULA_GRANT_ME_POWER,
    /* 0x858 */ SFX_DRACULA_PLAYTIME_IS_OVER,
    /* 0x859 */ SFX_DRACULA_MONSTER_MAGIC_ATTACK, // RBO6 only
    /* 0x85A */ SFX_PSP_DRACULA_FIREBALL_ATTACK,  // unused in PSX
    /* 0x85B */ SFX_DRACULA_PAIN_A,
    /* 0x85C */ SFX_DRACULA_PAIN_B,
    /* 0x85D */ SFX_DRACULA_PAIN_C,
    /* 0x85E */ SFX_UNUSED_DRACULA_PAIN_A,
    /* 0x85F */ SFX_UNUSED_DRACULA_PAIN_B,
    /* 0x860 */ SFX_UNUSED_DRACULA_PAIN_C,
    /* 0x861 */ SFX_UNUSED_DRACULA_PAIN_D,
    /* 0x862 */ SFX_UNUSED_862,
    /* 0x863 */ SFX_UNUSED_863,
    /* 0x864 */ SFX_UNUSED_864,
    /* 0x865 */ SFX_UNUSED_865,
    /* 0x866 */ SFX_DRACULA_MONSTER_ROAR,
    /* 0x867 */ SFX_UNUSED_867,
    /* 0x868 */ SFX_DRACULA_KARASUMAN_SQUISH,
    /* 0x869 */ SFX_DRACULA_ELECTRICITY,
    /* 0x86A */ SFX_UNUSED_86A,
    /* 0x86B */ SFX_DRACULA_BEHOLD_MY_TRUE_FORM, // "...and despair!"
    /* 0x86C */ SFX_UNUSED_86C,
    /* 0x86D */ SFX_UNUSED_86D,
    /* 0x86E */ SFX_SUCCUBUS_LAUGH,   // used for taunt and petal attack
    /* 0x86F */ SFX_UNK_SUCCUBUS_86F, // muted, related to charge attack
    /* 0x870 */ SFX_SUCCUBUS_DUPLICATES,
    /* 0x871 */ SFX_UNUSED_SUCCUBUS_ATTACK_A,
    /* 0x872 */ SFX_SUCCUBUS_HOMING_ORB_ATTACK,
    /* 0x873 */ SFX_UNUSED_SUCCUBUS_ATTACK_B,
    /* 0x874 */ SFX_SUCCUBUS_WING_ATTACK,
    /* 0x875 */ SFX_UNUSED_SUCCUBUS_AH,
    /* 0x876 */ SFX_SUCCUBUS_ILL_SUCK_YOU_DRY,
    /* 0x877 */ SFX_UNUSED_SUCCUBUS_OH_A,
    /* 0x878 */ SFX_UNUSED_SUCCUBUS_OH_B, // duplicate of 0x877
    /* 0x879 */ SFX_SUCCUBUS_PAIN_A,
    /* 0x87A */ SFX_SUCCUBUS_PAIN_B,
    /* 0x87B */ SFX_SUCCUBUS_DEFEAT, // "Nooooo!"
    /* 0x87C */ SFX_SUCCUBUS_HOMING_ORB,

    // vabid 2
    /* 0x87D */ SFX_MARIA_RICHTER, // "Richter!"
    /* 0x87E */ SFX_MARIA_GRANT_HIM_YOUR_STRENGTH,
    /* 0x87F */ SFX_UNUSED_MARIA_AIM_FOR_HIS_HEAD,
    /* 0x880 */ SFX_DRACULA_MONSTER_SILHOUETTE_APPEAR,
    /* 0x881 */ SFX_MARIA_ANIMALS_APPEAR,
    /* 0x882 */ SFX_MARIA_FOOTSTEPS_A,
    /* 0x883 */ SFX_MARIA_FOOTSTEPS_B,
    /* 0x884 */ SFX_UNUSED_884,

    // Familiars/Servants use lookup tables for playing sfxIDs
    /* 0x885 */ SFX_FAERIE_HEALING,      // "Healing!"
    /* 0x886 */ SFX_FAERIE_POTION,       // "Potion"
    /* 0x887 */ SFX_FAERIE_REGENERATION, // "Regeneration"
    /* 0x888 */ SFX_FAERIE_NO_MEDICINE,  // "No medicine left"
    /* 0x889 */ SFX_FAERIE_HAMMER_A,     // using hammer on stoned Alucard
    /* 0x88A */ SFX_FAERIE_HAMMER_B,
    /* 0x88B */ SFX_FAERIE_HAMMER_C,
    /* 0x88C */ SFX_FAERIE_HAMMER_D,
    /* 0x88D */ SFX_FAERIE_FALL_OFF_A, // falling off Alucard's shoulder
    /* 0x88E */ SFX_FAERIE_FALL_OFF_B,
    /* 0x88F */ SFX_FAERIE_FALL_OFF_C,
    /* 0x890 */ SFX_FAERIE_FALL_OFF_D,
    /* 0x891 */ SFX_FAERIE_OH_NO,      // "OH NOOO!" (death reaction)
    /* 0x892 */ SFX_FAERIE_ARE_YOU_OK, // "Are you ok?" (possibly unused?)

    // Yousei and Nose Demon are disabled in PSX
    /* 0x893 */ SFX_YOUSEI_POTION,
    /* 0x894 */ SFX_YOUSEI_UNK_A,
    /* 0x895 */ SFX_YOUSEI_REGENERATION,
    /* 0x896 */ SFX_YOUSEI_UNK_C,
    /* 0x897 */ SFX_YOUSEI_HAMMER_A,
    /* 0x898 */ SFX_YOUSEI_HAMMER_B,
    /* 0x899 */ SFX_YOUSEI_FALL_OFF_A,
    /* 0x89A */ SFX_YOUSEI_FALL_OFF_B,
    /* 0x89B */ SFX_YOUSEI_FALL_OFF_C,
    /* 0x89C */ SFX_YOUSEI_FALL_OFF_D,
    /* 0x89D */ SFX_YOUSEI_YELL,
    /* 0x89E */ SFX_DEMON_GRUNT_1,         // he-ya
    /* 0x89F */ SFX_DEMON_GRUNT_2,         // huh
    /* 0x8A0 */ SFX_DEMON_GRUNT_3,         // hrr
    /* 0x8A1 */ SFX_DEMON_TAKE_THAT,       // "Take that" - possibly unused
    /* 0x8A2 */ SFX_DEMON_DIE,             // "DIE!" - Used for cleave attack
    /* 0x8A3 */ SFX_DEMON_FIRE_SPEAR,      // "Fire Spear"
    /* 0x8A4 */ SFX_DEMON_ICE_SPEAR,       // "Ice Spear"
    /* 0x8A5 */ SFX_DEMON_THUNDER_SPEAR,   // "Thunder Spear"
    /* 0x8A6 */ SFX_DEMON_LIGHTNING_SPEAR, // "Lightning spear"
    /* 0x8A7 */ SFX_UNUSED_DEMON_EAT,      // "Eat!"
    /* 0x8A8 */ SFX_NOSE_DEMON_UNK_A,
    /* 0x8A9 */ SFX_NOSE_DEMON_UNK_B,
    /* 0x8AA */ SFX_NOSE_DEMON_UNK_C,
    /* 0x8AB */ SFX_NOSE_DEMON_UNK_D,
    /* 0x8AC */ SFX_NOSE_DEMON_UNK_E,
    /* 0x8AD */ SFX_NOSE_DEMON_UNK_F,
    /* 0x8AE */ SFX_NOSE_DEMON_UNK_G,
    /* 0x8AF */ SFX_NOSE_DEMON_UNK_H,
    /* 0x8B0 */ SFX_NOSE_DEMON_UNK_I,
    /* 0x8B1 */ SFX_NOSE_DEMON_UNK_J,
    /* 0x8B2 */ SFX_SWORD_SERVANT_SLASH,      // "Ssslash!"
    /* 0x8B3 */ SFX_SWORD_SERVANT_SLICE,      // "Slice!"
    /* 0x8B4 */ SFX_SWORD_SERVANT_TEAR,       // "Tear open the heavens!"
    /* 0x8B5 */ SFX_SWORD_SERVANT_DARK_EDGE,  // "Dark Edge!"
    /* 0x8B6 */ SFX_SWORD_SERVANT_BROS_SPELL, // "Gather, brother soul blades!"
    /* 0x8B7 */ SFX_SWORD_SERVANT_GRUNT_A,
    /* 0x8B8 */ SFX_SWORD_SERVANT_GRUNT_B,

    // vabid 9
    /* 0x8B9 */ SFX_THE_CREATURE_HEAD_FALL,
    /* 0x8BA */ SFX_TELEPORT_SYNTH_UP,
    /* 0x8BB */ SFX_TELEPORT_SYNTH_DOWN,
    /* 0x8BC */ SFX_UNUSED_TELEPORT_SYNTH_UP,
    /* 0x8BD */ SFX_UNUSED_TELEPORT_SYNTH_DOWN,
    /* 0x8BE */ SFX_BURNING_PHOTOGRAPH,
    /* 0x8BF */ SFX_DRACULA_TRIANGLE_ATTACK,
    /* 0x8C0 */ SFX_GRANFALOON_SCREAMS_A,
    /* 0x8C1 */ SFX_GRANFALOON_SCREAMS_B,
    /* 0x8C2 */ SFX_BEELZEBUB_PAIN,
    /* 0x8C3 */ SFX_BIBLE_SUBWPN_SWISH, // plays every 10 frames during attack

    // 0x8C4 - 0x8CB appear to be unused

    // vabid 0
    /* 0x8CD */ SFX_UI_NAME_ENTRY = 0x8CD,
    /* 0x8CE */ SFX_UNUSED_UI_NAME_ENTRY,
    /* 0x8CF */ SFX_UNUSED_ANIME_SWORD,

    // vabid 3
    /* 0x8D0 */ SFX_UNUSED_8D0,
    /* 0x8D1 */ SFX_SUCCUBUS_DELICIOUS, // "Mmm, delicious!"

    // 0x8D2 - 0x8E5 appear to be unused

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
