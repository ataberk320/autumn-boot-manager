
gcc -ffreestanding -mno-red-zone -c autumnoskrn.c -o autumnoskrn.o


cat > kernel.ld << EOF
ENTRY(kernel_main)
SECTIONS
{
    . = 0x0;
    .text : { *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .bss : { *(.bss) *(COMMON) }
}
EOF

ld -nostdlib -T kernel.ld -o autumnoskrn.elf autumnoskrn.o

objcopy -O binary autumnoskrn.elf autumnoskrn.exe
