# Tuco OS
Sistema Operacional criado para propositos educacionais.

## Como rodar
Para rodar sugiro usar o ```qemu``` como virtualizador assim como o [OS Dev Wiki](https://wiki.osdev.org/Expanded_Main_Page) orienta. Seguindo a orientação também foi usado o ```nasm``` como assembler e o ```gcc``` como compilador.

```
nasm -f bin boot/boot.asm -o boot.bin
```

```
nasm -f elf32 kernel/entry.asm -o entry.o
```

```
gcc -m32 -ffreestanding -fno-stack-protector -c kernel/kernel.c -o kernel.o
```

```
ld -m elf_i386 -o kernel.bin -Ttext 0x1000 entry.o kernel.o --oformat binary
```

```
cat boot.bin kernel.bin > tucoOS.bin
```

```
qemu-system-i386 -fda tucoOS.img
```

## Recursos
O projeto atualmente conta com o ```boot.asm```, um bootloader que inicia em real-mode(16 bits), carrega o kernel na memória e passa para o protected-mode(32 bits).

O ```kernel.c``` é o núcleo do sistema operacional, no momento, tem uma shell extremamente básica com alguns comandos de terminal. Tente usar:

```
tuco-OS~$ help
```

```
echo - imprime uma mensagem na tela
clear - limpa a tela
help - exibe os comandos na tela
shutdown - desliga o computador
sum - soma dois inputs inteiros do teclado
```