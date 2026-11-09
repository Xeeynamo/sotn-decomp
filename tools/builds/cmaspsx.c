// SPDX-License-Identifier: MIT
// Copyright (c) 2023 Mark Street
// C port of maspsx by Mark Street, https://github.com/mkst/maspsx
//
// Minimalistic port that works specifically for SOTN Decomp

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    const char* ptr;
    int len;
} Str;

static Str* lines;
static int nlines;

static char* out;
static size_t out_len, out_cap;

static int is_v221; // ASPSX 2.21 instead of 2.34

static int is_reorder = 1;
static int skip_instructions;
static int file_num = 1;
static int line_index;

static void fail(const char* why, Str line) {
    fprintf(stderr, "cmaspsx: %s: %.*s\n", why, line.len, line.ptr);
    exit(1);
}

static void put(const char* p, size_t n) {
    if (out_len + n > out_cap) {
        out_cap = (out_len + n) * 2;
        out = realloc(out, out_cap);
    }
    memcpy(out + out_len, p, n);
    out_len += n;
}

// Every output line is preceded by a new line, as maspsx joins an empty
// preamble and the lines with "\n".
static void emit(const char* fmt, ...) {
    char buf[4096];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    if (n >= (int)sizeof(buf)) {
        fail("line too long", (Str){buf, 64});
    }
    put("\n", 1);
    put(buf, n);
}

static void emit_s(Str s) {
    put("\n", 1);
    put(s.ptr, s.len);
}

static Str mk(const char* p) { return (Str){p, (int)strlen(p)}; }
static int ws(char c) { return c == ' ' || c == '\t'; }
static int az(char c) { return c >= 'A' && c <= 'z'; } // [A-z] includes [\]^_`
static int lower_digit(char c) {
    return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}
static int digit(char c) { return c >= '0' && c <= '9'; }
static int hexd(char c) {
    return digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

static int starts(Str s, const char* x) {
    int n = strlen(x);
    return s.len >= n && !memcmp(s.ptr, x, n);
}
static int ends(Str s, const char* x) {
    int n = strlen(x);
    return s.len >= n && !memcmp(s.ptr + s.len - n, x, n);
}
static int eq(Str s, const char* x) {
    return s.len == (int)strlen(x) && !memcmp(s.ptr, x, s.len);
}
static int eqs(Str a, Str b) {
    return a.len == b.len && !memcmp(a.ptr, b.ptr, a.len);
}
static int has(Str s, char c) { return memchr(s.ptr, c, s.len) != NULL; }
static int in(Str s, const char* const* set) {
    for (; *set; set++) {
        if (eq(s, *set)) {
            return 1;
        }
    }
    return 0;
}

static Str trim(Str s) {
    while (s.len && ws(*s.ptr)) {
        s.ptr++, s.len--;
    }
    while (s.len && ws(s.ptr[s.len - 1])) {
        s.len--;
    }
    return s;
}

static Str strip_comments(Str s) {
    const char* h = memchr(s.ptr, '#', s.len);
    if (h) {
        s.len = h - s.ptr;
    }
    return trim(s);
}

// The n-th token of str.split()
static Str token(Str s, int n) {
    int i = 0;
    for (;;) {
        while (i < s.len && ws(s.ptr[i])) {
            i++;
        }
        if (i == s.len) {
            return (Str){s.ptr + i, -1};
        }
        int j = i;
        while (j < s.len && !ws(s.ptr[j])) {
            j++;
        }
        if (n-- == 0) {
            return (Str){s.ptr + i, j - i};
        }
        i = j;
    }
}

// The tokens after the first one, joined by single spaces, written in buf
static Str rest_joined(Str s, char* buf) {
    int n = 0;
    for (int k = 1;; k++) {
        Str t = token(s, k);
        if (t.len < 0) {
            break;
        }
        if (k > 1) {
            buf[n++] = ' ';
        }
        memcpy(buf + n, t.ptr, t.len);
        n += t.len;
    }
    return (Str){buf, n};
}

// a, b, c = s.split(","): exactly `count` parts
static void split_comma(Str s, Str* parts, int count, Str line) {
    int k = 0;
    const char* p = s.ptr;
    for (int i = 0; i <= s.len; i++) {
        if (i == s.len || s.ptr[i] == ',') {
            if (k == count) {
                fail("unexpected operands", line);
            }
            parts[k++] = (Str){p, (int)(s.ptr + i - p)};
            p = s.ptr + i + 1;
        }
    }
    if (k != count) {
        fail("unexpected operands", line);
    }
}

static const char* const LOAD[] = {
    "lb", "lbu", "lh", "lhu", "lw", "lwl", "lwr", 0};
static const char* const STORE[] = {"sb", "sh", "sw", "swl", "swr", "swc2", 0};
static const char* const BRANCH_JUMP[] = {
    "beq", "bgez", "bgtz", "blez", "bltz", "bne", "j", "jal", 0};
static const char* const BRANCH[] = {
    "beq", "bgez", "bgtz", "blez", "bltz", "bne", 0};
static const char* const SINGLE[] = {
    "mult", "multu", "div", "divu", "rem", "remu", "move", "negu", "nor", 0};
static const char* const DOUBLE[] = {
    "and", "andi", "or",  "ori", "xor", "xori", "addu", "subu",
    "sll", "slr",  "srl", "sra", "slt", "slti", "sltu", 0};
static const char* const PLAIN[] = {
    "addu", "subu", "sra", "srl", "srr", "sll", "or", 0};
static const char* const MULT_DIV[] = {
    "mult\t", "multu\t", "div\t", "divu\t", "rem\t", "remu\t", 0};

static int starts_any(Str s, const char* const* set) {
    for (; *set; set++) {
        if (starts(s, *set)) {
            return 1;
        }
    }
    return 0;
}

// int(s, 0) and int(s) for the forms maspsx sees; others fail like Python does,
// or are not supported
static long long py_int(Str s, int base0, Str line) {
    int i = 0, neg = 0;
    long long v = 0;
    if (i < s.len && s.ptr[i] == '-') {
        neg = 1, i++;
    }
    if (base0 && s.len - i > 2 && s.ptr[i] == '0' && s.ptr[i + 1] == 'x') {
        for (i += 2; i < s.len; i++) {
            if (!hexd(s.ptr[i]) || v > 0xFFFFFFFFFFLL) {
                fail("bad number", line);
            }
            v = v * 16 + (digit(s.ptr[i]) ? s.ptr[i] - '0'
                                          : (s.ptr[i] | 0x20) - 'a' + 10);
        }
        return neg ? -v : v;
    }
    if (i == s.len || (base0 && s.ptr[i] == '0' && s.len - i > 1)) {
        fail("bad number", line);
    }
    for (; i < s.len; i++) {
        if (!digit(s.ptr[i]) || v > 0xFFFFFFFFFFLL) {
            fail("bad number", line);
        }
        v = v * 10 + s.ptr[i] - '0';
    }
    return neg ? -v : v;
}

// ^-?\d+$ or ^-?0x[A-Fa-f0-9]+$
static int is_number(Str s) {
    int i = s.len && s.ptr[0] == '-';
    if (s.len - i > 2 && s.ptr[i] == '0' && s.ptr[i + 1] == 'x') {
        for (int j = i + 2; j < s.len; j++) {
            if (!hexd(s.ptr[j])) {
                goto dec;
            }
        }
        return 1;
    }
dec:
    if (i == s.len) {
        return 0;
    }
    for (; i < s.len; i++) {
        if (!digit(s.ptr[i])) {
            return 0;
        }
    }
    return 1;
}

static int is_label(Str s) {
    if (!starts(s, "$L")) {
        return 0;
    }
    int i = 2;
    if (i < s.len && (s.ptr[i] == 'b' || s.ptr[i] == 'e')) {
        i++;
    }
    int d = i;
    while (i < s.len && digit(s.ptr[i])) {
        i++;
    }
    return i > d && i == s.len - 1 && s.ptr[i] == ':';
}

// (\$[a-z0-9]+), at s[i]; returns the index after the comma, or -1
static int reg_comma(Str s, int i, Str* reg) {
    if (i >= s.len || s.ptr[i] != '$') {
        return -1;
    }
    int j = i + 1;
    while (j < s.len && lower_digit(s.ptr[j])) {
        j++;
    }
    if (j == i + 1 || j == s.len || s.ptr[j] != ',') {
        return -1;
    }
    if (reg) {
        *reg = (Str){s.ptr + i, j - i};
    }
    return j + 1;
}

// \s*([^(]+)\(([^)]+)\) starting at s[a]
static int paren_operand(Str s, int a, Str* operand, Str* inner) {
    int b = a;
    while (b < s.len && ws(s.ptr[b])) {
        b++;
    }
    int start = b;
    if (b == s.len || s.ptr[b] == '(') {
        if (b == a) {
            return 0;
        }
        start = b - 1; // the regex gives back one blank to [^(]+
    }
    const char* k = memchr(s.ptr + start, '(', s.len - start);
    if (!k) {
        return 0;
    }
    int ki = k - s.ptr;
    const char* q = memchr(k + 1, ')', s.len - ki - 1);
    if (!q || q == k + 1) {
        return 0;
    }
    *operand = (Str){s.ptr + start, ki - start};
    if (inner) {
        *inner = (Str){k + 1, (int)(q - k - 1)};
    }
    return 1;
}

static void check_reg(Str r) {
    for (int i = 0; i < r.len; i++) {
        if (r.ptr[i] != '$' && !lower_digit(r.ptr[i])) {
            fail("unsupported register", r);
        }
    }
}

// ^.*\(\s*R\s*\)$
static int m_paren(Str s, Str r) {
    if (!s.len || s.ptr[s.len - 1] != ')') {
        return 0;
    }
    int j = s.len - 1;
    while (j > 0 && ws(s.ptr[j - 1])) {
        j--;
    }
    if (j < r.len || memcmp(s.ptr + j - r.len, r.ptr, r.len)) {
        return 0;
    }
    int k = j - r.len;
    while (k > 0 && ws(s.ptr[k - 1])) {
        k--;
    }
    return k > 0 && s.ptr[k - 1] == '(';
}

// ^R,.*$
static int m_first(Str s, Str r) {
    return s.len > r.len && !memcmp(s.ptr, r.ptr, r.len) && s.ptr[r.len] == ',';
}

// ^.*,\s*R$ ; returns the index of that comma, or -1
static int m_last(Str s, Str r) {
    if (s.len < r.len || memcmp(s.ptr + s.len - r.len, r.ptr, r.len)) {
        return -1;
    }
    int k = s.len - r.len;
    while (k > 0 && ws(s.ptr[k - 1])) {
        k--;
    }
    return k > 0 && s.ptr[k - 1] == ',' ? k - 1 : -1;
}

// ^.*,\s*R,.*$
static int m_middle(Str s, Str r) {
    for (int i = 0; i < s.len; i++) {
        if (s.ptr[i] == ',') {
            int j = i + 1;
            while (j < s.len && ws(s.ptr[j])) {
                j++;
            }
            if (s.len - j > r.len && !memcmp(s.ptr + j, r.ptr, r.len) &&
                s.ptr[j + r.len] == ',') {
                return 1;
            }
        }
    }
    return 0;
}

static int contains_comma_reg(Str s, Str r) {
    for (int i = 0; i + r.len < s.len; i++) {
        if (s.ptr[i] == ',' && !memcmp(s.ptr + i + 1, r.ptr, r.len)) {
            return 1;
        }
    }
    return 0;
}

static int line_loads_from_reg(Str line, Str r) {
    line = strip_comments(line);
    check_reg(r);
    if (!line.len || !az(line.ptr[0])) {
        return 0;
    }
    int i = 1;
    while (i < line.len && (az(line.ptr[i]) || digit(line.ptr[i]))) {
        i++;
    }
    if (i == line.len || !ws(line.ptr[i])) {
        return 0;
    }
    Str op = {line.ptr, i};
    while (i < line.len && ws(line.ptr[i])) {
        i++;
    }
    Str rest = {line.ptr + i, line.len - i};

    if (in(op, LOAD) || eq(op, "lwc2")) {
        return m_paren(rest, r);
    }
    if (in(op, STORE)) {
        return m_paren(rest, r) || m_first(rest, r);
    }
    if (eq(op, "jal")) {
        return m_last(rest, r) >= 0;
    }
    if (eq(op, "j")) {
        return eqs(rest, r);
    }
    if (eq(op, "ctc2") || eq(op, "mtc0") || eq(op, "mtc2")) {
        if (m_first(rest, r)) {
            fail("unsupported coprocessor move", line);
        }
        return 0;
    }
    if (in(op, BRANCH)) {
        return m_first(rest, r) || m_middle(rest, r);
    }
    if (in(op, SINGLE)) {
        if (m_last(rest, r) >= 0) {
            return 1;
        }
        if (starts(op, "mult") && m_first(rest, r)) {
            return 1;
        }
        return (starts(op, "div") || starts(op, "rem")) &&
               contains_comma_reg(rest, r);
    }
    if (in(op, DOUBLE)) {
        if (m_middle(rest, r)) {
            return 1;
        }
        int c = m_last(rest, r);
        return c > 0 && memchr(rest.ptr, ',', c) != NULL;
    }
    return 0;
}

static int uses_at(Str line) {
    line = strip_comments(line);
    Str operand;
    int store = line.len > 2 && line.ptr[0] == 's' &&
                strchr("wbh", line.ptr[1]) && ws(line.ptr[2]);
    if (store) {
        int i = 2;
        while (i < line.len && ws(line.ptr[i])) {
            i++;
        }
        int a = reg_comma(line, i, NULL);
        if (a >= 0) {
            int b = a;
            while (b < line.len && ws(line.ptr[b])) {
                b++;
            }
            // %lo\(([^(]+)\)\(([^)]+)\)
            if (starts((Str){line.ptr + b, line.len - b}, "%lo(")) {
                int c = b + 4;
                const char* k = memchr(line.ptr + c, '(', line.len - c);
                if (k && k - line.ptr > c + 1 && k[-1] == ')') {
                    const char* q =
                        memchr(k + 1, ')', line.ptr + line.len - k - 1);
                    if (q && q > k + 1) {
                        fail("unsupported %lo store", line);
                    }
                }
            }
            int j = b + (b < line.len && line.ptr[b] == '-');
            int k = j;
            while (k < line.len && (az(line.ptr[k]) || digit(line.ptr[k]) ||
                                    line.ptr[k] == '.' || line.ptr[k] == '+')) {
                k++;
            }
            if (k > j && k == line.len) {
                operand = (Str){line.ptr + b, line.len - b};
                if (!is_number(operand)) {
                    return 1;
                }
                goto number;
            }
            if (paren_operand(line, a, &operand, NULL)) {
                goto number;
            }
        }
        return 0;
    }
    if (line.len > 1 && line.ptr[0] == 'l' && line.ptr[1] >= 'a' &&
        line.ptr[1] <= 'z') {
        int i = 1;
        while (i < line.len && line.ptr[i] >= 'a' && line.ptr[i] <= 'z') {
            i++;
        }
        if (i == line.len || !ws(line.ptr[i])) {
            return 0;
        }
        while (i < line.len && ws(line.ptr[i])) {
            i++;
        }
        int a = reg_comma(line, i, NULL);
        if (a >= 0 && paren_operand(line, a, &operand, NULL)) {
            goto number;
        }
    }
    return 0;
number:
    if (is_number(operand)) {
        long long v = py_int(operand, 1, line);
        if (v > -32769 && v < 32768) {
            return 0;
        }
    }
    return 1;
}

typedef struct {
    Str r_source;
    Str r_dest;
    Str operand;
    int is_addend;
} LoadStore;

static LoadStore parse_load_or_store(Str rest, Str line) {
    LoadStore ls;
    int a = reg_comma(rest, 0, &ls.r_dest);
    if (a < 0) {
        fail("unable to parse load/store", line);
    }
    int b = a;
    while (b < rest.len && ws(rest.ptr[b])) {
        b++;
    }
    if (starts((Str){rest.ptr + b, rest.len - b}, "%lo(")) {
        fail("unsupported %lo load/store", line);
    }
    if (!paren_operand(rest, a, &ls.operand, &ls.r_source)) {
        ls.r_source.len = -1;
        int start = b;
        if (b == rest.len || rest.ptr[b] == '(') {
            if (b == a) {
                fail("unable to parse load/store", line);
            }
            start = b - 1;
        }
        const char* k = memchr(rest.ptr + start, '(', rest.len - start);
        ls.operand =
            (Str){rest.ptr + start,
                  (int)((k ? k : rest.ptr + rest.len) - (rest.ptr + start))};
    }
    ls.is_addend = !is_number(ls.operand);
    return ls;
}

static int div_needs_expanding(Str line) {
    Str inst = token(line, 0);
    if (!starts(inst, "div") && !starts(inst, "rem")) {
        return 0;
    }
    Str r = token(line, 1);
    if (r.len < 0) {
        fail("missing operands", line);
    }
    const char* c = memchr(r.ptr, ',', r.len);
    if (c) {
        r.len = c - r.ptr;
    }
    return !eq(r, "$zero") && !eq(r, "$0");
}

// Returns how many instructions it expanded into
static int expand_load_immediate(Str line) {
    if (!starts(line, "li") || line.len < 3 || !ws(line.ptr[2])) {
        fail("li regex failed", line);
    }
    int i = 2;
    while (i < line.len && ws(line.ptr[i])) {
        i++;
    }
    if (i == line.len || line.ptr[i] != '$') {
        fail("li regex failed", line);
    }
    int j = i + 1;
    while (j < line.len && (digit(line.ptr[j]) || az(line.ptr[j]))) {
        j++;
    }
    if (j == i + 1 || j == line.len || line.ptr[j] != ',') {
        fail("li regex failed", line);
    }
    Str r = {line.ptr + i, j - i};
    j++;
    if (j < line.len && ws(line.ptr[j])) {
        j++;
    }
    int k = j + (j < line.len && line.ptr[j] == '-');
    int e = k;
    while (e < line.len && (hexd(line.ptr[e]) || line.ptr[e] == 'x')) {
        e++;
    }
    if (e == k) {
        fail("li regex failed", line);
    }
    long long v = py_int((Str){line.ptr + j, e - j}, 1, line);
    if (v > 0 && v < 0x10000) {
        emit("ori\t%.*s,$zero,%lld", r.len, r.ptr, v);
        return 1;
    }
    if (v >= 0x10000 || v < -0x8000) {
        emit("lui\t%.*s,(%lld >> 16) & 0xFFFF", r.len, r.ptr, v);
        if (v & 0xFFFF) {
            emit("ori\t%.*s,%.*s,%lld & 0xFFFF", r.len, r.ptr, r.len, r.ptr, v);
            return 2;
        }
        return 1;
    }
    if (v < 0 && v > -0x8000) {
        emit("addiu\t%.*s,$zero,%lld", r.len, r.ptr, v);
        return 1;
    }
    if (v == -0x8000) {
        emit("addiu\t%.*s,$zero,%lld & 0xFFFF", r.len, r.ptr, v);
        return 1;
    }
    fail("unsupported li of zero", line);
    return 0;
}

static void emit_expand_move(Str line) {
    line = strip_comments(line);
    Str op = token(line, 0);
    if (op.len < 0) {
        fail("empty instruction", line);
    }
    if (!eq(op, "move")) {
        emit_s(line);
        return;
    }
    char buf[4096];
    if (line.len >= (int)sizeof(buf)) {
        fail("line too long", line);
    }
    Str args = rest_joined(line, buf), rd[2];
    split_comma(args, rd, 2, line);
    emit("addu\t%.*s,%.*s,$zero", rd[0].len, rd[0].ptr, rd[1].len, rd[1].ptr);
}

static int is_instruction(
    Str line, int ignore_nop, int ignore_set, int ignore_label) {
    if (!line.len) {
        return 0;
    }
    if (ignore_nop && eq(line, "#nop")) {
        return 0;
    }
    if (ignore_set &&
        (eq(line, ".set\treorder") || eq(line, ".set\tnoreorder") ||
         eq(line, ".set\tvolatile") || eq(line, ".set\tnovolatile"))) {
        return 0;
    }
    if (ignore_label && is_label(line)) {
        return 0;
    }
    if (starts(line, ".stab")) {
        fail("unsupported stabs", line);
    }
    if (starts(line, ".def") || starts(line, ".bend") ||
        starts(line, ".begin") || starts(line, ".loc")) {
        return 0;
    }
    if (line.ptr[0] == 'L') {
        if (line.len == 1) {
            fail("unsupported label", line);
        }
        if (!digit(line.ptr[1]) && line.ptr[line.len - 1] == ':') {
            return 0;
        }
    }
    return !(eq(line, ".set\tmacro") || eq(line, ".set\tnomacro") ||
             eq(line, "#.set\tvolatile") || eq(line, "#.set\tnovolatile") ||
             eq(line, "#APP") || eq(line, "#NO_APP"));
}

static Str get_next_instruction(
    int skip, int ignore_nop, int ignore_set, int ignore_label) {
    for (int i = line_index + 1; i < nlines; i++) {
        if (is_instruction(lines[i], ignore_nop, ignore_set, ignore_label) &&
            skip-- == 0) {
            return lines[i];
        }
    }
    fail("no next instruction", lines[line_index]);
    return lines[0];
}

static void handle_nop_before_next_instruction(Str next, Str r_dest) {
    if (line_loads_from_reg(next, r_dest) && (!uses_at(next) || is_v221)) {
        Str label = get_next_instruction(0, 1, 1, 0);
        if (is_label(label)) {
            emit_s(label);
            skip_instructions = 1;
        }
        emit("nop");
    }
}

static int handle_mflo_mfhi(Str r_source) {
    if (is_v221) {
        return 0;
    }
    size_t before = out_len;
    Str next = get_next_instruction(0, 1, 1, 1);
    Str next_next = get_next_instruction(1, 1, 1, 1);
    int skip = 0;
    if (starts_any(next, MULT_DIV)) {
        for (;;) {
            Str inst = get_next_instruction(skip++, 0, 0, 0);
            if (eqs(inst, next)) {
                emit("nop\nnop");
                if (div_needs_expanding(inst)) {
                    skip--;
                } else {
                    emit_expand_move(inst);
                }
                break;
            }
            if (inst.ptr[0] != '#') {
                fail("unsupported instruction before mult/div", inst);
            }
        }
        skip_instructions = skip;
    } else if (starts_any(next_next, MULT_DIV)) {
        int no_reorder = 0;
        for (;;) {
            Str inst = get_next_instruction(skip, 0, 0, 0);
            if (starts(inst, ".set") && ends(inst, "noreorder")) {
                no_reorder = 1;
                skip++;
                continue;
            }
            skip++;
            if (eqs(inst, next)) {
                Str op = token(inst, 0);
                if (in(op, LOAD)) {
                    skip = 0;
                    break;
                }
                if (eq(op, "mflo") || eq(op, "mfhi")) {
                    fail("unsupported mflo/mfhi before mult/div", inst);
                }
                if (eq(op, "li")) {
                    if (expand_load_immediate(inst) == 2) {
                        fail("unsupported li before mult/div", inst);
                    }
                    emit("nop");
                } else if (no_reorder) {
                    emit("nop\n.set\tnoreorder");
                    emit_expand_move(inst);
                } else {
                    if (r_source.len > 0 &&
                        line_loads_from_reg(inst, r_source)) {
                        fail("unsupported load before mult/div", inst);
                    }
                    if (is_label(get_next_instruction(skip, 0, 0, 0))) {
                        fail("unsupported label before mult/div", inst);
                    }
                    emit_expand_move(inst);
                    emit("nop");
                }
            } else if (eqs(inst, next_next)) {
                if (div_needs_expanding(inst)) {
                    skip--;
                } else {
                    emit_s(inst);
                }
                break;
            } else if (inst.ptr[0] != '#') {
                fail("unsupported instruction before mult/div", inst);
            }
        }
        skip_instructions = skip;
    }
    return out_len != before;
}

static void emit_expand_at(Str op, LoadStore* ls, int addiu, int source_first) {
    Str o = ls->operand, rs = ls->r_source, rd = ls->r_dest;
    emit(".set\tnoat\nlui\t$at,%%hi(%.*s)", o.len, o.ptr);
    if (addiu) {
        emit("addiu\t$at,$at,%%lo(%.*s)\naddu\t$at,$at,%.*s", o.len, o.ptr,
             rs.len, rs.ptr);
        emit("%.*s\t%.*s,0x0($at)", op.len, op.ptr, rd.len, rd.ptr);
    } else {
        emit(source_first ? "addu\t$at,%.*s,$at" : "addu\t$at,$at,%.*s", rs.len,
             rs.ptr);
        emit("%.*s\t%.*s,%%lo(%.*s)($at)", op.len, op.ptr, rd.len, rd.ptr,
             o.len, o.ptr);
    }
    emit(".set\tat");
}

static int out_of_range(LoadStore* ls, Str line) {
    if (ls->r_source.len <= 0) {
        return 0;
    }
    long long v = py_int(ls->operand, 0, line);
    return v > 32767 || v < -32768;
}

static void emit_div(Str op, Str line) {
    Str a = token(line, 1), r[3];
    if (a.len < 0) {
        fail("missing operands", line);
    }
    split_comma(a, r, 3, line);
    if (eq(r[0], "$zero") || eq(r[0], "$0")) {
        fail("unsupported division into $zero", line);
    }
    int sign = eq(op, "div") || eq(op, "rem");
    const char* move_from = eq(op, "rem") || eq(op, "remu") ? "mfhi" : "mflo";
    int i = line_index;
    emit(".set\tnoat\n%s\t$zero,%.*s,%.*s", sign ? "div" : "divu", r[1].len,
         r[1].ptr, r[2].len, r[2].ptr);
    emit("bnez\t%.*s,.L_NOT_DIV_BY_ZERO_%d\nnop\nbreak\t0x7", r[2].len,
         r[2].ptr, i);
    emit(".L_NOT_DIV_BY_ZERO_%d:", i);
    if (sign) {
        emit("addiu\t$at,$zero,-1");
        emit("bne\t%.*s,$at,.L_DIV_BY_POSITIVE_SIGN_%d", r[2].len, r[2].ptr, i);
        emit("lui\t$at,0x8000");
        emit("bne\t%.*s,$at,.L_DIV_BY_POSITIVE_SIGN_%d", r[1].len, r[1].ptr, i);
        emit("nop\nbreak\t0x6\n.L_DIV_BY_POSITIVE_SIGN_%d:", i);
    }
    emit("%s\t%.*s\n.set\tat", move_from, r[0].len, r[0].ptr);
    if (handle_mflo_mfhi(r[0])) {
        if (!sign) {
            fail("unsupported divu before mult/div", line);
        }
        return;
    }
    handle_nop_before_next_instruction(get_next_instruction(0, 0, 1, 1), r[0]);
}

static void process_line(Str line) {
    if (!line.len) {
        emit_s(line);
        return;
    }
    if (line.ptr[0] == '#') {
        return;
    }
    if (line.ptr[0] == '.') {
        if (starts(line, ".def\t") || starts(line, ".begin\t") ||
            starts(line, ".bend\t")) {
        } else if (starts(line, ".set\t")) {
            if (ends(line, "\tnoreorder")) {
                is_reorder = 0;
            } else if (ends(line, "\treorder")) {
                is_reorder = 1;
            }
        } else if (starts(line, ".file\t")) {
            Str name = token(line, 2);
            if (name.len < 0 || token(line, 3).len >= 0) {
                fail("unexpected .file", line);
            }
            emit(".file\t%d %.*s", file_num++, name.len, name.ptr);
        } else if (starts(line, ".ent\t")) {
            emit_s(line);
            emit(".set\tnoreorder");
        } else if (starts(line, ".comm") || starts(line, ".lcomm")) {
        } else if (starts(line, ".data")) {
            emit(".section .data");
        } else if (starts(line, ".sdata")) {
            fail("unsupported .sdata", line);
        } else if (starts(line, ".rdata")) {
            emit(".section .rodata");
        } else {
            emit_s(line);
        }
        return;
    }
    if (starts(line, "$L")) {
        emit_s(line);
        return;
    }
    if (has(line, ';')) {
        // only the last instruction of a macro matters
        Str m = strip_comments(line), last = {0, -1};
        const char* p = m.ptr;
        for (int i = 0; i <= m.len; i++) {
            if (i == m.len || m.ptr[i] == ';') {
                Str part = trim((Str){p, (int)(m.ptr + i - p)});
                if (part.len) {
                    last = part;
                }
                p = m.ptr + i + 1;
            }
        }
        if (last.len > 0 && in(token(last, 0), LOAD)) {
            fail("unsupported load in macro", line);
        }
    }

    Str op = token(line, 0);
    char buf[4096];
    if (line.len >= (int)sizeof(buf)) {
        fail("line too long", line);
    }
    if (in(op, LOAD)) {
        LoadStore ls = parse_load_or_store(rest_joined(line, buf), line);
        Str next = get_next_instruction(0, 1, 1, 1);
        const char* semi = memchr(next.ptr, ';', next.len);
        if (semi) {
            next.len = semi - next.ptr;
        }
        if (ls.is_addend && ls.r_source.len > 0) {
            emit_expand_at(op, &ls, is_v221, 0);
        } else if (!ls.is_addend && out_of_range(&ls, line)) {
            emit_expand_at(op, &ls, 0, 1);
        } else {
            emit_s(line);
        }
        handle_nop_before_next_instruction(next, ls.r_dest);
    } else if (in(op, STORE)) {
        LoadStore ls = parse_load_or_store(rest_joined(line, buf), line);
        if (ls.is_addend && ls.r_source.len > 0 && is_v221) {
            emit_expand_at(op, &ls, 1, 0);
        } else if (!ls.is_addend && out_of_range(&ls, line)) {
            emit_expand_at(op, &ls, 0, 1);
        } else {
            emit_s(line);
        }
    } else if (in(op, BRANCH_JUMP)) {
        emit_s(line);
        if (is_reorder) {
            emit("nop");
        }
    } else if (eq(op, "move")) {
        emit_expand_move(line);
    } else if (in(op, PLAIN)) {
        emit_s(line);
    } else if (eq(op, "li")) {
        expand_load_immediate(line);
    } else if (eq(op, "li.s") || eq(op, "li.d") || eq(op, "break")) {
        fail("unsupported instruction", line);
    } else if (eq(op, "mflo") || eq(op, "mfhi")) {
        emit_s(line);
        handle_mflo_mfhi((Str){0, -1});
    } else if (
        eq(op, "div") || eq(op, "rem") || eq(op, "divu") || eq(op, "remu")) {
        emit_div(op, line);
    } else if (eq(op, "sltu")) {
        Str a = token(line, 1), r[3];
        if (a.len < 0) {
            fail("missing operands", line);
        }
        split_comma(a, r, 3, line);
        if (is_number(r[2]) && py_int(r[2], 0, line) < 0) {
            emit("li\t$at,%.*s\nsltu\t%.*s,%.*s,$at", r[2].len, r[2].ptr,
                 r[0].len, r[0].ptr, r[1].len, r[1].ptr);
        } else {
            emit_s(line);
        }
    } else {
        emit_s(line);
    }
}

int main(int argc, char** argv) {
    if (argc != 2 || (strcmp(argv[1], "2.34") && strcmp(argv[1], "2.21"))) {
        fail("usage: cmaspsx 2.34|2.21 < input.s > output.s", mk(argv[0]));
    }
    is_v221 = !strcmp(argv[1], "2.21");

    size_t len = 0, cap = 1 << 20;
    char* in = malloc(cap);
    for (ssize_t r; (r = read(0, in + len, cap - len)) > 0;) {
        len += r;
        if (len == cap) {
            in = realloc(in, cap *= 2);
        }
    }
    in[len] = '\0';
    if (strstr(in, ".ent\t__maspsx_include_asm_hack")) {
        fail("unsupported include asm hack", mk(argv[0]));
    }
    int cap_lines = 1024;
    lines = malloc(cap_lines * sizeof(Str));
    for (size_t i = 0, start = 0; i < len; i++) {
        unsigned char c = in[i];
        if ((c < 0x20 && c != '\t' && c != '\n') || c >= 0x7f) {
            fail("only printable ASCII input is supported",
                 (Str){in + start, (int)(i - start)});
        }
        if (c == '\n' || i + 1 == len) {
            if (nlines == cap_lines) {
                lines = realloc(lines, (cap_lines *= 2) * sizeof(Str));
            }
            lines[nlines++] =
                trim((Str){in + start, (int)(i + (c != '\n') - start)});
            start = i + 1;
        }
    }
    if (!nlines) {
        fail("no input from stdin", mk(argv[0]));
    }

    // the .comm symbols become .bss, in order of first appearance
    Str* bss = malloc(nlines * sizeof(Str));
    long long* bss_size = malloc(nlines * sizeof(long long));
    int nbss = 0;
    for (int i = 0; i < nlines; i++) {
        Str l = lines[i];
        if (starts(l, ".sdata")) {
            fail("unsupported .sdata", l);
        }
        if (!starts(l, ".comm") && !starts(l, ".lcomm")) {
            continue;
        }
        Str var = token(l, 1), parts[2];
        if (var.len < 0 || token(l, 2).len >= 0) {
            fail("unexpected .comm", l);
        }
        split_comma(var, parts, 2, l);
        long long size = py_int(parts[1], 0, l);
        if (size <= 0) {
            fail("unsupported .sbss", l);
        }
        int k = 0;
        while (k < nbss && !eqs(bss[k], parts[0])) {
            k++;
        }
        if (k == nbss) {
            bss[nbss++] = parts[0];
        }
        bss_size[k] = size;
    }

    out_cap = len * 2 + 4096;
    out = malloc(out_cap);
    for (int i = 0; i < nlines; i++) {
        Str line = lines[i];
        line_index = i;
        if (is_instruction(line, 0, 0, 0) && skip_instructions > 0) {
            skip_instructions--;
        } else {
            process_line(line);
        }
    }
    if (nbss) {
        emit(".section .bss");
    }
    for (int k = 0; k < nbss; k++) {
        emit("\t.globl %.*s\n%.*s:\n\t.space %lld", bss[k].len, bss[k].ptr,
             bss[k].len, bss[k].ptr, bss_size[k]);
    }
    put("\n", 1);
    for (size_t done = 0; done < out_len;) {
        ssize_t w = write(1, out + done, out_len - done);
        if (w <= 0) {
            return 1;
        }
        done += w;
    }
    return 0;
}
