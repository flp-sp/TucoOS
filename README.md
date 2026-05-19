# Tuco OS
Sistema Operacional de desktop criado para propositos educacionais.

## Como rodar
Para rodar sugiro usar o ```qemu``` como virtualizador assim como o [OS Dev Wiki](https://wiki.osdev.org/Expanded_Main_Page) orienta. Seguindo a orientação também foi usado o ```nasm``` como assembler e o ```gcc``` como compilador.

Para facilitar o desenvolvimento, foi está sendo usado um Makefile para fazer toda a montagem, compilação e ligação de forma automática.

Para rodar, primeiramente clone o projeto:
```bash 
git clone https://github.com/flp-sp/TucoOS.git
```
Depois basta rodar o Makefile:
```bash 
make run
```
Para apagar os arquivos gerados use:
```bash 
make clear
```
>Isso não apaga a imagem do sistema operacional `tucoOS.img`

Caso queira rodar novamente sem compilar tudo novamente, apenas rode a imagem usando o qemu:
```bash
qemu-system-i386 -fda tucoOS.img
```
Ou rode em qualquer outra máquina virtual de sua preferência.

## Recursos
O projeto atualmente conta com um bootloader(`boot.asm`) que inicia em real-mode(16 bits), carrega o kernel na memória e passa para o protected-mode(32 bits).

O ```kernel.c``` é o núcleo do sistema operacional, no momento, tem uma shell extremamente básica com alguns comandos de terminal. Tente usar:

```bash
tuco-OS~$ help
```

```bash
echo - imprime uma mensagem na tela
clear - limpa a tela
help - exibe os comandos na tela
shutdown - desliga o computador
sum - soma dois inputs inteiros do teclado
```