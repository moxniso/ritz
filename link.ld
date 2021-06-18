OUTPUT_FORMAT("binary")
OUTPUT(ritz.bin)
INPUT(boot.o)
SECTIONS
{
   . = 0x7c00;
   .text : { *(.boot) *(.text) }
   .rodata : { *(.rodata) }
   .data : { *(.data) }
   .bss : { *(.bss) }
}
