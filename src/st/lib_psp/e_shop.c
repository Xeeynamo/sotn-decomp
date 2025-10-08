// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../lib/lib.h"

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
extern u8* OVL_EXPORT(cutscene_data_offset_four);

extern s32 g_SkipCutscene;
extern u32 g_CutsceneFlags;
extern s32 g_IsCutsceneDone;

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
    0x0A9, 0x046, 0x180, 0x06E, 0x040, 0x0AF, 0x04B, 0x01B, 0x051, 0x069, 0x01D,
    0x0F6, 0x0B2, 0x00D, 0x09D, 0x0C1, 0x00B, 0x0FE, 0x09C, 0x0F3, 0x031, 0x010,
    0x12F, 0x028, 0x066, 0x07C, 0x061, 0x130, 0x055, 0x006, 0x0E9, 0x06C, 0x05D,
    0x126, 0x053, 0x0FD, 0x043, 0x080, 0x0F7, 0x016, 0x0B7, 0x009, 0x058, 0x06A,
    0x022, 0x0B4, 0x092, 0x06B, 0x063, 0x105, 0x0FB, 0x044, 0x030, 0x073, 0x072,
    0x081, 0x09E, 0x11F, 0x076, 0x0E4, 0x014, 0x0E3, 0x0D6, 0x088, 0x029, 0x042,
    0x0D3, 0x12C, 0x07A, 0x03D, 0x0CE, 0x06F, 0x0EF, 0x0CB, 0x0E1, 0x085, 0x02D,
    0x0DD, 0x083, 0x115, 0x10F, 0x017, 0x0BC, 0x0BA, 0x0BE, 0x041, 0x04D, 0x118,
    0x047, 0x16B, 0x0A1, 0x032, 0x15E, 0x071, 0x156, 0x142, 0x106, 0x143, 0x108,
    0x127, 0x078, 0x11D, 0x0A5, 0x00E, 0x074, 0x0B6, 0x131, 0x185, 0x08D, 0x07E,
    0x025, 0x02B, 0x090, 0x182, 0x111, 0x0C3, 0x094, 0x08A, 0x0A7, 0x0D8, 0x097,
    0x026, 0x01F, 0x099, 0x04F, 0x0EC, 0x174, 0x172, 0x188, 0x10B, 0x16E, 0x11C,
    0x14E, 0x148, 0x151, 0x144, 0x0E5, 0x0E0, 0x0D9, 0x190, 0x133, 0x068, 0x0C6,
    0x18C, 0x164, 0x15F, 0x17B, 0xFFFF};

static char* D_psp_09299A18[] = {
    "Destroyed by Richter ",
    "Revives due to blood soaked",
    "Indestructible spinning skull．",
    "Fresh corpses．",
    "Vampire bats．",
    "Wolves which guard castle ",
    "Magically animated skeleton．",
    "Legendary ”creature”．",
    "４−legged skeleton．",
    "Ferocious skeleton ",
    "Fireball−spitting Merman．",
    "Low level axe knight．",
    "Bone−hurling skeleton．",
    "Eastern Church soldiers ",
    "Plant with razor−sharp ",
    "Possessed Ouija table．",
    "Boomerang wielding skeleton．",
    "Fire−breathing flying demon．",
    "Low level flaming ghosts．",
    "Demon with enchanted spear．",
    "Demonic puppet from Hell．",
    "Nauseating two−headed ",
    "From Medusa’s hair．",
    "Strange human−like creature．",
    "Skeletons equipped with",
    "Novice of twin−bladed ",
    "Heavily armored knight with ",
    "From Medusa’s hair．",
    "Mutated plant．",
    "Well armored axe knight．",
    "Fire and ice demon．",
    "Skeleton archer equipped ",
    "Armored warrior with ",
    "Snake living off Scylla．",
    "Animated ape skeleton．",
    "Shape−shifting demon．",
    "Executed soldier’s head．",
    "Slow−flying skeleton warrior．",
    "Book of beginner’s spells．",
    "Local barnyard owl Mutated ",
    "Pillar built from bleached",
    "Knight armed with ",
    "Physical manifestations of ",
    "Toad magically enlarged by ",
    "Heavily armored undead ",
    "Armored guard．",
    "Headless skeleton．",
    "Cave−dwelling frog．",
    "Ice−wielding female spirit．",
    "Giant skull spirit．",
    "Book of ancient weapons．",
    "Skeleton equipped with ",
    "Flea Man riding on specially ",
    "Flesh−eating raven．",
    "Spirit of long−dead blue ",
    "Evil demon−sword． Causes ",
    "Plant with razor−sharp ",
    "Mythological sea monster．",
    "Naginata−wielding skeleton．",
    "Sword Lord wields sword ",
    "Heavily armored knight． ",
    "Invisible huntress spirit．",
    "Animated mud golem．",
    "Evil demon−sword． Causes ",
    "Flea Man armed with axe and",
    "Monster made from gel．",
    "Giant skeleton．",
    "Part horse， lion and eagle．",
    "Master of twin−bladed ",
    "Were panther skeleton．",
    "Half−man， half−wolf．",
    "Grave Keeper．",
    "Creature with head of ",
    "Half−man， half−bull．",
    "Pyromaniacal gremlin．",
    "Bloodthirsty undead knight ",
    "Portable skull shrine carried ",
    "Ghost witches from Salem．",
    "Searches among graves and ",
    "Fish head guardian．",
    "Mysterious cloaked ",
    "Short magic−wielding demon．",
    "Giant brother．",
    "Giant brother．",
    "Eldest Giant brother．",
    "Monster created from slimy ",
    "Discus−wielding armored ",
    "Demon Lord of Ravens．",
    "Thunder−wielding demon．",
    "Watchdog of Hell．",
    "Watered with human blood．",
    "Magic−wielding vampire．",
    "Master Fish−head．",
    "Gravestones possessed by ",
    "Female demon．",
    "Impaled man looking for ",
    "The cowardly lion．",
    "Monster nicknamed ”schmoo”．",
    "Heartless tin man．",
    "Nightmarish creature．",
    "Skeleton eternally chasing ",
    "Holds countless poison seeds．",
    "Bomb−tossing armored ",
    "Zombies which attack even ",
    "Expert at throwing weapons．",
    "Mutated insect．",
    "Fiendishly accurate archer．",
    "Shape−shifting lycanthrope．",
    "Wyrm controlled by Flea Man．",
    "Wields fearsome beam ",
    "Liquid creature．",
    "Animated skeleton of huge ",
    "White dragon ridden by Flea ",
    "Bull−headed monster．",
    "Giant vampire bat．",
    "Angel archer．",
    "Fireball−spitting wolf．",
    "Evil demon−sword． Causes ",
    "Rock−tossing armored ",
    "Skeleton with leaping attack．",
    "Skeleton mounted on Warg．",
    "Evil mutated octopus．",
    "Armor plated war−beast．",
    "Pre−intelligent bloodsucker ",
    "Flame demon．",
    "Gruesome Demon from Hell．",
    "Shape−shifting demon．",
    "Made from the body parts ",
    "Advanced Venus Weed．",
    "Ancient Egyptian mummy．",
    "Snake−headed demoness ",
    "Mischievous little demon．",
    "Zombie impersonating Grant．",
    "Zombie impersonating Trevor．",
    "Zombie impersonating Sypha．",
    "Beelzebub, Lord of Flies．",
    "Young female witch．",
    "Executioner of Hell．",
    "Transvestite ice spirit.",
    "Vampire hunter. Uses 4 beasts",
    "Master Vampire hunter．",
    "Rare bird．",
    "Magical being with plan to ",
    "High level Armor Lord．",
    "Dracula’s close friend．",
    "Dark Priest of Dracula．",
    "Lord of Wallachia．"};
static char* D_psp_0929A320[] = {
    "in １７９２．（５ years ago）",
    "bones．",
    "",
    "Magically animated．",
    "Feared as servants of evil．",
    "entrance．",
    "",
    "Attacks all invaders．",
    "Drips poison．",
    "swordsman．",
    "Largest of merman kind．",
    "",
    "",
    "dispatched ３００ years ago．",
    "leaves．",
    "",
    "",
    "",
    "",
    "",
    "",
    "beast． Which is the head？",
    "",
    "Jumps like a flea．",
    "rifles．",
    "combat．",
    "iron ball．",
    "Can petrify．",
    "Seeds petrify．",
    "",
    "Seems reluctant to fight．",
    "with bow．",
    "naginata．",
    "",
    "Hurls wooden barrels．",
    "",
    "Hunting for vengeance．",
    "",
    "",
    "by castle’s influence．",
    "skull of dragon．",
    "Greatsword．",
    "bodiless tormented souls．",
    "demonic baptism．",
    "warrior．",
    "Strong in perilous areas． ",
    "Wields a rapier．",
    "",
    "",
    "",
    "",
    "spiked iron flail．",
    "trained war−goose．",
    "",
    "raven．",
    "poltergeist phenomena．",
    "leaves．",
    "",
    "",
    "even when banished．",
    "Attacks with trained owl．",
    "",
    "",
    "poltergeist phenomena．",
    "shield．",
    "",
    "",
    "",
    "combat．",
    "",
    "",
    "Master of unarmed combat．",
    "woman and body of bird．",
    "",
    "",
    "who eternally seeks combat．",
    "by skeleton priests．",
    "",
    "knows much wise lore．",
    "",
    "swordsman．",
    "Summons demonic allies．",
    "Wields a gurkha knife．",
    "Uses huge steel hammer．",
    "Wields two huge daggers．",
    "gel substance．",
    "knight．",
    "",
    "Called ”Musician from Hell”．",
    "",
    "",
    "Rules upper part of castle．",
    "",
    "evil spirits of dead．",
    "Invades men’s dreams．",
    "brains．",
    "",
    "",
    "",
    "Composed of many．",
    "his own skull．",
    "",
    "knight．",
    "when cut in half．",
    "",
    "Visible only to magicians．",
    "",
    "",
    "",
    "weapon．",
    "Takes black panther shape．",
    "dragon．",
    "Man．",
    "",
    "",
    "Slew Amalaric of the Goths．",
    "",
    "poltergeist phenomena．",
    "knight．",
    "",
    "",
    "",
    "",
    "with long tongue for sucking．",
    "",
    "",
    "",
    "of powerful warriors．",
    "Fed with demon blood．",
    "",
    "with gaze of stone．",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "Servant of Galamoth．",
    "of legend. Seeks Richter.",
    "",
    "Runs when it sees people．",
    "rule the netherworld．",
    "",
    "",
    "",
    "Father of Alucard．"};
static char* D_psp_0929B4A0[] = {
    "Destruido por Richter ",
    "Resucita gracias a huesos",
    "Calavera giratoria",
    _SE("Cadáveres frescos."),
    _SE("Murciélagos vampiros."),
    "Lobos que protegen la",
    "Esqueleto animado por magia.",
    "\"Criatura\" legendaria.",
    "Esqueleto de 4 patas.",
    "Feroz esqueleto",
    _SE("Tritón que escupe bolas de"),
    "Caballero de hacha de",
    "Esqueleto que lanza huesos.",
    "Soldados de Iglesia Oriental",
    "Planta con hojas",
    _SE("Mesa de ouija poseída."),
    _SE("Esqueleto con bumerán."),
    "Demonio volador que escupe",
    "Fantasmas llameantes de",
    "Demonio con lanza encantada.",
    _SE("Títere demoníaco del Infierno."),
    "Bestia nauseabunda de dos",
    "De pelo de Medusa.",
    _SE("Extraña criatura que parece"),
    "Esqueletos equipados",
    "Novato del combate con",
    _SE("Caballero con sólida armadura"),
    "De pelo de medusa．",
    "Planta mutada.",
    "Caballero de hacha con",
    "Demonio de fuego y hielo.",
    "Arquero esqueleto equipado",
    "Guerrero con armadura ",
    "Serpiente que vive a costa",
    "Esqueleto de simio animado.",
    "Demonio que cambia de forma.",
    "Cabeza de soldado ejecutado.",
    "Esqueleto guerrero que",
    _SE("Libro de hechizos básicos."),
    _SE("Búho de granja local mutado"),
    "Columna hecha con calaveras",
    "Caballero armado con",
    _SE("Manifestaciones físicas de"),
    _SE("Sapo agrandado mágicamente"),
    "Guerrero muerto viviente",
    "Guardia con armadura.",
    "Esqueleto sin cabeza.",
    "Rana que habita en cuevas.",
    _SE("Espíritu femenino con hielo."),
    _SE("Espíritu de calavera gigante."),
    "Libro de armas antiguas.",
    "Esqueleto equipado con",
    "Hombre pulga a lomos de un",
    "Cuervo que come carne.",
    _SE("Espíritu de cuervo azul"),
    "Espada de demonio malvado.",
    "Planta con hojas",
    _SE("Monstruo mitológico marino."),
    "Esqueleto con naginata.",
    _SE("El Señor de la espada porta"),
    _SE("Caballero con sólida armadura."),
    _SE("Espíritu de cazadora"),
    _SE("Gólem de barro animado."),
    "Espada de demonio malvado.",
    "Hombre pulga armado con",
    "Monstruo gelatinoso.",
    "Esqueleto gigante.",
    _SE("Mezcla de caballo, león y"),
    "Maestro del combate con",
    "Hombre esqueleto pantera.",
    "Mitad hombre, mitad lobo.",
    "Sepulturero. Maestro del",
    "Criatura con cabeza de mujer",
    "Mitad hombre, mitad toro.",
    _SE("Gremlin piromaníaco."),
    "Sanguinario caballero muerto",
    "Relicario de calavera llevado",
    _SE("Brujas fantasma de Sálem."),
    "Busca entre las tumbas y",
    _SE("Guardián con cabeza de pez."),
    _SE("Espadachín misterioso"),
    _SE("Demonio pequeño con magia."),
    "Hermano gigante.",
    "Hermano gigante.",
    "Hermano gigante mayor.",
    "Monstruo creado con una",
    "Caballero con armadura",
    _SE("Señor de los cuervos"),
    "Demonio que lleva un trueno.",
    _SE("Perro guardián del Infierno."),
    "Regada con sangre humana.",
    "Vampiro con magia. Domina",
    "Cabeza de pez de maestro.",
    _SE("Lápidas poseídas por espíritus"),
    "Mujer demonio. Invade",
    "Hombre empalado buscando",
    _SE("El león cobarde."),
    "Monstruo llamado  schmoo ．",
    "Hombre de hojalata",
    _SE("Criatura terrorífica."),
    "Esqueleto que busca",
    "Contiene infinitas semillas",
    "Caballero con armadura que",
    "Zombis que atacan incluso",
    "Experto en lanzar armas.",
    "Insecto mutado.",
    _SE("Arquero diabólicamente"),
    _SE("Licántropo que cambia"),
    "Wyrm controlado por Hombre",
    "Lleva una temible arma",
    _SE("Criatura líquida. Adopta"),
    "Esqueleto animado con",
    _SE("Dragón blanco montado"),
    "Monstruo con cabeza de toro.",
    _SE("Murciélago vampiro gigante."),
    _SE("Arquero ángel."),
    "Lobo que escupe",
    "Espada de demonio malvado.",
    "Caballero con armadura que",
    "Esqueleto con ataque de salto.",
    "Esqueleto montado en Warg.",
    "Pulpo mutado malvado.",
    "Bestia de guerra con peto.",
    "Chupasangre pre-inteligente",
    "Demonio de llamas.",
    "Demonio asqueroso del",
    "Demonio que cambia de forma.",
    "Hecha con partes del cuerpo",
    "Hierba de Venus avanzada.",
    _SE("Mamá en el antiguo Egipto."),
    "Mujer demonio con cabeza de",
    _SE("Pequeño demonio malicioso."),
    "Zombi que se hace pasar",
    "Zombi que se hace pasar",
    "Zombi que se hace pasar",
    _SE("Beelzebub, el Señor de las"),
    "Bruja joven.",
    "Ejecutor del Infierno.",
    _SE("Espíritu de hielo andrógino."),
    "Cazavampiros. Usa 4 bestias",
    "Maestro cazavampiros.",
    _SE("Pájaro raro."),
    _SE("Ser mágico con planes de"),
    "Caballero de armadura de",
    _SE("Amiga íntima de Dracula."),
    "Sacerdote oscuro de Dracula.",
    _SE("Señor de Wallachia.")};
static char* D_psp_0929BFF0[] = {
    _SE("en １７９２ （hace ５ años）."),
    "empapados de sangre.",
    "indestructible.",
    "Animados por magia.",
    "Temidos como siervos del mal.",
    "entrada al castillo.",
    "",
    "Ataca a todos los invasores.",
    "Le caen gotas de veneno.",
    _SE("espadachín."),
    _SE("fuego. El más grande."),
    "nivel bajo.",
    "",
    _SE("enviados hace ３００ años．"),
    "afiladas.",
    "",
    "",
    "fuego.",
    "nivel bajo.",
    "",
    "",
    _SE("cabezas. ¿Cuál es la cabeza?"),
    "",
    "humana. Salta como una pulga.",
    "con rifles.",
    "dos espadas.",
    "y bola de hierro.",
    "Puede petrificar.",
    "Las semillas petrifican.",
    "una buena armadura.",
    "Parece reacio a luchar.",
    "con arco.",
    "y naginata.",
    "de Scylla.",
    "Lanza barriles de madera.",
    "",
    "Busca venganza.",
    "vuela despacio.",
    "",
    "por los efectos del castillo.",
    _SE("de dragón blanqueadas."),
    "una gran espada.",
    "almas sin cuerpo atormentadas.",
    _SE("por un bautismo demoníaco."),
    _SE("con sólida armadura."),
    _SE("Fuerte en áreas peligrosas."),
    "Lleva una ropera.",
    "",
    "",
    "",
    "",
    "mayal de hierro con pinchos.",
    "ganso de guerra entrenado.",
    "",
    "que lleva tiempo muerto.",
    _SE("Causa fenómenos poltergeist."),
    "afiladas.",
    "",
    "",
    "una espada hasta desterrado.",
    _SE("Ataca con búho entrenado."),
    "invisible.",
    "",
    _SE("Causa fenómenos poltergeist."),
    "hacha y escudo.",
    "",
    "",
    _SE("águila."),
    "dos espadas.",
    "",
    "",
    "combate sin armas.",
    _SE("y cuerpo de pájaro."),
    "",
    "",
    _SE("viviente que ansía luchar."),
    "por los sacerdotes esqueletos.",
    "",
    "conoce muchas tradiciones.",
    "",
    "con capa.",
    _SE("Invoca a aliados demoníacos."),
    "Lleva un cuchillo gurkha.",
    "Usa un gran martillo de acero.",
    "Lleva dos dagas enormes.",
    "viscosa sustancia gelatinosa.",
    "que lleva un disco.",
    _SE("demoníaco."),
    _SE("Llamado  Músico del Infierno ．"),
    "",
    "",
    "la parte alta del castillo.",
    "",
    "malvados de los muertos.",
    _SE("los sueños de los hombres."),
    "sesos.",
    "",
    "",
    _SE("sin corazón."),
    "Compuesta de muchos.",
    "eternamente su calavera.",
    "venenosas.",
    "lanza bombas.",
    "cortados por la mitad.",
    "",
    "Solo lo ven los magos.",
    "preciso.",
    "de forma.",
    "Pulga.",
    "de rayo.",
    "la forma de pantera negra.",
    _SE("dragón enorme."),
    "por un Hombre pulga.",
    "",
    "",
    _SE("Mató al godo Amalarico."),
    "bolas de fuego.",
    _SE("Causa fenómenos poltergeist."),
    "lanza rocas.",
    "",
    "",
    "",
    "",
    "con lengua larga para chupar.",
    "",
    "Infierno.",
    "",
    "de guerreros poderosos.",
    "Alimentada con sangre de demonio.",
    "",
    "serpiente y mirada de piedra.",
    "",
    "por Grant.",
    "por Trevor.",
    "por Sypha.",
    "moscas.",
    "",
    "",
    "Siervo de Galamoth.",
    "de leyenda. Busca a Richter.",
    "",
    "Corre cuando ve a gente.",
    "dominar el inframundo.",
    "alto nivel.",
    "",
    "",
    "Padre de Alucard."};
static char* D_psp_0929D1B0[] = {
    "Distrutto da Richter",
    "Rivive bagnando le ossa",
    "Durissimo teschio rotante.",
    "Corpi freschi.",
    "Pipistrelli vampiri.",
    "Lupi a guardia dell'entrata",
    "Scheletro animato magicamente.",
    "Creatura leggendaria.",
    "Scheletro a quattro zampe.",
    "Feroce scheletro",
    "Tritone sputa-fuoco.",
    "Asciere di basso livello.",
    "Scheletro lancia-ossa.",
    "Soldati della Chiesa Orientale",
    "Pianta con foglie affilate",
    "Tavola Ouija posseduta.",
    "Scheletro armato di boomerang.",
    "Demone volante sputa-fuoco.",
    "Spettri di fuoco minori. ",
    "Demone con lancia incantata.",
    "Demoniaco burattino infernale.",
    "Nauseabonda bestia a due",
    "Dai capelli di Medusa.",
    "Strana creatura antropomorfa.",
    "Scheletri armati di",
    "Un pivello del combattimento",
    "Cavaliere con pesante armatura",
    "Dai capelli di Medusa.",
    "Pianta mutata.",
    "Asciere ben armato.",
    "Demone di fuoco e ghiaccio.",
    "Scheletro arciere armato",
    "Guerriero armato",
    "Serpente parassita di Scilla.",
    "Scheletro di scimmia animato.",
    "Demone mutaforma.",
    "Testa di soldato giustiziato.",
    "Scheletro guerriero volante.",
    "Libro di incantesimi di base.",
    "Gufo del cortile locale",
    "Pilastro ricavato da un",
    "Guerriero armato con",
    "Manifestazioni fisiche di",
    "Rospo magicamente ingrandito",
    "Guerriero non morto",
    "Guardia con armatura.",
    "Scheletro senza testa armato",
    "Rana che vive nelle grotte.",
    "Spirito femminile del gelo.",
    "Gigantesco spirito teschio.",
    "Libro delle armi antiche.",
    "Scheletro armato di mazza",
    "Uomo-Pulce che cavalca",
    "Corvo carnivoro.",
    "Spirito di un corvo blu",
    "Maligna spada demoniaca.",
    "Pianta con foglie affilate",
    "Mitologico mostro marino.",
    "Scheletro armato di naginata.",
    "Spadaccino che rimane",
    "Cavaliere con pesante armatura.",
    "Invisib. spirito di cacciatr.",
    "Golem di fango animato.",
    "Maligna spada demoniaca.",
    "Uomo-Pulce armato con",
    "Mostro fatto di gelatina.",
    "Scheletro gigante.",
    "Cavallo, leone e aquila.",
    "Maestro del combattimento",
    "Scheletro di pantera mannara.",
    _SE("Metà uomo e metà lupo."),
    "Camposantiere. Maestro del",
    "Creatura con testa di",
    _SE("Metà uomo e metà toro."),
    "Gremlin piromane.",
    "Guerriero non morto assetato",
    "Sacrario di teschio portato",
    "Streghe fantasma di Salem．",
    _SE("Cerca tra le tombe ed è"),
    "Guardiano con testa di pesce.",
    "Misterioso spadaccino",
    "Piccolo demone magico.",
    "Fratello Gigante.",
    "Fratello Gigante.",
    "Primo dei fratelli Giganti.",
    "Mostro fatto di viscida ",
    "Cavaliere in armatura ",
    "Demoniaco signore dei corvi.",
    "Demone armato di lampo.",
    "Cane da guardia degli Inferi.",
    "Innaffiata con sangue umano.",
    "Vampiro magico. Governa",
    "Un pesce grosso.",
    "Lapidi possedute dagli",
    "Demone femmina.",
    "Uomo impalato a caccia",
    "Il leone codardo.",
    "Mostro chiamato schmoo ．",
    "Uomo di latta senza cuore.",
    "Creatura da incubo.",
    "Scheletro che rincorre sempre",
    "Contiene infiniti semi velenosi.",
    "Cavaliere in armatura ",
    "Zombie che attacca",
    "Esperto di armi da lancio.",
    "Insetto mutato.",
    "Arciere micidialmente preciso.",
    "Licantropo mutaforma.",
    "Wyrm controllato dall'Uomo-Pulce.",
    "ｹ armato di una temibile",
    "Creatura liquida.",
    "Scheletro animato di un",
    "Drago bianco cavalcato ",
    "Mostro con testa di toro.",
    "Pipistrello vampiro gigante.",
    "Angelo arciere.",
    "Lupo che sputa palle di fuoco.",
    "Maligna spada demoniaca.",
    "Cavaliere in armatura ",
    "Scheletro con attacco con salto.",
    "Scheletro che cavalca un Warg.",
    "Malvagio polpo mutato.",
    "Bestia da guerra corazzata.",
    "Tutto istinto, poco cervello.",
    "Demone del fuoco.",
    "Orribile demone infernale.",
    "Demone mutaforma.",
    "Fatto di parti del corpo",
    "Erba Venere avanzata.",
    "Mummia dell'antico Egitto.",
    "Demone con testa di serpente.",
    "Piccolo demone malizioso.",
    "Zombie che impersona Grant．",
    "Zombie che impersona Trevor．",
    "Zombie che impersona Sypha．",
    "Belzebｦ, Signore delle Mosche．",
    "Giovane strega.",
    "Boia infernale.",
    "Spirito di ghiaccio androgino.",
    "Cacciatrice di vampiri. Usa 4",
    "Esperto cacciatore di vampiri.",
    "Uccello raro.",
    "Creatura magica che intende",
    "ArmaDuro di alto livello.",
    "Intimo amico di Dracula.",
    "Il prete oscuro di Dracula.",
    "Signore della Valacchia．"};
static char* D_psp_0929DBD0[] = {
    "nel １７９２．（Cinque anni fa）",
    "nel sangue.",
    "",
    "Animati magicamente.",
    "Temuti servi del male．",
    "al castello.",
    "",
    "Attacca tutti gli invasori.",
    "Gronda veleno.",
    "spadaccino.",
    "Il piｦ grande della sua razza.",
    "",
    "",
    "inviati trecento anni fa.",
    "come rasoi.",
    "",
    "",
    "",
    "",
    "",
    "",
    "teste. Quale delle due decide?",
    "",
    "Salta come una pulce.",
    "moschetti.",
    "a doppia lama.",
    "armato di una palla di ferro.",
    "Puﾙ pietrificare.",
    "I suoi semi pietrificano.",
    "",
    "Pare riluttante a combattere.",
    "di arco.",
    "con un naginata．",
    "",
    "Lancia barili di legno.",
    "",
    "ｹ assetato di vendetta.",
    "",
    "",
    "mutato dal castello.",
    "imbiancato teschio di drago.",
    "la Grande spada.",
    "spiriti tormentati.",
    "da un battesimo demoniaco.",
    "con pesante armatura.",
    "Forte nelle aree pericolose.",
    "con una micidiale striscia.",
    "",
    "",
    "",
    "",
    "di ferro chiodata.",
    "un'oca addestrata alla guerra.",
    "",
    "morto da tempo.",
    "Scatena fenomeni paranormali．",
    "come rasoi.",
    "",
    "",
    _SE("armato anche quando è bandito."),
    "Attacca con gufo addestrato.",
    "",
    "",
    "Scatena fenomeni paranormali．",
    "ascia e scudo.",
    "",
    "",
    "",
    "a due lame.",
    "",
    "",
    "combattimento a mani nude.",
    "donna e corpo di uccello.",
    "",
    "",
    "di sangue che ama la lotta.",
    "dai preti scheletri.",
    "",
    "depositario di antico sapere.",
    "",
    "ammantato.",
    "Evoca alleati demoniaci.",
    "Armato con un coltello gurkha．",
    "Usa un enorme martello.",
    "Armato di due grosse spade．",
    "sostanza gelatinosa.",
    "armato di disco.",
    "",
    "Detto  Musicista infernale ．",
    "",
    "",
    "la parte alta del castello.",
    "",
    "spiriti maligni dei morti.",
    "Invade i sogni degli uomini.",
    "di cervelli.",
    "",
    "",
    "",
    "Un incrocio di tante creature.",
    "il suo stesso teschio.",
    "",
    "che tira bombe.",
    _SE("anche se tagliato a metà."),
    "",
    "ｹ visibile solo ai maghi.",
    "",
    "",
    "",
    "arma a raggi.",
    "Si trasforma in pantera nera.",
    "grosso drago.",
    "dall'Uomo-Pulce.",
    "",
    "",
    "Ha ucciso Amalaric dei Goth．",
    "",
    "Scatena fenomeni paranormali．",
    "che scaglia pietre.",
    "",
    "",
    "",
    "",
    "Lunga lingua succhiasangue.",
    "",
    "",
    "",
    "di potenti guerrieri.",
    "Si nutre di sangue di demoni.",
    "",
    "Il suo sguardo pietrifica.",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "Servo di Galamoth．",
    "bestie mitiche. Cerca Richter.",
    "",
    "Scappa quando vede qualcuno.",
    "dominare gli inferi.",
    "",
    "",
    "",
    "Padre di Alucard．"};
static char* D_psp_0929ED18[] = {
    _SE("Eliminé par Richter "),
    _SE("Revit grâce à ses os"),
    _SE("Crâne indestructible tournant"),
    "Cadavre frais.",
    "Chauve-souris vampires.",
    _SE("Loups qui gardent l’entrée"),
    _SE("Squelette contrôlé par"),
    _SE("\"Créature\" légendaire."),
    _SE("Squelette à quatre jambes."),
    _SE("Féroce spadassin squelette."),
    "Triton cracheur de boules de",
    "Chevalier de bas niveau",
    _SE("Squelette lançant des os."),
    "Soldats de l’Eglise d’Orient",
    _SE("Plante dotée de feuilles"),
    _SE("Table ouija possédée."),
    "Squelette maniant",
    _SE("Démon volant cracheur de feu."),
    _SE("Fantômes enflammés"),
    _SE("Démon muni d’une lance"),
    _SE("Poupée démoniaque venue"),
    _SE("Bête repoussante à deux têtes."),
    _SE("Des cheveux de la Méduse."),
    _SE("Créature étrange à forme"),
    _SE("Squelettes équipés"),
    "Novice dans le combat",
    "Chevalier avec une lourde",
    _SE("Des cheveux de la Méduse."),
    "Plante mutante.",
    "Chevalier avec une lourde",
    _SE("Démon du feu et de la glace."),
    _SE("Archer squelette équipé"),
    "Guerrier avec une armure",
    _SE("Serpent rattaché à Scylla."),
    _SE("Singe squelette animé."),
    _SE("Démon capable de changer"),
    _SE("Tête de soldat exécuté."),
    "Guerrier squelette volant",
    _SE("Livre de sortilèges"),
    "Hibou de la basse-cour locale",
    _SE("Pilier construit à partir d’un"),
    _SE("Chevalier armé d’une"),
    _SE("Manifestation phys. d’une âme"),
    _SE("Crapaud devenu géant suite"),
    _SE("Guerrier mort-vivant équipé"),
    "Garde avec une armure. Fort",
    _SE("Squelette sans tête."),
    "Grenouille vivant dans",
    _SE("Esprit féminin maniant"),
    _SE("Esprit d’un crâne géant."),
    "Livre sur les armes anciennes.",
    _SE("Squelette équipé d’un fléau"),
    "Homme-puce chevauchant une",
    _SE("Corbeau dévorant la chair."),
    "Esprit d’un Corbeau bleu",
    _SE("Epée démon maléfique."),
    _SE("Plante dotée de feuilles"),
    "Monstre des mers",
    "Squelette maniant",
    _SE("Seigneur maniant une épée"),
    _SE("Chevalier lourdement protégé."),
    "Esprit de chasseuse invisible.",
    _SE("Golem de boue animé."),
    _SE("Epée démon maléfique."),
    _SE("Homme-puce armé d’une hache"),
    "Monstre gluant.",
    _SE("Squelette géant."),
    "Mi-cheval， mi-lion",
    _SE("Maître du combat à"),
    _SE("Squelette de panthère-garou."),
    "Mi-homme, mi-loup.",
    "Gardien des tombes.",
    _SE("Créature avec une tête de"),
    "Mi-homme, mi-taureau.",
    "Gremlin pyromane.",
    _SE("Chev. zombie assoiffé de sang"),
    _SE("Relique d’un crâne transportée"),
    _SE("Sorcières fantômes de Salem."),
    "Fouille parmi les tombes et a",
    _SE("Gardien formé de têtes"),
    _SE("Mystérieux spadassin"),
    _SE("Petit démon maniant la magie."),
    _SE("Frère géant."),
    _SE("Frère géant. Utilise un"),
    _SE("L’aîné des Frères géants."),
    _SE("Monstre formé d’une substance"),
    "Chevalier avec une armure.",
    _SE("Seigneur maléfique"),
    _SE("Démon contrôlant la foudre."),
    "Chien de garde des Enfers",
    _SE("Arrosée avec du sang humain."),
    _SE("Vampire maîtrisant la magie."),
    _SE("Maître Tête de poisson."),
    _SE("Pierres tombales possédées pa"),
    _SE("Démon féminin. S’immisce"),
    _SE("Homme empalé à la recherche"),
    "Lion peureux.",
    _SE("Monstre surnommé \"Schmoo\"."),
    _SE("Homme de fer sans cœur."),
    _SE("Créature cauchemardesque."),
    "Squelette poursuivant",
    "Renferme un nombre infini",
    "Chevalier avec une armure",
    "Zombies continuant d’attaquer,",
    "Expert dans le lancer d’armes.",
    "Insecte mutant. Seuls les",
    _SE("Archer diaboliquement précis."),
    "Lycanthrope capable de",
    _SE("Wyrm contrôlé par"),
    "Manie une arme tirant",
    _SE("Créature liquide. Prend la"),
    _SE("Squelette animé d’un"),
    _SE("Dragon blanc chevauché par"),
    _SE("Monstre à tête de taureau."),
    "Enorme chauve-souris",
    "Ange archer.",
    "Loup crachant des boules",
    _SE("Epée démon maléfique."),
    "Chevalier avec une armure.",
    "Squelette effectuant",
    "Squelette chevauchant",
    _SE("Pieuvre mutante et maléfique."),
    _SE("Bête de combat protégée"),
    _SE("Homo Sapiens suçant le sang"),
    _SE("Démon enflammé."),
    _SE("Démon terrifiant venu"),
    _SE("Démon capable de changer"),
    _SE("Formée des corps de puissants"),
    _SE("Herbe de Vénus développée."),
    _SE("Ancienne momie égyptienne."),
    _SE("Femme-démon aux cheveux de"),
    _SE("Petit démon espiègle."),
    "Zombie prenant l’apparence",
    "Zombie prenant l’apparence",
    "Zombie prenant l’apparence",
    "Seigneur des mouches.",
    _SE("Jeune sorcière."),
    "Bourreau des Enfers.",
    "Esprit de la glace travesti.",
    "Chasseuse de vamp. Utilise 4",
    _SE("Maître chasseur de vampires."),
    "Oiseau rare. S’enfuit",
    _SE("Etre magique voulant régner"),
    _SE("Puissant Seigneur à armure."),
    "Confidente de Dracula.",
    _SE("Prêtre maléfique de Dracula."),
    "Seigneur de Valachie."};
static char* D_psp_0929F950[] = {
    _SE("en １７９２．（５ ans plus tôt）"),
    "couverts de sang.",
    _SE("sur lui-même."),
    _SE("Contrôlé par la magie."),
    _SE("Redoutés serviteurs du diable."),
    _SE("du château."),
    "la magie.",
    "Attaque tous les intrus.",
    _SE("Dégouline de poison."),
    "",
    _SE("feu. Le + grand de son espèce."),
    _SE("équipé d’une hache."),
    "",
    _SE("envoyés il y a ３００ ans."),
    "coupantes comme un rasoir.",
    "",
    "un boomerang.",
    "",
    "de bas niveau.",
    "magique.",
    "des Enfers.",
    _SE("Mais laquelle est la tête ?"),
    "",
    "humaine. Saute comme une puce.",
    "de fusils.",
    _SE("à deux épées."),
    "armure et une boule de fer.",
    _SE("Peut pétrifier."),
    _SE("Ses graines pétrifient."),
    "armure et une hache.",
    _SE("Semble réticent à combattre."),
    "d’un arc.",
    "et une naginata.",
    "",
    "Lance des tonneaux en bois.",
    "d'apparence.",
    "A soif de vengeance.",
    "lentement.",
    "pour novices.",
    _SE("devenu mutant avec le château."),
    _SE("crâne de dragon blanchi."),
    _SE("Grande épée."),
    _SE("tourmentée errant sans corps."),
    _SE("à un rite maléfique."),
    "d’une lourde armure.",
    _SE("dans les zones périlleuses."),
    _SE("Manie une rapière."),
    "les grottes.",
    "la glace.",
    "",
    "",
    "en fer avec des piques.",
    _SE("oie spécialement entraînée."),
    "",
    "mort depuis longtemps.",
    "",
    "coupantes comme un rasoir.",
    "mythologique.",
    "une naginata.",
    _SE("même après avoir été banni."),
    _SE("Attaque avec un hibou dompté."),
    "",
    "",
    "",
    "et d’un bouclier.",
    "",
    "",
    "et mi-aigle.",
    _SE("deux épées."),
    "",
    "",
    _SE("Maître du combat sans armes."),
    "femme et un corps d’oiseau.",
    "",
    "",
    _SE("et condamné au combat éternel."),
    _SE("par des prêtres squelettes."),
    "",
    "d’inestimables connaissances.",
    "de poisson.",
    "portant une cape.",
    _SE("Invoque des alliés maléfiques."),
    "Manie un couteau gurkha.",
    _SE("énorme marteau en acier."),
    "Manie deux grandes dagues.",
    "gluante.",
    "Manie un disque.",
    "des corbeaux.",
    _SE("Appelé \"Musicien des Enfers\"."),
    "",
    "",
    _SE("Règne sur le haut du château."),
    "",
    _SE("r l’esprit maléfique des morts."),
    _SE("dans les rêves des hommes."),
    "de cerveaux.",
    "",
    "",
    "",
    "Forme un ensemble.",
    _SE("éternellement son crâne."),
    _SE("de graines empoisonnées."),
    _SE("lançant des bombes."),
    _SE("même une fois coupés en deux."),
    "",
    "magiciens peuvent le voir.",
    "",
    "changer de forme.",
    "un Homme-puce.",
    "de redoutables rayons.",
    _SE("forme d’une panthère noire."),
    _SE("énorme dragon."),
    "un Homme-puce.",
    "",
    "vampire.",
    "A occis Amalaric des Goths.",
    "de feu.",
    "",
    "Lance des pierres.",
    "un saut d’attaque.",
    "un ouargue.",
    "",
    "par une armure.",
    _SE("grâce à sa grande langue."),
    "",
    "des Enfers.",
    "de forme.",
    "guerriers.",
    _SE("Nourrie avec du sang de démon."),
    "",
    _SE("serpents et au regard pétrif."),
    "",
    "de Grant.",
    "de Trevor.",
    "de Sypha.",
    "",
    "",
    "",
    "Serviteur de Galamoth.",
    _SE("bêtes légend. Recher. Richter."),
    "",
    "quand il voit quelqu’un.",
    _SE("sur le monde des ténèbres."),
    "",
    "",
    "",
    _SE("Père d’Alucard.")};
static char* D_psp_092A0AF0[] = {
    "Von Richter vernichtet",
    "Wiedererweckt mit blut-",
    _SE("Unzerstörbarer Wirbelschädel."),
    "Frische Leichen.",
    _SE("Vampirfledermäuse."),
    _SE("Wölfe, die den Zugang zum"),
    "Magisch beseeltes Skelett.",
    _SE("Legendäres Wesen."),
    "Vierbeiniges Skelett.",
    _SE("Gefährlicher Skelett-"),
    "Feuerspuckender Wassergeist.",
    "Niederer Axtritter.",
    "Knochenwerfendes Skelett.",
    "Kirchensoldaten des Ostens,",
    "Pflanze mit rasiermesser-",
    "Besessener Ouijatisch.",
    "Bumerangwerfendes Skelett.",
    _SE("Feuerspeiender Flugdämon."),
    "Niedere Flammengeister.",
    _SE("Dämon mit verzaubertem Speer."),
    _SE("Dämonische Puppe aus "),
    _SE("Ekelerregende, zweiköpfige"),
    "Aus Medusenhaar.",
    _SE("Seltsames, menschenähnliches"),
    "Skelette mit",
    "Novize im Kampf mit",
    "Schwer gepanzerter Ritter",
    "Aus Medusenhaar.",
    "Mutierte Pflanze.",
    _SE("Gut gerüsteter Axtritter."),
    _SE("Feuer- und Eisdämon."),
    _SE("Skelettbogenschütze"),
    "Krieger, bewaffnet mit",
    "Schlange, Parasit Scyllas.",
    "Beseeltes Affenskelett.",
    _SE("Gestaltwandelnder Dämon."),
    "Kopf eines hingerichteten",
    "Langsam fliegender ",
    _SE("Zauberbuch für Anfänger."),
    "Heimische Eule, die durch das",
    _SE("Säule aus einem gebleichten"),
    "Ritter mit",
    _SE("Körperliche Manifestationen"),
    _SE("Magisch vergrößerte Kröte"),
    "Schwer gepanzerter, untoter",
    _SE("Gepanzerter Wächter."),
    "Kopfloses Skelett.",
    _SE("Höhlenfrosch."),
    "Eisbewaffneter, weiblicher",
    _SE("Riesiger Schädelgeist."),
    "Buch antiker Waffen.",
    "Skelett mit",
    "Flohmann auf trainierter",
    "Fleischfressender Rabe.",
    "Geist eines lang toten",
    _SE("Böses Dämonenschwert. Ruft"),
    "Pflanze mit rasiermesser-",
    "Mythologisches Meeresmonster.",
    "Naginateschwingendes Skelett.",
    "Der Schwertlord schwingt sein",
    "Schwer gepanzerter Ritter.",
    "Unsichtbarer Geist einer",
    "Animierter Schlammgolem.",
    _SE("Böses Dämonenschwert. Ruft"),
    "Flohmann mit Axt und",
    "Monster aus Gel und Schleim.",
    "Riesiges Skelett.",
    _SE("In Teilen Pferd, Löwe und"),
    "Meister im Kampf mit",
    "Skelett eines Werpanters.",
    "Halb Mensch, halb Wolf.",
    _SE("Grabwächter."),
    "Wesen mit Frauenkopf und",
    "Halb Mensch, halb Stier.",
    "Pyromanischer Gremlin.",
    "Blutdurstiger, untoter Ritter,",
    _SE("Tragbarer Schädelschrein,"),
    "Geiserhexen aus Salem.",
    _SE("Durchsucht Gräber und"),
    _SE("Fischkopfwächter."),
    _SE("Geheimnisvoll verhüllter"),
    _SE("Kleiner, magiekundiger Dämon."),
    _SE("Großer Bruder."),
    _SE("Großer Bruder."),
    _SE("Ältester großer Bruder."),
    "Monster aus schleimiger",
    "Scheibenschwingender,",
    _SE("Dämonenlord der Raben."),
    _SE("Donnerwerfender Dämon."),
    _SE("Wachhund der Hölle."),
    "Mit Menschenblut gegossen.",
    "Magiekundiger Vampir. Herrscht",
    "Fischkopfmeister.",
    _SE("Grabsteine, beseelt von bösen"),
    _SE("Weiblicher Dämon."),
    _SE("Gepfählter Mann auf der Suche"),
    _SE("Der feige Löwe."),
    "Ein Monster namens  Schmu .",
    "Herzloser Zinnmann.",
    "Albtraumkreatur.",
    "Skelett, das auf ewig seinen",
    "Steckt voller Giftsamen.",
    "Bombenwerfender, gepanzerter",
    "Zombies, die auch angreifen,",
    "Meister mit Wurfgeschossen.",
    "Mutiertes Insekt.",
    "Erschreckend zielgenauer",
    "Gestaltwandelnder Lykanthop.",
    "Vom Flohmann beherrschter",
    _SE("Schwingt eine fürchterliche"),
    _SE("Flüssiges Wesen. Tritt in Form"),
    "Beseeltes Skelett eines ",
    "Vom Flohmann gerittener",
    _SE("Stierköpfiges Monster."),
    "Riesige Vampirfledermaus.",
    _SE("Engelsbogenschütze. Hat Amalar"),
    "Feuerspuckender Wolf.",
    _SE("Böses Dämonenschwert. Ruft"),
    "Felsenwerfender, gepanzerter",
    "Skelett mit Sprungangriff.",
    "Ein wargreitendes Skelett.",
    _SE("Böser, mutierter Oktopus."),
    "Geharnischtes Kriegstier.",
    "Wenig intelligenter Blutsauger",
    _SE("Flammendämon."),
    _SE("Schrecklicher Dämon aus "),
    _SE("Gestaltwandelnder Dämon."),
    _SE("Besteht aus den Körperteilen"),
    _SE("Mächtige Venusranke."),
    _SE("Uralte ägyptische Mumie."),
    _SE("Schlangenköpfige Dämonin"),
    _SE("Boshafter kleiner Dämon."),
    "Zombie, der sich als Grant",
    "Zombie, der sich als Trevor",
    "Zombie, der sich als Sypha",
    "Beelzebub, Herr der Fliegen.",
    "Junge Hexe.",
    _SE("Henker der Hölle."),
    "Transvestiten-Eisgeist.",
    _SE("Vampirjäger. Nutzt 4 legendäre"),
    _SE("Meistervampirjäger."),
    "Seltener Vogel.",
    _SE("Magisches Geschöpf, das die"),
    _SE("Mächtiger Rüstungslord."),
    "Draculas Vertrauter.",
    "Dunkler Priester des Dracula.",
    "Herr von Wallachia."};
static char* D_psp_092A14D0[] = {
    "im Jahre １７９２ (vor ５ Jahren).",
    _SE("getränkten Knochen."),
    "",
    "Magisch beseelt.",
    _SE("Gefürchtete Diener des Bösen."),
    "Schloss bewachen.",
    "",
    "Greift alle Eindringlinge an.",
    "Trieft vor Gift.",
    _SE("schwertkämpfer."),
    _SE("Größter Wassergeist."),
    "",
    "",
    "seit 300 Jahren unterwegs.",
    _SE("scharfen Blättern."),
    "",
    "",
    "",
    "",
    "",
    _SE("der Hölle."),
    "Bestie. Was ist der Kopf?",
    "",
    "Wesen, springt wie ein Floh.",
    "Gewehren.",
    "zwei Klingen.",
    "mit Eisenkugel.",
    "Kann Feinde versteinern.",
    "Die Samen versteinern.",
    "",
    _SE("Geht Kämpfen aus dem Weg."),
    "",
    "Naginata.",
    "",
    _SE("Schleudert Holzfässer."),
    "",
    "Soldaten. Sinnt auf Rache.",
    "Skelettkrieger.",
    "",
    "Schloss mutiert ist.",
    _SE("Drachenschädel."),
    "Breitschwert.",
    "gepeinigter Seelen.",
    _SE("(dämonisch getauft)."),
    "Krieger.",
    _SE("Stark i.gefährlichen Gebieten."),
    "Schwingt ein Rapier.",
    "",
    "Geist.",
    "",
    "",
    "Eisennagelflegel.",
    "Kriegsgans.",
    "",
    "blauen Raben.",
    "Poltergeister.",
    _SE("scharfen Blättern."),
    "",
    "",
    "Schwert auch unter Bann.",
    "Greift m. trainierter Eule an.",
    _SE("Jägerin."),
    "",
    "Poltergeister.",
    "Schild.",
    "",
    "",
    "Adler.",
    "zwei Klingen.",
    "",
    "",
    "Meister im Kampf ohne Waffen.",
    _SE("Vogelkörper."),
    "",
    "",
    "der ewig den Kampf sucht.",
    "getragen von Skelettpriestern.",
    "",
    "steckt voller Wissen.",
    "",
    _SE("Schwertkämpfer."),
    _SE("Ruft dämonische Helfer."),
    "Schwingt ein Gurkha-Messer.",
    "Benutzt einen Stahlhammer.",
    "Schwingt 2 gewaltige Dolche.",
    "Gelmasse.",
    "gepanzerter Ritter.",
    "",
    _SE("Genannt \"Musiker der Hölle\"."),
    "",
    "",
    _SE("üb. d.oberen Teil d.Schlosses."),
    "",
    "Geistern der Toten.",
    _SE("Dringt in Männerträume ein."),
    "nach Intelligenz.",
    "",
    "",
    "",
    "Besteht aus Vielen.",
    _SE("eigenen Schädel jagt."),
    "",
    "Ritter.",
    "wenn sie zerschnitten sind.",
    "",
    _SE("Nur für Magier sichtbar."),
    _SE("Bogenschütze."),
    "",
    "Wyrm.",
    "Strahlenwaffe.",
    "eines schwarzen Panters auf.",
    "gewaltigen Drachens.",
    _SE("weißer Drache."),
    "",
    "",
    "von den Goth erschlagen.",
    "",
    "Poltergeister.",
    "Ritter.",
    "",
    "",
    "",
    "",
    "mit langer Saugzunge.",
    "",
    _SE("der Hölle."),
    "",
    _SE("mächtiger Krieger."),
    _SE("Mit Dämonenblut gegossen."),
    "",
    "mit versteinerndem Blick.",
    "",
    "ausgibt.",
    "ausgibt.",
    "ausgibt.",
    "",
    "",
    "",
    "Diener von Galamoth.",
    "Tiere. Sucht Richter.",
    "",
    _SE("Läuft vor Menschen davon."),
    "Unterwelt regieren will.",
    "",
    "",
    "",
    "Vater von Alucard."};
static char* D_psp_092A1730[] = {"ATT", "DEF"};
static char* D_psp_092A1798[] = {
    "\002"
    "Buy item",
    "\002"
    "Tactics",
    "\002"
    "Enemy list",
    "\002"
    "",
    "\002"
    "Exit",
    "\002"
    "Sell gem",
    "\002"
    "Sound test"};
static char D_psp_092A17B8[] = _S("SOLD OUT");
static char* D_psp_092A17D8[] = {_S("Jewel of Open")};
static char* D_psp_092A1870[] = {
    _S("Castle Map"),     _S("Magic Scroll 1"), _S("Magic Scroll 2"),
    _S("Magic Scroll 3"), _S("Magic Scroll 4"), _S("Magic Scroll 5"),
    _S("Magic Scroll 6"), _S("Magic Scroll 7"), _S("Magic Scroll 8")};
static char* D_psp_092A1990[] = {
    _S("Nothing"),      _S("Large Heart"), _S("$1"),     _S("$25"),
    _S("$50"),          _S("$100"),        _S("$250"),   _S("$400"),
    _S("$700"),         _S("$1000"),       _S("$2000"),  _S("$5000"),
    _S("Heart Up"),     _S("Meat"),        _S("Knife"),  _S("Axe"),
    _S("Cross"),        _S("Holy Water"),  _S("Clock"),  _S("Holy Book"),
    _S("ReboundStone"), _S("Bibuti"),      _S("Agunea"), _S("Life Up")};
static char* D_psp_092A1A20[] = {
    _S("Strong VS."), _S("Immune"), _S("Weak VS."), _S("Absorb")};
static char* D_psp_092A1A88[] = {
    _S("HOL"), _S("DRK"), _S("FIR"), _S("THU"), _S("ICE"), _S("H2O"),
    _S("STN"), _S("PSN"), _S("CUR"), _S("CUT"), _S("HIT")};
static char D_psp_092A1AB8[] = _S("None");
static char* D_psp_092A1B00[] = {
    _S("LV"),         _S("HP"),  _S("Def"), _S("Exp"),
    _S("Drop Items"), _S("No."), _S("??")};
static char D_psp_092A1B20[] = {
    // clang-format off
    CH('S'), CH('T'), CH('R'),
    CH('C'), CH('O'), CH('N'),
    CH('I'), CH('N'), CH('T'),
    CH('L'), CH('C'), CH('K')
    // clang-format on
};
static char* D_psp_092A1B60[] = {
    _S("Number"), _S("Equipped"), _S("Not equipped"), _S("a")};
static char* D_psp_092A1DC0[] = {
    _S("Prologue"),
    _S("Dance of Illusions"),
    _S("Prayer"),
    _S("Dracula's Castle"),
    _S("Dance of Gold"),
    _S("Marble Gallery"),
    _S("Tower of Mist"),
    _S("Nocturne"),
    _S("Wood Carving Partitia"),
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
    _S("The Outcasts"),
    _S("Finale Toccata"),
    _S("Black Banquet"),
    _S("Mournful Serenade")};
static char* D_psp_092A1FA8[] = {
    _S("Dracula"),         _S("Slogra&Gaibon"),
    _S("Doppleganger10"),  _S("Hippogryph"),
    _S("Scylla"),          _S("Minotaur&Werewolf"),
    _S("Karasuman"),       _S("Succubus"),
    _S("Cerberus"),        _S("Olrox"),
    _S("Granfaloon"),      _S("Maria Renard"),
    _S("Richter Belmont"), _S("Darkwing Bat"),
    _S("Akmodan II"),      _S("Medusa"),
    _S("The Creature"),    _S("Death"),
    _S("Doppleganger40"),  _S("Trevor Grant Sypha"),
    _S("Beelzebub"),       _S("Galamoth"),
    _S("Shaft"),           _S("True Dracula")};
static char* D_psp_092A2110[] = {
    "Basic map of Dracula’s castle", "Contains ”Dark Metamorphosis”",
    "Contains ”Summon Spirit”",      "Contains ”Hellfire”",
    "Contains ”Tetra Spirits”",      "Contains ”Soul Steal”",
    "Contains ”Wolf Charge”",        "Contains ”Wing Smash”",
    "Contains ”Sword Brothers”"};
static char D_psp_092A2138[] = {
    CIRCLE, SQUARE, CIRCLE, SQUARE, CH('G'), CH('O'), CH('L'), CH('D')};
static char* D_psp_092A2148[] = {"ATQ", "DEF"};
static char* D_psp_092A21A8[] = {
    "\002"
    "Cmp. obj.",
    "\002" _SE("Tácticas"),
    "\002"
    "Lista enem.",
    "\002"
    "",
    "\002"
    "Salir",
    "\002"
    "Vnd. gema",
    "\002"
    "Prob. son."};
static char D_psp_092A21C8[] = _S("AGOTADO");
static char* D_psp_092A21E8[] = {_S("Joya apertura")};
static char* D_psp_092A2280[] = {
    _S("Mapa castillo"),  _S("Perg. mágico 1"), _S("Perg. mágico 2"),
    _S("Perg. mágico 3"), _S("Perg. mágico 4"), _S("Perg. mágico 5"),
    _S("Perg. mágico 6"), _S("Perg. mágico 7"), _S("Perg. mágico 8")};
static char* D_psp_092A2390[] = {
    _S("Nada"),        _S("Gran corazón"), _S("1$"),       _S("25$"),
    _S("50$"),         _S("100$"),         _S("250$"),     _S("400$"),
    _S("700$"),        _S("1000$"),        _S("2000$"),    _S("5000$"),
    _S("Más corazón"), _S("Carne"),        _S("Cuchillo"), _S("Hacha"),
    _S("Cruz"),        _S("Agua sagrada"), _S("Reloj"),    _S("Libro sagr."),
    _S("P. recuper."), _S("Bibuti"),       _S("Agunea"),   _S("Más vida")};
static char* D_psp_092A2428[] = {
    _S("Fuerte contra"), _S("Inmune"), _S("Débil contra"), _S("Absorbe")};
static char* D_psp_092A2480[] = {
    _S("SAG"), _S("OSC"), _S("FUE"), _S("TRU"), _S("HIE"), _S("H2O"),
    _S("PIE"), _S("VEN"), _S("CUR"), _S("COR"), _S("GOL")};
static char D_psp_092A24B0[] = _S("Ninguno");
static char* D_psp_092A24E8[] = {
    _S("NV"), _S("PS"), _S("Def"), _S("Exp"), _S("Soltar objetos"),
    _S("Nº"), _S("??")};
static char D_psp_092A2508[] = {
    // clang-format off
    CH('F'), CH('U'), CH('E'),
    CH('C'), CH('O'), CH('N'),
    CH('I'), CH('N'), CH('T'),
    CH('S'), CH('U'), CH('E')
    // clang-format on
};
static char* D_psp_092A2540[] = {
    _S("Número"), _S("Equipado"), _S("No equipado"), _S("a")};
static char* D_psp_092A27F0[] = {
    _S("Prólogo"),
    _S("Baile de ilusiones"),
    _S("Plegaria"),
    _S("Castillo de Dracula"),
    _S("Baile de oro"),
    _S("Pasillo de mármol"),
    _S("Torre de niebla"),
    _S("Nocturno"),
    _S("Partita tallada en madera"),
    _S("Puerta de espíritussagrados"),
    _S("Festival de siervos"),
    _S("Tierra de bendición"),
    _S("Réquiem de los dioses"),
    _S("Lágrima de cristal"),
    _S("Pozo abandonado"),
    _S("Cementerio arco iris"),
    _S("Silencio"),
    _S("Cuadro perdido"),
    _S("Baile de los blancos"),
    _S("Zona de maldición"),
    _S("Banquete encantado"),
    _S("Fantasmas errantes"),
    _S("El príncipe trágico"),
    _S("Puerta al abismo"),
    _S("Puerta celestial"),
    _S("Balada de la muerte"),
    _S("Relaciones de sangre"),
    _S("Toccata final"),
    _S("Banquete negro"),
    _S("Serenata lamentable")};
static char* D_psp_092A2908[] = {
    _S("Dracula"),         _S("Slogra y Gaibon"),
    _S("Doppleganger10"),  _S("Hipogrifo"),
    _S("Scylla"),          _S("Minotauro y H.lobo"),
    _S("Karasuman"),       _S("Súcubo"),
    _S("Cancerbero"),      _S("Olrox"),
    _S("Granfaloon"),      _S("Maria Renard"),
    _S("Richter Belmont"), _S("Murciél. ala osc."),
    _S("Akmodan II"),      _S("Medusa"),
    _S("La Criatura"),     _S("Muerte"),
    _S("Doppleganger40"),  _S("Trevor Grant Sypha"),
    _S("Beelzebub"),       _S("Galamoth"),
    _S("Shaft"),           _S("Dracula auténtico")};
static char* D_psp_092A2A88[] = {
    _SE("Mapa básico del castillo."),  "Contiene ”Metamorfosis oscura”",
    _SE("Contiene ”Invoca-espíritu”"), "Contiene ”Fuego del infierno”",
    _SE("Contiene ”Tetra-espíritu”"),  "Contiene ”Roba-almas”",
    "Contiene ”Ataque de lobo”",       "Contiene ”Golpe de ala”",
    "Contiene ”Hermanos espada”"};
static char D_psp_092A2AB0[] = {
    CIRCLE, SQUARE, CIRCLE, SQUARE, CH('O'), CH('R'), CH('O')};
static char* D_psp_092A2AC0[] = {"ATT", "DIF"};
static char* D_psp_092A2B20[] = {
    "\002"
    "Compra og.",
    "\002"
    "Tattiche",
    "\002"
    "Lista nem.",
    "\002"
    "",
    "\002"
    "Esci",
    "\002"
    "Vendi gem.",
    "\002"
    "Test audio"};
static char D_psp_092A2B40[] = _S("ESAURITO");
static char* D_psp_092A2B60[] = {_S("Gioia Chiave")};
static char* D_psp_092A2BF8[] = {
    _S("Mappa castel."),  _S("RotoloMagico 1"), _S("RotoloMagico 2"),
    _S("RotoloMagico 3"), _S("RotoloMagico 4"), _S("RotoloMagico 5"),
    _S("RotoloMagico 6"), _S("RotoloMagico 7"), _S("RotoloMagico 8")};
static char* D_psp_092A2CB0[] = {
    _S("Niente"),     _S("Grande Cuore"), _S("$1"),       _S("$25"),
    _S("$50"),        _S("$100"),         _S("$250"),     _S("$400"),
    _S("$700"),       _S("$1000"),        _S("$2000"),    _S("$5000"),
    _S("Cuore +"),    _S("Carne"),        _S("Coltello"), _S("Ascia"),
    _S("Croce"),      _S("Acqua Santa"),  _S("Orologio"), _S("Libro Sacro"),
    _S("Rimbalzina"), _S("Bibuti"),       _S("Agunea"),   _S("Vita +")};
static char* D_psp_092A2D40[] = {
    _S("Potente contro"), _S("Immune"), _S("Debole contro"), _S("Assorbi")};
static char* D_psp_092A2D88[] = {
    _S("SAC"), _S("OSC"), _S("FUO"), _S("LAM"), _S("GHI"), _S("H2O"),
    _S("PIE"), _S("VEL"), _S("CUR"), _S("TAG"), _S("COL")};
static char D_psp_092A2DB8[] = _S("Nessuno");
static char* D_psp_092A2DE8[] = {
    _S("LV"), _S("PS"), _S("Dif"), _S("Esp"), _S("Lascia oggetti"),
    _S("Nº"), _S("??")};
static char D_psp_092A2E08[] = {
    // clang-format off
    CH('P'), CH('O'), CH('T'),
    CH('F'), CH('I'), CH('S'),
    CH('I'), CH('N'), CH('T'),
    CH('F'), CH('O'), CH('R')
    // clang-format on
};
static char* D_psp_092A2E40[] = {
    _S("Numero"), _S("Equipaggiato"), _S("Non equipag."), _S("a")};
static char* D_psp_092A30F8[] = {
    _S("Prologo"),
    _S("Danza d'illusioni"),
    _S("La preghiera"),
    _S("Il castello di Dracula"),
    _S("Danza dell'oro"),
    _S("Galleria di marmo"),
    _S("Torre della nebbia"),
    _S("Notturno"),
    _S("Spartito inciso nel legn"),
    _S("Porta degli spiriti sant"),
    _S("Festival dei servi"),
    _S("Terra di benedizione"),
    _S("Requiem per gli dei"),
    _S("Lacrima di cristallo"),
    _S("Fossa abbandonata"),
    _S("Cimitero dell'arcobaleno"),
    _S("Il silenzio"),
    _S("Il dipinto perduto"),
    _S("Danza dei pali"),
    _S("Zona maledetta"),
    _S("Banchetto incantato"),
    _S("Spiriti vaganti"),
    _S("Il tragico principe"),
    _S("Porta per gli abissi"),
    _S("Le porte del cielo"),
    _S("Ballata macabra"),
    _S("Legami di sangue"),
    _S("Toccata finale"),
    _S("Il nero banchetto"),
    _S("Tragica serenata")};
static char* D_psp_092A3210[] = {
    _S("Dracula"),         _S("Slogra e Gaibon"),
    _S("Doppleganger10"),  _S("Ippogrifo"),
    _S("Scilla"),          _S("Minot. e Licantr."),
    _S("Karasuman"),       _S("Succubus"),
    _S("Cerbero"),         _S("Olrox"),
    _S("Granfaloon"),      _S("Maria Renard"),
    _S("Richter Belmont"), _S("PipistrOscuro"),
    _S("Akmodan II"),      _S("Medusa"),
    _S("La Creatura"),     _S("Morte"),
    _S("Doppleganger40"),  _S("Trevor Grant Sypha"),
    _S("Belzebù"),         _S("Galamoth"),
    _S("Shaft"),           _S("Vero Dracula")};
static char* D_psp_092A3390[] = {
    "Mappa del castello di Dracula.", "Contiene ”Metamorfosi Oscura”",
    "Contiene ”Evoca Spirito”",       "Contiene ”Fuoco Infernale”",
    "Contiene ”Quattro Spiriti”",     "Contiene ”Furto d'Anima”",
    "Contiene ”Attacco del Lupo”",    "Contiene ”L'Ala che Spezza”",
    "Contiene ”Fratelli di Spada”"};
static char D_psp_092A33B8[] = {
    CIRCLE, SQUARE, CIRCLE, SQUARE, CH('O'), CH('R'), CH('O')};
static char* D_psp_092A33C0[] = {"ATT", "DEF"};
static char* D_psp_092A3428[] = {
    "\002"
    "Acht item",
    "\002"
    "Tactiques",
    "\002"
    "Ennemis",
    "\002"
    "",
    "\002"
    "Quitter",
    "\002"
    "Vdre item",
    "\002"
    "Test son"};
static char D_psp_092A3448[] = _S("STOCK EPUISE");
static char* D_psp_092A3468[] = {_S("Joyau ouvert.")};
static char* D_psp_092A3500[] = {
    _S("Carte château"),  _S("Parch. magie 1"), _S("Parch. magie 2"),
    _S("Parch. magie 3"), _S("Parch. magie 4"), _S("Parch. magie 5"),
    _S("Parch. magie 6"), _S("Parch. magie 7"), _S("Parch. magie 8")};
static char* D_psp_092A35C0[] = {
    _S("Rien"),         _S("Grand cœur"), _S("1$"),      _S("25$"),
    _S("50$"),          _S("100$"),       _S("250$"),    _S("400$"),
    _S("700$"),         _S("1000$"),      _S("2000$"),   _S("5000$"),
    _S("Cœur en plus"), _S("Viande"),     _S("Couteau"), _S("Hache"),
    _S("Croix"),        _S("Eau bénite"), _S("Montre"),  _S("Livre sacré"),
    _S("PierreRebond"), _S("Bibuti"),     _S("Agunea"),  _S("Vie en plus")};
static char* D_psp_092A3650[] = {
    _S("Fort contre"), _S("Immunise"), _S("Faible contre"), _S("Absorbe")};
static char* D_psp_092A36B8[] = {
    _S("FOI"), _S("TEN"), _S("FEU"), _S("FDR"), _S("GLA"), _S("EAU"),
    _S("ROC"), _S("POI"), _S("MAL"), _S("CPR"), _S("DEG")};
static char D_psp_092A36E8[] = _S("Aucun");
static char* D_psp_092A3708[] = {
    _S("NV"), _S("PV"), _S("Def"), _S("Exp"), _S("Items laissés"),
    _S("Nº"), _S("??")};
static char D_psp_092A3728[] = {
    // clang-format off
    CH('F'), CH('O'), CH('R'),
    CH('C'), CH('O'), CH('N'),
    CH('I'), CH('N'), CH('T'),
    CH('C'), CH('H'), CH('A')
    // clang-format on
};
static char* D_psp_092A3758[] = {
    _S("Nombre"), _S("Equipé"), _S("Non équipé"), _S("a")};
static char* D_psp_092A39A8[] = {
    _S("Prologue"),
    _S("Danse des illusions"),
    _S("Prière"),
    _S("Château de Dracula"),
    _S("Danse de l'or"),
    _S("Galerie en marbre"),
    _S("Tour de brume"),
    _S("Nocturne"),
    _S("Partita gravée dans le bois"),
    _S("Porte des esprits sacrés"),
    _S("Festival des serviteurs"),
    _S("Terre de bénédiction"),
    _S("Requiem pour les dieux"),
    _S("Larmes de cristal"),
    _S("Puit abandonné"),
    _S("Cimetière arc-en-ciel"),
    _S("Silence"),
    _S("Peinture perdue"),
    _S("Danse de Pales"),
    _S("Lieu maudit"),
    _S("Banquet enchanté"),
    _S("Fantômes errants"),
    _S("Le prince tragique"),
    _S("Porte vers les Abysses"),
    _S("Portes du Paradis"),
    _S("Ballade de la Mort"),
    _S("Liens du sang"),
    _S("Toccata finale"),
    _S("Banquet noir"),
    _S("Sérénade funèbre")};
static char* D_psp_092A3AC8[] = {
    _S("Dracula"),         _S("Slogra&Gaibon"),
    _S("Doppleganger10"),  _S("Hippogryphe"),
    _S("Scylla"),          _S("Minot.&Loup-garou"),
    _S("Karasuman"),       _S("Succube"),
    _S("Cerbère"),         _S("Olrox"),
    _S("Granfaloon"),      _S("Maria Renard"),
    _S("Richter Belmont"), _S("Chv-sris ténèbres"),
    _S("Akmodan II"),      _S("Méduse"),
    _S("La Créature"),     _S("La Mort"),
    _S("Doppleganger40"),  _S("Trevor Grant Sypha"),
    _S("Belzébuth"),       _S("Galamoth"),
    _S("Shaft"),           _S("Vrai Dracula")};
static char* D_psp_092A3C48[] = {
    _SE("Carte basique du chât. Dracula"),
    _SE("Contient ”Métamorphose noire”"),
    _SE("Contient ”Esprit invoqué”"),
    "Contient ”Feu de l’enfer”",
    "Contient ”Esprit Tetra”",
    "Contient ”Charge de Loup”",
    _SE("Contient ”Capture de l’âme”"),
    _SE("Contient ”Frappe ailée”"),
    _SE("Contient ”Frères spadassins”")};
static char D_psp_092A3C70[] = {
    CIRCLE, SQUARE, CIRCLE, SQUARE, CH('O'), CH('R')};
static char* D_psp_092A3C80[] = {"ANG", "DEF"};
static char* D_psp_092A3CD8[] = {
    "\002"
    "O. kaufen",
    "\002"
    "Taktik",
    "\002"
    "Feinde",
    "\002"
    "",
    "\002"
    "Verlassen",
    "\002"
    "Stein vk.",
    "\002"
    "Audiotest"};
static char D_psp_092A3CF8[] = _S("AUSVERKAUFT");
static char* D_psp_092A3D18[] = {_S("Öffnungsjuwel")};
static char* D_psp_092A3DB0[] = {
    _S("Schlosskarte"),   _S("Magiepergam. 1"), _S("Magiepergam. 2"),
    _S("Magiepergam. 3"), _S("Magiepergam. 4"), _S("Magiepergam. 5"),
    _S("Magiepergam. 6"), _S("Magiepergam. 7"), _S("Magiepergam. 8")};
static char* D_psp_092A3E70[] = {
    _S("Nichts"),       _S("Großes Herz"), _S("$1"),     _S("$25"),
    _S("$50"),          _S("$100"),        _S("$250"),   _S("$400"),
    _S("$700"),         _S("$1000"),       _S("$2000"),  _S("$5000"),
    _S("Herz Plus"),    _S("Fleisch"),     _S("Messer"), _S("Axt"),
    _S("Kreuz"),        _S("Weihwasser"),  _S("Uhr"),    _S("Heilig. Buch"),
    _S("Neubundstein"), _S("Bibuti"),      _S("Agunea"), _S("Leben Plus")};
static char* D_psp_092A3F08[] = {
    _S("Stark gegen"), _S("Immun"), _S("Schwach gegen"), _S("Absorbieren")};
static char* D_psp_092A3F58[] = {
    _S("HLG"), _S("DKL"), _S("FEU"), _S("DON"), _S("EIS"), _S("H2O"),
    _S("STN"), _S("GIF"), _S("FLU"), _S("MES"), _S("TRF")};
static char D_psp_092A3F88[] = _S("Nichts");
static char* D_psp_092A3FB0[] = {
    _S("LV"),           _S("HP"),  _S("Def"), _S("Erf"),
    _S("Obj. ablegen"), _S("Anz"), _S("??")};
static char D_psp_092A3FD0[] = {
    // clang-format off
    CH('S'), CH('T'), CH('K'),
    CH('K'), CH('O'), CH('N'),
    CH('I'), CH('N'), CH('T'),
    CH('G'), CH('L'), CH('K')
    // clang-format on
};
static char* D_psp_092A4008[] = {
    _S("Anzahl"), _S("Ausgerüstet"), _S("N. gerüstet"), _S("a")};
static char* D_psp_092A4270[] = {
    _S("Prolog"),
    _S("Tanz der Illusionen"),
    _S("Gebet"),
    _S("Draculas Schloss"),
    _S("Tanz des Goldes"),
    _S("Marmorgalerie"),
    _S("Nebelturm"),
    _S("Nocturne"),
    _S("Holzschnitzerpartitur"),
    _S("Tor der heiligen Geister"),
    _S("Fest der Diener"),
    _S("Land der Segnung"),
    _S("Requiem für die Götter"),
    _S("Kristallträne"),
    _S("Verlassende Grube"),
    _S("Regenbogenfriedhof"),
    _S("Stille"),
    _S("Verlorenes Gemälde"),
    _S("Tanz der Blassen"),
    _S("Fluchgebiet"),
    _S("Verzaubertes Bankett"),
    _S("Wandernde Gespenster"),
    _S("Der tragische Prinz"),
    _S("Tür zum Abgrund"),
    _S("Himmlischer Torbogen"),
    _S("Todesballade"),
    _S("Blutverwandschaft"),
    _S("End-Toccata"),
    _S("Schwarzes Bankett"),
    _S("Trauerserenade")};
static char* D_psp_092A4398[] = {
    _S("Dracula"),         _S("Slogra & Gaibon"),
    _S("Doppelgänger10"),  _S("Hippogryph"),
    _S("Scylla"),          _S("Minotaurus&Werwolf"),
    _S("Karasuman"),       _S("Sukkubus"),
    _S("Zerberus"),        _S("Olrox"),
    _S("Granfaloon"),      _S("Maria Renard"),
    _S("Richter Belmont"), _S("Dunkelflügel-Fl.m."),
    _S("Akmodan II"),      _S("Medusa"),
    _S("Die Kreatur"),     _S("Tod"),
    _S("Doppelgänger40"),  _S("Trevor Grant Sypha"),
    _S("Beelzebub"),       _S("Galamoth"),
    _S("Shaft"),           _S("Wahrer Dracula")};
static char* D_psp_092A44F0[] = {
    "Einf. Karte v. Dracula Schloss", _SE("Enthält ”Dunkle Verwandlung”"),
    _SE("Enthält ”Geisterruf”"),      _SE("Enthält ”Höllenfeuer”"),
    _SE("Enthält ”Tetra-Geist”"),     _SE("Enthält ”Seelendieb”"),
    _SE("Enthält ”Wolfsansturm”"),    _SE("Enthält ”Flügelhieb”"),
    _SE("Enthält ”Schwertbrüder”")};
static char D_psp_092A4518[] = {
    CIRCLE, SQUARE, CIRCLE, SQUARE, CH('G'), CH('O'), CH('L'), CH('D')};

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

// bss
static u32 D_us_801D415C[64];
static u32 D_us_801D425C[64];
static char** D_us_80181528;
static char** D_us_80181310;
static char* D_us_801816A4;
static char** D_us_801816AC;
static char** D_us_801816B0;
static char** D_us_8018181C;
static char** D_psp_092A5F98;
static char** D_us_8018187C;
static char* D_psp_092A5F88;
static char** D_us_801818C0;
static char* D_us_80181668;
static char** D_us_80181674;
static char** D_us_801818F4;
static char** D_us_801816C8;
static char** D_us_8018168C;
static char* D_us_80181660;
static char** D_psp_092A5F48;
static char** D_psp_092A5F40;
static ShopItem D_us_801D4364[64];
static u8* D_psp_092A5D38;
static char D_us_80181650[4];

#include "../../get_lang.h"

void func_psp_0925D4D0(void) {
    D_us_80181528 = GetLang(D_psp_092A1730, D_psp_092A33C0, D_psp_092A2148,
                            D_psp_092A3C80, D_psp_092A2AC0);
    D_us_80181310 = GetLang(D_psp_092A1798, D_psp_092A3428, D_psp_092A21A8,
                            D_psp_092A3CD8, D_psp_092A2B20);
    D_us_801816A4 = GetLang(D_psp_092A17B8, D_psp_092A3448, D_psp_092A21C8,
                            D_psp_092A3CF8, D_psp_092A2B40);
    D_us_801816AC = GetLang(D_psp_092A17D8, D_psp_092A3468, D_psp_092A21E8,
                            D_psp_092A3D18, D_psp_092A2B60);
    D_us_801816B0 = GetLang(D_psp_092A1870, D_psp_092A3500, D_psp_092A2280,
                            D_psp_092A3DB0, D_psp_092A2BF8);
    D_us_8018181C = GetLang(D_psp_092A1990, D_psp_092A35C0, D_psp_092A2390,
                            D_psp_092A3E70, D_psp_092A2CB0);
    D_psp_092A5F98 = GetLang(D_psp_092A1A20, D_psp_092A3650, D_psp_092A2428,
                             D_psp_092A3F08, D_psp_092A2D40);
    D_us_8018187C = GetLang(D_psp_092A1A88, D_psp_092A36B8, D_psp_092A2480,
                            D_psp_092A3F58, D_psp_092A2D88);
    D_psp_092A5F88 = GetLang(D_psp_092A1AB8, D_psp_092A36E8, D_psp_092A24B0,
                             D_psp_092A3F88, D_psp_092A2DB8);
    D_us_801818C0 = GetLang(D_psp_092A1B00, D_psp_092A3708, D_psp_092A24E8,
                            D_psp_092A3FB0, D_psp_092A2DE8);
    D_us_80181668 = GetLang(D_psp_092A1B20, D_psp_092A3728, D_psp_092A2508,
                            D_psp_092A3FD0, D_psp_092A2E08);
    D_us_80181674 = GetLang(D_psp_092A1B60, D_psp_092A3758, D_psp_092A2540,
                            D_psp_092A4008, D_psp_092A2E40);
    D_us_801818F4 = GetLang(D_psp_092A1DC0, D_psp_092A39A8, D_psp_092A27F0,
                            D_psp_092A4270, D_psp_092A30F8);
    D_us_8018168C = GetLang(D_psp_092A2110, D_psp_092A3C48, D_psp_092A2A88,
                            D_psp_092A44F0, D_psp_092A3390);
    D_us_80181660 = GetLang(D_psp_092A2138, D_psp_092A3C70, D_psp_092A2AB0,
                            D_psp_092A4518, D_psp_092A33B8);
    D_us_801816C8 = GetLang(D_psp_092A1FA8, D_psp_092A3AC8, D_psp_092A2908,
                            D_psp_092A4398, D_psp_092A3210);
    D_psp_092A5F48 = GetLang(D_psp_09299A18, D_psp_0929ED18, D_psp_0929B4A0,
                             D_psp_092A0AF0, D_psp_0929D1B0);
    D_psp_092A5F40 = GetLang(D_psp_0929A320, D_psp_0929F950, D_psp_0929BFF0,
                             D_psp_092A14D0, D_psp_0929DBD0);
}

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
        if (!g_Player.demo_timer && (g_Player.vram_flag & TOUCHING_GROUND)) {
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
    if (g_Player.vram_flag & TOUCHING_GROUND) {
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

static char D_us_80181328[] = {4, 0, 5, 1, 4};
static char D_us_80181330[] = {5, 0, 5, 1, 2, 4};
static char D_us_80181338[] = {6, 0, 5, 1, 2, 3, 4};
static char D_psp_092A4668[] = {6, 0, 5, 1, 2, 6, 4};
static char* D_us_80181340[] = {
    D_us_80181328, D_us_80181330, D_us_80181338, D_psp_092A4668};

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
    { INVENTORY_DOCUMENT,  0x80, DOC_CASTLE_MAP,      105 },
    { INVENTORY_DOCUMENT,  0x81, DOC_MAGIC_SCROLL_1,  500 },
    { INVENTORY_DOCUMENT,  0x82, DOC_MAGIC_SCROLL_2,  1500 },
    { INVENTORY_DOCUMENT,  0x83, DOC_MAGIC_SCROLL_3,  5000 },
    { INVENTORY_DOCUMENT,  0x84, DOC_MAGIC_SCROLL_4,  8000 },
    { INVENTORY_DOCUMENT,  0x85, DOC_MAGIC_SCROLL_5,  15000 },
    { INVENTORY_DOCUMENT,  0x86, DOC_MAGIC_SCROLL_6,  4000 },
    { INVENTORY_DOCUMENT,  0x87, DOC_MAGIC_SCROLL_7,  2000 },
    { INVENTORY_DOCUMENT,  0x88, DOC_MAGIC_SCROLL_8,  6000 },
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
    SPELL_WOLF_CHARGE,
    SPELL_WING_SMASH,
    SPELL_SWORD_BROTHERS,
    // clang-format on
};

static u16 D_us_8018151C[] = {0, 1, 2, 3, 5};

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

void func_us_801B0FBC(const char* str, u16 x, u16 y);

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
    for (i = 0; i < LEN(D_us_8018134C) - 1U; i++) {
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

static u16 D_us_80181530[] = {
    -0x012, -0x022, -0x00A, -0x022, -0x012, -0x01A, -0x00A, -0x01A, -0x02E,
    0x01A,  -0x026, 0x01A,  -0x01E, 0x01A,  -0x016, 0x01A,  -0x006, 0x01A,
    0x002,  0x01A,  0x00A,  0x01A,  0x012,  0x01A,  0x01A,  0x01A,  0x022,
    0x01A,  0x02A,  0x01A,  0x032,  0x01A,  0x032,  0x01A,  0x032,  0x01A,
    -0x016, 0x010,  -0x00E, 0x010,  -0x006, 0x010,  0x002,  0x010,  0x00A,
    0x010,  0x012,  0x010,  0x01A,  0x010,  0x022,  0x010,  0x02A,  0x010,
    0x032,  0x010,  0x002,  -0x022, 0x00A,  -0x022, 0x012,  -0x022, 0x01A,
    -0x023, 0x022,  -0x022, 0x02A,  -0x022, 0x032,  -0x022, 0x002,  -0x01A,
    0x00A,  -0x01A, 0x012,  -0x01A, 0x01A,  -0x01B, 0x022,  -0x01A, 0x02A,
    -0x01A, 0x032,  -0x01A, 0x002,  -0x00E, 0x00A,  -0x00E, 0x012,  -0x00E,
    0x01A,  -0x00F, 0x022,  -0x00E, 0x02A,  -0x00E, 0x032,  -0x00E, -0x036,
    -0x002, -0x02E, -0x002, -0x026, -0x002, -0x01A, -0x002, -0x012, -0x002,
    -0x00A, -0x002, 0x006,  -0x002, 0x00E,  -0x002, 0x016,  -0x002, 0x022,
    -0x002, 0x02A,  -0x002, 0x032,  -0x002, -0x036, 0x006,  -0x02E, 0x006,
    -0x026, 0x006,  -0x01A, 0x006,  -0x012, 0x006,  -0x00A, 0x006,  0x006,
    0x006,  0x00E,  0x006,  0x016,  0x006,  0x022,  0x006,  0x02A,  0x006,
    0x032,  0x006};

static s16 D_psp_092A49B8[] = {
    0x0002, 0xFFDE, 0x000A, 0xFFDE, 0x0012, 0xFFDE, 0x001A, 0xFFDD, 0x0022,
    0xFFDE, 0x002A, 0xFFDE, 0x0032, 0xFFDE, 0x0002, 0xFFE6, 0x000A, 0xFFE6,
    0x0012, 0xFFE6, 0x001A, 0xFFE5, 0x0022, 0xFFE6, 0x002A, 0xFFE6, 0x0032,
    0xFFE6, 0x0002, 0xFFF2, 0x000A, 0xFFF2, 0x0012, 0xFFF2, 0x001A, 0xFFF1,
    0x0022, 0xFFF2, 0x002A, 0xFFF2, 0x0032, 0xFFF2, 0x0000, 0x0000};

static s16 D_psp_092A4A10[] = {
    0xFFCA, 0xFFFE, 0xFFD2, 0xFFFE, 0xFFDA, 0xFFFE, 0xFFE6, 0xFFFE,
    0xFFEE, 0xFFFE, 0xFFF6, 0xFFFE, 0x0006, 0xFFFE, 0x000E, 0xFFFE,
    0x0016, 0xFFFE, 0x0022, 0xFFFE, 0x002A, 0xFFFE, 0x0032, 0xFFFE,
    0xFFCA, 0x0006, 0xFFD2, 0x0006, 0xFFDA, 0x0006, 0xFFE6, 0x0006,
    0xFFEE, 0x0006, 0xFFF6, 0x0006, 0x0006, 0x0006, 0x000E, 0x0006,
    0x0016, 0x0006, 0x0022, 0x0006, 0x002A, 0x0006, 0x0032, 0x0006};

static char D_us_80181658[] = {
    SQUARE, CIRCLE, CROSS, TRIANGLE, CH('L'), CH('R'), CH('L'), CH('R')};

static u16 D_psp_092A4A78[] = {
    0xFFE4, 0x0010, 0xFFEC, 0x0010, 0xFFF4, 0x0010, 0xFFFC, 0x0010};

static s16 D_psp_092A4A88[] = {4, 16, 12, 16, 20, 16, 20, 8, 36, 16, 44, 16};

static u16 D_psp_092A4AA0[] = {
    0xFFD8, 0x0010, 0xFFEC, 0x0010, 0xFFEC, 0x0008, 0xFFF4, 0x0010,
    0xFFFC, 0x0010, 0x0004, 0x0010, 0x000C, 0x0010, 0x0014, 0x0010,
    0x001C, 0x0010, 0x0024, 0x0010, 0xFFD4, 0x0010, 0xFFF4, 0x0010,
    0xFFFC, 0x0010, 0x0004, 0x0010, 0x000C, 0x0010, 0x0014, 0x0010,
    0x0024, 0x0010, 0x002C, 0x0010, 0x002C, 0x0010, 0x002C, 0x0010};

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

void func_psp_09264E08(void) { D_psp_092A5D38 = &g_Pix[0][0x2000]; }

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

void func_us_801B56E4(Entity* self) {
    Entity* tempEntity;
    s32 primIndex;
    s32 i, j;
    ShopItem* shopItem;
    DRAWENV drawEnv;
    DR_ENV* dr_env;
    RECT clipRect = {.x = 0, .y = 0x100, .w = 0x100, .h = 0x100};
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
    {0, MARIA_TACTICS,              3000},
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

    RECT clipRect = {.x = 0, .y = 0x100, .w = 0x100, .h = 0x100};
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

static char D_us_8018180C[] = _S("-------------");

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

    RECT clipRect = {.x = 0, .y = 0x100, .w = 0x100, .h = 0x100};
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
            } else if (self->ext.et_801B6F30.unk82 < 0x43) {
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
            } else if (self->ext.et_801B6F30.unk82 < 0x43) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82 += 7;
                if (self->ext.et_801B6F30.unk82 > 0x43) {
                    self->ext.et_801B6F30.unk82 = 0x43;
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
        if (self->ext.et_801B6F30.unk82 < 0x43) {
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

static u16 D_us_801818A8[] = {
    ELEMENT_HOLY,  ELEMENT_DARK,  ELEMENT_FIRE,  ELEMENT_THUNDER,
    ELEMENT_ICE,   ELEMENT_WATER, ELEMENT_STONE, ELEMENT_POISON,
    ELEMENT_CURSE, ELEMENT_CUT,   ELEMENT_HIT};

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

Primitive* func_us_801B7D10(Primitive* prim, u16 arg1, s16 posX, s16 posY);

void func_us_801B7DF8(Primitive* prim, Entity* arg1, s16 enemyId) {
    s16 posX, posY;
    s32 i;
    EnemyDef* enemyDef;
    u8 params;
    s32 strLen;
    s32 xOffset;

    xOffset = 12;
    enemyDef = &g_api.enemyDefs[enemyId];
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;
    posX = 0x14;
    posY = 0x2C;
    prim = func_us_801B1064(prim, posX, posY, enemyDef->name, 0x196);
    posX = 0xB4;
    posY = 0x2C;
    func_us_801B3FB4(prim, D_us_801818C0[5], 3, 1); // "No."
    for (i = 0; i < 3; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = posY;
        prim = prim->next;
        posX += 8;
    }
    func_us_801B3EC8(prim, arg1->params + 1, 3);
    for (i = 0; i < 3; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = posY;
        prim = prim->next;
        posX += 8;
    }
    posX = 0x18;
    posY = 0x38;
    func_us_801B3FB4(prim, D_us_801818C0[0], 2, 1); // "Strong VS."
    for (i = 0; i < 2; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = posY;
        prim = prim->next;
        posX += 8;
    }
    posX += 2;
    if (arg1->params) {
        func_us_801B3EC8(prim, enemyDef->level, 2);
    } else {
        func_us_801B3FB4(prim, D_us_801818C0[6], 2, 1); // "??"
    }
    for (i = 0; i < 2; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = posY;
        if (prim->drawMode != DRAW_HIDE) {
            posX += 8;
        }
        prim = prim->next;
    }
    posX = 0x40;
    posY = 0x38;
    func_us_801B3FB4(prim, D_us_801818C0[1], 2, 1); // "HP"
    for (i = 0; i < 2; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = posY;
        prim = prim->next;
        posX += 8;
    }
    posX += 2;
    if (enemyDef->hitPoints > 9999) {
        func_us_801B3FB4(prim, D_us_801818F0[0], 4, 1); // "????"
    } else {
        func_us_801B3EC8(prim, enemyDef->hitPoints, 4);
    }
    for (i = 0; i < 4; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = posY;
        if (prim->drawMode != DRAW_HIDE) {
            posX += 8;
        }
        prim = prim->next;
    }
    posX = 0x84;
    posY = 0xA4;
    func_us_801B3FB4(prim, D_us_801818C0[3], 3, 1); // "Exp"
    for (i = 0; i < 3; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = posY;
        prim = prim->next;
        posX += 8;
    }
    func_us_801B3EC8(prim, enemyDef->exp, 4);
    for (i = 0; i < 4; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = posY;
        prim = prim->next;
        posX += 8;
    }
    posX = 0x84;
    posY = 0x7C;
    strLen = 0x14;
    func_us_801B3FB4(prim, D_us_801818C0[4], strLen, 1); // "Drop Items"
    for (i = 0; i < strLen; i++) {
        prim->clut = 0x196;
        prim->x0 = posX - xOffset;
        prim->y0 = posY;
        prim = prim->next;
        posX += 8;
    }
    posX = 0x88;
    posY = 0x88;
    prim = func_us_801B1064(prim, posX - xOffset, posY,
                            func_us_801B7C94(enemyDef->uncommonItemId), 0x196);
    posX = 0x88;
    posY = 0x94;
    params = arg1->params;
    if ((g_CastleFlags[(params >> 3) + ENEMY_LIST_RAREDROP_1B0] &
         (1 << (params & 7))) ||
        !enemyDef->rareItemId) {
        prim = func_us_801B1064(prim, posX - xOffset, posY,
                                func_us_801B7C94(enemyDef->rareItemId), 0x196);
    } else {
        prim = func_us_801B1064(
            prim, posX - xOffset, posY, D_us_801818EC[0], 0x196); // "????????"
    }
    for (i = 0; i < 4; i++) {
        prim = func_us_801B1064(
            prim, 0x84 - xOffset, (i * 0x10) + 0x3C, D_psp_092A5F98[i], 0x196);
    }
    prim = func_us_801B7D10(prim, enemyDef->strengths, 0x8C - xOffset, 0x44);
    prim = func_us_801B7D10(prim, enemyDef->immunes, 0x8C - xOffset, 0x54);
    prim = func_us_801B7D10(prim, enemyDef->weaknesses, 0x8C - xOffset, 0x64);
    prim = func_us_801B7D10(prim, enemyDef->absorbs, 0x8C - xOffset, 0x74);
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

u8* func_psp_09269FF0(char* str, u8* pix, s16 x, s16 y) {
    u16 ch;
    s32 i;
    u16* chPix;
    u16* dst;

loop:
    ch = *str++;
    if (ch) {
        ch <<= 8;
        ch |= *str++;
        chPix = g_api.func_80106A28(ch, 1);
        if (chPix != NULL) {
            dst = (u16*)pix;
            for (i = 0; i < 0x30; i++) {
                *dst++ = *chPix++;
            }
            LoadTPage((u_long*)pix, 0, 0, x, y, 12, 16);
            x += 3;
            pix += 0x60;
        }
        goto loop;
    }
    return pix;
}

Primitive* func_us_801B7D10(Primitive* prim, u16 arg1, s16 posX, s16 posY) {
    s32 x = posX;
    s16 y = 8;
    s32 i;
    if ((arg1 & ELEMENT_ALL) == 0) {
        prim = func_us_801B1064(prim, posX, posY, D_psp_092A5F88, 0x196);
    } else {
        for (i = 0; i < LEN(D_us_801818A8); i++) {
            if (arg1 & D_us_801818A8[i]) {
                prim = func_us_801B1064(prim, x, posY, D_us_8018187C[i], 0x196);
                x += 0x20;
            }
        }
    }
    return prim;
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

// these strings are incompatible with the psp character map
#ifdef VERSION_PSP
static char* D_psp_092A4CA8[] = {
    "\xB5\xB7\xB1\xD5\x00\xD8\xAE\xB3\xC0\xDB\xB3\xFF",
    "\xD4\xC5\xC0\xFF\x9E\x00\xB7\xD6\xD5\xB7\xFF",
    "\xD6\xBA\xD4\xCF\x00\xC1\xBB\xFF",
    "\xDC\xB6\xD3\xC4\x00\xC9\xD8\xB5\xFF",
    "\xCC\xB6\xD0\x00\xD8\xB6\xFF",
    "\xBB\xC4\xB3\x00\xCF\xBB\xCA\xD9\xFF",
    "\xBC\xB2\xC5\x00\xCD\xB7\xD9\xFF",
    "\xD4\xC5\xD0\x00\xBC\xFF\x9E\xAE\xB3\xBC\xFF\x9E\xFF"};
#else
static char* D_psp_092A4CA8[] = {
    _S("おきあゆ りょうたろう"), // Okiayu Ryoutarou
    _S("やなだ きよゆき"),       // Yanada Kiyoyuki
    _S("よこやま ちさ"),         // Yokoyama Chisa
    _S("わかもと のりお"),       // Wakamoto Norio
    _S("ふかみ りか"),           // Fukami Rika
    _S("さとう まさはる"),       // Satou Masaharu
    _S("しいな へきる"),         // Shiina Hekiru
    _S("やなみ じょうじ")        // Yanami Jyouji
};
#endif

static char D_psp_092A4CC8[] =
    "平成７年８月に収録されたものです。"; // It was recorded in August of 1995

static u16 D_psp_092A4CF0[] = {
    // clang-format off
    JP_VO_OKIAYU_RYOUTAROU_MESSAGE,
    JP_VO_YANADA_KIYOYUKI_MESSAGE,
    JP_VO_YOKOYAMA_CHISA_MESSAGE,
    JP_VO_WAKAMOTO_NORIO_MESSAGE,
    JP_VO_FUKAMI_RIKA_MESSAGE,
    JP_VO_SATOU_MASAHARU_MESSAGE,
    JP_VO_SHIINA_HEKIRU_MESSAGE,
    JP_VO_YANAMI_JYOUJI_MESSAGE
    // clang-format on
};

void func_psp_0926ADD8(Primitive* prim, Entity* self) {
    s16 x, y;
    s32 i;

    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;
    y = 0x24;
    for (i = 0; i < 8; i++) {
        if ((i & 1) == 0) {
            x = 0x10;
            y += 0xC;
        } else {
            x = 0x80;
        }
        prim = func_us_801B1064(prim, x, y, D_psp_092A4CA8[i], 0x196);
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_psp_0926AED0(Entity* self) {
    DRAWENV drawEnv;
    DR_ENV* dr_env;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    u16 pads;
    s16 sfxIndex;
    u8* pix;

    RECT clipRect = {.x = 0, .y = 0x100, .w = 0x100, .h = 0x100};
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
                g_api.PlaySfx(D_psp_092A4CF0[sfxIndex]);
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
                g_api.PlaySfx(D_psp_092A4CF0[sfxIndex]);
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

static u16 D_us_80181978[] = {
    MU_PROLOGUE,
    MU_DANCE_OF_ILLUSIONS,
    MU_PRAYER,
    MU_DRACULAS_CASTLE,
    MU_DANCE_OF_GOLD,
    MU_MARBLE_GALLERY,
    MU_TOWER_OF_MIST,
    MU_NOCTURNE,
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
    MU_FINAL_TOCATTA,
    MU_BLACK_BANQUET,
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

    RECT clipRect = {.x = 0, .y = 0x100, .w = 0x100, .h = 0x100};
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x140);
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->ext.et_801B6F30.unk86 = 0;
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
                    prim->tpage = 0x110;
                    prim->u0 = prim->u2 = (i - 8) * 0x74 + 4;
                    prim->u1 = prim->u3 = prim->u0 + 0x74;
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
                    PRED(prim) = 0;
                    PGRN(prim) = 0x20;
                    PBLU(prim) = 0x40;
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
                        drawEnv.ofs[0] = 0;
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
        }
        break;

    case 1:
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
                         self->ext.et_801B6F30.unk7C * 2, 0x78, 0x20, 7, 1);
        for (i = 0; i < 15; i++) {
            prim = prim->next;
        }
        func_us_801B8958(prim, self);
        if (self->ext.et_801B6F30.unk7C == 0x10) {
            g_api.PlaySfx(SET_STOP_SEQ);
            SetStep(3);
        }
        break;

    case 3:
        pads = g_pads[0].repeat;
        if (pads & PAD_DOWN) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80++;
            } else if (self->ext.et_801B6F30.unk82 < 0x17) {
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
            } else if (self->ext.et_801B6F30.unk82 < 0x17) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82 += 7;
                if (self->ext.et_801B6F30.unk82 > 0x17) {
                    self->ext.et_801B6F30.unk82 = 0x17;
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
        pads = g_pads[0].tapped;
        if (pads & D_psp_08B42050) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            SetStep(4);
        } else if (pads & D_psp_08B42054) {
            SetStep(6);
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 10; i++) {
            prim = prim->next;
        }
        prim->x0 = prim->x2 = 0x11;
        prim->x1 = prim->x3 = 0xEF;
        prim->y0 = prim->y1 = self->ext.et_801B6F30.unk80 * 12 + 0x1E;
        prim->y2 = prim->y3 = prim->y0 + 12;
        prim->drawMode = DRAW_COLORS;
        prim = prim->next;
        if (self->ext.et_801B6F30.unk82) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        if (self->ext.et_801B6F30.unk82 < 0x17) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        prim = prim->next;
        prim = prim->next;
        func_us_801B8958(prim, self);
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            g_api.PlaySfx(SET_STOP_MUSIC);
            self->ext.et_801B6F30.unk86 = 1;
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

    case 6:
        g_api.PlaySfx(SET_STOP_MUSIC);
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
                         self->ext.et_801B6F30.unk7C * 2, 0x78, 0x20, 7, 1);
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
        if (self->ext.et_801B6F30.unk86) {
            g_api.PlaySfx(0x302);
        }
        DestroyEntity(self);
        return;
    }
}
