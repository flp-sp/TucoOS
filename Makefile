AS = nasm
CC = gcc
LD = ld
QEMU = qemu-system-i386

ASFLAGS_BIN = -f bin
ASFLAGS_ELF = -f elf32
CFLAGS = -m32 -ffreestanding -fno-stack-protector -c
LDFLAGS = -m elf_i386 -Ttext 0x1000 --oformat binary

OBJS = entry.o kernel.o video.o shell.o tucoio.o keyboard_handle.o disk.o fs.o
IMG = tucoOS.img

all: $(IMG)

$(IMG): boot.bin kernel.bin
	cat $^ > $@

boot.bin: boot/boot.asm
	$(AS) $(ASFLAGS_BIN) $< -o $@

kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

entry.o: kernel/entry.asm
	$(AS) $(ASFLAGS_ELF) $< -o $@

kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) $< -o $@

video.o: kernel/core/video.c
	$(CC) $(CFLAGS) $< -o $@

shell.o: kernel/core/shell.c
	$(CC) $(CFLAGS) $< -o $@

tucoio.o: kernel/stdlibs/tucoio.c
	$(CC) $(CFLAGS) $< -o $@

keyboard_handle.o: kernel/drivers/keyboard_handle.c
	$(CC) $(CFLAGS) $< -o $@

disk.o: kernel/drivers/disk.c
	$(CC) $(CFLAGS) $< -o $@

fs.o: kernel/core/fs.c
	$(CC) $(CFLAGS) $< -o $@

run: $(IMG)
	$(QEMU) -fda $(IMG)

clear:
	rm -f *.o *.bin