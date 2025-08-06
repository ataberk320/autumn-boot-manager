#include "IO.H"
#include "KEYBOARD.H"
#include <stdint.h>

int input_bf_full() {
    return inb(0x64) & 0x02;
}

int output_bf_full() {
    return inb(0x64) & 0x01;
}

void wait_input_clear() {
    while (input_bf_full()) {}
}

void wait_output_ready() {
    while (!output_bf_full()) {}

}

void Entry() {
    wait_input_clear();
    outb(0x64, 0xAE);

    wait_input_clear();
    outb(0x64, 0x20);

    wait_output_ready();
    uint8_t status = inb(0x60);

    status |= 1;

    wait_input_clear();
    outb(0x64, 0x60);
    
    wait_input_clear();
    outb(0x60, status);

    wait_input_clear();
    outb(0x60, 0xF4);

    
}