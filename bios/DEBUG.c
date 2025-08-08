#include "headers/IO.H"
#include "headers/DEBUG.H"

#define COM1 0x3F8

void init() {
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x03);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);
}

int is_ready() {
    return inb(COM1 + 5) & 0x20;

}

void writec(char c) {
    while (!is_ready());
    outb(COM1, c);

}


void serial_write(const char* str) {
    while (*str) {
        if (*str == '\n') {
            writec('\r');
        }
        writec(*str++);
    }
}