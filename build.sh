#!/bin/bash

# TODO: replace this with a proper fucking Makefile

rm bin/objs/*.o bin/ritz.bin
# I have to manually go into src/include because NASM wont %include right if I don't :/
cd src/include/
nasm -f elf32 ../boot/boot.s -o boot.o
mv *.o ../../

cd ../boot/
gcc -c -m32 -nodefaultlibs -nostdlib -fno-builtin -I../include/ -fno-pic kstart.c
mv *.o ../../

cd ../kernel
gcc -c -m32 -nodefaultlibs -nostdlib -fno-builtin -I../include/ -fno-pic *.c
nasm -f elf32 k_io.s 
nasm -f elf32 idt.s -o idt_s.o
mv *.o ../../

cd ../shell
gcc -c -m32 -nodefaultlibs -nostdlib -fno-builtin -Wno-incompatible-pointer-types -I../include/ -fno-pic *.c
nasm -f elf32 kcmds.s -o kcmds.o
mv *.o ../../

cd ../graphics/
gcc -c -m32 -nodefaultlibs -nostdlib -fno-builtin -I../include/ -fno-pic *.c
mv *.o ../../

cd ../rlibc/
gcc -c -m32 -nodefaultlibs -nostdlib -fno-builtin -I../include/ -fno-pic *.c
nasm -f elf32 kcall.s -o kcall_s.o
nasm -f elf32 stdio.s -o stdio.o
mv *.o ../../

cd ../../
ld -T link.ld -m elf_i386 *.o
mv *.o bin/objs/
mv ritz.bin bin/
qemu-system-x86_64 -fda bin/ritz.bin -cpu pentium -soundhw pcspk

