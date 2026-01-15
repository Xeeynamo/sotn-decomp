const gameMetadata = {
    "id": "sotn",
    "name": "Castlevania: Symphony of the Night",
    "links": [
        {
            "name": "Source Code",
            "url": "https://github.com/xeeynamo/sotn-decomp"
        },
        {
            "name": "Discord Server",
            "url": "https://sotn-discord.xee.dev/"
        },
    ],
    "labels": [
        {
            "id": "code",
            "name": "Coverage",
            "desc": "How much decompiled code covers the binary",
            "color": ""
        },
        {
            "id": "functions",
            "name": "Functions",
            "desc": "Amount of functions decompiled",
            "color": ""
        },
    ],
    "versions": [
        {
            "id": "us",
            "name": "PlayStation 1 US",
            "overlays": [
                "dra", "ric", "weapon",
                "stare", "stcat", "stcen", "stchi", "stdai", "stdre", "stlib", "stmad", "stno0", "stno1", "stno2", "stno3", "stno4", "stnp3", "stnz0", "stnz1", "stsel", "stst0", "sttop", "stwrp",
                "strare", "strtop", "strwrp",
                "bomar", "bobo4", "bobo6", "borbo3", "borbo5",
                "tt_000", "tt_001", "tt_002","tt_003", "tt_004"
            ]
        },
        {
            "id": "pspeu",
            "name": "PSP EU",
            "overlays": [
                "dra", "maria", "ric",
                "stare", "stcat", "stchi", "stdai", "stdre", "stlib", "stno2", "stno3", "stno4", "stnp3", "stnz1", "stsel", "stst0", "stwrp",
                "strare",
                "tt_000"
            ]
        },
        {
            "id": "hd",
            "name": "Debug JP build (from PSP hdbin)",
            "overlays": [
                "dra", "ric",
                "stcen", "stwrp",
                "tt_000"
            ]
        },
    ],
    "overlays": {
        "dra": {
            "name": "DRA.BIN",
            "desc": "Game engine"
        },
        "weapon": {
            "name": "BIN/WEAPON0.BIN",
            "desc": "Weapons, shield and consumable programs"
        },
        "maria": {
            "name": "PSPBIN/MARIA.BIN",
            "desc": "Maria program",
        },
        "ric": {
            "name": "BIN/RIC.BIN",
            "desc": "Richter program"
        },
        "stare": {
            "name": "ST/ARE/ARE.BIN",
            "desc": "Colosseum"
        },
        "stcat": {
            "name": "ST/CAT/CAT.BIN",
            "desc": "Catacombs"
        },
        "stcen": {
            "name": "ST/CEN/CEN.BIN",
            "desc": "Castle Center"
        },
        "stchi": {
            "name": "ST/CHI/CHI.BIN",
            "desc": "Abandoned Mine"
        },
        "stdai": {
            "name": "ST/DAI/DAI.BIN",
            "desc": "Royal Chapel"
        },
        "stdre": {
            "name": "ST/DRE/DRE.BIN",
            "desc": "Nightmare"
        },
        "stlib": {
            "name": "ST/LIB/LIB.BIN",
            "desc": "Long Library"
        },
        "stmad": {
            "name": "ST/MAD/MAD.BIN",
            "desc": "Debug room"
        },
        "stno0": {
            "name": "ST/NO0/NO0.BIN",
            "desc": "Marble Gallery"
        },
        "stno1": {
            "name": "ST/NO1/NO1.BIN",
            "desc": "Outer Wall"
        },
        "stno2": {
            "name": "ST/NO2/NO2.BIN",
            "desc": "Olrox's Quarters"
        },
        "stno3": {
            "name": "ST/NO3/NO3.BIN",
            "desc": "Entrance (first visit)"
        },
        "stno4": {
            "name": "ST/NO4/NO4.BIN",
            "desc": "Caverns"
        },
        "stnp3": {
            "name": "ST/NP3/NP3.BIN",
            "desc": "Entrance (second visit)"
        },
        "stnz0": {
            "name": "ST/NZ0/NZ0.BIN",
            "desc": "Alchemy Lab"
        },
        "stnz1": {
            "name": "ST/NZ1/NZ1.BIN",
            "desc": "Clock Tower"
        },
        "stsel": {
            "name": "ST/SEL/SEL.BIN",
            "desc": "Title screen"
        },
        "stst0": {
            "name": "ST/ST0/ST0.BIN",
            "desc": "Prologue"
        },
        "sttop": {
            "name": "ST/TOP/TOP.BIN",
            "desc": "Castle Keep",
        },
        "stwrp": {
            "name": "ST/WRP/WRP.BIN",
            "desc": "Warp rooms"
        },
        "strare": {
            "name": "ST/RARE/RARE.BIN",
            "desc": "Reverse Colosseum"
        },
        "strcat": {
            "name": "ST/RCAT/RCAT.BIN",
            "desc": "Floating Catacombs"
        },
        "strcen": {
            "name": "ST/RCEN/RCEN.BIN",
            "desc": "Reverse Center"
        },
        "strchi": {
            "name": "ST/RCHI/RCHI.BIN",
            "desc": "Cave"
        },
        "strdai": {
            "name": "ST/RDAI/RDAI.BIN",
            "desc": "Anti-Chapel"
        },
        "strlib": {
            "name": "ST/RLIB/RLIB.BIN",
            "desc": "Forbidden Library"
        },
        "strno0": {
            "name": "ST/RNO0/RNO0.BIN",
            "desc": "Black Marble Gallery"
        },
        "strno1": {
            "name": "ST/RNO1/RNO1.BIN",
            "desc": "Reverse Outer Wall",
        },
        "strno2": {
            "name": "ST/RNO2/RNO2.BIN",
            "desc": "Death Wing's Lair"
        },
        "strno3": {
            "name": "ST/RNO3/RNO3.BIN",
            "desc": "Reverse Entrance"
        },
        "strno4": {
            "name": "ST/RNO4/RNO4.BIN",
            "desc": "Reverce Caverns"
        },
        "strnz0": {
            "name": "ST/RNZ0/RNZ0.BIN",
            "desc": "Necromancy Laboratory"
        },
        "strnz1": {
            "name": "ST/RNZ1/RNZ1.BIN",
            "desc": "Reverse Clock Tower"
        },
        "strtop": {
            "name": "ST/RTOP/RTOP.BIN",
            "desc": "Reverse Keep"
        },
        "strwrp": {
            "name": "ST/RWRP/RWRP.BIN",
            "desc": "Warp rooms (reverse)"
        },
        "bomar": {
            "name": "BOSS/MAR/MAR.BIN",
            "desc": "Maria cutscene (clock room)"
        },
        "bobo4": {
            "name": "BOSS/BO4/BO4.BIN",
            "desc": "Doppleganger10 boss"
        },
        "bobo6": {
            "name": "BOSS/BO6/BO6.BIN",
            "desc": "Richter boss"
        },
        "borbo3": {
            "name": "BOSS/RBO3/RBO3.BIN",
            "desc": "Medusa boss"
        },
        "borbo5": {
            "name": "BOSS/RBO5/RBO5.BIN",
            "desc": "Doppleganger40 boss"
        },
        "tt_000": {
            "name": "SERVANT/TT_000.BIN",
            "desc": "Familiar Bat"
        },
        "tt_001": {
            "name": "SERVANT/TT_001.BIN",
            "desc": "Familiar Ghost"
        },
        "tt_002": {
            "name": "SERVANT/TT_002.BIN",
            "desc": "Familiar Faerie"
        },
        "tt_003": {
            "name": "SERVANT/TT_003.BIN",
            "desc": "Familiar Demon"
        },
        "tt_004": {
            "name": "SERVANT/TT_004.BIN",
            "desc": "Familiar Sword"
        },
    }
};

export default gameMetadata;
