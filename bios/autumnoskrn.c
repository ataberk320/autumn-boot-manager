#include "driver_header.h"
#include "IO.H"
#include "KEYBOARD.H"
#include "POWER.H"
__attribute__((section(".multiboot")))
__attribute__((used))
const unsigned int multiboot_header[] = {
    0x1BADB002,
    0x00000000,
    -(0x1BADB002 + 0x00000000)
};



void autumnkernelmain() {
    const char* str = "hello from c kernel!";
    char* vga = (char*)0xB8000;

    for(int i=0; str[i]  != 0; i++) {
        vga [i * 2] = str [i];
        vga [i * 2 + 1] = 0x07;
    }
    
    Entry();
    ACPIDriverEntry();
    

    while (1) {}
}