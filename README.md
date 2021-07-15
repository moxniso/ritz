# ritz by moxniso

Requirements to build:
* gcc
* ld
* nasm

To build and test:
``make``
``make test``
This utilizes qemu-system-i386 to test with 

To install on real hardware with GRUB, add this to your grub.conf:
```
title Ritz32
	root (hd0,0)
	kernel /path/to/ritz-001 ro
``` 

TODO:
* Add FAT32 filesystem drivers
* Write some proper documentation for the ABI
* Further flesh out the VGA driver 

Note: Ritz (working name btw) is a very WIP OS! 
There may be random crashes or failures to boot on real hardware. 
Please do report any such occurences along with debug output (registers, stack frame,
etc).

``media/ritztan_13h.png`` drawn by Sebastian#9999