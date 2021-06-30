OUTPUT_FORMAT("binary")
INPUT(BIN_DIR/src/boot/boot.s.o)
SECTIONS
{
   . = 0x7c00;
   .text : { *(.boot) *(.text) }
   .rodata : { *(.rodata) }
   .data : { *(.data) }
   .bss : { *(.bss) }
}
