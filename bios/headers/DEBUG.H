#ifndef DEBUG_H
#define DEBUG_H

void init();
void serial_write(const char* str);

#define DEBUG_LOG(msg) serial_write("[DEBUG]: " msg "\n")
#endif