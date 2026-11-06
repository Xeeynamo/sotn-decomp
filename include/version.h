// `version.h` describes which game build is being compiled. By including this
// file, you'll get:
//
// * `VERSION` - the build date of the game, as one of the `VER_*` constants.
//   Builds are ordered by date, so `VERSION >= VER_JP11` selects JP 1.1 and
//   every build that came after it.
// * `REGION` - one of the `REGION_*` constants, for regional differences that
//   are not a consequence of a later code revision.
// * `TARGET` - one of the `TARGET_*` constants, for code that only exists on
//   a specific platform the game was released on.
// * `VERSION_TOKEN` - a macro that expands to a token representing the build
//   (e.g `us`, `hd`, `psp`), useful for building symbol names
// * `VERSION_STR` - a string literalized version of `VERSION_TOKEN`
// * `GEN_VERSION` - macro that can be used to build an `#include` path for
//   generated files specific to the version
//
// Examples:
//
//     #if VERSION >= VER_JP11                      // JP 1.1 and later builds
//     #if VERSION >= VER_US && VERSION < VER_JP12  // a range of builds
//     #if VERSION == VER_USPROTO                   // a single build
//     #if REGION == REGION_JP                      // regional difference
//     #if TARGET == TARGET_PSP                     // PSP exclusive code
//     #if IS_VER_INTL                              // US, EU and HK builds
#ifndef VERSION_H
#define VERSION_H

// Build dates as YYYYMMDD. A day of 00 means the exact date is unknown.
#define VER_BETA_TEK 19970000U // found in PSP_GAME/USRDIR/res/ps/hdbin/tek.bin
#define VER_BETA_MAD 19970100U // found in ST/MAD/MAD.bin
#define VER_BETA_HD 19970200U  // found in PSP_GAME/USRDIR/res/ps/hdbin/dra.bin
#define VER_JP10 19970220U     // http://redump.org/disc/4687/
#define VER_JP11 19970306U     // http://redump.org/disc/4128/
#define VER_USPROTO 19970617U  // Also known as E3 Version
#define VER_US 19970901U       // http://redump.org/disc/3379/
#define VER_EU 19970929U       // http://redump.org/disc/1130/
#define VER_HK 19971112U       // http://redump.org/disc/63544/
#define VER_JP12 19980122U     // http://redump.org/disc/4684/
#define VER_PSP 20080215U      // http://redump.org/disc/4528/
#define VER_NEXT 20270101U     // Community patches from SOTN Decomp

#define REGION_JP 1
#define REGION_US 2
#define REGION_EU 3
#define REGION_HK 4

#define TARGET_PS1 1
#define TARGET_PSP 2
#define TARGET_SATURN 3
#define TARGET_XBOX 4

#if defined(_internal_version_us)
#define VERSION VER_US
#define REGION REGION_US
#define VERSION_TOKEN us
#elif defined(_internal_version_hd)
#define VERSION VER_BETA_HD
#define REGION REGION_JP
#define VERSION_TOKEN hd
#elif defined(_internal_version_jp10)
#define VERSION VER_JP10
#define REGION REGION_JP
#define VERSION_TOKEN jp10
#elif defined(_internal_version_jp11)
#define VERSION VER_JP11
#define REGION REGION_JP
#define VERSION_TOKEN jp11
#elif defined(_internal_version_jp12)
#define VERSION VER_JP12
#define REGION REGION_JP
#define VERSION_TOKEN jp12
#elif defined(_internal_version_usproto)
#define VERSION VER_USPROTO
#define REGION REGION_US
#define VERSION_TOKEN usproto
#elif defined(_internal_version_eu)
#define VERSION VER_EU
#define REGION REGION_EU
#define VERSION_TOKEN eu
#elif defined(_internal_version_hk)
#define VERSION VER_HK
#define REGION REGION_HK
#define VERSION_TOKEN hk
#elif defined(_internal_version_pspeu)
#define VERSION VER_PSP
#define REGION REGION_JP
#define TARGET TARGET_PSP
// use this to flag code as only non-psp due to deadstripping.
// will make it easier to restore stripped code if we ever work out a
// solution for doing proper deadstripping like the original.
#define PSP_DEADSTRIP
#define VERSION_TOKEN psp
#define NOP                                                                    \
    static asm nop_##line##() { nop }
#elif defined(_internal_version_beta)
#define VERSION VER_BETA_MAD
#define REGION REGION_JP
#define VERSION_TOKEN beta
#else
#warning "Version not specified. Falling back to the US version."
#define VERSION VER_US
#define REGION REGION_US
#define VERSION_TOKEN us
#endif

// International retail releases: US, EU and HK. Doesn't include VER_USPROTO.
// Valid only for PlayStation 1 builds. It is always false on PSP.
#define IS_VER_INTL (VERSION >= VER_US && REGION != REGION_JP)

#ifdef PLATFORM_PSYZ

// Macro to fix Undefined Behaviors found across the original codebase.
// These are community, unofficial fixes brought for making the code portable
// on different platforms, and to fix bugs in the original game release that
// are unrelated to gameplay mechanics or glitch exploitation. This includes:
//   * Array access beyond its intended boundaries
//   * Access to uninitialized or unrelated portion of memory
//   * Missing return statements
//   * Mismatching function signatures to their original intended type
//   * Data overflow
//   * Unintended graphical glitches
// What this macro must NOT be use for:
//   * Gameplay behavior or mechanics, even when they result to an exploit
//   * Enhancements and beautifiers
//   * Extend behavior or fix a dormant mechanic
#define FIX_UB

#endif

#define __CPP_STR(x) #x
#define CPP_STR(x) __CPP_STR(x)
// note: the "token" produced by PATH_JOIN gets stringified into a
//       path. clang-format wants to:to
// clang-format off
#define PATH_JOIN(a, b) a/b
// clang-format on

// `VERSION_STR` is a string literalized version of `VERSION_TOKEN`
#define VERSION_STR CPP_STR(VERSION_TOKEN)

// `GEN_VERSION` creates an include path for the provided `file`
// for version specific generated files.
//
// Example:
//
//     // expands to `#include "gen/us/blueprints.h"` when building us
//     // expands to `#include "gen/hd/blueprints.h"` when building hd
//     // expands to `#include "gen/psp/blueprints.h"` when building pspeu
//     #include GEN_VERSION(blueprints.h)
//
// Arguments:
//   file: a token literal file to include
//
// Expands to: a gen directory namespaced by version
#ifdef GEN_VERSION_ANGLE
// clang-format off
#define GEN_VERSION(file) <PATH_JOIN(gen, PATH_JOIN(VERSION_TOKEN, file))>
// clang-format on
#else
#define GEN_VERSION(file)                                                      \
    CPP_STR(PATH_JOIN(gen, PATH_JOIN(VERSION_TOKEN, file)))
#endif

#endif // VERSION_H
