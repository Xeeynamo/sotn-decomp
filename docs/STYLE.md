# Castlevania Symphony of the Night decompilation style guide

## Types

Use the types from `types.h`, not the standard C types: i.e. `u8`,`s8`,`s16`,`u16`,`s32`,`u32` rather than `char`, `short`, `int`, `float` and their `signed`/`unsigned` varieties.

We always write our enums and structs as `typedef`s. (Usually one can't use an enum typedef as a function argument since enum typedefs are implicitly `s32`.)

## Naming

| Type                 | Style                   | Example                 |
| -------------------- | ----------------------- | ----------------------- |
| Local variables      | camelCase               | `entityRotation`        |
| Global variables     | g_PascalCase            | `g_SettingsSoundMode`   |
| Static variables[^1] | s_PascalCase            | `s_ZeroVec`             |
| Struct members       | camelCase               | `hitboxWidth`           |
| Struct types         | PascalCase              | `RoomHeader`            |
| Enum types           | PascalCase              | `EntitySteps`           |
| Enum values          | SCREAMING_SNAKE_CASE    | `ENTITY_STEP_0`         |
| Defines/macros       | SCREAMING_SNAKE_CASE    | `PAD_UP`,`GET_PLAYER(x)`|
| Functions            | PascalCase              | `UpdateAccel`           |
| Files                | snake_case              | `include_asm.h`         |

[^1]: including in-function static

Ideally names should be both short and clear, although it's better to be clear than short.

## Formatting

A lot of formatting is done by clang-format, such as

- indent is 4 spaces, tabs are not used
- case labels indented
- 80 column limit
- brackets go on the same line (`if (1) {`)
- pointer goes on type (`s32* var;` not `s32 *var;`)

There are various other conventions that it does not catch, though:

- Blank line between declarations and code:

  ```c
  s32 var;
  
  func();
  ```

- combine declarations and definitions if possible:

  ```c
  s32 var = 0;
  
  func();
  ```

  instead of

  ```c
  s32 var;
  
  var = 0;
  func();
  ```

- blank lines between switch cases.

## Numbers

### dec(imal)

- timers
- colours and alpha
- Usually array accesses and sizes

### hex(adecimal)

- angles (for now; the code itself is very inconsistent with round hex, round dec, and degrees)
- Addresses
- Bitmasks (i.e. `& 0x80` etc.)
- Struct offset comments

### Booleans

If a function returns only `0` or `1`, and is used as a boolean (i.e. in conditionals), use `bool` type and replace the returns by `false` and `true`.

## Conditionals/Loops

- Spacing out conditional or loop blocks from surrounding code often makes them easier to read.
- We *always* use `{}` on conditional/loop blocks, even if they're one line
- When conditions are `&&`d or `||`d together, use brackets around each that includes an arithmetic comparison or bitwise operator (i.e. not `!var` or `func()`, but ones with `==` or `&` etc.)
- Flag checks or functions that return booleans do not need the `== 0`/`!= 0`.
- Prefer `if-else` over `if { return; }`, i.e.

**Exception**: There are instances when at the beginning of a function you want to return immediately if a validation fails so the rest of the body wouldn't be indented in an else if. See `func_8010189C` for an example.

  ```c
  if (cond) {
      foo();
  } else {
      bar();
  }
  ```

  over

  ```c
  if (cond) {
      foo();
      return;
  }
  bar();
  ```

  Become familiar with the various defines and enums we have available.

- Those in `macros.h`
  - `ABS`, `ABS_ALT`,
  - `CLAMP` and friends.

  ## Arrays

- It's better to not hardcode array sizes (easier to mod)
- Use `sizeof` or `ARRAY_COUNT`/`ARRAY_COUNTU` where it makes sense, e.g. in loops that are using an array.
- clang-format sometimes does weird things to array formatting. Experiment with and without a comma after the last element and see which looks better.

## Documentation and Comments

Documentation includes:

- Naming functions
- Naming struct variables
- Naming data
- Naming local variables
- Describing the general purpose of the file
- Describing any unusual, interesting or strange features of how the file or parts of its content work
- Labelling and explaining bugs

If you are not sure what something does, it is better to leave it unnamed than name it wrongly. It is fine to make a note of something you are not sure about when PRing, it means the reviewers will pay special attention to it.

We use comments for:

- Top of file: a short description of the system. For overlays there is already a brief description of our current understanding, but feel free to add to it.
- For function descriptions, we use multiline comments,

  ```c
  /**
   * Describe what the function does
   */
  ```

  These are *optional*: if you think the code is clear enough, you do not need to put a comment.
  - If something in a function is strange, or unintuitive, do leave a comment explaining what's going on. We use `//` for this.
  - A bug should be commented with an `//! @bug Bug description` above the code that causes the bug.
  - A fake should be commented with an `// !FAKE:` above or to the side of the code that you think it's fake.

### Functions

All functions should go in the main C file in the same order as the assembly (the latter is required to match anyway).
