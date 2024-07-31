package main

import (
    "bytes"
    "crypto/sha1"
    "encoding/binary"
	"errors"
	"fmt"
	"io/ioutil"
	"os"
    "strings"
)

// Creates a bootstrap stage splat config which can be extended
// when splat finds logiical boundaries.
//
// Usage: sotn-disk bootstrap-stage disks/pspeu/PSP_GAME/USRDIR/res/ps/PSPBIN/sel.bin config/splat.pspeu.stsel.yaml
func bootstrapStage(path string, outPath string) error {
    content, err := ioutil.ReadFile(path)

    if err != nil {
        return err
    }

    if bytes.Equal(content[0:4], []byte("MWo3")) {
        return bootstrapPSP(content, outPath)
    }

    return errors.New("Only PSP objects are supported at this time")
}

func bootstrapPSP(content []byte, outPath string) error {
    if len(content) < 0x80 {
        return errors.New("Expected content of at least 128 bytes long")
    }

    overlayID := content[4]
    loadAddress := binary.LittleEndian.Uint32(content[8:])
    textSectionSize := binary.LittleEndian.Uint32(content[0xC:])
    dataSectionSize := binary.LittleEndian.Uint32(content[0x10:])
    bssSectionSize := binary.LittleEndian.Uint32(content[0x14:])
    bssBegin := binary.LittleEndian.Uint32(content[0x18:])
    name := string(content[0x20:0x80])
    stage_name := name[:strings.Index(name, ".")]
    hasher := sha1.New()
    hasher.Write(content)
    sha := hasher.Sum(nil)

    fmt.Printf("overlay id: 0x%x\n", overlayID)
    fmt.Printf("load addr: 0x%x\n", loadAddress)
    fmt.Printf("text section size: 0x%x\n", textSectionSize)
    fmt.Printf("data section size: 0x%x\n", dataSectionSize)
    fmt.Printf("bss section size: 0x%x\n", bssSectionSize)
    fmt.Printf("bss begin: 0x%x\n", bssBegin)
    fmt.Printf("name: %s\n", name)
    fmt.Printf("stage: %s\n", stage_name)

    f, err := os.Create(outPath)
    if err != nil {
        return err
    }

    fmt.Fprintf(f, `
options:
  platform:     psp
  basename:     dra
  base_path:    ..
  build_path:   build/pspeu
  target_path:  disks/pspeu/PSP_GAME/USRDIR/res/ps/PSPBIN/%s.bin
  asm_path:     asm/pspeu/st/%s_psp
  asset_path:   assets/st/%s
  src_path:     src/st
  ld_script_path: build/pspeu/st%s.ld
  compiler:     GCC
  symbol_addrs_path:
    - config/symbols.pspeu.txt
    - config/symbols.pspeu.st%s.txt
  undefined_funcs_auto_path: config/undefined_funcs_auto.pspeu.st%s.txt
  undefined_syms_auto_path:  config/undefined_syms_auto.pspeu.st%s.txt
  find_file_boundaries: yes
  use_legacy_include_asm: no
  migrate_rodata_to_functions: yes
  asm_jtbl_label_macro: jlabel
  symbol_name_format : psp_$VRAM
  nonmatchings_path: psp
  section_order:
    - ".text"
    - ".data"
    - ".rodata"
    - ".bss"
  ld_bss_is_noload: True
  disasm_unknown: True
  asm_inc_header: |
    .set noat      /* allow manual use of $at */
    .set noreorder /* don't insert nops after branches */
    .include "macro.inc"
sha1: %x

segments:
  - [0x0, bin, mwo_header]
  - name: st%s
    type: code
    start: 0x00000080
    vram:  0x09237700
    bss_size: 0x%x
    align: 128
    subalign: 8
    subsegments:
      - [0x80, c, %s_psp/80]
      - [0x%x, data]
      - [0x%x, bss]
  - [0x%x]
`, stage_name, stage_name, stage_name, stage_name, stage_name, stage_name, stage_name,
sha, stage_name,
bssSectionSize, stage_name, bssBegin - loadAddress - dataSectionSize, bssBegin - loadAddress,
bssBegin - loadAddress)
    return nil
}
