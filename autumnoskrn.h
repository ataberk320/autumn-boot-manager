#pragma once
#include </usr/include/efi/efi.h>
#define MAGIC 0x4E554154

typedef struct {
    UINT32 Magic;
    UINT32 HeaderSize;
    UINT64 EntryPoint;
    UINT64 RequiredMemory;
    UINT64 GopBase;
    UINT64 Reserved[3];

} AUTUMN_KERNEL_HEADER;