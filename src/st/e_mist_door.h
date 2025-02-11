// SPDX-License-Identifier: AGPL-3.0-or-later
#if defined(VERSION_PSP)
static char alucard_mist_ENG[] = "\xBC\x10Mist could pass.\x00";
static char alucard_mist_ES[] =
    "\xBC\x10La niebla pasar\xD5"
    "a.\x00";
static char alucard_mist_IT[] = "\xBC\x10La nebbia pu\xD9 passare.\x00";
static char alucard_mist_FR[] = "\xBC\x10La Brume a pu passer.";
static char alucard_mist_DE[] = "\xBC\x10Nebel k\xCEme vorbei.\x00";

static char richter_mist_ENG[] = "\xB8\x10Not important to me.\x00";
static char richter_mist_ES[] = "\xB8\x10No me importa.\x00";
static char richter_mist_IT[] = "\xB8\x10Non importante per me.\x00";
static char richter_mist_FR[] =
    "\xB8\x10\xB8"
    "a ne me sert \xCB rien.";
static char richter_mist_DE[] = "\xB8\x10Geht mich nichts an.\x00";

static char maria_mist_ENG[] = "\xB8\x10I can't get through.\x00";
static char maria_mist_ES[] = "\xB8\x10No puedo pasar.\x00";
static char maria_mist_IT[] = "\xB8\x10Non riesco a passare.";
static char maria_mist_FR[] = "\xB8\x10Je ne peux pas passer.\x00";
static char maria_mist_DE[] = "\xB8\x10Ich komme nicht durch.\x00";

static char* alucard_mist_label; // bss
static char* maria_mist_label;   // bss
static char* richter_mist_label; // bss

extern s32 D_8B42058; // User's language selection?
#else
static char alucard_mist_label[] = "\x7C\x0EMist could pass\x81\x44";
static char richter_mist_label[] =
    "\x94\x1EI have nothing to do\x01"
    "with this wall\x81\x44\x81\x44\x81\x44";
#endif

#ifdef VERSION_PSP
static char* GetMistLabel(
    char* str_EN, char* str_FR, char* str_ES, char* str_DE, char* str_IT) {
    switch (D_8B42058) {
    case 1:
    default:
        return str_EN;
    case 2:
        return str_FR;
    case 3:
        return str_ES;
    case 4:
        return str_DE;
    case 5:
        return str_IT;
    }
}
#endif

void EntityMistDoor(Entity* self) {
    Entity* messageBox;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->hitboxState = 1;
        self->hitPoints = 0x7FFF;
        self->attack = 0;
        self->hitboxWidth = 0xC;
        self->hitboxHeight = 0x18;
    }
    if (self->hitFlags) {
        messageBox = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (messageBox != NULL) {
            CreateEntityFromCurrentEntity(E_MESSAGE_BOX, messageBox);
            messageBox->posX.i.hi = 0x80;
            messageBox->posY.i.hi = 0xB0;
#ifdef VERSION_PSP
            alucard_mist_label =
                GetMistLabel(alucard_mist_ENG, alucard_mist_FR, alucard_mist_ES,
                             alucard_mist_DE, alucard_mist_IT);
            maria_mist_label =
                GetMistLabel(maria_mist_ENG, maria_mist_FR, maria_mist_ES,
                             maria_mist_DE, maria_mist_IT);
            richter_mist_label =
                GetMistLabel(richter_mist_ENG, richter_mist_FR, richter_mist_ES,
                             richter_mist_DE, richter_mist_IT);
            if (g_PlayableCharacter == PLAYER_MARIA) {
                messageBox->ext.messageBox.label = maria_mist_label;
            } else if (g_PlayableCharacter == PLAYER_RICHTER) {
                messageBox->ext.messageBox.label = richter_mist_label;
            } else {
                messageBox->ext.messageBox.label = alucard_mist_label;
            }
#else
            if (g_PlayableCharacter != PLAYER_ALUCARD) {
                messageBox->ext.messageBox.label = richter_mist_label;
            } else {
                messageBox->ext.messageBox.label = alucard_mist_label;
            }
#endif
            messageBox->params = 0x100;
            self->hitboxState = 0;
        }
    }
}
