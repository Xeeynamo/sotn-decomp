# This template file is not yet used
options:
  platform: ${platform}
  basename: ${basename}
  base_path: ..
  build_path: ${build_path}
  target_path: disks/pspeu/PSP_GAME/USRDIR/res/ps/PSPBIN/dai.bin
  asm_path: asm/pspeu/st/dai_psp
  asset_path: assets/st/dai
  src_path: src/st
  ld_script_path: build/pspeu/stdai.ld
  compiler: GCC
  symbol_addrs_path:
    - config/symbols.pspeu.txt
    - config/symbols.pspeu.stdai.txt
  undefined_funcs_auto_path: config/undefined_funcs_auto.pspeu.stdai.txt
  undefined_syms_auto_path: config/undefined_syms_auto.pspeu.stdai.txt
  find_file_boundaries: true
  use_legacy_include_asm: false
  migrate_rodata_to_functions: true
  asm_jtbl_label_macro: jlabel
  symbol_name_format: pspeu_$VRAM
  nonmatchings_path: nonmatchings
  disassemble_all: true
  section_order:
    - .text
    - .data
    - .rodata
    - .bss
  ld_bss_is_noload: true
  disasm_unknown: true
  global_vram_start: 0x08000000
  ld_generate_symbol_per_data_segment: true
  # psp only
  asm_inc_header: |
    .set noat      /* allow manual use of $at */
    .set noreorder /* don't insert nops after branches */
sha1: 91f0ea1eaff4cf7a3773ee63cf516ef167bf73e3
segments:
# psp only
  - [0x0, bin, mwo_header]
  - name: stdai
    type: code
    start: 0x80
    vram: 0x09237700
    # Only present for psp, None will be passed for psx
    bss_start_address: 0x09297000
    # Only present for psp, None will be passed for psx
    bss_size: 0x900
    align: 128
    subalign: 8
    subsegments:
      - [0x80, c, dai_psp/first_dai]
      - [0x23780, data]
      - [0x5F680, .rodata, dai_psp/first_dai]
      - [0x5F980, bss]
  - [0x60280]
