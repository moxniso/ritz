#include <kernel/idt.h>
#include <kernel/kcommon.h>
#include <kernel/kcore.h>
#include <kernel/kpanic.h>
#include <stdint.h>

// Many many thanks to the various online resources that show how to set
// up a proper IDT.

IDT ridt[IDT_SIZE];
extern void rk_divpanic();

// Macro for setting IDT entry
#define sie(entryb, func) ridt[entryb].offset_lowerbits = (((uintl32)func) & 0xffff); \
                                    ridt[entryb].selector = 0x08; \
                                    ridt[entryb].zero = 0; \
                                    ridt[entryb].type_attr = 0x8e; \
                                    ridt[entryb].offset_higherbits = ((((uintl32)func) & 0xffff0000) >> 16)        

void init_idt(void)
{   
    // Map CPU exceptions to kernel panic routines
    sie(0x00, phandle0);
    sie(0x01, phandle1);
    sie(0x02, phandle2);
    sie(0x03, phandle3);
    sie(0x04, phandle4);
    sie(0x05, phandle5);
    sie(0x06, phandle6);
    sie(0x07, phandle7);
    sie(0x08, phandle8);
    sie(0x09, phandle9);
    sie(0x10, phandle10);
    sie(0x11, phandle11);
    sie(0x12, phandle12);
    sie(0x13, phandle13);
    sie(0x14, phandle14);
    sie(0x15, phandle15);
    sie(0x16, phandle16);
    sie(0x17, phandle17);
    sie(0x18, phandle18);
 
    sie(0x50, rk_syscall);
    
    /*         PIC1 PIC2
    * Command: 0x20 0xA0
    * Data:    0x21 0xA1
    */
    
    // Begin init
    rk_writeport(0x20, 0x11);
    rk_writeport(0xA0, 0x11);
    
    // Remap offset (First 32 interrupts are reserved by CPU for exceptions, 0x00 to 0x20)
    rk_writeport(0x21, 0x50); // PIC1 | 0x51
    rk_writeport(0xA1, 0x51); // PIC2 | 0x52
    
    // disable cascading
    rk_writeport(0x21, 0x00);
    rk_writeport(0xA1, 0x00);
    
    // environment info
    rk_writeport(0x21, 0x01);
    rk_writeport(0xA1, 0x01);
    
    // mask interrupts
    rk_writeport(0x21, 0xff);
    rk_writeport(0xA1, 0xff);
    
    uintl32 ridt_addr = (uintl32)ridt;
    uintl32 ridt_ptr[2] = {(sizeof (IDT) * IDT_SIZE) + ((ridt_addr & 0xffff) << 16), 
                                 (ridt_addr >> 16)};
    
    load_idt(ridt_ptr);
}
    
    
