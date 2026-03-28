[BITS 16]
[ORG 0x7c00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    sti

load_PM:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or al, 1
    mov cr0,eax
    jmp 0x08:PModeMain


gdt_start:
    dd 0x00000000
    dd 0x00000000

    dw 0xffff
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

    dw 0xffff
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

[BITS 32]
PModeMain:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x9c00
    mov esp, ebp

    in al, 0x92
    or al, 2
    out 0x92, al

    mov edi, 0xb8000
    mov esi, msg
println:
    lodsb
    cmp al, 0
    je hang
    mov ah, 0x02
    mov [edi], ax
    add edi, 2
    jmp println

hang:
    jmp $

msg: db "Bem vindo ao TucoOS",0

times 510 - ($ - $$) db 0
dw 0xaa55