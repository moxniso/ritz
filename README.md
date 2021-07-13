# ritz by moxniso

Requirements to build:
* gcc
* ld
* nasm

To build and test:
``make``
``make test``
This utilizes qemu-system-i386 to test with 

To flash to USB: 
``sudo dd if=ritz.bin of=/dev/sdb bs=4M conv=fdatasync``

TODO:
* Add FAT32 filesystem drivers
* Implement ELF parser to load in kernel
from memory instead of having one big static binary
* Write some documentation for the ABI

Note: Ritz (working name btw) is a very WIP OS! 
There may be random crashes or failures to boot on real hardware. 
Please do report any such occurences along with debug output (registers, stack frame,
etc).
