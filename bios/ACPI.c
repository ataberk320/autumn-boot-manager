#include <stdint.h>
#include "POWER.H"
#include "IO.H"
#include "PRINT.H"


int memcmp(const void* s1, const void* s2, unsigned int n) {
    const unsigned char* p1 = (const unsigned char*)s1;
    const unsigned char* p2 = (const unsigned char*)s2;

    for (unsigned int i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}


RSDPDescriptor* find_rsdp() {
    for (uint8_t addr = (uint8_t*)0xE0000; addr < (uint8_t*)0x100000; addr += 16) {
        if (memcmp(addr, "RSD PTR ", 8) == 0) {
            return (RSDPDescriptor*) addr;

        }
    }
    return 0;
}

FADT* find_fadt(RSDPDescriptor* rsdp) {
    ACPISDTHeader* rsdt = (ACPISDTHeader*)(uintptr_t)(rsdp->rsdt_address);
     int entries = (rsdt->length - sizeof(ACPISDTHeader)) / 4;
    uint32_t* entry_ptr = (uint32_t*)((uintptr_t)rsdt + sizeof(ACPISDTHeader));
    for (int i = 0; i < entries; i++) {
        ACPISDTHeader* header = (ACPISDTHeader*)(uintptr_t)(entry_ptr[i]);
        if (memcmp(header->signature, "FACP", 4) == 0) {
            return (FADT*)header;
        }
    }
    return 0;
}

void acpi_sleep(FADT* fadt, uint8_t sleep_type) {
    uint16_t pm1a_cnt_port = (uint16_t)(fadt->pm1a_cnt_blk & 0xFFFF);
    uint16_t pm1b_cnt_port = (uint16_t)(fadt->pm1b_cnt_blk & 0xFFFF);

    uint16_t val = inw(pm1a_cnt_port);

    val &= ~(0x7 << 10);
    val |= ((sleep_type & 0x7) << 10);

    val |= (1 << 13);

    outw(pm1a_cnt_port, val);

    if (pm1b_cnt_port != 0) {
        outw(pm1b_cnt_port, val);
    }

}

void acpi_shutdown(FADT* fadt) {
    acpi_sleep(fadt, 5);
}

void acpi_reboot(FADT *fadt) {
    outb (0x64, 0xFE);
}

void acpi_suspend(FADT* fadt){
    acpi_sleep(fadt, 3);
}

void ACPIDriverEntry() {


    RSDPDescriptor* rsdp = find_rsdp();
    if (!rsdp) {
        print("System cannot start because no RSDP found!\n");
    }

    FADT* fadt = find_fadt(rsdp);
    if (!fadt) {
        print("FADT not found!\n");
    }

    print("[ACPI]: ACPI initialized\n");

}