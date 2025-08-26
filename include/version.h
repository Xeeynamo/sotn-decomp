// `version.h` specifies several `VERSION` macros that can be used to
// conditionally compile particular version of the game. By including
// this file, you'll get:
//
// * `VERSION` - a macro that expands to a string literal version (e.g, `"us"`,
//   `"hd"`, `"psp"`)
// * `VERSION_TOKEN` - a macro that expands to a token representing the version
//   (e.g `us`, `hd`, `psp`), useful for building symbol names
// * One of `VERSION_US`, `VERSION_HD`, `VERSION_PSP`, or `VERSION_BETA`
// * `GEN_VERSION` - macro that can be used to build an `#include` path for
//   generated files specific to the version
#ifndef VERSION_H
#define VERSION_H

#if defined(_internal_version_us)
#define VERSION_US
#define VERSION_TOKEN us
#elif defined(_internal_version_hd)
#define VERSION_HD
#define VERSION_TOKEN hd
#elif defined(_internal_version_pspeu)
#define VERSION_PSP
// use this to flag code as only non-psp due to deadstripping.
// will make it easier to restore stripped code if we ever work out a
// solution for doing proper deadstripping like the original.
#define PSP_DEADSTRIP
#define VERSION_TOKEN psp
#define NOP                                                                    \
    static asm nop_##line##() { nop }
#elif defined(_internal_version_beta)
#define VERSION_BETA
#define VERSION_TOKEN beta
#else
#warning "Version not specified. Falling back to the US version."
#define VERSION_US
#define VERSION_TOKEN us
#endif

#define __CPP_STR(x) #x
#define CPP_STR(x) __CPP_STR(x)
// note: the "token" produced by PATH_JOIN gets stringified into a
//       path. clang-format wants to:to
// clang-format off
#define PATH_JOIN(a, b) a/b
// clang-format on

// `VERSION` is a string literalized version of `VERSION_TOKEN`
#define VERSION CPP_STR(VERSION_TOKEN)

// `GEN_VERSION` creates an include path for the provided `file`
// for version specific generated files.
//
// Example:
//
//     // expands to `#include "gen/us/blueprints.h"` when `VERSION==us`
//     // expands to `#include "gen/hd/blueprints.h"` when `VERSION==hd`
//     // expands to `#include "gen/psp/blueprints.h"` when `VERSION==psp`
//     #include GEN_VERSION(blueprints.h)
//
// Arguments:
//   file: a token literal file to include
//
// Expands to: a gen directory namespaced by version
#define GEN_VERSION(file)                                                      \
    CPP_STR(PATH_JOIN(gen, PATH_JOIN(VERSION_TOKEN, file)))

#endif // VERSION_H
