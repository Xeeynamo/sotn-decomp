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

#define SET_SOUNDMODE_MONO 5
#define SET_SOUNDMODE_STEREO 6
#define SET_STOP_SEQ 7
#define SET_STOP_MUSIC 0xA
#define SET_UNK_0B 0xB
#define SET_UNK_0E 0xE
#define SET_UNK_0F 0xF
#define SET_UNK_10 0x10
#define SET_UNK_11 0x11
#define SET_UNK_12 0x12

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

// This sound plays when MAX UP spawns and during Dracula transformation
#define NA_SE_UNK_62F 0x62F
#define NA_SE_EV_HEAVY_BLOCK_DRAG 0x609
#define NA_SE_EN_BLOOD_ZOMBIE_SWORD_SLASH 0x60B
#define SFX_SUBWPN_THROW 0x60C // Throwing rebound stone, vibhuti, others?
#define SFX_CLANK 0x611 // when attacking invulnerable enemy (like Stone Skull)
#define NA_SE_EN_ELECTRIC_ZAP 0x614
#define NA_SE_AL_BACKSLIDE 0x617
#define NA_SE_EV_VASE_BREAK 0x61D
#define NA_SE_PL_BT_ECHO 0x61F
#define NA_SE_EN_SALEM_WITCH_HAND_MOVEMENT 0x624
#define NA_SE_EN_SKELETON_DESTROY 0x62B
#define SFX_WEAPON_62C 0x62C
#define NA_SE_EV_GLASS_BREAK 0x632
#define NA_SE_BREAK_CANDLE 0x634
#define NA_SE_EN_SALEM_WITCH_TRIBOLT_LAUNCH NA_SE_BREAK_CANDLE
#define NA_SE_PL_WARP 0x636
#define SFX_SWITCH_PRESSED 0x640    // Demon presses switch in CHI

#if defined(VERSION_BETA)
#define SFX_OPEN_DOOR 0x640
#define SFX_DOOR_UNKNOWN 0x64D
#else
#define SFX_OPEN_DOOR 0x642
#define SFX_DOOR_UNKNOWN 0x64F
#endif

#define NA_SE_EN_COG_CLICK 0x642
#define NA_SE_EN_ROCK_BREAK 0x644
#define SOUND_BAT_SCREECH 0x64E
#define NA_SE_EN_SLOGRA_FLOOR_STOMP 0x64F
#define NA_SE_EN_GAIBON_SMALL_FIREBALL 0x652
#define NA_SE_EN_GAIBON_BIG_FIREBALL 0x655
#define NA_SE_SECRET_STAIRS NA_SE_EN_ROCK_BREAK
#define NA_SE_SECRET_STAIRS_THUMP NA_SE_EN_GAIBON_BIG_FIREBALL
#define NA_SE_FIRE_BURST 0x65B
#define NA_SE_EN_ZOMBIE_EXPLODE 0x65E
#define NA_SE_EN_GAIBON_FLAME_OUT 0x65E
#define NA_SE_EN_DR_FIREBALL 0x660
#define NA_SE_EN_SALEM_WITCH_CURSE_LAUNCH 0x663
#define NA_SE_EN_AXE_KNIGHT_BREAK_AXE 0x66B
#define NA_SE_EN_BONE_SCIMITAR_SWORD_SLASH 0x66D
#define NA_SE_EN_GAIBON_COLLAPSE 0x672
#define NA_SE_EV_SWITCH_CLICK 0x676
#define NA_SE_PL_COLLECT_HEART 0x67A
#define NA_SE_SY_MOVE_MENU_CURSOR 0x67B
#define NA_SE_PL_IT_PICKUP 0x67C
#define NA_SE_PL_MP_GAUGE 0x67D
#define NA_SE_PL_BT_FIREBALL 0x680
#define NA_SE_PL_MAX_HP_MP_INCREASED 0x687
#define NA_SE_BREAK_GLASS 0x68B
#define NA_SE_EN_GAIBON_FLAP_WINGS 0x68D
#define NA_SE_EN_SLOGRA_SPEAR_PROJECTILE 0x690
#define NA_SE_EN_GAIBON_FLAME 0x691
#define NA_SE_EN_EXPLOSIVE_DEATH 0x693
#define NA_SE_EN_SLOGRA_DEATH_EXPLOSION 0x697
#define NA_SE_EV_CLOCK_TICK 0x6A1
#define REBOUND_STONE_BOUNCE 0x6A4
#define NA_SE_PL_COLLECT_GOLD 0x6A9
#define NA_SE_EN_SLOGRA_SPEAR_SLASH 0x6C6
#define NA_SE_EN_SLOGRA_BEAK_ATTACK 0x6C8
#define NA_SE_EN_SKELETON_THROW_BONE 0x6C8
#define NA_SE_EN_BLOOD_SKELETON_DISASSEMBLES 0x6CB
#define NA_SE_EN_BLOOD_SKELETON_REASSEMBLES 0x6CC
#define NA_SE_PL_RIC_UNK_6E2 0x6E2
#define NA_SE_VO_AL_PUNCH 0x6F1
#define NA_SE_VO_AL_WHAT 0x6F2
#define NA_SE_VO_AL_DARK_METAMORPHOSIS 0x6F3
#define NA_SE_VO_AL_SOUL_STEAL 0x6F4
#define NA_SE_VO_AL_DYING 0x6F6
#define SFX_RICHTER_ATTACK_HIT 0x705
#define ALUCARD_DARK_METAMORPHOSIS 0x705
#define NA_SE_VO_WO_BARK 0x706
#define NA_SE_EN_SLOGRA_HISSING 0x709
#define NA_SE_EN_GAIBON_SCREAM 0x70B
#define NA_SE_EN_SLOGRA_HURT_2 0x70A
#define NA_SE_EN_SLOGRA_HURT 0x70C
#define NA_SE_EN_SALEM_WITCH_ATTACK 0x736
#define NA_SE_EN_SALEM_WITCH_HURT 0x737
#define NA_SE_EN_SALEM_WITCH_DEATH 0x738
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
#define NA_SE_CS_BURNING_PHOTOGRAPH 0x8BE
// plays every 10 frames while using bible subweapon
#define BIBLE_SUBWPN_SWOOSH 0x8C3

// STAGE DRE
#define NA_SE_SU_SHOOT_PINKBALLS 0x62C
#define SE_SUC_REVEAL 0x637
#define NA_SE_SU_LANDING 0x646
#define SE_DRE_FADE_TO_WHITE 0x65A
#define NA_VO_SU_CRYSTAL_2 0x6AF
#define NA_SE_SU_FLAPPING_WINGS 0x6C6
#define NA_SE_SU_PETAL_ATTACK 0x6B0
#define NA_SE_SU_CREATE_CLONES 0x6D5
#define NA_SE_SU_CHARGE_PINKBALLS 0x6E2
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
#define SE_DEATH_AMBIENCE 0x631
#define SE_DEATH_TAKES_ITEMS 0x7A0
#define NA_VO_DEATH_LAUGH 0x7A1
#define SE_ITEM_YOINK 0x7A2
#define SE_TREE_BRANCH_SNAP 0x7A4
#define SE_CASTLE_GATE_RISE 0x7A5

// NZ1
#define SE_HARPY_WING_FLAP 0x601

// SHARED SOUNDS
// These are sounds that are shared across multiple BIN files
#define SE_WEAPON_STAB 0x62E
#define SE_DOOR_OPEN 0x642
#define SE_DOOR_CLOSE 0x64F
#define SE_WEAPON_WHACK 0x678
#define SE_BOSS_DEFEATED 0x7D2

// UI SOUNDS
#define SE_UI_CONFIRM 0x633
#define SE_UI_START 0x63D
#define SE_UI_SELECT 0x67B
#define SE_UI_MAIN_MENU_SELECT 0x67D
#define SE_UI_ERROR 0x686
#define SE_UI_DEBUG_SELECT 0x688
#define SE_UI_OVERWRITE_SELECT 0x6A4
#define SE_UI_OVERWRITE_MSG 0x6AD

// DRA
#define SE_SAVE_HEARTBEAT 0x64D
#define SE_HEALTH_REGAINED 0x68E

// WEAPON SOUNDS
#define SE_WPN_POWER_OF_SIRE 0x66A
#define SE_WPN_ALUCARD_SWORD_SWING 0x6A8
#define SE_WPN_PENTAGRAM 0x6E4

// UNUSED SOUNDS
#define SE_UNK_ST0_618 0x618
#define SE_UNK_MAD_630 0x630
#define SE_UNK_TE1_651 0x651
#define SE_UNK_TE3_667 0x667
#define SE_UNK_TE1_66F 0x66F
#define SE_UNK_TE3_679 0x679
#define SE_UNK_TE1_692 0x692
#define SE_UNK_TE1_6B3 0x6B3
#define SE_UNK_TE2_6B4 0x6B4
#define SE_UNK_TE2_6B6 0x6B6
#define SE_UNK_TE3_6B8 0x6B8
#define NA_VO_MAR_AIM_HEAD 0x87F

#endif
