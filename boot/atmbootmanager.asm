[BITS 32]
[ORG 0x100000]

MB_MAGIC equ 0x1BADB002
MB_FLAGS equ 0x00010003
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

section .multiboot
align 4
    dd MB_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM

section .text
global _start
_start:

    mov si, msg_loading
    call print_string

    mov esi, 0x20000
    call load_kernel

    jmp 0x20000

load_kernel:
    mov ah, 0x02
    mov al, 10
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80

    mov bx, 0x2000
    mov es, bx
    mov bx, 0x0000

    int 0x13
    jc disk_error
    ret

disk_error:
    mov si, msg_error
    call print_string
    cli 
    hlt

print_string:
    mov ah, 0x0E

.next_char:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .next_char

.done:
    ret


section .data
msg_loading db "Input 1 (AutumnOS) will start automatically"
msg_error db "File autumnoskrn.exe is not found. System halted. Please load a copy of this file and try again to boot."
