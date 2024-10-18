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
                "dra", "ric", "weapon", "stcen", "stdre", "stmad", "stno0", "stno3", "stnp3", "stnz0", "stsel", "stst0", "stwrp", "strwrp", "bomar", "tt_000", "tt_001", "tt_002"
            ]
        },
        {
            "id": "hd",
            "name": "Debug JP build (from PSP hdbin)",
            "overlays": [
                "dra", "ric", "tt_000"
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
        "ric": {
            "name": "BIN/RIC.BIN",
            "desc": "Richter program"
        },
        "stcen": {
            "name": "ST/CEN/CEN.BIN",
            "desc": "Castle Center"
        },
        "stdre": {
            "name": "ST/DRE/DRE.BIN",
            "desc": "Nightmare"
        },
        "stmad": {
            "name": "ST/MAD/MAD.BIN",
            "desc": "Debug room"
        },
        "stno0": {
            "name": "ST/NO0/NO0.BIN",
            "desc": "Marble Gallery"
        },
        "stno3": {
            "name": "ST/NO3/NO3.BIN",
            "desc": "Entrance (first visit)"
        },
        "stnp3": {
            "name": "ST/NP3/NP3.BIN",
            "desc": "Entrance (second visit)"
        },
        "stnz0": {
            "name": "ST/NZ0/NZ0.BIN",
            "desc": "Alchemy Lab"
        },
        "stsel": {
            "name": "ST/SEL/SEL.BIN",
            "desc": "Title screen"
        },
        "stst0": {
            "name": "ST/ST0/ST0.BIN",
            "desc": "Prologue"
        },
        "stwrp": {
            "name": "ST/WRP/WRP.BIN",
            "desc": "Warp rooms"
        },
        "strwrp": {
            "name": "ST/RWRP/RWRP.BIN",
            "desc": "Warp rooms (reverse)"
        },
        "bomar": {
            "name": "BOSS/MAR/MAR.BIN",
            "desc": "Maria cutscene (clock room)"
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
    }
};

export default gameMetadata;
