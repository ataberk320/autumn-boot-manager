# 1) Derle .o dosyasına (standalone, freestanding)
gcc -ffreestanding -mno-red-zone -c autumnoskrn.c -o autumnoskrn.o

# 2) Linker script dosyası: kernel.ld (basit örnek)
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

# 3) Linkle ELF oluştur
ld -nostdlib -T kernel.ld -o autumnoskrn.elf autumnoskrn.o

# 4) ELF'den raw binary çıkar
objcopy -O binary autumnoskrn.elf autumnoskrn.exe
