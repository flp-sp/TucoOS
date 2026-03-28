# Tuco OS
Sistema Operacional criado para propositos educacionais

## Como rodar
Para rodar sugiro usar o ```qemu``` como virtualizador assim como o [OS Dev Wiki](https://wiki.osdev.org/Expanded_Main_Page) orienta. Seguindo a orientação também foi usado o ```nasm``` como assembler.

```
nasm boot/boot.asm -f bin -o boot/boot.bin
```

```
qemu-system-i386 -fda boot/boot.bin
```

## Recursos
Atualmente o arquivo ```boot.asm``` é apenas o esqueleto de um bootloader, ja que nao carrega o kernel em si, mas ele ja consegue ser reconhecido pela BIOS e fazer a transiçao do realmode(16 bits) para o protectedmode(32 bits) e exibir uma mensagem de boas vindas usando VGA.