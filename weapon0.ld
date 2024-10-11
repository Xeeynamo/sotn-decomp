SECTIONS {
    .WEAPON_OVL 0x8017A000 : AT(0) SUBALIGN(4)
    {
        *(.data)
        *(.rodata)
        *(.text)
        *(.bss)
    }

    end = .;
}
