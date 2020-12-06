#include "global.h"
#include "graphics.h"
#include "mail.h"
#include "palette.h"
#include "pokemon_icon.h"
#include "sprite.h"
#include "constants/species.h"

#define POKE_ICON_BASE_PAL_TAG 56000

struct MonIconSpriteTemplate
{
    const struct OamData *oam;
    const u8 *image;
    const union AnimCmd *const *anims;
    const union AffineAnimCmd *const *affineAnims;
    void (*callback)(struct Sprite *);
    u16 paletteTag;
};

// static functions
static u8 CreateMonIconSprite(struct MonIconSpriteTemplate *, s16, s16, u8);

// .rodata

const u8 *const gMonIconTable[] =
{
    [SPECIES_NONE] = gMonIcon_Chapebaya,
    [SPECIES_CHAPEBAYA] = gMonIcon_Chapebaya,
    [SPECIES_DENPECHA] = gMonIcon_Denpecha,
    [SPECIES_DENFROTA] = gMonIcon_Denfrota,
    [SPECIES_COALCHU] = gMonIcon_Coalchu,
    [SPECIES_RALLAMA] = gMonIcon_Rallama,
    [SPECIES_ROELLAMA] = gMonIcon_Roellama,
    [SPECIES_TODAD] = gMonIcon_Todad,
    [SPECIES_SHROAD] = gMonIcon_Shroad,
    [SPECIES_BULTOAD] = gMonIcon_Bultoad,
    [SPECIES_LARVET] = gMonIcon_Larvet,
    [SPECIES_MORFADE] = gMonIcon_Morfade,
    [SPECIES_EYEFLY] = gMonIcon_Eyefly,
    [SPECIES_DROSOFLY] = gMonIcon_Drosofly,
    [SPECIES_METAGASTER] = gMonIcon_Metagaster,
    [SPECIES_PHYLAFLY] = gMonIcon_Phylafly,
    [SPECIES_ORNLIL] = gMonIcon_Ornlil,
    [SPECIES_WASOO] = gMonIcon_Wasoo,
    [SPECIES_VOLATEO] = gMonIcon_Volateo,
    [SPECIES_BATOKA] = gMonIcon_Batoka,
    [SPECIES_MOUSPID] = gMonIcon_Mouspid,
    [SPECIES_TURKUR] = gMonIcon_Turkur,
    [SPECIES_PEAKUR] = gMonIcon_Peakur,
    [SPECIES_CHUK_TXU] = gMonIcon_ChukTxu,
    [SPECIES_LEECKEY] = gMonIcon_Leeckey,
    [SPECIES_COVOLTS] = gMonIcon_Covolts,
    [SPECIES_LUCIVOLTS] = gMonIcon_Lucivolts,
    [SPECIES_NOLE] = gMonIcon_Nole,
    [SPECIES_GROUNDOE] = gMonIcon_Groundoe,
    [SPECIES_URTIGA] = gMonIcon_Urtiga,
    [SPECIES_URTIGERE] = gMonIcon_Urtigere,
    [SPECIES_VENOGENA] = gMonIcon_Venogena,
    [SPECIES_URTIGO] = gMonIcon_Urtigo,
    [SPECIES_URTIGORO] = gMonIcon_Urtigoro,
    [SPECIES_VENOGENO] = gMonIcon_Venogeno,
    [SPECIES_AMAIRI] = gMonIcon_Amairi,
    [SPECIES_OGRAIRI] = gMonIcon_Ograiri,
    [SPECIES_HORMIG] = gMonIcon_Hormig,
    [SPECIES_LLAMOSE] = gMonIcon_Llamose,
    [SPECIES_FATTE] = gMonIcon_Fatte,
    [SPECIES_GLOTTEN] = gMonIcon_Glotten,
    [SPECIES_STULO] = gMonIcon_Stulo,
    [SPECIES_FUNGIO] = gMonIcon_Fungio,
    [SPECIES_SEMILLETO] = gMonIcon_Semilleto,
    [SPECIES_FLOCEPAN] = gMonIcon_Flocepan,
    [SPECIES_ARQUIDEA] = gMonIcon_Arquidea,
    [SPECIES_STREEK] = gMonIcon_Streek,
    [SPECIES_LOGGRE] = gMonIcon_Loggre,
    [SPECIES_CAPRITLE] = gMonIcon_Capritle,
    [SPECIES_DEERETLE] = gMonIcon_Deeretle,
    [SPECIES_ARMORITO] = gMonIcon_Armorito,
    [SPECIES_ARMORAZO] = gMonIcon_Armorazo,
    [SPECIES_ANKORI] = gMonIcon_Ankori,
    [SPECIES_FUREEP] = gMonIcon_Fureep,
    [SPECIES_PULSUL] = gMonIcon_Pulsul,
    [SPECIES_KOROPUL] = gMonIcon_Koropul,
    [SPECIES_DARKOON] = gMonIcon_Darkoon,
    [SPECIES_HUNTOON] = gMonIcon_Huntoon,
    [SPECIES_TIKIKA] = gMonIcon_Tikika,
    [SPECIES_TIKIRIKI] = gMonIcon_Tikiriki,
    [SPECIES_POOCHER] = gMonIcon_Poocher,
    [SPECIES_WAPPY] = gMonIcon_Wappy,
    [SPECIES_RIWOOF] = gMonIcon_Riwoof,
    [SPECIES_IVORO] = gMonIcon_Ivoro,
    [SPECIES_DREAMO] = gMonIcon_Dreamo,
    [SPECIES_MAMMARE] = gMonIcon_Mammare,
    [SPECIES_KANGO] = gMonIcon_Kango,
    [SPECIES_KINBOXO] = gMonIcon_Kinboxo,
    [SPECIES_PUNCHZO] = gMonIcon_Punchzo,
    [SPECIES_FENTEE] = gMonIcon_Fentee,
    [SPECIES_HELENTO] = gMonIcon_Helento,
    [SPECIES_HELECHOE] = gMonIcon_Helechoe,
    [SPECIES_PIKISH] = gMonIcon_Pikish,
    [SPECIES_LIONEGOSH] = gMonIcon_Lionegosh,
    [SPECIES_JONIC] = gMonIcon_Jonic,
    [SPECIES_DORIC] = gMonIcon_Doric,
    [SPECIES_CORINT] = gMonIcon_Corint,
    [SPECIES_FLACHOW] = gMonIcon_Flachow,
    [SPECIES_FURNING] = gMonIcon_Furning,
    [SPECIES_CRABBIX] = gMonIcon_Crabbix,
    [SPECIES_DZOIBIX] = gMonIcon_Dzoibix,
    [SPECIES_SPINGEN] = gMonIcon_Spingen,
    [SPECIES_DUOSGEN] = gMonIcon_Duosgen,
    [SPECIES_BLAHDALAH] = gMonIcon_Blahdalah,
    [SPECIES_BUBEL] = gMonIcon_Bubel,
    [SPECIES_SCENTBIRD] = gMonIcon_Scentbird,
    [SPECIES_NORION] = gMonIcon_Norion,
    [SPECIES_PHANTAN] = gMonIcon_Phantan,
    [SPECIES_SALAMA] = gMonIcon_Salama,
    [SPECIES_MANTIGA] = gMonIcon_Mantiga,
    [SPECIES_GALLUM] = gMonIcon_Gallum,
    [SPECIES_AIRDIV] = gMonIcon_Airdiv,
    [SPECIES_GAPPY] = gMonIcon_Gappy,
    [SPECIES_NINNIN] = gMonIcon_Ninnin,
    [SPECIES_SURHORN] = gMonIcon_Surhorn,
    [SPECIES_SHEGA] = gMonIcon_Shega,
    [SPECIES_ZEECO] = gMonIcon_Zeeco,
    [SPECIES_PSIRILLA] = gMonIcon_Psirilla,
    [SPECIES_MECHRAB] = gMonIcon_Mechrab,
    [SPECIES_BOBCRAB] = gMonIcon_Bobcrab,
    [SPECIES_SPIKI] = gMonIcon_Spiki,
    [SPECIES_ELIKO] = gMonIcon_Eliko,
    [SPECIES_SESPIRAL] = gMonIcon_Sespiral,
    [SPECIES_DENDRIRAL] = gMonIcon_Dendriral,
    [SPECIES_VOGOO] = gMonIcon_Vogoo,
    [SPECIES_MONKOODU] = gMonIcon_Monkoodu,
    [SPECIES_KLEVALT] = gMonIcon_Klevalt,
    [SPECIES_KLESUNG] = gMonIcon_Klesung,
    [SPECIES_SIKEDONKE] = gMonIcon_Sikedonke,
    [SPECIES_POWERGASS] = gMonIcon_Powergass,
    [SPECIES_PASQALL] = gMonIcon_Pasqall,
    [SPECIES_ROCORRODO] = gMonIcon_Rocorrodo,
    [SPECIES_CORNODRO] = gMonIcon_Cornodro,
    [SPECIES_KARIDARI] = gMonIcon_Karidari,
    [SPECIES_CAPTRUNKE] = gMonIcon_Captrunke,
    [SPECIES_BANKEDON] = gMonIcon_Bankedon,
    [SPECIES_PLURES] = gMonIcon_Plures,
    [SPECIES_DRACOON] = gMonIcon_Dracoon,
    [SPECIES_PISCY] = gMonIcon_Piscy,
    [SPECIES_DOLPHE] = gMonIcon_Dolphe,
    [SPECIES_PRAWBY] = gMonIcon_Prawby,
    [SPECIES_PRAWKING] = gMonIcon_Prawking,
    [SPECIES_BETHIN] = gMonIcon_Bethin,
    [SPECIES_BEETESPUK] = gMonIcon_Beetespuk,
    [SPECIES_SAXIMAUX] = gMonIcon_Saximaux,
    [SPECIES_EKTRON] = gMonIcon_Ektron,
    [SPECIES_GARSOOM] = gMonIcon_Garsoom,
    [SPECIES_TEJEMEJE] = gMonIcon_Tejemeje,
    [SPECIES_FURRAN] = gMonIcon_Furran,
    [SPECIES_THUNDISH] = gMonIcon_Thundish,
    [SPECIES_THUNDRAN] = gMonIcon_Thundran,
    [SPECIES_SHACKER] = gMonIcon_Shacker,
    [SPECIES_EYENDY] = gMonIcon_Eyendy,
    [SPECIES_CWABAY] = gMonIcon_Cwabay,
    [SPECIES_WETWAY] = gMonIcon_Wetway,
    [SPECIES_JOYLWAY] = gMonIcon_Joylway,
    [SPECIES_HEATWAY] = gMonIcon_Heatway,
    [SPECIES_ARBELUC] = gMonIcon_Arbeluc,
    [SPECIES_SPIRAULIX] = gMonIcon_Spiraulix,
    [SPECIES_MESSAURIX] = gMonIcon_Messaurix,
    [SPECIES_FISHIX] = gMonIcon_Fishix,
    [SPECIES_CEFASOKIX] = gMonIcon_Cefasokix,
    [SPECIES_BEAKODORON] = gMonIcon_Beakodoron,
    [SPECIES_BOULTAN] = gMonIcon_Boultan,
    [SPECIES_BEREUGA] = gMonIcon_Bereuga,
    [SPECIES_EMETRIK] = gMonIcon_Emetrik,
    [SPECIES_PARATIKI] = gMonIcon_Paratiki,
    [SPECIES_MITHEDAON] = gMonIcon_Mithedaon,
    [SPECIES_WHIRLDRAON] = gMonIcon_Whirldraon,
    [SPECIES_MIGHTDRA] = gMonIcon_Mightdra,
    [SPECIES_ZENGREDSE] = gMonIcon_Zengredse,
    [SPECIES_WIAMI] = gMonIcon_Wiami,
    [SPECIES_POTAC] = gMonIcon_Potac,
    [SPECIES_TUBIRATO] = gMonIcon_Tubirato,
    [SPECIES_OGRITATO] = gMonIcon_Ogritato,
    [SPECIES_LAVLON] = gMonIcon_Lavlon,
    [SPECIES_MAGBOL] = gMonIcon_Magbol,
    [SPECIES_CANLAVA] = gMonIcon_Canlava,
    [SPECIES_SHELLDAN] = gMonIcon_Shelldan,
    [SPECIES_LICKA] = gMonIcon_Licka,
    [SPECIES_TONGRITO] = gMonIcon_Tongrito,
    [SPECIES_FURBEE] = gMonIcon_Furbee,
    [SPECIES_MORKIBIA] = gMonIcon_Morkibia,
    [SPECIES_KIWIRAWA] = gMonIcon_Kiwirawa,
    [SPECIES_KIAWARIWA] = gMonIcon_Kiawariwa,
    [SPECIES_BZBY] = gMonIcon_Bzby,
    [SPECIES_KWIMBEE] = gMonIcon_Kwimbee,
    [SPECIES_VERPILLAR] = gMonIcon_Verpillar,
    [SPECIES_TRIWORN] = gMonIcon_Triworn,
    [SPECIES_TOSTOL] = gMonIcon_Tostol,
    [SPECIES_ELORU] = gMonIcon_Eloru,
    [SPECIES_AENGUILE] = gMonIcon_Aenguile,
    [SPECIES_GUSVOLTS] = gMonIcon_Gusvolts,
    [SPECIES_AIRI] = gMonIcon_Airi,
    [SPECIES_FOOKID] = gMonIcon_Fookid,
    [SPECIES_MADNUT] = gMonIcon_Madnut,
    [SPECIES_WOODIRD] = gMonIcon_Woodird,
    [SPECIES_FREION] = gMonIcon_Freion,
    [SPECIES_CORONNEO] = gMonIcon_Coronneo,
    [SPECIES_TEAMON] = gMonIcon_Teamon,
    [SPECIES_GRASSPARK] = gMonIcon_Grasspark,
    [SPECIES_SOOREGAT] = gMonIcon_Sooregat,
    [SPECIES_FRUCPAO] = gMonIcon_Frucpao,
    [SPECIES_BEAVON] = gMonIcon_Beavon,
    [SPECIES_UMBEAVELLA] = gMonIcon_Umbeavella,
    [SPECIES_COCCNUTO] = gMonIcon_Coccnuto,
    [SPECIES_PITDOG] = gMonIcon_Pitdog,
    [SPECIES_SPROOF] = gMonIcon_Sproof,
    [SPECIES_PEATOOF] = gMonIcon_Peatoof,
    [SPECIES_IVIDIGI] = gMonIcon_Ividigi,
    [SPECIES_BONGON] = gMonIcon_Bongon,
    [SPECIES_THINKOWER] = gMonIcon_Thinkower,
    [SPECIES_FLATHINKER] = gMonIcon_Flathinker,
    [SPECIES_TAERMITY] = gMonIcon_Taermity,
    [SPECIES_RACEVISH] = gMonIcon_Racevish,
    [SPECIES_LODDISH] = gMonIcon_Loddish,
    [SPECIES_BLOSWAY] = gMonIcon_Blosway,
    [SPECIES_INDINNY] = gMonIcon_Indinny,
    [SPECIES_TANKOO] = gMonIcon_Tankoo,
    [SPECIES_CRAPRAX] = gMonIcon_Craprax,
    [SPECIES_MAGIKEN] = gMonIcon_Magiken,
    [SPECIES_CORNSCRIPT] = gMonIcon_Cornscript,
    [SPECIES_MEDRAKE] = gMonIcon_Medrake,
    [SPECIES_ZHIPO] = gMonIcon_Zhipo,
    [SPECIES_MOROBERRY] = gMonIcon_Moroberry,
    [SPECIES_BOONGORY] = gMonIcon_Boongory,
    [SPECIES_BLUDLOP] = gMonIcon_Bludlop,
    [SPECIES_VAMKIRI] = gMonIcon_Vamkiri,
    [SPECIES_SHELCUAL] = gMonIcon_Shelcual,
    [SPECIES_GRECODALE] = gMonIcon_Grecodale,
    [SPECIES_ALLIGRALE] = gMonIcon_Alligrale,
    [SPECIES_BELLYO] = gMonIcon_Bellyo,
    [SPECIES_DRILLUK] = gMonIcon_Drilluk,
    [SPECIES_SANGAI] = gMonIcon_Sangai,
    [SPECIES_BETAL] = gMonIcon_Betal,
    [SPECIES_DEEMP] = gMonIcon_Deemp,
    [SPECIES_TRUFKIP] = gMonIcon_Trufkip,
    [SPECIES_TRUFFALO] = gMonIcon_Truffalo,
    [SPECIES_BURNCO] = gMonIcon_Burnco,
    [SPECIES_FLAMECO] = gMonIcon_Flameco,
    [SPECIES_HURGOOSE] = gMonIcon_Hurgoose,
    [SPECIES_DONIGONI] = gMonIcon_Donigoni,
    [SPECIES_FLYSH] = gMonIcon_Flysh,
    [SPECIES_TRODIC] = gMonIcon_Trodic,
    [SPECIES_TIDALO] = gMonIcon_Tidalo,
    [SPECIES_POLBEAR] = gMonIcon_Polbear,
    [SPECIES_ARBATROSS] = gMonIcon_Arbatross,
    [SPECIES_SNEETCHY] = gMonIcon_Sneetchy,
    [SPECIES_GAREDAR] = gMonIcon_Garedar,
    [SPECIES_FARIZARD] = gMonIcon_Farizard,
    [SPECIES_DRALULA] = gMonIcon_Dralula,
    [SPECIES_BERNARDOG] = gMonIcon_Bernardog,
    [SPECIES_RESCUDOG] = gMonIcon_Rescudog,
    [SPECIES_EMREV] = gMonIcon_Emrev,
    [SPECIES_GRAZILLA] = gMonIcon_Grazilla,
    [SPECIES_NINJICE] = gMonIcon_Ninjice,
    [SPECIES_AZTAKLE] = gMonIcon_Aztakle,
    [SPECIES_CHINNAKLE] = gMonIcon_Chinnakle,
    [SPECIES_JARXIMAUX] = gMonIcon_Jarximaux,
    [SPECIES_ETOD] = gMonIcon_Etod,
    [SPECIES_TARSONY] = gMonIcon_Tarsony,
    [SPECIES_GURTAN] = gMonIcon_Gurtan,
    [SPECIES_CONQARI] = gMonIcon_Conqari,
    [SPECIES_TITATOAD] = gMonIcon_Titatoad,
    [SPECIES_TITAFROTA] = gMonIcon_Titafrota,
    [SPECIES_TITALLAMA] = gMonIcon_Titallama,
    [SPECIES_CROGRONK] = gMonIcon_Crogronk,
    [SPECIES_SKANKRIN] = gMonIcon_Skankrin,
    [SPECIES_BAESTALIX] = gMonIcon_Baestalix,
    [SPECIES_VIVACZO] = gMonIcon_Vivaczo,
    [SPECIES_SHADDIRE] = gMonIcon_Shaddire,
    [SPECIES_MOTHATURA] = gMonIcon_Mothatura,
    [SPECIES_SEEGG] = gMonIcon_Seegg,
    [SPECIES_FLOWABY] = gMonIcon_Flowaby,
    [SPECIES_JARDINO] = gMonIcon_Jardino,
    [SPECIES_FIREGG] = gMonIcon_Firegg,
    [SPECIES_EMBABY] = gMonIcon_Embaby,
    [SPECIES_TYRADINO] = gMonIcon_Tyradino,
    [SPECIES_AQUEGG] = gMonIcon_Aquegg,
    [SPECIES_ORNABY] = gMonIcon_Ornaby,
    [SPECIES_OCEADINO] = gMonIcon_Oceadino,
    [SPECIES_SEVER] = gMonIcon_Sever,
    [SPECIES_AYEWIRAZ] = gMonIcon_Ayewiraz,
    [SPECIES_SQUIRRITI] = gMonIcon_Squirriti,
    [SPECIES_ACORNEL] = gMonIcon_Acornel,
    [SPECIES_LARVLY] = gMonIcon_Larvly,
    [SPECIES_CRICOON] = gMonIcon_Cricoon,
    [SPECIES_CRICRIT] = gMonIcon_Cricrit,
    [SPECIES_COMPOSCOON] = gMonIcon_Composcoon,
    [SPECIES_FLYNFLY] = gMonIcon_Flynfly,
    [SPECIES_WEEDO] = gMonIcon_Weedo,
    [SPECIES_FLOSEA] = gMonIcon_Flosea,
    [SPECIES_WEEDALGU] = gMonIcon_Weedalgu,
    [SPECIES_CACTINO] = gMonIcon_Cactino,
    [SPECIES_CACUTU] = gMonIcon_Cacutu,
    [SPECIES_DESSERTEA] = gMonIcon_Dessertea,
    [SPECIES_REABARI] = gMonIcon_Reabari,
    [SPECIES_RUYCANTOR] = gMonIcon_Ruycantor,
    [SPECIES_BOLICHANO] = gMonIcon_Bolichano,
    [SPECIES_PELICHEN] = gMonIcon_Pelichen,
    [SPECIES_HAMET] = gMonIcon_Hamet,
    [SPECIES_RATELO] = gMonIcon_Ratelo,
    [SPECIES_PSIMOUSE] = gMonIcon_Psimouse,
    [SPECIES_HOVEBUG] = gMonIcon_Hovebug,
    [SPECIES_PLANEBUG] = gMonIcon_Planebug,
    [SPECIES_STRAWBAYA] = gMonIcon_Strawbaya,
    [SPECIES_DENDROCK] = gMonIcon_Dendrock,
    [SPECIES_RONSLEPT] = gMonIcon_Ronslept,
    [SPECIES_LEIRAO] = gMonIcon_Leirao,
    [SPECIES_DORLIRON] = gMonIcon_Dorliron,
    [SPECIES_GUSTANO] = gMonIcon_Gustano,
    [SPECIES_DUOSTANO] = gMonIcon_Duostano,
    [SPECIES_PHICO] = gMonIcon_Phico,
    [SPECIES_TYNIGON] = gMonIcon_Tynigon,
    [SPECIES_BALAGON] = gMonIcon_Balagon,
    [SPECIES_IGUAGON] = gMonIcon_Iguagon,
    [SPECIES_ENERGIZ] = gMonIcon_Energiz,
    [SPECIES_MUSCLELC] = gMonIcon_Musclelc,
    [SPECIES_BEAVY] = gMonIcon_Beavy,
    [SPECIES_DEPRIP] = gMonIcon_Deprip,
    [SPECIES_BABOS] = gMonIcon_Babos,
    [SPECIES_OSOE] = gMonIcon_Osoe,
    [SPECIES_FATUBE] = gMonIcon_Fatube,
    [SPECIES_HOOLEY] = gMonIcon_Hooley,
    [SPECIES_OPAIL] = gMonIcon_Opail,
    [SPECIES_HOMPALON] = gMonIcon_Hompalon,
    [SPECIES_GEMMAL] = gMonIcon_Gemmal,
    [SPECIES_MINDUM] = gMonIcon_Mindum,
    [SPECIES_MINADOOM] = gMonIcon_Minadoom,
    [SPECIES_PLUG_OINK] = gMonIcon_PlugOink,
    [SPECIES_SPIG] = gMonIcon_Spig,
    [SPECIES_AMEDE] = gMonIcon_Amede,
    [SPECIES_AMEDI] = gMonIcon_Amedi,
    [SPECIES_ARMAY] = gMonIcon_Armay,
    [SPECIES_ARMSTORM] = gMonIcon_Armstorm,
    [SPECIES_FAIROOT] = gMonIcon_Fairoot,
    [SPECIES_SIMPLEON] = gMonIcon_Simpleon,
    [SPECIES_DOBLEON] = gMonIcon_Dobleon,
    [SPECIES_AWHOL] = gMonIcon_Awhol,
    [SPECIES_WHOLA] = gMonIcon_Whola,
    [SPECIES_COLOSSIO] = gMonIcon_Colossio,
    [SPECIES_DESCOMUNE] = gMonIcon_Descomune,
    [SPECIES_LLAMAYAMA] = gMonIcon_Llamayama,
    [SPECIES_CHIMNEYAMA] = gMonIcon_Chimneyama,
    [SPECIES_COALCHAR] = gMonIcon_Coalchar,
    [SPECIES_TIGAT] = gMonIcon_Tigat,
    [SPECIES_TIGATOR] = gMonIcon_Tigator,
    [SPECIES_BOUNNY] = gMonIcon_Bounny,
    [SPECIES_PROGON] = gMonIcon_Progon,
    [SPECIES_RUBYGON] = gMonIcon_Rubygon,
    [SPECIES_SAPHIREGON] = gMonIcon_Saphiregon,
    [SPECIES_APINEP] = gMonIcon_Apinep,
    [SPECIES_PINARK] = gMonIcon_Pinark,
    [SPECIES_JACKAN] = gMonIcon_Jackan,
    [SPECIES_LOTBIRD] = gMonIcon_Lotbird,
    [SPECIES_COPYKATTE] = gMonIcon_Copykatte,
    [SPECIES_ONIKE] = gMonIcon_Onike,
    [SPECIES_CLOSTAR] = gMonIcon_Clostar,
    [SPECIES_STARGO] = gMonIcon_Stargo,
    [SPECIES_SOIE] = gMonIcon_Soie,
    [SPECIES_CORONGORI] = gMonIcon_Corongori,
    [SPECIES_SEAROKET] = gMonIcon_Searoket,
    [SPECIES_HELIXET] = gMonIcon_Helixet,
    [SPECIES_GODUCK] = gMonIcon_Goduck,
    [SPECIES_DUKAMID] = gMonIcon_Dukamid,
    [SPECIES_TORIDO] = gMonIcon_Torido,
    [SPECIES_DOTORI] = gMonIcon_Dotori,
    [SPECIES_ENYENDRODE] = gMonIcon_Enyendrode,
    [SPECIES_MONGOSTRE] = gMonIcon_Mongostre,
    [SPECIES_ICISH] = gMonIcon_Icish,
    [SPECIES_FREECH] = gMonIcon_Freech,
    [SPECIES_KOTOKABE] = gMonIcon_Kotokabe,
    [SPECIES_MIMIKAT] = gMonIcon_Mimikat,
    [SPECIES_CATALON] = gMonIcon_Catalon,
    [SPECIES_MAZALON] = gMonIcon_Mazalon,
    [SPECIES_GUINETTE] = gMonIcon_Guinette,
    [SPECIES_WOOPET] = gMonIcon_Woopet,
    [SPECIES_LIOFANG] = gMonIcon_Liofang,
    [SPECIES_GRITESPEC] = gMonIcon_Gritespec,
    [SPECIES_AGOIR] = gMonIcon_Agoir,
    [SPECIES_BOGUON] = gMonIcon_Boguon,
    [SPECIES_SPINWING] = gMonIcon_Spinwing,
    [SPECIES_BOBEGUIN] = gMonIcon_Bobeguin,
    [SPECIES_COLDCHICK] = gMonIcon_Coldchick,
    [SPECIES_FREEZOCK] = gMonIcon_Freezock,
    [SPECIES_COTTOSTER] = gMonIcon_Cottoster,
    [SPECIES_BERCHI] = gMonIcon_Berchi,
    [SPECIES_MEJIYONSON] = gMonIcon_Mejiyonson,
    [SPECIES_LOAPA] = gMonIcon_Loapa,
    [SPECIES_MONKOOR] = gMonIcon_Monkoor,
    [SPECIES_TINCRAB] = gMonIcon_Tincrab,
    [SPECIES_DRISTAL] = gMonIcon_Dristal,
    [SPECIES_FEEGON] = gMonIcon_Feegon,
    [SPECIES_DRAHAGO] = gMonIcon_Drahago,
    [SPECIES_TENRY] = gMonIcon_Tenry,
    [SPECIES_WRESTORO] = gMonIcon_Wrestoro,
    [SPECIES_WRESTMILK] = gMonIcon_Wrestmilk,
    [SPECIES_MOLEBAS] = gMonIcon_Molebas,
    [SPECIES_DUGOBAS] = gMonIcon_Dugobas,
    [SPECIES_LAPIBAS] = gMonIcon_Lapibas,
    [SPECIES_ORDKIP] = gMonIcon_Ordkip,
    [SPECIES_TANORD] = gMonIcon_Tanord,
    [SPECIES_KAOMARE] = gMonIcon_Kaomare,
    [SPECIES_KAOSUNE] = gMonIcon_Kaosune,
    [SPECIES_PEEZGAL] = gMonIcon_Peezgal,
    [SPECIES_KARENDI] = gMonIcon_Karendi,
    [SPECIES_GAROTAO] = gMonIcon_Garotao,
    [SPECIES_EGG] = gMonIcon_Chapebaya,
};

const u8 gMonIconPaletteIndices[] =
{
    [SPECIES_NONE] = 0,
    [SPECIES_BULBASAUR] = 1,
    [SPECIES_IVYSAUR] = 1,
    [SPECIES_VENUSAUR] = 1,
    [SPECIES_CHARMANDER] = 0,
    [SPECIES_CHARMELEON] = 0,
    [SPECIES_CHARIZARD] = 0,
    [SPECIES_SQUIRTLE] = 0,
    [SPECIES_WARTORTLE] = 2,
    [SPECIES_BLASTOISE] = 2,
    [SPECIES_CATERPIE] = 1,
    [SPECIES_METAPOD] = 1,
    [SPECIES_BUTTERFREE] = 0,
    [SPECIES_WEEDLE] = 1,
    [SPECIES_KAKUNA] = 0,
    [SPECIES_BEEDRILL] = 2,
    [SPECIES_PIDGEY] = 0,
    [SPECIES_PIDGEOTTO] = 0,
    [SPECIES_PIDGEOT] = 0,
    [SPECIES_RATTATA] = 2,
    [SPECIES_RATICATE] = 1,
    [SPECIES_SPEAROW] = 2,
    [SPECIES_FEAROW] = 0,
    [SPECIES_EKANS] = 2,
    [SPECIES_ARBOK] = 2,
    [SPECIES_PIKACHU] = 0,
    [SPECIES_RAICHU] = 2,
    [SPECIES_SANDSHREW] = 2,
    [SPECIES_SANDSLASH] = 2,
    [SPECIES_NIDORAN_F] = 2,
    [SPECIES_NIDORINA] = 2,
    [SPECIES_NIDOQUEEN] = 2,
    [SPECIES_NIDORAN_M] = 2,
    [SPECIES_NIDORINO] = 2,
    [SPECIES_NIDOKING] = 2,
    [SPECIES_CLEFAIRY] = 0,
    [SPECIES_CLEFABLE] = 0,
    [SPECIES_VULPIX] = 2,
    [SPECIES_NINETALES] = 1,
    [SPECIES_JIGGLYPUFF] = 0,
    [SPECIES_WIGGLYTUFF] = 0,
    [SPECIES_ZUBAT] = 2,
    [SPECIES_GOLBAT] = 2,
    [SPECIES_ODDISH] = 1,
    [SPECIES_GLOOM] = 0,
    [SPECIES_VILEPLUME] = 0,
    [SPECIES_PARAS] = 0,
    [SPECIES_PARASECT] = 0,
    [SPECIES_VENONAT] = 0,
    [SPECIES_VENOMOTH] = 2,
    [SPECIES_DIGLETT] = 1,
    [SPECIES_DUGTRIO] = 2,
    [SPECIES_MEOWTH] = 1,
    [SPECIES_PERSIAN] = 1,
    [SPECIES_PSYDUCK] = 1,
    [SPECIES_GOLDUCK] = 2,
    [SPECIES_MANKEY] = 1,
    [SPECIES_PRIMEAPE] = 2,
    [SPECIES_GROWLITHE] = 0,
    [SPECIES_ARCANINE] = 0,
    [SPECIES_POLIWAG] = 0,
    [SPECIES_POLIWHIRL] = 0,
    [SPECIES_POLIWRATH] = 0,
    [SPECIES_ABRA] = 2,
    [SPECIES_KADABRA] = 2,
    [SPECIES_ALAKAZAM] = 2,
    [SPECIES_MACHOP] = 2,
    [SPECIES_MACHOKE] = 2,
    [SPECIES_MACHAMP] = 0,
    [SPECIES_BELLSPROUT] = 1,
    [SPECIES_WEEPINBELL] = 1,
    [SPECIES_VICTREEBEL] = 1,
    [SPECIES_TENTACOOL] = 2,
    [SPECIES_TENTACRUEL] = 2,
    [SPECIES_GEODUDE] = 1,
    [SPECIES_GRAVELER] = 1,
    [SPECIES_GOLEM] = 1,
    [SPECIES_PONYTA] = 0,
    [SPECIES_RAPIDASH] = 0,
    [SPECIES_SLOWPOKE] = 0,
    [SPECIES_SLOWBRO] = 0,
    [SPECIES_MAGNEMITE] = 0,
    [SPECIES_MAGNETON] = 0,
    [SPECIES_FARFETCHD] = 1,
    [SPECIES_DODUO] = 2,
    [SPECIES_DODRIO] = 2,
    [SPECIES_SEEL] = 2,
    [SPECIES_DEWGONG] = 2,
    [SPECIES_GRIMER] = 2,
    [SPECIES_MUK] = 2,
    [SPECIES_SHELLDER] = 2,
    [SPECIES_CLOYSTER] = 2,
    [SPECIES_GASTLY] = 2,
    [SPECIES_HAUNTER] = 2,
    [SPECIES_GENGAR] = 2,
    [SPECIES_ONIX] = 2,
    [SPECIES_DROWZEE] = 2,
    [SPECIES_HYPNO] = 1,
    [SPECIES_KRABBY] = 2,
    [SPECIES_KINGLER] = 2,
    [SPECIES_VOLTORB] = 0,
    [SPECIES_ELECTRODE] = 0,
    [SPECIES_EXEGGCUTE] = 0,
    [SPECIES_EXEGGUTOR] = 1,
    [SPECIES_CUBONE] = 1,
    [SPECIES_MAROWAK] = 1,
    [SPECIES_HITMONLEE] = 2,
    [SPECIES_HITMONCHAN] = 0,
    [SPECIES_LICKITUNG] = 0,
    [SPECIES_KOFFING] = 2,
    [SPECIES_WEEZING] = 2,
    [SPECIES_RHYHORN] = 1,
    [SPECIES_RHYDON] = 1,
    [SPECIES_CHANSEY] = 0,
    [SPECIES_TANGELA] = 0,
    [SPECIES_KANGASKHAN] = 1,
    [SPECIES_HORSEA] = 0,
    [SPECIES_SEADRA] = 0,
    [SPECIES_GOLDEEN] = 0,
    [SPECIES_SEAKING] = 0,
    [SPECIES_STARYU] = 2,
    [SPECIES_STARMIE] = 2,
    [SPECIES_MR_MIME] = 0,
    [SPECIES_SCYTHER] = 1,
    [SPECIES_JYNX] = 2,
    [SPECIES_ELECTABUZZ] = 1,
    [SPECIES_MAGMAR] = 0,
    [SPECIES_PINSIR] = 2,
    [SPECIES_TAUROS] = 2,
    [SPECIES_MAGIKARP] = 0,
    [SPECIES_GYARADOS] = 0,
    [SPECIES_LAPRAS] = 2,
    [SPECIES_DITTO] = 2,
    [SPECIES_EEVEE] = 2,
    [SPECIES_VAPOREON] = 0,
    [SPECIES_JOLTEON] = 0,
    [SPECIES_FLAREON] = 0,
    [SPECIES_PORYGON] = 0,
    [SPECIES_OMANYTE] = 0,
    [SPECIES_OMASTAR] = 0,
    [SPECIES_KABUTO] = 2,
    [SPECIES_KABUTOPS] = 2,
    [SPECIES_AERODACTYL] = 0,
    [SPECIES_SNORLAX] = 1,
    [SPECIES_ARTICUNO] = 0,
    [SPECIES_ZAPDOS] = 0,
    [SPECIES_MOLTRES] = 0,
    [SPECIES_DRATINI] = 0,
    [SPECIES_DRAGONAIR] = 0,
    [SPECIES_DRAGONITE] = 2,
    [SPECIES_MEWTWO] = 2,
    [SPECIES_MEW] = 0,
    [SPECIES_CHIKORITA] = 1,
    [SPECIES_BAYLEEF] = 1,
    [SPECIES_MEGANIUM] = 1,
    [SPECIES_CYNDAQUIL] = 0,
    [SPECIES_QUILAVA] = 0,
    [SPECIES_TYPHLOSION] = 0,
    [SPECIES_TOTODILE] = 2,
    [SPECIES_CROCONAW] = 2,
    [SPECIES_FERALIGATR] = 0,
    [SPECIES_SENTRET] = 2,
    [SPECIES_FURRET] = 2,
    [SPECIES_HOOTHOOT] = 2,
    [SPECIES_NOCTOWL] = 2,
    [SPECIES_LEDYBA] = 0,
    [SPECIES_LEDIAN] = 0,
    [SPECIES_SPINARAK] = 1,
    [SPECIES_ARIADOS] = 0,
    [SPECIES_CROBAT] = 2,
    [SPECIES_CHINCHOU] = 2,
    [SPECIES_LANTURN] = 0,
    [SPECIES_PICHU] = 0,
    [SPECIES_CLEFFA] = 0,
    [SPECIES_IGGLYBUFF] = 1,
    [SPECIES_TOGEPI] = 2,
    [SPECIES_TOGETIC] = 2,
    [SPECIES_NATU] = 0,
    [SPECIES_XATU] = 0,
    [SPECIES_MAREEP] = 2,
    [SPECIES_FLAAFFY] = 0,
    [SPECIES_AMPHAROS] = 0,
    [SPECIES_BELLOSSOM] = 1,
    [SPECIES_MARILL] = 2,
    [SPECIES_AZUMARILL] = 2,
    [SPECIES_SUDOWOODO] = 1,
    [SPECIES_POLITOED] = 1,
    [SPECIES_HOPPIP] = 1,
    [SPECIES_SKIPLOOM] = 1,
    [SPECIES_JUMPLUFF] = 2,
    [SPECIES_AIPOM] = 2,
    [SPECIES_SUNKERN] = 1,
    [SPECIES_SUNFLORA] = 1,
    [SPECIES_YANMA] = 1,
    [SPECIES_WOOPER] = 0,
    [SPECIES_QUAGSIRE] = 0,
    [SPECIES_ESPEON] = 2,
    [SPECIES_UMBREON] = 2,
    [SPECIES_MURKROW] = 2,
    [SPECIES_SLOWKING] = 0,
    [SPECIES_MISDREAVUS] = 0,
    [SPECIES_UNOWN] = 0,
    [SPECIES_WOBBUFFET] = 0,
    [SPECIES_GIRAFARIG] = 0,
    [SPECIES_PINECO] = 0,
    [SPECIES_FORRETRESS] = 2,
    [SPECIES_DUNSPARCE] = 2,
    [SPECIES_GLIGAR] = 2,
    [SPECIES_STEELIX] = 0,
    [SPECIES_SNUBBULL] = 0,
    [SPECIES_GRANBULL] = 2,
    [SPECIES_QWILFISH] = 2,
    [SPECIES_SCIZOR] = 0,
    [SPECIES_SHUCKLE] = 1,
    [SPECIES_HERACROSS] = 2,
    [SPECIES_SNEASEL] = 0,
    [SPECIES_TEDDIURSA] = 0,
    [SPECIES_URSARING] = 2,
    [SPECIES_SLUGMA] = 0,
    [SPECIES_MAGCARGO] = 0,
    [SPECIES_SWINUB] = 2,
    [SPECIES_PILOSWINE] = 2,
    [SPECIES_CORSOLA] = 0,
    [SPECIES_REMORAID] = 0,
    [SPECIES_OCTILLERY] = 0,
    [SPECIES_DELIBIRD] = 0,
    [SPECIES_MANTINE] = 2,
    [SPECIES_SKARMORY] = 0,
    [SPECIES_HOUNDOUR] = 0,
    [SPECIES_HOUNDOOM] = 0,
    [SPECIES_KINGDRA] = 0,
    [SPECIES_PHANPY] = 0,
    [SPECIES_DONPHAN] = 0,
    [SPECIES_PORYGON2] = 0,
    [SPECIES_STANTLER] = 2,
    [SPECIES_SMEARGLE] = 1,
    [SPECIES_TYROGUE] = 2,
    [SPECIES_HITMONTOP] = 2,
    [SPECIES_SMOOCHUM] = 1,
    [SPECIES_ELEKID] = 1,
    [SPECIES_MAGBY] = 1,
    [SPECIES_MILTANK] = 1,
    [SPECIES_BLISSEY] = 1,
    [SPECIES_RAIKOU] = 0,
    [SPECIES_ENTEI] = 2,
    [SPECIES_SUICUNE] = 0,
    [SPECIES_LARVITAR] = 1,
    [SPECIES_PUPITAR] = 0,
    [SPECIES_TYRANITAR] = 1,
    [SPECIES_LUGIA] = 0,
    [SPECIES_HO_OH] = 1,
    [SPECIES_CELEBI] = 1,
    [SPECIES_OLD_UNOWN_B] = 0,
    [SPECIES_OLD_UNOWN_C] = 0,
    [SPECIES_OLD_UNOWN_D] = 0,
    [SPECIES_OLD_UNOWN_E] = 0,
    [SPECIES_OLD_UNOWN_F] = 0,
    [SPECIES_OLD_UNOWN_G] = 0,
    [SPECIES_OLD_UNOWN_H] = 0,
    [SPECIES_OLD_UNOWN_I] = 0,
    [SPECIES_OLD_UNOWN_J] = 0,
    [SPECIES_OLD_UNOWN_K] = 0,
    [SPECIES_OLD_UNOWN_L] = 0,
    [SPECIES_OLD_UNOWN_M] = 0,
    [SPECIES_OLD_UNOWN_N] = 0,
    [SPECIES_OLD_UNOWN_O] = 0,
    [SPECIES_OLD_UNOWN_P] = 0,
    [SPECIES_OLD_UNOWN_Q] = 0,
    [SPECIES_OLD_UNOWN_R] = 0,
    [SPECIES_OLD_UNOWN_S] = 0,
    [SPECIES_OLD_UNOWN_T] = 0,
    [SPECIES_OLD_UNOWN_U] = 0,
    [SPECIES_OLD_UNOWN_V] = 0,
    [SPECIES_OLD_UNOWN_W] = 0,
    [SPECIES_OLD_UNOWN_X] = 0,
    [SPECIES_OLD_UNOWN_Y] = 0,
    [SPECIES_OLD_UNOWN_Z] = 0,
    [SPECIES_TREECKO] = 1,
    [SPECIES_GROVYLE] = 0,
    [SPECIES_SCEPTILE] = 1,
    [SPECIES_TORCHIC] = 0,
    [SPECIES_COMBUSKEN] = 0,
    [SPECIES_BLAZIKEN] = 0,
    [SPECIES_MUDKIP] = 0,
    [SPECIES_MARSHTOMP] = 0,
    [SPECIES_SWAMPERT] = 0,
    [SPECIES_POOCHYENA] = 2,
    [SPECIES_MIGHTYENA] = 2,
    [SPECIES_ZIGZAGOON] = 2,
    [SPECIES_LINOONE] = 2,
    [SPECIES_WURMPLE] = 0,
    [SPECIES_SILCOON] = 2,
    [SPECIES_BEAUTIFLY] = 0,
    [SPECIES_CASCOON] = 2,
    [SPECIES_DUSTOX] = 1,
    [SPECIES_LOTAD] = 1,
    [SPECIES_LOMBRE] = 1,
    [SPECIES_LUDICOLO] = 1,
    [SPECIES_SEEDOT] = 1,
    [SPECIES_NUZLEAF] = 1,
    [SPECIES_SHIFTRY] = 0,
    [SPECIES_NINCADA] = 1,
    [SPECIES_NINJASK] = 1,
    [SPECIES_SHEDINJA] = 1,
    [SPECIES_TAILLOW] = 2,
    [SPECIES_SWELLOW] = 2,
    [SPECIES_SHROOMISH] = 1,
    [SPECIES_BRELOOM] = 1,
    [SPECIES_SPINDA] = 2,
    [SPECIES_WINGULL] = 0,
    [SPECIES_PELIPPER] = 0,
    [SPECIES_SURSKIT] = 2,
    [SPECIES_MASQUERAIN] = 0,
    [SPECIES_WAILMER] = 2,
    [SPECIES_WAILORD] = 0,
    [SPECIES_SKITTY] = 2,
    [SPECIES_DELCATTY] = 2,
    [SPECIES_KECLEON] = 1,
    [SPECIES_BALTOY] = 1,
    [SPECIES_CLAYDOL] = 0,
    [SPECIES_NOSEPASS] = 0,
    [SPECIES_TORKOAL] = 1,
    [SPECIES_SABLEYE] = 2,
    [SPECIES_BARBOACH] = 0,
    [SPECIES_WHISCASH] = 0,
    [SPECIES_LUVDISC] = 0,
    [SPECIES_CORPHISH] = 0,
    [SPECIES_CRAWDAUNT] = 0,
    [SPECIES_FEEBAS] = 2,
    [SPECIES_MILOTIC] = 0,
    [SPECIES_CARVANHA] = 0,
    [SPECIES_SHARPEDO] = 0,
    [SPECIES_TRAPINCH] = 0,
    [SPECIES_VIBRAVA] = 0,
    [SPECIES_FLYGON] = 0,
    [SPECIES_MAKUHITA] = 2,
    [SPECIES_HARIYAMA] = 1,
    [SPECIES_ELECTRIKE] = 1,
    [SPECIES_MANECTRIC] = 0,
    [SPECIES_NUMEL] = 1,
    [SPECIES_CAMERUPT] = 0,
    [SPECIES_SPHEAL] = 2,
    [SPECIES_SEALEO] = 2,
    [SPECIES_WALREIN] = 0,
    [SPECIES_CACNEA] = 1,
    [SPECIES_CACTURNE] = 1,
    [SPECIES_SNORUNT] = 2,
    [SPECIES_GLALIE] = 0,
    [SPECIES_LUNATONE] = 1,
    [SPECIES_SOLROCK] = 0,
    [SPECIES_AZURILL] = 2,
    [SPECIES_SPOINK] = 0,
    [SPECIES_GRUMPIG] = 2,
    [SPECIES_PLUSLE] = 0,
    [SPECIES_MINUN] = 0,
    [SPECIES_MAWILE] = 2,
    [SPECIES_MEDITITE] = 0,
    [SPECIES_MEDICHAM] = 0,
    [SPECIES_SWABLU] = 0,
    [SPECIES_ALTARIA] = 0,
    [SPECIES_WYNAUT] = 0,
    [SPECIES_DUSKULL] = 0,
    [SPECIES_DUSCLOPS] = 0,
    [SPECIES_ROSELIA] = 1,
    [SPECIES_SLAKOTH] = 2,
    [SPECIES_VIGOROTH] = 2,
    [SPECIES_SLAKING] = 2,
    [SPECIES_GULPIN] = 1,
    [SPECIES_SWALOT] = 2,
    [SPECIES_TROPIUS] = 1,
    [SPECIES_WHISMUR] = 0,
    [SPECIES_LOUDRED] = 2,
    [SPECIES_EXPLOUD] = 2,
    [SPECIES_CLAMPERL] = 0,
    [SPECIES_HUNTAIL] = 0,
    [SPECIES_GOREBYSS] = 0,
    [SPECIES_ABSOL] = 0,
    [SPECIES_SHUPPET] = 0,
    [SPECIES_BANETTE] = 0,
    [SPECIES_SEVIPER] = 2,
    [SPECIES_ZANGOOSE] = 0,
    [SPECIES_RELICANTH] = 1,
    [SPECIES_ARON] = 2,
    [SPECIES_LAIRON] = 2,
    [SPECIES_AGGRON] = 2,
    [SPECIES_CASTFORM] = 0,
    [SPECIES_VOLBEAT] = 0,
    [SPECIES_ILLUMISE] = 2,
    [SPECIES_LILEEP] = 2,
    [SPECIES_CRADILY] = 0,
    [SPECIES_ANORITH] = 0,
    [SPECIES_ARMALDO] = 0,
    [SPECIES_RALTS] = 1,
    [SPECIES_KIRLIA] = 1,
    [SPECIES_GARDEVOIR] = 1,
    [SPECIES_BAGON] = 2,
    [SPECIES_SHELGON] = 2,
    [SPECIES_SALAMENCE] = 0,
    [SPECIES_BELDUM] = 0,
    [SPECIES_METANG] = 0,
    [SPECIES_METAGROSS] = 0,
    [SPECIES_REGIROCK] = 2,
    [SPECIES_REGICE] = 2,
    [SPECIES_REGISTEEL] = 2,
    [SPECIES_KYOGRE] = 2,
    [SPECIES_GROUDON] = 0,
    [SPECIES_RAYQUAZA] = 1,
    [SPECIES_LATIAS] = 0,
    [SPECIES_LATIOS] = 2,
    [SPECIES_JIRACHI] = 0,
    [SPECIES_DEOXYS] = 0,
    [SPECIES_CHIMECHO] = 0,
    [SPECIES_EGG] = 1,
    [SPECIES_UNOWN_B] = 0,
    [SPECIES_UNOWN_C] = 0,
    [SPECIES_UNOWN_D] = 0,
    [SPECIES_UNOWN_E] = 0,
    [SPECIES_UNOWN_F] = 0,
    [SPECIES_UNOWN_G] = 0,
    [SPECIES_UNOWN_H] = 0,
    [SPECIES_UNOWN_I] = 0,
    [SPECIES_UNOWN_J] = 0,
    [SPECIES_UNOWN_K] = 0,
    [SPECIES_UNOWN_L] = 0,
    [SPECIES_UNOWN_M] = 0,
    [SPECIES_UNOWN_N] = 0,
    [SPECIES_UNOWN_O] = 0,
    [SPECIES_UNOWN_P] = 0,
    [SPECIES_UNOWN_Q] = 0,
    [SPECIES_UNOWN_R] = 0,
    [SPECIES_UNOWN_S] = 0,
    [SPECIES_UNOWN_T] = 0,
    [SPECIES_UNOWN_U] = 0,
    [SPECIES_UNOWN_V] = 0,
    [SPECIES_UNOWN_W] = 0,
    [SPECIES_UNOWN_X] = 0,
    [SPECIES_UNOWN_Y] = 0,
    [SPECIES_UNOWN_Z] = 0,
    [SPECIES_UNOWN_EMARK] = 0,
    [SPECIES_UNOWN_QMARK] = 0,
};

const struct SpritePalette gMonIconPaletteTable[] =
{
    { gMonIconPalettes[0], POKE_ICON_BASE_PAL_TAG + 0 },
    { gMonIconPalettes[1], POKE_ICON_BASE_PAL_TAG + 1 },
    { gMonIconPalettes[2], POKE_ICON_BASE_PAL_TAG + 2 },

// There are only 3 actual palettes. The following are unused
// and don't point to valid data.
    { gMonIconPalettes[3], POKE_ICON_BASE_PAL_TAG + 3 },
    { gMonIconPalettes[4], POKE_ICON_BASE_PAL_TAG + 4 },
    { gMonIconPalettes[5], POKE_ICON_BASE_PAL_TAG + 5 },
};

const struct OamData sMonIconOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
};

// fastest to slowest

static const union AnimCmd sAnim_0[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_1[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_2[] =
{
    ANIMCMD_FRAME(0, 14),
    ANIMCMD_FRAME(1, 14),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_3[] =
{
    ANIMCMD_FRAME(0, 22),
    ANIMCMD_FRAME(1, 22),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_4[] =
{
    ANIMCMD_FRAME(0, 29),
    ANIMCMD_FRAME(0, 29), // frame 0 is repeated
    ANIMCMD_JUMP(0),
};

const union AnimCmd *const sMonIconAnims[] =
{
    sAnim_0,
    sAnim_1,
    sAnim_2,
    sAnim_3,
    sAnim_4,
};

static const union AffineAnimCmd sAffineAnim_0[] =
{
    AFFINEANIMCMD_FRAME(0, 0, 0, 10),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_1[] =
{
    AFFINEANIMCMD_FRAME(-2, -2, 0, 122),
    AFFINEANIMCMD_END,
};

const union AffineAnimCmd *const sMonIconAffineAnims[] =
{
    sAffineAnim_0,
    sAffineAnim_1,
};

const u16 sSpriteImageSizes[3][4] =
{
    [ST_OAM_SQUARE] = 
    {
        [SPRITE_SIZE(8x8)]   =  0x20,
        [SPRITE_SIZE(16x16)] =  0x80,
        [SPRITE_SIZE(32x32)] = 0x200,
        [SPRITE_SIZE(64x64)] = 0x800,
    },
    [ST_OAM_H_RECTANGLE] = 
    {
        [SPRITE_SIZE(16x8)]  =  0x40,
        [SPRITE_SIZE(32x8)]  =  0x80,
        [SPRITE_SIZE(32x16)] = 0x100,
        [SPRITE_SIZE(64x32)] = 0x400,
    },
    [ST_OAM_V_RECTANGLE] = 
    {
        [SPRITE_SIZE(8x16)]  =  0x40,
        [SPRITE_SIZE(8x32)]  =  0x80,
        [SPRITE_SIZE(16x32)] = 0x100,
        [SPRITE_SIZE(32x64)] = 0x400,
    },
};

u8 CreateMonIcon(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, u32 personality, bool32 handleDeoxys)
{
    u8 spriteId;
    struct MonIconSpriteTemplate iconTemplate =
    {
        .oam = &sMonIconOamData,
        .image = GetMonIconPtr(species, personality, handleDeoxys),
        .anims = sMonIconAnims,
        .affineAnims = sMonIconAffineAnims,
        .callback = callback,
        .paletteTag = POKE_ICON_BASE_PAL_TAG + gMonIconPaletteIndices[species],
    };

    if (species > NUM_SPECIES)
        iconTemplate.paletteTag = POKE_ICON_BASE_PAL_TAG;

    spriteId = CreateMonIconSprite(&iconTemplate, x, y, subpriority);

    UpdateMonIconFrame(&gSprites[spriteId]);

    return spriteId;
}

u8 sub_80D2D78(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, bool32 extra)
{
    u8 spriteId;
    struct MonIconSpriteTemplate iconTemplate =
    {
        .oam = &sMonIconOamData,
        .image = NULL,
        .anims = sMonIconAnims,
        .affineAnims = sMonIconAffineAnims,
        .callback = callback,
        .paletteTag = POKE_ICON_BASE_PAL_TAG + gMonIconPaletteIndices[species],
    };

    iconTemplate.image = GetMonIconTiles(species, extra);
    spriteId = CreateMonIconSprite(&iconTemplate, x, y, subpriority);

    UpdateMonIconFrame(&gSprites[spriteId]);

    return spriteId;
}

u16 GetIconSpecies(u16 species, u32 personality)
{
    u16 result;

    if (species == SPECIES_UNOWN)
    {
        u16 letter = GetUnownLetterByPersonality(personality);
        if (letter == 0)
            letter = SPECIES_UNOWN;
        else
            letter += (SPECIES_UNOWN_B - 1);
        result = letter;
    }
    else
    {
        if (species > NUM_SPECIES)
            result = 260;
        else
            result = species;
    }

    return result;
}

u16 GetUnownLetterByPersonality(u32 personality)
{
    if (!personality)
        return 0;
    else
        return (((personality & 0x3000000) >> 18) | ((personality & 0x30000) >> 12) | ((personality & 0x300) >> 6) | (personality & 0x3)) % 0x1C;
}

u16 sub_80D2E84(u16 species)
{
    u16 value;

    if (MailSpeciesToSpecies(species, &value) == SPECIES_UNOWN)
    {
        if (value == 0)
            value += SPECIES_UNOWN;
        else
            value += (SPECIES_UNOWN_B - 1);
        return value;
    }
    else
    {
        if (species > (SPECIES_UNOWN_B - 1))
            species = SPECIES_OLD_UNOWN_J; // That's an oddly specific species.
        return GetIconSpecies(species, 0);
    }
}

const u8 *GetMonIconPtr(u16 species, u32 personality, bool32 handleDeoxys)
{
    return GetMonIconTiles(GetIconSpecies(species, personality), handleDeoxys);
}

void FreeAndDestroyMonIconSprite(struct Sprite *sprite)
{
    sub_80D328C(sprite);
}

void LoadMonIconPalettes(void)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(gMonIconPaletteTable); i++)
        LoadSpritePalette(&gMonIconPaletteTable[i]);
}

// unused
void SafeLoadMonIconPalette(u16 species)
{
    u8 palIndex;
    if (species > NUM_SPECIES)
        species = 260;
    palIndex = gMonIconPaletteIndices[species];
    if (IndexOfSpritePaletteTag(gMonIconPaletteTable[palIndex].tag) == 0xFF)
        LoadSpritePalette(&gMonIconPaletteTable[palIndex]);
}

void LoadMonIconPalette(u16 species)
{
    u8 palIndex = gMonIconPaletteIndices[species];
    if (IndexOfSpritePaletteTag(gMonIconPaletteTable[palIndex].tag) == 0xFF)
        LoadSpritePalette(&gMonIconPaletteTable[palIndex]);
}

void FreeMonIconPalettes(void)
{
    u8 i;
    for (i = 0; i < 6; i++)
        FreeSpritePaletteByTag(gMonIconPaletteTable[i].tag);
}

// unused
void SafeFreeMonIconPalette(u16 species)
{
    u8 palIndex;
    if (species > NUM_SPECIES)
        species = 260;
    palIndex = gMonIconPaletteIndices[species];
    FreeSpritePaletteByTag(gMonIconPaletteTable[palIndex].tag);
}

void FreeMonIconPalette(u16 species)
{
    u8 palIndex;
    palIndex = gMonIconPaletteIndices[species];
    FreeSpritePaletteByTag(gMonIconPaletteTable[palIndex].tag);
}

void SpriteCB_MonIcon(struct Sprite *sprite)
{
    UpdateMonIconFrame(sprite);
}

const u8* GetMonIconTiles(u16 species, bool32 handleDeoxys)
{
    const u8* iconSprite = gMonIconTable[species];
    if (species == SPECIES_DEOXYS && handleDeoxys == TRUE)
    {
        iconSprite = (const u8*)(0x400 + (u32)iconSprite); // use the specific Deoxys form icon (Speed in this case)
    }
    return iconSprite;
}

void sub_80D304C(u16 offset)
{
    s32 i;
    const struct SpritePalette* monIconPalettePtr;

    if (offset <= 0xA0)
    {
        monIconPalettePtr = gMonIconPaletteTable;
        for(i = 5; i >= 0; i--)
        {
            LoadPalette(monIconPalettePtr->data, offset, 0x20);
            offset += 0x10;
            monIconPalettePtr++;
        }
    }
}

u8 GetValidMonIconPalIndex(u16 species)
{
    if (species > NUM_SPECIES)
        species = 260;
    return gMonIconPaletteIndices[species];
}

u8 GetMonIconPaletteIndexFromSpecies(u16 species)
{
    return gMonIconPaletteIndices[species];
}

const u16* GetValidMonIconPalettePtr(u16 species)
{
    if (species > NUM_SPECIES)
        species = 260;
    return gMonIconPaletteTable[gMonIconPaletteIndices[species]].data;
}

u8 UpdateMonIconFrame(struct Sprite *sprite)
{
    u8 result = 0;

    if (sprite->animDelayCounter == 0)
    {
        s16 frame = sprite->anims[sprite->animNum][sprite->animCmdIndex].frame.imageValue;

        switch (frame)
        {
        case -1:
            break;
        case -2:
            sprite->animCmdIndex = 0;
            break;
        default:
            RequestSpriteCopy(
                // pointer arithmetic is needed to get the correct pointer to perform the sprite copy on.
                // because sprite->images is a struct def, it has to be casted to (u8 *) before any
                // arithmetic can be performed.
                (u8 *)sprite->images + (sSpriteImageSizes[sprite->oam.shape][sprite->oam.size] * frame),
                (u8 *)(OBJ_VRAM0 + sprite->oam.tileNum * TILE_SIZE_4BPP),
                sSpriteImageSizes[sprite->oam.shape][sprite->oam.size]);
            sprite->animDelayCounter = sprite->anims[sprite->animNum][sprite->animCmdIndex].frame.duration & 0xFF;
            sprite->animCmdIndex++;
            result = sprite->animCmdIndex;
            break;
        }
    }
    else
    {
        sprite->animDelayCounter--;
    }
    return result;
}

static u8 CreateMonIconSprite(struct MonIconSpriteTemplate *iconTemplate, s16 x, s16 y, u8 subpriority)
{
    u8 spriteId;

    struct SpriteFrameImage image = { NULL, sSpriteImageSizes[iconTemplate->oam->shape][iconTemplate->oam->size] };

    struct SpriteTemplate spriteTemplate =
    {
        .tileTag = 0xFFFF,
        .paletteTag = iconTemplate->paletteTag,
        .oam = iconTemplate->oam,
        .anims = iconTemplate->anims,
        .images = &image,
        .affineAnims = iconTemplate->affineAnims,
        .callback = iconTemplate->callback,
    };

    spriteId = CreateSprite(&spriteTemplate, x, y, subpriority);
    gSprites[spriteId].animPaused = TRUE;
    gSprites[spriteId].animBeginning = FALSE;
    gSprites[spriteId].images = (const struct SpriteFrameImage *)iconTemplate->image;
    return spriteId;
}

void sub_80D328C(struct Sprite *sprite)
{
    struct SpriteFrameImage image = { NULL, sSpriteImageSizes[sprite->oam.shape][sprite->oam.size] };
    sprite->images = &image;
    DestroySprite(sprite);
}

void SetPartyHPBarSprite(struct Sprite *sprite, u8 animNum)
{
    sprite->animNum = animNum;
    sprite->animDelayCounter = 0;
    sprite->animCmdIndex = 0;
}
