[BITS 32]
section .data
tss:
    times 104 db 0

section .bss
vm86_stack resb 4096

section .text
global vm86_start

vm86_start:
    mov dword [tss + 4], 0x0
    mov word [tss + 8], 0x10

    mov dword [tss + 20], 0x0000
    mov word [tss + 36], 0x7000

    mov eax, 0x00020200
    mov dword [tss + 24], eax

    mov dword [tss + 28], vm86_stack + 4096
    mov word [tss + 40], 0x9000

    mov word [tss + 44], 0x7000
    mov word [tss + 48], 0x7000
    mov word [tss + 52], 0x7000
    mov word [tss + 56], 0x7000

    mov word [tss + 102], 104

    ; mov ax, 0x28
    ; ltr ax
    ; jmp 0x28:0x0000

    hlt
    jmp $
