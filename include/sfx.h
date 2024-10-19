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
#define SET_PAUSE_SFX_SCRIPTS 0xE
#define SET_UNPAUSE_SFX_SCRIPTS 0xF
#define SET_UNK_10 0x10
#define SET_UNK_11 0x11
#define SET_UNK_12 0x12
#define SET_UNK_90 0x90
#define SET_RELEASE_RATE_LOW_20_21 0xa3
#define SET_RELEASE_RATE_LOW_22_23 0xa7
#define SET_KEY_ON_20_21 0xa4
#define SET_KEY_ON_22_23 0xa8

#define CD_SOUND_COMMAND_FADE_OUT_2 2
#define CD_SOUND_COMMAND_FADE_OUT_1 3
#define CD_SOUND_COMMAND_START_XA 4
#define CD_SOUND_COMMAND_6 6
#define CD_SOUND_COMMAND_8 8
#define CD_SOUND_COMMAND_10 10
#define CD_SOUND_COMMAND_12 12
#define CD_SOUND_COMMAND_14 14
#define CD_SOUND_COMMAND_16 16

// XA music tracks
// LOOP_POINT means it starts playing from part way into the song
#define MU_LOST_PAINTING 0x301
#define MU_LOST_PAINTING_LOOP_POINT 0x302
#define MU_CURSE_ZONE 0x303
#define MU_CURSE_ZONE_LOOP_POINT 0x304
#define MU_REQUIEM_FOR_THE_GODS 0x305
#define MU_REQUIEM_FOR_THE_GODS_LOOP_POINT 0x306
#define MU_RAINBOW_CEMETERY 0x307
#define MU_RAINBOW_CEMETERY_LOOP_POINT 0x308
#define MU_WOOD_CARVING_PARTITA 0x309
// 0x30A seems to be blank
#define MU_CRYSTAL_TEARDROPS 0x30B
#define MU_CRYSTAL_TEARDROPS_LOOP_POINT 0x30C
#define MU_MARBLE_GALLERY 0x30D
#define MU_MARBLE_GALLERY_LOOP_POINT 0x30E
#define MU_DRACULAS_CASTLE 0x30F
#define MU_DRACULAS_CASTLE_LOOP_POINT 0x310
#define MU_THE_TRAGIC_PRINCE 0x311
#define MU_THE_TRAGIC_PRINCE_LOOP_POINT 0x312
#define MU_TOWER_OF_MIST 0x313
#define MU_TOWER_OF_MIST_LOOP_POINT 0x314
#define MU_DOOR_OF_HOLY_SPIRITS 0x315
#define MU_DOOR_OF_HOLY_SPIRITS_LOOP_POINT 0x316
#define MU_DANCE_OF_PALES 0x317
#define MU_DANCE_OF_PALES_LOOP_POINT 0x318
#define MU_ABANDONED_PIT 0x319
#define MU_ABANDONED_PIT_LOOP_POINT 0x31A
#define MU_HEAVENLY_DOORWAY 0x31B
// 0x31C empty
#define MU_FESTIVAL_OF_SERVANTS 0x31D
#define MU_FESTIVAL_OF_SERVANTS_LOOP_POINT 0x31E
#define MU_DANCE_OF_ILLUSIONS 0x31F
#define MU_DANCE_OF_ILLUSIONS_LOOP_POINT 0x320
#define MU_PROLOGUE 0x321
#define MU_PROLOGUE_LOOP_POINT 0x322
#define MU_WANDERING_GHOSTS 0x323
#define MU_WANDERING_GHOSTS_LOOP_POINT 0x324
#define MU_THE_DOOR_TO_THE_ABYSS 0x325
#define MU_THE_DOOR_TO_THE_ABYSS_LOOP_POINT 0x326
#define MU_METAMORPHOSIS 0x327
#define MU_METAMORPHOSIS_II 0x328
// 0x329 blank
#define SE_INTRO_WIND 0x32A // wind sound from intro
#define SE_INTRO_WIND_LOOP_POINT 0x32B
#define SE_INTRO_WIND_QUIET 0x32C // quieter wind
#define SE_INTRO_WIND_QUIET_LOOP_POINT 0x32D
#define MU_DANCE_OF_GOLD 0x32E
#define MU_DANCE_OF_GOLD_LOOP_POINT 0x32F
#define MU_ENCHANTED_BANQUET 0x330
#define MU_ENCHANTED_BANQUET_LOOP_POINT 0x331
#define MU_PRAYER 0x332
#define MU_PRAYER_LOOP_POINT 0x333
#define MU_DEATH_BALLAD 0x334
#define MU_DEATH_BALLAD_LOOP_POINT 0x335
#define MU_BLOOD_RELATIONS 0x336
#define MU_BLOOD_RELATIONS_LOOP_POINT 0x337
#define MU_FINAL_TOCATTA 0x338
#define MU_FINAL_TOCATTA_LOOP_POINT 0x339
#define MU_BLACK_BANQUET 0x33A
#define MU_BLACK_BANQUET_LOOP_POINT 0x33B
#define MU_I_AM_THE_WIND 0x33C
#define MU_SILENCE 0x33D
#define MU_LAND_OF_BENEDICTION 0x33E
#define MU_JP_FAIRY_SONG 0x33F      // japanese version of fairy song
#define MU_MOONLIGHT_NOCTURNE 0x340 // music during intro scrolling text

// japanese intro narration
#define JP_VO_KATSUTE 0x341 // Narrator says "Katsute ..."
#define JP_VO_SOSHITE                                                          \
    0x342 // Narrator says "Soshite 5 nen no tsukihi ga nagareta"
#define JP_VO_AKUMAJO                                                          \
    0x343 // Narrator says "Akumajo Dracula X Gekka no Yasoukyoku"

// japanese voice actor messages
#define JP_VO_FUKAMI_RIKA_MESSAGE 0x344      // Message from Fukami Rika
#define JP_VO_SHIINA_HEKIRU_MESSAGE 0x345    // Message from Shiina Hekiru
#define JP_VO_YANADA_KIYOYUKI_MESSAGE 0x346  // Message from Yanada Kiyoyuki
#define JP_VO_OKIAYU_RYOUTAROU_MESSAGE 0x347 // Message from Okiayu Ryoutarou
#define JP_VO_SATOU_MASAHARU_MESSAGE 0x348   // Message from Satou Masaharu
#define JP_VO_WAKAMOTO_NORIO_MESSAGE 0x349   // Message from Wakamoto Norio
#define JP_VO_YOKOYAMA_CHISA_MESSAGE 0x34A   // Message from Yokoyama Chisa
#define JP_VO_YANAMI_JYOUJI_MESSAGE 0x34B    // Message from Yanami Jyouji

// various voice actors saying konami
#define JP_VO_KONAMI_1 0x34C  // woman says konami
#define JP_VO_KONAMI_2 0x34D  // woman says konami
#define JP_VO_KONAMI_3 0x34E  // woman says konami
#define JP_VO_KONAMI_4 0x34F  // man says kona (mi cut off?)
#define JP_VO_KONAMI_5 0x350  // man says kona (mi cut off?)
#define JP_VO_KONAMI_6 0x351  // man says konami
#define JP_VO_KONAMI_7 0x352  // man says konami
#define JP_VO_KONAMI_8 0x353  // man says konami
#define JP_VO_KONAMI_9 0x354  // woman says konami
#define JP_VO_KONAMI_10 0x355 // woman says konami
#define JP_VO_KONAMI_11 0x356 // man says konami
#define JP_VO_KONAMI_12 0x357 // man says konami

// Prologue cutscene
#define NA_VO_RI_DIE_MONSTER 0x358 // Richter says "Die monster ..."
#define NA_VO_DR_IT_WAS_NOT 0x359  // Dracula says "It was not by my hand ..."
#define NA_VO_RI_TRIBUTE 0x35A     // Richter says "Tribute? ..."

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

#define JP_VO_SH_GROAN 0x52E      // Shaft groans
#define JP_VO_SH_SCREAM 0x52F     // Shaft screams
#define JP_VO_SH_SONO_TEIDO 0x530 // Shaft: Sono teido no chikara de tatakai...
#endif

#define NA_SE_VO_AL_PUNCH 0x6F1
#define NA_SE_VO_AL_WHAT 0x6F2
#define NA_SE_VO_AL_DARK_METAMORPHOSIS 0x6F3
#define NA_SE_VO_AL_SOUL_STEAL 0x6F4
#define NA_SE_VO_AL_DYING 0x6F6
#define SFX_UNK_6FF 0x6FF
#define SFX_RICHTER_ATTACK_HIT 0x705
#define ALUCARD_DARK_METAMORPHOSIS 0x705
#define NA_SE_VO_WO_BARK 0x706
#define NA_SE_EN_SLOGRA_HISSING 0x709
#define NA_SE_EN_GAIBON_SCREAM 0x70B
#define NA_SE_EN_SLOGRA_HURT_2 0x70A
#define NA_SE_EN_SLOGRA_HURT 0x70C
#define NA_SE_EN_SPITTLEBONE_ACID_SPLAT 0x73C
#define NA_SE_EN_BLOODY_ZOMBIE_INJURED_SCREAM 0x746
#define NA_SE_EN_BLOODY_ZOMBIE_DEATH_SCREAM 0x747
#define NA_SE_EN_BLOODY_ZOMBIE_INJURED 0x748
#define NA_SE_EN_BLOODY_ZOMBIE_HEMORRHAGE 0x749
#define NA_SE_VO_AXE_KNIGHT_THROW 0x766
#define NA_SE_VO_AXE_KNIGHT_SCREAM 0x767
#define NA_SE_EV_WATER_SPLASH 0x7C2
#define NA_SE_VO_DR_TAUNT_1 0x84F
#define NA_SE_VO_DR_TAUNT_2 0x850
#define NA_SE_VO_DR_HURT_1 0x853
#define NA_SE_VO_DR_HERE_IS_TRUE_POWER 0x855
#define NA_SE_VO_DR_GRANT_ME_POWER 0x857
#define NA_SE_VO_DR_PLAYTIME_IS_OVER 0x858
#define NA_SE_VO_DR_HURT_2 0x85B
#define NA_SE_VO_DR_HURT_3 0x85C
#define NA_SE_VO_DR_HURT_4 0x85D
#define NA_SE_PL_TELEPORT 0x8BA
#define SFX_UNK_8BB 0x8BB
#define NA_SE_CS_BURNING_PHOTOGRAPH 0x8BE
// plays every 10 frames while using bible subweapon
#define BIBLE_SUBWPN_SWOOSH 0x8C3

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
#define SFX_UNK_780 0x780
#define SFX_UNK_781 0x781
#define SFX_UNK_782 0x782
#define NA_SE_EV_WINDOW_LATCH 0x79D
#define SE_DEATH_TAKES_ITEMS 0x7A0
#define NA_VO_DEATH_LAUGH 0x7A1
#define SE_ITEM_YOINK 0x7A2
#define SE_TREE_BRANCH_SNAP 0x7A4
#define SE_CASTLE_GATE_RISE 0x7A5

// SHARED SOUNDS
// These are sounds that are shared across multiple BIN files
#define SE_BOSS_DEFEATED 0x7D2

// DRA
#define SFX_UNK_6F7 0x6F7

// UNUSED SOUNDS
#define NA_VO_MAR_AIM_HEAD 0x87F

// The VAB IDs appear in large chunks so all sounds proceeding
// a vabid label comment will belong in that VAB group unless noted.

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
    SFX_HARPY_WING_FLAP = 0x601,
    SFX_RIC_WHIP_RATTLE_A,
    SFX_RIC_WHIP_RATTLE_B, // (B through E appear to be unused)
    SFX_RIC_WHIP_RATTLE_C,
    SFX_RIC_WHIP_RATTLE_D,
    SFX_RIC_WHIP_RATTLE_E,
    SFX_STONE_MOVE_A,
    SFX_STONE_MOVE_B,
    SFX_STONE_MOVE_C,
    SFX_WEAPON_SWISH_A,
    SFX_WEAPON_SWISH_B,
    SFX_WEAPON_SWISH_C,
    SFX_METAL_CLANG_A,
    SFX_METAL_CLANG_B,
    SFX_METAL_CLANG_C,
    SFX_METAL_CLANG_D, // 0x610
    SFX_METAL_CLANG_E, // Stone Skull Hit
    SFX_METAL_CLANG_F,
    SFX_UNK_CROW,
    SFX_ELECTRICITY,
    SFX_SCRAPE_A,
    SFX_SCRAPE_B,
    SFX_SCRAPE_C, // Alucard backslide
    // vabid 9
    SFX_UNK_618, // Referenced in ST0, TE1, TE2
    // vabid 0
    SFX_GLASS_BREAK_A,
    SFX_GLASS_BREAK_B,
    SFX_GLASS_BREAK_C,
    SFX_GLASS_BREAK_D,
    SFX_GLASS_BREAK_E, // Vase Break
    SFX_BAT_ECHO_A,
    SFX_BAT_ECHO_B, // Alucard Echo of Bat
    SFX_BAT_ECHO_C, // 0x620
    SFX_BAT_ECHO_D,
    SFX_SKULL_BONK,
    SFX_RIC_RSTONE_TINK, // Rebound Stone
    SFX_SMALL_BURST,
    SFX_ARROW_SHOT_A, // Magic Missile Shot
    SFX_ARROW_SHOT_B,
    SFX_ARROW_SHOT_C,
    SFX_ARROW_SHOT_D,
    SFX_SKELETON_DEATH_A,
    SFX_SKELETON_DEATH_B,
    SFX_SKELETON_DEATH_C,
    SFX_FIRE_SHOT,
    SFX_WEAPON_STAB_A,
    SFX_WEAPON_STAB_B,     // Common stab sfx
    SFX_WEAPON_APPEAR,     // Item Crash, Neutron Bomb
    SFX_UNK_BETA_630,      // 0x630 (MAD, TE1, TE2, TE3, TE4, TE5)
    SFX_DEATH_AMBIENCE,    // BGM ambience during first Death cutscene
    SFX_MAGIC_GLASS_BREAK, // Subweapon Container
    SFX_UI_CONFIRM,
    SFX_CANDLE_HIT,
    SFX_TELEPORT_BANG_A, // Used when teleport starts
    SFX_TELEPORT_BANG_B, // Used when teleport ends, but is also Warp Enter
    SFX_SUC_APPEAR,      // Succubus reveal
    SFX_UNK_SCRAPE_A,
    SFX_UNK_SCRAPE_B,
    SFX_UNK_SCRAPE_C,
    SFX_UNK_UI_SELECT,
    SFX_START_SLAM_A, // Dark Shield
    SFX_START_SLAM_B, // "Press Start", Door Open, Dracula Stomp, etc.
    SFX_START_SLAM_C,
    SFX_ANIME_SWORD_A,
    SFX_ANIME_SWORD_B, // 0x640, Holy Rod ("Anime shing" element)
    SFX_ANIME_SWORD_C,
    SFX_DOOR_OPEN,
    SFX_WALL_DEBRIS_A,
    SFX_WALL_DEBRIS_B, // Warp Exit & Wall Break
    SFX_WALL_DEBRIS_C,
    SFX_STOMP_HARD_A,
    SFX_STOMP_HARD_B, // Alucard Landing (Hard)
    SFX_STOMP_HARD_C,
    SFX_STOMP_HARD_D,
    SFX_STOMP_HARD_E,
    SFX_STOMP_SOFT_A, // Richter Landing (Hard)
    SFX_STOMP_SOFT_B, // Alucard Landing (Normal)
    SFX_SAVE_HEARTBEAT,
    SFX_BAT_SCREECH,
    SFX_DOOR_CLOSE_A,
    SFX_DOOR_CLOSE_B, // 0x650
    SFX_UNK_UI_ERROR,
    SFX_EXPLODE_FAST_A, // Explosion "stutter" effect
    SFX_EXPLODE_FAST_B,
    SFX_EXPLODE_A,
    SFX_EXPLODE_B,
    SFX_EXPLODE_C,
    SFX_EXPLODE_D,
    SFX_EXPLODE_E,
    SFX_EXPLODE_F,
    SFX_FM_EXPLODE_A, // FM synth explosion
    SFX_FM_EXPLODE_B,
    SFX_FM_EXPLODE_C,
    SFX_FM_EXPLODE_D,
    SFX_EXPLODE_SMALL, // Zombie death explosion
    SFX_UNK_FIRE_WHOOSH,
    SFX_FIREBALL_SHOT_A, // 0x660
    SFX_FIREBALL_SHOT_B,
    SFX_FIREBALL_SHOT_C,
    SFX_GUNSHOT,
    SFX_THUNDER_A,
    SFX_THUNDER_B,
    SFX_THUNDER_C,
    SFX_UNK_LOW_UI,
    SFX_TRANSFORM,
    SFX_MAGIC_WEAPON_APPEAR_A,
    SFX_MAGIC_WEAPON_APPEAR_B,
    SFX_WEAPON_BREAK,
    SFX_BONE_SWORD_SWISH_A,
    SFX_BONE_SWORD_SWISH_B,
    SFX_BONE_SWORD_SWISH_C,
    SFX_TELEPORT_BANG_SHORT_A,
    SFX_TELEPORT_BANG_SHORT_B, // 0x670
    SFX_TELEPORT_BANG_SHORT_C,
    SFX_NOISE_SWEEP_DOWN_A,
    SFX_NOISE_SWEEP_DOWN_B,
    SFX_BOING,
    SFX_LEVER_METAL_BANG,
    SFX_SWITCH_CLICK,
    SFX_WEAPON_ENERGY,
    SFX_WEAPON_HIT_A,
    SFX_WEAPON_HIT_B,
    // vabid 9
    SFX_HEART_PICKUP,
    SFX_UI_MOVE,
    SFX_ITEM_PICKUP,
    SFX_UI_MP_FULL,
    SFX_CANDLE_HIT_WHOOSH_A,
    SFX_CANDLE_HIT_WHOOSH_B,
    SFX_QUICK_STUTTER_EXPLODE_A, // 0x680
    SFX_RARE_FM_IMPACT,          // RARE overlay only
    SFX_KARMA_COIN_JINGLE,
    SFX_QUICK_STUTTER_EXPLODE_B,
    SFX_FM_THUNDER_EXPLODE,
    SFX_GUNSHOT_HIGH,
    SFX_UI_ERROR,
    SFX_LEVEL_UP,
    SFX_DEBUG_SELECT, // Low Heartbeat sfx used for Debug menu
    SFX_WEAPON_SCRAPE_ECHO,
    SFX_GLASS_BREAK_WHOOSH,
    SFX_DRA_GLASS_BREAK, // "What is a man?!" wine glass shatter
    SFX_WING_FLAP_A,
    SFX_WING_FLAP_B,
    SFX_HEALTH_PICKUP,
    SFX_STUTTER_FIREBALL,
    SFX_FM_EXPLODE_SWISHES, // 0x690
    SFX_SMALL_FLAME_IGNITE,
    SFX_UNK_TRANSFORM,
    SFX_STUTTER_EXPLODE_LOW,
    SFX_FM_STUTTER_EXPLODE,
    SFX_FAST_STUTTER_EXPLODE,
    SFX_FM_MULTI_EXPLODE,
    SFX_STUTTER_EXPLODE_A,
    SFX_STUTTER_EXPLODE_B,
    SFX_STUTTER_EXPLODE_C,
    SFX_FM_EXPLODE_GLASS_ECHO,
    SFX_BAT_WING_SWISHES,
    SFX_BAT_SCREECH_SWISH, // Bat Death
    SFX_MAGIC_SWITCH,
    SFX_THROW_WEAPON_SWISHES,
    SFX_THROW_WEAPON_MAGIC,
    SFX_TRANSFORM_LOW, // 0x6A0 (Alucard Bat/Mist Transform)
    SFX_CLOCK_TICK,
    SFX_DEATH_SWISH,
    SFX_WATER_DAMAGE_SWISHES,
    SFX_UI_TINK, // Also Rebound Stone Bounce
    SFX_SKULL_KNOCK_A,
    SFX_SKULL_KNOCK_B,
    SFX_SKULL_KNOCK_C,
    SFX_ALUCARD_SWORD_SWISH,
    SFX_GOLD_PICKUP,
    SFX_MARIONETTE_RATTLE,
    SFX_SEED_SPIT,
    SFX_CANNON_EXPLODE,
    SFX_UI_ALERT_TINK,
    SFX_TINK_JINGLE, // Frozen Shade Shards, NO1 Telescope jingle
    SFX_GUARD_TINK,
    SFX_GLASS_SHARDS, // 0x6B0 (Succubus, Frozen Shade, Shamen Shield)
    SFX_TRANSFORM_3X, // Karma Coin and shields
    SFX_BIBLE_SCRAPE,
    SFX_UNK_TICK,
    SFX_UNK_RATTLE,
    SFX_RIC_FLAME_WHIP,
    SFX_UNK_FIRE_BURST,
    SFX_LOW_CLOCK_TICK,
    SFX_UNK_LOW_CLOCK_TICK,
    SFX_UNK_METAL_TING,
    SFX_FAST_SWORD_SWISHES, // Sword of Dawn
    SFX_GRANDFATHER_CLOCK_TICK,
    SFX_MULTI_CLOCK_TICK,
    SFX_QUIET_STEPS,
    SFX_BLIPS_A,
    SFX_UNK_BLIPS_B,
    SFX_BLIPS_C, // 0x6C0
    SFX_BLIPS_D, // Fleaman movement
    SFX_CAT_MULTI_EXPLODE,
    SFX_SWISHES_ECHO_REPEAT,
    SFX_RCAT_DISSONANT_DINK,
    SFX_MAGIC_NOISE_SWEEP,
    SFX_BOSS_WING_FLAP,
    SFX_WHIP_TWIRL_SWISH,
    SFX_BONE_THROW,
    SFX_CREAK,
    SFX_LOW_SKEL_EXPLODE,
    SFX_RED_SKEL_COLLAPSE,
    SFX_RED_SKEL_REBUILD,
    SFX_MULTI_NOISE_SWEEP_DOWN,
    SFX_SKEL_EXPLODE,
    SFX_EXPLODE_ECHO,
    SFX_IGNITE_SWISHES, // 0x6D0
    SFX_SEED_BLIP,
    SFX_DISSONANT_SCREECH,
    SFX_RNO4_MAGIC_GLASS_BREAK,
    SFX_PSWORD_TWIRL_ATTACK,
    SFX_PSWORD_TWIRL, // Also Succubus Clone Spawn
    SFX_CROW_CAW_PAIN,
    SFX_CROW_CAW,
    SFX_UNK_CLONE_DISAPPEAR,
    SFX_BOSS_CLONE_DISAPPEAR,
    SFX_METAL_RATTLE_A,
    SFX_METAL_RATTLE_B,
    SFX_METAL_RATTLE_C,
    SFX_RAPID_SYNTH_BUBBLE,
    SFX_RAPID_SYNTH_BUBBLE_SHORT,
    SFX_CRASH_CROSS,
    SFX_SAVE_COFFIN_SWISH, // 0x6E0
    SFX_RCEN_GLASS_BREAKS,
    SFX_RIC_SUC_REVIVE, // RIC and SUC both use this
    SFX_BUBBLE_BURST,
    SFX_PENTAGRAM_ATTACK,
    SFX_UNK_ANIME_EXPLODE,
    SFX_LOW_SYNTH_BUBBLES,
    // vabid 1
    SFX_VO_ALU_PAIN_A,
    SFX_VO_ALU_PAIN_B,
    SFX_VO_ALU_PAIN_C,
    SFX_VO_ALU_PAIN_D,
    SFX_VO_ALU_PAIN_E,
    SFX_VO_ALU_SILENCE,
    SFX_VO_ALU_YELL, // Elevator yell
    SFX_VO_ALU_ATTACK_A,
    SFX_VO_ALU_ATTACK_B,
    SFX_VO_ALU_ATTACK_C, // 0x6F0
    SFX_VO_ALU_ATTACK_D,
    SFX_VO_ALU_WHAT,
    SFX_VO_ALU_DARK_META,
    SFX_VO_ALU_SOUL_STEAL,
    SFX_UNUSED_6F5,
    SFX_VO_ALU_DEATH,
    SFX_ALU_WOLF_BARK,
    SFX_UNK_VO_ALU_WHOA,
    SFX_VO_RIC_ATTACK_A,
    SFX_VO_RIC_ATTACK_B,
    SFX_VO_RIC_ATTACK_C,
    SFX_VO_RIC_ATTACK_YELL,
};

#endif

#endif
