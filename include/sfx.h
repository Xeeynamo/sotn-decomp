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
 * DR = Dracula
 * DE = Death
 * SH = Shaft
 * ML = Master Librarian
 * FE = Ferryman
 * AL = Alucard
 * MA = Maria
 * RI = Richter
 * WO = Form of Wolf
 * BT = Form of Bat
 * MU = Music
 */

// playSfx flags
typedef enum { STEREO, MONO } SoundMode;

#define SET_SOUNDMODE_MONO 5
#define SET_SOUNDMODE_STEREO 6

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

// This sound plays when MAX UP spawns and during Dracula transformation
#define NA_SE_UNK_62F 0x62F
#define NA_SE_EV_HEAVY_BLOCK_DRAG 0x609
#define NA_SE_AL_BACKSLIDE 0x617
#define NA_SE_BREAK_CANDLE 0x634
#define NA_SE_PL_WARP 0x636
#define NA_SE_EN_OPEN_DOOR 0x642
#define NA_SE_EN_COG_CLICK 0x642
#define NA_SE_EN_ROCK_BREAK 0x644
#define NA_SE_SECRET_STAIRS NA_SE_EN_ROCK_BREAK
#define NA_SE_EV_SWITCH_CLICK 0x676
#define NA_SE_PL_COLLECT_HEART 0x67A
#define NA_SE_SY_MOVE_MENU_CURSOR 0x67B
#define NA_SE_PL_IT_PICKUP 0x67C
#define NA_SE_PL_MP_GAUGE 0x67D
#define NA_SE_PL_BT_FIREBALL 0x680
#define NA_SE_PL_MAX_HP_MP_INCREASED 0x687
#define NA_SE_BREAK_GLASS 0x68B
#define NA_SE_EV_CLOCK_TICK 0x6A1
#define NA_SE_PL_COLLECT_GOLD 0x6A9
#define NA_SE_PL_RIC_UNK_6E2 0x6E2
#define NA_SE_VO_AL_PUNCH 0x6F1
#define NA_SE_VO_AL_WHAT 0x6F2
#define NA_SE_VO_AL_DARK_METAMORPHOSIS 0x6F3
#define NA_SE_VO_AL_SOUL_STEAL 0x6F4
#define NA_SE_VO_AL_DYING 0x6F6
#define NA_SE_VO_WO_BARK 0x706
#define NA_SE_PL_TELEPORT 0x8BA
#define NA_SE_CS_BURNING_PHOTOGRAPH 0x8BE
