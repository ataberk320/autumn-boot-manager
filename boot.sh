#!/bin/bash
set -e

clang \
  --target=x86_64-unknown-windows \
  -ffreestanding -fshort-wchar -mno-red-zone \
  -I /usr/include/efi -I /usr/include/efi/x86_64 \
  -c atmbootmanager.c -o atmbootmanager.o

clang \
  --target=x86_64-unknown-windows \
  -nostdlib \
  -Wl,-entry:efi_main \
  -Wl,-subsystem:efi_application \
  -fuse-ld=lld-link \
  atmbootmanager.o \
  -o atmbootmanager.efi     

clang \
  --target=x86_64-unknown-windows \
  -ffreestanding -fshort-wchar -mno-red-zone \
  -I /usr/include/efi -I /usr/include/efi/x86_64 \
  -c autumnload.c -o autumnload.o

clang \
  --target=x86_64-unknown-windows \
  -ffreestanding -fshort-wchar -mno-red-zone \
  -nostdlib \
  -fuse-ld=lld-link \
  -Wl,-entry:load_main \
  -Wl,-subsystem:efi_application \
  autumnload.o -o autumnload.efi

   
mkdir -p iso_root/EFI/BOOT
mkdir -p iso_root/EFI/AUTUMN
mkdir -p iso_root/boot/grub

cp atmbootmanager.efi iso_root/EFI/AUTUMN/
cp autumnload.efi iso_root/EFI/AUTUMN

cat > iso_root/boot/grub/grub.cfg <<EOF
timeout=0
default=0
menuentry "Autumn Boot Manager" {
    insmod part_gpt
    insmod fat
    search --no-floppy --file /EFI/AUTUMN/atmbootmanager.efi --set=root
    chainloader /EFI/AUTUMN/atmbootmanager.efi
}
EOF

grub-mkimage -O x86_64-efi -o BOOTX64.EFI \
  -p /boot/grub \
  part_gpt fat ext2 chain search configfile \
  gfxterm gfxmenu png jpeg font video video_fb terminal

cp BOOTX64.EFI iso_root/EFI/BOOT/

grub-mkrescue -o AutumnOS.iso iso_root
