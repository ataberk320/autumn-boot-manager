CC=clang
CFLAGS=-target x86_64-unknown-none -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-nostdlib -T drv.ld
DRIVERS=mouse fat32

all: $(DRIVERS:%=%.drv)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.drv: %.o
	ld.lld $(LDFLAGS) -o $@ $<

clean:
	rm -f *.o *.drv
