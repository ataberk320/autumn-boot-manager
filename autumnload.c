#include </usr/include/efi/efi.h>
#include </usr/include/efi/efilib.h>

EFI_STATUS EFIAPI load_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTab) {
    SystemTab->ConOut->ClearScreen(SystemTab->ConOut);
    SystemTab->ConOut->OutputString(SystemTab->ConOut, L"hello guys ;)");
    while (1);
    return EFI_SUCCESS;
}