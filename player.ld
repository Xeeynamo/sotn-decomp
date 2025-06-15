SECTIONS {
    . = 0x8013C000;
    .data : {
        *(.data*)
    }
    .rodata : {
        *(.rodata*)
    }
    .text : {
        *(.text*)
    }
    end = .;
}
