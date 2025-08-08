#include <stdint.h>
#include "headers/IO.H"
#include "headers/KEYBOARD.H"
#include "headers/POWER.H"
#include "headers/PRINT.H"
#include "headers/DEBUG.H"


                          
__attribute__((section(".multiboot"), used))
static const uint32_t multiboot_header[] = {
    0x1BADB002,
    0x00000003,
    -(0x1BADB002 + 0x00000003)
};


        




void autumnkernelmain() {
    init();
    
    DEBUG_LOG("debug started!");
    print("hello from 32-bit c kernel!\n");
    DriverEntry();
    Entry();
    ACPIDriverEntry();
    

    while (1);
}