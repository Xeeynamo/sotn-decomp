#ifndef SOTNSTR_H
#define SOTNSTR_H

#ifndef SOTN_STR
// Decorator to re-encode strings with tools/sotn_str/sotn_str.py when building
// the game. Certain strings in SOTN do not follow the ASCII encoding and each
// character is offseted by 0x20. This is only for strings that use the 8x8
// font. e.g. _S("I am a Symphony of the Night encoded string")
#define _S(x) (x)
#endif

#endif
