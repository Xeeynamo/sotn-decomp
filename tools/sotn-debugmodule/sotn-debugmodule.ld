SECTIONS {
    . = 0x80280000;

    .inject : {
        *(.inject-head*)
        *(.inject-func*)
    }

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
