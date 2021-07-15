OUTPUT_FORMAT(elf32-i386)
ENTRY(_start32)
SECTIONS
{
   . = 0x100000;
   .text : ALIGN(4) { *(.text) }
   .rodata : ALIGN(4) { *(.rodata) }
   .data : ALIGN(4) { *(.data) }
   .bss : ALIGN(4) { *(.bss) }
}
