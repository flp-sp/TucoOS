nasm -f bin boot/boot.asm -o boot.bin
nasm -f elf32 kernel/entry.asm -o entry.o
gcc -m32 -ffreestanding -fno-stack-protector -c kernel/kernel.c -o kernel.o
ld -m elf_i386 -o kernel.bin -Ttext 0x1000 entry.o kernel.o --oformat binary
cat boot.bin kernel.bin > tucoOS.bin

qemu-system-i386 -fda tucoOS.bin