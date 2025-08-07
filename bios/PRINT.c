
#include "PRINT.H"
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
uint16_t* const VGA_BUFFER = (uint16_t*) VGA_ADDRESS;
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;



void putchar (char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= VGA_HEIGHT) cursor_y = 0;
        return;

    }
    uint16_t pos = cursor_y * VGA_WIDTH +cursor_x;
        VGA_BUFFER[pos] = ((0x07) << 8) | c;
    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= VGA_HEIGHT) cursor_y = 0;
    }
}

void print (const char* str) {
    for (size_t i = 0; str[i] != 0; i++) {
        putchar(str[i]);
    }
}

void print_hex(uint32_t num, int digits) {
    const char *hex = "0123456789ABCDEF";
    for (int i = (digits - 1) * 4; i >= 0; i -= 4) {
        putchar(hex[(num >> i) & 0xF]);
    }
}


void print_dec(uint32_t num) {
    char buffer[11];
    int i = 10;
    buffer[i--] = '\0';
    if (num == 0) {
        buffer[i] = '0';
        print(&buffer[i]);
        return;
    }
    while (num && i >= 0) {
        buffer[i--] = '0' + (num % 10);
        num /= 10;
    }
    print(&buffer[i + 1]);
}

void printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    for (const char* p = fmt; *p != '\0'; p++) {
        if (*p == '%') {
            p++;
            int digits = 8; // default

            // Çok basamaklı width kontrolü:
            if (*p == '0') {
                p++;
                digits = 0;
                while (*p >= '0' && *p <= '9') {
                    digits = digits * 10 + (*p - '0');
                    p++;
                }
            }

            switch (*p) {
                case 'x':
                case 'X': {
                    uint32_t val = va_arg(args, uint32_t);
                    print("0x");
                    print_hex(val, digits > 0 ? digits : 8);
                    break;
                }
                case 'd':
                case 'u': {
                    uint32_t val = va_arg(args, uint32_t);
                    print_dec(val);
                    break;
                }
                case 's': {
                    char* s = va_arg(args, char*);
                    print(s);
                    break;
                }
                case 'c': {
                    char c = (char) va_arg(args, int);
                    putchar(c);
                    break;
                }
                case '%': {
                    putchar('%');
                    break;
                }
                default: {
                    putchar('%');
                    putchar(*p);
                    break;
                }
            }
        } else {
            putchar(*p);
        }
    }

    va_end(args);
}


