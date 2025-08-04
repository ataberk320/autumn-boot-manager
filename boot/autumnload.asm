section .text
global load

extern vm86_start
extern vbe_main

_start:
    call vm86_start
    call vbe_main

    hlt