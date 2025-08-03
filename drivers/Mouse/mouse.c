
void wait() {
    while (!(inb(0x64) & 1));
}

void write(uint8_t val) {
    wait();
    outb(0x64, 0xD4);
    wait();
    outb(0x60, val);
}

void init() {
    outb (0x64, 0xA8);

    outb(0x64,0x20);
    uint8_t status = inb(0x60);
    status |= 2;
    outb(0x64, 0x60);
    outb(0x60, status);

    write(0xF6);
    write(0xF4);

}  
void handler(void) {
    static uint8_t cycle = 0;
    static int8_t mouse_bytes [3];

    if(!(inb(0x64)& 1)) return;
    mouse_bytes[cycle++] = inb(0x60);

    if (cycle == 3) {
        cycle = 0;
        int dx = mouse_bytes[1];
        int dy = mouse_bytes[2];
        mouse_x += dx;
        mouse_y -= dy;
    }
}

void getpos (int *x, int *y) {
    *x = mouse_x;
    *y = mouse_y;
}

__attribute__((visibility("default")))
void entry() {
    init();
}
