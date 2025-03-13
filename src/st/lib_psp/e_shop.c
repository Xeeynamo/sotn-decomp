// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../lib/lib.h"

typedef struct {
    /* 0x0 */ u16 category;
    /* 0x2 */ u16 itemId;
    /* 0x4 */ u32 price;
} ShopItem;

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

extern char* D_psp_0929A320[] = {
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
    "Cadﾌveres frescos.",
    "Murciﾑlagos vampiros.",
    "Lobos que protegen la",
    "Esqueleto animado por magia.",
    "\"Criatura\" legendaria.",
    "Esqueleto de 4 patas.",
    "Feroz esqueleto",
    "Tritﾚn que escupe bolas de",
    "Caballero de hacha de",
    "Esqueleto que lanza huesos.",
    "Soldados de Iglesia Oriental",
    "Planta con hojas",
    "Mesa de ouija poseﾕda.",
    "Esqueleto con bumerﾌn.",
    "Demonio volador que escupe",
    "Fantasmas llameantes de",
    "Demonio con lanza encantada.",
    "Tﾕtere demonﾕaco del Infierno.",
    "Bestia nauseabunda de dos",
    "De pelo de Medusa.",
    "Extraﾘa criatura que parece",
    "Esqueletos equipados",
    "Novato del combate con",
    "Caballero con sﾚlida armadura",
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
    "Libro de hechizos bﾌsicos.",
    "Bﾝho de granja local mutado",
    "Columna hecha con calaveras",
    "Caballero armado con",
    "Manifestaciones fﾕsicas de",
    "Sapo agrandado mﾌgicamente",
    "Guerrero muerto viviente",
    "Guardia con armadura.",
    "Esqueleto sin cabeza.",
    "Rana que habita en cuevas.",
    "Espﾕritu femenino con hielo.",
    "Espﾕritu de calavera gigante.",
    "Libro de armas antiguas.",
    "Esqueleto equipado con",
    "Hombre pulga a lomos de un",
    "Cuervo que come carne.",
    "Espﾕritu de cuervo azul",
    "Espada de demonio malvado.",
    "Planta con hojas",
    "Monstruo mitolﾚgico marino.",
    "Esqueleto con naginata.",
    "El Seﾘor de la espada porta",
    "Caballero con sﾚlida armadura.",
    "Espﾕritu de cazadora",
    "Gﾚlem de barro animado.",
    "Espada de demonio malvado.",
    "Hombre pulga armado con",
    "Monstruo gelatinoso.",
    "Esqueleto gigante.",
    "Mezcla de caballo, leﾚn y",
    "Maestro del combate con",
    "Hombre esqueleto pantera.",
    "Mitad hombre, mitad lobo.",
    "Sepulturero. Maestro del",
    "Criatura con cabeza de mujer",
    "Mitad hombre, mitad toro.",
    "Gremlin piromanﾕaco.",
    "Sanguinario caballero muerto",
    "Relicario de calavera llevado",
    "Brujas fantasma de Sﾌlem.",
    "Busca entre las tumbas y",
    "Guardiﾌn con cabeza de pez.",
    "Espadachﾕn misterioso",
    "Demonio pequeﾘo con magia.",
    "Hermano gigante.",
    "Hermano gigante.",
    "Hermano gigante mayor.",
    "Monstruo creado con una",
    "Caballero con armadura",
    "Seﾘor de los cuervos",
    "Demonio que lleva un trueno.",
    "Perro guardiﾌn del Infierno.",
    "Regada con sangre humana.",
    "Vampiro con magia. Domina",
    "Cabeza de pez de maestro.",
    "Lﾌpidas poseﾕdas por espﾕritus",
    "Mujer demonio. Invade",
    "Hombre empalado buscando",
    "El leﾚn cobarde.",
    "Monstruo llamado  schmoo ．",
    "Hombre de hojalata",
    "Criatura terrorﾕfica.",
    "Esqueleto que busca",
    "Contiene infinitas semillas",
    "Caballero con armadura que",
    "Zombis que atacan incluso",
    "Experto en lanzar armas.",
    "Insecto mutado.",
    "Arquero diabﾚlicamente",
    "Licﾌntropo que cambia",
    "Wyrm controlado por Hombre",
    "Lleva una temible arma",
    "Criatura lﾕquida. Adopta",
    "Esqueleto animado con",
    "Dragﾚn blanco montado",
    "Monstruo con cabeza de toro.",
    "Murciﾑlago vampiro gigante.",
    "Arquero ﾌngel.",
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
    "Mamﾌ en el antiguo Egipto.",
    "Mujer demonio con cabeza de",
    "Pequeﾘo demonio malicioso.",
    "Zombi que se hace pasar",
    "Zombi que se hace pasar",
    "Zombi que se hace pasar",
    "Beelzebub, el Seﾘor de las",
    "Bruja joven.",
    "Ejecutor del Infierno.",
    "Espﾕritu de hielo andrﾚgino.",
    "Cazavampiros. Usa 4 bestias",
    "Maestro cazavampiros.",
    "Pﾌjaro raro.",
    "Ser mﾌgico con planes de",
    "Caballero de armadura de",
    "Amiga ﾕntima de Dracula.",
    "Sacerdote oscuro de Dracula.",
    "Seﾘor de Wallachia."};

static char* D_psp_0929BFF0[] = {
    "en １７９２ （hace ５ aﾘos）.",
    "empapados de sangre.",
    "indestructible.",
    "Animados por magia.",
    "Temidos como siervos del mal.",
    "entrada al castillo.",
    "",
    "Ataca a todos los invasores.",
    "Le caen gotas de veneno.",
    "espadachﾕn.",
    "fuego. El mﾌs grande.",
    "nivel bajo.",
    "",
    "enviados hace ３００ aﾘos．",
    "afiladas.",
    "",
    "",
    "fuego.",
    "nivel bajo.",
    "",
    "",
    "cabezas. ｳCuﾌl es la cabeza?",
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
    "de dragﾚn blanqueadas.",
    "una gran espada.",
    "almas sin cuerpo atormentadas.",
    "por un bautismo demonﾕaco.",
    "con sﾚlida armadura.",
    "Fuerte en ﾌreas peligrosas.",
    "Lleva una ropera.",
    "",
    "",
    "",
    "",
    "mayal de hierro con pinchos.",
    "ganso de guerra entrenado.",
    "",
    "que lleva tiempo muerto.",
    "Causa fenﾚmenos poltergeist.",
    "afiladas.",
    "",
    "",
    "una espada hasta desterrado.",
    "Ataca con bﾝho entrenado.",
    "invisible.",
    "",
    "Causa fenﾚmenos poltergeist.",
    "hacha y escudo.",
    "",
    "",
    "ﾌguila.",
    "dos espadas.",
    "",
    "",
    "combate sin armas.",
    "y cuerpo de pﾌjaro.",
    "",
    "",
    "viviente que ansﾕa luchar.",
    "por los sacerdotes esqueletos.",
    "",
    "conoce muchas tradiciones.",
    "",
    "con capa.",
    "Invoca a aliados demonﾕacos.",
    "Lleva un cuchillo gurkha.",
    "Usa un gran martillo de acero.",
    "Lleva dos dagas enormes.",
    "viscosa sustancia gelatinosa.",
    "que lleva un disco.",
    "demonﾕaco.",
    "Llamado  Mﾝsico del Infierno ．",
    "",
    "",
    "la parte alta del castillo.",
    "",
    "malvados de los muertos.",
    "los sueﾘos de los hombres.",
    "sesos.",
    "",
    "",
    "sin corazﾚn.",
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
    "dragﾚn enorme.",
    "por un Hombre pulga.",
    "",
    "",
    "Matﾚ al godo Amalarico.",
    "bolas de fuego.",
    "Causa fenﾚmenos poltergeist.",
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

static char D_psp_0929C240[] = "Distrutto da Richter";
static char D_psp_0929C258[] = "Rivive bagnando le ossa";
static char D_psp_0929C270[] = "Durissimo teschio rotante.";
static char D_psp_0929C290[] = "Corpi freschi.";
static char D_psp_0929C2A0[] = "Pipistrelli vampiri.";
static char D_psp_0929C2B8[] = "Lupi a guardia dell'entrata";
static char D_psp_0929C2D8[] = "Scheletro animato magicamente.";
static char D_psp_0929C2F8[] = "Creatura leggendaria.";
static char D_psp_0929C310[] = "Scheletro a quattro zampe.";
static char D_psp_0929C330[] = "Feroce scheletro";
static char D_psp_0929C348[] = "Tritone sputa-fuoco.";
static char D_psp_0929C360[] = "Asciere di basso livello.";
static char D_psp_0929C380[] = "Scheletro lancia-ossa.";
static char D_psp_0929C398[] = "Soldati della Chiesa Orientale";
static char D_psp_0929C3B8[] = "Pianta con foglie affilate";
static char D_psp_0929C3D8[] = "Tavola Ouija posseduta.";
static char D_psp_0929C3F0[] = "Scheletro armato di boomerang.";
static char D_psp_0929C410[] = "Demone volante sputa-fuoco.";
static char D_psp_0929C430[] = "Spettri di fuoco minori. ";
static char D_psp_0929C450[] = "Demone con lancia incantata.";
static char D_psp_0929C470[] = "Demoniaco burattino infernale.";
static char D_psp_0929C490[] = "Nauseabonda bestia a due";
static char D_psp_0929C4B0[] = "Dai capelli di Medusa.";
static char D_psp_0929C4C8[] = "Strana creatura antropomorfa.";
static char D_psp_0929C4E8[] = "Scheletri armati di";
static char D_psp_0929C500[] = "Un pivello del combattimento";
static char D_psp_0929C520[] = "Cavaliere con pesante armatura";
static char D_psp_0929C540[] = "Pianta mutata.";
static char D_psp_0929C550[] = "Asciere ben armato.";
static char D_psp_0929C568[] = "Demone di fuoco e ghiaccio.";
static char D_psp_0929C588[] = "Scheletro arciere armato";
static char D_psp_0929C5A8[] = "Guerriero armato";
static char D_psp_0929C5C0[] = "Serpente parassita di Scilla.";
static char D_psp_0929C5E0[] = "Scheletro di scimmia animato.";
static char D_psp_0929C600[] = "Demone mutaforma.";
static char D_psp_0929C618[] = "Testa di soldato giustiziato.";
static char D_psp_0929C638[] = "Scheletro guerriero volante.";
static char D_psp_0929C658[] = "Libro di incantesimi di base.";
static char D_psp_0929C678[] = "Gufo del cortile locale";
static char D_psp_0929C690[] = "Pilastro ricavato da un";
static char D_psp_0929C6A8[] = "Guerriero armato con";
static char D_psp_0929C6C0[] = "Manifestazioni fisiche di";
static char D_psp_0929C6E0[] = "Rospo magicamente ingrandito";
static char D_psp_0929C700[] = "Guerriero non morto";
static char D_psp_0929C718[] = "Guardia con armatura.";
static char D_psp_0929C730[] = "Scheletro senza testa armato";
static char D_psp_0929C750[] = "Rana che vive nelle grotte.";
static char D_psp_0929C770[] = "Spirito femminile del gelo.";
static char D_psp_0929C790[] = "Gigantesco spirito teschio.";
static char D_psp_0929C7B0[] = "Libro delle armi antiche.";
static char D_psp_0929C7D0[] = "Scheletro armato di mazza";
static char D_psp_0929C7F0[] = "Uomo-Pulce che cavalca";
static char D_psp_0929C808[] = "Corvo carnivoro.";
static char D_psp_0929C820[] = "Spirito di un corvo blu";
static char D_psp_0929C838[] = "Maligna spada demoniaca.";
static char D_psp_0929C858[] = "Mitologico mostro marino.";
static char D_psp_0929C878[] = "Scheletro armato di naginata.";
static char D_psp_0929C898[] = "Spadaccino che rimane";
static char D_psp_0929C8B0[] = "Cavaliere con pesante armatura.";
static char D_psp_0929C8D0[] = "Invisib. spirito di cacciatr.";
static char D_psp_0929C8F0[] = "Golem di fango animato.";
static char D_psp_0929C908[] = "Uomo-Pulce armato con";
static char D_psp_0929C920[] = "Mostro fatto di gelatina.";
static char D_psp_0929C940[] = "Scheletro gigante.";
static char D_psp_0929C958[] = "Cavallo, leone e aquila.";
static char D_psp_0929C978[] = "Maestro del combattimento";
static char D_psp_0929C998[] = "Scheletro di pantera mannara.";
static char D_psp_0929C9B8[] = "Metﾋ uomo e metﾋ lupo.";
static char D_psp_0929C9D0[] = "Camposantiere. Maestro del";
static char D_psp_0929C9F0[] = "Creatura con testa di";
static char D_psp_0929CA08[] = "Metﾋ uomo e metﾋ toro.";
static char D_psp_0929CA20[] = "Gremlin piromane.";
static char D_psp_0929CA38[] = "Guerriero non morto assetato";
static char D_psp_0929CA58[] = "Sacrario di teschio portato";
static char D_psp_0929CA78[] = "Streghe fantasma di Salem．";
static char D_psp_0929CA98[] = "Cerca tra le tombe ed ﾐ";
static char D_psp_0929CAB0[] = "Guardiano con testa di pesce.";
static char D_psp_0929CAD0[] = "Misterioso spadaccino";
static char D_psp_0929CAE8[] = "Piccolo demone magico.";
static char D_psp_0929CB00[] = "Fratello Gigante.";
static char D_psp_0929CB18[] = "Primo dei fratelli Giganti.";
static char D_psp_0929CB38[] = "Mostro fatto di viscida ";
static char D_psp_0929CB58[] = "Cavaliere in armatura ";
static char D_psp_0929CB70[] = "Demoniaco signore dei corvi.";
static char D_psp_0929CB90[] = "Demone armato di lampo.";
static char D_psp_0929CBA8[] = "Cane da guardia degli Inferi.";
static char D_psp_0929CBC8[] = "Innaffiata con sangue umano.";
static char D_psp_0929CBE8[] = "Vampiro magico. Governa";
static char D_psp_0929CC00[] = "Un pesce grosso.";
static char D_psp_0929CC18[] = "Lapidi possedute dagli";
static char D_psp_0929CC30[] = "Demone femmina.";
static char D_psp_0929CC40[] = "Uomo impalato a caccia";
static char D_psp_0929CC58[] = "Il leone codardo.";
static char D_psp_0929CC70[] = "Mostro chiamato schmoo ．";
static char D_psp_0929CC90[] = "Uomo di latta senza cuore.";
static char D_psp_0929CCB0[] = "Creatura da incubo.";
static char D_psp_0929CCC8[] = "Scheletro che rincorre sempre";
static char D_psp_0929CCE8[] = "Contiene infiniti semi velenosi.";
static char D_psp_0929CD10[] = "Zombie che attacca";
static char D_psp_0929CD28[] = "Esperto di armi da lancio.";
static char D_psp_0929CD48[] = "Insetto mutato.";
static char D_psp_0929CD58[] = "Arciere micidialmente preciso.";
static char D_psp_0929CD78[] = "Licantropo mutaforma.";
static char D_psp_0929CD90[] = "Wyrm controllato dall'Uomo-Pulce.";
static char D_psp_0929CDB8[] = "ｹ armato di una temibile";
static char D_psp_0929CDD8[] = "Creatura liquida.";
static char D_psp_0929CDF0[] = "Scheletro animato di un";
static char D_psp_0929CE08[] = "Drago bianco cavalcato ";
static char D_psp_0929CE20[] = "Mostro con testa di toro.";
static char D_psp_0929CE40[] = "Pipistrello vampiro gigante.";
static char D_psp_0929CE60[] = "Angelo arciere.";
static char D_psp_0929CE70[] = "Lupo che sputa palle di fuoco.";
static char D_psp_0929CE90[] = "Scheletro con attacco con salto.";
static char D_psp_0929CEB8[] = "Scheletro che cavalca un Warg.";
static char D_psp_0929CED8[] = "Malvagio polpo mutato.";
static char D_psp_0929CEF0[] = "Bestia da guerra corazzata.";
static char D_psp_0929CF10[] = "Tutto istinto, poco cervello.";
static char D_psp_0929CF30[] = "Demone del fuoco.";
static char D_psp_0929CF48[] = "Orribile demone infernale.";
static char D_psp_0929CF68[] = "Fatto di parti del corpo";
static char D_psp_0929CF88[] = "Erba Venere avanzata.";
static char D_psp_0929CFA0[] = "Mummia dell'antico Egitto.";
static char D_psp_0929CFC0[] = "Demone con testa di serpente.";
static char D_psp_0929CFE0[] = "Piccolo demone malizioso.";
static char D_psp_0929D000[] = "Zombie che impersona Grant．";
static char D_psp_0929D020[] = "Zombie che impersona Trevor．";
static char D_psp_0929D040[] = "Zombie che impersona Sypha．";
static char D_psp_0929D060[] = "Belzebｦ, Signore delle Mosche．";
static char D_psp_0929D080[] = "Giovane strega.";
static char D_psp_0929D090[] = "Boia infernale.";
static char D_psp_0929D0A0[] = "Spirito di ghiaccio androgino.";
static char D_psp_0929D0C0[] = "Cacciatrice di vampiri. Usa 4";
static char D_psp_0929D0E0[] = "Esperto cacciatore di vampiri.";
static char D_psp_0929D100[] = "Uccello raro.";
static char D_psp_0929D110[] = "Creatura magica che intende";
static char D_psp_0929D130[] = "ArmaDuro di alto livello.";
static char D_psp_0929D150[] = "Intimo amico di Dracula.";
static char D_psp_0929D170[] = "Il prete oscuro di Dracula.";
static char D_psp_0929D190[] = "Signore della Valacchia．";
static char* D_psp_0929D1B0[] = {
    D_psp_0929C240, D_psp_0929C258, D_psp_0929C270, D_psp_0929C290,
    D_psp_0929C2A0, D_psp_0929C2B8, D_psp_0929C2D8, D_psp_0929C2F8,
    D_psp_0929C310, D_psp_0929C330, D_psp_0929C348, D_psp_0929C360,
    D_psp_0929C380, D_psp_0929C398, D_psp_0929C3B8, D_psp_0929C3D8,
    D_psp_0929C3F0, D_psp_0929C410, D_psp_0929C430, D_psp_0929C450,
    D_psp_0929C470, D_psp_0929C490, D_psp_0929C4B0, D_psp_0929C4C8,
    D_psp_0929C4E8, D_psp_0929C500, D_psp_0929C520, D_psp_0929C4B0,
    D_psp_0929C540, D_psp_0929C550, D_psp_0929C568, D_psp_0929C588,
    D_psp_0929C5A8, D_psp_0929C5C0, D_psp_0929C5E0, D_psp_0929C600,
    D_psp_0929C618, D_psp_0929C638, D_psp_0929C658, D_psp_0929C678,
    D_psp_0929C690, D_psp_0929C6A8, D_psp_0929C6C0, D_psp_0929C6E0,
    D_psp_0929C700, D_psp_0929C718, D_psp_0929C730, D_psp_0929C750,
    D_psp_0929C770, D_psp_0929C790, D_psp_0929C7B0, D_psp_0929C7D0,
    D_psp_0929C7F0, D_psp_0929C808, D_psp_0929C820, D_psp_0929C838,
    D_psp_0929C3B8, D_psp_0929C858, D_psp_0929C878, D_psp_0929C898,
    D_psp_0929C8B0, D_psp_0929C8D0, D_psp_0929C8F0, D_psp_0929C838,
    D_psp_0929C908, D_psp_0929C920, D_psp_0929C940, D_psp_0929C958,
    D_psp_0929C978, D_psp_0929C998, D_psp_0929C9B8, D_psp_0929C9D0,
    D_psp_0929C9F0, D_psp_0929CA08, D_psp_0929CA20, D_psp_0929CA38,
    D_psp_0929CA58, D_psp_0929CA78, D_psp_0929CA98, D_psp_0929CAB0,
    D_psp_0929CAD0, D_psp_0929CAE8, D_psp_0929CB00, D_psp_0929CB00,
    D_psp_0929CB18, D_psp_0929CB38, D_psp_0929CB58, D_psp_0929CB70,
    D_psp_0929CB90, D_psp_0929CBA8, D_psp_0929CBC8, D_psp_0929CBE8,
    D_psp_0929CC00, D_psp_0929CC18, D_psp_0929CC30, D_psp_0929CC40,
    D_psp_0929CC58, D_psp_0929CC70, D_psp_0929CC90, D_psp_0929CCB0,
    D_psp_0929CCC8, D_psp_0929CCE8, D_psp_0929CB58, D_psp_0929CD10,
    D_psp_0929CD28, D_psp_0929CD48, D_psp_0929CD58, D_psp_0929CD78,
    D_psp_0929CD90, D_psp_0929CDB8, D_psp_0929CDD8, D_psp_0929CDF0,
    D_psp_0929CE08, D_psp_0929CE20, D_psp_0929CE40, D_psp_0929CE60,
    D_psp_0929CE70, D_psp_0929C838, D_psp_0929CB58, D_psp_0929CE90,
    D_psp_0929CEB8, D_psp_0929CED8, D_psp_0929CEF0, D_psp_0929CF10,
    D_psp_0929CF30, D_psp_0929CF48, D_psp_0929C600, D_psp_0929CF68,
    D_psp_0929CF88, D_psp_0929CFA0, D_psp_0929CFC0, D_psp_0929CFE0,
    D_psp_0929D000, D_psp_0929D020, D_psp_0929D040, D_psp_0929D060,
    D_psp_0929D080, D_psp_0929D090, D_psp_0929D0A0, D_psp_0929D0C0,
    D_psp_0929D0E0, D_psp_0929D100, D_psp_0929D110, D_psp_0929D130,
    D_psp_0929D150, D_psp_0929D170, D_psp_0929D190};

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
    "armato anche quando ﾐ bandito.",
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
    "anche se tagliato a metﾋ.",
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

static char D_psp_0929DE20[] = "Eliminﾑ par Richter ";
static char D_psp_0929DE38[] = "Revit grﾍce ﾋ ses os";
static char D_psp_0929DE50[] = "Crﾍne indestructible tournant";
static char D_psp_0929DE70[] = "Cadavre frais.";
static char D_psp_0929DE80[] = "Chauve-souris vampires.";
static char D_psp_0929DE98[] = "Loups qui gardent l’entrﾑe";
static char D_psp_0929DEB8[] = "Squelette contrﾛlﾑ par";
static char D_psp_0929DED0[] = "\"Crﾑature\" lﾑgendaire.";
static char D_psp_0929DEE8[] = "Squelette ﾋ quatre jambes.";
static char D_psp_0929DF08[] = "Fﾑroce spadassin squelette.";
static char D_psp_0929DF28[] = "Triton cracheur de boules de";
static char D_psp_0929DF48[] = "Chevalier de bas niveau";
static char D_psp_0929DF60[] = "Squelette lanﾏant des os.";
static char D_psp_0929DF80[] = "Soldats de l’Eglise d’Orient";
static char D_psp_0929DFA0[] = "Plante dotﾑe de feuilles";
static char D_psp_0929DFC0[] = "Table ouija possﾑdﾑe.";
static char D_psp_0929DFD8[] = "Squelette maniant";
static char D_psp_0929DFF0[] = "Dﾑmon volant cracheur de feu.";
static char D_psp_0929E010[] = "Fantﾛmes enflammﾑs";
static char D_psp_0929E028[] = "Dﾑmon muni d’une lance";
static char D_psp_0929E040[] = "Poupﾑe dﾑmoniaque venue";
static char D_psp_0929E058[] = "Bﾒte repoussante ﾋ deux tﾒtes.";
static char D_psp_0929E078[] = "Des cheveux de la Mﾑduse.";
static char D_psp_0929E098[] = "Crﾑature ﾑtrange ﾋ forme";
static char D_psp_0929E0B8[] = "Squelettes ﾑquipﾑs";
static char D_psp_0929E0D0[] = "Novice dans le combat";
static char D_psp_0929E0E8[] = "Chevalier avec une lourde";
static char D_psp_0929E108[] = "Plante mutante.";
static char D_psp_0929E118[] = "Dﾑmon du feu et de la glace.";
static char D_psp_0929E138[] = "Archer squelette ﾑquipﾑ";
static char D_psp_0929E150[] = "Guerrier avec une armure";
static char D_psp_0929E170[] = "Serpent rattachﾑ ﾋ Scylla.";
static char D_psp_0929E190[] = "Singe squelette animﾑ.";
static char D_psp_0929E1A8[] = "Dﾑmon capable de changer";
static char D_psp_0929E1C8[] = "Tﾒte de soldat exﾑcutﾑ.";
static char D_psp_0929E1E0[] = "Guerrier squelette volant";
static char D_psp_0929E200[] = "Livre de sortilﾐges";
static char D_psp_0929E218[] = "Hibou de la basse-cour locale";
static char D_psp_0929E238[] = "Pilier construit ﾋ partir d’un";
static char D_psp_0929E258[] = "Chevalier armﾑ d’une";
static char D_psp_0929E270[] = "Manifestation phys. d’une ﾍme";
static char D_psp_0929E290[] = "Crapaud devenu gﾑant suite";
static char D_psp_0929E2B0[] = "Guerrier mort-vivant ﾑquipﾑ";
static char D_psp_0929E2D0[] = "Garde avec une armure. Fort";
static char D_psp_0929E2F0[] = "Squelette sans tﾒte.";
static char D_psp_0929E308[] = "Grenouille vivant dans";
static char D_psp_0929E320[] = "Esprit fﾑminin maniant";
static char D_psp_0929E338[] = "Esprit d’un crﾍne gﾑant.";
static char D_psp_0929E358[] = "Livre sur les armes anciennes.";
static char D_psp_0929E378[] = "Squelette ﾑquipﾑ d’un flﾑau";
static char D_psp_0929E398[] = "Homme-puce chevauchant une";
static char D_psp_0929E3B8[] = "Corbeau dﾑvorant la chair.";
static char D_psp_0929E3D8[] = "Esprit d’un Corbeau bleu";
static char D_psp_0929E3F8[] = "Epﾑe dﾑmon malﾑfique.";
static char D_psp_0929E410[] = "Monstre des mers";
static char D_psp_0929E428[] = "Seigneur maniant une ﾑpﾑe";
static char D_psp_0929E448[] = "Chevalier lourdement protﾑgﾑ.";
static char D_psp_0929E468[] = "Esprit de chasseuse invisible.";
static char D_psp_0929E488[] = "Golem de boue animﾑ.";
static char D_psp_0929E4A0[] = "Homme-puce armﾑ d’une hache";
static char D_psp_0929E4C0[] = "Monstre gluant.";
static char D_psp_0929E4D0[] = "Squelette gﾑant.";
static char D_psp_0929E4E8[] = "Mi-cheval， mi-lion";
static char D_psp_0929E500[] = "Maﾖtre du combat ﾋ";
static char D_psp_0929E518[] = "Squelette de panthﾐre-garou.";
static char D_psp_0929E538[] = "Mi-homme, mi-loup.";
static char D_psp_0929E550[] = "Gardien des tombes.";
static char D_psp_0929E568[] = "Crﾑature avec une tﾒte de";
static char D_psp_0929E588[] = "Mi-homme, mi-taureau.";
static char D_psp_0929E5A0[] = "Gremlin pyromane.";
static char D_psp_0929E5B8[] = "Chev. zombie assoiffﾑ de sang";
static char D_psp_0929E5D8[] = "Relique d’un crﾍne transportﾑe";
static char D_psp_0929E5F8[] = "Sorciﾐres fantﾛmes de Salem.";
static char D_psp_0929E618[] = "Fouille parmi les tombes et a";
static char D_psp_0929E638[] = "Gardien formﾑ de tﾒtes";
static char D_psp_0929E650[] = "Mystﾑrieux spadassin";
static char D_psp_0929E668[] = "Petit dﾑmon maniant la magie.";
static char D_psp_0929E688[] = "Frﾐre gﾑant.";
static char D_psp_0929E698[] = "Frﾐre gﾑant. Utilise un";
static char D_psp_0929E6B0[] = "L’aﾖnﾑ des Frﾐres gﾑants.";
static char D_psp_0929E6D0[] = "Monstre formﾑ d’une substance";
static char D_psp_0929E6F0[] = "Chevalier avec une armure.";
static char D_psp_0929E710[] = "Seigneur malﾑfique";
static char D_psp_0929E728[] = "Dﾑmon contrﾛlant la foudre.";
static char D_psp_0929E748[] = "Chien de garde des Enfers";
static char D_psp_0929E768[] = "Arrosﾑe avec du sang humain.";
static char D_psp_0929E788[] = "Vampire maﾖtrisant la magie.";
static char D_psp_0929E7A8[] = "Maﾖtre Tﾒte de poisson.";
static char D_psp_0929E7C0[] = "Pierres tombales possﾑdﾑes pa";
static char D_psp_0929E7E0[] = "Dﾑmon fﾑminin. S’immisce";
static char D_psp_0929E800[] = "Homme empalﾑ ﾋ la recherche";
static char D_psp_0929E820[] = "Lion peureux.";
static char D_psp_0929E830[] = "Monstre surnommﾑ \"Schmoo\".";
static char D_psp_0929E850[] = "Homme de fer sans cｪur.";
static char D_psp_0929E868[] = "Crﾑature cauchemardesque.";
static char D_psp_0929E888[] = "Squelette poursuivant";
static char D_psp_0929E8A0[] = "Renferme un nombre infini";
static char D_psp_0929E8C0[] = "Chevalier avec une armure";
static char D_psp_0929E8E0[] = "Zombies continuant d’attaquer,";
static char D_psp_0929E900[] = "Expert dans le lancer d’armes.";
static char D_psp_0929E920[] = "Insecte mutant. Seuls les";
static char D_psp_0929E940[] = "Archer diaboliquement prﾑcis.";
static char D_psp_0929E960[] = "Lycanthrope capable de";
static char D_psp_0929E978[] = "Wyrm contrﾛlﾑ par";
static char D_psp_0929E990[] = "Manie une arme tirant";
static char D_psp_0929E9A8[] = "Crﾑature liquide. Prend la";
static char D_psp_0929E9C8[] = "Squelette animﾑ d’un";
static char D_psp_0929E9E0[] = "Dragon blanc chevauchﾑ par";
static char D_psp_0929EA00[] = "Monstre ﾋ tﾒte de taureau.";
static char D_psp_0929EA20[] = "Enorme chauve-souris";
static char D_psp_0929EA38[] = "Ange archer.";
static char D_psp_0929EA48[] = "Loup crachant des boules";
static char D_psp_0929EA68[] = "Squelette effectuant";
static char D_psp_0929EA80[] = "Squelette chevauchant";
static char D_psp_0929EA98[] = "Pieuvre mutante et malﾑfique.";
static char D_psp_0929EAB8[] = "Bﾒte de combat protﾑgﾑe";
static char D_psp_0929EAD0[] = "Homo Sapiens suﾏant le sang";
static char D_psp_0929EAF0[] = "Dﾑmon enflammﾑ.";
static char D_psp_0929EB00[] = "Dﾑmon terrifiant venu";
static char D_psp_0929EB18[] = "Formﾑe des corps de puissants";
static char D_psp_0929EB38[] = "Herbe de Vﾑnus dﾑveloppﾑe.";
static char D_psp_0929EB58[] = "Ancienne momie ﾑgyptienne.";
static char D_psp_0929EB78[] = "Femme-dﾑmon aux cheveux de";
static char D_psp_0929EB98[] = "Petit dﾑmon espiﾐgle.";
static char D_psp_0929EBB0[] = "Zombie prenant l’apparence";
static char D_psp_0929EBD0[] = "Seigneur des mouches.";
static char D_psp_0929EBE8[] = "Jeune sorciﾐre.";
static char D_psp_0929EBF8[] = "Bourreau des Enfers.";
static char D_psp_0929EC10[] = "Esprit de la glace travesti.";
static char D_psp_0929EC30[] = "Chasseuse de vamp. Utilise 4";
static char D_psp_0929EC50[] = "Maﾖtre chasseur de vampires.";
static char D_psp_0929EC70[] = "Oiseau rare. S’enfuit";
static char D_psp_0929EC88[] = "Etre magique voulant rﾑgner";
static char D_psp_0929ECA8[] = "Puissant Seigneur ﾋ armure.";
static char D_psp_0929ECC8[] = "Confidente de Dracula.";
static char D_psp_0929ECE0[] = "Prﾒtre malﾑfique de Dracula.";
static char D_psp_0929ED00[] = "Seigneur de Valachie.";
static char* D_psp_0929ED18[] = {
    D_psp_0929DE20, D_psp_0929DE38, D_psp_0929DE50, D_psp_0929DE70,
    D_psp_0929DE80, D_psp_0929DE98, D_psp_0929DEB8, D_psp_0929DED0,
    D_psp_0929DEE8, D_psp_0929DF08, D_psp_0929DF28, D_psp_0929DF48,
    D_psp_0929DF60, D_psp_0929DF80, D_psp_0929DFA0, D_psp_0929DFC0,
    D_psp_0929DFD8, D_psp_0929DFF0, D_psp_0929E010, D_psp_0929E028,
    D_psp_0929E040, D_psp_0929E058, D_psp_0929E078, D_psp_0929E098,
    D_psp_0929E0B8, D_psp_0929E0D0, D_psp_0929E0E8, D_psp_0929E078,
    D_psp_0929E108, D_psp_0929E0E8, D_psp_0929E118, D_psp_0929E138,
    D_psp_0929E150, D_psp_0929E170, D_psp_0929E190, D_psp_0929E1A8,
    D_psp_0929E1C8, D_psp_0929E1E0, D_psp_0929E200, D_psp_0929E218,
    D_psp_0929E238, D_psp_0929E258, D_psp_0929E270, D_psp_0929E290,
    D_psp_0929E2B0, D_psp_0929E2D0, D_psp_0929E2F0, D_psp_0929E308,
    D_psp_0929E320, D_psp_0929E338, D_psp_0929E358, D_psp_0929E378,
    D_psp_0929E398, D_psp_0929E3B8, D_psp_0929E3D8, D_psp_0929E3F8,
    D_psp_0929DFA0, D_psp_0929E410, D_psp_0929DFD8, D_psp_0929E428,
    D_psp_0929E448, D_psp_0929E468, D_psp_0929E488, D_psp_0929E3F8,
    D_psp_0929E4A0, D_psp_0929E4C0, D_psp_0929E4D0, D_psp_0929E4E8,
    D_psp_0929E500, D_psp_0929E518, D_psp_0929E538, D_psp_0929E550,
    D_psp_0929E568, D_psp_0929E588, D_psp_0929E5A0, D_psp_0929E5B8,
    D_psp_0929E5D8, D_psp_0929E5F8, D_psp_0929E618, D_psp_0929E638,
    D_psp_0929E650, D_psp_0929E668, D_psp_0929E688, D_psp_0929E698,
    D_psp_0929E6B0, D_psp_0929E6D0, D_psp_0929E6F0, D_psp_0929E710,
    D_psp_0929E728, D_psp_0929E748, D_psp_0929E768, D_psp_0929E788,
    D_psp_0929E7A8, D_psp_0929E7C0, D_psp_0929E7E0, D_psp_0929E800,
    D_psp_0929E820, D_psp_0929E830, D_psp_0929E850, D_psp_0929E868,
    D_psp_0929E888, D_psp_0929E8A0, D_psp_0929E8C0, D_psp_0929E8E0,
    D_psp_0929E900, D_psp_0929E920, D_psp_0929E940, D_psp_0929E960,
    D_psp_0929E978, D_psp_0929E990, D_psp_0929E9A8, D_psp_0929E9C8,
    D_psp_0929E9E0, D_psp_0929EA00, D_psp_0929EA20, D_psp_0929EA38,
    D_psp_0929EA48, D_psp_0929E3F8, D_psp_0929E6F0, D_psp_0929EA68,
    D_psp_0929EA80, D_psp_0929EA98, D_psp_0929EAB8, D_psp_0929EAD0,
    D_psp_0929EAF0, D_psp_0929EB00, D_psp_0929E1A8, D_psp_0929EB18,
    D_psp_0929EB38, D_psp_0929EB58, D_psp_0929EB78, D_psp_0929EB98,
    D_psp_0929EBB0, D_psp_0929EBB0, D_psp_0929EBB0, D_psp_0929EBD0,
    D_psp_0929EBE8, D_psp_0929EBF8, D_psp_0929EC10, D_psp_0929EC30,
    D_psp_0929EC50, D_psp_0929EC70, D_psp_0929EC88, D_psp_0929ECA8,
    D_psp_0929ECC8, D_psp_0929ECE0, D_psp_0929ED00};

static char* D_psp_0929F950[] = {
    "en １７９２．（５ ans plus tﾛt）",
    "couverts de sang.",
    "sur lui-mﾒme.",
    "Contrﾛlﾑ par la magie.",
    "Redoutﾑs serviteurs du diable.",
    "du chﾍteau.",
    "la magie.",
    "Attaque tous les intrus.",
    "Dﾑgouline de poison.",
    "",
    "feu. Le + grand de son espﾐce.",
    "ﾑquipﾑ d’une hache.",
    "",
    "envoyﾑs il y a ３００ ans.",
    "coupantes comme un rasoir.",
    "",
    "un boomerang.",
    "",
    "de bas niveau.",
    "magique.",
    "des Enfers.",
    "Mais laquelle est la tﾒte ?",
    "",
    "humaine. Saute comme une puce.",
    "de fusils.",
    "ﾋ deux ﾑpﾑes.",
    "armure et une boule de fer.",
    "Peut pﾑtrifier.",
    "Ses graines pﾑtrifient.",
    "armure et une hache.",
    "Semble rﾑticent ﾋ combattre.",
    "d’un arc.",
    "et une naginata.",
    "",
    "Lance des tonneaux en bois.",
    "d'apparence.",
    "A soif de vengeance.",
    "lentement.",
    "pour novices.",
    "devenu mutant avec le chﾍteau.",
    "crﾍne de dragon blanchi.",
    "Grande ﾑpﾑe.",
    "tourmentﾑe errant sans corps.",
    "ﾋ un rite malﾑfique.",
    "d’une lourde armure.",
    "dans les zones pﾑrilleuses.",
    "Manie une rapiﾐre.",
    "les grottes.",
    "la glace.",
    "",
    "",
    "en fer avec des piques.",
    "oie spﾑcialement entraﾖnﾑe.",
    "",
    "mort depuis longtemps.",
    "",
    "coupantes comme un rasoir.",
    "mythologique.",
    "une naginata.",
    "mﾒme aprﾐs avoir ﾑtﾑ banni.",
    "Attaque avec un hibou domptﾑ.",
    "",
    "",
    "",
    "et d’un bouclier.",
    "",
    "",
    "et mi-aigle.",
    "deux ﾑpﾑes.",
    "",
    "",
    "Maﾖtre du combat sans armes.",
    "femme et un corps d’oiseau.",
    "",
    "",
    "et condamnﾑ au combat ﾑternel.",
    "par des prﾒtres squelettes.",
    "",
    "d’inestimables connaissances.",
    "de poisson.",
    "portant une cape.",
    "Invoque des alliﾑs malﾑfiques.",
    "Manie un couteau gurkha.",
    "ﾑnorme marteau en acier.",
    "Manie deux grandes dagues.",
    "gluante.",
    "Manie un disque.",
    "des corbeaux.",
    "Appelﾑ \"Musicien des Enfers\".",
    "",
    "",
    "Rﾐgne sur le haut du chﾍteau.",
    "",
    "r l’esprit malﾑfique des morts.",
    "dans les rﾒves des hommes.",
    "de cerveaux.",
    "",
    "",
    "",
    "Forme un ensemble.",
    "ﾑternellement son crﾍne.",
    "de graines empoisonnﾑes.",
    "lanﾏant des bombes.",
    "mﾒme une fois coupﾑs en deux.",
    "",
    "magiciens peuvent le voir.",
    "",
    "changer de forme.",
    "un Homme-puce.",
    "de redoutables rayons.",
    "forme d’une panthﾐre noire.",
    "ﾑnorme dragon.",
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
    "grﾍce ﾋ sa grande langue.",
    "",
    "des Enfers.",
    "de forme.",
    "guerriers.",
    "Nourrie avec du sang de dﾑmon.",
    "",
    "serpents et au regard pﾑtrif.",
    "",
    "de Grant.",
    "de Trevor.",
    "de Sypha.",
    "",
    "",
    "",
    "Serviteur de Galamoth.",
    "bﾒtes lﾑgend. Recher. Richter.",
    "",
    "quand il voit quelqu’un.",
    "sur le monde des tﾑnﾐbres.",
    "",
    "",
    "",
    "Pﾐre d’Alucard."};

static char* D_psp_092A0AF0[] = {
    "Von Richter vernichtet",
    "Wiedererweckt mit blut-",
    "Unzerstﾜrbarer Wirbelschﾎdel.",
    "Frische Leichen.",
    "Vampirfledermﾎuse.",
    "Wﾜlfe, die den Zugang zum",
    "Magisch beseeltes Skelett.",
    "Legendﾎres Wesen.",
    "Vierbeiniges Skelett.",
    "Gefﾎhrlicher Skelett-",
    "Feuerspuckender Wassergeist.",
    "Niederer Axtritter.",
    "Knochenwerfendes Skelett.",
    "Kirchensoldaten des Ostens,",
    "Pflanze mit rasiermesser-",
    "Besessener Ouijatisch.",
    "Bumerangwerfendes Skelett.",
    "Feuerspeiender Flugdﾎmon.",
    "Niedere Flammengeister.",
    "Dﾎmon mit verzaubertem Speer.",
    "Dﾎmonische Puppe aus ",
    "Ekelerregende, zweikﾜpfige",
    "Aus Medusenhaar.",
    "Seltsames, menschenﾎhnliches",
    "Skelette mit",
    "Novize im Kampf mit",
    "Schwer gepanzerter Ritter",
    "Aus Medusenhaar.",
    "Mutierte Pflanze.",
    "Gut gerｨsteter Axtritter.",
    "Feuer- und Eisdﾎmon.",
    "Skelettbogenschｨtze",
    "Krieger, bewaffnet mit",
    "Schlange, Parasit Scyllas.",
    "Beseeltes Affenskelett.",
    "Gestaltwandelnder Dﾎmon.",
    "Kopf eines hingerichteten",
    "Langsam fliegender ",
    "Zauberbuch fｨr Anfﾎnger.",
    "Heimische Eule, die durch das",
    "Sﾎule aus einem gebleichten",
    "Ritter mit",
    "Kﾜrperliche Manifestationen",
    "Magisch vergrﾜﾊerte Krﾜte",
    "Schwer gepanzerter, untoter",
    "Gepanzerter Wﾎchter.",
    "Kopfloses Skelett.",
    "Hﾜhlenfrosch.",
    "Eisbewaffneter, weiblicher",
    "Riesiger Schﾎdelgeist.",
    "Buch antiker Waffen.",
    "Skelett mit",
    "Flohmann auf trainierter",
    "Fleischfressender Rabe.",
    "Geist eines lang toten",
    "Bﾜses Dﾎmonenschwert. Ruft",
    "Pflanze mit rasiermesser-",
    "Mythologisches Meeresmonster.",
    "Naginateschwingendes Skelett.",
    "Der Schwertlord schwingt sein",
    "Schwer gepanzerter Ritter.",
    "Unsichtbarer Geist einer",
    "Animierter Schlammgolem.",
    "Bﾜses Dﾎmonenschwert. Ruft",
    "Flohmann mit Axt und",
    "Monster aus Gel und Schleim.",
    "Riesiges Skelett.",
    "In Teilen Pferd, Lﾜwe und",
    "Meister im Kampf mit",
    "Skelett eines Werpanters.",
    "Halb Mensch, halb Wolf.",
    "Grabwﾎchter.",
    "Wesen mit Frauenkopf und",
    "Halb Mensch, halb Stier.",
    "Pyromanischer Gremlin.",
    "Blutdurstiger, untoter Ritter,",
    "Tragbarer Schﾎdelschrein,",
    "Geiserhexen aus Salem.",
    "Durchsucht Grﾎber und",
    "Fischkopfwﾎchter.",
    "Geheimnisvoll verhｨllter",
    "Kleiner, magiekundiger Dﾎmon.",
    "Groﾊer Bruder.",
    "Groﾊer Bruder.",
    "ｷltester groﾊer Bruder.",
    "Monster aus schleimiger",
    "Scheibenschwingender,",
    "Dﾎmonenlord der Raben.",
    "Donnerwerfender Dﾎmon.",
    "Wachhund der Hﾜlle.",
    "Mit Menschenblut gegossen.",
    "Magiekundiger Vampir. Herrscht",
    "Fischkopfmeister.",
    "Grabsteine, beseelt von bﾜsen",
    "Weiblicher Dﾎmon.",
    "Gepfﾎhlter Mann auf der Suche",
    "Der feige Lﾜwe.",
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
    "Schwingt eine fｨrchterliche",
    "Flｨssiges Wesen. Tritt in Form",
    "Beseeltes Skelett eines ",
    "Vom Flohmann gerittener",
    "Stierkﾜpfiges Monster.",
    "Riesige Vampirfledermaus.",
    "Engelsbogenschｨtze. Hat Amalar",
    "Feuerspuckender Wolf.",
    "Bﾜses Dﾎmonenschwert. Ruft",
    "Felsenwerfender, gepanzerter",
    "Skelett mit Sprungangriff.",
    "Ein wargreitendes Skelett.",
    "Bﾜser, mutierter Oktopus.",
    "Geharnischtes Kriegstier.",
    "Wenig intelligenter Blutsauger",
    "Flammendﾎmon.",
    "Schrecklicher Dﾎmon aus ",
    "Gestaltwandelnder Dﾎmon.",
    "Besteht aus den Kﾜrperteilen",
    "Mﾎchtige Venusranke.",
    "Uralte ﾎgyptische Mumie.",
    "Schlangenkﾜpfige Dﾎmonin",
    "Boshafter kleiner Dﾎmon.",
    "Zombie, der sich als Grant",
    "Zombie, der sich als Trevor",
    "Zombie, der sich als Sypha",
    "Beelzebub, Herr der Fliegen.",
    "Junge Hexe.",
    "Henker der Hﾜlle.",
    "Transvestiten-Eisgeist.",
    "Vampirjﾎger. Nutzt 4 legendﾎre",
    "Meistervampirjﾎger.",
    "Seltener Vogel.",
    "Magisches Geschﾜpf, das die",
    "Mﾎchtiger Rｨstungslord.",
    "Draculas Vertrauter.",
    "Dunkler Priester des Dracula.",
    "Herr von Wallachia."};

static char* D_psp_092A14D0[] = {
    "im Jahre １７９２ (vor ５ Jahren).",
    "getrﾎnkten Knochen.",
    "",
    "Magisch beseelt.",
    "Gefｨrchtete Diener des Bﾜsen.",
    "Schloss bewachen.",
    "",
    "Greift alle Eindringlinge an.",
    "Trieft vor Gift.",
    "schwertkﾎmpfer.",
    "Grﾜﾊter Wassergeist.",
    "",
    "",
    "seit 300 Jahren unterwegs.",
    "scharfen Blﾎttern.",
    "",
    "",
    "",
    "",
    "",
    "der Hﾜlle.",
    "Bestie. Was ist der Kopf?",
    "",
    "Wesen, springt wie ein Floh.",
    "Gewehren.",
    "zwei Klingen.",
    "mit Eisenkugel.",
    "Kann Feinde versteinern.",
    "Die Samen versteinern.",
    "",
    "Geht Kﾎmpfen aus dem Weg.",
    "",
    "Naginata.",
    "",
    "Schleudert Holzfﾎsser.",
    "",
    "Soldaten. Sinnt auf Rache.",
    "Skelettkrieger.",
    "",
    "Schloss mutiert ist.",
    "Drachenschﾎdel.",
    "Breitschwert.",
    "gepeinigter Seelen.",
    "(dﾎmonisch getauft).",
    "Krieger.",
    "Stark i.gefﾎhrlichen Gebieten.",
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
    "scharfen Blﾎttern.",
    "",
    "",
    "Schwert auch unter Bann.",
    "Greift m. trainierter Eule an.",
    "Jﾎgerin.",
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
    "Vogelkﾜrper.",
    "",
    "",
    "der ewig den Kampf sucht.",
    "getragen von Skelettpriestern.",
    "",
    "steckt voller Wissen.",
    "",
    "Schwertkﾎmpfer.",
    "Ruft dﾎmonische Helfer.",
    "Schwingt ein Gurkha-Messer.",
    "Benutzt einen Stahlhammer.",
    "Schwingt 2 gewaltige Dolche.",
    "Gelmasse.",
    "gepanzerter Ritter.",
    "",
    "Genannt \"Musiker der Hﾜlle\".",
    "",
    "",
    "ｨb. d.oberen Teil d.Schlosses.",
    "",
    "Geistern der Toten.",
    "Dringt in Mﾎnnertrﾎume ein.",
    "nach Intelligenz.",
    "",
    "",
    "",
    "Besteht aus Vielen.",
    "eigenen Schﾎdel jagt.",
    "",
    "Ritter.",
    "wenn sie zerschnitten sind.",
    "",
    "Nur fｨr Magier sichtbar.",
    "Bogenschｨtze.",
    "",
    "Wyrm.",
    "Strahlenwaffe.",
    "eines schwarzen Panters auf.",
    "gewaltigen Drachens.",
    "weiﾊer Drache.",
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
    "der Hﾜlle.",
    "",
    "mﾎchtiger Krieger.",
    "Mit Dﾎmonenblut gegossen.",
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
    "Lﾎuft vor Menschen davon.",
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

static char D_psp_092A17B8[] = "\x33\x2F\x2C\x24\x00\x2F\x35\x34\xFF";
static char* D_psp_092A17D8[] = {
    "\x2A\x45\x57\x45\x4C\x00\x4F\x46\x00\x2F\x50\x45\x4E\xFF"};
static char* D_psp_092A1870[] = {
    "\x23\x41\x53\x54\x4C\x45\x00\x2D\x41\x50\xFF",
    "\x2D\x41\x47\x49\x43\x00\x33\x43\x52\x4F\x4C\x4C\x00\x11\xFF",
    "\x2D\x41\x47\x49\x43\x00\x33\x43\x52\x4F\x4C\x4C\x00\x12\xFF",
    "\x2D\x41\x47\x49\x43\x00\x33\x43\x52\x4F\x4C\x4C\x00\x13\xFF",
    "\x2D\x41\x47\x49\x43\x00\x33\x43\x52\x4F\x4C\x4C\x00\x14\xFF",
    "\x2D\x41\x47\x49\x43\x00\x33\x43\x52\x4F\x4C\x4C\x00\x15\xFF",
    "\x2D\x41\x47\x49\x43\x00\x33\x43\x52\x4F\x4C\x4C\x00\x16\xFF",
    "\x2D\x41\x47\x49\x43\x00\x33\x43\x52\x4F\x4C\x4C\x00\x17\xFF",
    "\x2D\x41\x47\x49\x43\x00\x33\x43\x52\x4F\x4C\x4C\x00\x18\xFF"};

static char D_psp_092A1898[] = "\x2E\x4F\x54\x48\x49\x4E\x47\xFF";
static char D_psp_092A18A8[] =
    "\x2C\x41\x52\x47\x45\x00\x28\x45\x41\x52\x54\xFF";
static char D_psp_092A18B8[] = "\x04\x11\xFF";
static char D_psp_092A18C0[] = "\x04\x12\x15\xFF";
static char D_psp_092A18C8[] = "\x04\x15\x10\xFF";
static char D_psp_092A18D0[] = "\x04\x11\x10\x10\xFF";
static char D_psp_092A18D8[] = "\x04\x12\x15\x10\xFF";
static char D_psp_092A18E0[] = "\x04\x14\x10\x10\xFF";
static char D_psp_092A18E8[] = "\x04\x17\x10\x10\xFF";
static char D_psp_092A18F0[] = "\x04\x11\x10\x10\x10\xFF";
static char D_psp_092A18F8[] = "\x04\x12\x10\x10\x10\xFF";
static char D_psp_092A1900[] = "\x04\x15\x10\x10\x10\xFF";
static char D_psp_092A1908[] = "\x28\x45\x41\x52\x54\x00\x35\x50\xFF";
static char D_psp_092A1918[] = "\x2D\x45\x41\x54\xFF";
static char D_psp_092A1920[] = "\x2B\x4E\x49\x46\x45\xFF";
static char D_psp_092A1928[] = "\x21\x58\x45\xFF";
static char D_psp_092A1930[] = "\x23\x52\x4F\x53\x53\xFF";
static char D_psp_092A1938[] = "\x28\x4F\x4C\x59\x00\x37\x41\x54\x45\x52\xFF";
static char D_psp_092A1948[] = "\x23\x4C\x4F\x43\x4B\xFF";
static char D_psp_092A1950[] = "\x28\x4F\x4C\x59\x00\x22\x4F\x4F\x4B\xFF";
static char D_psp_092A1960[] =
    "\x32\x45\x42\x4F\x55\x4E\x44\x33\x54\x4F\x4E\x45\xFF";
static char D_psp_092A1970[] = "\x22\x49\x42\x55\x54\x49\xFF";
static char D_psp_092A1978[] = "\x21\x47\x55\x4E\x45\x41\xFF";
static char D_psp_092A1980[] = "\x2C\x49\x46\x45\x00\x35\x50\xFF";
static char* D_psp_092A1990[] = {
    D_psp_092A1898, D_psp_092A18A8, D_psp_092A18B8, D_psp_092A18C0,
    D_psp_092A18C8, D_psp_092A18D0, D_psp_092A18D8, D_psp_092A18E0,
    D_psp_092A18E8, D_psp_092A18F0, D_psp_092A18F8, D_psp_092A1900,
    D_psp_092A1908, D_psp_092A1918, D_psp_092A1920, D_psp_092A1928,
    D_psp_092A1930, D_psp_092A1938, D_psp_092A1948, D_psp_092A1950,
    D_psp_092A1960, D_psp_092A1970, D_psp_092A1978, D_psp_092A1980};

static char D_psp_092A19F0[] = "\x33\x54\x52\x4F\x4E\x47\x00\x36\x33\x0E\xFF";
static char D_psp_092A1A00[] = "\x29\x4D\x4D\x55\x4E\x45\xFF";
static char D_psp_092A1A08[] = "\x37\x45\x41\x4B\x00\x36\x33\x0E\xFF";
static char D_psp_092A1A18[] = "\x21\x42\x53\x4F\x52\x42\xFF";
static char* D_psp_092A1A20[] = {
    D_psp_092A19F0, D_psp_092A1A00, D_psp_092A1A08, D_psp_092A1A18};
static char D_psp_092A1A30[] = "\x28\x2F\x2C\xFF";
static char D_psp_092A1A38[] = "\x24\x32\x2B\xFF";
static char D_psp_092A1A40[] = "\x26\x29\x32\xFF";
static char D_psp_092A1A48[] = "\x34\x28\x35\xFF";
static char D_psp_092A1A50[] = "\x29\x23\x25\xFF";
static char D_psp_092A1A58[] = "\x28\x12\x2F\xFF";
static char D_psp_092A1A60[] = "\x33\x34\x2E\xFF";
static char D_psp_092A1A68[] = "\x30\x33\x2E\xFF";
static char D_psp_092A1A70[] = "\x23\x35\x32\xFF";
static char D_psp_092A1A78[] = "\x23\x35\x34\xFF";
static char D_psp_092A1A80[] = "\x28\x29\x34\xFF";
static char* D_psp_092A1A88[] = {
    D_psp_092A1A30, D_psp_092A1A38, D_psp_092A1A40, D_psp_092A1A48,
    D_psp_092A1A50, D_psp_092A1A58, D_psp_092A1A60, D_psp_092A1A68,
    D_psp_092A1A70, D_psp_092A1A78, D_psp_092A1A80};

extern char D_psp_092A1AB8[];
extern char* D_psp_092A1B00[];
extern char D_psp_092A1B20[];
extern char* D_psp_092A1B60[];
extern char* D_psp_092A1DC0[];
extern char* D_psp_092A1FA8[];
extern char* D_psp_092A2110[];
extern char D_psp_092A2138[];
extern char* D_psp_092A2148[];
extern char* D_psp_092A21A8[];
extern char D_psp_092A21C8[];
extern char* D_psp_092A21E8[];
extern char* D_psp_092A2280[];
extern char* D_psp_092A2390[];
extern char* D_psp_092A2428[];
extern char* D_psp_092A2480[];
extern char D_psp_092A24B0[];
extern char* D_psp_092A24E8[];
extern char D_psp_092A2508[];
extern char* D_psp_092A2540[];
extern char* D_psp_092A27F0[];
extern char* D_psp_092A2908[];
extern char* D_psp_092A2A88[];
extern char D_psp_092A2AB0[];
extern char* D_psp_092A2AC0[];
extern char* D_psp_092A2B20[];
extern char D_psp_092A2B40[];
extern char* D_psp_092A2B60[];
extern char* D_psp_092A2BF8[];
extern char* D_psp_092A2CB0[];
extern char* D_psp_092A2D40[];
extern char* D_psp_092A2D88[];
extern char D_psp_092A2DB8[];
extern char* D_psp_092A2DE8[];
extern char D_psp_092A2E08[];
extern char* D_psp_092A2E40[];
extern char* D_psp_092A30F8[];
extern char* D_psp_092A3210[];
extern char* D_psp_092A3390[];
extern char D_psp_092A33B8[];
extern char* D_psp_092A33C0[];
extern char* D_psp_092A3428[];
extern char D_psp_092A3448[];
extern char* D_psp_092A3468[];
extern char* D_psp_092A3500[];
extern char* D_psp_092A35C0[];
extern char* D_psp_092A3650[];
extern char* D_psp_092A36B8[];
extern char D_psp_092A36E8[];
extern char* D_psp_092A3708[];
extern char D_psp_092A3728[];
extern char* D_psp_092A3758[];
extern char* D_psp_092A39A8[];
extern char* D_psp_092A3AC8[];
extern char* D_psp_092A3C48[];
extern char D_psp_092A3C70[];
extern char* D_psp_092A3C80[];
extern char* D_psp_092A3CD8[];
extern char D_psp_092A3CF8[];
extern char* D_psp_092A3D18[];
extern char* D_psp_092A3DB0[];
extern char* D_psp_092A3E70[];
extern char* D_psp_092A3F08[];
extern char* D_psp_092A3F58[];
extern char D_psp_092A3F88[];
extern char* D_psp_092A3FB0[];
extern char D_psp_092A3FD0[];
extern char* D_psp_092A4008[];
extern char* D_psp_092A4270[];
extern char* D_psp_092A4398[];
extern char* D_psp_092A44F0[];
extern char D_psp_092A4518[];
extern char** D_psp_092A5F40;
extern char** D_psp_092A5F48;
extern char** D_psp_092A5F58;
extern char** D_psp_092A5F60;
extern char** D_psp_092A5F68;
extern char** D_psp_092A5F80;
extern char* D_psp_092A5F88;
extern char** D_psp_092A5F90;
extern char** D_psp_092A5F98;
extern char** D_psp_092A5FA0;
extern char** D_psp_092A5FA8;
extern char** D_psp_092A5FB0;
extern char* D_psp_092A5FB8;
extern char** D_us_80181310;
extern char** D_us_80181528;
extern char* D_us_80181660;
extern char* D_us_80181668;
extern char** D_us_80181674;

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
extern const char* D_psp_092A4CA8[];
extern RECT D_psp_092A4D00;
extern RECT D_psp_092A4D48;
extern RECT D_psp_092A4BE8;
extern RECT D_psp_092A4BD0;
extern RECT D_psp_092A4AF0;
extern u16 D_us_80181978[];
extern u16 D_psp_092A4D08[];
extern char D_psp_092A4CC8[];
extern const char D_psp_092A4880[];
extern u16 D_us_801814D4[];
extern ShopItem D_us_801814D8[];
extern u16 D_us_80181510[];
extern u32 D_us_801D415C[];
extern u32 D_us_801D425C[];
extern ShopItem D_us_801D4364[];
extern u8 D_us_801811FC[];
extern u8 D_us_80181204[];
extern u8 D_us_80181210[];
extern u8 D_us_8018121C[];
extern u8 D_us_80181234[];
extern u8 D_us_80181244[];
extern u8 D_us_801812C0[];
extern u8 D_us_801812C8[];
extern u8 D_us_801812D0[];
extern u8* D_us_801812D8[];
extern u8* D_psp_092A5D38;
extern u16 D_psp_092A4BF0[11];
extern const char* D_psp_092A4C18[];
extern const char* D_psp_092A4C28[];
extern char D_psp_092A4BD8[];
extern ShopItem D_psp_092A4AF8[24];
extern char D_psp_092A4BB8[];
extern char D_psp_092A4BC8[];
extern u8* D_psp_092A54E0;
extern const char* D_us_80181340[];
extern s32 D_8B42058;

void* func_psp_0925D430(void* en, void* fr, void* sp, void* ge, void* it) {
    switch (D_8B42058) {
    default:
    case LANG_EN:
        return en;
    case LANG_FR:
        return fr;
    case LANG_SP:
        return sp;
    case LANG_GE:
        return ge;
    case LANG_IT:
        return it;
    }
}

void func_psp_0925D4D0(void) {
    D_us_80181528 =
        func_psp_0925D430(D_psp_092A1730, D_psp_092A33C0, D_psp_092A2148,
                          D_psp_092A3C80, D_psp_092A2AC0);
    D_us_80181310 =
        func_psp_0925D430(D_psp_092A1798, D_psp_092A3428, D_psp_092A21A8,
                          D_psp_092A3CD8, D_psp_092A2B20);
    D_psp_092A5FB8 =
        func_psp_0925D430(D_psp_092A17B8, D_psp_092A3448, D_psp_092A21C8,
                          D_psp_092A3CF8, D_psp_092A2B40);
    D_psp_092A5FB0 =
        func_psp_0925D430(D_psp_092A17D8, D_psp_092A3468, D_psp_092A21E8,
                          D_psp_092A3D18, D_psp_092A2B60);
    D_psp_092A5FA8 =
        func_psp_0925D430(D_psp_092A1870, D_psp_092A3500, D_psp_092A2280,
                          D_psp_092A3DB0, D_psp_092A2BF8);
    D_psp_092A5FA0 =
        func_psp_0925D430(D_psp_092A1990, D_psp_092A35C0, D_psp_092A2390,
                          D_psp_092A3E70, D_psp_092A2CB0);
    D_psp_092A5F98 =
        func_psp_0925D430(D_psp_092A1A20, D_psp_092A3650, D_psp_092A2428,
                          D_psp_092A3F08, D_psp_092A2D40);
    D_psp_092A5F90 =
        func_psp_0925D430(D_psp_092A1A88, D_psp_092A36B8, D_psp_092A2480,
                          D_psp_092A3F58, D_psp_092A2D88);
    D_psp_092A5F88 =
        func_psp_0925D430(D_psp_092A1AB8, D_psp_092A36E8, D_psp_092A24B0,
                          D_psp_092A3F88, D_psp_092A2DB8);
    D_psp_092A5F80 =
        func_psp_0925D430(D_psp_092A1B00, D_psp_092A3708, D_psp_092A24E8,
                          D_psp_092A3FB0, D_psp_092A2DE8);
    D_us_80181668 =
        func_psp_0925D430(D_psp_092A1B20, D_psp_092A3728, D_psp_092A2508,
                          D_psp_092A3FD0, D_psp_092A2E08);
    D_us_80181674 =
        func_psp_0925D430(D_psp_092A1B60, D_psp_092A3758, D_psp_092A2540,
                          D_psp_092A4008, D_psp_092A2E40);
    D_psp_092A5F68 =
        func_psp_0925D430(D_psp_092A1DC0, D_psp_092A39A8, D_psp_092A27F0,
                          D_psp_092A4270, D_psp_092A30F8);
    D_psp_092A5F58 =
        func_psp_0925D430(D_psp_092A2110, D_psp_092A3C48, D_psp_092A2A88,
                          D_psp_092A44F0, D_psp_092A3390);
    D_us_80181660 =
        func_psp_0925D430(D_psp_092A2138, D_psp_092A3C70, D_psp_092A2AB0,
                          D_psp_092A4518, D_psp_092A33B8);
    D_psp_092A5F60 =
        func_psp_0925D430(D_psp_092A1FA8, D_psp_092A3AC8, D_psp_092A2908,
                          D_psp_092A4398, D_psp_092A3210);
    D_psp_092A5F48 =
        func_psp_0925D430(D_psp_09299A18, D_psp_0929ED18, D_psp_0929B4A0,
                          D_psp_092A0AF0, D_psp_0929D1B0);
    D_psp_092A5F40 =
        func_psp_0925D430(D_psp_0929A320, D_psp_0929F950, D_psp_0929BFF0,
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
        g_Player.D_80072EFC = 1;
#endif
        break;
    case 1:
        g_Entities[1].ext.entSlot1.unk0 = 1;
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = true;
        g_Player.padSim = PAD_LEFT;
        g_Player.D_80072EFC = 1;
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
        g_Player.D_80072EFC = 1;
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
        g_Player.D_80072EFC = 1;
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
        g_Player.D_80072EFC = 1;
        break;
    case 4:
        g_Player.padSim = PAD_NONE | PAD_SIM_UNK20000;
        g_Player.D_80072EFC = 1;
        self->step++;
        break;
    case 5:
        g_CastleFlags[MET_LIBRARIAN] = 1;
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_MEET_MASTER_LIBRARIAN, TIMEATTACK_SET_RECORD);
        g_Player.D_80072EFC = 1;
        self->step++;
        /* fallthrough */
    case 6:
        if (g_CutsceneFlags & 0x100) {
            g_CutsceneFlags |= 0x2000;
            self->step = 0x10;
            break;
        }
        player->posX.i.hi = 0x74;
        break;
    case 8:
        self->step++;
        /* fallthrough */
    case 9:
        if (player->posX.i.hi > 0xFF) {
            g_api.PlaySfx(CD_SOUND_COMMAND_7);
            DestroyEntity(self);
            break;
        }
        if (player->posX.i.hi < 0x75) {
            switch (self->step_s) {
            case 0:
                g_Entities[1].ext.entSlot1.unk0 = 1;
                g_PauseAllowed = false;
                g_unkGraphicsStruct.pauseEnemies = true;
                g_Player.padSim = PAD_NONE;
                g_Player.D_80072EFC = 0x10;
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
                g_Player.D_80072EFC = 1;
                break;
            case 2:
                g_Player.padSim = PAD_NONE;
                g_Player.D_80072EFC = 0x80;
                SetStep(10);
                break;
            }
            player->posX.i.hi = 0x74;
        }
        break;
    case 10:
        if (!g_Player.D_80072EFC && (g_Player.pl_vram_flag & 1)) {
            g_Player.padSim = PAD_NONE | PAD_SIM_UNK20000;
            g_Player.D_80072EFC = 1;
            self->step++;
        }
        player->posX.i.hi = 0x74;
        break;
    case 11:
        g_Player.padSim = PAD_NONE | PAD_SIM_UNK20000;
        g_Player.D_80072EFC = 1;
        if (g_CutsceneFlags & 0x100) {
            g_CutsceneFlags |= 0x2000;
            self->step = 0x10;
        }
        break;
    case 16:
#ifdef VERSION_PSP
        g_PauseAllowed = false;
#endif
        g_Player.D_80072EFC = 0x20;
        g_Player.padSim = PAD_RIGHT;
        D_80097928 = 1;
        self->step++;
        break;
    case 17:
#ifdef VERSION_PSP
        g_PauseAllowed = false;
#endif
        if (!g_Player.D_80072EFC) {
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
                   ((*((f32*)&player->velocityY)).i.hi < 0)) {
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
    if (g_Player.pl_vram_flag & 1) {
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
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
            }
        } else if (g_pads[0].tapped & PAD_DOWN) {
            if (self->ext.libraryChair.debugAnimID != 0x10) {
                self->ext.libraryChair.debugAnimID++;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
            }
        }
        AnimateEntity(D_us_801812D8[self->ext.libraryChair.debugAnimID], self);
        break;
    }
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

void func_us_801B0FBC(const char* str, u16 x, u16 y);

void func_us_801B15C0(Entity* self) {
    Entity* tempEntity;
    Primitive* otherPrim;
    Primitive* prim;
    s32 primIndex;
    s16 tempVar;
    s32 i;
    u16 tempVar2;
    const char* ptr;
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
            *D_psp_092A54E0 = 0;
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

u16 func_us_801B29C4(void);
INCLUDE_ASM("st/lib_psp/psp/lib_psp/e_shop", func_us_801B29C4);

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
            for (i = 0; i < 64; i++) {
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
        FntPrint(D_psp_092A4880, self->ext.et_801B6F30.unk82);
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
        } else if (tempVar & (PAD_R1 + PAD_R2)) {
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
        } else if (tempVar & (PAD_L1 + PAD_L2)) {
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

INCLUDE_ASM("st/lib_psp/psp/lib_psp/e_shop", func_us_801B4830);

void func_psp_09264E08(void) { D_psp_092A5D38 = &g_Pix[0][0x2000]; }

void* func_us_801B0C40(u8* pix, const char* str, s32 x, s32 y, s32 size) {
    const u16 MINSCODE = 0x8140;
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
            ch = g_api.func_ptr_91CF870((char*)str, &sp3f);
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
                ch = MINSCODE;
                s_8 = 2;
            } else {
#ifdef VERSION_PSP
                if (sp3f > 1) {
                    str += sp3f - 1;
                }
            }
            chPix = (u8*)g_api.func_ptr_91CF86C(ch, 1);
#else
                ch = *str++ | (ch << 8);
                if (ch == MINSCODE) {
                    s_8 = 2;
                }
            }
            if (ch == RIGHT_DOUBLE_QUOTATION_MARK) {
                str += 2;
            }
            chPix = (u8*)g_api.func_80106A28(ch, 1);
#endif
            while (true) {
                if (ch == MINSCODE) {
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
        desc = D_psp_092A5F58[itemId];
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
    RECT clipRect;
    const char* name;
    Primitive* prim;
    Primitive* prim2;
    s16 posX, posY;
    s16 itemId;
    s16 index;
    s32 count;
    u32 price;

    clipRect = D_psp_092A4AF0;
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
                name = D_psp_092A5FB0[itemId];
                break;
            case INVENTORY_DOCUMENT:
                name = D_psp_092A5FA8[itemId];
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
                func_us_801B3FB4(prim2, D_psp_092A5FB8, count, 1);
#else
                func_us_801B3FB4(prim2, D_psp_092A5FB8, LEN(D_psp_092A5FB8), 1);
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
    *D_psp_092A54E0 = 0;
#else
    D_us_80183F64 = 0;
#endif
    if (D_8003C730 == 2) {
        D_8003C730 = 0;
#ifdef VERSION_PSP
        *D_psp_092A54E0 = 1;
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
        enemyTactics = &D_psp_092A4AF8[itemIndex];
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
            prim = func_us_801B1064(
                prim, 8, posY, D_psp_092A5F60[itemIndex], clut);
#else
            prim =
                func_us_801B1064(prim, 8, posY, D_psp_092A5F60[itemId], clut);
#endif
            enemyTactics->category++;
        } else {
            clut = 0x191;
            prim = func_us_801B1064(prim, 8, posY, D_psp_092A4BB8, 0x191);
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
            func_us_801B3FB4(prim2, D_psp_092A4BC8, 8, 1);
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
    RECT clipRect;
    DR_ENV* dr_env;
    Primitive* prim;
    s32 primIndex;
    s16 itemID;
    s32 i;
    s32 var_v1;
    u16 pads;

    clipRect = D_psp_092A4BD0;
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
#ifdef VERSION_PSP
            for (i = 0; i < 24; i++) {
#else
            for (i = 0; i < LEN(D_psp_092A4AF8); i++) {
#endif
                itemID = D_psp_092A4AF8[i].itemId;
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
            switch (D_psp_092A4AF8[itemID].category) {
            case 0:
                g_api.PlaySfx(SFX_UI_ERROR);
                break;

            case 1:
                if (g_Status.gold < D_psp_092A4AF8[itemID].price) {
                    g_api.PlaySfx(SFX_UI_ERROR);
                } else {
                    g_Status.gold -= D_psp_092A4AF8[itemID].price;
                    itemID = D_psp_092A4AF8[itemID].itemId;
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
        D_80097C98 = D_psp_092A4AF8[self->ext.et_801B6F30.unk82 +
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
                prim =
                    func_us_801B1064(prim, posX, posY, D_psp_092A4BD8, 0x191);
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
    RECT clipRect;
    DR_ENV* dr_env;
    Primitive* prim;
    s32 primIndex;
    s16 enemyIndex;
    s32 i;
    u16 pads;
    Entity* tempEntity;

    clipRect = D_psp_092A4BE8;
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
        name = D_psp_092A5FA0[itemId];
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
    func_us_801B3FB4(prim, D_psp_092A5F80[5], 3, 1); // "No."
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
    func_us_801B3FB4(prim, D_psp_092A5F80[0], 2, 1); // "Strong VS."
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
        func_us_801B3FB4(prim, D_psp_092A5F80[6], 2, 1); // "??"
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
    func_us_801B3FB4(prim, D_psp_092A5F80[1], 2, 1); // "HP"
    for (i = 0; i < 2; i++) {
        prim->clut = 0x196;
        prim->x0 = posX;
        prim->y0 = posY;
        prim = prim->next;
        posX += 8;
    }
    posX += 2;
    if (enemyDef->hitPoints > 9999) {
        func_us_801B3FB4(prim, D_psp_092A4C28[0], 4, 1); // "????"
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
    func_us_801B3FB4(prim, D_psp_092A5F80[3], 3, 1); // "Exp"
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
    func_us_801B3FB4(prim, D_psp_092A5F80[4], strLen, 1); // "Drop Items"
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
            prim, posX - xOffset, posY, D_psp_092A4C18[0], 0x196); // "????????"
    }
    for (i = 0; i < 4; i++) {
        prim = func_us_801B1064(prim, 0x84 - xOffset, ((i * 0x10) + 0x3C),
                                D_psp_092A5F98[i], 0x196);
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
        for (i = 0; i < LEN(D_psp_092A4BF0); i++) {
            if (arg1 & D_psp_092A4BF0[i]) {
                prim =
                    func_us_801B1064(prim, x, posY, D_psp_092A5F90[i], 0x196);
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
    const char* s3;
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

void func_us_801B8A00(Entity* self) {
    DRAWENV drawEnv;
    RECT clipRect;
    DR_ENV* dr_env;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    u16 pads;
    s16 sfxIndex;
    u8* pix;

    clipRect = D_psp_092A4D00;
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
            self->animFrameDuration = 0x30;
            self->step_s++;
            break;

        case 1:
            if (!--self->animFrameDuration) {
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

void func_us_801B8958(Primitive* prim, Entity* self) {
    s16 posY;
    s32 i, j;

    posY = 16;
    j = self->ext.et_801B6F30.unk82;
    for (i = 0; i < 7; i++, j++) {
        prim = func_us_801B1064(prim, 16, posY, D_psp_092A5F68[j], 0x196);
        posY += 12;
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_psp_0926BE68(Entity* self) {
    DRAWENV drawEnv;
    RECT clipRect;
    DR_ENV* dr_env;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    u16 pads;
    s16 sfxIndex;

    clipRect = D_psp_092A4D48;
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
            g_api.PlaySfx(7);
            SetStep(3);
            return;
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
            self->animFrameDuration = 0x30;
            self->step_s++;
            break;

        case 1:
            if (!--self->animFrameDuration) {
                self->step_s++;
            }
            break;

        case 2:
            if (!g_api.func_80131F68() && (g_CutsceneFlags & 0x200) == 0) {
                sfxIndex =
                    self->ext.et_801B6F30.unk80 + self->ext.et_801B6F30.unk82;
                g_api.PlaySfx(D_psp_092A4D08[sfxIndex]);
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
        break;
    }
}
