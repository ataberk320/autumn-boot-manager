[BITS 32]
global vbe_main
extern vbe_callback

section .data
vbe_stack_bottom:
    resb 4096
    
vbe_stack_top:

vbe_vm86_code:
    db 0xFB

    mov ax, 0x4F00
    mov di, 0x1000
    int 0x10

    mov ax, 0x4F01
    mov cx, 0x118
    mov di, 0x1100
    int 0x10   

    mov ax, 0x4F02
    mov bx, 0x4118
    int 0x10

    hlt
    jmp $

vbe_vm86_code_end:
section .text

vbe_main:
    pusha

    mov eax, vbe_stack_top
    mov ss, ax
    mov esp, eax

    mov ax, 0x0000
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    pushfd
    pop eax
    or eax, (1 << 17)
    push eax
    popfd

    push word 0x0000
    push word vbe_vm86_code

    iretd

.hang:
    hlt
    jmp .hang
