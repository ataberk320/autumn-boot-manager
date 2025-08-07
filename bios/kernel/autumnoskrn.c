#include <stdint.h>
#include "IO.H"
#include "KEYBOARD.H"
#include "POWER.H"
#include "PRINT.H"
#include "PCI.H"

                          
__attribute__((section(".multiboot"), used))
static const uint32_t multiboot_header[] = {
    0x1BADB002,
    0x00000000,
    -(0x1BADB002 + 0x00000000)
};


        




void autumnkernelmain() {
    print("hello from 32-bit c kernel!\n");
    DriverEntry();
    Entry();
    ACPIDriverEntry();
    PCIEntry();

    while (1) {}
}
