#!/bin/bash

set -e

KERNEL_NAME="autumnoskrn.exe"
ISO_NAME="autumnos.iso"
BUILD_DIR="build"
ISO_DIR="$BUILD_DIR/iso"
BOOT_DIR="$ISO_DIR/boot"
GRUB_DIR="$BOOT_DIR/grub"
AUTUMN32_DIR="$ISO_DIR/AUTUMN32"

echo "[0] Temizlik yapılıyor..."
rm -rf "$BUILD_DIR"
mkdir -p "$GRUB_DIR"
mkdir -p "$AUTUMN32_DIR"

echo "[1] Kernel ve sürücüler derleniyor..."
gcc -m32 -ffreestanding -c autumnoskrn.c -o "$BUILD_DIR/autumnoskrn.o"
gcc -m32 -ffreestanding -c IO.c -o "$BUILD_DIR/io.o"
gcc -m32 -ffreestanding -c KEYBOARD.c -o "$BUILD_DIR/keyboard.o"
gcc -m32 -ffreestanding -c ACPI.c -o "$BUILD_DIR/acpi.o"

echo "[2] Linkleme..."
gcc -m32 -ffreestanding -nostdlib -T linker.ld \
  "$BUILD_DIR/autumnoskrn.o" \
  "$BUILD_DIR/io.o" \
  "$BUILD_DIR/keyboard.o" \
  "$BUILD_DIR/acpi.o" \
  -o "$AUTUMN32_DIR/$KERNEL_NAME"

echo "[3] GRUB konfigürasyonu yazılıyor..."
cat > "$GRUB_DIR/grub.cfg" <<EOF
menuentry "AutumnOS" {
    multiboot /AUTUMN32/$KERNEL_NAME
    boot
}
EOF

echo "[4] ISO oluşturuluyor..."
grub-mkrescue -o "$ISO_NAME" "$ISO_DIR" > /dev/null 2>&1

echo "[✔] ISO hazır: $ISO_NAME"

read -p "QEMU ile başlatılsın mı? (e/h): " cevap
if [[ "$cevap" == "e" ]]; then
    qemu-system-i386 -cdrom "$ISO_NAME" -serial stdio
else
    echo "Tamamlandı."
fi

