#include <game.h>
#ifdef _MSC_VER
#define SDL_MAIN_HANDLED
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "sdl2_macros.h"
#include "stage.h"

int press_pos = 0;
int press_spell = 0;
int next_time = 0;
int spell_num = 0;
int spell_dir = 0;

#define STOP -1

struct SpellInput {
    int pad;
    int frames;
};

struct SpellInput tetra_spirit[] = {
    {PAD_UP, 33},   {PAD_UP + PAD_RIGHT, 1},
    {PAD_RIGHT, 1}, {PAD_DOWN + PAD_RIGHT, 1},
    {PAD_DOWN, 1},  {PAD_SQUARE, 1},
    {STOP, 0}};

struct SpellInput dark_metamorphosis[] = {
    {PAD_LEFT, 1},  {PAD_UP + PAD_LEFT, 1},
    {PAD_UP, 1},    {PAD_UP + PAD_RIGHT, 1},
    {PAD_RIGHT, 1}, {PAD_SQUARE, 1},
    {STOP, 0}};

struct SpellInput summon_spirit[] = {
    {PAD_LEFT, 1}, {PAD_RIGHT, 1},  {PAD_UP, 1},
    {PAD_DOWN, 1}, {PAD_SQUARE, 1}, {STOP, 0}};

struct SpellInput hellfire[] = {
    {PAD_UP, 1},    {PAD_DOWN, 1},   {PAD_DOWN + PAD_RIGHT, 1},
    {PAD_RIGHT, 1}, {PAD_SQUARE, 1}, {STOP, 0}};

struct SpellInput soul_steal[] = {
    {PAD_LEFT, 1},  {PAD_RIGHT, 1},           {PAD_DOWN + PAD_RIGHT, 1},
    {PAD_DOWN, 1},  {PAD_DOWN + PAD_LEFT, 1}, {PAD_LEFT, 1},
    {PAD_RIGHT, 1}, {PAD_SQUARE, 1},          {STOP, 0}};

struct SpellInput sword_brothers[] = {
    {PAD_DOWN, 1},   {PAD_DOWN + PAD_RIGHT, 1},
    {PAD_RIGHT, 1},  {PAD_UP + PAD_RIGHT, 1},
    {PAD_UP, 64},    {PAD_DOWN, 3},
    {PAD_SQUARE, 1}, {STOP, 0}};

struct SpellInput wing_smash[] = {
    {PAD_UP + PAD_CROSS, 1},    {PAD_UP + PAD_LEFT + PAD_CROSS, 1},
    {PAD_LEFT + PAD_CROSS, 1},  {PAD_DOWN + PAD_LEFT + PAD_CROSS, 1},
    {PAD_DOWN + PAD_CROSS, 1},  {PAD_DOWN + PAD_RIGHT + PAD_CROSS, 1},
    {PAD_RIGHT + PAD_CROSS, 1}, {STOP, 0}};

struct SpellInput wolf_charge[] = {
    {PAD_DOWN, 1},
    {PAD_DOWN + PAD_RIGHT, 1},
    {PAD_RIGHT, 1},
    {PAD_SQUARE, 1},
    {STOP, 0}};

struct SpellInput* spells_right[] = {
    &tetra_spirit, &dark_metamorphosis, &summon_spirit, &hellfire,
    &soul_steal,   &sword_brothers,     &wing_smash,    &wolf_charge};

struct SpellInput tetra_spirit_left[] = {
    {PAD_UP, 33},  {PAD_UP + PAD_LEFT, 1},
    {PAD_LEFT, 1}, {PAD_DOWN + PAD_LEFT, 1},
    {PAD_DOWN, 1}, {PAD_SQUARE, 1},
    {STOP, 0}};

struct SpellInput dark_metamorphosis_left[] = {
    {PAD_RIGHT, 1}, {PAD_UP + PAD_RIGHT, 1},
    {PAD_UP, 1},    {PAD_UP + PAD_LEFT, 1},
    {PAD_LEFT, 1},  {PAD_SQUARE, 1},
    {STOP, 0}};

struct SpellInput summon_spirit_left[] = {
    {PAD_RIGHT, 1}, {PAD_LEFT, 1},   {PAD_UP, 1},
    {PAD_DOWN, 1},  {PAD_SQUARE, 1}, {STOP, 0}};

struct SpellInput hellfire_left[] = {
    {PAD_UP, 1},   {PAD_DOWN, 1},   {PAD_DOWN + PAD_LEFT, 1},
    {PAD_LEFT, 1}, {PAD_SQUARE, 1}, {STOP, 0}};

struct SpellInput soul_steal_left[] = {
    {PAD_RIGHT, 1},
    {PAD_LEFT, 1},
    {PAD_DOWN + PAD_LEFT, 1},
    {PAD_DOWN, 1},
    {PAD_DOWN + PAD_RIGHT, 1},
    {PAD_RIGHT, 1},
    {PAD_LEFT, 1},
    {PAD_SQUARE, 1},
    {STOP, 0}};

struct SpellInput sword_brothers_left[] = {
    {PAD_DOWN, 1},   {PAD_DOWN + PAD_LEFT, 1},
    {PAD_LEFT, 1},   {PAD_UP + PAD_LEFT, 1},
    {PAD_UP, 64},    {PAD_DOWN, 3},
    {PAD_SQUARE, 1}, {STOP, 0}};

struct SpellInput wing_smash_left[] = {
    {PAD_UP + PAD_CROSS, 1},    {PAD_UP + PAD_RIGHT + PAD_CROSS, 1},
    {PAD_RIGHT + PAD_CROSS, 1}, {PAD_DOWN + PAD_RIGHT + PAD_CROSS, 1},
    {PAD_DOWN + PAD_CROSS, 1},  {PAD_DOWN + PAD_LEFT + PAD_CROSS, 1},
    {PAD_LEFT + PAD_CROSS, 1},  {STOP, 0}};

struct SpellInput wolf_charge_left[] = {
    {PAD_DOWN, 1},
    {PAD_DOWN + PAD_LEFT, 1},
    {PAD_LEFT, 1},
    {PAD_SQUARE, 1},
    {STOP, 0}};

struct SpellInput* spells_left[] = {
    &tetra_spirit_left, &dark_metamorphosis_left, &summon_spirit_left,
    &hellfire_left,     &soul_steal_left,         &sword_brothers_left,
    &wing_smash_left,   &wolf_charge_left};

struct SpellInput** spell[] = {&spells_right, &spells_left};

enum Spells {
    TETRA_SPIRIT,
    DARK_METAMORPHOSIS,
    SUMMON_SPIRIT,
    HELLFIRE,
    SOUL_STEAL,
    SWORD_BROTHERS,
    WING_SMASH,
    WOLF_CHARGE
};

u8 previousKeyStates[SDL_NUM_SCANCODES] = {0};

void check_macro(int scanCode, enum Spells which, const u8* keyb) {
    if (keyb[scanCode] && !previousKeyStates[scanCode]) {
        press_spell = 1;
        press_pos = 0;
        next_time = 0;
        spell_num = which;
        spell_dir = PLAYER.facingLeft;
    }
}

#define DAGGER 14
#define AXE 15
#define CROSS 16

void handle_macros(const u8* keyb, u_long* pressed) {
    // put a candle with a subweapon drop in the room
    if (keyb[SDL_SCANCODE_1] && !previousKeyStates[SDL_SCANCODE_1]) {
        Entity* temp = g_Entities + STAGE_ENTITY_START + 10;
        LayoutEntity l;
        l.posX = 128;
        l.posY = 128;
        l.entityId = 1; // entityBreakable
        l.entityRoomIndex = 0;
        l.params = CROSS;
        CreateEntityFromLayout(temp, &l);
    }
    check_macro(SDL_SCANCODE_Y, TETRA_SPIRIT, keyb);
    check_macro(SDL_SCANCODE_U, DARK_METAMORPHOSIS, keyb);
    check_macro(SDL_SCANCODE_I, SUMMON_SPIRIT, keyb);
    check_macro(SDL_SCANCODE_O, HELLFIRE, keyb);
    check_macro(SDL_SCANCODE_P, SOUL_STEAL, keyb);
    check_macro(SDL_SCANCODE_H, SWORD_BROTHERS, keyb);
    check_macro(SDL_SCANCODE_J, WING_SMASH, keyb);
    check_macro(SDL_SCANCODE_K, WOLF_CHARGE, keyb);

    memcpy(previousKeyStates, keyb, SDL_NUM_SCANCODES * sizeof(Uint8));

    if (press_spell == 1) {
        if (spell[spell_dir][spell_num][press_pos].pad == STOP) {
            press_spell = 0;
            press_pos = 0;
            next_time = 0;
        } else if (next_time == 0) {
            *pressed |= spell[spell_dir][spell_num][press_pos].pad;
            next_time = spell[spell_dir][spell_num][press_pos].frames + g_Timer;
        } else if (g_Timer >= next_time) {
            press_pos++;

            if (spell[spell_dir][spell_num][press_pos].pad == STOP) {
                press_spell = 0;
                press_pos = 0;
                next_time = 0;
            } else {
                *pressed |= spell[spell_dir][spell_num][press_pos].pad;
                next_time =
                    spell[spell_dir][spell_num][press_pos].frames + g_Timer;
            }
        } else {
            *pressed |= spell[spell_dir][spell_num][press_pos].pad;
        }
    }
}
