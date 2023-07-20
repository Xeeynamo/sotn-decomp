SECTIONS {
    . = 0x80170000;

    .data* : {
        *(.data*)
    }

    .rodata* : {
        *(.rodata*)
    }

    .text* : {
        *(.text*)
    }

    end = .;
}
