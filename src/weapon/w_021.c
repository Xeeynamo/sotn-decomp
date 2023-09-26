// Weapon ID #21. Used by weapons:
// Orange, Apple, Banana, Grapes, Strawberry, Pineapple, Peanuts, Toadstool,
// Shiitake, Cheesecake, Shortcake, Tart, Parfait, Pudding, Ice cream,
// Frankfurter, Hamburger, Pizza, Cheese, Ham and eggs, Omelette, Morning set,
// Lunch A, Lunch B, Curry rice, Gyros plate, Spaghetti, Grape juice, Barley
// tea, Green tea, Natou, Ramen, Miso soup, Sushi, Pork bun, Red bean bun,
// Chinese bun, Dim Sum set, Pot roast, Sirloin, Turkey, Meal ticket
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_021", func_97000_8017AB54);

INCLUDE_ASM("weapon/nonmatchings/w_021", func_97000_8017AF2C);

INCLUDE_ASM("weapon/nonmatchings/w_021", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_021", func_ptr_80170004);

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 21; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
