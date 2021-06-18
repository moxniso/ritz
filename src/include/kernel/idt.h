#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct IDTe {
        uint16 offset_lowerbits;
        uint16 selector;
        uint8 zero;
        uint8 type_attr;
        uint16 offset_higherbits;
} IDT; 

#define IDT_SIZE 256

void init_idt(void);
void load_idt(uintl32* a);
void rk_syscall(void);
void syscall_handle(int eax, int ebx, int ecx);
void kbhandle(void);

#endif /* IDT_H */
        
