#include </usr/include/efi/efi.h>
#include </usr/include/efi/efilib.h>
#include <stddef.h>

EFI_GUID gEfiGraphicsOutputProtocolGuid;
EFI_GUID gEfiFileInfoGuid;
EFI_GUID gEfiSimpleFileSystemProtocolGuid;

VOID *Align8(VOID *Buffer);

void *memcpy(void *dest, const void *src, unsigned long len)  {
    unsigned char *d = dest;
    const unsigned char *s = src;
    while (len--) {
        *d++ = *s++;
    }
    return dest;
}
VOID *memset(VOID *dest, INT32 value, UINTN count) {
    UINT8 *ptr = (UINT8 *)dest;
    while (count--) {
        *ptr++ = (UINT8)value;

    }
    return dest;
}

VOID ZeroMem(VOID *Buffer, UINTN Size) {
    UINT8 *Ptr = (UINT8 *)Buffer;
    for (UINTN i = 0; i < Size; i++) {
        Ptr[i] = 0;
    }
}


VOID StatusShow(EFI_SYSTEM_TABLE *SystemTable, EFI_STATUS Status) {
    CHAR16 HexChars[] = L"0123456789ABCDEF";
    CHAR16 Buffer[20];
    UINTN i;

    Buffer[0] = L'S';
    Buffer[1] = L't';
    Buffer[2] = L'a';
    Buffer[3] = L't';
    Buffer[4] = L'u';
    Buffer[5] = L's';
    Buffer[6] = L':';
    Buffer[7] = L' ';
    Buffer[8] = L'0';
    Buffer[9] = L'x';

    for (i = 0; i < 16; i++) {
        UINTN Shift = (15 - i) * 4;
        UINTN Digit = (Status >> Shift) & 0xF;
        Buffer[10 + i] = HexChars[Digit];
    }
    Buffer[10 + 16] = L'\r';
    Buffer[10 + 17] = L'\n';
    Buffer[10 + 18] = 0;

    SystemTable->ConOut->OutputString(SystemTable->ConOut, Buffer);
}

CHAR16* ShowStatusString (EFI_STATUS status) {
    switch (status) {
        case EFI_SUCCESS: return L"EFI_SUCCESS";
        case EFI_LOAD_ERROR: return L"EFI_LOAD_ERROR";
        case EFI_INVALID_PARAMETER: return L"EFI_INVALID_PARAMETER";
         case EFI_UNSUPPORTED: return L"EFI_UNSUPPORTED";
        case EFI_NOT_FOUND: return L"EFI_NOT_FOUND";
        case EFI_ACCESS_DENIED: return L"EFI_ACCESS_DENIED";
        case EFI_OUT_OF_RESOURCES: return L"EFI_OUT_OF_RESOURCES";
        default: return L"EFI_UNKNOWN_STATUS";
    }
}


VOID *AllocateZeroedPool(EFI_SYSTEM_TABLE *SystemTable, UINTN Size) {
    VOID *Buffer;
    if (SystemTable->BootServices->AllocatePool(EfiLoaderData, Size, &Buffer) != EFI_SUCCESS) {
        return NULL;
    }
    SystemTable->BootServices->SetMem(Buffer, Size, 0);
    return Buffer;
}


VOID *Align8(VOID *Buffer) {
    return (VOID*)(((UINTN)Buffer + 7) & ~((UINTN)7));
}









EFI_STATUS Kernel(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    EFI_STATUS Status;
    EFI_HANDLE KernelImageHandle = NULL;
    CHAR16 *KernelPath = L"\\EFI\\AUTUMN\\autumnload.efi";

    Status = SystemTable->BootServices->LoadImage(FALSE, ImageHandle, NULL, (VOID*)KernelPath, sizeof(KernelPath), &KernelImageHandle);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = SystemTable->BootServices->StartImage(KernelImageHandle, NULL, NULL);

     if (EFI_ERROR(Status)) {
        return Status;
    }
}


















EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    EFI_BOOT_SERVICES *BootServices = SystemTable->BootServices;
    EFI_HANDLE DeviceHandle = ImageHandle;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFileSystem;

    EFI_STATUS Status;
    UINTN index=1;
       EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFS;
    EFI_FILE_PROTOCOL *Root;
    EFI_FILE_PROTOCOL *File;
    EFI_BOOT_SERVICES *BS;



    VOID *Buffer = NULL;
    UINTN BufferSize = 0;
    UINTN Size = 0;
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"------------------------------Autumn Boot Manager-------------------------------");
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_GREEN);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"To boot, select an OS to start.");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"To start tools, select 'Tools' and press Enter.");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"1 - AutumnOS 2.0\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"2 - Tools\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"The selected operating system will start in 5 seconds");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"------------------------------©Leaves Development-------------------------------");
       
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_YELLOW);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"ESC = Reset, T = Select an input, E = Boot, POWER = Shutdown, S = Settings");
    while (1) {
        EFI_INPUT_KEY key;
        EFI_STATUS Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key);
        if (Status == EFI_SUCCESS) {
            if (key.UnicodeChar == L'1')
            {
                 index = 1;
            }
            if (key.UnicodeChar == L'2')
            {
                 index = 2;
            }
            if (key.UnicodeChar == L'e' || key.UnicodeChar == L'E') {
                if (index == 1) {
                   Status = Kernel(ImageHandle, SystemTable);
            
 
                      
            if (EFI_ERROR (Status)) {
                    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
                    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"------------------------------Autumn Boot Manager-------------------------------");
                    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_GREEN);
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Your computer encountered a fatal trouble and needs to be repaired.\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Reason: Loader is missing or corrupted. Please load a copy of this file and try again.\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"File: /EFI/AUTUMN/autumnload.efi\r\n");
                    StatusShow(SystemTable, Status);
                    
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, ShowStatusString(Status));
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
                    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_YELLOW);
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Press ESC to reset and return to bootloader.\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Press E/e to try again.\r\n");

                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hold power button to shut down.\r\n");

       
    
                }
            }

                else
                {
                    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
                    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"---------------------------------Boot Tools---------------------------------\r\n");
                    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_GREEN);
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"1 - Autumn Recovery Tools Interface\r\n");
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"2 - Terminal");
                }
                    
                

            
 
                    
                


            }
            if (key.ScanCode == SCAN_ESC)
            {
                SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
            }
            if (key.UnicodeChar == L's' || key.UnicodeChar == L'S') {
                SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
                SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);
                SystemTable->ConOut->OutputString(SystemTable->ConOut, L"------------------------------Autumn Boot Settings------------------------------");
                SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_GREEN);
                SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Automatic boot time: 5 seconds\r\n");
                SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Secure Boot: True\r\n");
                SystemTable->ConOut->OutputString(SystemTable->ConOut, L"----------------------------------------------------------------------------------");
            }
        }
    }
    return EFI_SUCCESS;
}
