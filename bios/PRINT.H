#ifndef _PRINT_H
#define _PRINT_H

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void putchar (char c);
void print(const char* str);
void print_hex(uint32_t num, int digits);
void print_dec(uint32_t num);
void printf(const char* fmt, ...);

#endif
